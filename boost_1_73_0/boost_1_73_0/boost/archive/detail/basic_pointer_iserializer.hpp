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
xPsHqmlOURdTl0sgpnJKRsSqIBvkweu+wxgq2x0EB0yBg+CwjSBZrih5y7sjzWbnb83gKNgzVpKl0DBhJjY2tsnt0G2t49lSWtgMDluTpmfhYjC8mn75enI6Pr/65eL08vrr9WBydno9E52wHEbR5ca45pM5FejUJzGSOYamq6ExfoRxz6RY7FEmSSPdINN9nUL0vrdFNuBmjxx9U8cVqVPXzpgn5ObRVOov85qiFa9pm3kh0CZ1ggMjpHkK+BvH8a7b8uMq8hyDe7bvTjtm3NWdDgiXFl9RTsrINp+TUYORMqreOjAeD6C8N1andckGUDMWmQLLta/AtdMsvxOtotozxzmXerVvcl70lTq6iFqPneDRDkHb8R7qaNhSw5xON+ky2KEsKvM42vZhTA8xqGTfYzu7VGwg6lAbb9SW4M/jrP7W5R8P+Iddk4qZszbZ1STJjPKBcxlT9+SdXLc5S3bcOssH4th476663hGPzrDeRmbSdeqRgLptXJ58MHUc22xtLWlEFr8VI8iOuDBNyvYwtcDpUItuA8kEd4Hg6KkJdNveGYLTWXUTNWcvazAJ1zq67m4Lw6pSk62sC+O7PtxfZKIbL5F1Zro/Zt30IjkWJLA969O080J2XthLbHuP2kQEH8JMUhXo1Quj
*/