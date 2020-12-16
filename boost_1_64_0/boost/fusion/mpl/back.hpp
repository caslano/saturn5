/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BACK_10022005_1620)
#define FUSION_BACK_10022005_1620

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/back.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/iterator/prior.hpp>
#include <boost/fusion/iterator/value_of.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct back_impl;

    template <>
    struct back_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence>
        struct apply : 
            fusion::result_of::value_of<
                typename fusion::result_of::prior<
                    typename fusion::result_of::end<Sequence>::type
                >::type> {};
    };
}}

#endif

/* back.hpp
knlu5MB1cI2ovLNrDkxnY7pfuU8hHK0N6qy+e2E8JtP5fi8Hh7cF6DxNwUWxG+7Yn8qhe0u4ykJ0/Z7s48Dqbd5pHapyeGc7E7eDxgb12dNuE08bOEhBxes7TBxl8vWqn3mnCx6QGXaF+R0+zx4TR+pqq6hQ9nCXCx7hXv3+s3MMWL69aZ0w58jam+v5sqpNLjg2p5/Tjm6WMJr7iDJSzXs2XM/WKrgtX/celZ28b+I4e1R06LXuNvD0YrXqjKSvI1N7Ct1jF/3N6/iFdj7oOih2VLGGE0OzbqE6wvfmW9X7kDrEUS8I07786B/DXTjrOAM39aO4kdVmHPf7cnB5ijLAqaeNDXi1iqM5ePp1cXp9VScWwJUT1qh4MzMfx711vZ/oj+GytOvMtSNcTKWtxaiTL1R4ETxAs/lsd2ygI1vavY73NH35rGIFz5OuKbOO8PQ2FW7yf+CyTYXrm/3juEhY19Ambr6EK1UeO0fjdSRh1TPOxdVc1rV2Rzh66wo38+O4LC303ss0bmEJC/2uC0eO+rUUDc4eEiPcMGXBRr8kNbEdZ+F8/bCPjjX7umDQIL/wIYx3NObj4Et1HpVww6nEjXc/7adgjgpm3+dgvntwf4XDyRqZQBZD71/DWdv+poqRwx1gwtzf47P0vs9saqxR9/h+nr2+YG77lzFdz+jHcmAcQuh+/ykOzP29rGSDum4HAecNhmyYNyo1EESNc8LQKSau/FKFwQvrVBeckwA7edXwqAHX79rS70fwNCp4Y/btUsZTETyHo+qswnjZP4WOw/7CeMhAx6hQQRw64+F2s1N4sYJ42UaQ6fsSeXj6VMPlIwvh6XWV3MRpCq8paHwvJum+7tID7+kumOt9TRm9rlwWt8XZmIpFZyh4IXZovmm8AuQb77LIxWtFpzjLW2acw4vleTg23Zr3TQXh7crp+u5scx4eDzuDaTw7kWxxcOQXd/iKo/kcYlrzTr/QU/kVxUe01sRzXvUlmhUtX44VwBfNq5xTTh/ev1C/6SOo/MtHhXDI6oXG8fyXsbMAb/OrwviHO4QBwyG4Q9Yx2NB0azcKowttN/gjT9omaVfWJiFJJ2hxh+AOxR2COwR3CO5Q3KG4y7n57veec+65KfDwPIO+v1w/956r359jjD7TWLzMlYbMeaW5Y+U9Y/sp12daC03uJ3NRnQpAvGd1uYBxhFibLl0x0BECjwvzj78GM3N3mpkcn8gW86nCaPdRtP/NGEudLK2HuCn+AsYly8n3cIgV+w1PiLI+bu5nihGO2qQHmetGONe5p9XI3PYozlWT4DaeaDl3pn8IC64X49brZXeIToX3JMu1RX7RFi3nbwFwu0+ebBj/uILjxHgnOBrxG2srlWEPgjZ92yuyTrtn1FQw40R6DhoGMzmM24clU1lzzIK8J3pU6yIe9llnRjLu/97qlqLv6N3dsGbvYnCfKBMPr2JZv3zH+z1Vy1D9rZyWd3aXLEM37Ni3PCn1pUWn7+F58a1gG6cst19wmNcZjineW2VGnJ/lObTVqZmvUkMSffVpyXRasfLO3X8k4/7v3jFR3lsbim3H2kPh4SOZzK/jdvwozcbSV3xMjImH17vKbmbpfC6u+Ulf95YcXtbHYD34Gru1hgCY2cpbxj91UOZ3m0Ucy9aukmdJPW5X+ZfGmHi9bL9WsnG7ar4zxsTDK37QsN6h4HLof1Qy0va4HAafsAx11xzPJ41OjZjasnjHbUMz0n5hK/mBZch+ud1eC3Wmn76Q6wPXtgy/YpHshY3v57j8bGhteFwqPcW0F2tLsp2tpYaJ83wHhEa/9w8N1NFGH3IppdNOA/uke6+kNGrm7AdeV+SBEi/y2YA=
*/