// -- Boost Lambda Library -- exceptions.hpp ----------------
//
// Copyright (C) 2000 Gary Powell (gwpowell@hotmail.com)
// Copyright (C) 1999, 2000 Jaakko Jarvi (jaakko.jarvi@cs.utu.fi)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org 

// -----------------------------------------------------

#if !defined(BOOST_LAMBDA_EXCEPTIONS_HPP)
#define BOOST_LAMBDA_EXCEPTIONS_HPP

#include "boost/lambda/core.hpp"
#include "boost/lambda/detail/control_constructs_common.hpp"

namespace boost { 
namespace lambda {

typedef lambda_functor<placeholder<EXCEPTION> > placeholderE_type;

namespace {
  boost::lambda::placeholderE_type freeE;
  boost::lambda::placeholderE_type& _e = freeE;        
}

// -- exception related actions -------------------

// catch actions.
template <class Catch1, class Catch2 = null_type, class Catch3 = null_type, 
          class Catch4 = null_type, class Catch5 = null_type, 
          class Catch6 = null_type, class Catch7 = null_type, 
          class Catch8 = null_type, class Catch9 = null_type, 
          class Catch10 = null_type>
struct catch_action {};

struct catch_all_action {};

template<class CatchActions>
struct return_try_catch_action {};

template<class CatchActions>
struct try_catch_action {};

// rethrow actions
struct throw_new_action {};
struct rethrow_action {};

template<class ThrowType> struct throw_action;

template<>
struct throw_action<rethrow_action> {
  template<class RET>
  static RET apply() {
    throw;
  }
};

template<> struct throw_action<throw_new_action> {
  template<class RET, class T>
  static RET apply(T& t) {
    throw t;
  }
};

// return types for throw_actions --------------------------------------------

template<class T, class Any>
struct 
return_type_N<throw_action<T>, Any> {
  typedef void type;
};


// return types deductions -------------------------------------------------

// the return type of try_catch is the return type of the try lambda_functor
// (the return types of try and catch parts must match unless try returns void
// or the catch part throws for sure)

// NOTE, the exception placeholder deduction rule is defined 
// in return_type_traits.hpp



// defined in control_constructs
class ifthenelse_action;

namespace detail {

// Templates for deducing, wether a lambda_functor throws inevitably of not -
// This mechanism is needed to make the compiler happy about
// return types of try and catch parts. 

// a lambda_functor throws for sure if:
//  - it is a throw expression
//  - it is a comma expression, and one of its arguments throws for sure
//  - it is an if_then_else expression and either the if statement or both 
//  the then and  else throw.
// (there are other cases as well, but we do not cover them)
// e.g. _1 + (rethrow(), 3) does throw for sure but this is not checked
// This implies, that in such a case, the return types of try and catch parts 
// must match if the try part returns other than void.
// (Such checks could be done though)

template <class Arg> 
struct throws_for_sure_phase2 {
  static const bool value = false;
};

template <int N, class ThrowType, class Args> 
struct throws_for_sure_phase2<
  lambda_functor< 
    lambda_functor_base<action<N, throw_action<ThrowType> >, Args> 
  > 
>
{
  static const bool value = true;
};

// Both then and else or the if throw of an if_then_else.
template <class Args> 
struct throws_for_sure_phase2<
  lambda_functor<
    lambda_functor_base<
      ifthenelse_action, Args
    > 
  > 
>
{
  static const bool value =
    throws_for_sure_phase2<
      typename boost::tuples::element<0, Args>::type>::value
    ||  
    (
       throws_for_sure_phase2<
         typename boost::tuples::element<1, Args>::type
       >::value
       && 
       throws_for_sure_phase2<
         typename boost::tuples::element<2, Args>::type
       >::value
    );
};

template <class Args> 
struct throws_for_sure_phase2<
  lambda_functor< 
    lambda_functor_base< other_action<comma_action>, Args> 
  > 
>
{
  static const bool value =
    throws_for_sure_phase2<
      typename boost::tuples::element<0, Args>::type
    >::value
    || 
    throws_for_sure_phase2<
      typename boost::tuples::element<1, Args>::type
    >::value;
};

