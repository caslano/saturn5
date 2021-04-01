/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   common.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * This header includes other Boost.Log headers that are commonly used in logging applications.
 * Note that the header does not include any headers required to setup the library, as usually
 * they aren't needed in more than one translation unit of the application.
 */

#ifndef BOOST_LOG_COMMON_HPP_INCLUDED_
#define BOOST_LOG_COMMON_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#include <boost/log/core.hpp>

#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/sources/record_ostream.hpp>

#include <boost/log/sources/basic_logger.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/channel_logger.hpp>
#include <boost/log/sources/severity_channel_logger.hpp>
#include <boost/log/sources/exception_handler_feature.hpp>

#include <boost/log/attributes/constant.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/attributes/scoped_attribute.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#endif // BOOST_LOG_COMMON_HPP_INCLUDED_

/* common.hpp
djV5w0YLTxqkx8VROc2lXOcYn7MDs/pOD4Il5/nbRkQIhGwutz49KI1ZgJA63Ajd9YwauKkC+vy6/2C7+AkyX02O8sgSKTikoi2iStWhG6Wtxas49gcSrlc9fbGYxDX9BpGoMRDc8sInAXWCNYXQNZQNJcjWFFFuYyk8VHClyn26BHXc+mgMpwoLivL2Xl8t2qJ66e+AswlJNRBqdArM+TayF14AQVOdk5WOKPyOLHaUeEVky7PxDXeqpKHNAdg72LgRpLNKq6PqOEKMUEhYEVIS0GHAIsHAe+k79cx35IYUcFNoSMcOrwmEh4vWqxNE05vydAnrguOZ8MpcStnUDmyhs4PPEKKnWi2YLKElTcbMPskPz8ieqN+9TAo6+8fCT3kpGBfJtlldJnyJuyhTavca/lVkBinGgvmL3tmjJmR88cz5qnBpn8grNNZDyV1NCcIJvIUyiKi3vUiIBuyDtHc+sQTtbkGqwd1RmQfO6m2AQc94AIU9b6hcPEMqBntwrrRTRy3cpFaSzNjJ610QfXjTjHF5oXB9fCedGuzyyqOGxobZSYda/76lVw==
*/