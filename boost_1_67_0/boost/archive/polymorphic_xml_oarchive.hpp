#ifndef BOOST_ARCHIVE_POLYMORPHIC_XML_OARCHIVE_HPP
#define BOOST_ARCHIVE_POLYMORPHIC_XML_OARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// polymorphic_xml_oarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/detail/polymorphic_oarchive_route.hpp>

namespace boost {
namespace archive {

class BOOST_SYMBOL_VISIBLE polymorphic_xml_oarchive :
    public detail::polymorphic_oarchive_route<xml_oarchive>
{
public:
    polymorphic_xml_oarchive(std::ostream & os, unsigned int flags = 0) :
        detail::polymorphic_oarchive_route<xml_oarchive>(os, flags)
    {}
    ~polymorphic_xml_oarchive(){}
};
} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(
    boost::archive::polymorphic_xml_oarchive
)

#endif // BOOST_ARCHIVE_POLYMORPHIC_XML_OARCHIVE_HPP


/* polymorphic_xml_oarchive.hpp
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
*/