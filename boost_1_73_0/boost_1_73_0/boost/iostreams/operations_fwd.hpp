// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_OPERATIONS_FWD_HPP_INCLUDED
#define BOOST_IOSTREAMS_OPERATIONS_FWD_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>

namespace boost { namespace iostreams {

template<typename T>
struct operations;

namespace detail {

struct custom_tag { };

template<typename T>
struct is_custom
    : mpl::not_<
          is_base_and_derived< custom_tag, operations<T> >
      >
    { };

} // End namespace detail.

template<typename T>
struct operations : detail::custom_tag { };

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_OPERATIONS_FWD_HPP_INCLUDED //--------------//

/* operations_fwd.hpp
EKaETIYh1cwK7KuNbrqEczlhNF78mQ0eqyls4jSS6VlU6uacE4+giciZjQnXHQCBY6wAnoxo+/sQge2WLouG0XjxLKx2rKawidNIpmfJqGf1JAqnNV9XoVz/SOMpAgc+wvVPOdzMCxCamNQU2HmBfP2jHKRih84OwPUPGQaUQzDlZNh5Ah5PEZBBQ2cL6XAzL0BoYpJQyHSlStnau2piiXm0oMwsMHcLUM36MlmtXy8wsdVtHVv+/Z9LvSNQHsLe/J6+Ii2ApruJ4lndK5lF2GfRl12E2EmoPWHhwNPB5QGaADY90GWmfkJO5tQyXCO1swWurwVRqbtSBpMpFcYbhEKIbHrEx0OMD6s7pJDwKlOiwNlt3HBbVZ2h9j1UW5WjptIE67kr2mtRD17pZWZAWiMWQnTcgTJ5ZA4TFrkF0NB7w8RCSQufH3giGDVh19l6CzqbW496F0Z+zlEYma475XCZU8J5/0OhsusVJxM5TsxOEUPDrU6LBm/nKQGwV9YbnKefOuty1dWYkqMPynYTaxLe0h3Ngvh2rwCaw+zLZDl1l/Rqkp2E2hMWDjwdXB6gCWDTA11m6ifkZE4tyh2ZxRvpgqjUXSmDyZQKrnseGpFNj/h4iPFhdYcUEl5lShQ4u40bnkPV8B5UOXHg
*/