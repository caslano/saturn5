// Boost.Geometry Index
//
// Copyright (c) 2011-2013 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>

#ifdef BOOST_MSVC

    #pragma warning (push)
    #pragma warning (disable : 4512) // assignment operator could not be generated
    #pragma warning (disable : 4127) // conditional expression is constant

    // temporary?
    #pragma warning (disable : 4180) // qualifier applied to function type has no meaning

#endif   //BOOST_MSVC


/* config_begin.hpp
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
*/