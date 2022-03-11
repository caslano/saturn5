// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_CORE_POINT_ORDER_HPP
#define BOOST_GEOMETRY_CORE_POINT_ORDER_HPP


#include <boost/mpl/assert.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/util/bare_type.hpp>

namespace boost { namespace geometry
{

/*!
\brief Enumerates options for the order of points within polygons
\ingroup enum
\details The enumeration order_selector describes options for the order of
    points within a polygon. Polygons can be ordered either clockwise or
    counterclockwise. The specific order of a polygon type is defined by the
    point_order metafunction. The point_order metafunction defines a value,
    which is one of the values enumerated in the order_selector

\qbk{
[heading See also]
[link geometry.reference.core.point_order The point_order metafunction]
}
*/
enum order_selector
{
    /// Points are ordered clockwise
    clockwise = 1,
    /// Points are ordered counter clockwise
    counterclockwise = 2,
    /// Points might be stored in any order, algorithms will determine it on the
    /// fly (not yet supported)
    order_undetermined = 0
};

namespace traits
{

/*!
\brief Traits class indicating the order of contained points within a
    ring or (multi)polygon, clockwise, counter clockwise or not known.
\ingroup traits
\tparam Ring ring
*/
template <typename Ring>
struct point_order
{
    static const order_selector value = clockwise;
};


} // namespace traits


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace point_order
{

struct clockwise
{
    static const order_selector value = geometry::clockwise;
};


}} // namespace detail::point_order
#endif // DOXYGEN_NO_DETAIL



#ifndef DOXYGEN_NO_DISPATCH
namespace core_dispatch
{

template <typename Tag, typename Geometry>
struct point_order
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_GEOMETRY_TYPE
            , (types<Geometry>)
        );
};

template <typename Point>
struct point_order<point_tag, Point>
    : public detail::point_order::clockwise {};

template <typename Segment>
struct point_order<segment_tag, Segment>
    : public detail::point_order::clockwise {};


template <typename Box>
struct point_order<box_tag, Box>
    : public detail::point_order::clockwise {};

template <typename LineString>
struct point_order<linestring_tag, LineString>
    : public detail::point_order::clockwise {};


template <typename Ring>
struct point_order<ring_tag, Ring>
{
    static const order_selector value
        = geometry::traits::point_order<Ring>::value;
};

// Specialization for polygon: the order is the order of its rings
template <typename Polygon>
struct point_order<polygon_tag, Polygon>
{
    static const order_selector value = core_dispatch::point_order
        <
            ring_tag,
            typename ring_type<polygon_tag, Polygon>::type
        >::value ;
};

template <typename MultiPoint>
struct point_order<multi_point_tag, MultiPoint>
    : public detail::point_order::clockwise {};

template <typename MultiLinestring>
struct point_order<multi_linestring_tag, MultiLinestring>
    : public detail::point_order::clockwise {};


// Specialization for multi_polygon: the order is the order of its polygons
template <typename MultiPolygon>
struct point_order<multi_polygon_tag, MultiPolygon>
{
    static const order_selector value = core_dispatch::point_order
        <
            polygon_tag,
            typename boost::range_value<MultiPolygon>::type
        >::value ;
};

} // namespace core_dispatch
#endif // DOXYGEN_NO_DISPATCH


/*!
\brief \brief_meta{value, point order (clockwise\, counterclockwise),
    \meta_geometry_type}
\tparam Geometry \tparam_geometry
\ingroup core

\qbk{[include reference/core/point_order.qbk]}
*/
template <typename Geometry>
struct point_order
{
    static const order_selector value = core_dispatch::point_order
        <
            typename tag<Geometry>::type,
            typename util::bare_type<Geometry>::type
        >::value;
};

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_CORE_POINT_ORDER_HPP

