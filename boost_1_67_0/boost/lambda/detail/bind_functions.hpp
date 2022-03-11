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