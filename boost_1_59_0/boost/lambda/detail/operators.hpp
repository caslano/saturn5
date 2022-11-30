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
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
*/