  // get rid of any qualifiers and references
  // lambda_functors should be stored like that, so this is to be extra sure 
template <class Arg> 
struct throws_for_sure {
  static const bool value 
    = throws_for_sure_phase2<
        typename detail::remove_reference_and_cv<Arg>::type
      >::value;
};


// -- return_or_throw templates -----------------------------

// false case, catch and try return types are incompatible
// Now the catch part must throw for sure, otherwise a compile time error
// occurs.
template<bool is_conversion>
struct return_or_throw_phase2 {
  template<class RET, class Arg, CALL_TEMPLATE_ARGS>
  static RET call(Arg& arg, CALL_FORMAL_ARGS) {
    BOOST_STATIC_ASSERT(throws_for_sure<Arg>::value);
    detail::select(arg, CALL_ACTUAL_ARGS); // this line throws
    throw 1; // this line is never performed, hence 1 is just a dummy
             // The line is needed to make compiler happy and not require
             // a matching return type
  }
};

// the try and catch return types are compatible
template<>
struct return_or_throw_phase2<true> {
  template<class RET, class Arg, CALL_TEMPLATE_ARGS>
  static RET call(Arg& arg, CALL_FORMAL_ARGS) {
    return detail::select(arg, CALL_ACTUAL_ARGS);
  }
};


// the non-void case. Try part returns a value, so catch parts must 
// return a value of the same type or throw
template<class RET, class ARG>
struct return_or_throw {
  // Arg should be equal to ARG except that ARG may be a reference
  // to be sure, that there are no suprises for peculiarly defined return types
  // ARG is passed explicitely
  template<class Arg, CALL_TEMPLATE_ARGS>
  static RET call(Arg& arg, CALL_FORMAL_ARGS)
  {        
    //    typedef typename Arg::return_type<ARG, open_args<A&, B&, C&> >::type RT;        
    typedef typename as_lambda_functor<ARG>::type lf_type;
    typedef typename lf_type::inherited::template 
      sig<tuple<CALL_REFERENCE_TYPES> >::type RT;  

    return 
      return_or_throw_phase2<
        ::boost::is_convertible<RT, RET>::value
      >::template call<RET>(arg, CALL_ACTUAL_ARGS);
  }
};

// if try part returns void, we do not return the catch parts either
template<class ARG>
struct return_or_throw<void, ARG> {
  template<class Arg, CALL_TEMPLATE_ARGS>
  static void call(Arg& arg, CALL_FORMAL_ARGS) { detail::select(arg, CALL_ACTUAL_ARGS); }
};

} // end detail

// Throwing exceptions ---------------------------------------------

namespace detail {

template <class T> struct catch_block {}; 
struct catch_all_block {};

template <class T> struct exception_catch_tag {};

// normal catch block is represented as
// tagged_lambda_functor<exception_catch_tag<catch_type<T> > >, LambdaFunctor>
  
// the default catch all block as:
// tagged_lambda_functor<exception_catch_tag<catch_all_block> >, LambdaFunctor>


} // end detail

// the code is RETHROW, this ensures that a compile time error results, 
// if this lambda_functor is used outside a delayed catch_expression
inline const 
lambda_functor< 
  lambda_functor_base< 
    action<0, throw_action<rethrow_action> >, 
    null_type
  > 
>
rethrow() { 
  return 
      lambda_functor_base< 
        action<0, throw_action<rethrow_action> >,
        null_type
      > 
    ( null_type() );
}

template <class Arg1>
inline const 
lambda_functor<
  lambda_functor_base< 
    action<1, throw_action<throw_new_action> >, 
    tuple<typename const_copy_argument<const Arg1>::type>
  > 
>
throw_exception(const Arg1& a1) { 
  return 
      lambda_functor_base< 
        action<1, throw_action<throw_new_action> >, 
        tuple<typename const_copy_argument<const Arg1>::type>
      > 
    ( tuple<typename const_copy_argument<const Arg1>::type>(a1));
}

// create catch blocks
template <class CatchType, class Arg>
inline const 
tagged_lambda_functor<
  detail::exception_catch_tag<detail::catch_block<CatchType> >, 
  lambda_functor<Arg> 
> 
catch_exception(const lambda_functor<Arg>& a) { 
  // the third placeholder cannot be used in catch_exception
  //    BOOST_STATIC_ASSERT((!has_placeholder<Arg, THIRD>::value));
  return 
    tagged_lambda_functor<
      detail::exception_catch_tag<detail::catch_block<CatchType> >, 
      lambda_functor<Arg> 
    > (a);
}

// catch and do nothing case.
template <class CatchType>
inline const 
tagged_lambda_functor<
  detail::exception_catch_tag<detail::catch_block<CatchType> >, 
  lambda_functor<
    lambda_functor_base<
      do_nothing_action,
      null_type
    > 
  >
>
catch_exception() { 
  return 
    tagged_lambda_functor<
      detail::exception_catch_tag<detail::catch_block<CatchType> >, 
      lambda_functor<
        lambda_functor_base<
          do_nothing_action,
          null_type
        > 
      >
    > ();
}

// create catch(...) blocks
template <class Arg>
inline const 
tagged_lambda_functor<
  detail::exception_catch_tag<detail::catch_all_block>, 
  lambda_functor<Arg> 
> 
catch_all(const lambda_functor<Arg>& a) { 
  // the third placeholder cannot be used in catch_exception
  BOOST_STATIC_ASSERT((!has_placeholder<Arg, THIRD>::value));
  return 
    tagged_lambda_functor<
      detail::exception_catch_tag<detail::catch_all_block>, 
      lambda_functor<Arg> 
    > (a);
}

// catch(...) and do nothing case.
inline const 
tagged_lambda_functor<
  detail::exception_catch_tag<detail::catch_all_block>, 
  lambda_functor<
    lambda_functor_base<
      do_nothing_action,
      null_type
    > 
  >
>
catch_all() { 
  return 
    tagged_lambda_functor<
      detail::exception_catch_tag<detail::catch_all_block>, 
      lambda_functor<
        lambda_functor_base<
          do_nothing_action,
          null_type
        > 
      > 
    > ();
}

// try_catch functions --------------------------------
// The second -> N argument(s) are must be catch lambda_functors 
template <class TryArg, class Catch1, class LF1>
inline const 
lambda_functor< 
  lambda_functor_base< 
    action<2, try_catch_action<catch_action<Catch1> > >, 
    tuple<lambda_functor<TryArg>, LF1>
  > 
>
try_catch(
  const lambda_functor<TryArg>& a1, 
  const tagged_lambda_functor<detail::exception_catch_tag<Catch1>, LF1>& a2) 
{ 
  return 
    lambda_functor_base< 
      action<2, try_catch_action<catch_action<Catch1> > >, 
      tuple<lambda_functor<TryArg>, LF1>
    > 
    ( tuple< lambda_functor<TryArg>, LF1>(a1, a2));
}

template <class TryArg, class Catch1, class LF1, 
                        class Catch2, class LF2>
inline const 
  lambda_functor< 
    lambda_functor_base< 
      action<3, try_catch_action<catch_action<detail::catch_block<Catch1>, Catch2> > >, 
      tuple<lambda_functor<TryArg>, LF1, LF2>
    > 
>
try_catch(
  const lambda_functor<TryArg>& a1, 
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch1> >, LF1>& a2,
  const tagged_lambda_functor<detail::exception_catch_tag<Catch2>, LF2>& a3) 
{ 
  return 
    lambda_functor_base<
      action<3, try_catch_action<catch_action<detail::catch_block<Catch1>, Catch2> > >, 
      tuple<lambda_functor<TryArg>, LF1, LF2>
    > 
    ( tuple<lambda_functor<TryArg>, LF1, LF2>(a1, a2, a3));
}

template <class TryArg, class Catch1, class LF1, 
                        class Catch2, class LF2, 
                        class Catch3, class LF3>
inline const lambda_functor< 
  lambda_functor_base< 
    action<4, try_catch_action<catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2>, Catch3> > >, 
    tuple<lambda_functor<TryArg>, LF1, LF2, LF3>
  > 
>
try_catch(
  const lambda_functor<TryArg>& a1, 
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch1> >, LF1>& a2,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch2> >, LF2>& a3,
  const tagged_lambda_functor<detail::exception_catch_tag<Catch3>, LF3>& a4) 
{ 
  return 
      lambda_functor_base< 
        action<4, try_catch_action<catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2>, Catch3> > >, 
        tuple<lambda_functor<TryArg>, LF1, LF2, LF3>
      > 
    ( tuple<lambda_functor<TryArg>, LF1, LF2, LF3>(a1, a2, a3, a4));
}

template <class TryArg, class Catch1, class LF1, 
                        class Catch2, class LF2, 
                        class Catch3, class LF3, 
                        class Catch4, class LF4>
inline const 
lambda_functor< 
  lambda_functor_base< 
    action<
      5, 
      try_catch_action<
        catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>, Catch4> 
      > 
    >, 
    tuple<lambda_functor<TryArg>, LF1, LF2, LF3, LF4> 
  > 
>
try_catch(
  const lambda_functor<TryArg>& a1, 
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch1> >, LF1>& a2,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch2> >, LF2>& a3,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch3> >, LF3>& a4,
  const tagged_lambda_functor<detail::exception_catch_tag<Catch4>, LF4>& a5) 
{ 
  return 
      lambda_functor_base< 
        action<
          5, 
          try_catch_action<catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>, Catch4> > 
        >, 
        tuple<lambda_functor<TryArg>, LF1, LF2, LF3, LF4>
      > 
    ( tuple<lambda_functor<TryArg>, LF1, LF2, LF3, LF4>(a1, a2, a3, a4, a5));
}

template <class TryArg, class Catch1, class LF1, 
                        class Catch2, class LF2, 
                        class Catch3, class LF3, 
                        class Catch4, class LF4, 
                        class Catch5, class LF5>
inline const 
lambda_functor< 
  lambda_functor_base< 
    action<
      6, 
      try_catch_action<catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>, detail::catch_block<Catch4>, Catch5> >
    >, 
    tuple<lambda_functor<TryArg>, LF1, LF2, LF3, LF4, LF5>
  > 
>
try_catch(
  const lambda_functor<TryArg>& a1, 
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch1> >, LF1>& a2,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch2> >, LF2>& a3,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch3> >, LF3>& a4,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch4> >, LF4>& a5,
  const tagged_lambda_functor<detail::exception_catch_tag<Catch5>, LF5>& a6) 
{ 
  return 
      lambda_functor_base< 
         action<
           6, 
           try_catch_action<
             catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>, detail::catch_block<Catch4>, Catch5> 
           > 
         >, 
         tuple<lambda_functor<TryArg>, LF1, LF2, LF3, LF4, LF5>
      > 
    ( tuple<lambda_functor<TryArg>, LF1, LF2, LF3, LF4, LF5>
        (a1, a2, a3, a4, a5, a6)
    );
}

template <class TryArg, class Catch1, class LF1, 
                        class Catch2, class LF2, 
                        class Catch3, class LF3, 
                        class Catch4, class LF4, 
                        class Catch5, class LF5, 
                        class Catch6, class LF6>
inline const 
lambda_functor< 
  lambda_functor_base< 
    action<
      7, 
      try_catch_action<
        catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>, detail::catch_block<Catch4>, detail::catch_block<Catch5>, Catch6> 
      > 
    >, 
    tuple<lambda_functor<TryArg>, LF1, LF2, LF3, LF4, LF5, LF6>
  > 
>
try_catch(
  const lambda_functor<TryArg>& a1, 
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch1> >, LF1>& a2,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch2> >, LF2>& a3,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch3> >, LF3>& a4,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch4> >, LF4>& a5,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch5> >, LF5>& a6,
  const tagged_lambda_functor<detail::exception_catch_tag<Catch6>, LF6>& a7) 
{ 
  return 
      lambda_functor_base< 
        action<
          7, 
          try_catch_action<
            catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>, detail::catch_block<Catch4>, detail::catch_block<Catch5>,Catch6> 
          > 
        >, 
        tuple<lambda_functor<TryArg>, LF1, LF2, LF3, LF4, LF5, LF6>
      > 
    ( tuple<lambda_functor<TryArg>, LF1, LF2, LF3, LF4, LF5, LF6>
        (a1, a2, a3, a4, a5, a6, a7));
}

template <class TryArg, class Catch1, class LF1, 
                        class Catch2, class LF2, 
                        class Catch3, class LF3, 
                        class Catch4, class LF4, 
                        class Catch5, class LF5, 
                        class Catch6, class LF6,
                        class Catch7, class LF7>
inline const 
lambda_functor< 
  lambda_functor_base< 
    action<
      8, 
      try_catch_action<
        catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>, detail::catch_block<Catch4>, detail::catch_block<Catch5>, detail::catch_block<Catch6>, Catch7> 
      > 
    >, 
    tuple<lambda_functor<TryArg>, LF1, LF2, LF3, LF4, LF5, LF6, LF7>
  > 
>
try_catch(
  const lambda_functor<TryArg>& a1, 
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch1> >, LF1>& a2,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch2> >, LF2>& a3,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch3> >, LF3>& a4,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch4> >, LF4>& a5,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch5> >, LF5>& a6,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch6> >, LF6>& a7,
  const tagged_lambda_functor<detail::exception_catch_tag<Catch7>, LF7>& a8) 
{ 
  return 
      lambda_functor_base< 
        action<
          8, 
          try_catch_action<
            catch_action<
              detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>, detail::catch_block<Catch4>, detail::catch_block<Catch5>, detail::catch_block<Catch6>, Catch7
            > 
          > 
        >, 
        tuple<lambda_functor<TryArg>, LF1, LF2, LF3, LF4, LF5, LF6, LF7>
      > 
    ( tuple<lambda_functor<TryArg>, LF1, LF2, LF3, LF4, LF5, LF6, LF7>
        (a1, a2, a3, a4, a5, a6, a7, a8));
}

template <class TryArg, class Catch1, class LF1, 
                        class Catch2, class LF2, 
                        class Catch3, class LF3, 
                        class Catch4, class LF4, 
                        class Catch5, class LF5, 
                        class Catch6, class LF6, 
                        class Catch7, class LF7, 
                        class Catch8, class LF8>
inline const 
lambda_functor< 
  lambda_functor_base< 
    action<
      9, 
      try_catch_action<
        catch_action<
          detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>, detail::catch_block<Catch4>, detail::catch_block<Catch5>, detail::catch_block<Catch6>, detail::catch_block<Catch7>, Catch8
        > 
      > 
    >, 
    tuple<lambda_functor<TryArg>, LF1, LF2, LF3, LF4, LF5, LF6, LF7, LF8>
  > 
>
try_catch(
  const lambda_functor<TryArg>& a1, 
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch1> >, LF1>& a2,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch2> >, LF2>& a3,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch3> >, LF3>& a4,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch4> >, LF4>& a5,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch5> >, LF5>& a6,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch6> >, LF6>& a7,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch7> >, LF7>& a8,
  const tagged_lambda_functor<detail::exception_catch_tag<Catch8>, LF8>& a9) 
{ 
  return 
      lambda_functor_base< 
        action<
          9,
          try_catch_action<
            catch_action<
              detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>, detail::catch_block<Catch4>, detail::catch_block<Catch5>, detail::catch_block<Catch6>, detail::catch_block<Catch7>, Catch8
            > 
          > 
        >, 
        tuple<lambda_functor<TryArg>, LF1, LF2, LF3, LF4, LF5, LF6, LF7, LF8> 
      > 
    ( tuple<lambda_functor<TryArg>, LF1, LF2, LF3, LF4, LF5, LF6, LF7, LF8>
        (a1, a2, a3, a4, a5, a6, a7, a8, a9));
}

template <class TryArg, class Catch1, class LF1, 
                        class Catch2, class LF2, 
                        class Catch3, class LF3, 
                        class Catch4, class LF4, 
                        class Catch5, class LF5, 
                        class Catch6, class LF6, 
                        class Catch7, class LF7, 
                        class Catch8, class LF8, 
                        class Catch9, class LF9>
inline const 
  lambda_functor< 
    lambda_functor_base< 
      action< 
        10, 
        try_catch_action<
          catch_action<
             detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>, detail::catch_block<Catch4>, detail::catch_block<Catch5>, detail::catch_block<Catch6>, detail::catch_block<Catch7>, detail::catch_block<Catch8>, 
             Catch9
          > 
        > 
      >, 
      tuple<
        lambda_functor<TryArg>, LF1, LF2, LF3, LF4, LF5, LF6, LF7, LF8, LF9
      >
    > 
  >
try_catch(
  const lambda_functor<TryArg>& a1, 
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch1> >, LF1>& a2,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch2> >, LF2>& a3,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch3> >, LF3>& a4,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch4> >, LF4>& a5,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch5> >, LF5>& a6,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch6> >, LF6>& a7,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch7> >, LF7>& a8,
  const tagged_lambda_functor<detail::exception_catch_tag<detail::catch_block<Catch8> >, LF8>& a9,
  const tagged_lambda_functor<detail::exception_catch_tag<Catch9>, LF9>& a10) 
{ 
  return 
      lambda_functor_base< 
        action<
          10, 
          try_catch_action< 
            catch_action<
              detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>, detail::catch_block<Catch4>, detail::catch_block<Catch5>, detail::catch_block<Catch6>, detail::catch_block<Catch7>, detail::catch_block<Catch8>, 
              Catch9
            > 
          > 
        >, 
        tuple<
          lambda_functor<TryArg>, LF1, LF2, LF3, LF4, LF5, LF6, LF7, LF8, LF9
        >
      > 
    ( tuple<
        lambda_functor<TryArg>, LF1, LF2, LF3, LF4, LF5, LF6, LF7, LF8, LF9
      >(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10));
}


// ---------------------------------------------------------------------------
// Specializations for lambda_functor_base of try_catch ----------------------

// 1 catch type case

template<class Args, class Catch1>
class lambda_functor_base<
  action<2, try_catch_action<catch_action<detail::catch_block<Catch1> > > >, 
  Args
> 
{
public:
  Args args;
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

// the return type of try_catch is the return type of the try lambda_functor
// (the return types of try and catch parts must match unless try returns void
// or the catch part throws for sure)

  template <class SigArgs> struct sig {
    typedef typename 
      as_lambda_functor<
            typename boost::tuples::element<0, Args>::type 
      >::type lf_type;

    typedef typename lf_type::inherited::template sig<SigArgs>::type type;  
  };

  template<class RET, CALL_TEMPLATE_ARGS>
  RET call(CALL_FORMAL_ARGS) const {
    try 
    {
      return detail::select(::boost::tuples::get<0>(args), CALL_ACTUAL_ARGS);
    }
    catch (Catch1& e)
    {                
      return 
       detail::return_or_throw<RET, typename ::boost::tuples::element<1, Args>::type>
               ::call(::boost::tuples::get<1>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
  }
};



template<class Args>
class lambda_functor_base<action<2, try_catch_action<catch_action<detail::catch_all_block> > >, Args> {
public:
  Args args;
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template <class SigArgs> struct sig {
    typedef typename 
      as_lambda_functor<
            typename boost::tuples::element<0, Args>::type 
      >::type lf_type;

    typedef typename lf_type::inherited::template sig<SigArgs>::type type;  
  };

  template<class RET, CALL_TEMPLATE_ARGS>
  RET call(CALL_FORMAL_ARGS) const {
    try 
    {
      return detail::select(::boost::tuples::get<0>(args), CALL_ACTUAL_ARGS);  
    }
    catch (...)
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<1, Args>::type>
               ::call(::boost::tuples::get<1>(args), CALL_ACTUAL_ARGS);
    }
  }
};


// 2 catch types case
template<class Args, class Catch1, class Catch2>
class lambda_functor_base<action<3, try_catch_action<catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2> > > >, Args> {
public:
  Args args;
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template <class SigArgs> struct sig {
    typedef typename 
      as_lambda_functor<
            typename boost::tuples::element<0, Args>::type 
      >::type lf_type;

    typedef typename lf_type::inherited::template sig<SigArgs>::type type;  
  };

  template<class RET, CALL_TEMPLATE_ARGS>
  RET call(CALL_FORMAL_ARGS) const {
    try 
    {
      return detail::select(::boost::tuples::get<0>(args), CALL_ACTUAL_ARGS);  
    }
    catch (Catch1& e)
    { 
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<1, Args>::type>
               ::call(::boost::tuples::get<1>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch2& e)
    {          
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<2, Args>::type>
               ::call(::boost::tuples::get<2>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
  }
};

template<class Args, class Catch1>
class lambda_functor_base<action<3, try_catch_action<catch_action<detail::catch_block<Catch1>,detail::catch_all_block> > >, Args> {
public:
  Args args;
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template <class SigArgs> struct sig {
    typedef typename 
      as_lambda_functor<
            typename boost::tuples::element<0, Args>::type 
      >::type lf_type;

    typedef typename lf_type::inherited::template sig<SigArgs>::type type;  
  };

  template<class RET, CALL_TEMPLATE_ARGS>
  RET call(CALL_FORMAL_ARGS) const {
    try 
    {
      return detail::select(::boost::tuples::get<0>(args), CALL_ACTUAL_ARGS);  
    }
    catch (Catch1& e)
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<1, Args>::type>
               ::call(::boost::tuples::get<1>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (...)
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<2, Args>::type>
               ::call(::boost::tuples::get<2>(args), CALL_ACTUAL_ARGS);
    }
  }
};

// 3 catch types case
template<class Args, class Catch1, class Catch2, class Catch3>
class lambda_functor_base<action<4, try_catch_action<catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3> > > >, Args> {
public:
  Args args;
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template <class SigArgs> struct sig {
    typedef typename 
      as_lambda_functor<
            typename boost::tuples::element<0, Args>::type 
      >::type lf_type;

    typedef typename lf_type::inherited::template sig<SigArgs>::type type;  
  };

  template<class RET, CALL_TEMPLATE_ARGS>
  RET call(CALL_FORMAL_ARGS) const {
    try 
    {
      return detail::select(::boost::tuples::get<0>(args), CALL_ACTUAL_ARGS);  
    }
    catch (Catch1& e)
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<1, Args>::type>
               ::call(::boost::tuples::get<1>(args), CALL_ACTUAL_ARGS_NO_ENV, e);

    }
    catch (Catch2& e)
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<2, Args>::type>
               ::call(::boost::tuples::get<2>(args), CALL_ACTUAL_ARGS_NO_ENV, e);

    }
    catch (Catch3& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<3, Args>::type>
               ::call(::boost::tuples::get<3>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
  }
};

template<class Args, class Catch1, class Catch2>
class lambda_functor_base<action<4, try_catch_action<catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2>,detail::catch_all_block> > >, Args> {
public:
  Args args;
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template <class SigArgs> struct sig {
    typedef typename 
      as_lambda_functor<
            typename boost::tuples::element<0, Args>::type 
      >::type lf_type;

    typedef typename lf_type::inherited::template sig<SigArgs>::type type;  
  };

  template<class RET, CALL_TEMPLATE_ARGS>
  RET call(CALL_FORMAL_ARGS) const {
    try 
    {
      return detail::select(::boost::tuples::get<0>(args), CALL_ACTUAL_ARGS);  
    }
    catch (Catch1& e)
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<1, Args>::type>
               ::call(::boost::tuples::get<1>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch2& e)
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<2, Args>::type>
               ::call(::boost::tuples::get<2>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (...)
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<3, Args>::type>
               ::call(::boost::tuples::get<3>(args), CALL_ACTUAL_ARGS);
    }
  }
};

// 4 catch types case
template<class Args, class Catch1, class Catch2, class Catch3, class Catch4>
class lambda_functor_base<action<5, try_catch_action<catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>, detail::catch_block<Catch4> > > >, Args> {
public:
  Args args;
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template <class SigArgs> struct sig {
    typedef typename 
      as_lambda_functor<
            typename boost::tuples::element<0, Args>::type 
      >::type lf_type;

    typedef typename lf_type::inherited::template sig<SigArgs>::type type;  
  };

  template<class RET, CALL_TEMPLATE_ARGS>
  RET call(CALL_FORMAL_ARGS) const {
    try 
    {
      return detail::select(::boost::tuples::get<0>(args), CALL_ACTUAL_ARGS);  
    }
    catch (Catch1& e)
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<1, Args>::type>
               ::call(::boost::tuples::get<1>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch2& e) 
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<2, Args>::type>
               ::call(::boost::tuples::get<2>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch3& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<3, Args>::type>
               ::call(::boost::tuples::get<3>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch4& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<4, Args>::type>
               ::call(::boost::tuples::get<4>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
  }
};

template<class Args, class Catch1, class Catch2, class Catch3>
class lambda_functor_base<action<5, try_catch_action<catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>,detail::catch_all_block> > >, Args> {
public:
  Args args;
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template <class SigArgs> struct sig {
    typedef typename 
      as_lambda_functor<
            typename boost::tuples::element<0, Args>::type 
      >::type lf_type;

    typedef typename lf_type::inherited::template sig<SigArgs>::type type;  
  };

  template<class RET, CALL_TEMPLATE_ARGS>
  RET call(CALL_FORMAL_ARGS) const {
    try 
    {
      return detail::select(::boost::tuples::get<0>(args), CALL_ACTUAL_ARGS);  
    }
    catch (Catch1& e)
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<1, Args>::type>
               ::call(::boost::tuples::get<1>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch2& e) 
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<2, Args>::type>
               ::call(::boost::tuples::get<2>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch3& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<3, Args>::type>
               ::call(::boost::tuples::get<3>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (...)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<4, Args>::type>
               ::call(::boost::tuples::get<4>(args), CALL_ACTUAL_ARGS);
    }
  }
};

// 5 catch types case
template<class Args, class Catch1, class Catch2, class Catch3, class Catch4, class Catch5>
class lambda_functor_base<action<6, try_catch_action<catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>, detail::catch_block<Catch4>, detail::catch_block<Catch5> > > >, Args> {
public:
  Args args;
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template <class SigArgs> struct sig {
    typedef typename 
      as_lambda_functor<
            typename boost::tuples::element<0, Args>::type 
      >::type lf_type;

    typedef typename lf_type::inherited::template sig<SigArgs>::type type;  
  };

  template<class RET, CALL_TEMPLATE_ARGS>
  RET call(CALL_FORMAL_ARGS) const {
    try 
    {
      return detail::select(::boost::tuples::get<0>(args), CALL_ACTUAL_ARGS);  
    }
    catch (Catch1& e)
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<1, Args>::type>
               ::call(::boost::tuples::get<1>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch2& e) 
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<2, Args>::type>
               ::call(::boost::tuples::get<2>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch3& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<3, Args>::type>
               ::call(::boost::tuples::get<3>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch4& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<4, Args>::type>
               ::call(::boost::tuples::get<4>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch5& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<4, Args>::type>
               ::call(::boost::tuples::get<5>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
  }
};

template<class Args, class Catch1, class Catch2, class Catch3, class Catch4>
class lambda_functor_base<action<6, try_catch_action<catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>, detail::catch_block<Catch4>,detail::catch_all_block> > >, Args> {
public:
  Args args;
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template <class SigArgs> struct sig {
    typedef typename 
      as_lambda_functor<
            typename boost::tuples::element<0, Args>::type 
      >::type lf_type;

    typedef typename lf_type::inherited::template sig<SigArgs>::type type;  
  };

  template<class RET, CALL_TEMPLATE_ARGS>
  RET call(CALL_FORMAL_ARGS) const {
    try 
    {
      return detail::select(::boost::tuples::get<0>(args), CALL_ACTUAL_ARGS);  
    }
    catch (Catch1& e)
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<1, Args>::type>
               ::call(::boost::tuples::get<1>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch2& e) 
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<2, Args>::type>
               ::call(::boost::tuples::get<2>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch3& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<3, Args>::type>
               ::call(::boost::tuples::get<3>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch4& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<4, Args>::type>
               ::call(::boost::tuples::get<4>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (...)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<5, Args>::type>
               ::call(::boost::tuples::get<5>(args), CALL_ACTUAL_ARGS);
    }
  }
};

// 6 catch types case
template<class Args, class Catch1, class Catch2, class Catch3, class Catch4, class Catch5, class Catch6>
class lambda_functor_base<action<7, try_catch_action<catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>, detail::catch_block<Catch4>, detail::catch_block<Catch5>, detail::catch_block<Catch6> > > >, Args> {
public:
  Args args;
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template <class SigArgs> struct sig {
    typedef typename 
      as_lambda_functor<
            typename boost::tuples::element<0, Args>::type 
      >::type lf_type;

    typedef typename lf_type::inherited::template sig<SigArgs>::type type;  
  };

  template<class RET, CALL_TEMPLATE_ARGS>
  RET call(CALL_FORMAL_ARGS) const {
    try 
    {
      return detail::select(::boost::tuples::get<0>(args), CALL_ACTUAL_ARGS);  
    }
    catch (Catch1& e)
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<1, Args>::type>
               ::call(::boost::tuples::get<1>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch2& e) 
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<2, Args>::type>
               ::call(::boost::tuples::get<2>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch3& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<3, Args>::type>
               ::call(::boost::tuples::get<3>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch4& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<4, Args>::type>
               ::call(::boost::tuples::get<4>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch5& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<5, Args>::type>
               ::call(::boost::tuples::get<5>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch6& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<6, Args>::type>
               ::call(::boost::tuples::get<6>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
  }
};

template<class Args, class Catch1, class Catch2, class Catch3, class Catch4, class Catch5>
class lambda_functor_base<action<7, try_catch_action<catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>, detail::catch_block<Catch4>, detail::catch_block<Catch5>,detail::catch_all_block> > >, Args> {
public:
  Args args;
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template <class SigArgs> struct sig {
    typedef typename 
      as_lambda_functor<
            typename boost::tuples::element<0, Args>::type 
      >::type lf_type;

    typedef typename lf_type::inherited::template sig<SigArgs>::type type;  
  };

  template<class RET, CALL_TEMPLATE_ARGS>
  RET call(CALL_FORMAL_ARGS) const {
    try 
    {
      return detail::select(::boost::tuples::get<0>(args), CALL_ACTUAL_ARGS);  
    }
    catch (Catch1& e)
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<1, Args>::type>
               ::call(::boost::tuples::get<1>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch2& e) 
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<2, Args>::type>
               ::call(::boost::tuples::get<2>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch3& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<3, Args>::type>
               ::call(::boost::tuples::get<3>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch4& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<4, Args>::type>
               ::call(::boost::tuples::get<4>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch5& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<5, Args>::type>
               ::call(::boost::tuples::get<5>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (...)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<6, Args>::type>
               ::call(::boost::tuples::get<6>(args), CALL_ACTUAL_ARGS);
    }
  }
};

// 7 catch types case
template<class Args, class Catch1, class Catch2, class Catch3, class Catch4, class Catch5, class Catch6,
                     class Catch7>
class lambda_functor_base<action<8, try_catch_action<catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>, detail::catch_block<Catch4>, detail::catch_block<Catch5>, detail::catch_block<Catch6>, detail::catch_block<Catch7> > > >, Args> {
public:
  Args args;
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template <class SigArgs> struct sig {
    typedef typename 
      as_lambda_functor<
            typename boost::tuples::element<0, Args>::type 
      >::type lf_type;

    typedef typename lf_type::inherited::template sig<SigArgs>::type type;  
  };

  template<class RET, CALL_TEMPLATE_ARGS>
  RET call(CALL_FORMAL_ARGS) const {
    try 
    {
      return detail::select(::boost::tuples::get<0>(args), CALL_ACTUAL_ARGS);  
    }
    catch (Catch1& e)
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<1, Args>::type>
               ::call(::boost::tuples::get<1>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch2& e) 
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<2, Args>::type>
               ::call(::boost::tuples::get<2>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch3& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<3, Args>::type>
               ::call(::boost::tuples::get<3>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch4& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<4, Args>::type>
               ::call(::boost::tuples::get<4>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch5& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<5, Args>::type>
               ::call(::boost::tuples::get<5>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch6& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<6, Args>::type>
               ::call(::boost::tuples::get<6>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch7& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<7, Args>::type>
               ::call(::boost::tuples::get<7>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
  }
};

template<class Args, class Catch1, class Catch2, class Catch3, class Catch4, class Catch5, class Catch6>
class lambda_functor_base<action<8, try_catch_action<catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>, detail::catch_block<Catch4>, detail::catch_block<Catch5>, detail::catch_block<Catch6>,
                                                               detail::catch_all_block> > >, Args> {
public:
  Args args;
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template <class SigArgs> struct sig {
    typedef typename 
      as_lambda_functor<
            typename boost::tuples::element<0, Args>::type 
      >::type lf_type;

    typedef typename lf_type::inherited::template sig<SigArgs>::type type;  
  };

  template<class RET, CALL_TEMPLATE_ARGS>
  RET call(CALL_FORMAL_ARGS) const {
    try 
    {
      return detail::select(::boost::tuples::get<0>(args), CALL_ACTUAL_ARGS);  
    }
    catch (Catch1& e)
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<1, Args>::type>
               ::call(::boost::tuples::get<1>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch2& e) 
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<2, Args>::type>
               ::call(::boost::tuples::get<2>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch3& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<3, Args>::type>
               ::call(::boost::tuples::get<3>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch4& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<4, Args>::type>
               ::call(::boost::tuples::get<4>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch5& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<5, Args>::type>
               ::call(::boost::tuples::get<5>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch6& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<6, Args>::type>
               ::call(::boost::tuples::get<6>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (...)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<7, Args>::type>
               ::call(::boost::tuples::get<7>(args), CALL_ACTUAL_ARGS);
    }
  }
};

// 8 catch types case
template<class Args, class Catch1, class Catch2, class Catch3, class Catch4, class Catch5, class Catch6,
                     class Catch7, class Catch8>
class lambda_functor_base<action<9, try_catch_action<catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>, detail::catch_block<Catch4>, detail::catch_block<Catch5>, detail::catch_block<Catch6>,
    detail::catch_block<Catch7>, detail::catch_block<Catch8> > > >, Args> {
public:
  Args args;
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template <class SigArgs> struct sig {
    typedef typename 
      as_lambda_functor<
            typename boost::tuples::element<0, Args>::type 
      >::type lf_type;

    typedef typename lf_type::inherited::template sig<SigArgs>::type type;  
  };

  template<class RET, CALL_TEMPLATE_ARGS>
  RET call(CALL_FORMAL_ARGS) const {
    try 
    {
      return detail::select(::boost::tuples::get<0>(args), CALL_ACTUAL_ARGS);  
    }
    catch (Catch1& e)
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<1, Args>::type>
               ::call(::boost::tuples::get<1>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch2& e) 
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<2, Args>::type>
               ::call(::boost::tuples::get<2>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch3& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<3, Args>::type>
               ::call(::boost::tuples::get<3>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch4& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<4, Args>::type>
               ::call(::boost::tuples::get<4>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch5& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<5, Args>::type>
               ::call(::boost::tuples::get<5>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch6& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<6, Args>::type>
               ::call(::boost::tuples::get<6>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch7& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<7, Args>::type>
               ::call(::boost::tuples::get<7>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch8& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<8, Args>::type>
               ::call(::boost::tuples::get<8>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
  }
};

template<class Args, class Catch1, class Catch2, class Catch3, class Catch4, class Catch5, class Catch6,
                     class Catch7>
class lambda_functor_base<action<9, try_catch_action<catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>, detail::catch_block<Catch4>, detail::catch_block<Catch5>, detail::catch_block<Catch6>,
    detail::catch_block<Catch7>,detail::catch_all_block> > >, Args> {
public:
  Args args;
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template <class SigArgs> struct sig {
    typedef typename 
      as_lambda_functor<
            typename boost::tuples::element<0, Args>::type 
      >::type lf_type;

    typedef typename lf_type::inherited::template sig<SigArgs>::type type;  
  };

  template<class RET, CALL_TEMPLATE_ARGS>
  RET call(CALL_FORMAL_ARGS) const {
    try 
    {
      return detail::select(::boost::tuples::get<0>(args), CALL_ACTUAL_ARGS);  
    }
    catch (Catch1& e)
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<1, Args>::type>
               ::call(::boost::tuples::get<1>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch2& e) 
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<2, Args>::type>
               ::call(::boost::tuples::get<2>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch3& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<3, Args>::type>
               ::call(::boost::tuples::get<3>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch4& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<4, Args>::type>
               ::call(::boost::tuples::get<4>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch5& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<5, Args>::type>
               ::call(::boost::tuples::get<5>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch6& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<6, Args>::type>
               ::call(::boost::tuples::get<6>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch7& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<7, Args>::type>
               ::call(::boost::tuples::get<7>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (...)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<8, Args>::type>
               ::call(::boost::tuples::get<8>(args), CALL_ACTUAL_ARGS);
    }
  }
};

// 9 catch types case
template<class Args, class Catch1, class Catch2, class Catch3, class Catch4, class Catch5, class Catch6,
                     class Catch7, class Catch8, class Catch9>
class lambda_functor_base<action<10, try_catch_action<catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>, detail::catch_block<Catch4>, detail::catch_block<Catch5>, detail::catch_block<Catch6>,
    detail::catch_block<Catch7>, detail::catch_block<Catch8>, detail::catch_block<Catch9> > > >, Args> {
public:
  Args args;
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template <class SigArgs> struct sig {
    typedef typename 
      as_lambda_functor<
            typename boost::tuples::element<0, Args>::type 
      >::type lf_type;

    typedef typename lf_type::inherited::template sig<SigArgs>::type type;  
  };

  template<class RET, CALL_TEMPLATE_ARGS>
  RET call(CALL_FORMAL_ARGS) const {
    try 
    {
      return detail::select(::boost::tuples::get<0>(args), CALL_ACTUAL_ARGS);  
    }
    catch (Catch1& e)
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<1, Args>::type>
               ::call(::boost::tuples::get<1>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch2& e) 
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<2, Args>::type>
               ::call(::boost::tuples::get<2>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch3& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<3, Args>::type>
               ::call(::boost::tuples::get<3>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch4& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<4, Args>::type>
               ::call(::boost::tuples::get<4>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch5& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<5, Args>::type>
               ::call(::boost::tuples::get<5>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch6& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<6, Args>::type>
               ::call(::boost::tuples::get<6>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch7& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<7, Args>::type>
               ::call(::boost::tuples::get<7>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch8& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<8, Args>::type>
               ::call(::boost::tuples::get<8>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch9& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<9, Args>::type>
               ::call(::boost::tuples::get<9>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
  }
};

template<class Args, class Catch1, class Catch2, class Catch3, class Catch4, class Catch5, class Catch6,
                     class Catch7, class Catch8>
class lambda_functor_base<action<10, try_catch_action<catch_action<detail::catch_block<Catch1>, detail::catch_block<Catch2>, detail::catch_block<Catch3>, detail::catch_block<Catch4>, detail::catch_block<Catch5>, detail::catch_block<Catch6>,
    detail::catch_block<Catch7>, detail::catch_block<Catch8>,detail::catch_all_block> > >, Args> {
public:
  Args args;
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template <class SigArgs> struct sig {
    typedef typename 
      as_lambda_functor<
            typename boost::tuples::element<0, Args>::type 
      >::type lf_type;

    typedef typename lf_type::inherited::template sig<SigArgs>::type type;  
  };

  template<class RET, CALL_TEMPLATE_ARGS>
  RET call(CALL_FORMAL_ARGS) const {
    try 
    {
      return detail::select(::boost::tuples::get<0>(args), CALL_ACTUAL_ARGS);  
    }
    catch (Catch1& e)
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<1, Args>::type>
               ::call(::boost::tuples::get<1>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch2& e) 
    {                
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<2, Args>::type>
               ::call(::boost::tuples::get<2>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch3& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<3, Args>::type>
               ::call(::boost::tuples::get<3>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch4& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<4, Args>::type>
               ::call(::boost::tuples::get<4>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch5& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<5, Args>::type>
               ::call(::boost::tuples::get<5>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch6& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<6, Args>::type>
               ::call(::boost::tuples::get<6>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch7& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<7, Args>::type>
               ::call(::boost::tuples::get<7>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (Catch8& e)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<8, Args>::type>
               ::call(::boost::tuples::get<8>(args), CALL_ACTUAL_ARGS_NO_ENV, e);
    }
    catch (...)
    {
      return 
        detail::return_or_throw<RET, typename ::boost::tuples::element<9, Args>::type>
               ::call(::boost::tuples::get<9>(args), CALL_ACTUAL_ARGS);
    }
  }
};


} // namespace lambda 
} // namespace boost


#endif







/* exceptions.hpp
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
*/