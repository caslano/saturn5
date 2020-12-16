// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHS_DETAIL_DISTANCE_IS_COMPARABLE_HPP
#define BOOST_GEOMETRY_ALGORITHS_DETAIL_DISTANCE_IS_COMPARABLE_HPP

#include <boost/type_traits/is_same.hpp>

#include <boost/geometry/strategies/distance.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace distance
{


// metafunction to determine is a strategy is comparable or not
template <typename Strategy>
struct is_comparable
    : boost::is_same
        <
            Strategy,
            typename strategy::distance::services::comparable_type
              <
                  Strategy
              >::type
        >
{};


}} // namespace detail::distance
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHS_DETAIL_DISTANCE_IS_COMPARABLE_HPP

/* is_comparable.hpp
05Mp6Ll+ARwnVjyLzR1pwLs8n1r6IAn+VQsFF6i7nPivB3zRE7H17XX3DrWWzwLOerLAfZ936Mar0Z9fmctuLbWn5viZju/YHh7BzAj37AfXujfXR3ziuWFeT9/c2SwmY9U+Hm5+GWeL/9c4K4zHGF9fpD3PbxH/l31pxzYwehH87KI/IuzHHBAZam2D+DewtIFYHojjOWNnETvL8DDouDV6MLeYj+H5bcrA23K+tL2nM6jUNIfXjFe3MzvSrM5bu2WGubHc+x0cVqOPfuSlJuHZvIQV6rDZaHoIpmR4z+/jrbX/QZydE7XLAgejcLn5v28ULEhuNrxhX3Cz8c80+zqc3dWcJ0d7cfTBDvqPvin23kxJ52e5H6MjaUP1OL4AT5v3uCWu3FfAI/8JhsueQQ3grYby9oI3Do+OwcNSofD5A73nc0sNRMQ8o8LjrE7DnFpAN1p3sidqCs83q6ymaKsEMHPKaPPTMnXwPd2azn5cN2SE+aYNToD5V0fCbGs/l8/MdFeu96iPLfhwMMzTf6tq0YvFeJ/WPGM+36yc+j8Pr574/hJ6l5bIgx+mmGcr3dZ3dG9rfm+CcO+B08Pg0frtNIJ8T/wb9t1Sn+/0PaBL+ScvbShNH8IXPKfXvoEbj8w1auuF9U6GIVvGmqddN5P+bAPfdpu7EvOmNhbTM4eclc+jaa2vHd6t/zUNOdBzwryAIp6rPjnc2Dtbn66ANXpqXxV+m+uvPsNnpvlGmjmiXsDLCWpjnd65pf/S8JLxVqCFvJitN+GoHdawCVfcmm4upZUrFcJh5emgLepRz/Ut7N7b5Hg7fz8WfS+u8wLW+dZ8dsVZyiu6lS4ME6+cr8Uot3qmddbp/ayt6QRe6eaJ6ud4zHNeAXzpGZA51p01IFcw9ym9aBavZS2tXf+bTTi9V4CXa8Yejq/b0EU1eRuF4K0ZZQBM2IEXMkfCkk703TF6S6/MjxBL9bEnN3xvbw/4pkICsR6Lb79S349ovSOuLdYV8eJa800c+V6hZvrj4RKdcX1Tsc7tmcSc9HsumFpDzo4E6AWYqiZe9YSl+COuuvmYHtn4pz1uNAfaZ4eV4k3nPhGfPXJSnAZKTgOlLqgO19Lqsc0saehsuUrrbPG2+03twutpR+fzZ6Yn4wvxhka5f4/4NJk1dekEq+rS4QvojAaeuelhb7Dtj5OwvKH/h8OodzE/604LlOXFHlVHtPJzXLGsPy7hB3zEl/W9wBy6O2sDfkQZtV3IfcfDdb7AoLZm4u00WLIAvOYtDaI9efKXm8Cc9eqHzqtHl7Y/wfvPYF7Ab8No2nu0dMUfcVdV3mF5++MXDykoX7yiqnBwPu918HuxScLPpeur0QLxxSHbH3wMc0DGYHMXLyB1IesbAwd6yiVM3R/jXdOwL/9Ln5ht7vPqVtvXhNTwb46+8d5ScGiJfTVYz+tqgZfphmIHYPFimoqXnuoe3sdf/flgVZw9fVoQ1hagZ3DRTHU2QC0cyU5XfQa3avPXHpg57uOLfc7XZ8qR13xAG0ScNCdYU8lIsd+ul8vSlqdoN8+M1E/vWdXRdGIdz5JOoiuyqou6eKMuTZeVj/Ib3c+L/1lfbbXG+LTrF3p6Em1YN7ccXQtyf9pUDQ2vxa/wrM1EvRK4ACMX0srHzFvuX+i5OSYLrt0MW80UG2KeA9NbhcX10Wl75ZXtLfrv33ltp65fzoCfOGKnz1ufo830w71o+ze7r6+qZ6c5V63oTLMP/V1cfeudIJox9zO8BWcK5lVTba1hnPqbIne87Wxr9QO+7faMj6Fmz1pPOntpxVvM7PNherLhP/iql575VS9XMifm4rHbU/Uaermif2FLmUb0aXc=
*/