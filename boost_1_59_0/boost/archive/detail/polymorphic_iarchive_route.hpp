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
    void load_object(
        void *t,
        const basic_iserializer & bis
    ) BOOST_OVERRIDE {
        ArchiveImplementation::load_object(t, bis);
    }
    const basic_pointer_iserializer * load_pointer(
        void * & t,
        const basic_pointer_iserializer * bpis_ptr,
        const basic_pointer_iserializer * (*finder)(
            const boost::serialization::extended_type_info & type
        )
    ) BOOST_OVERRIDE {
        return ArchiveImplementation::load_pointer(t, bpis_ptr, finder);
    }
    void set_library_version(boost::serialization::library_version_type archive_library_version) BOOST_OVERRIDE {
        ArchiveImplementation::set_library_version(archive_library_version);
    }
    boost::serialization::library_version_type get_library_version() const BOOST_OVERRIDE {
        return ArchiveImplementation::get_library_version();
    }
    unsigned int get_flags() const BOOST_OVERRIDE {
        return ArchiveImplementation::get_flags();
    }
    void delete_created_pointers() BOOST_OVERRIDE {
        ArchiveImplementation::delete_created_pointers();
    }
    void reset_object_address(
        const void * new_address,
        const void * old_address
    ) BOOST_OVERRIDE {
        ArchiveImplementation::reset_object_address(new_address, old_address);
    }
    void load_binary(void * t, std::size_t size) BOOST_OVERRIDE {
        ArchiveImplementation::load_binary(t, size);
    }
    // primitive types the only ones permitted by polymorphic archives
    void load(bool & t) BOOST_OVERRIDE {
        ArchiveImplementation::load(t);
    }
    void load(char & t) BOOST_OVERRIDE {
        ArchiveImplementation::load(t);
    }
    void load(signed char & t) BOOST_OVERRIDE {
        ArchiveImplementation::load(t);
    }
    void load(unsigned char & t) BOOST_OVERRIDE {
        ArchiveImplementation::load(t);
    }
    #ifndef BOOST_NO_CWCHAR
    #ifndef BOOST_NO_INTRINSIC_WCHAR_T
    void load(wchar_t & t) BOOST_OVERRIDE {
        ArchiveImplementation::load(t);
    }
    #endif
    #endif
    void load(short & t) BOOST_OVERRIDE {
        ArchiveImplementation::load(t);
    }
    void load(unsigned short & t) BOOST_OVERRIDE {
        ArchiveImplementation::load(t);
    }
    void load(int & t) BOOST_OVERRIDE {
        ArchiveImplementation::load(t);
    }
    void load(unsigned int & t) BOOST_OVERRIDE {
        ArchiveImplementation::load(t);
    }
    void load(long & t) BOOST_OVERRIDE {
        ArchiveImplementation::load(t);
    }
    void load(unsigned long & t) BOOST_OVERRIDE {
        ArchiveImplementation::load(t);
    }
    #if defined(BOOST_HAS_LONG_LONG)
    void load(boost::long_long_type & t) BOOST_OVERRIDE {
        ArchiveImplementation::load(t);
    }
    void load(boost::ulong_long_type & t) BOOST_OVERRIDE {
        ArchiveImplementation::load(t);
    }
    #elif defined(BOOST_HAS_MS_INT64)
    void load(__int64 & t) BOOST_OVERRIDE {
        ArchiveImplementation::load(t);
    }
    void load(unsigned __int64 & t) BOOST_OVERRIDE {
        ArchiveImplementation::load(t);
    }
    #endif
    void load(float & t) BOOST_OVERRIDE {
        ArchiveImplementation::load(t);
    }
    void load(double & t) BOOST_OVERRIDE {
        ArchiveImplementation::load(t);
    }
    void load(std::string & t) BOOST_OVERRIDE {
        ArchiveImplementation::load(t);
    }
    #ifndef BOOST_NO_STD_WSTRING
    void load(std::wstring & t) BOOST_OVERRIDE {
        ArchiveImplementation::load(t);
    }
    #endif
    // used for xml and other tagged formats default does nothing
    void load_start(const char * name) BOOST_OVERRIDE {
        ArchiveImplementation::load_start(name);
    }
    void load_end(const char * name) BOOST_OVERRIDE {
        ArchiveImplementation::load_end(name);
    }
    void register_basic_serializer(const basic_iserializer & bis) BOOST_OVERRIDE {
        ArchiveImplementation::register_basic_serializer(bis);
    }
    helper_collection &
    get_helper_collection() BOOST_OVERRIDE {
        return ArchiveImplementation::get_helper_collection();
    }
public:
    // this can't be inherited because they appear in multiple
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
    ~polymorphic_iarchive_route() BOOST_OVERRIDE {}
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