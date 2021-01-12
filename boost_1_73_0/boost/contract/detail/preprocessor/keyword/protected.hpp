
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
5tNpN5I+uc5lP3NM1Ebk7j2ufZ3K9V7WPrXeMy5qpn2qjp3ixkkf6qHrUkwi5kjMUPwdJflbUHdsZc1xsgrg0/fF9FTPFb/70pfyxPXXqU98O+/zmsOp4meCtQcpGY7x6fPi4wmZ+64GJ/d7ceLnAGt3Quzpq+/bxOPXrqWOg/AE8bO32m3NZ3AX1op/et2KjneTl9/nvrTi2xz51NHW4E8HvvfZS7dO7nrKk99UNu1L8+5L
*/