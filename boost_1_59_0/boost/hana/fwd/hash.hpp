/*!
@file
Forward declares `boost::hana::hash`.

@copyright Louis Dionne 2016
@copyright Jason Rice 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_HASH_HPP
#define BOOST_HANA_FWD_HASH_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


namespace boost { namespace hana {
    //! Returns a `hana::type` representing the compile-time hash of an object.
    //! @ingroup group-Hashable
    //!
    //! Given an arbitrary object `x`, `hana::hash` returns a `hana::type`
    //! representing the hash of `x`. In normal programming, hashes are
    //! usually numerical values that can be used e.g. as indices in an
    //! array as part of the implementation of a hash table. In the context
    //! of metaprogramming, we are interested in type-level hashes instead.
    //! Thus, `hana::hash` must return a `hana::type` object instead of an
    //! integer. This `hana::type` must somehow summarize the object being
    //! hashed, but that summary may of course lose some information.
    //!
    //! In order for the `hash` function to be defined properly, it must be
    //! the case that whenever `x` is equal to `y`, then `hash(x)` is equal
    //! to `hash(y)`. This ensures that `hana::hash` is a function in the
    //! mathematical sense of the term.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a `Hashable` `H`, the signature is
    //! \f$
    //!     \mathtt{hash} : H \to \mathtt{type\_tag}
    //! \f$
    //!
    //! @param x
    //! An object whose hash is to be computed.
    //!
    //!
    //! Example
    //! -------
    //! @include example/hash.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto hash = [](auto const& x) {
        return tag-dispatched;
    };
#else
    template <typename T, typename = void>
    struct hash_impl : hash_impl<T, when<true>> { };

    struct hash_t {
        template <typename X>
        constexpr auto operator()(X const& x) const;
    };

    BOOST_HANA_INLINE_VARIABLE constexpr hash_t hash{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_HASH_HPP

/* hash.hpp
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
*/