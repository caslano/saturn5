// Boost.Function library

//  Copyright Douglas Gregor 2002-2003. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org

#define BOOST_FUNCTION_NUM_ARGS 2
#include <boost/function/detail/maybe_include.hpp>
#undef BOOST_FUNCTION_NUM_ARGS

/* function2.hpp
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
*/