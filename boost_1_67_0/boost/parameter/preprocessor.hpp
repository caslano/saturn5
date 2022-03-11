// Copyright Daniel Wallin 2006.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_PREPROCESSOR_060206_HPP
#define BOOST_PARAMETER_PREPROCESSOR_060206_HPP

#include <boost/parameter/aux_/preprocessor/impl/forwarding_overloads.hpp>
#include <boost/parameter/aux_/preprocessor/impl/specification.hpp>
#include <boost/preprocessor/cat.hpp>

// Helper macro for BOOST_PARAMETER_CONSTRUCTOR.
#define BOOST_PARAMETER_CONSTRUCTOR_AUX(class_, base, tag_namespace, args)   \
    BOOST_PARAMETER_SPECIFICATION(tag_namespace, ctor, args, 0)              \
        BOOST_PP_CAT(constructor_parameters, __LINE__);                      \
    BOOST_PARAMETER_CONSTRUCTOR_OVERLOADS(class_, base, args)
/**/

#include <boost/parameter/aux_/preprocessor/impl/function_name.hpp>

// Defines the implementation function header.
#define BOOST_PARAMETER_FUNCTION_IMPL_HEAD(name, is_const)                   \
    template <typename Args>                                                 \
    typename BOOST_PARAMETER_FUNCTION_RESULT_NAME(name, is_const)<           \
        Args                                                                 \
    >::type BOOST_PARAMETER_FUNCTION_IMPL_NAME(name, is_const)(              \
        Args const& args                                                     \
    )
/**/

#include <boost/parameter/aux_/preprocessor/impl/parenthesized_return_type.hpp>
#include <boost/parameter/config.hpp>

// Expands to the result metafunction and the parameters specialization.
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#define BOOST_PARAMETER_FUNCTION_HEAD(result, name, tag_ns, args, is_const)  \
    template <typename Args>                                                 \
    using BOOST_PARAMETER_FUNCTION_RESULT_NAME(name, is_const)               \
    = typename BOOST_PARAMETER_PARENTHESIZED_RETURN_TYPE(result);            \
    BOOST_PARAMETER_SPECIFICATION(tag_ns, name, args, is_const)              \
        BOOST_PARAMETER_FUNCTION_SPECIFICATION_NAME(name, is_const);
/**/
#else
#define BOOST_PARAMETER_FUNCTION_HEAD(result, name, tag_ns, args, is_const)  \
    template <typename Args>                                                 \
    struct BOOST_PARAMETER_FUNCTION_RESULT_NAME(name, is_const)              \
      : BOOST_PARAMETER_PARENTHESIZED_RETURN_TYPE(result)                    \
    {                                                                        \
    };                                                                       \
    BOOST_PARAMETER_SPECIFICATION(tag_ns, name, args, is_const)              \
        BOOST_PARAMETER_FUNCTION_SPECIFICATION_NAME(name, is_const);
/**/
#endif  // BOOST_PARAMETER_CAN_USE_MP11

// Helper macro for BOOST_PARAMETER_BASIC_FUNCTION.
#define BOOST_PARAMETER_BASIC_FUNCTION_AUX(result, name, tag_ns, args)       \
    BOOST_PARAMETER_FUNCTION_HEAD(result, name, tag_ns, args, 0)             \
    BOOST_PARAMETER_FUNCTION_IMPL_HEAD(name, 0);                             \
    BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOADS(name, name, args, 0, 0)       \
    BOOST_PARAMETER_FUNCTION_IMPL_HEAD(name, 0)
/**/

#include <boost/preprocessor/control/expr_if.hpp>

// Helper macro for BOOST_PARAMETER_BASIC_MEMBER_FUNCTION,
// BOOST_PARAMETER_BASIC_CONST_MEMBER_FUNCTION,
// BOOST_PARAMETER_BASIC_FUNCTION_CALL_OPERATOR, and
// BOOST_PARAMETER_BASIC_CONST_FUNCTION_CALL_OPERATOR.
#define BOOST_PARAMETER_BASIC_MEMBER_FUNCTION_AUX(r, n, i, tag_ns, args, c)  \
    BOOST_PARAMETER_FUNCTION_HEAD(r, i, tag_ns, args, c)                     \
    BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOADS(n, i, args, 1, c)             \
    BOOST_PARAMETER_FUNCTION_IMPL_HEAD(i, c) BOOST_PP_EXPR_IF(c, const)
