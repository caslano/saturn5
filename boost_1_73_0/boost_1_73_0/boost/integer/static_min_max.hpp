//  Boost integer/static_min_max.hpp header file  ----------------------------//

//  (C) Copyright Daryle Walker 2001.
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history. 

#ifndef BOOST_INTEGER_STATIC_MIN_MAX_HPP
#define BOOST_INTEGER_STATIC_MIN_MAX_HPP

#include <boost/integer_fwd.hpp>  // self include

namespace boost
{

//  Compile-time extrema class declarations  ---------------------------------//
//  Get the minimum or maximum of two values, signed or unsigned.

template <static_min_max_signed_type Value1, static_min_max_signed_type Value2>
struct static_signed_min
{
    BOOST_STATIC_CONSTANT(static_min_max_signed_type, value = (Value1 > Value2) ? Value2 : Value1 );
};

template <static_min_max_signed_type Value1, static_min_max_signed_type Value2>
struct static_signed_max
{
    BOOST_STATIC_CONSTANT(static_min_max_signed_type, value = (Value1 < Value2) ? Value2 : Value1 );
};

template <static_min_max_unsigned_type Value1, static_min_max_unsigned_type Value2>
struct static_unsigned_min
{
    BOOST_STATIC_CONSTANT(static_min_max_unsigned_type, value
     = (Value1 > Value2) ? Value2 : Value1 );
};

template <static_min_max_unsigned_type Value1, static_min_max_unsigned_type Value2>
struct static_unsigned_max
{
    BOOST_STATIC_CONSTANT(static_min_max_unsigned_type, value
     = (Value1 < Value2) ? Value2 : Value1 );
};


}  // namespace boost


#endif  // BOOST_INTEGER_STATIC_MIN_MAX_HPP

/* static_min_max.hpp
PgimJrLhXM4t6YhNFTOMxNO7H37snGUaKgUue4KzLFiftABOq+BvziBobCgrMf7P+eadxiU0OG7RH8v18hb87ZC9fFBPIkCdYs8LgTVbr+4AlD/O08VP6BTXXXPdL4+D5eQW/UuPM9DssmOj+Tm1bRj6T3ogVHZh0Yat5IwnUGTd8+LW4TIO0reWKb+gBcZKbEi56xhbSRabl+al0V4QxAVaOLsuj1Q6EEzTPD5uDLqO91ntw6RxTMYql6zidIH8oEnSaIKVQyJlORzqHIw9ULsoROvUXR23ywJ2m2aBsvOGhiC6xVvqlxiC0htmoJy/5kBlA+1fTda+ZPDGfoY8eDp6X75IeXvhe1zU9W5EPpBHhWaTrQMuVEN2hqdjHkSYQn7hoXbnNKmiE0k27Am7XeRCXbYga0pF5Xk4LU9DotkPY6uCR/Bczsxy+VKATtAyLGqRtO9XnPSZQ8gZfDUFKoXGfFkfw0sUjv08vUDI1xmndzC5aApEHn/wtohoKnLcrEzkcmHjjK8ON5vG6x9EwQ2kUNrwfJ1KHfVeUtHqNn7NRfdukQLj9XCBGJddexRH+U6/98Aww3NMQe41oKPLKmMb3Ez1loO/4n7lTZh6B1Q4Y1IjvkIZR/AtU+PcBQ9YQXfVVj5HaSHgKaIR
*/