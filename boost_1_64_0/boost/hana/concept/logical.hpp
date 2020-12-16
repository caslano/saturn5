/*!
@file
Defines `boost::hana::Logical`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_LOGICAL_HPP
#define BOOST_HANA_CONCEPT_LOGICAL_HPP

#include <boost/hana/fwd/concept/logical.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/eval_if.hpp>
#include <boost/hana/not.hpp>
#include <boost/hana/while.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename L>
    struct Logical
        : hana::integral_constant<bool,
            !is_default<eval_if_impl<typename tag_of<L>::type>>::value &&
            !is_default<not_impl<typename tag_of<L>::type>>::value &&
            !is_default<while_impl<typename tag_of<L>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_LOGICAL_HPP

/* logical.hpp
7R9/S+8oYn5j0T8ct1bvKGLtxk7884plehaLHWBsyBuLH9EzZ1+PZ387RwNbp+saxOz8fXrCp3O0J8TajI0trBqq91aXDX5qsUfX7rLmxRd21zNczNZh9wP/9qruZ2J2fUNP3O9pPatc9tZH3qrmU6yvsW/7zNhdzyPX+tacMMqvd0Ux27un3lDYXv8mEeth17DgsRO1DmJ2301WO1p65uzX+b7UZ/R1F2vvinW3Z8Cjl2W0d8Xs+sb884Bt9HdaMafPNnzeNhl51bHwfjrTG23kpPln629kYj1MXPKRP69yLC421MT1OOWmgv42KtZm4q59OvW8/jYqtrWJ+83CcZ86Nk+sm4nr+Hr0JfrbqNgoE7dT/JTHHVsi1tXEfVWd+KT+VinWz8T9sKRL0rGVm/O50R6+oniM/uZo6vD//82JsQ841u0nnfPyZePjlx3zim1n4kL3nvdLx4a74l671zPTsaCY/b4Ljmhd5VhUzOb6roVXXOtYUszWdmH+tJP192uxgSZuTK8XW5pr17sk3vjmaMfyYnubuC937TFYf8MV62mstKL0rOZMbA9jkw9beoBjPtlAhhlb9NwDTcf2F7PvMvzro3s4FhEbaeIOe+oX7+jaxdqN9Zxx5n917WK7GFtw5F2zdX1ig42Nahtwr2NlsV7GPngysI/+ti22p7EvYkNud6xdVrqjsQdeuW2OYwGxDmMH7fDFn3R9Yj5j158+aDedMTH7ng/2n7y9zpiYre13D532rq5PzM70MSf2azhWcsU9k6mfp7UVG2BsyWfLL3WsKWbzec0t33XX2k7o3IM7FJdNc8wvZmt0332/v0/zImbXd9TBC6/WvJi4Nvl37/ff+InOg9hOxk5bffoRjs0W29RLG+3V63oO0JyJ9TFxtw+47G7HsmYNG+y9+UO0l3Jiw23c73d6zbHnXXHLj18+XvcesV1M3H/Pvau/5lNslLHrfe+u0ZxN7Pyel36xj+51QbFxxlaev3CeYwmxbY3N/fVLb+k8iNk13L30ucu1X8R6Gdvn7ln/cKwoNtTYrONuP1PnQczW6PFXXpitvSQ2xti2c09YpbMS7pyzLqFBRd0/xUaauAErBq/Wc0yszcRV182fpOeYWMDEJU6eOEHzImZ74qHW4c85lhQbbOKm/O2sF7QnxOz6ZvTf9zztCbHexn5+yYhvHSu44l45aq+5mk/Xe77w38M+0py53nPiHuFjHauL2Tq890z5e8c8k/Tc3GgXPbd0uuZabE8Td/OKZx7RfVfM1iHe68jXdf7E7Pp6r3lP6xAT62msbdjwGzXXYqONvTzr4hc1Z2IjjK1/4randd8V89u6v3r+U7p2MZuXH85pX6JnjthAE3fNRXecouf0gZ3jbup90wLtMzG/rd/cVExnzBXXb0pwL+1BMdufIx66bo7u12LdTdwTx1yrtU2I9TdxnxwfGaP7ktjWtkZ/W67ry4oNMFb9oPc07TOxXsYemHhjF93nxYYbm/7nOz/Te49rfW9/cvV1mk+xfibugNsu173Vc1Dn7/vgl9fUNZ9i+xpbs/ACvdtExdqNXXLLnz7XXhLb0djgcetn6J4lZvus38LX99F7pJit3z1LHxuseRGz69v5pOA7On9iw0xc952uuFPnz/WeA4ZOP117UMzWfeHMi9bpjE3uHHfd6leXaV7EdjW273WVK3X+xGy/vHHRtffq/IntbeIC866brv0iZte3dsB2MzUvYnafSO+wYIXmxfV9ty+cMkXzIjbRxNW7nbSnnlVitj+feOoEPVM9B3s8Y4396VenLtZZEWs3dm1j+Crdr8X2NHZT96879AwXs+t75+z+J+raxey5ucq3fAddg5g=
*/