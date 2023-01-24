
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_PREALLOCATED_H
#define BOOST_CONTEXT_PREALLOCATED_H

#include <cstddef>

#include <boost/config.hpp>

#include <boost/context/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace context {

struct preallocated {
    void        *   sp;
    std::size_t     size;
    stack_context   sctx;

    preallocated( void * sp_, std::size_t size_, stack_context sctx_) noexcept :
        sp( sp_), size( size_), sctx( sctx_) {
    }
};

}}

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_PREALLOCATED_H

/* preallocated.hpp
Hi0hm69O9MGFLEIV+QDv/bwL4D11unvNe6gWwUdsqxUsvbSc/hn8VDF/YZZC3HIJItdQOU+e5Gx9e53zW9/ieHqDpDTkWYEog69KLCWlmzByo1AcJZ4kM0ytIM6R6JTKFeTHrpLk19BqKYyeb8Z71//FyABqphQa0BKjH9HFES+4MCllBrHjqoemomd+O8TfRtUVEfOsnY7X8g28jy8TFIk0zn3bwkvz/na4MOgeF6I2B6IbzVEBAcSRYN4LqZmSpIrxcL4T0GETgdp/xxM7/nVxAe77a/cff/Tzz7211w3jur2LST77QiYelYZqOScebUIIrxx6jq+scrK6k52vLTN68iFM37D80Au88a4t3LDg0teWWb8dVo8/y3XO4ynpJh3uNXfw8jfexjj7EEduP4bOYWtqUQmkRqOVRonCJlLTTiHoJj4S1aqZ0FtreWMD3PQi9dDb6OcFn77O0NG1pa0VQIz1Ky8oFzdzFMZgxSX6OfUk4PpcgvbSHKe9ipmDtQLws2hAjRZqCyutf1G51I/FC3YKG+/axh15kf2tMZvpJmISKlfiXOhNpowmyXJEHKWt6Hfy8Ntph1ahLbrvTFm99zKXzq4y3rNzQh5WS/BrPkD0jJeQOg/ANAMzgt9fQ2w1i+3HezzXGKTVNbURnrkQH81xTesQ5VqWe+amqKZlt5q9LRZWNMENmSkI1f6O1NzODAHYyrGxotAq
*/