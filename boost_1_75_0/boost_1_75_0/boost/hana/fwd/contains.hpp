/*!
@file
Forward declares `boost::hana::contains` and `boost::hana::in`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CONTAINS_HPP
#define BOOST_HANA_FWD_CONTAINS_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/functional/flip.hpp>
#include <boost/hana/functional/infix.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns whether the key occurs in the structure.
    //! @ingroup group-Searchable
    //!
    //! Given a `Searchable` structure `xs` and a `key`, `contains` returns
    //! whether any of the keys of the structure is equal to the given `key`.
    //! If the structure is not finite, an equal key has to appear at a finite
    //! position in the structure for this method to finish. For convenience,
    //! `contains` can also be applied in infix notation.
    //!
    //!
    //! @param xs
    //! The structure to search.
    //!
    //! @param key
    //! A key to be searched for in the structure. The key has to be
    //! `Comparable` with the other keys of the structure.
    //!
    //!
    //! Example
    //! -------
    //! @include example/contains.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto contains = [](auto&& xs, auto&& key) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct contains_impl : contains_impl<S, when<true>> { };

    struct contains_t {
        template <typename Xs, typename Key>
        constexpr auto operator()(Xs&& xs, Key&& key) const;
    };

    constexpr auto contains = hana::infix(contains_t{});
#endif

    //! Return whether the key occurs in the structure.
    //! @ingroup group-Searchable
    //!
    //! Specifically, this is equivalent to `contains`, except `in` takes its
    //! arguments in reverse order. Like `contains`, `in` can also be applied
    //! in infix notation for increased expressiveness. This function is not a
    //! method that can be overriden; it is just a convenience function
    //! provided with the concept.
    //!
    //!
    //! Example
    //! -------
    //! @include example/in.cpp
    constexpr auto in = hana::infix(hana::flip(hana::contains));
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CONTAINS_HPP

/* contains.hpp
FeJg+hG80o7Od3o7Si2r+o0rtbA1hth3PjSlwVcSmFxIXblc8ZcCHcxlqPb4M4Fis3V0tzgwwF4vrTTUapDjKuajS3Bpvq2oWlRlPCMVoCIo28BmG6r92YurIzkjqyvTtYp6CQ4TpZZYRiSny8VDF2T5bizSUukoMa+N4ZVN3LWUcy3iCAuZO0hsPRvZWludsHJ/pb6R0itC6y0a63NRqIeN5VtmSzm2WD/HHMuqa9gcA2sI/dimkXIs9iiISi14d6msFMpJwwa0sFyouTlUDClyLUXUvVI7VvUVJmH0QRKhCZeGeV8GXfD0urghs1v2iBhfGumRZv2IRqfINgyD8WdcrbX8t7hvwbWBB/BxK/qmC6O1albjv83FX7xe2RvUR1bq/Bs8nKkBt0bW6Vqeo9MFBIaJf35p4iI1II3MlLDu2H8kU+f0jFQiNrj4WDViYuyFZPJrrpb8XHbPiJ0Yoc4BOBdKevL/c/6irPpZxb3O4tBUTaA/TDUVU4XL5PTXbYrLY3u0MJkwnxLe5eJVMl04DTqEl5BQ/LHApFDcGpgwA822Bn4UimcGRs7AAS5w3Yxd6KJ9QCg+JdA3FJ8bsMx4GwN6gM/PF6ZNxO3s+mrUt3Fbyy20G2Kz13vsRwAdL0xCNxRP6xcYxfan2FPZg/ZUDp8rDm24q/u2gDYndE6/Su/XLWGFmex7yDLPut2BToNmsTORXBBCu4rx
*/