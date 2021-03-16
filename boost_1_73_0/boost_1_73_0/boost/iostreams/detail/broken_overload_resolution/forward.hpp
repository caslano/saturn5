// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_BROKEN_OVERLOAD_RESOLUTION_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_BROKEN_OVERLOAD_RESOLUTION_HPP_INCLUDED

#include <boost/config.hpp>                     // BOOST_STATIC_CONSANT.
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace iostreams { namespace detail {

template<typename Device, typename U>
struct forward_impl {
    BOOST_STATIC_CONSTANT(bool, value =
        ( !is_same< U, Device >::value &&
          !is_same< U, reference_wrapper<Device> >::value ));
};

template<typename Device, typename U>
struct forward
    : mpl::bool_<forward_impl<Device, U>::value>
    { };

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_BROKEN_OVERLOAD_RESOLUTION_HPP_INCLUDED

/* forward.hpp
nZoU27eRSbnb+TQgDQejkrInMhp4CnBMUm7tOj0pjoXPSIoPnjOT4j8PCl+GegC038wjwAogvYjxwBeAk4H5eLZpQLoXHEpZZlCU3RZmioG1STmZNhM4B3g+cBEQ6lTmLuBsIPmCugD4KhDzi8zbwDnAvwDnAmkBdx6wBZgB/gs4H/g98KKkWLdfTM+Lur8E2AHYAKRz543AfYBLgMcDL02KA2MoQZla4DLgLODlSZkLXpEUXz7LgeTLEmpOZi0=
*/