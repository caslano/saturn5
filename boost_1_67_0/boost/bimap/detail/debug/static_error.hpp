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
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
*/