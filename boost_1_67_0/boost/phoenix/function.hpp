/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_FUNCTION_HPP
#define BOOST_PHOENIX_FUNCTION_HPP

#include <boost/phoenix/version.hpp>
#include <boost/phoenix/function/function.hpp>
#include <boost/phoenix/function/adapt_callable.hpp>
#include <boost/phoenix/function/adapt_function.hpp>

#endif

/* function.hpp
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
*/