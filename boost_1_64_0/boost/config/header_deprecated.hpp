#ifndef BOOST_CONFIG_HEADER_DEPRECATED_HPP_INCLUDED
#define BOOST_CONFIG_HEADER_DEPRECATED_HPP_INCLUDED

//  Copyright 2017 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//  BOOST_HEADER_DEPRECATED("<alternative>")
//
//  Expands to the equivalent of
//    BOOST_PRAGMA_MESSAGE("This header is deprecated. Use <alternative> instead.")
//
//  Note that this header is C compatible.

#include <boost/config/pragma_message.hpp>

#if defined(BOOST_ALLOW_DEPRECATED_HEADERS)
# define BOOST_HEADER_DEPRECATED(a)
#else
# define BOOST_HEADER_DEPRECATED(a) BOOST_PRAGMA_MESSAGE("This header is deprecated. Use " a " instead.")
#endif

#endif // BOOST_CONFIG_HEADER_DEPRECATED_HPP_INCLUDED

/* header_deprecated.hpp
/reWEHjzWh+jctM559lwigyh36QSTSJ1xz3r4YhTmva8PxDz38aZS/QpxV9dD9oCfH94bozVXdtM/mJ7vX6A++r3CXhttGCBaLAwuLSwbjGT9DlqD5ldZpaqvVOz0f2X+V0HkvC6IjwN7DWrQCj1BDWQD4JqjcSSiXlKla5GnBzlj5zYlD+6SNadaQnZRrmSDZBZpG1YCPPYc7V1wzjgTrQsNqA33965ccFnKau/5Jj/uBnpWwsfN0GxUOqC4M/pvh52JRcFDieFhaOUJVWRhRRI1C9Fs29xQ91F3kFxX6X0d0RJrz407yfIbVB+Dmj9s2CLLOrYSBLWVqrGuWw29r3iTw+IbHmLEAXsO6KXz7q+7hEvHU+/cviOgbGIVU69FYt1x5YCTqIUMMyNd1kUV8yxU4LkYpImtrADk4WmWI3S8lz6TeR9bheBbHixqCsWBbFTWUxQY7EW5inzcCi2aaPBjahXjDBQC0WGyrpu0rvuTN8dI1eH+RquNYBsvSsyYVGi8rlhU6TxiCkHxWMG8to9oU4sVBl5+LGB3qEM8U1RPq2lBJ5mQkP3hg==
*/