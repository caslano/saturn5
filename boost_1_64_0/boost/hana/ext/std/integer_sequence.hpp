/*!
@file
Adapts `std::integer_sequence` for use with Hana.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXT_STD_INTEGER_SEQUENCE_HPP
#define BOOST_HANA_EXT_STD_INTEGER_SEQUENCE_HPP

#include <boost/hana/bool.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/detail/fast_and.hpp>
#include <boost/hana/ext/std/integral_constant.hpp>
#include <boost/hana/fwd/at.hpp>
#include <boost/hana/fwd/core/tag_of.hpp>
#include <boost/hana/fwd/drop_front.hpp>
#include <boost/hana/fwd/equal.hpp>
#include <boost/hana/fwd/is_empty.hpp>
#include <boost/hana/fwd/unpack.hpp>

#include <cstddef>
#include <type_traits>
#include <utility>


#ifdef BOOST_HANA_DOXYGEN_INVOKED
namespace std {
    //! @ingroup group-ext-std
    //! Adaptation of `std::integer_sequence` for Hana.
    //!
    //!
    //!
    //! Modeled concepts
    //! ----------------
    //! 1. `Comparable`\n
    //! Two `std::integer_sequence`s are equal if and only if they have the
    //! same number of elements, and if corresponding elements compare equal.
    //! The types of the elements held in both `integer_sequence`s may be
    //! different, as long as they can be compared.
    //! @include example/ext/std/integer_sequence/comparable.cpp
    //!
    //! 2. `Foldable`\n
    //! Folding an `integer_sequence` is equivalent to folding a sequence of
    //! `std::integral_constant`s with the corresponding types.
    //! @include example/ext/std/integer_sequence/foldable.cpp
    //!
    //! 3. `Iterable`\n
    //! Iterating over an `integer_sequence` is equivalent to iterating over
    //! a sequence of the corresponding `std::integral_constant`s.
    //! @include example/ext/std/integer_sequence/iterable.cpp
    //!
    //! 4. `Searchable`\n
    //! Searching through an `integer_sequence` is equivalent to searching
    //! through the corresponding sequence of `std::integral_constant`s.
    //! @include example/ext/std/integer_sequence/searchable.cpp
    template <typename T, T ...v>
    struct integer_sequence { };
}
#endif


BOOST_HANA_NAMESPACE_BEGIN
    namespace ext { namespace std { struct integer_sequence_tag; }}

    template <typename T, T ...v>
    struct tag_of<std::integer_sequence<T, v...>> {
        using type = ext::std::integer_sequence_tag;
    };

    //////////////////////////////////////////////////////////////////////////
    // Comparable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct equal_impl<ext::std::integer_sequence_tag, ext::std::integer_sequence_tag> {
        template <typename X, X ...xs, typename Y, Y ...ys>
        static constexpr hana::bool_<detail::fast_and<(xs == ys)...>::value>
        apply(std::integer_sequence<X, xs...> const&, std::integer_sequence<Y, ys...> const&)
        { return {}; }

        template <typename Xs, typename Ys>
        static constexpr hana::false_ apply(Xs const&, Ys const&, ...)
        { return {}; }
    };

    //////////////////////////////////////////////////////////////////////////
    // Foldable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct unpack_impl<ext::std::integer_sequence_tag> {
        template <typename T, T ...v, typename F>
        static constexpr decltype(auto)
        apply(std::integer_sequence<T, v...> const&, F&& f) {
            return static_cast<F&&>(f)(std::integral_constant<T, v>{}...);
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Iterable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct at_impl<ext::std::integer_sequence_tag> {
        template <typename T, T ...v, typename N>
        static constexpr auto apply(std::integer_sequence<T, v...> const&, N const&) {
            constexpr std::size_t n = N::value;
            constexpr T values_[] = {v...};
            return std::integral_constant<T, values_[n]>{};
        }
    };

    template <>
    struct drop_front_impl<ext::std::integer_sequence_tag> {
        template <std::size_t n, typename T, T ...t, std::size_t ...i>
        static constexpr auto drop_front_helper(std::integer_sequence<T, t...>,
                                                std::index_sequence<i...>)
        {
            constexpr T ts[sizeof...(t)+1] = {t...}; // avoid 0-sized array
            return std::integer_sequence<T, ts[n + i]...>{};
        }

        template <typename T, T ...t, typename N>
        static constexpr auto apply(std::integer_sequence<T, t...> ts, N const&) {
            constexpr std::size_t n = N::value;
            constexpr std::size_t len = sizeof...(t);
            return drop_front_helper<n>(ts,
                    std::make_index_sequence<(n < len ? len - n : 0)>{});
        }
    };

    template <>
    struct is_empty_impl<ext::std::integer_sequence_tag> {
        template <typename T, T ...xs>
        static constexpr auto apply(std::integer_sequence<T, xs...> const&)
        { return hana::bool_c<sizeof...(xs) == 0>; }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXT_STD_INTEGER_SEQUENCE_HPP

/* integer_sequence.hpp
dL9diPR7d40E71hFPa1R7Cfx3eFa+bzzb8g/nqtI1NfbqvbV7W3/FjSfAG9HQL9UePtHwG4B7MkEu0Ng71awmvhdylamQ/y+OhjvuMcKeW8EpUyWJd11CxzsNHU1q/6M3q74fef3BF4jh9TnDY/4+0LHCl4uNyqxzjhecDZZDJ1oBgGXP5H6JmdTbfn5gfOKKirL52JOVv2f477BBdw/tO33/9QVcga0Ml0q5uL3pSwGDn6FSqGy83cJYLiYVw4Y0vkjQyt6YEob73x3r9KD1ErAn3L3EPu4in4dZTpmG9evkDsLIq7RmK5cIflkiqnSaCXv1vrV/riUoHMwHeV8oNXVa4TOViGpVczftRHN1tRwb+dQN/4V2387PdyWHlKu5wyhY7wSlQh/puABox1dV34ZJJ+F2M/NPsuVl5Sk+N3Z50R4XONRyEoqqtxfEK2n6yOaYbgyfd36Y/loEY/PeUJrzooVS8Vs3sVh4m0hccj5c5uY515iEX/P+T7fJaLDOlYNv9axfOdOYr4n30e4IEET99u2AC9nvfH5ybsuLlTlYdd68mf7kArohRbhUVRHp08DLnCcrdvTS35O0jbg5TJIN+2ID72+bMtos813cRUaZTrx9/bZvmAYdg4Md0tnIny/11f/XPCAX14R0Hzd6fdDb4wY6eF+3M/QScxVGEr44bjcSbabw+8CXvdctDGO5WT4bOklAdlBbMDZdgl8Mi7wQP4WbbMKU6kf6fh3oI5CrjDj7oa4mHU6jwmfk65yno7kxKurPKkW/4qcu/TOnsl5r+TZswzpfazSdo5nAYfglg+T9EW4vJRBlC5x39ZE1B81gSD7/jndAsmS+D0QBRAS//Yn6ojvSR8AXvkoMZmL7t4BruME6Mt50Km12SIGlvA//xa0RdQ7AcOIn/YUtx4e8O7buBRtqyqRYDQ7oy5mo3KPjnAY7vIMxb1DPr5OeC/ZuMDjUdaEgpysPgUwejceHITrnz8Qmy9PX8HvIViSeLz5UCGRm/YMlBtHAr+KZqhVhr/xWYyTtwu4Ptx1JTrb9eM5Xl/9nJjnxfoZ19Uv8MrKwWPULW3Gygqax8srz+crXxEvC5Sza16pyhUq9vDjeLGO3pETHB5ZVddl5jweAGd4SvBXSX1mI4jO2QEu+WOx6Dzrgjet4Lhzkm6p3y/lKVPbr4nansrhO5wMtS0O5JqJFWXvNl4Rykeri+27+7GRt4j9Fr175t9L83bg8b4n3hycnRnvQCLYAdenp9LbeOiMMkVz+bFZzhVjGuDN0djoW6806+aEnkjkm71b1ny+D8no3wy0pomXXaPmGXTHO+bBPq1pfwgRv4TeOH0x6w3/3J9Sl8yrD6+gu+Mk+Mnfei3wWECU1LTqsAXV+TEpO6s2fSjGdd2K0JlBGCnR1czEl47FQju4a2hwJ5ZuuXWh4r318ynU6dM1E/76AD5Nd2R8JtQnuSihPI2gLvXps0Fa4y3wWnJDtTpbnO3x+art5uCR7KvbcES6zCyCTZPQm5M8J79QlV7dj0Z36VTto7nv+ewj08ndz/T2VFVauQeaeHlTNVpZuJXcfwM0T4fcN4O+oaY107wMmIxJbQ7K/rfM+mUKsV7CutfVPWyWO4J/W+mP3CYN5rnwHacrJaqGeevl9qKc1V3fW0E5sHReIML/IIbX+bGxu7B/FGsv6Z+YD3Kx75+B/n3Cx+Vij/wCMBWLWjXPwW4R2FkE+43ATlew2sZAP76THIPtwTG4TdkfkxOJvME7I/lI9W3bOWRmtc1Bg60zuLW71chMPNf6ryuMfQowVLC5NUPh42V3dPW40rbs31Z4ufxoleuetzJe1rcX7qHx3YzFd8b6bBs=
*/