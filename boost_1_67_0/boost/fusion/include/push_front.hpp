/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_INCLUDE_PUSH_FRONT)
#define FUSION_INCLUDE_PUSH_FRONT

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/transformation/push_front.hpp>

#endif

/* push_front.hpp
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
*/