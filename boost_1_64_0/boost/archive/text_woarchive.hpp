#ifndef BOOST_ARCHIVE_TEXT_WOARCHIVE_HPP
#define BOOST_ARCHIVE_TEXT_WOARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// text_woarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>

#ifdef BOOST_NO_STD_WSTREAMBUF
#error "wide char i/o not supported on this platform"
#else

#include <ostream>
#include <cstddef> // size_t

#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{
    using ::size_t;
} // namespace std
#endif

#include <boost/archive/detail/auto_link_warchive.hpp>
#include <boost/archive/basic_text_oprimitive.hpp>
#include <boost/archive/basic_text_oarchive.hpp>
#include <boost/archive/detail/register_archive.hpp>
#include <boost/serialization/item_version_type.hpp>

#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {

namespace detail {
    template<class Archive> class interface_oarchive;
} // namespace detail

template<class Archive>
class BOOST_SYMBOL_VISIBLE text_woarchive_impl :
    public basic_text_oprimitive<std::wostream>,
    public basic_text_oarchive<Archive>
{
#ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
protected:
    #if BOOST_WORKAROUND(BOOST_MSVC, < 1500)
        // for some inexplicable reason insertion of "class" generates compile erro
        // on msvc 7.1
        friend detail::interface_oarchive<Archive>;
        friend basic_text_oarchive<Archive>;
        friend save_access;
    #else
        friend class detail::interface_oarchive<Archive>;
        friend class basic_text_oarchive<Archive>;
        friend class save_access;
    #endif
#endif
    template<class T>
    void save(const T & t){
        this->newtoken();
        basic_text_oprimitive<std::wostream>::save(t);
    }
    void save(const version_type & t){
        save(static_cast<unsigned int>(t));
    }
    void save(const boost::serialization::item_version_type & t){
        save(static_cast<unsigned int>(t));
    }
    BOOST_WARCHIVE_DECL void
    save(const char * t);
    #ifndef BOOST_NO_INTRINSIC_WCHAR_T
    BOOST_WARCHIVE_DECL void
    save(const wchar_t * t);
    #endif
    BOOST_WARCHIVE_DECL void
    save(const std::string &s);
    #ifndef BOOST_NO_STD_WSTRING
    BOOST_WARCHIVE_DECL void
    save(const std::wstring &ws);
    #endif
    text_woarchive_impl(std::wostream & os, unsigned int flags) :
        basic_text_oprimitive<std::wostream>(
            os,
            0 != (flags & no_codecvt)
        ),
        basic_text_oarchive<Archive>(flags)
    {}
public:
    void save_binary(const void *address, std::size_t count){
        put(static_cast<wchar_t>('\n'));
        this->end_preamble();
        #if ! defined(__MWERKS__)
        this->basic_text_oprimitive<std::wostream>::save_binary(
        #else
        this->basic_text_oprimitive::save_binary(
        #endif
            address,
            count
        );
        put(static_cast<wchar_t>('\n'));
        this->delimiter = this->none;
    }

};

// we use the following because we can't use
// typedef text_oarchive_impl<text_oarchive_impl<...> > text_oarchive;

// do not derive from this class.  If you want to extend this functionality
// via inhertance, derived from text_oarchive_impl instead.  This will
// preserve correct static polymorphism.
class BOOST_SYMBOL_VISIBLE text_woarchive :
    public text_woarchive_impl<text_woarchive>
{
public:
    text_woarchive(std::wostream & os, unsigned int flags = 0) :
        text_woarchive_impl<text_woarchive>(os, flags)
    {
        if(0 == (flags & no_header))
            init();
    }
    ~text_woarchive(){}
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::archive::text_woarchive)

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_NO_STD_WSTREAMBUF
#endif // BOOST_ARCHIVE_TEXT_WOARCHIVE_HPP

/* text_woarchive.hpp
dlSysnwC5I+QAfA37CTcAZ+Hk2sqjM5hMWjPwBJhERrHXVVHDskfJyKNs7oxx9aioGZgk454url0TAyfV5X6Q4/4Ck0lwZKbJooj1SlSoyRA+uKIt2/6cYqOwzsFwZ9qZZ8tDaNRbDr31VHl2WBkDRJ/m0f3/mA6w5kPebmCEKvnDQaozrA8uzowwEGNcGyvpj1+2r35Q9fZ2W5vW9h2ZN2juWTjapochmcNQ0XEB2lQbXOqy8fxRMs3TwjERADTZpajlW3qq1JJGo2tpnHFAElT4Ra02F31Gpt6W1/YTivMGy67lE/OvhLu6OopPGHu4oNnyo3J42MB+mmaS6xSu1ALMiAt2Fp1BHovDRlg/PG/6uucLAhI0tgotDT2meih2LJ4PpbOnEkp7WPMLjQkJdSeomrxUr4x/5FVsYyJxq2Iz4vMX1rjrkINjXLkF3mQsE3gugxBLO8TBdTg5QWFSidw0TCSnggQz5wpa7i/nVV1acRtXHy66PMKJfq0K8HVg8wEsU/+RGcFFe22dkwoG0anuSBPpbCE1yfJDBJfzuPRzHd+/Yg8pyS2OA==
*/