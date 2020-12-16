
#ifndef BOOST_MPL_LIST_AUX_PUSH_FRONT_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_PUSH_FRONT_HPP_INCLUDED

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

#include <boost/mpl/push_front_fwd.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/list/aux_/item.hpp>
#include <boost/mpl/list/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct push_front_impl< aux::list_tag >
{
    template< typename List, typename T > struct apply
    {
        typedef l_item<
              typename next<typename List::size>::type
            , T
            , typename List::type
            > type;
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_PUSH_FRONT_HPP_INCLUDED

/* push_front.hpp
v41YBx/AYNyEXXEz9sCtmI4Py/p7BB/BbfgkPo4f4Xb8FF/EL3APlpG67WB8CbviPuyBr+AAfBVT8DWcg//Azfg6bsO38AAexg/xbfwJ30Ff8ncE6+Ax7IbHMQE/wOl4AmfjR7gW/4nP4Sl8F0/jcTyDH+Gn6ncK5Ngv2/wah/eab5NybCblGIKB2AIbYCsMx1Dsgq1xBLZBM7bFXGyPedhB3s8NC6a/tWBvt75xqtTnnv1XxZtSX970bMX/iTrz66kvL66ufAhl5Ky+PJn1l0/YRNhLOBnsqR/3DP+9w83//r/l2vm6v/+v9P2fo7S9H6Xcv07JToxPy0zLiU82ZRot9QJ9Ne3+T8r5bifWwi3Ykevj2DiHegFD0fbvZVzXCVj6mftuEMvgVJ2ZfO17sF98lbbX8WZTlkMbb2nzLff/jGdb+pE6LN8WvIXwpSWd0rZb2hOnmrJzbMs/JtNYuDJN7VNqR5z+2r+LlMduuffvJ/fevbBTJPMPVsuDhtVSJuqtTvHtcpXymDnEEieN5e3lYU+v/t5nXFpmcnyGKdno0I491aEtdbamre4mKSMnbaulbkMaIDKUlfyVwi7kz2eoLn9KkuLTzMXfW0tbXFu7ZrUtbpCmPf0l7fqUtG/SrM+9lPmM0tZ+XsYo6dDkKZd/p0setPehobLxfWGQNtOEKPKRMEyXD2W1F1tH4pAHdT0EW7cblsJENU2u86JsV7cOt6a/W6S8ByPp3SXprUIoLWnuwW8KhmvTqxT7uKmZiRmsdvfrlZR0yzyWNKyWNPRySEOM3Lu3lvhbEGbX5DrfnoZsyiwnyRyfmWxMT5xqKL5+6Vbtfu3wzocps0iZ6bbF8tLePk7S01/q2QqH6+oS5O2S4r954OoYI/HL+wv6/WcCQbuNpkkZBo/Q19eEyngDh7rCMtLW/Zzk4TNCP2U7HKHPQ1pmislwHXmohK8Tt9SHqHVVfYhLlm3ZlypRpmcI6xmfJWl27IPQTy0TqZel/kp7bHxI5hsg9SR7XeT9Ncn7Msn7YkKXGsoHxhzznpZjcKM+yI/zVgfiPKqet2jyn2O05Ks8cW0iZCntDEcWzRfbiJr+ffL3OEn/oZHO0z+3vBzrJf29CIOZJ2qUvi6LI6EpKSe92PRr94WUZHW9obre1HcTSrOgxKzxkgf9tjfSEj/3zpL+rFHO09+wgjXyoZL+ONmfNxVJv/L5jeK3Pf2+LOmXcTkVuTwGMs5xWn+8WSnpC5RjXgDhIpn3sT5zIE2W9FGZbkzMzDWzneQUe8xTyqPxaE+93d+p3u6Cpd7uzSPpo1MHtZ3mX+Xo64H9x4z/a+vtLhvkGhd3Wuq3ZPskyHOy/Fr4b6yHP2MYXsFI/AX74FWMw19xGP6O2fKuw0IFLMAyuA7L4uNYDvfiLXgIy6OSmIpYASthVayMt+Gt2A6rYCf0wS5YFWOxGiZhdczFGrgQ/XAz+uMWrIPWb0fINS32k/xrvx3xntTbvI++eAzr43G8DU9gNzyJffEjHIr/xDvwNE7HjzEfP8UX8TM8gP/CV/EcXsEL0qb2C6yMX2Nt/AZb4bfYHb/DXvg9Eqhfk2tXLCv5UI4TGyQfwZKP+pKPBlgHG2EjbIwh2BT7YXNJfwhmYUvMwVa4FNvgCxiGH2A7PI0d8AsMx68wAn/DTqhcY3eW9O4wyDUqfiH1ZdVxi6Q3StIbLem9XdIbg8HYHdtjD+yMvbEn9sEB2A8nYH8p/wG4AmPxPoyT9TBI1sMQfBuH4hEchp/hSPwcR6ltwOVaFatIurVtwCfJrcVUSf90mS+csEPmay3zlcEQma+evDMQhL7YEltgK1S/xyvzx8n82nejxkp88VI=
*/