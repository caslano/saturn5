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
#include "boost/config.hpp"

#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) && !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#include <utility>
#endif

namespace boost { 
namespace lambda {

  // constructor is used together with bind. constructor<A> creates a bindable
  // function object that passes its arguments forward to a constructor call
  // of type A

template<class T> struct constructor {

  template <class U> struct sig { typedef T type; };

#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) && !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
  template <class... Args>
  T operator()(Args&&... args) const {
    return T(std::forward<Args>(args)...);
  }
#else
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
#endif

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

#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) && !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
  template <class... Args>
  T* operator()(Args&&... args) const {
    return new T(std::forward<Args>(args)...);
  }
#else
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
#endif

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