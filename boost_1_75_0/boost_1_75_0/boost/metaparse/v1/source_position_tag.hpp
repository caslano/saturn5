#ifndef BOOST_METAPARSE_V1_SOURCE_POSITION_TAG_HPP
#define BOOST_METAPARSE_V1_SOURCE_POSITION_TAG_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/source_position.hpp>
#include <boost/metaparse/v1/fwd/get_prev_char.hpp>
#include <boost/metaparse/v1/fwd/next_line.hpp>
#include <boost/metaparse/v1/fwd/next_char.hpp>
#include <boost/metaparse/v1/get_col.hpp>
#include <boost/metaparse/v1/get_line.hpp>


#include <boost/mpl/int.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      struct source_position_tag { typedef source_position_tag type; };
      
      template <>
      struct get_col_impl<source_position_tag>
      {
        template <class P>
        struct apply : P::col {};
      };

      template <>
      struct get_line_impl<source_position_tag>
      {
        template <class P>
        struct apply : P::line {};
      };

      
      template <>
      struct get_prev_char_impl<source_position_tag>
      {
        template <class P>
        struct apply : P::prev_char {};
      };
      
      
      template <>
      struct next_char_impl<source_position_tag>
      {
        template <class P, class Ch>
        struct apply :
          source_position<
            typename get_line<P>::type,
            boost::mpl::int_<get_col<P>::type::value + 1>,
            Ch
          >
        {};
      };

      template <>
      struct next_line_impl<source_position_tag>
      {
        template <class P, class Ch>
        struct apply :
          source_position<
            boost::mpl::int_<get_line<P>::type::value + 1>,
            boost::mpl::int_<1>,
            Ch
          >
        {};
      };
    }
  }
}

#endif


/* source_position_tag.hpp
aLlRJygNgLLgvyTcTNNU32JEg97FVVdt70p4hMIZ9nELExAvVgf6f6y9CXxTVRYwnjQNDdDywhIoglClSLUu1aK0BDSBBF4glTpudUGqlVpHnKmQaFEKxbTS8HiK27iMjowzLqPOiMsIKGKh2JZFNrfiBm7jKxEB0dIW5X1nue8lacGZ7////EmTvOUu55577tnPEpKbAXBYyBOaBRZnbLP/OQfJxv6XKbt51P9W1L8qbjJ4Ltm+/vW7x3VhOyDwt/pA/Gw8gpj34ESyDLQkYRzbBz4ICrXwkUYjgurJqSbW3TCFsWnpVOHbLD7/EmTLzp/wU6t5rUs342ZF7hl0jTrzB1tC/rFDmGMQSRifE0ugv8ULnbcC4x+W26dkeqTaqIW17OS8dIXMnmdXZkOXUarCF/c+4wRjlcAaLCiEWx7p4eboQl9sErYT8vdoY+Bvt+FJaMMEqLe5F3I/aKcX7lBFE9gdqooyj2FeG4DAQ9MZIsumHzdfMIJh9H5bgncbF+KEZ3YE1Et3ICRu3cDeaTlUsfZ9VI/nFPwFvcCkulQrK7o83pVUGdaDLo+freESrDADUpuIeqNUdpbc3OCkYw0qqkDCV7ETGJeWzYNdyvfeIsS814jsyOuhaKlutCY9gDg4yMTBWY1i1DiFN9dbuUKe8DXjwXVzE9BduRvY9U7UVMxJdL2Ll6D8dryRNkYJMbAN37P3Jwvdho/0
*/