/*!
@file
Defines `boost::hana::remove`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_REMOVE_HPP
#define BOOST_HANA_REMOVE_HPP

#include <boost/hana/fwd/remove.hpp>

#include <boost/hana/concept/monad_plus.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/filter.hpp>
#include <boost/hana/functional/compose.hpp>
#include <boost/hana/not.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Value>
    constexpr auto remove_t::operator()(Xs&& xs, Value&& value) const {
        using M = typename hana::tag_of<Xs>::type;
        using Remove = BOOST_HANA_DISPATCH_IF(remove_impl<M>,
            hana::MonadPlus<M>::value
        );

        #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
            static_assert(hana::MonadPlus<M>::value,
            "hana::remove(xs, value) requires 'xs' to be a MonadPlus");
        #endif

        return Remove::apply(static_cast<Xs&&>(xs),
                             static_cast<Value&&>(value));
    }
    //! @endcond

    template <typename M, bool condition>
    struct remove_impl<M, when<condition>> : default_ {
        template <typename Xs, typename Value>
        static constexpr auto apply(Xs&& xs, Value&& value) {
            return hana::filter(static_cast<Xs&&>(xs),
                    hana::compose(hana::not_,
                                  hana::equal.to(static_cast<Value&&>(value))));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_REMOVE_HPP

/* remove.hpp
Uk5SlYzkTyb5JBVPIuVBpHwiKSepOJDkS0k+ScUTCN54Uh5AykkqHkfKx5LyMSSfpKrRJN+f4JHUvP7/2z8jRaX7hbzcS5V2hv0Olcyjsv08Cv9cEPxcQuCbflH3dT/Nsob9DLwbcddv96UZo8e1gf0KlSqgHvgdvtZ9Xrw77H8ouYXqsd/c5w8OSLth/CUCqtjv7+c9e9ysxvvhAkvqhZ9FrfuJdlWwX6WiralXfh6+WUmbdsL+j/K3pd74Ba56eVb5G+z3qdImqnd+lvtmHzy9Dvbn1CYr8Xu/ifEPDh4ZDPsfKt3a+MHPtrpp84w1AZg/W3G53wbhn3uuVsN+iQpvYvzoNyvx06Pt7WH/Su1qSn3yO2SjmPMyHZe72asq/fJrHw+6XgD7UyqnGfXZb5jBdXz6Hly+Saiq9rsQtc9dXYvbc3I01vgVCVTXPA6LcHtO4i9+luELti07ieVn09Jo8uu0+R27YHk/XN8umaJ/yfE5f6OVFcBf7MQ8eqPQ9U7zhbj/7s0oPq1Pn6xYH+gG8BQHI5+Wzhu2ec0M3P4uocqCHrXi7sCqHfD9W6q4uVhAL/1tweOKhbDfpfgtigR0pyMeUQOr+gI8xynZkr4lHOd6bjPGz3cOt6JLFtY8uWuL60tbuVrT30zoOKfrboj/UDtcjNb004RlpeXV8P1fqnsblQ3d84r/3JnJuL2LbcW29C/Dz+zrkIPH
*/