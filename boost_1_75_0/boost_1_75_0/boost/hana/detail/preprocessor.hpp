/*!
@file
Defines generally useful preprocessor macros.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_PREPROCESSOR_HPP
#define BOOST_HANA_DETAIL_PREPROCESSOR_HPP

//! @ingroup group-details
//! Expands to the concatenation of its two arguments.
#define BOOST_HANA_PP_CONCAT(x, y) BOOST_HANA_PP_CONCAT_PRIMITIVE(x, y)
#define BOOST_HANA_PP_CONCAT_PRIMITIVE(x, y) x ## y

//! @ingroup group-details
//! Expands to the stringized version of its argument.
#define BOOST_HANA_PP_STRINGIZE(...) BOOST_HANA_PP_STRINGIZE_PRIMITIVE(__VA_ARGS__)
#define BOOST_HANA_PP_STRINGIZE_PRIMITIVE(...) #__VA_ARGS__

//! @ingroup group-details
//! Expands to its first argument.
#ifdef BOOST_HANA_WORKAROUND_MSVC_PREPROCESSOR_616033
#define BOOST_HANA_PP_FRONT(...) BOOST_HANA_PP_FRONT_IMPL_I(__VA_ARGS__)
#define BOOST_HANA_PP_FRONT_IMPL_I(...) BOOST_HANA_PP_CONCAT(BOOST_HANA_PP_FRONT_IMPL(__VA_ARGS__, ),)
#else
#define BOOST_HANA_PP_FRONT(...) BOOST_HANA_PP_FRONT_IMPL(__VA_ARGS__, )
#endif
#define BOOST_HANA_PP_FRONT_IMPL(e0, ...) e0

//! @ingroup group-details
//! Expands to all of its arguments, except for the first one.
//!
//! This macro may not be called with less than 2 arguments.
#define BOOST_HANA_PP_DROP_FRONT(e0, ...) __VA_ARGS__

#endif // !BOOST_HANA_DETAIL_PREPROCESSOR_HPP

/* preprocessor.hpp
ptP1F+WzAxpg+3xcmGkGSSxtwnJaGbMb/ZjJaKYHBwDLTYPhxCw6XGq5Xn6zUyNXS1YVSBXUTm9GeA6LBjrodroTzuKrMQv8bA1HeqaLbr0T5wAzB/3XlbI81FaotY0Umel1VavsrzDnLAN24rYFly0XPrlaCGYYg/4VZrwruMhkbMV7Dl97b8Lbqw8kwWD+UfX0CpMtWn01tysRiuBeOm96Nvi5yRgd/ZHwcNTkgJHnaNiIB1CLzMDzI/DeMDUb6/16XqDeDpnxPfRAIzXsiNvTMh8tLJH8Jy/aokaXGcJtOn6mR79Bl6nTSW88gGc5cOP5ENrpl9Y/TW/HSWtXAZwkljE3JyadF686vI0WdJv2oJVea0fTwYMHlS3sSXgzkrjNxAijepK1g5ZHL9tzwFIp65BFKKzYv1H258si34se6ubgOHOnSXR2Cmf1/I2k0uS/3QQM3o3+GI1+n3RBVb8LpPGTmCbQbO1QTBSATrsck9BoOFP5d1MLTQq9XEdTlbTgkSid9JeJuL9Fmvv5TtSG22z7xXET28r6P7R2rBNTaWZWucUexcgtdlxX1Yk1EWFQ9i4h9l5HHh6CmP+G/74ZoDgUWAOpiaBaX/UwsHBRwF81AALOHSFnYSx1RoUjAIwKD3fr0eC1s5M/BFTx6BiOcexc/koTw43iWSzZJtJTR1jBogFAsFW8TVxsJvboxLb+D8vyVSxtzdVL
*/