/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   functional.hpp
 * \author Andrey Semashev
 * \date   30.03.2008
 *
 * This header includes all functional helpers.
 */

#ifndef BOOST_LOG_UTILITY_FUNCTIONAL_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_FUNCTIONAL_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#include <boost/log/utility/functional/logical.hpp>
#include <boost/log/utility/functional/in_range.hpp>
#include <boost/log/utility/functional/begins_with.hpp>
#include <boost/log/utility/functional/ends_with.hpp>
#include <boost/log/utility/functional/contains.hpp>
#include <boost/log/utility/functional/matches.hpp>

#include <boost/log/utility/functional/nop.hpp>
#include <boost/log/utility/functional/bind_assign.hpp>
#include <boost/log/utility/functional/bind_output.hpp>
#include <boost/log/utility/functional/bind_to_log.hpp>
#include <boost/log/utility/functional/bind.hpp>
#include <boost/log/utility/functional/fun_ref.hpp>
#include <boost/log/utility/functional/as_action.hpp>
#include <boost/log/utility/functional/save_result.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#endif // BOOST_LOG_UTILITY_FUNCTIONAL_HPP_INCLUDED_

/* functional.hpp
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
*/