//  Boost operators.hpp header file  ----------------------------------------//

//  (C) Copyright David Abrahams, Jeremy Siek, Daryle Walker 1999-2001.
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/utility/operators.htm for documentation.

//  Revision History
//  22 Feb 16 Preserve old work-arounds. (Daniel Frey)
//  16 Dec 10 Limit warning suppression for 4284 to older versions of VC++
//            (Matthew Bradbury, fixes #4432)
//  07 Aug 08 Added "euclidean" spelling. (Daniel Frey)
//  03 Apr 08 Make sure "convertible to bool" is sufficient
//            for T::operator<, etc. (Daniel Frey)
//  24 May 07 Changed empty_base to depend on T, see
//            http://svn.boost.org/trac/boost/ticket/979
//  21 Oct 02 Modified implementation of operators to allow compilers with a
//            correct named return value optimization (NRVO) to produce optimal
//            code.  (Daniel Frey)
//  02 Dec 01 Bug fixed in random_access_iteratable.  (Helmut Zeisel)
//  28 Sep 01 Factored out iterator operator groups.  (Daryle Walker)
//  27 Aug 01 'left' form for non commutative operators added;
//            additional classes for groups of related operators added;
//            workaround for empty base class optimization
//            bug of GCC 3.0 (Helmut Zeisel)
//  25 Jun 01 output_iterator_helper changes: removed default template 
//            parameters, added support for self-proxying, additional 
//            documentation and tests (Aleksey Gurtovoy)
//  29 May 01 Added operator classes for << and >>.  Added input and output
//            iterator helper classes.  Added classes to connect equality and
//            relational operators.  Added classes for groups of related
//            operators.  Reimplemented example operator and iterator helper
//            classes in terms of the new groups.  (Daryle Walker, with help
//            from Alexy Gurtovoy)
//  11 Feb 01 Fixed bugs in the iterator helpers which prevented explicitly
//            supplied arguments from actually being used (Dave Abrahams)
//  04 Jul 00 Fixed NO_OPERATORS_IN_NAMESPACE bugs, major cleanup and
//            refactoring of compiler workarounds, additional documentation
//            (Alexy Gurtovoy and Mark Rodgers with some help and prompting from
//            Dave Abrahams) 
//  28 Jun 00 General cleanup and integration of bugfixes from Mark Rodgers and
//            Jeremy Siek (Dave Abrahams)
//  20 Jun 00 Changes to accommodate Borland C++Builder 4 and Borland C++ 5.5
//            (Mark Rodgers)
//  20 Jun 00 Minor fixes to the prior revision (Aleksey Gurtovoy)
//  10 Jun 00 Support for the base class chaining technique was added
//            (Aleksey Gurtovoy). See documentation and the comments below 
//            for the details. 
//  12 Dec 99 Initial version with iterator operators (Jeremy Siek)
//  18 Nov 99 Change name "divideable" to "dividable", remove unnecessary
//            specializations of dividable, subtractable, modable (Ed Brey) 
//  17 Nov 99 Add comments (Beman Dawes)
//            Remove unnecessary specialization of operators<> (Ed Brey)
//  15 Nov 99 Fix less_than_comparable<T,U> second operand type for first two
//            operators.(Beman Dawes)
//  12 Nov 99 Add operators templates (Ed Brey)
//  11 Nov 99 Add single template parameter version for compilers without
//            partial specialization (Beman Dawes)
//  10 Nov 99 Initial version

// 10 Jun 00:
// An additional optional template parameter was added to most of 
// operator templates to support the base class chaining technique (see 
// documentation for the details). Unfortunately, a straightforward
// implementation of this change would have broken compatibility with the
// previous version of the library by making it impossible to use the same
// template name (e.g. 'addable') for both the 1- and 2-argument versions of
// an operator template. This implementation solves the backward-compatibility
// issue at the cost of some simplicity.
//
// One of the complications is an existence of special auxiliary class template
// 'is_chained_base<>' (see 'detail' namespace below), which is used
// to determine whether its template parameter is a library's operator template
// or not. You have to specialize 'is_chained_base<>' for each new 
// operator template you add to the library.
//
// However, most of the non-trivial implementation details are hidden behind 
// several local macros defined below, and as soon as you understand them,
// you understand the whole library implementation. 

#ifndef BOOST_OPERATORS_V1_HPP
#define BOOST_OPERATORS_V1_HPP

#include <cstddef>
#include <iterator>

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#if defined(__sgi) && !defined(__GNUC__)
#   pragma set woff 1234
#endif

#if BOOST_WORKAROUND(BOOST_MSVC, < 1600)
#   pragma warning( disable : 4284 ) // complaint about return type of 
#endif                               // operator-> not begin a UDT

