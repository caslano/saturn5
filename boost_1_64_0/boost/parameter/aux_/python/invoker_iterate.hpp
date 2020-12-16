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
F58g2dfmJPBhSL/j/y7OW/5inu+RfuX/fyIxFhHXMsS8EJ+lxyL6DhMM+/h7cDl4GViW24/lxniU+4Pl/gSvBvb7esodxXLFHuWWsNwn4OHgTymvDulMpRzaSZ0dHMZ8bfI5Lp8xdyENQ5rNfFtz3922jFE1DTyKMbhqwTuB1wbPAG/C4y3BuzGG2SzG0NqFMZkOks8WwRMpbyhSE+WNprwx4GHg1Sl3M8ZmWouxzerBY8DjKH8CuEHkk+3ncz8+D0QZtf0YC06++UiTmW9T6hNEihkAY7LZfDpjRJ3F9w9dTr3OYQyr86jPBeA1eDwefBl4AvM3gC+inXDs2v9wyl/fw/7zCxz5C8BD7bzgEvCR4FLw0eA68LHgNcEng9cCnwCuB58EHsfzcjzdTnkllKeOpzjlJcDF4E6w7LdHWG51j367k+Xupp73cDwuAgfB94FHgR8A14AfBI8GPwyuZT65D3Qp5RR77AN9jHKeANvnnwQPAz9FOU+znll89uKOs4xYZAfyugnxOm0Fj2YMsjV4PBZ8MLgBPJf1Tjf4LIP3ii7OjbeS46WA44V2OBM8Enwh238O++lCpT/Cy9lej/64hPXdAi4C3wqW4/YQlpvsMW7v43V0P8ftg+BS8MO8fh/l9fs4uA78PL9Tn2IsvGfAExlDblPGjtuc+Wz5t8t5OfhGyq9AWmhwbgA9C8HrgUeA1wdXgTfk+JwInmDbErwteEtwI3hr8B7gaeB9wDuB9+fxgTyO8DjJ46PB08HngXcBXwqeCb4CvCv4GvAE2q1Dzlk5N+7iWmYz9d6X1/Vs2isC3ho8lzH3YuBZ4HbGRkyB92MMQBN8OBjJOBp8AvhYg+NazsvAYzzG9VXsr6sp/zruc76Z+5xvMTj+3PkObOwx/l5iPa+z/DuMNfkueCz4fcbW+4D17SvnHZy/dLkxKwlxnYDAFeAh4EoeV4P94DE8PxY8HDwZPEK5Dt9g/Q0e1+GqrL+G18do3h/W5vdgLe9va4E3Eud53cjfjuBRHtdNOeutoN6V4OuR+YSA390jfhX+V+P2PY3jH5HqhviNqUgxpMuQHlzq7CF/Ef93I32L48Bn2BteiPJIqv/+1EL/gPvLD0Ie6cc/G/V0/+HsMT8C55eALwOrfv0LkYe+/Wnx/rqRpF//7Sij+vUvwjFj/Ll70F/EORnf752lfcf4W4J8apy/wCr+NL//ahynDoB+4Dak65FeRQoW+Y0NkGYjzUdaiPQqUtFQvzEJqQ3pIqTHkZYhjR4GHZFOQLodaTHSt0jB4X5DQ0NDQ0NDQ0NDQ+P/h9zv/+9EFhH4z9n9/w/3ANg+8cOrDNfnobTAEJAzEB/9sd4rDNB3RIoPwQ0tFE73gBh4zUL1UzmmD1kf9iUr0/ssi5h9qrxv+5C3ZGB5zeYKyLve11ve0tWR+pCXuWos1+sw10f+kJ2pPRxT149Yl1w/ykK/SqNM5JuAVKnUqfqAt/m99f4iS71dL6Is9P8iD/p/4KH/VXgI8pW3/ljyjshFb3qAtXfEzJRpZKGPXGurRhp5hX391F04d8vYGyPG/5Isf+mMy87Y2F034TVEvTKf1/A5ewXYBx4JluU+7KfcGiy3JsutpZRb0k+5dVhuXZarV8ot7adcFctVs9yqSrkv+ik3muXGsFytUu6rfsqtz3IbsNx48GhwW9BvdCEtQvoRqb7Yb+yLdF6xfnaioaGhoaGhoaHx7yH38f+5/x9T0uTcVKIjB3EAcrGvflKV4fqk4ue4wGoFjm/BKPAldgwBsV59CuZfcnO4eNu44hNq72pQ54cso84P3fd9HxpOwgZzOltbsXWvw97vE6dfql2u3m+XW0vknwU=
*/