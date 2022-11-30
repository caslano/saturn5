#ifndef BOOST_ARCHIVE_POLYMORPHIC_IARCHIVE_HPP
#define BOOST_ARCHIVE_POLYMORPHIC_IARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// polymorphic_iarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <cstddef> // std::size_t
#include <climits> // ULONG_MAX
#include <string>

#include <boost/config.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{
    using ::size_t;
} // namespace std
#endif

#include <boost/cstdint.hpp>

#include <boost/archive/detail/iserializer.hpp>
#include <boost/archive/detail/interface_iarchive.hpp>
#include <boost/serialization/library_version_type.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/archive/detail/register_archive.hpp>

#include <boost/archive/detail/decl.hpp>
#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

namespace boost {
namespace serialization {
    class extended_type_info;
} // namespace serialization
namespace archive {
namespace detail {
    class basic_iarchive;
    class basic_iserializer;
}

class polymorphic_iarchive;

class BOOST_SYMBOL_VISIBLE polymorphic_iarchive_impl :
    public detail::interface_iarchive<polymorphic_iarchive>
{
#ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
    friend class detail::interface_iarchive<polymorphic_iarchive>;
    friend class load_access;
#endif
    // primitive types the only ones permitted by polymorphic archives
    virtual void load(bool & t) = 0;

    virtual void load(char & t) = 0;
    virtual void load(signed char & t) = 0;
    virtual void load(unsigned char & t) = 0;
    #ifndef BOOST_NO_CWCHAR
    #ifndef BOOST_NO_INTRINSIC_WCHAR_T
    virtual void load(wchar_t & t) = 0;
    #endif
    #endif
    virtual void load(short & t) = 0;
    virtual void load(unsigned short & t) = 0;
    virtual void load(int & t) = 0;
    virtual void load(unsigned int & t) = 0;
    virtual void load(long & t) = 0;
    virtual void load(unsigned long & t) = 0;

    #if defined(BOOST_HAS_LONG_LONG)
    virtual void load(boost::long_long_type & t) = 0;
    virtual void load(boost::ulong_long_type & t) = 0;
    #elif defined(BOOST_HAS_MS_INT64)
    virtual void load(__int64 & t) = 0;
    virtual void load(unsigned __int64 & t) = 0;
    #endif

    virtual void load(float & t) = 0;
    virtual void load(double & t) = 0;

    // string types are treated as primitives
    virtual void load(std::string & t) = 0;
    #ifndef BOOST_NO_STD_WSTRING
    virtual void load(std::wstring & t) = 0;
    #endif

    // used for xml and other tagged formats
    virtual void load_start(const char * name) = 0;
    virtual void load_end(const char * name) = 0;
    virtual void register_basic_serializer(const detail::basic_iserializer & bis) = 0;
    virtual detail::helper_collection & get_helper_collection() = 0;

    // msvc and borland won't automatically pass these to the base class so
    // make it explicit here
    template<class T>
    void load_override(T & t)
    {
        archive::load(* this->This(), t);
    }
    // special treatment for name-value pairs.
    template<class T>
    void load_override(
        const boost::serialization::nvp< T > & t
    ){
        load_start(t.name());
        archive::load(* this->This(), t.value());
        load_end(t.name());
    }
protected:
    virtual ~polymorphic_iarchive_impl() {}
public:
    // utility function implemented by all legal archives
    virtual void set_library_version(
        boost::serialization::library_version_type archive_library_version
    ) = 0;
    virtual boost::serialization::library_version_type get_library_version() const = 0;
    virtual unsigned int get_flags() const = 0;
    virtual void delete_created_pointers() = 0;
    virtual void reset_object_address(
        const void * new_address,
        const void * old_address
    ) = 0;

    virtual void load_binary(void * t, std::size_t size) = 0;

    // these are used by the serialization library implementation.
    virtual void load_object(
        void *t,
        const detail::basic_iserializer & bis
    ) = 0;
    virtual const detail::basic_pointer_iserializer * load_pointer(
        void * & t,
        const detail::basic_pointer_iserializer * bpis_ptr,
        const detail::basic_pointer_iserializer * (*finder)(
            const boost::serialization::extended_type_info & type
        )
    ) = 0;
};

} // namespace archive
} // namespace boost

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

namespace boost {
namespace archive {

class BOOST_SYMBOL_VISIBLE polymorphic_iarchive :
    public polymorphic_iarchive_impl
{
public:
    ~polymorphic_iarchive() BOOST_OVERRIDE {}
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::archive::polymorphic_iarchive)

#endif // BOOST_ARCHIVE_POLYMORPHIC_IARCHIVE_HPP

/* polymorphic_iarchive.hpp
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
*/