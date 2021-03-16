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
R46GttZVXWhr5C7njDH8rdPRNAy09kSlkUGGeLi3pSPEpxRuPfkgwowPhdUAk4Fod4sYS+RRsmd5uTSVcLfpE9tNvHEzjreJ+vUftMcGndwgDBbUXGhFtPSuBt3dKbcHNh+T3YTBXF6xCIm9Dnk8pFyI2hhOIH9xvhh6HL7nEw2fsWuYJY1m8RJ4h7Xn85KioXsQuCs4OLGDknsgSG+jWqbuyRKyHaA7dMVFAW7lNkIJuIUx7xUs9ZeT8wF1+SA=
*/