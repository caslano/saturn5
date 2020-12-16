// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2011-2015 Akira Takahashi
// Copyright (c) 2011-2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2015.
// Modifications copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_FUSION_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_FUSION_HPP


#include <cstddef>

#include <boost/core/enable_if.hpp>

#include <boost/fusion/include/is_sequence.hpp>
#include <boost/fusion/include/size.hpp>
#include <boost/fusion/include/tag_of.hpp>
#include <boost/fusion/include/front.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/mpl.hpp>

#include <boost/mpl/and.hpp>
#include <boost/mpl/count_if.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/size.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_reference.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_system.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{

namespace fusion_adapt_detail
{

template <class Sequence>
struct all_same :
    boost::mpl::bool_<
        boost::mpl::count_if<
            Sequence,
            boost::is_same<
                typename boost::mpl::front<Sequence>::type,
                boost::mpl::_
            >
        >::value == boost::mpl::size<Sequence>::value
    >
{};

template <class Sequence>
struct is_coordinate_size : boost::mpl::bool_<
            boost::fusion::result_of::size<Sequence>::value == 2 ||
            boost::fusion::result_of::size<Sequence>::value == 3> {};

template<typename Sequence>
struct is_fusion_sequence
    : boost::mpl::and_<boost::fusion::traits::is_sequence<Sequence>,
                fusion_adapt_detail::is_coordinate_size<Sequence>,
                fusion_adapt_detail::all_same<Sequence> >
{};


} // namespace fusion_adapt_detail


#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS
namespace traits
{

// Boost Fusion Sequence, 2D or 3D
template <typename Sequence>
struct coordinate_type
    <
        Sequence,
        typename boost::enable_if
            <
                fusion_adapt_detail::is_fusion_sequence<Sequence>
            >::type
    >
{
    typedef typename boost::mpl::front<Sequence>::type type;
};


template <typename Sequence>
struct dimension
    <
        Sequence,
        typename boost::enable_if
            <
                fusion_adapt_detail::is_fusion_sequence<Sequence>
            >::type
    > : boost::mpl::size<Sequence>
{};


template <typename Sequence, std::size_t Dimension>
struct access
    <
        Sequence,
        Dimension,
        typename boost::enable_if
            <
                fusion_adapt_detail::is_fusion_sequence<Sequence>
            >::type
    >
{
    typedef typename coordinate_type<Sequence>::type ctype;

    static inline ctype get(Sequence const& point)
    {
        return boost::fusion::at_c<Dimension>(point);
    }

    template <class CoordinateType>
    static inline void set(Sequence& point, CoordinateType const& value)
    {
        boost::fusion::at_c<Dimension>(point) = value;
    }
};


template <typename Sequence>
struct tag
    <
        Sequence,
        typename boost::enable_if
            <
                fusion_adapt_detail::is_fusion_sequence<Sequence>
            >::type
    >
{
    typedef point_tag type;
};


} // namespace traits

#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS


}} // namespace boost::geometry


// Convenience registration macro to bind a Fusion sequence to a CS
#define BOOST_GEOMETRY_REGISTER_BOOST_FUSION_CS(CoordinateSystem) \
    namespace boost { namespace geometry { namespace traits { \
    template <typename Sequence> \
    struct coordinate_system \
               < \
                   Sequence, \
                   typename boost::enable_if \
                       < \
                           fusion_adapt_detail::is_fusion_sequence<Sequence> \
                       >::type \
               > \
    { typedef CoordinateSystem type; }; \
    }}}


#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_FUSION_HPP

