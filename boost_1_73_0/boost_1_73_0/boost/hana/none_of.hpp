/*!
@file
Defines `boost::hana::none_of`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_NONE_OF_HPP
#define BOOST_HANA_NONE_OF_HPP

#include <boost/hana/fwd/none_of.hpp>

#include <boost/hana/any_of.hpp>
#include <boost/hana/concept/searchable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/not.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Pred>
    constexpr auto none_of_t::operator()(Xs&& xs, Pred&& pred) const {
        using S = typename hana::tag_of<Xs>::type;
        using NoneOf = BOOST_HANA_DISPATCH_IF(none_of_impl<S>,
            hana::Searchable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Searchable<S>::value,
        "hana::none_of(xs, pred) requires 'xs' to be a Searchable");
    #endif

        return NoneOf::apply(static_cast<Xs&&>(xs), static_cast<Pred&&>(pred));
    }
    //! @endcond

    template <typename S, bool condition>
    struct none_of_impl<S, when<condition>> : default_ {
        template <typename Xs, typename Pred>
        static constexpr auto apply(Xs&& xs, Pred&& pred) {
            return hana::not_(hana::any_of(static_cast<Xs&&>(xs),
                                           static_cast<Pred&&>(pred)));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_NONE_OF_HPP

/* none_of.hpp
WmwYlgKkRrpMTLTmTcl3Al2M/IR9J7wipaIWaHpkls05nStunvOvObcwT+V0+fix2ri/cO6+fE40Sh6akxNyBEYsO1cwHaE6JqEzaGQ7f2u3ncthr2CdCRKXLim23XUcWDTOEGxrjUBFZwA8WzAYIL8BFsjQntWazg8N2dW0v1qpDSd1me1UWHJsDyMuikJORj87yiUUppHc0tDDDdnVJIjq8s7ZnaZ3Tedlb+DsBiHbBIlnbxQHzZbxkNq0CGYK14Fyj3N2Uc5Hi6Yy2tDW+Px5cR8yxKE/oQ5dnaEX7nnv5bEShBDc7DDgw1gcDXbdspjiqVFlQ7BfGu1wG/Cs0AQ+w9WPTVBbup1N6MmZXpvs8wW80cCU1c3/VvuiwpmDcmAEu84sk87m9TscBw1yqxr8toIE6jTrd9gPqPNM5smdxz7eozE2YviTMy1bVHXBG+AbGFkpUe06WxPVJ9CUvtK1u4KS25AWzjhvXFzBmtlsENn8FmZxG/WoYqI30iIRvdk1pOscWi3q3o5keLsliFsTTRnNGLihOUWQDXMOmGb0Y6Gm7ajH5Ekw8UG4gYi2wH81BaG7rbQLSmRbGsPmsU9xNFtP2fEtMxrjRaXtbn7krmrZIL70ylZVIXHo+xH9BaFtul2lHPWdw9aP
*/