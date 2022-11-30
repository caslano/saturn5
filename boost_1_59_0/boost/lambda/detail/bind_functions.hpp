// -- bind_functions.hpp -- Boost Lambda Library
//
// Copyright (C) 1999, 2000 Jaakko Jarvi (jaakko.jarvi@cs.utu.fi)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org

// ----------------------------------------------------------------

#ifndef BOOST_LAMBDA_BIND_FUNCTIONS_HPP
#define BOOST_LAMBDA_BIND_FUNCTIONS_HPP


namespace boost { 
namespace lambda {

#ifdef BOOST_LAMBDA_INCORRECT_BIND_OVERLOADING

  // gcc 2.96 instantiates bind functions it does not even call.
  // These instantiations lead to incorrect types in the return type, 
  // and a compilation error results. 
  // This tweaking is to prevent the formation of the erroneous type.
namespace detail {

template<class T> struct constify_non_funcs {
  typedef typename 
  detail::IF_type<boost::is_function<T>::value,
    boost::add_reference<T>,
    boost::add_const<T>
  >::type type;
};

}
#endif
// 1-argument bind functions --------------------------
#ifndef BOOST_REF_TO_FUNC_CONFLICTS_WITH_REF_TO_T
template <class Result>
inline const
lambda_functor<
  lambda_functor_base<
    action<1, function_action<1, Result> >,
    typename detail::bind_tuple_mapper<Result(&)()>::type
  >
>

bind(Result(& a1)()) {
  return
    lambda_functor_base<
      action<1, function_action<1, Result> >,
      typename detail::bind_tuple_mapper<Result(&)()>::type
    >
    ( typename detail::bind_tuple_mapper<Result(&)()>::type
      (a1)
    );
}
#endif

 #ifndef BOOST_LAMBDA_INCORRECT_BIND_OVERLOADING 
template <class Arg1>
inline const
lambda_functor<
  lambda_functor_base<
    action<1, function_action<1> >,
    typename detail::bind_tuple_mapper<const Arg1>::type
  >
>

bind(const Arg1& a1) {
  return
    lambda_functor_base<
      action<1, function_action<1> >,
      typename detail::bind_tuple_mapper<const Arg1>::type
    >
    ( typename detail::bind_tuple_mapper<const Arg1>::type
      (a1)
    );
}

template <class Result, class Arg1>
inline const
lambda_functor<
  lambda_functor_base<
    action<1, function_action<1, Result> >,
    typename detail::bind_tuple_mapper<const Arg1>::type
  >
>

bind(const Arg1& a1) {
  return
    lambda_functor_base<
      action<1, function_action<1, Result> >,
      typename detail::bind_tuple_mapper<const Arg1>::type
    >
    ( typename detail::bind_tuple_mapper<const Arg1>::type
      (a1)
    );
}


 #else 
template <class Arg1>
inline const
lambda_functor<
  lambda_functor_base<
    action<1, function_action<1> >,
    typename detail::bind_tuple_mapper<
      typename detail::constify_non_funcs<Arg1>::type
    >::type
  >
>

bind(const Arg1& a1) {
  return
    lambda_functor_base<
      action<1, function_action<1> >,
      typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type
      >::type
      (a1)
    );
}

template <class Result, class Arg1>
inline const
lambda_functor<
  lambda_functor_base<
    action<1, function_action<1, Result> >,
    typename detail::bind_tuple_mapper<
      typename detail::constify_non_funcs<Arg1>::type
    >::type
  >
>

bind(const Arg1& a1) {
  return
    lambda_functor_base<
      action<1, function_action<1, Result> >,
      typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type
      >::type
      (a1)
    );
}

template <class Result>
inline const
lambda_functor<
  lambda_functor_base<
    action<1, function_action<1, Result> >,
    typename detail::bind_tuple_mapper<Result(*)()>::type
  >
>

bind(Result(* const & a1)()) {
  return
    lambda_functor_base<
      action<1, function_action<1, Result> >,
      typename detail::bind_tuple_mapper<Result(*)()>::type
    >
    ( typename detail::bind_tuple_mapper<Result(*)()>::type
      (a1)
    );
}


#endif 

// 2-argument bind functions --------------------------
#ifndef BOOST_REF_TO_FUNC_CONFLICTS_WITH_REF_TO_T
template <class Result, class Par1, class Arg2>
inline const
lambda_functor<
  lambda_functor_base<
    action<2, function_action<2, Result> >,
    typename detail::bind_tuple_mapper<Result(&)(Par1), const Arg2>::type
  >
>

bind(Result(&a1)(Par1), const Arg2& a2) {
  return
    lambda_functor_base<
      action<2, function_action<2, Result> >,
      typename detail::bind_tuple_mapper<Result(&)(Par1), const Arg2>::type
    >
    ( typename detail::bind_tuple_mapper<Result(&)(Par1), const Arg2>::type
      (a1, a2)
    );
}
#endif

#ifndef BOOST_LAMBDA_INCORRECT_BIND_OVERLOADING 
template <class Arg1, class Arg2>
inline const
lambda_functor<
  lambda_functor_base<
    action<2, function_action<2> >,
    typename detail::bind_tuple_mapper<const Arg1, const Arg2>::type
  >
>

bind(const Arg1& a1, const Arg2& a2) {
  return
    lambda_functor_base<
      action<2, function_action<2> >,
      typename detail::bind_tuple_mapper<const Arg1, const Arg2>::type
    >
    ( typename detail::bind_tuple_mapper<const Arg1, const Arg2>::type
      (a1, a2)
    );
}

template <class Result, class Arg1, class Arg2>
inline const
lambda_functor<
  lambda_functor_base<
    action<2, function_action<2, Result> >,
    typename detail::bind_tuple_mapper<const Arg1, const Arg2>::type
  >
>

bind(const Arg1& a1, const Arg2& a2) {
  return
    lambda_functor_base<
      action<2, function_action<2, Result> >,
      typename detail::bind_tuple_mapper<const Arg1, const Arg2>::type
    >
    ( typename detail::bind_tuple_mapper<const Arg1, const Arg2>::type
      (a1, a2)
    );
}


 #else 
template <class Arg1, class Arg2>
inline const
lambda_functor<
  lambda_functor_base<
    action<2, function_action<2> >,
    typename detail::bind_tuple_mapper<
      typename detail::constify_non_funcs<Arg1>::type, const Arg2
    >::type
  >
>

bind(const Arg1& a1, const Arg2& a2) {
  return
    lambda_functor_base<
      action<2, function_action<2> >,
      typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2
      >::type
      (a1, a2)
    );
}

