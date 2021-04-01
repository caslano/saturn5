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
qEOzjbszVUXB/jwr8hqOlgd43twpoLqAU6+GsPYDnUtG6SUv1uROgDJce69B7Ms5DKEmh6Wiz0hvjY5njFnrKOn8aBVN5hfZ9AC00kot/uKMe4DMud6Z2hwI/0m1e5e6Unyidy2VUfYuRYE6td1yxXY90QAoruzVG8F1WHiaaNA99DWdJm6a3fbAH/aannebcLtdjA7KGtE/+GHgJPVawxpcrSNCk/36QNQHPl+TGKysjbZyTtSsJ4YhqZxxFHhU09ypzcjOnF09E6BL7Y5qxg1KmWXvmMKD0IcdLTk8fPqLge+07Fe7HOGL2COuNYIg+PFXgEcw3fgn+zM3wyw0mb76iGC9047e+4lNRcKidYo+LcAi1mR0kD2y7sVL4XMHqsf9UK50hjXYY4q/pTBQ5zRtfqndHx7zebzcXZgOlPQ4zW28mzc6Dztl98hRR4b25mhyZNXouBaUqpQD81b0IM7C7ooeJsWNLVw1EYTeoIn2pPGfPmEMcGhUNDQW6yjJX9a7wTpe8LfUz/BZ5Kx0XWYqx3Pn5wsYzJ5yhLZVwC5xiBHLDv1Q+TQncA==
*/