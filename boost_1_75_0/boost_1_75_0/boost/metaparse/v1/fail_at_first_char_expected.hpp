#ifndef BOOST_METAPARSE_V1_FAIL_AT_FIRST_CHAR_EXPECTED_HPP
#define BOOST_METAPARSE_V1_FAIL_AT_FIRST_CHAR_EXPECTED_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/impl/void_.hpp>
#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/reject.hpp>
#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/get_position.hpp>

#include <boost/metaparse/v1/error/expected_to_fail.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/equal_to.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P>
      struct fail_at_first_char_expected
      {
      private:
        template <class S, class Pos>
        struct apply_err :
          boost::mpl::eval_if<
            typename boost::mpl::equal_to<
              Pos,
              typename get_position<typename P::template apply<S, Pos> >::type
            >::type,
            accept<impl::void_, S, Pos>,
            typename P::template apply<S, Pos>
          >
        {};
      public:
        typedef fail_at_first_char_expected type;

        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename P::template apply<S, Pos> >::type,
            apply_err<S, Pos>,
            reject<error::expected_to_fail, Pos>
          >
        {};
      };
    }
  }
}

#endif


/* fail_at_first_char_expected.hpp
28I74t4l7EEWqmUedlg/Fk5l6MadiYn1AMBQJzW5Jo1LvaW8dgnO+MQYMWOcrApHg8WJiSltrzfa3qjvsmp/A02gzKSVM+cO5SxIrgH5gR1vwaTu8KhaxXGq2sI4dy0DJRIzx5axNp5LAwJhqZuSveJ5hWNR3paKAsQDQ6zidQLCanLTketOKKUbf0dzEUUJJabkgHzwI6PLXkamgLZMQ7mErVtiHF67a5eF0oGuwaHZao7bBdJEHZ4cZtbkApTPMujZyjHwbHd2p1QN2l2OjwnNDM3GY9J+BxzKT0bPpn2kPOHJSZidsdHEA9PfAZEhlMHwlo0YGp7gDid+eC28oQ5mJ9m+BIIXGs6obtcd8Gc4cTle3rCLzHpgOkmcj2YCFO92syleiFM8CmQW5CumPIxiaOoJTktgd6keaydV37hdJRe6Ou/f+TS7bLQl3jmxHIfYwABdJn86n0GesYjESaRJ2CaB7LFrotkk/1jOBJAf2D/s9C8TSQ7ZPxEQyVlhQtWgLmg2af2/TsWpMaRC3wAKXoBB2/aSIBppjoHnM3AeqNLpIpHeJ21GrVpuB9WUfc7gsbFwxzjtDiZgIsOUX2GQivRiw6DykIFWQKY8bA6kGUak4Vzs5uAsFOOs/ngUvwS/xEjUf3hF5Z+m+ZvwRW+djNOIJJW//xi2tCc8ts4TvBn0UKYyVzqlQ/JdxWbq6j5N7EFqg/3tThFJ
*/