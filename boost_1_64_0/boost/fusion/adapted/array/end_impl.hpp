/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_END_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_END_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/basic_iterator.hpp>
#include <boost/type_traits/rank.hpp>
#include <boost/type_traits/extent.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct end_impl;

    template <>
    struct end_impl<po_array_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    po_array_iterator_tag
                  , random_access_traversal_tag
                  , Seq
                  , extent<Seq,rank<Seq>::value-1>::value
                >
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Seq& seq)
            {
                return type(seq,0);
            }
        };
    };
}}}

#endif

/* end_impl.hpp
kbMDpJfutf1wlTFSW9k/XeaEuhUVCEhcJxMg5l19QgEGFFxQZ6M3sODx5rqb94mphKRATc4eA5OA6dXV5eI5HGzJhQ7jYrO9Rwmcnd9XPhT3kCgGLMQAmIzglkJKQxASeUCQanzsDSd4dcoYRuoI9HM4PHcAe0aUnDCkDRBKWN7phmsBzb1u5th4FbsooJLZrkxHRWJ8x65HzT6hjdEN0+ARB/lHWDJjaxtnFO08p59l+0g7iIF8XGCZJIxgElHFPGQcgxW5Q8wUis0qBw4bN2b4RaaaGV1aD+PttSJ7PIkpvs5M7EnD9tsfjBLH9voQDrIYpGOu2kRujXo/4oyGJrYdMtvreMzroRjFicIqGq8ztFFUCis21IhBz8MCrEXlR6yBASAMBioc2Dewk7etLamwMbRSjp2pvm/KAfTOI9HzGO0cUr+CWAItcnlnaI1rSUhoVTJHRqfuOAhqnYpz7IIeEmIJQVCkC2Dlg916F2qBcMjN8qpUCFZCV0DD9i+rTvrThzSgxVOGVuWMTx/UJzTWAd0KSEDZQoT4lqtsLdL5kRkX0ZxgZChkZG4jmg/FUc3dFaYhhj1co4p/q0XH1mD5eDmxQiwbMmZAnzFMXmV3OVUsHvRpyDMyfzGw25vGgewjaXSNistD/G0+TcsCQpWNVQQxUEMWeiFlCSNB+ZWtGEYVYxAVnNBflif9EI00LkWRzz40fcAmCDEkIiRIGJ9Tj3FkkEIpEywjl5ZwHMXGJIjyJCyOpfNaXjyCErDNodu6eMNnZX5xocijmo3stmBSzrrIMjNCkN6nkWRiGSN5+REwTcBaigCMBR1LB1sn0CF1EJ/K1F+20iTspbgk1HzvpwDNiXlE1CReCeyYkGqNmj0nZ0zkIGbXhPHalQmZXM2XIUowLsocNyjCervBlDsz5b0rAzp4VQYIOpINe2/NgPbCvTBleccCwjsm8N++QoMw8eaxBzKLt88oZN6/ILoYS4iktzcIM0+3vJ2e8eARIMjHbviYGARQhNri9NxSrXhAp/tBBMbxtKEAgwfAosJYi0ZWVqLMgAV5AQmzOnLm9snyupzWKQt5X4rzGOMzBjhRA0B/d1oHOnikjSkPWmg9ALoToOn7dURRzv53q0FTyNbGE2gCQEpCcwZoUF4sAcz7IjXR+mObFMHmGn+3DrD3VeqSJjZ9ldoSpdypr1IDDr9KDSj5VWrg0VepPcxqKvgqNZDoq9Qeli6hDztA9RsxCg2G6GgNUWMwjonR3S/cjNAW09aY/nr1cvz1aoIqlKUSylKxslSkLJVQFrB0CbGyVFJZyiorBoOYkbKUryzoqfx1zK848+HQ5Z3LNfyUvgJeZAtWbXNjfbKCD6dRzdkioZ56bsmcipjwZyemtkcwPE+cURcHEV3QuBWqVcyMqxzHIPEugD0Vs0v5YwZqkMqO6oDJOwzR/VA5iPIqHBohCYPpOFgxvCBaCFGs8LPnBokdpgodpCIHCSLtIJXvIP3uBiqMPOrbMUJDMHsb0E/lFmdW51ZrmP5hwmZY50NZ/tfSl+lr6QiWfYWCcVYukyycwNC4V/D5iwPzZpvKUrqZLKmPCaNVgFBMM/acwjJKjaclFsPMbAODqKVpAVRCRQxM9gbFVaAWthEx96P0OGo1GjQo0hALJkzINvslUooHIcxMreTYY0ugC/eCX/pGMY62tnbtAObWVyUqpYJKqbhSgCYTySaDZJNhsrQuVFIXyteFinShvBr7zRYrqXwzdWVubtadxhaAubXAx9ABicBU1uP6RC9Obqes2OWF4eGPnqjqIOaoiIYQTU8LspyZIoxbEMwPJQRhkyLsxt65y/xQbBA2NsJ+UQCc5Lhcwfw=
*/