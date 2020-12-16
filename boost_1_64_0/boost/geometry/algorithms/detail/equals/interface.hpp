// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014, 2015, 2016, 2017, 2019.
// Modifications copyright (c) 2014-2019 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_EQUALS_INTERFACE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_EQUALS_INTERFACE_HPP


#include <cstddef>

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/reverse_dispatch.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/relate.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template
<
    typename Geometry1,
    typename Geometry2,
    typename Tag1 = typename tag<Geometry1>::type,
    typename Tag2 = typename tag<Geometry2>::type,
    typename CastedTag1 = typename tag_cast<Tag1, pointlike_tag, linear_tag, areal_tag>::type,
    typename CastedTag2 = typename tag_cast<Tag2, pointlike_tag, linear_tag, areal_tag>::type,
    std::size_t DimensionCount = dimension<Geometry1>::type::value,
    bool Reverse = reverse_dispatch<Geometry1, Geometry2>::type::value
>
struct equals: not_implemented<Tag1, Tag2>
{};


// If reversal is needed, perform it
template
<
    typename Geometry1, typename Geometry2,
    typename Tag1, typename Tag2,
    typename CastedTag1, typename CastedTag2,
    std::size_t DimensionCount
>
struct equals<Geometry1, Geometry2, Tag1, Tag2, CastedTag1, CastedTag2, DimensionCount, true>
    : equals<Geometry2, Geometry1, Tag2, Tag1, CastedTag2, CastedTag1, DimensionCount, false>
{
    template <typename Strategy>
    static inline bool apply(Geometry1 const& g1, Geometry2 const& g2, Strategy const& strategy)
    {
        return equals
            <
                Geometry2, Geometry1,
                Tag2, Tag1,
                CastedTag2, CastedTag1,
                DimensionCount,
                false
            >::apply(g2, g1, strategy);
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_strategy
{

struct equals
{
    template <typename Geometry1, typename Geometry2, typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        return dispatch::equals
            <
                Geometry1, Geometry2
            >::apply(geometry1, geometry2, strategy);
    }

    template <typename Geometry1, typename Geometry2>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             default_strategy)
    {
        typedef typename strategy::relate::services::default_strategy
            <
                Geometry1,
                Geometry2
            >::type strategy_type;

        return dispatch::equals
            <
                Geometry1, Geometry2
            >::apply(geometry1, geometry2, strategy_type());
    }
};

} // namespace resolve_strategy


namespace resolve_variant {

template <typename Geometry1, typename Geometry2>
struct equals
{
    template <typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        concepts::check_concepts_and_equal_dimensions
            <
                Geometry1 const,
                Geometry2 const
            >();

        return resolve_strategy::equals
                ::apply(geometry1, geometry2, strategy);
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T), typename Geometry2>
struct equals<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>, Geometry2>
{
    template <typename Strategy>
    struct visitor: static_visitor<bool>
    {
        Geometry2 const& m_geometry2;
        Strategy const& m_strategy;

        visitor(Geometry2 const& geometry2, Strategy const& strategy)
            : m_geometry2(geometry2)
            , m_strategy(strategy)
        {}

        template <typename Geometry1>
        inline bool operator()(Geometry1 const& geometry1) const
        {
            return equals<Geometry1, Geometry2>
                   ::apply(geometry1, m_geometry2, m_strategy);
        }

    };

    template <typename Strategy>
    static inline bool apply(
        boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry1,
        Geometry2 const& geometry2,
        Strategy const& strategy
    )
    {
        return boost::apply_visitor(visitor<Strategy>(geometry2, strategy), geometry1);
    }
};

template <typename Geometry1, BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct equals<Geometry1, boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    template <typename Strategy>
    struct visitor: static_visitor<bool>
    {
        Geometry1 const& m_geometry1;
        Strategy const& m_strategy;

        visitor(Geometry1 const& geometry1, Strategy const& strategy)
            : m_geometry1(geometry1)
            , m_strategy(strategy)
        {}

