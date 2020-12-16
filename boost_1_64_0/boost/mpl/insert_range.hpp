
#ifndef BOOST_MPL_INSERT_RANGE_HPP_INCLUDED
#define BOOST_MPL_INSERT_RANGE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/insert_range_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/insert_range_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(Pos)
    , typename BOOST_MPL_AUX_NA_PARAM(Range)
    >
struct insert_range
    : insert_range_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence,Pos,Range >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,insert_range,(Sequence,Pos,Range))
};

BOOST_MPL_AUX_NA_SPEC(3, insert_range)

}}

#endif // BOOST_MPL_INSERT_RANGE_HPP_INCLUDED

/* insert_range.hpp
KlDsdipg305l3QQnLESc0lCC0tDE000quGFhcalgp88hFfzaU1ocOP5YMjchVUK5En0oq4+YtKQOS9jPzZL8ZJMvo3OzAK3sZzq38Hs86OThc6dcPHyAsGeUnTioM8+HeRP2smM4XmU4bhYajofp7GL0yWZpBn3lG4pmKy5cL5c7YcWA/1zIgImVIq9P7X6KJA7ACMHKxllIlGDEHAENh8CIo/strpM7AE7gAOji0Abt2gX/K207ovStTnR+Yq10/3c/Qs8bef4b4vkvU5Sgb1IEvc9x/jMd579x6/y3aXa0D4VRsKujzyLumxznv9r8898mdf7rO9j579ii57/ME3H+myw8/006zn9Z+/w3l+e/LDbe5zyW8eF7SOnf4VRr2LKUKC+NktoOTfVzdhd6xxRRe3yyqNrju8e41R6ayt/iPPst5tlvVH7gjQxgLzyqjLuPKiYJh6Xl4KSTcEwWIxyTxQjH5IEJx2QRwjHJo8qEFqVpWEDpkkeVCR5VJpxHlYkDHVVGeVQZ5VHF4nAGuUM+m2uoI9l3Mo+fOA6AE5ZLNolxMZJ30Ovn7O16ZszersLZ65/WQU+5YTPqYyP5HLP8SE6d4yQYG3efcDgT2n4FIkJGiQiTxUSEyWIiwuSBRYTJIiLCJEWEcDK2lePwklVuFQZEixztlyWrOIyoNmIG7VWHu2vAmIaL71V9TLNOgtmCk+BDOAkWLgCm3nESzMpJ8Ok1T0HLQpsDVSKpiPLkuz3RIT6jGLImLHdozuLQXEijMMDCk6AxN+8kmH32JPhM++TOf7+Q819muue/8Wme/178WM9/RxY9/2WeiPPfZOH5b9Jx/ss+naSCm+a4pILSZz91uBsvfribVIe7J5cikVfz3OUe0o0Gec2hnv0m9Nlvgmc/Uw+YJzynFxOJBIGbryeXYSvdpAK/XiK2MWQn18EtC382xNEjh+UN59lvvMTZ7ykSQkqf/bIFfGZUBsSnQOQzo0X5TO61yq36Hu3Zs9+hfez74kU7cd47yzInzbs3TrVULvlOmfnIjn1T6rZYP9x25+9mvgniTsKckJbaad+/URHpfAEgdASJEehyVk5QN6IQSywGXjpBQJ/SS3QCf5Y4+0ZnzBhnhkV8GP3YbyDQRw5xkRKslEDJm7WmJYakcA2cFFQ5PDcyrWpL5L7vzDfLMBrm0J0ZclbM8uMweQ/bfMiT6kBS28v8mx8yqu5l4u6HcmkBK23VP8p0YtW9kX9Uba76lZrBHA+aFIYTALT6mMqklpqAHFNzXg4FgErGgN6s6u4ssxKRQoBX9hcAHCwEOFgE4GAxgIM2wFxSt8u3BgSbBFNvRKhFt8u3Brhha3Se6VcYDRFcCLcYjQgAaXFyll1R0ZBsqWjM49uTIaJEEZcDckJZU9kQWVMxHwYKjZEVFQsduck1vgZ4HWgs4nWAFX2oOGs+HA80RhpnLXTkJtEmsKeRrtWfS4vAozT510Bdv5PxUtLl6TLIJOf9L0unNj04epuDHiQuw/+Wl4K2c5TZCp8PJan9IfENJqn9sU0omhTzaQITNVAegkKW/rClDPNhdXGYt2zTT59hW/bzW5+sLRvPQGBugrCDPy0ugdpUGeOSYS8c96R5Xg0349MJ4e335B0/2TeVuLwCuNm2/hiDCGp+BzjrcMkf1iZvEsrLfAsUmgf3g4D2E52uVon0135TKhusVwBPmOefLdSXTuSxz+3+SuXKohJQO48yyPGqHC9zHIuFpAYrq5FZNjlFlmFlGcyyPXQxa7GVtYRZORqH3q2sSmY5T0XssDNh/QD9C7Yvag3aVqBrz+Zuz/PXY5GFsb/7pD7s7pIxCSHLJ4PnFrzyt1yRF5g=
*/