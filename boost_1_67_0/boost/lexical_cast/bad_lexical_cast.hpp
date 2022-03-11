// Copyright Kevlin Henney, 2000-2005.
// Copyright Alexander Nasonov, 2006-2010.
// Copyright Antony Polukhin, 2011-2020.
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

#include <typeinfo>
#include <exception>
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

#if defined(__BORLANDC__) && BOOST_WORKAROUND( __BORLANDC__, < 0x560 )
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

        virtual const char *what() const BOOST_NOEXCEPT_OR_NOTHROW {
            return "bad lexical cast: "
                   "source type value could not be interpreted as target";
        }

        virtual ~bad_lexical_cast() BOOST_NOEXCEPT_OR_NOTHROW
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