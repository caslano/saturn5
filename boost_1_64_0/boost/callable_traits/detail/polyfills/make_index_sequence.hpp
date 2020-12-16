/*
Copyright Barrett Adair 2016-2017

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/

#ifndef BOOST_CLBL_TRTS_DETAIL_POLYFILLS_MAKE_INDEX_SEQUENCE_HPP
#define BOOST_CLBL_TRTS_DETAIL_POLYFILLS_MAKE_INDEX_SEQUENCE_HPP

#undef BOOST_CLBL_TRTS_IX_SEQ
#define BOOST_CLBL_TRTS_IX_SEQ(...) \
    ::boost::callable_traits::detail::index_sequence<__VA_ARGS__>

#undef BOOST_CLBL_TRTS_MAKE_IX_SEQ
#define BOOST_CLBL_TRTS_MAKE_IX_SEQ(...) \
    ::boost::callable_traits::detail::make_index_sequence<__VA_ARGS__>

namespace boost { namespace callable_traits { namespace detail { 

template<std::size_t...>
struct index_sequence { using type = index_sequence; };

template<typename, typename>
struct concat;

template<std::size_t... I1, std::size_t... I2>
struct concat<index_sequence<I1...>, index_sequence<I2...>>
    : index_sequence<I1..., (sizeof...(I1)+I2)...> {};

template<std::size_t N>
    struct make_index_sequence_t;

template<std::size_t N>
struct make_index_sequence_t : concat< 
    typename make_index_sequence_t<N/2>::type,
    typename make_index_sequence_t<N - N/2>::type >::type {};

template<>
struct make_index_sequence_t<0> : index_sequence<> {};

template<>
struct make_index_sequence_t<1> : index_sequence<0> {};

template<std::size_t... I>
using make_index_sequence = typename make_index_sequence_t<I...>::type;

}}} // namespace boost::callable_traits::detail

#endif // #ifndef BOOST_CLBL_TRTS_DETAIL_POLYFILLS_MAKE_INDEX_SEQUENCE_HPP

/* make_index_sequence.hpp
8513gLrb4fX11bN+h+tMz0Bvd2ujd4OE3caiDZewtzvCzjXPvk9I2A3MPZWIbl1PmUxtTpQ6KmFl4PNScX/dEdY5Jr0+E7cLrATNM0viFeNLoq9Z60n2PEicRdeEG8c9oGvuId230EpBu8Bzurcd72yXyHX95f0vEvY5YaHW+9drUvYs01xkTieR8G71pjCT5H0LD55e7MXzqbXI29B5BmIeYZh7v1HSosRX4d6N/jmiH6vvWzXkGrV88daj7Gsapfbl99LDysVlgpd7kPfc2mI/wVfe3iyWw3Xsd6ehcv3jDned76nt6Vhx/8Dhfo7xH4NUU9Igy2ouMmmg5aKrdan1PTsZjfb2Zt++DPaibC7pmoSfMyTM8LDye1ws92jn6UJx3+MLzrdy/emin6B15E+i38XXz3qQPdT6WpG+cHUrT5cE62pcn/Ks9F4h8ehh0caJv2U+x/lZAedhXit+k3grDVM7DY/S4i8zDn+p4k/rTqrolDBS1Nahs9joZKLTQnSu5S20FmmHnSk/A3312VHoVdrB4aTbW15WPPiaajhmLYhpH3qKnzDndQqc62v2N9XzWcvznwwuf059Qtx7WiPoH6LNc2qgeVv3mpisfQSGd9VyMwwzKKi/WHKS/mJIYmB/sTWov9gW1F/sDHpG2R36GYU+XcdhMMm6l/Qc/zNKM5f+IfS7jeq3RNZ2VeQ813eVkUY/1dTtwyJPc31XeVfcMkXONH47hnxX+b24n675buunhHw/OS7uGSHfT94X96mu7yd/rMKeIvFJgfmYEfR+MszlXSQzqK+fcoK+/rt493eR7KQKecmh3q75iG7gu8hFSSHfRdANfBfZnBTyXQTdwHeRK5NCv4tcmhTwLoLfk7+LZCdV7l1kS9KJ30V2JJ34XWRPUuh3kQ+r+C6SkPzvexf5NNGSX4oPAyOh/12kJNmtbLjV8wES/pui/ydvjJQX2/8MRnzC3cqIug83ZeQtkQ95A8vIALnXl8Xtz94YLQevinzEO9ATp+sP7fD6B7UTAyQtnhG3L712Xj0n8kVajmy/p2nf47F+1xyZHS+7Wes9FduSAZLe74mft7z2O81ekb/2JniWepzlj7BN+auHnT+8ucQvUseEY6yBpJfOMW3h110gdqQROoQrdrXEbrTu5blT7CLFLlP3dd4mdkutWAmvLMBUsWvgibCOqS5fAox9G4kT9+To95akWo7nloGi94G+F7JzlKTLHM947ILfm2L5q4Hox5kx5CGivzpgvDlG3Z4Rt+s8c9iZWfQJX+NlnnGeF53PPOXPrAtN+3OKuG107Jm1jMWC5fW1k7g/acWIbMd9syeNnRfL73ep3K89Dv+z6HTR50HbT7GnLnaLrSfsZx61f9bjSLculqMt6Cf3MdpyXEfcY3T8/0fxn8W9r1a78mvVwl6f/811/GfQ/kQbnpTI2B0J7VvzCMfONub82YSEiDBfMn9E1qtdv3btOnERPuwRI+0x8T/HGuN8/pH7Jv9pWwLsu9j29DlyBlxzwqnB30fNe275GPu7jj6u9CTfi7bY34to3y5oGdi+HQtq374Lat9QDmjfIj2BfR/1ytm+iZ2fc0WHeqZtXl9t8w5ph/yh9ocvYrqiu7pVhTZv4fyCc/KzFizmcGvXfhE/QWN0Ij/q1uahGzRGJ/Kdrn3d/eJ2tciZxm96qDP/1b2j6Ud3iPxg6LE3cb8m9NibuF8YeuxN3Fe59nefVLG/S239S/u7svyf5dK/DbDnA7Sy5LfUR5jKOf7via1D57V8WgyR3/iTNipB83u/yEMYKwtjd75wVoTPN/sAzmor3+Mc41WmTGSZZ14TZisrVp87nxZ5jqclfl+118Q=
*/