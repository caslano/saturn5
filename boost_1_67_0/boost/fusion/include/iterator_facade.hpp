/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_INCLUDE_ITERATOR_FACADE)
#define FUSION_INCLUDE_ITERATOR_FACADE

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/iterator_facade.hpp>

#endif

/* iterator_facade.hpp
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
*/