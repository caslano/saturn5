/*!
@file
Forward declares `boost::hana::mod`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_MOD_HPP
#define BOOST_HANA_FWD_MOD_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Generalized integer modulus.
    //! @ingroup group-EuclideanRing
    //!
    //! Given two elements of an EuclideanRing `x` and `y`, with `y`
    //! nonzero, `mod` returns the modulus of the division of `x` by `y`.
    //! In other words, `mod` can be seen as an equivalent to `%`.
    //!
    //! Cross-type version of the method
    //! --------------------------------
    //! The `mod` method is "overloaded" to handle distinct data types
    //! with certain properties. Specifically, `mod` is defined for
    //! _distinct_ data types `A` and `B` such that
    //! 1. `A` and `B` share a common data type `C`, as determined by the
    //!    `common` metafunction
    //! 2. `A`, `B` and `C` are all `EuclideanRing`s when taken individually
    //! 3. `to<C> : A -> B` and `to<C> : B -> C` are `Ring`-embeddings, as
    //!    determined by the `is_embedding` metafunction.
    //!
    //! In that case, `mod` is defined as
    //! @code
    //!     mod(x, y) = mod(to<C>(x), to<C>(y))
    //! @endcode
    //!
    //!
    //! Example
    //! -------
    //! @include example/mod.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto mod = [](auto&& x, auto&& y) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct mod_impl : mod_impl<T, U, when<true>> { };

    struct mod_t {
        template <typename X, typename Y>
        constexpr decltype(auto) operator()(X&& x, Y&& y) const;
    };

    constexpr mod_t mod{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_MOD_HPP

/* mod.hpp
J5CPRcJOa3yics11YJzjtpU/PrWfJ6dnezYshNalPQEedL8tf7wnX6EstNdeN5wEd025WkcWEc+I26jElZQsV6gQ+MwSG7FEMKPSYJksNsG5YYg37EFhsadoVcDf8oFlTIl8lxCXo+xiyQvVQXxXIi9Re01OakwU+rsSVRMt9wIDY0fB8DrsdncPbIPVheuUKkHhuClVOcd3N23vTuoSMhUZTr4W16+cUvsWwiZUfXurM2VRwmT58d0BXwCabrxPQJlcXvpX4U195oDncVYljM4b/RfNG4aCW2yP7RCmgx5AXkBoDH8R4d0uFK+MmDiNZPuNM2UqpHrrkA3C3x7JRL5860yVl3yJ7iFtGP3w1vFHgX5481STqMM6OW+e/16BQkkEffE9IuKb4xDo97r+YOzXWeuKYiP5MlXkxG36cHz8M/0aPbKUrtPoC6fzpf74JY544cpKLYHisqS6eFH25CcKGM85TeUczXYuK/35S1xEud6NF/tro5BiKaOV7suFZOjIem+e0qZeApIlqDrJ55UysxRT/AjTciUQhQ0eGCzMZ2ZXjh6JZTM3rwdTumY5k1FGo2qOwUd9HrMcAyeCbv2kTFEA8822va+0FePaCrrSkx/9L/IOMa5HOj3Cd/ymHxslNWKHYJWDkQvD
*/