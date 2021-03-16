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
2skKdl3hyjRkMcZNA910gaDSpa0KkubfTwcWCGjJ8SDywBEiD+jV5HNd6fJA2zR5YKh0jLr7PcV1kFmDmOvPZw1IDuhB1US5nGtLXcTXh6mu8L2ZnlDNmTv18knzyqbOnTBv6mQKag5+SK6anlU26RKxLEFb8dsxTUd3sN6fWUej7PTlLHW1jlPvKlr6zGWvk2ZeMmGSrFOOZW4QmrNuzhSG5SxW+zJXyFNNOEzjWQta4p5gVsFJllnGIXdbXZI=
*/