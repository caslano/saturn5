/*!
@file
Defines `boost::hana::empty`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EMPTY_HPP
#define BOOST_HANA_EMPTY_HPP

#include <boost/hana/fwd/empty.hpp>

#include <boost/hana/concept/monad_plus.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename M>
    constexpr auto empty_t<M>::operator()() const {
    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::MonadPlus<M>::value,
        "hana::empty<M>() requires 'M' to be a MonadPlus");
    #endif

        using Empty = BOOST_HANA_DISPATCH_IF(empty_impl<M>,
            hana::MonadPlus<M>::value
        );

        return Empty::apply();
    }
    //! @endcond

    template <typename M, bool condition>
    struct empty_impl<M, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    template <typename S>
    struct empty_impl<S, when<Sequence<S>::value>> {
        static constexpr auto apply() {
            return hana::make<S>();
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EMPTY_HPP

/* empty.hpp
1I85YXyexf1QspD7von9p905OEx9LeI5vornDvX3FPt5h+fD/CLqE/V0Cf2dyAFBf1j2Y4v6ftsmnr/Uv13qfXrqxWX1uZ6VehVO+5gk6O/K8udp968XCBHj3gd8/2yKjeNaz/dM1PcPfOgn8PodnNuT3POlvjfO+GYL491jQ3wu/57Cf7/A/tJfHtjF9a8UMh/7W8L+b/uK1/i4b/B8nE9/zcH6zYzXts/muBkHKmbaZzV+oZ8ewnP6xm4hyzOer2A/tvG+ZTTj2h1clxnUc9s66qc3n4PtYPmzjK+ahRzfJcYxJvaT/mEN89tXSn1yGPicm3bzsBrn8lydyfet9kXTXjMuvMT5nM99uVy1T0M8X2kfHWaeg2uk/3HOLvfDZYX3s4u4Dht5HsyjXWQ/z7IfN/j9JtuZT7tZwvPjFO2zH+9r7OzhPqc9d9EPcVBfFfrDCsdxLpft08+zz2bcpNpPpnvUf2fH52XRb9EOzpZ6cr2X8y2ELJcv67VTP3J+wXNZfa9wvZyPQMaL14vYLvXlRhbjHjPtk7rfn5bPs7ev4b8joP9bUiDE4vF/18T9zvNz/nzu+2T6K7QH56kvtt/zvo/6PIlpCOutucD2qxl3vM9xJ1LfeL7NZ/y7p5L+E/X2pp3+Of+9wZlstjOJfifnRTkp+F4g78ufZ3zDeGBRAffPellPBf3RT01/aOqG/Rn78wzZcQF+Tcb6ylcDQu4zvJy13Csr+NOhUx/pfOvVRHFG+Pi9cl+9/8uBoX9tem5m9Gti659/9V5bw49ffORtv5eeCPxsWFvn9W9srX0ncu6V51q/4mv+6PYJAV9UPtIb5WXYJUJDlQ/PnrBOPB6W1fzNSeaDsduFklce0Obr5d9ytn3HqE+Gb3ugrSXys6GDM7YtS+kNyPGdLPpWNP5yzdMbdo/4e9fmPZBcY/z+rLQdgX8YfrRtj/jD1qmfqH2j7/ojLcrXnmxvXWh85VP99VNTzbXec9cFnHox5bOXOgOU1jm9czvDrRUDhT+LKB26f9NQnunSdGNe5vMXOi3ZDcnOl17/84d/EJXnmPeMn3Ga4WxAceu+ltDiubFxc771o9kvrhULRdzl/q8HXZp31GgUU6dPmhleb3zU/8HfRL+4fWxkXeO+l42fXfhEc4slI6Bln1Bevvi6Ys6xv/zW5pE43wfFCu8XQ69OaT/8nmHaqSmP7jmyYsGKJ4LDpju96grOe/143tKqLwSt3rtuevlLLw3t/sKTWc2v1CZ7NTySodwf0XB/XPic2uSHfmBMCX0oO+Bl37SAqZ2T/Jaf8y2YlPFAxmLr1CD/V+d3Gj/0063PBjjrH/TaX/+KqPe6399/+QPVjb77a6eJJ6O3/vCVvD+Gio8lrHq3I+yptvxOEXY55sV2wytbV3RP/s1zw3UzIlre7bJ2OnoFP/4gDEQIuQ+SQQYoBtWgDjSCvaAN9IB+MAxGwG3gqwgxFcwDMcAErCAbFAEnqAXtoAN0gz4wBK6BMWDwEiIcRAEjsIBMUA42g3rQBFrAIXAcdIFecAWMAuEthD8IAxFgMUgGGaAaNIK94CjoBD2gHwyDEXAbTDUIEQrmgRhgAlZQBJygFjSAVtAOOkA3uAbGgMFHiABgBJmgHGwGTaAFHALHQRfoBYPgChgFYoIQQSAMRIDFIAPkgWJQDepAI9gLjoJO0AP6wTC4DXwnYhwgFMwDMcAErCAbFIFa0ACaQSvoAN1gCFwDAb5CBINwEAWMoABsBvWgCbSAQ6AL9IIrYBT4+wkRBMLAYpAMMkAxqAZ1oBHsBW2gE/SDYXAb+E5C/0EoiAEmYAXZoAg4QS1oAK2gHfSBITAGDJPRfxAMjMA=
*/