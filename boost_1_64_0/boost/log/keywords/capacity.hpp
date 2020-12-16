/*
 *             Copyright Andrey Semashev 2016.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/capacity.hpp
 * \author Andrey Semashev
 * \date   23.02.2016
 *
 * The header contains the \c capacity keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_CAPACITY_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_CAPACITY_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to pass interprocess queue capacity to the queue constructor
BOOST_PARAMETER_KEYWORD(tag, capacity)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_CAPACITY_HPP_INCLUDED_

/* capacity.hpp
if0ThOd2+9qUSVf73pp1Yj/Hf5x9Xz3urW29GZc8KPbv+gbj6mHGeCW+qbb8xR/Lvhrdn7NV7Kb6Y+3F2iT25/r7ITu2/YPZvD0vPBP83ZwM4RkoOTLNXXw3bfecV2Ucata2/vla4J4xzz6aEnfRJVPTfrHwX+c7A81uErbQ/hnh2RjNo2sv5Knn/v+28p2ppEN702/oLmZfYHKf7fuyX2Wv+H207ypnoW3Pp2k/EsSvFhrucHfWcFt4POE26XWj+FtkC7M1PNka7gDfR/AVOG8gRdOpM3PMXqLQ/qH90N90H9GnoEvf6ftZhPlm5b2vvaxXGbOrckL7JRfp3qJbcxq+vyhhe3x3nkauf6Vb9hytM/uLNA/NPqTwde/1EXzZYW5NWtrcw4t7C6/3Do01hF9KB5QKzYc+wqxmu6mDzF4mDnlNZKUtrvVM3JvyO1jaygozR/e62J1vrT/UnXXNcofYTbfupc0B3xb7s2UEp/0R755dZCCeu5eatGz5utnfYF3TbK75TBgwqwhLz5ohRqeVPIfpXoIpr3vTs5hrcmbS8sqcua5Z1nkfBO4j74OQBWtLGtp4py6YAVrqWcOr671m3cPfJf6+ytcx72whjKYMqJmGxZtmicfY06w6PM0CHeIGpFl1A9KsugFpVm1Js59l/WfSbJim2V5V+pjqc8MPgQ5ptun18Htg55aWl0+dUTpa0s6JPZb6o7jr7+TZ1xXw19ovMHuWM97AnhZ9BKOSNfgRlcYWPxz84JZ/M3/bVvy4xxmCH9fwVW1H1O9iBy1i3nGXmUd2xP5Z6rAE53f1rFl8KmHw6xjQ53wj7y84C/m/Dso2dUtYypn+0wr51pHslW0q468UZLfX0IbNC2SBX8h3k2OFQ/xedSxr3UO/39yAG66ioeFzA6NirVUof9XQutcqdM1Q2uABmfLNsD2+nx7inZamjo24T2jdcaGzuD5oIPQX3Gf8ych6aDhTYpfxNmBr4e/n9LHPF6h/voh0jf9e2Fh3Nnf4F3tnAh5VdQXgN0kIIQkQQggBggQIqywBWQIihFVWDYgKyhIgAYIBIouGqjUKWmwRUwQbBRUVFC1qqqhoUVPFSlu0tKJFwZoqtlSpTREVK2r/d+bMnTczb5IJdP+YLyf/e/ede9/d33bvubrO3UL1VIRUo5vnj//S/Jmzli7qxRTDJUVh58Lmi34rt7gTVlD/RTzc+zqj67pm5fVybBh9cax5N/GquNXzjSvmJwvVmmeteXI8TfdVH/+aj+RhrWtf1zp+SPpBb5oId0CT636n9jc7BV5LJg/VusLBWNgHNs4mvwPyms9U9nyCpYWLF5lviZLfAeOdP/PWF4/ruwCXPDRjd+TY2Z5w3zaSDvjzs9i73m3A8RVyPD3se8m35Xh/Wa82g7qVk6PvzxPiEqMn1jwmF33s9On768TmIW1cw8ROH8dtnehCeTfUg2BrCnMn+g0lzNJSl3fionM0x/ddpfQXEuiY2uOaNNTbJxFulev7SmmnkY9VGOO97uYHzwneNczSu03ckSuRL9Etfdtfb/i2GfIixeWdkulvnhW/2fTx9dzaLGFH/j4J3aD2LY+q5tp5sxxfYJ1NyKOtKPc56+iY+xZtl40os8Z1GOtR83upoPsWjaOzfe7RNfvu0758s68vfydw3WFu94wxiHDfj5uJn41WP/4Xu/bpGq7aUaikjIuH4y71+kqGfdRL6GkP3UkL8z0Qt1g7DPQZi22ud280sal5FsF4yJB3mZoXpS5r+cXRV1W941yvcTj5SlWbM2tZwfD5iwvnFCx1rjMZm13jPTBhnfr6foSt96iB8S5xWd8vHt3q2uItK+BFFu/qdyJf/64=
*/