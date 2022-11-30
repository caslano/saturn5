// Boost.Geometry Index
//
// R-tree algorithms parameters
//
// Copyright (c) 2011-2017 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019-2021.
// Modifications copyright (c) 2019-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_PARAMETERS_HPP
#define BOOST_GEOMETRY_INDEX_PARAMETERS_HPP

#include <limits>

#include <boost/geometry/core/static_assert.hpp>

#include <boost/geometry/index/detail/exception.hpp>

#include <boost/geometry/strategies/default_strategy.hpp>

namespace boost { namespace geometry { namespace index {

namespace detail { 

template <size_t MaxElements>
struct default_min_elements_s
{
    static const size_t raw_value = (MaxElements * 3) / 10;
    static const size_t value = 1 <= raw_value ? raw_value : 1;
};

inline size_t default_min_elements_d()
{
    return (std::numeric_limits<size_t>::max)();
}

inline size_t default_min_elements_d_calc(size_t max_elements, size_t min_elements)
{
    if ( default_min_elements_d() == min_elements )
    {
        size_t raw_value = (max_elements * 3) / 10;
        return 1 <= raw_value ? raw_value : 1;
    }
    
    return min_elements;
}

template <size_t MaxElements>
struct default_rstar_reinserted_elements_s
{
    static const size_t value = (MaxElements * 3) / 10;
};

inline size_t default_rstar_reinserted_elements_d()
{
    return (std::numeric_limits<size_t>::max)();
}

inline size_t default_rstar_reinserted_elements_d_calc(size_t max_elements, size_t reinserted_elements)
{
    if ( default_rstar_reinserted_elements_d() == reinserted_elements )
    {
        return (max_elements * 3) / 10;
    }
    
    return reinserted_elements;
}

} // namespace detail

/*!
\brief Linear r-tree creation algorithm parameters.

\tparam MaxElements     Maximum number of elements in nodes.
\tparam MinElements     Minimum number of elements in nodes. Default: 0.3*Max.
*/
template <size_t MaxElements,
          size_t MinElements = detail::default_min_elements_s<MaxElements>::value>
struct linear
{
    BOOST_GEOMETRY_STATIC_ASSERT((0 < MinElements && 2*MinElements <= MaxElements+1),
        "Invalid MaxElements or MinElements.",
        std::integer_sequence<size_t, MaxElements, MinElements>);

    static const size_t max_elements = MaxElements;
    static const size_t min_elements = MinElements;

    static size_t get_max_elements() { return MaxElements; }
    static size_t get_min_elements() { return MinElements; }
};

/*!
\brief Quadratic r-tree creation algorithm parameters.

\tparam MaxElements     Maximum number of elements in nodes.
\tparam MinElements     Minimum number of elements in nodes. Default: 0.3*Max.
*/
template <size_t MaxElements,
          size_t MinElements = detail::default_min_elements_s<MaxElements>::value>
struct quadratic
{
    BOOST_GEOMETRY_STATIC_ASSERT((0 < MinElements && 2*MinElements <= MaxElements+1),
        "Invalid MaxElements or MinElements.",
        std::integer_sequence<size_t, MaxElements, MinElements>);

    static const size_t max_elements = MaxElements;
    static const size_t min_elements = MinElements;

    static size_t get_max_elements() { return MaxElements; }
    static size_t get_min_elements() { return MinElements; }
};

/*!
\brief R*-tree creation algorithm parameters.

\tparam MaxElements             Maximum number of elements in nodes.
\tparam MinElements             Minimum number of elements in nodes. Default: 0.3*Max.
\tparam ReinsertedElements      The number of elements reinserted by forced reinsertions algorithm.
                                If 0 forced reinsertions are disabled. Maximum value is Max+1-Min.
                                Greater values are truncated. Default: 0.3*Max.
\tparam OverlapCostThreshold    The number of most suitable leafs taken into account while choosing
                                the leaf node to which currently inserted value will be added. If
                                value is in range (0, MaxElements) - the algorithm calculates
                                nearly minimum overlap cost, otherwise all leafs are analyzed
                                and true minimum overlap cost is calculated. Default: 32.
*/
template <size_t MaxElements,
          size_t MinElements = detail::default_min_elements_s<MaxElements>::value,
          size_t ReinsertedElements = detail::default_rstar_reinserted_elements_s<MaxElements>::value,
          size_t OverlapCostThreshold = 32>
struct rstar
{
    BOOST_GEOMETRY_STATIC_ASSERT((0 < MinElements && 2*MinElements <= MaxElements+1),
        "Invalid MaxElements or MinElements.",
        std::integer_sequence<size_t, MaxElements, MinElements>);

    static const size_t max_elements = MaxElements;
    static const size_t min_elements = MinElements;
    static const size_t reinserted_elements = ReinsertedElements;
    static const size_t overlap_cost_threshold = OverlapCostThreshold;

