// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2017.
// Modifications copyright (c) 2017 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_MULTI_MODIFY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_MULTI_MODIFY_HPP


#include <boost/range.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{


template <typename MultiGeometry, typename Policy>
struct multi_modify
{
    static inline void apply(MultiGeometry& multi)
    {
        typedef typename boost::range_iterator<MultiGeometry>::type iterator_type;
        for (iterator_type it = boost::begin(multi);
            it != boost::end(multi);
            ++it)
        {
            Policy::apply(*it);
        }
    }

    template <typename Strategy>
    static inline void apply(MultiGeometry& multi, Strategy const& strategy)
    {
        typedef typename boost::range_iterator<MultiGeometry>::type iterator_type;
        for (iterator_type it = boost::begin(multi);
            it != boost::end(multi);
            ++it)
        {
            Policy::apply(*it, strategy);
        }
    }
};


} // namespace detail
#endif


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_MULTI_MODIFY_HPP

/* multi_modify.hpp
QvrCgvAx4s1mjGjrPjZql0+gU7cSvMjALdAcoM6wDbvdjhORhppKon+f1dm7CB6xcAwgQeuXZrwYMq68j+ANblzJ4aaQceVqdYazTY0rD1j9p3yd7SWDm6W3xcKp+Q1kbeBs0v2DQve3TWBDjg2MUZJijJLyGjF2+o0cO03YPgqKbhdzB79FHcnx44M5xo+HhJ/xY+Vn/M7FmbbHtP+g2uEfc/iOf0LY0NTrmQQL9eseFT640EncSat1utB7LByf/2r8x8ETwWWbsGFZpqd47CTx6a5o4P9YyeBvAl/aor8LP+PBkDHTP0X8H0PinyUY2inLQbRRjI0kj9O959TYaEztJ70dY6VfYayxhOjPgqwoHmMjjHmQZ7hNICqE0Ejpj86TPp2XxtHetNrgHPA08HevGgs9qHzUGbXi3siQsdCsWjmuAL48y8NjIw5zfT6YQ6dfVItxh8LR46G5yIv6UX2fAHiT8eAFdQh8DusxEcFC206p4E3i6DHRsbXZ9n6jau/ltTKf8DFRpZI7aLDORjiebU4gvqbWtaHvizFPXS3nn92LruprsR8uZFwe88iw6Rtk+D4VTit6d6n4Ayp8swrfqsK3yzDKosdIBqbHSMtqg/F6jLRcxf9SyflkFX+fij9Fxet6eLmKv0ulP1XFH1Dxp6n4m1V8s4q/VcW3qPjbVXwr9ORO2AHYee3Hsa2Xdr4NaX+BtJsDvvnI9kQ6JcZtuzh8jfPLh63vjvFWkRxvAafUjdV4jvCMWrk3kjpnNZgRANtfh875TSKd3ftdK/oe1bfLdrpRtOXz54bjvIrrAHRUHXRzPGio+E2Q808hZ/jQ/Pvn+B24n2eKs+9vUWf8L1Rn/F8N2q+pVff6ivO3b8T52yhwtwFX3uGAtWtuf8Wwg9uRpg9peI1e0ItLWYNe2F1ZA8AflPjI0+Boue8A/k7gS7t2HOYIhxH3N+iuyVP62efUOj971O65z8KKLCwzYqHQ2V6Cl1r49gTdxNafGemz+h4jeMTC+9LJIUejn2D1FmbyitJBCHLI09l9lAmKb8C9JMkBwJF3k/O9Obxa+d5DBGujsXF6cPu+3liM044QvNMbGBrdTm90jI7upJHBE/7591HRtrbkvw+F96KebdKI8esjC0lWNoz1e7T9Ij0eBnwexgf++LhUjY/7rdxyyofkJ2SDMVIDyWIojvrj9SxTS/FYlKOyY+vV/tgae1F3CTm0hd/Rw2vlU4XOXYg2kuL+ktuXvuuE5KbT0cxFrQiruduzOc7R3Cf7WLQj4No6kP35+cAlONOV94uR2XjiwcA9DbE93Ylzef6hxnKXHlzWuMHeotO+VtxbaOGdyVGq1xRFZO8tfOXQ9qG+kfSmVO9AXN5baHAZLvYk0wBzTW8q3myUNZtvxIdbhrBHzt7tOOiYAeyTx9q7Kc4F0MIuMO2nIHVu6954JzUEbxXq90JRv01TaJOIu7HJngbGbQ8aGKjzGnzSz3w97MwbYEuuD9oS7CPBXKUNY/0dOGZvibkoITAvCZjB9PEidl91Iinx6gETeCQLg8Q4pP9AoHTAsTZjSPDVZsKOL24LbxKy6rTxfmPAb5JM+N3Bk5er7aNU32P3Cygdfytk/DZhy6ldsE7LM/3hZ/OneRfXBvelYN4Z7RVrHq4tFT28UJxpqFVnGpSP+x7lM5/v9+doj9onfb8fD1pppU8fZD6z5fFU33Y55HGD698P846OPYmRZY3ZXopu6LDvCD0PGrI3sWRIxyAnaqtqvQM8X1mbZ09puJ7ZOvl4bbZOPhHir3ySYNK/uErI0cDqMPaVPsWnwdNnhF4ZvqWP8DnEmd8fF79n1YT6LVyfX6h1eXzJjN8=
*/