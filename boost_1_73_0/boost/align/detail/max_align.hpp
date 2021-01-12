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
CPUV3w/FG1Pk60VevvAfjSBUypyC13V653iONGNN8lD57hP2oeKzDxUAefOzn3dOwMiEpsxGsy4lIDsIt7H4xpdxVHZU4Snjj/At7HgVhh/fMWiO+bTLhtHDr6gpO3HLIAZvOnqAn+1aSheIv3RqaNRZnQc5fvuix2fhmKvUKjsPosy/1zc27w1Bv8Ffdawzw2n8X3Y4jecJzMaHzO9fn1SAOLcpM2R+IyVA6Jzm5He4pOzI
*/