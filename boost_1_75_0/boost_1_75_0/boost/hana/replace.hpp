/*!
@file
Defines `boost::hana::replace`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_REPLACE_HPP
#define BOOST_HANA_REPLACE_HPP

#include <boost/hana/fwd/replace.hpp>

#include <boost/hana/concept/functor.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/replace_if.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename OldVal, typename NewVal>
    constexpr auto replace_t::operator()(Xs&& xs, OldVal&& oldval, NewVal&& newval) const {
        using S = typename hana::tag_of<Xs>::type;
        using Replace = BOOST_HANA_DISPATCH_IF(replace_impl<S>,
            hana::Functor<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Functor<S>::value,
        "hana::replace(xs, oldval, newval) requires 'xs' to be a Functor");
    #endif

        return Replace::apply(static_cast<Xs&&>(xs),
                              static_cast<OldVal&&>(oldval),
                              static_cast<NewVal&&>(newval));
    }
    //! @endcond

    template <typename Fun, bool condition>
    struct replace_impl<Fun, when<condition>> : default_ {
        template <typename Xs, typename OldVal, typename NewVal>
        static constexpr decltype(auto)
        apply(Xs&& xs, OldVal&& oldval, NewVal&& newval) {
            return hana::replace_if(
                static_cast<Xs&&>(xs),
                hana::equal.to(static_cast<OldVal&&>(oldval)),
                static_cast<NewVal&&>(newval)
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_REPLACE_HPP

/* replace.hpp
LxkrhvfHMCvjCsz/sldhVsyL2Qc/Pj+O2+tZYrJkdnzjbuNyHs+/opIDlszSm45Vj25i/K2vaUtmcJstE387iu2J+M0jAVO4+YCbgyXEs6nXb+IETLOxWx/wb3YDePpbWsCsy/15zfezcP/57x5ZMMkf3CS/rsD688O7OAtm9MuVPlsm4vojSztaMKMqw6JO9O4B8JNShs/81ivq9bC/sfxj3ofxmabh8y2L12H9dvxg4jFduy370W4Y5veHDwd4jK1h0vbTbXD/rcrCeExzx4uf+aPweO8oM1HM0y4d5jE5XQB2LT9AMb4bH84oOIXnV0o5TTEDuoePqdqO9XX6K8aU8af/sHMdnL8BOLzE9CUj/GHJGY9+2L5Nf01/yQhMOWHTjMH8TXoTV5vxQCQbUVSN5THiLVOTEXDjxPzBk/H8Ln5L12Q4Oe/v3e0PPsDZ7+KqM9Ll39+9NhnrT0op8zlj8u5DF7N34fkR/95UlaFI/NZCzOL2p3ygqzJcyr7/PvkG1k+3srjKjA1F2tl3yjD912XMp4xVj27a992F5Xus3FSRccla0fTuJDy+8o90RcbL1kM7XO2B5VP0kfmYsfpZ6uwbKTi+vL3CVJ6xZkPVzT7fwvMWSvSJLs8YtaGLim6O+Sv6FFeW8UNsn5X3XmJYVcl8yLBbeTz+fBQeP5cq0/uMwOJok3UHHJ9OqaLfZ1ScS+gpbCLC68Xn
*/