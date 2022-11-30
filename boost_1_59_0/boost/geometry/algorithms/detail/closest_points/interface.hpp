// Boost.Geometry

// Copyright (c) 2021, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_CLOSEST_POINTS_INTERFACE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_CLOSEST_POINTS_INTERFACE_HPP

#include <boost/concept_check.hpp>

#include <boost/geometry/algorithms/detail/throw_on_empty_input.hpp>
#include <boost/geometry/algorithms/detail/closest_points/utilities.hpp>

#include <boost/geometry/algorithms/dispatch/closest_points.hpp>

#include <boost/geometry/algorithms/detail/distance/interface.hpp>

#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/geometries/adapted/boost_variant.hpp> // For backward compatibility
#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/detail.hpp>
#include <boost/geometry/strategies/closest_points/services.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// If reversal is needed, perform it

template
<
    typename Geometry1, 
    typename Geometry2, 
    typename Tag1, 
    typename Tag2
>
struct closest_points
<
    Geometry1, Geometry2,
    Tag1, Tag2, true
>
    : closest_points<Geometry2, Geometry1, Tag2, Tag1, false>
{
    template <typename Segment, typename Strategy>
    static inline void apply(Geometry1 const& g1, Geometry2 const& g2,
                             Segment& shortest_seg, Strategy const& strategy)
    {
        closest_points
            <
                Geometry2, Geometry1, Tag2, Tag1, false
            >::apply(g2, g1, shortest_seg, strategy);
        
        detail::closest_points::swap_segment_points::apply(shortest_seg);        
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_strategy
{

template<typename Strategy>
struct closest_points
{
    template <typename Geometry1, typename Geometry2, typename Segment>
    static inline void apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Segment& shortest_seg,
                             Strategy const& strategy)
    {
        dispatch::closest_points
            <
                Geometry1, Geometry2
            >::apply(geometry1, geometry2, shortest_seg, strategy);
    }
};

template <>
struct closest_points<default_strategy>
{
    template <typename Geometry1, typename Geometry2, typename Segment>
    static inline void
    apply(Geometry1 const& geometry1,
          Geometry2 const& geometry2,
          Segment& shortest_seg,
          default_strategy)
    {
        using strategy_type = typename strategies::closest_points::services::default_strategy
            <
                Geometry1, Geometry2
            >::type;

        dispatch::closest_points
            <
                Geometry1, Geometry2
            >::apply(geometry1, geometry2, shortest_seg, strategy_type());
    }
};

} // namespace resolve_strategy


namespace resolve_variant
{


template <typename Geometry1, typename Geometry2>
struct closest_points
{
    template <typename Segment, typename Strategy>
    static inline void apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Segment& shortest_seg,
                             Strategy const& strategy)
    {
        resolve_strategy::closest_points
            <
                Strategy
            >::apply(geometry1, geometry2, shortest_seg, strategy);
    }
};

//TODO: Add support for DG/GC

} // namespace resolve_variant


/*!
\brief Calculate the closest points between two geometries \brief_strategy
\ingroup closest_points
\details
\details The free function closest_points calculates the distance between two geometries \brief_strategy. \details_strategy_reasons
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\tparam Segment Any type fulfilling a Segment Concept
\tparam Strategy \tparam_strategy{Closest Points}
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\param shortest_seg Output segment containing the closest points
\param strategy \param_strategy{closest_points}
\note The strategy can be a point-point strategy. In case of distance point-line/point-polygon
    it may also be a point-segment strategy.

\qbk{distinguish,with strategy}

\qbk{

[heading Example]
[closest_points_strategy]
[closest_points_strategy_output]

[heading See also]
\* [link geometry.reference.algorithms.distance distance]
}
*/

template <typename Geometry1, typename Geometry2, typename Segment, typename Strategy>
inline void closest_points(Geometry1 const& geometry1,
                           Geometry2 const& geometry2,
                           Segment& shortest_seg,
                           Strategy const& strategy)
{
    concepts::check<Geometry1 const>();
    concepts::check<Geometry2 const>();

    detail::throw_on_empty_input(geometry1);
    detail::throw_on_empty_input(geometry2);

    resolve_variant::closest_points
        <
            Geometry1,
            Geometry2
        >::apply(geometry1, geometry2, shortest_seg, strategy);
}


/*!
\brief Compute the closest points between two geometries.
\ingroup closest_points
\details The free function closest_points calculates the closest points between two geometries. \details_default_strategy
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\tparam Segment Any type fulfilling a Segment Concept
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\param shortest_seg Output segment containing the closest points

\qbk{

[heading Example]
[closest_points]
[closest_points_output]

[heading See also]
\* [link geometry.reference.algorithms.distance distance]
}
*/

