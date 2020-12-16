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
524IwrLzPU+JtheT4hfDY/ZLngvvK9571IiG58lo0fS5NyrK7CZSF6u2rg/auG20k6pKOpVXt3kwSFbmLZY293zHYP6KUe/Sy4lpzk3t3to7DKOu4VVp94Q0slB/nPMS8bXIZ+1LlTFlwr4b9lQ9TzebU3AKb7ECP965g3+Vqd9SkbrCNG0ljGotVrCSWXJh86y2bHr5c4w4H4f30lXL2Xe/tdrzgHVX7NzhL6bLxE3xdMu/fFnC/ICRh1GAiosOQ6Xr/+Xg1oGZiTNXqVb3+5m+LWzCqXTSHz2bdEdoKJ7YORf8mCr88CTtzqdbFIQd0zDBLb59w756Kbvs1Safjtt1ZmkKT95PuX43SnpjvK+iDg7r3vxKLp+dhkWHeOcmy8w6na6sDvfokQD+U4bbrLRfYfSka2OksDan7/AxptNWztFxy+zuNtniV21ZcynzkfGBIceRtjjH48kSgtuSfbbFyR+zL0vXvqfKTh2UoDqsJdBQGISlZubOV+SPn+HuM+IU2eqgIex0tDXybo+7y5Eu+ltCC8THqSOZPAPuDPWsVFgsInetw4bzgQuHOU9YZ4ESr8CHpOXp3rJLMTVH+WlplNiZmnr2lTwxaOx+4jagrXQhTqJjwFv/cs8QZqSil/nSnbzdcyUG/VdtpF/KZHONrF5pSJ9dc+N0XGWNAW8AwXYZbulB14chDtTlDKXu+usrRiYUI8Rry4yFFEYaCpb7F6xSsI8etbiP/ZxuWekvIneObv3jBUf1aq/cb00dWf9xOe1+c06+tbFUVnpermen3VukpLKF49odH23cFrnwvsahvuee+3sNhncdop7zVd2b5xYjke7/YVF3nUvoMG3bG9rSTK7OCe615/1cCvKm12Rhd1eOHrFlWqeXpswlk5LfO6WyRUD4CO9a1skK3Ie2vYQZqYomG9YlQml+nM9q3nPTXjq5HJMlzLFIwETKYoS44ODslyLN54ye3KEli6IvO7FLMePPbm1l2/oov/nBk/DK68yvqCSn544S7VJfDx12GD+zQqLxYT1XcMdd21KGq89S1R4asJ6NrAyXp3ogUZVTJ1WaRy/i8ez1xQuL1/f6OOb7zhphBvkbKuaurapiPT1RdYX9VII3H6apvzdwyjmR7aQkDiOQIF45J5B6jSM4VtTv1B2/9tykG2ve1IoSLr42WTsueXlA8UpDXLnJ0f61SS2Zej3MoXULni5bZkpFE8fgPrUppeOgQYZHp0F3R6nJmEBYt2vkHvqq3NHK9MKm/LfP3EtX9oqqc1R0jtpIfPLqu3HzntOE8XDXuFvio6fM23rk5ULaVkgEhS2zcsY8mFGLy0wStRVNqJDQzCq1PA5fyX6r7WXzWQk6305eJ6H2t3sO8vSt0p2y6/58iPYRJ81WAbXQhn0vClaIEjxVZ58+8pQPVJ6qE4vfXWmYH9jUqcUs2utlq3t78xcsf4ivvnRi9tjIEmLuXPPdqhDFJt/RBbTMtb63XRzWdlqynGX3lL4053eocNKomU/t/Es1P04pro/vPjE+Yp/sx/DQNWGK9js/EyxY8zDAQm7TqqmrXrOlNn79aX112PtjnBqa9/zvTj5S4gyR08jI5njIHdk313FlF9UCDdMrNxfTfl6aKPR6tEE5Ok9J61P+sVVfeIuiqc9mKtMu0F/+kBBT1D+xhyjElZ7QOkJ/d0Fi+qkrt+WrDn3x3G0xPf5eyf+GtUES85vIhDz28P3Dr7L7mMIMDne1Xv4iqiXea2mBKW+kpjt29d7hSff4NbJ0zO9lQgypS3GCtSkqT/3TlnQ2Gd9yKT8tYD3SK9AysPmTbu6bazW1fhkiAacTtmA+rDA53Sz3ZeGcFvMQwyo=
*/