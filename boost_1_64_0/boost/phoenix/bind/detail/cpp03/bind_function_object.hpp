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
Sp5glcfbpMVMvjIvz+GNwd/nNv1CgyGX+Z2CXyGdzNVQi9l65v/lp2zAIyswT21TZ84I3qCuPjehXMH9wxnVWTXmZguDrVZC6JiJr8Yc7w/A9O7VIf//09BH3w7jm+hSZp5ER0ncKxE1XKG/sa0IjDssij3gK5iOwzJ3KAGO5vB7EC56yGEb5J6Eixz2GLfmXoSLHC54z+ViDA5TmbkHfOJKxsAEZHPGSIk+JspcvTfjYfSSkWF4G763XCVwBMLYCY1V/q3hul53DeGdKcbku9KiQ+nUHhTn20N8sL4AbkFTAq8J1kSlMTKaMnV12bhRXBwwnFkU3p+9jvDRLou014b8186HU+dtjD32cMIasyXedrz5EQp7ebcy3Qbn1xHemj44792PlnTRDMOMNXbgnRHxl4SduPaCS1f2DNN36vsLTqQXTd+t6bSG8l3e22zf3ezeP/D9+jE5izsgnb84GBGH53mghe44iLtR/zTxbGDgbvZj6Ji83xj2tQ/5iL/bwYwj+AcWsdJ1n+0MB9uaYN95GT/iEyGc4zvv0P284M1KjFpa/i/F4OTe0Xn2n+cHGkX93foX4UNPGBkvarWIJzIzBV3al8gZe6mX933oGAFHZuyzOhVxp47W8dAhNLGw947fGeGf3oatH9xBP7CBcF0XCMcHLzfAlhsaCvhiVAxeKjA2s8d7Y2r9H6gv770d+Yemm9demmp/r0enb7p7gLR4nscXeGpvXJp4X+Ajz4xLE/YFTjwjDhv2BZ59egx2Pl/g3XFp4n2Bu+LqaT5f4Lh8Ig/Eua5OPzfsT+gcKbSMzX7M9QO2j5uMX+XLXFzk0du4xk+93sVHHqeNm7XSS128PAIUMRPeEi0vHaN1jA68ML4O6ECqZWR9scHSY0FRBzZctmR0/bopOJbiiB4HIKQEBm+PdYxf/fNj+cb6354e4TRhJCu89LmeerVbh1Yi9n1+Y1xdy1KyH+ttw2afngYfOeYo429kPAG8acvZcHnlERW1Jc5OaT3IglgOK4CMa+ztNObXC6V6Dk+SYAyCPKLSoaN6LXD+bfY6MpvLFKpeqfr/riPJBxO8yAcT206X88FckjDQSB/MpYYe9oO8m0MjP0JDv7uhR/tJXsH0SB/NZa5s5KN5HdHvwXTH15Hlv6fBhH0p78U025eR6MsN/Snk62rXzZVMD9XNvZkWWfarnLTkI2p4r2B6SO77ME34jzL9aqY75Vp2n6/BnodxuKMEep98kpfo33Tobnz474TS0/Oljg/o8vl9QEGf3wd0ecxZxfqloM3j57nnbqDH+Hkeuzto8/h5rl8G+gL9PA/cE9gF+nnesRzYefw8t947gr6J6UeuiqD3inWpr6vz+4GevhqYGF/OU9eANo8v5/mVoC/Al3PdKgdHBTVtd78o+iZD714dRe81cvTeH/QF+HrefC1w8/h6eg8guuPruYronTWKjhcXh/3dfJOu+ED/O8ZuZWfQc0Mizv9Fnx47PZj2GniIwlnzow7ibdbdcz5mQeagSXPgoSrNgsxB4+t4dq1Ks2DTjt+9fFh8OtfXceQR0dgoX8fOOoVdkHlq0rzsUSrNgkx/k+bEepVmQaa/af/qBqQJ+zrye1OPBd329aNlDPPo7QZmHp/C80Sfz1/w7EZg4v0FYciBPo+/4J5NROfVJmxiLseK3hCdnPqYx7LNYQwc+3iMJ7rjT2jou7eAPo/PYPVxoMf4DHZvBS3mPdbV1yvavKYfjeHAPcHBRtnOhL1NY6WbIbwOaRQ0+6A3P4lwYRObzyCTCnN5U9n4g6cIz52fPNVYvrlMJIY81RIGdygfiSNvNd6bu6kcxoU91hI8ptXDePJaE+/JhjE=
*/