    static size_t get_max_elements() { return MaxElements; }
    static size_t get_min_elements() { return MinElements; }
    static size_t get_reinserted_elements() { return ReinsertedElements; }
    static size_t get_overlap_cost_threshold() { return OverlapCostThreshold; }
};

//template <size_t MaxElements, size_t MinElements>
//struct kmeans
//{
//    static const size_t max_elements = MaxElements;
//    static const size_t min_elements = MinElements;
//};

/*!
\brief Linear r-tree creation algorithm parameters - run-time version.
*/
class dynamic_linear
{
public:
    /*!
    \brief The constructor.

    \param max_elements     Maximum number of elements in nodes.
    \param min_elements     Minimum number of elements in nodes. Default: 0.3*Max.
    */
    explicit dynamic_linear(size_t max_elements,
                            size_t min_elements = detail::default_min_elements_d())
        : m_max_elements(max_elements)
        , m_min_elements(detail::default_min_elements_d_calc(max_elements, min_elements))
    {
        if (!(0 < m_min_elements && 2*m_min_elements <= m_max_elements+1))
            detail::throw_invalid_argument("invalid min or/and max parameters of dynamic_linear");
    }

    size_t get_max_elements() const { return m_max_elements; }
    size_t get_min_elements() const { return m_min_elements; }

private:
    size_t m_max_elements;
    size_t m_min_elements;
};

/*!
\brief Quadratic r-tree creation algorithm parameters - run-time version.
*/
class dynamic_quadratic
{
public:
    /*!
    \brief The constructor.

    \param max_elements     Maximum number of elements in nodes.
    \param min_elements     Minimum number of elements in nodes. Default: 0.3*Max.
    */
    explicit dynamic_quadratic(size_t max_elements,
                               size_t min_elements = detail::default_min_elements_d())
        : m_max_elements(max_elements)
        , m_min_elements(detail::default_min_elements_d_calc(max_elements, min_elements))
    {
        if (!(0 < m_min_elements && 2*m_min_elements <= m_max_elements+1))
            detail::throw_invalid_argument("invalid min or/and max parameters of dynamic_quadratic");
    }

    size_t get_max_elements() const { return m_max_elements; }
    size_t get_min_elements() const { return m_min_elements; }

private:
    size_t m_max_elements;
    size_t m_min_elements;
};

/*!
\brief R*-tree creation algorithm parameters - run-time version.
*/
class dynamic_rstar
{
public:
    /*!
    \brief The constructor.

    \param max_elements             Maximum number of elements in nodes.
    \param min_elements             Minimum number of elements in nodes. Default: 0.3*Max.
    \param reinserted_elements      The number of elements reinserted by forced reinsertions algorithm.
                                    If 0 forced reinsertions are disabled. Maximum value is Max-Min+1.
                                    Greater values are truncated. Default: 0.3*Max.
    \param overlap_cost_threshold   The number of most suitable leafs taken into account while choosing
                                    the leaf node to which currently inserted value will be added. If
                                    value is in range (0, MaxElements) - the algorithm calculates
                                    nearly minimum overlap cost, otherwise all leafs are analyzed
                                    and true minimum overlap cost is calculated. Default: 32.
    */
    explicit dynamic_rstar(size_t max_elements,
                           size_t min_elements = detail::default_min_elements_d(),
                           size_t reinserted_elements = detail::default_rstar_reinserted_elements_d(),
                           size_t overlap_cost_threshold = 32)
        : m_max_elements(max_elements)
        , m_min_elements(detail::default_min_elements_d_calc(max_elements, min_elements))
        , m_reinserted_elements(detail::default_rstar_reinserted_elements_d_calc(max_elements, reinserted_elements))
        , m_overlap_cost_threshold(overlap_cost_threshold)
    {
        if (!(0 < m_min_elements && 2*m_min_elements <= m_max_elements+1))
            detail::throw_invalid_argument("invalid min or/and max parameters of dynamic_rstar");
    }

    size_t get_max_elements() const { return m_max_elements; }
    size_t get_min_elements() const { return m_min_elements; }
    size_t get_reinserted_elements() const { return m_reinserted_elements; }
    size_t get_overlap_cost_threshold() const { return m_overlap_cost_threshold; }

private:
    size_t m_max_elements;
    size_t m_min_elements;
    size_t m_reinserted_elements;
    size_t m_overlap_cost_threshold;
};


template <typename Parameters, typename Strategy>
class parameters
    : public Parameters
    , private Strategy
{
public:
    parameters()
        : Parameters(), Strategy()
    {}

    parameters(Parameters const& params)
        : Parameters(params), Strategy()
    {}

    parameters(Parameters const& params, Strategy const& strategy)
        : Parameters(params), Strategy(strategy)
    {}

    Strategy const& strategy() const
    {
        return static_cast<Strategy const&>(*this);
    }
};


namespace detail
{

template <typename Parameters>
struct strategy_type
{
    typedef default_strategy type;
    typedef default_strategy result_type;
};

template <typename Parameters, typename Strategy>
struct strategy_type< parameters<Parameters, Strategy> >
{
    typedef Strategy type;
    typedef Strategy const& result_type;
};


template <typename Parameters>
struct get_strategy_impl
{
    static inline default_strategy apply(Parameters const&)
    {
        return default_strategy();
    }
};

template <typename Parameters, typename Strategy>
struct get_strategy_impl<parameters<Parameters, Strategy> >
{
    static inline Strategy const& apply(parameters<Parameters, Strategy> const& parameters)
    {
        return parameters.strategy();
    }
};

template <typename Parameters>
inline typename strategy_type<Parameters>::result_type
    get_strategy(Parameters const& parameters)
{
    return get_strategy_impl<Parameters>::apply(parameters);
}

} // namespace detail


}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_PARAMETERS_HPP

/* parameters.hpp
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
*/