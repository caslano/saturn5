/*
@file
Defines `boost::hana::experimental::type_name`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXPERIMENTAL_TYPE_NAME_HPP
#define BOOST_HANA_EXPERIMENTAL_TYPE_NAME_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/string.hpp>

#include <cstddef>
#include <utility>


namespace boost { namespace hana { namespace experimental {
    namespace detail {
        struct cstring {
            char const* ptr;
            std::size_t length;
        };

        // Note: We substract the null terminator from the string sizes below.
        template <typename T>
        constexpr cstring type_name_impl2() {

        #if defined(__clang__)
            constexpr char const* pretty_function = __PRETTY_FUNCTION__;
            constexpr std::size_t total_size = sizeof(__PRETTY_FUNCTION__) - 1;
            constexpr std::size_t prefix_size = sizeof("boost::hana::experimental::detail::cstring boost::hana::experimental::detail::type_name_impl2() [T = ") - 1;
            constexpr std::size_t suffix_size = sizeof("]") - 1;
        #else
            #error "No support for this compiler."
        #endif

            return {pretty_function + prefix_size, total_size - prefix_size - suffix_size};
        }

        template <typename T, std::size_t ...i>
        auto type_name_impl1(std::index_sequence<i...>) {
            constexpr auto name = detail::type_name_impl2<T>();
            return hana::string<*(name.ptr + i)...>{};
        }
    } // end namespace detail

    //! @ingroup group-experimental
    //! Returns a `hana::string` representing the name of the given type, at
    //! compile-time.
    //!
    //! This only works on Clang (and apparently MSVC, but Hana does not work
    //! there as of writing this). Original idea taken from
    //! https://github.com/Manu343726/ctti.
    template <typename T>
    auto type_name() {
        constexpr auto name = detail::type_name_impl2<T>();
        return detail::type_name_impl1<T>(std::make_index_sequence<name.length>{});
    }
} }} // end namespace boost::hana

#endif // !BOOST_HANA_EXPERIMENTAL_TYPE_NAME_HPP

/* type_name.hpp
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
*/