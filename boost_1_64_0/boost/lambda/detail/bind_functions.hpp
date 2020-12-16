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
8eplq71f27iPSPxfG98pt/jHin+W+Mu36iX8j5gX+PoMu35jyzzQbOFrYrRWr2t3F+gecW9ktFK7OUdkiPsjUo8d1eaImHaWd87HAdwgfA18bfja3h4r8S8xVqpxorNwU8vitssIUSvVW2jUDuNuZWOvFxkvEt76RhO1X+9RmRhtmVuqw1r2z/5NNnmEl7pVKPGyzlGGk7XY5lu0MeeYfnz+2ttzd/e5+KavyheeaDq8pcwxofKyPrL/4vdaJKzIzLPbmgNbce16f84tDaGtfiTPeBpLW/19wDiuZe8A/JRnmFVwLfvXwAuAJ3iWWX0kPhgYDhwCjAReCOxOW31fYHfgQGBPM13a7O+w2Oz7Ad8BJgHLgf2BHwIHAD8GJgOPAi8FOh2V6TUADvGx9cf557f8l//yX/7Lf/kv/+W/fpHrFxr/T8o6R/b/bIv9fwcHDftdiIW4xNz/f0SP/82Ube3/1rFJvc9M/iznNerPDu/e4XckjgTDu+Y66Kj5fLHDu7Y973Oxkeu9xc9LHL25Rlv7258vcMR23kCP37seM/2jjPrgvkMN0Xb5jeI+kWli7CQy7dP7iS8S/1kYg7j0Ovm9ktY9rijHBFvZm5hyyHNn7oXQ/nbzD5Tdfv4hypRf86x2Fam3ja2OPSrcNUTHQX+bdRE28w92utLj0v6yTtojOkh0lBmzOFbFJW6XOSZadPNniec+V3vHGJaxzqftfAXStZ9rYNqRmmepY6Z6z9DzFJawHMfjKjQrnB6DW+YH9Br5AKk/QXq+oNmn5vMRrL1+WpdliuQryzhfPcd65q13vchjqJnC86rhUiuMRiyPNhLXFNfbRorDrGPHIYPwQe7XlAuj8jst4/biGbO6VJ1x0FL4OjjW4rTsC41nVSPu/Rgl7r0cJ41YhmU+E5Sur+lSH1vrdSepIsdgncdGIvt452PqVod3H87NEu868jB/aJe9VBF5mEezjjMv10k6YcYbqposaFQJWpZdEiZBNacsn0oZPeBKU+nqLgNxOR4zmroG6/3/AZ+zPJjfYJF9getL6LB6Gl30HNYmkeNi1Q4l3QXUmGl/IWk1cKSj7UYZC7Q+3haZLlVR3PtxTMLfh5A4KwLUSqUpbxnuEL+d2PURq+vf+SLTNNd7lEmXX4LSaTeTNC5wbFDd0Js9p8P2E/dhjoYOn/LrUtUvTpD4L3ImqwpHI8qcLXIkmV9a0u0tVMoozfmEWY5sb6US/+PkqSrH3qqQPN5y9Oi2vFrirlCbkEd+U5BzRNXnisJrnitCXjwmsG1XPQ/lcyPlDlOV962HDruwi6LbyWPaLcHrVqHduvb2uh2rcuvldfukyq2n1+1AlVsPr9tbVW7dvW67q9y6ed3Gf6bdunrdUqrctMwDq9y0zEnarYuWuWeVm5a5U5WblrlVlZuWuXmVW3d1DubiTN5Qn/VfvvNwiuEj6zDnBgGqrRdbxu/z/hCIugL8O3ChaRP4wrImkLHVN+u9/Kdk6374feEL0f3G49/KvK5eKxhfIfOY9vaAL3z/13jWDeOKkbAFgd6+7ivhDxL7QJAOn2r9v7XGyTZalCeVnfJO+lLmYN1hkLErWs7XwHBjk9prtFAngM84Wqh9jhfVBmcLtcv5F7XBBXQB3S10Oz8laTwZGAvZvG16m8g6CPkM0P31QnFrp5qizY6hPnqIW+/Ai+A2CLN9d2DF3ACji5prBKgjhkd9a6SqNMfDKtDZUz3m9KjfO1NRzs+oA66+apXbox5xZ6qogOfUgYBLVMdAjxpI3bgkX8MCeiPey1SOehL94lijp/oBcQY7UlUB4oxGnH9GnO85M9VQ13MqxN1X/dmNZ8QJnUo9mSbx3CA=
*/