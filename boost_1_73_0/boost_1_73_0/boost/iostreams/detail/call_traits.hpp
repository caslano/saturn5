// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_VALUE_TYPE_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_VALUE_TYPE_HPP_INCLUDED

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

template<typename T>
struct value_type {
    typedef typename mpl::if_<is_std_io<T>, T&, T>::type type;
};

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_VALUE_TYPE_HPP_INCLUDED //-----------//

/* call_traits.hpp
f5M234ClSxb3+Iai6cFK1mYUZcWLDssySgZT4RLu7cuoXJg78xoCDfYkZOZAKma/VFBZaq2YvaiY8xFsOUqvQ/BzFrkCPmpTQDGVyz6flKmQylRIJZ/JIo/6bWWieU7J2iGpwH6HriPhQC6lJc3HppTVwb06Njp4qapLGV2cinG8W4ySHRWjTNlD7/Z9LWO2YU6OTQ13Rh1WJ53ROe6MZo0qQhR9975pk9MsSprLfNk0qHA2MmkSrYfivWbcRC8=
*/