namespace boost {
namespace detail {

template <typename T> class empty_base {};

} // namespace detail
} // namespace boost

// In this section we supply the xxxx1 and xxxx2 forms of the operator
// templates, which are explicitly targeted at the 1-type-argument and
// 2-type-argument operator forms, respectively. Some compilers get confused
// when inline friend functions are overloaded in namespaces other than the
// global namespace. When BOOST_NO_OPERATORS_IN_NAMESPACE is defined, all of
// these templates must go in the global namespace.

#ifndef BOOST_NO_OPERATORS_IN_NAMESPACE
namespace boost
{
#endif

//  Basic operator classes (contributed by Dave Abrahams) ------------------//

//  Note that friend functions defined in a class are implicitly inline.
//  See the C++ std, 11.4 [class.friend] paragraph 5

template <class T, class U, class B = ::boost::detail::empty_base<T> >
struct less_than_comparable2 : B
{
     friend bool operator<=(const T& x, const U& y) { return !static_cast<bool>(x > y); }
     friend bool operator>=(const T& x, const U& y) { return !static_cast<bool>(x < y); }
     friend bool operator>(const U& x, const T& y)  { return y < x; }
     friend bool operator<(const U& x, const T& y)  { return y > x; }
     friend bool operator<=(const U& x, const T& y) { return !static_cast<bool>(y < x); }
     friend bool operator>=(const U& x, const T& y) { return !static_cast<bool>(y > x); }
};

template <class T, class B = ::boost::detail::empty_base<T> >
struct less_than_comparable1 : B
{
     friend bool operator>(const T& x, const T& y)  { return y < x; }
     friend bool operator<=(const T& x, const T& y) { return !static_cast<bool>(y < x); }
     friend bool operator>=(const T& x, const T& y) { return !static_cast<bool>(x < y); }
};

template <class T, class U, class B = ::boost::detail::empty_base<T> >
struct equality_comparable2 : B
{
     friend bool operator==(const U& y, const T& x) { return x == y; }
     friend bool operator!=(const U& y, const T& x) { return !static_cast<bool>(x == y); }
     friend bool operator!=(const T& y, const U& x) { return !static_cast<bool>(y == x); }
};

template <class T, class B = ::boost::detail::empty_base<T> >
struct equality_comparable1 : B
{
     friend bool operator!=(const T& x, const T& y) { return !static_cast<bool>(x == y); }
};

// A macro which produces "name_2left" from "name".
#define BOOST_OPERATOR2_LEFT(name) name##2##_##left

//  NRVO-friendly implementation (contributed by Daniel Frey) ---------------//

#if defined(BOOST_HAS_NRVO) || defined(BOOST_FORCE_SYMMETRIC_OPERATORS)

// This is the optimal implementation for ISO/ANSI C++,
// but it requires the compiler to implement the NRVO.
// If the compiler has no NRVO, this is the best symmetric
// implementation available.

#define BOOST_BINARY_OPERATOR_COMMUTATIVE( NAME, OP )                         \
template <class T, class U, class B = ::boost::detail::empty_base<T> >        \
struct NAME##2 : B                                                            \
{                                                                             \
  friend T operator OP( const T& lhs, const U& rhs )                          \
    { T nrv( lhs ); nrv OP##= rhs; return nrv; }                              \
  friend T operator OP( const U& lhs, const T& rhs )                          \
    { T nrv( rhs ); nrv OP##= lhs; return nrv; }                              \
};                                                                            \
                                                                              \
template <class T, class B = ::boost::detail::empty_base<T> >                 \
struct NAME##1 : B                                                            \
{                                                                             \
  friend T operator OP( const T& lhs, const T& rhs )                          \
    { T nrv( lhs ); nrv OP##= rhs; return nrv; }                              \
};

#define BOOST_BINARY_OPERATOR_NON_COMMUTATIVE( NAME, OP )               \
template <class T, class U, class B = ::boost::detail::empty_base<T> >  \
struct NAME##2 : B                                                      \
{                                                                       \
  friend T operator OP( const T& lhs, const U& rhs )                    \
    { T nrv( lhs ); nrv OP##= rhs; return nrv; }                        \
};                                                                      \
                                                                        \
template <class T, class U, class B = ::boost::detail::empty_base<T> >  \
struct BOOST_OPERATOR2_LEFT(NAME) : B                                   \
{                                                                       \
  friend T operator OP( const U& lhs, const T& rhs )                    \
    { T nrv( lhs ); nrv OP##= rhs; return nrv; }                        \
};                                                                      \
                                                                        \
template <class T, class B = ::boost::detail::empty_base<T> >           \
struct NAME##1 : B                                                      \
{                                                                       \
  friend T operator OP( const T& lhs, const T& rhs )                    \
    { T nrv( lhs ); nrv OP##= rhs; return nrv; }                        \
};

#else // defined(BOOST_HAS_NRVO) || defined(BOOST_FORCE_SYMMETRIC_OPERATORS)

// For compilers without NRVO the following code is optimal, but not
// symmetric!  Note that the implementation of
// BOOST_OPERATOR2_LEFT(NAME) only looks cool, but doesn't provide
// optimization opportunities to the compiler :)

#define BOOST_BINARY_OPERATOR_COMMUTATIVE( NAME, OP )                   \
template <class T, class U, class B = ::boost::detail::empty_base<T> >  \
struct NAME##2 : B                                                      \
{                                                                       \
  friend T operator OP( T lhs, const U& rhs ) { return lhs OP##= rhs; } \
  friend T operator OP( const U& lhs, T rhs ) { return rhs OP##= lhs; } \
};                                                                      \
                                                                        \
template <class T, class B = ::boost::detail::empty_base<T> >           \
struct NAME##1 : B                                                      \
{                                                                       \
  friend T operator OP( T lhs, const T& rhs ) { return lhs OP##= rhs; } \
};

#define BOOST_BINARY_OPERATOR_NON_COMMUTATIVE( NAME, OP )               \
template <class T, class U, class B = ::boost::detail::empty_base<T> >  \
struct NAME##2 : B                                                      \
{                                                                       \
  friend T operator OP( T lhs, const U& rhs ) { return lhs OP##= rhs; } \
};                                                                      \
                                                                        \
template <class T, class U, class B = ::boost::detail::empty_base<T> >  \
struct BOOST_OPERATOR2_LEFT(NAME) : B                                   \
{                                                                       \
  friend T operator OP( const U& lhs, const T& rhs )                    \
    { return T( lhs ) OP##= rhs; }                                      \
};                                                                      \
                                                                        \
template <class T, class B = ::boost::detail::empty_base<T> >           \
struct NAME##1 : B                                                      \
{                                                                       \
  friend T operator OP( T lhs, const T& rhs ) { return lhs OP##= rhs; } \
};

#endif // defined(BOOST_HAS_NRVO) || defined(BOOST_FORCE_SYMMETRIC_OPERATORS)

BOOST_BINARY_OPERATOR_COMMUTATIVE( multipliable, * )
BOOST_BINARY_OPERATOR_COMMUTATIVE( addable, + )
BOOST_BINARY_OPERATOR_NON_COMMUTATIVE( subtractable, - )
BOOST_BINARY_OPERATOR_NON_COMMUTATIVE( dividable, / )
BOOST_BINARY_OPERATOR_NON_COMMUTATIVE( modable, % )
BOOST_BINARY_OPERATOR_COMMUTATIVE( xorable, ^ )
BOOST_BINARY_OPERATOR_COMMUTATIVE( andable, & )
BOOST_BINARY_OPERATOR_COMMUTATIVE( orable, | )

#undef BOOST_BINARY_OPERATOR_COMMUTATIVE
#undef BOOST_BINARY_OPERATOR_NON_COMMUTATIVE
#undef BOOST_OPERATOR2_LEFT

//  incrementable and decrementable contributed by Jeremy Siek

template <class T, class B = ::boost::detail::empty_base<T> >
struct incrementable : B
{
  friend T operator++(T& x, int)
  {
    incrementable_type nrv(x);
    ++x;
    return nrv;
  }
private: // The use of this typedef works around a Borland bug
  typedef T incrementable_type;
};

template <class T, class B = ::boost::detail::empty_base<T> >
struct decrementable : B
{
  friend T operator--(T& x, int)
  {
    decrementable_type nrv(x);
    --x;
    return nrv;
  }
private: // The use of this typedef works around a Borland bug
  typedef T decrementable_type;
};

//  Iterator operator classes (contributed by Jeremy Siek) ------------------//

template <class T, class P, class B = ::boost::detail::empty_base<T> >
struct dereferenceable : B
{
  P operator->() const
  { 
    return &*static_cast<const T&>(*this); 
  }
};

template <class T, class I, class R, class B = ::boost::detail::empty_base<T> >
struct indexable : B
{
  R operator[](I n) const
  {
    return *(static_cast<const T&>(*this) + n);
  }
};

//  More operator classes (contributed by Daryle Walker) --------------------//
//  (NRVO-friendly implementation contributed by Daniel Frey) ---------------//

#if defined(BOOST_HAS_NRVO) || defined(BOOST_FORCE_SYMMETRIC_OPERATORS)

#define BOOST_BINARY_OPERATOR( NAME, OP )                                     \
template <class T, class U, class B = ::boost::detail::empty_base<T> >        \
struct NAME##2 : B                                                            \
{                                                                             \
  friend T operator OP( const T& lhs, const U& rhs )                          \
    { T nrv( lhs ); nrv OP##= rhs; return nrv; }                              \
};                                                                            \
                                                                              \
template <class T, class B = ::boost::detail::empty_base<T> >                 \
struct NAME##1 : B                                                            \
{                                                                             \
  friend T operator OP( const T& lhs, const T& rhs )                          \
    { T nrv( lhs ); nrv OP##= rhs; return nrv; }                              \
};

#else // defined(BOOST_HAS_NRVO) || defined(BOOST_FORCE_SYMMETRIC_OPERATORS)

#define BOOST_BINARY_OPERATOR( NAME, OP )                                     \
template <class T, class U, class B = ::boost::detail::empty_base<T> >        \
struct NAME##2 : B                                                            \
{                                                                             \
  friend T operator OP( T lhs, const U& rhs ) { return lhs OP##= rhs; }       \
};                                                                            \
                                                                              \
template <class T, class B = ::boost::detail::empty_base<T> >                 \
struct NAME##1 : B                                                            \
{                                                                             \
  friend T operator OP( T lhs, const T& rhs ) { return lhs OP##= rhs; }       \
};

#endif // defined(BOOST_HAS_NRVO) || defined(BOOST_FORCE_SYMMETRIC_OPERATORS)

BOOST_BINARY_OPERATOR( left_shiftable, << )
BOOST_BINARY_OPERATOR( right_shiftable, >> )

#undef BOOST_BINARY_OPERATOR

template <class T, class U, class B = ::boost::detail::empty_base<T> >
struct equivalent2 : B
{
  friend bool operator==(const T& x, const U& y)
  {
    return !static_cast<bool>(x < y) && !static_cast<bool>(x > y);
  }
};

template <class T, class B = ::boost::detail::empty_base<T> >
struct equivalent1 : B
{
  friend bool operator==(const T&x, const T&y)
  {
    return !static_cast<bool>(x < y) && !static_cast<bool>(y < x);
  }
};

template <class T, class U, class B = ::boost::detail::empty_base<T> >
struct partially_ordered2 : B
{
  friend bool operator<=(const T& x, const U& y)
    { return static_cast<bool>(x < y) || static_cast<bool>(x == y); }
  friend bool operator>=(const T& x, const U& y)
    { return static_cast<bool>(x > y) || static_cast<bool>(x == y); }
  friend bool operator>(const U& x, const T& y)
    { return y < x; }
  friend bool operator<(const U& x, const T& y)
    { return y > x; }
  friend bool operator<=(const U& x, const T& y)
    { return static_cast<bool>(y > x) || static_cast<bool>(y == x); }
  friend bool operator>=(const U& x, const T& y)
    { return static_cast<bool>(y < x) || static_cast<bool>(y == x); }
};

template <class T, class B = ::boost::detail::empty_base<T> >
struct partially_ordered1 : B
{
  friend bool operator>(const T& x, const T& y)
    { return y < x; }
  friend bool operator<=(const T& x, const T& y)
    { return static_cast<bool>(x < y) || static_cast<bool>(x == y); }
  friend bool operator>=(const T& x, const T& y)
    { return static_cast<bool>(y < x) || static_cast<bool>(x == y); }
};

//  Combined operator classes (contributed by Daryle Walker) ----------------//

template <class T, class U, class B = ::boost::detail::empty_base<T> >
struct totally_ordered2
    : less_than_comparable2<T, U
    , equality_comparable2<T, U, B
      > > {};

template <class T, class B = ::boost::detail::empty_base<T> >
struct totally_ordered1
    : less_than_comparable1<T
    , equality_comparable1<T, B
      > > {};

template <class T, class U, class B = ::boost::detail::empty_base<T> >
struct additive2
    : addable2<T, U
    , subtractable2<T, U, B
      > > {};

template <class T, class B = ::boost::detail::empty_base<T> >
struct additive1
    : addable1<T
    , subtractable1<T, B
      > > {};

template <class T, class U, class B = ::boost::detail::empty_base<T> >
struct multiplicative2
    : multipliable2<T, U
    , dividable2<T, U, B
      > > {};

template <class T, class B = ::boost::detail::empty_base<T> >
struct multiplicative1
    : multipliable1<T
    , dividable1<T, B
      > > {};

template <class T, class U, class B = ::boost::detail::empty_base<T> >
struct integer_multiplicative2
    : multiplicative2<T, U
    , modable2<T, U, B
      > > {};

template <class T, class B = ::boost::detail::empty_base<T> >
struct integer_multiplicative1
    : multiplicative1<T
    , modable1<T, B
      > > {};

template <class T, class U, class B = ::boost::detail::empty_base<T> >
struct arithmetic2
    : additive2<T, U
    , multiplicative2<T, U, B
      > > {};

template <class T, class B = ::boost::detail::empty_base<T> >
struct arithmetic1
    : additive1<T
    , multiplicative1<T, B
      > > {};

template <class T, class U, class B = ::boost::detail::empty_base<T> >
struct integer_arithmetic2
    : additive2<T, U
    , integer_multiplicative2<T, U, B
      > > {};

template <class T, class B = ::boost::detail::empty_base<T> >
struct integer_arithmetic1
    : additive1<T
    , integer_multiplicative1<T, B
      > > {};

template <class T, class U, class B = ::boost::detail::empty_base<T> >
struct bitwise2
    : xorable2<T, U
    , andable2<T, U
    , orable2<T, U, B
      > > > {};

template <class T, class B = ::boost::detail::empty_base<T> >
struct bitwise1
    : xorable1<T
    , andable1<T
    , orable1<T, B
      > > > {};

template <class T, class B = ::boost::detail::empty_base<T> >
struct unit_steppable
    : incrementable<T
    , decrementable<T, B
      > > {};

template <class T, class U, class B = ::boost::detail::empty_base<T> >
struct shiftable2
    : left_shiftable2<T, U
    , right_shiftable2<T, U, B
      > > {};

template <class T, class B = ::boost::detail::empty_base<T> >
struct shiftable1
    : left_shiftable1<T
    , right_shiftable1<T, B
      > > {};

template <class T, class U, class B = ::boost::detail::empty_base<T> >
struct ring_operators2
    : additive2<T, U
    , subtractable2_left<T, U
    , multipliable2<T, U, B
      > > > {};

template <class T, class B = ::boost::detail::empty_base<T> >
struct ring_operators1
    : additive1<T
    , multipliable1<T, B
      > > {};

template <class T, class U, class B = ::boost::detail::empty_base<T> >
struct ordered_ring_operators2
    : ring_operators2<T, U
    , totally_ordered2<T, U, B
      > > {};

template <class T, class B = ::boost::detail::empty_base<T> >
struct ordered_ring_operators1
    : ring_operators1<T
    , totally_ordered1<T, B
      > > {};

template <class T, class U, class B = ::boost::detail::empty_base<T> >
struct field_operators2
    : ring_operators2<T, U
    , dividable2<T, U
    , dividable2_left<T, U, B
      > > > {};

template <class T, class B = ::boost::detail::empty_base<T> >
struct field_operators1
    : ring_operators1<T
    , dividable1<T, B
      > > {};

template <class T, class U, class B = ::boost::detail::empty_base<T> >
struct ordered_field_operators2
    : field_operators2<T, U
    , totally_ordered2<T, U, B
      > > {};

template <class T, class B = ::boost::detail::empty_base<T> >
struct ordered_field_operators1
    : field_operators1<T
    , totally_ordered1<T, B
      > > {};

template <class T, class U, class B = ::boost::detail::empty_base<T> >
struct euclidian_ring_operators2
    : ring_operators2<T, U
    , dividable2<T, U
    , dividable2_left<T, U
    , modable2<T, U
    , modable2_left<T, U, B
      > > > > > {};

template <class T, class B = ::boost::detail::empty_base<T> >
struct euclidian_ring_operators1
    : ring_operators1<T
    , dividable1<T
    , modable1<T, B
      > > > {};

template <class T, class U, class B = ::boost::detail::empty_base<T> >
struct ordered_euclidian_ring_operators2
    : totally_ordered2<T, U
    , euclidian_ring_operators2<T, U, B
      > > {};

template <class T, class B = ::boost::detail::empty_base<T> >
struct ordered_euclidian_ring_operators1
    : totally_ordered1<T
    , euclidian_ring_operators1<T, B
      > > {};

template <class T, class U, class B = ::boost::detail::empty_base<T> >
struct euclidean_ring_operators2
    : ring_operators2<T, U
    , dividable2<T, U
    , dividable2_left<T, U
    , modable2<T, U
    , modable2_left<T, U, B
      > > > > > {};

template <class T, class B = ::boost::detail::empty_base<T> >
struct euclidean_ring_operators1
    : ring_operators1<T
    , dividable1<T
    , modable1<T, B
      > > > {};

template <class T, class U, class B = ::boost::detail::empty_base<T> >
struct ordered_euclidean_ring_operators2
    : totally_ordered2<T, U
    , euclidean_ring_operators2<T, U, B
      > > {};

template <class T, class B = ::boost::detail::empty_base<T> >
struct ordered_euclidean_ring_operators1
    : totally_ordered1<T
    , euclidean_ring_operators1<T, B
      > > {};

template <class T, class P, class B = ::boost::detail::empty_base<T> >
struct input_iteratable
    : equality_comparable1<T
    , incrementable<T
    , dereferenceable<T, P, B
      > > > {};

template <class T, class B = ::boost::detail::empty_base<T> >
struct output_iteratable
    : incrementable<T, B
      > {};

template <class T, class P, class B = ::boost::detail::empty_base<T> >
struct forward_iteratable
    : input_iteratable<T, P, B
      > {};

template <class T, class P, class B = ::boost::detail::empty_base<T> >
struct bidirectional_iteratable
    : forward_iteratable<T, P
    , decrementable<T, B
      > > {};

//  To avoid repeated derivation from equality_comparable,
//  which is an indirect base class of bidirectional_iterable,
//  random_access_iteratable must not be derived from totally_ordered1
//  but from less_than_comparable1 only. (Helmut Zeisel, 02-Dec-2001)
template <class T, class P, class D, class R, class B = ::boost::detail::empty_base<T> >
struct random_access_iteratable
    : bidirectional_iteratable<T, P
    , less_than_comparable1<T
    , additive2<T, D
    , indexable<T, D, R, B
      > > > > {};

#ifndef BOOST_NO_OPERATORS_IN_NAMESPACE
} // namespace boost
#endif // BOOST_NO_OPERATORS_IN_NAMESPACE


// BOOST_IMPORT_TEMPLATE1 .. BOOST_IMPORT_TEMPLATE4 -
//
// When BOOST_NO_OPERATORS_IN_NAMESPACE is defined we need a way to import an
// operator template into the boost namespace. BOOST_IMPORT_TEMPLATE1 is used
// for one-argument forms of operator templates; BOOST_IMPORT_TEMPLATE2 for
// two-argument forms. Note that these macros expect to be invoked from within
// boost.

#ifndef BOOST_NO_OPERATORS_IN_NAMESPACE

  // The template is already in boost so we have nothing to do.
# define BOOST_IMPORT_TEMPLATE4(template_name)
# define BOOST_IMPORT_TEMPLATE3(template_name)
# define BOOST_IMPORT_TEMPLATE2(template_name)
# define BOOST_IMPORT_TEMPLATE1(template_name)

#else // BOOST_NO_OPERATORS_IN_NAMESPACE

#  ifndef BOOST_NO_USING_TEMPLATE

     // Bring the names in with a using-declaration
     // to avoid stressing the compiler.
#    define BOOST_IMPORT_TEMPLATE4(template_name) using ::template_name;
#    define BOOST_IMPORT_TEMPLATE3(template_name) using ::template_name;
#    define BOOST_IMPORT_TEMPLATE2(template_name) using ::template_name;
#    define BOOST_IMPORT_TEMPLATE1(template_name) using ::template_name;

#  else

     // Otherwise, because a Borland C++ 5.5 bug prevents a using declaration
     // from working, we are forced to use inheritance for that compiler.
#    define BOOST_IMPORT_TEMPLATE4(template_name)                                             \
     template <class T, class U, class V, class W, class B = ::boost::detail::empty_base<T> > \
     struct template_name : ::template_name<T, U, V, W, B> {};

#    define BOOST_IMPORT_TEMPLATE3(template_name)                                    \
     template <class T, class U, class V, class B = ::boost::detail::empty_base<T> > \
     struct template_name : ::template_name<T, U, V, B> {};

#    define BOOST_IMPORT_TEMPLATE2(template_name)                           \
     template <class T, class U, class B = ::boost::detail::empty_base<T> > \
     struct template_name : ::template_name<T, U, B> {};

#    define BOOST_IMPORT_TEMPLATE1(template_name)                  \
     template <class T, class B = ::boost::detail::empty_base<T> > \
     struct template_name : ::template_name<T, B> {};

#  endif // BOOST_NO_USING_TEMPLATE

#endif // BOOST_NO_OPERATORS_IN_NAMESPACE

//
// Here's where we put it all together, defining the xxxx forms of the templates
// in namespace boost. We also define specializations of is_chained_base<> for
// the xxxx, xxxx1, and xxxx2 templates, importing them into boost:: as
// necessary.
//

// is_chained_base<> - a traits class used to distinguish whether an operator
// template argument is being used for base class chaining, or is specifying a
// 2nd argument type.

namespace boost {
// A type parameter is used instead of a plain bool because Borland's compiler
// didn't cope well with the more obvious non-type template parameter.
namespace detail {
  struct true_t {};
  struct false_t {};
} // namespace detail

// Unspecialized version assumes that most types are not being used for base
// class chaining. We specialize for the operator templates defined in this
// library.
template<class T> struct is_chained_base {
  typedef ::boost::detail::false_t value;
};

} // namespace boost

// Import a 4-type-argument operator template into boost (if necessary) and
// provide a specialization of 'is_chained_base<>' for it.
# define BOOST_OPERATOR_TEMPLATE4(template_name4)                     \
  BOOST_IMPORT_TEMPLATE4(template_name4)                              \
  template<class T, class U, class V, class W, class B>               \
  struct is_chained_base< ::boost::template_name4<T, U, V, W, B> > {  \
    typedef ::boost::detail::true_t value;                            \
  };

// Import a 3-type-argument operator template into boost (if necessary) and
// provide a specialization of 'is_chained_base<>' for it.
# define BOOST_OPERATOR_TEMPLATE3(template_name3)                     \
  BOOST_IMPORT_TEMPLATE3(template_name3)                              \
  template<class T, class U, class V, class B>                        \
  struct is_chained_base< ::boost::template_name3<T, U, V, B> > {     \
    typedef ::boost::detail::true_t value;                            \
  };

// Import a 2-type-argument operator template into boost (if necessary) and
// provide a specialization of 'is_chained_base<>' for it.
# define BOOST_OPERATOR_TEMPLATE2(template_name2)                  \
  BOOST_IMPORT_TEMPLATE2(template_name2)                           \
  template<class T, class U, class B>                              \
  struct is_chained_base< ::boost::template_name2<T, U, B> > {     \
    typedef ::boost::detail::true_t value;                         \
  };

// Import a 1-type-argument operator template into boost (if necessary) and
// provide a specialization of 'is_chained_base<>' for it.
# define BOOST_OPERATOR_TEMPLATE1(template_name1)                  \
  BOOST_IMPORT_TEMPLATE1(template_name1)                           \
  template<class T, class B>                                       \
  struct is_chained_base< ::boost::template_name1<T, B> > {        \
    typedef ::boost::detail::true_t value;                         \
  };

// BOOST_OPERATOR_TEMPLATE(template_name) defines template_name<> such that it
// can be used for specifying both 1-argument and 2-argument forms. Requires the
// existence of two previously defined class templates named '<template_name>1'
// and '<template_name>2' which must implement the corresponding 1- and 2-
// argument forms.
//
// The template type parameter O == is_chained_base<U>::value is used to
// distinguish whether the 2nd argument to <template_name> is being used for
// base class chaining from another boost operator template or is describing a
// 2nd operand type. O == true_t only when U is actually an another operator
// template from the library. Partial specialization is used to select an
// implementation in terms of either '<template_name>1' or '<template_name>2'.
//

# define BOOST_OPERATOR_TEMPLATE(template_name)                    \
template <class T                                                  \
         ,class U = T                                              \
         ,class B = ::boost::detail::empty_base<T>                 \
         ,class O = typename is_chained_base<U>::value             \
         >                                                         \
struct template_name : template_name##2<T, U, B> {};               \
                                                                   \
template<class T, class U, class B>                                \
struct template_name<T, U, B, ::boost::detail::true_t>             \
  : template_name##1<T, U> {};                                     \
                                                                   \
template <class T, class B>                                        \
struct template_name<T, T, B, ::boost::detail::false_t>            \
  : template_name##1<T, B> {};                                     \
                                                                   \
template<class T, class U, class B, class O>                       \
struct is_chained_base< ::boost::template_name<T, U, B, O> > {     \
  typedef ::boost::detail::true_t value;                           \
};                                                                 \
                                                                   \
BOOST_OPERATOR_TEMPLATE2(template_name##2)                         \
BOOST_OPERATOR_TEMPLATE1(template_name##1)



namespace boost {
    
BOOST_OPERATOR_TEMPLATE(less_than_comparable)
BOOST_OPERATOR_TEMPLATE(equality_comparable)
BOOST_OPERATOR_TEMPLATE(multipliable)
BOOST_OPERATOR_TEMPLATE(addable)
BOOST_OPERATOR_TEMPLATE(subtractable)
BOOST_OPERATOR_TEMPLATE2(subtractable2_left)
BOOST_OPERATOR_TEMPLATE(dividable)
BOOST_OPERATOR_TEMPLATE2(dividable2_left)
BOOST_OPERATOR_TEMPLATE(modable)
BOOST_OPERATOR_TEMPLATE2(modable2_left)
BOOST_OPERATOR_TEMPLATE(xorable)
BOOST_OPERATOR_TEMPLATE(andable)
BOOST_OPERATOR_TEMPLATE(orable)

BOOST_OPERATOR_TEMPLATE1(incrementable)
BOOST_OPERATOR_TEMPLATE1(decrementable)

BOOST_OPERATOR_TEMPLATE2(dereferenceable)
BOOST_OPERATOR_TEMPLATE3(indexable)

BOOST_OPERATOR_TEMPLATE(left_shiftable)
BOOST_OPERATOR_TEMPLATE(right_shiftable)
BOOST_OPERATOR_TEMPLATE(equivalent)
BOOST_OPERATOR_TEMPLATE(partially_ordered)

BOOST_OPERATOR_TEMPLATE(totally_ordered)
BOOST_OPERATOR_TEMPLATE(additive)
BOOST_OPERATOR_TEMPLATE(multiplicative)
BOOST_OPERATOR_TEMPLATE(integer_multiplicative)
BOOST_OPERATOR_TEMPLATE(arithmetic)
BOOST_OPERATOR_TEMPLATE(integer_arithmetic)
BOOST_OPERATOR_TEMPLATE(bitwise)
BOOST_OPERATOR_TEMPLATE1(unit_steppable)
BOOST_OPERATOR_TEMPLATE(shiftable)
BOOST_OPERATOR_TEMPLATE(ring_operators)
BOOST_OPERATOR_TEMPLATE(ordered_ring_operators)
BOOST_OPERATOR_TEMPLATE(field_operators)
BOOST_OPERATOR_TEMPLATE(ordered_field_operators)
BOOST_OPERATOR_TEMPLATE(euclidian_ring_operators)
BOOST_OPERATOR_TEMPLATE(ordered_euclidian_ring_operators)
BOOST_OPERATOR_TEMPLATE(euclidean_ring_operators)
BOOST_OPERATOR_TEMPLATE(ordered_euclidean_ring_operators)
BOOST_OPERATOR_TEMPLATE2(input_iteratable)
BOOST_OPERATOR_TEMPLATE1(output_iteratable)
BOOST_OPERATOR_TEMPLATE2(forward_iteratable)
BOOST_OPERATOR_TEMPLATE2(bidirectional_iteratable)
BOOST_OPERATOR_TEMPLATE4(random_access_iteratable)

#undef BOOST_OPERATOR_TEMPLATE
#undef BOOST_OPERATOR_TEMPLATE4
#undef BOOST_OPERATOR_TEMPLATE3
#undef BOOST_OPERATOR_TEMPLATE2
#undef BOOST_OPERATOR_TEMPLATE1
#undef BOOST_IMPORT_TEMPLATE1
#undef BOOST_IMPORT_TEMPLATE2
#undef BOOST_IMPORT_TEMPLATE3
#undef BOOST_IMPORT_TEMPLATE4

// The following 'operators' classes can only be used portably if the derived class
// declares ALL of the required member operators.
template <class T, class U>
struct operators2
    : totally_ordered2<T,U
    , integer_arithmetic2<T,U
    , bitwise2<T,U
      > > > {};

template <class T, class U = T>
struct operators : operators2<T, U> {};

template <class T> struct operators<T, T>
    : totally_ordered<T
    , integer_arithmetic<T
    , bitwise<T
    , unit_steppable<T
      > > > > {};

//  Iterator helper classes (contributed by Jeremy Siek) -------------------//
//  (Input and output iterator helpers contributed by Daryle Walker) -------//
//  (Changed to use combined operator classes by Daryle Walker) ------------//
template <class T,
          class V,
          class D = std::ptrdiff_t,
          class P = V const *,
          class R = V const &>
struct input_iterator_helper
  : input_iteratable<T, P
  , std::iterator<std::input_iterator_tag, V, D, P, R
    > > {};

template<class T>
struct output_iterator_helper
  : output_iteratable<T
  , std::iterator<std::output_iterator_tag, void, void, void, void
  > >
{
  T& operator*()  { return static_cast<T&>(*this); }
  T& operator++() { return static_cast<T&>(*this); }
};

template <class T,
          class V,
          class D = std::ptrdiff_t,
          class P = V*,
          class R = V&>
struct forward_iterator_helper
  : forward_iteratable<T, P
  , std::iterator<std::forward_iterator_tag, V, D, P, R
    > > {};

template <class T,
          class V,
          class D = std::ptrdiff_t,
          class P = V*,
          class R = V&>
struct bidirectional_iterator_helper
  : bidirectional_iteratable<T, P
  , std::iterator<std::bidirectional_iterator_tag, V, D, P, R
    > > {};

template <class T,
          class V, 
          class D = std::ptrdiff_t,
          class P = V*,
          class R = V&>
struct random_access_iterator_helper
  : random_access_iteratable<T, P, D, R
  , std::iterator<std::random_access_iterator_tag, V, D, P, R
    > >
{
  friend D requires_difference_operator(const T& x, const T& y) {
    return x - y;
  }
}; // random_access_iterator_helper

} // namespace boost

#if defined(__sgi) && !defined(__GNUC__)
#pragma reset woff 1234
#endif

#endif // BOOST_OPERATORS_V1_HPP

/* operators_v1.hpp
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
*/