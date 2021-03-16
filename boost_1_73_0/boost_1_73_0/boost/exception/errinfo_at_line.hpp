//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_E7255CE26C1211DE85800C9155D89593
#define BOOST_EXCEPTION_E7255CE26C1211DE85800C9155D89593

namespace
boost
    {
    template <class Tag,class T> class error_info;

    //Use with parsing errors exceptions, for example in a XML file parser.
    typedef error_info<struct errinfo_at_line_,int> errinfo_at_line;
    }

#endif

/* errinfo_at_line.hpp
Pt7L2HGmHqPK2BYwUTsYP47hac31dxBVeAz8NT5H4d8afH49eFV9NBaZGwu0lOCjVfGS0kVTqsbU4y/wIgvjJfPDiXh9eVl9uDXYnGwMweWEsgnllWVVkyaU1SdBi+u5S5ow79xHAvMXQrvAXyKsxM/nmAvjicZw5HyOSANSgSh8Xle/8NwIWjFpKg3Zgu1aE+c4THxeIBZqRB4HmiE6+GdH060T82EYqDHrU+biPCO1uwDXI5nPtk8D8fusugQ=
*/