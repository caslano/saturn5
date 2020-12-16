
#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)
#ifndef BOOST_PHOENIX_CORE_DETAIL_ACTOR_RESULT_OF_HPP
#define BOOST_PHOENIX_CORE_DETAIL_ACTOR_RESULT_OF_HPP

#include <boost/phoenix/support/iterate.hpp>

#include <boost/phoenix/core/detail/cpp03/preprocessed/actor_result_of.hpp>

#endif
#else

#if !BOOST_PHOENIX_IS_ITERATING

#ifndef BOOST_PHOENIX_CORE_DETAIL_ACTOR_RESULT_OF_HPP
#define BOOST_PHOENIX_CORE_DETAIL_ACTOR_RESULT_OF_HPP

#include <boost/phoenix/support/iterate.hpp>

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/actor_result_of_" BOOST_PHOENIX_LIMIT_STR ".hpp")
#endif

/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

        template <typename Expr
            , BOOST_PHOENIX_typename_A_void(BOOST_PHOENIX_ACTOR_LIMIT)
            , typename Dummy = void>
        struct actor;

        template <typename Expr>
        struct nullary_actor_result
        {
            typedef
                typename boost::phoenix::evaluator::impl<
                    Expr const&
                  , vector2<
                        vector1<const ::boost::phoenix::actor<Expr> *> &
                      , default_actions
                    > const &
                  , proto::empty_env
                >::result_type
                type;
        };

#define BOOST_PHOENIX_ITERATION_PARAMS                                          \
    (3, (1, BOOST_PHOENIX_ACTOR_LIMIT,                                          \
    <boost/phoenix/core/detail/cpp03/actor_result_of.hpp>))
#include BOOST_PHOENIX_ITERATE()

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif

#else

        template <typename Expr, BOOST_PHOENIX_typename_A>
        struct actor<Expr, BOOST_PHOENIX_A>
        {
            typedef
                typename phoenix::evaluator::
                    impl<
                        Expr const&
                      , vector2<
                            BOOST_PP_CAT(
                                vector
                              , BOOST_PP_INC(BOOST_PHOENIX_ITERATION)
                            )<const ::boost::phoenix::actor<Expr> *, BOOST_PHOENIX_A> &
                          , default_actions
                        > const &
                      , proto::empty_env
                    >::result_type
                type;
        };

#endif

#endif // BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES

/* actor_result_of.hpp
0N/qH03wdcLF/dWifH+B+yVX76/e47UZ37NJrtxfbfeJ+Xe7vz+tJzyXjG+F8KBZ8Kz27m+Au/GmQPJDl0n3N8BLFR+3xCrfEvg5im+AR3OzFD5B8Y/g4vrPMqzPtDO/6Grm78/wPvA0yVH/onzVAZTPaOtZDiu2GvgyxT3waP788BrF98LF/omHS/qx358Fz0uR6lc5vu2C/xWNlSt56VIr/x/Adyp+F1zMf+EPKN4Cj+b/M/j9il/ik+7/uRrXn9j4KFxz/FqD/pEoFV7pPyPhe6W41evHefDnJVevH5deg/MLdvyBDyTeAD+HrY9ey70ohtfDryLHj7vhq2RX/74DPCi7+nzsOlw/ZM8vwgex9W34cHZ8hM9gv/8CPpXE/7Gavnr9/Ls8/rFwFv9FcBb/JngBO/+ijvzh5ortkqvrr/nw+4SL47/4+znj4XeR3091LvzH5PlUOwb3i0j7doPPJPVTBz+TzZ/gZaT+H4Nfzp7/2sDDj93AwzfAafpwmv51MdKH0/ThQ9jfN4Bnk/DNMcLvjxHefj3W5yVXf/9KN/gW4WJ+JNb3M+H1ivd3Wuv73eF3Kn6vdH/+KPi1iqdMldaP4PT3h9xgM14W46twcb5mg78ouXr/agL818LF+pe4PyQR/ozk6vPlKfBdsqvPl2/E+iL7/efwctnV58vhl5Hn67vAvy25uv/WwXuw338JD5L+ew+8ivSfF+Az2fh6I7//oRC+lHhTDC+9SVl/UPw6+PtkfnkvfA+5//FVuEdy9fnNxv+wd+fxUZR3HMdndwNyE05RrgXkEokLCIogxkq9aYMnKkICBAUCLAkCFmsD9RY1KKIVtMF6VEWJrVdBa8ATFQlWxYrV4H3WoPWqR/sJ3Z15+GX3O9Xav9q+2hds38zMM8/MPPPM8/ye57mc+E1Rv12PzxXza23AS1238xfiJa7b8dsVxH+o9z8+THgdfoaI79l9Kd+Pov28HB8t2i9W4L1V/A8+Ucw/sR0/zXUbv4qfquLXrtDtF8mdLsan4YOFV+N3qvnx8dWO2+/LZ/DrG5af/q/N+LWi/NyKLxXlZ+WVEW+5iq/Al4n4irvxn4n4ivV4rvGzpjr35zK+L53+D1v/LMIXO27rn1Pxs1238ddXUT6K+LY2+Eni/u2KHyXia3vio42vxf3yFX9XzK93Cf5yw/5x//ir8EeNl+wbHH8Tfo3xl5z8rcGXGR95epDaquXcv2p+Yfx58fwOuJr6oXh+vWv0+yWO7yk8H5fzB+PNhRfid0Sye/m1evsKfF/hNXg31f+wwrRfGE/g+whP4tPV/ldG5PoPcVzO/4a/Gs1evi/C7xLzG9T+mv4BVf+q1P03cbyleL8kcHV+Bfgy4cvwn6r67SrKFzU+Ci933d7fv6H+rM4Pby48EeL5+O7CC/E2wsvxJsIr8NbCq0K2rw7xGryZ+r4NOf+6EPdu1OcfD/F8fDfhBbg6fiHeTuV/yPYVeCfx/Ffho2JifTO8X0ysb4Z3wbPVf/rfxPdd1HFbf/1tyPXFu6v4CLyreP68W3X/exyX6+fgs9T8lXiJmr8Snyrq9zW4ii+pwzsLj99Wv73oX8bl/BN4O7H/Qnyc+j6qd5E/W/ATRf68gBfI+e/09SnE5fOBt1Djj0O8Eh+myo8Qz1+t34+FeDP1fsb3VfFf+EDVvoO3VtcPl/dfiOfeocd/JPAOwgtwlb5kiFfgcn0qXJ5/SPrqQjz3zog3Rl0/fILaP95R7X+NPr8Erq5PQcj2SXxf9X7G71Htg/jvxf33N3y6aJ+prKL9QKR/Dd5Dfb/j3dX8+3hXEZ+Ze1fI/Yvvra4v3ka9f/ELhef/jveHqB8egk8=
*/