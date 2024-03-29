## Makefile for the C++03 sources of the GNU C++ Standard library.
##
## Copyright (C) 1997-2014 Free Software Foundation, Inc.
##
## This file is part of the libstdc++ version 3 distribution.
## Process this file with automake to produce Makefile.in.

## This file is part of the GNU ISO C++ Library.  This library is free
## software; you can redistribute it and/or modify it under the
## terms of the GNU General Public License as published by the
## Free Software Foundation; either version 3, or (at your option)
## any later version.

## This library is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.

## You should have received a copy of the GNU General Public License along
## with this library; see the file COPYING3.  If not see
## <http://www.gnu.org/licenses/>.

include $(top_srcdir)/fragment.am

# Convenience library for C++98 runtime.
noinst_LTLIBRARIES = libc++98convenience.la 

headers =

# Source files linked in via configuration/make substitution for a
# particular host.
host_sources = \
	atomicity.cc \
	codecvt_members.cc \
	collate_members.cc \
	messages_members.cc \
	monetary_members.cc \
	numeric_members.cc \
	time_members.cc

codecvt_members.cc: ${glibcxx_srcdir}/$(CCODECVT_CC)
	$(LN_S) ${glibcxx_srcdir}/$(CCODECVT_CC) . || true

collate_members.cc: ${glibcxx_srcdir}/$(CCOLLATE_CC)
	$(LN_S) ${glibcxx_srcdir}/$(CCOLLATE_CC) . || true

messages_members.cc: ${glibcxx_srcdir}/$(CMESSAGES_CC)
	$(LN_S) ${glibcxx_srcdir}/$(CMESSAGES_CC) . || true

monetary_members.cc: ${glibcxx_srcdir}/$(CMONEY_CC)
	$(LN_S) ${glibcxx_srcdir}/$(CMONEY_CC) . || true

numeric_members.cc: ${glibcxx_srcdir}/$(CNUMERIC_CC)
	$(LN_S) ${glibcxx_srcdir}/$(CNUMERIC_CC) . || true

time_members.cc: ${glibcxx_srcdir}/$(CTIME_CC)
	$(LN_S) ${glibcxx_srcdir}/$(CTIME_CC) . || true

atomicity_file = ${glibcxx_srcdir}/$(ATOMICITY_SRCDIR)/atomicity.h
atomicity.cc: ${atomicity_file}
	$(LN_S) ${atomicity_file} ./atomicity.cc || true

# Source files linked in via configuration/make substitution for a
# particular host, but with ad hoc naming rules.
host_sources_extra = \
	basic_file.cc c++locale.cc \
	${inst_sources} ${parallel_sources}

c++locale.cc: ${glibcxx_srcdir}/$(CLOCALE_CC)
	$(LN_S) ${glibcxx_srcdir}/$(CLOCALE_CC) ./$@ || true

basic_file.cc: ${glibcxx_srcdir}/$(BASIC_FILE_CC)
	$(LN_S) ${glibcxx_srcdir}/$(BASIC_FILE_CC) ./$@ || true


if ENABLE_EXTERN_TEMPLATE
# XTEMPLATE_FLAGS = -fno-implicit-templates
inst_sources = \
	allocator-inst.cc \
	concept-inst.cc \
	ext-inst.cc \
	locale-inst.cc \
	misc-inst.cc \
	wlocale-inst.cc
else
# XTEMPLATE_FLAGS =
inst_sources =
endif

parallel_sources = parallel_settings.cc

# Sources present in the src directory, always present.
sources = \
	bitmap_allocator.cc \
	pool_allocator.cc \
	mt_allocator.cc \
	codecvt.cc \
	complex_io.cc \
	globals_io.cc \
	hash_tr1.cc \
	hashtable_tr1.cc \
	ios_failure.cc \
	ios_init.cc \
	ios_locale.cc \
	list.cc \
	list-aux.cc \
	list-aux-2.cc \
	list_associated.cc \
	list_associated-2.cc \
	locale.cc \
	locale_init.cc \
	locale_facets.cc \
	localename.cc \
	math_stubs_float.cc \
	math_stubs_long_double.cc \
	stdexcept.cc \
	strstream.cc \
	tree.cc \
	istream.cc \
	streambuf.cc \
	valarray.cc \
	${host_sources} \
	${host_sources_extra}

vpath % $(top_srcdir)/src/c++98

libc__98convenience_la_SOURCES = $(sources)