/**/

#include <boost/parameter/aux_/preprocessor/impl/flatten.hpp>

// Expands to a Boost.Parameter-enabled constructor header.  All arguments are
// accessible via args and keywords only.
#define BOOST_PARAMETER_CONSTRUCTOR(class_, base, tag_namespace, args)       \
    BOOST_PARAMETER_CONSTRUCTOR_AUX(                                         \
        class_, base, tag_namespace                                          \
      , BOOST_PARAMETER_AUX_PP_FLATTEN(2, 2, 3, args)                        \
    )
/**/

// Expands to a Boost.Parameter-enabled function header.  All arguments are
// accessible via args and keywords only.
#define BOOST_PARAMETER_BASIC_FUNCTION(result, name, tag_namespace, args)    \
    BOOST_PARAMETER_BASIC_FUNCTION_AUX(                                      \
        result, name, tag_namespace                                          \
      , BOOST_PARAMETER_AUX_PP_FLATTEN(2, 2, 3, args)                        \
    )
/**/

// Expands to a Boost.Parameter-enabled member function header.  All arguments
// are accessible via args and keywords only.
#define BOOST_PARAMETER_BASIC_MEMBER_FUNCTION(result, name, tag_ns, args)    \
    BOOST_PARAMETER_BASIC_MEMBER_FUNCTION_AUX(                               \
        result, name, name, tag_ns                                           \
      , BOOST_PARAMETER_AUX_PP_FLATTEN(2, 2, 3, args), 0                     \
    )
/**/

// Expands to a Boost.Parameter-enabled const-qualified member function
// header.  All arguments are accessible via args and keywords only.
#define BOOST_PARAMETER_BASIC_CONST_MEMBER_FUNCTION(r, name, tag_ns, args)   \
    BOOST_PARAMETER_BASIC_MEMBER_FUNCTION_AUX(                               \
        r, name, name, tag_ns                                                \
      , BOOST_PARAMETER_AUX_PP_FLATTEN(2, 2, 3, args), 1                     \
    )
/**/

// Expands to a Boost.Parameter-enabled function call operator header.  All
// arguments are accessible via args and keywords only.
#define BOOST_PARAMETER_BASIC_FUNCTION_CALL_OPERATOR(result, tag_ns, args)   \
    BOOST_PARAMETER_BASIC_MEMBER_FUNCTION_AUX(                               \
        result, operator(), operator, tag_ns                                 \
      , BOOST_PARAMETER_AUX_PP_FLATTEN(2, 2, 3, args), 0                     \
    )
/**/

// Expands to a Boost.Parameter-enabled const-qualified function call
// operator header.  All arguments are accessible via args and keywords only.
#define BOOST_PARAMETER_BASIC_CONST_FUNCTION_CALL_OPERATOR(r, tag_ns, args)  \
    BOOST_PARAMETER_BASIC_MEMBER_FUNCTION_AUX(                               \
        r, operator(), operator, tag_ns                                      \
      , BOOST_PARAMETER_AUX_PP_FLATTEN(2, 2, 3, args), 1                     \
    )
/**/

#include <boost/parameter/aux_/preprocessor/impl/function_dispatch_layer.hpp>

// Helper macro for BOOST_PARAMETER_FUNCTION.
#define BOOST_PARAMETER_FUNCTION_AUX(result, name, tag_ns, args)             \
    BOOST_PARAMETER_FUNCTION_HEAD(result, name, tag_ns, args, 0)             \
    BOOST_PARAMETER_FUNCTION_IMPL_HEAD(name, 0);                             \
    BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOADS(name, name, args, 0, 0)       \
    BOOST_PARAMETER_FUNCTION_DISPATCH_LAYER(                                 \
        1, (name, BOOST_PARAMETER_FUNCTION_SPLIT_ARGS(args), 0, 0, tag_ns)   \
    )
/**/

// Expands to a Boost.Parameter-enabled function header.  All arguments are
// accessible via args and keywords, as well as by name.
#define BOOST_PARAMETER_FUNCTION(result, name, tag_namespace, args)          \
    BOOST_PARAMETER_FUNCTION_AUX(                                            \
        result, name, tag_namespace                                          \
      , BOOST_PARAMETER_AUX_PP_FLATTEN(3, 2, 3, args)                        \
    )
