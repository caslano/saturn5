#ifndef BOOST_METAPARSE_V1_IS_ERROR_HPP
#define BOOST_METAPARSE_V1_IS_ERROR_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fail_tag.hpp>

#include <boost/mpl/tag.hpp>
#include <boost/mpl/vector.hpp>

#include <boost/type_traits/is_same.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class T = boost::mpl::na>
      struct is_error :
        boost::is_same<
          fail_tag,
          typename boost::mpl::tag<typename T::type>::type
        >
      {};

      template <>
      struct is_error<boost::mpl::na>
      {
        typedef is_error type;

        template <class T = boost::mpl::na>
        struct apply : is_error<T> {};
      };
    }
  }
}

#endif


/* is_error.hpp
2aD9FAFU7W6A01jWXXWXMdU30MfEfpD6Rk6iEKwGDsnw8iSEZMBsw4e/A8fKlnxLFKFWdgsVV1zbRGphGT+uaFJMWOgmCKYW8HgQ6SQHxSJREBH9KCzkbO2qIwpIXz+TjhWYMhcsslneoG+uFwV37pHV5p3QdRe4B7RB0DSquMa0/ahEFcBuor2B+2LYvzhPcHSiJ+ArYVeefvYYD4MLxn7C/naxdyUgHWit34G2fl8Cu2tZtwjkDsHRKd5AXzZh2sMHj+lpgSml0KTc9OBiAbiTi55W7b1Ox9EwlMtmrKSoMu/qdFyD6GIkA8eNIHq6SwOjepsvYQhqb3EpQW6WsSPrOfeLRvNnd7BEOxSyTXvgv1T4LwXDXoCjBdLIs5WPDj9hH+jh0nsgHmORuxRKvOH+GHCvBjYU9K2weGTX3Ws3NuvYrfv49xcISWPiXB7wCiKOqEmbUArrsAvrUnpoesPkeyz+sUz4CXpIdt5ZyGx15/X3IG3hptbrW2K748mKDPRhRuYZ2yi57p8/En2lNhr0hTUkOHId7ZpRXy+UhQ3S1U2ItY8BoxjrDqhwgKnkDQLiS+ZGWI9Djul6wL9XdZcH3Mer3HtIfxPj8cH3fDxWid0IAFjZCCQZ9zwt7imUY7YRx4xNB+L1w4AZt0+i2xE/jq3vKkrJw+GVd5sGsGeWYcJnwxuVhYOH1Qy+qaPBQ7sLmeDBuEfjteUH
*/