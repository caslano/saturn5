/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SIZE_IMPL_09272006_0724)
#define BOOST_FUSION_SIZE_IMPL_09272006_0724

#include <boost/fusion/support/config.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace fusion 
{
    struct boost_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct size_impl;

        template <>
        struct size_impl<boost_tuple_tag>
        {
            template <typename Sequence>
            struct apply : mpl::int_<tuples::length<Sequence>::value> {};
        };
    }
}}

#endif

/* size_impl.hpp
o3WJB/bLxhjd5KPHu6+u8nuYq/P7e1/M023e+wDvq+v8zwneRRe+bo0P8r66xn0Tvacu8gpM0R1ecHA2JukW7/0Na6XLfBMmpnEeOMQ8XeSFWKKbySX7ov1H8rHNYfZLlzh7eDZWpuYfY7Gu8p2TsrFGZ47IxiePtG5pDv/lm9YkjU/Oxl8x9D3PxuOPysYwXeaDjraeusYnH5ONDWlteYcp2Viri1z4VjbWp3Ge821rbn6Ttyx7Bp3nk7FcV/mfWKbjuGx8BlN1kU/CvDSHb8US3eI3MUPHd9wXk3SBD8VsXebzMEXX+RFM1G3e4rv2RWd4L0zXJT4Nc3WN/4pVusX9U62hLvJLWKgzx2fjEizQTX4aY3Sbt/ies6QzvBfG6xKfjnG6xrdjtG7xVSf6vrzvmb9vrzFWt/iL07NR1DV+Gm3d4T1OzsZGXeLLsUI3+MUfWDdd+GE2fvsj76XrP7Y2p/j+6Bo/gAm6zfETe5Sejb//U3unG/y3U+2pzs/MxjvYrAunZePZnzsP6b5V+3mWPdZFno28rvMHZ/s3XT7Hu2BNekf++i+yMXiz63Pnl+6d+lfZGD7HGdUFPh+ZNM7PoZHel7c9Nxs1neeDMF+X+TzM0XV+BHXd5iG/zsaiNJ9/gNW6xo+hlebwlPP8Fugq9831TLrEF2KdrvN6NHWcn42vYGmaw3XkPWeTP3WBddBF/uBC66wrNXt6UTbKusN7XOxddIkvxwrd4N9cYq91m5+Y53zqzKXZ+Cam6Qr/Dq00hwcu8166zHegqVv8ycs9m87zQZif5vBZqOoa34SZusmvoqZjvu8a5ugiH4e6rvAVqOjSFb4XKH9gTfhuTNYt3oT4n2e+Mhufw0bjRT4ReV3lq5DVDX4GVfPjN94FM3WBj0LbnApfiNW6zg+hbE6bP8RknVmQjT2R12U+E1ld49vRTM/Gb2Cpjt9mY1dUdZG/jZm6wlegnfaCH8Nq3eYhv7MO5hT4EMzXZT4XRV3nuzFWt3gT6p4hf5Vzgvm6xKehqGv8Z4zVTX4FkZ6tbh2wMZ1/PhnT0rrxXRhsfou3udq5Mp7nYzHHeIVvxDrjTf4A09L6/D4bB2OULvNvsSKtP7+GOTr+4O8L1qX95fOxKL0XP48JusO7LTTuOkU+AxN0jR/FYHPavP01zonO8+HIpPvyJSika/KTqKV95O2v9V1L8/lwVNJ8vgQFXecn0UrX5+2v89k0nw9HJ51tvgSNdH1+EqU0n7dfZDztBR+Oki7zJcikteKH/+gsfZj+u8Rs/Asb07otdt4w2HjcmI1fInSDF/zZZ3W+4bcUo3SFd77J/uoyf4iSLtzs/KOg67zTLfZd13iPJc5tms+zkU3j/LNbra1u8qtoe574i79rWKcLfBQ6usK/QkvX+CY0dZNfxWodtznzWKGL/B0s1RVuouxebR691FmN0VHky1HXDX4ec3SHd7/d+usSn4GqrvGDmKbb3HOHfdQFPgEzdZWvQVk3eDNKOnOnOZic5vCNKOomb7HMOug8H4yxusyXI68b/ApG6bjLeqKgS/wTZHWVV2Kwbqc5f7V3aQ6fgY1pzflxRHpHHnG3tU17xydgta7y7WjrFn+saS90nvdHS5d4Adrp2fhj95ij83wwWrrMV2O1bvJrWKHjXs+Ghi7xuViq6/w0mrrDw+/zHdR5/i+Wpudc7v+ro6lbPPR++6jzPPQB+6hLfCcW6TaPXOFeusrLUNMtfuphz6PLj/itXmkd0n35Y4/aa+MZ3gtzdIlPwDRd4d9gpm7wc6joDv/lb/Z6C9fhQx+zX7rGm1HU+ZbnQkG3eLun7ZFurLb/z9h3XeGpz9r3NM4vYYLu8Nw=
*/