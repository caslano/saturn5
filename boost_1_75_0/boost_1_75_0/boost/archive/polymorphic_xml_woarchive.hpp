#ifndef BOOST_ARCHIVE_POLYMORPHIC_XML_WOARCHIVE_HPP
#define BOOST_ARCHIVE_POLYMORPHIC_XML_WOARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// polymorphic_xml_woarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#ifdef BOOST_NO_STD_WSTREAMBUF
#error "wide char i/o not supported on this platform"
#else

#include <boost/archive/xml_woarchive.hpp>
#include <boost/archive/detail/polymorphic_oarchive_route.hpp>

namespace boost {
namespace archive {

class BOOST_SYMBOL_VISIBLE polymorphic_xml_woarchive :
    public detail::polymorphic_oarchive_route<xml_woarchive>
{
public:
    polymorphic_xml_woarchive(std::wostream & os, unsigned int flags = 0) :
        detail::polymorphic_oarchive_route<xml_woarchive>(os, flags)
    {}
    ~polymorphic_xml_woarchive(){}
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(
    boost::archive::polymorphic_xml_woarchive
)

#endif // BOOST_NO_STD_WSTREAMBUF
#endif // BOOST_ARCHIVE_POLYMORPHIC_XML_WOARCHIVE_HPP


/* polymorphic_xml_woarchive.hpp
naMpSHK1hQKOQROnEQm59UhzWNuDcp6gabE/TS5DKHjOU4Ew6g0FHaq4wFhIZ++u0kSL3+frK/dh6Cdvu8DcU8d8j8DctsVob3UDzAUHqaV0wNKkXEuSw5Ik11KM7me5rDbBxh5qC0yH9JV/fGJwJ59RyiIrYF+5HFgB/GYzJtIDIcL1t274yemZwJq4Y9IzDwAC7xf65DdL2A8oYbZAFLFUlK+VHUm+AIP9Id9qHQfbxK/L1wh27RX8/nfNGajVVTlSdjPI8V1vJcRDtb4Ldpva8O7QvbiP9NKjGK/hxQAELPvTrfXopbCiJ1D2WqN1l8CGHWqgYA3HXgVah7LFehle9Bb6Gl3Sp+Rf4j++IhqP1yuwhY+KoA910DRFucx4uUDVFfKkfn2rgFtexS3niVJYCtggE7IsRKPmWo5OTQZ7Q0NR8DFQM4Wx34k6x3N8ut07jB3UG7AqUY6k7v9YJzX2Y9HqheaKH04UpO6CIrYVWrlj2Dq9mA8LwlNJWt+Oj0As+yBkiag4Te+dByN4OoDvjfH+qFTQm/0rn/8MsrY60GbKTGVjVuN91xa8vLMHC8/xaWzW63eYpEsQKzHclFF7YMQK63AXqwVZ1CbPPb7bQHylM7PbIPz4WAZqSmZ2Dyq81UZybvhILKk8+C0Oi1Y9VqNiolYTphTmdzS4Uy5VjA8PgpopUEMrKhkf3j8eQGO1xiOxcYBWONYW
*/