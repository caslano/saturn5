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
VcOvhVy3le0t992+1TlFTx4fE1mxhvXmLWGneXPeY9uJbFbA8y3W7eaJrpQ0R2LzUfJrI+HmycjBm76V2i4KPO0iX/zWWSPxeYzjpnW+ievfKP4/D/wB+a1WkUnbFtxWi9s/ArnmmSraf+TQm/c7DJfK/TCM9LUyenVeE5l3Xpf7VEM203DpUkY55gz1IAlztVXB0/hiwjYTeSyuNuaeOl7shfZzVlvLk7bpFVOOjUtbc/iy
*/