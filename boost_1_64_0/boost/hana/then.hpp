/*!
@file
Defines `boost::hana::then`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_THEN_HPP
#define BOOST_HANA_THEN_HPP

#include <boost/hana/fwd/then.hpp>

#include <boost/hana/chain.hpp>
#include <boost/hana/concept/monad.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/functional/always.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Before, typename Xs>
    constexpr decltype(auto) then_t::operator()(Before&& before, Xs&& xs) const {
        using M = typename hana::tag_of<Before>::type;
        using Then = BOOST_HANA_DISPATCH_IF(then_impl<M>,
            hana::Monad<M>::value &&
            hana::Monad<Xs>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Monad<M>::value,
        "hana::then(before, xs) requires 'before' to be a Monad");

        static_assert(hana::Monad<Xs>::value,
        "hana::then(before, xs) requires 'xs' to be a Monad");
    #endif

        return Then::apply(static_cast<Before&&>(before),
                           static_cast<Xs&&>(xs));
    }
    //! @endcond

    template <typename M, bool condition>
    struct then_impl<M, when<condition>> : default_ {
        template <typename Xs, typename Ys>
        static constexpr decltype(auto) apply(Xs&& xs, Ys&& ys) {
            return hana::chain(static_cast<Xs&&>(xs),
                               hana::always(static_cast<Ys&&>(ys)));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_THEN_HPP

/* then.hpp
2ved1K6LZYNVPe210Ve2KFcwoTzvhZVsK3gV7v+3kou55YdFX3tvuHQm7NrDlDTp65+L8ls3re4brtswR+Y4ONiRnF8LBt4LuBdZpFmnKPfmkpZbN8H1mXO2WMSj4OQ+Qpb3dbzqOw89HWOnESVqzO8dFotlnEDQtdSjZRnL13dW88G2K3qkjTAdqCf6Iy7f1eskfVfGCNloyU7BXPBSxPDHu1tZ7nnEUDvbDB3bjOy4So27k4QqMzvGJaFNe58H5XFC9V3U0hvQFW9tSxyxT8oSa040VS+471m1vx8LjbnYMx7PE8bKh99baD4Pq9zZKcVH2VBlXtHa8a6qasfUK8GeH4PqoO9jYnjcaJ2egmf5GLQW/SYRX1WVe4yet71vjWJiDsPuxeeYi4FASIUorJc/FupFYhFfp8qYkUGJwVtY/iF7/yJ36+IMwsYWCNgDn0TcrlI/2U+qAmur1+GCqWZj2Ow+5oHEvcIXVHmv2Wnlm04aNgYBQWEgNN75QJ7s2WkeiUkRw3VdFTlDzdBzybvwzcMnu5jkC1clFmWtdGOaph5jsg7+60sIPpm5vfepy1hhr6p+qOpQcPA/W+QASfRnr0u7SGNNI2GBjUM+o3VQwY1l/nBdF33besP7uopFHdL4yDbbNyi/MsyZxteNMCy+uCgSDzyn52MzL4QvNTosBFC8rQNG/HM/SnV51rWma1TVhMKj2Q/ukGbZkoNYLUX5mhkz8LbtHexCw0SGYjnxCExtcYSnCSOO80t5jmvKftNcWgmDPVZAVP+2DvehcqphpnKcO1P9P3VAn92mvFusB9kraSF+Bv00VmKBPtqUOYcCYnbb63BgEJMqo8xnqYxl1llVN04xUU1EoJw8rr7SlHsTbl0NBfVs9yp8+rM4sMThLoSBr8a7/7yZ5LwXnTV1z+AEBEaAg/0sksv6QzPFc2uF8zULR/dYkLvqMMJgguV2cz3xJeK6F7bvGHHN0MvBXGEsoy7jowws674LLh7X4MMMV5i45aowrn5SFle1lsJ1LAx9Qwb+JDboMpV7vOSD7mshwyvbhiFS7uuYLnI8wWra2p6JKjGj//Xd8tx/48C/szODJJFnkJAR+gl9TM9+EH29nK13QuD7BuZ7w+fR8pZmpY0qy70O6dHyjT6bv/l+eL79bLhL46Oz68Ys6/zkD6b+1nvXTqAP7pf9F5d0BWGParPaTtAnG9uZ53NreWIVttFfccnzjG0RcnyM+fXPgsGH+Ll9BfmyU7N5rpIr/Mfos7jkD0wxYBkeG8RfWSk3Vh7pP16lx4rnev98bX1QzyL38W/LehS+3JeXPu3ThmDs9D/X9iFwkvjqG/8QeeJNZEjGnhxOj9FPcMnzDGtCGsqqTy/2bJ5LBf5ss+1/WODSXRsjmgkgPuRTzro3C944BhOOSHY+Pp7thzGe49x/mGO90Vl4P9Ne88MyVhwQ6LG/3jmhKbu9+ZzxtaD8P79b8lDMnQ8u5TfVM12XBiz6oH/khzQGPdKwjz9e0qLTbNrIYf3+XvDE15lAELIfMfz3o5IHY/Lj9c/GIvPddIXvMRQLAPluvcpHsQBwHN5xwgeWK7TP3xVp2C+gJ9koR9sc+i3faz3vcncioVgyjh5A+Z+eMlkmU1byST7LvPpH5buL1wiA1/HKnSvX71gjKa/9T7yOt4E3v5ftNbxhzw2FX5/78bkTHoiah2Ge2TbarOtFJV8YCKgr1+0q8pBxGksdk7pRv+Cjf8sb4wGwDafF+4tOxBEgAaIicGy9cuXdrOd7PfI987E7ENGeNe4c78GhgOT50xvAt0hQDOGSdaO/V55P7hRo4dkObogX5Dt+Gwv00/nZ0tqN3+HJ3QM=
*/