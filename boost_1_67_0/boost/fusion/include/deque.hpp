/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_INCLUDE_DEQUE)
#define FUSION_INCLUDE_DEQUE

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/deque.hpp>

#endif

/* deque.hpp
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
*/