/* boost_fusion.hpp
4BnwHTU3+67rWHOBxtO5Dvw2jed62BPeDk+DG+AkeC88F94NZ8ONMFfNzXpHPUe5SMN3rqO6Wte/Xwvj4XWwN7xe29WNcIqaz4a3mP5FxwbweI/+ZZP2Lw/ArvBB2EP14TGBuf9jkcjz+8Pn77vn7nvP2XfP1feeo+89Nz84H78R2YN4zb93zr13zrt3z693z60/gHjPqXfOp3fOo/eeP38Qcc+bP/Kcea/58ruRg0ikefE6J17nw9tz4Z1z4J3z3yPOfXfOe3fOd9e57uHz3CsQe377DsR7XnvonPYjz2d3zl3Xeetmzno6MnH615unfvg56kc3P13npuuc9MAalt5wM/Sajx55LnrkeejDkWxkGeKcb67zzHWOedj8cjO3/BDsdIF7LnkhEjp//B0kOG/ce874DqThZojsR7rcgjukEFmJbER2InuR+AbKocF37Hfsd+x37Hfsd+x37Hfsd+x37Hfsd+x37Pct//7V8/8XFXw78//PTOW9nc7V2aZzsK09kLvAVPgb/ti/R753VZdWDc3NPvcMr7kF6uYE+Qb2ZsCuqKhwqH7zU3udezATvcNblh4d5Zx7gPtcppqJm1TMUsTNn/06d0DD6BlyjUydC6D2OtdnFnpb8d8i5BqZcg3n3AD8OedLh4Q/zLjNCHG7Gt0d9jBX2KND3NeHhT3cuB0X4rYhLOzhrrCzQtxvCAt7hHGbHeJ2U1jYI1xh54S4b9Sw+2nYBei227wQt1vVrYZNsEG3xSFutzvnrOrcTtttRYjbna5wy13h1oa43eVwq/NOzTqS3lIn/uC37Cuk1pcV+hzzuAaK/UdifwKVkJgwGTr4zb1U7Bv89nwTX3DuqZkjOobvvK1hz3a8n0mibFN4h4OMP4yMREanNGdOaGzyn94mDiSlqLISnTkZwbkeZi7Gm6JLm9J598H5H9rOxG2ty22muK1Tt2pm3K52uR0mbuvVrZoZtw0ut8PF7QZ1q2bG7SaX2xHitlHdqplxu9XMS9F6iNn2oFucBcx2mrmvlI+622XcSf2JOM/VOQfgo3j+kb3/gkylXBt/FewT8+lMq5myUVjkrKPowTnt6r5nQOev69+x9Lgjzq9s40u04Ov0Lu4d+jrxT7qoD4Ql9WHy1GEjfWq2Omg2wjZbETQbbpstC5oNs80WB80ybbOKoNlQ22xB0CzDNis0Zpkn2mYXBs1G22Y5QbNRttm5QTOTjslBM5OOM4JmJh3jgmYmHWOCZiYdw4NmJh2Dg2YmHf2M2VCTjp5BM5OOLkEzk47UoJlJR1LQzKSjVdDMpCMmaGbS8fdfGTOTjoNBswyf9gtfGrMTRd9n9NGi/9boo0RvMvpI0d82+gjRf2n04dJ+4k37oW6HrAPJbuuT3yW0uSGWDsdgk/ResJ0UFOcvms+Ux5KKYtZvVVXnV7vnKaZqH3um+Hk2tjTmZt+82DN1jGGHdaLO5fL7Hv0wMC8QF452t6S4pKBY5y/afk6VsBf5ibvoT8Y+Ez3NNzSm1t9GzGmJH1nmlxJ28L5RwzxMaz5yio5HzhW/W2KXRZ0QHRij2P5WyvUXJuu8WmqWfU9uZcJbJHGwnIz6wF5LFONrac2Z1T5ihJjnka+xmEf5WuMjRcc+Y8TuOExTtA+xr53svnZm4NpNeg88UXoXUuFYe/GFpKNF7LW+5bjBjPQflLysl/i+In4KxG6GdY8X933jrLw5SezK8gtydY2QjrWi3pf5zzEX87Wzu584ibkd7tWOfCgx86xfb7LsriNep8l8xbdEfyy6O7kbdL8A+0C+DZQ86M8ev20J4zTpuz8WPysc60zKqiStOu7MFD/FviTxg5kp60TxU5UsaWVITFo=
*/