#ifndef BOOST_ARCHIVE_CODECVT_NULL_HPP
#define BOOST_ARCHIVE_CODECVT_NULL_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// codecvt_null.hpp:

// (C) Copyright 2004 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <locale>
#include <cstddef> // NULL, size_t
#ifndef BOOST_NO_CWCHAR
#include <cwchar>   // for mbstate_t
#endif
#include <boost/config.hpp>
#include <boost/serialization/force_include.hpp>
#include <boost/archive/detail/auto_link_archive.hpp>
//#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std {
// For STLport on WinCE, BOOST_NO_STDC_NAMESPACE can get defined if STLport is putting symbols in its own namespace.
// In the case of codecvt, however, this does not mean that codecvt is in the global namespace (it will be in STLport's namespace)
#  if !defined(__SGI_STL_PORT) && !defined(_STLPORT_VERSION)
    using ::codecvt;
#  endif
    using ::mbstate_t;
    using ::size_t;
} // namespace
#endif

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {

template<class Ch>
class codecvt_null;

template<>
class codecvt_null<char> : public std::codecvt<char, char, std::mbstate_t>
{
    bool do_always_noconv() const throw() BOOST_OVERRIDE {
        return true;
    }
public:
    explicit codecvt_null(std::size_t no_locale_manage = 0) :
        std::codecvt<char, char, std::mbstate_t>(no_locale_manage)
    {}
    ~codecvt_null() BOOST_OVERRIDE {}
};

template<>
class BOOST_SYMBOL_VISIBLE codecvt_null<wchar_t> :
    public std::codecvt<wchar_t, char, std::mbstate_t>
{
    BOOST_SYMBOL_EXPORT std::codecvt_base::result
    do_out(
        std::mbstate_t & state,
        const wchar_t * first1,
        const wchar_t * last1,
        const wchar_t * & next1,
        char * first2,
        char * last2,
        char * & next2
    ) const BOOST_OVERRIDE;

    BOOST_SYMBOL_EXPORT std::codecvt_base::result
    do_in(
        std::mbstate_t & state,
        const char * first1,
        const char * last1,
        const char * & next1,
        wchar_t * first2,
        wchar_t * last2,
        wchar_t * & next2
    ) const BOOST_OVERRIDE;

    BOOST_SYMBOL_EXPORT int do_encoding( ) const throw( ) BOOST_OVERRIDE {
        return sizeof(wchar_t) / sizeof(char);
    }

    BOOST_SYMBOL_EXPORT bool do_always_noconv() const throw() BOOST_OVERRIDE {
        return false;
    }

    BOOST_SYMBOL_EXPORT int do_max_length( ) const throw( ) BOOST_OVERRIDE {
        return do_encoding();
    }
public:
    BOOST_SYMBOL_EXPORT explicit codecvt_null(std::size_t no_locale_manage = 0);

    BOOST_SYMBOL_EXPORT ~codecvt_null() BOOST_OVERRIDE ;
};

} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#  pragma warning(pop)
#endif
//#include <boost/archive/detail/abi_suffix.hpp> // pop pragmas

#endif //BOOST_ARCHIVE_CODECVT_NULL_HPP

/* codecvt_null.hpp
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
*/