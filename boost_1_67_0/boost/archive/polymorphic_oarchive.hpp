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
    virtual ~polymorphic_oarchive_impl(){};
public:
    // utility functions implemented by all legal archives
    virtual unsigned int get_flags() const = 0;
    virtual library_version_type get_library_version() const = 0;
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
    virtual ~polymorphic_oarchive(){};
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