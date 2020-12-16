// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2018, 2019.
// Modifications copyright (c) 2018, 2019 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CONCEPTS_WITHIN_CONCEPT_HPP
#define BOOST_GEOMETRY_STRATEGIES_CONCEPTS_WITHIN_CONCEPT_HPP



#include <boost/concept_check.hpp>
#include <boost/core/ignore_unused.hpp>
#include <boost/function_types/result_type.hpp>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tag_cast.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/concepts/box_concept.hpp>
#include <boost/geometry/geometries/concepts/point_concept.hpp>

#include <boost/geometry/util/parameter_type_of.hpp>


namespace boost { namespace geometry { namespace concepts
{


/*!
\brief Checks strategy for within (point-in-polygon)
\ingroup within
*/
template <typename Point, typename Polygonal, typename Strategy>
class WithinStrategyPolygonal
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS

    typedef typename geometry::point_type<Polygonal>::type point_of_segment;

    // 1) must define state_type
    typedef typename Strategy::state_type state_type;

    struct checker
    {
        template <typename ApplyMethod, typename ResultMethod>
        static void apply(ApplyMethod, ResultMethod)
        {
            typedef typename parameter_type_of
                <
                    ApplyMethod, 0
                >::type point_type;
            typedef typename parameter_type_of
                <
                    ApplyMethod, 1
                >::type segment_point_type;

            // CHECK: apply-arguments should both fulfill point concept
            BOOST_CONCEPT_ASSERT
                (
                    (concepts::ConstPoint<point_type>)
                );

            BOOST_CONCEPT_ASSERT
                (
                    (concepts::ConstPoint<segment_point_type>)
                );

            // CHECK: return types (result: int, apply: bool)
            BOOST_MPL_ASSERT_MSG
                (
                    (boost::is_same
                        <
                            bool, typename boost::function_types::result_type<ApplyMethod>::type
                        >::type::value),
                    WRONG_RETURN_TYPE_OF_APPLY
                    , (bool)
                );
            BOOST_MPL_ASSERT_MSG
                (
                    (boost::is_same
                        <
                            int, typename boost::function_types::result_type<ResultMethod>::type
                        >::type::value),
                    WRONG_RETURN_TYPE_OF_RESULT
                    , (int)
                );


            // CHECK: calling method apply and result
            Strategy const* str = 0;
            state_type* st = 0;
            point_type const* p = 0;
            segment_point_type const* sp = 0;

            bool b = str->apply(*p, *sp, *sp, *st);
            int r = str->result(*st);

            boost::ignore_unused(r, b, str);
        }
    };


public :
    BOOST_CONCEPT_USAGE(WithinStrategyPolygonal)
    {
        checker::apply(&Strategy::template apply<Point, point_of_segment>,
                       &Strategy::result);
    }
#endif
};

template <typename Point, typename Box, typename Strategy>
class WithinStrategyPointBox
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS

    struct checker
    {
        template <typename ApplyMethod>
        static void apply(ApplyMethod)
        {
            typedef typename parameter_type_of
                <
                    ApplyMethod, 0
                >::type point_type;
            typedef typename parameter_type_of
                <
                    ApplyMethod, 1
                >::type box_type;

            // CHECK: apply-arguments should fulfill point/box concept
            BOOST_CONCEPT_ASSERT
                (
                    (concepts::ConstPoint<point_type>)
                );

            BOOST_CONCEPT_ASSERT
                (
                    (concepts::ConstBox<box_type>)
                );

            // CHECK: return types (apply: bool)
            BOOST_MPL_ASSERT_MSG
                (
                    (boost::is_same
                        <
                            bool,
                            typename boost::function_types::result_type<ApplyMethod>::type
                        >::type::value),
                    WRONG_RETURN_TYPE
                    , (bool)
                );


            // CHECK: calling method apply
            Strategy const* str = 0;
            point_type const* p = 0;
            box_type const* bx = 0;

            bool b = str->apply(*p, *bx);

            boost::ignore_unused(b, str);
        }
    };


public :
    BOOST_CONCEPT_USAGE(WithinStrategyPointBox)
    {
        checker::apply(&Strategy::template apply<Point, Box>);
    }
#endif
};

template <typename Box1, typename Box2, typename Strategy>
class WithinStrategyBoxBox
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS

