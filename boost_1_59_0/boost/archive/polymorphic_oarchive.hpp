#ifndef BOOST_ARCHIVE_POLYMORPHIC_OARCHIVE_HPP
#define BOOST_ARCHIVE_POLYMORPHIC_OARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// polymorphic_oarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <cstddef> // size_t
#include <climits> // ULONG_MAX
#include <string>

#include <boost/config.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{
    using ::size_t;
} // namespace std
#endif

#include <boost/cstdint.hpp>
#include <boost/archive/detail/oserializer.hpp>
#include <boost/archive/detail/interface_oarchive.hpp>
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
    class basic_oarchive;
    class basic_oserializer;
}

class polymorphic_oarchive;

class BOOST_SYMBOL_VISIBLE polymorphic_oarchive_impl :
    public detail::interface_oarchive<polymorphic_oarchive>
{
#ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
    friend class detail::interface_oarchive<polymorphic_oarchive>;
    friend class save_access;
#endif
    // primitive types the only ones permitted by polymorphic archives
    virtual void save(const bool t) = 0;

    virtual void save(const char t) = 0;
    virtual void save(const signed char t) = 0;
    virtual void save(const unsigned char t) = 0;
    #ifndef BOOST_NO_CWCHAR
    #ifndef BOOST_NO_INTRINSIC_WCHAR_T
    virtual void save(const wchar_t t) = 0;
    #endif
    #endif
    virtual void save(const short t) = 0;
    virtual void save(const unsigned short t) = 0;
    virtual void save(const int t) = 0;
    virtual void save(const unsigned int t) = 0;
    virtual void save(const long t) = 0;
    virtual void save(const unsigned long t) = 0;

    #if defined(BOOST_HAS_LONG_LONG)
    virtual void save(const boost::long_long_type t) = 0;
    virtual void save(const boost::ulong_long_type t) = 0;
    #elif defined(BOOST_HAS_MS_INT64)
    virtual void save(const __int64 t) = 0;
    virtual void save(const unsigned __int64 t) = 0;
    #endif

    virtual void save(const float t) = 0;
    virtual void save(const double t) = 0;

    // string types are treated as primitives
    virtual void save(const std::string & t) = 0;
    #ifndef BOOST_NO_STD_WSTRING
    virtual void save(const std::wstring & t) = 0;
    #endif

    virtual void save_null_pointer() = 0;
    // used for xml and other tagged formats
    virtual void save_start(const char * name) = 0;
    virtual void save_end(const char * name) = 0;
    virtual void register_basic_serializer(const detail::basic_oserializer & bos) = 0;
    virtual detail::helper_collection & get_helper_collection() = 0;

    virtual void end_preamble() = 0;

    // msvc and borland won't automatically pass these to the base class so
    // make it explicit here
    template<class T>
    void save_override(T & t)
    {
        archive::save(* this->This(), t);
    }
    // special treatment for name-value pairs.
    template<class T>
    void save_override(
            const ::boost::serialization::nvp< T > & t
        ){
        save_start(t.name());
        archive::save(* this->This(), t.const_value());
        save_end(t.name());
    }
protected:
    virtual ~polymorphic_oarchive_impl() {}
public:
    // utility functions implemented by all legal archives
    virtual unsigned int get_flags() const = 0;
    virtual boost::serialization::library_version_type get_library_version() const = 0;
    virtual void save_binary(const void * t, std::size_t size) = 0;

    virtual void save_object(
        const void *x,
        const detail::basic_oserializer & bos
    ) = 0;
    virtual void save_pointer(
        const void * t,
        const detail::basic_pointer_oserializer * bpos_ptr
    ) = 0;
};

// note: preserve naming symmetry
class BOOST_SYMBOL_VISIBLE polymorphic_oarchive :
    public polymorphic_oarchive_impl
{
public:
    ~polymorphic_oarchive() BOOST_OVERRIDE {}
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::archive::polymorphic_oarchive)

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_ARCHIVE_POLYMORPHIC_OARCHIVE_HPP

/* polymorphic_oarchive.hpp
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
*/