/* point_order.hpp
4/aeOg3bsg7HIMoOwAz5vceL+OB91Q2QzaGNzMbRc//P/DqUf8wDWHQkpf/Or9P6p1/HM1SHBswAK9x31bThK9JoDybXJ3LtVd9oJMXYWZOiffq6U8WLo6GM00LZs1K+cV0ja7DgrTeqrRfP5m4Jm0vqr6iYTzCJeV8QFk4wBJ0Z0ZSLWmf3AeDh4AG1+z1x/x/t68H/kzD/0S4uzKV7/g7v0j/nhUNJRPD9/KjC28nIyBIB/bn+qKpgwKF7kEEkeuwStn1QtdKIYZxaIgJEdcxhIR9hrPoDQJ8xGk+MviYjANwGBbkFFx6Ww9Sf9RJk6Vq0yzhEfmHl+n7osNm9S4l7sTWKmrZYmmdjdQ8uFh8qEG4JNyxpRPzIWfdMtLdKu0M6aBr74ivcNKOS3zf6ahbDwN6Uyh23wZY9Yopceothrjrg2dM/OHwynXtvhoGWlfc0hJwP/KAIcctjjDPsAV3xc64OfQIQw1wfVX9+zrniaDzwBbjvWTQYIqg5/z+Y36H+5cD+g6dPhrX1v1vXbfyTp4tFAQlQBkSwGd2TgBArj1lQbBOmUMzNCNc0JjdI112gzrAdlXvk/pkVIiM9Vig4bUX8fGHEW4TrZ1SwnCnZ0I7qAjHi9mCi8leifAQnd16vt4y3cFfPyFDrT8EXL01cDtNhgJ+rZ5xj4gBdiT+clR7IF6TSorumjImZpozcYhoae/LTMoaDDaN070M7xWy8w1S643B7dXGI97YhrphdFNIAPWGQHrDk9zCG/nDIzqdDHI8rIuKLOpyVXvBPzbg0eUsWoSYVeiaKosLvpGFhUOft8ESg7wAcfiWSh1zwiP+oXqH/STb/4ItkaC/l/1KvUP5KQID0TEwAAFTxL77MtrpSuazwRFBDvpi4uBqWm+NQdsNGY6Lw4ggVUPtJZuQJ2/J/rEG2CTOfUNQmENIrOZkTS2A0lpXCoqLKB7mhqTEgvGCj7KKuwLPXLXO9YUZsdjSUXV1JuWbIih1l/5kbkQCuf2NUeMPacxsJ7nxhvX8ez0U21Nc2zvkeLKzsw8yLwUIeLUdDXI40iT01OsKb5vCZNLvgBUYeyeAztKi65jZQB6KDkUYAx5AEU4/nMqUIfQcSptihUBjVgveO46AoIiyMaFJgH9XajBCHAsgMSfwwE4Eje1w5mGkbB0JQyu4PfuK/dDjupNi5BTZPV+iF6AJ1l+dPMQ7vpJZHBQM7jwA2VhcsuK2tE8UVQb0Om+U/yBOBus0PoJhSwmWmxhOBRsybrOMnikB1qmTZARJ5veX2U7M0M2Tm5rcMfvJjwF7DBkHwV8hUcUNSM8ytWnQ2FecJwVCryEPJAAALI5WgIRLWQTU2gQObP4L5UwFbwjkZGLw312VlZ3MsGfpdVdoWhYefabs7nxx9xjnL5JLMD704NmADkmRCMrX9d24eVjRed8+ghubYerggk7vteFm3UvhfrmZ2YI5GJi8WRaWvSeXO7YalfwpIl0o8JzjWICqDS75RhtIxyQzJ41NHo5+Hfp4X/hKi8vo5gPEd7Hyv0/DkF9ABL1jULzBJMQRbojX1Q7/YKSK67DIa7e2AoIY1wr65OMi4VMU64T8XmHJQULiuNNYAFkHgjJgiNKRKqVpmYT+zKKW6YAZ5a/NSaLmCwgiaSvnoIjD+wbO6JjPqKkr+BzMemcpyGjhlINkssMcvwnNDEEtl65ODpjKny4kufNEp2EntT2NG6Ylt2d65oZYU0xBqF1jAfcbysqak7kYHL8huG4eHuzbXET2HTZpWa5eoNMpImZYRVyDgOwcGdy3zOy8aLrX2pT2VDR31kJAPlUMKyFeVfF9VUd0bBgb36Fzl8s8+qOSlEK7RqqK9oF9wyc08lOxqazEKfX1zY5BoGybmLkNEkpqXORj1ThObI9bJIUv7ERnUXZkb4keXPRJpbQcofNw2J/PrbBRbHXf3nmeRd0cmYIDur1vHaashS9seKg9986Kv8zG+Mh4dNY0TyyPcYbHW9cm2Pibbh+O4hSQ+wooTYcMTq1Bo+GSXjtCFiAveNjTbheTHbs5vkmfPcdTSWzZ9cyEdsYFFNKrSeJKOf4AZpYFL4lx2Eaulvx+BSY5scMAnqyChbWi80tLqc74lAWv/RNC7kG0qurL9jDE7hQbzegrvcpOt0S4wOolWJHCtd3rFYpN82qppuF+4KdCStGWzwCbY8yFcNSkoTuUaJpJ0rKHCk2zoU08WMKaFeGtUX7P1kW6+H48uGvPVGZnTchiZ24Cdq2N2nW1JRmdsTSxqm4bOop7sMnCmlk42tzQfsBapZea4bU5+/JVAZVN/r6q5PNeyQJ7kucS2+HPA4yZZM/KOruuOD0SBjq2JfE/zP1unQf2V/jFe297Fi/3d+Hfxr/E6SkBygB6TP7FRUsgTUv2sPZrjWkUUswPONYNwlw5fZ8lQhDvMilIKVcWpYi0ZnzVh7cWd4lUGAZ8bt5rwSwL9yTW1rdnsTFse/UyP8GOqLs1qd+Tg1sBjDW0hX1hZJ+HB5C6MtZRo5CjFNFEnEkhg+juKy1DWsHyFo7ejJMXVm/QZwO+THeAENjTBQhOKAtJVWAlfgyUECZbdLLK+caT57CKbXg7fVAp9oi3AX3Tlbq73/sVML8OojW5JHFpQQe/xpnQdCCxbAL2LwJIh1se/awc2RubjoSa31YLbPd2Sq8CBCzX9BRb9ZmrIxPwPyejf+jZ/9fNk/+BPtvK97+/4i/vXuJjUATUgBysyDXKBknLSINruRxhSGUcKSwuMNeT9S9U4zVRzVYBRDdTSb+AjTBPW8NR+25iadZNj+z1sWhNQicQOpHbETlxtAEPyvX5Uf3BXtJYvnOkHiSeJhFcT6ExNOxQdIt7pnYcDSRIlv2bY8GrydeC0/WCegSKaepRdUnrxgkEq/GKPRuwlhLyQEbTcQ8zev9XNIP5K/xjHBhVU5//u/XT+WT+cpxjgeulhwWYlVcYxBQfcgCfcpEgwu7lbFEMlLqps24Di0lK+teMwDWyuesbGpy1rRIbtlJWzH9GTdgEIieMGz226T22K07zz0xg2s8o9BJR/X0b1aPrhGBfSdBOL+PwnPirI/+xja/dkm/s7vDz/xGvY+fa+6QtOofeXtp85cHtFkDnZe/u0zQd6hFA/kdMzyuj7tZvUpw9IpMeAGdj2/cIMalPDBKRCE08puAP7/yf146/2BfmP+lFYI7j7d3hU/oXnefqaAAuP3cV6tXgekRUFhPF52m5nI/Eh9JLfLeoL65NknIH+z5+gOzXFK6a8mxQsLCxErLZu9wlsUOyEiWAdyGb31xdScd5a6Cm6EgAwLsPSjumr/PM/4O0/wyn6L5zv09c5QBB6Bs/TfnEiJkz09H9gMcts4qnUA/eLmTAx0DOyY46BrpX9wZpbi4WJebMWCkt/IQRe+kgEovQG+DWHkWTheSX+H+BC+KtM/4FrwKXf5O9wcfyfuL526s6mt7yi75n09fR6p00M/ofCP2AQjZg+v77+sif944GII3LgACzprPg/9Oif/29Q/r/qm4CSf+qbhu9fbpQgNr2DfhhyZJPAeVudXy32X9PeJT5/eGJPq3vhqo+EZCQqZLv84rD9cIXE6ReH3xXGhJ+FgLCjtZdxZDQUQg92zHN546ofmAxihyOeYvfLG37+/HgDiqnr8f3y+Xx/OVuu+VP6GxsbnZ2dExMTkCfTOXy+z9dA/SH0oKCgiCFC931AmZKZ861tbfEiv7VKN//cZ8dEJIPzLAcC0FXgz8I+slT59+s50L/SP96bLBHq+9+9N9W/+J/I8Uz099cXrMcGAQFBAQH95+7QP6VC0G+gZ6TnL4cIANx1QYD9zMPw/s/GJ5L/Kf9kDCL2/9fyx5w3lMryyv7zfJVqIBAQobV9mEbDP3WR3m0F6/31JfRPoRdbDX/BfhEJWp1T/yGv0RAE4Mmk1sUHdIf478r/n+vEv3AYwKwd/x2O/n/2802JPNB/1olBpstwAUiVVpUiCsX1N6DZfSRu+HR6e1BWYDA4MFAqfTmURVV9Bjc8MNLXANtDAAHBQNT6efXON0DqgaHjZV4rGKD8V72KDhEl8xlbDSKRC41gA7oBUVKw2wwyIJMODSyrRDPfmVU73XF8j/JPKb02gnZ8TmNTxoWesHvQcGJrWlrN0Pad2YTLkPsuLW4hZ03iOFX+RpZ0qsRh5u7vfd/fruZpF5q/aTLb7jMTcDd012CK+QRKsOGc9gKyMP+/EvL/wIf4/+hJhuZrvX/W/RT/sq5Sxy1QBVBDehzLD9GHBBgi7Un6YJA2W+NaIQPoCJ+hecNid+cgZqI7iAhBnYnc9IUDkTGQOnOxgtqcVJsi08bqK9pz8+A41l/aS173vio8RLMvLzGUUienGijZB7JSfj73XYT+fN54kXj/uIAr61+vOsPI/41xhQBo9boTQO15ekUKs3tY26T43DMbfTxMO37g/qIH31mKjpR/r3B9U8KTPG21PcjJAAIAa7U1CrB+qEe0tB+9MGOT0RRRlFojg6Hxo/f5lTu0b5uamBY5HSkRKEujKjHLx0UifwPe8sykOup6CrPTAkWKJ0yGQoZO2btzfxFqx11kFtpik5b73fsFlWo/DgoVPE1xa/5C4x3yTXSUzRbhNi4axPVRLIA5I7fBQafhR30uJ1VxphQe2h09glJlh3hcRO6q7vm9KqHAWSluCY/ZI9cENZXJUejz2NNt8ATEGNq4wzK9AG3gAN3BxOrQd3Joyz0kSz6XXy86OD+o3zvtAxB7hekjI/SJu8fitOoWzk69ERJaJUVANaCz+Lk10v9kPZW8goYHuPRPxBPCbLrwx0mjG1mgOjlMLDdDpNls4BdWgDoHQElURZjrDIFK0U1UUprANWr6/0zdj1Av+LINEAZYkoCu7uveLTFfoirO6Cw8khHrwTYCB0h5BEjt/aHm7Gk31t1wZyOLnfWA6HQjUOWLSTWtiy2Wqs2L8R13svrTtJqxw7ZnieyYoOAtnaz19kXsP2v/HH+S2z/qmTiuhtTf6A4IRP/06C+0JKOMltU//wyCV1Wnp9k3z2gjrIw3JMk/4/RWf/hB3iipiMch4uMQEwnymwwNK6gRscoTj8L3gddFqKkhEQ4mgKITJohsjZLFR/O44O4dTbiZtFdc8hx9qW2cXp5mZ19W122Gh74WrRdxOp9m32V9uXc7Vvj/rDQipVIfk1CpT/h/uExGpe1+iaTj/QD088HueANsQJ01dsHDD60DTBVnepb3+XxfDV29j6Djcj7eTPn2Q558di7HUHquPzOmxdtxesHHoPxYADck8HbgOz3d71WqOu+vTCm+wKM1vK+znt0RQ+EdZxh8j32a3U5XF4muUjkv/cWTOs8Iq6W906hDZREuVSaOYn1raZlSl+V8zMrWvGcrnLZLX4Qz1hzjImI8BBPq+8M8V89FOe/P0gibrh53tp8HQ7Hia99e8ED8Jt4Jhzwvu7xvZ098fU2odH0NNBaalJoXDpKbQF9pK7dhp2iHDw8riMZkXtc2vFjYOzCXbMFfadUk5VI0KdfzqydVe3zMXzenu11MurpCBz8ShrnSv3EA2zMBhCbjh7BSYj3WCntFg/eKR9mgiSuIobmpxlCWiz05iTN/+Vmzk4DMRwPSCWkwrQMZYQCugNa0fbNZLTFkGRBxnE03jSUlhwXykaH1Zr9E4BiYWpVUaQFjEVeO2eqjcKJz2gxl7Hp7PRp+UHVgEpGLNXpLYF7L1C4Qdjg9YD2E0RvuAJmVbF4QUSAxMFZaqyXPNNU1DwQCDDclTMoJKr9EEHMbZnZi3Ex2M6DxEA6HXYdAK2CLQEoGhCQA/VbBD0AcM7Bslv4z7n6p354gwUOtvX80ZSUNMcpohAIyksc4ULIgIVzhvEYgI4C91M8EDsQ/yi+dv4zIHKGaxxYAmjFmroZaR4NuDZQBVMkCtqRET3mC1ghtJOExLpDwozfKCeKgdtjfiRAkj56h3k0OSS/8o/Wxk+jHyhrnBuUseh1NbXGcPASKCRgDYEJKTRHoGFQQPn5IgAkRfq7PrjbEal8cBhtEDxCduO+l48nf3PFkudRbWovZKL69pIWUDuwGnPlmBF2Lcj3OnIqijmcHgU3CxI9AhBc0gCYO3vncj7EuEje5QQ6mAdIOJDMzsWPsJktiTlgRDm8EnPxNlvgZM+4w/4AeIhQzt+M7T5mf17V8IV2rnCOYeMIvSdlPPytor4WBfKXmIfZTpAJgSxgrLUrR8OKy3tL+jyoI9QogJrFtLnqmfeY47dwJYhbLXNo4UjnT6AWxjfu8jiPSM1rxH+tgbhav/UpWnr0ekfZAGd2vGrG80OzC6pZrAVqSK6X5trL8iVlEpjHtxquu/pngzJZxpGot2KW29VIgo8DOk9xNL6zVFxEjR3qJHJZBlG4gSaArAU1ySODo/cXxHKddJxFGQINQftSiZJY9aKPqgZXg1izUpLm8ubR+c7mPAkmiCsDX1lp1bEoNYhcBUpAG9chSgaoN2PAP1WaU9Q3pGXCVVX5Z/E7SxFwEvc5wkld60cL2RnwQGoGrbHJQCR/NZbQBG5k92ePnOKlmaWTt/idyBBzCa7U+Kn2sO0T2FcCcQHHffsZoQDrHS4SWI+zM5W2VrRWWk0gC2NnozlgxBLp5fb1n4+AW3H/BHNtQi9xDPwKJSnuAFZuvfusLWoWiYAQaVegCqgXSsy/lVOb5SaTMtoBJzKADanfEWm0dd3RYMy3Z8EZIpRdSNi18n1sUj2ZVHgZKndgASpG5oiMcNOfHDA3+kJ0gaR4y901PgYUQpDcRgL823AR3u/hy1jB6iz+aSf3dg8gSMjutUk9XoLgvGOgcyqYRGZFa/vsYIQdFSfkPYmWQ/h2d3obI1sdAL3z1YQBVb5AFcCUoWL5gNv0PpxNQ59azNLty5B8Bi4TshMAO/CHW1713EP4brMsYSdog9PykJ1BEAmRGEo/mP4F/csvT0FokJqPS6PMjJ/g7KqJZA6IxHn9rjEW4at9UU205D3VUuy2jXbXvaqt2nv2fmZ8zbqoVOxoQlme9Hc0B+f0ZoJTyngGEchAucM46GMtdlevVDuhe7uv9XltLkAE7k9fdZH27pXgQW02OZhUiUwFN98u9HTYsgsCXwlWgWROTfu7yzHCUPxcjcMAi6KEoQqgHbPCC+VkK2f2QnwoVp/wtEMSBkKmZ/UpyyfzFU8kZ2SmYw4kQAkjxTnEKIX+Cl/prBKbiTXRI/PTjLxdzoYknSyefTSUSgBasrwmIHJ2oHJo4zW07x5MqKQdZ7DUAwZOHilvHntBf5nVlHMicwuWfZZGjZbVTsKLcQbsHTcedKyQtxxIWmIzjEjFJiMssjZkgXASxANfihyRkpMOh8vMgcuRkzNeXsPuRRq8c+LAxixwpQKoUCUQaslhVXQmkQjJHZL+jmQCAJMVgq1mLIR8ExIjPfHMLVusTn6FC5cF0Jv91hNuYDwynmI0a7ARsRAZbihFl3E+dAYz5rIh4TIvlSdyhGjXPUMmWG6CeuYQ1w6WEbYZeSepXDSYBcg+nAAcQmIP3JAdO31Oz2h5q2alpGyAIBBAZVLvaddMW9h4TXulbIzR3IYJZRBorlZXpaQKFzqJweC+ubkNZafcb1vZ6Chzfnk1ZzBSlBEk+aaIHeAMaRFc5ZqKj55HqcQQ4UiXr+cV7kwThHVmI8jaB/dcOcx7jEWHcrLvBuYqlMNmZI+hnUkHHMY/Z9DLAMcLlU6xKes3AG8Gwp3OLoa1FvD/G9GT1XjltwEBaAigwprE8y30PjBWffGph9NYEG0JWNMhLDFERf4KZK5+EozLCSeGIm8hJmNO3teGLwH1WBq4kBxuEg4KmilsHLsyYmY+5m5tKYPYG+LmiNKx+t2OVjGL1nwO6mKhHX0zRcUnM43PFb+kHbumPq8l0ZTXy+ULbd8LjtSw9gdzAbrCRjksupS5fl5HJ9YBOZiEaRQ4oTwX4J4U0EkIp2YAsCEKxs0lk1IC7akA4soQVQoJECQ1BVcBjT4oogfDAsWqyVVSV0hizEnImk09zXBHfboBlhkBoIB6ULWc9IW+yTQduinPgzReD8MtTxFHSJIYbSGEd3oh/52csZi9FSkKeyd1si3CdcJ0lcpVyuhad9NcHQPhVOoFOzpmZm5CRxKkLlAgAwwW5Wtq18YMcH3e7911kDS650u2SInqgW3J6DkRT7d567Gp/vRPkvH1n4mE0/2BLr3V2eLqXF+JccabUZ4uy4Aoy0/3q+i1yJ6r/W8nRN+djb+eZPFeCB+40MuDzdVbXc3le9bY6luehO5pL1veN5Io3ep1VI4jAoYEEfJGBl32qs2lh0t88h/1tDlX3ZYvDymUe4X1s5PJtbZc2aOuVBIHHDtzVCjRKrEw3NGbMcCJy2UPCfdQ0MdltOraKSGNXctvtBgmQA5ybGivm19NW97tWn8Bn0J4iJacPuJ4tQ2Kmm8imzRy04IvVTwwocx3c3MRFskl/gP7C+Xkj1tyFM3/evo92gDgNaJ6ozmYidonGxXWrQ4iAh0PbeVhjeKGRe4fq1aKnDlGRlhF6J6AN3rfQXdobjqqCBHsrbKnmc/ZnVYO26y7rKNVer3xiYgybvXaGSgrjgXfWCb+YFlDCm7Q8xEp8spo3zYUh5zuXZLrz7+yqrCEB/Y9RbgoaYwcPmLsLgY/HjpOf6VoUYslpmcnQghpTmSk31vY9dwzwkVntv/Cce0s9ClAWbwLGZ7srqaCjqSYeLGadsaTxxo+caLo7vAAdEWQp93VsJPTm4e+U1BejNyuGsdLZnpccusyy5m2N9kZbC7PDT6JzkwZ3+ZPc79cDBRAEXrWxq1bF1WcLtE5zysADv9Eik+mwY7KwG5NeLhnFlNabI2S9dlE0Ae93X/dcXG+deNL40Aqh6Wkxig06iwtNTiyNIHZ503uxfDpT2TzrIwJsXPTXx8/GK4yHbp1vWppDznpOPGYsyelB1TpduBVbPIwE+AXI80iELMv5j6u/caIzQ39ajzCekUYEeJOcHKToJgP1XrRs20yO6s/h56CGNBjh2dGI/r5oBnkThPDxtc0hGV5hKwm8YspUKvQT17fmuZ7vuR3LAPT6Pjzxtnxq+r6/THef+ePwOR2VgVvryjtulx+fIlm17fLbzmjFxvwSzQ0i0oSwr+i6K87o7u8=
*/