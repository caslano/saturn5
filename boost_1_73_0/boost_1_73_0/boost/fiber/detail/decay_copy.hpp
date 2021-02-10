
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBER_DETAIL_DECAY_COPY_H
#define BOOST_FIBER_DETAIL_DECAY_COPY_H

#include <type_traits>

#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace detail {

template< typename T >
typename std::decay< T >::type
decay_copy( T && t) {
    return std::forward< T >( t);
}

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBER_DETAIL_DECAY_COPY_H

/* decay_copy.hpp
hP12S64YtJmg9kQ1ocUj+MuB/6qZFm5UjDcP3MOg5tcMhwf3C7Wbumjpm3Bb/1sGrKoejyTlzMJlhhaGfvVbvvs+uO0+F6v5nVDEJUGanuMIdfXLouNmAOPDHVLxA0F9MTB613rRcCb79rD1t+NXwtYq+BTMF8H7+WKerZ2gLIcP8TADHWdejRKnocUlfSzLQQbLMFstI/gULFahs+QGvzrahh3m8Sn1CCHoI9K3JHxeeuPuKjqN4vMoj+2woZOoSQ+l7YzoVZbHH/Oz8Cxermmbvhncdhs2WV+hvu20rDlrcc6ygg8BuWkYQrBIYxzP75cPkk9dDy72PfL4cHEPu3dM/A/4PuwfUEsDBAoAAAAIAC1nSlKg7QjGRAQAAMcJAAA4AAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9QUk9YWV9TU0xLRVlUWVBFLjNVVAUAAbZIJGCtVW1v2zYQ/q5fcdC+OIEi5wXt1i0rpjpqY8SRBEluaiCAQEtUxFUWBZKyYyz77ztSMhJ3KZINVWBTJu+5Oz733MW9teHwhz2Wq93Bi09mPhk+uO5AkeB/0lw9D8iyB+j/EHiL6ytCjeER9ZAdwKtQDzAyqGyIda7fs+wV4W51kvprrMG3
*/