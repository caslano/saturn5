/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_MIN_SIZE_HPP
#define BOOST_ALIGN_DETAIL_MIN_SIZE_HPP

#include <boost/align/detail/integral_constant.hpp>
#include <cstddef>

namespace boost {
namespace alignment {
namespace detail {

template<std::size_t A, std::size_t B>
struct min_size
    : integral_constant<std::size_t, (A < B) ? A : B> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* min_size.hpp
JvDu7dvjo/CdNW1qRW4opyULUaNEGDpmUUq/mgusLQ1oWrOHMylh4nbSAP2Q799OiwpftKlXsyU7FM7AknqpKGcmq4XKmU0Rarf41pOm8SM03tbaEUl50K0safuaGkhO33374eLs+BhW7zcnl71onfgdQJE4greynokeFcxjNh5ptSKqpk2HBKWNVGeXdc17Pcu8LOClO4cDYFEcoGRTK7curb2TagDBvL5GsVjqrYr2vo/vXh2fn7x99S7YgXYFWjf5UouC1QvUGbVKGd7EJsrUe4YbK6eP/YJWMavDuyrTHdUrKr9w35Sy7qASmPcAwhJUkqVVx3uGOgVqlgn1X1yf3oin61lhFEkSJZMmgOBCn4jO/lHlDNq6gUxWLYT8B7hSJI0ZPSom0Scs7UhDpoY4yegLRomlULIruGH7CqkXkzBLdoFSq0yQV3eH+Y8QKcfcYeD7lpUSo7PQLECMS6/Dw1qTr+2StLV1qHgcUhKUbGyFkhhXSJ85VEZt3ZMZ2rnW+VgWZZgzQ4rzaRcPSA8sZ9ixDLwxWtC+QhMYeEfXKH5liv8Oj4QQsEq1amwoq09WyGPxmZ36l/2ovRisr4rd2crjuw5kyA2RuLgrpqvOOwJpZIjZEVT31bLHqFJ3SOIUVXV3rFhk+AMj
*/