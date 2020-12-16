/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   bind_output.hpp
 * \author Andrey Semashev
 * \date   30.03.2008
 *
 * This header contains a function object that puts the received value to the bound stream.
 * This is a lightweight alternative to what Boost.Phoenix and Boost.Lambda provides.
 */

#ifndef BOOST_LOG_UTILITY_FUNCTIONAL_BIND_OUTPUT_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_FUNCTIONAL_BIND_OUTPUT_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/utility/functional/bind.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

//! The function object that outputs its second operand to the first one
struct output_fun
{
    typedef void result_type;

    template< typename StreamT, typename T >
    void operator() (StreamT& strm, T const& val) const
    {
        strm << val;
    }
};

template< typename StreamT >
BOOST_FORCEINLINE binder1st< output_fun, StreamT& > bind_output(StreamT& strm)
{
    return binder1st< output_fun, StreamT& >(output_fun(), strm);
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_FUNCTIONAL_BIND_OUTPUT_HPP_INCLUDED_

/* bind_output.hpp
XFo7lPb5x5DnJ473XJ6yuaEZTh2H+u0ScHfmUIohBmE+WegjWZgvQRi/zmt1ePQRXayinlldrg2ja5zvmG30dckby+QGP5plhiOeG4DjtUOPI1JRVpVQ5tvDKI7IQl4icMcJ9ls8gOKI0Zh3LfSlLEHHE1zHoEfbmdV30TBqu8XIu0volz3Gab5wHTGEn2R65mA/6ngzUDgvNIxiiDUD6DiXh/nGCWVv0Mp+LF8NhbItzj1lDzeOTyQNZ/EJtz2A6y7ZvXU4IsSsvR4cTvvuY8gLEOe3WM3vfrHCEcPQZxsIOGIK4+nLHT5cm/s1H2mO+RyCLgnDKY4Ix3y+4vzn0u9TNiYaYon+KM9PWCeMRV60eP5pPF8nbJmMa98asMTeETRO8dwIiiVWcrnylrCasETxCGqbshF0z/Uilxn02FemZ1nwvYaCrCHICxZkhU1gspTHXjRba4WOoPu3HUZQPFbCZflv7QNrLYx7d7Bow40j6Zy+aSTFD7e43NCtnjCnm+7h10E/OSrM6X8ZQvcIfxxhvEfoO1LbIxTqFTNRs+GLtcFuDUbSfcK2I2kfq3LJ3cd82PA8ggfW6y/CvP411quZokqKEJvwGEnnda9J3Mbbwq0wRG40xRCLoymGiOfy5K1/qMmn+0RTnx4abXD+ySVzV01nzH4YSfueP5Mp7JNr9d66ysy3v2B20fv2Z8hLE/SLmczXqtv+pDrCITBhrt/wUXROGom8OoJdLnCZodueg/WRKYbYhf66SthnXR1tjCGWjKDrozPRxmefwqbwNt9WaoUh3o6mcYnL0RRDbJii+VmyGYYoR/1eUIT4UDTFEA+MoHPriWg65lznZfpvf782Z206jqb+2G00XbtmxXHbbN+hOsxxxHL0lSPCmJMxkuKIjWj/AsnudubyceRnkzOXp3n58vYpNZ0HPDKK7le8jLwQoU6tpmoy+1vhiPmo/2tCXGIm8obIvm7nnx4bRdesZbwc/x0v1iYu0WAMtck9YwzOP8Vzm+xYpTrM43gZ6CebhP5ShjbOx71qfX8ZHk37y0OYN12S3dZx43n58o6hNZ2b2TOajgGVoymmOMtlKjsijOqzBeozDXVsJsQllqGsYKHPjI+mfWbFaLrPFzaN12Pn47U5//TtGIopPGIopjjD5QbvnGuwXsS6LEZZewWccWk4jo3CevGTMRRTzERePolNbB1OMUXGGOPYRPB0re6drGITq/H9UPEcCvIaCT6x3iXPgbgiwDw28YpBPaeNobhi73Bqx2zMlyyUfV0re9eims49zYsxxhU5McbnngYlaLKH1QZXbIuhfXhvDF3zfOaSq1rhiqTRrK10uCJ/NG2/8TE0PtFzNI1PZMVQXNF7ND33FJHI++PO78wwxYgYGp+YGEPnppVclv/jCbXBFE+Ppeuak2MpprjM5cqPt6xp/bVgLF1j3zeWrr8ikjS7fF7TvlWfsXR9O2YsXX+VcpnKrt+arb/aj6WxibZj6Zh1UdOvYqBax87vfXUy03H7OFrvneMothifzOeUCrgcYH7uKRx95RlhnpdHU2zhGGe8Xxgyzvjc04FkzZav1wZbtBxH9wy7IS9IHOdSNLmHYVwy3XsLxTpcF7CFgry7FG+3+EQdLCdePP/Dywnc3dlM5yWxdP5YFUt9sDJFs/EPNfl1TCwdb+Ji6X0hr1RN5rM1nSH3i6VnyO+JpfcqxnOZSsWjZn793TiKK24yHxDsz2X5P+FRmzNPU8fTeieNp2uldmlMboPd51h8wnA9vg/72nFh7/UU1jlfCnDDFvePpWul92ONzzyV8vLl3eussMXnsRRb/CWWYosbXJ6yu8hs3bod9TssYIs3Yim2WI8=
*/