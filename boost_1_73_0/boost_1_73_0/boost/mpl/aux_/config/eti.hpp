
#ifndef BOOST_MPL_AUX_CONFIG_ETI_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_ETI_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

// flags for MSVC 6.5's so-called "early template instantiation bug"
#if    !defined(BOOST_MPL_CFG_MSVC_60_ETI_BUG) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && BOOST_WORKAROUND(BOOST_MSVC, < 1300)

#   define BOOST_MPL_CFG_MSVC_60_ETI_BUG

#endif

#if    !defined(BOOST_MPL_CFG_MSVC_70_ETI_BUG) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && BOOST_WORKAROUND(BOOST_MSVC, == 1300)

#   define BOOST_MPL_CFG_MSVC_70_ETI_BUG

#endif

#if    !defined(BOOST_MPL_CFG_MSVC_ETI_BUG) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && ( defined(BOOST_MPL_CFG_MSVC_60_ETI_BUG) \
        || defined(BOOST_MPL_CFG_MSVC_70_ETI_BUG) \
        )

#   define BOOST_MPL_CFG_MSVC_ETI_BUG

#endif

#endif // BOOST_MPL_AUX_CONFIG_ETI_HPP_INCLUDED

/* eti.hpp
AAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MjA1NlVUBQABtkgkYN1UXXOaQBR93xn/w006zrSZ4mpa05SiM/iVMDVRAXX65CCushFZuruk2l/fCxjNtP0D7QOwC/fjnHMPa2mmdBgo1iYWT9YCH1t2+CHkSrXJve+Pixvc9f1y8cg2QvNAMwgyHcFbpbMlbOWy+Y5Y9Jxp0bLYG/CYfGbSUHzFiCVZGh/w64VhwIBLpUGy7xkieA9sn7JQg8rCkCkFPAGRMFCR0GAYmLIKdNAoIdFGrQHX9Tr4EU82CgLJYM0xGpNU0Q7iIFmRsrUJDzyUQom1NhzHo59qddIViWaJNvxDykzQbK9ppHfxFwijQCqmW1wJ4/a2+dlokPl8btjIFeN5iMTNVxq4dqt1KjZkyUZHJjSahDzy8KiQ4vIC5TjCL2iEEQu3/zaVIwWLHieKg+7GPE8tBx0WGwwoSbRJpHWK4S9bKwl2rP03Sx2xcZH8Zq4yw1qzQGeSocfuPM+wxw6JV4tUslgEK3KxYstsg8HnKESAlJ7bZNhbjN3+cGT3WtXxvEdjvsy9T2u4UPku77ZRqqYE6U7d4cLzp50FNll03X7Pa11+dTvNhR2jHJcFk7KsFYrdDkfUJkZmolWTE5uc
*/