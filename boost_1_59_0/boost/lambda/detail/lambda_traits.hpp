// - lambda_traits.hpp --- Boost Lambda Library ----------------------------
//
// Copyright (C) 1999, 2000 Jaakko Jarvi (jaakko.jarvi@cs.utu.fi)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// -------------------------------------------------------------------------

#ifndef BOOST_LAMBDA_LAMBDA_TRAITS_HPP
#define BOOST_LAMBDA_LAMBDA_TRAITS_HPP

#include "boost/type_traits/transform_traits.hpp"
#include "boost/type_traits/cv_traits.hpp"
#include "boost/type_traits/function_traits.hpp"
#include "boost/type_traits/object_traits.hpp"
#include "boost/tuple/tuple.hpp"

namespace boost {
namespace lambda {

// -- if construct ------------------------------------------------
// Proposed by Krzysztof Czarnecki and Ulrich Eisenecker

namespace detail {

template <bool If, class Then, class Else> struct IF { typedef Then RET; };

template <class Then, class Else> struct IF<false, Then, Else> {
  typedef Else RET;
};


// An if construct that doesn't instantiate the non-matching template:

// Called as: 
//  IF_type<condition, A, B>::type 
// The matching template must define the typeded 'type'
// I.e. A::type if condition is true, B::type if condition is false
// Idea from Vesa Karvonen (from C&E as well I guess)
template<class T>
struct IF_type_
{
  typedef typename T::type type;
};


template<bool C, class T, class E>
struct IF_type
{
  typedef typename
    IF_type_<typename IF<C, T, E>::RET >::type type;
};

// helper that can be used to give typedef T to some type
template <class T> struct identity_mapping { typedef T type; };

// An if construct for finding an integral constant 'value'
// Does not instantiate the non-matching branch
// Called as IF_value<condition, A, B>::value
// If condition is true A::value must be defined, otherwise B::value

template<class T>
struct IF_value_
{
  BOOST_STATIC_CONSTANT(int, value = T::value);
};


template<bool C, class T, class E>
struct IF_value
{
  BOOST_STATIC_CONSTANT(int, value = (IF_value_<typename IF<C, T, E>::RET>::value));
};


// --------------------------------------------------------------

// removes reference from other than function types:
template<class T> class remove_reference_if_valid
{

  typedef typename boost::remove_reference<T>::type plainT;
public:
  typedef typename IF<
    boost::is_function<plainT>::value,
    T,
    plainT
  >::RET type;

};


template<class T> struct remove_reference_and_cv {
   typedef typename boost::remove_cv<
     typename boost::remove_reference<T>::type
   >::type type;
};


   
// returns a reference to the element of tuple T
template<int N, class T> struct tuple_element_as_reference {   
  typedef typename
     boost::tuples::access_traits<
       typename boost::tuples::element<N, T>::type
     >::non_const_type type;
};

// returns the cv and reverence stripped type of a tuple element
template<int N, class T> struct tuple_element_stripped {   
  typedef typename
     remove_reference_and_cv<
       typename boost::tuples::element<N, T>::type
     >::type type;
};

// is_lambda_functor -------------------------------------------------   

template <class T> struct is_lambda_functor_ {
  BOOST_STATIC_CONSTANT(bool, value = false);
};
   
template <class Arg> struct is_lambda_functor_<lambda_functor<Arg> > {
  BOOST_STATIC_CONSTANT(bool, value = true);
};
   
} // end detail

   
template <class T> struct is_lambda_functor {
  BOOST_STATIC_CONSTANT(bool, 
     value = 
       detail::is_lambda_functor_<
         typename detail::remove_reference_and_cv<T>::type
       >::value);
};
   

namespace detail {

// -- parameter_traits_ ---------------------------------------------

// An internal parameter type traits class that respects
// the reference_wrapper class.

// The conversions performed are:
// references -> compile_time_error
// T1 -> T2, 
// reference_wrapper<T> -> T&
// const array -> ref to const array
// array -> ref to array
// function -> ref to function

// ------------------------------------------------------------------------

template<class T1, class T2> 
struct parameter_traits_ {
  typedef T2 type;
};

// Do not instantiate with reference types
template<class T, class Any> struct parameter_traits_<T&, Any> {
  typedef typename 
    generate_error<T&>::
      parameter_traits_class_instantiated_with_reference_type type;
};

// Arrays can't be stored as plain types; convert them to references
template<class T, int n, class Any> struct parameter_traits_<T[n], Any> {
  typedef T (&type)[n];
};
   
template<class T, int n, class Any> 
struct parameter_traits_<const T[n], Any> {
  typedef const T (&type)[n];
};

template<class T, int n, class Any> 
struct parameter_traits_<volatile T[n], Any> {
  typedef volatile  T (&type)[n];
};
template<class T, int n, class Any> 
struct parameter_traits_<const volatile T[n], Any> {
  typedef const volatile T (&type)[n];
};


template<class T, class Any> 
struct parameter_traits_<boost::reference_wrapper<T>, Any >{
  typedef T& type;
};

template<class T, class Any> 
struct parameter_traits_<const boost::reference_wrapper<T>, Any >{
  typedef T& type;
};

template<class T, class Any> 
struct parameter_traits_<volatile boost::reference_wrapper<T>, Any >{
  typedef T& type;
};

template<class T, class Any> 
struct parameter_traits_<const volatile boost::reference_wrapper<T>, Any >{
  typedef T& type;
};

template<class Any>
struct parameter_traits_<void, Any> {
  typedef void type;
};

template<class Arg, class Any>
struct parameter_traits_<lambda_functor<Arg>, Any > {
  typedef lambda_functor<Arg> type;
};

template<class Arg, class Any>
struct parameter_traits_<const lambda_functor<Arg>, Any > {
  typedef lambda_functor<Arg> type;
};

// Are the volatile versions needed?
template<class Arg, class Any>
struct parameter_traits_<volatile lambda_functor<Arg>, Any > {
  typedef lambda_functor<Arg> type;
};

template<class Arg, class Any>
struct parameter_traits_<const volatile lambda_functor<Arg>, Any > {
  typedef lambda_functor<Arg> type;
};

} // end namespace detail


// ------------------------------------------------------------------------
// traits classes for lambda expressions (bind functions, operators ...)   

// must be instantiated with non-reference types

// The default is const plain type -------------------------
// const T -> const T, 
// T -> const T, 
// references -> compile_time_error
// reference_wrapper<T> -> T&
// array -> const ref array
template<class T>
struct const_copy_argument {
  typedef typename 
    detail::parameter_traits_<
      T,
      typename detail::IF<boost::is_function<T>::value, T&, const T>::RET
    >::type type;
};

// T may be a function type. Without the IF test, const would be added 
// to a function type, which is illegal.

// all arrays are converted to const.
// This traits template is used for 'const T&' parameter passing 
// and thus the knowledge of the potential 
// non-constness of an actual argument is lost.   
template<class T, int n>  struct const_copy_argument <T[n]> {
  typedef const T (&type)[n];
};
template<class T, int n>  struct const_copy_argument <volatile T[n]> {
     typedef const volatile T (&type)[n];
};
   
template<class T>
struct const_copy_argument<T&> {};
// do not instantiate with references
  //  typedef typename detail::generate_error<T&>::references_not_allowed type;


template<>
struct const_copy_argument<void> {
  typedef void type;
};

template<>
struct const_copy_argument<void const> {
  typedef void type;
};


// Does the same as const_copy_argument, but passes references through as such
template<class T>
struct bound_argument_conversion {
  typedef typename const_copy_argument<T>::type type; 
};

template<class T>
struct bound_argument_conversion<T&> {
  typedef T& type; 
};
   
// The default is non-const reference -------------------------
// const T -> const T&, 
// T -> T&, 
// references -> compile_time_error
// reference_wrapper<T> -> T&
template<class T>
struct reference_argument {
  typedef typename detail::parameter_traits_<T, T&>::type type; 
};

template<class T>
struct reference_argument<T&> {
  typedef typename detail::generate_error<T&>::references_not_allowed type; 
};

template<class Arg>
struct reference_argument<lambda_functor<Arg> > {
  typedef lambda_functor<Arg> type;
};

template<class Arg>
struct reference_argument<const lambda_functor<Arg> > {
  typedef lambda_functor<Arg> type;
};

// Are the volatile versions needed?
template<class Arg>
struct reference_argument<volatile lambda_functor<Arg> > {
  typedef lambda_functor<Arg> type;
};

template<class Arg>
struct reference_argument<const volatile lambda_functor<Arg> > {
  typedef lambda_functor<Arg> type;
};

template<>
struct reference_argument<void> {
  typedef void type;
};

namespace detail {
   
// Array to pointer conversion
template <class T>
struct array_to_pointer { 
  typedef T type;
};

template <class T, int N>
struct array_to_pointer <const T[N]> { 
  typedef const T* type;
};
template <class T, int N>
struct array_to_pointer <T[N]> { 
  typedef T* type;
};

template <class T, int N>
struct array_to_pointer <const T (&) [N]> { 
  typedef const T* type;
};
template <class T, int N>
struct array_to_pointer <T (&) [N]> { 
  typedef T* type;
};


// ---------------------------------------------------------------------------
// The call_traits for bind
// Respects the reference_wrapper class.

// These templates are used outside of bind functions as well.
// the bind_tuple_mapper provides a shorter notation for default
// bound argument storing semantics, if all arguments are treated
// uniformly.

// from template<class T> foo(const T& t) : bind_traits<const T>::type
// from template<class T> foo(T& t) : bind_traits<T>::type

// Conversions:
// T -> const T,
// cv T -> cv T, 
// T& -> T& 
// reference_wrapper<T> -> T&
// const reference_wrapper<T> -> T&
// array -> const ref array

// make bound arguments const, this is a deliberate design choice, the
// purpose is to prevent side effects to bound arguments that are stored
// as copies
template<class T>
struct bind_traits {
  typedef const T type; 
};

template<class T>
struct bind_traits<T&> {
  typedef T& type; 
};

// null_types are an exception, we always want to store them as non const
// so that other templates can assume that null_type is always without const
template<>
struct bind_traits<null_type> {
  typedef null_type type;
};

// the bind_tuple_mapper, bind_type_generators may 
// introduce const to null_type
template<>
struct bind_traits<const null_type> {
  typedef null_type type;
};

// Arrays can't be stored as plain types; convert them to references.
// All arrays are converted to const. This is because bind takes its
// parameters as const T& and thus the knowledge of the potential 
// non-constness of actual argument is lost.
template<class T, int n>  struct bind_traits <T[n]> {
  typedef const T (&type)[n];
};

template<class T, int n> 
struct bind_traits<const T[n]> {
  typedef const T (&type)[n];
};

template<class T, int n>  struct bind_traits<volatile T[n]> {
  typedef const volatile T (&type)[n];
};

template<class T, int n> 
struct bind_traits<const volatile T[n]> {
  typedef const volatile T (&type)[n];
};

template<class R>
struct bind_traits<R()> {
    typedef R(&type)();
};

template<class R, class Arg1>
struct bind_traits<R(Arg1)> {
    typedef R(&type)(Arg1);
};

template<class R, class Arg1, class Arg2>
struct bind_traits<R(Arg1, Arg2)> {
    typedef R(&type)(Arg1, Arg2);
};

template<class R, class Arg1, class Arg2, class Arg3>
struct bind_traits<R(Arg1, Arg2, Arg3)> {
    typedef R(&type)(Arg1, Arg2, Arg3);
};

template<class R, class Arg1, class Arg2, class Arg3, class Arg4>
struct bind_traits<R(Arg1, Arg2, Arg3, Arg4)> {
    typedef R(&type)(Arg1, Arg2, Arg3, Arg4);
};

template<class R, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
struct bind_traits<R(Arg1, Arg2, Arg3, Arg4, Arg5)> {
    typedef R(&type)(Arg1, Arg2, Arg3, Arg4, Arg5);
};

template<class R, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
struct bind_traits<R(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)> {
    typedef R(&type)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6);
};

template<class R, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
struct bind_traits<R(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)> {
    typedef R(&type)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7);
};

template<class R, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7, class Arg8>
struct bind_traits<R(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)> {
    typedef R(&type)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8);
};

