#ifndef BOOST_METAPARSE_V1_UTIL_IS_DIGIT_HPP
#define BOOST_METAPARSE_V1_UTIL_IS_DIGIT_HPP

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
        struct is_digit : in_range_c<char, '0', '9'>::apply<C> {};

        template <>
        struct is_digit<boost::mpl::na>
        {
          typedef is_digit type;

          template <class C = boost::mpl::na>
          struct apply : is_digit<C> {};
        };
      }
    }
  }
}

#endif


/* is_digit.hpp
3LS7f7Avjj0+PmfmzCiRQW2yVGPMIiELRZ8NHj5Vk+uYTZNk4RZ4fUlYxC83EW/B7IZFDdbVgUJ5alKQKisx24z8A2q/ZeD9uz4Mej2Yf/PYJDUYQrLDLvQe4U3t6abfg/4wHD6GhHn9kXhshc0emxBsboF2B16kG/TYWEmD0gTfUa5NGcJXF5KYGaFkCFml9BUqOdRoWX4ZXpptdbmYCF0rLdpHhahQplsc2aV///DwBFmZNhrNqNhJeXgCVVvkSJsmlWvi91h/cD/8Qi7Ymq0bRw/IjhsYV8JqaJEjizJ3IEhbRsxKY2p6cDpGVjQ+mwyBgsKGIBCQyhz+kXEXPoUp1c5AMCGmliDK1HZrHxxz9aUKCFLvTJd2QmbVLke/lQ8570znq2S2CDtWeDFfJtwWbkUpgUqtOb21vtgoaRzJSYaSMK7DMauxqaCzWo4nsyWvxIftFpeK7Bba6Lu6ckSO125O7hLdFQlxHx1y3r1jI4oDuFFKC4MNmBLdHECZavhAlODrUhmfRXuHtTk1yqhMVTGzDraKp8Hz2JTEQvirYI/9pB4Ez2sSp8HZNRXvvL8sV7P5m8eeswxrCt/yW9ttyvgswSLnC7iJ8f+w6j+YeFfqyYbBlQ3a5OTE0YUWN7A4fu4Tv/xrfgNQ
*/