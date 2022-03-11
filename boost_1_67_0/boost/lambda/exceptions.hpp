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