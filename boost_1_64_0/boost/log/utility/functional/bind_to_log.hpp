/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   bind_to_log.hpp
 * \author Andrey Semashev
 * \date   06.11.2012
 *
 * This header contains a function object that puts the received value to the bound stream using the \c to_log manipulator.
 * This is a lightweight alternative to what Boost.Phoenix and Boost.Lambda provides.
 */

#ifndef BOOST_LOG_UTILITY_FUNCTIONAL_BIND_TO_LOG_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_FUNCTIONAL_BIND_TO_LOG_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/utility/functional/bind.hpp>
#include <boost/log/utility/manipulators/to_log.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

//! The function object that outputs its second operand to the first one
template< typename TagT = void >
struct to_log_fun
{
    typedef void result_type;

    template< typename StreamT, typename T >
    void operator() (StreamT& strm, T const& val) const
    {
        strm << boost::log::to_log< TagT >(val);
    }
};

//! The function object that outputs its second operand to the first one
template< >
struct to_log_fun< void >
{
    typedef void result_type;

    template< typename StreamT, typename T >
    void operator() (StreamT& strm, T const& val) const
    {
        strm << boost::log::to_log(val);
    }
};

template< typename StreamT >
BOOST_FORCEINLINE binder1st< to_log_fun< >, StreamT& > bind_to_log(StreamT& strm)
{
    return binder1st< to_log_fun< >, StreamT& >(to_log_fun< >(), strm);
}

template< typename TagT, typename StreamT >
BOOST_FORCEINLINE binder1st< to_log_fun< TagT >, StreamT& > bind_to_log(StreamT& strm)
{
    return binder1st< to_log_fun< TagT >, StreamT& >(to_log_fun< TagT >(), strm);
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_FUNCTIONAL_BIND_TO_LOG_HPP_INCLUDED_

/* bind_to_log.hpp
+byF+fWtWDp+D5uh2eaz2mCLqAl0zTdggsE5cS439IlDqmKO+9ahvzwvjDmzx9Ex54nxxvsZz403PvPUaCa3zRNZNY31Z8fT8ea98XS8WeaSOZ6NN4Zr2eWov78w3hQgb5SsSu0FbHFwPD3zdJmX47/n9dqcQ2s5kZ5/bT3R4PxrOrfJnk1WZwRL0U8eE7DFfROM71bEx9L+sn2Chi2E8g/w8uU9k61iFZUGPvYi8lRxXy+D95c9fcywaz6ri76/PDCBxipmxtJYxboJ9F5FCS9T3nu4NrjCcxJd79SdRG0TlqnJXaoGeUlm2GID2nW3gC0+x3XZLbuwJziRYotC5M2BvpIm2HB/DMUWxZh3KeSdKfSrQpeeXVW/epb4cIeBX26ZSOMWN1wygxFfhJrji3dQ1/t99OVkTqT44kgMxRfzMF+a0O7DZrGyQ/Y9DBcfTLHFqknc/5MEbLFwEscWiYKf7OBy5X2TGbbwVSz68MFJdM6rmkTHoKgsTW4jK2yRMwHbRMAWixhPX27qJIothkyg2KJ0EsUWw1g+fZ9cw/VT9tnNsEXcJIotZiBvvBj/4LLq7y9SHV3N74pOpmuvd5DnI67/s3nb7e9T09rr4cnUHluRFyDiH03mvh9rs7adNJnONWmTDeIf2Vo7/sFs/RU1md6n6DuZ3qdol8Pnkyfj+BxvpeOzU2jdK5GniuM5lxv6ZFOrmEUE+smrwhwfPIHuHzacYowrWk0xnuOlXM2eH9c0x/eaQtt92BSDcz4uma9YxStaTKBnnoKQF6b4SjYhXhE2hcYrqrRyDgy0ukuxLo7GK3bG0XiFmqfJc9Tk29PiqH1nxlFckajJfPJUTbjirjiKK9rFUVxxgMtUnnzSzK9/xvYKFfzaN47iZWU29+unavU9h6ypdF2RM9Xgew5cboMD71nhilPY144KuGJfnPFdiu2T6TrpszgNVwhtdIGXH3Rgm1ld/hxH9+5+iqOYYlA+b+8DS8wwxZHJFFN8GEcxxf7JdE69HEcxxZZ8zS4/1AZTTIyndpkcT+3SqIDb5amX4R69eSwJ/adKGG9WTKHjzXNo+yLJyy1e8cpU43hFHi9ffqq0pvjdxal03fflVLpXeMklM9UKU5Sj/jZhvFmGvGjZ1w1TvDCVntNvV8j3MA7+Hs+h+Znr3nMa3VfqjzwvcfznMkMPPgUDjimeuB99ZJeAJ7ajfYvJPndGHO0nRzDvDIInfuLlywdzrPDEawb+9X48jVPkFfG+cjDWDE8sQv0qBDzxeDzFE4VxFE/sjqd44iwvU376ZdVfgf1t674SMp36Vfh0+t2crGImN/jpzWZYYjPa9JCAJT7CdVgrYY34yzSKJe6bZhynOD6JYon7pxnHKU4Ua3UfaxWnOIrv+wh1fgp47ncoeszR5LW0uEOB3zP6YBK+L9RzwTSKI34zidrxgWk0TrFBK/vQ9priFI9ON45TrEX+Anr+ySU7vTZxihem0/n97HSD808lmtx2VlhiWfVYLGCJjYwn3AufTrFEfDzFEmumUywxPZ5iiUtcP+VQqBmWyJxOsUTxdDonRczlc9IzS2qzB/l2AsUUVxIopljG5crPjKhp3bUjgdplP/ICxP0fl0yv2mCK1AS6ts1PoGuBVvO09rxhiikS6DmomASD739wWf7PZrI53tHWQseXEumcciaRYgppPp9Tnu2sKubnaYegvxxUhH2weDrHN8cyiiRfN0zRI9H4HNTk+Vrb/7k2bT86ke7tTk6kuOK0S+57bJ43PFsbiXX4Qpjnm8cb36WISKS4IqCU2/jwRKtzULuSKK6oTKK4IpXLkw83rMm/85Kof89DXpDQxic0mc++DesovKs=
*/