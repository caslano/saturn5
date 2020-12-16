// Boost.Geometry

// Copyright (c) 2017-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DENSIFY_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DENSIFY_HPP


#include <boost/geometry/algorithms/detail/convert_point_to_point.hpp>
#include <boost/geometry/algorithms/detail/signed_size_type.hpp>
#include <boost/geometry/arithmetic/arithmetic.hpp>
#include <boost/geometry/arithmetic/dot_product.hpp>
#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/strategies/densify.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_most_precise.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace densify
{


/*!
\brief Densification of cartesian segment.
\ingroup strategies
\tparam CalculationType \tparam_calculation

\qbk{
[heading See also]
[link geometry.reference.algorithms.densify.densify_4_with_strategy densify (with strategy)]
}
 */
template
<
    typename CalculationType = void
>
class cartesian
{
public:
    template <typename Point, typename AssignPolicy, typename T>
    static inline void apply(Point const& p0, Point const& p1, AssignPolicy & policy, T const& length_threshold)
    {
        typedef typename AssignPolicy::point_type out_point_t;
        typedef typename select_most_precise
            <
                typename coordinate_type<Point>::type,
                typename coordinate_type<out_point_t>::type,
                CalculationType
            >::type calc_t;

        typedef model::point<calc_t, geometry::dimension<Point>::value, cs::cartesian> calc_point_t;
        
        calc_point_t cp0, cp1;
        geometry::detail::conversion::convert_point_to_point(p0, cp0);
        geometry::detail::conversion::convert_point_to_point(p1, cp1);

        // dir01 = xy1 - xy0
        calc_point_t dir01 = cp1;
        geometry::subtract_point(dir01, cp0);
        calc_t const dot01 = geometry::dot_product(dir01, dir01);
        calc_t const len = math::sqrt(dot01);

        BOOST_GEOMETRY_ASSERT(length_threshold > T(0));

        signed_size_type n = signed_size_type(len / length_threshold);
        if (n <= 0)
        {
            return;
        }

        // NOTE: Normalization will not work for integral coordinates
        // normalize
        //geometry::divide_value(dir01, len);

        calc_t step = len / (n + 1);

        calc_t d = step;
        for (signed_size_type i = 0 ; i < n ; ++i, d += step)
        {
            // pd = xy0 + d * dir01
            calc_point_t pd = dir01;

            // without normalization
            geometry::multiply_value(pd, calc_t(i + 1));
            geometry::divide_value(pd, calc_t(n + 1));
            // with normalization
            //geometry::multiply_value(pd, d);
            
            geometry::add_point(pd, cp0);

            // NOTE: Only needed if types calc_point_t and out_point_t are different
            // otherwise pd could simply be passed into policy
            out_point_t p;
            assert_dimension_equal<calc_point_t, out_point_t>();
            geometry::detail::conversion::convert_point_to_point(pd, p);
            
            policy.apply(p);
        }
    }
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

template <>
struct default_strategy<cartesian_tag>
{
    typedef strategy::densify::cartesian<> type;
};


} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::densify


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DENSIFY_HPP

/* densify.hpp
MRrlkBlEulPkOs52/lXtLlSrlmN6a5j3eZt5vWY7Bqb114VxWOrc9wn9VVvLdF+56p7css0u8Bjw9QnNK/Le49j7P1qfEcg037PBdn5lFGHEJ+0CROn/DD5kgK8feBPpB34F/whLtazXzKzcDFUqZeg7e76+cQOaGPlQNRLTrG2Shd5t7LLk35rPRySfbslnquRzc0A+SbPc+WSRi86n9CcYqBOZQAiX9p9o4otI8+XTaAFT3dHKsI+Yx0qEXx82M/+DjbwyJNevP8kuyUeB5CNXRci8a5zyYQzpLb3MZH8KyIuUh/nOWvsYjSt0BDcFkQ9xqCqPGX75UFWDutIpw7ar6aqu11HFYfn/Zu//K4ev0v9uFZ/Q1/j/9d7/Rxn/v8b7/z7G/+d5/9/b+L/H+/9exv+zvP/vaS0Ha79FW30RP0j2gyC9vyZirDquMvzX+7fql67qS18bRntvfWE/l4epnUna/prKNeRw1cbm9suXylZuhtrIpe6jUo/53k0t9dgzje19+ROt1zb+xyDT2PzWc6uULRP9rgWKZR16qTjkfaYj1L49M3Adsspw7SNl5suv/7E0WO6JguSeCEepdlNLen6jDEq9/nC8JrX385dzrrfuZ7CftT+EOc3al9mcN41mgHnWfhDmNLnftF5/5HIbm66S9u9r79T32e8a5yq/MYFpLGMvu8whvjbdJtKmO1od/1m+spNCSzFy6M644PsU6zWa3N9b10W2s1lnZlLpSfuu5DVjqE7kB3UsGu8J1m0tJ3x5JY+eXOrMXDqFmBfZRqNLWe9DPH75nu/QrlLs167SQraXtFVw7edt4JdmNrm+8c5j/tn/2YB9Meuz58wYndFt8sz2PnlmGzm79HU3HtqWcf0D9nnrupahnSQqoE+AvubLZNslxehnzitVngPut/O9bSPfyN9fDbfff26P1Zm9TJ6nNcQxqk9yjrcM5NLZuPuksT0tp6zbPeCZmuVes77tHkPdxrjd3EXJeSbwmjXwPlruSQKvY+X49GtjoLyyKatHYjmhsWLRuaxfQH98vaZkI7AOMMd0hPv631nr58Uj5NnXpdSX4lh18Hvs5SiDx4zy21mG833PBXKfTMr9Crzn494umdbRN62XOa2pb1pPc1oN37Qe5rRz+d5p3c1p3/imdTPKjWlH2Vm9/TnV2VWuN6bN19PduRnS/8u+vff6tS3sdxjrdsA21k36nPn1XW3ssI1mZqcZ+ZD9yLynNR4quiz3BYV+dbhsP6n3rfuInK+tz0wDnlfI+2UkcV+fKhnnk5VOS0Behtvsh8G+dnY443PVc6s5qqz8x4nkmeddmV+/ZLoXx+D6fGsbqjm/2dzgu8dopY8VGU+Wa8TzM2kujtPPLfIKfPVCseUcJvex5rnCyIM1H9vj9PiyNUXW5w7m9kxP88/3fPb/9pWYONeX72j7NjMe8lj7RTUK13GlZOTqeOL0u5bVfjNF4pFnF2Y8KgrqRXtfKZleIHnyxlVIXCoPb83zrcM23z5pnrcDjmXe3Wz8XpR2lz/jeNWesMj/WDbqnHKfu6UfsFn2ct629u8KrH/q2645pI+qlHOUX/9V699aOe+7RhkVj+Bcz7rext/rLfaVUYS3D0h6lrRJ2a4ZouP1yk1Wz6XUfFhNtQtc7V8+jNXNzkpXTzAsTx2N8lpRUnlJPdSqmLgs/Sulz6/0B/IOiXbo7xLYJtVM9kVfGVlz4zL+HuetQ7x/S5GdymyjCXx+Ksf55pH6/d0qzdHXWJ6hBS4jz4sC+wqZ8XSibKeq7XytLx5PYDze8/pbMl9+Pb9r0NG6QI/LPnwUJ6jr92L/beROV23lF3JOr28Zz2o9/0qeZbo=
*/