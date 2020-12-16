// Boost Lambda Library - operators.hpp --------------------------------------

// Copyright (C) 1999, 2000 Jaakko Jarvi (jaakko.jarvi@cs.utu.fi)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org

// ---------------------------------------------------------------

#ifndef BOOST_LAMBDA_OPERATORS_HPP
#define BOOST_LAMBDA_OPERATORS_HPP

#include "boost/lambda/detail/is_instance_of.hpp"

namespace boost { 
namespace lambda {

#if defined BOOST_LAMBDA_BE1
#error "Multiple defines of BOOST_LAMBDA_BE1"
#endif

  // For all BOOSTA_LAMBDA_BE* macros:

  // CONSTA must be either 'A' or 'const A'
  // CONSTB must be either 'B' or 'const B'

  // It is stupid to have the names A and B as macro arguments, but it avoids
  // the need to pass in emtpy macro arguments, which gives warnings on some
  // compilers

#define BOOST_LAMBDA_BE1(OPER_NAME, ACTION, CONSTA, CONSTB, CONVERSION)      \
template<class Arg, class B>                                                 \
inline const                                                                 \
lambda_functor<                                                              \
  lambda_functor_base<                                                       \
    ACTION,                                                                  \
    tuple<lambda_functor<Arg>, typename const_copy_argument <CONSTB>::type>  \
  >                                                                          \
>                                                                            \
OPER_NAME (const lambda_functor<Arg>& a, CONSTB& b) {                      \
  return                                                                     \
    lambda_functor_base<                                                     \
      ACTION,                                                                \
      tuple<lambda_functor<Arg>, typename const_copy_argument <CONSTB>::type>\
    >                                                                        \
   (tuple<lambda_functor<Arg>, typename const_copy_argument <CONSTB>::type>(a, b)); \
}


#if defined BOOST_LAMBDA_BE2
#error "Multiple defines of BOOST_LAMBDA_BE2"
#endif

#define BOOST_LAMBDA_BE2(OPER_NAME, ACTION, CONSTA, CONSTB, CONVERSION)      \
template<class A, class Arg>                                                 \
inline const                                                                 \
lambda_functor<                                                              \
  lambda_functor_base<                                                       \
    ACTION,                                                                  \
    tuple<typename CONVERSION <CONSTA>::type, lambda_functor<Arg> >        \
  >                                                                          \
>                                                                            \
OPER_NAME (CONSTA& a, const lambda_functor<Arg>& b) {                      \
  return                                                                     \
    lambda_functor_base<                                                     \
      ACTION,                                                                \
      tuple<typename CONVERSION <CONSTA>::type, lambda_functor<Arg> >      \
    >                                                                        \
  (tuple<typename CONVERSION <CONSTA>::type, lambda_functor<Arg> >(a, b)); \
}


#if defined BOOST_LAMBDA_BE3
#error "Multiple defines of BOOST_LAMBDA_BE3"
#endif

#define BOOST_LAMBDA_BE3(OPER_NAME, ACTION, CONSTA, CONSTB, CONVERSION)    \
template<class ArgA, class ArgB>                                           \
inline const                                                               \
lambda_functor<                                                            \
  lambda_functor_base<                                                     \
    ACTION,                                                                \
    tuple<lambda_functor<ArgA>, lambda_functor<ArgB> >                     \
  >                                                                        \
>                                                                          \
OPER_NAME (const lambda_functor<ArgA>& a, const lambda_functor<ArgB>& b) { \
  return                                                                   \
    lambda_functor_base<                                                   \
      ACTION,                                                              \
      tuple<lambda_functor<ArgA>, lambda_functor<ArgB> >                   \
    >                                                                      \
  (tuple<lambda_functor<ArgA>, lambda_functor<ArgB> >(a, b));              \
}

#if defined BOOST_LAMBDA_BE
#error "Multiple defines of BOOST_LAMBDA_BE"
#endif

#define BOOST_LAMBDA_BE(OPER_NAME, ACTION, CONSTA, CONSTB, CONST_CONVERSION) \
BOOST_LAMBDA_BE1(OPER_NAME, ACTION, CONSTA, CONSTB, CONST_CONVERSION)        \
BOOST_LAMBDA_BE2(OPER_NAME, ACTION, CONSTA, CONSTB, CONST_CONVERSION)        \
BOOST_LAMBDA_BE3(OPER_NAME, ACTION, CONSTA, CONSTB, CONST_CONVERSION)

#define BOOST_LAMBDA_EMPTY() 

BOOST_LAMBDA_BE(operator+, arithmetic_action<plus_action>, const A, const B, const_copy_argument)
BOOST_LAMBDA_BE(operator-, arithmetic_action<minus_action>, const A, const B, const_copy_argument)
BOOST_LAMBDA_BE(operator*, arithmetic_action<multiply_action>, const A, const B, const_copy_argument)
BOOST_LAMBDA_BE(operator/, arithmetic_action<divide_action>, const A, const B, const_copy_argument)
BOOST_LAMBDA_BE(operator%, arithmetic_action<remainder_action>, const A, const B, const_copy_argument)
BOOST_LAMBDA_BE(operator<<, bitwise_action<leftshift_action>, const A, const B, const_copy_argument)
BOOST_LAMBDA_BE(operator>>, bitwise_action<rightshift_action>, const A, const B, const_copy_argument)
BOOST_LAMBDA_BE(operator&, bitwise_action<and_action>, const A, const B, const_copy_argument)
BOOST_LAMBDA_BE(operator|, bitwise_action<or_action>, const A, const B, const_copy_argument)
BOOST_LAMBDA_BE(operator^, bitwise_action<xor_action>, const A, const B, const_copy_argument)
BOOST_LAMBDA_BE(operator&&, logical_action<and_action>, const A, const B, const_copy_argument)
BOOST_LAMBDA_BE(operator||, logical_action<or_action>, const A, const B, const_copy_argument)
BOOST_LAMBDA_BE(operator<, relational_action<less_action>, const A, const B, const_copy_argument)
BOOST_LAMBDA_BE(operator>, relational_action<greater_action>, const A, const B, const_copy_argument)
BOOST_LAMBDA_BE(operator<=, relational_action<lessorequal_action>, const A, const B, const_copy_argument)
BOOST_LAMBDA_BE(operator>=, relational_action<greaterorequal_action>, const A, const B, const_copy_argument)
BOOST_LAMBDA_BE(operator==, relational_action<equal_action>, const A, const B, const_copy_argument)
BOOST_LAMBDA_BE(operator!=, relational_action<notequal_action>, const A, const B, const_copy_argument)

BOOST_LAMBDA_BE(operator+=, arithmetic_assignment_action<plus_action>, A, const B, reference_argument)
BOOST_LAMBDA_BE(operator-=, arithmetic_assignment_action<minus_action>, A, const B, reference_argument)
BOOST_LAMBDA_BE(operator*=, arithmetic_assignment_action<multiply_action>, A, const B, reference_argument)
BOOST_LAMBDA_BE(operator/=, arithmetic_assignment_action<divide_action>, A, const B, reference_argument)
BOOST_LAMBDA_BE(operator%=, arithmetic_assignment_action<remainder_action>, A, const B, reference_argument)
BOOST_LAMBDA_BE(operator<<=, bitwise_assignment_action<leftshift_action>, A, const B, reference_argument)
BOOST_LAMBDA_BE(operator>>=, bitwise_assignment_action<rightshift_action>, A, const B, reference_argument)
BOOST_LAMBDA_BE(operator&=, bitwise_assignment_action<and_action>, A, const B, reference_argument)
BOOST_LAMBDA_BE(operator|=, bitwise_assignment_action<or_action>, A, const B, reference_argument)
BOOST_LAMBDA_BE(operator^=, bitwise_assignment_action<xor_action>, A, const B, reference_argument)


// A special trick for comma operator for correct preprocessing
#if defined BOOST_LAMBDA_COMMA_OPERATOR_NAME
#error "Multiple defines of BOOST_LAMBDA_COMMA_OPERATOR_NAME"
#endif

#define BOOST_LAMBDA_COMMA_OPERATOR_NAME operator,

BOOST_LAMBDA_BE1(BOOST_LAMBDA_COMMA_OPERATOR_NAME, other_action<comma_action>, const A, const B, const_copy_argument)
BOOST_LAMBDA_BE2(BOOST_LAMBDA_COMMA_OPERATOR_NAME, other_action<comma_action>, const A, const B, const_copy_argument)
BOOST_LAMBDA_BE3(BOOST_LAMBDA_COMMA_OPERATOR_NAME, other_action<comma_action>, const A, const B, const_copy_argument)



namespace detail {

// special cases for ostream& << Any and istream& >> Any ---------------
// the actual stream classes may vary and thus a specialisation for, 
// say ostream& does not match (the general case above is chosen). 
// Therefore we specialise for non-const reference:
// if the left argument is a stream, we store the stream as reference
// if it is something else, we store a const plain by default

// Note that the overloading is const vs. non-const first argument


template<class T> struct convert_ostream_to_ref_others_to_c_plain_by_default {
  typedef typename detail::IF<
                       is_instance_of_2<
                         T, std::basic_ostream
                       >::value,
                       T&,
                       typename const_copy_argument <T>::type
                     >::RET type;
};

template<class T> struct convert_istream_to_ref_others_to_c_plain_by_default {
  typedef typename detail::IF<
                       is_instance_of_2<
                         T, std::basic_istream
                       >::value,
                       T&,
                       typename const_copy_argument <T>::type
                     >::RET type;
};

} // detail

BOOST_LAMBDA_BE2(operator<<, bitwise_action< leftshift_action>, A, const B, detail::convert_ostream_to_ref_others_to_c_plain_by_default)
BOOST_LAMBDA_BE2(operator>>, bitwise_action< rightshift_action>, A, const B, detail::convert_istream_to_ref_others_to_c_plain_by_default)      


// special case for io_manipulators.
// function references cannot be given as arguments to lambda operator
// expressions in general. With << and >> the use of manipulators is
// so common, that specializations are provided to make them work.

template<class Arg, class Ret, class ManipArg>
inline const 
lambda_functor<
  lambda_functor_base<
    bitwise_action<leftshift_action>,
    tuple<lambda_functor<Arg>, Ret(&)(ManipArg)> 
  > 
>
operator<<(const lambda_functor<Arg>& a, Ret(&b)(ManipArg))
{
  return 
      lambda_functor_base<
        bitwise_action<leftshift_action>,
        tuple<lambda_functor<Arg>, Ret(&)(ManipArg)>
      > 
    ( tuple<lambda_functor<Arg>, Ret(&)(ManipArg)>(a, b) );
}

template<class Arg, class Ret, class ManipArg>
inline const 
lambda_functor<
  lambda_functor_base<
    bitwise_action<rightshift_action>,
    tuple<lambda_functor<Arg>, Ret(&)(ManipArg)>
  > 
>
operator>>(const lambda_functor<Arg>& a, Ret(&b)(ManipArg))
{
  return 
      lambda_functor_base<
        bitwise_action<rightshift_action>,
        tuple<lambda_functor<Arg>, Ret(&)(ManipArg)>
      > 
    ( tuple<lambda_functor<Arg>, Ret(&)(ManipArg)>(a, b) );
}


// (+ and -) take their arguments as const references. 
// This has consquences with pointer artihmetic
// E.g int a[]; ... *a = 1 works but not *(a+1) = 1. 
// the result of a+1 would be const
// To make the latter work too, 
// non-const arrays are taken as non-const and stored as non-const as well.
#if defined  BOOST_LAMBDA_PTR_ARITHMETIC_E1
#error "Multiple defines of  BOOST_LAMBDA_PTR_ARITHMETIC_E1"
#endif

#define BOOST_LAMBDA_PTR_ARITHMETIC_E1(OPER_NAME, ACTION, CONSTB)           \
template<class Arg, int N, class B>                                         \
inline const                                                                \
lambda_functor<                                                             \
  lambda_functor_base<ACTION, tuple<lambda_functor<Arg>, CONSTB(&)[N]> >    \
>                                                                           \
OPER_NAME (const lambda_functor<Arg>& a, CONSTB(&b)[N])                     \
{                                                                           \
  return                                                                    \
    lambda_functor_base<ACTION, tuple<lambda_functor<Arg>, CONSTB(&)[N]> >  \
  (tuple<lambda_functor<Arg>, CONSTB(&)[N]>(a, b));                         \
}


#if defined  BOOST_LAMBDA_PTR_ARITHMETIC_E2
#error "Multiple defines of  BOOST_LAMBDA_PTR_ARITHMETIC_E2"
#endif

#define BOOST_LAMBDA_PTR_ARITHMETIC_E2(OPER_NAME, ACTION, CONSTA)           \
template<int N, class A, class Arg>                                         \
inline const                                                                \
lambda_functor<                                                             \
  lambda_functor_base<ACTION, tuple<CONSTA(&)[N], lambda_functor<Arg> > >   \
>                                                                           \
OPER_NAME (CONSTA(&a)[N], const lambda_functor<Arg>& b)                     \
{                                                                           \
  return                                                                    \
    lambda_functor_base<ACTION, tuple<CONSTA(&)[N], lambda_functor<Arg> > > \
    (tuple<CONSTA(&)[N], lambda_functor<Arg> >(a, b));                      \
}


BOOST_LAMBDA_PTR_ARITHMETIC_E1(operator+, arithmetic_action<plus_action>, B)
BOOST_LAMBDA_PTR_ARITHMETIC_E2(operator+, arithmetic_action<plus_action>, A)
BOOST_LAMBDA_PTR_ARITHMETIC_E1(operator+, arithmetic_action<plus_action>,const B)
BOOST_LAMBDA_PTR_ARITHMETIC_E2(operator+, arithmetic_action<plus_action>,const A)


//BOOST_LAMBDA_PTR_ARITHMETIC_E1(operator-, arithmetic_action<minus_action>)
// This is not needed, since the result of ptr-ptr is an rvalue anyway

BOOST_LAMBDA_PTR_ARITHMETIC_E2(operator-, arithmetic_action<minus_action>, A)
BOOST_LAMBDA_PTR_ARITHMETIC_E2(operator-, arithmetic_action<minus_action>, const A)


#undef BOOST_LAMBDA_BE1
#undef BOOST_LAMBDA_BE2
#undef BOOST_LAMBDA_BE3
#undef BOOST_LAMBDA_BE
#undef BOOST_LAMBDA_COMMA_OPERATOR_NAME

#undef BOOST_LAMBDA_PTR_ARITHMETIC_E1
#undef BOOST_LAMBDA_PTR_ARITHMETIC_E2


// ---------------------------------------------------------------------
// unary operators -----------------------------------------------------
// ---------------------------------------------------------------------

#if defined BOOST_LAMBDA_UE
#error "Multiple defines of BOOST_LAMBDA_UE"
#endif

#define BOOST_LAMBDA_UE(OPER_NAME, ACTION)                                 \
template<class Arg>                                                        \
inline const                                                               \
lambda_functor<lambda_functor_base<ACTION, tuple<lambda_functor<Arg> > > > \
OPER_NAME (const lambda_functor<Arg>& a)                                   \
{                                                                          \
  return                                                                   \
    lambda_functor_base<ACTION, tuple<lambda_functor<Arg> > >              \
    ( tuple<lambda_functor<Arg> >(a) );                                    \
}


BOOST_LAMBDA_UE(operator+, unary_arithmetic_action<plus_action>)
BOOST_LAMBDA_UE(operator-, unary_arithmetic_action<minus_action>)
BOOST_LAMBDA_UE(operator~, bitwise_action<not_action>)
BOOST_LAMBDA_UE(operator!, logical_action<not_action>)
BOOST_LAMBDA_UE(operator++, pre_increment_decrement_action<increment_action>)
BOOST_LAMBDA_UE(operator--, pre_increment_decrement_action<decrement_action>)
BOOST_LAMBDA_UE(operator*, other_action<contentsof_action>)
BOOST_LAMBDA_UE(operator&, other_action<addressof_action>)

#if defined BOOST_LAMBDA_POSTFIX_UE
#error "Multiple defines of BOOST_LAMBDA_POSTFIX_UE"
#endif

#define BOOST_LAMBDA_POSTFIX_UE(OPER_NAME, ACTION)                         \
template<class Arg>                                                        \
inline const                                                               \
lambda_functor<lambda_functor_base<ACTION, tuple<lambda_functor<Arg> > > > \
OPER_NAME (const lambda_functor<Arg>& a, int)                              \
{                                                                          \
  return                                                                   \
    lambda_functor_base<ACTION, tuple<lambda_functor<Arg> > >              \
    ( tuple<lambda_functor<Arg> >(a) );                                    \
}


BOOST_LAMBDA_POSTFIX_UE(operator++, post_increment_decrement_action<increment_action>)
BOOST_LAMBDA_POSTFIX_UE(operator--, post_increment_decrement_action<decrement_action>)

#undef BOOST_LAMBDA_UE
#undef BOOST_LAMBDA_POSTFIX_UE

} // namespace lambda
} // namespace boost

