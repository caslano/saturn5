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
    BOOST_ARCHIVE_DECL library_version_type get_library_version() const;
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