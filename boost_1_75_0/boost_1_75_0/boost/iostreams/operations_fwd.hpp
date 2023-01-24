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
Tm6sKHmQoRizWLmoEwXPIGkDcQPyr78A3z7gbf/lEtFFTGhcf9yaAiD7BiewQ/RI9EiMRHQ1FyZGImbynScAiuiI7Fg7k43CTmkYGRJX/eGSyloxm1ytOXb1zGLEAbROZtAWAOiwebIW8b/8hYviip5llZBNPmnbLAHzFisX+kkvu6CQS3CqSg1llUI92VtYFCSKDWKOJodplHK29oukiw2YGBwfXc7nFRMKHT+FKwz3YGKQmwjtFC3ddfMy5ETxtldDm7yuyp2ucozPn7iGG92wuHtnc6YYc6Ku2qWHQdc7YnuERgUYnS73U06v9njC39IvTYw6x3t3EnUs2FRAQQCvN4sqDwmGY6UpKn5f5m3F79mbWfzgmckiJze4GaeNqaDmq/qrPQjgOcH2NPAynDfR+kJzmN6YNzE80SmtO0tl8vhFBYyy7f8i8EoPe0ARW9P6UxdXX4Fc/QBXAGOTvddfewOPr7/cXud0dw9/f3PBb4MOXJybVlrU8xkGjM/0Bp30b7rokXVoVZFVcFf58aaQ5NTHQJJGr30SCyCQUGrT1nqjEGM/nuFsmBWGrrG9HrnQIyX/cOZeH7nn5HE5oAPMGAa72a4MUl++F1J5iAoPEf6tf0D76blDVJaq6siQn6yKWXiehTK273ZzshhjrkbPsOmrcOzrgcfw5WZMox0+zK0SxWDw5tw/AW9YH7YFoKMhJ85hlvFS6h8T
*/