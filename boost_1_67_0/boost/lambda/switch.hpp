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