#ifndef BOOST_ARCHIVE_POLYMORPHIC_XML_WIARCHIVE_HPP
#define BOOST_ARCHIVE_POLYMORPHIC_XML_WIARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// polymorphic_xml_wiarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#ifdef BOOST_NO_STD_WSTREAMBUF
#error "wide char i/o not supported on this platform"
#else

#include <boost/archive/xml_wiarchive.hpp>
#include <boost/archive/detail/polymorphic_iarchive_route.hpp>

namespace boost {
namespace archive {

class BOOST_SYMBOL_VISIBLE polymorphic_xml_wiarchive :
    public detail::polymorphic_iarchive_route<xml_wiarchive>
{
public:
    polymorphic_xml_wiarchive(std::wistream & is, unsigned int flags = 0) :
        detail::polymorphic_iarchive_route<xml_wiarchive>(is, flags)
    {}
    ~polymorphic_xml_wiarchive(){}
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(
    boost::archive::polymorphic_xml_wiarchive
)

#endif // BOOST_NO_STD_WSTREAMBUF
#endif // BOOST_ARCHIVE_POLYMORPHIC_XML_WIARCHIVE_HPP


/* polymorphic_xml_wiarchive.hpp
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
*/