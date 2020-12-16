// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2010-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_FILTERED_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_FILTERED_HPP


#include <boost/range/adaptor/filtered.hpp>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{

namespace traits
{

template<typename Filter, typename Geometry>
#if BOOST_VERSION > 104500
struct tag<boost::filtered_range<Filter, Geometry> >
#else
struct tag<boost::range_detail::filter_range<Filter, Geometry> >
#endif
{
    typedef typename geometry::tag<Geometry>::type type;
};

}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_FILTERED_HPP


/* filtered.hpp
7RLrwkg3h6G/5u3wnWXrzf3roWXuDY91XvKR7+5u/P/h82+77h8yMXPp1EXdlv52lD39vIZ+0p/lyna+MenZN5s/Hn85YvbTtE8xhv5Bb+x7PRMT99cPq1hneNFmnAtvI/o9dk1cHf1l3Butpl54cvDNboxT10r8t3/2zpd/F2o+8WDDEZ8eStw/l3m7pP+ohOeuT+mw5PFnKnRdHp0Y+SN9htvQd+7Nm9p7+IMrl2x4u+t/Shzrw5hX0i3Om9ry0w6Xh1QovfC5SePXX2d+JPFc9+qaptNczv807lNr/dAfaqUwvhH929984F781JTM5qdupAx4ovRZypjE8/KcYq88eGDo7SnXVu+YuvqBt+Q9UfTTjw+Zcf1q2Q8/f6lJ4Urnau9lHz3W0C/yZR/P4B6tp30bOSO9VPnk19jdFv01C/t13OK6cmb3qjJ3lsybSf1KF/8fadcn4Vy3PypFphc++/RDN/GnsPg//Y1Xvjh/uGrVKYc7jRvw/OuXuflI0n/3mHEX183t1qzkldGt/5zT0birQvx3rBpQotRTN+ok3EzIm39r79PMwUjPZPziT+52zKLcnLL5zlJfQL8fvxfq72lGHdbfJLltv/6ex+9l+pumR86HncWfFGM9IeD3X9Zv7Mf4f79m/cZf/d2a3y/4f0tbNQ6WRB3R35VQa/V3W9S7+ns4Kkt/z0Vt0t+voLbp7/Worfp7O2qD/v4BtU5/X0Ft1N/F7LTr+rs6v9/W3w34vUV/P43arL/bof+O/l5jJwz9vYPfb+rvi/zey+802Jbye0DT8E2bby59BP0W6N8I+L0iIK2iYv36kQG/PQG/IwJ+59bfLY264v8t736O03PZ7jjf726ocP2dioqQ3yi7vN8g8ZR7q/T3cpvcQSjPUgo/ryEny+lC2mz4AGocKgKln6Ey8jXDYFuYB7aDeWEnGAOTYX7YERZV/WsatxXqbwf1141qgxL/GNAWhu3gg4YdKP01fEjlOrAzbArbw0dUvgaroqIH+/x3qf9OVCn1v4HGuyF0wkYarxaoYuquqroLRyWpuz7YywVTYSzsq8/XHybAfrCiymb69VL/CodIv9XE1+AaGAlfhx64AXrhWhgH18NCqm+mX6b6WzxE+l3W57sCc8NrGl9k8e8qLAJ/13z5FRZT2Yz3vnvEu5rGu7rGsxbMCx+C8bA2LAhraLyRxd9eqKvq7xD1NxLVWf3dir1ccAcsAHfCtnAv7AL3wW5wP0yBB2A/+B5MU9kMJ2OIL5xxIcL5ScO5qOFcUn+vwl7w37AP/AMOhtfhcHgFjlTZzIdiQ33hPBQiH5ZoPryi6b0CllC5HFwOq8GVsDpcChNVvgbTUOnqfwv1PwrVXf3fpv5vh2Equ1WuBnfDmio/DHfBpnAPbAZ3wOYqm/l+XMNrECLfn9L68jSsAqeq/9PV/2dgEszgX32Vr8F0VLFhPn9nq78eVKr6O5r0LAvHwSQ4HjaCE7R+T4It4FNaHqZofk+FQ+AzMB3OgKPhs5o/tVHHNdwoDdeFqqThdtX066bp9xiMhI8HpMdZdR8fIj2+V/c/QEP/nLq/AKPgeRgNf4YFVF/9JVF8/uYP4e8DWr+KwXBYHLphGSjfvoJ5YGmYT/VNf4upv9VD+Fsfe9GwgbYrDbW+NoNFYGNYDjaFD6q+Wc57qb8VQ5Tz5zUd5upzvwC9cL62ly/CgvAlbWfmwQpqbtbXFep/Uoj6uk79X6/+bdD+5m1N37dgIbhR/d2k5X+zlkvsWe37VQ2nXIj2PV3DGQ7D4SjNt9EwXuWyIpv9DGq4z7+wEP1MRfWvEnRB0tQqlw3VXc8Q5XKetp/zYWW4CDaHS6D5HPs=
*/