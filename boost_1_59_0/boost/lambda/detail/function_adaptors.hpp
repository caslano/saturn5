// Boost Lambda Library -  function_adaptors.hpp ----------------------------
 
// Copyright (C) 1999, 2000 Jaakko Jarvi (jaakko.jarvi@cs.utu.fi)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org


#ifndef BOOST_LAMBDA_FUNCTION_ADAPTORS_HPP
#define BOOST_LAMBDA_FUNCTION_ADAPTORS_HPP

#include "boost/mpl/has_xxx.hpp"
#include "boost/tuple/tuple.hpp"
#include "boost/type_traits/same_traits.hpp"
#include "boost/type_traits/remove_reference.hpp"
#include "boost/type_traits/remove_cv.hpp"
#include "boost/type_traits/add_const.hpp"
#include "boost/type_traits/add_volatile.hpp"
#include "boost/utility/result_of.hpp"

namespace boost { 
namespace lambda {

namespace detail {

BOOST_MPL_HAS_XXX_TEMPLATE_DEF(sig)

template<class Tuple>
struct remove_references_from_elements {
  typedef typename boost::tuples::cons<
    typename boost::remove_reference<typename Tuple::head_type>::type,
    typename remove_references_from_elements<typename Tuple::tail_type>::type
  > type;
};

template<>
struct remove_references_from_elements<boost::tuples::null_type> {
  typedef boost::tuples::null_type type;
};

}

template <class Func> struct function_adaptor {

  typedef typename detail::remove_reference_and_cv<Func>::type plainF;

#if !defined(BOOST_NO_RESULT_OF)
  // Support functors that use the boost::result_of return type convention.
  template<class Tuple, int Length, bool HasSig>
  struct result_converter;
  template<class Tuple, int Length>
  struct result_converter<Tuple, Length, true>
    : plainF::template sig<
        typename detail::remove_references_from_elements<Tuple>::type
      >
  {};
  template<class Tuple>
  struct result_converter<Tuple, 0, false>
    : result_of<plainF()>
  {};
  template<class Tuple>
  struct result_converter<Tuple, 1, false>
    : result_of<plainF(
        typename tuples::element<1, Tuple>::type)
      >
  {};
  template<class Tuple>
  struct result_converter<Tuple, 2, false>
    : result_of<plainF(
        typename tuples::element<1, Tuple>::type,
        typename tuples::element<2, Tuple>::type)
      >
  {};
  template<class Tuple>
  struct result_converter<Tuple, 3, false>
    : result_of<plainF(
        typename tuples::element<1, Tuple>::type,
        typename tuples::element<2, Tuple>::type,
        typename tuples::element<3, Tuple>::type)
      >
  {};
  template<class Tuple>
  struct result_converter<Tuple, 4, false>
    : result_of<plainF(
        typename tuples::element<1, Tuple>::type,
        typename tuples::element<2, Tuple>::type,
        typename tuples::element<3, Tuple>::type,
        typename tuples::element<4, Tuple>::type)
      >
  {};
  template<class Tuple>
  struct result_converter<Tuple, 5, false>
    : result_of<plainF(
        typename tuples::element<1, Tuple>::type,
        typename tuples::element<2, Tuple>::type,
        typename tuples::element<3, Tuple>::type,
        typename tuples::element<4, Tuple>::type,
        typename tuples::element<5, Tuple>::type)
      >
  {};
  template<class Tuple>
  struct result_converter<Tuple, 6, false>
    : result_of<plainF(
        typename tuples::element<1, Tuple>::type,
        typename tuples::element<2, Tuple>::type,
        typename tuples::element<3, Tuple>::type,
        typename tuples::element<4, Tuple>::type,
        typename tuples::element<5, Tuple>::type,
        typename tuples::element<6, Tuple>::type)
      >
  {};
  template<class Tuple>
  struct result_converter<Tuple, 7, false>
    : result_of<plainF(
        typename tuples::element<1, Tuple>::type,
        typename tuples::element<2, Tuple>::type,
        typename tuples::element<3, Tuple>::type,
        typename tuples::element<4, Tuple>::type,
        typename tuples::element<5, Tuple>::type,
        typename tuples::element<6, Tuple>::type,
        typename tuples::element<7, Tuple>::type)
      >
  {};
  template<class Tuple>
  struct result_converter<Tuple, 8, false>
    : result_of<plainF(
        typename tuples::element<1, Tuple>::type,
        typename tuples::element<2, Tuple>::type,
        typename tuples::element<3, Tuple>::type,
        typename tuples::element<4, Tuple>::type,
        typename tuples::element<5, Tuple>::type,
        typename tuples::element<6, Tuple>::type,
        typename tuples::element<7, Tuple>::type,
        typename tuples::element<8, Tuple>::type)
      >
  {};
  template<class Tuple>
  struct result_converter<Tuple, 9, false>
    : result_of<plainF(
        typename tuples::element<1, Tuple>::type,
        typename tuples::element<2, Tuple>::type,
        typename tuples::element<3, Tuple>::type,
        typename tuples::element<4, Tuple>::type,
        typename tuples::element<5, Tuple>::type,
        typename tuples::element<6, Tuple>::type,
        typename tuples::element<7, Tuple>::type,
        typename tuples::element<8, Tuple>::type,
        typename tuples::element<9, Tuple>::type)
      >
  {};

  // we do not know the return type off-hand, we must ask it from Func
  // To sig we pass a cons list, where the head is the function object type
  // itself (potentially cv-qualified)
  // and the tail contains the types of the actual arguments to be passed
  // to the function object. The arguments can be cv qualified
  // as well.
  template <class Args>
  struct sig
    : result_converter<
        Args
      , tuples::length<typename Args::tail_type>::value
      , detail::has_sig<plainF>::value
      >
  {};
#else // BOOST_NO_RESULT_OF

  template <class Args> class sig {
    typedef typename detail::remove_reference_and_cv<Func>::type plainF;
  public:
    typedef typename plainF::template sig<
      typename detail::remove_references_from_elements<Args>::type
    >::type type;
  };
#endif

  template<class RET, class A1>
  static RET apply(A1& a1) {
    return a1();
  }
  template<class RET, class A1, class A2>
  static RET apply(A1& a1, A2& a2) {
    return a1(a2);
  }
  template<class RET, class A1, class A2, class A3>
  static RET apply(A1& a1, A2& a2, A3& a3) {
    return a1(a2, a3);
  }
  template<class RET, class A1, class A2, class A3, class A4>
  static RET apply(A1& a1, A2& a2, A3& a3, A4& a4) {
    return a1(a2, a3, a4);
  }
  template<class RET, class A1, class A2, class A3, class A4, class A5>
  static RET apply(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5) {
    return a1(a2, a3, a4, a5);
  }
  template<class RET, class A1, class A2, class A3, class A4, class A5, class A6>
  static RET apply(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6) {
    return a1(a2, a3, a4, a5, a6);
  }
  template<class RET, class A1, class A2, class A3, class A4, class A5, class A6, 
           class A7>
  static RET apply(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, 
                           A7& a7) {
    return a1(a2, a3, a4, a5, a6, a7);
  }
  template<class RET, class A1, class A2, class A3, class A4, class A5, class A6, 
           class A7, class A8>
  static RET apply(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, 
                           A7& a7, A8& a8) {
    return a1(a2, a3, a4, a5, a6, a7, a8);
  }
  template<class RET, class A1, class A2, class A3, class A4, class A5, class A6, 
           class A7, class A8, class A9>
  static RET apply(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, 
                           A7& a7, A8& a8, A9& a9) {
    return a1(a2, a3, a4, a5, a6, a7, a8, a9);
  }
  template<class RET, class A1, class A2, class A3, class A4, class A5, class A6, 
           class A7, class A8, class A9, class A10>
  static RET apply(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, 
                           A7& a7, A8& a8, A9& a9, A10& a10) {
    return a1(a2, a3, a4, a5, a6, a7, a8, a9, a10);
  }
};

template <class Func> struct function_adaptor<const Func>; // error 

// -- function adaptors with data member access
template <class Object, class T>
struct function_adaptor<T Object::*> {

