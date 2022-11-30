#ifndef BOOST_ARCHIVE_BASIC_OARCHIVE_HPP
#define BOOST_ARCHIVE_BASIC_OARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_oarchive.hpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <cstddef> // NULL
#include <boost/config.hpp>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>

#include <boost/archive/basic_archive.hpp>
#include <boost/serialization/tracking_enum.hpp>
#include <boost/archive/detail/helper_collection.hpp>
#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

namespace boost {
namespace serialization {
    class extended_type_info;
} // namespace serialization

namespace archive {
namespace detail {

class basic_oarchive_impl;
class basic_oserializer;
class basic_pointer_oserializer;

//////////////////////////////////////////////////////////////////////
// class basic_oarchive - write serialized objects to an output stream
class BOOST_SYMBOL_VISIBLE basic_oarchive :
    private boost::noncopyable,
    public boost::archive::detail::helper_collection
{
    friend class basic_oarchive_impl;
    // hide implementation of this class to minimize header conclusion
    boost::scoped_ptr<basic_oarchive_impl> pimpl;

    // overload these to bracket object attributes. Used to implement
    // xml archives
    virtual void vsave(const version_type t) =  0;
    virtual void vsave(const object_id_type t) =  0;
    virtual void vsave(const object_reference_type t) =  0;
    virtual void vsave(const class_id_type t) =  0;
    virtual void vsave(const class_id_optional_type t) = 0;
    virtual void vsave(const class_id_reference_type t) =  0;
    virtual void vsave(const class_name_type & t) = 0;
    virtual void vsave(const tracking_type t) = 0;
protected:
    BOOST_ARCHIVE_DECL basic_oarchive(unsigned int flags = 0);
    BOOST_ARCHIVE_DECL boost::archive::detail::helper_collection &
    get_helper_collection();
    virtual BOOST_ARCHIVE_DECL ~basic_oarchive();
public:
    // note: NOT part of the public interface
    BOOST_ARCHIVE_DECL void register_basic_serializer(
        const basic_oserializer & bos
    );
    BOOST_ARCHIVE_DECL void save_object(
        const void *x,
        const basic_oserializer & bos
    );
    BOOST_ARCHIVE_DECL void save_pointer(
        const void * t,
        const basic_pointer_oserializer * bpos_ptr
    );
    void save_null_pointer(){
        vsave(BOOST_SERIALIZATION_NULL_POINTER_TAG);
    }
    // real public interface starts here
    BOOST_ARCHIVE_DECL void end_preamble(); // default implementation does nothing
    BOOST_ARCHIVE_DECL boost::serialization::library_version_type get_library_version() const;
    BOOST_ARCHIVE_DECL unsigned int get_flags() const;
};

} // namespace detail
} // namespace archive
} // namespace boost

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif //BOOST_ARCHIVE_BASIC_OARCHIVE_HPP

/* basic_oarchive.hpp
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
*/