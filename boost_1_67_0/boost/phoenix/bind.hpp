/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_BIND_HPP
#define BOOST_PHOENIX_BIND_HPP

#include <boost/phoenix/version.hpp>
#include <boost/phoenix/bind/bind_function.hpp>
#include <boost/phoenix/bind/bind_function_object.hpp>
#include <boost/phoenix/bind/bind_member_function.hpp>
#include <boost/phoenix/bind/bind_member_variable.hpp>

#endif

/* bind.hpp
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
*/