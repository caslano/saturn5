/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_INCLUDE_REMOVE)
#define FUSION_INCLUDE_REMOVE

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/transformation/remove.hpp>

#endif

/* remove.hpp
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
*/