#ifndef BOOST_METAPARSE_V1_IMPL_ONE_OF_HPP
#define BOOST_METAPARSE_V1_IMPL_ONE_OF_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/error/none_of_the_expected_cases_found.hpp>
#include <boost/metaparse/v1/fail.hpp>

#include <boost/metaparse/v1/cpp98/impl/one_of_fwd_op.hpp>

#include <boost/mpl/fold.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class Parsers>
        struct one_of
        {
          typedef one_of type;

          template <class S, class Pos>
          struct apply :
            boost::mpl::fold<
              Parsers,
              fail<error::none_of_the_expected_cases_found>::apply<S, Pos>,
              one_of_fwd_op<S, Pos>
            >::type
          {};
        };
      }
    }
  }
}

#endif


/* one_of.hpp
H5x28I+/x2RPi9FyPbxNmqXPSZ0bfMtyMyMkNx7lJVUyk9t+k8NhMiBRWBwASH+0slyQqKDynrCmRshpvAvD8LozD2MUdpzTFlO+dJ5m0d5xVCvk+hdXQldqg0fY5lCZh6uf4p8xHAzoZ2asaVKeB3+3HCyhGUcLr8olVR4MupouIfuKUvZjZ2FP7f3xHA/sky6mAONbAjfyvrDb/Si60fDxOfVLFOfXs/+nbgEgLbS3v5W6wpML2FyPbDyAhWriSp1m8OIe+212wZkFHJUTA//kuVUaMRTdol3Y0YrMqQusmPmZ203xIEupZEJOcGfbYzHWoLwA9DlLqmDPICeJu5DxP9NPIfgLN0Dy894RWEHp6MAAbiStOJTPqM3zl0B/0f425mrDFBJJy/sV/HpIqxpOpgX2jEcDtT9p/kj1eniUmhOfL5dQURyzw99JTYZQEaJaTAnfP7jEdSHRJRxI0rovRaKhqUWMt/FRSuL6QPj0fSwmXXJtKQ9GnGcBkemLFv2yqU2i/XqOn6nwzpLjB2w70nfyvKtvnHRRNSoSCo7W6uOcUNM0IP17gw==
*/