#ifndef BOOST_METAPARSE_V1_ERROR_INDEX_OUT_OF_RANGE_HPP
#define BOOST_METAPARSE_V1_ERROR_INDEX_OUT_OF_RANGE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <string>
#include <sstream>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace error
      {
        template <int From, int To, int N>
        struct index_out_of_range
        {
          typedef index_out_of_range type;

          static std::string get_value()
          {
            std::ostringstream s;
            s
              << "index (" << N << ") out of range ["
              << From << "-" << To << "]";
            return s.str();
          }
        };
      }
    }
  }
}

#endif


/* index_out_of_range.hpp
PZKMiIXg4vDDwiiY+oF65CccKSaI5QdZ/GurqYfM/hZYB+PlZJTlMrCtSldm1hQfe9Xjjla69My4jIXSHEjwiBpXb73PpeSk8QAxqTVciONUKqtgBRN8RO6WxSM/ij6bFyZ8ISivwsPilayYyKG2+25MYfAKMR/+3efwLoDtioYoCW1IfxAYZv+3KCHM4jFMr6sw6NQKQaWW7jYd6lR4SgXTb0MO2j/MY2y/YmiJ7X39BvLYtfPQVR4A0tSKkaxqmPj9U+zBqrc2bHPOQYfO7eJkfdOZ8ZT0TKInxoVWPvidrHLwmEuUNBcQgd4XhHKvZOaKxZZupjMQxORyqXzDSnzyMXvFD+P+pqGj37CK0+TqQpRN582DTkq8uGP9OzOFA1UfGGJXSPXeK4Z7fWCIOO9w/mDY3C80soDKtIg0QTIMIcvDJF6pfCcvQj3eyttVri0Js3K6vD9+K8wIQRecY+DrDApkTFe5TNk/Ag3CfJ9AaBx9Q2BVtiy+8kwWc5UyW4SnM1ukDRBCDrFL8cMNXDHk7HnNdyg8ELRr/qAAJvh/9HEL7twEBmmgPg==
*/