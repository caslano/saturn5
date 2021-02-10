/*
 * Distributed under the Boost Software License, Version 1.0.(See accompanying 
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)
 * 
 * See http://www.boost.org/libs/iostreams for documentation.
 *
 * File:        boost/iostreams/detail/restrict.hpp
 * Date:        Sun Jan 06 12:57:30 MST 2008
 * Copyright:   2008 CodeRage, LLC
                2004-2007 Jonathan Turkanis
 * Author:      Jonathan Turkanis
 * Contact:     turkanis at coderage dot com
 *
 * Defines the class template boost::iostreams::restriction and the 
 * overloaded function template boost::iostreams::slice.
 *
 * This header is provided for platforms on which "restrict" is a keyword.
 */

#ifndef BOOST_IOSTREAMS_RESTRICT_HPP_INCLUDED
#define BOOST_IOSTREAMS_RESTRICT_HPP_INCLUDED

#include <boost/iostreams/detail/restrict_impl.hpp>
#define BOOST_IOSTREAMS_RESTRICT slice
#include <boost/iostreams/detail/restrict_impl.hpp>
#undef BOOST_IOSTREAMS_RESTRICT

#endif // #ifndef BOOST_IOSTREAMS_RESTRICT_HPP_INCLUDED

/* slice.hpp
bG5VVAUAAbZIJGDFm0tv2kAUhddB4j9YdNNKMbIpIWTRhcGhiURTVEvtmoeJXLkYGUgrpfnvNQ2EgOdx7vg63oEzc8835x7ZHpt8iaZpskrma+t7tNqMYytYb2ZRYgVJvFlHycIaRHF4bg2S9Nc4GxOmq+1B12k6Tr327mRSy3G69dooTX6G0/X7xmO317/qX/e6drfX9mzX9R2767uu7Tie079ys7+2W0+ND9YnqxFHk+kmjRvnLx+bD9NlVml75NH3OoOLTq9tOx2vbbfbrm97/qVje/0L79K/cAee33tq1GvXi9lOvV77HCeTcVyvnT1/CLKDGfr7/cL6yWIe3W/S8fbLKB6v59kSV1uWZRruB2Wzz/zh0PLDyebesq3t56/LcBEEw923YTQJgpvW3x/R4mMrm0wYjRf/02nDpbOxisI6Ti2ZmkWmnlWdJb9XVhCMbg+Hbv07KY9mBk1EzKwcrxOAwDFWAC9HlJcXaJ0Wfl3lWxiH41UIZxoeTxE48IGjlcX1vAChjklOgWWcNIcqJGOHki6fAi4AZYYwBWQiDKFmXmBfbXjbI5zLCaPx4s9s8FhFYR2nlkzNIlPX55w4gyYiZtYmXDUBAsdYATwR0fbzIQLbb6osakbjxfOwyrGKwjpOLZmaJaee
*/