  //  typedef detail::unspecified type;

  // T can have qualifiers and can be a reference type
  // We get the return type by adding const, if the object through which
  // the data member is accessed is const, and finally adding a reference
  template<class Args> class sig { 
    typedef typename boost::tuples::element<1, Args>::type argument_type;
    typedef typename boost::remove_reference<
      argument_type
    >::type unref_type;

    typedef typename detail::IF<boost::is_const<unref_type>::value,
      typename boost::add_const<T>::type,
      T
    >::RET properly_consted_return_type;

    typedef typename detail::IF<boost::is_volatile<unref_type>::value,
      typename boost::add_volatile<properly_consted_return_type>::type,
      properly_consted_return_type
    >::RET properly_cvd_return_type;


  public:
    typedef typename detail::IF<boost::is_reference<argument_type>::value,
      typename boost::add_reference<properly_cvd_return_type>::type,
      typename boost::remove_cv<T>::type
    >::RET type;
  };

  template <class RET>
  static RET apply( T Object::*data, Object& o) {
    return o.*data;
  }
  template <class RET>
  static RET apply( T Object::*data, const Object& o) {
    return o.*data;
  }
  template <class RET>
  static RET apply( T Object::*data, volatile Object& o) {
    return o.*data;
  }
  template <class RET>
  static RET apply( T Object::*data, const volatile Object& o) {
    return o.*data;
  }
  template <class RET>
  static RET apply( T Object::*data, Object* o) {
    return o->*data;
  }
  template <class RET>
  static RET apply( T Object::*data, const Object* o) {
    return o->*data;
  }
  template <class RET>
  static RET apply( T Object::*data, volatile Object* o) {
    return o->*data;
  }
  template <class RET>
  static RET apply( T Object::*data, const volatile Object* o) {
    return o->*data;
  }
};

// -- function adaptors with 1 argument apply
   
template <class Result>
struct function_adaptor<Result (void)> {
  
