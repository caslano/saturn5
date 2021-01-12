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
JryiWeq5tDlaVlhuHj/BepZX4U6cS4ZQ55HS1th5ghUcRegzcHGBzwkVFpRIdVZky5XkAfqqBkFwUNYcLSmp3W8g/xCSdiPFfs5Pt1w4t3GGuz/uqxOzbAorG6qensL1u8DlLzkM8rxdP8RrFamYaOl2vF+DrtNklqCw5t2UWFPAejlft5OW8IqWeKv4E7XQdpy9lWnSMEErs257UYh59YOv5swe2RZtGgvAHQK4HSZrDTP8
*/