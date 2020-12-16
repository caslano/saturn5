/*!
@file
Defines `boost::hana::at` and `boost::hana::at_c`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_AT_HPP
#define BOOST_HANA_AT_HPP

#include <boost/hana/fwd/at.hpp>

#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/concept/iterable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/integral_constant.hpp>

#include <cstddef>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename N>
    constexpr decltype(auto) at_t::operator()(Xs&& xs, N const& n) const {
        using It = typename hana::tag_of<Xs>::type;
        using At = BOOST_HANA_DISPATCH_IF(at_impl<It>,
            hana::Iterable<It>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Iterable<It>::value,
        "hana::at(xs, n) requires 'xs' to be an Iterable");

        static_assert(hana::IntegralConstant<N>::value,
        "hana::at(xs, n) requires 'n' to be an IntegralConstant");
    #endif

        return At::apply(static_cast<Xs&&>(xs), n);
    }
    //! @endcond

    template <typename It, bool condition>
    struct at_impl<It, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    template <std::size_t n, typename Xs>
    constexpr decltype(auto) at_c(Xs&& xs) {
        return hana::at(static_cast<Xs&&>(xs), hana::size_t<n>{});
    }
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_AT_HPP

/* at.hpp
LhbfgWenuMho1NmSl8z+3yWyDitI93y0qw6KbucQ3WmT7Ghf6Ljmxsv6vsB9dRr3derYiVnjCuzS3SW61zcFdM/HeEL6pbKHq9blPEG7xxO2ieYzHwQ0z8d4woCO8i5oUFzt7GOb639Et+B4QPd89HkTOsn+OkG6dvV5zf6faL4VlMZ29z3N/l9nOcfnWJi2WVTZo7tMdA8Hxfl8lI9nRPdYkK5dbRrz/K8ucu7ZkYCm3f3Ok6L5ZJDm+ep36ni7ukp7KigMdvf9DopmhzcCmnb3/XJln/6ywwHN89H32yW6K4J0z0ffLyNBzpV5J6B7Pvp+O0R3RZDu+er7pV0u44PvBrTPR99vE7qKhwK6dvX9zPe/usn4SZCm3f2gNaLpC9K0qx/UJ+wcgAFvBWnSD7KzTFwkmsMPBDTt7gOdFM1P94tm8WDP+egDlXWXd1VN3fNTxx8S3dNBunb3gQquFN86LznRvDFrSlbemBw1BWaT7m7RzWzSuvbOqer2Re5V8r7N+6Kr+gR65xG3Tw6Nkb2GrQ2DWf9JGHZGC4PFcTf7fz1kr6CDzXXtyl/bRDP542DNGh+vaBqbaNukOyBR3rk+GKJbZfY9bdLdKLonmkJ0PRVu3lCdxzupFusO1uOeV8v+SyHpXF1bPE+d5kpV7z+psayoqtxlqb45/in648+tb6m2Of7ZU965+SBE21Na6X8h1tr07qn7gaJ56qNwTWv1dL46K3rbD4boBd6MtDhf6fu6qJe8VxSuG3Jv7dE+LdovfNBMWx0MMqW2otjts1Zbp3d5kuyR1Cze3tri+W7Ly8vksL3/dzbT9VRX17p9Krkt1jbPv+4t+2OFPMM+N7fZKKwtTmv9/DaJbsqbQbqy+bzbpuc3s4+c69Rc01I9vR9co+jtaArRq6Itu5jq0O1Wm5GoXXeNv3rc1VbnsaG6zXeNjMmeOywSDGv7h2b7T8JQGJLXqkqqvR6XcRusjbt5/ndfmdcPeb54UdLitDbbP6L3g+C2njrhyKW2vLL6Huv2QFo/WWMWnL5ShoQ2B6zV1+VYvehnnFPfWm1z/Vd/qTdC8ndZDWeNVlrddzPXf4nmqRDN0grd8rP6Ppvrv66V9vX+YF2e3wr/TrVj3XPZ1shqbR3nNaKdFlF7zFwGlyzV1XHuMED2UQvVPS9tkpWive5omLZq+zlran3uokqPPW3suIGyd8LBEO3z0h5aItp5b4do294eOiO6PUPv9XlpD3llr35XM23/PscMgNmke1x0Z38cSbekqtbiNopOa9cgqTMixrd4sX9a3Or7bM5/iHZeBG2rx0N0HVmYIvP/h8M0zQ161YCQk4Ullurr9G4S/ZHh9zl44bvFcdfpnZ0qZ11+GKadqhphlmrqfN0gmvM+bqbprnB6yq3OWzqd0wfLHEi4booutK2vI3Ue2yHaT74Xrq0KTjWaXMNgo9X65vzPdXLW/8Eo+hbrmu0/0X3kaLiu/e2SvmlytmezONvTLtF9i/Wi2z6kDGOfMIvbIjqe8UOkDxvyDKtHya9qefqa+9+J7pmQsS+Xp9RdXWO1pjn+JZqFwWlLOV3OFCZVhOW6Oq7eobLvXUhcSyq8jOla3cY063/RdIWUV7K5Y63PW1XttlTXrP+HyRqi4DGR5ptKWqptvv8l2tv3N9f2eIuc1SX2pHXBcDmPKYJuWZV9+Xm36G6JoKueYJt09VkAdSHjEc5yj7PalvEIrbtDdLt/3ExXlcxW6+rnN2WktKVD0pnNQm1oV+rnaLNo9vw4TDNVJr6q/L1Ua9vwur0xYJT0jZtrq4FcEbc8X2v9zaLfPSR/TcvKmzB+RlHumLwxk9VgNoWntWXYUH2/06U=
*/