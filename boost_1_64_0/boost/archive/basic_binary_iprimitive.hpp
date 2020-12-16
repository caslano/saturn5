#ifndef BOOST_ARCHIVE_BINARY_IPRIMITIVE_HPP
#define BOOST_ARCHIVE_BINARY_IPRIMITIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

#if defined(_MSC_VER)
#pragma warning( disable : 4800 )
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_binary_iprimitive.hpp
//
// archives stored as native binary - this should be the fastest way
// to archive the state of a group of obects.  It makes no attempt to
// convert to any canonical form.

// IN GENERAL, ARCHIVES CREATED WITH THIS CLASS WILL NOT BE READABLE
// ON PLATFORM APART FROM THE ONE THEY ARE CREATED ON

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <iosfwd>
#include <boost/assert.hpp>
#include <locale>
#include <cstring> // std::memcpy
#include <cstddef> // std::size_t
#include <streambuf> // basic_streambuf
#include <string>

#include <boost/config.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{
    using ::memcpy;
    using ::size_t;
} // namespace std
#endif

#include <boost/cstdint.hpp>
#include <boost/serialization/throw_exception.hpp>
#include <boost/integer.hpp>
#include <boost/integer_traits.hpp>

//#include <boost/mpl/placeholders.hpp>
#include <boost/serialization/is_bitwise_serializable.hpp>
#include <boost/serialization/array_wrapper.hpp>

#include <boost/archive/basic_streambuf_locale_saver.hpp>
#include <boost/archive/codecvt_null.hpp>
#include <boost/archive/archive_exception.hpp>
#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

namespace boost {
namespace archive {

/////////////////////////////////////////////////////////////////////////////
// class binary_iarchive - read serialized objects from a input binary stream
template<class Archive, class Elem, class Tr>
class BOOST_SYMBOL_VISIBLE basic_binary_iprimitive {
#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
    friend class load_access;
protected:
#else
public:
#endif
    std::basic_streambuf<Elem, Tr> & m_sb;
    // return a pointer to the most derived class
    Archive * This(){
        return static_cast<Archive *>(this);
    }

    #ifndef BOOST_NO_STD_LOCALE
    // note order! - if you change this, libstd++ will fail!
    // a) create new locale with new codecvt facet
    // b) save current locale
    // c) change locale to new one
    // d) use stream buffer
    // e) change locale back to original
    // f) destroy new codecvt facet
    boost::archive::codecvt_null<Elem> codecvt_null_facet;
    basic_streambuf_locale_saver<Elem, Tr> locale_saver;
    std::locale archive_locale;
    #endif

    // main template for serilization of primitive types
    template<class T>
    void load(T & t){
        load_binary(& t, sizeof(T));
    }

    /////////////////////////////////////////////////////////
    // fundamental types that need special treatment

    // trap usage of invalid uninitialized boolean
    void load(bool & t){
        load_binary(& t, sizeof(t));
        int i = t;
        BOOST_ASSERT(0 == i || 1 == i);
        (void)i; // warning suppression for release builds.
    }
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    load(std::string &s);
    #ifndef BOOST_NO_STD_WSTRING
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    load(std::wstring &ws);
    #endif
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    load(char * t);
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    load(wchar_t * t);

    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    init();
    BOOST_ARCHIVE_OR_WARCHIVE_DECL
    basic_binary_iprimitive(
        std::basic_streambuf<Elem, Tr> & sb,
        bool no_codecvt
    );
    BOOST_ARCHIVE_OR_WARCHIVE_DECL
    ~basic_binary_iprimitive();
public:
    // we provide an optimized load for all fundamental types
    // typedef serialization::is_bitwise_serializable<mpl::_1>
    // use_array_optimization;
    struct use_array_optimization {
        template <class T>
        #if defined(BOOST_NO_DEPENDENT_NESTED_DERIVATIONS)
            struct apply {
                typedef typename boost::serialization::is_bitwise_serializable< T >::type type;
            };
        #else
            struct apply : public boost::serialization::is_bitwise_serializable< T > {};
        #endif
    };

    // the optimized load_array dispatches to load_binary
    template <class ValueType>
    void load_array(serialization::array_wrapper<ValueType>& a, unsigned int)
    {
      load_binary(a.address(),a.count()*sizeof(ValueType));
    }

    void
    load_binary(void *address, std::size_t count);
};

template<class Archive, class Elem, class Tr>
inline void
basic_binary_iprimitive<Archive, Elem, Tr>::load_binary(
    void *address,
    std::size_t count
){
    // note: an optimizer should eliminate the following for char files
    BOOST_ASSERT(
        static_cast<std::streamsize>(count / sizeof(Elem))
        <= boost::integer_traits<std::streamsize>::const_max
    );
    std::streamsize s = static_cast<std::streamsize>(count / sizeof(Elem));
    std::streamsize scount = m_sb.sgetn(
        static_cast<Elem *>(address),
        s
    );
    if(scount != s)
        boost::serialization::throw_exception(
            archive_exception(archive_exception::input_stream_error)
        );
    // note: an optimizer should eliminate the following for char files
    BOOST_ASSERT(count % sizeof(Elem) <= boost::integer_traits<std::streamsize>::const_max);
    s = static_cast<std::streamsize>(count % sizeof(Elem));
    if(0 < s){
//        if(is.fail())
//            boost::serialization::throw_exception(
//                archive_exception(archive_exception::stream_error)
//        );
        Elem t;
        scount = m_sb.sgetn(& t, 1);
        if(scount != 1)
            boost::serialization::throw_exception(
                archive_exception(archive_exception::input_stream_error)
            );
        std::memcpy(static_cast<char*>(address) + (count - s), &t, static_cast<std::size_t>(s));
    }
}

} // namespace archive
} // namespace boost

