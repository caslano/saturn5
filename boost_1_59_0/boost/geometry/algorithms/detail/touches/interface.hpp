// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2015 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013-2021.
// Modifications copyright (c) 2013-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_TOUCHES_INTERFACE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_TOUCHES_INTERFACE_HPP


#include <deque>

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/core/reverse_dispatch.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tag_cast.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/detail.hpp>
#include <boost/geometry/strategies/relate/services.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch {

// TODO: Since CastedTags are used is Reverse needed?

template
<
    typename Geometry1,
    typename Geometry2,
    typename Tag1 = typename tag<Geometry1>::type,
    typename Tag2 = typename tag<Geometry2>::type,
    typename CastedTag1 = typename tag_cast<Tag1, pointlike_tag, linear_tag, areal_tag>::type,
    typename CastedTag2 = typename tag_cast<Tag2, pointlike_tag, linear_tag, areal_tag>::type,
    bool Reverse = reverse_dispatch<Geometry1, Geometry2>::type::value
>
struct touches
    : not_implemented<Tag1, Tag2>
{};

// If reversal is needed, perform it
template
<
    typename Geometry1, typename Geometry2,
    typename Tag1, typename Tag2,
    typename CastedTag1, typename CastedTag2
>
struct touches<Geometry1, Geometry2, Tag1, Tag2, CastedTag1, CastedTag2, true>
    : touches<Geometry2, Geometry1, Tag2, Tag1, CastedTag2, CastedTag1, false>
{
    template <typename Strategy>
    static inline bool apply(Geometry1 const& g1, Geometry2 const& g2, Strategy const& strategy)
    {
        return touches<Geometry2, Geometry1>::apply(g2, g1, strategy);
    }
};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_strategy
{

template
<
    typename Strategy,
    bool IsUmbrella = strategies::detail::is_umbrella_strategy<Strategy>::value
>
struct touches
{
    template <typename Geometry1, typename Geometry2>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        return dispatch::touches
            <
                Geometry1, Geometry2
            >::apply(geometry1, geometry2, strategy);
    }
};

template <typename Strategy>
struct touches<Strategy, false>
{
    template <typename Geometry1, typename Geometry2>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        using strategies::relate::services::strategy_converter;

        return dispatch::touches
            <
                Geometry1, Geometry2
            >::apply(geometry1, geometry2,
                     strategy_converter<Strategy>::get(strategy));
    }
};

template <>
struct touches<default_strategy, false>
{
    template <typename Geometry1, typename Geometry2>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             default_strategy)
    {
        typedef typename strategies::relate::services::default_strategy
            <
                Geometry1,
                Geometry2
            >::type strategy_type;

        return dispatch::touches
            <
                Geometry1, Geometry2
            >::apply(geometry1, geometry2, strategy_type());
    }
};

} // namespace resolve_strategy


namespace resolve_variant {

template <typename Geometry1, typename Geometry2>
struct touches
{
    template <typename Strategy>
    static bool apply(Geometry1 const& geometry1, Geometry2 const& geometry2, Strategy const& strategy)
    {
        concepts::check<Geometry1 const>();
        concepts::check<Geometry2 const>();

        return resolve_strategy::touches
                <
                    Strategy
                >::apply(geometry1, geometry2, strategy);
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T), typename Geometry2>
struct touches<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>, Geometry2>
{
    template <typename Strategy>
    struct visitor: boost::static_visitor<bool>
    {
        Geometry2 const& m_geometry2;
        Strategy const& m_strategy;

        visitor(Geometry2 const& geometry2, Strategy const& strategy)
            : m_geometry2(geometry2)
            , m_strategy(strategy)
        {}

        template <typename Geometry1>
        bool operator()(Geometry1 const& geometry1) const
        {
            return touches<Geometry1, Geometry2>::apply(geometry1, m_geometry2, m_strategy);
        }
    };

    template <typename Strategy>
    static inline bool apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<Strategy>(geometry2, strategy), geometry1);
    }
};

template <typename Geometry1, BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct touches<Geometry1, boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    template <typename Strategy>
    struct visitor: boost::static_visitor<bool>
    {
        Geometry1 const& m_geometry1;
        Strategy const& m_strategy;

        visitor(Geometry1 const& geometry1, Strategy const& strategy)
            : m_geometry1(geometry1)
            , m_strategy(strategy)
        {}

        template <typename Geometry2>
        bool operator()(Geometry2 const& geometry2) const
        {
            return touches<Geometry1, Geometry2>::apply(m_geometry1, geometry2, m_strategy);
        }
    };

    template <typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry2,
                             Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<Strategy>(geometry1, strategy), geometry2);
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T1),
          BOOST_VARIANT_ENUM_PARAMS(typename T2)>
