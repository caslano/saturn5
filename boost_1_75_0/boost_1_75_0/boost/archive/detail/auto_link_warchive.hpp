#ifndef BOOST_ARCHIVE_DETAIL_AUTO_LINK_WARCHIVE_HPP
#define BOOST_ARCHIVE_DETAIL_AUTO_LINK_WARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
//  auto_link_warchive.hpp
//
//  (c) Copyright Robert Ramey 2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/serialization

//----------------------------------------------------------------------------//

// This header implements separate compilation features as described in
// http://www.boost.org/more/separate_compilation.html

//  enable automatic library variant selection  ------------------------------//

#include <boost/archive/detail/decl.hpp>

#if !defined(BOOST_WARCHIVE_SOURCE) \
&& !defined(BOOST_ALL_NO_LIB) && !defined(BOOST_SERIALIZATION_NO_LIB)

// Set the name of our library, this will get undef'ed by auto_link.hpp
// once it's done with it:
//
#define BOOST_LIB_NAME boost_wserialization
//
// If we're importing code from a dll, then tell auto_link.hpp about it:
//
#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_SERIALIZATION_DYN_LINK)
#  define BOOST_DYN_LINK
#endif
//
// And include the header that does the work:
//
#include <boost/config/auto_link.hpp>
#endif  // auto-linking disabled

#endif // ARCHIVE_DETAIL_AUTO_LINK_ARCHIVE_HPP

/* auto_link_warchive.hpp
5Wuf88L6a6CbEHfP9YyJDIyk4L40MpiqIfcQco9GeCi7SW52bwJNYuJRSBgjZT6nAo7DLHYLZ7FTS7jr7HKai1CCoMASKp9oIgLoYIPk5uQmtArdSPzxFf/Sy/jxQdaZf/IxaY/i+bFkBFG+2mPjiyGbdTZTkN5yGz88oZsGd/zw5diA065Ve18mX7yAPmx+G5IjTphfFyC4DfEnIQmlzB++jGsyZwtoCg87ZjXdP6zvfvUHHMW7fax7ZDrHHGXSHlrnaDgu3yPHG71HiTeHPSq8yfY46Jy3HKegYtfPmrkjnkd1D2+5RdjxgDuyowg4qh8PKMCKZRTche8QHEdGtlxCqE4JjDvg59eRkEzIBQD5sHnVN66V05Dd44Td+14mzVVBqQfgrpaam9bX3HghiSehR/Q1eYnYZEpmXvEybs3+K4emtKxGwc895UStXu36YSK+tIUfIiiBNq9+FwlAC5vk75LWQIp+l7QHUg7vImuYkr2L1HX41QjI5Jq/Jt/0PgtCEJj0EJlUBJwFITSJQpA+xkBYm64GC5xZr5s+27QZmzOz3rXqm5293H4mJR3N70tJB/ObUrLC/A4kOecqk87B1mw4TJsdIOTl2n0exdek8HdEWvJNPds4Hb6QaxvXIWzhyfGXUZp2n3b2UTpNoUxqqq+vSWh2Uq6KcFEe2DhMOA9F/IenYbWMcFaWQv4MT+d78uVFCqVS4axc
*/