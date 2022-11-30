// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Samuel Debionne, Grenoble, France.

// This file was modified by Oracle on 2015-2021.
// Modifications copyright (c) 2015-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_INTERFACE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_INTERFACE_HPP


#include <boost/geometry/algorithms/dispatch/expand.hpp>

#include <boost/geometry/core/coordinate_system.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/visit.hpp>

#include <boost/geometry/geometries/adapted/boost_variant.hpp> // For backward compatibility
#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/detail.hpp>
#include <boost/geometry/strategies/expand/services.hpp>

#include <boost/geometry/util/type_traits_std.hpp>


namespace boost { namespace geometry
{

namespace resolve_strategy
{

template
<
    typename Strategy,
    bool IsUmbrella = strategies::detail::is_umbrella_strategy<Strategy>::value
>
struct expand
{
    template <typename Box, typename Geometry>
    static inline void apply(Box& box,
                             Geometry const& geometry,
                             Strategy const& strategy)
    {
        dispatch::expand<Box, Geometry>::apply(box, geometry, strategy);
    }
};

template <typename Strategy>
struct expand<Strategy, false>
{
    template <typename Box, typename Geometry>
    static inline void apply(Box& box,
                             Geometry const& geometry,
                             Strategy const& strategy)
    {
        using strategies::expand::services::strategy_converter;
        dispatch::expand
            <
                Box, Geometry
            >::apply(box, geometry, strategy_converter<Strategy>::get(strategy));
    }
};

template <>
struct expand<default_strategy, false>
{
    template <typename Box, typename Geometry>
    static inline void apply(Box& box,
                             Geometry const& geometry,
                             default_strategy)
    {
        typedef typename strategies::expand::services::default_strategy
            <
                Box, Geometry
            >::type strategy_type;

        dispatch::expand<Box, Geometry>::apply(box, geometry, strategy_type());
    }
};

} //namespace resolve_strategy


namespace resolve_dynamic
{
    
template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct expand
{
    template <typename Box, typename Strategy>
    static inline void apply(Box& box,
                             Geometry const& geometry,
                             Strategy const& strategy)
    {
        concepts::check<Box>();
        concepts::check<Geometry const>();
        concepts::check_concepts_and_equal_dimensions<Box, Geometry const>();
        
        resolve_strategy::expand<Strategy>::apply(box, geometry, strategy);
    }
};

template <typename Geometry>
struct expand<Geometry, dynamic_geometry_tag>
{
    template <class Box, typename Strategy>
    static inline void apply(Box& box,
                             Geometry const& geometry,
                             Strategy const& strategy)
    {
        traits::visit<Geometry>::apply([&](auto const& g)
        {
            expand<util::remove_cref_t<decltype(g)>>::apply(box, g, strategy);
        }, geometry);
    }
};
    
} // namespace resolve_dynamic
    
    
/*!
\brief Expands (with strategy)
\ingroup expand
\tparam Box type of the box
\tparam Geometry \tparam_geometry
\tparam Strategy \tparam_strategy{expand}
\param box box to be expanded using another geometry, mutable
\param geometry \param_geometry geometry which envelope (bounding box)
\param strategy \param_strategy{expand}
will be added to the box

\qbk{distinguish,with strategy}
\qbk{[include reference/algorithms/expand.qbk]}
 */
template <typename Box, typename Geometry, typename Strategy>
inline void expand(Box& box, Geometry const& geometry, Strategy const& strategy)
{
    resolve_dynamic::expand<Geometry>::apply(box, geometry, strategy);
}

/*!
\brief Expands a box using the bounding box (envelope) of another geometry
(box, point)
\ingroup expand
\tparam Box type of the box
\tparam Geometry \tparam_geometry
\param box box to be expanded using another geometry, mutable
\param geometry \param_geometry geometry which envelope (bounding box) will be
added to the box

\qbk{[include reference/algorithms/expand.qbk]}
 */
template <typename Box, typename Geometry>
inline void expand(Box& box, Geometry const& geometry)
{
    resolve_dynamic::expand<Geometry>::apply(box, geometry, default_strategy());
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_INTERFACE_HPP

/* interface.hpp
qDYaLrWHz5RpgQXwEJ1A4aBOiAfK+9aaxNO2l92Vw2odGZJU7umGw+zEDBo/wyUMD+yuzQZ8b5L/0/u7iVCg5pZyvgGYWFbo8D1Jm3FXjjx4qo9eVn3SNZz9DsuzocqnJjh0T4+DH7MT0PHiN2DPvVtHSJWYWIDPmkiWu1O470S7+e/OC/sal942+NtGy/OpJ0nZehJ3NigPFvibb/97umTf5LeiO2tAfzZ1vYHe+fYhGZJeR75G2Yrw4Kq+Upkkf3w8gtnqxjuPH4/oZUdekSH10budONdfr9OhVwqAM41ug+pPv/9evN+if6Pf17Ow3z6qU+z2XJrRLZIvfuBk0mTp2X2/N2grP2DDTqkOdhpJ679TKntT1sUnm9Lrd0+mTJaeLtwX73fOv9HvxstTJzs5ES09twbRUuXcU5KUjJhSk0qUCOkLkJrSmIVxgGFkchbfHO1GMv47ijAZHkIXepFf+MWvARxF1PwUrXxRr1a+kHzQARd4ME2YC851dD3uEOZ5xtQJmIrC22h1YD6u19FtuQnnLNuiCk4NlepAF6cH2MIZwCOFKOAuPpzpa68ZxNoxwQFyUL5T8OsU/HKYyUUlK9fvyG1+MXfb3nMmP94DMTer/izmz871O3Nb9ed4M8Tcqvopa0+AXx7p0Q5x76QTsMKy7eiAI/D36Cx3Vpfl6Ax31hH4hhagAY/edBiKHylyZ+mBPJoPdfAk3EOMIIwOAOCxbdu2sWPbtrVj27Zt27Zt7di29ebPO3xJzz00bdOU3w6TsP8AR8X3yYB5pwX0AdBJQz2ZO9Sgp2Wf5py9Nbv5uGVerXGnnKW0XOTa/pioFZs5M3AtgC2U6GWo7BIPvdoBfa745s52rTpuvBCU8iar5QeBn2hhy9gADB1r1QhNfaKK4iiIOdKQiTRl8NMyrSTfbzYEUxFw1w8vUv8ZDIGX0V/ozyHnIIy9fMoO1NHfMZYxguAk5z+lMC1Thc4y4fQJKjSKahv5abZ4npdcJQi9bw+ikpI3FVhF2n9VFEYAHcd4lHb4sLEDdifVYHkqSUnLKxxO1AzfleJP8EaAJ+WDfA0QI4TBPA9UCLBcdvdv1bQWGRFuYAwYNdo11aUb3knQGnodmtjr54KKlC3COUOgnnCEQuPW3XFiAT2zMhEfr5x3RJaYLkw44FxPboOF8ko7Hf36ID0R5HO9IBv398gOQbFer+qlKbfDxB7YDJlZYxtG5fSx0rok3xDmDhvpDTVBKVx2vPcxghqjYNybPqHklFL1m15qBGwe0RkDOjrgBuWBRlUOXe4Qq9PTEEEgdOFavV4C0PJKe9fTKN25vGwIgBQcUrbSfu6hYPp1wudTKAMRGtjTROYlWPH8sZIXKNL267TiE/7QSloH1TdP+hN3Xrkww6CeSrDzhQhY++8RAYdJPODNvNiW7MGzYAuZMf9D7gJINID2moQGC/RXZAP68NqIJ1NAe24g72QtHsPtgxFZ91rlTk+o80ElK7WbDfTe+rwP66G8kYzTyswptI7Zqwi66tISRRWIuT9/ZpHwQg6LuoIyGoDOmQeBPtvPNSSID3572rpn2GXbSk5bIstpmUeWEi6OrjlBbqvCrwWP2GyZ323456ofZVLZRtPiFYXJOccVx7tESrF6F12dxjIKCsxxx8Xz73ymT9jU/ZEzhM+RqW6I4/UyHwn51ALQ+3jxRJhKASL35BtaCmV+Mf2RM5APWNkQzSunag2C9Hhh8e1RQyL3gUl4wNT5AuiddtEsiK9yt9FhS+ZGmGrnsRu4Gb+01PmxPYkvtd9sTFraw2kczKMpgE9t/gT6MdzgAPh8Re1sFOv10Get7vQ+MbD8wum7lYj5NuYCwZo3tNTN8FzV2GapOs1GYEsyP0rtJn/25Wwc632qgAnOclkil+4uiK/xVILNp4Yv4Cj18Rm+0kbUFpVQKJJOg2AkVegJTnEz+rE9ZSIn7wbF3YG6dDbx0T2Cb3buhBNLB95bsm1ZamPvgw+mph0kfWQzrqK6RR5e9d0rcENXLHezHJZElcjW1Qmyxqnvtb7gJbTDGTh5eLGoRlSmf2HddneG/JtQpEkMzPuxWCXvz8tbzCwLLVyf7wcvwN/3kDZRlHxUEjcuYikypJyK2OWo2tVLKXohdKYAfk8WWPt3pKCZsmLEh3syEthcMiiVKwAUMQDaihvRBuneq3k0y23v+nNO5Wza0a+qm7DRYhXzTP91g0n7VeRtkr7lVNd00E8yf3O/+0T+JyQ/gmyY73n8DkCoW4y7VVSaYLMYtUU1njyeML0ziMR3w6lntyy/n/Yv6ujebjwM854Ji7Vh7E09acPC4CtaYcYg8ASosb8XM7ZdT9PEiHwA01eocEmDctST8/QjEy5LeKN5TxU/EFJiXW1AhX89WWD8hFZvZee8uxLB1PM0pzpRGSMvUVyNfB7mU80/ZWu3CCUCZZI99aUVfvr93DA5P4tD3qIKKXZw+okSiotgGFATA8rQfB5ZS4fgcni9SE3YTb8DTw1ehMq1PjpIPyEqORTTe6Edfe+1cvqHqspU4dIn3N8y6JtrqiaYyfJ0NGb13YzbIXKE2nF3AlSnBJymI08HuxSihoAGi9BCQr6FLFaBbunHfK1xCZ3XKRztpPddS2PjnPQs+X5eKP319O2vMq9FjGCZky2pbxFK06zC+iZh7YH0PB0COBmZRfA+JUkenK8F3QqUPLq0jU1Q2fQ7Gxg38Uw6O5DNkxpGcBkiLxs4F1b6cmTSAF1gjgFE+eATgf/Yu2rUNc/wQh9xfRfTw2ocbvJmNERVWC7hkcHqQl7Vs7VIO2X92U6Z3/UbwHVbGYu4bTmi7a6k6r8ydFCQ3gfHnfYbsPDaipUWv8fFkPJSOedqQ1olpLfAdXivEvK54cqrACcfirxieRH0vqY7s/G+HpM1NThnk+bKgC2kLLDgN5Du1EJ8GLRQ0vhGYhnWNEh48y7JJi7xtk7e229QyW3ZvG2nXDzRFnbcBgLC7+n/uzxLLoL0WC2sTWlWP06X3GPYIAaTQgW/G/svcTcVJWNV/Tx4EOMNf0/es4NHs0vwqfbgxqY/C6FKpfp0b1rAOD9C7RbcVwpHGdpB/pvdi9vP32PEfx0YC1jzFZTWcZuBI7kSUcNTDbkt1jRRvhq5wRz8HvJ+mfQ1RStmjhEXpUOTW79AbEsq7r14PBCT8GNGIUgv/vtN89DJmVVRRPVfGQu8Ymotohw+yGNHRhPYyxvdWqrBH1dg7h8AG2z7y6zhFASFJ7uwdzX9jv3R2H6IL2xLMIafkJr+98HQ3T2WZEkPuAuMz9QAELEbHQUqBhpmkRsdpQpQU8C39BWJGLbWBtK2AWnjhW3H58D4j6RYzyQbtIduK++bFXV1x1WEpWGKUY+ktOFLPeoVACzxUDAKkeEcq0+rYaA0Y2gIlLOoNoBnnJkkWrFzGx84av+/h5taiSPbrLnsuchlxg/gTUnuQ9WQdy6LjZBUhG4nS66DYJPZ4R+I1ROvmtC9/lrv/+z8SOFrhYLA+TcX4pFVrWi6qiiRQ1/X7ZSAhpZ7QtI87ihlKk9xHhsa4Sc0XpQDpPckp1QTSJQOMd2l3lxVOUmblk1gYpxz8oPcxWvSyhdAFzhFGXRzeON8TjB7L8Dmb9r32cNcpGL+RH8sdQGKX1/DXMyfCJwevmR/AR1xl54weOTJSKsXmuVp7e4u6jlLEl3A5JpjESoQ7d5T3P0R+Lb1DBliAli4fp5xGleixg9NNUnWQJOcFrK1vvWF+ZyNJN/Vd5m4T8WFsDjyKuPSDgC3uANH4usrWqxXOhcthYUb6KPvnaMIt9FlCswFddvdjUBRY4fx6wYJRdv9joGZIk1/InC4b+TOnOxZSKBjl+dBBR9Ryseg4v/kEze/QOxrCtWJQoHKUbdptoGhSfs6Wtv2pcjNUO6dVs8KniUBiKvQt7dbI9s5OLtF2zz0hyps3EjO74rR6zGEciDuMXUn6cFDnMUsRnsRJvYI6whJQLLxAgyp8lmD0Mg+4g71ubjPYwNtl4lHH0sXDT/tZZaapawYxOv1TGSm/EklT8FqFK4mzaEg06tBU2yL1Dz0VsjUigQvmyS01hhCqB0i/1KYOm5F6ltNAWnQABszdHrFYHCaHaHAup/oJxAscbCsWoPt7cI55KaU12hGcwtUiFrQoAAELPvTy09gfCvFUKrj3euha5Dqd7j+Yo56iplgPAPApdejNyxAbccVds4bjxctqyiSLN1Brp//4+RkUQDNSIJULgQwKQav4DJapcsgNOfwVYvmNyUy8piLB7JIP+Of//baRX7QiPtRFP85r9uagWJG18JtsguQfvQ582Jw+mbYY6e9ataj9pRNr7L4TDqVlq1UsaUof1u3jOm1WtvZTLcb86/LHvEdVVZV3BBIQRs9+7q+YlKiRTOmAfUvobfqyJaZyRItJPWBuKhZzVBxPaZUozkBjUwzMRzN/U7zX7x32iEhw+FS0yNEmERfhKE+jWuaHQFP3GNchdK1NUcK6NfnJf2g4Z33FpWfCFry+n7VSTAPduKRxNHjjxYVXOSWePDaZVTUoQKB3MS5gx7cwZrbXp+K/In5dedEu0xeTX+WhI0BhMQUzRT0bNs9MTnffIO/KA1+TltkDh8o7Y4Uam0dBKHVI3dLLQVh8r5rPY8OURk/aeH8j7P+SFwYgL5ASqo29Axp4GxFu6zMT4zgVv1eRpSQKaNFVQ0X3AR5FsXWWn8uXcTlKod6hVrdjCOZVlOy5Cp6D3tNjO9enBqFtkXY3ENqIeUCtIcwrrvtUnnGXHVl6U8mIIWJt5+GBP8F0Y3+RAPlEKmHncQBGowJ1tk395mse5kdKbzt2yzzDax7VCzxsAnKJU9AMAJBn4cbVDihvCLgnDNKtHTkENSOSPYsggZYCYMyHG0RVYV9r0QRHqlpRirvcV6ROZMjSDt21ogLjVqhM9GU7owlJZEpPipvMj7QNyuP/DhFxHTIpLkZz4OwOw8sumV6qJoYl2PXPYAZxASp8n9nK1ENfgIFi/oA5gNN3OAEhTuUah5he3UOFnZhIODfGLD4Ekl0c2bgr1xlVFU/MACwoCA8HBPnYRRP9cxsBkWi9EStKXQAqgLfxCGVyYiD77Pom/YSn2kOihWTBw8YUUtIxyav3lS+oWUl2A1SvqF9ZK91kFobtNBbJ1e7ifKBaUi9OuJjItgVoFm9eBj/yLKEHF9nKPS/e8db73yf07SkZ2S+8oARpsi8ub4+q3kzmblA+5r+uVefk6Ni+icWrQpvSqXSuET25veC+SRexgwlysvEd/4a94OEf3/67dGhfTOOdxNe4LOZIINg4oQHB5yqrRb5vOBtGbz8QdTfHTUD1/NS4XNeeKccql5tbh7Mvg8RK4++2wzYGTvluhfF1os6/ohb8Fcls3WAKvbpcnGzQ5MGr+k4hNXxqYVlEa0HR+2S/jxybeaSMyk3FZwWjqX9wqWLbptbH8euWzQm0yiath+2HevZiKeJl80i6UxyiCw4VB8eP5+dknQaNyJGcolBct73wJeZnBYfoZVpds9haI1gvww1TURWHPn5yK7AAKooy+T0Yl+L6BaQ9EmLLi9vhXuUEN3jZO0QZmtdKNtI6UTdW1hngL35bXZX6Ia6aAdPZcTlYXV7UKrXfHRVkrr09VRmuXTKd8aRA594S55eRW7mTjXLH/VqDjSzct2xqYBbX2QnGFWHyLQ7SdWp4UZHfX4Zbt/Bw0/Dcg9YPyGEwEAtdbeyxWujoYbYWlgDQGW6aaUzYVFrTjJWWHiTJbstUQlAlKAa5HX2JxzGMqLTV4MHoMK7nFeA0pTMyq/7pb80IZ/UqEUUoO+Ig+ijIkVYNtwUr3v00KqVvxkR3avVez0TpNj1dbuZXmggY5Omcw1vXv5h1KJYYXMhQTHuEojHyKL1eL3U2vVfPm2uOIlEDRqtod9TpQVoB14EmmXPg4oFhnCfa75lyI22c9/axHQAcV8fUCIvriGrNy0rsv746GvZuKXrQgN8Dg2eGu4VFp2qOqx6Z9WnRKKQYqBqi8w/Hzknov4jriFoukBO54tDUydv10MFfO/ab0qlIahqKfWU8n2TZcCqBCPl9OPCm+VW5uEtPdQFbLywGnwxD6men1rg4lOPheMrv1o19r2/jKtM/ETFRMjNaCqTn9+bd32Ptuy8IrbHrF3ImZZrIC0UTlIBtkfais9KeUKUHaggIoMZymg6xyOb6lk/bEpUgamvg4vRLRmg52DsHQT2i9h6BZ9odxPXoAbQcf1v5vRCmcp/NnfJ1FjWcf1+mHd/pF/5pSansKGYIi9dmgG9dZodjIIkW1fa53foaHPgH7HmxY95wI8JhYzkDjKTehYEFrBSv7U+odLdXnuZSOPbvwxSI1KE1nnhvuXkKXOpEG0aBazIEdprHDrlL1oN6d6pPsGt9iJLdefmcgu1/4ERACdlsiKnqhesGyTK4+ptXyAvRCf8TTaHm5B9pCpzSK3tI4TcJIG3mU3aAFuDw4+Na11vPuhkZYx4KhMLVeDAwnoEhz4VEMIU7zhQ9wx8dgJIxoJKp4Mas5TUde3DM6asNu/KDJ8fhv7HDAx7B+pIEAsDyzFHCvIFb5VP1pCLVee1d2XPgPvf1tSD99xwBVrlRfyQGVK73mWpIUYjmgwmbKtcO/IhTn8PRzLx1h6zhgUyt0+gO1HZxcJrgcMpiVD4/ZHGOHnG4p5gUCskO4IpvwQyAi+plnV9gmliz0YfKOuGcC0pFUPAPSgVUjaIMkgI1+mOGtqFUUzvvUxQNeGVCAAgBrKUGVRGOCrfIaStIbwvHvWWFQ8nDRAiGIwAIhWv6ca9I/5pEdEPPlXiHStVIm+C2dxfKWjCEjcxrmhcSF1fm0GTQ3aImFF+gLsO5i9B1j3Cgrbx3L+/x2WVN77HgoJi8DWnAZGXN9GfiVodrDa8aMZwlpgjMlVrs3eYNrwmCQMr9qVzULQes9B7Vx381TNJu1mc+qXSZbCscAR6o50KPxrlvUmver5fpOeBd6Fg6n73H143q+lpLKkMwgmqKPUQf9dv6K5H/6UnILBrnN2lzutZECIzJFxIgfiWV6dRqBrEid+FU4XaBjth7vlLIlvekbwBSmtLkoMNF1C5tsz4nRwC1dqi8XRm/g2KX1F+ZghAZjpAtj4VnyBb85iqkOzVpxi0jSuaIZKkuvYDDPd32U3IDPdly6n5Y8P7zRU8b6XPfN55xD3+YQuaE9RSzpQNzlU1ExISVy6wyt0f0qGv3P3p7ZKXShkq4CRq/0K2N+Z8ugLXh2La3aJ/cweBrUfuEA4/0h+EM+Z0M/okrxr2lDfw7DH1V6oaynm+SbPUeEc5igxS68F+dNdVStAiWRypzGdVm9ANsLhDsaqFkgel1HQgHEy7IsDDbsQhSOQi5RSmFbZbvWfIv8AZuDtWJANZhqJzsvzG3RxIM1ZVQpJLukBdqNmA8XW1nwRKf3++S2YtgQeFgpINr3/kDJEZPHB8cwDPsV7J3MqPNz2gdiEYeA5qSQo0uqnvmQun9d7vX6cUZGYCiRPmpKPITUUe7TCi3NU3saiV8RxcHuDtLZh9EqNfS6kQR1pFsEN4/REVbdmpgH+/5P1T2pHaZFbssUovXGYykZIdDsq8
*/