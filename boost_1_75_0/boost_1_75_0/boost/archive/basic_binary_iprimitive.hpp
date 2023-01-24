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
B1urPyjwDpCjOuB2gPl2gPE2LNh3RrnN5G23y2ivw3i0/1iD+/Ac/v4apKHasQCG8HeE+dV58J1GqnPfO416nf6QZrmXmp9/7TcZvvqZL3kCOXTKKu0JtpmtLL5toEFJOYWRHaKfwMfCHZ9AG+xwOX5MIo5GAZ86N7wWEoZvf/uCr7q3lL/+ST2eGsYN8XEMiwbutplnJOFDmxrHBtlYcF/cPHl9f3TYzdK2Uiue2MuTU22t1TyT2jkKPwAEXVFqbwvVVrUrLDAaZLOyQeZSGdB88GI9Pm3VPnVoKKU4A4A/PkU3vA5/DEoZvzDBoC3SnnIcyao2MJL8cziS+VCzpFciH52CrxsC+GQPbKA3o2Qz2C78RSwMjl8Du+0s2WQzey/bwubxtlClJFn1jHklvpt0oCwv0MEiHKWH+UtQ2946zlIjbdyRQsfqHEfwVb3rD/jq/50UioARqNhDos/ys5ArqgeqCqWN5ZBmdd/VY1wr8fjh+kGjbMZv5j7A+EiQDZgjbSsPPM8RL2ymu+Dnxln+5xRtvIDwZUhnn8oDFfmpnpq6CeePWfFUz4bWMORkhkNe0wUFvIYE/DlMJ9eQFKwgOHOsgUkZrJSX1VEoh2Qm7SmdZmVjTUI7ymDzm20BxZaG4ozGCkuTId3bmY38rl6bhOjDxRkNFZZGwxhABeKQY/Kk1NkCp0/zJDdMS1Pf3UUzwazs6W1oPvSD
*/