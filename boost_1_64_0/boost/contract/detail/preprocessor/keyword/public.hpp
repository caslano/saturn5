
#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_PUBLIC_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PUBLIC_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/detail/preprocessor/keyword/utility/is.hpp>
#include <boost/preprocessor/cat.hpp>

/* PRIVATE */

// Must expand to a single comma `,` (not local macros, do not #undefine).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PUBLIC_CAT_TO_COMMApublic ,

// Must expand to empty `` (not local macros, do not #undefine).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PUBLIC_CAT_TO_EMPTYpublic

/* PUBLIC */

// Precondition: tokens must start with a token concatenable to a macro name
//               (e.g., a literal or integral token).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PUBLIC(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_UTILITY_IS( \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_PUBLIC_CAT_TO_COMMA, tokens)

// Precondition: tokens must start with `public` (this can be
//               checked with `..._IS_PUBLIC` macro above).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_REMOVE_PUBLIC(tokens) \
    BOOST_PP_CAT(BOOST_CONTRACT_DETAIL_PP_KEYWORD_PUBLIC_CAT_TO_EMPTY, tokens)

#endif // #include guard


/* public.hpp
w7kBWzzBl5v4umnVvelANG7Fg+MuCQl2WGvxXEy8eAyNQJao5geW7TiADtjJYohA/Seq/zc2oncyMqK120ZiREflDtIpZY0Y8h7eTp8Izhx/OuOwlpTjI6EuWK6AiaHYl+5/2ujDIg/kIOVBpm429TdAk2i8ALdCqc4MjZLOLVqWTsZtD6yxuApZrWPUTivLxV3nfl1jKApL43wvUhhS7yOtVPzyiSjonZvy64id9c5PvcruGjZYeufKXC6nIMuE62vbHMp6qj/wPaCInjS4EsbByc3bJsHwxdWyod1GuEpOJuMxtdbLhs6U3geFDytcwn3Zh76hqwtlPgtz1jLRLLL+nMurm4qTU1RP7mW3acWzEt0OTNIYHCSTpmyjJ/ngJatFGJs+KTNdQr2efohpmZ0+elbLCmWavUhySkC9ssAdy+RNKKWkrMjWR+0BEBIwKjIwb7MQ6ZobWcX+QGvBqpzlhKniwFK0/UHBU5RS2blZ01iFOQOUP+UL5Bs6hwe9I3H9zhKGsU22PWBMZaC8l/aEfiHkf5HFQG7yolDaQnsAMLKgsHSsovMs1Q==
*/