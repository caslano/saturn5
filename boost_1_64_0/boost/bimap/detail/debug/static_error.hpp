// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file detail/debug/static_error.hpp
/// \brief Formatted compile time error

#ifndef BOOST_BIMAP_DETAIL_DEBUG_STATIC_ERROR_HPP
#define BOOST_BIMAP_DETAIL_DEBUG_STATIC_ERROR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/preprocessor/cat.hpp>

// Easier way to call BOOST_MPL_ASSERT_MSG in class scope to generate
// a static error.
/*===========================================================================*/
#define BOOST_BIMAP_STATIC_ERROR(MESSAGE,VARIABLES)                           \
        BOOST_MPL_ASSERT_MSG(false,                                           \
                             BOOST_PP_CAT(BIMAP_STATIC_ERROR__,MESSAGE),      \
                             VARIABLES)
/*===========================================================================*/



#endif // BOOST_BIMAP_DETAIL_DEBUG_STATIC_ERROR_HPP

/* static_error.hpp
0geSzpUcJMRkQbd+yRIDwuguoUQMA1QeGht7mOgM6jkEPnH4wOGDSEPxI61z/UC6EdsnYvY3PbeqmB6kQlIVXC0ngOjigI13xk5IyYE3Sac3Qg7ckDNKHKt8yW0MoX8eTraELVFx9myLsiqPwivZeqVr9BcagNhXNy34dgpE69NvbkHvkdhpFpdfxcdDX2JgJhO7acbxBicv5p30mdlEI0W43r8mTS3Vxcgev9XcbCiiu2NXwzzdl4OVZKIpEDxeUSP37WSc/bUtl01i6CcgqyT2k2OOlQBKGNe+TKi8BKregjXvuHqshnCc4smesviWGVnncS43NeAqVS2Lq/FJMIXLabiusd/pBdvgs+Q/SBlk923usVHSdTfnEf2EposWmehf8fJIB1NtcDMNNIA013Df9Au8sYd2/vXoPDxuujOoaRiEg8WP2BlCFX1SN8/H2J7iSDh5Z5j0rKMQK3/ivK/HGAP9aypMaTF+tusxiHG6/9APhg38ZI8nZ7RqOjKM6RppyTtLazcovEDP6hVm6Lr6N5k0RPE3UPcv7RQU+BwPHXZp/SHhr0XDZg==
*/