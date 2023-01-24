#ifndef BOOST_ARCHIVE_BASIC_POINTER_ISERIALIZER_HPP
#define BOOST_ARCHIVE_BASIC_POINTER_ISERIALIZER_HPP

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

// forward declarations
namespace archive {
namespace detail {

class basic_iarchive;
class basic_iserializer;

class BOOST_SYMBOL_VISIBLE basic_pointer_iserializer
    : public basic_serializer {
protected:
    explicit BOOST_ARCHIVE_DECL basic_pointer_iserializer(
        const boost::serialization::extended_type_info & type_
    );
    virtual BOOST_ARCHIVE_DECL ~basic_pointer_iserializer();
public:
    virtual void * heap_allocation() const = 0;
    virtual const basic_iserializer & get_basic_serializer() const = 0;
    virtual void load_object_ptr(
        basic_iarchive & ar,
        void * x,
        const unsigned int file_version
    ) const = 0;
};

} // namespace detail
} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_ARCHIVE_BASIC_POINTER_ISERIALIZER_HPP

/* basic_pointer_iserializer.hpp
YWoBPFm8q8Q7ZbLZHv0ma+pb51ybbIyclsvxomgFuTY7SHmL1U4QRObNk/hXUs3zaeW4BQI/t+b3XdLzQP4RV8JH/umi7LwsSR6yKRQVTCtfgrzdcFVDmk7LL+rLH0utBdgbYv6LmA/s9OVPpSbZlf8oWJIPbpr2pmyOGcUFVG8ZNyorvI9mK6QJS+RsrSJyJ1XAXWg6zCWpa4vwADksxtM5Nx0J1dQkpwmA5KySgnwdVUNUDPmZhWJ+iTeVXDIXrjwqOTd/3VqE5WUU61IzRc+SfEZg/6o/3mBe27hk+sfLf1skMFeLety3pvMjZsbR+ZG/r7slwvci3Mv92mdM7J9SdNX3kcUQJIHwnV989zWzs3Fe3qZUJxFuQjh/7ft65plJI7mIY90inUMID9v0eQMzYpPv6JbCySJ+I8K1Z2uOMtOs05ROf3IT4ccQ3q1fc4J57vzD349sdBDhzQiv7eROMqFHvOu45Bki/BTCfTeuPc28/8/spCRGgp8hfH7g/R1T4PPpa2c8xonw7xGunmD9ngkZd1X+e4TETwvC/SI+aWHMS87HfvKmxM85hJuupZ9jypb848qU1Dki/ALCG/eNvMCkbz/R/XqbhP8jwul17/+Lafppm3Xf/eNFeCvC5f9S/8Scykw4WFv7sAi/iPAd5RmtzJ7Z73ZPyLxfhF8i/CdOv8gED/s09MUfGRH+M8L3jGi9yBgSXn2j
*/