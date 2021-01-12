/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGNMENT_OF_CODEGEAR_HPP
#define BOOST_ALIGN_DETAIL_ALIGNMENT_OF_CODEGEAR_HPP

#include <boost/align/detail/integral_constant.hpp>
#include <cstddef>

namespace boost {
namespace alignment {
namespace detail {

template<class T>
struct alignment_of
    : integral_constant<std::size_t, alignof(T)> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* alignment_of_codegear.hpp
PSKFwM7UIqeaJAqY/d0m88UFKzIztIGyD2WYh9FLcqCqQPmUjLdicjnAveWY2lt+i1/QdJzNxoytGhYyQcU4N65Fw0hOxJaeNwo10fKcJAUGdmIkbeNXvzqeRExMg0sRVxh8D6v78zgwpdJ9236GNsF9VWyFF4aixUKCDL7QBrbUj15xWjwdkUnJm3DrwD5K3gRWQLHtxPm7UY1/E1RoHJnT9YtA8PuZ4GJCEjJWPnRcRKND
*/