# Use special rules for the deprecated source files so that they find
# deprecated include files.
GLIBCXX_INCLUDE_DIR=$(glibcxx_builddir)/include
strstream.lo: strstream.cc
	$(LTCXXCOMPILE) -I$(GLIBCXX_INCLUDE_DIR)/backward -Wno-deprecated -c $<
strstream.o: strstream.cc
	$(CXXCOMPILE) -I$(GLIBCXX_INCLUDE_DIR)/backward -Wno-deprecated -c $<

# Use special rules for the concept-checking instantiations so that all
# the generated template functions are also instantiated.  Force the checks
# to be on so that the instantiations are actually seen.
concept-inst.lo: concept-inst.cc
	$(LTCXXCOMPILE) -D_GLIBCXX_CONCEPT_CHECKS -fimplicit-templates -c $<
concept-inst.o: concept-inst.cc
	$(CXXCOMPILE) -D_GLIBCXX_CONCEPT_CHECKS -fimplicit-templates -c $<

# Use special rules for parallel mode compilation.
PARALLEL_FLAGS = -D_GLIBCXX_PARALLEL 
parallel_settings.lo: parallel_settings.cc
	$(LTCXXCOMPILE) $(PARALLEL_FLAGS) -c $<
parallel_settings.o: parallel_settings.cc
	$(CXXCOMPILE) $(PARALLEL_FLAGS) -c $<

# AM_CXXFLAGS needs to be in each subdirectory so that it can be
# modified in a per-library or per-sub-library way.  Need to manually
# set this option because CONFIG_CXXFLAGS has to be after
# OPTIMIZE_CXXFLAGS on the compile line so that -O2 can be overridden
# as the occasion calls for it.
AM_CXXFLAGS = \
	$(glibcxx_lt_pic_flag) $(glibcxx_compiler_shared_flag) \
	$(XTEMPLATE_FLAGS) $(VTV_CXXFLAGS) \
	$(WARN_CXXFLAGS) $(OPTIMIZE_CXXFLAGS) $(CONFIG_CXXFLAGS)

AM_MAKEFLAGS = \
	"gxx_include_dir=$(gxx_include_dir)"

# Libtool notes

# 1) In general, libtool expects an argument such as `--tag=CXX' when
# using the C++ compiler, because that will enable the settings
# detected when C++ support was being configured.  However, when no
# such flag is given in the command line, libtool attempts to figure
# it out by matching the compiler name in each configuration section
# against a prefix of the command line.  The problem is that, if the
# compiler name and its initial flags stored in the libtool
# configuration file don't match those in the command line, libtool
# can't decide which configuration to use, and it gives up.  The
# correct solution is to add `--tag CXX' to LTCXXCOMPILE and maybe
# CXXLINK, just after $(LIBTOOL), so that libtool doesn't have to
# attempt to infer which configuration to use.
# 
# The second tag argument, `--tag disable-shared` means that libtool
# only compiles each source once, for static objects. In actuality,
# glibcxx_lt_pic_flag and glibcxx_compiler_shared_flag are added to
# the libtool command that is used create the object, which is
# suitable for shared libraries.  The `--tag disable-shared` must be
# placed after --tag CXX lest things CXX undo the affect of
# disable-shared.

# 2) Need to explicitly set LTCXXCOMPILE so that EXTRA_CXX_FLAGS is
# last. (That way, things like -O2 passed down from the toplevel can
# be overridden by --enable-debug.)
LTCXXCOMPILE = \
	$(LIBTOOL) --tag CXX --tag disable-shared \
	$(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) \
	--mode=compile $(CXX) $(TOPLEVEL_INCLUDES) \
	$(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CXXFLAGS) $(CXXFLAGS) $(EXTRA_CXX_FLAGS)

LTLDFLAGS = $(shell $(SHELL) $(top_srcdir)/../libtool-ldflags $(LDFLAGS))

# 3) We'd have a problem when building the shared libstdc++ object if
# the rules automake generates would be used.  We cannot allow g++ to
# be used since this would add -lstdc++ to the link line which of
# course is problematic at this point.  So, we get the top-level
# directory to configure libstdc++-v3 to use gcc as the C++
# compilation driver.
CXXLINK = \
	$(LIBTOOL) --tag CXX --tag disable-shared \
	$(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) \
	--mode=link $(CXX) \
	$(VTV_CXXLINKFLAGS) \
	$(OPT_LDFLAGS) $(SECTION_LDFLAGS) $(AM_CXXFLAGS) $(LTLDFLAGS) -o $@
