/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_INCLUDE_FILTER)
#define FUSION_INCLUDE_FILTER

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/transformation/filter.hpp>

#endif

/* filter.hpp
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
*/