template <class Result, class Arg1, class Arg2>
inline const
lambda_functor<
  lambda_functor_base<
    action<2, function_action<2, Result> >,
    typename detail::bind_tuple_mapper<
      typename detail::constify_non_funcs<Arg1>::type, const Arg2
    >::type
  >
>

bind(const Arg1& a1, const Arg2& a2) {
  return
    lambda_functor_base<
      action<2, function_action<2, Result> >,
      typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2
      >::type
      (a1, a2)
    );
}

template <class Result, class Par1, class Arg2>
inline const
lambda_functor<
  lambda_functor_base<
    action<2, function_action<2, Result> >,
    typename detail::bind_tuple_mapper<Result(*)(Par1), const Arg2>::type
  >
>

bind(Result(* const & a1)(Par1), const Arg2& a2) {
  return
    lambda_functor_base<
      action<2, function_action<2, Result> >,
      typename detail::bind_tuple_mapper<Result(*)(Par1), const Arg2>::type
    >
    ( typename detail::bind_tuple_mapper<Result(*)(Par1), const Arg2>::type
      (a1, a2)
    );
}


 #endif 

// 3-argument bind functions --------------------------
#ifndef BOOST_REF_TO_FUNC_CONFLICTS_WITH_REF_TO_T
template <class Result, class Par1, class Par2, class Arg2, class Arg3>
inline const
lambda_functor<
  lambda_functor_base<
    action<3, function_action<3, Result> >,
    typename detail::bind_tuple_mapper<
      Result(&)(Par1, Par2), const Arg2, const Arg3
    >::type
  >
>

bind(Result(&a1)(Par1, Par2), const Arg2& a2, const Arg3& a3) {
  return
    lambda_functor_base<
      action<3, function_action<3, Result> >,
      typename detail::bind_tuple_mapper<
        Result(&)(Par1, Par2), const Arg2, const Arg3
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        Result(&)(Par1, Par2), const Arg2, const Arg3
      >::type
      (a1, a2, a3)
    );
}
#endif

 #ifndef BOOST_LAMBDA_INCORRECT_BIND_OVERLOADING 
template <class Arg1, class Arg2, class Arg3>
inline const
lambda_functor<
  lambda_functor_base<
    action<3, function_action<3> >,
    typename detail::bind_tuple_mapper<
      const Arg1, const Arg2, const Arg3
    >::type
  >
>

bind(const Arg1& a1, const Arg2& a2, const Arg3& a3) {
  return
    lambda_functor_base<
      action<3, function_action<3> >,
      typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3
      >::type
      (a1, a2, a3)
    );
}

template <class Result, class Arg1, class Arg2, class Arg3>
inline const
lambda_functor<
  lambda_functor_base<
    action<3, function_action<3, Result> >,
    typename detail::bind_tuple_mapper<
      const Arg1, const Arg2, const Arg3
    >::type
  >
>

bind(const Arg1& a1, const Arg2& a2, const Arg3& a3) {
  return
    lambda_functor_base<
      action<3, function_action<3, Result> >,
      typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3
      >::type
      (a1, a2, a3)
    );
}


 #else 
template <class Arg1, class Arg2, class Arg3>
inline const
lambda_functor<
  lambda_functor_base<
    action<3, function_action<3> >,
    typename detail::bind_tuple_mapper<
      typename detail::constify_non_funcs<Arg1>::type, const Arg2, const Arg3
    >::type
  >
>

bind(const Arg1& a1, const Arg2& a2, const Arg3& a3) {
  return
    lambda_functor_base<
      action<3, function_action<3> >,
      typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3
      >::type
      (a1, a2, a3)
    );
}

template <class Result, class Arg1, class Arg2, class Arg3>
inline const
lambda_functor<
  lambda_functor_base<
    action<3, function_action<3, Result> >,
    typename detail::bind_tuple_mapper<
      typename detail::constify_non_funcs<Arg1>::type, const Arg2, const Arg3
    >::type
  >
>

bind(const Arg1& a1, const Arg2& a2, const Arg3& a3) {
  return
    lambda_functor_base<
      action<3, function_action<3, Result> >,
      typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3
      >::type
      (a1, a2, a3)
    );
}

template <class Result, class Par1, class Par2, class Arg2, class Arg3>
inline const
lambda_functor<
  lambda_functor_base<
    action<3, function_action<3, Result> >,
    typename detail::bind_tuple_mapper<
      Result(*)(Par1, Par2), const Arg2, const Arg3
    >::type
  >
>

bind(Result(* const & a1)(Par1, Par2), const Arg2& a2, const Arg3& a3) {
  return
    lambda_functor_base<
      action<3, function_action<3, Result> >,
      typename detail::bind_tuple_mapper<
        Result(*)(Par1, Par2), const Arg2, const Arg3
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        Result(*)(Par1, Par2), const Arg2, const Arg3
      >::type
      (a1, a2, a3)
    );
}


 #endif 

// 4-argument bind functions --------------------------
#ifndef BOOST_REF_TO_FUNC_CONFLICTS_WITH_REF_TO_T
template <class Result, class Par1, class Par2, class Par3, class Arg2,
          class Arg3, class Arg4>
inline const
lambda_functor<
  lambda_functor_base<
    action<4, function_action<4, Result> >,
    typename detail::bind_tuple_mapper<
      Result(&)(Par1, Par2, Par3), const Arg2, const Arg3, const Arg4
    >::type
  >
>

bind(Result(&a1)(Par1, Par2, Par3), const Arg2& a2, const Arg3& a3,
     const Arg4& a4) {
  return
    lambda_functor_base<
      action<4, function_action<4, Result> >,
      typename detail::bind_tuple_mapper<
        Result(&)(Par1, Par2, Par3), const Arg2, const Arg3, const Arg4
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        Result(&)(Par1, Par2, Par3), const Arg2, const Arg3, const Arg4
      >::type
      (a1, a2, a3, a4)
    );
}
#endif

 #ifndef BOOST_LAMBDA_INCORRECT_BIND_OVERLOADING 
template <class Arg1, class Arg2, class Arg3, class Arg4>
inline const
lambda_functor<
  lambda_functor_base<
    action<4, function_action<4> >,
    typename detail::bind_tuple_mapper<
      const Arg1, const Arg2, const Arg3, const Arg4
    >::type
  >
>

bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4) {
  return
    lambda_functor_base<
      action<4, function_action<4> >,
      typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3, const Arg4
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3, const Arg4
      >::type
      (a1, a2, a3, a4)
    );
}

template <class Result, class Arg1, class Arg2, class Arg3, class Arg4>
inline const
lambda_functor<
  lambda_functor_base<
    action<4, function_action<4, Result> >,
    typename detail::bind_tuple_mapper<
      const Arg1, const Arg2, const Arg3, const Arg4
    >::type
  >
