/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_INCLUDE_PRIOR)
#define FUSION_INCLUDE_PRIOR

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/prior.hpp>

#endif

/* prior.hpp
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
*/