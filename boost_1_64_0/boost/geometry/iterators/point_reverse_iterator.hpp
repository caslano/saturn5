// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ITERATORS_POINT_REVERSE_ITERATOR_HPP
#define BOOST_GEOMETRY_ITERATORS_POINT_REVERSE_ITERATOR_HPP

#include <iterator>

#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_convertible.hpp>

#include <boost/geometry/iterators/point_iterator.hpp>

namespace boost { namespace geometry
{


// MK:: need to add doc here
template <typename Geometry>
class point_reverse_iterator
    : public std::reverse_iterator<point_iterator<Geometry> >
{
private:
    typedef std::reverse_iterator<point_iterator<Geometry> > base_type;

    template <typename OtherGeometry> friend class point_reverse_iterator;
    template <typename G>
    friend inline point_reverse_iterator<G> points_rbegin(G&);

    template <typename G>
    friend inline point_reverse_iterator<G> points_rend(G&);

    inline point_reverse_iterator(base_type const& base_it)
        : base_type(base_it) {}

public:
    inline point_reverse_iterator() {}

    template <typename OtherGeometry>
    inline
    point_reverse_iterator(point_reverse_iterator<OtherGeometry> const& other)
        : base_type(other.base())
    {
        static const bool is_conv = boost::is_convertible
            <
                std::reverse_iterator<point_iterator<Geometry> >,
                std::reverse_iterator<point_iterator<OtherGeometry> >
            >::value;

        BOOST_MPL_ASSERT_MSG((is_conv),
                             NOT_CONVERTIBLE,
                             (point_reverse_iterator<OtherGeometry>));
    }
};


// MK:: need to add doc here
template <typename Geometry>
inline point_reverse_iterator<Geometry>
points_rbegin(Geometry& geometry)
{
    return std::reverse_iterator
        <
            point_iterator<Geometry>
        >(points_end(geometry));
}


// MK:: need to add doc here
template <typename Geometry>
inline point_reverse_iterator<Geometry>
points_rend(Geometry& geometry)
{
    return std::reverse_iterator
        <
            point_iterator<Geometry>
        >(points_begin(geometry));
}


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ITERATORS_POINT_REVERSE_ITERATOR_HPP

/* point_reverse_iterator.hpp
PraTsbK3NU4Hqr2vedYkjGZ0OdFY6L+l/jip+yztR8aFfOmzYRVHf9yifTVbubWVcPY+yr2ybv+kd2ZL3/xMXe9WwXxjbsJnCXcZH/o/V/oYHyJwDfV1p6qvGo5OVVKnib6wPxyj7YhOHJWH5wKTjSXUjekWqZsnWZOaw97ilqpuOhL/20nUdrKtfXw/NAByPyaJJDnzJOHWE+4uddZ1dY3ZwML6vBVhJK+HCXO3yut888Sr2WaSTL9NuO+TdMIJq1eY7SZF5NuJ/yFMrSWrTriaYYISJmIifWlaiD2oKuxp5qEyDqX6Vdv8nDhyQ7o8zVZPkjKIXz5+94ocR9CSw8wZ6rb59YS5T4XprfJhus/AbR1G19PgaL7SRa5H2DozEm62pqruteko7zkS1Pi52z/MO86zzTfZ8CcsMzYnVBsjmVllqzDRfj6Zndlhz0bVz8081JB+97B1psW3pkr1LXV2D/fOYWtsCSSG/Wsui11n6wnzgJIdG1pEjbVKMFS8ubgXY6RsCWvOkesifuswD1pyRJ+QHBpEt033G3Xjf0/H394Rfw3uT9vj7ynxi9/bOv72DcY/MUXa1hqPOo8ckvgPId8ZPx0/VPGL31j8ai25yBnkEM25Xvy7UiT/q3+v8p8m8efjvtYW/+r3JH7x24550JKL5r+Zr167osPK+Pwzs+2FTfdaZA9aceP+K7NpJSgZ8fscs1PLJCTWHUtLm0Xq5E2V53+xdyZgVlUFHH+zsAiDDohsog4IOCjLzLAKKAMMy8gAwyquwzDzYEZmhnEWHAyLDJUMCxWL0ozKEBGJzBSXDI2M0gzNisyFzBRNi0yNVLTfO/d/z7tv3n3D4n1W3+d8HH7v3nvu+d+zn3vuWdLT8WDIee50ro3B2HB5S3PKda0cs8251zy3M/08Ejypac3DpgF72zFpq77Y/oxIcZ0XarG8HjhM6x/oXWStOX46rW0oM/Wk1OtTmpfLnbReT6GxNzttbOhfqc45996O3JueFlsex7bTcoy9fubcOSqPhw3TvObm7xXkqsh7hbEb03brHuqhtlsfc+/Z6WeFJqc+nbo19Iu0maYuryLcOmeqTF61WWVyh7RE5fEI4840cvt7qeac9dOj+GljWiQuVxxH+Ydxy5dVPzTlcLu0kMov2cnMdMvgVZvjymA9W22m0tmqdVhpewxFmHnubpwrxmw2175pivmMtDZO3a3rVZg77b1preV2TDp+o6ObFmbixsD2LaWDd4ZqTQknHdiwbxUiDbQQlwfMfd1j4vLg0KOPyzfMvcvSR4ZWpbZL2xpKoeM74p8m/LGuoxuXtfg505SpUzjXhHHCajn+bGvyXiddW4tRPNTa8JF7+zq64X8h7rU37q3n3C7rXjjiXpq5R9dextypexKFe59OqpdWDcNOp3am7OO+rE6uu2Nx9xjb3trKt+3TuW8p11Zi7seswjwg1mIexDyE+bG+ez9sr8X+/glmB6ZW5hHMzR57j+p+zsfc/1PMTszPdO4x2ZOJmz+9JyXk80fEmj6fUR03cH1GSopZW+feEVpbp6bcfIvfnxK7lu0Bjmn7c6yGv+ZXr4UbjT3TR2DsboC8n3Iu+n7aQ+s13GPOx74fap0GrsWuc73SrlXqfTc5s6Pz/kK60Ro+V+TFjuO4dGjs8VXDnOMf6Pigjrfq+OXhsfbnjbDux6yH2u0E/z01FpwVOqI9NbDf4p4aup5ojXGufzJ7arhr/67WZKuZmOMxkzBLcXNtjL/LltYut8NeYv3ueRfbYu4ZHOptxxzJHa1hnGXXlI+uF3GHuT6QnoCuThjZe7o3DyPbX7nRXB/FXSlOuNl7upiyqidxmdFFbei0ga0=
*/