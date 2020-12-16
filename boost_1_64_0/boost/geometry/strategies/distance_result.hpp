// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2015 Adam Wulkiewicz, Lodz, Poland.
// Copyright (c) 2014-2015 Samuel Debionne, Grenoble, France.

// This file was modified by Oracle on 2014, 2015.
// Modifications copyright (c) 2014-2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_DISTANCE_RESULT_HPP
#define BOOST_GEOMETRY_STRATEGIES_DISTANCE_RESULT_HPP

#include <boost/mpl/always.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/vector.hpp>

#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/distance.hpp>

#include <boost/geometry/util/compress_variant.hpp>
#include <boost/geometry/util/transform_variant.hpp>
#include <boost/geometry/util/combine_if.hpp>

#include <boost/geometry/algorithms/detail/distance/default_strategies.hpp>


namespace boost { namespace geometry
{


namespace resolve_strategy
{

template <typename Geometry1, typename Geometry2, typename Strategy>
struct distance_result
    : strategy::distance::services::return_type
        <
            Strategy,
            typename point_type<Geometry1>::type,
            typename point_type<Geometry2>::type
        >
{};

template <typename Geometry1, typename Geometry2>
struct distance_result<Geometry1, Geometry2, default_strategy>
    : distance_result
        <
            Geometry1,
            Geometry2,
            typename detail::distance::default_strategy
                <
                    Geometry1, Geometry2
                >::type
        >
{};

} // namespace resolve_strategy


namespace resolve_variant
{

template <typename Geometry1, typename Geometry2, typename Strategy>
struct distance_result
    : resolve_strategy::distance_result
        <
            Geometry1,
            Geometry2,
            Strategy
        >
{};


template
<
    typename Geometry1,
    BOOST_VARIANT_ENUM_PARAMS(typename T),
    typename Strategy
>
struct distance_result
    <
        Geometry1, boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>, Strategy
    >
{
    // A set of all variant type combinations that are compatible and
    // implemented
    typedef typename util::combine_if<
        typename boost::mpl::vector1<Geometry1>,
        typename boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>::types,
        // Here we want should remove most of the combinations that
        // are not valid, mostly to limit the size of the resulting MPL set.
        // But is_implementedn is not ready for prime time
        //
        // util::is_implemented2<boost::mpl::_1, boost::mpl::_2, dispatch::distance<boost::mpl::_1, boost::mpl::_2> >
        boost::mpl::always<boost::mpl::true_>
    >::type possible_input_types;

    // The (possibly variant) result type resulting from these combinations
    typedef typename compress_variant<
        typename transform_variant<
            possible_input_types,
            resolve_strategy::distance_result<
                boost::mpl::first<boost::mpl::_>,
                boost::mpl::second<boost::mpl::_>,
                Strategy
            >,
            boost::mpl::back_inserter<boost::mpl::vector0<> >
        >::type
    >::type type;
};


// Distance arguments are commutative
template
<
    BOOST_VARIANT_ENUM_PARAMS(typename T),
    typename Geometry2,
    typename Strategy
>
struct distance_result
    <
        boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>,
        Geometry2,
        Strategy
    > : public distance_result
        <
            Geometry2, boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>, Strategy
        >
{};


template <BOOST_VARIANT_ENUM_PARAMS(typename T), typename Strategy>
struct distance_result
    <
        boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>,
        boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>,
        Strategy
    >
{
    // A set of all variant type combinations that are compatible and
    // implemented
    typedef typename util::combine_if
        <
            typename boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>::types,
            typename boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>::types,
            // Here we want to try to remove most of the combinations
            // that are not valid, mostly to limit the size of the
            // resulting MPL vector.
            // But is_implemented is not ready for prime time
            //
            // util::is_implemented2<boost::mpl::_1, boost::mpl::_2, dispatch::distance<boost::mpl::_1, boost::mpl::_2> >
            boost::mpl::always<boost::mpl::true_>
        >::type possible_input_types;

    // The (possibly variant) result type resulting from these combinations
    typedef typename compress_variant<
        typename transform_variant<
            possible_input_types,
            resolve_strategy::distance_result<
                boost::mpl::first<boost::mpl::_>,
                boost::mpl::second<boost::mpl::_>,
                Strategy
            >,
            boost::mpl::back_inserter<boost::mpl::vector0<> >
        >::type
    >::type type;
};

} // namespace resolve_variant


/*!
\brief Meta-function defining return type of distance function
\ingroup distance
\note The strategy defines the return-type (so this situation is different
    from length, where distance is sqr/sqrt, but length always squared)
 */
template
<
    typename Geometry1,
    typename Geometry2 = Geometry1,
    typename Strategy = void
>
struct distance_result
    : resolve_variant::distance_result<Geometry1, Geometry2, Strategy>
{};


template <typename Geometry1, typename Geometry2>
struct distance_result<Geometry1, Geometry2, void>
    : distance_result<Geometry1, Geometry2, default_strategy>
{};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_DISTANCE_RESULT_HPP

/* distance_result.hpp
1J3sgTziAhyb0KofQ6vm/k5p+cXxsGbJRxGR0eH14DSIqGg3PT4NyHe6yRDV2eUmo9SHvZ1uMlC94XKTsepFl5sMVxtcbjJirXa5yaB1G7n9b0lS/Wca1yl0bgWip4Hd0OnHusNmFIljUr+5g/RCbnqhVPSqDoNenZteXSp6aw6DXpGbXlEqehVM7/Dk42S62GeSDO9yzmAOOgJTxxOxDeaaHQ7pJZtVx7hcl/dInnzFeglvdn9PPeA1LdXjUsiRVMhOKuSad/6spzspcR3oSCrkSioUvdWRVEgPPI6kwnZSYdeMNqKTcrk+1t0xZXQlFY4WOJIK6+HJkVSVnVTENc/9cw93UuJ6miOpKldSkej6HnZS5Oc+usCty/3ShrsrdoC78LmuDNZmQY7hSF0L/ZmZsnbvTz7/iw4l8/d1d05HjYz2i/YBkHBe9FIKhIqV9mh8AtGIw0cz1iL6DR3XXTuYNyR23VoyHQHCrgB+Di+El24iL30x7/QAl6ZQ2/LIRqXkK7w3sVuFbM1s7Mb8QvOmPpOdCUet1mH9O1EzMU/va5iYFfpylm2eapdUV0s+mlaJdiG+pMz07+Dg5t5B7R1fweHNkceaTs0sqTyYymUnEHGENy17jHYxjbtAu5j23U27mCbeWcRVnvY4mKhF0ZmdwIVVnmtE1bDD/+FcO+PUHCp9rthLKLYprTQQR+FDDqvwZcXqmEz4jtLnQ8VDhLwdU91C0d2sLj7jJ85oM/1iKsqs2r0TwQ2oO5INoYPGcU3WrvFyoDvDnOcO5j7JmwXBpaewU311b9dFfvoOt9gr9ESi0gMPqezIzV+vlPSgkN91PMAcUXLePZ5KkWNKjrnMD1fkKmn8JZbNY3eEWhHRz3r2OIViOM61UdQSyxaK5PUpuw23bBJ55m4XEXCkMA7xSg4dRzMiFx2lSKeq+5pXuzrl2jjOc6pY5S41KViuaGG3iNk0SF0gGcq/1tV9AM8bq5bB9Y5slr7LurPhjSzfU5v2+bifhewb7wKJ/ppJInV3sd8pTMokijDkCp1yoiPx1lsOrQxy/mzoaByGHi1Bf5qjz6w+yE8yRxks04qrSAq6eWPJ+vMtXM2yt8S+mmUXpS9952KKxtLUn35H47M1jl3fxmK0b3ejTdGs3UfyKhytuUK3zQeyVWv+WIeS1mxiRBJj1GW73hxF3WQSQFRpTUKLuzJpqGFNsCqRYM9sZ+NGa5J3NKVzu61pqLSmYEhaUw+fs0Ga1hQSOp07p2pNIRFW/MOJ0pok6LwuWnLwgi7SLD63DchEqZzvjXGoWvHn2fUKiBSqh3BRdCPGqWuHJ3mFot8Xr262SyzALjVwCZtN71voR4cpjL4QkFoIji+pujZXhTxVNmvnS7CGujzW8iVRRG0gLPFIHg2ZCXFGxoamyPZRnWWWmxDYf4SFZOKDB13l9cQHZwMP1DHuAb4BfAW4FdgCfAh4F/DrwHrgYuBc4LnAMHAccBhwADAP6AV+cCXjW8BdwGeBTwAfAa4C3gZcBrzoq4zFl4E+8BTgRGAIOAlYCpwCDANPB5YBpwEjwOnAGZch/8By4EzgrMuQLrACeDFwLnA+sBJ4KXAhcBGwCrgYWAO8AlgHvBq4BHgdsB54A3AZ8CZgI3A58ObLUP/AFcDbgHcAvwVcCfwO8C7gPcBVwPuBDwBXA9cAHwI+DHwEuBb4KPAx4DpgC3AD8Angk8CNwKeAW4BbgduBzwKfB74I3AHcCXwF+CpwF/C3wN8DXwO2At8Avgl8CxgFvg18B/gecA9wL/AD4IfAfcD9wI+BB4CehYxeYAYwExgAdgZmA7sC84DdgD2AvYD5wL7AfsABwCBwELAAOAQ=
*/