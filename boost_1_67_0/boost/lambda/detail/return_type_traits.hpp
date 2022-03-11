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