>

bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4) {
  return
    lambda_functor_base<
      action<4, function_action<4, Result> >,
      typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3, const Arg4
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3, const Arg4
      >::type
      (a1, a2, a3, a4)
    );
}


 #else 
template <class Arg1, class Arg2, class Arg3, class Arg4>
inline const
lambda_functor<
  lambda_functor_base<
    action<4, function_action<4> >,
    typename detail::bind_tuple_mapper<
      typename detail::constify_non_funcs<Arg1>::type, const Arg2, const Arg3,
      const Arg4
    >::type
  >
>

bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4) {
  return
    lambda_functor_base<
      action<4, function_action<4> >,
      typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3, const Arg4
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3, const Arg4
      >::type
      (a1, a2, a3, a4)
    );
}

template <class Result, class Arg1, class Arg2, class Arg3, class Arg4>
inline const
lambda_functor<
  lambda_functor_base<
    action<4, function_action<4, Result> >,
    typename detail::bind_tuple_mapper<
      typename detail::constify_non_funcs<Arg1>::type, const Arg2, const Arg3,
      const Arg4
    >::type
  >
>

bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4) {
  return
    lambda_functor_base<
      action<4, function_action<4, Result> >,
      typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3, const Arg4
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3, const Arg4
      >::type
      (a1, a2, a3, a4)
    );
}

template <class Result, class Par1, class Par2, class Par3, class Arg2,
          class Arg3, class Arg4>
inline const
lambda_functor<
  lambda_functor_base<
    action<4, function_action<4, Result> >,
    typename detail::bind_tuple_mapper<
      Result(*)(Par1, Par2, Par3), const Arg2, const Arg3, const Arg4
    >::type
  >
>

bind(Result(* const & a1)(Par1, Par2, Par3), const Arg2& a2,
     const Arg3& a3, const Arg4& a4) {
  return
    lambda_functor_base<
      action<4, function_action<4, Result> >,
      typename detail::bind_tuple_mapper<
        Result(*)(Par1, Par2, Par3), const Arg2, const Arg3, const Arg4
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        Result(*)(Par1, Par2, Par3), const Arg2, const Arg3, const Arg4
      >::type
      (a1, a2, a3, a4)
    );
}


 #endif 

// 5-argument bind functions --------------------------
#ifndef BOOST_REF_TO_FUNC_CONFLICTS_WITH_REF_TO_T
template <class Result, class Par1, class Par2, class Par3, class Par4,
          class Arg2, class Arg3, class Arg4, class Arg5>
inline const
lambda_functor<
  lambda_functor_base<
    action<5, function_action<5, Result> >,
    typename detail::bind_tuple_mapper<
      Result(&)(Par1, Par2, Par3, Par4), const Arg2, const Arg3, const Arg4,
      const Arg5
    >::type
  >
>

bind(Result(&a1)(Par1, Par2, Par3, Par4), const Arg2& a2, const Arg3& a3,
     const Arg4& a4, const Arg5& a5) {
  return
    lambda_functor_base<
      action<5, function_action<5, Result> >,
      typename detail::bind_tuple_mapper<
        Result(&)(Par1, Par2, Par3, Par4), const Arg2, const Arg3, const Arg4,
        const Arg5
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        Result(&)(Par1, Par2, Par3, Par4), const Arg2, const Arg3, const Arg4,
        const Arg5
      >::type
      (a1, a2, a3, a4, a5)
    );
}
#endif

 #ifndef BOOST_LAMBDA_INCORRECT_BIND_OVERLOADING 
template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
inline const
lambda_functor<
  lambda_functor_base<
    action<5, function_action<5> >,
    typename detail::bind_tuple_mapper<
      const Arg1, const Arg2, const Arg3, const Arg4, const Arg5
    >::type
  >
>

bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5) {
  return
    lambda_functor_base<
      action<5, function_action<5> >,
      typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3, const Arg4, const Arg5
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3, const Arg4, const Arg5
      >::type
      (a1, a2, a3, a4, a5)
    );
}

template <class Result, class Arg1, class Arg2, class Arg3, class Arg4,
          class Arg5>
inline const
lambda_functor<
  lambda_functor_base<
    action<5, function_action<5, Result> >,
    typename detail::bind_tuple_mapper<
      const Arg1, const Arg2, const Arg3, const Arg4, const Arg5
    >::type
  >
>

bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5) {
  return
    lambda_functor_base<
      action<5, function_action<5, Result> >,
      typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3, const Arg4, const Arg5
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3, const Arg4, const Arg5
      >::type
      (a1, a2, a3, a4, a5)
    );
}


 #else 
template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
inline const
lambda_functor<
  lambda_functor_base<
    action<5, function_action<5> >,
    typename detail::bind_tuple_mapper<
      typename detail::constify_non_funcs<Arg1>::type, const Arg2, const Arg3,
      const Arg4, const Arg5
    >::type
  >
>

bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5) {
  return
    lambda_functor_base<
      action<5, function_action<5> >,
      typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3, const Arg4, const Arg5
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3, const Arg4, const Arg5
      >::type
      (a1, a2, a3, a4, a5)
    );
}

template <class Result, class Arg1, class Arg2, class Arg3, class Arg4,
          class Arg5>
inline const
lambda_functor<
  lambda_functor_base<
    action<5, function_action<5, Result> >,
    typename detail::bind_tuple_mapper<
      typename detail::constify_non_funcs<Arg1>::type, const Arg2, const Arg3,
      const Arg4, const Arg5
    >::type
  >
>

bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5) {
  return
    lambda_functor_base<
      action<5, function_action<5, Result> >,
      typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3, const Arg4, const Arg5
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3, const Arg4, const Arg5
      >::type
      (a1, a2, a3, a4, a5)
    );
}

template <class Result, class Par1, class Par2, class Par3, class Par4,
          class Arg2, class Arg3, class Arg4, class Arg5>
inline const
lambda_functor<
  lambda_functor_base<
    action<5, function_action<5, Result> >,
    typename detail::bind_tuple_mapper<
      Result(*)(Par1, Par2, Par3, Par4), const Arg2, const Arg3, const Arg4,
      const Arg5
    >::type
  >
>

bind(Result(* const & a1)(Par1, Par2, Par3, Par4), const Arg2& a2,
     const Arg3& a3, const Arg4& a4, const Arg5& a5) {
  return
    lambda_functor_base<
      action<5, function_action<5, Result> >,
      typename detail::bind_tuple_mapper<
        Result(*)(Par1, Par2, Par3, Par4), const Arg2, const Arg3, const Arg4,
        const Arg5
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        Result(*)(Par1, Par2, Par3, Par4), const Arg2, const Arg3, const Arg4,
        const Arg5
      >::type
      (a1, a2, a3, a4, a5)
    );
}


 #endif 

