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
sTqF3cFcu2feSvWsYvQd1ny49rrCoeBwj+mYKbMDb50Npr3aTV5K3JXiTFV1nJLUG/mY+7HVj+ORZ8ioUcfexoOzEu3LHq+P8fpwSHJm6xj1kzNSp1k/qlRkD3dfptc8Vs28sq1QRDLQv2a848XhHNPmGp6jjGZV5aUDtRdwuyczij+OStw/vS5QMM+pKjBC6/mz4g28kX2c/JKegwqrLw3NZVcXPsfZaNzEKD6eK1AQecG4f6pNNfHUq2mJgmVuF8/yxqTIhr7Iab7MWRBfmTzssOTy1uriahXZPcuLRaxHnxJo9ma5HxLf+Wa1DGfTisB1DiZMn94fb38oOnRw8rjRUj9tozhvmyC9RxlWwhpmy0KGru6MajGTC/rQtXLRUV85O82mvgXMZsE3+Zxlnm2vznkxZLDram5AydbsLJaVYcVy+I85t8Zy0w7GqGzj/uxlS7OgJCJbOyL9PP6gsvqFlUE0JrcVDmwlJrSqHmmw9+Xv7KQfvWdnJ59udtiptMyZzi0s6N3ISnWlitHo5AMfhcq2xA4z1LINzPmZbd/Zk7xRrXpFVOyDx9fLPuSUDj349FZnWf3AdYbOPfThLMc16K6NBUVvfvWEzel4sg8b+20fPENLT/fNgyLaW7AZN253BXZ8jBS2SlnnSQwsv6moL/b6jMaJU6MtxYoHF7/9PCcwy2Mc+KZK/7hSmuFi6qDlWnN+XUX92wL3siw1PFY27SwdHpAcNaD1+VL6rcDaAr7yDHxFsqGUNpOVqWLJ+7vTc0qfowtW3G2yPXa211u1bEv26Z3V7bf6yqMtTp8P0OetOZXqIE61Q2RHeNVhx8pHSypUC9+pMthtjmAKMn35hlVnwE/C16+8tcxPh5r2zKf9DU3bL69btodza5nTDf8llUbrJBNN71UeIVLnsS4IHPVjvTZ7Mur6mrUHNM8MHisMb9NJmVgdHGt4lV8zz9GT48XewLM+JaM++4iXnillXKNVn1SncTnwka5y68By1zjtChuD48qDoyvXvaPJfL9otVl+jxu1C2H2xM0Qz+MP290C3QLcqaPjbswkTWtoddrjYliCz78O8pEIrull3hCYf+ekRk5efNZmyVGRG9qJZ28kuy8yeHEcy79bMPyKbPDJF6I+L5oNVr89Ehup1LTiVveR8v7UPMveg7jByvPYmc3djSfMlC+cq2PZ5maikDiECfB42rLWcPvs8zd20+cEM0quXPNZrMVwVDW2/NSKo+08jKW+KfEcD+Ruz23OPjVTXrFl5Oby6D0scvhP3o+sw1ezPg+g0lzcMtd74NCM78ulr9PcrGku3o5JOHD845z8zsHr8kULm+cuKsRPf1wZqmn/sXjzMnVX89VeEyaBKZEluEYV/sYJ2muPj1/wXVwQrcJGzCQGZtxzOr6w12dxTaqxiPaE+eb0oXIZqSa6gU+iESqBnZ/zdA/laxvf9WHJWsG44jp3KJs94+znCJG5D+yPdtpcNzm0cveDjsVVUYprv4g3NJ00Gp1p21vfY2XMkRClsUOTOSP/dnFgjIm6bXOE7AmzTZm1mBHdvYfVNHeGLVAqdm7ltdpwZMr3MPVG/WHtOYmGtHtmZU3lNIot9qN5Oo1R2xnCuR0w+oq9acUtfbc5/WnTpOUMT1n5YFu3xLB2SHvPEKW1H2UdqAp3y7709U+RvU80uWIMZ8LvfEiiUomYS8erdFFbhIg9byfa8Jx62yGR5iB2ndHUHud1wyqstrdpeEV9Rc0o7rDQ1XcV8oGPCncJWDUG9eaYb31R8LiEzU/OZMGHLWpjrNX2Dmaam/TMNO6uNuQ7Oigmx5V3dFXpKyxr28kbQsHq1r0KQad91BeZ6cRLiJg=
*/