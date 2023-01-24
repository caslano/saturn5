/*!
@file
Forward declares `boost::hana::append`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_APPEND_HPP
#define BOOST_HANA_FWD_APPEND_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Append an element to a monadic structure.
    //! @ingroup group-MonadPlus
    //!
    //! Given an element `x` and a monadic structure `xs`, `append` returns a
    //! new monadic structure which is the result of lifting `x` into the
    //! monadic structure and then combining that (to the right) with `xs`.
    //! In other words,
    //! @code
    //!     append(xs, x) == concat(xs, lift<Xs>(x))
    //! @endcode
    //! where `Xs` is the tag of `xs`. For sequences, this has the intuitive
    //! behavior of simply appending an element to the end of the sequence,
    //! hence the name.
    //!
    //! > #### Rationale for not calling this `push_back`
    //! > See the rationale for using `prepend` instead of `push_front`.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a MonadPlus `M`, the signature is
    //! @f$ \mathtt{append} : M(T) \times T \to M(T) @f$.
    //!
    //! @param xs
    //! A monadic structure that will be combined to the left of the element.
    //!
    //! @param x
    //! An element to combine to the right of the monadic structure.
    //!
    //!
    //! Example
    //! -------
    //! @include example/append.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto append = [](auto&& xs, auto&& x) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct append_impl : append_impl<M, when<true>> { };

    struct append_t {
        template <typename Xs, typename X>
        constexpr auto operator()(Xs&& xs, X&& x) const;
    };

    constexpr append_t append{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_APPEND_HPP

/* append.hpp
tA19E0ZobCBz9kcNzbYPsEjovAM9bn4LFSxlKB33n+8KPvPdfwOyeAN/NkNh8cQQFRxCt7Mg71k95s1T876CeSN5zXw0HrIDE6FSr2/sq8itf0VVs5I6aGDE7xDNCTd3KtppWI8/ESytCstDsJxNLmzhL5xitOl5lQ1zraZc+9OVXNnvEiMdAEY6AIXrqb2bQAD8VZoyXmGmmZTpP9VMsW2E8oEEyi9jzAN1gn51AMcAtTgAUD7RK3wz0OvmcTr9cqUrPPPaNjGoeRJglqK+al4jst5eWAPfE7ko+28GnuHX9xJDV6PveWgy/sJTgmvP4O5hYgz7iQfVRn7BYcFxs/9eeKcZowu1a0oa2SHqDXyFkrWSGJ5DFRdCSKKKBVTFv5iVKuq2UfsgJAN/EpXanI0wmL36Z1HfP4t0HjaJus3HgLP8MTbnjzkqUh+VP47dwvL2KlPp/nevxuHpIeTwkibiMmJzeb0NalNLKo/DRCmsln88SmHxU08ji2dVPoIsvno0WXtBobbQwn9NB7NQHojZ4ePBPkKGsr6DdW9a4vW9+gYyV5uwtI+yBnM2u70gL2XcfhUZ8aO3FRnxBCHSzHVXReQIIRJsvkQmkGmH0GtSZYI+o5IyIm1wZKaozkRASj7tkvv7YFFo3e48v6nmTRsaVMn7HlWm4vjowEc7Plpd+RDzbb5vKq4Mpnuo6WD1F9o7ltWgmsrDI2EB
*/