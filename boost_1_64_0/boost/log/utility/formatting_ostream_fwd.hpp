/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   formatting_ostream_fwd.hpp
 * \author Andrey Semashev
 * \date   11.07.2012
 *
 * The header contains forward declaration of a string stream used for log record formatting.
 */

#ifndef BOOST_LOG_UTILITY_FORMATTING_OSTREAM_FWD_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_FORMATTING_OSTREAM_FWD_HPP_INCLUDED_

#include <string>
#include <memory>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * \brief Stream for log records formatting
 */
template<
    typename CharT,
    typename TraitsT = std::char_traits< CharT >,
    typename AllocatorT = std::allocator< CharT >
>
class basic_formatting_ostream;

#ifdef BOOST_LOG_USE_CHAR
typedef basic_formatting_ostream< char > formatting_ostream;
#endif
#ifdef BOOST_LOG_USE_WCHAR_T
typedef basic_formatting_ostream< wchar_t > wformatting_ostream;
#endif

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_UTILITY_FORMATTING_OSTREAM_FWD_HPP_INCLUDED_

/* formatting_ostream_fwd.hpp
psWcrV4nblKdcP3am1m1uITzc7rOpQzQenO6tou9kXEpG11SFrUv+EDs9nV6WOuM+sV/4TzrF6oP/0GdD3/79LxER56RGvcRqKu70u4+D8c9f9CgMwvGTZwysXSCftvxSuQBp9ic8+4ndofa4o0/3ro+Zor7HPwQkfcz59bzRR806SzPtLft1Ci/nYkb6Sz+oXw0jUt03mOnpnEHajb2lkWmkYYdmb5G4TYt9t522smJ9/bOr+FD9nLCT+/867hJo8fb50KW+eRNFvyLyI8T+a+6yp0eZaHJwEzN9+0in4VfQWe8q69YQE5tbco52UZOlb+1q/kWOW+pcXfn5Wna2bRST1pqfSn/S0ReUl3KIvLSfFNf7DWz5Z36EfBrewNscXbX51E1D4/LCTIu6yHmAxHx0zcGT33W8q4pdjvb4og/7jE58j6d2jBe5CfZytu4zTDj+dRx40qlKzL5U0fstK20XdvLTb+VqnFy50uW/nRpom0gGzUTt/kmX4ae3avPGaahyzy/5Etpmbu9DhP7x9jyRv0KaD9a6Zg8wN0/ERbxJixPvNdqvOuroyyN9wxPvKXCOfZ4p8NrxH5dW7zxq2r1zhZXd9uYlBLZxo5GXYHdxZ64Fk8tjhrPB8Rukv1eqP8wnuE8XaOd5w36rZg5qOu6Yu6N5zRqQsU8NWPWK2J/FrU9aP8usaet6HfJbW3D2M0w99owaIe6u1LH3Id0SOwMdpJNG1J7pRMvpSnrHSz0i2KvkFglcNtInBlLFqRVbSyx5J+nfZEOzzyofX4r2nxn9edNt8l857jd5znTvnpyZfr0gesv2TvzhiP3PeLYd4d/Pt8dDr1Dj4JfoHrq31+jeujf6fjRV/9uwN/6HV79vShjX4Xv8K7V7/C+AlPhqzAdboYZ8HXYGL4BW8INMBe+CbvAt2APtX8Qjgj/XoMna3hJqDM1vLs1vHtgTbgMHgOfgA1V30z1reGTsDt8Sv0vDv9OggXqv3yfUv1/W/1/R9OxEzaH78I+8D3YH34MT4MfwKHwI3iumv8C7oC/FH04Xfo7CF5oSdd12JO+E2bBX8McOFfz61bYEd4Mh8F58AI1Pwh7otao/+nqf4Kr7H+j/t8BE+B8zb87YRq8yxXPverPAEs8/6D5s1Lz53nNn1XwFLha8+lF2Bc+C09XvdSn8Ls7HGmpT40D+A+bwTTYHMq9VrAhbAlbqHl72AqeAFvD02EbOAKa7waa92HKUsOrj9qq4Z2g4XWC6bAzbAu7wA5wCDwZ5sG+sCscBLvBwfAkeJ7KC+HJcBLsAafDnvAK2B/OhAPgPPX3FtgHLlDzR9X8MXgWXAYHwuVwEFwJ8+E6OBjuUPu6VqDvueSJptO9VlAfeyE2gFnwGNgSNlT3o/Q90t3Oa6LOVvfD1P0ILY+RsAn8hZbH+bAL/CXMgwWwq9rrAUdDs6ah4TSxxPNvWr++hvXhIZgNv4HqXt+rSJPF/QGt51/AZHhQ29Nf3d+RU/dp6t79Xbc0TWc6PBpmaLyvN+8StFF1dxTqcnX3D/wPwu/h0RCL0u8F4UkwDvaGtWAfmAAHwEQ4EtaAk2ESnAprwhKYAq+CqXCOut/3E90x88Dq5B99fWc5YXjXeF5bnXxE1nn2rk6u1lrPj7XOc4B4pL6Q7LRG9UWNQs1ALUQ9j9qO+hJVZw3fmkPloyatia0JxZ7YE3tiT+yJPbEn9lT1+WnW//kIX1loB8B/vv7fvxkThLrmd72u/9fTtGSGzPghlfbJ4f3/ZQUl48bmdsrpqptqQ+f/I88ByHqPfe3/k8i59EeqsD4asQ9d/W7K2f5Dx/N7cGFovnLIqX0kPvlDTj+rn4lPkBj00HQ=
*/