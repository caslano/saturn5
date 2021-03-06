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
3pNpeXG2hzc8qfpo8t6Ox9llF8EdU338midzgrXocRoALTt0v7Ml50MQjOgU+xBILZAYTsvDcX3WFCPX6JW5rFmBc3/l4LuFfezGRniTg5wB4y13uvrbr/nDRg720MaFxWgKbl8II04UO01UMRCDGuje+irXRK4qdzsczqW6KwgDOKH6AZL0tQ6FJzvZZ8tilbMO5U06OJIep8wb7qHkgdGja6GZcNQIPWiwlOGnDmWFJ37lD3b3EQOhoBqxO4CLphb0hCyz35RMVRDma+Ju/C/aBVGtXyirDCmuuYIQwQj7dQhkmPeRvI16dpnvTP7RFJUAgHe3ATt+39fz1LhEhBjM46kBrMODLgDqe+wyYtWej7vWd7pyjU8rfKroIcDnuHYexZvmp2PN972FbBPo71BzNZTvT1EVqUVIYCwJLiwwQko7HnLf4Vkm4hjAZfmWj4+J/ZEKnkHlz5QwoFKz5eEbZNIMkwfU5SvtWsKE9BvVZhVosokOBLp0oz50ZXT+JY+iJzKq3Z2D5ha6SrtntAoRq6b0BzCGi6gnOPK+XYROobfRZhi+f1K4yQ==
*/