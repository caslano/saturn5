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
A5d0cTh6oVTh7Rp4hwa+R4clq4y1RxPy35oUL2rgT2rg9TF4RYXKVBVVCmQ9i1VRrny7FEYqFhpd+J0XY6IlSowbYgw0T4FMUphnmtAIz9OVE8IpbzPOOV2ZwO0ezDoLY4DtLH9r6tlhfDPCMx44Bk/NV48NGz3jV8MXJMBvo/BVptDShnazMbG3wlYzu/Jh4hwg7ojQZhadA7bOiiw01VokgbhvrJhiawRx7+5VxT0H4r6mq8ostJkgcngSDMdRReZPfRFkfgv5CEX+UZ3ojiB3LbmZcheIJygz9NYFWS5GcMkKqm2v2zFE9P/gVib6e0hneAlgRPhoYbFL4k6q0n++FP2DKv0h+Q5F/kcg/jU7qPjv0b3DxP87TPz3hLk++wDK/48Bqf4T5AOU/8PEPz+DWklUxX8iiP+jQy+vffglTNOLXUJPJjrVIV/77TI5+KE76pKr0EGEXJXtKpB+c4La1JOrNkh76ess3LPH62V677jazTfo8KxSmIOc8Gr6kiTs+PMCZd+ynIW0nBwoZ5Fajku6/eTF5WQPLWf0JcqxYDmR4eX8xR0ZUp+PPorVZ8MV6xPBcj5N/OfKiden4qNYffouUU720HJ2X6KcSexKYUlO2Q38AsHxkImsfIisxksa46Tm38dGZvl39CYCOuYhiYo1rVR/vkl0PEQ2DYD2cxhNEk3FMFNqCwStNEvvWnW6ZqNOeuL3qtGm
*/