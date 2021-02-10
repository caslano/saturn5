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
8NexteuMrkOFsNAqrhz1J/dW+R8y99Wn0laOxw0E5NhYN9ia4fNPlLYa84PAWjbXZCNXShlBOF1OXMJKBi74EVvZhu3GUKtzo6qfPpmhPCdPHdJ3A1AkhKs5bZ5/z4gI1DW3KukV9nuct/rHmhdFFsLJ0Vtx/+Hx/acP7978/OlH+eSMwwCrL4cZgSBhm/9aIm+fj60NVmW7spbwYEUdDFZ4Z1It3/7G31rrrz5FecVT8GGr2vo957qOYJcFqTC3se+35ZbZbWRN9/7WRCw40uNMCheEk6bksr2OVLbRn1BLAwQKAAAACAAtZ0pS+3WVAvgRAABXLQAAGwAJAGN1cmwtbWFzdGVyL2RvY3MvSElTVE9SWS5tZFVUBQABtkgkYK1aa3MbubH9Pr8CV19WSoljknrrVm6VLNmWEj0YkxvffNoCZ0ASq+GAGcyIoj/kt+d0A5gHKa+Vqqhqay0Kz+7Tp083eGvWIqmKTHxUiVwqca+flZgstI3+/KOfKJqYtSxSK8qFEipPhZmJwcXF6aG4kblWmRiXKp+qYi7W0gq7whCdz0Wpsf660CX9InNx9/VaTE0ZzUxBv14t9VyKQmWyVKlIFjLPsZTJxafPuSpjcatov1zwMauVWOtywSfQqZKiNGIpn1WEuxQq
*/