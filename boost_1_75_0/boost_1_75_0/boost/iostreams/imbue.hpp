// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_IMBUE_HPP_INCLUDED
#define BOOST_IOSTREAMS_IMBUE_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/config.hpp>  // DEDUCED_TYPENAME, MSVC.
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/detail/dispatch.hpp>
#include <boost/iostreams/detail/streambuf.hpp>
#include <boost/iostreams/detail/wrap_unwrap.hpp>
#include <boost/iostreams/operations_fwd.hpp>
#include <boost/mpl/if.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp>

namespace boost { namespace iostreams { 

namespace detail {

// Implementation templates for simulated tag dispatch.
template<typename T> 
struct imbue_impl;

} // End namespace detail.

template<typename T, typename Locale>
void imbue(T& t, const Locale& loc)
{ detail::imbue_impl<T>::imbue(detail::unwrap(t), loc); }

namespace detail {

//------------------Definition of imbue_impl----------------------------------//

template<typename T>
struct imbue_impl
    : mpl::if_<
          is_custom<T>,
          operations<T>,
          imbue_impl<
              BOOST_DEDUCED_TYPENAME
              dispatch<
                  T, streambuf_tag, localizable_tag, any_tag
              >::type
          >
      >::type
    { };

template<>
struct imbue_impl<any_tag> {
    template<typename T, typename Locale>
    static void imbue(T&, const Locale&) { }
};

template<>
struct imbue_impl<streambuf_tag> {
    template<typename T, typename Locale>
    static void imbue(T& t, const Locale& loc) { t.pubimbue(loc); }
};

template<>
struct imbue_impl<localizable_tag> {
    template<typename T, typename Locale>
    static void imbue(T& t, const Locale& loc) { t.imbue(loc); }
};

} // End namespace detail.

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>

#endif // #ifndef BOOST_IOSTREAMS_IMBUE_HPP_INCLUDED

/* imbue.hpp
xCL2oyxM9uupiuHdn9b7u2EqL0ucpN/P17dzAaA0RPN2OAoOk2T6/of2Pqx94vU1ozsVQv/9nljDu1oM/LzfTnUa+fbS2NQLO2acorjm7U4PxQNVH9C5BtVCoZh5eg1/aY745lI8j/x4giMolRh3xWxt1XO/AdeB8EaS5kmZpe7jLU2cSRfL/AR9rmEhq1WvwGkrwW+OVPrYTLaOS1JbN7vuTQK+Nrva1/JFk/7SWhZH/fi53a/Bj4vqKOPk/aPgjX3JxaLx47zN1P5fTU3hH8HGquy1sHl7Ma0vzl36paJE2Em/5O8N6HQq47yVZjGKgR3WlYn2DpE2+MYu5bp02pGNZqTgaFc6J8+Gc9FIjn33Yby/Xtsy0GUnbJ0Uy3uYBaXNe1Jd3y17keH3sO9DEmEbTL6H6ZlpzIngM7aDqRjZ2Ou4rULjJHDJukdV81tjWCJ8CheX5Hqo9biRnPyTLrwUw81m6gHmF30maIJ7uJq8BEqfhhz7yq2MAqQP2W5wC07dTWg8qh/JC06/6aB7dLYrlLSvxKl6tg4Et8EwMTxiSfAPV+dwDtnuXH6eAqtRPdifhH/2dx6qef6OBGhC9hechdkjrspJ9U7Df/VcbBRAeVMaomymFePaXnceV6jjLYZ+HK5oo59dtq19iuiX2SYN9pmYbn9EHhGTmLiC1GqMNqvR3+lLGEe1akbEnIFvZc7H0qJyGtxNhD7j
*/