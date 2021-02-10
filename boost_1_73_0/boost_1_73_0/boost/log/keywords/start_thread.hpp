/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/start_thread.hpp
 * \author Andrey Semashev
 * \date   14.07.2009
 *
 * The header contains the \c start_thread keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_START_THREAD_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_START_THREAD_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows enable/disable spawning a dedicated thread in the asynchronous sink frontend
BOOST_PARAMETER_KEYWORD(tag, start_thread)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_START_THREAD_HPP_INCLUDED_

/* start_thread.hpp
7+M/+vE/+lFIW9y4+o96rEeo8s3SWrrIDDwqF/gBqhEgmJpR+d5fgsxD9OKDO2p/GHvj3pv33+/uwb9LPXBSb78vTWTDW2IBfODFhXrX5TudFDftXcAgMd3Pypas0/AtJRFbDXcUMq2LzrGNztFTtfGrRdR5JiamrIWLe9oBP3jJTvqsUGUGCzfWHNAJdF1eR7UQA/oC2ism+7IZsJt/zXlwo3Zsw3YThE8DFiDbpnX322VH40l7cj22jwsb4Bc+jAOg2+qsCjhpRYCNZrcNujK3EhrLzMrSBWpsW8i0yT9cT721/6lENJQdB34YBpwXtR7NoZqTT9YqJsdbBee0fVSERLkjeKgaltUrQg5QItmFiXZ4Bns8wdw5MHWqwCTBbfwxADgpDHaxiMHeLWzMasBH3ffDd12APp543YuL4WhXH5GfhbeBN/M9Xr6lCvigPem973qddg28o1igbg5+MBQoEgjrajOs4wJ0tc2tXacSkFPVYSgCUGe55XOuzVS9pZEvc9ltCYvlZ9eKc78zM4YyL3wsJV0nxQ73+r322OsVpAAapA9PMSupVlUqr8XNpDFVx8Z/5mHScF1Hj+/ct32Iguh6GbPDNF0efYziu8hD/YQ1zai903tyXnUi0p7yXO0fi4ZhvawKzG56
*/