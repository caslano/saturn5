/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ALGORITHM_QUERY_10022005_0549)
#define FUSION_ALGORITHM_QUERY_10022005_0549

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/query/all.hpp>
#include <boost/fusion/algorithm/query/any.hpp>
#include <boost/fusion/algorithm/query/count.hpp>
#include <boost/fusion/algorithm/query/count_if.hpp>
#include <boost/fusion/algorithm/query/find.hpp>
#include <boost/fusion/algorithm/query/find_if.hpp>
#include <boost/fusion/algorithm/query/none.hpp>

#endif

/* query.hpp
+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
*/