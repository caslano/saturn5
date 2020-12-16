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
9Zm5QKL5rWgtdWxPfJzrJMXrqVsgrcn6OdnaWj+3vibvManT9b2eziPNZ+6WxgyR1yo6UudrLdY3TznSmKC+aUze9xt16gdlfa8FLJHfMs+vockF4qwcJg3E20dhP3VZ5zUtLmleVvshDsr0sp9nfcaXV1mfaO7R7QY+P1+utCCMAHN899NiMu9xdZvyXa70KxNWESwyp487+Xk+8aFBHS2+LCkuSFRvcvq6pDvNRnUs+T4opZybaKr295GPM9o0V9twdxOR3Fl80KCfg1scot2oBF3PW9Tx3O/QJjSReuN+riV1Pvp6fbanlTaPvI96Xnd0ho/W86J15HfpGAwJGNnO2kj1Vr2fId8ZiwWVRRdZLLbi46xelc/Ke3/KTRrbk/R0vLwOnKenT3v6FNDHHqH3MnKx6nh8w1CYXinjWhetPslSL+yvG3WhfHloO5GbLsueXaWFvv3XatOeW3r4ex3L2yRAqVj9eI7nrkzXk3BLW3M7Y8xIUzv3TceMMre1jGno+Ahfb5UsnH+D5y2UOh3TluEzSZk3+lz8ep923UfguI+8kan+JnmnmDqmnLN4gh1qfc/HZ8C8xveuN8YvE46BgIqMvfTkfatteO9Hlb5uA7HUsRa57u/LHVT3jacf+lxHPHPRxScGJUg4AsQBaAaveVDt5wsjy7hWX3jy2c3XauCJkTevY7lvB0HEimTs66/0L/CJLQO8+oMykn4OUee+IfY85NU/ydTfqfb3iU2Z1GWCTQ2FzDS+na2V1RVlZcErmD9vQnzI9GufeJXLPHxrWnJEGHCBL+RKALPQ3YP8lgY8uHFboEFvl3eTMUEYXeaPyO2MGZGZ93yeWWSZF3n1Z3QJC0s0f3CDtejrGGltJ2qlcR5Vz+4/jjNebec1jjjPidStKAf39sM/l+k83bwA9YWjB2v6+l6dSbJMIuxJKTrJMb3bR7Y3bIeQjfEm/5u0K4GPs6jiKXifHKXQlJa0alWUmqQHBc80TWtsm9YkFdDiutndJNsmu8t+uz1QvBBUPBDFW1QUUUBFRVQ88T5RURG8ES9UPLDiff3nm/fN/OfYZLf+ftLW99689+bNmzdv3sw325ofjG3H/AKyYUhr6V7q2cinW5SNHfLKtOs48MvmycvFhkthw95ObFhbm6tNxO4j3x6NM69U+duGobQM5n2XB7sRjuqjr6I2fs71askHUy3Umsw1d+CoEImWNsa+zm/Xq+6DVuvM+/Qjub1b532jjEmmF7e7RMaBccrGbxUbPxw27hPffZvAHqxgndt9b3+wJt4Vtfvl2ob9ZHjKRRjn7g/fye28O5JXpbgtGzcxV7Rlvoznb17f7bXl8+/38tj067NVc0bg45A57aV+fkDWisHhHU8cGuVvVn0c2smBJMe9axya8FveazN8uTZdqsu3njSnj13I7aVqKy+tsJzuhb4cXWXI8B8K9YB5W/YFy1LWGSvjI2SrPcVJZS1nbD8mPmzGl+z4ScHRGJnxud74d9juM4LjdsrPPw/467DmHgOa/k5qlvDzRP3/aL57/6NjNcsvBj4iLEjPL4v90IcMac9OgKvtKSSZZMWB1+obDP+9/RkJBqC8FxeQeIy/BbqxdDXTZf8x7z7Cd8MxLqRuRf50c0gTH+uFnixvPb8l0AVuLTHoJ8DdgLF5LOhWC+zngN3/Xl1dTyPYH4XuiQQ7KLDnEeyvAjtAsL8LbCnB/imwYwj2b8AGIfdRBPuv0BUI9sDFGnYhwY4E7D6IpW8n2NGLdXx9AsGOkbYHCbZYYP9VsI7i8PosKfR8c2XMNzFO8foFRsvQdC+O02DETI5xvKFR0lV1HiX6RqOefQRp3qNYrNewfCOgsfc=
*/