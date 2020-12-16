
#ifndef BOOST_MPL_SET_SET40_HPP_INCLUDED
#define BOOST_MPL_SET_SET40_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/set/set30.hpp>
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER set40.hpp
#   include <boost/mpl/set/aux_/include_preprocessed.hpp>

#else

#   include <boost/preprocessor/iterate.hpp>

namespace boost { namespace mpl {

#   define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(31, 40, <boost/mpl/set/aux_/numbered.hpp>))
#   include BOOST_PP_ITERATE()

}}

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS

#endif // BOOST_MPL_SET_SET40_HPP_INCLUDED

/* set40.hpp
ewDwB/tdFovFYrFYLBaLxXKpXO//scvdoFH7BXTFkf+f/0/XmzVw/87XKfn/APL/zznq4kR7/Z/uASA/S4XJS9Kp/AIkzz9efoweCnJ4fl+EXvL8x34J6rphQKcNR1vXfW9pg3cerNTzS95+o6D+nMbRBLFKlK3ZdwVt53Qjb+8L1iPP34A8vxLsAd4B+pO37wl6ggFgc/L8XmAweDcYArYCQ0EfsC/YDuwHdqDcQEewP9Xww8nzv8uen8VisVgsFovFYrFqTa73//jxf7Nl7P+1/k/+33Gdsvu/Wv9f4uZYI0+kewC+Lvt/+Vny+v08+ZjG7OcrtXfY2919y+QAcqUcwJsruhRcaecTd9Lw3qnHtS3nXDsH8K6gPh1jKfvbf2GUA4ikHEAU5QAGUQ5gCFif1u83dFq/H0d1/niq6w+nHEAC1fVHUA7Aef9+KzARbOO0f38U5QKSwE6ghtbxaykXcJFzASwWi8VisVgsFovlUrne/6eYVRqDYaxe5/gNAIEicD3RhHw/WIH/H2K06NP1E/UZKT7hhnSj3pYDaC08PIsbw4PGx6jCwwYP7h8W/pAqMnpYVOyQaCHlFAZ7ZnkJySefQTR6xeaHs6MK3/ilideKL+t189ruvRRmc/ta2/GgMe1e00a/sMTn023ddo3Mtwjx9Brb8QHRmruKE0o61ze2LJrS8+KHQnSWjnfKLV7frqjuhU9jJuyb0CrRCg8rHfeM/3b5Yx1jvDPabB8S5n8UXr7FOtvxwCfCSr47dil0rXfeb1+1W+4hRLh0fPXzybF57qcObVnZsfTF52atFKKDNJ7CSXs+Kz2fU5I1t43XW/MeQ4JkqHS8y8LgLYcfeves11/1V1/YPxvmeLZ03Fq/R6PhW7QHl+bmjti4PSlO9vjreytEsL9StPRTiuBeCqGNQhuR0AvEsYj+CjGrj0J8jShBdA5WiH6INEQuokOIQsQjtAgRqhARiCWInYj9iIsIj74K4T9IITLBPMQOW7ufQsxDLEOsRyjDFCIIkWDrbxD6A4sQJYjgcIVIRMxCrEUcR7BYLBaLxWKxWCwW6+aqVvy/SWc0mCw19v/thNJzWyj8/zQh6ogH41SRmRodzjNkxOo0BpNWQK1xzhack2s/J9yAkWda6AzpNT7B4yWT6gpFmdeIMeht12gWVcozzPGCPaYa/0mq8XcS6BNxL2IX+hgt7aevr1KZ1HqzTmXWaawmvSUrWa1Ps5p0tn7uRC8VKru7dC0NPT3AAryWzj5MldExzjtEL08d7dnfHSq3DdT+gtoTqb2H2lOp/Q3aClxJb7oGI1nwOniwPliKyO+KeaRroPdQlWJ2DF8af4c6ogJ5YPzoD+M/eLm0dB/60k4Q4k60L5aWlu5HW04JyWPoT2PYT2NQ0jw2oDGceaPsGEzqjBSdJlWnGWsfy/XnEv043q9UGnOhkK91F2JpU/zxpq2fKHs/5d8wqY+W17jeu+j9aoeg5yD1pdUJmosjjrkoe92J7kLSPTT3bcHvcF7jt+i6Kx5PZCZdt88Njsn2mJIeM6pN6nQd/l3hUWuGRTTHY7YJPd3Y6TGzfB1FV68D59XxTEP/Ce7SvhFx0TZmul6cVmp7bT3Nv30NS6pb9XNqleXmlks5vu37Xt2QM1cVMe7H5Q/uvdz6ZyEypONHFvv7Dc/qeGCTt/LbjxrNDBdii/Q6YxccmK4+0vWvnPO65YNP9IzE/wdpTc3MYWNWLmtxKPjE1raii//bIa7LzVU3F3lKOr5wRtzFTd7z5vu+rVrRcGxIYfVzi2elfTb0WUSfUfMRdRH+QtZEuqdHNq3tmQo2A5+h/Tg5oO117nOjzwP6nJhP/3Za0uc=
*/