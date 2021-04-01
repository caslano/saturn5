#ifndef BOOST_METAPARSE_V1_GET_RESULT_HPP
#define BOOST_METAPARSE_V1_GET_RESULT_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/get_result.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class>
      struct get_result_impl;

      template <class T>
      struct get_result :
        get_result_impl<typename T::type::tag>::template apply<typename T::type>
      {};
    }
  }
}

#endif


/* get_result.hpp
CiUsD792S05oRCjhqK9jIQd7oRqAoDMxylekpvt48HN5TiL3T9CmLRUk9jwOhpTmCocp22BxdAm+rjZyf8OCdJROwoXVsSCsrVDotMmlwPMEwidyx2bn0Qrfispa2zxtioVRCMNVSExSHSlEhAJlvRT7iRU8+glWw4f8viuBmATQpmCX+RLIuIcgGiUKpUVD6WJgHXLKL8L6VIyvQZ9AeiikVFjNylOJmhYEOtDe6/iy9NHgB8qrkSsYAFG0YCg4rUw4L/VkBNoJQaMGOoiIkP6aILUYQE846Pz+q03MyenK7dJ0oJTz31HodxdpmR1whYI8WlagGRpf8/izBLmw5bW2zHZ2ubeBG2Tv5h9TBeFh9dXYuy6n6mQ467bFMAziVbrUfrnVCVGwTy3R7xtoh6uBb9X/aDOjWqK6AO3jjg1KKDQwbYb0v6o2qzO4nFh3ckdEUUsfzonWK+mH6fi/z/YAfEVrflvI5TfJgI0YYgC5eoX/1lZyde3Y0dPXTOvSmyevjSRAu+Ac7OEpe926TVSIQEwTm6PEjpEJmtDvmihQ79bXHtM/M2OqUw==
*/