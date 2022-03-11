// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014, 2017, 2019.
// Modifications copyright (c) 2014-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERSECTION_INTERFACE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERSECTION_INTERFACE_HPP


#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/algorithms/detail/overlay/intersection_insert.hpp>
#include <boost/geometry/algorithms/detail/tupled_output.hpp>
#include <boost/geometry/policies/robustness/get_rescale_policy.hpp>
#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/util/range.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

// By default, all is forwarded to the intersection_insert-dispatcher
template
<
    typename Geometry1, typename Geometry2,
    typename Tag1 = typename geometry::tag<Geometry1>::type,
    typename Tag2 = typename geometry::tag<Geometry2>::type,
    bool Reverse = reverse_dispatch<Geometry1, Geometry2>::type::value
>
struct intersection
{
    template <typename RobustPolicy, typename GeometryOut, typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
            Geometry2 const& geometry2,
            RobustPolicy const& robust_policy,
            GeometryOut& geometry_out,
            Strategy const& strategy)
    {
        typedef typename geometry::detail::output_geometry_value
            <
                GeometryOut
            >::type SingleOut;

        intersection_insert
            <
                Geometry1, Geometry2, SingleOut,
                overlay_intersection
            >::apply(geometry1, geometry2, robust_policy,
                     geometry::detail::output_geometry_back_inserter(geometry_out),
                     strategy);

        return true;
    }

};


// If reversal is needed, perform it
template
<
    typename Geometry1, typename Geometry2,
    typename Tag1, typename Tag2
>
struct intersection
<
    Geometry1, Geometry2,
    Tag1, Tag2,
    true
>
    : intersection<Geometry2, Geometry1, Tag2, Tag1, false>
{
    template <typename RobustPolicy, typename GeometryOut, typename Strategy>
    static inline bool apply(
        Geometry1 const& g1,
        Geometry2 const& g2,
        RobustPolicy const& robust_policy,
        GeometryOut& out,
        Strategy const& strategy)
    {
        return intersection
            <
                Geometry2, Geometry1,
                Tag2, Tag1,
                false
            >::apply(g2, g1, robust_policy, out, strategy);
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_strategy {

struct intersection
{
    template
    <
        typename Geometry1,
        typename Geometry2,
        typename GeometryOut,
        typename Strategy
    >
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             GeometryOut & geometry_out,
                             Strategy const& strategy)
    {
        typedef typename geometry::rescale_overlay_policy_type
            <
                Geometry1,
                Geometry2,
                typename Strategy::cs_tag
            >::type rescale_policy_type;
        
        rescale_policy_type robust_policy
            = geometry::get_rescale_policy<rescale_policy_type>(
                    geometry1, geometry2, strategy);

        return dispatch::intersection
            <
                Geometry1,
                Geometry2
            >::apply(geometry1, geometry2, robust_policy, geometry_out,
                     strategy);
    }

    template
    <
        typename Geometry1,
        typename Geometry2,
        typename GeometryOut
    >
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             GeometryOut & geometry_out,
                             default_strategy)
    {
        typedef typename geometry::rescale_overlay_policy_type
            <
                Geometry1,
                Geometry2,
                typename geometry::cs_tag<Geometry1>::type
            >::type rescale_policy_type;
        
        typename strategy::relate::services::default_strategy
            <
                Geometry1, Geometry2
            >::type strategy;

        rescale_policy_type robust_policy
            = geometry::get_rescale_policy<rescale_policy_type>(
                    geometry1, geometry2, strategy);

        return dispatch::intersection
            <
                Geometry1,
                Geometry2
            >::apply(geometry1, geometry2, robust_policy, geometry_out,
                     strategy);
    }
};

} // resolve_strategy


namespace resolve_variant
{
    
template <typename Geometry1, typename Geometry2>
struct intersection
{
    template <typename GeometryOut, typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             GeometryOut& geometry_out,
                             Strategy const& strategy)
    {
        concepts::check<Geometry1 const>();
        concepts::check<Geometry2 const>();
        
        return resolve_strategy::intersection::apply(geometry1,
                                                     geometry2,
                                                     geometry_out,
                                                     strategy);
    }
};


