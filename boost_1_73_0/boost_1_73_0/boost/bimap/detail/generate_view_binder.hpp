// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file detail/generate_view_binder.hpp
/// \brief Define macros to help building the set type of definitions

#ifndef BOOST_BIMAP_DETAIL_GENERATE_VIEW_BINDER_HPP
#define BOOST_BIMAP_DETAIL_GENERATE_VIEW_BINDER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/multi_index/tag.hpp>

/*===========================================================================*/
#define BOOST_BIMAP_GENERATE_MAP_VIEW_BINDER(                                 \
                                                                              \
    MAP_VIEW_TYPE                                                             \
                                                                              \
)                                                                             \
                                                                              \
template< class Tag, class BimapType >                                        \
struct map_view_bind                                                          \
{                                                                             \
    typedef MAP_VIEW_TYPE                                                     \
    <                                                                         \
        Tag,                                                                  \
        BimapType                                                             \
                                                                              \
    > type;                                                                   \
};
/*===========================================================================*/


/*===========================================================================*/
#define BOOST_BIMAP_GENERATE_SET_VIEW_BINDER(                                 \
                                                                              \
    SET_VIEW_TYPE                                                             \
                                                                              \
)                                                                             \
                                                                              \
template< class IndexType >                                                   \
struct set_view_bind                                                          \
{                                                                             \
    typedef SET_VIEW_TYPE<IndexType> type;                                    \
};
/*===========================================================================*/


#endif // BOOST_BIMAP_DETAIL_GENERATE_VIEW_BINDER_HPP

/* generate_view_binder.hpp
iWAWhnPcz2VJAjyPYryKluH7xfSv1TRaIhlBnEJPFHrGnjjIaiZNhm3geef4sGvc+wbDIGWWPZN3Fv4eTtY+vLg9IZs3LNRLgqrhUUNG46hfg3qwyRG7qevghiPQOOfJ34BvgGuttGnT0TeE8N3RaT3v8COUVRrNmnVx22EKCvE1Rw8yPK15+hp+MPey43tf/oydNGy1oyWu3klVo2LH9gaSgjNZV18L1bxomwH4TKkHfaGL5fUQ8Mr77P0DUEsDBAoAAAAIAC1nSlL/ngWfeQMAALYHAAAlAAkAY3VybC1tYXN0ZXIvZG9jcy9leGFtcGxlcy9wb3AzLXJldHIuY1VUBQABtkgkYK1VYW/bNhD9rl9x8zDMNlQpST90bdxghpNtQTvbsB0EAQIIlHSKuNGiRlJ2jKX/vXeUNbvoBu9DaTuUKL737t4dlXj47UYAQzg5Ev9LaNDsEXOj/8DM/fvuJHmB9kOoR5pPicRwgLwkAzgNeYG+hyR7lRFfJ8kpoUeOjf/EjHxM+JJWCMbIia53Rj6VDvqTAZy/ffsTvIKLs4uzEK5FJVHB0mGVonkKYZT7lZ9L8fwcWbwKAR0IFe2pVqW0YHXhtsIg0LWSGVYWcxAWcrSZkSndyApciVBIhTCZzR9up7+GsC1l
*/