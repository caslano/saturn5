
#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_UTILITY_IS_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_UTILITY_IS_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/variadic/size.hpp>

/* PRIVATE */

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_UTILITY_IS_1 0
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_UTILITY_IS_2 1

/* PUBLIC */

// Precondition: A macro named `cat_to_comma_prefix ## token-to-check` must be
//               #defined to expand to `,`.
// Precondition: tokens must start with a token concatenable to a macro name
//               (e.g., a literal or integral token).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_UTILITY_IS( \
        cat_to_comma_prefix, tokens) \
    BOOST_PP_CAT(BOOST_CONTRACT_DETAIL_PP_KEYWORD_UTILITY_IS_, \
            BOOST_PP_VARIADIC_SIZE(BOOST_PP_CAT(cat_to_comma_prefix, tokens)))

#endif // #include guard


/* is.hpp
/Kussqrqci2MJSlgFmFPt1i43rcX4SVKwyIoHjqHpx95GWtRi6meLVvcqtML07sIX1WrAthOa20OkipDm0sicNySzkByCPs9fvjLNAPICCJaoJJQqqy5g7QiTaMhJDHBcR7htulnZBtNnV2/SUrZI2vAfcMZMaLtVuEJ1fcWmakfHh7I6bxIusWR6MFAoTSVcMk1CIE7QG6GntEB8sv8vuJ9DMU9P1insZ5xDHdcm6BUcdswixZQGFvxMxoKpVEnWVVCBbsncaEG+BDDPz0ynG8Ygq2joMtBhx4lkL2tspQBZnJ9KMl6RRLNT0Vm72ZU/FQVkhSGl0Y8gT/MKt6YIu2sOQKH2N39qHlAQsJpz2zI0ggTSStQHDPt5qz3R1oQA1muSwxnXEzmG8Wd3vfZjL82cm4ViIfYudLOKTcFL/47DmItsf0xkTuNS9U826ZuUV2gcoj4ILPKU9sKsL2q08jVQ3g9aBPVaA1YJ1MWg26V/bv4NQ8U+sHEP9KLsksIQEXGPyznsjqHujQ3ZYGnCBrKrn5UlAamhTgU0Wz9V7vtmfwcXu+cdywWaQ==
*/