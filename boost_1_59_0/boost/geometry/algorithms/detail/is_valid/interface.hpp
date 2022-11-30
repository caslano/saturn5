// Boost.Geometry

// Copyright (c) 2014-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_INTERFACE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_INTERFACE_HPP

#include <sstream>
#include <string>

#include <boost/geometry/algorithms/detail/visit.hpp>
#include <boost/geometry/algorithms/dispatch/is_valid.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/visit.hpp>
#include <boost/geometry/geometries/adapted/boost_variant.hpp> // For backward compatibility
#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/policies/is_valid/default_policy.hpp>
#include <boost/geometry/policies/is_valid/failing_reason_policy.hpp>
#include <boost/geometry/policies/is_valid/failure_type_policy.hpp>
#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/detail.hpp>
#include <boost/geometry/strategies/relate/services.hpp>


namespace boost { namespace geometry
{
    
namespace resolve_strategy
{

template
<
    typename Strategy,
    bool IsUmbrella = strategies::detail::is_umbrella_strategy<Strategy>::value
>
struct is_valid
{
    template <typename Geometry, typename VisitPolicy>
    static inline bool apply(Geometry const& geometry,
                             VisitPolicy& visitor,
                             Strategy const& strategy)
    {
        return dispatch::is_valid<Geometry>::apply(geometry, visitor, strategy);
    }

};

template <typename Strategy>
struct is_valid<Strategy, false>
{
    template <typename Geometry, typename VisitPolicy>
    static inline bool apply(Geometry const& geometry,
                             VisitPolicy& visitor,
                             Strategy const& strategy)
    {
        using strategies::relate::services::strategy_converter;
        return dispatch::is_valid
            <
                Geometry
            >::apply(geometry, visitor,
                     strategy_converter<Strategy>::get(strategy));
    }
};

template <>
struct is_valid<default_strategy, false>
{
    template <typename Geometry, typename VisitPolicy>
    static inline bool apply(Geometry const& geometry,
                             VisitPolicy& visitor,
                             default_strategy)
    {
        // NOTE: Currently the strategy is only used for Areal geometries
        typedef typename strategies::relate::services::default_strategy
            <
                Geometry, Geometry
            >::type strategy_type;

        return dispatch::is_valid<Geometry>::apply(geometry, visitor,
                                                   strategy_type());
    }
};

} // namespace resolve_strategy

namespace resolve_dynamic
{

template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct is_valid
{
    template <typename VisitPolicy, typename Strategy>
    static inline bool apply(Geometry const& geometry,
                             VisitPolicy& visitor,
                             Strategy const& strategy)
    {
        concepts::check<Geometry const>();

        return resolve_strategy::is_valid
                <
                    Strategy
                >::apply(geometry, visitor, strategy);
    }
};

template <typename Geometry>
struct is_valid<Geometry, dynamic_geometry_tag>
{
    template <typename VisitPolicy, typename Strategy>
    static inline bool apply(Geometry const& geometry,
                             VisitPolicy& policy_visitor,
                             Strategy const& strategy)
    {
        bool result = true;
        traits::visit<Geometry>::apply([&](auto const& g)
        {
            result = is_valid<util::remove_cref_t<decltype(g)>>::apply(g, policy_visitor, strategy);
        }, geometry);
        return result;
    }
};

template <typename Geometry>
struct is_valid<Geometry, geometry_collection_tag>
{
    template <typename VisitPolicy, typename Strategy>
    static inline bool apply(Geometry const& geometry,
                             VisitPolicy& policy_visitor,
                             Strategy const& strategy)
    {
        bool result = true;
        detail::visit_breadth_first([&](auto const& g)
        {
            result = is_valid<util::remove_cref_t<decltype(g)>>::apply(g, policy_visitor, strategy);
            return result;
        }, geometry);
        return result;
    }
};

} // namespace resolve_dynamic


// Undocumented for now
template <typename Geometry, typename VisitPolicy, typename Strategy>
inline bool is_valid(Geometry const& geometry,
                     VisitPolicy& visitor,
                     Strategy const& strategy)
{
    return resolve_dynamic::is_valid<Geometry>::apply(geometry, visitor, strategy);
}


/*!
\brief \brief_check{is valid (in the OGC sense)}
\ingroup is_valid
\tparam Geometry \tparam_geometry
\tparam Strategy \tparam_strategy{Is_valid}
\param geometry \param_geometry
\param strategy \param_strategy{is_valid}
\return \return_check{is valid (in the OGC sense);
furthermore, the following geometries are considered valid:
multi-geometries with no elements,
linear geometries containing spikes,
areal geometries with duplicate (consecutive) points}

\qbk{distinguish,with strategy}
\qbk{[include reference/algorithms/is_valid.qbk]}
*/
template <typename Geometry, typename Strategy>
inline bool is_valid(Geometry const& geometry, Strategy const& strategy)
{
    is_valid_default_policy<> visitor;
    return resolve_dynamic::is_valid<Geometry>::apply(geometry, visitor, strategy);
}

/*!
\brief \brief_check{is valid (in the OGC sense)}
\ingroup is_valid
\tparam Geometry \tparam_geometry
\param geometry \param_geometry
\return \return_check{is valid (in the OGC sense);
    furthermore, the following geometries are considered valid:
    multi-geometries with no elements,
    linear geometries containing spikes,
    areal geometries with duplicate (consecutive) points}

\qbk{[include reference/algorithms/is_valid.qbk]}
*/
template <typename Geometry>
inline bool is_valid(Geometry const& geometry)
{
    return is_valid(geometry, default_strategy());
}


/*!
\brief \brief_check{is valid (in the OGC sense)}
\ingroup is_valid
\tparam Geometry \tparam_geometry
\tparam Strategy \tparam_strategy{Is_valid}
\param geometry \param_geometry
\param failure An enumeration value indicating that the geometry is
    valid or not, and if not valid indicating the reason why
\param strategy \param_strategy{is_valid}
\return \return_check{is valid (in the OGC sense);
    furthermore, the following geometries are considered valid:
    multi-geometries with no elements,
    linear geometries containing spikes,
    areal geometries with duplicate (consecutive) points}

\qbk{distinguish,with failure value and strategy}
\qbk{[include reference/algorithms/is_valid_with_failure.qbk]}
*/
template <typename Geometry, typename Strategy>
inline bool is_valid(Geometry const& geometry, validity_failure_type& failure, Strategy const& strategy)
{
    failure_type_policy<> visitor;
    bool result = resolve_dynamic::is_valid<Geometry>::apply(geometry, visitor, strategy);
    failure = visitor.failure();
    return result;
}

/*!
\brief \brief_check{is valid (in the OGC sense)}
\ingroup is_valid
\tparam Geometry \tparam_geometry
\param geometry \param_geometry
\param failure An enumeration value indicating that the geometry is
    valid or not, and if not valid indicating the reason why
\return \return_check{is valid (in the OGC sense);
    furthermore, the following geometries are considered valid:
    multi-geometries with no elements,
    linear geometries containing spikes,
    areal geometries with duplicate (consecutive) points}

\qbk{distinguish,with failure value}
\qbk{[include reference/algorithms/is_valid_with_failure.qbk]}
*/
template <typename Geometry>
inline bool is_valid(Geometry const& geometry, validity_failure_type& failure)
{
    return is_valid(geometry, failure, default_strategy());
}


/*!
\brief \brief_check{is valid (in the OGC sense)}
\ingroup is_valid
\tparam Geometry \tparam_geometry
\tparam Strategy \tparam_strategy{Is_valid}
\param geometry \param_geometry
\param message A string containing a message stating if the geometry
    is valid or not, and if not valid a reason why
\param strategy \param_strategy{is_valid}
\return \return_check{is valid (in the OGC sense);
    furthermore, the following geometries are considered valid:
    multi-geometries with no elements,
    linear geometries containing spikes,
    areal geometries with duplicate (consecutive) points}

\qbk{distinguish,with message and strategy}
\qbk{[include reference/algorithms/is_valid_with_message.qbk]}
*/
template <typename Geometry, typename Strategy>
inline bool is_valid(Geometry const& geometry, std::string& message, Strategy const& strategy)
{
    std::ostringstream stream;
    failing_reason_policy<> visitor(stream);
    bool result = resolve_dynamic::is_valid<Geometry>::apply(geometry, visitor, strategy);
    message = stream.str();
    return result;
}

/*!
\brief \brief_check{is valid (in the OGC sense)}
\ingroup is_valid
\tparam Geometry \tparam_geometry
\param geometry \param_geometry
\param message A string containing a message stating if the geometry
    is valid or not, and if not valid a reason why
\return \return_check{is valid (in the OGC sense);
    furthermore, the following geometries are considered valid:
    multi-geometries with no elements,
    linear geometries containing spikes,
    areal geometries with duplicate (consecutive) points}

\qbk{distinguish,with message}
\qbk{[include reference/algorithms/is_valid_with_message.qbk]}
*/
template <typename Geometry>
inline bool is_valid(Geometry const& geometry, std::string& message)
{
    return is_valid(geometry, message, default_strategy());
}


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_INTERFACE_HPP

/* interface.hpp
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
*/