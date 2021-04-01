/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2014-2015
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTRUSIVE_DETAIL_MINIMAL_PAIR_HEADER_HPP
#define BOOST_INTRUSIVE_DETAIL_MINIMAL_PAIR_HEADER_HPP
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif
#
#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#//Try to avoid including <utility>, as it's quite big in C++11
#if defined(BOOST_GNU_STDLIB)
#  include <bits/stl_pair.h>
#else
#  include <utility>    //Fallback
#endif
#
#endif //BOOST_INTRUSIVE_DETAIL_MINIMAL_PAIR_HEADER_HPP

/* minimal_pair_header.hpp
+g7QlfmV/uPjzRZHZQqc4+qGNVZFnBvqZmqaViJqyjmmUJ/LWs+7LiNCHyIH+3l2OQO99oekx0Z1ssTyfDtGf0ruO2njlQXK7FiCGg2KSoveskoYUKDl7QY2fkE+kU4d5/FVFEcyzAjw8KUARUy/zdtQCBLxFSXd7nDMPmWVNW18N0SL79pHeTmoYrAqU1JBez25vcwXzDPI5RuQ2HvvmUaxv4ZfMuu+sK06Pn5n/uNprt0/9HRDvl92yHWTkzNVBYl44709VHbzwe4NXOxudKFDfWugNV9V05dE6iI+DJADgVewq0g/jY4b6juDgu4K1xCmSQlhJGUZawj6RHcNoccQsnEpSv99ktZqmhBroQnyoYIAUdoqAIeX0IwCPMB0lyJ84IiR/Pt94Hm/1x5c3XoanSe+4KMg+73FjdbA5bgyC7FOUXWjhDSKHgREwL4jHC3/3ZMe5cP+SRIVGJpYIMn1S8FD7icbiFLeKeD9AKmK32+ZzafGmQteFyqc0FQ9sRCgqMs4xGLvP8W8F8pGEE0MMhmOdQQN0nzSNAOOvIH3lrP83iZ8qoYe5g==
*/