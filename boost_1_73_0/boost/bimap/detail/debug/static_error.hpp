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
UxQc9pJn4x98KjwoTuN3PomL0EBKxVuKVwrRM1FqB1Bvq/oJm3kVtMqoiGvZ0GijpbL7PkIbyz7OYlC9hd6Obd7JuAUf4798h/t9udGbdP5xJtN2+qMR6Xx/c5i5mTutD0f3SAxus2ZRrYVsQ5S3Y3CkBXKVnvZYGOYu0oMTsLOGJOUD2JbPR22/4wx0v3RFrws1u4aN1+p+xh8q33fg0JHBXsPDwnahkdhSPCaekCqRDV2K
*/