  template<class T> struct sig { typedef Result type; };
  template <class RET>
  static Result apply(Result (*func)()) {
    return func();
  }
};

template <class Result>
struct function_adaptor<Result (*)(void)> {

  template<class T> struct sig { typedef Result type; };
  template <class RET>
  static Result apply(Result (*func)()) {
    return func();
  }
};


// -- function adaptors with 2 argument apply
template <class Object, class Result>
struct function_adaptor<Result (Object::*)() const> {

  template<class T> struct sig { typedef Result type; };
  template <class RET>
  static Result apply( Result (Object::*func)() const, const Object* o) {
    return (o->*func)();
  }
  template <class RET>
  static Result apply( Result (Object::*func)() const, const Object& o) {
    return (o.*func)();
  }
};

template <class Object, class Result>
struct function_adaptor<Result (Object::*)()> {

  template<class T> struct sig { typedef Result type; };
  template <class RET>
  static Result apply( Result (Object::*func)(), Object* o) {
    return (o->*func)();
  }
  template <class RET>
  static Result apply( Result (Object::*func)(), Object& o) {
    return (o.*func)();
  }
};

template <class Arg1, class Result>
struct function_adaptor<Result (Arg1)> {

  template<class T> struct sig { typedef Result type; };
  template <class RET, class A1>
  static Result apply(Result (*func)(Arg1), A1& a1) {
    return func(a1);
  }
};

template <class Arg1, class Result>
struct function_adaptor<Result (*)(Arg1)> {

  template<class T> struct sig { typedef Result type; };
  template <class RET, class A1>
  static Result apply(Result (*func)(Arg1), A1& a1) {
    return func(a1);
  }
};


// -- function adaptors with 3 argument apply
template <class Object, class Arg1, class Result>
struct function_adaptor<Result (Object::*)(Arg1) const> {

  template<class T> struct sig { typedef Result type; };
  template <class RET, class A1>
  static Result apply( Result (Object::*func)(Arg1) const, const Object* o, 
    A1& a1) {
    return (o->*func)(a1);
  }
  template <class RET, class A1>
  static Result apply( Result (Object::*func)(Arg1) const, const Object& o, 
    A1& a1) {
    return (o.*func)(a1);
  }
};

template <class Object, class Arg1, class Result>
struct function_adaptor<Result (Object::*)(Arg1)> {

  template<class T> struct sig { typedef Result type; };
  template <class RET, class A1>
  static Result apply( Result (Object::*func)(Arg1), Object* o, A1& a1) {
    return (o->*func)(a1);
  }
  template <class RET, class A1>
  static Result apply( Result (Object::*func)(Arg1), Object& o, A1& a1) {
    return (o.*func)(a1);
  }
};

template <class Arg1, class Arg2, class Result>
struct function_adaptor<Result (Arg1, Arg2)> {

  template<class T> struct sig { typedef Result type; };
  template <class RET, class A1, class A2>
  static Result apply(Result (*func)(Arg1, Arg2), A1& a1, A2& a2) {
    return func(a1, a2);
  }
};

template <class Arg1, class Arg2, class Result>
struct function_adaptor<Result (*)(Arg1, Arg2)> {

