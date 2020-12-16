// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_IO_HPP
#define BOOST_GEOMETRY_IO_HPP

#include <boost/geometry/io/wkt/read.hpp>
#include <boost/geometry/io/wkt/write.hpp>

namespace boost { namespace geometry
{

struct format_wkt {};
struct format_wkb {}; // TODO
struct format_dsv {}; // TODO

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{
template <typename Tag, typename Geometry>
struct read
{
};

template <typename Geometry>
struct read<format_wkt, Geometry>
{
    static inline void apply(Geometry& geometry, std::string const& wkt)
    {
        read_wkt<typename tag<Geometry>::type, Geometry>::apply(wkt, geometry);
    }
};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

template <typename Format, typename Geometry>
inline void read(Geometry& geometry, std::string const& wkt)
{
    geometry::concepts::check<Geometry>();
    dispatch::read<Format, Geometry>::apply(geometry, wkt);
}

// TODO: wriite

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_IO_HPP

/* io.hpp
N0/VdYqVc8mn8/ySrAHv9ehFwq7TfN/oipuSy0ObO1lN1k9C53TlXd0+/4LbCYz9/j5nsGfdJE7CJFQnjH2thuV2Cr8xuK0RN33uSPzPry7rea6S09GREdHuGEOlXw33Eox9tqjkx2Bni1JVviurvLXE/yxvWhGOszGS3m5P/kLmLPKUaRFuO73h1nrCiE4v5jmYC5zDMLbRHXz1wMi7JW70Zz0GJspY6RiP5NwH7UfOSJRqX069L7LnulAyMwVTTBolT/mfV5jM4TfP6RMj4JyCMUrCVdT7b5cqe5Zuy2aAfbpEI+Gi9Jm4xcqe7TsG6Xm0jDkSJtznfLNkTw64+Ma/SflVZ2w516bP8jG2e+O7Sflp6HOGd0J+Ptfj5Po2db2D4WbubLXBaxjrj9VAB6C696Oiwzg8FiVriOtxP4rZ4HdNt2EJP6Cm5/xWq2hXWHQoTT7gOthDKu2WKu7jxNuHcOu84dzVZH0yAfceGLs9DnWsT+o8e9IMaxIdkhjtjnSuY+lxb75Kc3Sp/MTx9wPqWozqb+nEdxSzTsdp52ULboc8eQnpXsa1Usd+e8czP8mxpuRsR4mO9SXdVhzrK32SvecKKsuennjrm8PTPjpM8zOsj3uFvByWmntLGxf/jXz6wPRC3/nYRep6F63DsL8OU8X3HVLPcS9T1+LJaZj+jra1DLogZY95qblSH11vKl+O+UlxbdmbionHzJU6KHHWwdQ8XQtGsHqQMMl6HeYuZc/jPcf0HR8cdbNO+clldhJm142Op0bA9+sv1LUKeo6wX9ldWmdiJzw98pvUVaGuq2ZSV/VS7Qhutd4d4DwYhd+0Z7x1xQpEoPUO8ZOi3wnSlX0ycwMTN6kb5gf2l06Zm+lwtXSdDlT2fJNTlb7fZTN8w2XrcBlazsUyZf/BaIXmikDvZ9LHJVySllPQT6dnn3O1qyBXz9n2qusvih2N3/vUuO28dzIP+1j5rSnpO9ZC9HxoogpfQ+wSH2F89IwX+a7FFas4u6CLO9xnnWMMfrw66V5Qfp627TrOytg9urK4a/yfKO9wC5T/OOKMMLpQX6m0rXA5K7INsx3ju3bxcGzZvnGX0tOq25rc91LvFHJfxT0bOt5lZJ1hxT7R91DFOb4dkAy9zsDZAq6HSofbs7q9+i4fB1w/nqX8DoxoGf6htGVP+AF6XeHFF9U8PfB6sswnj/xBn70KulY383n1ncRd3egnbswqlf6r50NrGNmhev7quw9B2ulClaeiCN/16kQZM95R15ai2XMEreAF2x2XvSpPPcPdxoO87Vwb5rcWqPdz3KnCh0n74L1E2V8zU40ic58ZoeVe3K3cx0QEGtPbqbJ9Rz96Ucs26fmcaus6Px1UWV3MJHuZReYCM1nm09nKX4PQVYzax5iZFZpzDdMV7z7XmmLLPxIG7SvNzTqy1u6py5eoyzj3IHdVY4K7pss3jhlSp4nyPpGtyjM44lVXDWOWe4071XLX8TxNPBXMa8x+xiZXtPEoK9+9QjqZPu9LOi9DVdkvZl7RzRUn/fwKK3+UsxL5q18qf9uMWmYk+6KrGj9TAsmrhPX4e1G1iVLfAOSePaXiH0nfTVPlH4ZbvipPv4gXKM9HIZXMKmFV6beMqzrOu4gzwXUTkmz+RHmy3MmkSVi/NB3fFKSfbD9gXf9Q4uM5pdJ6Oby3+Y3Rh/T2I2XkD2EfluoziZJ+K3WP7w5z815Z06RczjVbPd6uVPFOjDjXt4XXVLuuEXD9Nh16w+Z4Go5+hzypynnWmMEoUpb7XWotWN59GzxvnzVsRTzJlpujL29DT1h/zgG04h6fcQdbT35L3cMFRrS170a56byo++Sbj2Drzcs=
*/