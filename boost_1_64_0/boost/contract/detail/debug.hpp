
#ifndef BOOST_CONTRACT_DETAIL_DEBUG_HPP_
#define BOOST_CONTRACT_DETAIL_DEBUG_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// Usually, never #defined (so "debug" assertions always in code).
#ifdef BOOST_CONTRACT_DETAIL_NDEBUG
    #define BOOST_CONTRACT_DETAIL_DEBUG(cond) /* nothing */
#else
    #include <boost/assert.hpp>
    // Extra parenthesis around BOOST_ASSERT to be safe because its is a macro.
    #define BOOST_CONTRACT_DETAIL_DEBUG(cond) (BOOST_ASSERT(cond))
#endif

#endif // #include guard


/* debug.hpp
1TMWmyHXo4zCeWVdt9vTnWAyAydsqgfOVm7jObDqC8ypQTt8C2rv4TSw4AFwGB2QRrgwCXpHKPPyDeIib8xgpCyAeuBmPiO2Z++EMt6SyLcyQMwZd2qwHSh62nTp34J35botol5JRZJmO/c5Cmj+6dLwg6aeCD9/vxlsWopkbUUv5GJwstfZps4uHPdBDJxHKfzHO265pUb822Bei/hxPdYtBbbkNLLQUQzyquXKgGOuaaokl92A8lr0uLvLLnFq0bsg/HrYpFJKf8GHh9ZtbTYjq68Z9SjMf1LbwI2UmHZYYlRmKGbMMM+Mwmh2W9MaEK+RII6vdmoHIlqjhbU1fy5kU+7dziVI8pmOCoti9VSSbBEsMBcGrVWlekehmwjYp5T8hDo+/aC9isrz9PpgKGEWIMynrCGJ5M+ytM/PVfPWX3H4j56tXhVGPR0QraSmcQz/+STfL/D4gc7dWN5szS47m3t3h2wIe9om/C2WPEhLrqQJj9GCouoEPlub0VzLnC4F+BHyLD6wo06wmGSsYY0atitJg6gZicD9mpfMN4brlBO91Ma1UcjyMg==
*/