  template<class T> struct sig { typedef Result type; };
  template <class RET, class A1, class A2>
  static Result apply(Result (*func)(Arg1, Arg2), A1& a1, A2& a2) {
    return func(a1, a2);
  }
};


// -- function adaptors with 4 argument apply
template <class Object, class Arg1, class Arg2, class Result>
struct function_adaptor<Result (Object::*)(Arg1, Arg2) const> {

  template<class T> struct sig { typedef Result type; };
  template <class RET, class A1, class A2>
  static Result apply( Result (Object::*func)(Arg1, Arg2) const, const Object* o, A1& a1, A2& a2) {
    return (o->*func)(a1, a2);
  }
  template <class RET, class A1, class A2>
  static Result apply( Result (Object::*func)(Arg1, Arg2) const, const Object& o, A1& a1, A2& a2) {
    return (o.*func)(a1, a2);
  }
};

template <class Object, class Arg1, class Arg2, class Result>
struct function_adaptor<Result (Object::*)(Arg1, Arg2)> {

  template<class T> struct sig { typedef Result type; };
  template <class RET, class A1, class A2>
  static Result apply( Result (Object::*func)(Arg1, Arg2), Object* o, A1& a1, A2& a2) {
    return (o->*func)(a1, a2);
  }
  template <class RET, class A1, class A2>
  static Result apply( Result (Object::*func)(Arg1, Arg2), Object& o, A1& a1, A2& a2) {
    return (o.*func)(a1, a2);
  }
};

template <class Arg1, class Arg2, class Arg3, class Result>
struct function_adaptor<Result (Arg1, Arg2, Arg3)> {

  template<class T> struct sig { typedef Result type; };
  template <class RET, class A1, class A2, class A3>
  static Result apply(Result (*func)(Arg1, Arg2, Arg3), A1& a1, A2& a2, A3& a3) {
    return func(a1, a2, a3);
  }
};

template <class Arg1, class Arg2, class Arg3, class Result>
struct function_adaptor<Result (*)(Arg1, Arg2, Arg3)> {

  template<class T> struct sig { typedef Result type; };
  template <class RET, class A1, class A2, class A3>
  static Result apply(Result (*func)(Arg1, Arg2, Arg3), A1& a1, A2& a2, A3& a3) {
    return func(a1, a2, a3);
  }
};


// -- function adaptors with 5 argument apply
template <class Object, class Arg1, class Arg2, class Arg3, class Result>
struct function_adaptor<Result (Object::*)(Arg1, Arg2, Arg3) const> {

  template<class T> struct sig { typedef Result type; };
  template <class RET, class A1, class A2, class A3>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3) const, const Object* o, A1& a1, A2& a2, A3& a3) {
    return (o->*func)(a1, a2, a3);
  }
  template <class RET, class A1, class A2, class A3>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3) const, const Object& o, A1& a1, A2& a2, A3& a3) {
    return (o.*func)(a1, a2, a3);
  }
};

template <class Object, class Arg1, class Arg2, class Arg3, class Result>
struct function_adaptor<Result (Object::*)(Arg1, Arg2, Arg3)> {

  template<class T> struct sig { typedef Result type; };
  template <class RET, class A1, class A2, class A3>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3), Object* o, A1& a1, A2& a2, A3& a3) {
    return (o->*func)(a1, a2, a3);
  }
  template <class RET, class A1, class A2, class A3>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3), Object& o, A1& a1, A2& a2, A3& a3) {
    return (o.*func)(a1, a2, a3);
  }
};

template <class Arg1, class Arg2, class Arg3, class Arg4, class Result>
struct function_adaptor<Result (Arg1, Arg2, Arg3, Arg4)> {

  template<class T> struct sig { typedef Result type; };
  template <class RET, class A1, class A2, class A3, class A4>
  static Result apply(Result (*func)(Arg1, Arg2, Arg3, Arg4), A1& a1, A2& a2, A3& a3, A4& a4) {
    return func(a1, a2, a3, a4);
  }
};

template <class Arg1, class Arg2, class Arg3, class Arg4, class Result>
struct function_adaptor<Result (*)(Arg1, Arg2, Arg3, Arg4)> {

  template<class T> struct sig { typedef Result type; };
  template <class RET, class A1, class A2, class A3, class A4>
  static Result apply(Result (*func)(Arg1, Arg2, Arg3, Arg4), A1& a1, A2& a2, A3& a3, A4& a4) {
    return func(a1, a2, a3, a4);
  }
};


// -- function adaptors with 6 argument apply
template <class Object, class Arg1, class Arg2, class Arg3, class Arg4, class Result>
struct function_adaptor<Result (Object::*)(Arg1, Arg2, Arg3, Arg4) const> {