    struct checker
    {
        template <typename ApplyMethod>
        static void apply(ApplyMethod const&)
        {
            typedef typename parameter_type_of
                <
                    ApplyMethod, 0
                >::type box_type1;
            typedef typename parameter_type_of
                <
                    ApplyMethod, 1
                >::type box_type2;

            // CHECK: apply-arguments should both fulfill box concept
            BOOST_CONCEPT_ASSERT
                (
                    (concepts::ConstBox<box_type1>)
                );

            BOOST_CONCEPT_ASSERT
                (
                    (concepts::ConstBox<box_type2>)
                );

            // CHECK: return types (apply: bool)
            BOOST_MPL_ASSERT_MSG
                (
                    (boost::is_same
                        <
                            bool,
                            typename boost::function_types::result_type<ApplyMethod>::type
                        >::type::value),
                    WRONG_RETURN_TYPE
                    , (bool)
                );


            // CHECK: calling method apply
            Strategy const* str = 0;
            box_type1 const* b1 = 0;
            box_type2 const* b2 = 0;

            bool b = str->apply(*b1, *b2);

            boost::ignore_unused(b, str);
        }
    };


public :
    BOOST_CONCEPT_USAGE(WithinStrategyBoxBox)
    {
        checker::apply(&Strategy::template apply<Box1, Box2>);
    }
#endif
};

// So now: boost::geometry::concepts::within
namespace within
{

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template
<
    typename Geometry1, typename Geometry2,
    typename FirstTag, typename SecondTag, typename CastedTag,
    typename Strategy
>
struct check_within
{};


template
<
    typename Geometry1, typename Geometry2,
    typename AnyTag,
    typename Strategy
>
struct check_within<Geometry1, Geometry2, point_tag, AnyTag, areal_tag, Strategy>
{
    BOOST_CONCEPT_ASSERT( (WithinStrategyPolygonal<Geometry1, Geometry2, Strategy>) );
};


template <typename Geometry1, typename Geometry2, typename Strategy>
struct check_within<Geometry1, Geometry2, point_tag, box_tag, areal_tag, Strategy>
{
    BOOST_CONCEPT_ASSERT( (WithinStrategyPointBox<Geometry1, Geometry2, Strategy>) );
};

template <typename Geometry1, typename Geometry2, typename Strategy>
struct check_within<Geometry1, Geometry2, box_tag, box_tag, areal_tag, Strategy>
{
    BOOST_CONCEPT_ASSERT( (WithinStrategyBoxBox<Geometry1, Geometry2, Strategy>) );
};


} // namespace dispatch
#endif


/*!
\brief Checks, in compile-time, the concept of any within-strategy
\ingroup concepts
*/
template <typename Geometry1, typename Geometry2, typename Strategy>
inline void check()
{
    dispatch::check_within
        <
            Geometry1,
            Geometry2,
            typename tag<Geometry1>::type,
            typename tag<Geometry2>::type,
            typename tag_cast<typename tag<Geometry2>::type, areal_tag>::type,
            Strategy
        > c;
    boost::ignore_unused(c);
}


}}}} // namespace boost::geometry::concepts::within


#endif // BOOST_GEOMETRY_STRATEGIES_CONCEPTS_WITHIN_CONCEPT_HPP

