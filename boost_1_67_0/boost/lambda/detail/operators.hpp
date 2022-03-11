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