  template<class T> struct sig { typedef Result type; };
  template <class RET, class A1, class A2, class A3, class A4>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3, Arg4) const, const Object* o, A1& a1, A2& a2, A3& a3, A4& a4) {
    return (o->*func)(a1, a2, a3, a4);
  }
  template <class RET, class A1, class A2, class A3, class A4>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3, Arg4) const, const Object& o, A1& a1, A2& a2, A3& a3, A4& a4) {
    return (o.*func)(a1, a2, a3, a4);
  }
};

template <class Object, class Arg1, class Arg2, class Arg3, class Arg4, class Result>
struct function_adaptor<Result (Object::*)(Arg1, Arg2, Arg3, Arg4)> {

  template<class T> struct sig { typedef Result type; };
  template <class RET, class A1, class A2, class A3, class A4>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3, Arg4), Object* o, A1& a1, A2& a2, A3& a3, A4& a4) {
    return (o->*func)(a1, a2, a3, a4);
  }
  template <class RET, class A1, class A2, class A3, class A4>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3, Arg4), Object& o, A1& a1, A2& a2, A3& a3, A4& a4) {
    return (o.*func)(a1, a2, a3, a4);
  }
};

template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Result>
struct function_adaptor<Result (Arg1, Arg2, Arg3, Arg4, Arg5)> {

  template<class T> struct sig { typedef Result type; };
  template <class RET, class A1, class A2, class A3, class A4, class A5>
  static Result apply(Result (*func)(Arg1, Arg2, Arg3, Arg4, Arg5), A1& a1, A2& a2, A3& a3, A4& a4, A5& a5) {
    return func(a1, a2, a3, a4, a5);
  }
};

template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Result>
struct function_adaptor<Result (*)(Arg1, Arg2, Arg3, Arg4, Arg5)> {

  template<class T> struct sig { typedef Result type; };
  template <class RET, class A1, class A2, class A3, class A4, class A5>
  static Result apply(Result (*func)(Arg1, Arg2, Arg3, Arg4, Arg5), A1& a1, A2& a2, A3& a3, A4& a4, A5& a5) {
    return func(a1, a2, a3, a4, a5);
  }
};


// -- function adaptors with 7 argument apply
template <class Object, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Result>
struct function_adaptor<Result (Object::*)(Arg1, Arg2, Arg3, Arg4, Arg5) const> {

  template<class T> struct sig { typedef Result type; };
  template <class RET, class A1, class A2, class A3, class A4, class A5>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3, Arg4, Arg5) const, const Object* o, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5) {
    return (o->*func)(a1, a2, a3, a4, a5);
  }
  template <class RET, class A1, class A2, class A3, class A4, class A5>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3, Arg4, Arg5) const, const Object& o, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5) {
    return (o.*func)(a1, a2, a3, a4, a5);
  }
};

template <class Object, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Result>
struct function_adaptor<Result (Object::*)(Arg1, Arg2, Arg3, Arg4, Arg5)> {

  template<class T> struct sig { typedef Result type; };
  template <class RET, class A1, class A2, class A3, class A4, class A5>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3, Arg4, Arg5), Object* o, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5) {
    return (o->*func)(a1, a2, a3, a4, a5);
  }
  template <class RET, class A1, class A2, class A3, class A4, class A5>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3, Arg4, Arg5), Object& o, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5) {
    return (o.*func)(a1, a2, a3, a4, a5);
  }
};

template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Result>
struct function_adaptor<Result (Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)> {

  template<class T> struct sig { typedef Result type; };
  template <class RET, class A1, class A2, class A3, class A4, class A5, class A6>
  static Result apply(Result (*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6), A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6) {
    return func(a1, a2, a3, a4, a5, a6);
  }
};

template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Result>
struct function_adaptor<Result (*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)> {

  template<class T> struct sig { typedef Result type; };
  template <class RET, class A1, class A2, class A3, class A4, class A5, class A6>
  static Result apply(Result (*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6), A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6) {
    return func(a1, a2, a3, a4, a5, a6);
  }
};


// -- function adaptors with 8 argument apply
template <class Object, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Result>
struct function_adaptor<Result (Object::*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6) const> {

