/*=============================================================================
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_KEY_OF_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_KEY_OF_IMPL_HPP

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct key_of_impl;

    template <>
    struct key_of_impl<struct_iterator_tag>
    {
        template <typename It>
        struct apply
          : extension::struct_assoc_key<
                typename remove_const<typename It::seq_type>::type
              , It::index::value
            >
        {};
    };
}}}

#endif

/* key_of_impl.hpp
JLwMfg5nwbJkxiHwPHilyR9eDe+G18D74XVwObwevglvgj/Bm+HvcC7chQ7sdrg7vAv2hvNgX3gvHAPnwwL4ADwdPgjPhI/Am+BjcC58HC6Ai+D78EkjL1wMWzXluwz3gM/APnAJHAifg5XweXgFfAG+DF+Ea2EdTN+M7zc8Gi6D0+ByeBtcYeoHvgY/hK/DtfAtuH0zvuOwF3wPFsOV8BT4AZwFP4QPwlXwafgRXAI/hivgJ/AHuBqug5/B3+Dnpv5o52uc7yl7EHo/Xb6n/Tz29zpL62yHeoLG07pvhst4+k2tD70Fd4Rva33tHa3TvSvbp+9pPWol9MlG61lwFVwTZHNiCR/glYT12Z1YcJNt+2DgLbHZn0jYntj4tif+DrsT6x5rmO2JnR+P3f6E7+b/rg2Kbo9vXDsU/zcbFJvC/kTO49xHqCXMJywj/ErYcyHlJFQRZhMWElYTmj1BeyP0IxQQphPmEd4mJC/i/wjZBB/hYsICwirCr4Q9nyQ/whTCDYSlhO8IqYupV8IwwhTCxYR5hKWE1QTPU9xLGEjwEWoJ8wmvE34lpD6NPIQiQi1hPuF1gpn0tnkmYVcjcSWuxJW4ElfiSlyJK3ElrsSVuBJX4vo3X5vK/l9FmTH/t2G+/409v8kdPAH7IzO0LLFA/ugfgM+Zc0UVrH3btiqO6uzNyh1G9sVlVTGcm2jSam4V9wbZzZsa5r/T/DY9+Ky0fquFu/vt5snG/CxPuJ9P56zM4O0ibd3nhPnMNHG7WGkoL9mpbxlqfz7M1lx54EzOaOschO4tz1f+Ok/eVL97HX/OuQG7+vaxF2PLZ69K7U+38Vh/D9PfRRn23/fr7+f19x5V0jPS3zP19wv6e1VVaHqeavvvS3q42+Qr095HMeElc2aq2vXZesfGcA52a5V9ilUn3KHfsiOep87Thz3P3CjPc99AGxlTXO7FapurrYXQ8vWTHb5TkuzynQhfNm13Unj5eBaUMR57IuHtNTvQrkhLMueElSXSJmRpSYhP1ui+XEPsx1TJht6nKtcq+Ko551UTXC7nNJP9+Or3gWHZpnTq2Rfk/0I29aqKeT8CtinTu+h5Vso2pcv7OdVTvx/eliHv4HjrPHJ2Mu8J5TS6DcvscumMkdOOQs70W+2N7s/ljPLqJu7+sOecuPH9YfdSnjVNI8/ipfGPusg8nZOBceRLW4s4G1iwXfSzgZ7Novjnnrxp/HMH6mWzyGexkIefMznkbCAvZdagoQMGD4r3eaRHOTOe3Cyy/IuIOzVKvvHWQXoc57RXS5avVQ9rCMtNv2vLUl02oaz8+DLzAttvbiy+o9WfRvRLufqGqd/VNyv8e6f33OX99YW/vxH+tQO2o/5TZ+Lcz77F7yf5n3Ymzv3sW7Szcv/+M3E1na32tqZml2+SPr3nnoMfvWnLg9+9vmFn4jKTNO7VeHg6YS9Lx0/2ReVnNFtn3QbAzjoDkQEHw346C3GUzkIU6ixEJRwuf59HwcU6E1GnMxHf6ixEC/IaJb8ox8oPsxeOgKPhJJgHT4Zj4GmwEN4HK+ETsAp+CKvh53AS/ALWwO0p04lwDzgZDoBT4JHwJDgUngyPgdN0xu1Ukw88DV4AT4c3wTPhvfAs+ACcHjhDpDEmLHM5K7NE9bhUOjIvwF7wRZ0VeUn1VgeL5S9YOpoa2zHmc9HR3FHp7gL3kx+d9vKj0xemwtFwN1gGd4enwD3hzXAveCfcG74gfzrL5E/nI/nTWQf3l//sdjqLeADcCx5oygPT4LGwl/xmH6KziZk6m9hb5anzaEwHP1V5zFhiscpznspTCzvoLFt3nWHrLX/gE+QPfIrOYt4gv98PwNmS+yo=
*/