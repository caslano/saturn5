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
dGvO4Z+7anAIL16e+ffwwruxuErlPyzQ+7U97xfkf2g1w/tLQRzYmPzyLHjZ5Bc0jYlXRDmjZ897KdCMcqMfhyxnHj3iCpqR5YVMVim/jTQ0Lyw4fv/+HbyFk6OTIxu6vuAsholmYs7SWxvOQrPyKfIfHlqKfbSBafDjVuHKjbgCJRf63k8Z4HPMAyYUC8FXEDIVpHyOL1yAjhgseMzgYnQ17Q8/23Af8SAiJyuZgYpkFocQ+XcMUhYwfpf7SPxUg1ygOToPudLoMNNcihbGZqBZulTkg8L7sZLg3/k89ucYyNcQaZ2oD44TZGmM2TuhDJQTlNtvRXq53skUk1j6K5CJBi0hU8wG0rRhKUO+oDsCgotJNo+5iuxNNhhKhI5MQbE4Jl9ox5nK02YwKeCxSQ2Q50uu6aakUBTqPpLLLUXEkbwsslRgIMQBlUKJMNuQiZClRtnsvAxRYGoA/s/SbPINQQpMBuqdCfQndZj7iisbvvbdL6NrF752xuPO0J3C6BI6wyk5+7s/7GLpOQZLgT0kKVMYPAW+TGLOwiLmn7ucGnZ/uYUsDRhiGppd3DLBUp/2MDfFQipoKncriZHF3REMRy70un0XzqfwpTPsAjk74CKIM/RQJyp4iuksaUX1yjrz1Sp3p0hA4f04
*/