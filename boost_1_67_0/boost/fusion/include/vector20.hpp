/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_INCLUDE_VECTOR20)
#define FUSION_INCLUDE_VECTOR20

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/vector20.hpp>

#endif

/* vector20.hpp
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
*/