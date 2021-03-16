// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_PARAM_TYPE_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_PARAM_TYPE_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <boost/iostreams/traits.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace iostreams { namespace detail {

template<typename T>
struct param_type {
    typedef typename mpl::if_<is_std_io<T>, T&, const T&>::type type;
};

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_PARAM_TYPE_HPP_INCLUDED //-----------//

/* param_type.hpp
bIJQox1Bb4waXrK4msShvyF0IodoQWY9h5pihmNlzHDcGzOHOJ60ITP6jsZfwXvHN+nR9xngw22MvphbT5owm8fdWSrrr5VxN6P84y6C+sRFPf9N3ZoMp9Ps3F0OOkylfX+/86+abPYDZiGgPUupHl9RV+Fu3+3biYWNt+6HYkmbzjdJPwb/3yHDdgff9L5mct3smio7T58dk/R2aKeRneY95rdJj+z7K7FEpV+ftIzs/dPi5/JQIFXDYWnZ4yk=
*/