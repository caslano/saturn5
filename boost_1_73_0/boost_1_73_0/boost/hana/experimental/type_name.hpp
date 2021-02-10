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


BOOST_HANA_NAMESPACE_BEGIN namespace experimental {
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
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXPERIMENTAL_TYPE_NAME_HPP

/* type_name.hpp
RKaYW1HchlPc12DT44x2EoVOYW4/XkxODycfRh9Oz3/hMpb4y0JgxGme4HeMrt3hh11tuByNuQMTvek86TrfOX0h8jN5TFmoUlB6Tj8bET7NhoNDLOIRkYjlellPataIHeV6MoJ1idGCyyqSlIjFj3IewA8mv3MTzoFG1Cpi32tJDxQxTEnQzkAZgbSLA5liiG4SWRDvOIZv/rHiSNkaZWjIXINIME8FFe5m0upUSoPDw3MPE+3CI/otFjBXkJG57Rk5tVzrP3p3wGX8cOy58fSa8kPfwqqdeUtYEzAqir93TEIsJmtjncJPOf1F7PqMbFkct+hbNw6hUNJzksgJvBQEEkzYJtL5ipznYeDBtPj00pvCd2Dm1qQ3yMyPZl6Y+undzyB+HbuXXnAazMbT6ygKRDz4AB82ThIkPzB6CRkZ9yas6cl04k5umKmrLiT8h2OzQ53UW5xEKSW5R7xrSByksBwuV6l37AM3d+HXJIBvZaWoRO4lzwOLhDQjGeO370f6RoDSB8gbqyXRuqvawU4IjUV1ahsImDIc9Al49hy/weNH3DkDarSKUY7zZN+mGK0/ztQhrLKduldQ/QZ6S3OF6BqIcdL7GefVoTlTD1UCAMorsLfbBdYMzzpUqqu6gYK4aFzmJ3ey+Smg
*/