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
CZ9jE6RSsyZs34Bc77Srn+0hqXohW5jrtLDlc3SiaXnco4OA0+1d7BJqnkrIXb/sBF4d3T2FaDCWFTx4ijkJmz8JfPYy85FrbbmDSdG1Wn5kYuIy0N899qk8rR7+lPfaX+fCX+V+FNpgujgEPgVidiDRCypRqhnFOmxQqPSJLn3zgXoYg2swzpaG5cW9LavSgT/ue1IWWaj5gKzmPTLt8Z+IsRp/1fHivZ4TzQcgpQBUNb6q
*/