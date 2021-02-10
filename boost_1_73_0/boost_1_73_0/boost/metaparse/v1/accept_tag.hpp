#ifndef BOOST_METAPARSE_V1_ACCEPT_TAG_HPP
#define BOOST_METAPARSE_V1_ACCEPT_TAG_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/get_remaining.hpp>
#include <boost/metaparse/v1/fwd/get_position.hpp>
#include <boost/metaparse/v1/fwd/get_result.hpp>


namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      struct accept_tag { typedef accept_tag type; };

      template <>
      struct get_position_impl<accept_tag>
      {
        template <class A>
        struct apply : A::source_position {};
      };

      template <>
      struct get_remaining_impl<accept_tag>
      {
        template <class A>
        struct apply : A::remaining {};
      };

      template <>
      struct get_result_impl<accept_tag>
      {
        template <class A>
        struct apply { typedef typename A::result type; };
      };
    }
  }
}

#endif


/* accept_tag.hpp
kJVxOORkbePxCH8RL6muGCvxpxcZqASxR2qd2utKhQqnCs9Zdgef4tB6PSkriRpfcDqC0HmN6TBEmL2CxdoQ/lBNN4gx0BhLvoD3FSCkqWuf0WMmnE9Xm4dsvU2mAWy7uc94vFh8CADn6y1Mfw+4bx1wyBijAfztuz733AZc/3mk3wl7DH60vYv5jtAGYyDsB5S5gydEDRNXGpow0XkXzGqsISNNlbKgrmd0MitiK+MogX+IR+ybH9Dsau+beycOtuLTx5v7h/XmLmJXUmLjwxf8ImKRJzm2EP0C/ad1CEPulfw135Ok4PmRnODDdPj4d/0BUEsDBAoAAAAIAC1nSlLbpD8tSQEAAAcCAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTIyNFVUBQABtkgkYEVRwW6DMAy9R+IfrE49btGqnaqIbWqZxqkMWKvtloERqIBRknXj72dS1uYQ2/Hzey+JcmhdoS2GQjV9RRyOOP6QKW0oXvJEJM/ZXqRRngolrx0lz+AbyNCc0NzapkShDA7tyN1SOx2KaRfAy5EPABZRuFo7mJiZ6mi5YQlKQguNe2Te86iSMxUrbNoGezcrFL5ggPW6oajcwOj/ClSvO/TOoUJX1KChalqEylAHrkYwRA7K
*/