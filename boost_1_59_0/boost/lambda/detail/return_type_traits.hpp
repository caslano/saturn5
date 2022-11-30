//  return_type_traits.hpp -- Boost Lambda Library ---------------------------

// Copyright (C) 1999, 2000 Jaakko Jarvi (jaakko.jarvi@cs.utu.fi)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org


#ifndef BOOST_LAMBDA_RETURN_TYPE_TRAITS_HPP
#define BOOST_LAMBDA_RETURN_TYPE_TRAITS_HPP

#include "boost/mpl/has_xxx.hpp"

#include <cstddef> // needed for the ptrdiff_t

namespace boost { 
namespace lambda {

// Much of the type deduction code for standard arithmetic types 
// from Gary Powell

  // different arities:
template <class Act, class A1> struct return_type_1; // 1-ary actions
template <class Act, class A1, class A2> struct return_type_2; // 2-ary
template <class Act, class Args> struct return_type_N; // >3- ary

template <class Act, class A1> struct return_type_1_prot;
template <class Act, class A1, class A2> struct return_type_2_prot; // 2-ary
template <class Act, class A1> struct return_type_N_prot; // >3-ary


namespace detail {

template<class> class return_type_deduction_failure {};

  // In some cases return type deduction should fail (an invalid lambda 
  // expression). Sometimes the lambda expression can be ok, the return type
  // just is not deducible (user defined operators). Then return type deduction
  // should never be entered at all, and the use of ret<> does this.
  // However, for nullary lambda functors, return type deduction is always
  // entered, and there seems to be no way around this.

  // (the return type is part of the prototype of the non-template
  // operator()(). The prototype is instantiated, even though the body 
  // is not.) 
 
  // So, in the case the return type deduction should fail, it should not
  // fail directly, but rather result in a valid but wrong return type,
  // causing a compile time error only if the function is really called.



} // end detail



// return_type_X_prot classes --------------------------------------------
// These classes are the first layer that gets instantiated from the 
// lambda_functor_base sig templates. It will check whether 
// the action is protectable and one of arguments is "protected" or its
// evaluation will otherwise result in another lambda functor.
// If this is a case, the result type will be another lambda functor.

// The arguments are always non-reference types, except for comma action
// where the right argument can be a reference too. This is because it 
// matters (in the builtin case) whether the argument is an lvalue or 
// rvalue: int i; i, 1 -> rvalue; 1, i -> lvalue

template <class Act, class A> struct return_type_1_prot {
public:
  typedef typename 
    detail::IF<
      is_protectable<Act>::value && is_lambda_functor<A>::value,
      lambda_functor<
        lambda_functor_base< 
          Act, 
          tuple<typename detail::remove_reference_and_cv<A>::type>
        >
      >,
      typename return_type_1<Act, A>::type
    >::RET type;  
};

  // take care of the unavoidable instantiation for nullary case
template<class Act> struct return_type_1_prot<Act, null_type> {
  typedef null_type type;
};
 
// Unary actions (result from unary operators)
// do not have a default return type.
template<class Act, class A> struct return_type_1 { 
   typedef typename 
     detail::return_type_deduction_failure<return_type_1> type;
};


namespace detail {

  template <class T>
  class protect_conversion {
      typedef typename boost::remove_reference<T>::type non_ref_T;
    public:

  // add const to rvalues, so that all rvalues are stored as const in 
  // the args tuple
    typedef typename detail::IF_type<
      boost::is_reference<T>::value && !boost::is_const<non_ref_T>::value,
      detail::identity_mapping<T>,
      const_copy_argument<non_ref_T> // handles funtion and array 
    >::type type;                      // types correctly
  };

} // end detail

template <class Act, class A, class B> struct return_type_2_prot {

// experimental feature
  // We may have a lambda functor as a result type of a subexpression 
  // (if protect) has  been used.
  // Thus, if one of the parameter types is a lambda functor, the result
  // is a lambda functor as well. 
  // We need to make a conservative choise here.
  // The resulting lambda functor stores all const reference arguments as
  // const copies. References to non-const are stored as such.
  // So if the source of the argument is a const open argument, a bound
  // argument stored as a const reference, or a function returning a 
  // const reference, that information is lost. There is no way of 
  // telling apart 'real const references' from just 'LL internal
  // const references' (or it would be really hard)

  // The return type is a subclass of lambda_functor, which has a converting 
  // copy constructor. It can copy any lambda functor, that has the same 
  // action type and code, and a copy compatible argument tuple.


  typedef typename boost::remove_reference<A>::type non_ref_A;
  typedef typename boost::remove_reference<B>::type non_ref_B;

typedef typename 
  detail::IF<
    is_protectable<Act>::value &&
      (is_lambda_functor<A>::value || is_lambda_functor<B>::value),
    lambda_functor<
      lambda_functor_base< 
        Act, 
        tuple<typename detail::protect_conversion<A>::type, 
              typename detail::protect_conversion<B>::type>
      >
    >,
    typename return_type_2<Act, non_ref_A, non_ref_B>::type
  >::RET type;
};

  // take care of the unavoidable instantiation for nullary case
template<class Act> struct return_type_2_prot<Act, null_type, null_type> {
  typedef null_type type;
};
  // take care of the unavoidable instantiation for nullary case
template<class Act, class Other> struct return_type_2_prot<Act, Other, null_type> {
  typedef null_type type;
};
  // take care of the unavoidable instantiation for nullary case
template<class Act, class Other> struct return_type_2_prot<Act, null_type, Other> {
  typedef null_type type;
};

  // comma is a special case, as the user defined operator can return
  // an lvalue (reference) too, hence it must be handled at this level.
template<class A, class B> 
struct return_type_2_comma
{
  typedef typename boost::remove_reference<A>::type non_ref_A;
  typedef typename boost::remove_reference<B>::type non_ref_B;

typedef typename 
  detail::IF<
    is_protectable<other_action<comma_action> >::value && // it is protectable
    (is_lambda_functor<A>::value || is_lambda_functor<B>::value),
    lambda_functor<
      lambda_functor_base< 
        other_action<comma_action>, 
        tuple<typename detail::protect_conversion<A>::type, 
              typename detail::protect_conversion<B>::type>
      >
    >,
    typename 
      return_type_2<other_action<comma_action>, non_ref_A, non_ref_B>::type
  >::RET type1;

   // if no user defined return_type_2 (or plain_return_type_2) specialization
  // matches, then return the righthand argument
  typedef typename 
    detail::IF<
      boost::is_same<type1, detail::unspecified>::value, 
      B,
      type1
    >::RET type;

};


  // currently there are no protectable actions with > 2 args

template<class Act, class Args> struct return_type_N_prot {
  typedef typename return_type_N<Act, Args>::type type;
};

  // take care of the unavoidable instantiation for nullary case
template<class Act> struct return_type_N_prot<Act, null_type> {
  typedef null_type type;
};

// handle different kind of actions ------------------------

  // use the return type given in the bind invocation as bind<Ret>(...)
template<int I, class Args, class Ret> 
struct return_type_N<function_action<I, Ret>, Args> { 
  typedef Ret type;
};

// ::result_type support

namespace detail
{

BOOST_MPL_HAS_XXX_TRAIT_DEF(result_type)

template<class F> struct get_result_type
{
  typedef typename F::result_type type;
};

template<class F, class A> struct get_sig
{
  typedef typename function_adaptor<F>::template sig<A>::type type;
};

} // namespace detail

  // Ret is detail::unspecified, so try to deduce return type
template<int I, class Args> 
struct return_type_N<function_action<I, detail::unspecified>, Args > { 

  // in the case of function action, the first element in Args is 
  // some type of function
  typedef typename Args::head_type Func;
  typedef typename detail::remove_reference_and_cv<Func>::type plain_Func;

public: 
  // pass the function to function_adaptor, and get the return type from 
  // that
  typedef typename detail::IF<
    detail::has_result_type<plain_Func>::value,
    detail::get_result_type<plain_Func>,
    detail::get_sig<plain_Func, Args>
  >::RET::type type;
};


} // namespace lambda
} // namespace boost

#endif




/* return_type_traits.hpp
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
*/