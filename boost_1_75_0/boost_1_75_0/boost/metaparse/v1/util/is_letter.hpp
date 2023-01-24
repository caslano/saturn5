#ifndef BOOST_METAPARSE_V1_UTIL_IS_LETTER_HPP
#define BOOST_METAPARSE_V1_UTIL_IS_LETTER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/util/is_ucase_letter.hpp>
#include <boost/metaparse/v1/util/is_lcase_letter.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace util
      {
        template <class C = boost::mpl::na>
        struct is_letter :
          boost::mpl::bool_<
            is_lcase_letter<C>::type::value || is_ucase_letter<C>::type::value
          >
        {};

        template <>
        struct is_letter<boost::mpl::na>
        {
          typedef is_letter type;
          
          template <class C = boost::mpl::na>
          struct apply : is_letter<C> {};
        };
      }
    }
  }
}

#endif


/* is_letter.hpp
+y0B0bfFmtn0LP3+/DbGGw79RfQOH9epwtbEbU35H9SQckU9jYinjjfoSGDIEVft7+tnUpgTHXBZ0DADk7aSm5EN8H9QpBi/P84yTjFOa0D5i1xnqpCXV1/q95TndLcuIJgYxZtqxbqHc3rAqKvHU5BXW9Uz2uNgvv61KEptdv5cY06b6uJlAvhxVaxxAvVvMTPHRhm5BxbKopkKExM/My5MkhFFjQp5A7/jlKVLv12c9aVEwvVTclKeun7ZHfoqbaKwmWPrHq2qZ583L91ho1RP0TV4Y6J6eMdGwbhleRrqjDCwTr7zYNH5uxzJHk/fy+cnGKYJl7IjCdZai6gvH8mqws5Udx512lrRaTh3Jpzfzu/eSk6oUI5+yUjPPiDKBKBSuF4OdRo67Gr74qDG3Yrq21pf4ZLvIz9ifjj9csnv8NfcoQJ8SbHFZ1WrYVJxid3CT2qMy+NyaNY4JYAVtHgMN4HYbJgGAY4WkLr1jVvyQ4WQK9c5r30PB/I2yIRX+MM94ghNd852k0NBb2GBs+ShzYtpYpcjkUpHb6qXlwU7IyTZ/F7W2s6pQC0SauE8aXBCra0/m1fBmK7AQ3ZWKo8Ve0Ve2VN9/mH52DjqlVoChjo1jDuZLrbt59fWgqSFPyYSJWd39yi4ePocfa2/OrzW5I8rsXTxZ9bQ03vdk5So5cDps60OYWXXDixW8iSJviK34Gx+w+CQPrEG
*/