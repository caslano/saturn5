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
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
*/