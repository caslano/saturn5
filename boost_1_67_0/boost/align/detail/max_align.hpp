/*
Copyright 2014-2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_MAX_ALIGN_HPP
#define BOOST_ALIGN_DETAIL_MAX_ALIGN_HPP

#include <boost/align/detail/max_size.hpp>
#include <boost/align/alignment_of.hpp>

namespace boost {
namespace alignment {
namespace detail {

template<class A, class B>
struct max_align
    : max_size<alignment_of<A>::value, alignment_of<B>::value> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* max_align.hpp
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
*/