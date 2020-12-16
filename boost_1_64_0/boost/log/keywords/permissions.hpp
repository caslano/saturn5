/*
 *             Copyright Andrey Semashev 2016.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/permissions.hpp
 * \author Andrey Semashev
 * \date   23.02.2016
 *
 * The header contains the \c permissions keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_PERMISSIONS_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_PERMISSIONS_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to pass interprocess queue permissions to the queue constructor
BOOST_PARAMETER_KEYWORD(tag, permissions)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_PERMISSIONS_HPP_INCLUDED_

/* permissions.hpp
yohQjvb6LBJnyRelPi9At/nmDFt99qhhGWlof9Hj5F7F+4waJ22QSX7kp8dJVkLgWE0FX1f3r+G7fJxxnJFe+yw3q/QeMsAr1+zTAX/wuKyttPvkrFH39+Z+VmccV3lTiGNFfy8rLXg8a9mvUumuws4QL7LvHM/HZ5vnvpQI+od/XCMXGetde6w3qzhpa5Ducntpm51qcyV4h2+8T+nS3d71NV7DWNft+VzxFtPmjYjr1OdKFTfRNdg6sHNO4Oo7FWecR6U8+xkm+FHbyniuM61rC/Iz6FbSi27t/ugm3Qbx76B83TsHs5q7/T6yiud8azvata812ujLY6/31p0+QnWeWuN5KvA6zvOK97ZDlb88abjW8hrp6mllusZah6k2zBio+orCF5gTT0+XOOk/JwjRj4j/Y31JncEietB9KdDHXfu+I0PitQz1mS3IhHglE3jZN2Q75nu17vC46kYcqI8J7o+yvvtlmXtfgu6ibi2HdfXHgzxVLHcL7Y8ZMg+cpXiftJLoWZnk/iD6M/U58rT3Of3b3RfRJOr7L6P7/IC+ptPpvlaFNLr8Vq9Q95fAG2/dwL+m/mfP41O11o02VdAG6QunqfsrSMPvJPSULk/3Gz3WlineVuzkvWw89bXVU73aH/hxxZNjbcx/m6g4ns4OJ476bSLtXaF4Tg+ek6Du6EciW3s/UnIL+m0T/W8pmQ+F7ibP1sO79M9mCs11ofrX607mK97NjDonH7tPK2Nk/T6tprbZffeXyPr0Q6E0sX8u8c2hnXWuq5hRXTaDdnb9bs0Yrca96O9txbeDeV7011f6iVpPI/38aXXvAPN8yL2AM1WCnimfl/umvqnL1PNUjUrn66bLpUzfvSx1z636WIJvrKp7460B0g/lfn31TK9KH+fTr+LpRxqu+atdXY+krf3saSoaG2epND25ekXxxEfcB9VvoF/G0geRHXG1QWdOKZlo/8ZCKtiu/Pc2e93du/bIfWa/2+t0z9Ctiq9hHlP+e9dfMnXyPQmfvfPwtcN+u2z+3Gux2av4n1c/nnjpSae07vnmtxU1h2/Zjl+iit9jf3fGh1PW5fTyZLafvP33jzr7Pe6r/CTjrq3JHnrSt+Myvs/oM+C+yrewjS91Eb/3utWFY6/+sWHOU/FX1O512P38Vij/wJePf+WZ3745b92sszdPu3ve4T2d/Q/NfoZO53o4+g0yl/riO3ablNk84tx5j6SPP7dX+6+fWNZPqj4Zj50w7+ctpjx8xsyJd57+0B0r8LlQ9bn5quuLZifE/7qbO/+W+g/yK2ivil87L+vyUU/W/3zKV9c9cOp1m9/GG6vy8/SsrDv9m47hz7xywYTMnA8LkNuceF/81Qc/nbDx6T/dnn3P69kjrpy4s7Nfpdl/0tlP0uynGr0/6rdd/VK907SCu0DKL8L/7gvuafCLoDktLh8/qHz1wTRwVzAb3A0cBU4AdwSLwD3A3bVfjrxLgnMMfjkHS/5TwE3AQ8E+oBvsBx4GbiXXI8FSMA88AtwNPBIsBsvAI8FysBasAI8HK8HZkl77gUh9ygzt3U/qsz/YCywGx4MHgDvL9V5yvR84Wco9UJ+vIO9U4EbrOd+kJzhR0nmgYkm3l6TrDVXZzm9xgaNF/mPAQWCe6GF7cBg4FoSsfHAcuCO4AzgOLAJ3APe0nceyXL9T8K4k5aZCy6TcB6Tch0Q/y0Q/L4P9wYelHo9IPR4Fx4CPSflPgDuBT4qengKrwKfBqeBysBF8BpwDPgu2ip/QdeIfdB/4Atgm/kFPSfnLwZfAF+T6K7BdP9Oq9wfVnoHQqza/TB8eBeaAtSKfOqnnuaLnevAQ0APWgUeDx4LngC0=
*/