/*!
@file
Forward declares `boost::hana::less`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_LESS_HPP
#define BOOST_HANA_FWD_LESS_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/nested_than_fwd.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns a `Logical` representing whether `x` is less than `y`.
    //! @ingroup group-Orderable
    //!
    //!
    //! Signature
    //! ---------
    //! Given a Logical `Bool` and two Orderables `A` and `B` with a common
    //! embedding, the signature is
    //! @f$ \mathrm{less} : A \times B \to Bool @f$.
    //!
    //! @param x, y
    //! Two objects to compare.
    //!
    //!
    //! Example
    //! -------
    //! @include example/less.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto less = [](auto&& x, auto&& y) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct less_impl : less_impl<T, U, when<true>> { };

    struct less_t : detail::nested_than<less_t> {
        template <typename X, typename Y>
        constexpr auto operator()(X&& x, Y&& y) const;
    };

    constexpr less_t less{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_LESS_HPP

/* less.hpp
AXnerOMeFMjl5C0C1YFtSLn+rKCUTGFHTSDNKwsSz6ubqbjOiDQOmRtaucgRutcg+8t3dzfpx+j9sRZXo9QwvulJoL56DkGA6+Y6uSkw4m2xjBW/NeGXDCGc+xsczWWmrdjudgdoRp73do4R/pNTijlQoYC20ffEO6r7En7lCg0yVTehEhkGXFNFJAOfo/b035yndyCp+ysMCtytJkNER163mQ1Fy008WUU/2todES9ScvIxtLQdKRjlykQjd65Ghc1XJ5q1dDLyL3S+VfrxrVUdZ64X5M9rRYgPf0ZifVoGvF4Z1EpUB8CcFD3lJqxztpp/B1Jhgt5jh0YYNSnuznsT0bihCAA4MPfpb2RtfK3Rbo9KDlFznqUTn5a4lo8ax1D38RgKRu+1Gy49rXrcCSnhK28jbcuxfipd74TRr0XgjmCYGXsPB6+eofhX61PrWCDB7UmUgBNsXitIEERs2EWizAAaCLVrVCnNAwlBFB2t20b9leg3UF3IcpfnD6yB0WyMWPwSBWGQiURWyHqiQ1XgcejGJ6w8hAAFIWa5UycSk0ljjiuABOGbBQ==
*/