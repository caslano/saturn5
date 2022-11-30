/*!
@file
Forward declares `boost::hana::flatten`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_FLATTEN_HPP
#define BOOST_HANA_FWD_FLATTEN_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


namespace boost { namespace hana {
    //! Collapse two levels of monadic structure into a single level.
    //! @ingroup group-Monad
    //!
    //! Given a monadic value wrapped into two levels of monad, `flatten`
    //! removes one such level. An implementation of `flatten` must satisfy
    //! @code
    //!     flatten(xs) == chain(xs, id)
    //! @endcode
    //!
    //! For `Sequence`s, this simply takes a `Sequence` of `Sequence`s, and
    //! returns a (non-recursively) flattened `Sequence`.
    //!
    //!
    //! Signature
    //! ---------
    //! For a `Monad` `M`, the signature of `flatten` is
    //! @f$
    //!     \mathtt{flatten} : M(M(T)) \to M(T)
    //! @f$
    //!
    //! @param xs
    //! A value with two levels of monadic structure, which should be
    //! collapsed into a single level of structure.
    //!
    //!
    //! Example
    //! -------
    //! @include example/flatten.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto flatten = [](auto&& xs) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct flatten_impl : flatten_impl<M, when<true>> { };

    struct flatten_t {
        template <typename Xs>
        constexpr auto operator()(Xs&& xs) const;
    };

    BOOST_HANA_INLINE_VARIABLE constexpr flatten_t flatten{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_FLATTEN_HPP

/* flatten.hpp
+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
*/