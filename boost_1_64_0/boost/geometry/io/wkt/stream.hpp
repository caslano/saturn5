// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_IO_WKT_STREAM_HPP
#define BOOST_GEOMETRY_IO_WKT_STREAM_HPP

#include <boost/geometry/io/wkt/write.hpp>

// This short file contains only one manipulator, streaming as WKT
// Don't include this in any standard-included header file.

// Don't use namespace boost::geometry, to enable the library to stream custom
// geometries which are living outside the namespace boost::geometry

// This is currently not documented on purpose: the Doxygen 2 QBK generator
// should be updated w.r.t. << which in the end ruins the DocBook XML
template<typename Char, typename Traits, typename Geometry>
inline std::basic_ostream<Char, Traits>& operator<<
    (
        std::basic_ostream<Char, Traits> &os,
        Geometry const& geom
    )
{
    os << boost::geometry::wkt(geom);
    return os;
}

#endif // BOOST_GEOMETRY_IO_WKT_STREAM_HPP

/* stream.hpp
6nlK+j2W/T3K0t1YTS3pOO21nPxcYtXzK10WU6/9BNJbvlP5mY42p2zT059vVOmsJZWLtB6zapulfIHzUnpNRM6Dnlbx/16dc82TtY2/Kje3zxhaMKnY5xkVvUl991T2K7BPVPanTPs6T1Flb1pKz698e5G8HTCuMqqSX9GJaaXJ+FQR3Vc7zY4yD5ByUTPY8aftpXUCy7xgikp7q5nEWBPqM9Y8jYF6HGh7nveh0d4+rezZ3vPwtg4xbaedybsyFDdpQ+Jeot11O1D9qukmrUdM2Rf72YfcY9uXJzi/E1Wra2e2OkbZMVUIc3qzv85m/SkwY2rBON7GDZ93Dy55v8EQ9sL2QtjjFXH4rbMfr297znNznlN4nXXecIvOm3y7UtOlgOvsXZXfzu6PXHpMkPBppd4NZVyQ6031M6+Tsndzn3K5VJjXPWvhGfr7vYRpbMRJO+6g7JcRJkTScZ5xztFhrnZ3pHRbkWKbrOdYRQW5OcUZRdx3vdrhMxecca/qj+Zcs6nvu4d+1rdV8fZyf+5yBxwHDqvrWawO1Nf96Jb7cEMzygSerakyDoSpdAaQr3i+gIYaDxm1kf3dwKzjitV9ylDhiEfngzZsr+Hod8WbVDyHzOvVm63W2ZZvMVHGjpItts7aRigpWOyqZcTJe3gbFTbFdcSsFWzdTZehvspLN56RITp/E5RbPeeas9znXupaHduu/Yb6lAVN3Zk5pOEd+y+WNCw/g9UcR69lqbE3zf/d1FMXcs8jVPhZtPNoozXjSjS+1si846yMK4PtfQl6HW+R2Lmmz6IfO8/cYzv06EM0/HTNR5il1+tirHFT+VHtWrlV0/6k3cq3acrtu4anxpfXtujnuuOb6CHZUHQHF6vB+TCE8KMf0H3Y+f05sLwM8V9Ly1qYrewzzUjK6N+P5RuChJlgjuY7guce71NuDUp905J3CwlzoycMbs4wU/2+/+foMNMkDG7eMM7+J/lKfFA9VwwX/d4/X873Sm/eqsIblZ9CVB+G6T0s61SbKKuMAqdMgjhZ//RvC+kB9hqMgFN1W7Dv+fsPeJ4pZZNZEPgMf7Cz+hcumyDw2fJgshKCnTm/cBkKv5VMhMCyDIKf4f9KyTKom/3+mwUnh3S4c8MdMyPezV1y4TILAstiCCaD4MJ13wWW6RBM1kAwWQwXLlshoMyCoDIXgsksCCZzIajsA6VbTyY+6tuN9dwYK7rvFmHs/a3q0amuVYKzxP9Fcia+GawLL4GtYQvYCbaEl8FWsB9sA9NhWzgctoejYQeYDTvBxbA7XAkvg+tgD637TPaugnBMtp9sBTc6vCyGwDAYCj0yAmIkXFMVzikjIJn4K8LaMAbWgfVgKmwodq2TTuKpWDp9pdPM4k8wGv4dfg1HYEZLuMYSLgIOkHDUBeHwByPg1bCi2BPEXg1eI/kaBRvBDJ98bZT4IwPka7DEP0TiHwo9+dou4XoGyFdv0SXRB1aHfWEd2A82gP1hc8s/7AAHwq5il3zJnkCekwHyNUPyNRNGwut8wqU4wgXX/Uc4rftvtBVWwi2UcF6ZE9ilHnPkvk6ETWGu5H8y7A2nSvucAjNgIeRv3L3t6YSkkxygPY2R/I2FSTAL1hB7LbHr+rlZdAcGKOcqied2GA5XS7hsTIqEayvhouA1Em6rhHtEyvs4rA13wRS4AzYQe0P4KGwu9jS4Dbax7Tq9gnOkd5ekd7ekd7+k96Ckd69KD7ukt1mlh13S2wTbiF3rRjxHvayV9O6Uelkn4U67ZC+K7HOywl3N3ydx56d0PDWD18H+8EY4EM6FmXAepO6UToQTYv9M7N+Jvx/EnUSUexhchD0F3gzbwiWwN1wKB8M=
*/