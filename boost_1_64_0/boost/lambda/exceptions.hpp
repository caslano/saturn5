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
DvWZc4GJwNHAIcA84CjqNY8GDgCeZT0zn+1qfQXemU88aCvz+YhyOMj+8w9gIvATYEfgIWAO8FPW8+fAMdQbzgN+yXHnK9b7UeAU6h9PA37H+5G+B84AmohXDnQA51Mf+SKmVwMMod5wKPBaYBhwDf05LnDdABlqxoV1HId+DgwHbuQ4cBewC/BuoBXnHo4Hm4ADgPey/f4KOB54P3AS4xcCf836RsacH2MezvzbgY4w/60I5wQ+zfyfBUYAnwMmA//A9vU8+/0O5v8CcCRwJ+X5IjAf+BL5eJly3QU8D/hn8rUbOBv4GrAC+DpwJfAN9vM3gdcD/wK8CfhX4G3AD4HrgW8DHwS+C3wI+B7wCeD7wKeB+4DPAj8A7mQ8jhucl+EbpRk3Wpj1cohh+41lu42nvnkb6pknAK24ScBMYDLwTGA7tuf21NfvBCym/3zqk1dTn3wn8MDCMKUjnEw94boT6ArH5jTQF8YHNcxwQVc4sgD3hwM3+ugPb/XRIb7F5/7x6aAEpJENmg5aAloP2graD3Itgo4xKA9UAVoL2gLaBToIci1uus6xC1R5+s//sStW7K4VFYAfrgMQnWSoPcjdJm0dQPymG3nWHQAdGuxZV5WW1bOBIAGdNUkaXDvsjZX9DDQb/ZrEHna+TLZnVtvXQO+If3cjEeuyEDyfj4gXgApAMUkYzwPY69fshas5O/jDO/DHtdsIyifXyQRADtBw0FjIJyXFv3wKZ5ZXaWSk1j9dJe4gncyYrpID/qpaYF9vZYp/T60MVVy1FsY5g23t3F/8O3jv+XDdPlD8kr3X9JR9N/EbqNbEjzXhXEona6tccSyXXdalLn1brNPLekFt8WxKPLD2WJcSeHtkWL/tcXWK//bY+jS0x9GUUQXPhh/jt+8RtsddJ5SRtEptm4wGviPx26i19KiOsi7W92t9G1VxUyRuF61c7XFTNW30a/FP5ZrdNL6Q5wHIN1Xbbr8S/84Ij2dbeIe8U3lAEGWl9n2fDyVcjdr3uUJ4dh23dRb/dTY+3VXu4gpV/wcYX55VfJ7hSh8hsR24AthLCKSveM5rl4fp+8q2jr7tQCo/oP6xrWPg/YNh/faPlzr67x+xp6F/eM6ZdvIg4UuemXzB/hGVqpELO4W/cTpR4nyslRXS0/cBlj9O/A/rZKfijoZsoqSt/DAK9CwlkPZ1BNjNgT0M2c/5ds8z4esuX7pmzF++LC6/oMterCXk/egJJYn7ph9Jb1advPeKfkefavo+1TOyT7V130eVV79y3cYDvR+Pv6FmGCafD8g+zyuXvrrj+y+uO7L42g5tHll1Qai/faqm32e7VfadhqWUfXlZwew058LZEUs+KnvV/74W5uN4f3jEOckLuq1e9WTCkNXN9n73MWw7hc/Ep5es+rbT9N9fvWjsQ1f97teYDN8sfN57x10jl7mc340oGXBf5fsDisGPvD+4KuW2ns9Vfrv0s42PX7mxwwOydsb76l3zr/ri8Bk7Xr3hzOT0fdmQ53Kn9f4X0553tbjqnw+mPvp6arfbx+b422dr+v7YqdqXk/t7PfM3jkdF9vt7uR9hcv8hmvsPccA07g+lc/+lJ9djvYC09+WcBg2Z6drsfWVfxgGczvXzeUzvfO4fXAAcDpwBJJ/8ruv57EM+s8hnP/I5gOlmk8+B5HOQWo/xu8bvcpHPegzPdXLWAGwHnMX1/Wyug+cAs4HlvN94LnAocB5wGMOPA1YCC4BV3F+s5j5UDfAR4EJVTo7PfsrZluVMZjnbsZwdWM4UlrMjy5nKdDd5xi6Or0U++2vDmG4u96uGcx91BDALeCb3MUZyfT2Kv2E2muXI4z7aWdyXGgtcBxw=
*/