/*
Copyright 2014-2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_MAX_SIZE_HPP
#define BOOST_ALIGN_DETAIL_MAX_SIZE_HPP

#include <boost/align/detail/integral_constant.hpp>
#include <cstddef>

namespace boost {
namespace alignment {
namespace detail {

template<std::size_t A, std::size_t B>
struct max_size
    : integral_constant<std::size_t, (A > B) ? A : B> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* max_size.hpp
BSJrunu4JnjFlPuKWjDSAiT5coTwNrePuyKuk4qMf0uTJs4Mw49n2TZ4d+lMt3siYAfCTtRnGc4o5F9mGztk7mQjqemcA1WoLi0necBK4I1fbbmnocJbCHQoQJgA/ircQuOIU5dNctnMGuvoNO0WprZ3x8n/ga5TLCeeadu1K5N8eWmVn6qK1apwSJDKhaUepd84RX9Mm9PRtLSmCrfYammXrj7l3sdt7YaCtZFwPnXXVdKKh5EnTVQs1SdVgCQ=
*/