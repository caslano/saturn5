// Boost.Geometry Index
//
// Copyright (c) 2011-2015 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_IS_BOUNDING_GEOMETRY_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_IS_BOUNDING_GEOMETRY_HPP

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

namespace boost { namespace geometry { namespace index { namespace detail {

template
<
    typename Geometry,
    typename Tag = typename geometry::tag<Geometry>::type
>
struct is_bounding_geometry
{
    static const bool value = false;
};

template <typename Box>
struct is_bounding_geometry<Box, box_tag>
{
    static const bool value = true;
};

}}}} // namespave boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_IS_BOUNDING_GEOMETRY_HPP

/* is_bounding_geometry.hpp
OVd7/NjvIeRtj5y67120sIHhHnX4lut79F0d0PONN6efbvn8k9721PG2l4+3vYj+fXvw2O9F5G2PKG97EXnbm8f7XkqnjXEwhJ+616/x4fnbV83xVz+SqL4JKME9gTIJ0n87+w+lsjdFA/7ei/tPuP9B/m7s5+yDxBjx+Ki1JbT/rm5/93L7O17/rb7jVfG8wd895O9PiLOz/H0BaVJ7ZjhkLSU4VK7FDWT+jkP2GGkEU2FzOA3GwTTYFmbBDjADdoKZsB+cDi+T41/BeOSknMdfzuOHqClxsleBwUHQDw6GZji1HhEIsAnXWcJ1gf7wIgkXh4RJuIsR0qz+jpJwK/1d/lJq6a9C/A2vwV/YjTX724vki79AX+VPjUPsEn+zfNkrAc6H7UTvJPqlcBEcCW+FSXApnAaXw+vhClgAH4I74D3wdVgG98Et8BB8HB6GW+F74v9ruB02wqZn4CD4LHwC7oTH4QvwFNwNjfTMMdeBAIsl3aEwR9LzmR970sATMA6ehO3h17A/PAWHwm/gSNFHi54IT8NM+C28AVbBhfDv0KwnFXL+YHV+z3oyk3w3mAuDYB40w+0+Q7hUCTdNwqVJuATkoIQLlXCBcICEW4VdBu+GAXA1DIJrYDC8B4YoXfYUQSolvl0SXwDsJfG9IvVhD2whepzoj8LfQkmPfDNOeJv0TJL0TIb+MMktHyrPEG6AhLtUwl0Gdbs+Q7gREi5Bwo3U4VRl9hpunIRLlHBXuoULO0O4vhKun4Tr7xYu7gzhhki4oRJumA6HzPdeP7IkXLbUj+slnOE4SMI9JuEawSIJV4i/5oYO28NiOBzOgiNgCRwP58BkOBfOh7+Ct8N5cIn4WwVvhmvhfLhB3HW6S7zbf7vYv1jsX+Ke7jOEWyHhSiXcnW7hBp0h3FQJd62Eu+4f7J0HeFXVHcDfy2AlkBBCJiMM2SMMFWSFvSFsZJgEEpJAlhmAihpGhSpqrFRFUakDFVGjooITkSKuiq21UqlSq+JAixsFa3/3vP89793cezMAv7ZfeXyHX868Z/7PueeeIf5SDSX+IsRffThC/F0p7Wm9tKeroXqutKdrpD1dC5uI+VdwF6pIwl3v9YXbnL+3S7gf0G4MHoaxok+An8Kz4RGYAo/C6fArkbNfwyL4DVwBv4XXwu/gLfB7uB0eg6/B4/BL+BNsbkSG+PWAXjgahsB0WA/mwfrwCtggQL6lr3LP1zmSP3MlX+YF+Cuqxl+a+EsXfxkB8qhc/EU4yKNvpN/9FobC72Aj+D1sAo9B8/mbq3n+Unn+Mnn+8oDnV4q/BIfnF4q/ItgIXij9SzGMhyVQy0MJp77D849LOk7AevAniXc/1CHx11L8hcBu4m8C7hrDiTAaToJxopf4swfIPf8+l+d+Ifn3T8m/o5J/X0LdDiWcYIf4z5B8mAmD4Cyo2+Fq93Tnir/FsB5cAs1+LVXH296vjRJ/o6UdjpFyGyftcKy0P/Q6vKJqwhsi4aVIeEMlvOES3jAJD71OV4WE19ghXZkSXhYMh4ugKY83i78iB3nMO58qzw6wPewIO8PO8BzYFabAbiKfu8NJsC+cBnvCOTAZZsBeMAf2hkvEncgj2Yuh9oHY5FEDkY8NYRIMhx1hE3g2jIT9YFM4ALaBY2FbOA42gxNhNJwr9rlivxjGwkIYD4thAiwXd9eIu2thS3gDbAXvF/udYv8V3I9K+pXUS5GrscZ4RNIxxeNrj9NhRzgDdoMz4QQ4C06CS+B0OB/OhHNgOiTuKr7zYKnYl8ML4HqYBq+D6fBhmAH3wgVwn4T7B5gFP4KLpD1lw2MwB/4IF8OfxD32mMveCni+lE8jOE/S1SXYV08=
*/