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
z5y73yr+LW1t4gxLWzHDpsPmYTknYJvwNLfb+6/D19frE7JtbeGaT5+bnm9nuyaf1WYu+dY2jmzxb2a7xt6alyKGZVaEP8bCH+Mj071xsq5czyU9IH4NoLUrwrbAxxzLf49EPIFBHrcnOCh4SHDr4E4BDo8DZ+nB3mcW51pkNBdl/GOkKa+Os7DYcm76Qol3hVhlfNNyqGFhjZneSaT3A+JxliwIcHnOc3vPM+gQoYSPNkZJ6xToNAj3Z5wjEHTGHI47TNLDkH7WLLFVSTxmPYtgPbPaxVCfOLdDu5i2a1nridjFaFfLludwfX57Ptel00bG8vSuSy+iG6OCuyfsVrSDMrcT+cwumj59Dr/B4AmbYCoQynSq6fAL0Gtp0riXZiMogOce3IY4Uj7QbSl9wKjU9KwZBWY2WDZSV83C0bbg0cK/FnMXhl07Y3yGJfxsM7yeA5wi/ql27UyHjUL5mpEdBk2NRl5mBscFxwUEeJoHabvx1dFVtDm0WnlL/Voc6aWf/kaGWd4vfKDLW9tATfkjmH+WNd0kT9X0m8qDH6aCDFMG0CPgTfiwun4nz8rJqa5fiUrbnLoLf5aNbhkX9ZPhhs4CKvUTXI/6ia6bfuIjqmh1KPVTh7M/JO+U15r348x7oOUsjTtRt7b75H1KTqHZciTvt3fSebfLK8MaP3nmh1c2xEfZqtuLF1Go3iyXXqD7kY/dPrLl51xbY390SHhb42/NsOnHatXfkDAfXe1iZ7OVenoGVArZYw9Vl2dWDr6wcmY90TK1Ef4n1Vzbdsj4WFcWQwfdgtiWSkp0ZamtrjRnuAKG87iMYHdVM6y1nnl11C7CS3Xrc9ccsm2D1nLVewPL6ym5OlKPHUB3QY+hH1XXI7SYPjkvc8rsWtpchIRpY6dHxqft87iT2PS5wlHi38K2P2NYXWfiIkh10IdN/nUf1BIUQTmsdX1rsJJrPSgWtAy0DuFTLDoZODU/M6+WejVDeOerDKRgow/EZfvuodewFYr/tZgbb2yrEx1ev3/In5r+f7la/Bfi/yXE9l2K4S3fWJoqfFu5903+/9SkosnsV7bB3VtXO0bI/4G8H3RkGQyylIGn5nNjpX4e+qi2+um7TqbqHcGj/8P1u4DIK//9kB88IqcpewRlt5ZrbAMlV3cK1w10D+p6wsdV5To4f2qhzf+KXRkinO27sG15WXkLlS4v27LRvHwnZ92we9fVvNwriL5U3tHq3N9rvdu/h2m9F4Kod702CbKxfKrrOYUpO00bFfFBpFPio+f0nOIa28+zwvuq8aQKtdV9ib3u9VqNzeL/JlYxXADL5RHbMimxLxPdhh4R/3excqChbTmV2JeTbsMviP+LxiMqzLbsrOE7VK63nl6QV7kvuhD1+CXx/4PhXYtwnzwfMq7CmoZ+xr22YxrGaf2Ol16/tP0TWVeFEU28xf9qPd5pJv7h+oztDHluh7JtKjIVQyZD3OYY1Bku+YdlGLwTSPofGONUCeS2xuOG9T4Nb+yVe19flUO9CjKzWa/nIe4earzoOAxG2EchcPsI3cfgXtzxXO1ev5eW1vHcarP/yfikbv3PP9MOvGv0zPKMYHnCTfJn5jmCeba2l8VcixdLoVuAHoY8oUeq2svoguzMwhyb/xvqPfwI1ybZv8cwLsOyth/xZdr3VVbeotr7Ks1rGTPW1vcMqb3v4biOsuk+X+u8ut7iudk7xPItqeXozxMteps9dS60Vrd35USfvNwWXvd+1Pe9uQe/8VZBGfvyvbkPxzMZlTKaUz7pCJWehVmh/KKCGt+tcoS/p/2cDOW2f5f86fdqm/LQaysSHXhHDEA5G83+mhWcN/Hyhe/Xu6mgdfs=
*/