#include <boost/archive/detail/abi_suffix.hpp> // pop pragmas

#endif // BOOST_ARCHIVE_BINARY_IPRIMITIVE_HPP

/* basic_binary_iprimitive.hpp
+1yzhB3vhKaElW+pQiflMBfXBudrj9NC9Eo+HPf7Q8yB2u6tppp61KI17WNDwFS9+RD2AJEM+lHEccKYO2mecjRtoGvoxeQW4KI5psCmAU4R3QUINmqIw6/QUm/hncltB7ryNqAWui5teAwwe18y3Ey0yqWHzQdj6PUPd2XolceInTPSaWbGfqIIwOnte8X/v6VG6fQSA3TU4co5w1N0u7T46kBFHs/+RLHmVdZ35M3w/rknx2b/W/KLPrbZ/5b882zKT7Dkz3zRZv9b8rvb1N/Nkt/wBZv9b8m/7DEb+mfJP8Mm/8gUC/0bYjN+S367ATbjt+R/btO/CZb85/Ntxm/J7z7bZvyW/EWP2Izfkp9E5e3jvxhQaYZ7yiT9kUFsgxcZdQD7gZ6a9w1ismjzfij5q0cazyrLQcYmFGvFp4rY9u/n974RVPH1srW14tIzm0SZPs0JZ40u/PFp61KW4zbBF4mm/c2LxKWIkoqQCVlEMs0LRRxdKEhwd6GSidYh4t4wl5m/+KLTcP9pJ68l+01ZlpdflwOht8eVhXhq6DwOANwnfdotjkMk3zjfWzgoiQk3CLjeBXSU1wHLSDaAkBP6tG1BuDv2gIixK5nNNFXdaao4MGa/bO1PLbKYh1zA5uJpeS1c7tFjSN4aWOpi+7oHXcQgDwO7nYy0ZLhHGd6fGZ4/w58CWcxhHffy49EhZifTvIG29KTcfaBghtji1CYmZtNAOSXPUL/XgFVQK09uXVEXXKic159dqLzpCZVmtqXuPJ2L48HXdpv/XHa5EGxF3+v7tGwIg1ChDzJmpXtTn086tR41fQXZLELtJ8EnNQxcRKhqev4lYtT0m2/13CJIufZVQ3yWreH/KyjY4RUP8RFYzxRaenr8GcxDe1eIY+GlQ28GT0FarLd4VzyHs9Z+YWcEGJcTGAlPjA/yWqSo+7byV3PLB3LC+ieq65EYzYqPmuIHeYI34hctfXd9xoNyb3+ZylOy3ojLr/VpsBc7pgf7maLsjuTB+z4sFJyDZ2jOlOW8f7Y8oDzvFIgNJYdp7JpIXqm7JKKeUkcdZGRrHVz6N4OlrsBjyfT8mp/LkrVkwzl+MlGFouHBEL/XsrvEBg+Ku8R7QiFDLI5O8wWErRfYv4E5dYEbW8YwVHAbEGLDyt/7Y09/9k02PHvxtvLGbsalLG2Qa2gXYhQmF/HssjWGrt8h/FKXH9snOegi20C8rCNXvz6Os67wilWxA9weXAj6E0NwZVGS3HaoK29G5cQHw/9m5Sl/iMFNJGbTdXM3aNh1s8T/nWxwp4X9i4G+Hm0ziJI+AGsfWuYTyaZ77h7XAvri+ZT+/wn9r9DrdLc/XvB0i7ECUDPD3f4w/tZyty8jkWxhB7YxFwFKzz/DcJnePFMzCnuF4H80M39v7uUe8kK+Sh8KKQRcxARWKF+c8iSOeer0scK/bqS01+rkoNUe7Ssq+ejY/NCwhPSjS2P8f9XWUx1Xow6UJrS+G/LpDE13z91Z2/34CnliwrsGrw2KOHMgUgDzxUTHnXEIeoFNPUeXJBd2BBdcqh3TlmntGkHNLb5tsTvrWCAI4jyNvSsN0rSlgWVx+QBbWiB+sqY6RbLlKXpTBAjXPshy5qf0hvejPYkdoIeNGXu/iNliwEYApOesInrfIiqg7+pHzHSmg7ZjM3ioFrj9f4PQhAy+MSXBrlCmC3aaQxvfU3CXi2x+rh/H48L0waLoovvN8+6cbG0VEpFFTKZvoJxvF9CspjyMhlDl3D50ztHbbGrEQmGK3aM+QgeMoXsDpUkebQOV+hzCCLVMx57iZYIb2Smz+BvNfktiJgqHJUNeo/tICSlhhJvwPxOOcxsEvk4=
*/