// Boost Lambda Library -- switch.hpp -----------------------------------
//
// Copyright (C) 2000 Gary Powell (powellg@amazon.com)
// Copyright (C) 1999, 2000 Jaakko Jarvi (jaakko.jarvi@cs.utu.fi)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org

// --------------------------------------------------------------------------

#if !defined(BOOST_LAMBDA_SWITCH_HPP)
#define BOOST_LAMBDA_SWITCH_HPP

#include "boost/lambda/core.hpp"
#include "boost/lambda/detail/control_constructs_common.hpp"

#include "boost/preprocessor/enum_shifted_params.hpp"
#include "boost/preprocessor/repeat_2nd.hpp"
#include "boost/preprocessor/tuple.hpp"

namespace boost { 
namespace lambda {

// Switch actions
template <int N, class Switch1 = null_type, class Switch2 = null_type, 
          class Switch3 = null_type, class Switch4 = null_type,
          class Switch5 = null_type, class Switch6 = null_type, 
          class Switch7 = null_type, class Switch8 = null_type, 
          class Switch9 = null_type>
struct switch_action {};


namespace detail {

  // templates to represent special lambda functors for the cases in 
  // switch statements
  
template <int Value> struct case_label {};
struct default_label {};

template<class Type> struct switch_case_tag {};

  // a normal case is represented as:
  // tagged_lambda_functor<switch_case_tag<case_label<N> > >, LambdaFunctor>
  
