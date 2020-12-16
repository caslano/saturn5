#ifndef BOOST_METAPARSE_V1_UTIL_INT_TO_DIGIT_HPP
#define BOOST_METAPARSE_V1_UTIL_INT_TO_DIGIT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/util/int_to_digit_c.hpp>

#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace util
      {
        template <class N = boost::mpl::na>
        struct int_to_digit : int_to_digit_c<N::type::value> {};

        template <>
        struct int_to_digit<boost::mpl::na>
        {
          typedef int_to_digit type;

          template <class N = boost::mpl::na>
          struct apply : int_to_digit<N> {};
        };
      }
    }
  }
}

#endif


/* int_to_digit.hpp
+K2BwR8SAaYDxO+e/M9R+r5ClmUPtRE2B9EWeKKqkyZDqfJIf12bxwSFa+wqkJ2qByBzJcbrA4qfl9N+OoDsWM3xGuoIs2IWyKfl3FUd0WE4ZcZRpMJdaWOhrgBtssjemaL+S9X6nab9PoF2c7030vtYamSdoCet7zMAqQqlrLiv9XFb9oHeQY3PjVqxZ2GwzxGwqow7+q4C0aQY2YpL5J+UX6D4ebKPVoAoex/QbJjil+qNiNVga0rwRivhHP/cXvd9W/QtpPc56br/htIvGxRRXN0furvy8VQfJH9xXu33N6hmrZtw5Xjdj/Q6Nc9LiNfJFj3WWf7OsroffYfVzjHy72rqdVKw/aGc5MukQueZeg+iUM+2QOi6lKbu4y6k3gZCMqqj4lEKhRoX0XvvYhrfcaQu19f61avTzKp0SYarJ+NxCC6h39mVC92lId+Fms+3tF95wiBCxt3i7npP/V3v9XLpPNLNYaEamnMTupl63JdZErVMpkg+kXRu56b7DKmxenc4/Qip9rp8X7JQ/GO5Qe8PaHzHCQQK0Lu+4V/0nlo+jwvqv5AupFLE74gfYNFSuJg2k/9gnOKD5rSWKrXGaYF1faX7ltzl5aOhW9IVpn3nKf7hSL+8+k3281mUrthe7//WyT496Kz1q/1UizPRU+9zZsBl9kxSNkNINdIUqDsoB/zGku34Ay5B3eU/kDOpk4hduqNW7QrUuLFL/hz12nKNVtRRsJMnAu4Vt2d8NS06qI34WPnvHUh5hMm/q1T/z5p/sr5SZBC0VON/UOSxgTTybejCfMkAO/Qpm2CdHjR5bqj8TfpcIF1h93C98x2eiOYTdOFYqqhMJ02VgkFkj+SBaWgI/B4tgF+WHGC5d1A2Wbqt0AZaUyBGD07f7TVDvkDGaMp4+nnVQzvpS6raLYgrao5755T9UodUpYLo9kb8Erfq/DhDd/o31/xbovfeLakbqVuW3wMQ688gZL06gMN6w2KpGF99bYJbpcKz0RDvVpcY9QZ8X637x0ZmSf5xltjjCkO7K2adXlb2rsRYry/hglrIflG3j8iCwVxpeTcGFW40IjtvNG208qDDSnzW936TEXdcRY2v5m6VAlbI5wr2pfpluMSYI91Kn0LchDqKr3qQqq0Yy8h+cC7kZww/g+KhvwPcFss/HqLvheS3Ne+m9xY+ei+gJj301iBnFk1G9wYxVQiTTXqfI8GrR+o+Laa+h0D0G+8Gv+Vkx0mWUfJZNupAa8bV9D5RNRpvVLzCRd+X+cO5k8JTq+P03kIWY/GCgEJ6VDNWnfM9WedHKcUrCsr/p0X8xJRUvGTx08IefhfRJuSC2F07cJNt8AvWudDtlfzZzzVfluh7kv0gauimNF+NX9LZPeqS1oc+MruvB95LtJtl94Hze92EW+wh+3QPqQxfxZMLyV8cD2igq1HZTopXjCdbuPcv/ymNl/SSP0xGYPpuWgvopfNSdw3nQFKlryteJnvIRB0bt1HynWJAd4+UfX+L7IG+et80k1RyqOyDwqyZdfJM1PXX92VrAI0/sMcef8QAvOqBGJ7y+tX3pHfLvKXxG28ArgUUz/OyV/yXbGXt98mamC/kaTPPpXhPBgw2b9f5JhfDZVfAFtWtJjC3v977LED9zsvlD0u1RD5zBN+o0/TxSkZwu2bs7zUBC1SjgEDep7qf6wON90rdKSB/0wjkGyxWZRqQPZOp/WWY7Cttr7m/Kd74FlX9nekcm/tUuyZWx2pRFtCNbLa8JM76muiOTqEmnfS9qQLShjsoOPI1xO00ld+81XvRr5rPHvRGnRekaorVOpH0zNZ9Zq0F/M7LP6QLr52wIQMVD80AHBkEdpp8gpM=
*/