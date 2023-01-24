/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/message_file.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * The header contains the \c message_file keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_MESSAGE_FILE_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_MESSAGE_FILE_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword is used to pass the name of the file with event resources to the Windows Event Log backend constructor
BOOST_PARAMETER_KEYWORD(tag, message_file)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_MESSAGE_FILE_HPP_INCLUDED_

/* message_file.hpp
vQCJHyVb+15QK0B7kByppomMKAGE54N5jMSGoFLZgTeQjiC5gfspDpHOBYVYf/oIrnXMKTNBaf7Rymt1RnMCW/cvn9MMYp43LxaeP+L+iBQfJlXS9+pyTAC8eQnb3Ui1msdnKrvt/h680+YWIOes/rljYcB5ootUXpRxzFH7eU2JJsNtYkSP3k5QO2DEehDHumAponj6daSMgm9vVC6LK4VUXEJzzMpbqnE06OBHiPxaRkQ2L31H7P6XsASP8x/kdlIb0h19XyyGZBYCvbIz3AjQhqeL20YeqMWSzDy6VzTjU2MyMrwu0pLlrJwQDwloCMY3X2Kf8kk05ibe88/YC2K4iJoPhKsPJfgOKdAGPvAwbrfr3/bQ5O/+bLto0/nkgDMo3YvAzEHKRTcgYRq3sy814cCHqpSL11JzF9pAkXjWmBQZ90SwRiJe73S25Cxmbhi/FThE2cg5sadT9TPF3OUXA295sNSsQonPlIB/Vw4f4R1SZVAi93zMYME9XYG6TeSqZPBDf/wzaVdiPp8Lw6zPsdzH2UNnuwjye17Km8XXTNLMOL/u5vvsooSAcovZuDvppHLRYxVunh/7jcePpX+U9x/weNp+Rq/o2nwZYnIODNy7qaioyBThzEY394zRBUTHvHYKIYocolskc/uG9Hf92vFzdo9P5jTomryQYTFtmQ8Pv7hx6Hfwwxu3ygANEX8xH09B+ak6/uH5
*/