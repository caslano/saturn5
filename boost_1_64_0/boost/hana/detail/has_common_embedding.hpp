/*!
@file
Defines `boost::hana::detail::has_[nontrivial_]common_embedding`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_HAS_COMMON_EMBEDDING_HPP
#define BOOST_HANA_DETAIL_HAS_COMMON_EMBEDDING_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/common.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/detail/void_t.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <template <typename...> class Concept, typename T, typename U, typename = void>
    struct has_common_embedding_impl : std::false_type { };

    template <template <typename...> class Concept, typename T, typename U>
    struct has_common_embedding_impl<Concept, T, U, detail::void_t<
        typename common<T, U>::type
    >> {
        using Common = typename common<T, U>::type;
        using type = std::integral_constant<bool,
            Concept<T>::value &&
            Concept<U>::value &&
            Concept<Common>::value &&
            is_embedded<T, Common>::value &&
            is_embedded<U, Common>::value
        >;
    };

    //! @ingroup group-details
    //! Returns whether `T` and `U` both have an embedding into a
    //! common type.
    //!
    //! If `T` and `U` do not have a common-type, this metafunction returns
    //! false.
    template <template <typename...> class Concept, typename T, typename U>
    using has_common_embedding = typename has_common_embedding_impl<Concept, T, U>::type;

    template <template <typename...> class Concept, typename T, typename U>
    struct has_nontrivial_common_embedding_impl
        : has_common_embedding_impl<Concept, T, U>
    { };

    template <template <typename...> class Concept, typename T>
    struct has_nontrivial_common_embedding_impl<Concept, T, T>
        : std::false_type
    { };

    //! @ingroup group-details
    //! Returns whether `T` and `U` are distinct and both have an embedding
    //! into a common type.
    //!
    //! If `T` and `U` do not have a common-type, this metafunction returns
    //! false.
    template <template <typename...> class Concept, typename T, typename U>
    using has_nontrivial_common_embedding =
        typename has_nontrivial_common_embedding_impl<Concept, T, U>::type;
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_HAS_COMMON_EMBEDDING_HPP

/* has_common_embedding.hpp
2JCJNY9jbikC5tDKbxfsj4snWJ6W30KLD8cxbBHDziFYDv5WU4YwqG9/4CPh88hPWdIq8WOZxrHtMP5BiBRtxrEl0Kmmyx6TXU/Sjk0xji0qRdvQqu8f+OjfB0g/o1dbX9pZmi+dKF0vPSN9LU3NmJExL2M04+yM2zNeyfg5Y93Mxsz+zCMzL8tcnvlJZmHWFlldWdGs07NuyXox64eskuyts/fMPih7cfY92W9mZ03ZeEr3lJEp5025Z8qbUzJyKnJacgZyjs25MufmnBdyXsl5Vft7J+eDnE9yvsnJyM3InZa7Re72uTvkdufumzs/dzg3lBvOjeTun3tM7rG5x+Uen3tR7sW51+bekftE7tu5n+Z+keTvy9yfk/6tL20srY+/DaQK/Gv920A7jg2/NlSO6fvWP9Aq6EIqbEitpNLSFWDLRomqn1wpG3/58WuTYlxFFoIU419lTJah/U3TvkuwrQr5qUixKqT4Twa0in3asJ2P7Rtsm8GwA7E9iK0I9WIWtoOxLcfmQGX1YTs1CxzbGtng2E7C9iK2/Cmoi9j2xXYltp+wteO8ch62Z7HlokZNx+bHdj62p7Bl5ql6TtJ0NeSpumETZNR8YRvyBs/UZcx5qHnvl6fqR36wQbURH+St+oU84Y+a7+lI+zq2mlUwNsK2DBt8hO9Ii987InCwE/7osTC4sQ+dsNFsnxEv2K/aNZKv2rGGKT7wETbG/cXH6k/iWMEf2K3KgkG/mo81f9gEeVUG+SNvNa+L81UdRVr88IFNRh5G/vmqDYavsNnwF/bCBoMhZvZi8agpFg156YkH8sVvo/4aecI+2KLaB1uM8lNs+U6zAzaZywUfI0/YhHw1m6x5r7uqYq+5/qZWN7pWTW/daNPaL/IzynqW0W4N+4xYLFzVaMdGLPLVtoQPm6fR5pEv7E0eB9hk9t+w6ZJV9bJIXxz0PJE2nu+VpliY9Bo6n9Bs2M5iA3zBx+yPYbeRP3yx9mnwhSh/xgZF5kcbdhD5q/FJMQ7OAvH8ReOQSruYU5DedmE3DrF/SByWpDkO5vP8slXEzvWPFCQ+1zfkTex8n+o55JuC9J9DqL4MtmAsoI2LmD61fDVzv6rYacQMH3O/ytiT4rmsbbWJncvGn8cmHouRvzEWS9IcC9RN3Q6iXppjpI1xVlN0m+so23/AHrG+HBt0meu0ERvkpZeB0a6QH/K3+Ig8oVfNdzvwr1dTbUa+8FMfE6t+SVrMYTviEPfR3MZgs/3rhvLC9F83EDYYdcPafxys7Bda+1XFRt0e3QY2f9iafMzD9WP7F6anb98xX+/HUhtzLC40rpWsbQZ+2R9zpBKL5ZMUC7v9x5eF6e0/UrFh7dXTa4PdNrrT6v+MNiqvnt42ajcOF/yFcaBsWD4JNtgdC3+1unj/IDoWTqWfWtshPiYX6afsloXLkf6ySHUMrJ+ng470j4Upm8zlo9hxJvJ+ZKX8Ddtgh2GDNX/kpcfVXA5kvIx4Kjq/c4z1q7PXQP5rmNJr9pvteQ0ctur2G2MX2IS84vrhr2G3YRf8N2xDHGC/aiPiYS5n+K/HxIihoQu2QF7Rby7PhHE1xmF5Rfq8pfV8SMYT/uux0+IwgTk63fYtiyavbtmxZ9802rFslYmND04sSu+5mYsF7EH+RiyMunZrkVi9wCduz9tFfJkUTFX8S61P7psqfm4Q6ZPNx5HeXJ5W28w2wRZV9zFTVTvgi/m8AB90O1Rbz3SodsNW2GPMicP+1OvpdVPTM4Z9YerE2ktucXrsmIgNdWm2AXLo91X9s9cwzr1GX71PsWmOLcX7NCel2Wa9X7m1WJV9G9/TpknSztgWYrt4GmSx/Yatbk0=
*/