#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/context/detail/preprocessed/null_eval.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #define BOOST_PROTO_EVAL_N(Z, N, DATA)                                                          \
        proto::eval(proto::child_c<N>(expr), ctx);                                                  \
        /**/

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/null_eval.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file null_eval.hpp
    /// Contains specializations of the null_eval\<\> class template.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (1, BOOST_PROTO_MAX_ARITY, <boost/proto/context/detail/null_eval.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

    #undef BOOST_PROTO_EVAL_N

#else

    #define N BOOST_PP_ITERATION()

    template<typename Expr, typename Context>
    struct null_eval<Expr, Context, N>
    {
        typedef void result_type;

        void operator ()(Expr &expr, Context &ctx) const
        {
            BOOST_PP_REPEAT(N, BOOST_PROTO_EVAL_N, ~)
        }
    };

    #undef N

#endif

/* null_eval.hpp
dMF6ktJ3jvAPa7DUmGn9QaW29BGML1P3eNieUpKQBvxZGvBnaY18T4n2IAB/AIZ0gCEdYEivSOlm6SFdZTykh+8Knp74vDjg82KBzzMhfvIyzFBGEpSRCGUAPd0NZVDa+Ki06VdDXs1PotdNLgfUaFQ+EnjISuAh8yBvo1qnBcLMEAY85otQDuFPVhT+0F5Ngl5IyIsVEipMDRqLUbDUxgoWqNtSkdCguSpOuKpymHBVnkW4qnFUb1p3amdyw4ga1tbh0NZh0FaLkPYib+voOGF0ZZIwOi9RGF0R7mWNBcqDNkKZuFrQjEmflgh0fZowtjIHaPtPhLEAW5jCRsCXZoK6YqEucPNicG+vQZORADQR/ipxHw5o5PRwTs3EOGEitHlixVW9Gd2jOtP8qQ0pNcnlRBsqoS+hrdCvNZrRJoAV4AX/6OkAa0NyjWaYURgG/mHTExsSauLLaZygLenTGd01+3n4+Fhh/IHRvendIztT/CMahtcMy7EArmligQXEfU0qG/oAxoP6AcumPgPcgDrToA5oRzfBi3MC6kipGNZr7ublD07L+pfanQTtToR2w3dFRLuTsW2JuIcaxTkwXIM2QH+lQ3+lQ3+lNyKuxTHcqIhOT7xu3nDBsjs8VkRrcE5YEwQr4JoVyrFCOdbpGb2jutM6U/0wJiOAd3LpgU7rhPhKoCN5wCYZtIIB3GFD7AdX17B9vx3A1JyD
*/