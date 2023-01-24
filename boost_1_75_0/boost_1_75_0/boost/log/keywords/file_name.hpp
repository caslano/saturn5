/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/file_name.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * The header contains the \c file_name keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_FILE_NAME_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_FILE_NAME_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to pass log file name the rotating file stream methods
BOOST_PARAMETER_KEYWORD(tag, file_name)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_FILE_NAME_HPP_INCLUDED_

/* file_name.hpp
dQ3TIdNyN5Y8BOQzfiSbS1gtHsNB8uFt9HZCeWxXa4KflbczYvryz9LNeKNaIzpqmDMebXEA/VZl8ik5Fa8jmeRmfGKxhrQE2MVaCpZ3KHPy1qqf6qXB4YbIc86G6VrX8cc2JQ21oygFtaM4hcooD7/omjM/uWWyeC/+G6K3zfw5D8KbISMEgcGyfq/LfsUZitKuwe8z6OQmGHe3QnBxqnkGO9rJc1BGNPAS4lMtkLfzAyMfzLgU/MAqmUoaPxq3sOfp54t26WRFovCZ95KAxsqWW/iAAoCTc5ghVSNfBocgr6BLSdouaCryYpaK0lyEkLQxO0f6CiLNz1e85tXSJ5+hkoRF7wnYmplRp4jrW8hrwC/RleNKXtytjMoNc2uliqGzYmzBIGLrk/Zj0lac8ZxsVhIfpYoCnM2zIo3jKR29m8MVV3UVvwhDZ1L6i/63PeG6GN6g+I9RrAbbNplYzV6Jyrzc6CpiaA14m0pT7z09fxKTMpUD/pJEMa35hC5vzmR3lAHEcJz54Hkeo/rez2pknastbNiN6JCRZGABsLaD1JtJt3umMeMXVAIsAm5fuUyNH6Ie/KxOkrZWpwd+mmWRK2r2ystXR/EDWGgNT1Aq29OlvNGzMmVcSJtZYN52cddwrq3yFJkmiVT5o8/frEkETdKERMBG+WS6xU2vUAV3ZoaRB5Nvh55Tcn9prR79flzVkORJIIucKh78
*/