/**/

#include <boost/preprocessor/control/if.hpp>

// Helper macro for BOOST_PARAMETER_MEMBER_FUNCTION
// BOOST_PARAMETER_CONST_MEMBER_FUNCTION,
// BOOST_PARAMETER_FUNCTION_CALL_OPERATOR, and
// BOOST_PARAMETER_CONST_FUNCTION_CALL_OPERATOR.
#define BOOST_PARAMETER_MEMBER_FUNCTION_AUX(r, name, impl, tag_ns, c, args)  \
    BOOST_PARAMETER_FUNCTION_HEAD(r, impl, tag_ns, args, c)                  \
    BOOST_PARAMETER_FUNCTION_FORWARD_OVERLOADS(name, impl, args, 1, c)       \
    BOOST_PARAMETER_FUNCTION_DISPATCH_LAYER(                                 \
        0, (                                                                 \
            impl                                                             \
          , BOOST_PARAMETER_FUNCTION_SPLIT_ARGS(args)                        \
          , BOOST_PP_IF(                                                     \
                BOOST_PARAMETER_MEMBER_FUNCTION_IS_STATIC(impl)              \
              , 0                                                            \
              , 1                                                            \
            )                                                                \
          , c                                                                \
          , tag_ns                                                           \
        )                                                                    \
    )
/**/

// Expands to a Boost.Parameter-enabled member function header.  All
// arguments are accessible via args and keywords, as well as by name.
#define BOOST_PARAMETER_MEMBER_FUNCTION(result, name, tag_ns, args)          \
    BOOST_PARAMETER_MEMBER_FUNCTION_AUX(                                     \
        result, name, name, tag_ns, 0                                        \
      , BOOST_PARAMETER_AUX_PP_FLATTEN(3, 2, 3, args)                        \
    )
/**/

// Expands to a Boost.Parameter-enabled const-qualified member function
// header.  All arguments are accessible via args and keywords, as well as
// by name.
#define BOOST_PARAMETER_CONST_MEMBER_FUNCTION(result, name, tag_ns, args)    \
    BOOST_PARAMETER_MEMBER_FUNCTION_AUX(                                     \
        result, name, name, tag_ns, 1                                        \
      , BOOST_PARAMETER_AUX_PP_FLATTEN(3, 2, 3, args)                        \
    )
/**/

// Expands to a Boost.Parameter-enabled function call operator header.  All
// arguments are accessible via args and keywords, as well as by name.
#define BOOST_PARAMETER_FUNCTION_CALL_OPERATOR(result, tag_ns, args)         \
    BOOST_PARAMETER_MEMBER_FUNCTION_AUX(                                     \
        result, operator(), operator, tag_ns, 0                              \
      , BOOST_PARAMETER_AUX_PP_FLATTEN(3, 2, 3, args)                        \
    )
/**/

// Expands to a Boost.Parameter-enabled const-qualified function call operator
// header.  All arguments are accessible via args and keywords, as well as
// by name.
#define BOOST_PARAMETER_CONST_FUNCTION_CALL_OPERATOR(result, tag_ns, args)   \
    BOOST_PARAMETER_MEMBER_FUNCTION_AUX(                                     \
        result, operator(), operator, tag_ns, 1                              \
      , BOOST_PARAMETER_AUX_PP_FLATTEN(3, 2, 3, args)                        \
    )
/**/

#endif  // include guard


