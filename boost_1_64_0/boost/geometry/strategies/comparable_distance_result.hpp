// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_COMPARABLE_DISTANCE_RESULT_HPP
#define BOOST_GEOMETRY_STRATEGIES_COMPARABLE_DISTANCE_RESULT_HPP

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
struct comparable_distance_result
    : strategy::distance::services::return_type
        <
            typename strategy::distance::services::comparable_type
                <
                    Strategy
                >::type,
            typename point_type<Geometry1>::type,
            typename point_type<Geometry2>::type
        >
{};

template <typename Geometry1, typename Geometry2>
struct comparable_distance_result<Geometry1, Geometry2, default_strategy>
    : comparable_distance_result
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
struct comparable_distance_result
    : resolve_strategy::comparable_distance_result
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
struct comparable_distance_result
    <
        Geometry1, boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>, Strategy
    >
{
    // A set of all variant type combinations that are compatible and
    // implemented
    typedef typename util::combine_if<
        typename boost::mpl::vector1<Geometry1>,
        typename boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>::types,
        boost::mpl::always<boost::mpl::true_>
    >::type possible_input_types;

    // The (possibly variant) result type resulting from these combinations
    typedef typename compress_variant<
        typename transform_variant<
            possible_input_types,
            resolve_strategy::comparable_distance_result<
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
struct comparable_distance_result
    <
        boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>,
        Geometry2,
        Strategy
    > : public comparable_distance_result
        <
            Geometry2, boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>, Strategy
        >
{};


template <BOOST_VARIANT_ENUM_PARAMS(typename T), typename Strategy>
struct comparable_distance_result
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
            boost::mpl::always<boost::mpl::true_>
        >::type possible_input_types;

    // The (possibly variant) result type resulting from these combinations
    typedef typename compress_variant<
        typename transform_variant<
            possible_input_types,
            resolve_strategy::comparable_distance_result<
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
\brief Meta-function defining return type of comparable_distance function
\ingroup distance
*/
template
<
    typename Geometry1,
    typename Geometry2 = Geometry1,
    typename Strategy = void
>
struct comparable_distance_result
    : resolve_variant::comparable_distance_result
        <
            Geometry1, Geometry2, Strategy
        >
{};

template <typename Geometry1, typename Geometry2>
struct comparable_distance_result<Geometry1, Geometry2, void>
    : comparable_distance_result<Geometry1, Geometry2, default_strategy>
{};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_COMPARABLE_DISTANCE_RESULT_HPP

/* comparable_distance_result.hpp
pH1zKqFeEbmXJ8mbSt3MXUjBcy3LoImzvS8E830GQ0YhyOBJuKhGWjtZdgrUcxka0X0M9nfCf05A2Fss5phdHOPnr/Wo9Sf2GJMFzPnIfTskTJyC5ZClBiJ9uAj15wpncn02fiWV+kxJ66k+hxr1ed/35dYnQVQYisT5twi5rGAuokGc54NiMI1PfRSovvBcn/xDM9yKKfZepwr4GKcInm/ig2+8yLNn2xyBvzkIjOeSqqSwoZR9yJTANk1IvvMxOMjBa8FEVMp9GkuRNNAq7hwP8OHpqfA954ivoszCyYQvD/vv4WbyCFiiEg9MxEpUkyVpNTsXx6ke/aaV03jp4aKZEpeKokvriUYa6W7MSZFGifDvnETwNVDveexWINEyB09OrQTH9j5ykmN7b/c4tveW7JRK6qm/vzIxlf7+8W62F5vc3w+Pk7zrS+rgyfgPSgn/xRDgjP+Vu/89+HNTn1ySyE9b3Ro/uRU/vZ2VUis78tMHExz5aYfbkZ+uSK2k3vo/l6dks/5xbrml9UV9u1ziA83X8nu1eOcRI+IWKzGc+e01W6hibbNFy51nxiI8aFs1hJwe58whseAJqQVPHsHHONCN+OJL6kTSXj9eG2/iFk12xkLL5X+Ct8TtVipEdR7/9UJutnhQC9KgNpjXfCx1ydRqWNyP+eWlwzT4hxvwC5lpuC654k7iaCtlBkks6jy9qJcJxk43lVSqEWzjdp+gmR0YtCioIxPdHvSDoqnUf5xef5de/6EO9V/xaTxuFuo8XwZ9ySkSu8rJ40RXuZG7yjvFWlf57d9ll7gLBtmKtSuY/TcUm7vb67odmL//S4/U9bsI85vGEuYIOw4/9mCiJndG+36oHRWYAvwEycrhYzVpBu8v4QGmBFnIQjLeAj2WzjFIhDIft/ekbnIefIFgANotu4glaZSZb9jmUNfBqI7Mdh/vMsIDqakpcLqXQ4MiNMihPg4NCStWIQwFdx3ZbRRcLYKrRXAOBCch2adUJfVfj/KXXYcYknghXU4cWpFSGyGKKuRfehMzSYhO20J2XjIixWr2IaLuMqYut3OASavg1oHAwLjGUEeDNVj9cbdZmKBWS2DRdKolqEKIdBwBgfJI8PV7ILFEh8UxjNFamiE//aifbJ2KPC1STBQUEjTenj5NGvLN5RjUVD+UAsX2NgACtvgGYK/Ya/AGV5+Gp9LMoQS2/zoXSoDpOoqXttDw6i0CsGUQUJ9Jm5rYkFi+CJmbyTOkt++jC+fx72AqFIafX22WlwmeGU5qbdRJSja70hF+HaQ4eYJb6pCbKcKYYgakKFMwrjJTrLDsSzJ1NLSpIb4Up+tBHDXgMxXVr6Hdrl+CTYMPx0hNkake0hShcxL9ekYxsS13hwE00lBYaSGFdHMHadxvIX7FBOs3VrFvWSAK3fo5yOJg+xJ/fj1YsopeMnwXH2BsqvQGXZy48RNW6eBOOJADz3YK3N2tB+KMdInylRpjwgr+KyGkcZeGl2Hq96dPmtKwb5Wd0uaj7BNiW2VCWtRiZPspzT4ZyAJIeBWzK/U/VLuYBpz5RSwtpPYj1jQ3nZ5KCMGdJ6Bkb91JcjR2o4iALWlK/NCI/PD7IskPYyzFDzXqDA7JDSQehySWkqyQphjHbga56zeXLpWBbZayPs2MMs8i6xAUIu4asWIRyr7zCi0ZqTnpZo4pP5A5JggcE3KtGyszxQePOQPwVTIxLjdXHnFtoqfJDyU0YlE61HUj2wVq7zMu+sFnMHFjMi3sLQgD6ONAWG8Ly+/XlZRiA5PPxAKC8UrrxyvJdinw1jhivAIjrBjCsokZvxl7XGXGYR8jJTMGbGYMUMub6cY5pdOZtgaZtm0=
*/