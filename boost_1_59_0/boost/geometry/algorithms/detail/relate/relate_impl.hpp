// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2013-2020.
// Modifications copyright (c) 2013-2020 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_RELATE_IMPL_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_RELATE_IMPL_HPP

#include <type_traits>

#include <boost/geometry/algorithms/detail/relate/interface.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>
#include <boost/geometry/core/tag.hpp>

namespace boost { namespace geometry {


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace relate {

struct implemented_tag {};

template
<
    typename Geometry1,
    typename Geometry2
>
struct relate_impl_base
    : std::conditional_t
        <
            std::is_base_of
                <
                    nyi::not_implemented_tag,
                    dispatch::relate<Geometry1, Geometry2>
                >::value,
            not_implemented
                <
                    typename geometry::tag<Geometry1>::type,
                    typename geometry::tag<Geometry2>::type
                >,
            implemented_tag
        >
{};

template
<
    typename Geometry1,
    typename Geometry2,
    typename StaticMask
>
struct relate_impl_dispatch
    : relate_impl_base<Geometry1, Geometry2>
{
    template <typename Strategy>
    static inline bool apply(Geometry1 const& g1, Geometry2 const& g2, Strategy const& strategy)
    {
        typename detail::relate::result_handler_type
            <
                Geometry1,
                Geometry2,
                StaticMask
            >::type handler;

        dispatch::relate<Geometry1, Geometry2>::apply(g1, g2, handler, strategy);

        return handler.result();
    }
};

template <typename Geometry1, typename Geometry2>
struct relate_impl_dispatch<Geometry1, Geometry2, detail::relate::false_mask>
    : relate_impl_base<Geometry1, Geometry2>
{
    template <typename Strategy>
    static inline bool apply(Geometry1 const& , Geometry2 const& , Strategy const& )
    {
        return false;
    }
};

template
<
    template <typename, typename> class StaticMaskTrait,
    typename Geometry1,
    typename Geometry2
>
struct relate_impl
    : relate_impl_dispatch
        <
            Geometry1,
            Geometry2,
            typename StaticMaskTrait<Geometry1, Geometry2>::type
        >
{};

}} // namespace detail::relate
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_RELATE_IMPL_HPP

/* relate_impl.hpp
2PkhzQAszTFgDmwdeaQPcqAkGEpBHAjw4c47vDUDqJGnUrQ1IvQ7Dh/t62EvutgvzuDmsd2MYI5w5MBhV+vdVoRilIoREsMUIl2wmzs+ZW0VEDrqqm4oI0O6VMsMkl2aG61zHVrXqU8v7l7z5Zl39FVrtpMx25CtJkgP3VXGu9BBXdjSjJ4uIEIHEr3HbcUGdFdCvDiibG+hLpuzE7+TNIywEMsnS4M1Om5eQDfuYgv/rhO310BcFfuAPO2wP9nKnVzq4GBrfKdGaA6iJ/Zf7iI341hmYDnuCVk4GbarFaJyixURapUfQYIKMVYkkslBhaheg7F9dlSrZfYJ5b0h8iy2sleOf6vHMqcuxwWJ+SOpBjCEYE2P2P+cPW5glbNXNx3Xea0L+230vP+9kOUxE+YZ6DrapN+XkYfwud46ceUPtOFHznxW17RDytZGBvRa6M1ROMsqLJoJhBBYMy5Wyqy6OgUoPfxDLoLP9YvqFPhZWDUAchZhZP2iNAJRNBDBGUudZcF8adl5t/SzqzMscMPeZaJ0KZK7Ygu0Rc3UplvQby4gks2bRR0Xr1bHx38MxXh81pVzk68wVBsZQjw2qBBzT7fw9dhOga6vg+SFtr/47IGo3x6AxZKfl8LntGcWAcOrpVZ1PIIbv2dXSy3xDO0cToX5ffOuyJLSm9jxxEFgL38HQETR1JgJZzQMY0f8jeN6P/SGqQRTT1P+wzeOf89QRgqaX8E458/eScZspW6lmbSUtsYVZkEwQsqWt7HrX+U2ZyE0S78SLuBkJxmT5bzKPaa122jzrW2Wvv4prnmbhME1gChOfwMZiRY8LaTTNjy9Dk7JXLPDhrBochs7iKtVoT0UqBlyDA3bWgJstfO0ri2c0nRYek0zBxHzCn+dqu89RC7VTKQiK98yE25adXkLO16RIWBDXkE7H6DuTU9iEpgojzxouEXaGm/Ds1J39Ak0KZsVnXNslvoyJteGRefsmRVdO5n24Gm7OBAEUc+o7BTp46CiHOPGl0LCUH6PsT+xU0jsM6P5yRY0TLTWYC3s9PEOdLhvRj8A3GJFo27hCg4yRu7ma6fQCrcF7i/Hd6BWQMrC/iX9pa8kS6KkjRNTS5qaLGkylISO+NG1c01c83gROhIcgxs1fTf0jVPJkEnfOIXcMvX1LXz8qjQzBosO5NK0mEEs5MVaG34wFK8Ubz9Ht6lfJtOvaAx66LXkoE9/LTnohXT6XgdZt93mrnFM3VjHvmLY4BaYUNCz7JIh3+q6/P8AfNS9kjpGAIBDS829fXhU1bUHPMlMkgECM0iCg0YIddQosUYnaOIEDYZJohCcJDID1QT8ounovaUyQ2IlCA5Bjsex2Optb2utrYK2omLLR6yCwSAJhSIqxXjBGiW2O05uDRJhrEnOu35rn5nMTNDb+973j5fnIXPOPvtz7b3XXmvt9XFAv68P7JH8dgwgNM0HwLnu4VSsOTrhuefaBgTlDu7i2z3/pNi3wtg3toT99AKjIfYtj7UYtA2PoT/RJqz4PNFncNOXH+OLtiI3qj7AKgjmmI5DHiLEimmvGmHOuoF+2NlTKTQK0IRDq/BqG9bHPAYkQKjw9zEIXfz7GISm0qOjTTx1x5mV2buZ/3kThJ4QF/49Sq3l7v0mQo8LPaYXui1WKPzm/1ho8Zs6dShAHbaJaNEtb34Tj8VF7chSLqILZ1za3TH5j1o+kGCGrZQP1I+4BUdh95tfK/PTq39zzwkNUZzpdCkf0PXM6QFWGfhsefNMd88JNQT3sBZsqHxQNTfAnbhbmyhH986eM7Cg6vU0oXXaU9AEiXoJ8cFLSN5tupeQbrjnuBT94gi9mWw/xJBTU6JuPzasZp1C6eLEt4eFoeLnt/FZDV8fS3YPaa0TH0ly5BelRrjf+9up1Aqhbp8nVUTX7MXuhlZSVf9GMZnqXDxq5FHxKlfwEFWA3zD9st7FvmQCL0YudjPts4gy6gb0tIC2PQFMOorgInZcxM9xP5M9D7bHiMivn4kv39DrH6eW7wnN36O5l4QnJFSnC/2K279JNsB1vfAGLzvHvmr8k+y91TdMpIIu4frijf9x1X8PWdI5hoxd/82UhVvfSOxAA+68Wk8LWgbTl4wsg83iQsrItnuH2DrZLKwPSBK46hCfmhlrowZ9r7lF5i1DUbO7VMbXHHydDbm0K2CNpr/SCt9TzfC5RaaJPVd+qSl165W6ng46WaC7a4NZV6mZQ0pySuvqDWykFVfpTgcUlA6w9d1rbH333AvEd1QdgnFb9QPY5JvFn3fLxTm0mBenvoATKo0DwcsAwdTF8SA4f3cSCMavSQCBKRgHgjE3x0BgXOxNAsI/Lz8jEBbqQHh9ZhQISvPgGQCw5tFkALx2RTIAnt0cA4B7jQTAgTYJgMH6MwGAK/2aDXZxm9xgD7XFNlhmonLWa3VR9zQPdn4p3dN0pL/G5H+uvfGVJmWVXVmVp6zKV1YV+IzKqkJlVZGyqkRUt32iFc+6ZfCjpsCV6qzSSbhIbHiMyr1aSaVqtfca2EjoKUqpfbrnr/Cm/bT4K4KGogwQcUN3zFsucQm59YnHDFxrTIOrn9lFgbNbZpcEJhClCZuFNOKmDOHxjrbwmOCthYZWvI5saZnnAuL3DKP1Qe0QycxqnQK/kI6jvhSlvlCpL1LqS7T3lra03Ts2OL8kJTi/KDU80Zcqk8yUlEpJKVp2powVALV5Ns85zCr6g3NSDcX1hZaWbSA+Zi2kxFcNrMyXz9+P0Xeny2xpeZzddjWMSYXiSCrOenboDS/hgSx8gB65O5bmd4G/npVKOf11s9Lw45mVgp8bZ5nwUwlrqeBKe865/lm4Og2V2/FDlFT+udub2FGoUl4ouz2Duu1MA/RXZHSUF7JK36pCoqw97P20C0RCeaFurBS1x9u8YrTHs24x60PDmTyedYvHR32I83jWLSwffa3OGX2G0s/Cr9E5G+T7j53STqS8OzS/G0iHceDWnWdCwiwVWGeOkwosGVHyWnhmn4R1mWrAqsyz5/LNbPcgS3Xm2Juc/QG40LcTKJ1d/vG1oVV2r6RVw5dCdgSdJFZ01bLvtvG9uY2y4If+5+K/V96yqx1Cfe0TWDiM0WcgPIU+DZ7DTkwm/Bo7xO2mlFyaPfUasTe3R3MTBexdQuvjCsepqCNAuxj/5pdScJDgCHCefaHjgPBcG5W5QHFAuiSd/Fdacf6orZ75ryzgymFHhvCOiDY7Ycjrt+eE/zMBNfx6EdX2vlLXL+7eQ6jhlBIY7DAeoN3dUVY4p+mVJp9JWZ6rLLd3lOVBk0JcQwMsnrkQKOE6dSajhHENSyj/60AJXu2I74oGN56e7gM+wOsyfu3n16cHGD0sjKKHyAh6aBcp34mih4YsWv6t3wGr+OIixl3beoY0rSMdPWP8BZxevCpXOs0TV1JlvZtj1kchQZnFiaeJttVgrG5Ut3EI33TelaFQ35BuPQ5Vv4tDLXh3+8oa1lLtDX23E9fSghoaMu/A9v7FNJgq2cK5Z8iRwznu5RxZXq+6E6lecd6kL2E0xNj/1U3wCKE7Z2791U/hHoFHo6vGTm//UhOORQmYsdrjZRpRPSGcx4Bz9tDs+eD/VHENMuqAj5Qi2Bg1rOVpF5OOgUWAZnubdEw7XtrvUXYOJlOWq5Tn0oJffkfpzYvj6ZGYJu63aYG/hnZSfAbZ+kGx8ygzbmieeA3x+bWphuCSOwzJ2rpyP6bmxe3HypH9WJq4Hxfq+xEikoZI7yvUjkILUywrYp9ccBv97VSc3VkItWeFmUKmZGtmUbHVlhYrhI9tUV19+l8EBRSqucDNDBGMKn+N5Ue7uiC00l66cePpLvdGtF3p3tgxhzatBuyNbYhWZubzg5XjM2hHwFt/yiLELOi+s/EjElvYhNVlddKImsdCyGegasIT6L1yJYwLslI01qekhDnNGZbtlBJG7nkrJ/DLeHbmRg+0KjWMuGMBPN57naf9WUAnNFyo8x2UKivhibS/cyC9oqzaBhCnzg42YshC99eslL/+ORL/qzcxpsp31ub5M5WyfHU8dpwyt2BGWb6zrMCy7jd8OFFb96vpNQkNrXRoa+7j7W1Ze/+wpikr7bn0P4eaymNly5WEHFfal6jL7Swj/f6vpdjRCJjNQ+AImFnkVUMxR91POUsIexMyWwJklhPFHMVUqjd3mNW7MKwaOSbYLFB3fw3EoJQV6B0JjGOAsLuuuyHuVsrguzjYnVmSGchoNdE6CGeecmWaW6mK1YGUUiDHRFxZSrjykqslrrQmuZTTl50YmsnaX5MhlU6PN4nZgFCn9Ymi6PiCe762YNM3F1S/tuDqby5YwwUDacFODX7Dc1DahtIxvfW1sgLb11QwUbY8VgqRVsrMUULgtcbRhMABUfjeGQmBA+Lh976BEDgg0t+PIwRaOv1GdXf79f5x1wdsz6X4Mx1tpe3PpfpNvtSF7c+Z6Ne0sN3RpntsKmj9IRxLXldrMrA2sghV7REV207E+0k9yn5Sc2i1vk1PzPcaaztcmdLTpSnU2C9SjtD+bexTpoprnakGBCPLUlw9qsumuAS8djGeaMBpHhBqxQEt0BO6kf5aPazeb25pa5oLQ6cuxXVY95OkuI6FqqS7i+8/ifWvl0Ogc+yDqsPVHqpDqTvMpMthqoX5jusos7ogR00l8AgEJQzemWlQUjGs97ey4hEioPaJv7xMrPhvfsluN/eIXfRJut3sqyEqNyrCL2y9AdCx1+icj2D56FbWoJLOVANnSw1sSv8h0veK52s4MDb7bFnR1+HqA5hE3tWp8IfngvdMCRxI6vj8kGDpUcsPIBbB/AMIExQDSzXAQoM71OE6JsHSxeLYVf2IrrDgl4CMXjR45zGdAauupWqU5kPEaYM/0yGT90sEx8N1KUEGN2Uw4lUy1EBf7yz2MS5E2xYCymtPJskncuWtKy+ObnHJH4hsbOwTnuJUAwempflXpxLx2FExwMqfrgHF1a+7glFcEbHlCXTSTNPHMTUxZ/2EZcSf32V5k9hA31Hx1X+AypKjbcSqllbnOYD/M+4o/IN7D2C6Nv1eimEgVrCsNbGkJAd3fF/qC5TWW5SjK5fo8NkiTMDXL7KxT2islUbLCy5Pk9fv8rj1m47li2jE1mr2ILVEPVvtVN8QDwzKdRrBlKTXeLFGOUMDfB6Y1Ej4AjW9RfMTOhFcvscrv98BL4IOLaw7pArutYst73CkMilLOqwU8Qwu/QUgtUdYf8+8q1zImS/RnN31lL6Qv3g5upDPd48s5NjNz+lXwBqbO9LvaGKrpUNNMFCyE4GRbxhRAoDMLg8gKC/k2wTr/ysTpe3zYyZKaI29fsy3s6eZu96R3BJCeOq+pBfp5NkD1EPx3RuTva2q8/Od8wvuARk2jcgn9ZDlpbeNnjx3DVwbiopitm7XyvMTAp2os/PV6gLnG/cYCd+VOt9QZuef23a6Sw/leWu+oT3B/DKNO+wrERcf6E2yvrQQBitAX4koewln6vx8pTJfvD4/oZ+MrTvFv719RjTeKd58+xvQeKe49l1Dggfr6yB/fK5KX/s9kCm+8BJmPotxjwwXCzar2arUmTtcVqx3LBQw+v4L1fJOL3RE4X/TbzOuElqVOdyDJfP+Zloyr/yGlkz4bKoNRqoz6syKDYE+zAg85bKy/2duzCrer4rzRGxrPQfdmpjQrckvSZVO6paObbgLudQF7sEt7PSemhdo/jtovuhp3eNx2UuQ5cqGxb9XJRn2J2q+vvgixH+yziVISH9JFwSbYt37/Bzq3j3zot0L7u1EK/4XJcbAsXa+PMPoXB5x1wx35zBpTFMq7GGj0mjH9UebiWjxPEQm6CjCTlScqOrHL0rJ0RvzYnLd9c/TiHqfjuLNVtu90eM9uhl+OzcqEvJvh0MunkL2Jt6RvvJeOLeVzmM7yucN0KtgHYW9on7eCOhj2+/gv7T9roq1mMot2qTcOivaniT09fawiSyyyfBcPr/iblfV99UqGa+atkOZfX3ZDaH78jig3/IcZW6RWmVV5paoVVnK3FK1yuZW5s7ZWzZXW6qUVSpluWLlC59odB7liz1vf67FR5vCDanejuQ/zwb/+e258fwnuuo4qgcHKq7Psay14JpsKfQnVuXUimlUOZEB+SJElavnoV5uQmF2UXs3yAyiwdIiXRqLzzZ/ghhYhITPomIFwkPFQOWp95eEP5Wde3cUY2t7/H/H2C5vyL33TIztG9YoYzs6h2Rsn7ImMbZzTCOM7cc/jWdsmzYlM7aVWwlzfueGBJtPcRsdqqubsgyBC0Lldjfts/ISy2Ntbp8pVD7PHSrPowXeKvlXjrgyXH4DO2iJxWT5FpXnyF3bnifIrcgPS3rWvVBdkdtyKvB5cniuBI+93qhDuGO/51oi4vuopTE/XKjXQrC/0GelfnBcxIQgGRNkFkIdAeN016BsrzNujrV3PWLa8zyf4VK1seD/UOn9JUTJvabXqroGRzw+MxRXr7rB4J8sEQSCrG6F7TCdmnvLbxhhy2m4YuBlfZwP/k6OcyzNyysgriS0knp/K+eaF56sriqgrG+JR5D1/lzqzOfqihIq8Tc9b5xVtBRHO95xvhHIUGfPcb7hn1SDfz6j2+0O7s6rFum3JR8zmAvhjXbu099y5/TJCWdFldvgoT8OLCKpt3/4rextLnrLhVjxLlaI+y1kv48lwjLWmeuLxJw8yVj1nvvckJYA5EoDIcF0IpfWl1+/t7wyxbK9/HodvA25xIK2Hm4lBPFOOSRoDq34vjksuwDnqJbN8XqLm83SA4jX6wUwQsvz3B5l2+GvaAufXELEXksftJIiKZaWqznIuaBXyrETycpOvGnZ83gzWNb/NwQS25AWCh1DDd82/Q1yMHWmYTLbBVJ1XShxRCnStiFHqKWf/jY8Z6SNrRkN0n8PLRbTZBkbqKWbsxcX+TO1I1qBMH0R0RaFx1JVIVSkmIt3IsdK9xr+Renlc7yhlh70smEaIRyvbMLdALGMuHHnP4G6pmvLS7VtyOQVdy1Fp/Esx6plL3uaZmGbHBpcgDCqaEF3cRu94SfHtWIefmCGevMcgA16VxJkP1iCtSFXVXterbg1BkKV/4qjrqT7AFplGmIXEvquG9SyEe6TNky5dKAsSVt6v1Kd2fnMR01eiMqOYBVFtCPOSCDby46vBuN2ayCljBMQGlO3ZUiKPR1sa9VP6DPQW1uFqfMb6K2t4sF9o+XnHESHg+hZ2RsXLArq4ogfF3xDZc0xGfjK4hDogSmbTuiCXElN8FEVyPRniOunEwjThJd+lACHgvBskrTDujkx2mHe00Q7XLD5a+6ED4HK2bERxAtxAvO3ikOD4OIy4WddqTCr5Vt9SCbQwsV3hUlCi+9/N57pqjip5rqN4GWtwYu4br/0F3QJ1eplrbOtcsrOcpxC5v9EjbpeAOu4h3t3nQW1vY+j0PkTaK9T1+m016Hg3q0YdOQZDDqHz3FnO3HMRtaPPyYqNzLHfG8ZcyqQr3CMWMXGItcJLLPBsllGb1nQzcPFzlmEUvd/pWsNcvNboeI71WdlISoENHEIP2OXFVkelRTf63Bspx4kallptoHq66d5cZ70XwSHDi4bsjrb/WnF9Zl+Yn4Y
*/