template <BOOST_VARIANT_ENUM_PARAMS(typename T), typename Geometry2>
struct intersection<variant<BOOST_VARIANT_ENUM_PARAMS(T)>, Geometry2>
{
    template <typename GeometryOut, typename Strategy>
    struct visitor: static_visitor<bool>
    {
        Geometry2 const& m_geometry2;
        GeometryOut& m_geometry_out;
        Strategy const& m_strategy;
        
        visitor(Geometry2 const& geometry2,
                GeometryOut& geometry_out,
                Strategy const& strategy)
            : m_geometry2(geometry2)
            , m_geometry_out(geometry_out)
            , m_strategy(strategy)
        {}
        
        template <typename Geometry1>
        bool operator()(Geometry1 const& geometry1) const
        {
            return intersection
                <
                    Geometry1,
                    Geometry2
                >::apply(geometry1, m_geometry2, m_geometry_out, m_strategy);
        }
    };
    
    template <typename GeometryOut, typename Strategy>
    static inline bool
    apply(variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry1,
          Geometry2 const& geometry2,
          GeometryOut& geometry_out,
          Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<GeometryOut, Strategy>(geometry2,
                                                                   geometry_out,
                                                                   strategy),
                                    geometry1);
    }
};


template <typename Geometry1, BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct intersection<Geometry1, variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    template <typename GeometryOut, typename Strategy>
    struct visitor: static_visitor<bool>
    {
        Geometry1 const& m_geometry1;
        GeometryOut& m_geometry_out;
        Strategy const& m_strategy;
        
        visitor(Geometry1 const& geometry1,
                GeometryOut& geometry_out,
                Strategy const& strategy)
            : m_geometry1(geometry1)
            , m_geometry_out(geometry_out)
            , m_strategy(strategy)
        {}
        
        template <typename Geometry2>
        bool operator()(Geometry2 const& geometry2) const
        {
            return intersection
                <
                    Geometry1,
                    Geometry2
                >::apply(m_geometry1, geometry2, m_geometry_out, m_strategy);
        }
    };
    
    template <typename GeometryOut, typename Strategy>
    static inline bool
    apply(Geometry1 const& geometry1,
          variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry2,
          GeometryOut& geometry_out,
          Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<GeometryOut, Strategy>(geometry1,
                                                                   geometry_out,
                                                                   strategy),
                                    geometry2);
    }
};


template <BOOST_VARIANT_ENUM_PARAMS(typename T1), BOOST_VARIANT_ENUM_PARAMS(typename T2)>
struct intersection<variant<BOOST_VARIANT_ENUM_PARAMS(T1)>, variant<BOOST_VARIANT_ENUM_PARAMS(T2)> >
{
    template <typename GeometryOut, typename Strategy>
    struct visitor: static_visitor<bool>
    {
        GeometryOut& m_geometry_out;
        Strategy const& m_strategy;
        
        visitor(GeometryOut& geometry_out, Strategy const& strategy)
            : m_geometry_out(geometry_out)
            , m_strategy(strategy)
        {}
        
        template <typename Geometry1, typename Geometry2>
        bool operator()(Geometry1 const& geometry1,
                        Geometry2 const& geometry2) const
        {
            return intersection
                <
                    Geometry1,
                    Geometry2
                >::apply(geometry1, geometry2, m_geometry_out, m_strategy);
        }
    };
    
    template <typename GeometryOut, typename Strategy>
    static inline bool
    apply(variant<BOOST_VARIANT_ENUM_PARAMS(T1)> const& geometry1,
          variant<BOOST_VARIANT_ENUM_PARAMS(T2)> const& geometry2,
          GeometryOut& geometry_out,
          Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<GeometryOut, Strategy>(geometry_out,
                                                                   strategy),
                                    geometry1, geometry2);
    }
};
    
} // namespace resolve_variant
    

