/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_INCLUDE_AUXILIARY)
#define FUSION_INCLUDE_AUXILIARY

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/auxiliary.hpp>

#endif

/* auxiliary.hpp
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
*/