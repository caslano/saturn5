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
hHht2EieKzXm1U2ptgEZ/FxVaWJindfh+9vDl1z+mRPkp23eiIGQwzQVcnTfDm9EklwVoVzLa14bf9NsUDYBqdW5ynVAYs4riZAsqvOSH2gg/kXOjQmwP4ZNoviz8Dn3PhcqpyA0A3qC2jPFM/wTWbOgxk30cThHltnAfYYvmfVyqitaUyiXtRNpzaHwOdv60qV3IWy4qaLgQnQEB9kjtq5TVubo3ZcxXbg4sxJ0w03x2RoXuoJ22pSXkkGe4Sy8XkT6btMP+4QwKkS+WoGz6UYrtt10ycAPSRFZSbBOgGSvy2inJTmTRIFSpz82riEJ+tPTeEmOkHQaCoE07XSIzY3+X9lTiMn2TQDyKyQUJsx3HifXDuN9cz7RhQ3DQJeTrO6YbNB6LUS6X9LDGXkkLQBGbr2Ad0Aq8+12SnsCzPm1NY8LgxDA8+phYOr1rPK51zJMHrlwgGZ/j9zDdkci3XhgrhacS7dy2y0ck8i/VCnXqUQspP25Snlmgpk80k0dKaUMx7uVjoCGccJRrCwUm1zpoN2IGVONB7t2mGdDG1KaWoQQNkeJkGVC5kt2Fj6D151ei8HoCOBCsIkpzad98WF8gvJfiMrXt0jvbqSzgikBnN5DECAN+xreGZTi8Asxw6/FBJug7886T0UC+04UHroDqhUkP15SwoDY57nRSLo/q7oD9kdMxP8sUs72H+qp/Rup3/zzo22Hv5L6
*/