//  Boost operators.hpp header file  ----------------------------------------//

//  (C) Copyright David Abrahams, Jeremy Siek, Daryle Walker 1999-2001.
//  (C) Copyright Daniel Frey 2002-2017.
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/utility/operators.htm for documentation.

//  Revision History
//  23 Nov 17 Protect dereferenceable<> from overloaded operator&.
//  15 Oct 17 Adapted to C++17, replace std::iterator<> with manual
//            implementation.
//  22 Feb 16 Added ADL protection, preserve old work-arounds in
//            operators_v1.hpp and clean up this file. (Daniel Frey)
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
// 'is_chained_base<>' (see 'operators_detail' namespace below), which is used
// to determine whether its template parameter is a library's operator template
// or not. You have to specialize 'is_chained_base<>' for each new
// operator template you add to the library.
//
// However, most of the non-trivial implementation details are hidden behind
// several local macros defined below, and as soon as you understand them,
// you understand the whole library implementation.

#ifndef BOOST_OPERATORS_HPP
#define BOOST_OPERATORS_HPP

// If old work-arounds are needed, refer to the preserved version without
// ADL protection.
#if defined(BOOST_NO_OPERATORS_IN_NAMESPACE) || defined(BOOST_USE_OPERATORS_V1)
#include "operators_v1.hpp"
#else

#include <cstddef>
#include <iterator>

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/core/addressof.hpp>

#if defined(__sgi) && !defined(__GNUC__)
#   pragma set woff 1234
#endif

#if BOOST_WORKAROUND(BOOST_MSVC, < 1600)
#   pragma warning( disable : 4284 ) // complaint about return type of
#endif                               // operator-> not begin a UDT

// In this section we supply the xxxx1 and xxxx2 forms of the operator
// templates, which are explicitly targeted at the 1-type-argument and
// 2-type-argument operator forms, respectively.

