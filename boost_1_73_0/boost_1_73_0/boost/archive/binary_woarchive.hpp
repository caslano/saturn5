#ifndef BOOST_ARCHIVE_BINARY_WOARCHIVE_HPP
#define BOOST_ARCHIVE_BINARY_WOARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// binary_woarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#ifdef BOOST_NO_STD_WSTREAMBUF
#error "wide char i/o not supported on this platform"
#else

#include <ostream>
#include <boost/archive/binary_oarchive_impl.hpp>
#include <boost/archive/detail/register_archive.hpp>

namespace boost {
namespace archive {

// do not derive from this class.  If you want to extend this functionality
// via inhertance, derived from binary_oarchive_impl instead.  This will
// preserve correct static polymorphism.
class binary_woarchive :
    public binary_oarchive_impl<
            binary_woarchive, std::wostream::char_type, std::wostream::traits_type
        >
{
public:
    binary_woarchive(std::wostream & os, unsigned int flags = 0) :
        binary_oarchive_impl<
            binary_woarchive, std::wostream::char_type, std::wostream::traits_type
        >(os, flags)
    {}
    binary_woarchive(std::wstreambuf & bsb, unsigned int flags = 0) :
        binary_oarchive_impl<
            binary_woarchive, std::wostream::char_type, std::wostream::traits_type
        >(bsb, flags)
    {}
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::archive::binary_woarchive)

#endif // BOOST_NO_STD_WSTREAMBUF
#endif // BOOST_ARCHIVE_BINARY_WOARCHIVE_HPP

/* binary_woarchive.hpp
TlRuAapHMO9a/UKUUYrjfr/PFAuUzsC5qTrEH4XFyRJOxUR4jAwlHppV6CNcCpkXQGHRMpsBM7zIXmJWm0zNyr0WKVzi5PlMzytsa5NCr0qfYOkaHPEJKYJZlTEmdKY4EVj4rJBZtJS/gwooV0umZLsBOJbWsWFOg3rIXaXq8Z0tMmwqep8xge1WO5T2dCZLTJW5JGT1ksSMErwAgJwZdp5ECgHJUZhPPt0/fprs4gP345g42Ul3TYqloN2i17JO33Rw53ukumgl53DPSJkV1JQtJRsGGowufK/z6lV8HT2A35NnDIR5Kj6n9ln4whOjz7SX4ubuujlzOO8TdAhhHRZ6ds5lEne45otN8YHJeTDiNUD7Rk1JMvnNW8i/v7kaXX74wMt8vrv/RP/ubso+cjhVU0s2BvlaMTgC8l40PkB4KgXZEYsHnAhYoDEAGAf9Qr6+xnmFHcckFByWvgZT87KncT8Wg5M2kgUhmRRa8MPw/NJDoJ2DgY0xazIkmrkLumD3ypLZcThgsHgB6i3LavhJzll7d1TQEJt7+49XRL6XwkFWsyKWGdt6IQFvXAzzXqCxif2BORbPnlLc+JlMcPhG5eUm701VKRu5Jx2Xp+KMUislkqLQL221EHPNAVPMiMAijlFpWxs4iqkg
*/