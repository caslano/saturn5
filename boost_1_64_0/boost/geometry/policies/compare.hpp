// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017, 2019.
// Modifications copyright (c) 2017, 2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_POLICIES_COMPARE_HPP
#define BOOST_GEOMETRY_POLICIES_COMPARE_HPP


#include <cstddef>

#include <boost/geometry/strategies/compare.hpp>
#include <boost/geometry/util/math.hpp>


namespace boost { namespace geometry
{


/*!
\brief Less functor, to sort points in ascending order.
\ingroup compare
\details This functor compares points and orders them on x,
    then on y, then on z coordinate.
\tparam Point the geometry
\tparam Dimension the dimension to sort on, defaults to -1,
    indicating ALL dimensions. That's to say, first on x,
    on equal x-es then on y, etc.
    If a dimension is specified, only that dimension is considered
*/
template
<
    typename Point = void,
    int Dimension = -1,
    typename CSTag = void
>
struct less
{
    typedef Point first_argument_type;
    typedef Point second_argument_type;
    typedef bool result_type;

    inline bool operator()(Point const& left, Point const& right) const
    {
        typedef typename strategy::compare::services::default_strategy
            <
                strategy::compare::less,
                Point, Point,
                Dimension,
                CSTag, CSTag
            >::type strategy_type;

        return strategy_type::apply(left, right);
    }
};

template <int Dimension, typename CSTag>
struct less<void, Dimension, CSTag>
{
    typedef bool result_type;

    template <typename Point1, typename Point2>
    inline bool operator()(Point1 const& left, Point2 const& right) const
    {
        typedef typename strategy::compare::services::default_strategy
            <
                strategy::compare::less,
                Point1, Point2,
                Dimension,
                CSTag, CSTag
            >::type strategy_type;

        return strategy_type::apply(left, right);
    }
};

template <typename Point, int Dimension>
struct less<Point, Dimension, void>
{
    typedef Point first_argument_type;
    typedef Point second_argument_type;
    typedef bool result_type;

    inline bool operator()(Point const& left, Point const& right) const
    {
        typedef typename strategy::compare::services::default_strategy
            <
                strategy::compare::less,
                Point, Point,
                Dimension
            >::type strategy_type;

        return strategy_type::apply(left, right);
    }
};

template <int Dimension>
struct less<void, Dimension, void>
{
    typedef bool result_type;

    template <typename Point1, typename Point2>
    inline bool operator()(Point1 const& left, Point2 const& right) const
    {
        typedef typename strategy::compare::services::default_strategy
            <
                strategy::compare::less,
                Point1, Point2,
                Dimension
            >::type strategy_type;

        return strategy_type::apply(left, right);
    }
};


/*!
\brief Greater functor
\ingroup compare
\details Can be used to sort points in reverse order
\see Less functor
*/
template
<
    typename Point = void,
    int Dimension = -1,
    typename CSTag = void
>
struct greater
{
    typedef Point first_argument_type;
    typedef Point second_argument_type;
    typedef bool result_type;

    bool operator()(Point const& left, Point const& right) const
    {
        typedef typename strategy::compare::services::default_strategy
            <
                strategy::compare::greater,
                Point, Point,
                Dimension,
                CSTag, CSTag
            >::type strategy_type;

        return strategy_type::apply(left, right);
    }
};

template <int Dimension, typename CSTag>
struct greater<void, Dimension, CSTag>
{
    typedef bool result_type;

    template <typename Point1, typename Point2>
    bool operator()(Point1 const& left, Point2 const& right) const
    {
        typedef typename strategy::compare::services::default_strategy
            <
                strategy::compare::greater,
                Point1, Point2,
                Dimension,
                CSTag, CSTag
            >::type strategy_type;

        return strategy_type::apply(left, right);
    }
};

template <typename Point, int Dimension>
struct greater<Point, Dimension, void>
{
    typedef Point first_argument_type;
    typedef Point second_argument_type;
    typedef bool result_type;

    bool operator()(Point const& left, Point const& right) const
    {
        typedef typename strategy::compare::services::default_strategy
            <
                strategy::compare::greater,
                Point, Point,
                Dimension
            >::type strategy_type;

        return strategy_type::apply(left, right);
    }
};

template <int Dimension>
struct greater<void, Dimension, void>
{
    typedef bool result_type;

    template <typename Point1, typename Point2>
    bool operator()(Point1 const& left, Point2 const& right) const
    {
        typedef typename strategy::compare::services::default_strategy
            <
                strategy::compare::greater,
                Point1, Point2,
                Dimension
            >::type strategy_type;

        return strategy_type::apply(left, right);
    }
};


/*!
\brief Equal To functor, to compare if points are equal
\ingroup compare
\tparam Geometry the geometry
\tparam Dimension the dimension to compare on, defaults to -1,
    indicating ALL dimensions.
    If a dimension is specified, only that dimension is considered
*/
template
<
    typename Point,
    int Dimension = -1,
    typename CSTag = void
>
struct equal_to
{
    typedef Point first_argument_type;
    typedef Point second_argument_type;
    typedef bool result_type;

    bool operator()(Point const& left, Point const& right) const
    {
        typedef typename strategy::compare::services::default_strategy
            <
                strategy::compare::equal_to,
                Point, Point,
                Dimension,
                CSTag, CSTag
            >::type strategy_type;

        return strategy_type::apply(left, right);
    }
};

template <int Dimension, typename CSTag>
struct equal_to<void, Dimension, CSTag>
{
    typedef bool result_type;

