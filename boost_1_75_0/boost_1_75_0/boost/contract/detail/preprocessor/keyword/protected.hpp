
#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_PROTECTED_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PROTECTED_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/detail/preprocessor/keyword/utility/is.hpp>
#include <boost/preprocessor/cat.hpp>

/* PRIVATE */

// Must expand to a single comma `,` (not local macros, do not #undefine).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PROTECTED_CAT_TO_COMMAprotected ,

// Must expand to empty `` (not local macros, do not #undefine).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PROTECTED_CAT_TO_EMPTYprotected

/* PUBLIC */

// Precondition: tokens must start with a token concatenable to a macro name
//               (e.g., a literal or integral token).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PROTECTED(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_UTILITY_IS( \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_PROTECTED_CAT_TO_COMMA, tokens)

// Precondition: tokens must start with `protected` (this can be
//               checked with `..._IS_PROTECTED` macro above).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_REMOVE_PROTECTED(tokens) \
    BOOST_PP_CAT(BOOST_CONTRACT_DETAIL_PP_KEYWORD_PROTECTED_CAT_TO_EMPTY, \
            tokens)

#endif // #include guard


/* protected.hpp
icuKGF8nM7eWRc+GU2Srn5ORra4cs+au+Lq5I65zcTFZq9XnafqL6XqYo1z1pT9xV3F8OvqOr5j5akr8Vl/A+P9Wl/Awv2T+bXwo/6CHYb/VUbI6RS7miU9Vq3VdXXJ8IkLZCtX1cUnoi+Dq35v77+sLv7Pv7+fr9/P5R1GOHITgfwNf/fy38+T/nJ9/MYPnarp3R6ccvOhZ4nwRxDwsxcSRC8qiErfeE+tZnkLup0d+ylLYEcRmr+lZLlzyQC6CPhdDs4kr9YiRS+i5i+tfc9cV03fXXzX4aon+/bbYrAraOar/NLh/ID/uO//gv9v48k1cya2EuN9TYQxlRDGGfLsx7fVV2KCr6lh11rXY8cHBChtddWxMTALGWUkUoy3KhVHaTQi97a2gxLYV5qYnMGWpCZ7u2pJWMc5XPS0luTzlGUgt64tyICPI2VKJea3YaG+npaWKuJWpKKtlhIMpRpuV0nJpbkksLybIUpttq5iNPJ+lpbwoWW9rvWWIpS65s7q4pbeu/DWZ3YTuKqzU7hPjo+4qzKSeTVVF7qaizJ6m4lyeo52duktLc54ZId6eukd2YDqb6jFBhiqYmKQkjBIDIWa0sx0zNzeHqclJxcgwUGJGBzsx8lsJMaaCzJjBzlaMt64MJsnbBmMjw4dRZ16LsRRnY/n8eYmlKCmCxVlJcP6qkqR5jI2hmLe6JNlVSb55UyVJMlNBBrHO
*/