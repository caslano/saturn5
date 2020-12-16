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
ARwDzAaeBRwHzAfOBk4ELgZOAVp5TAPeBrwAGIGMLgQmAAuBFn95ar2AdQifQ8W2CY76ocI7MIZnbQnAJNpctecdNfhb0stQ83fIUfO729nI18KBLNcg8nHUist4rzFeMugg431DPv4JlKvBGd8JbAcMB3YENgNaeTUHdgVGArsDWwL7AlsBBwCjgIOAMcAxwI7AqcAsYDGwH3AmsDXQDYwF1gE7UJ5nADcAuwE3ArsD7wf2AD4MTAM+CkwH/gbYG/gEMBP4EvPZzXw+A1Y7OE/jfDSPd3qVOtRdRNI++gJlzg1sy7uNUnin0UTaphUDBwNvpk3anbRJ201btIPAEbT5Gklbr1HAfOAY4PnAPOBq4FjgLcCzgfuBE4DNwVM+MBU4EZgDnAwsAk4BXgWcZsUDngt8Bnge8K/A84GYJogtWjJwBnAAcBbQmiDPAbYBlgMzgPOAZwErgLOB84GXAiuBa4FVwAeA1cAXgBcB3wXWAI8Ca4HR6J9uYE/gAuBw4ELgFOBi4DrgJcBtwMuAh4CXAz8FXgFMRINbavEBvBI4DrgM6Ab+BPhL4FXAu4BXA18FrrD4AF4DPAZcCfweeC2wa1j9nWjDgKuB04HXAS8CrgGuBF5vpQu8AbgVeCPwNeBa4CfAm4Ah4RhfgL2B66x0gLcBbwPeDnwCeAfwReAG4N+BvwBa65xfAhf9m87Cs3EWng+aA1oO2hA8Gw+6oAu6oAu6oAu6oAu6oAu6/yF32s//syw6dfr/ZtKJ9f839+PZaJZe///tfo3q/yN+YPr/DOdX/39HP//6//Y8Mvzo/ztQVifIlfTv1f/P8NH/d50K/f8UE+8zK1fmHxu6PMx8+qr7om/t+cyp2wv9T+v/b+7349D/P9F+x3MLvG24dwf3OIIu6IIu6IIu6IIu6IIu6P5v3L9p/X/K9P9DkxrX/8/GImpXd8/6/8T6/+4e/vT/mQ7X6Jk++v+vdfer/894ev3/t7v71///a/fG9f/n9/Cv/x+WZNEP1//PDFD/PwvhMtKUnKn/r+Skytsvza/+P+I3Tf8/M0D9/8HWQlrx1lD/nzzqeEK8wPX/GZb6/5b8A9f/z/wB+v/9EXeDKp+3/n+mj/7/b9Ma1f9HOoHr/zOsX/3/+9Ia1f9nfL3+/860hvr/YekN9f8Hp/vX//99WuP6/3elNa7/3zZdr///17QG+v/sb4Hr/2cGrL/YUP9/fQtDXDoGuVhgN+BApLc5nfr/WXr9/0wf/f8nJXxbNYZN7Ws9L9XvgaY3qv9P/zQVh+8a1f9/Q/xDwvoYz4Xq2gfj2/X/1dg3L1N+T8F0GRPQvoqMJ4Ce+pko5Sg1UiG1rixbRm/5rWdXKHaGW5l3mW85HMZg6Lj+FPQpyKMnPSzDCnel6UAJ5kIS+0HjMar3YBvcKTxFhp1l1JpPmhHQc1tsvudciH3CUuNZ1xJjeMgmpVO9oacV9oARQx3mdyXusdB7zE4hMdQrNiTMntA4xzUOnU3AHlsYnU3AZr2/sgl41Oavswn4m5T3QsjRgTY+0XCjtq82XlM2Ac8Lz8tCWxizYfcwxfGYs9o4w1UJnWC30SpkKywsJhldQs9X48vnvRAeXyPIT8m0k7z7xGm92wW/X5mfm5vx1JUy7dnH8p8F240c6InlG/GQfim+iE9A7gmOUPW7wi9JHbaFb6xxL+rFI8M4eX+NI8Z8zYihPvYu1pNhPhViyeEo3s2VfGaIXL7F80F57mja7QkyKZcUSTPX5UCKZ8A2ZInpNo6YpUaB40pjr2OKkQ2LgpXO6cZ+5/lGKmX1quTZLGwAfutiGdrG2Y5Xnb1DcY9m6IPK1mRZhvBgtoGEfooyfAE=
*/