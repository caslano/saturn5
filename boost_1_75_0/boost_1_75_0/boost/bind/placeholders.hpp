#ifndef BOOST_BIND_PLACEHOLDERS_HPP_INCLUDED
#define BOOST_BIND_PLACEHOLDERS_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//
//  bind/placeholders.hpp - _N definitions
//
//  Copyright (c) 2002 Peter Dimov and Multi Media Ltd.
//  Copyright 2015 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//  See http://www.boost.org/libs/bind/bind.html for documentation.
//

#include <boost/bind/arg.hpp>
#include <boost/config.hpp>

namespace boost
{

namespace placeholders
{

#if defined(__BORLANDC__) || defined(__GNUC__) && (__GNUC__ < 4)

inline boost::arg<1> _1() { return boost::arg<1>(); }
inline boost::arg<2> _2() { return boost::arg<2>(); }
inline boost::arg<3> _3() { return boost::arg<3>(); }
inline boost::arg<4> _4() { return boost::arg<4>(); }
inline boost::arg<5> _5() { return boost::arg<5>(); }
inline boost::arg<6> _6() { return boost::arg<6>(); }
inline boost::arg<7> _7() { return boost::arg<7>(); }
inline boost::arg<8> _8() { return boost::arg<8>(); }
inline boost::arg<9> _9() { return boost::arg<9>(); }

#else

BOOST_STATIC_CONSTEXPR boost::arg<1> _1;
BOOST_STATIC_CONSTEXPR boost::arg<2> _2;
BOOST_STATIC_CONSTEXPR boost::arg<3> _3;
BOOST_STATIC_CONSTEXPR boost::arg<4> _4;
BOOST_STATIC_CONSTEXPR boost::arg<5> _5;
BOOST_STATIC_CONSTEXPR boost::arg<6> _6;
BOOST_STATIC_CONSTEXPR boost::arg<7> _7;
BOOST_STATIC_CONSTEXPR boost::arg<8> _8;
BOOST_STATIC_CONSTEXPR boost::arg<9> _9;

#endif

} // namespace placeholders

} // namespace boost

#endif // #ifndef BOOST_BIND_PLACEHOLDERS_HPP_INCLUDED

/* placeholders.hpp
1K8ls1f9apNLiXxTsjfw+Q2qN9AuVsFRnyXpo+Vz1qyDh8Rn4J66ODzhF0yLlIQnEoPOIVThC8yz4zHPisaDK+GGmx97sa7KvlDumBNeVUMVojFU4TUJFHu0W7rDTv0UrPOY1/UN9rb94pkEUuQxj+fsNnCnpHAkH8lbiwZDAnnitL6aH+xg1TJyq5b4FVsruT1grZyTkg0GHbUl8LYaVjbdFn3/wHH5+2W8zueN6thi9jvEXdZ1ejBitXWCJ/WrAJ3OumhbbeCiYRYhbqzRlLsZnty4zZS3ATdrCEYhbp8pz4Gpo4TwhNixlowJCfkTLXBny09EM8tQ8OTZXfHh6NFjExLocLHiMDD4n6FVsN1lN9aGO+LijRnBYJioDQLbhcMF9YzQliCONbLq4dC3UPTyToLsJWnQXOeE2NstGaEJscmWjKk1w9lz/Mn6cbsF6iXkj7XAqRCsH8PC0TIIV+gHWENEveAKgP+pH2NZP4Q4AfuRiP2AHQ0j2V876Id1Ubwl32qx5SdbqDsl6UEJ7Ab7CHsuFmFw+KWPt+YW7L8GjkYtHBnJijfKX/4b7YYTHOWqGcGOwWON4I8fiz2cC/DpgXCcicBrA0Czi5U1m8CRBs8nJOCYx4ZrwWlE6ypc/x44jQROozc4jVpwGv+dIY81OsQAhr52QN88K+R9YX0PAtzY1siPLogTw+1iHRgWYaNrnk7ZaDk82hFX
*/