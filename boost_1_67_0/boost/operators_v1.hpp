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