#ifndef BOOST_METAPARSE_V1_UTIL_IS_LCASE_LETTER_HPP
#define BOOST_METAPARSE_V1_UTIL_IS_LCASE_LETTER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/util/in_range_c.hpp>

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
        struct is_lcase_letter : in_range_c<char, 'a', 'z'>::apply<C> {};

        template <>
        struct is_lcase_letter<boost::mpl::na>
        {
          typedef is_lcase_letter type;

          template <class C = boost::mpl::na>
          struct apply : is_lcase_letter<C> {};
        };
      }
    }
  }
}

#endif


/* is_lcase_letter.hpp
5t0TkcxR7576nHitGah9PaKxvhEbkzIb683WmEltbBAAgss9I3G5L5PLUgaXt+0zkSVOrI4BUAEqgXdEKnsyqezLpJKzFUQ6ot7+mLcPAwfEIw5cb8bA9WQbOKs6cN3xxfuTSUCBVNfme8semOTetq8E7ahscG1eLTL3uit3ocdAn55tZ3avLg9w6kJXG+FC9w3WSsEpGUtssE66dIp+fUFOR2fHfL3D6OnJTk9fdnqkTHqwpEzqkoLYwKKqk343eTg93oEaaefkNHp8zuj1tphf2vYaCLpDNNJTAgK1IdDIdFdul8d0WL6d+X36TEAOH1o23l8jnZtBkq+/Vjo1jSQI9ugNAOdc0PpdAhK1iaYR6q7swATEzB2Wb2d+jz4TkIqcsKpyops0dddIPyrNoKm7Vnq4NIMm58difxyF0jTSh5Y0fX/8quz6vnRU+v7rE7Pr+7snjlLfXzFxBH3vmzhKfT9l4gj6Pn/i6PT9yxNG0Pc7J7wHfZ+uSm+RJXJDhr5fOUyVrsrU95Kq7/v1mggYqWcaMvU9UIIITROtOoi+7x6RyMEMIgd0RGbq+x5V3w+mKTegpOZqyNT3wAnjIKXcVh2evlc06YiN9WQ21qdrbLT6Xs/lvkwuSykuZ9H3mlUyIpVSJpW9OipHq+/1A9ebMXA9uoEbWd8LhnpIBGgFSBKoUpxgB9Egsk1Upz1oRCu5hSUoQAnI07IbmM0fI6v/FeOzqf+Pjs+m/jPJ6xmRvL4RyZMyyRvZGugszmYNbC3OZg30cO5gzEBfOcmDftcNETlPuknfdv2ws+gWFqEERehnKr+B+fwxom1QUZzNNphUPJJtwH6vZL9Jod48IOWrSDnqpBsIKCGBRIYS9DOV3YBsvo9sJ8Q82eyE2z2GnfBfm2gveGgv7L8d9kLM667BCqiFpqyTFi+mV8EJuR0J95nCnHPxfbAeABT1DrV7B01IqrKEoLRgpSXGQtVE2myQv1AQkbgNYhNCoNo/4Gp9kuDMH4p5mqN+SAK+Y2XG6pHzxainGesROVAjeFdKlzbbhoMu/aItiuwUMH5o0PZMaDsA7Clo/NCgnZnQTgA4U9D4EZ+ZTCbRXTPoT4wR/TOjf+g5eyY672ptt7BzQ5E28kbVRciIOd2QdGnLPyU9UWpPSRUbYTK3ppq6p5EUs1k0WQh9APi0HauMuguowVF3+tLO9BcQYdRpSYlLVDJD7ulrpAw0EOsAsZnyDC206Ha9w2vYs9Qg6D3DQUeAuz8NLmpzCHp39YxILgTrYVK7a+9oid21d1S0AixFKpUzR84BiZ2mqXRiVoyrO31cMx0KmqnKrhelZDoGHzXSHA0y7p3WUZErUILeovgU2A6VbYb0TpOPTsrHl2+CfGz3DuDdhG2VuqGyRzqS8R/kmUzNYedKFIVK8dLGl3F4MZnx4thyAAIkviZPFZ0KaL0LIqS9mfLDQdFSzpoiH+7s9juY72R+AWq1r+TPQvzTtmIHnMOVMfY92Df1OfXqWFvqGN+TzaltWFtGbWCttdVJj6RVT8kGVk/twZqzVofS+HRGdSzVtNrYgJ2dtbazTpqdWVusHlR3KFxztSwEU7dQGLe0uVadihfdDi5GQ30w1elBTQakG5vCMlR3RZkmJ0qy25uDw9cwMwdomq/TxJQFdEQ9dlVokRhqR1JXT4lf6RyvbuBSAhhcUrqRA+IIaDNX2sYrebny8lQFhpabCZknQ0KdRbabo3iGBxz1eZVt8fwcnYKKb8WUVNjurpN+5MgylRa5a6X1joy5JHqC8XAr1T11UihrdU+tdGVmdXZazAZOdjGcX8QIPiWG80XXqihelGEHcyg0oWk1dZrykKdbvtw=
*/