/* within_concept.hpp
/JOPXbDzY1YkH5ti58egKFpk58YQSD52wc6PgZB8zI0/buyLO8rEpj8+9u+l5t91cfMjii7/4usN+moKYyCE51HoLBYU/WPGQGgmhoTl7i025+tTumPoG/oYluOxic+F50LskP9zId2KHMi2PCXP59b/RnrHhfS6sBy75vlc1m+k1y2k1z2k14Oh3MKzF+sufC5SbveG9O5jJd7PelzJNnyAvfgQ+3AVE2MYhOXOE5vz9UX3eOgjfA3b8ikO4NM8hc9wBJ/lGVzHmXyBc/hioo/J8NyEhwrpRPqYXBX6+HyYtfgoG3J1ns8v/43PXxv6FFnIWlzEhryeiXIPnz84SbnfEcr9Th7I5Ym+scPzBt4oNkfb3usbw+fYhrXYjs3ZnofzaA5mBw7nMRzPrryAx3MWT+Cl7MUr2ZsL2Y+L2J+JMRBCfo4Qm/P1OT0k1IOhrMBhrMnhbMAUHs7URH0MzxRYN0m53BLK5VYewNvy9km/pfD6f1nIx+Usx7l5+6QPn6suNufrw/388LkLWJ4Xsiov4n68OG8f8mE5FZOkPzEsZxIr8KxE+uG+mw2TpH9t+NxCVuB1rMmb2IA3J5YT7p/ZKsly/my+MpzP8ryS9XgVj+CCvMetsJwqSdZjVljOn1iZ6kjYH8J9Kg9Isj+MCesxlhU4jjU5PqdeFwv3m+E+1Ocda9Vrxl5fhv1xC+vyazbid2zJ73kcf/gXe3cCV0W1B3Ac3DJzAVRwQcV93zdwCRBUVFLc0TRAuCyKcGVRLFNccssFl4wsS9N8bhkupZWampnPtMxAITGtzMzKzDYzq/e79/7vXIaZy6LW630e9/P+7xvjnTlnzpyZOXdmzhkchrcwFH/DWLyNKfg7zsE/cC7+icvRoRT1GhxxC5bC17AsHsJy+BHehxewAl7FB7AGma6MndEFg7AqDsFqGI1uGI81cTK643Ssi4uwHr6E9XEfNsVT2AzPY3O8hK2QZTm0xrbYBodiWxyNnfEgdsVs9MTb6IWl2ZA9sAr6YCvshb3QD/thbwzCfjgO++MCHIDrMBDfwYfwBA7CSzgEf8ZhWJ0NPwLdcRR64Wjsg2MwCENwDIZiNIbheIzAyRiFj+F4fBon4A6ciHvRiEdwEh7FJPwck/E6TsFfcCr+io+jM/VqOnbGGdgLU7EPzsIBOBupj7wbQX43y+9p6iN1mPwx3UHeJeGKuVgPz2ML/AQ74gX0xYvYDz/HofgFjsUrGI9fYRJexWn4DT6J13ANfoev43V8F7/HD7Ey9fYcVsGr6ITfozMSDtWwOVbHjuiK3lgTB2AtHIq1MQrr4Eysi9vRA09jfTyLDTEHG+EVbIwVKZMm6Iwt0BNb4hhshWHYFidiO5yB7XEOdsR07IRrsAtuxa64G7vhYeyO72JPPIO98BscgLcwEP/EQejEtgnCujgYm+EQbI0j0BNHYi8MxigchWkYirtxHP4bw/EjjMBsNODHOB5v4UR0ol7FYXWMx86YgCMxESMxGafhFFyFKfgiTsOX8XHcg9PxbZyJH+IsPIez8Sucg9fxCfwN52JZ6uU8vA8X4P24EB/AJ7E6LsKGuBhb4BLsjEvRF9MwAJfhUFyOw3EljsRVOArTMRyfQQM+i+NxDSbj8/g4rsOluB2fwVdwHWbgJtyB+3EXnsJXMRNfU94tJddYcIVO+2+BtKsWogcuxi64BINwKYbjMkzC5TgZV+ASfAot7Ve5doLDddqvTaQd1RTrYjPsjs3RG1viAGyNQdgGLedPuVaCDYjgfOdPV8m/G9bBGsh8lI9c75DrIFeIjjJujulzSOY7jA3xGLbC4/ggnsBAPInB+D5G4AdoxFM4DT/E6XgaF+I=
*/