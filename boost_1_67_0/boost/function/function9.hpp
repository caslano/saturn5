// Boost.Function library

//  Copyright Douglas Gregor 2002-2003. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org

#define BOOST_FUNCTION_NUM_ARGS 9
#include <boost/function/detail/maybe_include.hpp>
#undef BOOST_FUNCTION_NUM_ARGS

/* function9.hpp
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
*/