// 6-argument bind functions --------------------------
#ifndef BOOST_REF_TO_FUNC_CONFLICTS_WITH_REF_TO_T
template <class Result, class Par1, class Par2, class Par3, class Par4,
          class Par5, class Arg2, class Arg3, class Arg4, class Arg5,
          class Arg6>
inline const
lambda_functor<
  lambda_functor_base<
    action<6, function_action<6, Result> >,
    typename detail::bind_tuple_mapper<
      Result(&)(Par1, Par2, Par3, Par4, Par5), const Arg2, const Arg3,
      const Arg4, const Arg5, const Arg6
    >::type
  >
>

bind(Result(&a1)(Par1, Par2, Par3, Par4, Par5), const Arg2& a2,
     const Arg3& a3, const Arg4& a4, const Arg5& a5, const Arg6& a6) {
  return
    lambda_functor_base<
      action<6, function_action<6, Result> >,
      typename detail::bind_tuple_mapper<
        Result(&)(Par1, Par2, Par3, Par4, Par5), const Arg2, const Arg3,
        const Arg4, const Arg5, const Arg6
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        Result(&)(Par1, Par2, Par3, Par4, Par5), const Arg2, const Arg3,
        const Arg4, const Arg5, const Arg6
      >::type
      (a1, a2, a3, a4, a5, a6)
    );
}
#endif

 #ifndef BOOST_LAMBDA_INCORRECT_BIND_OVERLOADING 
template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5,
          class Arg6>
inline const
lambda_functor<
  lambda_functor_base<
    action<6, function_action<6> >,
    typename detail::bind_tuple_mapper<
      const Arg1, const Arg2, const Arg3, const Arg4, const Arg5, const Arg6
    >::type
  >
>

bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5, const Arg6& a6) {
  return
    lambda_functor_base<
      action<6, function_action<6> >,
      typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3, const Arg4, const Arg5, const Arg6
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3, const Arg4, const Arg5, const Arg6
      >::type
      (a1, a2, a3, a4, a5, a6)
    );
}

template <class Result, class Arg1, class Arg2, class Arg3, class Arg4,
          class Arg5, class Arg6>
inline const
lambda_functor<
  lambda_functor_base<
    action<6, function_action<6, Result> >,
    typename detail::bind_tuple_mapper<
      const Arg1, const Arg2, const Arg3, const Arg4, const Arg5, const Arg6
    >::type
  >
>

bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5, const Arg6& a6) {
  return
    lambda_functor_base<
      action<6, function_action<6, Result> >,
      typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3, const Arg4, const Arg5, const Arg6
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3, const Arg4, const Arg5, const Arg6
      >::type
      (a1, a2, a3, a4, a5, a6)
    );
}


 #else 
template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5,
          class Arg6>
inline const
lambda_functor<
  lambda_functor_base<
    action<6, function_action<6> >,
    typename detail::bind_tuple_mapper<
      typename detail::constify_non_funcs<Arg1>::type, const Arg2, const Arg3,
      const Arg4, const Arg5, const Arg6
    >::type
  >
>

bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5, const Arg6& a6) {
  return
    lambda_functor_base<
      action<6, function_action<6> >,
      typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3, const Arg4, const Arg5, const Arg6
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3, const Arg4, const Arg5, const Arg6
      >::type
      (a1, a2, a3, a4, a5, a6)
    );
}

template <class Result, class Arg1, class Arg2, class Arg3, class Arg4,
          class Arg5, class Arg6>
inline const
lambda_functor<
  lambda_functor_base<
    action<6, function_action<6, Result> >,
    typename detail::bind_tuple_mapper<
      typename detail::constify_non_funcs<Arg1>::type, const Arg2, const Arg3,
      const Arg4, const Arg5, const Arg6
    >::type
  >
>

bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5, const Arg6& a6) {
  return
    lambda_functor_base<
      action<6, function_action<6, Result> >,
      typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3, const Arg4, const Arg5, const Arg6
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3, const Arg4, const Arg5, const Arg6
      >::type
      (a1, a2, a3, a4, a5, a6)
    );
}

template <class Result, class Par1, class Par2, class Par3, class Par4,
          class Par5, class Arg2, class Arg3, class Arg4, class Arg5,
          class Arg6>
inline const
lambda_functor<
  lambda_functor_base<
    action<6, function_action<6, Result> >,
    typename detail::bind_tuple_mapper<
      Result(*)(Par1, Par2, Par3, Par4, Par5), const Arg2, const Arg3,
      const Arg4, const Arg5, const Arg6
    >::type
  >
>

bind(Result(* const & a1)(Par1, Par2, Par3, Par4, Par5), const Arg2& a2,
     const Arg3& a3, const Arg4& a4, const Arg5& a5, const Arg6& a6) {
  return
    lambda_functor_base<
      action<6, function_action<6, Result> >,
      typename detail::bind_tuple_mapper<
        Result(*)(Par1, Par2, Par3, Par4, Par5), const Arg2, const Arg3,
        const Arg4, const Arg5, const Arg6
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        Result(*)(Par1, Par2, Par3, Par4, Par5), const Arg2, const Arg3,
        const Arg4, const Arg5, const Arg6
      >::type
      (a1, a2, a3, a4, a5, a6)
    );
}


 #endif 

// 7-argument bind functions --------------------------
#ifndef BOOST_REF_TO_FUNC_CONFLICTS_WITH_REF_TO_T
template <class Result, class Par1, class Par2, class Par3, class Par4,
          class Par5, class Par6, class Arg2, class Arg3, class Arg4,
          class Arg5, class Arg6, class Arg7>
inline const
lambda_functor<
  lambda_functor_base<
    action<7, function_action<7, Result> >,
    typename detail::bind_tuple_mapper<
      Result(&)(Par1, Par2, Par3, Par4, Par5, Par6), const Arg2, const Arg3,
      const Arg4, const Arg5, const Arg6, const Arg7
    >::type
  >
>

bind(Result(&a1)(Par1, Par2, Par3, Par4, Par5, Par6), const Arg2& a2,
     const Arg3& a3, const Arg4& a4, const Arg5& a5, const Arg6& a6,
     const Arg7& a7) {
  return
    lambda_functor_base<
      action<7, function_action<7, Result> >,
      typename detail::bind_tuple_mapper<
        Result(&)(Par1, Par2, Par3, Par4, Par5, Par6), const Arg2, const Arg3,
        const Arg4, const Arg5, const Arg6, const Arg7
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        Result(&)(Par1, Par2, Par3, Par4, Par5, Par6), const Arg2, const Arg3,
        const Arg4, const Arg5, const Arg6, const Arg7
      >::type
      (a1, a2, a3, a4, a5, a6, a7)
    );
}
#endif

 #ifndef BOOST_LAMBDA_INCORRECT_BIND_OVERLOADING 
