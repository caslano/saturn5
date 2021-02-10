/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !BOOST_PHOENIX_IS_ITERATING

#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/detail/function_eval.hpp>

namespace boost { namespace phoenix {
    template <typename F>
    inline
    typename detail::expression::function_eval<F>::type const
    bind(F f)
    {
        return detail::expression::function_eval<F>::make(f);
    }

#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)
    #include <boost/phoenix/bind/detail/cpp03/preprocessed/bind_function_object.hpp>
#else

#if defined(__WAVE__) && defined (BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
    #pragma wave option(preserve: 2, line: 0, output: "preprocessed/bind_function_object_" BOOST_PHOENIX_LIMIT_STR ".hpp")
#endif

/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
    #pragma wave option(preserve: 1)
#endif

#define BOOST_PHOENIX_ITERATION_PARAMS                                          \
    (3, (1, BOOST_PP_DEC(BOOST_PHOENIX_ACTOR_LIMIT),                            \
            <boost/phoenix/bind/detail/cpp03/bind_function_object.hpp>))
#include BOOST_PHOENIX_ITERATE()

#if defined(__WAVE__) && defined (BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
    #pragma wave option(output: null)
#endif

#endif

}}

#else

    template <
        typename F
      , BOOST_PHOENIX_typename_A
    >
    inline
    typename detail::expression::function_eval<
        F
      , BOOST_PHOENIX_A
    >::type const
    bind(F f, BOOST_PHOENIX_A_const_ref_a)
    {
        return
            detail::expression::function_eval<F, BOOST_PHOENIX_A>::make(
                f
              , BOOST_PHOENIX_a
            );
    }

#endif

/* bind_function_object.hpp
Ur596aG7uIzrtOqp5QwPcdqwu8y4qE5mAgueYSXmPIWFCioPR5C6oh7xs22NMRXy5yzpA6n8tt08CBtAao287VxWctqHHa1btD/PQHxnEzE1lrcQaw1SD/vtyrL+/a7mXKG2LU1jBa1pBncWGrK8/kdTo5KnjSJrszgHLqhKfnpxq8keuOfYRknLxC5zJJm35Kj3LCO4fQGqTG6qWJW0akthKPtSRV3JfjhEDmsQxSN3fCyDv8pLnswA81u4XbBpl+zwNR4Z9NC72hwIjca/pwEw2EZj5HsXDXJ2EgeY13SjgSGbuJGjaLmt8uqqYk38mgOy7IJy7odZSJj3YH7jsBYbPSjqx8n2+uP5iPqgsSLN2TfbapWrL46N1abRzMwgXPWhTNXXFakDapU8kcKH2Hgi/XSWpcR1Gl5f6yjBneUu7uML+eDb0Us0cSE9q5HRooLf2Vh4LusAKK/Jo89qhUvzbAVvdcwYedBY6/c7+D6jpcI8bs3cCLEcvMbzWIRSmSmgJd85ZoFG+HL3Odn0K0/U6KCC9DKpgjw+LknxrIJQrnCf2VJyZTF4al6ZaIrJIVXn2cUkGuaN5YMhTHLFvEXbnAXQZmvk4D4n5ERJlqmnLJ9U+RGAEi33im+UUQfp6Qhl4bI2OXUAX36s
*/