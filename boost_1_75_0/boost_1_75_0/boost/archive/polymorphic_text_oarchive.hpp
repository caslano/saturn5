#ifndef BOOST_ARCHIVE_POLYMORPHIC_TEXT_OARCHIVE_HPP
#define BOOST_ARCHIVE_POLYMORPHIC_TEXT_OARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// polymorphic_text_oarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/detail/polymorphic_oarchive_route.hpp>

namespace boost {
namespace archive {

class BOOST_SYMBOL_VISIBLE polymorphic_text_oarchive :
    public detail::polymorphic_oarchive_route<text_oarchive>
{
public:
    polymorphic_text_oarchive(std::ostream & os, unsigned int flags = 0) :
        detail::polymorphic_oarchive_route<text_oarchive>(os, flags)
    {}
    ~polymorphic_text_oarchive(){}
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(
    boost::archive::polymorphic_text_oarchive
)

#endif // BOOST_ARCHIVE_POLYMORPHIC_TEXT_OARCHIVE_HPP


/* polymorphic_text_oarchive.hpp
SDx6IAHJNUpKLX/fv5qhCFzKL3VSck0w/GlQAWVg2ZKRIxesWrVgbbyB0jlLVswDmuINqr0TDmoNbf0hSn5Y9PXYKLlL7Ai59Y0JQle3JgO1xg5MAGgaZi7adV3JlrQliku6iBjTdaxVoMmH9tuF9I4TcPpavgUtZygZYbHRclcAajy1LQAoJkroAZ+wd/F6tiTTHB4NmIUulQ7EOK6MEWmHGig9/YbP3oO6n7Pos0UXUBPdOAE6DPxGMNDyNe+zjs0AUmxt2fbVYqevY2MXkoEySblx43Ri3xtKRZLcJsl+f/aWp4CNQdmbnhLtekC1G6f7Nsl9sp/TQGYAeataSjwvABPEdj8WvzQf56dByahDRQ9W7cIld1NcUwG6MMduWLA8xzAoAuVCDIxNKkTByNZ2gBJ8k+ocDio6PkFyDsaQl6Noq5Cc4xY3qIWjxi/FjOthyPCvF9PGXmW1zfF40FphB+eRzPyIP5YqdzAaVYmmCktbAw+FytFq0UVkmRqkrTZ3RoMNrKwz+KBwK+4CyRhcHvT4GIypjDZf8iXNWANLr5o1LBAmoqWGnlbVkjQm17AytGfya5SMWm8HJf+M8pW3bdFFepr+WUC0Cr1AX86z9umaIZZgdws53kWkD0TSWwnSBxHpu+iB3du2DFgI+HI6Zp54XBeMO12iSdDPcxbhHd6CzfTGIYBnAEiUpnpc2YDXCjhcMZQweFyz
*/