
#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_PRIVATE_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PRIVATE_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/detail/preprocessor/keyword/utility/is.hpp>
#include <boost/preprocessor/cat.hpp>

/* PRIVATE */

// Must expand to a single comma `,` (not local macros, do not #undefine).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PRIVATE_CAT_TO_COMMAprivate ,

// Must expand to empty `` (not local macros, do not #undefine).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PRIVATE_CAT_TO_EMPTYprivate

/* PUBLIC */

// Precondition: tokens must start with a token concatenable to a macro name
//               (e.g., a literal or integral token).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PRIVATE(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_UTILITY_IS( \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_PRIVATE_CAT_TO_COMMA, tokens)

// Precondition: tokens must start with `private` (this can be
//               checked with `..._IS_PRIVATE` macro above).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_REMOVE_PRIVATE(tokens) \
    BOOST_PP_CAT(BOOST_CONTRACT_DETAIL_PP_KEYWORD_PRIVATE_CAT_TO_EMPTY, tokens)

#endif // #include guard


/* private.hpp
P1LE1/RJVn+wuJq5QidwP91avY8ek8KE+yHg6n2oRoVbFlfvo8foE6++n8XJj7+n/TnxfX1lC7iXwri3yFhcgV0tMFgWdMlSUVGBmnAtsPoCHOniCwywoEuWL/f/M/H8Q0HtHlY/iTWu3V33J5HAtcv+/OxZFCseYj+L+L9o9/wn7Z7ft8v+cbu4JxqR56XftUvgfuVpZY4hs/6hXcIc88UG5tbftUuY/2Yc82vf2sVxzbhUvPrJt3ZNMiurL/OMa3f92m6Fa7ZClvX0wHzXforMypzM/Qsv9MhrX9qFrazIXL8O4xSZ+Vd9TRyHb/Jbv8JWZN8ZB0v+tf0U5tpXU6B/zF2/8Vxt97TCkKPiu/HqXROTwA+AGBH63j7uYuI4u/32vO/sfAq1u/7RvCBH/sP5WsCQ/dSOJotczJz8h3ZxMTF9cxwXLPEP7cghL+kjLrrC137frntJD+Oqe8pVV/d37boSZOK6+quu/UO7rtVXJ0dRsdqujwsQd0/936Jltf3nKPq/0/6z4Ntdf27Hx+mfxfuftP8r+S0P4fM30deyAvP/y/9u+dXKX+39498D/3Kdgd+tM7h/ccsLFq0zFfirH9cZ3L/wZcn5aZ1Z8Px+ofD0X/jRj/zn/b/zQ1mJ39cd539w15/q/qt1WRATg9lv9VkJtEhZu85+qc/icxAG5cbVugeGzBxlXJT98HUJzGryRVkSX8daYcjw
*/