template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5,
          class Arg6, class Arg7>
inline const
lambda_functor<
  lambda_functor_base<
    action<7, function_action<7> >,
    typename detail::bind_tuple_mapper<
      const Arg1, const Arg2, const Arg3, const Arg4, const Arg5, const Arg6,
      const Arg7
    >::type
  >
>

bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5, const Arg6& a6, const Arg7& a7) {
  return
    lambda_functor_base<
      action<7, function_action<7> >,
      typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3, const Arg4, const Arg5,
        const Arg6, const Arg7
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3, const Arg4, const Arg5,
        const Arg6, const Arg7
      >::type
      (a1, a2, a3, a4, a5, a6, a7)
    );
}

template <class Result, class Arg1, class Arg2, class Arg3, class Arg4,
          class Arg5, class Arg6, class Arg7>
inline const
lambda_functor<
  lambda_functor_base<
    action<7, function_action<7, Result> >,
    typename detail::bind_tuple_mapper<
      const Arg1, const Arg2, const Arg3, const Arg4, const Arg5, const Arg6,
      const Arg7
    >::type
  >
>

bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5, const Arg6& a6, const Arg7& a7) {
  return
    lambda_functor_base<
      action<7, function_action<7, Result> >,
      typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3, const Arg4, const Arg5,
        const Arg6, const Arg7
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3, const Arg4, const Arg5,
        const Arg6, const Arg7
      >::type
      (a1, a2, a3, a4, a5, a6, a7)
    );
}


 #else 
template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5,
          class Arg6, class Arg7>
inline const
lambda_functor<
  lambda_functor_base<
    action<7, function_action<7> >,
    typename detail::bind_tuple_mapper<
      typename detail::constify_non_funcs<Arg1>::type, const Arg2, const Arg3,
      const Arg4, const Arg5, const Arg6, const Arg7
    >::type
  >
>

bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5, const Arg6& a6, const Arg7& a7) {
  return
    lambda_functor_base<
      action<7, function_action<7> >,
      typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3, const Arg4, const Arg5, const Arg6, const Arg7
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3, const Arg4, const Arg5, const Arg6, const Arg7
      >::type
      (a1, a2, a3, a4, a5, a6, a7)
    );
}

template <class Result, class Arg1, class Arg2, class Arg3, class Arg4,
          class Arg5, class Arg6, class Arg7>
inline const
lambda_functor<
  lambda_functor_base<
    action<7, function_action<7, Result> >,
    typename detail::bind_tuple_mapper<
      typename detail::constify_non_funcs<Arg1>::type, const Arg2, const Arg3,
      const Arg4, const Arg5, const Arg6, const Arg7
    >::type
  >
>

bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5, const Arg6& a6, const Arg7& a7) {
  return
    lambda_functor_base<
      action<7, function_action<7, Result> >,
      typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3, const Arg4, const Arg5, const Arg6, const Arg7
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3, const Arg4, const Arg5, const Arg6, const Arg7
      >::type
      (a1, a2, a3, a4, a5, a6, a7)
    );
}

template <class Result, class Par1, class Par2, class Par3, class Par4,
          class Par5, class Par6, class Arg2, class Arg3, class Arg4,
          class Arg5, class Arg6, class Arg7>
inline const
lambda_functor<
  lambda_functor_base<
    action<7, function_action<7, Result> >,
    typename detail::bind_tuple_mapper<
      Result(*)(Par1, Par2, Par3, Par4, Par5, Par6), const Arg2, const Arg3,
      const Arg4, const Arg5, const Arg6, const Arg7
    >::type
  >
>

bind(Result(* const & a1)(Par1, Par2, Par3, Par4, Par5, Par6),
     const Arg2& a2, const Arg3& a3, const Arg4& a4, const Arg5& a5,
     const Arg6& a6, const Arg7& a7) {
  return
    lambda_functor_base<
      action<7, function_action<7, Result> >,
      typename detail::bind_tuple_mapper<
        Result(*)(Par1, Par2, Par3, Par4, Par5, Par6), const Arg2, const Arg3,
        const Arg4, const Arg5, const Arg6, const Arg7
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        Result(*)(Par1, Par2, Par3, Par4, Par5, Par6), const Arg2, const Arg3,
        const Arg4, const Arg5, const Arg6, const Arg7
      >::type
      (a1, a2, a3, a4, a5, a6, a7)
    );
}


 #endif 

// 8-argument bind functions --------------------------
#ifndef BOOST_REF_TO_FUNC_CONFLICTS_WITH_REF_TO_T
template <class Result, class Par1, class Par2, class Par3, class Par4,
          class Par5, class Par6, class Par7, class Arg2, class Arg3,
          class Arg4, class Arg5, class Arg6, class Arg7, class Arg8>
inline const
lambda_functor<
  lambda_functor_base<
    action<8, function_action<8, Result> >,
    typename detail::bind_tuple_mapper<
      Result(&)(Par1, Par2, Par3, Par4, Par5, Par6, Par7), const Arg2,
      const Arg3, const Arg4, const Arg5, const Arg6, const Arg7, const Arg8
    >::type
  >
>

bind(Result(&a1)(Par1, Par2, Par3, Par4, Par5, Par6, Par7), const Arg2& a2,
     const Arg3& a3, const Arg4& a4, const Arg5& a5, const Arg6& a6,
     const Arg7& a7, const Arg8& a8) {
  return
    lambda_functor_base<
      action<8, function_action<8, Result> >,
      typename detail::bind_tuple_mapper<
        Result(&)(Par1, Par2, Par3, Par4, Par5, Par6, Par7), const Arg2,
        const Arg3, const Arg4, const Arg5, const Arg6, const Arg7, const Arg8
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        Result(&)(Par1, Par2, Par3, Par4, Par5, Par6, Par7), const Arg2,
        const Arg3, const Arg4, const Arg5, const Arg6, const Arg7, const Arg8
      >::type
      (a1, a2, a3, a4, a5, a6, a7, a8)
    );
}
#endif

 #ifndef BOOST_LAMBDA_INCORRECT_BIND_OVERLOADING 
template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5,
          class Arg6, class Arg7, class Arg8>
inline const
lambda_functor<
  lambda_functor_base<
    action<8, function_action<8> >,
    typename detail::bind_tuple_mapper<
      const Arg1, const Arg2, const Arg3, const Arg4, const Arg5, const Arg6,
      const Arg7, const Arg8
    >::type
  >
>

bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5, const Arg6& a6, const Arg7& a7, const Arg8& a8) {
  return
    lambda_functor_base<
      action<8, function_action<8> >,
      typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3, const Arg4, const Arg5,
        const Arg6, const Arg7, const Arg8
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3, const Arg4, const Arg5,
        const Arg6, const Arg7, const Arg8
      >::type
      (a1, a2, a3, a4, a5, a6, a7, a8)
    );
}

template <class Result, class Arg1, class Arg2, class Arg3, class Arg4,
          class Arg5, class Arg6, class Arg7, class Arg8>
inline const
lambda_functor<
  lambda_functor_base<
    action<8, function_action<8, Result> >,
    typename detail::bind_tuple_mapper<
      const Arg1, const Arg2, const Arg3, const Arg4, const Arg5, const Arg6,
      const Arg7, const Arg8
    >::type
  >
>

bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5, const Arg6& a6, const Arg7& a7, const Arg8& a8) {
  return
    lambda_functor_base<
      action<8, function_action<8, Result> >,
      typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3, const Arg4, const Arg5,
        const Arg6, const Arg7, const Arg8
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3, const Arg4, const Arg5,
        const Arg6, const Arg7, const Arg8
      >::type
      (a1, a2, a3, a4, a5, a6, a7, a8)
    );
}


 #else 
template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5,
          class Arg6, class Arg7, class Arg8>
inline const
lambda_functor<
  lambda_functor_base<
    action<8, function_action<8> >,
    typename detail::bind_tuple_mapper<
      typename detail::constify_non_funcs<Arg1>::type, const Arg2, const Arg3,
      const Arg4, const Arg5, const Arg6, const Arg7, const Arg8
    >::type
  >
>

bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5, const Arg6& a6, const Arg7& a7, const Arg8& a8) {
  return
    lambda_functor_base<
      action<8, function_action<8> >,
      typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3, const Arg4, const Arg5, const Arg6, const Arg7, const Arg8
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3, const Arg4, const Arg5, const Arg6, const Arg7, const Arg8
      >::type
      (a1, a2, a3, a4, a5, a6, a7, a8)
    );
}

template <class Result, class Arg1, class Arg2, class Arg3, class Arg4,
          class Arg5, class Arg6, class Arg7, class Arg8>
inline const
lambda_functor<
  lambda_functor_base<
    action<8, function_action<8, Result> >,
    typename detail::bind_tuple_mapper<
      typename detail::constify_non_funcs<Arg1>::type, const Arg2, const Arg3,
      const Arg4, const Arg5, const Arg6, const Arg7, const Arg8
    >::type
  >
>

bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5, const Arg6& a6, const Arg7& a7, const Arg8& a8) {
  return
    lambda_functor_base<
      action<8, function_action<8, Result> >,
      typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3, const Arg4, const Arg5, const Arg6, const Arg7, const Arg8
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3, const Arg4, const Arg5, const Arg6, const Arg7, const Arg8
      >::type
      (a1, a2, a3, a4, a5, a6, a7, a8)
    );
}

template <class Result, class Par1, class Par2, class Par3, class Par4,
          class Par5, class Par6, class Par7, class Arg2, class Arg3,
          class Arg4, class Arg5, class Arg6, class Arg7, class Arg8>
inline const
lambda_functor<
  lambda_functor_base<
    action<8, function_action<8, Result> >,
    typename detail::bind_tuple_mapper<
      Result(*)(Par1, Par2, Par3, Par4, Par5, Par6, Par7), const Arg2,
      const Arg3, const Arg4, const Arg5, const Arg6, const Arg7, const Arg8
    >::type
  >
>

bind(Result(* const & a1)(Par1, Par2, Par3, Par4, Par5, Par6, Par7),
     const Arg2& a2, const Arg3& a3, const Arg4& a4, const Arg5& a5,
     const Arg6& a6, const Arg7& a7, const Arg8& a8) {
  return
    lambda_functor_base<
      action<8, function_action<8, Result> >,
      typename detail::bind_tuple_mapper<
        Result(*)(Par1, Par2, Par3, Par4, Par5, Par6, Par7), const Arg2,
        const Arg3, const Arg4, const Arg5, const Arg6, const Arg7, const Arg8
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        Result(*)(Par1, Par2, Par3, Par4, Par5, Par6, Par7), const Arg2,
        const Arg3, const Arg4, const Arg5, const Arg6, const Arg7, const Arg8
      >::type
      (a1, a2, a3, a4, a5, a6, a7, a8)
    );
}


 #endif 

// 9-argument bind functions --------------------------
#ifndef BOOST_REF_TO_FUNC_CONFLICTS_WITH_REF_TO_T
template <class Result, class Par1, class Par2, class Par3, class Par4,
          class Par5, class Par6, class Par7, class Par8, class Arg2,
          class Arg3, class Arg4, class Arg5, class Arg6, class Arg7,
          class Arg8, class Arg9>
inline const
lambda_functor<
  lambda_functor_base<
    action<9, function_action<9, Result> >,
    typename detail::bind_tuple_mapper<
      Result(&)(Par1, Par2, Par3, Par4, Par5, Par6, Par7, Par8), const Arg2,
      const Arg3, const Arg4, const Arg5, const Arg6, const Arg7, const Arg8,
      const Arg9
    >::type
  >
>

bind(Result(&a1)(Par1, Par2, Par3, Par4, Par5, Par6, Par7, Par8),
     const Arg2& a2, const Arg3& a3, const Arg4& a4, const Arg5& a5,
     const Arg6& a6, const Arg7& a7, const Arg8& a8, const Arg9& a9) {
  return
    lambda_functor_base<
      action<9, function_action<9, Result> >,
      typename detail::bind_tuple_mapper<
        Result(&)(Par1, Par2, Par3, Par4, Par5, Par6, Par7, Par8), const Arg2,
        const Arg3, const Arg4, const Arg5, const Arg6, const Arg7,
        const Arg8, const Arg9
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        Result(&)(Par1, Par2, Par3, Par4, Par5, Par6, Par7, Par8), const Arg2,
        const Arg3, const Arg4, const Arg5, const Arg6, const Arg7,
        const Arg8, const Arg9
      >::type
      (a1, a2, a3, a4, a5, a6, a7, a8, a9)
    );
}
#endif

 #ifndef BOOST_LAMBDA_INCORRECT_BIND_OVERLOADING 
template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5,
          class Arg6, class Arg7, class Arg8, class Arg9>
inline const
lambda_functor<
  lambda_functor_base<
    action<9, function_action<9> >,
    typename detail::bind_tuple_mapper<
      const Arg1, const Arg2, const Arg3, const Arg4, const Arg5, const Arg6,
      const Arg7, const Arg8, const Arg9
    >::type
  >
