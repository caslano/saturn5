#ifndef BOOST_ARCHIVE_BINARY_IARCHIVE_HPP
#define BOOST_ARCHIVE_BINARY_IARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// binary_iarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <istream>
#include <boost/archive/binary_iarchive_impl.hpp>
#include <boost/archive/detail/register_archive.hpp>

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {

// do not derive from this class.  If you want to extend this functionality
// via inhertance, derived from binary_iarchive_impl instead.  This will
// preserve correct static polymorphism.
class BOOST_SYMBOL_VISIBLE binary_iarchive :
    public binary_iarchive_impl<
        boost::archive::binary_iarchive,
        std::istream::char_type,
        std::istream::traits_type
    >{
public:
    binary_iarchive(std::istream & is, unsigned int flags = 0) :
        binary_iarchive_impl<
            binary_iarchive, std::istream::char_type, std::istream::traits_type
        >(is, flags)
    {
        init(flags);
    }
    binary_iarchive(std::streambuf & bsb, unsigned int flags = 0) :
        binary_iarchive_impl<
            binary_iarchive, std::istream::char_type, std::istream::traits_type
        >(bsb, flags)
    {
        init(flags);
    }
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::archive::binary_iarchive)
BOOST_SERIALIZATION_USE_ARRAY_OPTIMIZATION(boost::archive::binary_iarchive)

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif // BOOST_ARCHIVE_BINARY_IARCHIVE_HPP

/* binary_iarchive.hpp
XJ7lOitni0ryfACKfR+Yv9qkVHmDpL2fgW239xdpbz0kvV01D1GbAfD5TG0mSHuPk5d4UQxC8xXFYIVjaBoZXaqc8bZXPle+8vMXTSPx40Sk/ITkWoxcIOnAWG7BYF3BiAU1fDpKHAmi2MtAJ6E2An+xI/JV3wZHPyok3R4KywhKR1PpwF+XzV/e89cDtiiho14z/JY8739PU4xrZvuk+QvJ+W88lzKL2ju/NWCUVVQVOFdxt+T7fKsHfE2iD/w+pM22Eq/J9dAuv2NLSw18m/qZsraRnM5Z6F9hr4poZtsivKx/Y4CNI5KzFiX2Jgi1F99Ria3VtUN7asIM++t9KxoX7lb84GnlrLg6yfUi7i4xRP9GjFOquAzUCdpfwg/DPPhhHBG32Cpa0PnK33HLotE2MxZ9X9rL0PelhPB9iQdrZitH+A20oKNLbUFCtQkR9tBfKysq9p3470qq0RSoqcZ6DPTyGEaKpZUdSPXdlOaTAIzxPcdRcTO5t+m463mN5DJjG3SZt27y0+t/vuXT6EKaQV2JkUvOUZvwQ/IYDy5s2YzecyRAis283yZ0nh8UChb5wP/6DEJIUn3ySe/cbWveNc7m7z3TeFdGpr4rxIyHkrtjoIVhJd8X52Qa87YWvi+WeNN9U73PoE31G02aj00r34VtBJZmP9hAbMASVvID+IgkGDhrogsxd2KrBf1ri5odeZB8YmyHPjHN
*/