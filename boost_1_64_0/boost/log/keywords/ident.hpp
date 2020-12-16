/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/ident.hpp
 * \author Andrey Semashev
 * \date   22.10.2012
 *
 * The header contains the \c ident keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_IDENT_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_IDENT_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword for passing process identification string to the \c openlog call
BOOST_PARAMETER_KEYWORD(tag, ident)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_IDENT_HPP_INCLUDED_

/* ident.hpp
f9t+2iz1Qw0RP83NnC2zLix+ZVVYR5x6ie50wtPwWZ96DsXprK9RopOEjtdPQ9m/gfdLwywN2/gjePGXisvXEre1VsgayjpmO0bCucnMq+jbjj4aeQ/PmyJcj3vpulNfj9vU51C7ROKmdj51bVrNu8A6qS+E5RuI/MYjlecg62qqk9JxyurvIWv4a9vcLf7HWK1dbWto+FpvZlIRqAOE5+8XPtYyc6unTr86bn/5FQv9fr+S48mufaX6NWNISpMivyYFl0EcJO64SdwD+w+NkzOvcxqE2vP9GXmdcXutec2cT/e8bgIzbf8cjXOfJ0b4dbO94kyn8zobp0aMPlRPh5HniH9O7fFnDuQ8rrTh0zBCwugYrr7oOShVf31ZPptcd9piuUd0buT9WEPmaXNfasW51h8Tlqk/hKV9hs/OxqOis4Q+ohHfExN499fArT4Rlus9gbEhcJscX2eNQHuuxTOMVd/tuks44a+7LbW/WSw6T1mL+f895DHE5ZpLWDVfc0vl+FbXa67T77nSny8uvMJxzV0ix5/U9lM3u5bOepUa2H5MWaY625CWi7kOB16vT/k6vF/rcQ/Lby/xTdKat77WekxnuzRsHc5fX2MdJvx/Tt/jbJMpaqtwpnqagWwiLZtrTIs2R/OM4J6eLRJGF9LjaquGc0T+3ICuW70yzw375HgPeW7ohKgtBPKo7s8OJq/CPzuYurC6sb47Q+rpt417iF/Ghpryb6ldF4qphcF555pPhGXSPrWJd56ZM5/72MdJXVM3WyVB/j+R8Zd2JPzr6HeW41OsDP6PVb2/tOKA2PD232tNFr2zKU//XND7CeBepH87e7v2OWNyz7LB3LPUmOekVeaVBd9zbErW97MEkgDbwPV2nd1g5ue55HnBorrcBxOW232wmU/8uBz/ocy1vghRWw7q70ITlrq53eOa8vtYw2poXW3C+au47XfaZjL3xDl32MeWm/vdZ2U/Nmz5vi9hvS1PbHvJMb0/56f353r9myrhXIQ/9tnKlf0FVgPcpnP9kefD/upvqd8u1RGNawtawKvE2KXvl/DjJbxR4cJ3uwc39/Bu99kcE3uhtg3mNbTD/U1Iq9hIKb0bU2OJnhmJDCWw3G0wq58T+PnA9lO/tCLY/lNH9uO0D8mmfg/Qeap94Y/ayL069kZrty8a6X15qvMeXNOp7pJOuQ93pN9pc+OwvsQ/gniQPyHn2+8wflRDmxCzG+H77w62X+m9o9zaCGEH999L7FO49kHouvdhWjd+I8czeQsQ7XqfZPxrPWBMe9GseUvd7oXQde/vzpL2ADlut4cm0lJpechuJKhdmHuwsaK/3cog1fnkxY8Qu/5sTqZeEPmB7Yhj4sAQW/I+ey7nar0Z5OBceJ7uN4KNkcHIkqa12/6s/Tol5WCeJ0w/6rgPkrqkeeicM1Ws9hEf0vNuRcbZc07LffVIao7aO5pZUDy/YGHBkllFM7Wuap6ja6u59q2E5VoXQuuNiy7tnzP5+4Vw16rZ4m8l991Rwc/fZs70BaJzh3UNdU7tusi17D7Cux9xXtuubCr7sHa7Lr7ysfOhmeSD6zXNPHOLm6bLOTckRe2fTadSdYVD4HC7Td/pL4uCK2ZS1PZbJcsxp7fYnmQr15IdhN9X9LM9vnbdRfaP0lZecy0fwjfPEstjfOHJw7+EuZMwh4pON4/vHckA2W9k7vMb32Xvx+k+b2Nk3309AM5nyvhj39xtPdd2zjVOjrcz5zpf9t2fp5xhUcclLGLu2k+obnCdNXWopxzv7emJi8tzEv6D57/RN0O35yKn7nSZ0E3Rqe4uc31TdzvCeqyCY/53XxSDo/4OlzBbe1paTV3reAo=
*/