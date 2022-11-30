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


namespace boost { namespace hana { namespace detail {
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
} }} // end namespace boost::hana

#endif // !BOOST_HANA_DETAIL_HAS_COMMON_EMBEDDING_HPP

/* has_common_embedding.hpp
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
*/