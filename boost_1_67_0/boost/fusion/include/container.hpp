/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_INCLUDE_CONTAINER)
#define FUSION_INCLUDE_CONTAINER

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container.hpp>

#endif

/* container.hpp
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
*/