  template<class T> struct sig { typedef Result type; };
  template <class RET, class A1, class A2, class A3, class A4, class A5, class A6>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6) const, const Object* o, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6) {
    return (o->*func)(a1, a2, a3, a4, a5, a6);
  }
  template <class RET, class A1, class A2, class A3, class A4, class A5, class A6>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6) const, const Object& o, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6) {
    return (o.*func)(a1, a2, a3, a4, a5, a6);
  }
};

template <class Object, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Result>
struct function_adaptor<Result (Object::*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)> {

  template<class T> struct sig { typedef Result type; };
  template <class RET, class A1, class A2, class A3, class A4, class A5, class A6>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6), Object* o, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6) {
    return (o->*func)(a1, a2, a3, a4, a5, a6);
  }
  template <class RET, class A1, class A2, class A3, class A4, class A5, class A6>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6), Object& o, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6) {
    return (o.*func)(a1, a2, a3, a4, a5, a6);
  }
};

template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7, class Result>
struct function_adaptor<Result (Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)> {

  template<class T> struct sig { typedef Result type; };
  template <class RET, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
  static Result apply(Result (*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7), A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7) {
    return func(a1, a2, a3, a4, a5, a6, a7);
  }
};

template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7, class Result>
struct function_adaptor<Result (*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)> {

  template<class T> struct sig { typedef Result type; };
  template <class RET, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
  static Result apply(Result (*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7), A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7) {
    return func(a1, a2, a3, a4, a5, a6, a7);
  }
};


// -- function adaptors with 9 argument apply
template <class Object, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7, class Result>
struct function_adaptor<Result (Object::*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7) const> {

  template<class T> struct sig { typedef Result type; };
  template <class RET, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7) const, const Object* o, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7) {
    return (o->*func)(a1, a2, a3, a4, a5, a6, a7);
  }
  template <class RET, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7) const, const Object& o, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7) {
    return (o.*func)(a1, a2, a3, a4, a5, a6, a7);
  }
};

template <class Object, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7, class Result>
struct function_adaptor<Result (Object::*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)> {

  template<class T> struct sig { typedef Result type; };
  template <class RET, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7), Object* o, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7) {
    return (o->*func)(a1, a2, a3, a4, a5, a6, a7);
  }
  template <class RET, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7), Object& o, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7) {
    return (o.*func)(a1, a2, a3, a4, a5, a6, a7);
  }
};

template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7, class Arg8, class Result>
struct function_adaptor<Result (Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)> {

  template<class T> struct sig { typedef Result type; };
  template <class RET, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
  static Result apply(Result (*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8), A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8) {
    return func(a1, a2, a3, a4, a5, a6, a7, a8);
  }
};

template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7, class Arg8, class Result>
struct function_adaptor<Result (*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)> {

  template<class T> struct sig { typedef Result type; };
  template <class RET, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
  static Result apply(Result (*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8), A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8) {
    return func(a1, a2, a3, a4, a5, a6, a7, a8);
  }
};


// -- function adaptors with 10 argument apply
template <class Object, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7, class Arg8, class Result>
struct function_adaptor<Result (Object::*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8) const> {

  template<class T> struct sig { typedef Result type; };
  template <class RET, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8) const, const Object* o, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8) {
    return (o->*func)(a1, a2, a3, a4, a5, a6, a7, a8);
  }
  template <class RET, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8) const, const Object& o, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8) {
    return (o.*func)(a1, a2, a3, a4, a5, a6, a7, a8);
  }
};

template <class Object, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7, class Arg8, class Result>
struct function_adaptor<Result (Object::*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)> {

  template<class T> struct sig { typedef Result type; };
  template <class RET, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8), Object* o, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8) {
    return (o->*func)(a1, a2, a3, a4, a5, a6, a7, a8);
  }
  template <class RET, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8), Object& o, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8) {
    return (o.*func)(a1, a2, a3, a4, a5, a6, a7, a8);
  }
};

template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7, class Arg8, class Arg9, class Result>
struct function_adaptor<Result (Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9)> {

  template<class T> struct sig { typedef Result type; };
  template <class RET, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
  static Result apply(Result (*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9), A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8, A9& a9) {
    return func(a1, a2, a3, a4, a5, a6, a7, a8, a9);
  }
};

template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7, class Arg8, class Arg9, class Result>
struct function_adaptor<Result (*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9)> {

  template<class T> struct sig { typedef Result type; };
  template <class RET, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
  static Result apply(Result (*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9), A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8, A9& a9) {
    return func(a1, a2, a3, a4, a5, a6, a7, a8, a9);
  }
};

} // namespace lambda
} // namespace boost

#endif














/* function_adaptors.hpp
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
*/