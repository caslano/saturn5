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
DdHvwy0T0vueRTYKp+87u1cQuUZW7G+KelPAhckH08BqoJEMW0yL21h3BeJgfIuxJRlF0a7c9MDKCHDc9WdmbCBh2P2emQP86gRorRyZSguJ9jYHxkthBsytfQGyFK22K8uNNgS23ExMz7QESsQMkw3Saebnt1ossa4Yo09+Zaa82abHa2l5bYYLQW8zbP5XcI/CfdtDFB/yYieV7aLzcDZKvfFsNLILk2mcxqfxKLF90E/27Orwt/ByMhp6AS891692Fry51c2MM93H3mRl3yzuwT8euI6sRU7qbNmWJZV/HB4cvfjzTW87QBTlRe/EWN4fC2ZhNw7w4kNve7TRG4Ljlga5WPUwJLoP9h3d3XmwhbfDqpTdEeNSsAeRibs9pyX9q6W4S/uDx/O4o2AfDo9Gu/gG0gb+FtBWjrIi+Zcnod8fereZc3F2ADibjEId2Sfev15QMrtX4ccwGoXvolGUzr2wKNwPkuPgEP+twXSYzqZj+BiOZkNvSjUes8qmMMziD8Acgzu5qLZphNRmVDij2fjDOP40zmI7fI0DKtQ3GuxAZmkWn2eXw8t4Ou/wcMSsiZ17WAzLGcXOqShpQDUkp06LvWQ4hHCUxHgovZs+QDn0UMsog4d3Y/ut9x9QSwMECgAAAAgALWdK
*/