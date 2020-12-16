/*!
@file
Defines `boost::hana::accessors`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ACCESSORS_HPP
#define BOOST_HANA_ACCESSORS_HPP

#include <boost/hana/fwd/accessors.hpp>

#include <boost/hana/concept/struct.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename S>
    struct accessors_t {
    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Struct<S>::value,
        "hana::accessors<S> requires 'S' to be a Struct");
    #endif

        constexpr decltype(auto) operator()() const {
            using Accessors = BOOST_HANA_DISPATCH_IF(accessors_impl<S>,
                hana::Struct<S>::value
            );

            return Accessors::apply();
        }
    };

    template <typename S, bool condition>
    struct accessors_impl<S, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    namespace struct_detail {
        template <typename ...>
        struct is_valid { static constexpr bool value = true; };
    }

    template <typename S>
    struct accessors_impl<S, when<
        struct_detail::is_valid<typename S::hana_accessors_impl>::value
    >>
        : S::hana_accessors_impl
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_ACCESSORS_HPP

/* accessors.hpp
h3MRTpPIN6VDf4FpBiPfzXXZEMxx/G4BzBK3m85wPvRg939sfJYN+7DaO9uSd5wmfbiM01D3YVdC/+uVx12nqefWH6dp+o7Sj9Q/yKJFXd066/Ku7rWO9R73Gd3cdFU3t457WTe3TrzP4/6Surv3beEudP5tgGMvwSZIQ04PW/aFF86r7tffiHn2EfJPeOd4dBrpo9V9sI7RZpKeZk4wo/fVJVG24IVSHHywws1Tf9P1vaca0oPMrmZj3QNkOto75Zb6m0R/M0GXkz7X7G2mMI0pjI9lQZ7p4Mknz0Qz10xwyTSEpfJpb7xB/3E6Lw3/8v5pGfnOMweajWz55vH/Iv3rvHYkybqvbTH5hpqW7j+ddI7Z1Tiq4Q3xhHcw3rlmzzqrY5D7yZdgHjL66BrN0p5y1jXG3ZW5epeLWy6FgEsZ1kCzlxlHnsIQ40OVsGXXavL0Mjubpvcsqt4/dow8T3EEMc4o1zspW4ocyAbC4LeNrYCtYdrIW1iz4k+zFyve1ise7ql6xQBLr0AeUHYUl5VE7xmMcV70wfj68zU7YZdEOaD1lPa7YY966G3zrCuoZ9rmYcfyj9P5fdqhDHXOv1DPKbrvx2T7/SPzjmlw6d5XFcreujjkD/BG0V129nS03yVFSIPvuEh4z1Id+jekV55Kf4EfGSvJnoE3SJ8X95LZVe9LaNOH7d5Xf+lAHUXTap4PHWStkWDsgHnKGGV0MEd79Rb6meLj5xljBP049BXdWzq2F8d+0GbSXe0b4Wh7CjdQZ3H6WX4KneUd8k01Oxit0IptnWVZ74j9wVOtC6jOkkQ5Zb+hvKm3dY/oMmM1742U/aT8vtfM/kaSOd3M49xXljSOg0zHNCObdibtOpK/V9wM1KTNZjbjWxhd560udIyDtjG+rjoG+Q7pgLhrGcfyz/T+vrd9/tz2vwYpX8Q5q2PofzbmW3rWgdovRM/adQn0k3zRs2q/OIWeFThjPes3/PYt1LM8ZcI0HUDc5fmqZzXz0bPId1W+6lklHj2L37ZLw5nmp2eR7+N8S88631fP+rynrWeNQjhN+c1R086hZ+Xgd3uYDjAdYTrBdIbpAtPVmg9v4Fx4mz7/3N4PP12rNIauFfboWst9dS3/OfFjPd160hc93XpVSi+3+wEP/UEvt950rJdbrxrS2+2e2zv2fRYvzjP4F2mbPQVXIA0FfVQuyxY1p8yJ2njmRcTPQNWfbibd0sS8r/O8d1UJrwFRGS3+cOebrAveQLq1+X25d3QZZSTaRmGZ6FyWnz6qc11Pup35NNaYPHMq+nbnreRpgXBN8iwN1W9zW8jT3NxmNHXsq0fEjrc2t5InFXcYBERHcc+T5AAHod4Hgd3T7bs1e+B3T8dYohd+9xa6T/qZ32cdqfeZZ9nzD6zLqhM4y8h7F4WWgd5FgTyGPfPYc/e1PS/xIr8bd7dK395HdPO9xQb/tsBkwlwNcwX87mTaahdV8iSaEfMuszjD4svSeecXSVcZQxGHb9+u/prr3MTzpNfgxjtT5ddZ6ac/e8N5mBh3Tw3xu9tM2s6RBXIO00QcgmuRN3l9+d0VOOGWj1vuaiqrcXdkVbWe7+6YKOfdqHZq+xF/3XVecQXpvvIWiHs8M1H5O6o+VC38nvc3KJP79YveATaS73tY937ztj2dKxlInktdfXK4r5wBdfTJa2jX2rTD4Ye41rFuIU885wD3F8v7SZF+o9HlKY0x/ZfOScAevIYj9hxg7DtKmwFfY9jPxLqjgzrX+3TfhjowQueINvWz7/jOljS9Pd+6X/wSXC7eiy99xHjng/n3BMPsF/MO8WbAnXRvY78lgvBnLYiGD6WgOwJPTovEEPR/S2Q=
*/