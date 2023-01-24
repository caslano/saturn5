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
qL6v8NvbiuikWipHTIJ3OYTQkzuqtODo3Q6k2JNM3kV5uu1wY9VnvqqRCvL8IqYnJZAafH0bFb9fM0Bi4oVqUwtZB4Vbmqo+AwCHTWwEXbZB5cFSXTrrJJcAIPlPpXTqwaysD+MaXN27JeoZsZysQfdvpct8ZSMo1HSS10+gSGikslLhEm6Yqun5L+rrGx247EChDnytGSO80f7su7rUV8tDgSkTxdK7FgO9OzJEsvxslHcLb6BVdFn69EDC5pUX37xQSgxchVrWRw4Aw6hea1iENa1LUxz9Cgd1rNDuR8FuPxXsHmGCXdOUuGD3SKMjyAS7JxodJyu1NJTlBm0djY4TxT7HKernzNFPRbnIHZWjUYqKEU7yI+p2LAcdVM13HEeWoS/GMmgTAfNT0x3Avx2nrHlflDVne6rn03DkHL0KMT3mACd99RzhFerZiQpFL82NCkV/0hcTilouIBSdNmmUUJQkF3HcDA699zOFchwS+Xh2NYoeG/7KMXfxZYT8Fjlsx3GlDsV60J5pTNBbjZLejGo5kKv7WlTaWUCb+ib2sseAvurWFCC9N4apFrFfSqmmLsH82liACENniUrneYzFwjk4dVCmZym/0UluKKbMI5RM10tiHh7CI3W1p2jfkfOuRNBFURaZnR3bSO6cqG8ko6TQu+PkEtUBYQ9PgxaT+gHAVctjomIpxU3m0QirHO5bO4McmZjQiaug
*/