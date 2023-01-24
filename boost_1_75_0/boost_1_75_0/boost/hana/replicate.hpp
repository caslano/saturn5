/*!
@file
Defines `boost::hana::replicate`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_REPLICATE_HPP
#define BOOST_HANA_REPLICATE_HPP

#include <boost/hana/fwd/replicate.hpp>

#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/concept/monad_plus.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/cycle.hpp>
#include <boost/hana/lift.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename M>
    template <typename X, typename N>
    constexpr auto replicate_t<M>::operator()(X&& x, N const& n) const {
        using Replicate = BOOST_HANA_DISPATCH_IF(replicate_impl<M>,
            hana::MonadPlus<M>::value &&
            hana::IntegralConstant<N>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::MonadPlus<M>::value,
        "hana::replicate<M>(x, n) requires 'M' to be a MonadPlus");

        static_assert(hana::IntegralConstant<N>::value,
        "hana::replicate<M>(x, n) requires 'n' to be an IntegralConstant");
    #endif

        return Replicate::apply(static_cast<X&&>(x), n);
    }
    //! @endcond

    template <typename M, bool condition>
    struct replicate_impl<M, when<condition>> : default_ {
        template <typename X, typename N>
        static constexpr auto apply(X&& x, N const& n) {
            return hana::cycle(hana::lift<M>(static_cast<X&&>(x)), n);
        }
    };

    template <typename S>
    struct replicate_impl<S, when<Sequence<S>::value>> {
        template <typename X, std::size_t ...i>
        static constexpr auto replicate_helper(X&& x, std::index_sequence<i...>)
        { return hana::make<S>(((void)i, x)...); }

        template <typename X, typename N>
        static constexpr auto apply(X&& x, N const&) {
            constexpr std::size_t n = N::value;
            return replicate_helper(static_cast<X&&>(x),
                                    std::make_index_sequence<n>{});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_REPLICATE_HPP

/* replicate.hpp
MUj41w5DTr8FxnM939OXji74wykt0FDU56ff9gx7T+8f8H4P03ebIXDz0exdU9/Ttr+8PR0lXi9aExgrSl/2nlZuvHt6aOI6wyv9Jp+qje/p+Q47b3YRbjEory4umXb4PV0sH71m3LTNovzpgviis+9p6wqPbzYE7Tb8fFre79v897RoziFqEW+/qP29ms7SN+9p3ak1/F2PthjubJqV4Gv1gd4eP2ad8pJetKMwdsvojh/oN0e3b1/703qRzyzlotU+H+hllpf+XJu6W0T/cGLC9cAP9JHy8ozJ5zeKHsQ8iZDM/0Dfeyne7XVuvWjd7I+PH8V/oGPt6U2Dx+0xPH7Y8WPS/g/0ZMdff2cdN4gS7/2dG5f+gT7cxudOYZOhhqYWxT9obn2g84fenzSKnyiS9fX76ffXH2h1l9sShytLRc6n+jX5YlVGF6/vdyuqfIOoX8G4miWdyugYgcvmF/s2ikwt55ywEZXRR0MGxHfqtk30/sDWsL9kZXT3keOnv52uM1z9afDAH5eWIX96GPNq8A5DZIHlwt82ldEGwW6R/vv9hk8Hnnnf/7GMfvJx5p0BxUrDs5QWmX0yy+jMHqEDK037DZ29Hcf98LCMPru/tLnt3xtF7VTHBJLPZXRZlayqS+5OQ0+PT52atCyno7d6tptXNsOwM0V672O/cnrXqrCnDy6tM/TRzgy3GV9O31C9E6ze6y8Kptq/
*/