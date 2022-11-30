#ifndef BOOST_ARCHIVE_DETAIL_BASIC_IARCHIVE_HPP
#define BOOST_ARCHIVE_DETAIL_BASIC_IARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_iarchive.hpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

// can't use this - much as I'd like to as borland doesn't support it

#include <boost/config.hpp>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>

#include <boost/serialization/tracking_enum.hpp>
#include <boost/archive/basic_archive.hpp>
#include <boost/archive/detail/decl.hpp>
#include <boost/archive/detail/helper_collection.hpp>
#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

namespace boost {
namespace serialization {
    class extended_type_info;
} // namespace serialization

namespace archive {
namespace detail {

class basic_iarchive_impl;
class basic_iserializer;
class basic_pointer_iserializer;

//////////////////////////////////////////////////////////////////////
// class basic_iarchive - read serialized objects from a input stream
class BOOST_SYMBOL_VISIBLE basic_iarchive :
    private boost::noncopyable,
    public boost::archive::detail::helper_collection
{
    friend class basic_iarchive_impl;
    // hide implementation of this class to minimize header conclusion
    boost::scoped_ptr<basic_iarchive_impl> pimpl;

    virtual void vload(version_type &t) =  0;
    virtual void vload(object_id_type &t) =  0;
    virtual void vload(class_id_type &t) =  0;
    virtual void vload(class_id_optional_type &t) = 0;
    virtual void vload(class_name_type &t) = 0;
    virtual void vload(tracking_type &t) = 0;
protected:
    BOOST_ARCHIVE_DECL basic_iarchive(unsigned int flags);
    boost::archive::detail::helper_collection &
    get_helper_collection(){
        return *this;
    }
public:
    // some msvc versions require that the following function be public
    // otherwise it should really protected.
    virtual BOOST_ARCHIVE_DECL ~basic_iarchive();
    // note: NOT part of the public API.
    BOOST_ARCHIVE_DECL void next_object_pointer(void *t);
    BOOST_ARCHIVE_DECL void register_basic_serializer(
        const basic_iserializer & bis
    );
    BOOST_ARCHIVE_DECL void load_object(
        void *t,
        const basic_iserializer & bis
    );
    BOOST_ARCHIVE_DECL const basic_pointer_iserializer *
    load_pointer(
        void * & t,
        const basic_pointer_iserializer * bpis_ptr,
        const basic_pointer_iserializer * (*finder)(
            const boost::serialization::extended_type_info & eti
        )
    );
    // real public API starts here
    BOOST_ARCHIVE_DECL void
    set_library_version(boost::serialization::library_version_type archive_library_version);
    BOOST_ARCHIVE_DECL boost::serialization::library_version_type
    get_library_version() const;
    BOOST_ARCHIVE_DECL unsigned int
    get_flags() const;
    BOOST_ARCHIVE_DECL void
    reset_object_address(const void * new_address, const void * old_address);
    BOOST_ARCHIVE_DECL void
    delete_created_pointers();
};

} // namespace detail
} // namespace archive
} // namespace boost

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif //BOOST_ARCHIVE_DETAIL_BASIC_IARCHIVE_HPP

/* basic_iarchive.hpp
+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
*/