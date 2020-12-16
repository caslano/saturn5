// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2017, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_POINTLIKE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_POINTLIKE_HPP

#include <boost/core/ignore_unused.hpp>
#include <boost/range.hpp>

#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/validity_failure_type.hpp>
#include <boost/geometry/algorithms/detail/is_valid/has_invalid_coordinate.hpp>
#include <boost/geometry/algorithms/dispatch/is_valid.hpp>

#include <boost/geometry/util/condition.hpp>


namespace boost { namespace geometry
{



#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

// A point is always simple
template <typename Point>
struct is_valid<Point, point_tag>
{
    template <typename VisitPolicy, typename Strategy>
    static inline bool apply(Point const& point, VisitPolicy& visitor, Strategy const&)
    {
        boost::ignore_unused(visitor);
        return ! detail::is_valid::has_invalid_coordinate
            <
                Point
            >::apply(point, visitor);
    }
};



// A MultiPoint is simple if no two Points in the MultiPoint are equal
// (have identical coordinate values in X and Y)
//
// Reference: OGC 06-103r4 (6.1.5)
template <typename MultiPoint, bool AllowEmptyMultiGeometries>
struct is_valid<MultiPoint, multi_point_tag, AllowEmptyMultiGeometries>
{
    template <typename VisitPolicy, typename Strategy>
    static inline bool apply(MultiPoint const& multipoint,
                             VisitPolicy& visitor,
                             Strategy const&)
    {
        boost::ignore_unused(multipoint, visitor);

        if (BOOST_GEOMETRY_CONDITION(
                AllowEmptyMultiGeometries || !boost::empty(multipoint)))
        {
            // we allow empty multi-geometries, so an empty multipoint
            // is considered valid
            return ! detail::is_valid::has_invalid_coordinate
                <
                    MultiPoint
                >::apply(multipoint, visitor);
        }
        else
        {
            // we do not allow an empty multipoint
            return visitor.template apply<failure_few_points>();
        }
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_POINTLIKE_HPP

/* pointlike.hpp
yJWb41Jr3R8neyQNjn9rHLqKc60uibH9nLMvDo8Xx2kryA//Bu97RGHkCefTWe1UXP0JOZVc/dsGaiR/yjeTf68OxmYRk/5+Ge9/j139KP65xgw5xMQbcJDacViaxroe5HPdo7DcvJcbUxAbizo/A0lPspEWMKA9X001thPGu8vPbOcdNwnu+/48Hxo3xhz9noc800++8r6/S7/EMXBjmDi6bQyMGCf+5LTGjqlDv98WFtffkj+Pxzmet1TzxfthcutJ/Ihu0k6h0z74XV98n+2c+EndIH2wDvIfuroPP3pM4GzS2F/PeNGajsMp2EtT+USG4XxVnenACLp0v+V4ywUcbWwrse6QsU6nJxz3nsfh2DC4aA2ylhMD5Si/qllVx5OeuIut1cG3bodzE9hbqvwdv3gLV3pATeGq5+8m0EVt9ZlRX9Lj78Ea4y3u+VMN+FsElk/Cz1L4VDlxjy+1lRuOKYrPy3PuOGDexjabxPTSam78r/i6zFoeFrdn8e/edeHEBdcZAU/rmodjX1qd8K4UnKWoe15Re/RzJplHvrMmJarybz/30e3QNPbKmPcYXO+EdepZAXepKr907LUs7j3W+tzjOnfGYfTNccjEZ2K++udFsfwD45Mn9fsN33N8vT/hhGsMGRWF59jfE7j0xXI4462uyfb/LieucJjNw9W1rWHWbr6Vn3/zj/1zzKEV/gXnt15mi663h4y4mggn5Z391RArwoVer8lP+E8x9cR6cuOJZ9gDfz72jHVjq8WyygNvda+Z8t8UeiyIA8C3Nfyr1RNqaAV930KN7Te+9BKON5A+rP3NBdgyyUmyk4fhZmf1leZ16F29886v4Ca+MhWf+WBIFJ50zM4XrPNmOMVO7rcuz/q5pQE7g0+5fB/Dsjcvy5nVMqpav56l1SauidOw5L1WdDxa/oiznznL7qYZA3wq5rzna+E48G/3c7hrrkRoeQqPVXd/sC3fGsp2Z6o3PMW26/Of5+S1VdUZ8OsyFcU113vsV1hwM1uHET3g3xJ1jZHy4wn8t/Ye+f5JOHYQp8Ann2nMTh/FFR9lq2nV76xnClypW4v/yeMHspOBcquS9PfV++o6p+N/xbWT7jndOvapxL/vc102eP45HJlNTSql/t3b+n4VhZ/6wa3BbIgPdPsax6WLtqnm1d+YB4rNbxhLC/WluWpDS3G8+/BTGNbugvEtlDMlax/l5IQV4OB01+Lbmzv4O3RvqnPWZ/NqjLvEpV9/UK/KIV/9Iwo3mkNt8bbLdXHI0l8Mp/PSu8Xabfx6omdRs0Sh3E0B5tCh+0dqQ/nelCOkg/nygiFPur+1X6aG3rxSHF4pjScUll/DoZfF+p3i1nqYeqR1IqS/y7rdr27O97vzz4q42AC1iW7t5fjy2If3xqGSeaWIE23c67RY1SG9+KGWOW8RzKnsWP7WsBx+04d++Njc1mL2b67ViT5gy4jB/Mv6X4Mx5ybTVTv2C9uKiTWvD1KjacU3vhBn4NnzPcSCI3hBDet/1rjF0LvGwMeC8kg1ndynEuHRB9k+PprjLC7s2DObYaK1++2sHgmOWZ0+F3fhc9ay81r+FtPjAfk0XNz6u5rsJRjbUixhF71WWw92vie/WjjbLWPtj/h5mHR4mc78/JKM+yUOx/w8QV48LtbPS4SBGWHocbrbCxdzGp97puWv43fAiO3wA//fKTb2sc6F4NmPm8TcUfbdLcYTp/Gn94yrTGxN1V7+gBtiZxF5d748ceiIx592r+av4vVqgA2GeKbMemSqIL4dE6vNayR72IePdh/od3Y6FM5cZMdnnoSHehV1lrEp65z9S/6Ym87xsbe688PVaoSZnYdDFV+K1/M=
*/