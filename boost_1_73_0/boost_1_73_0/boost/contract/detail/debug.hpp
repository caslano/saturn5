
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
TymWqeh6ZH22AOoGHYvhg6K2pFLd5Jq2/5xDJbbLZTWwYYiWo87zDB0bqnCA4fDM+seyxgcdTaakoq0yLb7HKCavhIOx9R9B6I1nhbDn0/6yLEz98ghGSr9ozyLXIipYx5770fUD970f+MnCcvPcnOmnzvGRc9oZzLxkPgvhoxvMPWvWFSq7BF4aXQMzh5KZMN022da1aPDEMaegMZyH12F0E6ZRJ1jtVAllmjuIPQ/cII5wOt/P/q92GKCabBg82ERTL3zexPoXUEsDBAoAAAAIAC1nSlLbcJR/fwQAADUKAAA7AAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9DTE9TRVNPQ0tFVEZVTkNUSU9OLjNVVAUAAbZIJGCtVW1v2zYQ/s5fcfCwwQ5UOS/Dsq5BMcVRGi+uZFhyswAGBFqiI64yKYiUHWPZf9+Rkpom6Ys/1Ikti7577rm7507uogcHP+xFXAMH330l9p3gC6+d07SS/7BUf9khSR6g+UPHBV73CDWER6+HZAB7eT1A33olbawz8z1J9gi3MCTNx9A4LxLzFU8az9Z/JMtdxe9yDf3RAI5ev/4dXsHx4fGhAxdUcFZApJlYsurOgbPMnvyZ0/t7V7G3DjANtHCf
*/