/*!
\brief \brief_calc2{intersection}
\ingroup intersection
\details \details_calc2{intersection, spatial set theoretic intersection}.
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\tparam GeometryOut Collection of geometries (e.g. std::vector, std::deque, boost::geometry::multi*) of which
    the value_type fulfills a \p_l_or_c concept, or it is the output geometry (e.g. for a box)
\tparam Strategy \tparam_strategy{Intersection}
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\param geometry_out The output geometry, either a multi_point, multi_polygon,
    multi_linestring, or a box (for intersection of two boxes)
\param strategy \param_strategy{intersection}

\qbk{distinguish,with strategy}
\qbk{[include reference/algorithms/intersection.qbk]}
*/
template
<
    typename Geometry1,
    typename Geometry2,
    typename GeometryOut,
    typename Strategy
>
inline bool intersection(Geometry1 const& geometry1,
                         Geometry2 const& geometry2,
                         GeometryOut& geometry_out,
                         Strategy const& strategy)
{
    return resolve_variant::intersection
        <
            Geometry1,
            Geometry2
        >::apply(geometry1, geometry2, geometry_out, strategy);
}


/*!
\brief \brief_calc2{intersection}
\ingroup intersection
\details \details_calc2{intersection, spatial set theoretic intersection}.
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\tparam GeometryOut Collection of geometries (e.g. std::vector, std::deque, boost::geometry::multi*) of which
    the value_type fulfills a \p_l_or_c concept, or it is the output geometry (e.g. for a box)
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\param geometry_out The output geometry, either a multi_point, multi_polygon,
    multi_linestring, or a box (for intersection of two boxes)

\qbk{[include reference/algorithms/intersection.qbk]}
*/
template
<
    typename Geometry1,
    typename Geometry2,
    typename GeometryOut
