
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
0z6H9cA2A5/JXG0dnICnUaUedhHLsl6nCOz+LAGuJys8Ejljw8y9zAqLgwLbnVigie7j6uEx7i81W83diMYkSaMv4TdS3k33cAQ+pusf1GuFWon+NoiLb9Qz5qV7GMN3POEmsAvh3kon5vHIj6rG26iwMARqX2aCIuOtKLkSCZamLGUzrRgg/Vvo3zNpjJVa9T+EtyUV+e/g91OqMT38fdAnAOvHEiyZzPBvvBVaHCumLRlMRxbPrNZ8uMAZyVM=
*/