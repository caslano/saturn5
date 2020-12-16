
#ifndef BOOST_MPL_CONTAINS_HPP_INCLUDED
#define BOOST_MPL_CONTAINS_HPP_INCLUDED

// Copyright Eric Friedman 2002
// Copyright Aleksey Gurtovoy 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/contains_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/contains_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct contains
    : contains_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence,T >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,contains,(Sequence,T))
};

BOOST_MPL_AUX_NA_SPEC(2, contains)

}}

#endif // BOOST_MPL_CONTAINS_HPP_INCLUDED

/* contains.hpp
Bt0MjW6Gg24G0K3U6IqjamXVTXqLZL4Kqe9b0N0aL0Dh7i59kdo1Sh3CWamywiwdj8Ktmyk7vYrt2D8W8FkJAT/aRQAfcs6DlY3OZcCfiMdMexxyXLHZIVF36/yE4KY54B5TX38omeDochKse5rZqlXJdGfQjRIA2QIgcqUyiYHwPWnToY0YTgZbF0spOHheewSAWpfEw9rdWWDl6mgi1mwn1zWS6xHJpfjKwmPbBVt0axccQP+eoX/tctsFJ9K/r7r9d/GVRvWbT0krxc7flbxrrzqiPe1k1Cg10g8TIuiIPSblGR3kbrhVErCtlEGbGjphQ/92QenNN1uhN63bXVBC9uPBpvsxuPCFHhS3f9lP4T8yzSJbV8lcK79Hu2DYo/9rbb8IG6u+7qmeeOgeQYRReoZHxu2dZPzM0laBtRBCfgGsGlTWVj2TKoiYDpkq30R7ewvkW62SeFpe0DfKUpalnIfAzz8hDm18PlO+ozdXInrMV/To3AP7YaVDlJHy5ciBetKay7zqlPYw9qdbLUEjaLV5MoIdZHDCUh8WcL6wT7ld+SiW65/VGAjC5Y5DIVD7crIkVmbZ6ABcI0a1EI14hPWAwywWK/o+y/TN6wj6EiA1tHoArF+5r3r40j+waFST41STi2rYAZ9GDXkqQwyegkB2aaqcxvKtTwFOffd6sEhypr4lCDzeQbjVGq++61CFxVlhHLSwhZhdqGE+2E2C5pGzNLL7SaO2PJ4Uzuivf4P9thaV1KmPc0KIHQq04JbrxxO398RPo9trveIQ6Q4Xkdo4ONarDzPUaCqfvJh2lZ/Hfq39Bq076VyD8kSDV5qKILEJq+cABti7bAlWOxvsN4cBice0+t1sQp1qyAeMgacm+a3VwFN99wHPDx1CXi5IXpLFG+Yzyscu5vF+NGNHQ/r7IBTd1zsS6NzlnNjuh1GW5V3Q1frCAXmpgDwySyZfa/uLjw/UN80++O/+M/6vxEms+zzS7L724J7i8qB9PLV6t8pj5NovmTR1R2nSwN/ZnkK9Ba2jJ/a1e3qKh1gPxZfayqWsh6OY7rA2xhEBYHaMyl5FiVBfch7lbDvyc0H9toq7FdoPdGbbaKZib8zFFh2HmeFmKgOgkoA7sgnimw8PuGIbFNHtiFCW0vQyWnhnmRfQYQ1Nh3jpWWhPSgEzsV4S5LHVVdIayH9Hntmcn1n/06yy7+0nF/gyq1SkXe0Bz0f4uhYSr6NkWaZf0QokX9ZKPl9Ct9hDKpJ1qq18pDvwSVqhfX/+ywH9kfxfjqGPqvjEb+TjcWE/ypb2krKZ1sb+mjZf5cg+IhdbQTwfW03NM3gkbX9Xav+faSFs4oZ0Rj1PwazMiHXjOu0TKw9g1ZbYn24eOhTD6NE02auPtYdO66r96XJ91G4cbUjTcYgVk7oDYytoQqO8SX/kIHAWZcIoOomSnNsRvCUtoaYmja9Rm15+K88JNmH0DNnTACCNg/XwV5jlFT+fmxMVukNRehKb4eokS6RSsOxsLTZabB1RrSUKi5p6kyRipXwPJ1ZNIw3jMFvtZP8p8NmBpPtVe3rG71et6d74flWp7FclSf9Vm4bTP+8m6XH8E05RdwQtxS8s6A2wvFnqC/mn/YonhJU/E68b+LUpO6xG/82m8T09DfM7ko6R/bnCV1beOCR5EDs1acUBpBdWAJHInmaIKqHnEezWzNZ1fgbP/GlXPCPPEKY5xwxLNXmsVJPn54NNniNZ0jal2TH0L63I531r+6pWgKFdkr5m/WDRfuXCTDlUjS1aunO8zfoN3aBJyQq5F/NMMssYwPdp+H+ISv4Jw6c9wqIMAM891r3NvoAgL3rfk0Z1ZwD4x8e4k38=
*/