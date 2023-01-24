/*!
@file
Defines a SFINAE-friendly version of `std::common_type`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_STD_COMMON_TYPE_HPP
#define BOOST_HANA_DETAIL_STD_COMMON_TYPE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/decay.hpp>

#include <utility>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    //! @ingroup group-details
    //! Equivalent to `std::common_type`, except it is SFINAE-friendly and
    //! does not support custom specializations.
    template <typename T, typename U, typename = void>
    struct std_common_type { };

    template <typename T, typename U>
    struct std_common_type<T, U, decltype((void)(
        true ? std::declval<T>() : std::declval<U>()
    ))> {
        using type = typename detail::decay<
            decltype(true ? std::declval<T>() : std::declval<U>())
        >::type;
    };
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_STD_COMMON_TYPE_HPP

/* std_common_type.hpp
yQf+ZXoQ8s5Wcsh2+vF5JOjIakT0Fj4ltJhIki2RH7Fc+MokfGmy7a/5KjwK7fUEsxrJkidNtiXEVKlf5OvgU8vijUJqWtGK8vw9ZMmeAdHehQev+IPe5LemAIJZreGEt4BRdHvwn+g8mRUU7ftgUnMdnlJy7gP55zx59P6uo5+lRiCVIBuqOCzRuY8seS96VEq2d1n7Wuy4T6cTGvFMFFePXsqgpf1p/yE6I37TAv/tA2hmMG2L6Nxps/dWJ5B8PKISEGpO6kiBiSSL9vYWeydtF/uA6OypWk7OkkYoA2bwRQNHvwIUpHsewlMeJ1NPp0ZJM+F7yPGjnwk1USOm4HsqxhF7q9HeTfESAK/UCKEB6En5oGuVtOhBaE837rZ1ovG/RtE9gPfPzorud0V7wIeOIc/LVdfT6EKTXmiXXYXSa5AIzwcJB5jNQEyE8SVM0lftqkjAo23LXYUgHfpTnbSwLuAMyQsJbR9UXFedYLMPVE0jdklokiEpZGusOYjHyIo6oa4BPgUyqHofOj/k6R4ANMy4fLETBzJnK2qs0BJF2HruiBAw0bNqvUSHNpnsgf77O9GIxbvwNB4xRomRHB59mgxa+2zBygShRT+6D9rSKDSZiL0HEgsP9+ohAz5A3AOYeQC5rSIht6a9Mg9KuQlb9SwpigjNJtLpf2kGNgdJ8VeZYPxaZTKuHBgdMB4QVwwI7XjI+is9/ylk
*/