struct touches<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T1)>,
               boost::variant<BOOST_VARIANT_ENUM_PARAMS(T2)> >
{
    template <typename Strategy>
    struct visitor: boost::static_visitor<bool>
    {
        Strategy const& m_strategy;

        visitor(Strategy const& strategy)
            : m_strategy(strategy)
        {}

        template <typename Geometry1, typename Geometry2>
        bool operator()(Geometry1 const& geometry1,
                        Geometry2 const& geometry2) const
        {
            return touches<Geometry1, Geometry2>::apply(geometry1, geometry2, m_strategy);
        }
    };

    template <typename Strategy>
    static inline bool apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T1)> const& geometry1,
                             boost::variant<BOOST_VARIANT_ENUM_PARAMS(T2)> const& geometry2,
                             Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<Strategy>(strategy), geometry1, geometry2);
    }
};

template <typename Geometry>
struct self_touches;

template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct self_touches<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    struct visitor: boost::static_visitor<bool>
    {
        template <typename Geometry>
        bool operator()(Geometry const& geometry) const
        {
            return self_touches<Geometry>::apply(geometry);
        }
    };

    static inline bool
    apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry)
    {
        return boost::apply_visitor(visitor(), geometry);
    }
};

} // namespace resolve_variant


/*!
\brief \brief_check{has at least one touching point (self-tangency)}
\note This function can be called for one geometry (self-tangency) and
    also for two geometries (touch)
\ingroup touches
\tparam Geometry \tparam_geometry
\param geometry \param_geometry
\return \return_check{is self-touching}

\qbk{distinguish,one geometry}
\qbk{[def __one_parameter__]}
\qbk{[include reference/algorithms/touches.qbk]}
\qbk{
[heading Examples]
[touches_one_geometry]
[touches_one_geometry_output]
}
*/
template <typename Geometry>
inline bool touches(Geometry const& geometry)
{
    return resolve_variant::self_touches<Geometry>::apply(geometry);
}


/*!
\brief \brief_check2{have at least one touching point (tangent - non overlapping)}
\ingroup touches
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\return \return_check2{touch each other}

\qbk{distinguish,two geometries}
\qbk{[include reference/algorithms/touches.qbk]}
\qbk{
[heading Examples]
[touches_two_geometries]
[touches_two_geometries_output]
}
 */
template <typename Geometry1, typename Geometry2>
inline bool touches(Geometry1 const& geometry1, Geometry2 const& geometry2)
{
    return resolve_variant::touches
        <
            Geometry1, Geometry2
        >::apply(geometry1, geometry2, default_strategy());
}

/*!
\brief \brief_check2{have at least one touching point (tangent - non overlapping)}
\ingroup touches
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\tparam Strategy \tparam_strategy{Touches}
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\param strategy \param_strategy{touches}
\return \return_check2{touch each other}

\qbk{distinguish,with strategy}
\qbk{[include reference/algorithms/touches.qbk]}
 */
template <typename Geometry1, typename Geometry2, typename Strategy>
inline bool touches(Geometry1 const& geometry1,
                    Geometry2 const& geometry2,
                    Strategy const& strategy)
{
    return resolve_variant::touches
        <
            Geometry1, Geometry2
        >::apply(geometry1, geometry2, strategy);
}


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_TOUCHES_INTERFACE_HPP

