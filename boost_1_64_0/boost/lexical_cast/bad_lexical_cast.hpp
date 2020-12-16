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
ruL4uo78v57jaw3H11qOrxuB5zO+gPHljK9gfAvj9wNv4vhay/F1NcfXao6vtbqd7U3e+8+FLOfF7D8V7D+Xsf8sYf9ZxvJfzv5Tyf6zlP1nGfvPJew/i4F5PM/xRVkZvDSMr0NYjj7k10BgJ9qlDqZd6jD6xT6c9qnnMT6f8ZsYX0v71IcZf4T2r28B+wPf53nyh3Kl2X7Vtsclf7qSP2nkTzfypwf5k07+dCd/MsifHuRPJ+BY2tFO5HmnHXIVy5FnsEM+kXao41iOHEV/7rTrzqMdcj7tuydzf4eT2B4TgLm8btd7nfd6D2O9h/N+I1nvo1nvUaz3GNY7m/U+hvU+lvUew3ofwXqPYL3HaP2iiuX40tAvTmM5Tme/mMd+cQ7H0bkcRws4juYDL2T8IsarGL+d9rtPM/4M/XN+BDwL+AXPkz98ZzTzZyrLVUj+zCJ/ismfEvJnNvlzMvlTSv6UkT+zyZ/p5E+RxR+eXxiwKw7YFf8FdsXTYDO8EGEDwjMINQiJt4WqPgjjEeYirELYgrALIawqYGMcOAJH4AgcgSNwBI7AETgCR+AIHIFj39r/c2GwUez/b9bs/9+nX7ksB3T7wDTgFZay7hp7XfJ4ufOwwll5RbXr2hMSuRap+Y+6SdK3cExUsaZ1SNJz4Jy2rjxp9hRZN8Uy4ib4crpT0kQ7nGuTKyTeybTeDXoNs/Nges2+VFwcSfnjcf0aud7KMQ1nDGvden6uXc/McdoZbkTZm9nrq4WyPhuLX9dKnkTHZBUHvV13uVcszoSsts6PRN5BdX5qUB5w1PYTdbPkjXQMVjORBucQGyH5mqOt0QYJUga5/xbcP4btolT5zBI3H2CfCa1c1Ua1dKelrwvPkbZg2dvL9c7GMvfD2nBzpJmFcncFgzohzAOTFibWxtMQrsHvdbheCRyLQqzX/IYdpXiQtzyGRIvut5/49YoTXu8XfaPcV8GFWN06M+pprzPHu9jFsE/5YRtDW1z2gWhpQ0nLdoWPH+Er+Gyds9evVwc13jq1eV9t7+vX5vVT7+va5nV27+vd/WS9O/Kerz/cft5TC1+b/nLaKzec/WHjrXeb94n//62Dm/enb9x18GrnnMW5fQcwAeFRzT/JAcB4riskUG/fiutMrbmvahIwn35JZtAvSTEwmetP7bjecAjX6zoAb+D60c3AA4EPcB3pCa4DPc11pJ1cR3qb60af069LM5T3YGBHYC8gnklCPzvYv3UB7jXlsT5QA4w62n2dwLSXlNd9pLh3lH/rBtwnym0vKPM+UPp6QhXXFLQ9n9z2ejKvL8x1W2Mw7OtkXG/gHk7cv8nb2oP7Pk2+1yFKEEz7MW0A7kHcvC7h395L2n5L9nrFRuv3mD+3t5L3fZXc9lP6E+sZDdk3SV/jSEFw7pF0CYJpb6SxCNvw+30E97UPdSLKDEwF6nse6fsdzQ+sbwSOwBE4AsdeHftE/i8rpPd/tdfy/y2a/J9FY97pDnlXU8cC5+MlreoqW/4fjTtT+jfL/7HA5yT9IMcpqoVJ/ic9B85p3z/BFFmX/18jDaf8/6TE4w3yP+mZv5GyZfqXJE1/RzHOGG3drzLrBFAekQc/k+vd7fK8LfEkytBKXXS12Kab9AWkbdYXbHDXF1CH8o7k6eqYCJpnqF7UrTjUYXKf0QjDNHplRZD0hV4V6HnTI+wUmj0cI9Sptuy/QOiFNFiP0PFqTz0CaXnqEVinCXK9s7Euh0KPEOlTjyC2/qJLuFXTJdym6RLGNECX8MvV/ukS5LsAZ//043syd13CBlddgpyrss9Ju/0v9QszRb9Q0eXsXosiH716ZETVcWeeNezogH7h36hf+Ng5x/E=
*/