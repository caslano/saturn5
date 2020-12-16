// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_CONVERT_INDEXED_TO_INDEXED_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_CONVERT_INDEXED_TO_INDEXED_HPP


#include <cstddef>

#include <boost/numeric/conversion/cast.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_type.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace conversion
{


template
<
    typename Source,
    typename Destination,
    std::size_t Dimension,
    std::size_t DimensionCount
>
struct indexed_to_indexed
{
    static inline void apply(Source const& source, Destination& destination)
    {
        typedef typename coordinate_type<Destination>::type coordinate_type;

        geometry::set<min_corner, Dimension>(destination,
            boost::numeric_cast<coordinate_type>(
                geometry::get<min_corner, Dimension>(source)));
        geometry::set<max_corner, Dimension>(destination,
            boost::numeric_cast<coordinate_type>(
                geometry::get<max_corner, Dimension>(source)));

        indexed_to_indexed
            <
                Source, Destination,
                Dimension + 1, DimensionCount
            >::apply(source, destination);
    }
};

template
<
    typename Source,
    typename Destination,
    std::size_t DimensionCount
>
struct indexed_to_indexed<Source, Destination, DimensionCount, DimensionCount>
{
    static inline void apply(Source const& , Destination& )
    {}
};


}} // namespace detail::conversion
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_CONVERT_INDEXED_TO_INDEXED_HPP

/* convert_indexed_to_indexed.hpp
tAP5N+PC1TXButBJob7l+gFzwDaeHujpw9yywZ1s4OvTyVzKwdZRmZxjYAO0N4LwfPrzDYyymkm7tbw1RLvNwDL2fRPey7dW2lOJZUzGM0TpWrklAGVWKM8k8QJLJwFcZsejzA7Mcy6irb2R3h+29H7A0l4Qtl9iCQumOB8+zsFTyXQ26I8Ddyh5Cu8f2mbWrB3cyMe4MQfL9CXtayVuzaRGwd3bOd4CrFmdKHS3RxE6iLSXHbA3o8N1NeG+YA+FqX9I/sN9si/Yi7apDzS438/ie9izG7wlNkD1JAiXen05stVhuU+q3+rDrGmM5FLh+z2oksl7PaiCURj1EmcjyOYwXokLvc0tor6/HKoXq0J7abbY8mxPJodwr6L1UfVOxqVBPTmtlGQPwet7aF/YUD1ueBN5p/x0UJ1rGPLz8OFSO/7py5oDz5R0fZLq5SZnZx8tNXloSoz0+IeYmKOlPY/iF3o5i3ss/T7C8+Pb04lk2u2tRt4We512n+sy3DO3Xuip2evuaqdtjK2tS+rqj6FJ3VUtHfRmz6r5VmV54qzN7FRueO9BefF/T9iD+rHQacKmcRy/G36SDbfGN1IJCp3bceKB8JcbhFwTCtTbyPN8RbZZcmxfg77SCOw4DdmHrRyWjOqIkz9JsFLPHojk8ozZcE+ahurCZtPxrLRZeydOjtepe6zdmvpHrAnPr/MpabvIy0nJXs4JA5CPyLWrd12W40rT0EGkHy5CHjtHVMN9Vfot7i6m37IPewr6rDn6a7A2wZ9sBh5o+C7tDzk491NPrXGf7KeeBh6nq7Ryqr+8FXhnAG8JlznekqEdmX2DvOeZ6J3PSqcpsx5gxq+7c4fxflOGsN+PiDKshc5GuV41lzqs5D2rRt117Ms/MWyz5xRRXmOlfa7Q93mVRe1brutcu6K+e1nbEst1NJh5f0L1oy6wuiEdZrygH2X12m034TsY3jxwINbrJyP6USnyzJw5hhTa25XMZMyRLWr4MvFsll7/zPj0UTHEh21UzotS/WU74vcQ8El7vIjiI8umCPnt24hy/Ab+09EeyzexLoE9XxqUJckc3odyGYWN3FkKkB/j9Tm57nc57Ow8+qvH0p9VdejzYkx+gYr7AsIXCD7QI+KhN9DmVD2+usata3wd54JT1H+V4XYKg577KJL+K0K2HiXb1/z5DMQNlxFPde/7N2p4DUbgROHu5F1P8aq/RHj0qfm7b0EOwtH7RHU/i/pC4TRugD5ysIFm6CMn7u6chjr2Xcu/3dalm2oMLh3jw/juZtnml/YOdIvLRjhEthfdh86Lb339LcLX3wrbwzqZndOk9XO3572G94ep9dNJ3m0qn5Mpn9At8yD6gA66vZNgsPPotNQdwz8U9pcDTzkfefdY/OiT/O5B/btF1dd7ISvxCM2X3UfwRe6sEO4Vo+PZneYqQfrZTPf78byJiqO3eFbZM0+TbHna+5BrHIfBZCabiac3dqdc1y8Rz7h5gjyRZn5gnpTBP1JU39pCL5R7SJ/hNm26y3CBSPsBpI0eNR7dpDQV0KS1apyfVks7zfZ0mYy2t7V3dfp5ZXhL/fJ2nI8KYEt92HiGLV3aDtoJAV77qkNwLyLDuup9vPcwrH2lDytj2MoGH1Yd8GPY+2QaC1wa+zOso21lF026APcAhjd11C1dTup0+PMY3tjp853PsLpmf/5okdQFpebDD2d4cK7sCIY1dHYJfS4PcHl+bIXg29q0Zsly4L4T5KNuNWBeiQ9bXrfGLyOGdTRac2gwBCirUXGkqM7Gep5XyxPf1tTU2lbX4NlyHI2zesUq3IE5Oo4EozkussdpsMcHa9i6nB0iYOyP7wwXd4w/7Pc=
*/