/*!
@file
Defines operators for Orderables.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_OPERATORS_ORDERABLE_HPP
#define BOOST_HANA_DETAIL_OPERATORS_ORDERABLE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/fwd/greater.hpp>
#include <boost/hana/fwd/greater_equal.hpp>
#include <boost/hana/fwd/less.hpp>
#include <boost/hana/fwd/less_equal.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <typename Tag>
    struct orderable_operators {
        static constexpr bool value = false;
    };

    namespace operators {
        template <typename X, typename Y, typename = typename std::enable_if<
            detail::orderable_operators<typename hana::tag_of<X>::type>::value ||
            detail::orderable_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator<(X&& x, Y&& y)
        { return hana::less(static_cast<X&&>(x), static_cast<Y&&>(y)); }

        template <typename X, typename Y, typename = typename std::enable_if<
            detail::orderable_operators<typename hana::tag_of<X>::type>::value ||
            detail::orderable_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator>(X&& x, Y&& y)
        { return hana::greater(static_cast<X&&>(x), static_cast<Y&&>(y)); }

        template <typename X, typename Y, typename = typename std::enable_if<
            detail::orderable_operators<typename hana::tag_of<X>::type>::value ||
            detail::orderable_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator<=(X&& x, Y&& y)
        { return hana::less_equal(static_cast<X&&>(x), static_cast<Y&&>(y)); }

        template <typename X, typename Y, typename = typename std::enable_if<
            detail::orderable_operators<typename hana::tag_of<X>::type>::value ||
            detail::orderable_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator>=(X&& x, Y&& y)
        { return hana::greater_equal(static_cast<X&&>(x), static_cast<Y&&>(y)); }
    } // end namespace operators
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_OPERATORS_ORDERABLE_HPP

/* orderable.hpp
80YjUd7PcrRvh2IPDpWM4R6NV7sjeP4AD5Evs/1JNdUuxctDWa69sLGpLnWaVko88+uPuU6QCLhJxK9m2m6VKfT88gxgAWaT9EBRahd0Gp9NPA/6vSAL0BjoKb6ymH2udnoHFJqecE0k/igmEX5+JjGqtAXgNKWFaWrxh3iei8ssb2ShfUSf0jUHsRIh+ulgBN47Vkc+RIpuomUsBs1DCQUkEfsPZv36Ij+cw1/1l/pBILkA0sh/glthce+uWG/UHr5cjmVtNnH6Gw/zvUzn1K8TPlTEqwrSyE2AP3ZnRFEUZy/huL0tC2EbwemqLwp7KUi96GsHAF/I8lXqhlkBagJcxy306D4qe9kQb3l3eufqGSpJfB0Krb17uSHaCTHpwRXx/LVnXcmKjpj9vYRJBHHFzaj33phofawmY6A9+0iDldN2QCCrVUrrt9bvNRhGVephQZ9J7+UVnclM8DLbppqnzpoE/ModSmhfggtEBsQLTT3iNx3w7tolZ4tFiLXk0KQrfWqmqtGRyOk0pzeaZpxksuaApTcu6joIAjcODzZUdzUf7pTh+RPqmw==
*/