template <typename Geometry1, typename Geometry2, typename Segment>
inline void closest_points(Geometry1 const& geometry1,
                           Geometry2 const& geometry2,
                           Segment& shortest_seg)
{
    closest_points(geometry1, geometry2, shortest_seg, default_strategy());
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_CLOSEST_POINTS_INTERFACE_HPP

/* interface.hpp
onqJjmJB9h1J0vxg3rdW38hF9FUfs/vsEt1mu21nHgVFtjHCqlFK26wHN1T54GGKshrjr+1k1jB1BoySel1MWMOQSGu653jyS9BTbIKpfocWv5pLzr+VsDpHLg0mDBhjUtcxsW4ox0Tf4Qw4Js4wXBhG3Y3BpOWCI/sbtlHBwjAugNdlTowQirNLq2JHXGMcLZm7/kAkswiMX37+DaT42JsceMYeisGXMWm6O5PMgJbTHBY0twtrwkHj8iOuHWBjfBB/x74SCTYAli9mZyZ8zzRLXVDMCPCWO2S64LlvhBGgt2/UlQ+mMQfwBJ2EOdYlJgCa0vpG0QeD15EwgaQPXRcOvkRJZiBZB50HjDnWSa8Iz5dJa9W6es11auEOZphoyvuTiwQ9CwwquwAZJXwrNgH4L1nqijPZhk3oL/+ZGlt813NyOZTRNPGoFgdCWVZNlKAQb/h2pkWlCpvZhf2EW4d5zoqX/LfKUOJAOOs/FTHSOh8KBk7Y3tL559utfXPiGS4s3Y5dV0MK62OImPlOFQEOcrYY4+IweuDHf/KZDVNl3xXUXorMtKdz+tECP//L7xRScc84Q1kB4zL2cg1lhgRC8Ho67B9FUmI+5yM1TRc90d3eCFHsoU1lvfs/Pa3df9JVvyzuyZfZBEk6kNUf93TcO48dQHb8hROtj1jBhyZrGkzHkkFoKpmb3GsLtXeBaKikpmRIoG3GzwrAiruzckwGtxENcBey6twnc7Xgnm/Hup1RwzU2ON4vCbPOpI9MQsFb4JikoG5lvf/9t2eipbWH3XyoxId3yqg6qoIEhyMn+WoxX+6CJFZUkR9q47CN2X8o/zyK5WpDQvOIk10k7pmmF2PenNNr9kg/8Ng31c6nL4rCcXA/PXrWpfsirp9P+aH+67eP602UySKfDH4kIJ561eNtrLYfoqBIDcpbuq8BQvzD9gsU4XneIPlYcTp8nTWr+799ZJbOLXZavWPgnKBvDs7Dr0pbcdf3mpswHB6Xy8ms8fzmx+hkmmHagAGRIAyuHP3snlB0yMypBQaNd8hdzbWRVV4mtQBnLRUnXCd0epKeVC7+3NE1ZUEgoOB+L8sPZ7ETAG15vbQ01NTx4845gm7VfUGdKCCwJ5SK/W/r/PCzwyAM9W0PpItIdWMU7bZSK9USXKdhpgC7o5y6Fe7lIGpqBkf+cNtPquy9TDN6KBWixBhMYhY2884hNXFG8upIroXk7kvYTuNTDNMLqCdBW2DvurtByIq80FtUGOwLVU7Hdq8Y0elpi/XUvPiqAm9AfCkjni5LE9SA/pEPnYbxqZ3ka2SL64BfYPZN91DzjfIdmiivz75R8J3cMVyRxt266GhcYBat2EsfDWuwd68AkSIx/+1Hdn8DdRA9KhMjt0p8mdtrELvADGLLMScmhrxgKYayCrbwsRzf1u7oPeiCsclgnkh5OsKzG0iUDVr9V7xgF7GOGP5dCFsgq7e93RrmW1NrLyMwaYZKzjffVLelNNifeQI3hPKwB3sor80NDvz2zVlH0WkyMpN7QtRjoFia33FPw5uiq2/gU2EQTUCXt86923HssYRbKL47+kU+gLTLx+T4OFRXCpPetLxRzVx+ruhxCDtrbFx5JQN+04i5/KXuyYDBo/rbDM1SFE7AbF9Vw97M/54N5PWuy0/O3eUmZ4rLvS0OaLkQ0/N83Tc2OOH3nMgijsyBI3R9XffjG0kKK8h1E+YRDHF944tyUjYGe4Bf/r6y1rul6vLpblGzauu5LN29Fd5RdHJ9QPdS8G+9U3Wq0dMuibJW6EiHWMggMMn63PXQNe2MLwDI8cn8Jfa01wUq+hItLW/AnsckAaGSUyZEYC8aa5IApq5TjpsuflKn6eY1FESlhA2Rx1GI3E/FSGahYyIy3VOgsQ31TiCDZe6+Fc5Tdg87qlMN5eC0JpUNiufap/obh9FVzI+bfJn9XV8GUDqpR6QFO9YSL1M60fXyc41LNBCuap6EfeKtqU4USP2EofszOaJvMEsm5+0DR7zzdM3p6Ea6ELmf/5Le+4obnPwTmgTIVT91qBEKUw5wYy3bx0x3++4Bn1WtyasdA5L/MfBRtJyD2MvEyaxgTycAOMPJ/27zn8z8Pm4DWL++5y7U6i2RLGZhasxL49hJ3lcTAxDhBz8pPAXujtSywfbcSm/1PuyruVYP0cXcghh/F0RlslcLeOjO5tA0vSt9QlirYdbNfzwJfFJdTdeUU/qEyN0rBgggKJht2vrv+bhR74uvzrqPfrLx8pXWrIGcuSKbWtATGN+OeVQTX6T7kxmG28dHGB0fNBFMtP9EpzP05PZ7HdGAThMm6kPtVmMBxpM6calvpStuCNObkdskMpEZfa7oJBgJ9m80VSeK6JYcO3wv0SLz57jt+Fkf2br2sXU4h6RzcBxJGKFGJbHVlyavXlWdSh5H+zfOAl8VUII+aDqY0n4OstN1AiToA+3Nfc6s6FHk7ao/lf2c2dCNlsf6XZ3Ouu2eFmFbQHye8OjQD2GNb7W/UGbihcrI8GEj+IKxX4ufNdhrv76XrCrn+jk+k2XzMR+wepXojf9Bw580y7JLUIRzsCM/4/Htfml1QW1gUJjOgN+O0TKGYdG/Ug5YQLs167vabgdjb52BW/dWtn6+HMskgQBSfwSVQ0v23+K2NJtPyDk+UHc39797+MlN7H7S4vmVtVsJOvlDYZv24gBMYhkzZVsZ0rwLSJwxNbgFMGKX2C7fXA+F30WVzm3emtZD95356wDc5PWaCdlQ0wCMr2y1uqH9lyuxOopU9GMP7VkQ8R3bDOut5vxSG/YH8ZDf26gQ/g8xP+C+60thqlkDnfl7GIGWlUjFdc5QTNbL03TAgv9NepITjB17g610Pvse8r+61ZsJtoR9K20mWJ1q+oFfze5k38eIEunG4N2gTY5LSM068lcK74jSjWX8m3FXVGeScblf3n8p6nlzN0Dm2PimktxitolmOAgt7KQTCQbE/hYnl/OLXQDTNPnItkKJrDYoP2MiLomnZQWQdMLESON1ZaQ16Q2fwvFlFMoMr9Y3dqkg+MzC/ws0HczLz2gevM5+yh4AlJ14CcITXneCt/Mgqpx/9cgEHMpOhCzhTEKWQhUN6C64dMy6MznuS3c1qmXveU/lz3b774hmGB6486kirXGES08ODUOO0XS8ywO4XRk0pwDcPB3fWVk2RNsrszDY0Y4dWQDE0o/1PjLZd4YiQjIw87csGRONj0pkTc3mpGlkZlv8pCLR5Op8aC3dk5mCZ9V3FZWTUw8nfP+gesaqDAo6p8Mgrtn7XatW3OY0eixd2Z06E9IbD1+ducmoGE7Nna7tLxhXTvI51fCGgNwmTsdi5BPOyu+TBdC/AqqCidIUrWBDZyL32fg3a3ZLl5r/neCAF5AarM263fskekd+bf83tLJf6oyFAZOaP9O6lkl8W09iZZ2zAMAFcSSUdwZVRrLOOt2h004kCBSvpNa6EGbzcWmsGhuEr9RmnYnDaP4lCzYY3Ekobu2o43T1BTth8DZe9A92W3bH1ZJA66FlcMhHuoeoqW0fZNQG179kcg9GtopDQbIwl1TWlY+Zj1BvvrNy/PwjFlRoesMd7k3cSFyP7MjpZrOh2A5tQk/bmlPPpHYk7/WM6N46VLp3gNwYya3SUAfdrHaPotHI5jvaxwsia3rHhSNCnKXdGmFVEa0BPYfq5G3RdcWHXPiKDTvqBScL+P/1HB69cV0zja7ovSTmIF4n6sjhUvb+PKEdC7Jdob1QT17RgT75hXHeExMnYYpcIERjQ3r/E7810bLfwE+the2vFuPRuMsYdMRai50xMXJRTgkJkfuw/Pvl8h2uZwed+Ub1d1bnXsFoHR1hboQ+myLDx1auUsvk2Xzjtsd2S9svMSSryGdHwmhLNR4m6JGuFe84gKXiFrTth9zkj5EnT5pFE9GagzL6FX4MO2G0GgycmibbWSrguRuJio53IgRMKjD5xfl44rBoltJzxaVqUifwtk8hYMNV7s02YKOPfAiGaIW9NRYTdmzhZQ6lXfmSksm4AxoET2PG3mKopBIfjmblRFnT7cHEXmLc6w3PTZBJ9GbxOFYxKCccPaXKfTYDMR6EGOKhPEawRaSvkPR2Ft99k40P09tNVUKe9kkDxq2DdpFrWvHbPn51C/g6qrgkHuNzoFDZc/tiFDNwdc/owdSHeRF6SddSwYGqy076+tfor92935lNDiuRsHoQ10af+kL+8sDyqpKJFObwkQwm7uTdKwavHWwqJlYqTtQV+fDEAhQT053H+vO+UDxXsM9dXqh1AqU2zyv3CoKNSp/A+afq411n91+m6EDvMBDbyq36MFk1tHakZGYZvLBX1yhX/e4LDC2mBWKFvdsxp5UqFEfeeL/qeFeaSVSbUXYOLfmlRRxFjFbvzOFVnkX+OgQ1/ZV4XiqM+hVozf4xk+7MM35m+oF7WtO33gz1zt0KLkTRSrvrhaQI2rziuqeX49gSu/bXYCwruohAembKG3Xl4ryOtxrOLF2cTvbhkuLVgcr8Gmb6sBaNyv3Bjln/V7nGj5paNPip1gdJZDB4Ul82oBZ6AAOpsS38fMDPpZ0YxHXb6r5oAGOpAY6Qb414dJvkGwdI6xR06YXvXQSRLHgOKsG8pnafGCWpIuPde5nvvB05SX44HknHnc/p0eHtajQVlzb5IODJjBOOpCyYFj+f9HCwlxEd91uMUm66nZbax4exlRnXfZP7U6ApfhL6dfBCyFgBnKw0A09Yyyxw43t5BnVTQ2lz2QWmoglNHXBQsbxspazV6j0csDHx3QgnQHn2M5lZY6n4xnvsuq+J5yCOff+TmO8LUgHXhTmnvmSLl1mBCyVbS8t3MocTkfuhCdjFA8ly3MLRGOmOjeJq4XRs1VKwP+UZtE3spRlEtW/MzHsTh5vajZUr35iJwwglD+/p6vwNgmv5HA/93Aqi6FZL4T290zqX6NYYJCtn9zlG7ZYbctHLNSH5t/4HYCaHoBbu+RkT/r+hWbiBen52780NzJsE4FgFrJ7o8RVcnxDPxEe2vgpy2qCYiScN4i/NxK89lzoFkJ3cmrbmccUELzyrZgpYL8yGgsoj9h8RopfRlFZLi+uFhzJuQQqWvjkAVVcaFwNFMfDvjxFjxAbS0rr2DuYV34ul1HssfeUUJaHXOB44Njv7Zj23K/3+XYoVUMA/3cOVizfJs6GSFOuit/WkFuoms1cPIlkJLkpe+WlFso7tqDN0ReRl93C0d0ObG+p3a2u2WxQ3YjRkH3R1xPpZTVGm+VF0sTu547bCp2pIllVnbiwMfdUANnsT+DDyfg+rXEDHaFiyv8u2rDOo1xxNUK0+W/Mb1f1+V9EDlw056IYx9nAlsWGxuYubzON8KVS/K/IXiucOoW4qeNtZvmUso6KHuvVMFipw50/2ksZwFSTmQx6vQobd4+P3oaZ5Y2JnzpCt2/qHGNoB91HrlbB3sk6OJ+PNUeDypiOw0EF6BjAt4MszTl2/WekYTHLeSRf1QW1YqfP4KQdUxTi/Ng1lvlFqyq3SG8/dDCcwXjpuaDCnHX23V2pK6b1zqXvnspsDVcHrWu/6DaaSy5Qc89WAeYvqHQP+1bCVKifPWhrHhCTtdt5uFgDwur48VKHPVnL0CYPwUsv/EK23qw2rNXHxHz34+0P0DxyXMDw2zGn56kS/Jlhw1wxM9iBWBhwSWWBFFyTg23fgHlJ+xKmgsn3WUyvzs6cEmlxkjCxbei4RAb/XdKPOSKw+OZA5W30QkNYj2uwQQXcz5UayLCsTly/OCPkt026d7fojrHrY63RLN9f0wXrQzJkKOVgFGy7k9XKuzdxz0e0Gtcgeb+Cqd+du6Pc7TC+Qu3M3bLhm2LaV2nr1MSRgOGmlk+ZvJsGk03ki2TmvrG/y/wPJgDZ/bM8Evpee/8EY9de0fy5shwv0/SfwVMHsuyue9fvPAvUtwAuTXgS4gBAvaOtIhfSsFej7N7JLC36EyY88eG3yo+8plIunzHd1eUGvTXoN8Gaeov4/8MJTZrloCHq6rfue47vo/5NeGriJsPGUVs6+a79P5afM+1QnO6VvHTeQHzHwhp+m/AdeRJh6WnsPK/gReJqef2QXE/zQ43TbJPDS5McGcC/Ka0HTywh+1MmP1tOmXVnwI01+jKKOjP+a9r8DjiDMdq6remRr3/W6pXxc1GyUrnXPPKqPPvAypJNT96BzzSfEnSGdEHhtSkdfEW1mUVuvJvjUJq0UeNNFWv8DPF/sji1TgpZu564BBy9epPf/wBtF+/NE8a3v0km3Dl6DfGwDe57R9nAWfGyQ1tASxr/P0PlHwAmEuWfonKIle7lynjHLctRiq+Kxnr30DD33wcuTP2XghkVzUtDMk+Y8eIP/R/vfAE8ieJ812/55QVO3d8f24IVIcwk4btGMCpoh0lwDL0eaJeC6RXNN0MyRZhG8gWdp/cezu/WKQt7qtjvPsjV6Xuz7XtVZfJbWfwMnntXWJX5PWP9N+iPg5Z+l/b+AtzrX1O+2NiFPOtPg7SvR+dfAYyXzGat41vOvS7SGDrxAycybEHDEoqm4trwJkOYieBnyMQdcIr1FwccM6SXA632O5r+Bh57T+iJCPuh27hgJvNnnTN8CwCmEkKaXFfRi5McK2ZWENM2SHy3wyuRHHbj1nFl+W4JemfQG/7fqjPzG1PMCT//GLK+KZ9PTbd2+B3gO6UWVFulNCHoO6fnBy5NeGbiOUHpeW9ct6OVJzwFv4Hmq/8De5009R9DTbd3yA16Q9BzgKOklBL0g6WXByz5P89+kpTjW+W/SqoDXWzaft/3Aowjl8u565fJtdaFMZRC8OdJdAI4Iui1Bd450930f9b9M+58Lmopr3f+cNEfB8/yWzj8BHv6tdp7o94XzT35L/SrwfKQ1DxzStEKClo+0kuCtktYa8IamlRS0VklrA7wGabWBPb/Tvq0WtBqkpdqvGLURTdjO/I7WvwAHNf2moK/bufkWqToJ0koBZzQtxbF+/0BaM+DVSKup8O+1s14FrRppLYA39nta/ws8o2ktCFq6nTtOBW+RtGLACU0rLWgtklYNvDxplYFrmlZN0MqT1vDfVJ3op+i75KvR/leo/QeeRlj4lPbd+9VC+1+hd7vgOaQXBU6Q3oCg55DeGHh50isD10lvTNDLk14QvIEXzDZmBNhBmHjB7E/PCJr+F0x/ghZbFY+tfdLjVn+b4KXInyzw5CmM+/Cv51R3HJsU/KmTP60XdttGrhb2cTxF+z+eMu02hXSkKB3eH6D/f8p8JiwB97+IvFd6p8y5l4EfCO33KWr/T9ntm8K9aJ6i9f8v7rZVvtqeR7r/7pgCvKkXTX98wEmE4ItmWx38gfAtzov0/Y/Fdk24F3rcbprBK5FeDbj5oln2moIvJdIb+mHVGd6i/Aee3NLGqT8Uys0W9d3B81RpPgPXIqQfB17d6s4d+AT9COmvglckrS3gIcTZ6FxXPljn8qs0/6/ZrArxFyn+PHizVVr/ArxQ7aYlL2jN0n3piVadlSrN/wE3ETaq2vcygl6Z/KiTndK3zv+RH6PgDf+B5v+ApxCCL2vvuAU93da9/+CFSS8CXECI/0FbyxkV5n//QPO/ZLco+BEm
*/