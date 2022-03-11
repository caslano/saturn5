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