  // the default case as:
  // tagged_lambda_functor<switch_case_tag<default_label> >, LambdaFunctor>


} // end detail


/// create switch_case_tag tagged_lambda_functors
template <int CaseValue, class Arg>
inline const 
tagged_lambda_functor<
  detail::switch_case_tag<detail::case_label<CaseValue> >, 
  lambda_functor<Arg> 
> 
case_statement(const lambda_functor<Arg>& a) { 
  return 
    tagged_lambda_functor<
      detail::switch_case_tag<detail::case_label<CaseValue> >, 
      lambda_functor<Arg> 
    >(a); 
}

// No case body case.
template <int CaseValue>
inline const 
tagged_lambda_functor<
  detail::switch_case_tag<detail::case_label<CaseValue> >,
  lambda_functor< 
    lambda_functor_base< 
      do_nothing_action, 
      null_type
    > 
  > 
> 
case_statement() { 
return 
  tagged_lambda_functor<
    detail::switch_case_tag<detail::case_label<CaseValue> >,
    lambda_functor< 
      lambda_functor_base< 
        do_nothing_action, 
        null_type
      > 
    > 
  > () ;
}

// default label
template <class Arg>
inline const 
tagged_lambda_functor<
  detail::switch_case_tag<detail::default_label>, 
  lambda_functor<Arg> 
> 
default_statement(const lambda_functor<Arg>& a) { 
  return 
    tagged_lambda_functor<
      detail::switch_case_tag<detail::default_label>, 
      lambda_functor<Arg> 
    >(a); 
}

// default lable, no case body case.
inline const 
tagged_lambda_functor<
  detail::switch_case_tag<detail::default_label>,
  lambda_functor< 
    lambda_functor_base< 
      do_nothing_action, 
      null_type
    > 
  > 
> 
default_statement() { 
return 
      lambda_functor_base< 
        do_nothing_action, 
        null_type 
      > () ;
}


// Specializations for lambda_functor_base of case_statement -----------------

// 0 case type:
// useless (just the condition part) but provided for completeness.
template<class Args>
class 
lambda_functor_base<
  switch_action<1>, 
  Args
> 
{
public:
  Args args;
  template <class SigArgs> struct sig { typedef void type; };
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template<class RET, CALL_TEMPLATE_ARGS>
  RET call(CALL_FORMAL_ARGS) const {
    detail::select(::boost::tuples::get<1>(args), CALL_ACTUAL_ARGS);  
  }
};

// 1 case type:
// template<class Args, int Case1>
// class 
// lambda_functor_base<
//   action<
//     2, 
//     return_void_action<switch_action<detail::case_label<Case1> > > 
//   >, 
//   Args
// > 
// {
//   Args args;
// public:
//   explicit lambda_functor_base(const Args& a) : args(a) {}

//   template<class RET, class A, class B, class C>
//   RET call(A& a, B& b, C& c) const {
//     switch( detail::select(::boost::tuples::get<0>(args), a, b, c) )  
//     {
//       case Case1:                
//         detail::select(::boost::tuples::get<1>(args), a, b, c);
//         break;
//     }
//   }
// };

// switch with default being the sole label - doesn't make much sense but
// it is there for completeness
// template<class Args>
// class
// lambda_functor_base<
//   action<
//     2,
//     return_void_action<switch_action<detail::default_label> >
//   >,
//   Args
// >
// {
//   Args args;
// public:
//   explicit lambda_functor_base(const Args& a) : args(a) {}
// 
//   template<class RET, class A, class B, class C>
//   RET call(A& a, B& b, C& c) const {
//     switch( detail::select(::boost::tuples::get<0>(args), a, b, c) )
//     {
//       default:
//         detail::select(::boost::tuples::get<1>(args), a, b, c);
//         break;
//     }
//   }
// };



// // 2 case type:
// The different specializations are generated with Vesa Karvonen's 
// preprocessor library.

// This is just a comment to show what the generated classes look like

// template<class Args, int Case1, int Case2>
// class 
// lambda_functor_base<
//   action<3, 
//     return_void_action< 
//       switch_action< 
//         detail::case_label<Case1>,
//         detail::case_label<Case2>
//       > 
//     > 
//   >, 
//   Args
// > 
// {
//   Args args;
// public:
//   explicit lambda_functor_base(const Args& a) : args(a) {}

//   template<class RET, class A, class B, class C>
//   RET call(A& a, B& b, C& c) const {
//     switch( detail::select(::boost::tuples::get<0>(args), a, b, c) )  
//     {
//       case Case1:                
//         detail::select(::boost::tuples::get<1>(args), a, b, c);
//         break;
//       case Case2:                
//         detail::select(::boost::tuples::get<2>(args), a, b, c);
//         break;
//     }
//   }
// };

// template<class Args, int Case1>
// class 
// lambda_functor_base<
//   action<3, 
//     return_void_action< 
//       switch_action< 
//         detail::case_label<Case1>,
//         detail::default_label 
//       > 
//     > 
//   >, 
//   Args
// > 
// {
//   Args args;
// public:
//   explicit lambda_functor_base(const Args& a) : args(a) {}

//   template<class RET, class A, class B, class C>
//   RET call(A& a, B& b, C& c) const {
//     switch( detail::select(::boost::tuples::get<0>(args), a, b, c) )  
//     {
//       case Case1:                
//         detail::select(::boost::tuples::get<1>(args), a, b, c);
//         break;
//       default:                
//         detail::select(::boost::tuples::get<2>(args), a, b, c);
//         break;
//     }
//   }
// };
// -------------------------

// Some helper preprocessor macros ---------------------------------

// BOOST_LAMBDA_A_I_LIST(N, X) is a list of form X0, X1, ..., XN
// BOOST_LAMBDA_A_I_B_LIST(N, X, Y) is a list of form X0 Y, X1 Y, ..., XN Y

#define BOOST_LAMBDA_A_I(z, i, A) \
BOOST_PP_COMMA_IF(i) BOOST_PP_CAT(A,i)

#define BOOST_LAMBDA_A_I_B(z, i, T) \
BOOST_PP_COMMA_IF(i) BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(2,0,T),i) BOOST_PP_TUPLE_ELEM(2,1,T)

#define BOOST_LAMBDA_A_I_LIST(i, A) \
BOOST_PP_REPEAT(i,BOOST_LAMBDA_A_I, A) 

#define BOOST_LAMBDA_A_I_B_LIST(i, A, B) \
BOOST_PP_REPEAT(i,BOOST_LAMBDA_A_I_B, (A,B)) 


// Switch related macros -------------------------------------------
#define BOOST_LAMBDA_SWITCH_CASE_BLOCK(z, N, A) \
  case Case##N: \
  detail::select(::boost::tuples::get<BOOST_PP_INC(N)>(args), CALL_ACTUAL_ARGS); \
  break;

#define BOOST_LAMBDA_SWITCH_CASE_BLOCK_LIST(N) \
BOOST_PP_REPEAT(N, BOOST_LAMBDA_SWITCH_CASE_BLOCK, FOO)
// 2 case type:

#define BOOST_LAMBDA_SWITCH_NO_DEFAULT_CASE(N)                                \
template<class Args, BOOST_LAMBDA_A_I_LIST(N, int Case)>                      \
class                                                                         \
lambda_functor_base<                                                          \
      switch_action<BOOST_PP_INC(N),                                          \
        BOOST_LAMBDA_A_I_B_LIST(N, detail::case_label<Case,>)                 \
      >,                                                                      \
  Args                                                                        \
>                                                                             \
{                                                                             \
public:                                                                       \
  Args args;                                                                  \
  template <class SigArgs> struct sig { typedef void type; };                 \
public:                                                                       \
  explicit lambda_functor_base(const Args& a) : args(a) {}                    \
                                                                              \
  template<class RET, CALL_TEMPLATE_ARGS>                                     \
  RET call(CALL_FORMAL_ARGS) const {                                          \
    switch( detail::select(::boost::tuples::get<0>(args), CALL_ACTUAL_ARGS) ) \
    {                                                                         \
      BOOST_LAMBDA_SWITCH_CASE_BLOCK_LIST(N)                                  \
    }                                                                         \
  }                                                                           \
};

        

#define BOOST_LAMBDA_SWITCH_WITH_DEFAULT_CASE(N)                              \
template<                                                                     \
  class Args BOOST_PP_COMMA_IF(BOOST_PP_DEC(N))                               \
  BOOST_LAMBDA_A_I_LIST(BOOST_PP_DEC(N), int Case)                            \
>                                                                             \
class                                                                         \
lambda_functor_base<                                                          \
      switch_action<BOOST_PP_INC(N),                                          \
        BOOST_LAMBDA_A_I_B_LIST(BOOST_PP_DEC(N),                              \
                                detail::case_label<Case, >)                   \
        BOOST_PP_COMMA_IF(BOOST_PP_DEC(N))                                    \
        detail::default_label                                                 \
      >,                                                                      \
  Args                                                                        \
>                                                                             \
{                                                                             \
public:                                                                       \
  Args args;                                                                  \
  template <class SigArgs> struct sig { typedef void type; };                 \
public:                                                                       \
  explicit lambda_functor_base(const Args& a) : args(a) {}                    \
                                                                              \
  template<class RET, CALL_TEMPLATE_ARGS>                                     \
  RET call(CALL_FORMAL_ARGS) const {                                          \
    switch( detail::select(::boost::tuples::get<0>(args), CALL_ACTUAL_ARGS) ) \
    {                                                                         \
        BOOST_LAMBDA_SWITCH_CASE_BLOCK_LIST(BOOST_PP_DEC(N))                  \
      default:                                                                \
        detail::select(::boost::tuples::get<N>(args), CALL_ACTUAL_ARGS);      \
        break;                                                                \
    }                                                                         \
  }                                                                           \
};






// switch_statement bind functions -------------------------------------

// The zero argument case, for completeness sake
inline const 
lambda_functor< 
  lambda_functor_base< 
    do_nothing_action, 
    null_type
  > 
>
switch_statement() { 
  return 
      lambda_functor_base< 
        do_nothing_action, 
        null_type
      > 
  ();
}

// 1 argument case, this is useless as well, just the condition part
template <class TestArg>
inline const 
lambda_functor< 
  lambda_functor_base< 
    switch_action<1>, 
    tuple<lambda_functor<TestArg> >
  > 
>
switch_statement(const lambda_functor<TestArg>& a1) { 
  return 
      lambda_functor_base< 
         switch_action<1>, 
         tuple< lambda_functor<TestArg> > 
      > 
    ( tuple<lambda_functor<TestArg> >(a1));
}


#define HELPER(z, N, FOO)                                      \
BOOST_PP_COMMA_IF(N)                                           \
BOOST_PP_CAT(                                                  \
  const tagged_lambda_functor<detail::switch_case_tag<TagData, \
  N>)                                                          \
BOOST_PP_COMMA() Arg##N>& a##N

#define HELPER_LIST(N) BOOST_PP_REPEAT(N, HELPER, FOO)


#define BOOST_LAMBDA_SWITCH_STATEMENT(N)                              \
template <class TestArg,                                              \
          BOOST_LAMBDA_A_I_LIST(N, class TagData),                    \
          BOOST_LAMBDA_A_I_LIST(N, class Arg)>                        \
inline const                                                          \
lambda_functor<                                                       \
  lambda_functor_base<                                                \
        switch_action<BOOST_PP_INC(N),                                \
          BOOST_LAMBDA_A_I_LIST(N, TagData)                           \
        >,                                                            \
    tuple<lambda_functor<TestArg>, BOOST_LAMBDA_A_I_LIST(N, Arg)>     \
  >                                                                   \
>                                                                     \
switch_statement(                                                     \
  const lambda_functor<TestArg>& ta,                                  \
  HELPER_LIST(N)                                                      \
)                                                                     \
{                                                                     \
  return                                                              \
      lambda_functor_base<                                            \
            switch_action<BOOST_PP_INC(N),                            \
              BOOST_LAMBDA_A_I_LIST(N, TagData)                       \
            >,                                                        \
        tuple<lambda_functor<TestArg>, BOOST_LAMBDA_A_I_LIST(N, Arg)> \
      >                                                               \
    ( tuple<lambda_functor<TestArg>, BOOST_LAMBDA_A_I_LIST(N, Arg)>   \
        (ta, BOOST_LAMBDA_A_I_LIST(N, a) ));                          \
}




// Here's the actual generation

#define BOOST_LAMBDA_SWITCH(N)           \
BOOST_LAMBDA_SWITCH_NO_DEFAULT_CASE(N)   \
BOOST_LAMBDA_SWITCH_WITH_DEFAULT_CASE(N)        

// Use this to avoid case 0, these macros work only from case 1 upwards
#define BOOST_LAMBDA_SWITCH_HELPER(z, N, A) \
BOOST_LAMBDA_SWITCH( BOOST_PP_INC(N) )

// Use this to avoid cases 0 and 1, these macros work only from case 2 upwards
#define BOOST_LAMBDA_SWITCH_STATEMENT_HELPER(z, N, A) \
BOOST_LAMBDA_SWITCH_STATEMENT(BOOST_PP_INC(N))

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable:4065)
#endif

  // up to 9 cases supported (counting default:)
BOOST_PP_REPEAT_2ND(9,BOOST_LAMBDA_SWITCH_HELPER,FOO)
BOOST_PP_REPEAT_2ND(9,BOOST_LAMBDA_SWITCH_STATEMENT_HELPER,FOO)

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

} // namespace lambda 
} // namespace boost


#undef HELPER
#undef HELPER_LIST

#undef BOOST_LAMBDA_SWITCH_HELPER
#undef BOOST_LAMBDA_SWITCH
#undef BOOST_LAMBDA_SWITCH_NO_DEFAULT_CASE
#undef BOOST_LAMBDA_SWITCH_WITH_DEFAULT_CASE

#undef BOOST_LAMBDA_SWITCH_CASE_BLOCK
#undef BOOST_LAMBDA_SWITCH_CASE_BLOCK_LIST

#undef BOOST_LAMBDA_SWITCH_STATEMENT
#undef BOOST_LAMBDA_SWITCH_STATEMENT_HELPER



#endif








/* switch.hpp
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
*/