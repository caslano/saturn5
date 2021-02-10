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
MyPkxCb+V5iMK5uLS6T5B2HRakz+j6UNwyysm4KVwvOgBEBc1pNxmUoFCuQWu0kYp6cJWyiP5qwal6doJ6kJs0W4+mcaqaZ/VUUUbplln51q/ExXEBNYcqIvZqIsVVNjZMuWsiaxE6hmTEl+ZTpROk9PM9xaMv32Q6QsvknM7/mmLDE4oosupHp9cudr8oBMkjCjcLEO0js27ZxkmeD7u9xn1AxlxTXdVCXKFVqq0KD5QEsVvx9YxUbFX0fkZM33umyWnn+ZAapSAp/c1Ab4UqTOMc/J0ul7bGath6bv4Rv1HYnWt8o8IQKqaESjcktg9m+cDxdkvLm7usFS4fpGxNMkshLRZW7RPVcIZ4LqtLCfQNV4Cs7wfA7zXa2ApYPAjKQvqFEgauEHTibTAE+1XJbpgcb3DT84xh12FnLZnRYCbLFoES7L4CUypops9hNAX7Be7vH2cPku8eAMmuNRbKllvn+jMzPeUYNfoDUvRXAl8g9toFwVmo3xFnvrFVuu/JAS8/oRD/SMR2bq8mjE3TNSaXfM80c34q1J13eQDD4B2kESdyV04WSyXkVcO+DmbUE5ScOCchbrKObNCUiAjujEDirjoRGPHF8IEOgGygLIm+La9dSK1v3yNG5CF0Dij1TaFAzfnuRpU7aa
*/