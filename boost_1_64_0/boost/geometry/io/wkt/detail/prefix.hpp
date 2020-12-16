// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_IO_WKT_DETAIL_PREFIX_HPP
#define BOOST_GEOMETRY_IO_WKT_DETAIL_PREFIX_HPP

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace wkt
{

struct prefix_null
{
    static inline const char* apply() { return ""; }
};

struct prefix_point
{
    static inline const char* apply() { return "POINT"; }
};

struct prefix_polygon
{
    static inline const char* apply() { return "POLYGON"; }
};

struct prefix_linestring
{
    static inline const char* apply() { return "LINESTRING"; }
};

struct prefix_multipoint
{
    static inline const char* apply() { return "MULTIPOINT"; }
};

struct prefix_multilinestring
{
    static inline const char* apply() { return "MULTILINESTRING"; }
};

struct prefix_multipolygon
{
    static inline const char* apply() { return "MULTIPOLYGON"; }
};

}} // namespace wkt::impl
#endif


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_IO_WKT_DETAIL_PREFIX_HPP

/* prefix.hpp
XtaebEg71P7OK7c0mBxI0sZeqGVGcS9FjpUjPcdc7qBM4l6SMXc3/J7I0qf6lF9eJjI8ryjSDoLpWZ6kwt5jFphaZiTxSR/3kWNTwFtf/iSvDLWrpqn5nz7fvVTZa5bul9LvrldxxmvZLI8p/1EqjW+Vf7lpPrqPqys/a6mDxlqGyz4Vz0gznrPjF2FPRabZsYrUB3VzLRlzlzwa5nInhMVEVwkLC4sOaUB8loyzZPFXjL8My18B3uIrXFShf5grOiLRlgsv71hXx+q+HWSc4ZrKRysVdyphw+WhYpm+mNGYkZa9zLp+HeODo933qGp7tPZ0XQyLoCXjavl07333EXIVUJbBwX+wdybwURVnAH+7m91NshtIQgghcoQblSMccohAOERuI6CgokkggYQzJOHwwnCotEWMSCsVrVTRIqBGxaOKiketWrTYoq2tbbFqaz0qVVRaj/b/5n07+16yLyRIrW13f7/JP3N8c72ZefPmzXxPhe2W5EPH1Zd+reNK4jhN68L4qLrBc8wSfriyT0f+58o+KclddxX9RaczWM9JnlP26UkOXVOi16MaPqX8i5IOBvL1GPWMcvuHNZ/XcQ6Q7zvTNlaoeBKH+Z4wNvgfrXtG2jlPWx6dp6V6YumOEj1RdcKy38dVv9MElX6WpzU7UjKVWyRPxYnNOSXypLEk6NTrJGfBVZhnEmPpW7pY+d0f6MEu/fG+pz2n+xcYj/l/qfUt3aX8lyV2MDrH1Le09lJ5BnLqOtL6G4euVNeF6cIO40UjzyNnnKUd9Kqr30jrZfiFqpOJSW7944MVVjty1fEjc+xPLzLDrVMzx77KzV5nP/a09GZ4ynzt2JP9sTHDP8C4x/+MsTnA6lDwSmNj8ObYOn1El07gYnWel76UTdy41Yl7qPc9I993t8SdQ5v5i477h8Ga+jp65B7hVfHOoD1QOtPNEe9Oz+Po6DmTE+5LvbvRr5VtPOxL0Wk84H9Cp3F98AZXHT1/vFy+dS/1eVjZs8Wur4+r/NOXOHXe/Bw78nX7eYM6frKgV7WfT7wPGZs8yg3bGCX7W54Ubm9Qt08r+KVKN4UeeY1H9KTW7acxdftUw1tV21zlzee5xLzOM1U5F1bOLSgtJo/6ucKtDh6/zFkHz18Wuw7uYvw+yYjO92ZBu+6f2Wn17wuvYIqxl2DOddcNpOIpxe05+MdY+oHcdAO56BBa1MjnmhqbnqCi6vp6grgG9fQEHaozTzkSQ08QQq56ghI99fUEpTrP+4sOgPp6gqrr6AnKlPsh1xw3uebyTLR8hVM/0EmXOPUDffsSp//oS53+a8WeKvYrLnPqGdDr0VlWpV4t62dXYXqSx5o1jvuuWpEqWVKAYoZZJRWVMefbIpOudQLcouyXcJ4zZLv3VCwHcqZfZEi9t9HPNhaRlAojzy8qzFzu4Il67v1CI9YNXebecl3IR511xAWizGW+rJ0q/TPURd5aR12g950BoO7kM/YzCLLO9dNzlH0a2/g8bs+SItO+7rxM18cs5T+K84+B2HO6hutmvGvdOJ/VHM/Wxgmiu12+iVBmWDpl9tvqxqFUJnZ9SPjuesw/ouxnu83FJHwXPY/4WNknO/XJGIaeP32k46MN6vQ6GbH0c2bAQzo+7ss6fE7MNa3BV4iOePk2RT6OHx/DvLch/REv1dUfEeNbFcPkOflwGyuRG5Q7YyfmRFP3l8pndWkRrbS0aFExb7zml+hlmJjXRWQSlX0q9hXKvtHlukh4Uq47t5W+r/37GsXixhOYcuvH1UiK+U2QDLhUhdlk1Mh6SJmOy+/UFyr37h8ovzn1dTnK/GiL8p/v1N0o8W5UflX2OVBllW0+/xPln1Q=
*/