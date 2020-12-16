// Boost.Geometry

// Copyright (c) 2014-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_INTERFACE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_INTERFACE_HPP

#include <sstream>
#include <string>

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/algorithms/dispatch/is_valid.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/policies/is_valid/default_policy.hpp>
#include <boost/geometry/policies/is_valid/failing_reason_policy.hpp>
#include <boost/geometry/policies/is_valid/failure_type_policy.hpp>
#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/intersection.hpp>


namespace boost { namespace geometry
{
    
namespace resolve_strategy
{

struct is_valid
{
    template <typename Geometry, typename VisitPolicy, typename Strategy>
    static inline bool apply(Geometry const& geometry,
                             VisitPolicy& visitor,
                             Strategy const& strategy)
    {
        return dispatch::is_valid<Geometry>::apply(geometry, visitor, strategy);
    }

    template <typename Geometry, typename VisitPolicy>
    static inline bool apply(Geometry const& geometry,
                             VisitPolicy& visitor,
                             default_strategy)
    {
        // NOTE: Currently the strategy is only used for Areal geometries
        typedef typename strategy::intersection::services::default_strategy
            <
                typename cs_tag<Geometry>::type
            >::type strategy_type;

        return dispatch::is_valid<Geometry>::apply(geometry, visitor, strategy_type());
    }
};

} // namespace resolve_strategy

namespace resolve_variant
{

template <typename Geometry>
struct is_valid
{
    template <typename VisitPolicy, typename Strategy>
    static inline bool apply(Geometry const& geometry,
                             VisitPolicy& visitor,
                             Strategy const& strategy)
    {
        concepts::check<Geometry const>();

        return resolve_strategy::is_valid::apply(geometry, visitor, strategy);
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct is_valid<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    template <typename VisitPolicy, typename Strategy>
    struct visitor : boost::static_visitor<bool>
    {
        visitor(VisitPolicy& policy, Strategy const& strategy)
            : m_policy(policy)
            , m_strategy(strategy)
        {}

        template <typename Geometry>
        bool operator()(Geometry const& geometry) const
        {
            return is_valid<Geometry>::apply(geometry, m_policy, m_strategy);
        }

        VisitPolicy& m_policy;
        Strategy const& m_strategy;
    };

    template <typename VisitPolicy, typename Strategy>
    static inline bool
    apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry,
          VisitPolicy& policy_visitor,
          Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<VisitPolicy, Strategy>(policy_visitor, strategy),
                                    geometry);
    }
};

} // namespace resolve_variant


// Undocumented for now
template <typename Geometry, typename VisitPolicy, typename Strategy>
inline bool is_valid(Geometry const& geometry,
                     VisitPolicy& visitor,
                     Strategy const& strategy)
{
    return resolve_variant::is_valid<Geometry>::apply(geometry, visitor, strategy);
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
    return resolve_variant::is_valid<Geometry>::apply(geometry, visitor, strategy);
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
    bool result = resolve_variant::is_valid<Geometry>::apply(geometry, visitor, strategy);
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
    bool result = resolve_variant::is_valid<Geometry>::apply(geometry, visitor, strategy);
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
tmSqabAo2BQUIVCvHSwSem3hhV5bSDJqC0lGbRzJqI0jGbVxJKO2i2TUdpGM2i6SUdtFMmq7SEZtF8mo7SIZtV0ko7k8klHbRTKa3yMZtV0ko7aLZNR2kYzaLpJR20UyartIRu0UyaidIhm1UySjtoZk1NaQjNoaklFbQzJqa0DG2pqPQRr3JRlra0DWwLyU+Rsqvqn8Qnuzpo3aG/IBecgbd1xwj24Z7yAi3zwZ4+i7b4w3tLxpmQdeEHnLhTR5es0CXskcauLyaLyUHEiO4FoByfXGNIBTqA6s0zOA/fxssCGVP6H+Tgv1d1roG08L/mBaqB/TQl2YFua6pwV7mRbsYLoBO5gphFm9bSlbrkWqbcl644LNbdJ89NeXgQ7BbWfSmVmY8dVeu2Dnasugx461UE+AWxT8VlHwW0XBbxUFv1UU/FZR8FtFwW8VG9CPnb9V3Zv0DHSYomoS009CrCcXQZpqr7RtnUwc0JbtWGT6tk8IkKoU2JWi/aeUh91OGa2mMmLtK8YCVV419dDL8m02EGw2EOpAINSBQGivAmFMFghjskCwj0Cwj0Cwj0Cwj0Cwj0Cwj0Cwj0Bo1wJhTBYI7VogjMkCoV0LhHYtENq1QGjXAq9dI1kIvCmocwdR5q2NBUL7FwjtXyCM1wOhTQyENjFga22vhLx85S4gE9baAqHtDIS2LhDa00BoTwPPP5Js9nzMyzXMri7RsveQjK3xkeyI5j2C4iN/i7LG6zP+VkdYpqulstD21sinsHZryX3N2Cyn9jdM5itwVrRE72E9ao3CQzPIUytxdn3t0bY/jF5pqnQofSiaLUanRGfOpP47MNk7eINOv30mE0APHcY65bI8vgjzqg+Ou25z/uiFxkaPo3jn4fv+qCT4o5LQJpcE/1YS2uSS0CaXhDa5JNhcSbCRUgNrw1GbHC3LZicmW7Ixu7jC8fPOum80vWdOAmdhYO3vaygLvrws6K7s6Y5kl7ah7KS7kGzlfdEX3fsYkpGeSPYkKN9PQF3a1AQyQXdlQXflBnSH6+r6Eh1Pd8+R+jFop3bxOrJ5vavCH+NdpPP3VPiOP8F3nNZEMtIzyUjPJCM9k+zpEF8LjC0TLL5nCTJqH0lG7SPJqH0kGbWPJKP2kWTUPpKM2keSUftIsucKeaZ6RbKXad5TSEbtKMmo/nGZkMZVgux1guwNuh29uI9kb9Oyy5jsk7p8D3Gdatlrmew2kD0V0hhnsrtuR9k5THYGypzvOFfLLmey7dsxjaeRjPURSEZ9BJJRH4FkvdtRB4dZfEktezTJWPtNsn6BN6Blm5kso/N8PpNNaN7jScbaeZJRm06ygo5vNYVlPoJk06g/tBfBb1zUwNxrfmqsGuBdc9gYe/3rG9ukudelYltZPVzO4+FJYV6uFkhMoS9eEfxKRfArFc+vkOwi0NGHQUfPbAKZ4EMqgg+pCD6kIviQiuBDKoIPqQg+pCL4kIrnB0hWFb7jEJcJfeyKUH8qQv2pCPWn4vWTSXYxT1eoPxXB3iuCvVc82yZZN8h+AWksY2kcEdIle0fZ8CLt3YxrzR/8Og9zkYdcD37q1IPN89aDeSJv8m07FGw7FGw7FPomodDnCAX9hoLewgbmA0z/PXc4UDcZqY8V9u/dRv0M1re9bLvT/+ZRpFVvbTyTnTZzJ5cD9wHnNjWthXBV4Xurgm+oCvqrCvqrCn6gKviBquAHqoIfqAp+oCr4gargB6qCH6gK/Yaq4BuqQh+hKtT5qlDnq0Kdrwp1uSrU5apQl6uCrVUFW6s20CZVqtkxZRxq/Uyui/dq53WRnx9WW0fSSVsTmzxsBPbWFGAbjdDHrQm2VRNsqybYVk2wrZo=
*/