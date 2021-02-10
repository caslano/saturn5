#ifndef BOOST_METAPARSE_V1_UTIL_IS_WHITESPACE_HPP
#define BOOST_METAPARSE_V1_UTIL_IS_WHITESPACE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/util/is_whitespace_c.hpp>

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
        struct is_whitespace : is_whitespace_c<C::type::value> {};

        template <>
        struct is_whitespace<boost::mpl::na>
        {
          typedef is_whitespace type;
          
          template <class C = boost::mpl::na>
          struct apply : is_whitespace<C> {};
        };
      }
    }
  }
}

#endif


/* is_whitespace.hpp
JGiFTHhcmx2tKhllzmKnA9BotUFonI1oY6DScVUE/UeGJ+eUGUMRklbTqzw5Pi+q+WdBYfn0AUMIl2dnJNT30iqwLsLGKvQhOqcGkUO14BMJAd4ZTb4TYJMme6uctXG9L80ZCCt7TD2DcltrnFSw1bFzmwgDJGgLAxqE6LX9ghFkhJvASISPKiCmVLK55vz4cVHV8/L6mPTLxbLmKyMNvdxs0sPPL66IZl9F4cRLfbyh1+0OhsMD2Ub0EDuE4eagkwFWiBZmoXNxxsRP2ksCa++ia5zJ2WtVLAnX2V3vNiFj5W1VAWHd4K/s1wZPyZWy7/cZu3u/h4lsnEx4GSvK6i1j9UdZwDxjqWtCztJtjdHL67zOCPxgLPiehh/+s39QSwMECgAAAAgALWdKUsXG2BTPAgAA8wQAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMzgwVVQFAAG2SCRgdVRtb9owEP5uKf/hlhUJpoJ50d6qFG0DqiFtKiO01SY05CZOsRrsyHZKo7b/fWcTWlRpQTi2n7vnznePE1lubMIMH5JIyEzh65ZXW6VTMyRnixmZTxZzEtGXzYju7MhbiLm+47ptRMpJpHmRVwinzDKQKlnz5PY0rLgJhyRTSpGNGyLqcMdS
*/