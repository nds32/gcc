// { dg-do compile { target c++11 } }

struct A { };
struct B { B(); operator int(); };
struct C {
  C() = default;
  C(const C&);
  C(C&&) = default;
  C& operator=(C&&);
  C& operator= (const C&) = default;
};
struct D { ~D() {} };

#define SA(X) static_assert((X),#X)

SA(__is_trivially_constructible(A));
SA(__is_trivially_constructible(A,A));
SA(!__is_trivially_constructible(B));
SA(__is_trivially_constructible(B,B));

SA(!__is_trivially_constructible(A,B));
SA(!__is_trivially_constructible(B,A));

SA(__is_trivially_constructible(C));
SA(__is_trivially_constructible(C,C));
SA(!__is_trivially_constructible(C,C&));
SA(__is_trivially_assignable(C,C&));
SA(!__is_trivially_assignable(C,C));
SA(!__is_trivially_assignable(C,C&&));

SA(__is_trivially_constructible(int,int));
SA(__is_trivially_constructible(int,double));
SA(!__is_trivially_constructible(int,B));

SA(!__is_trivially_constructible(D));