>

bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5, const Arg6& a6, const Arg7& a7, const Arg8& a8,
     const Arg9& a9) {
  return
    lambda_functor_base<
      action<9, function_action<9> >,
      typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3, const Arg4, const Arg5,
        const Arg6, const Arg7, const Arg8, const Arg9
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3, const Arg4, const Arg5,
        const Arg6, const Arg7, const Arg8, const Arg9
      >::type
      (a1, a2, a3, a4, a5, a6, a7, a8, a9)
    );
}

template <class Result, class Arg1, class Arg2, class Arg3, class Arg4,
          class Arg5, class Arg6, class Arg7, class Arg8, class Arg9>
inline const
lambda_functor<
  lambda_functor_base<
    action<9, function_action<9, Result> >,
    typename detail::bind_tuple_mapper<
      const Arg1, const Arg2, const Arg3, const Arg4, const Arg5, const Arg6,
      const Arg7, const Arg8, const Arg9
    >::type
  >
>

bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5, const Arg6& a6, const Arg7& a7, const Arg8& a8,
     const Arg9& a9) {
  return
    lambda_functor_base<
      action<9, function_action<9, Result> >,
      typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3, const Arg4, const Arg5,
        const Arg6, const Arg7, const Arg8, const Arg9
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3, const Arg4, const Arg5,
        const Arg6, const Arg7, const Arg8, const Arg9
      >::type
      (a1, a2, a3, a4, a5, a6, a7, a8, a9)
    );
}


 #else 
template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5,
          class Arg6, class Arg7, class Arg8, class Arg9>
inline const
lambda_functor<
  lambda_functor_base<
    action<9, function_action<9> >,
    typename detail::bind_tuple_mapper<
      typename detail::constify_non_funcs<Arg1>::type, const Arg2, const Arg3,
      const Arg4, const Arg5, const Arg6, const Arg7, const Arg8, const Arg9
    >::type
  >
>

bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5, const Arg6& a6, const Arg7& a7, const Arg8& a8,
     const Arg9& a9) {
  return
    lambda_functor_base<
      action<9, function_action<9> >,
      typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3, const Arg4, const Arg5, const Arg6, const Arg7,
        const Arg8, const Arg9
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3, const Arg4, const Arg5, const Arg6, const Arg7,
        const Arg8, const Arg9
      >::type
      (a1, a2, a3, a4, a5, a6, a7, a8, a9)
    );
}

template <class Result, class Arg1, class Arg2, class Arg3, class Arg4,
          class Arg5, class Arg6, class Arg7, class Arg8, class Arg9>
inline const
lambda_functor<
  lambda_functor_base<
    action<9, function_action<9, Result> >,
    typename detail::bind_tuple_mapper<
      typename detail::constify_non_funcs<Arg1>::type, const Arg2, const Arg3,
      const Arg4, const Arg5, const Arg6, const Arg7, const Arg8, const Arg9
    >::type
  >
>

bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5, const Arg6& a6, const Arg7& a7, const Arg8& a8,
     const Arg9& a9) {
  return
    lambda_functor_base<
      action<9, function_action<9, Result> >,
      typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3, const Arg4, const Arg5, const Arg6, const Arg7,
        const Arg8, const Arg9
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3, const Arg4, const Arg5, const Arg6, const Arg7,
        const Arg8, const Arg9
      >::type
      (a1, a2, a3, a4, a5, a6, a7, a8, a9)
    );
}

template <class Result, class Par1, class Par2, class Par3, class Par4,
          class Par5, class Par6, class Par7, class Par8, class Arg2,
          class Arg3, class Arg4, class Arg5, class Arg6, class Arg7,
          class Arg8, class Arg9>
inline const
lambda_functor<
  lambda_functor_base<
    action<9, function_action<9, Result> >,
    typename detail::bind_tuple_mapper<
      Result(*)(Par1, Par2, Par3, Par4, Par5, Par6, Par7, Par8), const Arg2,
      const Arg3, const Arg4, const Arg5, const Arg6, const Arg7, const Arg8,
      const Arg9
    >::type
  >
>

bind(Result(* const & a1)(Par1, Par2, Par3, Par4, Par5, Par6, Par7, Par8),
     const Arg2& a2, const Arg3& a3, const Arg4& a4, const Arg5& a5,
     const Arg6& a6, const Arg7& a7, const Arg8& a8, const Arg9& a9) {
  return
    lambda_functor_base<
      action<9, function_action<9, Result> >,
      typename detail::bind_tuple_mapper<
        Result(*)(Par1, Par2, Par3, Par4, Par5, Par6, Par7, Par8), const Arg2,
        const Arg3, const Arg4, const Arg5, const Arg6, const Arg7,
        const Arg8, const Arg9
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        Result(*)(Par1, Par2, Par3, Par4, Par5, Par6, Par7, Par8), const Arg2,
        const Arg3, const Arg4, const Arg5, const Arg6, const Arg7,
        const Arg8, const Arg9
      >::type
      (a1, a2, a3, a4, a5, a6, a7, a8, a9)
    );
}


 #endif 

// 10-argument bind functions --------------------------
#ifndef BOOST_REF_TO_FUNC_CONFLICTS_WITH_REF_TO_T
template <class Result, class Par1, class Par2, class Par3, class Par4,
          class Par5, class Par6, class Par7, class Par8, class Par9,
          class Arg2, class Arg3, class Arg4, class Arg5, class Arg6,
          class Arg7, class Arg8, class Arg9, class Arg10>
inline const
lambda_functor<
  lambda_functor_base<
    action<10, function_action<10, Result> >,
    typename detail::bind_tuple_mapper<
      Result(&)(Par1, Par2, Par3, Par4, Par5, Par6, Par7, Par8, Par9),
      const Arg2, const Arg3, const Arg4, const Arg5, const Arg6, const Arg7,
      const Arg8, const Arg9, const Arg10
    >::type
  >
>

bind(Result(&a1)(Par1, Par2, Par3, Par4, Par5, Par6, Par7, Par8, Par9),
     const Arg2& a2, const Arg3& a3, const Arg4& a4, const Arg5& a5,
     const Arg6& a6, const Arg7& a7, const Arg8& a8, const Arg9& a9,
     const Arg10& a10) {
  return
    lambda_functor_base<
      action<10, function_action<10, Result> >,
      typename detail::bind_tuple_mapper<
        Result(&)(Par1, Par2, Par3, Par4, Par5, Par6, Par7, Par8, Par9),
        const Arg2, const Arg3, const Arg4, const Arg5, const Arg6,
        const Arg7, const Arg8, const Arg9, const Arg10
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        Result(&)(Par1, Par2, Par3, Par4, Par5, Par6, Par7, Par8, Par9),
        const Arg2, const Arg3, const Arg4, const Arg5, const Arg6,
        const Arg7, const Arg8, const Arg9, const Arg10
      >::type
      (a1, a2, a3, a4, a5, a6, a7, a8, a9, a10)
    );
}
#endif

 #ifndef BOOST_LAMBDA_INCORRECT_BIND_OVERLOADING 
