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
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
*/