/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   deduce_char_type.hpp
 * \author Andrey Semashev
 * \date   17.11.2012
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_DEDUCE_CHAR_TYPE_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_DEDUCE_CHAR_TYPE_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

template< typename T >
struct deduced_char_type;

template< >
struct deduced_char_type< char >
{
    typedef char type;
};

template< >
struct deduced_char_type< const char >
{
    typedef char type;
};

template< >
struct deduced_char_type< wchar_t >
{
    typedef wchar_t type;
};

template< >
struct deduced_char_type< const wchar_t >
{
    typedef wchar_t type;
};

//! Auxiliary traits to detect character type from a string
template< typename RangeT >
struct deduce_char_type :
    public deduced_char_type< typename RangeT::value_type >
{
};

template< typename T >
struct deduce_char_type< T* > :
    public deduced_char_type< T >
{
};

template< typename T >
struct deduce_char_type< T* const > :
    public deduced_char_type< T >
{
};

template< typename T, unsigned int CountV >
struct deduce_char_type< T[CountV] > :
    public deduced_char_type< T >
{
};

template< typename T >
struct deduce_char_type< T& > :
    public deduce_char_type< T >
{
};

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

template< typename T >
struct deduce_char_type< T&& > :
    public deduce_char_type< T >
{
};

#endif

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_DEDUCE_CHAR_TYPE_HPP_INCLUDED_

/* deduce_char_type.hpp
w7IPeT1X1fMiKopLdUtDP+O9iTB4lsfO805hwb2mz+gNVbtTXWPMufORorfdMt65aAF/zPnnX4qbf3aes26c9y8yr1hk7PNy4+BhkXmd+wZ3Fqh5Ajzf4w/8dSbvoY0nLGje1cE8i9c8W/wy9N7Tc8Kt6v2E5s03XzfLmBPm8B5t57K2fNynpeMjKavd6C9eG/76q3PSi164P+HrA4cnv3n8xo9+6PNXncePfvhxSedxsZafZ9vS8TLn8Ur/42Xav6/fGL5hDnvitNd+qzjYFsbDOJgAP4eHjXwNP1P7HVEH1X6S2jsZJsBOMAl2gf1hNzgIdocj4ClwCuwL8+GpcB5Mg4thJlwCB8JlcBBcCc+Et8HBcD3MghvgWXATHA7vhyO0v3wkfFTNt8Ex8Dk4Fr6k/fivwfFwr/bjvwcnwE/gREgXVVN9c3oGZPP3DAqc8fj/e8ZjSQX7GgX6lQJX4ApcgStw/R9cJ6j9T4P1+LT/U7E7XNv/1dpmXoIy5g4s8Ow1Prpx+192Yy+qKFpczhx5l7XtbD/T726xW+46xXk9C277zlmVVT3O8+ZVNhbZj6nE425RUSFHLric586b8uq2ypfQ2HdaP2HKJ3jkZV5+waLKUsKYR5j0GXEWO3E+/u8mduZ7pEU20SKb6CPbqae4P8el7na0yHb0ka2Ut3KRRIwxT/bvYt5ZzAtkzm3RxWULC8150e+IeSRt61CzH+OA6PUzzwMaksCcMYRviCMsyUdfv2Nru+t7ts8HFi+a63d4R+iZ70j0ow1Zy7tIQj/Oox+CvjXO1f1E2M1jpnGLnsQXcYiexKH0BW2X8NH281lTNl83gzgnnDYQHAiXIpM9xrcvyDwOwTc9S99MCX0zJWKne7jxHvLkPsHsc3l2ouf+BnO/gymTPPdpTmmf59vfsaZ9edYEnhU51mO+MixJn1Uv8k8Hx7qCmbvxNPMa3wgy1hzvGI8ZNo09DcaJ3VCHfOTwXE1bTnlIZc105tZ05vHjVPx4n5i/F2bk92VynxI6LXinW/qqzDhIdcxzuO+cpzXOx/KMB0Xm7TAjjud549ztkB9t7lXa87yZN+Ikbvry1lo55FO7G8khphuLKiu8fqrCT1eKTNtww81KuX8lrL1rE/5Ezwx3K8f8zTP8f2s07GU8Z43IfaNu8o2W+/bmWvMOk8Qf8oxkyzOS9RkO3yZxuwK3fynmn5hu3+4Nk+l2T3E7Se/t4elheRa/eZbDt03DkcmzHhbzN81n3SP3WWa+uUPSb7ZZbsyf4Ln/mLWwnRvlpVhNV6tE5jC7i2yXtJBi8VNKg58se4bkmv2nL5yNGSWdTxoV/87HvxsljXwUil1jTQrvSt+B+LV3ULLrVfd37s74EH106sXOwtBE15/c7qDWrg5By90PB9/vduobjoPLRH5M6GjXSSFGf3Gp+Dk2vJ37zVB7uEPEb+n4rUjs9Qkz/IYtMx7fFr8FW8I8T+xlYe9asReKPaNMmW+WJ6fKM4L0nlLC8sxZ2N3p/fbw/gx3PUtTXKb9C+W7F2764xl51qkaViNufhoa5vpRqMfNFNx8UfSeC/W4ebW4uXBRqeaxbMwni/kQnmmE8yJZV2SUZzXip7+J+dYEXd+T4S1P92K/IQ4KxM1C9H4tbr4V6rSWqGycx+wFd4rrCreRB94UvRus+9WIW4Nw6w5x67NQp378fMyfEP+9GtZgt8xMf8Ml7fZyTMse+6nYf1zcfy20IXwLC436wlLMbeFW/bWibzxvcbr4R9PWFeLeHkvYF5j+iZL8cHej/BBryur3yWVZF67fHiPPviZpb6f7DOLPJx055rNc/OpNF3c2hFG+td6wPG57h9PN514=
*/