        template <typename Geometry2>
        inline bool operator()(Geometry2 const& geometry2) const
        {
            return equals<Geometry1, Geometry2>
                   ::apply(m_geometry1, geometry2, m_strategy);
        }

    };

    template <typename Strategy>
    static inline bool apply(
        Geometry1 const& geometry1,
        boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry2,
        Strategy const& strategy
    )
    {
        return boost::apply_visitor(visitor<Strategy>(geometry1, strategy), geometry2);
    }
};

template <
    BOOST_VARIANT_ENUM_PARAMS(typename T1),
    BOOST_VARIANT_ENUM_PARAMS(typename T2)
>
struct equals<
    boost::variant<BOOST_VARIANT_ENUM_PARAMS(T1)>,
    boost::variant<BOOST_VARIANT_ENUM_PARAMS(T2)>
>
{
    template <typename Strategy>
    struct visitor: static_visitor<bool>
    {
        Strategy const& m_strategy;

        visitor(Strategy const& strategy)
            : m_strategy(strategy)
        {}

        template <typename Geometry1, typename Geometry2>
        inline bool operator()(Geometry1 const& geometry1,
                               Geometry2 const& geometry2) const
        {
            return equals<Geometry1, Geometry2>
                   ::apply(geometry1, geometry2, m_strategy);
        }

    };

    template <typename Strategy>
    static inline bool apply(
        boost::variant<BOOST_VARIANT_ENUM_PARAMS(T1)> const& geometry1,
        boost::variant<BOOST_VARIANT_ENUM_PARAMS(T2)> const& geometry2,
        Strategy const& strategy
    )
    {
        return boost::apply_visitor(visitor<Strategy>(strategy), geometry1, geometry2);
    }
};

} // namespace resolve_variant


/*!
\brief \brief_check{are spatially equal}
\details \details_check12{equals, is spatially equal}. Spatially equal means
    that the same point set is included. A box can therefore be spatially equal
    to a ring or a polygon, or a linestring can be spatially equal to a
    multi-linestring or a segment. This only works theoretically, not all
    combinations are implemented yet.
\ingroup equals
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\tparam Strategy \tparam_strategy{Equals}
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\param strategy \param_strategy{equals}
\return \return_check2{are spatially equal}

\qbk{distinguish,with strategy}
\qbk{[include reference/algorithms/equals.qbk]}
 */
template <typename Geometry1, typename Geometry2, typename Strategy>
inline bool equals(Geometry1 const& geometry1,
                   Geometry2 const& geometry2,
                   Strategy const& strategy)
{
    return resolve_variant::equals
            <
                Geometry1, Geometry2
            >::apply(geometry1, geometry2, strategy);
}


/*!
\brief \brief_check{are spatially equal}
\details \details_check12{equals, is spatially equal}. Spatially equal means
    that the same point set is included. A box can therefore be spatially equal
    to a ring or a polygon, or a linestring can be spatially equal to a
    multi-linestring or a segment. This only works theoretically, not all
    combinations are implemented yet.
\ingroup equals
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\return \return_check2{are spatially equal}

\qbk{[include reference/algorithms/equals.qbk]}
 */
