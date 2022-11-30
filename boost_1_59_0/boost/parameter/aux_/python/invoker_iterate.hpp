// Copyright Daniel Wallin 2005. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

#define N BOOST_PP_ITERATION()

#define BOOST_PARAMETER_PY_ARG_TYPES(z, n, _) \
    typedef typename mpl::next< \
        BOOST_PP_CAT(iter,BOOST_PP_DEC(n)) \
    >::type BOOST_PP_CAT(iter,n); \
    \
    typedef typename mpl::deref<BOOST_PP_CAT(iter,n)>::type BOOST_PP_CAT(spec,n); \
    typedef typename mpl::if_< \
        mpl::and_< \
            mpl::not_<typename BOOST_PP_CAT(spec,n)::required> \
          , typename BOOST_PP_CAT(spec,n)::optimized_default \
        > \
      , parameter::aux::maybe<typename BOOST_PP_CAT(spec,n)::type> \
      , typename BOOST_PP_CAT(spec,n)::type \
    >::type BOOST_PP_CAT(arg,n); \
    typedef typename BOOST_PP_CAT(spec,n)::keyword BOOST_PP_CAT(kw,n);

#if BOOST_PP_ITERATION_FLAGS() == 1
template <class M, class R, class Args>
struct invoker<N, M, R, Args>
#elif BOOST_PP_ITERATION_FLAGS() == 2
template <class T, class R, class Args>
struct call_invoker<N, T, R, Args>
#elif BOOST_PP_ITERATION_FLAGS() == 3
template <class T, class Args>
struct init_invoker<N, T, Args>
#elif BOOST_PP_ITERATION_FLAGS() == 4
template <class M, class R, class T, class Args>
struct member_invoker<N, M, R, T, Args>
#endif
{
    typedef typename mpl::begin<Args>::type iter0;
    typedef typename mpl::deref<iter0>::type spec0;
    typedef typename mpl::if_<
        mpl::and_<
            mpl::not_<typename spec0::required>
          , typename spec0::optimized_default
        >
      , parameter::aux::maybe<typename spec0::type>
      , typename spec0::type
    >::type arg0;
    typedef typename spec0::keyword kw0;

    BOOST_PP_REPEAT_FROM_TO(1, N, BOOST_PARAMETER_PY_ARG_TYPES, ~)

    static
#if BOOST_PP_ITERATION_FLAGS() == 3
    T*
#else
    R
#endif 
    execute(
#if BOOST_PP_ITERATION_FLAGS() == 2 || BOOST_PP_ITERATION_FLAGS() == 4
        T& self
      ,
#endif
        BOOST_PP_ENUM_BINARY_PARAMS(N, arg, a)
    )
    {
        return
#if BOOST_PP_ITERATION_FLAGS() == 1 || BOOST_PP_ITERATION_FLAGS() == 4
         M()(
              boost::type<R>()
# if BOOST_PP_ITERATION_FLAGS() == 4
            , self
# endif
            , BOOST_PP_ENUM_BINARY_PARAMS(N, parameter::keyword<kw, >::get() = a)
         );
#elif BOOST_PP_ITERATION_FLAGS() == 2
         self(
            BOOST_PP_ENUM_BINARY_PARAMS(N, parameter::keyword<kw, >::get() = a)
         );
#elif BOOST_PP_ITERATION_FLAGS() == 3
         new T(
             BOOST_PP_ENUM_BINARY_PARAMS(N, parameter::keyword<kw, >::get() = a)
         );
#endif
    }
};

#undef BOOST_PARAMETER_PY_ARG_TYPES
#undef N


/* invoker_iterate.hpp
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
*/