#endif

/* operators.hpp
+8F/PvBV4D7UjyVvSP3Y1Mcf5c6lvnxmtTLrxFHFgbWvfuj+lvCvjw20fXfLfYrlXYC6WfdRl+UdgHye/nIgXcrh52p5/p1Ys+1fIG6Z1vcEUx9sIf23gL0ZL/z8o8y9FlaIzKLYn6pnY9w6vdBNq91SHmM7qoFBfTGWNfklCM+OdvEqo51ZR7cX985B9fFjb8ENKRLQ/0fx89LYC9WvdT4sgXuKyPaJDeSvMrgliVt2rA4H6/VuDMeX5PnOoP7YQHHbo7rQv7PlfiCse3nyShhqE4QfbNpb5rcJNTsSsIi25vXO/XFob3Lnsfib3XlA53M7n9UhqV067ipAKR3i27UDFoEycN0D6JPDfXvEd4hN6JjRoX1CamKHDgmxgxJiT+t8CdwS2ie0w0c9M5+bbWEvoy3sWu+GLzUmVvb96ax6oH5j/SW/ffJ8lbSVpq0/brJNUH94mctLG/Wg20XiNkLXxfGgAyL7Np7vbuKle+Kb0k7q8CWAfiK8Nzix6i/qb/hC2c8ZosORBLpEZGKb6m+6nSluN0LPYCVxoXuV6PoBYhMb1B7+SNypg27XSrgvRXv4hQ5POuh14X0Q4XlN1SP+R9H+9Tbav5fleR2eZznZeM8c4lSqZ5xk6uA3P+FJgs3vUfeqRMy7qHR6G+3bk/L8XDx/SdXBHj9S2c5nRryzQQ8IT/em+NGtRsI8E23cLuFNZ3v2mPB+K6Yn45cLihPeRqcLbDpalTpSZgLfiOVZQYzka7Zjf9tNN+b/4aA/G27JbL9OE9kY3X7larf+ur3JRrmQ+gI1YqC9yTHcyOfkhriNjBka4ubE5IXqU8ND+VR+qD6nIFQ2Znwon5oQqs/xhbq1m2G4ufXfHbiX9ayeNmd/lOvSg9sctgt8l6Cb3Cc0vwd42qQiuS9s7sN77m8OnmOezm+dMfJdXF0H3OuOT+0x2qyrr5QGi+9abGMs41J7QtsYsx/+/ttN4y0DkHt7Gu3MXSL3kcrHv+8HyiWf3SAyGXib/bEy8516h2ND3rbOGo4rgtqTSaJzmDNX3R00HnKnuKc5V6o7dT/L/b0hfjnkdYT32+J2Efw42z4utsfbLhfpd9lHRDZet4tPiL8/UbeoRMuaN5sujH9QtpPoSrSMQdnkJgpflsGXRT49zsN223x3f0yel6he9HOZ3A+KiYHbdHWN2oGZhQedfqob3+3/Kc9vRx7ry3OxA25vOZmw2Sr1vlru5Hjbe51Ptok9noT714PGsV4RHfEx+ephxxw7aS/8RVqHREHctsD/R4La61Fir25B7dhW0Ts2qB3rKfLni1s63R4U2fOpj3mDacm8KXzXimxXcyyT8Y+hPnGjrKPHQJYIT37MEOcFlcY6zHXfKfrq1Atu2WD9dAzuW8T9NOdVuBt9ronmPhFPi841znN40x/kJBo2vyWob/O56PpSkK3+Im7nBb2vZEuYuxpjo6abjMExvImIBcMlktVVs/zNeepxkemuzxqpzdAk9WV6pPEX1pFZRn0Y76kPkzzjJumsPwP1Y6a+L5T7LH0/0TsGIveH9f0teg78DKf15qi3dA75CwMcuGcOXLr/06KHdi1ZkbH7wGm9feHOamj53PKWzvG2zyEPPxfdPrc87Fx986xm6U9Xs26U+WgOx5P5naWaad+HTcVqzvf6HnAq8FngPOAPeKbvi8A64GvAg8C3gMmQ3QhM4fzETOAeYH/gj4FX8vm1fH4D8D1gBfAD4ALgfuBi4M+BjwIPAHeQfyewAbgb+EvgXrrvA34M/A3wEPBPwE+BR4G/Bv4LeBjYPgZxBQ4B/h54FfAPwPt4/zDwT65+4GfAA8C/Aj8Fcr4l/OfYGcf0qoGngfY=
*/