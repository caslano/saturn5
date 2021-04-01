
#ifndef BOOST_CONTRACT_DETAIL_ASSERT_HPP_
#define BOOST_CONTRACT_DETAIL_ASSERT_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/core/exception.hpp>
#include <boost/contract/detail/noop.hpp>
#include <boost/preprocessor/stringize.hpp>

// In detail because used by both ASSERT and CHECK.
// Use ternary operator `?:` and no trailing `;` here to allow `if(...) ASSERT(
// ...); else ...` (won't compile if expands using an if statement instead even
// if wrapped by {}, and else won't compile if expands trailing `;`).
#define BOOST_CONTRACT_DETAIL_ASSERT(cond) \
    /* no if-statement here */ \
    ((cond) ? \
        BOOST_CONTRACT_DETAIL_NOOP \
    : \
        throw boost::contract::assertion_failure( \
                __FILE__, __LINE__, BOOST_PP_STRINGIZE(cond)) \
    ) /* no ; here */

#endif // #include guard


/* assert.hpp
wY0Ik8h5ltLY6UckYkesKpfi1lzNeou4gs3nsQUTgQU245U20SrRC1IagfKK0tNaCpqv7joIu24zliLWMGbz02HMsAh2jCqbUksG3eXOf1QgxJRPH46OXe55OZILuIvHsbtRtnj1MYehkmCDVCJKgmk36Bua7kHqaCvjZ0bN5f2g4lOhUBsFyNdYKHdnJRP0r6syoTn01nk8DVuucnkv4hUqjoTikPLHjS0FIdhJ1uZOJoTaRP8uQr6Z6gSo5mJLs7Nr7r+rILzTSbKuwojZNSX1T/5bPLRZFQY2Gd4dFal3xD97Kg0rPKHBK/6yMt1BixNTg4tsOJ9z3koBgNESQhsufoT1FfsCPwKgX/vzgqSEQkny+8TLAGfI18mt8G5Y4Ua0pKbmsyNw1WcMltnRIMG+RMvr94vOoFCRIZ+Lv8FHPvwWIdPeom1AzhUiNeEN+krtS403y1y33kQ6RfS1JzlwP20EeDNwscVIxDp7KRimE6SAn0BQj5GrPltmL4yQD6rQW1tpRflM9tAYtMlCEPt/eNldSWKPzJPkZ9vhJijz2pYHX479/GT+Zw==
*/