>
inline bool intersection(Geometry1 const& geometry1,
                         Geometry2 const& geometry2,
                         GeometryOut& geometry_out)
{
    return resolve_variant::intersection
        <
            Geometry1,
            Geometry2
        >::apply(geometry1, geometry2, geometry_out, default_strategy());
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERSECTION_INTERFACE_HPP

/* interface.hpp
Ya0hWPaGsHoPeEwIKuGtiwH7ObastObiw7wBWYD7POkOaM1BbTuHs9xlJmv6AOhymaVL+NvTABlCPGO3Y7t06nYyeeWgx8AvFyrsZpjb8FDFoqmFkpJ5MScWBBAmZPw9ips9gTGnaweD+xx0l7GLLjvW7QpzKt75zMjpJKCrgw2+ZbUB0J0vzIPen5CK+54dhxn+wWZSpRN/ABas4sk8wHQncpsGpLFAP4cEBNG9jK0YzRdwnQopL3BMZOcA+1KTwe0Wr+rySghZA/RxcExFszKsmnZM/5+Dmv4lBuw+J5sQ4L6hG4n/mKJT8s7aqGJ/9qMFo18LDq9wvg1jgc/uzoCR/htTLJ8BdbCs1RNYrtkIVBYfIRLFQBvJXdDhemYq9SGcyF/XmdR9XJhbgVlFFXu2Pz80Rsi1tDisF9Mngo9tYQcHGV2xy/xBItwiKfTEI/etTQ2x88rRYBpSvXj2YHP4gZP3VuhAUko5ngpKOSryt9rFwpB0kC2B+ud0zv4EYYudM73Mzu9BKa7FdBTHoutTQLAPI+2r+l9/TeGDUgul/wVRV9xuHLzkJ5yxAupEyHBhMs1RyaktqmTvWJ2JN+1ybOassLnUvpNHniHfsHiCVpqRgAHguAiG/gDfug49JSznP9m8XFr3jZI54pk33gkXCmmg5ma35LX04VIykHohmazy9yfAW0GnS7jURWrvRy5OJZ1ktzXVzZT8w2oPz5u+TccISJtZqGi62JcYLsJtPi+2Fc0BUenVntfIkhCDhXnB+3BafFqU0aGXfrj7DIVhYPalOR7R6OvjPdiQ08gpMYCFvqMmS4G736PyTLgF/fvD85U4WC4BLyzFcXWBcHCdDviW3y7OiBBJdc6wa7Eustp6+PDkB4zPaLe3hTYQ+54ukwZ1d/OQ8PIRMyWs/Pk3Jl1KNdbECPCfcazQXJVisroKXaA2WS2U6b70Hpwak+fsUKYVvZq0qX2LJYO63XZmjeG9gZbPGeflzZO+E+70wNsql/SJtIMU+2DrZE86t8gZ0v+esJd7xnVLilTDbR+dUGUbzXNbMaQVy577O6dKpBkyQNpkuxriMln4WabHpSFjGDSdAZsvpCyWzcOrL1LX65WlZdYTLB/2vjEECX3zJO3n4Q0NoLmP0CzQTWlRcHWePU0ZtKdqMb5kSdYiH2iyG6ohub7S67EfkBZGeb2EWvGqBDtk709LFfkmH5vHPGSMu3IU0Wt5+3qpQHzLJJcv1enn0sKnyX0ti2J0qxIfGHw1ImMHNJmdDYOYLeKfYR9vEX60R3o731qDfTffCMmNVoeN7hLIf3NLyTqaAmrgXktf7+8fYeyREl93bwsaabtzOPzJr6NVFsKVUO0XwAuHhr5M59DRwa0fNCFX9MQCs4eHemSO93rDzTwLIR1/cKU15z0u/v/eBqQX0nL3r40LIsoaUSRNx8JaTceKWUGJ9JwVkHWSVRRzP7g/NBmt5rW06gZI9nAeeGynfwN3lYOmRXNztdKiRWRYBAbExj8ywHq/JQqU2oWV0fxINDOIepGT38+fmSkehK9dz0vRBkbTmSz22d3P+WjwCqaH8xJGP0zq/IWIYVbgCPWsrx/wwD5iNnpOZX8f5rZwSyH4tersxtDVfyY+HhFYHhsFwZo8h0anUhS2ghdpbySXjNnm4UbSeoANqWwXQNTg3HSM8zhllwW/V2POiohm3Ujj1hb/cXzLoNLrjHzwZcOpDSmCNivaMg0UqDEaB9Z/Y715L7hjhRBfRGVNih93BwB1lkYALGHqO66ZGZPRlthePqlXaAG2TtAYQne16vuCLTKhAYyxmk/AbWfwqEE4/cdDJyrzhqervAjUqPg+oyz5bCIJ1QGTdJuTEtY9Hj+F2Io3mMHD2RKsrtEtfgckKp0Xk1FeyE52oSD9T+iqzuOgdAQ+J3YD62DO1yMPinz5HlBknV4qPBCzYLwS0aNvcIT9tQzmI+ktY2d2ZpInFwOQw/ooxa8HfoNzRLPZuq+kdbSFayS7a/EKA6HdNZza6+zD5taeb2Hxd8I8FKfMFSvWen0ogIibTvwVUsxfB53qHBVGDMKSrVCauXIauZupilJDRVWl/L3WrzpiK2mqtbjFyDuvKXYlr9tbJ5PL7j60b976RLDZHdz9cCTPuzu8uz/0wb/33c6IeHEQkOCfz10z1b8cDg/2+6jC1cRkjzpPoYv+b/Ry0O1j0mHMewYqvTt0pWXapFkaoYS3sHg42Mq5fyOvusGjHlCz7IGQuSsDyPykmS5JFiobRIZfRMeQXWPRGmuMH2z7e9BWxbASHdVZT+BFoA7Dw5lYCvPop9BBA3uMl/cn6kyuwu4TLkuwiXNFoMQyjUSjIz4rbvCSViGhs2xTXk9nULxVPjjKvLHluc/lgdUxxLg+MobGgBDAeBllj8sNX4VeXU5x3nWELjuQTbA2x9Z5zAe23iM9VfvTcuo+CXMA2BZqNQZz/aZ39t45G039K4DeH+maivxni52Q7dBZEGVEWavz+ff9SERin9bkUjVdF1fwaMHlVZLbytcFpk61MlbLM8Q6jvxbECTsLuuX7FbFqthjQY8YQ3VKfGIZwJ5zAV/Tao2AGIJL6s4auIK4Dw6POkOozKax/RTflsW+HQ0fEfYBkGn3U6jX/zzN3wsKDTX9sqC8A+Co0I80ocJ6cM8aDUPnoe52Io/QKqZdpv+NPDVKfPONLK+i+431pqE2YgbIG36ptPDMjy6GrA2xBfoxINcGiKvop90OxDMYfpEQPVDSAc/840DUCZp8Yn8htRA5VrrWdVA5ERSlPX0lyGog0hBYTFKzAgNE0mpWzTWPYeBu0GB/oyTCWCSNtOD91jI+qBah7vx8ahT5rjqGr8vfUsExFeek1rbgSZDRavQcfOKTN/CQgdFulSclHQp4McOxykl0r7AAV644VKvh71xDxB4t74i4q03/SSKBJDhVA4YHCk+++Zbwn+ayZ/2u+flx7/Mbvnf5yaI9iGKr9F/9WtZgk6qDBGrCPNR9mdNypAiGBX20BsgoripOl3kUbq7rZR+i3IivJbSdtaD5B5ZFZMs9rmfzG5aVv01henavCiFyBCVcNucgKK+OAh2knvjbFqZmX5KQ9qLfLAxiP5Qk1+XQ9qLQP51Mydjlu6UOQZ4LTuA5TEGEiSKPmlCW1XtQdAMXmQWfS78DOQ/l4I2A3wzVWalcxb+UstYbdYbct4HDTjdGNj2Izo8/JcJtpIcHcEIjSDFEnfs5J6YTvdm86XbBXa8J5JOptmK4ABgzJs3YPGIOISa0DfGI5Do++eOepdhSQgrHqMK0pbc4TU94a+yoYrzTzSPZob02vpdK+Y8Vlh6E7BbcRqQN4shYSGghOUvUJ4u+WjpIS5SlXlv7HV9Z9BVYnXjxBv+ElJ57L9vEzHqA0ISjUodU7Z7FcmSq+G7IlCPR+kLzOHQCVgrcxmfUq5n8UPk/56eJ2SXK8Ti18GGSnT2KeyyUroskHQytgyVa8Bb2Zy157XQnuF7t5dUbBEXmejOPBfWezDoMZkBkBH/BjoqoVnZFdT3GQMwhllpT6JF2kSYxprYz2hSJnTRdPc4Hy+bMgaz9LeTL8fm4gwAwZFGEe6a8p9hnr4CAca09fmSK2sM1S62jQwiT+faKMhjgk8gZp/jM3R3K2F/uZwLOyYlBX1nmGogXe/9M3tnarjfXl+JnaN1PgqFRRHrL688nS2Ftza5q6XiGWb0ARKtmAASYu2D8jDqg6P2AXSS602rBg0zCWv1YK3c/74G6+eC957XSAgLWxZKz9BJ7CuH2w+/FkLD8ijLIPgK1JfgKFyBDMsna8a/Ue8TcY5bUDjJedUwY1lHN7YsWdixbSLTZPU4TFW2LKikwrsRv1RKegWyoIhuuew7Vi5FIKMKnYtE78WVTOfSMK26B29ugitUtzB2lBo9D6gPU2ZR/IRxaBjGcO3ZNX0XDYyO1MbvHSZS+YMDX8kIGYaKhRg/KrdXDslbxEl8iWNcn0nEb2NA2RkW+KWrOcc12Wa6sbXZ4F2GixnaHIieeHbo18Nb9ZVEnLrd5lPYsVoGlycHx6j28OBxUtz44PWDWiR39nJHf/WW6s9/V09DWr/N7imqk3KZXPkT+FZhwx4sIjFyLGPMibcpMbxIYXPcDRbC07xllg+FnnA3vMYZ3BpT/vp2yGdnfW/ME54FErTITO6ejT6h9w3vdQkLOmTdKifFlvZLguafwdZoYFHE+piHZVMcjb1HXGvgUDBPdgFBAnQQ88UZgIaRgqC+iZwjDKmkfNNy+POeXcA6mjpOxkg3GjwPGh9ZEf4pRI9BxRn/eoHYjtiVpmtASH6VqCl4X4mjFPU0pbcosneI4vlrCTFNyOteB7u9l00IyGfBmzKWY3DCYiTJyVyyEQof4h12T0gMzTqNiDfQfb67gmTDkaQUhWPP8uZ5xDrLKEWKr3Hh3WzglDaOPpGtvnShTbKxkH1D+E5XWL1ym9p0HTec5/ezOq/UDOKhSt2fxLNuoyV08+Fh/3RiieZ+RSYk4HfbtERHua1lP4Y9p8SbAv85lXORqIVfYFhLGLDezcZ+dfgyxtIhcGKF7c+MimvQ8CzPGbA9jZRLZy3pajjdzK503Yi9kgOe2uLe1ttqh/1fZ8sCrtEt1qYNhs4HAqQEYFIiWMV8fHpJ6PLJGHuiDSMke6HZ+gk9IeNxADv37zBkX4ijzIu61oJ1BLpP+1W4oMlKvEPyYIzE+aP2kxdLLKYWzs1ZWFizFgT8mxL8fkXv/jAFisHsaC21xH9PvNhp3oIM2UmsESVJmQeldFYXySpFZwq83A8rGA+iI+cB7+zsUpolGUSQRmJktRH9ZKFyr5R6tTzQKoHhc+1gfTPmRQHVxuNsgwvGcGB5tpckhkvwki2yNrnEhBcwFlnn8XRXuCq06x5tUnhcrrYONYD0WXN35w9maWJPIbjvG+th52btDcrqoBaze07RErAJTl6NRhSV1WWkujVJbwMx+anslrGKThFsB4f5EH5NDXh872vJLmI75uba39BiKpE4EAadO2JaGhyAdszLwWrgmyO840kv1UEo4e8rD3UtOFfnOJBqZyE2dRqauGVk27bTBEWL2IbIY8jv8aGhNDpvBJc/Xl5rhwFR8NaoSwUUZE5xd6GanleoMaZaGlSurVSxsRc1TGjHy8REh6NHe1t9r0KrTAYOdj0JjMaUNsDlKKE26f32MjHjv5/L7kK3l863EApjAkuF/VdeKZo3TbEe5KSI9XYfr6cSZ5VMo5AHHrHDayoOcd/sxPbs9nUvok0Zq5E6LisP5ns8fqPQoklztHum9k1Jc2+GISi1+RQuACCbHO6q95p6TXS2dpMhai7RCvjvvqD2V58wAAiz90/EAv0fMoN9ABkcEagDifZIWb/Y8FSH6CT7DDwtJm25TVsMcEOowzyUjlDEIhMen5NspD5/FPVEui49AxOaI5wEjhpzxDpmVzu5ICwKGpZ4D5q7W5rlqqsZEaQFaQTiWrwFSf0hlNNBNwof7LpE2odHNZnaDIqZdbIp5pW0yHSAI6N0W/4HTO029s3RES5pWT41NwSBOGRqmfzwGwB3w9Hr2zw+05eQDUntCIqMFycLVBTdNWFHdfW0pQ3Tk6Riay0FS0yD80eS/AnZJWfT6nghMlF/C+gRUs5MYRKtZ9Mwo9Prz9ofL1Tar+Ppj7nDUyvKBKt8vkplP0aukTxjUr12nt/rI9nkezlc9dh43IyrvOY4wDBiDA2s01A7DQMNbLaKXXZ88gvxY+4jlyXvn/xpSyxKZnKrJ510KW9fEG9wVP8iIZxNun5Dges59ri2tH8pxzuLof13qIy98WuSlPwO1Yobk9Tkiin8ZqBTZ2Pmyx05yY2QM2G5tRFhUnz/eu4GxKshW9uvPZ9ascTQVC/RDt+bsJ+islZaziE84PgUCDd01O1SCQp4chQJFrUr72eR2n6fgMHOjPY5b8tVyGVu6B8zQonoociyLXW1ldMhS2oaUp8kpMxr3rvYZSHBsUKynS1wnx89ywSNKYG3VuIJTw907q9zXLse69dHsWids9vRaHOgQI/+D6UNhsipWH4WOqlbyeJrjzBAg7svOLxRBei2+sMShEMRauoeVn67I/vhXgHHWzUFJNUs41l3QsIiYQ/07qPV+0xKgTyScZujVsPhiXE/recNmTOVQHPLoKn/pRSX6qzm5FBy5QdBq8VUVUM0i/aZD9KrqG0F/8LRNGAUvT0Rqy91Ib9DIZqOxIOX8cvyOU8x9l33LbuV0mbArh2rDLqrtduzUEeY9KPjr1eL+q6Ln/Ig5NoJv0U0nW58tadq9Ej3pmxMo+RY62ftYnEhziuN+mWUoglJP/z79H/L57xFSrratjNbp0lHGPC5G+dzP5aHKk1AqCeo8otnM6zjvMZlx8xcHMj8/tW1BpFpuqfqX4A6pAtF461ngOCWCK3vmUeuI3HRnl/SDSo8d83jm+8A2Uel8sH1qqA53pk6y5e4UkX7GEJXtVQ4g5srbybV+/dw2FUrnUdNtvWADEMz4i50j4ubnuhaf14977rgTE9337+9vQC8AQOCfoD/Bf0L+hP4J+xP+J+JP5J+oP9F/Yv7E/on7E/8n4U/in6Q/yX9S/qT+SfuT/ifjT+afrD/Zf3L+5P7J+5P/p+BP4Z+iP8V/Sv6U/in7U/6n4k/ln6o/1X9q/tT+qftT/6fhT+Ofpj/Nf1r+tP5p+9P+p+NP55+uP91/ev70/un70/9n4M/gn6E/w39G/oz+Gfsz/mfiz+SfqT/Tf2b+zP6Z+zP/Z+HP4p+lP8t/Vv6s/ln7s/5n48/mn60/2392/uz+2fuz/+fgz+Gfoz/Hf07+nP45+3P+5+LP5Z+rP9d/bv7c/rn7c//n4c/jn6c/z39e/rz+efvz/ufjz+efrz/ff37+APT9vf9qjwgO16l2aYGiS3NOOb4t5OTcpS925LoIHNmJejps47iZEOM2Rn3CYY4i2ZL6VEFa52Ntl4xb5jEuZL7KiY19E2aI8U1qAoXu+oYFmpmByVhFQO359XHTm1pjlUgJS19hsSYBt0cvNOB5gW2gQVqAaMDgMYe6YW95d2l9z9554KgTM7u++69KEHSfSkSI0+jU30vTa6af+tFW8CZYNXOwjoyh4PLcq+GsfF8Z3TvWUFo6Au7hC6eAUOuZMAYpVRD2HJm91++kQx8UM+u66KSM9KriUfICwr+pfGn4WuQpD36bGPeNUP4ekVT+b851i0f6rqHAPuMxMXFHie6Gu4oRd8BDa8pngF3PHX1n5XaXfhktyzD2OjEPvN4msMoZPqRWxqBHgXIjrqHPINMPiJrgWYy4tVLcy4dfvCZ8YrMYdiHajCbGm6aOvDx0vrNQCyAeGLABjho1OhhWOIzIFb6f5+N4EHMvUfsOylXGIhHEB/jX6ZoV+GWc9ZB1lFmrrfyTi0odDAMuVR5xb0ROb6VFGhgAhkrYneDWvJysI7VdFw5t6MSRgWDt6Tdh9uJjfp9trPLaMcZF5GFfWmp4gf8vAXxL3/AsNoeP7HIAOWulwPgSujUN9lh6JdHzXVz2Q7zZA8G6kachhCfBrDC2S05iNhOB8ogU5BoCjYOFmdX+qe9ec/bEvFfIuVfsiXDAcFZdbDpaxN4plyfSsP7THGBzmmWKtkfNDiq9VVU+FFGpnBhVBjITAF5Fac6xetwN5TnqPrAw7c4x3FQ+x4voufkIaKJprx5DKUxnRyAK65o9K/gmsmaYGEZ0aKYeyseNc5ThrEjZ5x+tUUbCysdelnxypIM30vJFiYZfuTmif2uv8CTd4TNS+OBeO3Se48MhjbBABZme4mTGoeP3fbv/29bB25bCu1LpYEqaxvwU5vm8jHPWgSPloSMp8Gyo/L+zXIlUah77dAL3HS/vf+OOT74Mmkc73L8b6B6vj6NaFCmk90zNPnMAzYAENwfNw0Kz6mklVDqaFNrp2N9sIQDGPDeW1sVgyMOWpOklTku7pjUyz64W5PCUo0gyltcmMx91ZdBKyyi7zneuvAdpcIgodvc3JtE9RLcZ/aF6kpP/XeB4y/KcnmA/0DzvJLSqE3q8ypILSkGFkOGYlSUcmrst8C/KXEehzDndMJSwsztfdf5N+8SClv/UKgeAqpRDJiXPERYNcmPpCHV/mydJbt2ojWf2Lnr+5bM4e90RZs3CxfM2oKNo++54Qdwsdw09nWNmOyBPk8+vncuCnroX3Kq/o1U/Mcfy3tMXtvs82i3CfHNZu8zbNVnIRpDTw29dCNyJPtD6GiQRP4SJWLKQ4FirOGRy8Bh+HoFgPJQ23ykDJF6PVxPmpOJmJHAlMY996mCzj/m6lIKye+GFrppCD33+Yo69/Ock+DHDFafwnHE263VfbbQiT6X8widtYON3NmEwr9rQzaF2ef5msLzpqo1f0iFk6xA1pzWA0jVeSAj4GW50k1TRitotOwtpxjmBmUst5+KcRYfgpOSVI7oTghXl/WgzQxJvBoORLWQSkWqkdF1qy2Lu9Niu265nw5bafHZ2JDSETajR2pLOKLcazmKUx/JUK2QFh7RM/fOvYShyqB1s+817LaQcVPUhcPiWciaCUC4ryiZbFOzIhKevoZiAEl48jfx2SKB0jfL3Be31jCCDq5Qda4b/Ibf3yGjWwLbRqoCiBFc9RV5ChJJXuVprjYqCETM9y+ZosIaR5T9WyFqGetxigxx30TYOZWaQmzcrZcN77dPwS23x2DNivb1g6auzvJDldWxujZ3BQy2VHG6ZgXAffdZj/Zt/Wd94jLcMK1Ut5XzoJWFwJi83VvtSU7aR064lxYzH3CrGHQ+wkHW1sfrTUHshgRsSsPrsS/yD2IwGj+GI0+nIrs/KnOwXqtmc0KaOJhmZpuwfbdyF6VaFZZQ65HXNfMh4rKpeGfJL46oKIvKwvBn7ZT7j004CvGu2A9zvTwSYR8fHoAeMIR8PF77OkppfPmfgB6+9U77sMVuRctRK35QacFi9OX66TLQ88L31nvnGjAQ36k0d9irww+szFD60lFkuo4OQH2ozIJF+bm3MOpWjg9b3Gy89yXCAqAJtMyT7p/fISxzvXsDgn2Q9AS70qbV4OC4N7UiWhrem2g8SUjIwqQ35y99Vmd26xCESsYEfPPqPhopCm4RAxUIKsbgFvbFs4KzjGbw5AA4=
*/