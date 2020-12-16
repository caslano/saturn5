/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DISTANCE_IMPL_09172005_0751)
#define FUSION_DISTANCE_IMPL_09172005_0751

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/minus.hpp>

namespace boost { namespace fusion
{
    struct vector_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct distance_impl;

        template <>
        struct distance_impl<vector_iterator_tag>
        {
            template <typename First, typename Last>
            struct apply : mpl::minus<typename Last::index, typename First::index>
            {
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static typename mpl::minus<
                    typename Last::index, typename First::index>::type
                call(First const&, Last const&)
                {
                    typedef typename mpl::minus<
                        typename Last::index, typename First::index>::type 
                    result;
                    return result();
                }
            };
        };
    }
}}

#endif

/* distance_impl.hpp
Fft3Yy7+z/zY7Xi7C7/l84vn55TlFpl05nLz72Ipr8iJyKdB5r6Cd+z6Ckrk93IE2VPWHDuV7fZ818E6VsAyPKAF9wn0N48JyCufJWUxapmlbZ1p2yyed3yQ8eQ66lGROERtk4esX9BfGbuNXbGdH/W/V9s0y37MgptL82MWjtqNWejo0rh9Xi6O7aOfgbKSNnK/Q7v49Qtrn4eUHcT2tI395VnL9qtjDri/ovRb+KJe+jYa9kMUFYFD/0ehw5wG+jIa9IdUSl+IdZ/5PLefT7/I3O+S6Njv4rjOn/TndGgwTiHPvG1Kw20bjFPgfDcZ+201x5APrVywKnTFllnve/5y17dBvlEtjy1bGis2FXNeaN7PAp9g/WbP1ff+uOih5bsv+SaDeMxcPu6hjWPf++3uUV/dcU31qXcG3MDf0k0pNxhuzfz45Z+8Mvad5Z1xo/eztN8ci7636cO2X0asan3qlENRMUv23mmJRQ06+bzI56ie3MoSa5IsMZwnDsX+OAXZjs+evKflvV6PIWSjvJ+zqReG+RiHs/AcnI1X4hysxkLchGfi1zgXXdlHEZ6G89AXSzEey3AGmnA2lmMhVuBZuBDPxkqswkX4EJ6Fz+ES/BLPwd9wKS45hX/xz+V4Lp7KCTgPO+P56IkXYBJeiDPxIizAi3EZLsfL8BJch5fiJrwMH8YV+ARejrvwCnwJq/AVvBIP41V4FFfJOI/V2BWvRtqoa3edu86fHEW8a419s3j8LDmV+HcP+QjZNYy5GuSjZCUm3ke23nd0GbHxerI1Ro6POEWXFYHEyneR68hexMzbyPvIB8nxHDPzOi2G1pKWtKQlLWlJS1r6J6aTfv2/IP+Erv/3ht36f3dJ/PCu3P/vDXQjRq35Ro2fOXrD9f9SjxHXp8t4e/v16bMc7/9nFyfXO8TJc5ysNx/kZP5AjBqbFhU1vuZfJLGz/RyDhn0H2TL3oZDcnmwkf8wxEm39GcWcwuL5Zcdz38N2ndy6MJ7iAemnkDITGqOUssL5hSbLGIJadp7FsUfy3yZZjiXzBNS+hcLFBQ2vuepdWh4Xt3S8/2vuSvlT7bpsy4mK2pHQOmTwgt7DezYV57Y8Xm5pnO5vUspfvWVIh/eHx9z8ZK/yvT9f3ebDpvsNiJOJC+W9K+/peuxAXiJ/rD5yrTcQY7EvTsBg3If98BCG4Hx2EopLsT+uwjBcjwPk/oIGjMBwvAcj8A2MRNrDx1TeT1go8b47OVPa05F67dEDu6EneqMX9sMeOBB7Sju9cTr2RiP6ILFyi+PT2mPEqP4RxxenHiX/TJzqfb0Wq2pJS1r6nb27gYuizAM4vigqqBi+o6IiomIiLm+Kika+olFSkuJbqCwIiYiwKCr5lq+pyZV1dKlRaWlZcWZlnhWVlpVdluVheUWXlZVdnplZWd1vdv/M7MusgFHX3c18+vddHuflmWd3Z/Z5mRljMiZjMiZjMqb/j+m3qP9H1eHz/4463v9f6v/vSf3/KDYM5sVXjvX/qKoGgF+1/h+h1v+1tEhJy3VIi5K0wktsJ3BrF5C0EK3tIAKkTq6m/e6vvx9nqy9/v2tHUG/f/mU/Duhb/sCOVZPt9eJik7yn8l4X42UEdUenZ8a1wAHYEsdia6zANjiFhdtiDgbgYmyHK7E93ouBuBc74mvYCY9jZ5wgz5A7il3QfJHr3wN0xhTHGnVMYzImYzImYzImYzImYzImY/oPT796/Z+oy/7/vzqM6a+Q+n/P+tTJMASVC2BzB6v1f0u6LStRNegDl3Hk9nvdTbNOk2vdder4STp1/BTHOr7bOPc81/597fp3Mtqc+At5BpfnzFmt4Hz9u8w/IV6bP0w=
*/