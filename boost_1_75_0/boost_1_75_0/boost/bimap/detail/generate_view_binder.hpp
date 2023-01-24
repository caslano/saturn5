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
uModEOu+NndAC3ff3AGt3fG5A1q6e+L6/hYUZDM/Pw0hrqtmeP4Gq/wMq9zht+Vils3W/B5haoc/ulNDXBSDWu2WteAC4ya5KZdZC/68SMdHtgFvc4wdNaoV7MUK6L7qNszIxO5LBDArtYwD7yTUFrwjqqt5i1f3rJGLbRXKnywX3ErKxUyMiqoGwUVA//YqSRRbJYrdpVWeroPCIaAofotDcY2Wce1IkdHTmc7jRW1R0M4KY9Veg25wrQVnLjAsDLjZWvDrBaiWYbqfqPY7g1rtQyO19jdfCEDjCqyAofFjUUHdm7yCl7UKnsEKaiiUxQXegZ2Ysczt5pn8mRyFD1zguPgYc2xyj8CKF1PF7jQUfCuU90YSMpMugAH1rDAp5YL16afOs2W24Ee3iXHq6jBY39Uwp4kaixvNN3iG0QG24+PjYoIMyEGb6uvTli3cjmv9kCHDkfQjKARhxt+izvjUuUkwzZmszaY4WyYAeOUNjvobtOm9P6m0Og6/bhVfYbeamwxTLLmlx5SanOgJl9h+saDUJf/Fus24QA1Ec5igo+RPGYHPNTjy/e7o/tOsBcPgSP9afxWYZfRnExI8ULH3+SnwnEG+edHBOEzJdqO0kWhn5LP/5je0aVkIpqRXsYn4ZAfJus4srTJczp1QW9/aMPlyHInWb/AhvptmIxvFyTtoO+K3xWBlbBdzcgmOrzX/epyQ6piJboBe
*/