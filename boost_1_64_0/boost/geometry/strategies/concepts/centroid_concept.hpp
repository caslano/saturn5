// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CONCEPTS_CENTROID_CONCEPT_HPP
#define BOOST_GEOMETRY_STRATEGIES_CONCEPTS_CENTROID_CONCEPT_HPP



#include <boost/concept_check.hpp>
#include <boost/core/ignore_unused.hpp>

namespace boost { namespace geometry { namespace concepts
{


/*!
    \brief Checks strategy for centroid
    \ingroup centroid
*/
template <typename Strategy>
class CentroidStrategy
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS

    // 1) must define state_type,
    typedef typename Strategy::state_type state_type;

    // 2) must define point_type,
    typedef typename Strategy::point_type point_type;

    // 3) must define point_type, of polygon (segments)
    typedef typename Strategy::segment_point_type spoint_type;

    struct check_methods
    {
        static void apply()
        {
            Strategy *str = 0;
            state_type *st = 0;

            // 4) must implement a static method apply,
            // getting two segment-points
            spoint_type const* sp = 0;
            str->apply(*sp, *sp, *st);

            // 5) must implement a static method result
            //  getting the centroid
            point_type *c = 0;
            bool r = str->result(*st, *c);

            boost::ignore_unused(str, r);
        }
    };

public :
    BOOST_CONCEPT_USAGE(CentroidStrategy)
    {
        check_methods::apply();
    }
#endif
};


}}} // namespace boost::geometry::concepts


#endif // BOOST_GEOMETRY_STRATEGIES_CONCEPTS_CENTROID_CONCEPT_HPP

/* centroid_concept.hpp
cTDDdghtQX02yXaYb74qvJL1eBWP5NU8novZjTdwK7NEeljeG2E77B/KoEgY66wK72A9LmcL3s0UruA5vJczeD8X8QHezod4Nx/haj7Kp7ma6/gEt/JpxurlWtbms+zCdRzO5zmSL3ImX+JsvsKb+T7v5Qe8n1/xKX7N5/k9X+Y2xsdWCe08+alYn29slfPCek9jPZ7PnryQp3AGM3kxL+AlnM2ZnMtLOY+XcRkv54Ocz6d4LZ/nIr7Lm/ghb+ZWWka8nSc7hO2yTyzdkL9U268qR/AgjuJgnsEMjuMlTOcCZvAWTuKDPJvPcSrf4TRu4QX8Jy/iPmEMuAqcE+rL6mKhXWRoJylf+jtQDxh72SeVm+WzHqfydJ7HVE7jmZzuvym8kFdyBhfyIi7lxbybs3g/Z/NJzuErvIxv8XJ+wrnM4hXcynn8mX9mrF7NZ0X+hVV5FVtzATvxavbkNezH63g5l3ARb+KtvJkP8G98nbfwXd7Kz3gbv+Ht3MY7WErZ3MUWvIdtuILH8V725v3sy5UcyQeYwQc5jQ/xYq7iPD7MhXyMN3At7+MzfJzPch1f5Ft8iXsUt79wb77K6nyN9fgGG/AdNuO7PIrv8QS+z/78gCfzEw7hpxzLzZzEzzmFWziLX3Euv+ZCZvFm/p1LuZV38xs+wm/5JP/Bp/kDX+KPfJc/cRN/4SdUEY39Cv7AYiyiXpZlZZbjkdybbbkPpWksn9CeNLQvXS8a+/fY8JvdKuaryKqszf3YizV5Kg9gKg9iGutzChvwIjbmNWzCpTyUK9iMj7AFn2VLvsqO/IzH8Dsey+/ZicXl6ThWYxfW4/Fsyu5swx7sxH7MYH+ezwGcw4G8ioN4I0/jrRzKlRzGNRzO9UzhG0zlmxzBjTyDX3EMf+RYFlV241ic47kP07g/01mHE1mPZ4Xyby2y25eyTZ4+MBuHf9exffdkXdZiPR7Jg7iVtcX08PlGIrYvF2Wl8PmuxXPnWx3mO3A782WF+RpsZ75mtQtf3vF55hsS5muwnfkW51le73zzdcuzvutrh/XdznzlD9yx+XqH+aommW9onvnSc5a3nfmW7+B8WWG+Br8xX9eioS1YaCO2Pt+YhF/saf/k37k/t7Iuv2V7fseTuI3j+APP4j85h79yPovs5boBxfgmi/M9luBGluTnLMUvuQe/Z2nuLy97sjbLsT335umswImsyKtZiYtYmYtZlfezGt9mdW7kAfyetRnbf+qwJg/mUTyEx7E+z2ADjmUTZvBQXsJmnMXmDPefoV2ZdQrXE3nvP6eF8pzO7jyf/XghH+YMPsZZ/J6X8ifOZmyhcygd96GhDRmvC+nE6teakM6p8lODg1iPg9mdQzmAw3k6U5jKVKZxJP/MUbyZZ/BRjuFjHMv3OI7fcDy/YwZj65vJspzMRjybHTiF/TmNGZzOmZzBBbyI8bGfQ3ssfiTW5xv7+YSwXt1Yjz3Yhj05j314Nfvyep7IezmAb/EkvseBjF+XhzZUfCXJdXlWmVD/mV3/WY/fsh2/Y3/+wDP5I6fxJ97IX7iUv/JuFt/T8Z4l+CVLsrx0S7EyS7MFy7Ar9+RYluVEluN53JvTWZ6zWIHz2IBXsxHvZWOuYxO+wKa03u7rQ/srfh7Wu5p/rwvr/XBpY7XxUTbkY2zHJ9ifaziIT3I6n+IlXMu/8Bku4rN8nM/xGb7ADVzPbXyJNaT/Mg/mK2zCN3g0N3AQ3+Q9fItP8m2+zne4ke/xY25ibP2UaWhbZZuF9asVK/dwXPs0rN9nbMjPeRi/YCdu4SB+xRR+zZnM4uX8hov4LW/md3yW/+CL/IGf8kfuJc2fWJ6/si6LlpEui7Eni7M=
*/