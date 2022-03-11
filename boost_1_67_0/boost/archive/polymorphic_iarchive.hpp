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
    virtual ~polymorphic_iarchive_impl(){};
public:
    // utility function implemented by all legal archives
    virtual void set_library_version(library_version_type archive_library_version) = 0;
    virtual library_version_type get_library_version() const = 0;
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
    virtual ~polymorphic_iarchive(){};
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::archive::polymorphic_iarchive)

#endif // BOOST_ARCHIVE_POLYMORPHIC_IARCHIVE_HPP

/* polymorphic_iarchive.hpp
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
*/