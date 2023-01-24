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
lNYtoXL6E9rZu44vMlw1q6lslxmsFqyYei8SsWfFHkyVphR3wi/I4+3yblYnxX9qQBUguDI8afRqdjPslKNyDvtM7UzYmBbNzG6yto/JpVPnrhNnjdJU99ktDUMvT1WwETsKNCMqYEklTZXuNtSYuld3UtT0xyLzLGayQ3doiVvXNmha+eGabVRgQkHhIFU4Cz/2B9GD88GeRoZRY8MCgY+gFeEKAWRE0n0ZizezYWO9mekciqMry2eOZiRdeRNYrIG/EXlV7vjEuxp3VcKGaU7ELJVRmPK1SEAed+4dzswXEQn5Z+dg7pzCO49g0W97kDMInlRBNIQMwi8irvOHZNFQ5Gu9jqgRSCeEXGmM/NWdM++Q/MUyg9pdBkoESYfwQbwhuBEMW+JVPkqHRWJp7UdClu4IU3lMR4ligVpl0PI6kBvlPYa67/wc8PLWH4gdsBIf4vziO08qRrW6dyTpKkZ1en9XGf4GHfvLY/0GPcX9y70DAu8tOVLZu7Zuy2bXS5qmvFY3Sk4dkOgdaSebEkv+6Mve9Gxpn6H488Nt9Z4K0PEE1zjTE1CxoG3famvfbNB0rx/doiysQDZgZtGHGihps6zYku/41WHhYZrXMQZx16rpxyo1a4HIT0/b5uWfbDbWTUbcWnuPVDMdzaXjPaw6/imiFW+Ax7zfcNw0mRppUfwe0ddnX0tqeK9PhAIcfu0DuV+2JoJs4bNh
*/