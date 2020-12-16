#ifndef BOOST_MP11_DETAIL_MP_MIN_ELEMENT_HPP_INCLUDED
#define BOOST_MP11_DETAIL_MP_MIN_ELEMENT_HPP_INCLUDED

//  Copyright 2015-2017 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/detail/mp_fold.hpp>
#include <boost/mp11/list.hpp>
#include <boost/mp11/utility.hpp>

namespace boost
{
namespace mp11
{

// mp_min_element<L, P>
namespace detail
{

template<template<class...> class P> struct select_min
{
    template<class T1, class T2> using fn = mp_if<P<T1, T2>, T1, T2>;
};

} // namespace detail

template<class L, template<class...> class P> using mp_min_element = mp_fold_q<mp_rest<L>, mp_first<L>, detail::select_min<P>>;
template<class L, class Q> using mp_min_element_q = mp_min_element<L, Q::template fn>;

// mp_max_element<L, P>
namespace detail
{

template<template<class...> class P> struct select_max
{
    template<class T1, class T2> using fn = mp_if<P<T2, T1>, T1, T2>;
};

} // namespace detail

template<class L, template<class...> class P> using mp_max_element = mp_fold_q<mp_rest<L>, mp_first<L>, detail::select_max<P>>;
template<class L, class Q> using mp_max_element_q = mp_max_element<L, Q::template fn>;

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_DETAIL_MP_MIN_ELEMENT_HPP_INCLUDED

/* mp_min_element.hpp
+TiVJloDB7un0cpvuYLSbv6B0v19OSAaNMcepFQytqw0SEH2zPU2Zga/7TMgf3K8iIaS4x4txxTIsVMl+J8fUbu2EBL7ZfjGzUrbzcN65QqCWA134mU/qq5rNNX1DE11XaOprmdqqusaUV3P1lTXNaK6rlaqa3omFN2iYg7FVs7WovDMxGdqNdYyg/LMY/WaqK55llsoMnm1I6XRqUX/d5mb959VGH+rD9uf51Jdn5uf6vpcpboO3WivrWma6nqarrqexqprgZfh+UDV9RwN1s/4HNX1Wf0OrkjLyzrUOspyvp1g75LbblML8m9QVDR4uG8nLpe06uZ1Z9FKPwD3By89cdVi1Nv6jALoMdLk1tlbYyVpcut0KJL3sTYzSkPFwDLY5+evyZ1na3LrXJrcOpcm9/OxfppcbIV1pDirfL/a1aLJvVrT5J6vNLnnCwwIsgxHdR6aXFoN++vzW6W5xy5do8SmG5NrteElkJT2VhWJaEXCMYSR9bZ1rLel/8oCUNpxnhLR247armvQCQ2m6mmpChZ74VF6ZcTJUtUXV30iVX38fkiPWyn+x3dz6XGNswLOzaXHJ31L0eOEJl41Aj3+0/1Cj9MBmx6/dp/QRyaCGj2e8qBGj2ty6fGUZbn0eCK/M1lntJRYEbDp8UurFT3uvdZu7yyhxy9fOzA9PmtQejwpoIs4Rj+cb/3hQUUJUXvUL8PK66RrIrldGKUOqI4mfkaU8IpBKOEVg1DCKwaihFfslBJy9L2Vs1XcPaox1qIi1MVWzqA8OZTwjx7FEMgoxZbTKPV758OquZZ5rcLkb+lkcA2RwV42TMjjPBKzNXyRpnTYNToZtHPhc/SuFp0MHmUDK8DYFHM5/UdRRJ6hS69RgB6BNJAR37n9aWDLFdyDKBELxanaphLLRLZE/bNDrVjaG79E0qqa12HVKC+yOJOLyF+7WkHz3RwCeDtWiS0rEJIPMLqO0iApAqhAy4PNYAKoETwmgEvonXJyF+Yv7kcAL8qXAF6kCOBFTAAZZBmLqjwIIK2DiQMO2sNfVKSsHhxHeMcOTvrqOL+Qvos+iPSdOwDpG0ukr0YnfX+7irEPfWVa1/ztT2jdv+fn6ANf+iboAwHJEOYGPIOnPib54hk8+6uu030D3uM4Gv6S27+sKcZHaWcAFmiBWowVUAWdBxgNn3NOC7OUWQJ0yiWxDQeKXsn6O7uFNvd6KzaWt4PKA+qKhVZM6CyO9OGp3fPkqURnOX3RwB3JpYlqLwHenPCJvBBJ8Tss+1czFAAnBRhgQhW43YVqPWTueHtOM9Gq3lovfb/B9b2n1kffz3N976710/eTXd+71HiogwIYzzSd06XpYMooaXmAVa85Y8JxnSV8f6qh5nJQ0fopgkBsStOE+l6KrpvC8TBWTKjqKf5zDN+yLeDZAjUHlk0IdxenLq9K+f1YB3/pKoaxCLHq6H6vDuuEPxfXx6P18eSt7E6JExePhpbSEYI48gcITy/+ujJq/vhqbRx/qPe/5lrPaVrPKfI7MypPCDSifywdORsqjA56Z47UI3b7I2kOFgUz1jCaHbpoLcXqs7HQU9FQU7JjV4aE/ecqgCmyJkOpgeIfOF5KHTAHHDrDXX5bB2TA1dxWbe0t1eykvTZrHG2ktgH962704v5/IJd/7douaHzTdiGPafub0t+XwZoxgs2bvfVlEKXjgMmk+b8eONlJdwgn++ZQ27Sy5HabDemFagjzvy+mZT3bkajBdxRym9f10MM4m3W9bCGzrgRSjP5NLMVKV2KBypWYu3F4jKrl2ySSRoyv0WlZrW6VoNus0DXOessWrqrGz7H+fKkNAl8WMx6cnORLn+R/6dIB7C8=
*/