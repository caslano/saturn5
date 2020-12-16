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
DQpT7mAtcjuiyG9X1kzgduIO4FqzeC4LV4nbhtuPY72PrPOpwSV+emrW+Ox9O8Jvnc+udOe1PofTg9f7xHYnvzAVhlr307e789qfElwlbh2uOmAt0I7up349UGdoXxO0WNcF1XvHtzZoVQ/7+iBk8dvXCG3HvwuXzrH90L5eKL6n85qhyfi3wIx3OM7fFbhQa4h2hVhHdLRnqLVEuAzn9UTphIVaUzSI4zNw3rVFJRkRYa0v2kJY4lCOZYReZzSDch0g7HjrjY4Szlo1s+4opleE39qjzvh3wMmwALcUt8a2FmknTEd2D/SuSXqPvwPXJdXrTXjvE1+fVAHXvOO8Tml5b+e1SpsIq8btxAWuW9rT27d2ydXHrF8ya5fu55zxHF+KbBoMtY5pKW7NCa5nqkFmP+4wLrpv7eubBsFxuBIcawmD1jpVcTzUeifWHP5ga55i+9Gf4DJw3vVPmf3810DlWn6cwzoobqT810JV9fOth9qBa92Y9VC4Slw1bj8uNob1R7gK3BbcXlx0E9Yw4XJxlbjbcC/gjjb5z1qf9C+a/188X2b/f//9/59PdBm77JvcwTac+1v7+j0s7z2Hjj5XbBzy8tNxT3tk/e03DxB/Ysh5y6PdnItwY79Z4gfbbx57At8UzZ7zeqx/8F4GprzbIjwJ3KDlXYS7EtlS8uDdq6mCb7tzrbTI/+WS/5nzF84ryCtbYsqMfMA+V+JfxHOmO2S5x5o4KcF7hGi93Cjh05kPV9+2D1FYezP52T6/XMpu8qzfvJ3rZG+kJ5F++t47AzcoFT4idZI1YnwONSLGvCXv7N/C8VmltnfcKtvNZhN9sSk3YWae+FkSlj/TzOs04WkSN1K+vS6UsIkmrIV5N/7CCcxjI5+UV/OpdUDeOLbYzE85S/yaH51zQh44ttB/D4yo4DrKJG5lQB2xSYzUk+9amWmvJ+Sd66mylnqqPE49VQbU0+4TqCfP9TPzlNTTLq2nEVpPmbiRxK3x1dMi9ucplEri56BPKt9LyjrcXk8mLEXLil/Lml1LWXND6EQRHK5ltdu2X1c/uBxjkMv4tX85TIPzc2hz4jiWhTD/srx8AmXRdnMqi9kDMFHnrhfiTtd3UhOQq3Ioi/aATv29xuti5jk8quVz6PdUvqOZ+/KI+AeY9M28Ce1LH5Lws43eE9/siVARMB8qHn+1hPcTf7GRT/UbT3rG1d5/+l8PUuZQfadeE8gFfO/PhhUB84rMnsYNg8fZLNogdru0wXnjR48fYXpZP12iUUzdq7xtrO0i/kSPfEuRN/tejya843a/sZb4wWNt3xMea8mTbazlvNaxoH2c6+k8761a3utU73LtZTa9gWOZVb6rmatznfgvddI3lT/D1NHN4i+ypW9tNa79qpHvY+bdrBV/eUh9S8B/vYTPFn+xid/dNgdBdqXKmafr9UqQqRaZbJtMvrVjlZFpyZFNIjNNZNrGcUD21ePEtnuEJ0SmtyuC/2SfFN3n6elEobTniDDnZ+aGaM+iELpeauSk3uTY4mBdN/cThxsH6/ok2j3zUb+9VDipY5+JbMCeIPhVzxk3g+8ppz4asCeI+v32gwxjT5AAPS+1f1fnvCHvn96LCS7vechWPerdB6X28lYFlHcr/uPdQ98dUN6qEOXd/D3LG3i/eFbAnP9pOp4M1+t6f1B5zb2001hCHP+xpKF8u+zgdG0j7z+W1Bf57o5jSaSE9zPXOvGPO5a4fuPLT7HIB48l3f9NY4nHHvm/z+546O/8Jz7PIvS8D6d5AafOfvlhmZcx6ppNF/TeMe5n+/YMKb/xole7nrid8h/aHvkhsSenz8XwDMvPH/WgbDmi3wOTYC/YCfY=
*/