template <typename Geometry1, typename Geometry2>
inline bool equals(Geometry1 const& geometry1, Geometry2 const& geometry2)
{
    return resolve_variant::equals<Geometry1, Geometry2>
                          ::apply(geometry1, geometry2, default_strategy());
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_EQUALS_INTERFACE_HPP


/* interface.hpp
pLbXb1I+eKASa6q7GAvqzt0s505etPN7GJcdu9fRvTpuJrA8/1R4juDw7zHubSX7jftojsvzYvrM6fEfEr4Ve7rSImA+v3VcfO9+QOBoc6jK1I/+GPJ7oMXdwbmtqX50YnAysssVql1+zmVze4M89ktg1sp0P2SjZ3WQByrOxOJ4TvNJNR8PpvPEejDn89/w9jRYgkpaSarC55cgTHUgqRmFFYLJLIc9C2ETQBSWbfI7U7Yy1WI4R33jlHGbEkRxN2oH22BN+R+1/Gke62/sLX9+dX1K9rQ0802jRGT3Bv+0T+FTDsRL9xt6uwod69at7l57LKQrenvo0zR05N7YF+S+o9d3dazoFRLz3v2JOPLa3Yn38Fd1r+0S2LruTvwfiXubed6/wVf94fvauLE8iksEysmCtkLbxnmc+P83uRZn/5QJlknq+MVzF2wpLVl06KK5C1Yl5tdK/EzOXTBaxXAjddx7Yi9pFbL038Lqro61hY61Kwpr8Aekq6G9Fd3pn3BB9hV6uzo3rO9Ktdu1Di+PdPQZxW5Y293Zs6LLkPyfa1aU5i7oKRnb4QH0VQazf7yqMnfBAFWeUnlioy3ncZ0b+6rV4WTjml782bZkId6jb19qkI6+1WtWdrpa1+Lt30QUNmyjr+Kv7epbeULvimM3Llm4bGGbC/0/vau/dNGy9Gn+gfrYtkdiH+enWjCPxtsd0P/h/ZNdMUdC7/dZ/HwOP5/HzwdQN27Av/9rcv9LsW0UWyqjabn70PBOiL+VXmf77Rv3Cebh+N2Dyo+a6uYoftycuUeEpQvv9C5W9K9PI7YDzBylwbUy9sxsNNdzD2xORuJx5VZ1XHkU6azAkXobbnykybT0+5O+rKb1N07L7vVt7P4qk1Z6rXq5VI7LdbvqA3jCpoUgizN3snvOkyGn6XvUfb4QLs7XN1Sf6T8pzSBLje5ttenl6Pybqs7/zek1rXP85KR1t5oWJgdIy+8VXyx9itsBY13rd8jvQBwHtU2BtUusxWOcbmumzo0izW2xL67XX1xQ7Xufat8dXV4QbhvTy9H5/arOd+L0ov3zvwUTmP2009ibcyYPg+nf2n6Qn+yj7Rl8ls0Dpc7y51j5YBN38HP6BeXb2y/U9J+HdFyYammy4XJWc/uUX6t9yvNFHd6W9wU4Ta0+/VatT7vbNKvb2F9Uc/uLP6j1aU+X3jb0FzUeELLvKYm04rZZ28a2efJ4KWese0Qt2162bCePF9OA4w3eS2LSSh/fw9I1TutRNa19bFomXHWEzrmacX025O3Px1wXnO/bb3X7WlmbkO1vZcuMrAl712t5Y/KTats5COkUTEffZD22z10o6fwrajtSH3RWBiGx8QYeVuwtjXVmHrwvF1NWi8NeZDETMkEk/C45Y5Qn+CV0OaUt7jg4OIOPjzoG19EXCw5e7Xe59uX6JT7EGi84po+FoHxN2Aye43Zdl8+YpbWbhZQn63E224xN8ITvA87iTeZna2473lnNT7tNb2vYjunefWCl52MsAO9+W7dXWdkLjKzRfG3Cf/7lkeg9o1laGzza5Otoev6/UArfojjGY+zjd37a1cCMS6O0qdZCMnqrBBnor4yxnueTzL6/b/KGSTynj/sVLZ7wXUEx5jXm9bl2nsdMtauVy/XgvsV1jItvMOb8F8fRYfOG7dsic4gjLM8IXH6oI3r+D085hLktDw47UmIogcQOkRjplvVOmD3SHt6v0kYYQky45Dy2lDGXHO/rZQw+uMxbs2wn+B/DczStLKfk5FkmxpAcY5ye82dScq2hXrH5eNx0FFRhRF7WG9tVUbUonK9ffZDjm3Ja5/w+BsjAMeT+UewckvsJVu3uMHI=
*/