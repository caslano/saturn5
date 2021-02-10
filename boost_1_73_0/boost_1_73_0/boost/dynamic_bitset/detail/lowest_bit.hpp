// -----------------------------------------------------------
// lowest_bit.hpp
//
//           Position of the lowest bit 'on'
//
//         Copyright (c) 2003-2004, 2008 Gennaro Prota
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// -----------------------------------------------------------

#ifndef BOOST_LOWEST_BIT_HPP_GP_20030301
#define BOOST_LOWEST_BIT_HPP_GP_20030301

#include "boost/integer/integer_log2.hpp"
#include "boost/assert.hpp"

namespace boost {
namespace detail {

    template <typename T>
    int lowest_bit(T x) {

        BOOST_ASSERT(x >= 1); // PRE

        // clear all bits on except the rightmost one,
        // then calculate the logarithm base 2
        //
        return boost::integer_log2<T>( x - ( x & (x-1) ) );

    }

}
}


#endif // include guard

/* lowest_bit.hpp
03/vLkhZduI0foh8IQnt7tnLwQG9ZQOOftqHeRQOfviJ3F+EH7zunWaF/lvE9mmHKPoC1Q86LvH6DKgOHLy+RC14ltcXaDqvqMZ6Q/dR9Ay4JSVJ/zrkvIzoFlcqz9p/qDe7Ql5nFprDFvROTn6FF9Dv9rttOOW5FApCK/KVKK7b8CZxK39k/O7OM+L3NggLXHmPAi4yacDo1G55IQDvlYxFbkQC3EAiTFzIFT7IHGwmIJVKwDCYXY2n79uwzWSc1XF2ugST6VIlkPFbAYWIhbytwmx4YUGnGAHjJ9JYjFlaqXMP4QVYUaxNHYaS4Mpo4LdcKr5COG4hs3Zjfut04rJQWEkn0bHpxPtWeJldf1XVFWaz5jvQGwtWQ2lEG8i+DWudyJSu2CJc3JQrJU3WPqSFgHnS0QUYoVQdDl2lMFUJAsK6W22yhA1mLy1djM4NoW0zvX5kiG2tA6VlkSMctgXtEo2Nb0OZJ6Jw9q4Re5S6y67lPxjZIfcEdI5ZQcMPYRw2YMWNNG24HC/Og4sFXPrzuT9dXEFwBv70qo73YTw9RW5IRC1A3G0KYTCLAuR6o6RIHoH/1J3OvMU5DC/mk2C2iGZBuJiPTsdzGECjdwJ/ljkSu/eyAQ0lVzR5OPYGx14XF+gpEtzsIiMs
*/