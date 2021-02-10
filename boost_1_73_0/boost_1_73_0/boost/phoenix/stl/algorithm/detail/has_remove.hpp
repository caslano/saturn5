// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler
///////////////////////////////////////////////////////////////////////////////
//
// has_remove.hpp
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_PHOENIX_HAS_REMOVE_EN_14_12_2004
#define BOOST_PHOENIX_HAS_REMOVE_EN_14_12_2004

#include "./is_std_list.hpp"

namespace boost
{
    // Specialize this for user-defined types
    template<typename T>
    struct has_remove
        : is_std_list<T>
    {
    };
}

#endif

/* has_remove.hpp
0l8eTCOlEeoyEDO2IKJkRsWanroA5OrDHXaKrTYR/CKbfdgudV5JgVo7t08Td/XMxYAKMg0sxzQeVFi7cNHpUVdaPW3DrJYKW+oe+IqRoj6NgG7AgsK1IOvcgTvgvbpXv3NsYVUXdt7qNd+DqhBTdjewiAIhBI45oKvqZ0QfWthcDC4Yv7SKHB3i23toIigbJpAyOUBMKWfYVLWImDUIXoPw+WMoe1lq6iRyt+oGMDiDDWhpAL2nPp8VYMt1wFRfkK57TWNUJeqoEaspQriRGaWoc5tUDJM75YgL9+nr1Wqz+FKF6jBXHuNPnRyaKabQj27sz37N0k68kcaimbyoWaOgKedzSl/p+h7YI16VkqlftX6a1X5AXMWryEdUc0Gv/pCXLhCIQWJHyypbxGQPkGbKht3upvBRUe0d9cyL3ptrHfpcO6yrQlw1UzvD7tiV/TbP7q5TMLwF67gTk732tlb3EXPMFMWKLr5uyQxjiquEZHUC1hlixyWWqfRCeRqsWAhhemRtmnjPWqsymEL1yLIRVbApcn0O8HLnomQwxHf5XeP/Bk0Nv7+GqutXP5euZYxWincCte66qt6zebT+qFajpngxpCe7gbsLz7GKRbLLijnydT5mTRNKbAVxRSCl9pXnRswIsok/qfOP
*/