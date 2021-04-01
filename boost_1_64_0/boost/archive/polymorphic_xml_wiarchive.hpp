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
7gyozDPC8NwKdvAebQ5iMdw0N2Ve5cDbiThSwYK5xJ+wHr4zVyylz0RtlqixvuXulvm5L4vQ193Z03GvuVNgWXySBujYfz/3iMrzO6ZoDa3D/+RybwB2gU86z5z5vTOTiYdm4uMU0uNaqAEJ4P1EeJ4l1Sa/BHNM35uhSVG8bhcivgA0AC5al/wZWp+SuOT/B6xDZ9Wokbl0FnMlIdOyF6tQt7CNxmR6YIJWQ54pPnCfkcpl9RWGbuFyk8tPuoXcZb7/n1Sc6vcTbJzIoxnvXf1adr9U2GcihmBbGmlaKifBCOwcYuZsgBFxZE0yBwKitsD9HUaCfcn6kmB8I5n8/ElMz1DzumDKpm7ggOi8AIgHnriZ7Hs40hnhkTq1QmObKjA9rCQ2EGHWD8XQcJRaQ0zAmh5od6jjlJ8IwcrQssNifMf3GD2V4Speqt2HaiEKwEn6rxWaqynvcZGRfskTg5DvWxG7jZ2jiznOaFK10tzPBG0fqQJwJY8q07+KE/AtaSiCzJq0C1qnK1P8KhVHec9Tm809jmD286hZkBCOqKpo5Nbq83I/WSrwZw==
*/