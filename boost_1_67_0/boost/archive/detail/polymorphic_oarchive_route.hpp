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
    virtual void save_object(
        const void *x,
        const detail::basic_oserializer & bos
    ){
        ArchiveImplementation::save_object(x, bos);
    }
    virtual void save_pointer(
        const void * t,
        const detail::basic_pointer_oserializer * bpos_ptr
    ){
        ArchiveImplementation::save_pointer(t, bpos_ptr);
    }
    virtual void save_null_pointer(){
        ArchiveImplementation::save_null_pointer();
    }
    // primitive types the only ones permitted by polymorphic archives
    virtual void save(const bool t){
        ArchiveImplementation::save(t);
    }
    virtual void save(const char t){
        ArchiveImplementation::save(t);
    }
    virtual void save(const signed char t){
        ArchiveImplementation::save(t);
    }
    virtual void save(const unsigned char t){
        ArchiveImplementation::save(t);
    }
    #ifndef BOOST_NO_CWCHAR
    #ifndef BOOST_NO_INTRINSIC_WCHAR_T
    virtual void save(const wchar_t t){
        ArchiveImplementation::save(t);
    }
    #endif
    #endif
    virtual void save(const short t){
        ArchiveImplementation::save(t);
    }
    virtual void save(const unsigned short t){
        ArchiveImplementation::save(t);
    }
    virtual void save(const int t){
        ArchiveImplementation::save(t);
    }
    virtual void save(const unsigned int t){
        ArchiveImplementation::save(t);
    }
    virtual void save(const long t){
        ArchiveImplementation::save(t);
    }
    virtual void save(const unsigned long t){
        ArchiveImplementation::save(t);
    }
    #if defined(BOOST_HAS_LONG_LONG)
    virtual void save(const boost::long_long_type t){
        ArchiveImplementation::save(t);
    }
    virtual void save(const boost::ulong_long_type t){
        ArchiveImplementation::save(t);
    }
    #elif defined(BOOST_HAS_MS_INT64)
    virtual void save(const boost::int64_t t){
        ArchiveImplementation::save(t);
    }
    virtual void save(const boost::uint64_t t){
        ArchiveImplementation::save(t);
    }
    #endif
    virtual void save(const float t){
        ArchiveImplementation::save(t);
    }
    virtual void save(const double t){
        ArchiveImplementation::save(t);
    }
    virtual void save(const std::string & t){
        ArchiveImplementation::save(t);
    }
    #ifndef BOOST_NO_STD_WSTRING
    virtual void save(const std::wstring & t){
        ArchiveImplementation::save(t);
    }
    #endif
    virtual library_version_type get_library_version() const{
        return ArchiveImplementation::get_library_version();
    }
    virtual unsigned int get_flags() const {
        return ArchiveImplementation::get_flags();
    }
    virtual void save_binary(const void * t, std::size_t size){
        ArchiveImplementation::save_binary(t, size);
    }
    // used for xml and other tagged formats default does nothing
    virtual void save_start(const char * name){
        ArchiveImplementation::save_start(name);
    }
    virtual void save_end(const char * name){
        ArchiveImplementation::save_end(name);
    }
    virtual void end_preamble(){
        ArchiveImplementation::end_preamble();
    }
    virtual void register_basic_serializer(const detail::basic_oserializer & bos){
        ArchiveImplementation::register_basic_serializer(bos);
    }
    virtual helper_collection &
    get_helper_collection(){
        return ArchiveImplementation::get_helper_collection();
    }
public:
    // this can't be inheriteded because they appear in mulitple
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
    virtual ~polymorphic_oarchive_route(){};
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