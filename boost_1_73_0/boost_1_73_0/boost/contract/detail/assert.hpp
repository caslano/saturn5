
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
kSnNSF2oXdcwuvAe5flPV8Ky/Srg5OQhe1MaHqZ9PfC4wBasCJcZ7j4dJ+H0BH4/PIP+wLjdoWrN4BTfbRHuEptd+pOJN7qXGuDaKByuhn+vpWPt3riZxLFabIqDU1GrslZwApkoKe/uryl0NqstPGb1y/2gu5SeoD13/fGWtqV+wju8fGehj25H3WTdphm1arqPM5zH285upHq03b//0rWYfkOA73F4VOhnPS8oAlJckA0vBEn1mZMInmB67RmP+7PSx4mhejDctGF/qN0fIPbenjYqPgulGY2/7dTR08I4GTNDxP2Eqrpn/tiPFpabps3/Jq+dl0fOoXGYetF8GsAndzz3rKnRWxoSDyXGhTTjrzkutCCyLkuhS21O88YRMwnCqyAOzSTWQdi3zZzrzDwP3PEsxKPmbPqEBtDB8YhN9N3lyh+Phu509NGNhhfbt9b/UEsDBAoAAAAIAC1nSlJK53HDZwQAAJ0JAAA6AAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9DSFVOS19FTkRfRlVOQ1RJT04uM1VUBQABtkgkYK1VYU/jOBD9nl8x6kmntgopLCtxHBy60JYlR0mqJl2uUqXITRzi2zSObKdQLfvfb+yksLDsLh82
*/