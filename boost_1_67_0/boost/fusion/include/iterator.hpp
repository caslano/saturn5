/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_INCLUDE_ITERATOR)
#define FUSION_INCLUDE_ITERATOR

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator.hpp>

#endif

/* iterator.hpp
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
*/