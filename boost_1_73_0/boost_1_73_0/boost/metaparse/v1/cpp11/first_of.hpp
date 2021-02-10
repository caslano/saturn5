#ifndef BOOST_METAPARSE_V1_CPP11_FIRST_OF_HPP
#define BOOST_METAPARSE_V1_CPP11_FIRST_OF_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/impl/nth_of_c.hpp>

#include <boost/metaparse/v1/fail.hpp>
#include <boost/metaparse/v1/error/index_out_of_range.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class... Ps>
      struct first_of
      {
        typedef first_of type;

        template <class S, class Pos>
        struct apply : impl::nth_of_c<0, S, Pos, Ps...> {};
      };

      template <>
      struct first_of<> : fail<error::index_out_of_range<0, -1, 0>> {};
    }
  }
}

#endif


/* first_of.hpp
MAyG73mKyM6ligw8hF18BV+gdJkrbqm0nbK3N9vQeUr+/B/JT6hwLt5lboAOxuCtDxkTPwfnOeNiYl1f0Bj1g3RRy4Pnd0xtbmCSUBYEepd7ILs7ZDcYKqjwOgSWYnJoGcivQonM6cWpAYmiY/uV1LErU+L/9WT3IZK4UdMGKZzEDbjcRp8UYNsqneK85g5yV9huNPk4jk7aBk7nY60Lf1rbbyK7/+IDUEsDBAoAAAAIAC1nSlKPvH8wuQAAADQBAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTMwNlVUBQABtkgkYE1QSw7CIBDdzynGdE3QmJqYTLrxCl6AwGiJ7WAANd7eaetvBe/LC1S5VO8Kd0ArY/DYx4KZr4PzXHASsW33aIzqUU5Jjws/HymH0sFNYp0s0LvSA9mfQnYxQwMNHobIUk2JgYH8DNRRON85dyBJlLYfSCd29Zb5v57sj0QSN+raKJWzuAGnt9FnNbB1IdigiZye8/YoZw3YJUE1pWFp3WzXrbYuBPk0jk5CB0rvlP5ivb7XTubvR70AUEsDBAoAAAAIAC1nSlItLeg/pwAAAAUBAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTMwN1VUBQABtkgk
*/