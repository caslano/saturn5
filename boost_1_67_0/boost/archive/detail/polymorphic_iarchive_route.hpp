#ifndef BOOST_ARCHIVE_DETAIL_POLYMORPHIC_IARCHIVE_ROUTE_HPP
#define BOOST_ARCHIVE_DETAIL_POLYMORPHIC_IARCHIVE_ROUTE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// polymorphic_iarchive_route.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <string>
#include <ostream>
#include <cstddef>

#include <boost/config.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{
    using ::size_t;
} // namespace std
#endif

#include <boost/cstdint.hpp>
#include <boost/integer_traits.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

namespace boost {
namespace serialization {
    class extended_type_info;
} // namespace serialization
namespace archive {
namespace detail{

class basic_iserializer;
class basic_pointer_iserializer;

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

template<class ArchiveImplementation>
class polymorphic_iarchive_route :
    public polymorphic_iarchive,
    // note: gcc dynamic cross cast fails if the the derivation below is
    // not public.  I think this is a mistake.
    public /*protected*/ ArchiveImplementation
{
private:
    // these are used by the serialization library.
    virtual void load_object(
        void *t,
        const basic_iserializer & bis
    ){
        ArchiveImplementation::load_object(t, bis);
    }
    virtual const basic_pointer_iserializer * load_pointer(
        void * & t,
        const basic_pointer_iserializer * bpis_ptr,
        const basic_pointer_iserializer * (*finder)(
            const boost::serialization::extended_type_info & type
        )
    ){
        return ArchiveImplementation::load_pointer(t, bpis_ptr, finder);
    }
    virtual void set_library_version(library_version_type archive_library_version){
        ArchiveImplementation::set_library_version(archive_library_version);
    }
    virtual library_version_type get_library_version() const{
        return ArchiveImplementation::get_library_version();
    }
    virtual unsigned int get_flags() const {
        return ArchiveImplementation::get_flags();
    }
    virtual void delete_created_pointers(){
        ArchiveImplementation::delete_created_pointers();
    }
    virtual void reset_object_address(
        const void * new_address,
        const void * old_address
    ){
        ArchiveImplementation::reset_object_address(new_address, old_address);
    }
    virtual void load_binary(void * t, std::size_t size){
        ArchiveImplementation::load_binary(t, size);
    }
    // primitive types the only ones permitted by polymorphic archives
    virtual void load(bool & t){
        ArchiveImplementation::load(t);
    }
    virtual void load(char & t){
        ArchiveImplementation::load(t);
    }
    virtual void load(signed char & t){
        ArchiveImplementation::load(t);
    }
    virtual void load(unsigned char & t){
        ArchiveImplementation::load(t);
    }
    #ifndef BOOST_NO_CWCHAR
    #ifndef BOOST_NO_INTRINSIC_WCHAR_T
    virtual void load(wchar_t & t){
        ArchiveImplementation::load(t);
    }
    #endif
    #endif
    virtual void load(short & t){
        ArchiveImplementation::load(t);
    }
    virtual void load(unsigned short & t){
        ArchiveImplementation::load(t);
    }
    virtual void load(int & t){
        ArchiveImplementation::load(t);
    }
    virtual void load(unsigned int & t){
        ArchiveImplementation::load(t);
    }
    virtual void load(long & t){
        ArchiveImplementation::load(t);
    }
    virtual void load(unsigned long & t){
        ArchiveImplementation::load(t);
    }
    #if defined(BOOST_HAS_LONG_LONG)
    virtual void load(boost::long_long_type & t){
        ArchiveImplementation::load(t);
    }
    virtual void load(boost::ulong_long_type & t){
        ArchiveImplementation::load(t);
    }
    #elif defined(BOOST_HAS_MS_INT64)
    virtual void load(__int64 & t){
        ArchiveImplementation::load(t);
    }
    virtual void load(unsigned __int64 & t){
        ArchiveImplementation::load(t);
    }
    #endif
    virtual void load(float & t){
        ArchiveImplementation::load(t);
    }
    virtual void load(double & t){
        ArchiveImplementation::load(t);
    }
    virtual void load(std::string & t){
        ArchiveImplementation::load(t);
    }
    #ifndef BOOST_NO_STD_WSTRING
    virtual void load(std::wstring & t){
        ArchiveImplementation::load(t);
    }
    #endif
    // used for xml and other tagged formats default does nothing
    virtual void load_start(const char * name){
        ArchiveImplementation::load_start(name);
    }
    virtual void load_end(const char * name){
        ArchiveImplementation::load_end(name);
    }
    virtual void register_basic_serializer(const basic_iserializer & bis){
        ArchiveImplementation::register_basic_serializer(bis);
    }
    virtual helper_collection &
    get_helper_collection(){
        return ArchiveImplementation::get_helper_collection();
    }
public:
    // this can't be inheriteded because they appear in mulitple
    // parents
    typedef mpl::bool_<true> is_loading;
    typedef mpl::bool_<false> is_saving;
    // the >> operator
    template<class T>
    polymorphic_iarchive & operator>>(T & t){
        return polymorphic_iarchive::operator>>(t);
    }
    // the & operator
    template<class T>
    polymorphic_iarchive & operator&(T & t){
        return polymorphic_iarchive::operator&(t);
    }
    // register type function
    template<class T>
    const basic_pointer_iserializer *
    register_type(T * t = NULL){
        return ArchiveImplementation::register_type(t);
    }
    // all current archives take a stream as constructor argument
    template <class _Elem, class _Tr>
    polymorphic_iarchive_route(
        std::basic_istream<_Elem, _Tr> & is,
        unsigned int flags = 0
    ) :
        ArchiveImplementation(is, flags)
    {}
    virtual ~polymorphic_iarchive_route(){};
};

} // namespace detail
} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_ARCHIVE_DETAIL_POLYMORPHIC_IARCHIVE_DISPATCH_HPP

/* polymorphic_iarchive_route.hpp
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
*/