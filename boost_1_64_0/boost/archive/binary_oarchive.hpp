#ifndef BOOST_ARCHIVE_BINARY_OARCHIVE_HPP
#define BOOST_ARCHIVE_BINARY_OARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// binary_oarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <ostream>
#include <boost/config.hpp>
#include <boost/archive/binary_oarchive_impl.hpp>
#include <boost/archive/detail/register_archive.hpp>

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {

// do not derive from this class.  If you want to extend this functionality
// via inhertance, derived from binary_oarchive_impl instead.  This will
// preserve correct static polymorphism.
class BOOST_SYMBOL_VISIBLE binary_oarchive :
    public binary_oarchive_impl<
        binary_oarchive, std::ostream::char_type, std::ostream::traits_type
    >
{
public:
    binary_oarchive(std::ostream & os, unsigned int flags = 0) :
        binary_oarchive_impl<
            binary_oarchive, std::ostream::char_type, std::ostream::traits_type
        >(os, flags)
    {
        init(flags);
    }
    binary_oarchive(std::streambuf & bsb, unsigned int flags = 0) :
        binary_oarchive_impl<
            binary_oarchive, std::ostream::char_type, std::ostream::traits_type
        >(bsb, flags)
    {
        init(flags);
    }
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::archive::binary_oarchive)
BOOST_SERIALIZATION_USE_ARRAY_OPTIMIZATION(boost::archive::binary_oarchive)

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif // BOOST_ARCHIVE_BINARY_OARCHIVE_HPP

/* binary_oarchive.hpp
jmTFZE9cWJ62WVwzkpx7GEktqUgfUTkP8sRx1IiZ5LZ4wkXBZBE9Z2b4505FcEFizna5CWbqhyNL2PlFkmSbXw8AmG4wL8aKb1vjuE1bos716dx3e42LZ5p9l3AYoWBAjxLhK/c7xxJ542pkAiuxIYp/zik/e7PK4otGb9H3JRNs54vffUuJkUYthLHdCWwL8O+Sd20JHdpDHXdeQ69LLPBO3CRbU48eTvVeXDiei1S5DwN2/kAMk3PwSUq8pSUiRMnIKtLjzPx+9fEYfjbvg6hLv6x9yBQrYBKjye3IfOIVXjNzQMkes3HG28aDXLIU3ZD3Ana3OowlFls4FvQdOLNXdAG71EYdZcVUzBPv2K7tDgIxmoZ2YGeXmRGvfp2x1W4F8c3Rd2tCKFwN0fbjNXQvoQxGroBURxax9zzfTfFNgQhErxQYJtjfuZEJKgAHtf+lBoYPVU5gFG5oPrCqQXAB0017QUgt+IvDert/HuStm7NBQaH6RXtXnIsK8D0undL2Q5g3OhDYeq2szloHht/uECOvL/IJTlX0zbTuzDJZipL8ysxBdVaMMw==
*/