/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_INCLUDE_BEGIN)
#define FUSION_INCLUDE_BEGIN

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>

#endif

/* begin.hpp
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
*/