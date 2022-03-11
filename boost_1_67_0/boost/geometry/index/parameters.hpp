// Boost.Geometry Index
//
// R-tree algorithms parameters
//
// Copyright (c) 2011-2017 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019.
// Modifications copyright (c) 2019 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_PARAMETERS_HPP
#define BOOST_GEOMETRY_INDEX_PARAMETERS_HPP


#include <limits>

#include <boost/mpl/assert.hpp>

#include <boost/geometry/index/detail/exception.hpp>


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
    BOOST_MPL_ASSERT_MSG((0 < MinElements && 2*MinElements <= MaxElements+1),
                         INVALID_STATIC_MIN_MAX_PARAMETERS, (linear));

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
    BOOST_MPL_ASSERT_MSG((0 < MinElements && 2*MinElements <= MaxElements+1),
                         INVALID_STATIC_MIN_MAX_PARAMETERS, (quadratic));

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
    BOOST_MPL_ASSERT_MSG((0 < MinElements && 2*MinElements <= MaxElements+1),
                         INVALID_STATIC_MIN_MAX_PARAMETERS, (rstar));

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