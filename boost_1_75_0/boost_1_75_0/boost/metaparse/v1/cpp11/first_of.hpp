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
08mj1w8nZtix+Oh4GFjIhbGkdX+xYkaiqTYkrQ9Y45mH4EG/kVmJUOUDWZjZtT8sIMwQ7nRMfozKIcWVPtZ93QAdtj1jMfNilRTVfWMg9s2qQR59KfHkWgElNTuheNSguxC9txoutCcn5nwaHc/5FKeROwSNLDFuGg61e6w9hklUUoy0KZlMElRridQ0s0WWiaPhNVErimxiRP1yxvQMuY/wIrrb8H+qFZYw9CLK9BeGs8Kj+JV6I+KqGH0aB5o+jftVYW0zYiyu0127l1ktsSsWH50GqxO+GJYrHMDxFZvlaFV7SjU6TLLPUlC4NSV2JKx5yf6Ti1Vr4kMJm3j7sqQ7fHEuPV7UfRMT7v9FoU2cHCjb3acJszJxjFjaMitbCkUVsB6Wwmaz2BBs9TWp1p5uwIa68+8ZTNAPItHXmvrxr68GmlaMSEbcJzdxxzPHZp/zb3PHM3P3SZAVSRVE8emAW7k0ieJX4N731ixCkr+IoPA+7uJibcIIci8EDsgg0+p9tKOFXgrDkUjUNXI203aV4X3tZnJLvxFl5kUH46WOchP82X3ZlZlEguYgbs+hDHgfpQmMOynucVcpnNZguEPbGUNSQxLuXOU+SpgzuzfxqsK9G3HCauLErYrVYqbGw4UjL5R/WYTl6QPaHhSv/ldCsRnd0YEAdl+UsDhunUpEgmKBBClLEQnilL6iO6UXfgmAAatS2HJFVHrx
*/