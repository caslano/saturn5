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
asvIxDIjEqT6yfDK1YyfKp5doNr5d/IQwcC1bc1ORM0irn0sLiCZmjEzGeaScHyetXAe+gwXZrAFzoLCBVBqLkUDzS+Emu42NcO9wGlXrmeZITRr8s0gpW0m/kv2a/jMl9zKBRU+kocj71WOrKxxx/9alyUh25WpXx+vWSLsNhFSQw59lSV4gZHAeaqeWzssr+mpZSkBwv2RlYuRGB6DoQywAfdeJZ0ygAIVOyLR5TxAN4kITYkZnHjuYE0eWaSCQm2Ux+46RrGXlxTYGv9kIr0Npof3Ly9+BpG4IosHq/3Fz/RSqvWGuVQAn6MWXYKCPbGCeRjdC93EpqbR3rIO0H5Axb2yIHYtS0p5qIA/8KIsMRubY6nEJLBOWJgCdoeVnV/YVoGJk9DsD6MzTaYEzjP0V+kQ3gRnFdyW6POXdZ/BsRDmdO9WV4RqePfHX1BUMaiKwaTc+xUHP3GnjMaqzlZpD1TVFiq4Jyick3AtLl7sdKgWtJ9GjZQRoh/jopJNNoVlpIf8+U9Jjz9VIye76ERMGL5buRSLQY1m1AELX+UAOUiSaOXJcbGnUPQOUaO8stKH+ajmWJA1nyMXAjb36a9SALdXXxLmucZoK42RwtoAIIiMQXBuBEUXxIYn1sbHP88guQkuqRDyuDGdWS4NAnNMrCwQxYvSRLyq1F6SOk4kl3ySznCEh581p4a1muucCNA6+56RZrrV+gScg+F4pqEp5vFMOXkSyIZnfjeD4NDbq2GiIubt0+SRBlPfhqjCy6H2u/MjRDgxOWQC+rnUtY/SYUEvW1Iaes1BxGnBQMPbsTzIDtbgIGMAwQdMR1X1BOM9SqQuwM75rIU+y3zmkwvt8/lfsmGiO1zN5zA4wfhkVomClJGYCsNNVJDq1rphBpALpU670IQiJUdBSA7wZdCLJcOTraJ818+u24yU8Zs27MVVsD1RMzFBakbJBxzIOa0+41m4MyvcbCZF4IMW/X1KRJQTCGXHHqTmWkWXKTKGQUdV1Gc9KGt4olnHLK1x6f1rMe+TSauT1WzCWj6n5sGgOQGyN4D7Erj09KFR0pc1WRJGzsKnMyJENAOeRv/1tK2Y4i93tR0O0EGTeiXwNq59y8NNiB9MtidbKuju89gdhi1JI3m8lalDJCOojClijQ6pdspMQHH5qVsTz2GRRiGU2NH+sBhD9aCaA8w3bhUnaQ6Xh9+gHuBxYnuyORB5A/u81UdvqDcwMfBi61Z0rNnKv3/W6NOg0aGaRIeWLsEuDVGXhowupXTIiFQlMqApphEGjoSym//yv8pNXCf3z7EXoDHtKeUWPAAtqjvZrposmW6/pwYt9RfrufYxKBwAjMqvXkmJeKfG8v/m89uXpEmUof0cGYC/tyR2DsFxxV33ZEjUClpF8c+r08RpF4uTmztEptZ48JagT4RLD8lUOuZHUOos5341SwoEYmmOJ/I/PUR5vxDTFlE8dkDWPn7dqiyRwUR4Rx3gl8ESBGgAq+CzeAyI8Bs0gp+vyEKRnWOMiA7obrWtGY8h3u0A2kKXRu5Fqo2C+OXmQbluFHRAnSC8hTfjEm9Qcy30p90dZykqrqMVXQIlrdzKRN62cgujOLgMivq1coDwZQ6KCShmVHvQ0mrGI5H3LsapLelGn7Bze0MPxoJK8e0DKLPhrINlxNM6N+xFahPP/XH+YNG1mE+R+yr13PJstOZ7GM09x7Hr0bu1qyJAgpKaDCJpAYd2Me+gcDZ4bvFIx8yCYQFTBaPEWlp4drjTRBES7h1owVR2SjUG5Ezo2N2DSjF+LbKReGZPF7lHU4cxwWogkYgXTRM9APtdscwBdbQR1joIRaPoZVnUCZB4HnwIJkvNAYrrAKfja5TQKRm2xv1EJliUrJAFCjyblBd2/13J4izKegYNprEWgUTDW4idMpiwmqYmFJjUPIRMmI6uohFvGzkCD3HtJxloPWyHMyniafNFIigsJmlJwe3A08du08RIfXJSgbFzUSLXth5aufqneIZxvu8hknUxb1erh6eXSKuBnE/nY98zS02PHH2kJt6fH2F/uCqYQm50aQ8FARvi/U/EuoRuyXuS+7Thtv+mT/XYae8e7NNTMDJk1aI3oEQnI5Ysmnk7GzYK6ssitXq64r28/4iZyjeVf2hIgahY+OMzDftktBWjW95/PuafczXzXx1D+rGLv6em5GarQKlceFC2rUMWTHc2PnPskZrwa8gISrY1yHazhnwCBYCE/O4T+JHY2/djb/8fWeLQ+P0+AIBDS719f3xT5fX/bZO2t21oAhaIULBCZZ0wBVOgpYBVSKlCWUogAaVFHWNd5hzCDa2TVrq0hfgYrA6VzV9souI+bh83EeovaC2jMFTwxxRXptVP1aemm+WjtgUr93vOee7NrwZw39dn+6NNcp+f9zy/zjnPOe8jUrO7/4zW6HQYG831ZCP3vEVk/S/KatErMnX/WoR7vgfFTC3wbh1+d7GpS5bUtaIUAGyky1oRXK9Vonjg6ApXkRW8Dsvjb8WxJPixnmt+RB5rcAaqFVHVF1g2EKhbTQlLsK9CuSdj2F5gRFRiRSwh9SIuw6btQNo98PcroMjb8KnC3yT4fiX8LYK/H3SErpFJkn4R10fDo68SU8024zsFk7jpG7JVsAAXCR+phI2AloeaLP3p5yFZ+gR81YqnepK1cDYULrztrN5NJsI52U8t7yMMnYbnCWi0oFxW8BKJDI42EVdv9h+GJI2bR2bKFCAdFb1yZioVL3gEu+2t1qYgWhiSNgM49bRmnH0UbFWYPXPc8A99hWduF+r5OfEAiRJh+gslSBSs/9qoYNJlbOtdFFkwG4utFHLHQ+KhJ4l3HQBmhTQqdP/56mi6/3TKkAatXvUNwaXrbloed8QGUylDXc3r0SD8lnUIHt2L4NGwcw9fBDVX89v/KqSNQM83msPKYUV28Vcw0A/KGKgwsQQCWKqMHWK9wl4LNyxbHzvIn14XVqKImPOXipgUHYVfKxMpYpxg0as0Fl18QybbwSfBC9Q9gYRWP4C1r/HBToefyA4TFsb9df6DQYR9hy/XCejHGIvcF05jhNLCVuVClExalRGeUYJrKSvD4BAkFkTEbcURGWKNmxNljXuK3X0XoZgWvu5N4pPfNEieUZ7VntUul4tb2xD38IRDTGiBzer3duFOuDYirLCe3OP39vq9XyIA1dpsHcN1YLK9VzQx2c49owz2ToPdBAzxl5PtXZPtPQb7CYNddmBrv3slNXRsbFs2xJ0m8EekHZzAOH0tda1NZJKIGF8UUz5ZHIxD4Ul92VKsBIDBGtnJQGOTuMIUR6GsmQs04YrRBRPWOsRQDxjBM6dDjGBdT1GcKHRhdrA+xwFPdI7QhF44dFWvWFmjVV+AOZobnr8N5WVNk/RGT7LkkdzkX/6jKeiww47z478hBYqVgKvFmb4tUQTfoSCEbjYHya6+Sx6iTvqkYImWa8jthu9I0QIoYi18yj/Q18FBiMrQ+dUiYiPGWMDYgrkYTqZoMnC0FNl7Kv4sgZ/Lkb/ZmcKqnYSyl8mbUoQ/MrojXPAUVolxus0Pt7C7xOtHMK13EYmAb/2jM9p3r7r5IJCV77kFHdCA29JVD5uEGwiyGs/A9NaWkHqH2v0RHnOX7+9X1SKLkGncoUh+IpweMwv4YLfgb7QqkZW5UGxSFDSzKLsEsiGSUQ5ZQAdKOwVSDTBO6L4p6Ew7QYcyURO1EPSzjA1EiD8geZFoESx2iYOeX1wtIokE7Nsd6BCnT9VA6bEyLC+yhQxZCeRXlPxRNQb04GX3pkp8xi2R5zZJqyFlDRoxjlssS8JOINYdTuNb3ejBcvXvBThpDzWHe3/fAmuCkukhFfGOkJB7x1e47xyOXS/I/l73X0L6fp1/GZAiLCF8z4spbWJ1oSltijy3tPQxIl0X4C3aImOtuPfG2FWQM6NWzqLXi4c5nlcgox4eWj8ZmyJfPBKXt1bE5RbXd7dN6rNbZGXUe8k8EejpT3mv2MgHfgrfFhiDaR0p743vWGB8r8IYK4LThfEWvLDdw5PjXSZTWnp38tkvkynHLz5LHnKZbMG7VHXPTrow7uWfPNtPImwjFghs3UK3x4fohraXX7G7H5ZVxRB1S3QVj8Wr4lWtis+fjVcFKUMialmUY+IrIWddjWkWHINKMjpneyeIyviER9CUo6W1c7itcSlUfgmC90+jr0PaPZZAe5XMN4iGh8TwjO39x3/Ci3C0V5LVRgtUEUxWt+Ino1+onjA2HCbj3dHweYForkxv723tPVPivSceBGRMeXGJCS0phyjYyUESr5Ak7+WscRFe2tuwVwuQ18IdoN3eu2v2TdX+mgF/zZdiBfmpAKwWbTIS99kWM4sD9kGHDvO5AzZNnLwRSmMN4FZGH+gN2Q19SopLHTkV9iFdZYz3Tk0PhSvWZCjF4C9R+MXXxjrBxlHIa9cd7qfo6PxeK09H94KBSA5Qv/JI9khu/QzsRiwOYew1W8RFVIXmXLB3GwnGIkuDssgJcwSoSg9zeMH5/AtEmj9uUws/UK7SGqJ4CaK21/mmICklLG7tZKNY5WWhylEnLnhS5BTDCvi1pXSAxAZ2zg2/fI4zerdcjfc73gp+E3QIw63DozLNmQPt7AV65XyKjAq9WwkH5AVLksXJhpHJtGh75BM/n9Qg2egTgUb6eVEdnEL9O7Yosn8kGokRGCHwi9KHoejopwS+vESOgbV+Plff/HKFxhRYlbK84Hi8o3EAa0oqY1gKXyCwG1pnV+KkiZnXQypJoEouildJqichfi0B6qJ5T6nc+mGiTfZ9aJwWsX4osZUnwpxqi3piCD2p84ujPCFycWiaW9g/yCf2arZMZq/4eLZi9fHVSnrdKxKu+dOpVR8xeyYwccFxwtLekw2zKhSngNxxEaU9Gjc6rGMkNv30R8moj2PllubhF4NEM1CVo1xbp06Gub3uhjr1cvjcMKtOLcC5fkWdupgUucHiOjUTcq+bW6eOhM8N1jp1Gn5eVqfm46dcp1omwECOxyWOmAuBzVKnAA18eQNa2pobUCTw0V21pPyENeZox9gAyaVOTYeCxyXIpAu9N+sVsdfd/F1hgGPWfy+9EX2cB/XailTvQLjCqMoswYmRFW2NqShdVAS9XIpksQ8OhcK9LVtCd4fVDpl4Z9PZmY8ddlmYaZ2NQ8GL79shU8XZasEM11GGIedSHqzf99wYHALX4swvtaCbDd/Bt4ZzoA8kltv+bCCOmJe8TRE4cvjvfo9GxtVszjFgFwuLjQQINTuIkEQ/9pAP3CJxQa/A16vYciNwdbOAVaYbAcGJ116KkDLA5XaJKpRw0C5I3/hRMM3Jd+8gtJjZaMT+Lm0NqApGB17yy5zzKl4kraQ7qmzKg0w6tLgKYYVt+lNqwcF/JCpDQ+YrgdldG84+Fe27J3tg+kMbuVKfD1dNgmKag5Gi1ocibTtJ8Vr5V0LAwQ00G3qav+4XGv5T5OjCyY5mqmgsO94jNSd0ghhTeZNw4/Q3iiCwuKyCpUJJcmW/3bQWN6wZgS0SHMR1pz4H+leNTMIfrdyYJH2OqgIsGBwzB+PUrDspYA0ugoRgiu8JgXNHjwoJAlWZEBGuedh8GhQzARCGfUkrIoOGdRQ1VvPcmwjmYj/taSAjKLdont4yf9iMALomgUHhvYhAKlMgocyJACSbwvNlH4XvQjZhame32v8+KuPYZrE5ju2b6O11wQKaqnlaL3iom2IKw9fZ+HUz2a48Kv7j2/C6m8IQGqFYTd6LGEXXKyTABGW4R6fvrSEHoSEGlZuQu3K+H5fFpLRd75+DxaQcF3XGYTGF7lrd+5DGY9U91Y+EsnUUfuEdtc9QJG3Cp2/DUw1/TgYeSiY8PrZ5E7FXd+OHv9wkRE0QeexyYduGeeQgY2ztNBYeqSIPGdzFU2BLnp/Gqv3oqABjAFVltH5oLHOXObhzGqHdBzPa7aYMKWVTMEk04zV1V4eD5oRjgym5NCOmhoI3sMYTdONK8FfItqz2PUE50VJj4zVRkQHkq+BFSML25UsVShrTT9DseJLN3HVxcuNRmT0koAlavE9P0AYTjeOG4GRgjhnnzWE7b4688+a44rw5Zp43R/7Zc9T1GKPDtlVKFKNtkCKy4YUkb+pLJQcY2NIMzA5Mk56IUmKyjoAbiia2piJN8mTzL1s/jwklhphOeLjzG+7T7JZg5pRk+e2WSse8zdUBu8XBd5en6WFrNA5jBHAYoTiEh0K2hZW3nfx59fNr0ftMDg6QFWv3kv0G/ZYhm9d/jE+VlHYpf85N1SGnqu5Z30/SKvsyL8bo9SQfB4ln96nvLnwwKdr1IbBYaU+Q77ypmn9UYETJel6xfI4KYCf+Pl42zCtHSAgk34kCWURGTMOqkjPzoKpVUJUnm24QPgnIYsMcaUX9IprNN1sHgfgOxIB1eIThRWW9wIe9CTZZdpC/UZ4WC5qzNFKnLJv3lJjL4F8G/huG/0z4Lx3/peG/VPwnl5n3liTjP2OZOjVgf7py0/Sbqj25sPo5ORXmwzP4sUs4Ctpe421XRVxwrflNbwWrXgMDY6l8e+qqan4rrP81j+HDNi1DTyjDAczgoAw9oQyCyG42wN/AFPSnytiHOTF4bsvjRcFM/oCekLIP2wh+PNSuKmIH3Y476N//lhzP0p/S/mggRXBKM21dZijqa5mKi4C0HWcrdfu5SlnOVsoeVQohz6CUENTiHB1UZMS5GrKeraETiZGlRqjeTCplYbKwg86K47ZABR9LPEdz2dHNOVm51TdREujXVc14VToCVkARXZAqWhUX4B0p+iaLfcCNThPkm5YZI8RXN0vQLF5HBE2sqDmCltGEMWHmi6XI/GmQn1nKHOqSGDLi8v7DziS0bvEX57Un90xHg9EpRhGWcIhTE9+981xbgcZC56FVZ8cLBoldk8cSytUdiNkwJMMLERmMURkIC5/y3P+CgVCGF+fhvpqgNsmCcybmb1gofEnurqQhyn7RyLKIRkzRvUA22yJs+k8RP/1dyOurhTlnM+9N9g0YvOnoxcG/el9VgxNQZDfxOwbpWmsE/JDpHDjq4kee1E0Xh6h54poI4mRAu74GVTFSu3983iCZ96ZgC1ZbBx8r2piImIqkJ3C5+XNPaQDkw8hyBhUls2ESCY0Aa0OZe+WcWEC4H98B586k5eIGt4fUimQDLHnLySvibX7Ljn7Vk0976vUvkuE91wzvKRTu39AREt6MzNAb5yfoVlw34G0XFN8OxYPDWWkXf2uPQWr+ez9dyvYwyspvWB4TZyITgdFJKhW2xTbVY7B1LFi+Bq/wy3v9NV+22wfRMqHwCFDlwWYDXak5+Vcw53jXaYw7PJ90xQMqFqHEUDkT8qRHcCZTJlFyxONQ0h8qGSrFT0HGCMNYkP6b8AaA9bJi2Zeveis9GfyaR4Oq9nOx083et6lssbHhsHKZ7zYZOLTmXUCdyVcZ+xISKLD1CN9A2vphzNiwdMZNuLoT0wd8rRbvm+jPpCSr77De4H42T/bnr7q+sinkqKn7Z069N+rUZQno2UZ9snXMA8azCqaKMhb3KQq8I1y4J/gOWuZBF2E7+pSlwIMc9Vhr0DLPvLej9X8sviMJwT+zYiNKURij3m7yW9lBMVPDkZY81ubtf4Z5cmaZdtNv6/CXn2i3d5JPA1lg44X/8pIkCS8ElvUUviXEPN9p1ZvO9jVThp5gDmt8Cel+rXq1HzI55FoDPC48svG6whK5Zhm6vs7eUvi18jK6C6X+MgnBA+Aroh/XnHA6KTSSv7yT5uIESIZGg6NxalXvNhAv0Dz7tLjzpw52r8O7gqo9Bi0C+Qn+3L0w1j3LYkKkobtUwJ6p81gZUGpFefgik02/C3g/t8eivmM7DIeueXurZzg7Bb864JdnhHl7WzglYFwYMC6Ivpk077XLGMUeGgFumtVmO/h96MVZm+397hoyBpuA0TfMe5eZWHLrh5b0v5RhsI0yivmrg+vHat7jVIoWCOevNOlfqzT4rSqV/rVKC75VpQnnqFRTktCCLJL7JItS6HTzUjR3KpfNewfM+9sdzsptsMwqd8IadPERkGTea/AdyFxDMD+j3OhFeu9OrPv6eJ65EZUbqXK89h5S+RNU+XPfxK18R7zKYbfHOYUyPGLouNnxyts0I+p3zHvssttRmZig/WbjciFbcHRdDcc8yjgK3gSMGVe9Xeo7HoMbTRi7HBg+yfu3VVFBK4R7cUiPlA5c7ggbAkshQq7Yo7UXZJKvUwZJNb19VZQhtm7Eh7wvDqLTvBetLUkm9Nu71JFrL8AAVZ1RlfVJ8n7sv/ITX02npOR4Et2odwvYW9CKaoyAlWD2rtZOOd1+yLwXJJwuVpwNVXf57SfwZSq3I2EfJ8KuhHMOhGKYJl2SMoysKbCtXSKKaQGUa+gj++8uJPzaNYXHle9T7BnZ4QfWlXpI/bgIaQX9aGjBniiy6Aswj+JzDJQehdUf5G6cQ9A/Pa5X7Nwk4c2tBYvAqqtBArFzB8nhL4kXXMrG3Qwte9RKx4P4gemeBIIGUt8qKVHskLIR3nJoymRIqY5bZrj2BmFKhow8GqZHhD+MtiR16tNAH2trX9tjXt2I3QLjdLOwTlvrRU3j4DgJ2IwaWVyJsKOtHxrTD9kO+T5cazskDKf62rKVXDppgRuF4YNNc7vDvN8uOyofwnF7jMZt52kct6z+d1s/Tak7ihzRxfu0mD4r4sCtD7mRoabcfa1rzfV/QeU6TDz2df+7rB2mqe/Q3RNbhVfKLtHrpnE61xGa0aiorG+5LZfPOmtPf0M9PX2KetqHFs3KEvHerTxlYtuuFO88gfk7xB0jfOMtgldboeowwu+wkP8oXkvFECB8P3PMNhQvKP5wKctQQs06/8gkoia08kl6rwkYElK8zacp6QO2gbpPN8EW4jtgsg34zzIWsftekTLLDfs17xtAGlqIhqbtDp1IRl9nikbL31KbfxggWsLOvorG5beXRYZP14c7hAjkSeATcSF/fM4sC86f5Xfny2LkL0jnzfL++bNcdb6GEnnZ+WpJ5N7zZzkePwselwkCXTIb2N9hY2kGonyjFeXJMNPwZEXyT/yeLAmBI2bBaTXwxO/JseUrtfKlYpDFjVyRuJEreIo2jCsuURHklNIFGAdbjMZWJkeZOjJfbIA=
*/