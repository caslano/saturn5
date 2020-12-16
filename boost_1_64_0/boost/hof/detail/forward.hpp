/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    forward.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FORWARD_H
#define BOOST_HOF_GUARD_FORWARD_H

#include <utility>

namespace boost { namespace hof {

// contexpr-friendly forwarding

template<typename T>
constexpr T&& forward(typename std::remove_reference<T>::type& t) noexcept
{ return static_cast<T&&>(t); }


template<typename T>
constexpr T&& forward(typename std::remove_reference<T>::type&& t) noexcept
{
  static_assert(!std::is_lvalue_reference<T>::value, "T must not be an lvalue reference type");
  return static_cast<T&&>(t);
}

#if (defined(__GNUC__) && !defined (__clang__) && __GNUC__ == 4 && __GNUC_MINOR__ < 7) || defined(_MSC_VER)
#define BOOST_HOF_FORWARD(...) boost::hof::forward<__VA_ARGS__>
#else
#define BOOST_HOF_FORWARD(...) static_cast<__VA_ARGS__ &&>
#endif

}} // namespace boost::hof

#endif

/* forward.hpp
sw94ff31q7QtwXLbvIpZbtFf8GkUdIMdVlXR3gYi0Oeh3R0ilwZc2laVxVAsI/yXs7nAfiPkuW6NM7S7PR3UQLy1LegSIeFi47Y4DbB17D5Fmb0ZyP9HiAHF6hhcTRu8o2i4R25wfSbt7L/cqi6JyTSgifCSCWjIQaBe9fpiCQapXO3Ttq8yMGXtq3KzZ/F9CDtAkYzAjUimy0+lOWUag7FUHAe6wd33iT/X/ptUnqV/t6PopWnVaiR9i5CTngGIV+DDw5T+iACLiwxoQe6lHuNJeL//KjGM8Sr/J+utCJ6ZLhruPz0+rfhxfcIxexwlony5dNj+CO5xevmhViXsQpf2fvwnrKCUHvWZ4grUYIj9EbOSnMD7lZ148cLXjOsjdCqqTwB9A9yBN1bSqbdI0jZqJ7HN8h7Bcqq61Cs+VdbDgj4fahLr42oINkQfp4sHO2bsXYrhMMgnI8VRkFNQwVNcAeFY3WWCR7jvUmfo6zHDlaRzNhzJX6zljfps9n9aK/c3CUOQOAPgMUy5Vesh/2Y58JcFhO03g1iBazzQqaQWxijE1yVCxJA5AUmtBVJnoYDxRwir3L2C4HexLpGsSV/i3OwvDhkNe2y9wFUwpq2A7T+jKZwofGnlHcHvXPHpZgXBJSVIF9tkkbArNNoRHM125K8imdBgUSjq0AfURHmFFqdNOsGOnMVdgLOy1tOursIRaRc6NSS4GlVNFPdvVoJ+D4aidgj/rhwcue7ZoYQzzJU6EWvM1qewSkS/+Nb7c+uvcOsHi2Vz/WLN6XOppa6s5zB8s9JzqIcP1Y7oIh8RvOV0AFZiLkNJ1IneNoCxGPFVjlbwrfkBLlLl3CK78dlc6uUTSo0zm9dJF8RR4ItbJ+f6wVGn5P9qzP1uTRevyWdFi/j8kC+b6zNTfAxCFh3PKBAGzQ9TQqAaEGdc3C/e+jIftOyC470S8dwm81pKo0XncRB+zPZ0of+Jy40LU+3hDw3Jmi2ogairMF6ZklbzQ2m3XzuBufKHZ7nCueKyK3g8YPeQSaWJKV58JdNXO/py0lcSfTnoy46vJK/2GRUXY7lzAyJfCp3KChblHUt7siOySBfp7B4dec7jPKl1cx2hUynBFE18Nd0d6RA6lQayHfk5hxrzVG7fEzrlXv1MpKe2ezaV+y3OwEiKF1aCJfJuCNPUTJUmLyeLHRgt2ZBB5SQU/NmpmNuUf4XQOL8v2RhuD6J0fXuLkrRM4UUrXepARpf8KQWgrL3OzOCab+QIX+3On+6uRHiIDPtTwytSQ03O5d0Wbg478pOD7tAeJ7w1IeqWD0InP9MHbXCMScb+PPm53tcwr70ndPKU3n3DBMcYjyP4ROhkVHdtmJA0xpMU3D6/Dc9T64f5W/wGAi/KFfa5NkB2MtiOEf9w+/CI/EOVPXMOJTVUfTpY71xVER2su8p4GHMbvTOi3YcB0TCfFkNaI3Vn2rcAOXw4ESjDc13kPjwAJ3WHA4UlYRE9bNAWgy48toaTWA0eByOrxg0OltLxGpaOOdrnN1Rm5DQkvVniN/tBPlOVHI7Ry/wP4HrsUHhvzos5+/Mbgn8sRvY44anDdWvsbB/HOpZzlcsk/Br03Iyw18UuYDU6cj916p1Cn7p1l3EjNoZOuuAx6mRW8P06Z6/8BiQY3fXhKVQ3LKfmSGVWzvs5hyFQkb4h/bINzsF9e/RNHvMqXMUgpsiT/+lqwUeqMdSzismZHzqVpKBt3hFgkL4NjIJkyKti2cLN9Lw8vh6RVxGWEHbndwjm8W0xlW+LiaFTDr3vjJpjvAFLYVBYybcS7OvK6ZY6MSS4NjpyovikVl1SD+FRHeyK2RysJmco95idIoqf1ao=
*/