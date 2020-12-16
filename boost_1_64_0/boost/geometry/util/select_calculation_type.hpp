// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_SELECT_CALCULATION_TYPE_HPP
#define BOOST_GEOMETRY_UTIL_SELECT_CALCULATION_TYPE_HPP


#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_void.hpp>

#include <boost/geometry/util/select_coordinate_type.hpp>


namespace boost { namespace geometry
{


/*!
    \brief Meta-function selecting the "calculation" type
    \details Based on two input geometry types, and an input calculation type,
        (which defaults to void in the calling function), this meta-function
        selects the most appropriate:
        - if calculation type is specified, that one is used,
        - if it is void, the most precise of the two points is used
    \ingroup utility
 */
template <typename Geometry1, typename Geometry2, typename CalculationType>
struct select_calculation_type
{
    typedef typename
        boost::mpl::if_
        <
            boost::is_void<CalculationType>,
            typename select_coordinate_type
                <
                    Geometry1,
                    Geometry2
                >::type,
            CalculationType
        >::type type;
};

// alternative version supporting more than 2 Geometries

template <typename CalculationType,
          typename Geometry1,
          typename Geometry2 = void,
          typename Geometry3 = void>
struct select_calculation_type_alt
{
    typedef typename
        boost::mpl::if_
        <
            boost::is_void<CalculationType>,
            typename select_coordinate_type
                <
                    Geometry1,
                    Geometry2,
                    Geometry3
                >::type,
            CalculationType
        >::type type;
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_UTIL_SELECT_CALCULATION_TYPE_HPP

/* select_calculation_type.hpp
OP8svVS5K1x/WM9qxpspe2kH9tfBeDPlmEX1k+M6iXE5gfPjPMdj9yjWe1L93DT8GU9lr020/91sL1Kle8dw/8n5do7rfCbq9RY9mf/4XGW/EMYBP+5jXqXemdT7EvUOYdzaQv2jGddPrOX+6hL9n/3wzuS8oB+eiFV235zGftNehwdxHerXS9n9H5yHMzHvJN2ovg9dzPV2BOct5qekp1d6qvLTlT57o1XqKKP+5znvElR959je1hjuEwfhucifox0+p7+8w3kwgXH8PWX/fQMZL7GP9pRxZDtXuR4cP0u90jkv2d58jscOxuPD9Mc8rpeLPuJ6y/3+pUSu85f4PYrrSj3nzYNcd+Zx/5Cs0kzuC+yJKg5vg3yUtBfL+vqr58O5vp+IpH4lFjW+S7m/4/p8mnH5gAv9k/YHM+7MVPLNXfQ32j3EzvjA76t53piSQj9lemEx58FC1uNkOy/Tv9z7hTvoP3GSQpbKeT2D9pjPcg6us0lch+/leYDnn8Nrlf7LKZ9EP7v8c45LGuMY+7eccTrzI+6P3fvcBotKn1D5Js7ifvAe6sV4UHCF/bif48dxeXUp6+G63se9bhRxH7dGpZOKaGfq04/+NjKU6x3nQfSDany9KR/p3v/T73a8yHg8Vc2/DZzXAz5AKvlepD+fZjx7Qq2Ty7m+r0tU43juHj6n3+37hOMXQ7vvYNz1Zz/XqDRzGMeN/Vt9iO26909IPaU+riPJ6ZwXD3Nfeprrw2juC6/SHn2VfscHcH7O5nr3Q54H6U+ZHP/V3GcUcD0aU0J7OTjveG5fzvb6LWGcCeG+iefl+De5DlC/6HN8zv5m38l+16p83lxnVrr3bd/gevEDjlOuSvPoT8cZT3YyDm3gPHDQTydx3euH+dtb7DyU/sd6+yRzv0g/9cvzVOP9NMeF+1dvrgNHN/NcPp3z00fVc+J+lW8K/MlTyo2mnTZwXtm4n+M8LEjn+vol/SGYcegcz9GMM9413Jc9Qvs/xvhtpz5c30/DH/2kXq5fsZ9R/39xvGm3C9wvjPvY0/IN8fNi6tWf8yeO+4anKd9LP32K/nsH/ZzxzT6K4+HPde0JxvX5mGeS0g5baJ/4e+h37nsarkNb2K9JnN9XH2R85P755Kdcd85xXNn+5jnch+TzvPUB9XXfZwzhPvwvPG/RzsujlH6D6R/rknge/SH15Tid5z1OJteNWPk3VkSvKHyX56n0X+7Dj9Fuu2m3+dQntpT++iLzD+L4MH4duIPxlH64bj3vp+xch0oZX4cyrmziPukXjMfp3Jezf+uW0L7t9OvfcX0OZbzn/NlHu/sxbh24lfsKX65DL3F9stHOT9GvqUfBeJ4r1rJfjDM7uA46ZtCuM5S9J3IftdzKdW0w17MOnp9KOL7Ud5H4jaTTGZc/5vnpVcRB+R6rng/Iof14HzSG6WbmO8r0PM8189+ln4RyHNjPk5wPl97gOLTQfownyzFe1/5JbvrlzrlcN/wZZzlekxgXvOmnG04z7nH9PtOP522uxyOfo5+wf/ZpvAew8znvezy4z7FnMj5yXXg1Xu3XsmNUmof921jRB/tvr2vnPc6DFO6z4+mfXE92cxw3cz32yOe6wPVr7yqus/TXE/SP7LXKHgV47infOZ+yX+Y91N95PmE838V4Fbuf4+2+TxrOfjm4roWw/EOMO9wfnWR8GUD7juT4j0llHMpinJjJ+7H51IdxYivXv/iNHM/F3LfR/y/T/46zn+u+on/DD+8We3xIP+T9aizHdd9CxATxr0FcPxgnEjZzP76JcYX7ioQZPO8/xHuExzk+HI/BZzge3FePm63yT8rnfepHjM9fsH3egwy9g/6yiP0=
*/