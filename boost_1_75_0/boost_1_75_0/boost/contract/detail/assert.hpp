
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
g9sGnK2aaTICbNUCmzxiSHEIJgGXorQpCjNEjhxGWnCtoUwK5yyMKeFgYCxDmAKMcfKlv8TAJIMtqzp8ayfnlwyMhZ73ADiBcw2RaCRZhmz5LUjOPAiZKgzzIZQSEIKqCTLhwc4DAL0rFOr4GSLNH3EniJNnVyoBV2lZa0qMCw+GxX0L+AcPSOzJkh0mc+x8CViNXff3aQ5JMoUoaSA0I5UmSdKgQTRopHkiKo2nedAszTMNKk00z0WlNEiK5jlCpdKkrG+fEx4ez+B53vf//a/vur51XT/73vus+96/vfZaa+99dw61K1bHFehebpeLZeLtdJU4iCEs4B27zrlRJ530Svfsnb7JjjFvke3r3Kd2VS0SjvAeHOjOjvM+5LQQw6zRWEwYZZGekaHO5s3gUaux5WGqU49SA53Roq4xvV3eG4anrZ8Vhq4fwGD66VZq+P1Xuhzno/3tBxpkHcLX9Z7ZXpHrOq6/+URfaNMFoZPbnFLDsRdH9nHyVgeMkbQVuAxXRWp+pHncfe7sqIKj0qaXzC67qjs+mk+yFLfc6yAQK+Py43XZvGPNAa17Yl6ESjuoiMXuldCnME9kXT8wkepTkEJ8i1GW+jplEzUtTR0nxz7ze3HX1iYeDn4vGltE9uTApLBexs0qv/hg2TEnzqxULcmUSZbpKV1jFYzrKcZLMm5TbYbU3bWktGd3uFzROqtC/7ZpwMVMp8DC
*/