/* preprocessor.hpp
AxyKB+7IkvZipEcqrwJj3rdtI0xlj+WSIdbNiLUbKOvGUaOifIMje4ffCI9vzdOb+ePb6G1nOYUBpZkUgTlBz/yfWxXUJ1WUj82zrWMNmZcw7UaGSB0PqZI1Dv1/hZ7l1xj0rqJUVz8cLjtKkzjICTS07T611AzrGX/ZC3hMhsrk7AbTgO9dUW5dolQvPyPHg5tOIA1sQAVrlO0/gwDJ9JuQwj/v50TRZ/Y6Cpx0DxHmzt/UNKG4F9ktpouowoJdIVq/nUfqVTx4ll80y6vmbZgTY+GBLI0iQLtbRWHWhZPJq9F48PQIl0/QH3uhN/a9c2h82XJNkEimwSsWHJvtS2/OIjWmnTqO/LcRrYohf6aMGwB78NxOkteaKB/GsSRJXoX9tbVehIzQws1uvTjk+CNtggNfq2ZK3cexImFPcKhYU1eP2FcEDnRNUBkZoxhK5UUg9S1izZOMk6asodkwuNUCumVrgft2iOtdbY9+bi61bRi91jPXsm7t3HlTTZVcJ3R7kntP1al0/DOX6dh4EIajnM56UIgOUDo6xQrXW8ZKefeWQY9ZtyM9okW7xNq//ggV1sqHiaLVJLHoFb4jZ5AFet1nF/rZ+wpLZeK1W/5Mvwus+3bJHnGXmdM9kqxFmSPel49YCD6wGA5d1D1C+BBsRc8GWsdbZ14OFl0ULyO2kNsuaZqXttPXcEg+HCubnr89BqPG+4hiEqFu2WHdbhLKW7FoY9ksjEy4t6ZRlUkF01TcurbQTVKkwbc/XEr29KxiV/N8cllvzVSXGnK45VgfzFRoc7Ww22LYy/n27meLcC09sIFTqJyLY3mytgr8qXXq4rCuu1jKRIEODqwirttRGgPrttvzaAunrtb0e1k7vhLMUHff8OpWovd9GbJBWJRNSSzTIJsSIIjTLkAF4NmmDt+Nj9Sn295PvUl68CRmMPSZXHL0znTtAqrO8X2Xj11ri02sY6KwOj6Rv1G+jH7RKz7TcEYuYmTShBIONIxreePGVvSeefGSA975W3EHEcPOmrG/JWollyMjDZL7w8vqnL3Z5YfhcNStreS2x+hfhAB+WHiaMfvv7UIpTjThsRC5i28178gkpe/fc9yeNdMTDOSde/iSiVQE933NI7CZtgo7lzZ6Z9vUhxTL+qaTJ9ZM/VRHTMfeixM5g7JyQPt45/0fC0HqxGpND/MSvCCf3OD5Spt7xQ8DWedpIYkb6vJIhTBamqBm9Z15RmtAkkYWqlHEhedLUA9BSe9nOgm+xkB2SwQtDkzSSiERqJxOolAmnbCFcyjvKLEKtdC9bcP3+qpLiNwpENJ5shLpQZcFLSMVHBCu6UqI/RxQ+Sa9gSfjB6FFW2VH2Z706oXFBTDuSIoPr/ibYQpfNeYRUtoMdMvTPVvLU/3cxjnFvnPVuLwmO0ikuZpRzYk8G98IlH9eTzWNr/EuCPjV9e66GVXUV8dT6tdacQ/vJyEElgxojRe8oanzHCzrXAM9sne0aFzs9qP2C3odiX0lxIXmrD3g4q/Xe+o27ocSLiSgsZSsm66TSR9LIHQN9+ZaqyU0funJT074ajMKOrU5zJNiD1H7D0AuhTbEmkWXlS9+9obNc0yZvByxvicPN1ufE5pyisg/1fu6LNsPPta3IqlmYQyr8X+uBZM//9pZHYUwxBG78Rx2J74gemnLMns9h0l+HrKXGUQ9lc1CdfSFLJiufDFex+tfutRzGBvdMneaGN5SvYHxDXLYKT0mJpJwmuNdsN1TjOzMWJOkRPsYsCJ8z4Rm7qLmrcQE0kzcUbvbYkSJW/wZKtwkf5p05h3XHmhWuyNzleNm3It1WKm9jynztnHEdKXZyDlvu+n0/jugO/L/FbqnukBEp6bDBo63CrqBrNyC/gREGqA21W5v0j94DuQ1qbVqIQUtpNtLq6TjQiuqh0aFFL4U+n6zdnS72iXodWP306XkfonTDRbIESkMsLBZZBHG0ouuQZPlnvVgz3mvciAzpSR0KRD1fNtG+ZkWvWfxmoaIwB2hAmla5ZaVeeMFHv+t5Oeh/7a8zsK0U+PBH0Kjj0Jg72Nwf39oqFggP5JYE0OKqymYnL1YNnAIuWpKOs1TJ0jiPdou+VaZeyiM8TDRYDbJyGM3hDXlXum+BSeIsOFanSnLyVlDY0ee+qAe6pzCjDv9iRbfTKSTxUtlbGq3JChuLR6LRXCvwfnain7Dkvl5WXJAj3qT+008RXJTANHYTNy3UPigHWadMriSEiLpoNm4g7jkLNxDep4O0hZ+DxWwGRe7H7AJSUzPX83+3gPpsCgqfFp4/WJ4sX/O25dUtJobIDFaAJJxa9JY3NXIDOkSvSjyWpCAxCzv847nnLyC7uVv7nsLEsPBAlGux0GpNi1wQZFJPBzQZ0bZKsMuMsaOzSRjWPW5s9xvbS2t1u5UhsKkO3HCvLluUXW96uiFLkuCJiHxKTY4OzGWAfb+KpUdR2YdybTgCv34eEoZ9t1taabpZmG+KZNxG0X57If15ARLmkhtKPbj4u6qiiQTw8KK1PiWdfzVeE9bv/3khk30TexjGeDQF2nved4gTuyj570gU5ZNWg3MEfaWU6qKadJ98uB7kHxf7xbb2+B+HrVsuiITLa8wAa03j3vJAp52edy8NUNgukUIoT1rc+HlJAgIuCfohJAZ5pxKKjOIUEdWIdRd3KDazTOver9ejivnfvBcm8NNjIscTsyusCfinVbtMGSq8sc7P9EkS9bnns7zmd+vNL1U/5janZXlYfu1ELvS0Tk3w3I0M5Fih/b4DCtL3Xw+idGCyX2GYTCYHG8lmWuvmtGiPCrjSITbBPNK8vMjLMNct3MCyb/72dFrqk/3glyveQhZ4F0IQX04f0OppLBTodQSOQIZhKLXGlaceo/iBSvNSPLjfrzcyVZnzYGbt8afPdayf9smt63ovumNVTE0azcPnHviyaLPAPeLql+W2FnUNXg5S7i4Sjv2dQdKfou6BHcKlujj8FxyrwjoTv8cWLaCh8BLsuVzSysmekLZ+QWoEF5+2smUemcs1ksCej0KVNu717jCD0WDh/fOqce1VPaLVJRQ4I3RA+Fjd8RtKmSlnT/wJvtV2vXN0QMuIuLkwPEglvQ9XElv31wowhs8jFgCDzaC3VxdwnAogkn+6lHK9fxAeMsja8sgttU8lRaOJ7R0FN/KIC5HxNZVmERTc+Do38jUKou8S9/fRO4EVehbAXnR2wlKVbJRANODorvFVshnSm9ohepvmvSpm2rlGYHAbJPqpz5nkavkN1FzOfFRalXsVryR83Ca1e2X+Xllj2HXAOlJnTfti+Y307dPISfdIR6qlhy5f8VDZnKeMkjG30y50FrLlNXOi6VbTANpT45LA27FPMuO5peGKmhQ3nQzD3UX8S32m3nNi6xr3H4tiyPyOqvfQjEbOw/5P1mu35YpOzespOIzLUv4Ne2aPcAg1VGoatrFEJCcuXLl2BPqseVsU++HhMZyReTM5kvyK+Ws6oYN/lPHNer+zHVk8EtxE4iYCZUYDBLJfnpn8kxPBGeNcQXH6BTkGHSYBMYGGEpYlmvRpZI4nYMUChp980pGLOuG5kVc29U++Ok8ATmzHYdFBzvzyDmxT6CSqFEsX5+NLlY6Ez6nrkQ+S9XdHBpdIri3IAmfAIrX118ptkgTkLR7UIdunEvD9uYnx9dFGmAJWhcan8JlhxWT400T7baUwsc92JpOfnYRnF0xV4yFC4yJgzorFJiktn8KzxNXVIWn6ChD9rZ9kXOnWqbr3y79nFV4ME2x6zxVdy/jnF1YcrGbp7O8muc5PjYUsrgNsrF3GygurMCyQW7sVvluz5wQs+vDde0F7hMuwiEJaADTmpl39KdudN66cVE6u+Ucl5QjbCu7tRYfgHuqVkbLpsBA7jlSerzfKUIPJEm1Oo9iBNbhVlfkbWbtR73edd4wedJrZHBOEoHOD0sSBpsnwsOtf+wMDDZcZQctKZcsG1qhjmhIurwUimWq9xJJF8Vhsv8cxaMfTgiAaVse/9nf0OgL7sya5XO8RxQzdtVcbFxev/8KDzvqs4BB8M/JAIM+s8UOf0wa6hOOjE03JfD7klm/fFERcAqFLOovn1ZCi0xA/F7prw2mZQfV7ko0uZoTHpFSieTEnOAzafkcCu79VAhNS1lrkL3UyC1CzpTMnmcGs+S25bAuwnQX5rwv4dRypqWQxTzNIq0JNwJNkIg44iQJurfz31Klyi0JN33LSNMBU15l3KpzkxVK3WJyDaeCw707KKl8sboWg/BeoLqk+Hfqs3JMkr4dw61Wbe6yhmQCVhASeYSgzLJFkbJQ/QcVX9icNbrPURQAYYGGlEohPo34juC7OTmi7Lr+DNphQTcpZ2b7lWa93dY1StK9gl3avnFcgJEf3SSIlfNFb1KNUfwvhggQZBS0BLDp3zomeQErPfh//sSDoClwmKBiYeSkntKF/kcDoCmwmDKJsF0ykmyPMo1EgrQFGopwckx660ayR6P4YUHhL24obG86JEL9g56d3q4nB9tGxJFzYcBlPFQRdYTJ6mdiccg1U7w2DODFQMsHVLKWU0ozNCuEq3dcV9V0CTNu50sFZSdlKDpPt/gIrKviBkGVamV6VNiK8nwf91UlPMsGAMc5D9DicwZgrTa9k4QGH4OOZ0rf7SjERbkkOBjQVLwstZ+rtSJ/oz5c5uhk68fGMZN63R7emFZzu5ExL3tY7vQMzZbsTEdCUpyBoSuxX3uwjutGfg70c255YR8Wb3w/6HRfv2xxj/m9bAsQmsGgHuJtoRzvXmRwj8nRTAYwjtdf6VRpP2RDWpt8wyqm31Pwv4fZVLw3zEgWeq0nmsd0ZUvnrLyK1YdCt0Ppna+iKAFIXPswtkQJe+8Kbnz0h4uecJvhdj6GZYZIeUNWONbTk61IIHTPXb4q0w2fSqRNAUUTAGnMdNX0XK3y3/aixwfmHRMGGvKR5L1c1l/RcqUXBhokMc1ppsq3/DGSRhl2/7kgisIp668NPeJ6ctt7scjrH31x0PF8qCu6ThTjCoMN7sq8L6NtYt+DNxGLrAACLP3TVS0WUTjWcdacJTvqr0I1Z0aNQLfbHpLltonV+TJa/Ca1yIPHEI20lH+tGbQ4opAOmfgmwAkBHSTIqWU2zL7ln85PShRMDqoBqFsbsYABQ3056+MbKky70E858qnsWds+UsxgikmSnlDSEQBtf/JleN42cBqCLIz/LJbw1pnaPGgRv7BeD9xW6EpGzOlfec2liGASQNG6IGA3eEDUWzWbrONbmsoAl2oRCMJkVrnsCSXOFd5/NAE4DOGDf/SeBkQ78HvH/rvtIBAU6rtEYS8z1b21U1Dv4UVga8mEEUZftlHnkf6A7JDOtB7/tBm+yHZIC3rr/Tr+gBScmpiGjZIDM31q3IeUk1STsY38GaSPFDxAbY6tA8aZ+FthAC04Qs76x3GxHQwuup9cnw17SRJKBac2/DqiQ4GtYgr0KC9DCgEL6iydug6HQiAvIv9lnFk/OUeGzNN4i79ibx3oj5cP+sHKCGhT50WhSd0OljN2oO3LrOW+RDOVi1UXGIOYeW6K9CWOJlbuwdyO7MwsAYaI8riqethqYi17gkB2dgfjIlVnF4TeNDooos7hyMQNud9Dtumj3kjv+5D92zQh9zFfGd+A5yhfwQhhVMB8MZ6/Ekuz4HnQVyUbnCDS85FbbBImSDoFOOELLbuOOVIUdSKhjhMxCT8Hdpb89hv+K6I7aFL/6slgshgJHJptN+ooAvaxZ9SeG4ByywilNTjl9dI0RAa5hwReG9Y/MDpmOsxZWsbA492jf/yObtBfq0/kbkP+f4SIKnoKTvTsZ0SJv7r1WiGdHuYKoG0mv/OwiqSz87V5DENYPEJYBBuHuKNqNG3Z7/mT98kvnZmZZsBxZKBZYGOwGqudO3IsYFhgwy8l2GB1bTGx3Lm/5xem9D3BPd5HIS0g/GvLbe68+RR7FueCwhHX89kLq95u+Q31WdczCrTxNEiJ2nSshwkgcGxgxpP7nul5hCV6o2Tx5lGss4vahC0jGxfm+4eccfcLFDtSYnpOwzKUbl3pOiRPvYi86fQsw4nAeKUpqssa1POrMd0Akug6dV3BInFTEu0OjKS8nypSXkMkzU+kG2wnHCbq66wM0SPdniUlwxS98BlRlsQzB1ysYDJbhl6QOhEGGthgJ/x0g0DfCjH33XDNU/nT58qbUcMRUuT/ImeNfuCa+ipCBwaR3t8vCzFLVa3VhLw9Xi4s0g1BTH0E1u5q6PbELTW0+UWhXb04mrXtQFDDsh36s+qzYEsq2ESopRBDMArHa2sBCCQcoU5k7YOKTv/1nc4pUCdWYQvJVPZYqmFYttxcCGOxU5xh8oe2biMAsbrHQeQrTa8jfb8Zy5WL9HZYFK4EpbRGFifeP0rO+u4UaNNpQ141aemvl0LZsrdEiBxQUSg1qaVauFJMoFtbKOWaCBF+sFC/I5mK5ei0ot2OAr5dT+t06OAhaO2vg8ojtSj8I1bmQaHeER6BH5AkLBs1O4Ni3sYZKP1HOGCRp4ns2cmoH8lIenHkX+bYIiHWI0qHLVPvjGZyeuMbu9JI4PudSzyorO8Vl/LaJLlf3WyIYzazF0aypPGfmEM1e7fkG12B3xqq2CtkWVjCNcPfopignKkY70XJ+AqomUdQvWmCBBSsmD11H5j+GojjaCOl69VVJipkYFbKkkZd1oKw9SVaGRFJKoUu5JsSo6iw62hBpuUD0tiuaTzqLh38Z1VehMNz7vWyqsClA+Pfo9I5Cmbzw/ernGnOSj70w9iFz4znampx5elM7CPZk4c32Keuuc/1Esq23m266c18W8F13HwuEjLihnO0S3K7nkw3CcwDo5Z2AcUuQePzeT+Tff0R7ljfxbz1u+ZxRSvBDpqg4hUI1vrxZHTfGeob0D9Q6nH5jjq0SXnRWuhHAopjfFBDzJM8SGIf9UaNNxzLYiFmJECfuh3SkfTK5Rz405KnRpxq3dENxmMBD1ZHiEmAd2MADYuPQEZTUtHp0N3Mf7mI1GnZldEFDgHRf8SazgIBXbga7J5X/I18fbEfmY0dJxARIOA1VRKtC7EX8GNtb+g3IOo3fjJzgEkbFOwZ3uQCTOGBDA1rNz8BItYQVCZiAs8XNPQHFiEu9u0XFIX6HOR9k/a8EuPkcAh1xDHljMRu3epzTBafhitBygXy4GJuJ2bIt3ebCaHCbvxW+klzRaYAaKIXD6lmvcAWhlhh6Bqtxt0Q/sy3IhnYpUvVgHRJPA47Ilwo3IlDOBZQFJLMm893lm+hxpYf2SHeFesyXRnCklHzvgLGWOEnZqRd04IOsa70g7GNxq4+OkaHeEOVlxrjAaLfhj6iHVRzJzDFVeyv3niHA3ycb4AboVzdT70UklwnueQ8mfma6dSeoT8jlay9RhkUIrt5IDtPHypzlzv2N9EpEnmRmrGdHYiLXO2tnmhUXp2+mfqT2209U7m1t7h8s2aTCOnIgj+XmJ+AeC40NQR2wVgr1a5Ut6WfeMpMnf+dUNKrp7hMKHWDLwnnCDJNaRqW0rrcCMFHco4+F9kCXZrV7xsWsYEFD2O4Y8IxH0ox34jZqdswzCLUmMssagvoGlvXU6JUzvG0XpysAOFedBjsxmyCZ7X41+e7bg71aoDHvm91UEikM3qbDXSkiP+8dSffHOYzK1UQMGVE8TrFRZH2j+4hWqe9OFaIk6W35Up5UmVQ6d/qoiqOH3k3awzDY8R+sqFj1rMGDflOPfLyflFTkzL2n8StMewIAy941ozUdXdu5V4vdONx4USPKZ+4UA3Oj0zOaA2wlkH4SJwfTgW48oHu74FAtOl/MSr0S9sYK1ttT05wU4fzKrmxrtJgTuUyunjBLjbZw469h6R9BMrdDtBpGKZlbRRDZHahMOcnEEEzloHe9e5Ci1i6JrmIWqeNIKgcVtlmKWnmL6Eu54lC0RsP9tL1bOTrcYDqNGjxcFa2SKvGt6xhLa6YzNMyk0DyB49enfsE8ru3Tq3nur3JX+wfGt8pXJRWNcJePvS8N5dGdfl/NIfdPF7HdnfmFZubHktmPytliPV5GA6Z8/zdNU43qMmtb2FO1XIMkuqna6aexGDkVatnv/fiiv+BT892Dsq82B+mjp3MRwOGriYvxJyHXFXcvQH1uKztyrZasomGA7fI0llcivgvkDkSVVtJaoEL/7tI0cZm5pbEnggFnrTjT5AFlI10Tpp2GGjL5w0LDckXI1bE4ity80IDyuuSENeuf/qrY/wv+0Rhrurek9JTSqt7/N2T/fuZ1nvoYz3wKoa/ScbyeYGqbEjl9F3dkZKM39rwxyDP+DMUmcgaaXUIA3c1Jh2mDnRXcpgO+OAOH7q7rm+EgFfWImYMXTBRCooV7Qw5lHV2wA00MbbCc0d50fwvLBJ7VJMb3qtgR1VTT19MhL3dp7bR3VIlTIkvsiqRztOYdQ+3MYyb5eyZ7dDGQ2bcveqoKwEkohaUOLjTV6UwuuuE0IQfkXvuCt4Ta5jlLYYmeh1DlmbpYufXNVt+5M6ySFnHcaVE5F+C9ebSygdXZpQhGJdo44Kqfk4frUvYIqsuxiEJBz8o8mMyojGEg2PKcHe6DAuQHYducln+FBt3f8Rg2R/2sVxOdCr9z2T5hrLRMtExZAC+m8rfrhgrcOIk5arx9KMjtmKMoCdLSioC2YRhs/N+9obW5eXkSJAl0cxZoEQFuVqaUa1HrZsz9wEJGjHT71unA+iRaR8ps1nTdCysmkNVRn0obScrYRVbbL+R+IoFOSK18pVDVCrMzlrh/nEpdmRDUehp4oDEjPUImeMpYF0RJHd27IVFtpQ3p6aR0lLW3X6PQTkQoRiUrLyVUFhcP+4+m2fiB+3k9XbWjYRtgzFFbk9MKQdqo7iT8p6545UMkPXwxGe5sB64aLxkk4wIvzQtgDberENyegM7WNJT0lRiZmMuheiKwOL6LSe20dHSdBrUEviP9pAdXrHhVf/a7J1QyB1wjC5MkYaWvpHWX+04VSxDHVsyRirkl1qIoy8+h/ChWny6q6/BtNoFJGA8ljaSgjKPsvnAsnkDtLuOkcNAVRH2dFhbg4V4BC3XkL0Liujz6gKITOtiWHbO94W72o4bH4vj25aCY8sozY0CdiD1UQiKI9854TmM1Os=
*/