/* interface.hpp
34/prh/+BuBvCP4uY9msi08pMBr0MNO7fpQyJvpzcsODSS3vSRUtX78dW/7jqEFgdv8d2o4ajXSn3vZVI23vF20f0No+RG3/d3XK1kn4OLUapIdqBo8UyAJqJvwO4Zmv7zJhY7zNH/UaR+LYW/5lg7XA3XZCdnJTe4/y07/H9n64QaP0/QbpNpScSmEtF9RNE9Sdo1F3jjlWUM1sgrrzibrwO0LXvuvRFrGgEr+bTuRyJaHN7Tm/i4dP+P6BxMMebR9bfXY3OdkVBgmKKHqS2lzq6gCyD95+FWWqr6LzhhTyS3P9Upbf1tyKrh7XWCe3O6+ivlt7W8sBNFGLhBGj8srtlJh5Gzll4GYrz0cAnP0aIJbyMmX2Q9bfCvfeApFVe/AnqLj/S1Ax6C8YZ7c0q7mjLp2KflUUnSH/EnPCC8LyWfoJ6Jk/S+iZ6yzb597cIfABWIZt4/6gOmn0Nr7IdODzMrWH4jgA7Xm/S3KYQ1S3PujWPGglalDRYiuOhVS9vXiFB9bRBUNlYSNyEHT4QNAaPvtL2IPVCFdvh0tXhy6Yq3mamrs/0Wbaqk6ZpWEOanuon17sVsk3NNHRefQMxjEzD+bqPCv8TYA/i1bqPtehTgN+zU4vbufAj7247Eyd4jcrfqvid+zXNxNeRvZ87mdoghDO5F23ctWlLvR0SlaY0DsI37MXLRJ7EQHpaMj/+q66ipCpDj4JcNt7yWwnMi2sVobGI+esfghRiDXTxYXc/fMUw/6RewztyTteTcLMFWL7ig8TjkUCI76Y/uTzY904i+Ais9CD/ZIWQMrBu/4bAfIrBYB66dNxAPXwYx+obCjscJ1FW8JgPO65hKIWxj6vpziWGP4yjxfAe3jYQn5O3SnizCOgtBD6+jTCU38eDWxDaFzPfzpdRLBGmSZE265dfEv7IJmWyHOdIVVpIQsuOniW8KAqtLQeWre9EVun0EmIralZxJCyq8ulUEcLPN6oP84GgeNeCu5JxysCyb0Vi/S8HY+Mobx8nCaIBhAvQBF67kMdCRQL9txMIe3ZPe9EJjAlT4iCdmYPIuQ9hoal0/IXbTsXWETZzBhK4ajJ5BgMZeSSSiCoeK60HEulPrlOzlYCddoL0BGlQEoUuzVREOOe2aHykBux2oE1svXo7wWtn8aM4tjePHNHXalq9+zHUhq+6t6MLZRuYetzRMbJozJiNj0EFWJ2QpYcypJfVqoGHBTUcy5FJXVQsrdMoxtKzfhNOtci+r1RtBtP6z2aAbPrc0hQmdD/a3r/O70UVZelooljKfm8VVKkLAp0EwQOC11fhuMC/r4Hf8vVwEMwHh2jPmdPIRa57rjojUMpsI6MFrZe+9TpzFhaGhQvkLTEnxX4VuPhcnYqcNK7MUrFMX7ySVjQqH3BsDH0iClxyUgT0QCw8wQk4BWxQhOtBlEmnuv0g0B85emxCJdk0gb95P0IU9nFD43DY7URLup9fRTrDBICXv5SHC2dqd+DxzAH9+BpXGEnueXPvLCrTtlE3vybaFnYhDwaGIuyCPc5OB76y77hHLVkaPVFZRMGQ1c2zaX/A/R/Of6/B91RligvE6b9ywT7v4mmxCZCU9n0G/q/il4gZJVNR+h/UoM25dD/OOg6ySQxRYDfJ20t4C5lwRdDugC7VSzEXC3EX+3AYhV/puIHFQ/UO2f8YMKL7PauLXHneiRLlJAYNKGaf7gZyLsH28tuwYqaVRgAx/hXnIhl+M5CdccRise1kLW+IfAbdE4g78EuGaTskOEpAtydcv5GgiXEsLDqDnyoTnnoxh1afXgKww9DZZrz/tQlUPm6Lcl4ASif4VccvxnDmItIP+nMxh6wKq2/uQ7OvGDnVz9IYOc5CQFQk9l5vs7OLbD2eHUMlhsFU7XLy5xegwbYp3xJxLyBGewFrkrEgTkojV+OmBPilq1FFVn2O7zJKY1LHSrN2yoh/UBNVRb+fiankF5Y+q0tl4lns1ZC79pBY4VQeNDUYKs2+fcaR9elLrcLUvKPN8E3ozHGJrHnCbCVvo66Eh2AEbOCRl6VVeBRiLeEFKQGnORASwDd9BLLQNBdB0FaUJFas/QGvWbUi8eyCXiXSkAIblE+qDhUgxrICVepO8hZdoqG/U13SovfqKcpLXNHeubNVFpmCZdXi/IyXsXsrBUnhmdfTarSOouyziICIStvR7CZQCDI3qZYO/cuiZdkYQrSwbazdPpeA8zKas97q5badj6QlXui8bIKA7S2DPh4JsLGjeR9IItcADT62nZ6p+OoCRvIPkEw1Tze+mtq360B8gfAEMrOIH/jV2iJEzYEiRTniBTYjqC63AEN22NHuRRxdpKZXTYwu4lrxkZ2pnMh9y7kC5E7XSfdu5AENZmuAfYishulfnrmbPlgjoeW15X/4F+HHsbuYhFreMK32cEXB6+AnlCJcAvK67QttYv24Bq3ELg7PFYa0f2Ub1l2HfBGPeTRw5UC0ybAm9aK4D+wbBJ3h3FbSJxdA6S4W0uG+ek6FDOx+dmlIs60AIuZJla1kPlDqPLufxD3/vZFAUcyGjUS5vqarQTUshclqUqeujouSt26GESp08FK/nEdpolSXWdhhVroXihJ5Zp4c4qeoiXEfskLghb8uANCtNlVJ8yDPFekO/SlFo3jfMOaGLMZ1yd9rapLlHfGiZxicLXixk2F9o7fwYgXsYygqyMg5owG2/P8GwIdM5mbRzJRjSPcF3UKwt1jmIFUjI8RQXB3JX+Jsty8eExMaLnXikitwJoCQCVkbxjIfhOOh8fP5kTLJ9vLwtrUBo5sCFvVQL26w08z5hRFZH/10+66aL3Jrt4j6lXS1B04+dS7tsITtdasJc8xwzVLVe9B3xwdFYRCdhEoYyuWhpikFqU8PZt5zUpROkwE/gox5G+PHst0oASqaxTU37OBCvaZMl1ZbIY1FreevvwYSICviHHO1iVyN9tO//Q/YKyjas9h6QaYi1m5XfAVfEN3prKJ0YIhCicp70VekKKsw732yIRoAafkmCla0CcXm/uU1CW0mo6NmYuYAxagG+JwsnXYo+hMExGXF6OYOc/J1mGzYPLNy7ZteUvmBmkWaqWR2c0npVSvUpwJE26fUpzFirNNHbnFzlimMg9v4LHZtC827vEOU+4+ag7mtcITRDktdsIrag38y1Rr7ILgcIsKBSVpQ4LtxCbJHekE0oK/YUvYYvqkQgQLkPdi2wyR+1ixObfYym5x3ryjzgRcm+rzB1hqbrEl4b5CfQemtTHigmV5J9IKEmJ3sHnW3HlmAsIPISMFedVRJu+zl8odFK7iGO9ZeN1PKu8S1acu6ql4AYjVSI2tyzRg+MnNlQkwHeHs9tgOFDk20gYcDMopIZQKoiWneEub0RD1nXLhRgaqcznPw33JOXaa8MyUhnNKw3ml4SN0RwtUMR/P9Z1nJR/llpwL3WboMwRK1ch5NXJOrYFh+wYsJLgA/O9zRi2k3KlO36nyZTvqeKAb4T293LfxuvbCHR8knNisNySe2KAsl3xis9mQeGJzxjWAkGju7dsI4q7LDEN5u4C7220m61xHQK21qFOyMgh2x6FH/yXTN4lM4fKP/AAm3BsUqYDdhaQJp6rvBsIpKD9twOAaaKPG3b8worfcTAO8koevhO0Hm5wochoxt8k1UDGSfSafANmZjLMJ9G78UmgY596Oc8XW8r6J7mfELAxaz+BJlLVrrNDJmBABCKJujjkAUgCTkdsxhsWZDioFDpEQteZ5ulZ+PWpN9RxdmStqY3Yhfdh2lk33HK6dImKOgUChbhf8kAIAylSFCAYygQJ8UBAGSg5bKAEtoEWNgbBB3ucMG0rFwNfqoVaGU+QOZ0BdoYfMIEtnJ9uOg9EEHSRoZSjI1vxrYUCdJSCLEcZH/iONYFvTM8KOOoQbcvZviYBbhsHT+KkGz7g60BfQLSOhpRCkLYc/Cf7QerEeXlseoA1BRB+BD1uXCymMkTdRV8NkPUXnAuLr10OSxNizI5koZSSTU1t/ArNIwEjD/+GrBkoxzYueC6K9IJP/2IiL1Th8MIPCPEPiB61GQyU7yG8Nf6iK8A7H+NFWDFVmljtMAZjt3gDFS8bp/QKmW70iFRJu36QnpGJm3PPA5H2j812BhKg4v8OjJ1VMFlWcyMi/oRO8FPhFUqS41EotUAweoOjHNjRvNyBmXmpYxV2DHO3b4lCts9uaTAmLAWM45FAgizr+w3Pctu5vmDg5WmwEsmAMD6f6/AHxcg5wUzE+gJ/ya3gKQXfE3CorESUL/pywRN4AC6T2DKcqr90AeVNZjRmjehjR3l4EvaAoH3jgA/eZxiJaEjO1KuCKb2J6HfzXcKluF0OUpObtutT8m/iw1aVm78i0yyEmX+SckYPrgEemifr0omFVjc38/Jc8g5GpYi7KQ8aa9LDRj4M4mErHqfk8/IrRQJ6iD8PFQREMxbAHmQem0n7TzHMfoM3rq5rNaz4k5vNbIZFtELwu6bQKPzHIq4tXjZVXtQUB2X/tI6OhhrSHFVLa4kU9v3qENC5YTm1NCJHqtzUh9/VLT/olr1+62++XpvttzW3YycZkecA7vafleslZsZVhhDmKPRF/9Kx4NHs6cKKssDH3rfAEuWO86+TiwQFTI1IsVvBFeV0nITfkZc9h3tzjZbHJjF7zxtLEhT9sDHAOXD5Rhq2oDJvYZ1W560hBof/55YGLKohI7BlKW08SOD2BJu8kxnpMWYeqDP+JeQTXXlQSNnoDXDbHMfK1RH+AP2FOAM5nl4QAWskLX9SidI7jmReuoFb9i35V5Sq0oVIIxzu/j8Jx2BBK6waJPEMLW4lhyk1x5PGk8AAkLM0Y0aFzEsL+uNBSwQ6DxuomWUmaChPJGeBd5aRUec3GdGOhGXKJtQ/XPRR0srWVUWOc8h0GIcYZarNACYb1S0B8DiwX48xiYNcYRuG5+/GBHBPJRdq5LB7I2uU9YuiVaGh2M3D/jVDtiix9wFNZObDdLgwyBIl5Jz6D/zOjRfY+IRk9sDrFdai5A/7vCJQK99YpKEupq9DOIkd1wf0MLaw8BmJRYcR4WsT8fBTkxJ4HUVisd+K+GcnFj3fkMIeFFVnMd06+s9AMyZu0ZFWyZ7J0+D+rVJOzTQkvqZIF+Ioli6Ke0VOknLen99oYvxlomDlA2OyXeJWA3f4Sa8kjPpBCDkpGbxzHFAgX4FaKgzXWT5stsLifoy/nAGVEoUvNJHAZDtRRW3BYO2vETBVQkzQRpA7XybIKGKT/BVRI8JAYlRmRSCQr5YWx+9R188q9zqSNGkIBc52tDLpfxjJszW8TvifOFHYf6teoaYvNAvW95H0R0hyEzn941VShOYDcROfijZ+h7l9jBk2eaAOzELG23XArVYli0LvqOtsCmaO2BbLQt8HhUucEKkFYrXfO4JGf0MZARhAKzqaNgexK/tMXaarvoKl+lKNrRM//Meg6GfvscTWnk3pB+7nl+dlKIBt+nApIMiJLeb5dCdjhx6HgTg4WZNqHZ3/fRfkUY6Sjf6TIS9HTovVpmajM3YPf/x2MOCZu7Hhj13LS9PQh3q2xxCp2dauraBd4hph+td+/DuzjAoynLMikbMpP2md5YHql5wTu0eSP4s5uavKqVIV+XaqbJmwkY4QqYSNPheXG3WCVnK5DbkJhq7nJdTLIXha7HZMzC+S3cjytYrfj22FjZUJwxRFdY2l7BE1TD61LIdW4wRot8qjskuLbzIcvCTbszVZ8G10dsmq0vdChHeJvYUO85GS3KkBGxT5UVnhCJcyxLQF+ZhpqLltwzyPqexV4qz1YEQ4gm5iKmMx2BOfbnJTkaO5YMw3j4THfxrAW4VbfB48W9/Gv/7lb5TvWJXmMl0eh4S+14L5sHNxj1wnRJo3DRSxi5yuWKqYBORxF22f3IefvyRYhgiopMMm0+WSEPI5P4lfIBHFRn+YiY9UL+wowFzdtOUtZrJU6PV58ymp3wfTaCW6qqxa3JQngdhLGD6k7BS3/sGWUIlXB9rFttDOHx5uVrJ2+6trRi3dUul/19FH8I4xZtGhsGfTG3WyHeKMmy7MtXy9Ve21MzKR99NR1Vm7HbqXYXvj8A9g8vazrZiIWZJcbrEbchJIm8Pe/BzO1UQiHdtBRdahVdcr38DviToFAasYljIiaInkJJ4GWN5hPu4eIN+e6aWM8cnPYujdlNX6s+25JMSCq99KbcPuTNsZpezx2A22dVybtnKO5b6JxkO7/05RiCD1E/j8pY/1/Pvsb+v80x/1/nt2tH450Gou276rrSV1/WR3ly4np/MK6y//KGlruzaqoDAXrztTt6kDk/d0Zl1ThSRfJ5j/73ysqeqiRG/6UKg3FmrMyIsVk9xqzdN7VAT+2jR0i7BcsVwMJLoCH/3lRVZfD4sUPnTaKQ/0p2w0E6u15Nt5myJnQgnszBPY/vx1qD6ewo51eM51l/L71spoozNBGFIj4NCarWSCrstoTmF4zgXVVs4KsaqVgOn8Q6md1ZtdZ92JLxOtebI143IvNUupA8awUKW/kXT9k92cm3E+H+5vUu0E5eikwqIJELj0R+7r+3F1lj3yDNK6SQWzqLXqZRmkSvfNd7R1cvVewiaxRf2s89xZdQdr97V/VnVCXtIutQ0lzbxEyB6U4kx/KSkH3Q+QP87L44IMfqGRN9vGHV1SKEXNdb8HoLX8Z2Rt51ZQUANI0em9kmym+N3ImuoFWW1hks3nJeGT6ym5nuwmPV2DR2mXpRi7jt0TC/GxM8GVquadTKpHrHKbIHOZ3wtcBbl1ZWgbjaAuq96JMwaOUAjtrEveiz3X2yCQ0A0hFM4AlswbVns0WWMqbnJn60mrSGoWhA+OHKqsgE7k9VQhMnSPdKmhK2FJjUvkDXke2rWkpHlfvdtpJHgniObyvj5StLO5b9rEaKhZ3mVDEbigihX8NU+eI1Bwt1cRvxFS/SJ2hpZq5CVJhYauEhAMmgTaUB03GKR5Oxf0QTKjk9750WW9iKpDkvDhbzlEKMDNu5vLz2y6r2jWOqHu13OP4wCuX0aExh+LfHO3Gayde/1xcO/B6k7jO7PGlEecrCvALaGKE5NGamsa3ikxF+MKjcK3VFq8omlCRL6Eid0JFXz2aQGrNpPTGo2hJh6g+ew7Hn1pYoQQDwyZ3ZAfo2R2QK5YFmu6CDWT+MY7P6L6C6qsXjcDKVgG90KF0qR43AUqfKx+wYsEzQLZb6hCmw8v4wpFK0DZ4hnt1f+QubZhR14Hdh/gvC65Q9/UvNYG3/Wmk+9VwHbsNxMNlIbNAXJrBt73drdJdgKw/b7p0RcVtOzpuRmuPelC0652ztKrTtREVuS1pxOHhHm7lTfuhESXSWcljGB/RQH5tZEhGbKFjj5+pE3bbW2HG8AtFoMl3VULr/HzPn2k3QOK9jZfVoNYXayiljhpdD1XU0wJwh3xZTWCt76dfUl2HPJ0IRXfM1vQchsupM1ckjOcbeMahOB0n0hbFXGdd6BDy3xUnjIYRgoLsf4v3ip7VpuZRxsOY0X/CqA+fibrZdjpMRtzPqaBgMthIfhtkC4/D1/jPTxl1O3BhTBCfmD8Ra/ZDmgX7a0AJYFhemg5q5Cn40kUgcP4W3r8OPbeJ
*/