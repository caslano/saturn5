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
pQ5AgtpBVGtGW/+EDYXJFUbIjIlDEdbpQDyYCE74cd7cP4KyRE0DOzBGPM74Pjp6Mw9XHWpKnRiYpmqme+jmE6Y6JyBj9EqBI5X32+QB+17qXB40KzHfYzbsZzhQKypLgVN/AqM9Ir9iO75JZk94AkcpD6kpD6qJxkOzY4py1euH0xd/BinmnPVouS0ACbCdv90kyg1KdWgBm3QH1XEI5MSq9mqOtTsf2AkAXWMHT4HNyuQPHbgo1sP0q9YuZdCxG8sST2WtirkxNx7Wigz57dd7Q80oE/PlmAbFRr+1mjXECxvnpGYtwxHKosFqfJy69KAYwVM3g9B2/maNdcmqJpdKC49vlnbrn6MeU5bKU3ci/LVEyjdlfuIC4I1HS7kkLV6dc5b3cmvwh5f6t2Cuxdlj376gVDJTAZUDOBX2t0c4FaVnnKCIcVPW3fHkPP6A9stQIgwSd9sTxRTYsXriN+c3+7AX8QYrfDqukYBrpsTF7ZpSuXN4LQh/nXp5Sv8S3D3UJgZIkUg49iKdhJ89nF0QMV5TfXqDk3VzKN7tTGtXK9/llR+PfiZ5EdoOE30Skb/k/QH39im7K4kUPyYdHv3jswRr6QTcBBAR2cCsetfTZF9heVCLbcQpVMXwBC/7Lfq8rXbbw/8DjgizXp42ojp67mFkVckKgQM+PW9Tj5peSqgJw2fesl/rqqYfjEy8M1Ben4UG0+f/QqbU
*/