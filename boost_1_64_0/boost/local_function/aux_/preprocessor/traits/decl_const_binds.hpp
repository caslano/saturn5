
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BINDS_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BINDS_HPP_

#include <boost/local_function/aux_/preprocessor/traits/bind.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_/index.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/list/transform.hpp>

// PRIVATE //

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BIND_APPLY_( \
        d, bind_macro, bind_traits) \
    bind_macro(bind_traits)

// PUBLIC //

// Expand: pp-list of const bind-traits.
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BINDS(decl_traits) \
    BOOST_PP_TUPLE_ELEM(BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_MAX, \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_CONST_BINDS, \
            decl_traits)

// Expand: pp-list of const bind-this-traits (size <= 1 after validation).
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BIND_THIS_TYPES( \
        decl_traits) \
    BOOST_PP_TUPLE_ELEM( \
          BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_MAX \
        , BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_CONST_BIND_THIS_TYPES \
        , decl_traits \
    )

#endif // #include guard


/* decl_const_binds.hpp
i3xjpVzwBdwTwVpobRHpgkug1ZBxFGUCrkWurIupK9wF4BjQBdXwuw5cAC3mt7E/c1D7R8dV0St6Ra/oFb2i1//9ioOmb/Hx/+aP/bdhXW8Kyvh123v19ExVeofzzuknzCqrqUZ05f8ZfnU7WP2rEGn2LG+AdPxTwYSpXn9EQg1wbI2Kp+a2+5n3ayqI5UZzwDp+/CVest9f1AgSXfnHUohZwf7En2FIfOROUf7m5KqzorS6wuAajH8NWJRj8XdWHjutqrTqZCfrbqaReeGzFXyGKj4TjpoQlL/thU+a8nfPVmxMjQeyOmdTYUSocRoDJWyGKTPhA8Oo9GqpK1eOpTxFrmPLq5Uupt5riyHzsC1iN1gMOaCjof7Im3uMObc8YeLIiaPlCHFlo9AXf+ZiTRuF3VXYI3XzssLHYe5VsCAF0swfJ9usByEt7xxqwHz4gthQ+5FXEWRJm8ylbrdUmG9q3rKuiLoJth0RGUV+c6730jB0Pv65Xut6K6usabLeOxeGSWAOOIA8NetkPVEJGyyrrlyJH7xutrTqmGrtfHdwWC7ahGUN6U/KP97xNZwt65tkH13Sq8Afi+mpRiY8uIdrtrrXzdz3PEO519EzZFrXNpnrkxKV//fsd1Zk8a827VJGKv+dKcOtzb1Ev1Ny9XIkmnJ7zPDTVPjLje5YgLf5l5rrTfsq/49Ykeg0118pGVGlxHJ3oHFYr8ZY6r4LNp7Uc2zdQ0nHxMfHpsTHxO4UH5Oc1NUw2+zl+NNmrfky7XoaFM8DcavngouHjMv/bFyk/CfQJsb18p9xcS28PiUT26V6+Xa896mmjQWuB5S6t5530ijt7kQoVuwOVsG48Fiz3ZXR8Vf5Wp5hK/8UFX6GpSzCe36tsiyU/QAGQV1lrnYgabW0yaKkkH7PELsl/Mp1bZ94QW3fss9uKrhR+WdqnwWJaz7js/p3bMvi74sGyhkhAWVvns+erGyeEqoob7HzsfYD2bL/+mwSHQZOBluYrM46TlsGTtSX1nIwbXLGqPBddPsgwyuoXEQOTTkQVmsvY9Z7vvLvqVtracYV+biq2vYCV34Z6hnO4xn2KPcAR5utWKXZvlLBpBle/74qfC7hT1Hhe1vCTw8Iv1H591Hhcwh/tnInqfDb5fr4k2uV5+V/BdjAmTxuUXF6WOSfbq5dP1r5nYxfV6ONZ5XJcwQ8Tdm4r2STuKtU3JPEzS7IKm8OJetw4tUr/78sfKebfOfgH9C/SH0fpngME7efZ6Klz6s2+6JCxX9nR1s/Xza7cvYss24mqbi9pQ91GIXKvb/3FBPz/P8reB66EfhKsbEzSZ75VZp+SmdrZ//MBNrBJYfaRKl6o3y4p+pS3Rth3qsy780x76lyVDZ0E1Se6GPTfc/ffv5vBumgzoUSoblQS29ohv/5Ux+lAQ8hQTrui2a0PQun+2wkzT0bvO+YoTz3/Uj7KsozOX63+C7JMUlJByYNSsrhJdMjxexXG2B4Qy9ferenybtO2kBupdrL29ibFFPhuRCeGfC82suzxySzL1vT21DvGS/572WqM5QmqG/ZFUdwJz7kW9ZsH/updFJ976MI+kPcKr/kH7c7oO9v6O6LOAeKgU6FPsvi/VRplvsx5SKQob6HeS+Tt5ruxCV/STHx2yT36BqfmOzYKikm6bCkgvjs5D3ik5PyQt/PPaSurPuup4GvqbTGat/fK5TfkcHvP7Ps71D+VbgdqmzDee/5+/wxPX0eiyXvd0E7kkb+zNC8O5UZqNg6ZtLexH7UXzfVKk6erg0KP7EDVv2+Ymb2d+cr/2zde8CMuzflvoAy/72Hvtzjk2Pj+DTaJmkHWu9A/kbFJyfv1C05KTc=
*/