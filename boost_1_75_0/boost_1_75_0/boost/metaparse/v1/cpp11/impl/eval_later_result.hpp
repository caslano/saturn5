#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_EVAL_LATER_RESULT_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_EVAL_LATER_RESULT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/get_position.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/less.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class R1, class R2>
        struct eval_later_result :
          boost::mpl::eval_if<
            typename boost::mpl::less<
              typename get_position<R2>::type,
              typename get_position<R1>::type
            >::type,
            R1,
            R2
          >
        {};
      }
    }
  }
}

#endif


/* eval_later_result.hpp
GeB4FqJxSXg6fAQQ1ub0GM80NT0fOhyO47mYxgOdfDENnViIma9AdGu7BfgJNv/5MT4AdgIZBzPUjSh6HAAK43U3SZGBvYim17p6WSwsa3JlUZJfMQcuHE1ZqMNBc1hDOtJem9hadGxg5EAvlJu+LbKazxgWNby7AlBTW3lLvAIF3sSLhGXLsmtS8e0jQNPQ+cH4/V2QNdKpcH4WJN7YZmJ9CKE+ciKaAFp0V/nF5AeOz7u93DIaTmFcVTZL/NeBKeR+4VZl3buatqyvsDaI90JjlBZ4mX+oslW2bZIXdzqwHHAk1U78wNp0MpljyhGnEFBxMg39YIbXfSVMaRhiYSSpUu1/LEihFCAN/LNE/OSUJcuyS0jkHC9j0ZprgeHfYsV8JFTUU+QeUbm+D+DxVMqUIJoqk1OD6ujHjqD89fd0upRwS70fk8JEH0pfK5popSb2TSVP7luOWC1GURccKhV/g08qoqe6vnFzQAilbumbYbG82V+0soNaSaVWXJ9T9FOL1pZuIUkD1mAfAHe5Ua7Cuy7NwilGVlsYehRRE9mSilNsr6XuUsJeHHcm5bTAkJTQufgbtY1Bdy2NLChNEl9yLYGdHRiQqHLlB+26vkBcp4mmUsMefJV0iQol0iNVAqfrceLXHGykDHZ7QzB3Q9C2HlszmhrYl9IPi6ifCNficMjSZHHFqPKEEot3zVBLCiZBkZvXp1C0dfR2
*/