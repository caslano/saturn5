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
#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

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
    virtual bool do_always_noconv() const throw() {
        return true;
    }
public:
    explicit codecvt_null(std::size_t no_locale_manage = 0) :
        std::codecvt<char, char, std::mbstate_t>(no_locale_manage)
    {}
    virtual ~codecvt_null(){};
};

template<>
class BOOST_WARCHIVE_DECL codecvt_null<wchar_t> :
    public std::codecvt<wchar_t, char, std::mbstate_t>
{
    virtual std::codecvt_base::result
    do_out(
        std::mbstate_t & state,
        const wchar_t * first1,
        const wchar_t * last1,
        const wchar_t * & next1,
        char * first2,
        char * last2,
        char * & next2
    ) const;
    virtual std::codecvt_base::result
    do_in(
        std::mbstate_t & state,
        const char * first1,
        const char * last1,
        const char * & next1,
        wchar_t * first2,
        wchar_t * last2,
        wchar_t * & next2
    ) const;
    virtual int do_encoding( ) const throw( ){
        return sizeof(wchar_t) / sizeof(char);
    }
    virtual int do_max_length( ) const throw( ){
        return do_encoding();
    }
public:
    explicit codecvt_null(std::size_t no_locale_manage = 0) :
        std::codecvt<wchar_t, char, std::mbstate_t>(no_locale_manage)
    {}
    //virtual ~codecvt_null(){};
};

} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#  pragma warning(pop)
#endif
#include <boost/archive/detail/abi_suffix.hpp> // pop pragmas

#endif //BOOST_ARCHIVE_CODECVT_NULL_HPP

/* codecvt_null.hpp
11OGEiV7lnz4H26Y0yUpDJKyAv1vghqKDIYUEE+zEiWLWwX3mRdyaf0a06Ay+G8Ng+KO7FLQ8tLYko2267K/VLm6bEiRwbCE9Xj1vQYTVu0FFB42wzsQY3JzEBMeYi6nj25HYl5tKIwNq09/tFpE0XqWktfS5OUClEi5aStukViKFEFblPXVIAxcZWYXuDZAtIoFZT/kNwvLUH4LwUGhDT7IiOL5PMAbVALtEbwMm9AfjgHvoXfnmmmLlSspmJnJMrKvpdApyHuI0cFplGp2O7KQP5AvS4jxaQcuHDll0pqugOxG2LMq8H9jj99kvYbVQ7jQqmvjMj9qR6QGxrZiCee8fufW4JSLO/ZoXxROEcsU5ASJjCNYJTnKCDZ1gTR+erx6+OTVjSuDFYN24MJvsEN/rqQpOlRxFp9ADbvEKLk6CAmNN74UD3cTsQ+1i1x34I5Bn4RBXN6VBRJ8xj6n3MQoT2B3IB+pCwbHZpzYkXUjONcFjOcK23HkTOccW6uK0iFX/j7X7lEWzKjusnss5KKVyws6fzGZj3Rs4LQrr0zeL2sFhFVdVV2YhZ5q8hEbmnktCrZdLzStWXYTmLMPpXuqMaAvbyoVDgbqKN1O9HdIq1QpIqI90hiAMAm6UoPS9khWefU6vPTB7LBk
*/