/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_INCLUDE_VIEW)
#define FUSION_INCLUDE_VIEW

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view.hpp>

#endif

/* view.hpp
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
*/