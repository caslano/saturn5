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