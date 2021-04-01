// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Forward declarations of templates defined in traits.hpp.

#ifndef BOOST_IOSTREAMS_IO_TRAITS_FWD_HPP_INCLUDED
#define BOOST_IOSTREAMS_IO_TRAITS_FWD_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <iosfwd> // stream types, char_traits.

namespace boost { namespace iostreams {      

template<typename T>
struct is_istream;

template<typename T>
struct is_ostream;

template<typename T>
struct is_iostream;

template<typename T>
struct is_streambuf;

template<typename T>
struct is_istringstream;

template<typename T>
struct is_ostringstream;

template<typename T>
struct is_stringstream;

template<typename T>
struct is_stringbuf;

template<typename T>
struct is_ifstream;

template<typename T>
struct is_ofstream;

template<typename T>
struct is_fstream;

template<typename T>
struct is_filebuf;

template<typename T>
struct is_std_io;

template<typename T>
struct is_std_file_device;

template<typename T>
struct is_std_string_device;

template<typename T>
struct char_type_of;

template<typename T>
struct category_of;

template<typename T>
struct int_type_of;

template<typename T>
struct mode_of;

template<typename T>
struct is_device;

template<typename T>
struct is_filter;

template<typename T>
struct is_direct;

namespace detail {

template<typename T>
struct is_boost_stream;

template<typename T>
struct is_boost_stream_buffer;

template<typename T>
struct is_filtering_stream;

template<typename T>
struct is_filtering_streambuf;

template<typename T>
struct is_linked;

template<typename T>
struct is_boost;

} // End namespace detail.

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_IO_TRAITS_FWD_HPP_INCLUDED

/* traits_fwd.hpp
Od4l28Up7iIN4Shde9m8M19HeV2BI7/c24R0Ml9/fRuKOuFPElpAd7bvU5hUrKL+v/rV6hjcyqb1c7isf3QPane1kYAZJdEyYNbck80Gruj0wA7WD/kpZx9zikrpG55FMj914Je1U4tTCbIIYOrRfSdLG129NLBCnt9POkVqyiClLdDT+NbGlPGZM2ajRYhf4xkD7R/v/tLEbpk6D5xcFyXHwMBNjBBscAqAIUGIX8aTbv389DTpQi6aS3Cpm8cLa9J6FZLMnyYx6i3ntnEFD0EM2EUOvyE1jqhgxiJ8bdC9NzZcwu7QG3iITZQdkR7On2llh/2BIGLS+FOJrH8BXQGheQsElVWGZy1E1AZzh15/E30iVkzYZQaONuYzro8LF+uOShxpPP78/g9IEI0Mhte5pJVMSFuzMJov9njAXEKE9QsNlMRmNhrFJ8D0zKBkj4eTcXk9RocoS+FXBskGoFSeTNT2M+gJ9wOeht9sreHNCvASg1B1bY++n16Hv6h2rt6BygEeHpXCbLLG11PCZoUK/7FpuW/8ZPbKR7pibtveRUK3x1x3C+B9VA==
*/