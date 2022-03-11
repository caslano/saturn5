// - construct.hpp -- Lambda Library -------------
//
// Copyright (C) 2000 Gary Powell (powellg@amazon.com)
// Copyright (C) 1999, 2000 Jaakko Jarvi (jaakko.jarvi@cs.utu.fi)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org
//
// -----------------------------------------------

#if !defined(BOOST_LAMBDA_CONSTRUCT_HPP)
#define BOOST_LAMBDA_CONSTRUCT_HPP

#include "boost/type_traits/remove_cv.hpp"
#include "boost/type_traits/is_pointer.hpp"

namespace boost { 
namespace lambda {

  // constructor is used together with bind. constructor<A> creates a bindable
  // function object that passes its arguments forward to a constructor call
  // of type A

template<class T> struct constructor {

  template <class U> struct sig { typedef T type; };

  T operator()() const {
    return T();
  }

  template<class A1>
  T operator()(A1& a1) const {
    return T(a1);
  }

  template<class A1, class A2>
  T operator()(A1& a1, A2& a2) const {
    return T(a1, a2);
  }

  template<class A1, class A2, class A3>
  T operator()(A1& a1, A2& a2, A3& a3) const {
    return T(a1, a2, a3);
  }

  template<class A1, class A2, class A3, class A4>
  T operator()(A1& a1, A2& a2, A3& a3, A4& a4) const {
    return T(a1, a2, a3, a4);
  }

  template<class A1, class A2, class A3, class A4, class A5>
  T operator()(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5) const {
    return T(a1, a2, a3, a4, a5);
  }

  template<class A1, class A2, class A3, class A4, class A5, class A6>
  T operator()(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6) const {
    return T(a1, a2, a3, a4, a5, a6);
  }

  template<class A1, class A2, class A3, class A4, class A5, class A6, class A7>
  T operator()(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7) const {
    return T(a1, a2, a3, a4, a5, a6, a7);
  }

  template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
  T operator()(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8) const {
    return T(a1, a2, a3, a4, a5, a6, a7, a8);
  }

  template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
  T operator()(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8, A9& a9) const {
    return T(a1, a2, a3, a4, a5, a6, a7, a8, a9);
  }

  template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
  T operator()(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8, A9& a9, A10& a10) const {
    return T(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
  }

};


namespace detail {

// A standard conforming compiler could disambiguate between
// A1* and A1&, but not all compilers do that, so we need the
// helpers


template <bool IsPointer>
struct destructor_helper {

  template<class A1>
  static void exec(A1& a1) {
    // remove all the qualifiers, not sure whether it is necessary
    typedef typename boost::remove_cv<A1>::type plainA1;
     a1.~plainA1();
  }
};

template <>
struct destructor_helper<true> {

  template<class A1>
  static void exec(A1* a1) {
    typedef typename boost::remove_cv<A1>::type plainA1;
    (*a1).~plainA1();
  }
};

}

// destructor funtion object
struct destructor {  

  template <class T> struct sig { typedef void type; };  

  template<class A1>
  void operator()(A1& a1) const {
    typedef typename boost::remove_cv<A1>::type plainA1;
    detail::destructor_helper<boost::is_pointer<plainA1>::value>::exec(a1);
  }
};



// new_ptr is used together with bind.

  // note: placement new is not supported

template<class T> struct new_ptr {

  template <class U> struct sig { typedef T* type; };  

  T* operator()() const {
    return new T();
  }

  template<class A1>
  T* operator()(A1& a1) const {
    return new T(a1);
  }

  template<class A1, class A2>
  T* operator()(A1& a1, A2& a2) const {
    return new T(a1, a2);
  }

  template<class A1, class A2, class A3>
  T* operator()(A1& a1, A2& a2, A3& a3) const {
    return new T(a1, a2, a3);
  }

  template<class A1, class A2, class A3, class A4>
  T* operator()(A1& a1, A2& a2, A3& a3, A4& a4) const {
    return new T(a1, a2, a3, a4);
  }

  template<class A1, class A2, class A3, class A4, class A5>
  T* operator()(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5) const {
    return new T(a1, a2, a3, a4, a5);
  }

  template<class A1, class A2, class A3, class A4, class A5, class A6>
  T* operator()(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6) const {
    return new T(a1, a2, a3, a4, a5, a6);
  }

  template<class A1, class A2, class A3, class A4, class A5, class A6, class A7>
  T* operator()(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7) const {
    return new T(a1, a2, a3, a4, a5, a6, a7);
  }

  template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
  T* operator()(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8) const {
    return new T(a1, a2, a3, a4, a5, a6, a7, a8);
  }

  template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
  T* operator()(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8, A9& a9) const {
    return new T(a1, a2, a3, a4, a5, a6, a7, a8, a9);
  }

  template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
  T* operator()(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8, A9& a9, A10& a10) const {
    return new T(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
  }

};

// delete_ptr return void

struct delete_ptr {

  template <class U> struct sig { typedef void type; };  

  template <class A1>
  void operator()(A1& a1) const {
    delete a1;
  }

};


// new_array is used together with bind.

template<class T> struct new_array {

  template <class U> struct sig { typedef T* type; };  

  T* operator()(int size) const {
    return new T[size];
  }
};


// delete_ptr return void

struct delete_array {

  template <class U> struct sig { typedef void type; };  

  template <class A1>
  void operator()(A1& a1) const {
    delete[] a1;
  }

};



} // namespace lambda 
} // namespace boost

#endif

/* construct.hpp
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
*/