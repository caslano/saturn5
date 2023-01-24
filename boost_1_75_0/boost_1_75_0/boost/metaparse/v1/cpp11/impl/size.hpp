#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_SIZE_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_SIZE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/fwd/string.hpp>

#include <boost/mpl/int.hpp>

#include <type_traits>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S>
        struct size;

        template <char... Cs>
        struct size<string<Cs...>> : boost::mpl::int_<sizeof...(Cs)> {};
      }
    }
  }
}

#endif


/* size.hpp
yYvSrs7LiAXJ4bwRd4i+3lswwQFCwnplfdDW4LNtwkiOb7lqBKp/fWqgF9eACyhFsD7LhmO4Bs3Qvq4fbXp/iexulWqX24hKF2vf/gQnwN0U5L6H9JfHBy3yoYnqKtZgoc4KcwMEyw4ZOiv0h+zdi9nQgDpFCriberCh3+4mfA8CG5oXOxu1OgYbWmojcQDY0KtGczS3PajosT4yWnRbg8CHBnb+gHqjc8u90YsodCkoONCgWldKuiziQl8YyVzopsAogF61BetWVqP4g+zYyXGWc1+2YDlJA9L2KnkrFXmofJbuGn4KJzWYf1L8jdXGG0pTWwRVPn5P1I8umDmi3IksPNBSLaLKmlgM/SRsLN7QH42GuLolD5/h/gVgA8A9M3wkOlNub7Sy64bS+Fjuhp0dwbIOHyqYAdOL0N+5Os/E9sCRdsb2Uah6BOGZsJ1Pw2JtBFakVYoI24sA24tAMAlbYifn68pM2YeKXLgZVMJ5BuLDbQrsHEivv/WjrpMxoG2ZFckSMPzau8+gA9fHwbJPYX/cuwFRQdnuVzYEdmpBm794krTuoQyclrI50nX9outCd0a6ChadE8qJtOVxZroR+Gco/hlkBjf1wT92RO0pNfvyYoFIW2GoPdLmOPFzI2r2jYudEmm7oecjnfCIZylIIjX7rvTCML60rv8yZTWuTe76pS27vvI6nF59Q0BfX+TeIi3zkq8TyjWK
*/