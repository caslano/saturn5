#ifndef BOOST_ARCHIVE_BASIC_POINTER_OSERIALIZER_HPP
#define BOOST_ARCHIVE_BASIC_POINTER_OSERIALIZER_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_pointer_oserializer.hpp: extenstion of type_info required for
// serialization.

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.
#include <boost/config.hpp>
#include <boost/noncopyable.hpp>
#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/detail/basic_serializer.hpp>

#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace serialization {
    class extended_type_info;
} // namespace serialization

namespace archive {
namespace detail {

class basic_oarchive;
class basic_oserializer;

class BOOST_SYMBOL_VISIBLE basic_pointer_oserializer :
    public basic_serializer
{
protected:
    explicit BOOST_ARCHIVE_DECL basic_pointer_oserializer(
        const boost::serialization::extended_type_info & type_
    );
public:
    virtual BOOST_ARCHIVE_DECL ~basic_pointer_oserializer();
    virtual const basic_oserializer & get_basic_serializer() const = 0;
    virtual void save_object_ptr(
        basic_oarchive & ar,
        const void * x
    ) const = 0;
};

} // namespace detail
} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_ARCHIVE_BASIC_POINTER_OSERIALIZER_HPP

/* basic_pointer_oserializer.hpp
W/MKIKY77r2j+p1Q8aZBM62UTCpnHn0p3VPBYPYZZgEiYgGGXzfxlvLXOo3pb9/18Br9QMNY17apfXOMkDGxT3rVz8maaX2ectPpBQI6CT5FsUNvDGVa4EqR4HBYtvup4UEowUUmWV8qqR9ghNT0X8d/u/AMHYQN2g+2hU6TsW0vZ6EhVYIq4M4SRTD5lu0gSXHMbI/3KfexMlamwrK41naHzoU1+/tcpwUUbJdZQqLDdd1ds6yFw3nrt9ykDZm/niQ1excmC9BScAEn6N/vFHZvfxPXW22GzCfGLY3fLoEpBaflWrLIqAgVquTLVN5DWm1g1MtNTC7BiVadQwpsfu59rEuNypQXNMUc8IE1wSvj/hwbxhz/1IYrcJ/ANrO/dI7u1Cg7ake3ZYZe6A7EH2dyyG66JAvA49aOB1/B0Ra/9Jt05TOb/k2WRxnyFt5qB8Wi0y5270zdQuJNNjq9OSaUyx4uetFJmOLDQUjNABYFcXwrQCLroU312hanqkzuRbHYrDdqTDCK83csx/w3lFqf2c8xOF8Aylywv+hojIOQR5NPEXIyK6MmBA==
*/