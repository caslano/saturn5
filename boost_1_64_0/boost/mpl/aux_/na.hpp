
#ifndef BOOST_MPL_AUX_NA_HPP_INCLUDED
#define BOOST_MPL_AUX_NA_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/na_fwd.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl {

template< typename T >
struct is_na
    : false_
{
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    using false_::value;
#endif
};

template<>
struct is_na<na>
    : true_
{
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    using true_::value;
#endif
};

template< typename T >
struct is_not_na
    : true_
{
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    using true_::value;
#endif
};

template<>
struct is_not_na<na>
    : false_
{
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    using false_::value;
#endif
};

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
template< typename T, typename U > struct if_na
{
    typedef T type;
};

template< typename U > struct if_na<na,U>
{
    typedef U type;
};
#else
template< typename T > struct if_na_impl
{
    template< typename U > struct apply
    {
        typedef T type;
    };
};

template<> struct if_na_impl<na>
{
    template< typename U > struct apply
    {
        typedef U type;
    };
};

template< typename T, typename U > struct if_na
    : if_na_impl<T>::template apply<U>
{
};
#endif

}}

#endif // BOOST_MPL_AUX_NA_HPP_INCLUDED

/* na.hpp
27ePYLPZxNjYGDExMUFcuHCB4HA4xNTUFHH+/HkiMDCQ+MUvfkEcPnyYwLWqxOrVq4mBgQFi9uzZRGxsLHHp0iXi4cOHhL6+PlFeXk64uroSO3fuJE6ePElkZmYS3759I9bjCn9cp0rU1dUR/v7+xNevX4mPHz8SP/30EyEpKUnY2NgQnp6ehJGREbFq1SrC0dGRsLOzI0ZGRohf/vKXhIuLC2FoaEh0dHQQSUlJRH19PdHS0kIIhULi2rVrhKKiItHf309UVFQQnz9/JhISEoibN28SW7duJY4fP74OAjBB+KsR/KsI/SsEPgBhf4+g/wohZyLgUQi3O4JdglAPIdA+CLMmgnwAId6BAFcivJsRXAZC64zAPkNYlyGoUgjpKQTUHuHsRDCDEconCOQShNEXQVyDEO5BAI8ifJMI3lmEbgMCZ4ywfULQtiNkvQhYK8JljWBtRKiiEagyhKkdQZqFECkgQA4Iz3MERw6hsURgjiEsfgjKbxCSHwhIG8LRhGBsQij0EIi3CMNyBCESITiDAJzA8Bdh8H+OoV+IgdfCsL/AoK/AkMsSmG8cxRjseAz1bgz0GwwzBYPcgyHOwACnYXjvYnD3Y2jjMLBfMKwFGNRGDOkCDOhjDOctDOYNDGUqBjIGw0jHIIZhCN9hAEsxfIUYvMsYOjYGbgLDxsGgnceQ/QIDJobhGsBgxWKoHmKgyjFMOzFImRii9RigOgzPVwzOTxgaGwyMEYbFEYMygiFxwYB0YDjqMRhCDIUiBqICw5CAQdiKIdgG+X+A+FmQ/msIPx2y50L00pC8AIIfhtxzIHZVSF0HQpeBzOdB5OGQeAMEfhHyzoK4ByHtexC2OWQdAlE3Q9JqEHQf5HwbYvaAlJ0g5BmQ8SOIeBEk7A0BUyHflRDvHUjXFMKVh2y1IdoqSPYIBPszyPU6xLoFUhWFUGshUwuIVBkS7YJAF0OeoRCnOqSpAWHSIEsliFIFktSFIN0gx3MQYw2kmA0hSkCGpyHC75DgfAjwPuSXDPHtgvTyILwgyC4XopuG5B5AcL+G3OZAbOOQWjeEJgKZPYXI+JDYQQhsKeQ1E+KaC2lZQVgRkNUoRJUCSb2EoPIhJwOIyRZS4kFIhyAjL4joCiRkBgElQj57IZ61kM4+CGcMsrkA0UxBMoEQzGHIZTXEMhtSuQSh6EMmrhDJSUjkGwQiDnn4QxwfIQ1JCMMTslgFUdhBEr+EIAwhhySIoQVSuAYh9EMGnyGCm5DAcQgAOifXFFYQuSqhWnJNQ5vkSoNKyFWLdU/qDeuVXD9Yr2RtgOrIFYjVStYG6J5cWVAtqTusAHKNQTXkCsOaI9c0lEjqCquXVCVWO7nyoT9yLWLtk6pHHSBXFvRIahtaJlc2ViG5arHCyZUHjZLrCZoltQ31kisQdYZcK9A1qUCol1Qr1gW58rGKyRqBakOufawucq1jFZOVAWuTXKGoDKRqUTXI1YE1Rq4nrCFS/1iVZE2Cosn1iipF6hsrj1w9WNvkSsV6JNcOVjJZeaBusmqgZpD1AZWIVD5WO6l5rFly9aLekBUNdYesQ6hm5NrHKiJXCtYWWauwTskqBtWT1QwrmVzRqB1k9UGtI1cZVje58rFyyJWPKkeuI6wNckVipZOrDpWBXHtYO2QFwkoh1z/WLFnxUInIuoCDXNmoXmQdRE0kaw/WD7kasdbJWoIqRdYjrClytaLakPUPK5CsRFjlZC1AdSTrGGoDWQNRI8nVipVOVh5UALIGYgWS6x6VjKxhqDzk+sZ6JSsYqgdZ41CryBqAikDWHNQDsnZgbZJVCvWUrK2oJmTVRCUgqyrqBVlHUT3IKof6SVZE1CeybqE=
*/