template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5,
          class Arg6, class Arg7, class Arg8, class Arg9, class Arg10>
inline const
lambda_functor<
  lambda_functor_base<
    action<10, function_action<10> >,
    typename detail::bind_tuple_mapper<
      const Arg1, const Arg2, const Arg3, const Arg4, const Arg5, const Arg6,
      const Arg7, const Arg8, const Arg9, const Arg10
    >::type
  >
>

bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5, const Arg6& a6, const Arg7& a7, const Arg8& a8,
     const Arg9& a9, const Arg10& a10) {
  return
    lambda_functor_base<
      action<10, function_action<10> >,
      typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3, const Arg4, const Arg5,
        const Arg6, const Arg7, const Arg8, const Arg9, const Arg10
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3, const Arg4, const Arg5,
        const Arg6, const Arg7, const Arg8, const Arg9, const Arg10
      >::type
      (a1, a2, a3, a4, a5, a6, a7, a8, a9, a10)
    );
}

template <class Result, class Arg1, class Arg2, class Arg3, class Arg4,
          class Arg5, class Arg6, class Arg7, class Arg8, class Arg9,
          class Arg10>
inline const
lambda_functor<
  lambda_functor_base<
    action<10, function_action<10, Result> >,
    typename detail::bind_tuple_mapper<
      const Arg1, const Arg2, const Arg3, const Arg4, const Arg5, const Arg6,
      const Arg7, const Arg8, const Arg9, const Arg10
    >::type
  >
>

bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5, const Arg6& a6, const Arg7& a7, const Arg8& a8,
     const Arg9& a9, const Arg10& a10) {
  return
    lambda_functor_base<
      action<10, function_action<10, Result> >,
      typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3, const Arg4, const Arg5,
        const Arg6, const Arg7, const Arg8, const Arg9, const Arg10
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        const Arg1, const Arg2, const Arg3, const Arg4, const Arg5,
        const Arg6, const Arg7, const Arg8, const Arg9, const Arg10
      >::type
      (a1, a2, a3, a4, a5, a6, a7, a8, a9, a10)
    );
}


 #else 
template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5,
          class Arg6, class Arg7, class Arg8, class Arg9, class Arg10>
inline const
lambda_functor<
  lambda_functor_base<
    action<10, function_action<10> >,
    typename detail::bind_tuple_mapper<
      typename detail::constify_non_funcs<Arg1>::type, const Arg2, const Arg3,
      const Arg4, const Arg5, const Arg6, const Arg7, const Arg8, const Arg9,
      const Arg10
    >::type
  >
>

bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5, const Arg6& a6, const Arg7& a7, const Arg8& a8,
     const Arg9& a9, const Arg10& a10) {
  return
    lambda_functor_base<
      action<10, function_action<10> >,
      typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3, const Arg4, const Arg5, const Arg6, const Arg7,
        const Arg8, const Arg9, const Arg10
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3, const Arg4, const Arg5, const Arg6, const Arg7,
        const Arg8, const Arg9, const Arg10
      >::type
      (a1, a2, a3, a4, a5, a6, a7, a8, a9, a10)
    );
}

template <class Result, class Arg1, class Arg2, class Arg3, class Arg4,
          class Arg5, class Arg6, class Arg7, class Arg8, class Arg9,
          class Arg10>
inline const
lambda_functor<
  lambda_functor_base<
    action<10, function_action<10, Result> >,
    typename detail::bind_tuple_mapper<
      typename detail::constify_non_funcs<Arg1>::type, const Arg2, const Arg3,
      const Arg4, const Arg5, const Arg6, const Arg7, const Arg8, const Arg9,
      const Arg10
    >::type
  >
>

bind(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4,
     const Arg5& a5, const Arg6& a6, const Arg7& a7, const Arg8& a8,
     const Arg9& a9, const Arg10& a10) {
  return
    lambda_functor_base<
      action<10, function_action<10, Result> >,
      typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3, const Arg4, const Arg5, const Arg6, const Arg7,
        const Arg8, const Arg9, const Arg10
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        typename detail::constify_non_funcs<Arg1>::type, const Arg2,
        const Arg3, const Arg4, const Arg5, const Arg6, const Arg7,
        const Arg8, const Arg9, const Arg10
      >::type
      (a1, a2, a3, a4, a5, a6, a7, a8, a9, a10)
    );
}

template <class Result, class Par1, class Par2, class Par3, class Par4,
          class Par5, class Par6, class Par7, class Par8, class Par9,
          class Arg2, class Arg3, class Arg4, class Arg5, class Arg6,
          class Arg7, class Arg8, class Arg9, class Arg10>
inline const
lambda_functor<
  lambda_functor_base<
    action<10, function_action<10, Result> >,
    typename detail::bind_tuple_mapper<
      Result(*)(Par1, Par2, Par3, Par4, Par5, Par6, Par7, Par8, Par9),
      const Arg2, const Arg3, const Arg4, const Arg5, const Arg6, const Arg7,
      const Arg8, const Arg9, const Arg10
    >::type
  >
>

bind(Result(* const & a1)(Par1, Par2, Par3, Par4, Par5, Par6, Par7, Par8,
     Par9), const Arg2& a2, const Arg3& a3, const Arg4& a4, const Arg5& a5,
     const Arg6& a6, const Arg7& a7, const Arg8& a8, const Arg9& a9,
     const Arg10& a10) {
  return
    lambda_functor_base<
      action<10, function_action<10, Result> >,
      typename detail::bind_tuple_mapper<
        Result(*)(Par1, Par2, Par3, Par4, Par5, Par6, Par7, Par8, Par9),
        const Arg2, const Arg3, const Arg4, const Arg5, const Arg6,
        const Arg7, const Arg8, const Arg9, const Arg10
      >::type
    >
    ( typename detail::bind_tuple_mapper<
        Result(*)(Par1, Par2, Par3, Par4, Par5, Par6, Par7, Par8, Par9),
        const Arg2, const Arg3, const Arg4, const Arg5, const Arg6,
        const Arg7, const Arg8, const Arg9, const Arg10
      >::type
      (a1, a2, a3, a4, a5, a6, a7, a8, a9, a10)
    );
}


 #endif 

} // namespace lambda 
} // namespace boost

#endif

/* bind_functions.hpp
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
*/