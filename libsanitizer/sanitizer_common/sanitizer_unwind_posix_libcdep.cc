//===-- sanitizer_unwind_posix.cc ----------------------------------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the unwind.h-based (aka "slow") stack unwinding routines
// available to the tools on Linux, Android, FreeBSD and OS X.
//===----------------------------------------------------------------------===//

#include "sanitizer_platform.h"
#if SANITIZER_POSIX
#include "sanitizer_common.h"
#include "sanitizer_stacktrace.h"

#if SANITIZER_ANDROID
#include <dlfcn.h>  // for dlopen()
#endif

#if SANITIZER_FREEBSD
#define _GNU_SOURCE  // to declare _Unwind_Backtrace() from <unwind.h>
#endif
#include <unwind.h>

namespace __sanitizer {

//------------------------- SlowUnwindStack -----------------------------------

typedef struct {
  uptr absolute_pc;
  uptr stack_top;
  uptr stack_size;
} backtrace_frame_t;

extern "C" {
typedef void *(*acquire_my_map_info_list_func)();
typedef void (*release_my_map_info_list_func)(void *map);
typedef sptr (*unwind_backtrace_signal_arch_func)(
    void *siginfo, void *sigcontext, void *map_info_list,
    backtrace_frame_t *backtrace, uptr ignore_depth, uptr max_depth);
acquire_my_map_info_list_func acquire_my_map_info_list;
release_my_map_info_list_func release_my_map_info_list;
unwind_backtrace_signal_arch_func unwind_backtrace_signal_arch;
} // extern "C"

#if SANITIZER_ANDROID
void SanitizerInitializeUnwinder() {
  void *p = dlopen("libcorkscrew.so", RTLD_LAZY);
  if (!p) {
    VReport(1,
            "Failed to open libcorkscrew.so. You may see broken stack traces "
            "in SEGV reports.");
    return;
  }
  acquire_my_map_info_list =
      (acquire_my_map_info_list_func)(uptr)dlsym(p, "acquire_my_map_info_list");
  release_my_map_info_list =
      (release_my_map_info_list_func)(uptr)dlsym(p, "release_my_map_info_list");
  unwind_backtrace_signal_arch = (unwind_backtrace_signal_arch_func)(uptr)dlsym(
      p, "unwind_backtrace_signal_arch");
  if (!acquire_my_map_info_list || !release_my_map_info_list ||
      !unwind_backtrace_signal_arch) {
    VReport(1,
            "Failed to find one of the required symbols in libcorkscrew.so. "
            "You may see broken stack traces in SEGV reports.");
    acquire_my_map_info_list = 0;
    unwind_backtrace_signal_arch = 0;
    release_my_map_info_list = 0;
  }
}
#endif

#ifdef __arm__
#define UNWIND_STOP _URC_END_OF_STACK
#define UNWIND_CONTINUE _URC_NO_REASON
#else
#define UNWIND_STOP _URC_NORMAL_STOP
#define UNWIND_CONTINUE _URC_NO_REASON
#endif

uptr Unwind_GetIP(struct _Unwind_Context *ctx) {
#ifdef __arm__
  uptr val;
  _Unwind_VRS_Result res = _Unwind_VRS_Get(ctx, _UVRSC_CORE,
      15 /* r15 = PC */, _UVRSD_UINT32, &val);
  CHECK(res == _UVRSR_OK && "_Unwind_VRS_Get failed");
  // Clear the Thumb bit.
  return val & ~(uptr)1;
#else
  return _Unwind_GetIP(ctx);
#endif
}

struct UnwindTraceArg {
  StackTrace *stack;
  uptr max_depth;
};

_Unwind_Reason_Code Unwind_Trace(struct _Unwind_Context *ctx, void *param) {
  UnwindTraceArg *arg = (UnwindTraceArg*)param;
  CHECK_LT(arg->stack->size, arg->max_depth);
  uptr pc = Unwind_GetIP(ctx);
  arg->stack->trace[arg->stack->size++] = pc;
  if (arg->stack->size == arg->max_depth) return UNWIND_STOP;
  return UNWIND_CONTINUE;
}

void StackTrace::SlowUnwindStack(uptr pc, uptr max_depth) {
  CHECK_GE(max_depth, 2);
  size = 0;
  UnwindTraceArg arg = {this, Min(max_depth + 1, kStackTraceMax)};
  _Unwind_Backtrace(Unwind_Trace, &arg);
  // We need to pop a few frames so that pc is on top.
  uptr to_pop = LocatePcInTrace(pc);
  // trace[0] belongs to the current function so we always pop it.
  if (to_pop == 0)
    to_pop = 1;
  PopStackFrames(to_pop);
  trace[0] = pc;
}

void StackTrace::SlowUnwindStackWithContext(uptr pc, void *context,
                                            uptr max_depth) {
  CHECK_GE(max_depth, 2);
  if (!unwind_backtrace_signal_arch) {
    SlowUnwindStack(pc, max_depth);
    return;
  }

  void *map = acquire_my_map_info_list();
  CHECK(map);
  InternalScopedBuffer<backtrace_frame_t> frames(kStackTraceMax);
  // siginfo argument appears to be unused.
  sptr res = unwind_backtrace_signal_arch(/* siginfo */ 0, context, map,
                                          frames.data(),
                                          /* ignore_depth */ 0, max_depth);
  release_my_map_info_list(map);
  if (res < 0) return;
  CHECK_LE((uptr)res, kStackTraceMax);

  size = 0;
  // +2 compensate for libcorkscrew unwinder returning addresses of call
  // instructions instead of raw return addresses.
  for (sptr i = 0; i < res; ++i)
    trace[size++] = frames[i].absolute_pc + 2;
}

}  // namespace __sanitizer

#endif  // SANITIZER_POSIX
