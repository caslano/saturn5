/*!
@file
Defines `boost::hana::flatten`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FLATTEN_HPP
#define BOOST_HANA_FLATTEN_HPP

#include <boost/hana/fwd/flatten.hpp>

#include <boost/hana/concept/monad.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/detail/unpack_flatten.hpp>
#include <boost/hana/functional/id.hpp>
#include <boost/hana/fwd/chain.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs>
    constexpr auto flatten_t::operator()(Xs&& xs) const {
        using M = typename hana::tag_of<Xs>::type;
        using Flatten = BOOST_HANA_DISPATCH_IF(flatten_impl<M>,
            hana::Monad<M>::value
        );

#ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Monad<M>::value,
        "hana::flatten(xs) requires 'xs' to be a Monad");
#endif

        return Flatten::apply(static_cast<Xs&&>(xs));
    }
    //! @endcond

    template <typename M, bool condition>
    struct flatten_impl<M, when<condition>> : default_ {
        template <typename Xs>
        static constexpr auto apply(Xs&& xs)
        { return hana::chain(static_cast<Xs&&>(xs), hana::id); }
    };

    template <typename S>
    struct flatten_impl<S, when<Sequence<S>::value>> {
        template <typename Xs>
        static constexpr auto apply(Xs&& xs) {
            return detail::unpack_flatten(static_cast<Xs&&>(xs), hana::make<S>);
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FLATTEN_HPP

/* flatten.hpp
3oumqyAgiggGp2Z1byI2ID4GLVbBvg3TWV3IhaE8wVv2bm/+J1c0AkcUDB+gN4pb3NAGTwxgVAIxfozd9JUVm/xnZ4Aw9V+wQVWjz22ECXYP5KxWCU/BcVIAvrR8HogNq/vBpTjAMC8ijlPE3a5rcTwd9dGmM+zNHel1+jKljcIlkjnH0Re2IeIp03Wd1k2p9RynlDwUOUoR7+RzgwRkoZXV81BoDpXPuRN1OtatrK9EOK+/cHmY8M2mX351m+RkqCFnVcBygpnGrh8T2jEl7M/cKiscruISV0lYUmf21O7wSMIWMF7bY33SUlut/GLRt9j5iE9zIH/rFn4nn2SyzYLpvQpVe9XZuWfwKQm8tGSUHHAkxXT8rx91Ung3NTlqdCF3Re/YrxQ5kx1C6kpCDJ7Ub6rm690oXBTVq/ovZiQhSxp6bw8zrN6rEGSry582gjWFUK4IHiKMixexEX8wtWKNMQtwguKvOo771P7GSlr8DY4KaYL+Ldd9u7yIwaqURdrwu9/OubnfukdccVBOjUKH/lL2NFyS2HMMqqSf+VNJBXgnH3il2C35nA==
*/