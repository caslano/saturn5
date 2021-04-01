/*!
@file
Defines `boost::hana::any`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ANY_HPP
#define BOOST_HANA_ANY_HPP

#include <boost/hana/fwd/any.hpp>

#include <boost/hana/any_of.hpp>
#include <boost/hana/concept/searchable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/functional/id.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs>
    constexpr auto any_t::operator()(Xs&& xs) const {
        using S = typename hana::tag_of<Xs>::type;
        using Any = BOOST_HANA_DISPATCH_IF(any_impl<S>,
            hana::Searchable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Searchable<S>::value,
        "hana::any(xs) requires 'xs' to be a Searchable");
    #endif

        return Any::apply(static_cast<Xs&&>(xs));
    }
    //! @endcond

    template <typename S, bool condition>
    struct any_impl<S, when<condition>> : default_ {
        template <typename Xs>
        static constexpr auto apply(Xs&& xs)
        { return hana::any_of(static_cast<Xs&&>(xs), hana::id); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_ANY_HPP

/* any.hpp
yT64DhfaBHJBSdEzM7DpXw4CggFm57R0iHHzRAEOZqDlbVg1W58hznC1vncdHpkZDIJNLoysnYeSyCp+3QV/ir5C64KybYiy9wOTLpse17jiS7C4uc4TDw4eaNn9WOJI3+8nlTklxlF/Kni1NJoU3uAZ6qOYsgCnEAhqvHiFDs9EBHZuXkKZPy+kLmbEUfCOVBD2gZ2SJKFe32crExxYTQyncZaNqn+WLCcc/veshl/zArYJoyFLbPftVV/mj7NgryaqeiVVO0HWK8tJX65O7Z579Qt02r1uez/uS1L9jypUpSrYAbKvUSeyh7zxgDyDH/OCUeUBgR+jo22OM/5TUsEkOUBLwrqyRk1ouxISrqN0vNkzJJNVP6hNowR2pdtWdQmZyfLbvEUfNiUd7W1Ye1m6iZLoS4CEUgy8hjzmtLwqDIWhmOOfI3pNrVkeyBrW85HWnFLWP475dCfLVaPfZKjQwlheg1vrq4fx060/Pr1Ju6eNNPepjWVF0wZw4aByZFMdiDNIb4mUU2IVEwpO4e8Tzwsr87rk7BDcLlf/Sn5dMSg446Bosvyf4w==
*/