    template <typename Point1, typename Point2>
    bool operator()(Point1 const& left, Point2 const& right) const
    {
        typedef typename strategy::compare::services::default_strategy
            <
                strategy::compare::equal_to,
                Point1, Point2,
                Dimension,
                CSTag, CSTag
            >::type strategy_type;

        return strategy_type::apply(left, right);
    }
};

template <typename Point, int Dimension>
struct equal_to<Point, Dimension, void>
{
    typedef Point first_argument_type;
    typedef Point second_argument_type;
    typedef bool result_type;

    bool operator()(Point const& left, Point const& right) const
    {
        typedef typename strategy::compare::services::default_strategy
            <
                strategy::compare::equal_to,
                Point, Point,
                Dimension
            >::type strategy_type;

        return strategy_type::apply(left, right);
    }
};

template <int Dimension>
struct equal_to<void, Dimension, void>
{
    typedef bool result_type;

    template <typename Point1, typename Point2>
    bool operator()(Point1 const& left, Point2 const& right) const
    {
        typedef typename strategy::compare::services::default_strategy
            <
                strategy::compare::equal_to,
                Point1, Point2,
                Dimension
            >::type strategy_type;

        return strategy_type::apply(left, right);
    }
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_POLICIES_COMPARE_HPP

/* compare.hpp
q4Lxt9bZFX5PpTX00anbfhleFNtro9YfGn+1HKhx+be2t6xYNvFSVK0M22n6L+T/rdemiX/vGlcDqltXjll8a6zvghVLli2QfQtLzjmiLiHXyjBC6+MvbC35eETFHiIvmXVQ5+h+nK1DKIoGdgrHb+W1qdT0+nocr3nlwUESTzcp7TGSG4q/+5s490YS00QUUXR8IeNI2BMKNmCwIWyvERykFgzQwQnt6815KeEsE5YiZhW+SA2ZBXiuPhMHqm8PQd4+1tU6oBeHpthFfrw7Jk4Fsx+qGgsTpt/KiEfa48s+C/bc3/wOhMogBWWTyCqE8pvVfjpj9j9XuTmkQYTjN+zRNyA/mbP8G1DrDG7uSIO9sk4o5jef5/wjC7Eb4ApZwz1BD0vrmz/CaWSod4VjBD4N8zvNNJxLnE6IMgRJgZAQZP+3CdH5beLcR4hxmBI8ZdutObbObxO2cGAtjOIQLokPaTUlpS6uoXXj/BvyoA4bUS7Xt2VCg5+rP948a+HX5kE29R0z/eIh7Z8AWIMfSEB4fKI0s+U3p2vd7zbh9yGhc5UViGDCK8HaY4Az9xj8wGIhlh5pD5sUKSEieb0TjmPilHCVhBpGlCL2hTiAxO7zSoo3/Vs4DuLymyrFZutQRhKFaDyWw0dYECVynCoaxJSxJkYcJ4UjL9IQ+4rI8T6c04+3YjiqABWm5DSb32L62nOcJC3xNoJ7ZqdFM7+GcM5xnDRBuQGkmpKE6INMnAscR5RRzuKy1nSO9+Bc5DhhGJVIDitP3CnjdtniTRQxgPOsRmp6vuf7HKeqcZPXeeGYp6G9/35j4twn9TBqQRqgqtJIoPD1+9GHmeu3SqHqE5W3oHrnMtk/zD4PVEmE46/zpjw5a/M8s8p975CmvK5hTzrSPWGPGgIIrXUTp8HTGyJ96eM9LBzCI1lrYsx5P7rKZKg0ykXgnAfRzFrjJlzp+Eg47Lni7ict5KQeetXS4cQiA2pSyw3bQCBagoSxYNcEO8PwSgfjhNLuFQq6bRzW4km9fvi/+ahdMPuYS6ESiOM0x5QfYbLeYQV/0YQvcBdkWCVljDuTo+gaEat2veYcqmL43Ty41RMXrRg0ySGtLzbuEcyjqOWeIPuhkbtNyzEm7H0K8bwqMIqHDfU/ndNrJmwODX6GJDotLGL1OOyNTNj9cY69VEHDVusZEe8XdbfiEXSVwXC4sjYadmVS10b4uVbt56329Q6gvrN8P53r3k/+MA8f3upijp3qpIqhkDAGzi0k3LtMuOObS0uDwVC9097ftsEkIiszIOdFkHQB04NK3SVrVk7zMoDmFsWlD+3H/2e7f27AX0YoEQ7uPbQff80cPzSLP7b/ECKreQ48io1RAYMqtKlOmzw0qKTu4BZ44z3g5mKTCFjZyfEhgMbt+89B22MXddsano8I+4bfJt52Nxlc/foPQrvOS4o4IEH3zsa78IastcvbOjy+On9iTO/Hj1zBhpMaPjGHEmbuSpMwGGHdfscrT7RjpoiXF020d1G1XS4nglu9ah+c4ph4nrtaLxwGifoaXH0aDBy+QfMWEu4LHA6DTN/9h2vZbcP5zRMnNY1PXmeivXU9HArt1kDM0V26PXtdASdWN9R/+/ai/+73N15P/C7QSIICnm6fub5qJ4nAbH/RDXQ7SSVG+09uqNpNyZrar3xj1W5endS++yZWuyRwN9l+/5tS+5THDsa5g01upmC7Z8rA4BPrXLaZNyvmW7Z/9Baqnb9EzD5O30rBGBK10d7cWrevrFO75m/3bVS7FJUN3N23VW0kiQ4M3GC3bpcdE+/O7VQblza7vSrH5vYKpm8EiY/iDgrOlKio/fwdebucL5rvO6s=
*/