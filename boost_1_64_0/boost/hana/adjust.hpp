/*!
@file
Defines `boost::hana::adjust`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ADJUST_HPP
#define BOOST_HANA_ADJUST_HPP

#include <boost/hana/fwd/adjust.hpp>

#include <boost/hana/adjust_if.hpp>
#include <boost/hana/concept/functor.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/equal.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Value, typename F>
    constexpr auto adjust_t::operator()(Xs&& xs, Value&& value, F&& f) const {
        using S = typename hana::tag_of<Xs>::type;
        using Adjust = BOOST_HANA_DISPATCH_IF(adjust_impl<S>,
            hana::Functor<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Functor<S>::value,
        "hana::adjust(xs, value, f) requires 'xs' to be a Functor");
    #endif

        return Adjust::apply(static_cast<Xs&&>(xs),
                             static_cast<Value&&>(value),
                             static_cast<F&&>(f));
    }
    //! @endcond

    template <typename Fun, bool condition>
    struct adjust_impl<Fun, when<condition>> : default_ {
        template <typename Xs, typename Value, typename F>
        static constexpr auto apply(Xs&& xs, Value&& value, F&& f) {
            return hana::adjust_if(
                static_cast<Xs&&>(xs),
                hana::equal.to(static_cast<Value&&>(value)),
                static_cast<F&&>(f)
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_ADJUST_HPP

/* adjust.hpp
Gu8j/yXYKZzl873gs+2Q8isZ9kcx5AxlAGRz2ga73YxPaZTSlUtB/jLgI35fIx3jv026mO0Et/n5tpXd5BthywbEvWqDpdN0SUlJ6aAiqAv4/fSnZxnOaow12vjKh+fIM4hx8d7v+n2/7sct4L5Tpe27xwKnaaMBu40iv939e8DnTKDau9tfOOC6c1Tb5EeeNrl9tLvNNR0Tu80Vb5I1cTh2AdYA/wiegjHa5hq+x5N+huj9NVtIP4ESSDDuMOL825j6PVvvyLmF9ONGHfzeKu8V7gvZcesZG/XbX+cqbyQ9x4yxP5RtcRPdC0w9z0z6rJhzESHgBrrPNz17PrXtbaR7ielsx9lSl5+k2818azcf37IKv2K0YbbZ9Y54PvFph+WQkXdeJ31xTaQFxKUkR1tiY992yHATkSZph6TzjWTY9cP/F52i33ptjK2XW/Eb11tt8ZscXzTm+KK775rwMwwjy7cNPj3Gbu/ZEscqiSMwIqVDdJjU2Lc/3mF/H2jszyd9Ob8Pd2Vglind9/vulrR523+Ro+1vhsGcEu3nAQ8BN3CP7pmdE460/31j3X102PTfk7vc9MgAsa+FPdqC+tF7V0zXXl2VDZ+obHC3/bdlQ8xw+EsX/Ay8xvnRtl8iqwXW/codOG/F6UTNe/Ay/0LS9rJIdzJTsZ/rBIzrLXO7Toq/YcYElHcpZFA50lKCRATj0yOqWCO8U4nj4EnYezkAdNNAsFFbqLcZ+D06GW/Oxo0NNk1KTA427ZjYKNikc7B1uuOOgfnpsc+BlcOxOeOdAxqzR7TDqRzaHUB/nmN823vfhciAUeT5q7Ff7vc7O132dDnq+WURHmlLGWniXm27D6N7op7pyyX9JXarplOXP4F86HYD6j514GG46xgv9Fzte/cF+SeBfwHvEKr9yHuH0CjhGYO8LQVPYHXK6JROKR1TRkFgJAUCKb0TA4G0xGbBuOTE9MD0SJanpAxCexsFnsHI6kaNvOWn+sVqpv0Zo4hyE3aaj03o52T0fF1NUbk9Z3s33e8yJnIeAHbq5yzve4Fsm3V0w8gdXxOSNwTX024XbALGXO7Hgr2Gk+7Km9IbkU7eIx+ut+8yYhpyDwXn7TgfynrvuVsCeSLvkX8l503jDDYZfHe0332A6cIdWp6x7vKb7bvN28DsgTFboE5c4G57kafJUYXqrbOh7YHXfU9uGekHHP0s93AXY9SsfdV88txh30VIuovDD07J0Ie9j2reBa41F/jxvnddXLii2u4vC+i+jXSZ8ufouuqlyIGFMOUwi2AidEXENGDOnvOQnjUxe01Ev9dzZ49+k2d+lul2r4vcYvBvK0wmTIRMRrnkjNNyiWzdjzzqFt2vmuh6p1DvGBxK/jojB2FPgKmx9+VIWC1jy0Z1DyEsWUsjfY3RDf9PhVllmKfNJ30zJNH9Bp2uIWn9lTdzx2k9JV3moW9S2p1fOd8y+JcvfchM6UP2an5x5fBUfYjwZulY6Qjp881U04ydR+pngNDYnT0BNHUZvHeMQtu+xdmfNGZ/0kT7kzT0J+24q79rSrB1P3Qogba40yqY2ijSp7RHnxI8J5jTtIF9yi+YlnFmUzOuXt9RAfcvo+Vtvmh08O07zhp/6r7j03HuvuMvpFubLxhdqReOuRXy7jar7xgQfWtxXTCpkf/dSfSz8TbtP34fo/8gz1VbpP+odvYfwdQATzQ6upDySC43ZhdSlDIcuRuM9+s/BvB7f4tVl7Haf3SiXVPf/mM63Z81ZnKvPuzUT9+Y/ceg8e7+43yEMYJ2R9h/lHG9CPYaToYrbx7cIv1HSvG/vf9IgYzJ64mwsS+MvYe0y/njY7e79bcb/LtD7rc=
*/