namespace boost
{
namespace operators_impl
{
namespace operators_detail
{

template <typename T> class empty_base {};

} // namespace operators_detail

//  Basic operator classes (contributed by Dave Abrahams) ------------------//

//  Note that friend functions defined in a class are implicitly inline.
//  See the C++ std, 11.4 [class.friend] paragraph 5

template <class T, class U, class B = operators_detail::empty_base<T> >
struct less_than_comparable2 : B
{
     friend bool operator<=(const T& x, const U& y) { return !static_cast<bool>(x > y); }
     friend bool operator>=(const T& x, const U& y) { return !static_cast<bool>(x < y); }
     friend bool operator>(const U& x, const T& y)  { return y < x; }
     friend bool operator<(const U& x, const T& y)  { return y > x; }
     friend bool operator<=(const U& x, const T& y) { return !static_cast<bool>(y < x); }
     friend bool operator>=(const U& x, const T& y) { return !static_cast<bool>(y > x); }
};

template <class T, class B = operators_detail::empty_base<T> >
struct less_than_comparable1 : B
{
     friend bool operator>(const T& x, const T& y)  { return y < x; }
     friend bool operator<=(const T& x, const T& y) { return !static_cast<bool>(y < x); }
     friend bool operator>=(const T& x, const T& y) { return !static_cast<bool>(x < y); }
};

template <class T, class U, class B = operators_detail::empty_base<T> >
struct equality_comparable2 : B
{
     friend bool operator==(const U& y, const T& x) { return x == y; }
     friend bool operator!=(const U& y, const T& x) { return !static_cast<bool>(x == y); }
     friend bool operator!=(const T& y, const U& x) { return !static_cast<bool>(y == x); }
};

template <class T, class B = operators_detail::empty_base<T> >
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

#define BOOST_BINARY_OPERATOR_COMMUTATIVE( NAME, OP )                   \
template <class T, class U, class B = operators_detail::empty_base<T> > \
struct NAME##2 : B                                                      \
{                                                                       \
  friend T operator OP( const T& lhs, const U& rhs )                    \
    { T nrv( lhs ); nrv OP##= rhs; return nrv; }                        \
  friend T operator OP( const U& lhs, const T& rhs )                    \
    { T nrv( rhs ); nrv OP##= lhs; return nrv; }                        \
};                                                                      \
                                                                        \
template <class T, class B = operators_detail::empty_base<T> >          \
struct NAME##1 : B                                                      \
{                                                                       \
  friend T operator OP( const T& lhs, const T& rhs )                    \
    { T nrv( lhs ); nrv OP##= rhs; return nrv; }                        \
};

#define BOOST_BINARY_OPERATOR_NON_COMMUTATIVE( NAME, OP )               \
template <class T, class U, class B = operators_detail::empty_base<T> > \
struct NAME##2 : B                                                      \
{                                                                       \
  friend T operator OP( const T& lhs, const U& rhs )                    \
    { T nrv( lhs ); nrv OP##= rhs; return nrv; }                        \
};                                                                      \
                                                                        \
template <class T, class U, class B = operators_detail::empty_base<T> > \
struct BOOST_OPERATOR2_LEFT(NAME) : B                                   \
{                                                                       \
  friend T operator OP( const U& lhs, const T& rhs )                    \
    { T nrv( lhs ); nrv OP##= rhs; return nrv; }                        \
};                                                                      \
                                                                        \
template <class T, class B = operators_detail::empty_base<T> >          \
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
template <class T, class U, class B = operators_detail::empty_base<T> > \
struct NAME##2 : B                                                      \
{                                                                       \
  friend T operator OP( T lhs, const U& rhs ) { return lhs OP##= rhs; } \
  friend T operator OP( const U& lhs, T rhs ) { return rhs OP##= lhs; } \
};                                                                      \
                                                                        \
template <class T, class B = operators_detail::empty_base<T> >          \
struct NAME##1 : B                                                      \
{                                                                       \
  friend T operator OP( T lhs, const T& rhs ) { return lhs OP##= rhs; } \
};

#define BOOST_BINARY_OPERATOR_NON_COMMUTATIVE( NAME, OP )               \
template <class T, class U, class B = operators_detail::empty_base<T> > \
struct NAME##2 : B                                                      \
{                                                                       \
  friend T operator OP( T lhs, const U& rhs ) { return lhs OP##= rhs; } \
};                                                                      \
                                                                        \
template <class T, class U, class B = operators_detail::empty_base<T> > \
struct BOOST_OPERATOR2_LEFT(NAME) : B                                   \
{                                                                       \
  friend T operator OP( const U& lhs, const T& rhs )                    \
    { return T( lhs ) OP##= rhs; }                                      \
};                                                                      \
                                                                        \
template <class T, class B = operators_detail::empty_base<T> >          \
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

template <class T, class B = operators_detail::empty_base<T> >
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

template <class T, class B = operators_detail::empty_base<T> >
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

template <class T, class P, class B = operators_detail::empty_base<T> >
struct dereferenceable : B
{
  P operator->() const
  {
    return ::boost::addressof(*static_cast<const T&>(*this));
  }
};

template <class T, class I, class R, class B = operators_detail::empty_base<T> >
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

#define BOOST_BINARY_OPERATOR( NAME, OP )                               \
template <class T, class U, class B = operators_detail::empty_base<T> > \
struct NAME##2 : B                                                      \
{                                                                       \
  friend T operator OP( const T& lhs, const U& rhs )                    \
    { T nrv( lhs ); nrv OP##= rhs; return nrv; }                        \
};                                                                      \
                                                                        \
template <class T, class B = operators_detail::empty_base<T> >          \
struct NAME##1 : B                                                      \
{                                                                       \
  friend T operator OP( const T& lhs, const T& rhs )                    \
    { T nrv( lhs ); nrv OP##= rhs; return nrv; }                        \
};

#else // defined(BOOST_HAS_NRVO) || defined(BOOST_FORCE_SYMMETRIC_OPERATORS)

#define BOOST_BINARY_OPERATOR( NAME, OP )                               \
template <class T, class U, class B = operators_detail::empty_base<T> > \
struct NAME##2 : B                                                      \
{                                                                       \
  friend T operator OP( T lhs, const U& rhs ) { return lhs OP##= rhs; } \
};                                                                      \
                                                                        \
template <class T, class B = operators_detail::empty_base<T> >          \
struct NAME##1 : B                                                      \
{                                                                       \
  friend T operator OP( T lhs, const T& rhs ) { return lhs OP##= rhs; } \
};

#endif // defined(BOOST_HAS_NRVO) || defined(BOOST_FORCE_SYMMETRIC_OPERATORS)

BOOST_BINARY_OPERATOR( left_shiftable, << )
BOOST_BINARY_OPERATOR( right_shiftable, >> )

#undef BOOST_BINARY_OPERATOR

template <class T, class U, class B = operators_detail::empty_base<T> >
struct equivalent2 : B
{
  friend bool operator==(const T& x, const U& y)
  {
    return !static_cast<bool>(x < y) && !static_cast<bool>(x > y);
  }
};

template <class T, class B = operators_detail::empty_base<T> >
struct equivalent1 : B
{
  friend bool operator==(const T&x, const T&y)
  {
    return !static_cast<bool>(x < y) && !static_cast<bool>(y < x);
  }
};

template <class T, class U, class B = operators_detail::empty_base<T> >
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

template <class T, class B = operators_detail::empty_base<T> >
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

template <class T, class U, class B = operators_detail::empty_base<T> >
struct totally_ordered2
    : less_than_comparable2<T, U
    , equality_comparable2<T, U, B
      > > {};

template <class T, class B = operators_detail::empty_base<T> >
struct totally_ordered1
    : less_than_comparable1<T
    , equality_comparable1<T, B
      > > {};

template <class T, class U, class B = operators_detail::empty_base<T> >
struct additive2
    : addable2<T, U
    , subtractable2<T, U, B
      > > {};

template <class T, class B = operators_detail::empty_base<T> >
struct additive1
    : addable1<T
    , subtractable1<T, B
      > > {};

template <class T, class U, class B = operators_detail::empty_base<T> >
struct multiplicative2
    : multipliable2<T, U
    , dividable2<T, U, B
      > > {};

template <class T, class B = operators_detail::empty_base<T> >
struct multiplicative1
    : multipliable1<T
    , dividable1<T, B
      > > {};

template <class T, class U, class B = operators_detail::empty_base<T> >
struct integer_multiplicative2
    : multiplicative2<T, U
    , modable2<T, U, B
      > > {};

template <class T, class B = operators_detail::empty_base<T> >
struct integer_multiplicative1
    : multiplicative1<T
    , modable1<T, B
      > > {};

template <class T, class U, class B = operators_detail::empty_base<T> >
struct arithmetic2
    : additive2<T, U
    , multiplicative2<T, U, B
      > > {};

template <class T, class B = operators_detail::empty_base<T> >
struct arithmetic1
    : additive1<T
    , multiplicative1<T, B
      > > {};

template <class T, class U, class B = operators_detail::empty_base<T> >
struct integer_arithmetic2
    : additive2<T, U
    , integer_multiplicative2<T, U, B
      > > {};

template <class T, class B = operators_detail::empty_base<T> >
struct integer_arithmetic1
    : additive1<T
    , integer_multiplicative1<T, B
      > > {};

template <class T, class U, class B = operators_detail::empty_base<T> >
struct bitwise2
    : xorable2<T, U
    , andable2<T, U
    , orable2<T, U, B
      > > > {};

template <class T, class B = operators_detail::empty_base<T> >
struct bitwise1
    : xorable1<T
    , andable1<T
    , orable1<T, B
      > > > {};

template <class T, class B = operators_detail::empty_base<T> >
struct unit_steppable
    : incrementable<T
    , decrementable<T, B
      > > {};

template <class T, class U, class B = operators_detail::empty_base<T> >
struct shiftable2
    : left_shiftable2<T, U
    , right_shiftable2<T, U, B
      > > {};

template <class T, class B = operators_detail::empty_base<T> >
struct shiftable1
    : left_shiftable1<T
    , right_shiftable1<T, B
      > > {};

template <class T, class U, class B = operators_detail::empty_base<T> >
struct ring_operators2
    : additive2<T, U
    , subtractable2_left<T, U
    , multipliable2<T, U, B
      > > > {};

template <class T, class B = operators_detail::empty_base<T> >
struct ring_operators1
    : additive1<T
    , multipliable1<T, B
      > > {};

template <class T, class U, class B = operators_detail::empty_base<T> >
struct ordered_ring_operators2
    : ring_operators2<T, U
    , totally_ordered2<T, U, B
      > > {};

template <class T, class B = operators_detail::empty_base<T> >
struct ordered_ring_operators1
    : ring_operators1<T
    , totally_ordered1<T, B
      > > {};

template <class T, class U, class B = operators_detail::empty_base<T> >
struct field_operators2
    : ring_operators2<T, U
    , dividable2<T, U
    , dividable2_left<T, U, B
      > > > {};

template <class T, class B = operators_detail::empty_base<T> >
struct field_operators1
    : ring_operators1<T
    , dividable1<T, B
      > > {};

template <class T, class U, class B = operators_detail::empty_base<T> >
struct ordered_field_operators2
    : field_operators2<T, U
    , totally_ordered2<T, U, B
      > > {};

template <class T, class B = operators_detail::empty_base<T> >
struct ordered_field_operators1
    : field_operators1<T
    , totally_ordered1<T, B
      > > {};

template <class T, class U, class B = operators_detail::empty_base<T> >
struct euclidian_ring_operators2
    : ring_operators2<T, U
    , dividable2<T, U
    , dividable2_left<T, U
    , modable2<T, U
    , modable2_left<T, U, B
      > > > > > {};

template <class T, class B = operators_detail::empty_base<T> >
struct euclidian_ring_operators1
    : ring_operators1<T
    , dividable1<T
    , modable1<T, B
      > > > {};

template <class T, class U, class B = operators_detail::empty_base<T> >
struct ordered_euclidian_ring_operators2
    : totally_ordered2<T, U
    , euclidian_ring_operators2<T, U, B
      > > {};

template <class T, class B = operators_detail::empty_base<T> >
struct ordered_euclidian_ring_operators1
    : totally_ordered1<T
    , euclidian_ring_operators1<T, B
      > > {};

template <class T, class U, class B = operators_detail::empty_base<T> >
struct euclidean_ring_operators2
    : ring_operators2<T, U
    , dividable2<T, U
    , dividable2_left<T, U
    , modable2<T, U
    , modable2_left<T, U, B
      > > > > > {};

template <class T, class B = operators_detail::empty_base<T> >
struct euclidean_ring_operators1
    : ring_operators1<T
    , dividable1<T
    , modable1<T, B
      > > > {};

template <class T, class U, class B = operators_detail::empty_base<T> >
struct ordered_euclidean_ring_operators2
    : totally_ordered2<T, U
    , euclidean_ring_operators2<T, U, B
      > > {};

template <class T, class B = operators_detail::empty_base<T> >
struct ordered_euclidean_ring_operators1
    : totally_ordered1<T
    , euclidean_ring_operators1<T, B
      > > {};

template <class T, class P, class B = operators_detail::empty_base<T> >
struct input_iteratable
    : equality_comparable1<T
    , incrementable<T
    , dereferenceable<T, P, B
      > > > {};

template <class T, class B = operators_detail::empty_base<T> >
struct output_iteratable
    : incrementable<T, B
      > {};

template <class T, class P, class B = operators_detail::empty_base<T> >
struct forward_iteratable
    : input_iteratable<T, P, B
      > {};

template <class T, class P, class B = operators_detail::empty_base<T> >
struct bidirectional_iteratable
    : forward_iteratable<T, P
    , decrementable<T, B
      > > {};

//  To avoid repeated derivation from equality_comparable,
//  which is an indirect base class of bidirectional_iterable,
//  random_access_iteratable must not be derived from totally_ordered1
//  but from less_than_comparable1 only. (Helmut Zeisel, 02-Dec-2001)
template <class T, class P, class D, class R, class B = operators_detail::empty_base<T> >
struct random_access_iteratable
    : bidirectional_iteratable<T, P
    , less_than_comparable1<T
    , additive2<T, D
    , indexable<T, D, R, B
      > > > > {};


//
// Here's where we put it all together, defining the xxxx forms of the templates.
// We also define specializations of is_chained_base<> for
// the xxxx, xxxx1, and xxxx2 templates.
//

namespace operators_detail
{

// A type parameter is used instead of a plain bool because Borland's compiler
// didn't cope well with the more obvious non-type template parameter.
struct true_t {};
struct false_t {};

} // namespace operators_detail

// is_chained_base<> - a traits class used to distinguish whether an operator
// template argument is being used for base class chaining, or is specifying a
// 2nd argument type.

// Unspecialized version assumes that most types are not being used for base
// class chaining. We specialize for the operator templates defined in this
// library.
template<class T> struct is_chained_base {
  typedef operators_detail::false_t value;
};

// Provide a specialization of 'is_chained_base<>'
// for a 4-type-argument operator template.
# define BOOST_OPERATOR_TEMPLATE4(template_name4)           \
  template<class T, class U, class V, class W, class B>     \
  struct is_chained_base< template_name4<T, U, V, W, B> > { \
    typedef operators_detail::true_t value;                 \
  };

// Provide a specialization of 'is_chained_base<>'
// for a 3-type-argument operator template.
# define BOOST_OPERATOR_TEMPLATE3(template_name3)        \
  template<class T, class U, class V, class B>           \
  struct is_chained_base< template_name3<T, U, V, B> > { \
    typedef operators_detail::true_t value;              \
  };

// Provide a specialization of 'is_chained_base<>'
// for a 2-type-argument operator template.
# define BOOST_OPERATOR_TEMPLATE2(template_name2)     \
  template<class T, class U, class B>                 \
  struct is_chained_base< template_name2<T, U, B> > { \
    typedef operators_detail::true_t value;           \
  };

// Provide a specialization of 'is_chained_base<>'
// for a 1-type-argument operator template.
# define BOOST_OPERATOR_TEMPLATE1(template_name1)  \
  template<class T, class B>                       \
  struct is_chained_base< template_name1<T, B> > { \
    typedef operators_detail::true_t value;        \
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

# define BOOST_OPERATOR_TEMPLATE(template_name)                                       \
template <class T                                                                     \
         ,class U = T                                                                 \
         ,class B = operators_detail::empty_base<T>                                   \
         ,class O = typename is_chained_base<U>::value                                \
         >                                                                            \
struct template_name;                                                                 \
                                                                                      \
template<class T, class U, class B>                                                   \
struct template_name<T, U, B, operators_detail::false_t>                              \
  : template_name##2<T, U, B> {};                                                     \
                                                                                      \
template<class T, class U>                                                            \
struct template_name<T, U, operators_detail::empty_base<T>, operators_detail::true_t> \
  : template_name##1<T, U> {};                                                        \
                                                                                      \
template <class T, class B>                                                           \
struct template_name<T, T, B, operators_detail::false_t>                              \
  : template_name##1<T, B> {};                                                        \
                                                                                      \
template<class T, class U, class B, class O>                                          \
struct is_chained_base< template_name<T, U, B, O> > {                                 \
  typedef operators_detail::true_t value;                                             \
};                                                                                    \
                                                                                      \
BOOST_OPERATOR_TEMPLATE2(template_name##2)                                            \
BOOST_OPERATOR_TEMPLATE1(template_name##1)

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
//  (Adapted to C++17 by Daniel Frey) --------------------------------------//
template <class Category,
          class T,
          class Distance = std::ptrdiff_t,
          class Pointer = T*,
          class Reference = T&>
struct iterator_helper
{
  typedef Category iterator_category;
  typedef T value_type;
  typedef Distance difference_type;
  typedef Pointer pointer;
  typedef Reference reference;
};

template <class T,
          class V,
          class D = std::ptrdiff_t,
          class P = V const *,
          class R = V const &>
struct input_iterator_helper
  : input_iteratable<T, P
  , iterator_helper<std::input_iterator_tag, V, D, P, R
    > > {};

template<class T>
struct output_iterator_helper
  : output_iteratable<T
  , iterator_helper<std::output_iterator_tag, void, void, void, void
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
  , iterator_helper<std::forward_iterator_tag, V, D, P, R
    > > {};

template <class T,
          class V,
          class D = std::ptrdiff_t,
          class P = V*,
          class R = V&>
struct bidirectional_iterator_helper
  : bidirectional_iteratable<T, P
  , iterator_helper<std::bidirectional_iterator_tag, V, D, P, R
    > > {};

template <class T,
          class V,
          class D = std::ptrdiff_t,
          class P = V*,
          class R = V&>
struct random_access_iterator_helper
  : random_access_iteratable<T, P, D, R
  , iterator_helper<std::random_access_iterator_tag, V, D, P, R
    > >
{
  friend D requires_difference_operator(const T& x, const T& y) {
    return x - y;
  }
}; // random_access_iterator_helper

} // namespace operators_impl
using namespace operators_impl;

} // namespace boost

#if defined(__sgi) && !defined(__GNUC__)
#pragma reset woff 1234
#endif

#endif // BOOST_NO_OPERATORS_IN_NAMESPACE
#endif // BOOST_OPERATORS_HPP

/* operators.hpp
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
*/