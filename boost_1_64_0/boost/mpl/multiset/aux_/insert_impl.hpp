
#ifndef BOOST_MPL_MULTISET_AUX_INSERT_IMPL_HPP_INCLUDED
#define BOOST_MPL_MULTISET_AUX_INSERT_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/multiset/aux_/item.hpp>
#include <boost/mpl/multiset/aux_/tag.hpp>
#include <boost/mpl/insert_fwd.hpp>

namespace boost { namespace mpl {

template<>
struct insert_impl< aux::multiset_tag >
{
    template< typename Set, typename Key, typename unused_ > struct apply
    {
        typedef ms_item<Key,Set> type;
    };
};

}}

#endif // BOOST_MPL_MULTISET_AUX_INSERT_IMPL_HPP_INCLUDED

/* insert_impl.hpp
gCV24VOOoUTD7OTcjERN/+IGicXoTqpNCiZ9wrS+TYzHG7PExmcn3rheU92/OH3k5urRXt/AJep+maVe86LUH6vzVV1iCSzxKJIvgzVfCemGisvXVdv+osvIV77k6z7J1yLJ10lrvnIzUmfe8nyFSP16f8lXX8nX8qbWfOUkh1RYvkqs58F19+N+yVdbyVcryVexKV+pGcZs3TieyJF8WfqU57OcT5o+hiOlLr+f5KU3aWRPnvP5mvKSHUu0jz4rNVF38/mxtP+SYmozcpRx2Txbr6/NyzHJyzzJy52Sl+XmvJiaeYlPSNNXWF4uS14OeWn3UYocEF0lL4GyjwKaGfPC5cW4k246H2XsI7m+afsljqxhWuAYeeY7Eo8qFX6mvORkxc/UZ2XrpbGYG5//6jZ7DJb8aL8j3Gy/I+R7Q7lmZhmvmBK3V/Y5YNkuzbZT5i80J9eyLHWZH5Pt3Cdl/rq5zFuYtnO2wbiNFVrmyjTKgrN1zjZx/hfbxGmyQRkfFXbAZd6dz0UffDh55TM7n+90a9rECdDJvTW20rwvV7rvsBbYFi9itIv53harmOZL4e9hch/cUeqoArEJdsNWGILtsTv2wB4Yij1xEPbBdOyHuRiGy3AAPowDcS0Owg0Ygc/gUHwTh+O7OBI/xkj8BMfgMRyL13AcukidfyOMxhY4EVvhZGyPU7ADxmM4JuBw1OMkTMZsnIr3YwquxVTchGn4IqbjIczAU5iJl9GA1zAHm0gdfheciT3xDgzDOzEC5+AYnIuT8C5MwnmYJnX2uXg3zsUFuBjvwX/gQlyFi3A9LsYCvBdfxCX4Mt6He/B+3IcP4Lu4DAvxQTyKD+FJXI5n8B9YhCuwqtTp18WV2AAfxmb4CLbAR7ENrsKu+Bj2wscxCldjDK7FJMzHNFyPC3EDrsEncSNuwgJ8Gt/HrXgEC/BLfBaP4zY8iy9gEW7Hn/Al/BV34h+4C5Uf1C9jNXwFW+IebI+v43Dci2PxDYzHN3E27sO78C1cjG/jQ3gAV+FB3IHv4C5819L3ntzLY3fSQds+/SRGqC16YDtshO2xBfpjAHbAYOyoij0yyHLHy3LVsUddZLnBstyustxuGIQh2A+74wjsgWOwJ5r71j4py79Plq/uWztUlh8my+8vyx8gyw/H4TgQk3EQZuNgnI9DcBFGoPT5KvfKLEvWp+7zdaSsb7SsLwo74FjsgeOwL45H6WNc7nEpW1meuo/xK1KHfRU98Br64h/YCv9EUznL/Sn2K1XO2r5oPXAeeuN8bIwLpDzuwRC8H3vjA+qYNln+PFm+OqZtkix/six/iiw/Vpavx7aYjAE4FXthCvbHVByJ03AcTscsTMPZOAvvxDxLucl9J3a1U25VJD+3SX6qyX6ojoFYQ5ZTQpovyxkjbYT58HeRLOeIlP9n6I1Hpfw/x0D8AkPxSxyCx3AKHsdsPIF341d4P57Edfg17sJT+AGexjN4Bn/Es3gev0G2QfctuuI5dMfvsCF+jy2wCNvij9gDf8JQPI/heAEj8CKOxJ/RFKMi95K4T8pRHaPiLuXogV7oKeXohV2xPo5AbxyPDVCPt2MGNsR52AiXoA+uxsb4FDbBZ7EpbkdffBmb4evYHJPKESvhfF/+P4+DuNkYiL9b7ENQTfp8Jc0hrSQVkPaTjpEukdxq0W8laQApqZYzDsI5OAfn4Bycg3NwDs7B0aEKKfkvrv+X1v//47r/n1V1/72k7n+xPFtfQPpcqaOrbK1DDx8xdnj46H5R4QNip+pzTPUIljtFB9v9U96PVX6DZtnUt6TK8/Uwyc9+yY+3xCJ4kb5U6uZcysqPUixdg3TliEnwUOqas7TtEcY=
*/