template<class R, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7, class Arg8, class Arg9>
struct bind_traits<R(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9)> {
    typedef R(&type)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9);
};

template<class T> 
struct bind_traits<reference_wrapper<T> >{
  typedef T& type;
};

template<class T> 
struct bind_traits<const reference_wrapper<T> >{
  typedef T& type;
};

template<>
struct bind_traits<void> {
  typedef void type;
};



template <
  class T0 = null_type, class T1 = null_type, class T2 = null_type, 
  class T3 = null_type, class T4 = null_type, class T5 = null_type, 
  class T6 = null_type, class T7 = null_type, class T8 = null_type, 
  class T9 = null_type
>
struct bind_tuple_mapper {
  typedef
    tuple<typename bind_traits<T0>::type, 
          typename bind_traits<T1>::type, 
          typename bind_traits<T2>::type, 
          typename bind_traits<T3>::type, 
          typename bind_traits<T4>::type, 
          typename bind_traits<T5>::type, 
          typename bind_traits<T6>::type, 
          typename bind_traits<T7>::type,
          typename bind_traits<T8>::type,
          typename bind_traits<T9>::type> type;
};

// bind_traits, except map const T& -> const T
  // this is needed e.g. in currying. Const reference arguments can
  // refer to temporaries, so it is not safe to store them as references.
  template <class T> struct remove_const_reference {
    typedef typename bind_traits<T>::type type;
  };

  template <class T> struct remove_const_reference<const T&> {
    typedef const T type;
  };


// maps the bind argument types to the resulting lambda functor type
template <
  class T0 = null_type, class T1 = null_type, class T2 = null_type, 
  class T3 = null_type, class T4 = null_type, class T5 = null_type, 
  class T6 = null_type, class T7 = null_type, class T8 = null_type, 
  class T9 = null_type
>
class bind_type_generator {

  typedef typename
  detail::bind_tuple_mapper<
    T0, T1, T2, T3, T4, T5, T6, T7, T8, T9
  >::type args_t;

  BOOST_STATIC_CONSTANT(int, nof_elems = boost::tuples::length<args_t>::value);

  typedef 
    action<
      nof_elems, 
      function_action<nof_elems>
    > action_type;

public:
  typedef
    lambda_functor<
      lambda_functor_base<
        action_type, 
        args_t
      >
    > type; 
    
};


   
} // detail
   
template <class T> inline const T&  make_const(const T& t) { return t; }


} // end of namespace lambda
} // end of namespace boost


   
#endif // BOOST_LAMBDA_TRAITS_HPP

/* lambda_traits.hpp
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
*/