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
    set_library_version(library_version_type archive_library_version);
    BOOST_ARCHIVE_DECL library_version_type
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
m5quyihOyyjQZefnQZ9IDs5Yq18XkZqL39PW5RcuXLn4scfEp4wZD6lmq5bm6TLWZRSq8jdkFGbm5m8kn3auWUHNp7zh/zxqJDWcmg2CzKRyqXwqldJR2VQetQ4gBfCMaR2kiyg9PCOkkDznQQrvQpl0KgMupERRwrqZRN+vl75UIoOk9FBDFqFbAOXTAIocIHUVPBdCrp5aT3B1gNNHWaLr/1/QRYwN0KJCeM7rpS7QFujOhUuim0qtFVs7g3oInrMAUgT3tVAOS6qAeiq0P7df2yU68/8L/nSQUwgQlKcKLtRF6gD+FvTS1QO9DKoY6GQAHR3hQgWt0gNHqMP+1FBPadQThI9CIoHCQfQ1105fg9PPIhQL/iMd/350UJa5pK06KKGCq6BXhqiLIvgr5KMloY5QMvfSnUf5/hdyTSZ1YFtQKo8QuUpPKiJjgbvB6nu0t74CqKOQ0BVsSAfPqH+sB9uYRqSe388yBtrtvP/KLooAL53QVpH+mE1qwhqyqafEHov1Dsb/gv+iPrSVjf9lfX7/Vu/3Usuws6n+fcjHri8Ggf2vtGvDYHQGG398wBIlGoGAj3pfDzXp/gNHOsJTX73riWSknFSi43yi8wxqDtBfCdBsMjogvXRiv4KVFZGRBEcNPRlTs0nZEqIBYazDUTW3t4Qg2Tn3yGLef6lHwRIzxJqFnPWD6FCqx+c/yEsPNSG1CLIuHS72
*/