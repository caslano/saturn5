/*
Copyright 2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGN_DOWN_HPP
#define BOOST_ALIGN_DETAIL_ALIGN_DOWN_HPP

#include <boost/align/detail/is_alignment.hpp>
#include <boost/assert.hpp>

namespace boost {
namespace alignment {

inline void*
align_down(void* ptr, std::size_t alignment) BOOST_NOEXCEPT
{
    BOOST_ASSERT(detail::is_alignment(alignment));
    return reinterpret_cast<void*>(~(alignment - 1) &
        reinterpret_cast<std::size_t>(ptr));
}

} /* alignment */
} /* boost */

#endif

/* align_down.hpp
xMYsuDKzyezI2er75clslPgtntsqge/J7OEdle4X2Zx5oJ6B01YU0x+F5WX5HJ7uhExt3F18s+Bo2f4RqLLSvHnKm+MlyAHdGytRrBe88fQkW3x8CsX6p172IDh3YbQvfzf7uqGmrnpx9PSVg1tjqbdzDLYNh3emJAKCi4Tp1tCvKDeI2GpJAZPi29B8TR56N/MruBoHSO2B+1EtR51faQyagnf1hRIVX4v1R5j4yD2ADWh8LwXRkXVA/fkpUREHJrcirXJ6+6tZtqAWYwjrLz0OyO5N0SqxLEaziUO8XXrkvyukubzFbByoycddYFzx+dqgxilPufQo7JfCxTNIStjpG8Z+rOxR+UpDbKGqrImZ8fknAMOpTN3T58dmD9pdYsEw/3M26jPkUUMCDPoxyNmqcD7eycpmnjcoWjLGJJ+1ZFYmNf04NH1YCsNuOipCdSeaB1UrIfgQH5FfOkrxu4S4FEzQKCShERqgGBYihD9rVgtaZiPZcFB+fTX0ki2tg97ahrgjFfANZTVIRxTxs2wIxLwM063t80sQP5FztwCZZBvtApVBM6Rfw8yapd9VIzTNur81C46p4GxGbIjgTNzu9rKTvnbXMRG6ewJSBPMwCK1fBt+wi71HMfStIBpm/NIEkYZ6RJNxagvCOOPoH4qcSC9UXgiGg1peazXABCqFNBRQKJLS7whtaZCXtoseZCiw8AWy8OtA96hP
*/