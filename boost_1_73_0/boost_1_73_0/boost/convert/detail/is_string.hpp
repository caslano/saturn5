// Copyright (c) 2009-2016 Vladimir Batov.
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. See http://www.boost.org/LICENSE_1_0.txt.

#ifndef BOOST_CONVERT_DETAIL_IS_STRING_HPP
#define BOOST_CONVERT_DETAIL_IS_STRING_HPP

#include <boost/convert/detail/range.hpp>

namespace boost { namespace cnv
{
    namespace detail
    {
        template<typename T, bool is_range_class> struct is_string : std::false_type {};

        template<typename T> struct is_string<T*, false>
        {
            static bool const value = cnv::is_char<T>::value;
        };
        template <typename T, std::size_t N> struct is_string<T [N], false>
        {
            static bool const value = cnv::is_char<T>::value;
        };
        template<typename T> struct is_string<T, /*is_range_class=*/true>
        {
            static bool const value = cnv::is_char<typename T::value_type>::value;
        };
    }
    template<typename T> struct is_string : detail::is_string<
        typename boost::remove_const<T>::type,
        boost::is_class<T>::value && boost::cnv::is_range<T>::value> {};
}}

#endif // BOOST_CONVERT_DETAIL_IS_STRING_HPP

/* is_string.hpp
nxPOMeroN/GVmuteILzqkZ4D7AWoufKx3Iof1Fz3Y75x5a/HVmx5NEjUfc2X96Hrbcinxp+PIX+Cf/h8jBd8yg8S86DWEs4VHMNPPlr9seRmSjynUC32Qaxyjr6OpR/qy+OI1ggrWkUYxU4gukpYtYpR/lOJUAlOJ8InZgYRJlFnEqG+m0WE+mQO0SuKqoneVlQTxDp+AREqsVqig/X1HCIcw1IiraFZU5TIaQErPkXYwheI6gNWdYq0luMUaIk=
*/