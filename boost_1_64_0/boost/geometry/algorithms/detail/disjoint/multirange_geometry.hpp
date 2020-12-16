// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2017, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_MULTIRANGE_GEOMETRY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_MULTIRANGE_GEOMETRY_HPP

#include <boost/range.hpp>

#include <boost/geometry/algorithms/detail/check_iterator_range.hpp>
#include <boost/geometry/algorithms/dispatch/disjoint.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace disjoint
{


template <typename Geometry, typename Strategy, typename BinaryPredicate>
class unary_disjoint_geometry_to_query_geometry
{
public:
    unary_disjoint_geometry_to_query_geometry(Geometry const& geometry,
                                              Strategy const& strategy)
        : m_geometry(geometry)
        , m_strategy(strategy)
    {}

    template <typename QueryGeometry>
    inline bool apply(QueryGeometry const& query_geometry) const
    {
        return BinaryPredicate::apply(query_geometry, m_geometry, m_strategy);
    }

private:
    Geometry const& m_geometry;
    Strategy const& m_strategy;
};


template<typename MultiRange, typename ConstantSizeGeometry>
struct multirange_constant_size_geometry
{
    template <typename Strategy>
    static inline bool apply(MultiRange const& multirange,
                             ConstantSizeGeometry const& constant_size_geometry,
                             Strategy const& strategy)
    {
        typedef unary_disjoint_geometry_to_query_geometry
            <
                ConstantSizeGeometry,
                Strategy,
                dispatch::disjoint
                    <
                        typename boost::range_value<MultiRange>::type,
                        ConstantSizeGeometry
                    >
            > unary_predicate_type;

        return detail::check_iterator_range
            <
                unary_predicate_type
            >::apply(boost::begin(multirange), boost::end(multirange),
                     unary_predicate_type(constant_size_geometry, strategy));
    }

    template <typename Strategy>
    static inline bool apply(ConstantSizeGeometry const& constant_size_geometry,
                             MultiRange const& multirange,
                             Strategy const& strategy)
    {
        return apply(multirange, constant_size_geometry, strategy);
    }
};


}} // namespace detail::disjoint
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_MULTIRANGE_GEOMETRY_HPP

/* multirange_geometry.hpp
WCvp9Bs897ezvmK0utP3WzaEDyPPoOvqPxfeqaddLZ6t3zXNKnZo+OfhOLkS6wU75Xx7/dlguLNPLNEnX+iN/6vFo/i/1VjaBE6fRayv/xqe6AfbjRTPMPurwXA1izoYyacWiZpk3B/RYyqq7epW9QdhUid2a8C3cGZndlwn0Vse1VerJauOwOjMdMFLxFRNY9rOLr67WS7uhBP5x9GI6qqLOPtVMPMtPU8JmHfBQ57/SD8qgUveg2uP+AmX6iceWtPeYVrVJ2jhWdXVyuyiDx5Fl76ynDzks9X4+AAc4Qfct8iOEC7yvX3f0oycr2AdfQmtrQO99FB3eFVXr802o/iphrj/Vn9T5GxxK9b6nE9D/Mk88pvnbpx1HM4y2M9bYgm9lCYZhdHrjKVtokc/yY8LPxpC02Yx/aH4EJp51MTm8nmxnLzkCXY/EqPr4GTb4PI9dPSp+FdvMYsLbhlj3W4BnvWYfKE3voa79jwHT80Ea8XU1nF4ClzNfAsfWaNKuUKuiqHscnraNeYr7ruy5Qty7Q/sWra+XocOUU+8DUs7eZ/ctXnl0hWwjQaeDWbMxcWa4GC5bpBfDWgAF8B4c1/p3HdOp6vTv9qz00g5sjWb3oXNl/4YD5/ez/7t+T47TW9znE348Atr5+fCsCvVnwnOAbPzH8f91ZP+H8sZn1e4GTcYq9aNtt7jXL/Bleb41dB4Yp8jH62h9z4DKum8u2DopFo48WI6aD+9W3NYwF7r13seD80xWc/dzBd77mFD2HbgPb2t/M1nbnmnyN1KcND41+Bl3yc0PXXyzRfgnfnOslY0riCbwPSknAltw/NjWlt3bSYXfmCfIO57BOsHcbBNuzpEt7mXj94VJ3hWh2fZR858nhtW1NIrrIKvMGNYfhj1AhtPVCPpMv2cZ3VhssRiNY8e3O8CnPw5MabHz92AHcRXIz6rO0If86YaVBV/lfc52eWLN9VHeupt8KbRJvXzQXziaDAvffzL+nW51eURWDJHTnylVsLwJL5o9Qr+uUqfA/+eMcZJ1g0q6eWmNqFRFYnTHGnxRcyNv2v0pDsI1No79Bf91ewUmMNHbemiI+jSmxK9WnP3fqqxC+RhzbvVqlSQu1YPScOpf1R9+l7PTgPttdO1ZpofnlMZPo2cA+s3WHffBNsnqZ/4U/PxkXUcXFot+FV+NnyF/SrArLPk0XXy2VpQITrACtjUupZ4YOti9KxmPfFUsfTepfJMPeiVlx6Sm29p/WPH6aNxujN76GecL594rd/ZOZbC0Uny/yJxvFk+dDK2SvxEq+xdn9b0uBqyAd7W1yN2VjMOOHYYLNczNGbvV8V59Zj4gpk/lMPxRsMW+ZaLfevLqY8rizt9ad/jNP0xuCpMOwxzC4up1/LCM9rqy/hPG3EwIZex8tNkcbnRmL7h13U5jFnsXLAeto6GdXr+2/qqN+PhkHWCsvTR4nhNhxLGhIMUh5tpT8GXgeL4Yhj7iZq2Wx7htMdh2jnyqfNH7FgGf2XbPE/5/094MB60EM/dI2bX0v9r6TGWsucZ0+HmeGO5BN74XX+1ZZIxtKirFsDjXXx1rDC7w6T7W8ipauKokBrTS0zI/bT+PnvQHDPR8OTPOYv4dmUUHnDdiXLyjpawUt5lmQCPYc0s6+ftZ+MKr0fpWDEQxy3zGL0IV6heTO7Jy/gH1iBmqU04XJ3KYvsBWn5BteAWOHOefTqB3XbiIfrcTHBm9OKTfdTEufj7nfrxLXJyCU2va0wvrP/pfHKPzrNjaeE1+DGP/MoL1y9lb987KysejEM03W796TN5lRMm8MvM79QxYzv40cm9PRsaWxP71Ttl1Ogv7JvJ9pi+kebach4=
*/