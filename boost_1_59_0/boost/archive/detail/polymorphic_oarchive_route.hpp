#ifndef BOOST_ARCHIVE_DETAIL_POLYMORPHIC_OARCHIVE_ROUTE_HPP
#define BOOST_ARCHIVE_DETAIL_POLYMORPHIC_OARCHIVE_ROUTE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// polymorphic_oarchive_route.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <string>
#include <ostream>
#include <cstddef> // size_t

#include <boost/config.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{
    using ::size_t;
} // namespace std
#endif

#include <boost/cstdint.hpp>
#include <boost/integer_traits.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

namespace boost {
namespace serialization {
    class extended_type_info;
} // namespace serialization
namespace archive {
namespace detail{

class basic_oserializer;
class basic_pointer_oserializer;

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

template<class ArchiveImplementation>
class polymorphic_oarchive_route :
    public polymorphic_oarchive,
    // note: gcc dynamic cross cast fails if the the derivation below is
    // not public.  I think this is a mistake.
    public /*protected*/ ArchiveImplementation
{
private:
    // these are used by the serialization library.
    void save_object(
        const void *x,
        const detail::basic_oserializer & bos
    ) BOOST_OVERRIDE {
        ArchiveImplementation::save_object(x, bos);
    }
    void save_pointer(
        const void * t,
        const detail::basic_pointer_oserializer * bpos_ptr
    ) BOOST_OVERRIDE {
        ArchiveImplementation::save_pointer(t, bpos_ptr);
    }
    void save_null_pointer() BOOST_OVERRIDE {
        ArchiveImplementation::save_null_pointer();
    }
    // primitive types the only ones permitted by polymorphic archives
    void save(const bool t) BOOST_OVERRIDE {
        ArchiveImplementation::save(t);
    }
    void save(const char t) BOOST_OVERRIDE {
        ArchiveImplementation::save(t);
    }
    void save(const signed char t) BOOST_OVERRIDE {
        ArchiveImplementation::save(t);
    }
    void save(const unsigned char t) BOOST_OVERRIDE {
        ArchiveImplementation::save(t);
    }
    #ifndef BOOST_NO_CWCHAR
    #ifndef BOOST_NO_INTRINSIC_WCHAR_T
    void save(const wchar_t t) BOOST_OVERRIDE {
        ArchiveImplementation::save(t);
    }
    #endif
    #endif
    void save(const short t) BOOST_OVERRIDE {
        ArchiveImplementation::save(t);
    }
    void save(const unsigned short t) BOOST_OVERRIDE {
        ArchiveImplementation::save(t);
    }
    void save(const int t) BOOST_OVERRIDE {
        ArchiveImplementation::save(t);
    }
    void save(const unsigned int t) BOOST_OVERRIDE {
        ArchiveImplementation::save(t);
    }
    void save(const long t) BOOST_OVERRIDE {
        ArchiveImplementation::save(t);
    }
    void save(const unsigned long t) BOOST_OVERRIDE {
        ArchiveImplementation::save(t);
    }
    #if defined(BOOST_HAS_LONG_LONG)
    void save(const boost::long_long_type t) BOOST_OVERRIDE {
        ArchiveImplementation::save(t);
    }
    void save(const boost::ulong_long_type t) BOOST_OVERRIDE {
        ArchiveImplementation::save(t);
    }
    #elif defined(BOOST_HAS_MS_INT64)
    void save(const boost::int64_t t) BOOST_OVERRIDE {
        ArchiveImplementation::save(t);
    }
    void save(const boost::uint64_t t) BOOST_OVERRIDE {
        ArchiveImplementation::save(t);
    }
    #endif
    void save(const float t) BOOST_OVERRIDE {
        ArchiveImplementation::save(t);
    }
    void save(const double t) BOOST_OVERRIDE {
        ArchiveImplementation::save(t);
    }
    void save(const std::string & t) BOOST_OVERRIDE {
        ArchiveImplementation::save(t);
    }
    #ifndef BOOST_NO_STD_WSTRING
    void save(const std::wstring & t) BOOST_OVERRIDE {
        ArchiveImplementation::save(t);
    }
    #endif
    boost::serialization::library_version_type get_library_version() const BOOST_OVERRIDE {
        return ArchiveImplementation::get_library_version();
    }
    unsigned int get_flags() const BOOST_OVERRIDE {
        return ArchiveImplementation::get_flags();
    }
    void save_binary(const void * t, std::size_t size) BOOST_OVERRIDE {
        ArchiveImplementation::save_binary(t, size);
    }
    // used for xml and other tagged formats default does nothing
    void save_start(const char * name) BOOST_OVERRIDE {
        ArchiveImplementation::save_start(name);
    }
    void save_end(const char * name) BOOST_OVERRIDE {
        ArchiveImplementation::save_end(name);
    }
    void end_preamble() BOOST_OVERRIDE {
        ArchiveImplementation::end_preamble();
    }
    void register_basic_serializer(const detail::basic_oserializer & bos) BOOST_OVERRIDE {
        ArchiveImplementation::register_basic_serializer(bos);
    }
    helper_collection &
    get_helper_collection() BOOST_OVERRIDE {
        return ArchiveImplementation::get_helper_collection();
    }
public:
    // this can't be inherited because they appear in multiple
    // parents
    typedef mpl::bool_<false> is_loading;
    typedef mpl::bool_<true> is_saving;
    // the << operator
    template<class T>
    polymorphic_oarchive & operator<<(T & t){
        return polymorphic_oarchive::operator<<(t);
    }
    // the & operator
    template<class T>
    polymorphic_oarchive & operator&(T & t){
        return polymorphic_oarchive::operator&(t);
    }
    // register type function
    template<class T>
    const basic_pointer_oserializer *
    register_type(T * t = NULL){
        return ArchiveImplementation::register_type(t);
    }
    // all current archives take a stream as constructor argument
    template <class _Elem, class _Tr>
    polymorphic_oarchive_route(
        std::basic_ostream<_Elem, _Tr> & os,
        unsigned int flags = 0
    ) :
        ArchiveImplementation(os, flags)
    {}
    ~polymorphic_oarchive_route() BOOST_OVERRIDE {}
};

} // namespace detail
} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_ARCHIVE_DETAIL_POLYMORPHIC_OARCHIVE_DISPATCH_HPP

/* polymorphic_oarchive_route.hpp
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
*/