#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/transform/detail/preprocessed/default_function_impl.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #define BOOST_PROTO_DEF_FUN_INVOKE_ARG(Z, M, DATA)                                              \
        BOOST_PROTO_DEFAULT_EVAL(Z, BOOST_PP_ADD(M, 2), DATA)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/default_function_impl.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file default_function_impl.hpp
    /// Contains definition of the default_function_impl, the implementation of the
    /// _default transform for function-like nodes.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (3, BOOST_PROTO_MAX_ARITY, <boost/proto/transform/detail/default_function_impl.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

    #undef BOOST_PROTO_DEF_FUN_INVOKE_ARG

#else

    #define N BOOST_PP_ITERATION()

    template<typename Grammar, typename Expr, typename State, typename Data>
    struct default_function_impl<Grammar, Expr, State, Data, N>
      : transform_impl<Expr, State, Data>
    {
        BOOST_PP_REPEAT(N, BOOST_PROTO_DEFAULT_EVAL_TYPE, Expr)

        typedef
            typename proto::detail::result_of_fixup<r0>::type
        function_type;

        typedef
            typename BOOST_PROTO_RESULT_OF<
                function_type(BOOST_PP_ENUM_SHIFTED_PARAMS(N, r))
            >::type
        result_type;

        result_type operator ()(
            typename default_function_impl::expr_param e
          , typename default_function_impl::state_param s
          , typename default_function_impl::data_param d
        ) const
        {
            return this->invoke(e, s, d, is_member_function_pointer<function_type>());
        }

    private:
        result_type invoke(
            typename default_function_impl::expr_param e
          , typename default_function_impl::state_param s
          , typename default_function_impl::data_param d
          , mpl::false_
        ) const
        {
            return BOOST_PROTO_DEFAULT_EVAL(~, 0, e)(
                BOOST_PP_ENUM_SHIFTED(N, BOOST_PROTO_DEFAULT_EVAL, e)
            );
        }

        result_type invoke(
            typename default_function_impl::expr_param e
          , typename default_function_impl::state_param s
          , typename default_function_impl::data_param d
          , mpl::true_
        ) const
        {
            BOOST_PROTO_USE_GET_POINTER();
            typedef typename detail::class_member_traits<function_type>::class_type class_type;
            return (
                BOOST_PROTO_GET_POINTER(class_type, (BOOST_PROTO_DEFAULT_EVAL(~, 1, e))) ->* 
                BOOST_PROTO_DEFAULT_EVAL(~, 0, e)
            )(BOOST_PP_ENUM(BOOST_PP_SUB(N, 2), BOOST_PROTO_DEF_FUN_INVOKE_ARG, e));
        }
    };

    #undef N

#endif

/* default_function_impl.hpp
LCiCgogH4oECKnghXgiKoiIqxQtExBvwQAQFKSgiHvid+b3fb97v5ZdNCuoffpoPS3fee/PmzZs3b96c+2QKsdDNsBv4voNJJ0vEHPBRSn9mDsaEZvQRHYuD/g7YWxT1OnYYtrZFqaVxf77ZH0HMcQzaEPPE4TLG2+Xwd1colYX93EJ6fbsCTSfZB5tv3LRLjft3EHT4li7IAb47z0MbIibtvJH1HfA+7UzIreMlxO4ngv6y6y3+TtCeDX+bRz2ug79Kot+nIOcKjJOL4Zt+3YK+r9CH4K/aXoIY9R2wnQNR16tgz8eh/JPQ58Hv4aPgq4BfuRz81mOMPh46Ak0VsdieRbBh2FEjfNnmCD7ok4/jE/kC/CX6S12PmvDvIfiOocOR76Vqwr/b2ff5g9DpoYgvdEyD+KMjo9Tg5fCH16LvYpxuRdxy7enQ2RVohxchRtiIMjLwZevg2+bALrcDdw3qDh7fyiGeKWIe1Iu2vw4f1Puv6OuHt6LPoC8uhn3Kvwsy/vReyFM6G3K8ksWBzMZeB51PbUffWivmdTSuj0wyDt//t/9v/9/+v/1/+//2/+3/2/+3/2//3/6//X/7//b/+ZfvT1V782oaJvG7xeQ6ldqeSdlD1ytWZLdn85VUKZvJ5rZnSyEXoxadEhoYB3eqYILSnnxi72w1tUEvx8x+g1IHqSlNuuClSC/Gv4eoWQ11+Ffjj8PngKlT1fIGWkYC7RSiHUs3RZ1AdGNxyOvhpjdp3PFI639PpH9X4N9Xq7qmhlaHvz50lcqqvXNb69QrkB6v8gcCr+lNDtAjbepRr0bSuwpVfaCymM0PIbOj5+mqaepJoHf/Zv4X9Xwa6jMV8kxRQyMj6om9+vtUhVNR9L1OlbOl7bkMpSFzNV8uZjPmaJdHH94Y9ugT4fj6SJdOb1YzUJeZUytKqZUNAdaCI3fVkawn4YoVpFHUYsMy5/upRFOjFntfPTnbtJysribmTrZ4Ktki7KuhqBT05cA7NXy3Up2wu7l6mwnpLvapKG2z9ruEL3ZhzF51WSFjk3NVt7DrUwLppqgeohO4QLsOkz2von978e/gFMeuTxF2HUHaKsna8ynCniE/bCOfHmXpmQr2pw8PqSc82BxVreaGHBqtgwY1kkHa6xMtik6qsjzzlL5D4NxjQnt4eeczuM6F04fKzbOA4WDZHvwIA9dHVK0MRxmYy+EJT5Zj1ZbcELolyvRgL1OlrOaaqWSHXDj4ApepliuFUQ5bBlrnMmHKKEbbaTP69mrWt0/4D9rpQWpmwxTXXvBvzzj9IlOq0KHVVLFgToqWTSGBGLDWdr6W7PwQ+Atdv7p6w6t/JJ3JbimMDGVLau/RKA82OjXG6levUrkCXk8zBThfwfGJvSsnlk0fp3OySSjJtI5kqlXPUZxiyw3uqgh2AgGO1J8TxPNoqmfc1AVl68O6ZBtJY+ujgy5Ml4/Cpw5wn/0c9Qy9mvJ1W26wbYl0XavGLUT6dAVdB9dZ6tqr12mmXtaPvLLBKQP933iz0zUedK9qsOVXBC7l4TAeE4+i4rRTVbrB4iv6I/AZ4jVky0GdWT2RBl9T7qFEO+zJjnp4fhi+l31fS9/bULZml0P6DHy2ahnruQwYdQE7h8Y9pfoLO7KlAYxy/eitZgw246GFRwsVQrnjncVF8ulMBcOsMmOfha9N78yNVkfVXgGPOIfcFWxmRus0pczYmNdj4wDGzVSoKxlZH0luSvXHw4lwFKOoGQrHQeqx73qvHux2FCgisbgm7Y2s6lWmPsH4aCy+NtTn1iuYpi+2geoRjI9E14f6It01abpiA9Gk9lGdrN5FXe8gcqp1EErX+WYvZlkd60zFOlc=
*/