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
HqZ5hoFvrPFTati/aUf1PoHvvRtQ7eulv18BXPu33zWuLZH8FAvxa8lsFQO4xeIdIsYEGcC9YERjgTzlbS6fyT7NDFr7odO41h6zVZvWQDiuesY38iaV2b58CIkgkd/JCRg9fg9r5O/qqIHbIbaipMuMRo+Tgz4Ky45+cB+m1SxZO+RJRjf+xehAgUnC1hXnaJ8ytpyNsdEIL7MhsuHYcqIIepVThO6Uv6awTD0TjORUAFfJ27gV0kRYeLJ47EBy1XlDmvxHWoo7LmvG5c4xlbDggp8KSY6qUNbXRKLcaC8zG6v6493csuq9BAuRBbgThsqQJGLJqewPeJHvGxRZlOlUhcVReGPV3wZdRMU1Vxh1XoIz0F0JecNFQDOgbvTkkwqONbHi57SKM5SeWLHdmnZR75Vmy0OEzHquh1Pz/Z4nVCmKbUsWQ07ArkMu40BlKKtn8TCPWN8NQkzk+MomMNrr+/fab5EGNkD+IFCwaR54w144QDhCxQHv+5BZNzJR3Nk4XgVJfi0OeBN7yT7n+G2/P4pZp8dlJ98TN87dSxrDRs/lu67cmXLR3RHNaHc+akYzWieY0Yqsj3Dvuv9+lDeFvTaz9f9Bcagm0Y2fQFd1PFQJI/CS7yLBFwLQckAgKvL/FEt8zN+Dnrf3pOdvPUKd5fDDN9g+DPytlXr4Bgvis6Uod7NFvOIQ4wyc+abv0paPXbeB3RBKAl1w
*/