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
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
*/