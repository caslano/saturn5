#ifndef BOOST_ARCHIVE_POLYMORPHIC_XML_IARCHIVE_HPP
#define BOOST_ARCHIVE_POLYMORPHIC_XML_IARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// polymorphic_xml_iarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/detail/polymorphic_iarchive_route.hpp>

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {

class BOOST_SYMBOL_VISIBLE polymorphic_xml_iarchive :
    public detail::polymorphic_iarchive_route<xml_iarchive>
{
public:
    polymorphic_xml_iarchive(std::istream & is, unsigned int flags = 0) :
        detail::polymorphic_iarchive_route<xml_iarchive>(is, flags)
    {}
    ~polymorphic_xml_iarchive(){}
};

} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(
    boost::archive::polymorphic_xml_iarchive
)

#endif // BOOST_ARCHIVE_POLYMORPHIC_XML_IARCHIVE_HPP


/* polymorphic_xml_iarchive.hpp
do66qdIzr2NZ3TR7V605Twc6ig6TU/8MJMU1yQxSriq5nePCJ0WHC/Hbjnex2gX1hoqVwwDwilal6MIGFP7DCdwDkL7H2h7nTkhMmiR3njTJ/i60aaA2JmizWSC5SQAYCS8QgFdgw8RQax82YedLIaVRVxIQH7U+Ij52Q0/pQKmj9PPAg0JNbwV1FopfH/DRUHkf0byIePSg9EwsnZ0ZXrDSUTdGcuE3FNBFLfW5BerFQ7192NGjfCgkAbodoAPoRMs4ydkVEkmSM0D8/ESsDJVcl5pUnajuMEvGwvooadN+VI31w6XNeD2IdKD7hwZgVtsqhzfqgHpFVT/Bpy3ApGBkizdYjLQwHw/3QrqJSArGd1eQa1S129evlxtls5gRanIeRnMx2OE1yKOAqT0nTZJcadAU0JqLLjyCV9kth1o/wu9igLXVp8yb6j9f3iQs1CfLG0skRUeXOs9Kz5UGEeOvZtBsXKc2W6FNJ8j9h3K/I2IO4wsmn+AchNo4P9Km8cCr+BhpM3IW5mmso/QENISeRE1HnVl6egd+sN/Pde6ZoDBikhAd9RZhD9CG+op6m0hlCoquUC18F5QMgP/avllqe2XcJrWh/wft2wq28gtzqTFwlp8WSZiKtsf4YZG5SE3nA9IPBeAT1beQ3hQALwGyAfC8AFwjQA4AXAJQT4A1AJABEB9rb69xd18jTsg8AEYfBtdgW1lRGU1R
*/