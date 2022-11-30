// Copyright Kevlin Henney, 2000-2005.
// Copyright Alexander Nasonov, 2006-2010.
// Copyright Antony Polukhin, 2011-2022.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// what:  lexical_cast custom keyword cast
// who:   contributed by Kevlin Henney,
//        enhanced with contributions from Terje Slettebo,
//        with additional fixes and suggestions from Gennaro Prota,
//        Beman Dawes, Dave Abrahams, Daryle Walker, Peter Dimov,
//        Alexander Nasonov, Antony Polukhin, Justin Viiret, Michael Hofmann,
//        Cheng Yang, Matthew Bradbury, David W. Birdsall, Pavel Korzh and other Boosters
// when:  November 2000, March 2003, June 2005, June 2006, March 2011 - 2014

#ifndef BOOST_LEXICAL_CAST_BAD_LEXICAL_CAST_HPP
#define BOOST_LEXICAL_CAST_BAD_LEXICAL_CAST_HPP

#include <boost/config.hpp>
#ifdef BOOST_HAS_PRAGMA_ONCE
#   pragma once
#endif

#include <exception>
#include <typeinfo>
#include <boost/throw_exception.hpp>

namespace boost
{
    // exception used to indicate runtime lexical_cast failure
    class BOOST_SYMBOL_VISIBLE bad_lexical_cast :
    // workaround MSVC bug with std::bad_cast when _HAS_EXCEPTIONS == 0
#if defined(BOOST_MSVC) && defined(_HAS_EXCEPTIONS) && !_HAS_EXCEPTIONS
        public std::exception
#else
        public std::bad_cast
#endif

#if defined(BOOST_BORLANDC) && BOOST_WORKAROUND( BOOST_BORLANDC, < 0x560 )
        // under bcc32 5.5.1 bad_cast doesn't derive from exception
        , public std::exception
#endif

    {
    public:
        bad_lexical_cast() BOOST_NOEXCEPT
#ifndef BOOST_NO_TYPEID
           : source(&typeid(void)), target(&typeid(void))
#endif
        {}

        const char *what() const BOOST_NOEXCEPT_OR_NOTHROW BOOST_OVERRIDE {
            return "bad lexical cast: "
                   "source type value could not be interpreted as target";
        }

        ~bad_lexical_cast() BOOST_NOEXCEPT_OR_NOTHROW BOOST_OVERRIDE
        {}

#ifndef BOOST_NO_TYPEID
    private:
#ifdef BOOST_NO_STD_TYPEINFO
        typedef ::type_info type_info_t;
#else
        typedef ::std::type_info type_info_t;
#endif
    public:
        bad_lexical_cast(
                const type_info_t &source_type_arg,
                const type_info_t &target_type_arg) BOOST_NOEXCEPT
            : source(&source_type_arg), target(&target_type_arg)
        {}

        const type_info_t &source_type() const BOOST_NOEXCEPT {
            return *source;
        }

        const type_info_t &target_type() const BOOST_NOEXCEPT {
            return *target;
        }

    private:
        const type_info_t *source;
        const type_info_t *target;
#endif
    };

    namespace conversion { namespace detail {
#ifdef BOOST_NO_TYPEID
        template <class S, class T>
        inline void throw_bad_cast() {
            boost::throw_exception(bad_lexical_cast());
        }
#else
        template <class S, class T>
        inline void throw_bad_cast() {
            boost::throw_exception(bad_lexical_cast(typeid(S), typeid(T)));
        }
#endif
    }} // namespace conversion::detail

} // namespace boost

#endif // BOOST_LEXICAL_CAST_BAD_LEXICAL_CAST_HPP

/* bad_lexical_cast.hpp
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
*/