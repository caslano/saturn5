/*!
@file
Defines `boost::hana::none`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_NONE_HPP
#define BOOST_HANA_NONE_HPP

#include <boost/hana/fwd/none.hpp>

#include <boost/hana/concept/searchable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/functional/id.hpp>
#include <boost/hana/none_of.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs>
    constexpr auto none_t::operator()(Xs&& xs) const {
        using S = typename hana::tag_of<Xs>::type;
        using None = BOOST_HANA_DISPATCH_IF(none_impl<S>,
            hana::Searchable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Searchable<S>::value,
        "hana::none(xs) requires 'xs' to be a Searchable");
    #endif

        return None::apply(static_cast<Xs&&>(xs));
    }
    //! @endcond

    template <typename S, bool condition>
    struct none_impl<S, when<condition>> : default_ {
        template <typename Xs>
        static constexpr auto apply(Xs&& xs)
        { return hana::none_of(static_cast<Xs&&>(xs), hana::id); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_NONE_HPP

/* none.hpp
o9Btkpm3Vub+nabo5h/VGeqo61fhFJcVslupIWTjrBJnmLfxvCcc5MZBqGeluRgFs4lbYTTjwhJs3a8+LpDt3Pom9UYsso3E+UN8oTDLNEpu1iSTpFVw0ORc9s/Hwpmmb6dSVS9ffLNNMAoDqsy6PltzUZ7i8Plcmlo085PX2APO5Oa1rDpl2S0pypNaMvD8ffE0UttysbwJ8+25mkGy5t0ENz7mxpB1dBb6S9wY5HttHiQ+G33+MttDfi673fkp8qCoRn4Mf1lWCZD3UayZe95xzoMwpkMlxgUZ9beLbMyER20M0CRtMPWSOT/gf0Lv/FHvCz+wqbtcsPfby5yXd+jc3CTdcipGRva8oYl//34rxownNn17NSLOLS/Mwy0lySMspiKkjVtHSzuafNFLMjI2StSNjx9JTNZN+bqhlaJv2lrSVJSW/naTEp0v+PJP7n7kwxvq4oUrojyGNlogOpIAI/XkDPzp8+Rm5PEeqNRVfnwsCezoNoCAvuoSoMB2r9tLLRo0YbnfZx2H/Ox0PSVEuF1erwImrV5jXgXE2savyRQMph5X9vkYbvl2quwrKj8ccav5bv4+t/I+WgLbR8Pkd5Pjb6q7xe53CioIkrwHJb7s7hv2OfIbDg0XQC9DUwc/n7ZbKpeNFF9ZZci9CfE2nQCs7j45x+UQSjUzDgz9UK9KWzvtL99SAYeB2joSEDP+GDRCeN/CTqgA
*/