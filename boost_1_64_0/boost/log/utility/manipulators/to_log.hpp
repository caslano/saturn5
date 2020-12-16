/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   to_log.hpp
 * \author Andrey Semashev
 * \date   06.11.2012
 *
 * This header contains the \c to_log output manipulator.
 */

#ifndef BOOST_LOG_UTILITY_MANIPULATORS_TO_LOG_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_MANIPULATORS_TO_LOG_HPP_INCLUDED_

#include <iosfwd>
#include <boost/core/enable_if.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/is_ostream.hpp>
#include <boost/log/utility/formatting_ostream_fwd.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * \brief Generic manipulator for customizing output to log
 */
template< typename T, typename TagT = void >
class to_log_manip
{
public:
    //! Output value type
    typedef T value_type;
    //! Value tag type
    typedef TagT tag_type;

private:
    //! Reference to the value
    value_type const& m_value;

public:
    explicit to_log_manip(value_type const& value) BOOST_NOEXCEPT : m_value(value) {}
    to_log_manip(to_log_manip const& that) BOOST_NOEXCEPT : m_value(that.m_value) {}

    value_type const& get() const BOOST_NOEXCEPT { return m_value; }
};

template< typename StreamT, typename T, typename TagT >
inline typename enable_if_c< log::aux::is_ostream< StreamT >::value, StreamT& >::type operator<< (StreamT& strm, to_log_manip< T, TagT > manip)
{
    strm << manip.get();
    return strm;
}

template< typename T >
inline to_log_manip< T > to_log(T const& value) BOOST_NOEXCEPT
{
    return to_log_manip< T >(value);
}

template< typename TagT, typename T >
inline to_log_manip< T, TagT > to_log(T const& value) BOOST_NOEXCEPT
{
    return to_log_manip< T, TagT >(value);
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_MANIPULATORS_TO_LOG_HPP_INCLUDED_

/* to_log.hpp
yxodBVtJlHesuat5enrqehoaXFZPOVzWLUHttWrfv3PcMXO9t+5nFu38fcRd/zLbw/Hbdqo99ki6/lpr5z1xpRzF3U3Die2FPIlziI4Oj65yZkRYdESqccqRvns4+/2eWlN/k7LOOpnvudn4pVkxzvzS0p985y300iD5pchXLr/0MOKd+aWSt1x+aeLPekB+6U/I688v3foH8UsPcE/DQtFjHJFfOsrXXqSXOvPexkq68Q5tp8qwc0vtbSVpg+aRWtPa+aLjJX6cba6qtp0k8dEmB222hPtosVoH87loI7llMzNOuNfdKX/T7gYc359ftpjhj9tZ+yqO3OlBbqQjXoLzSz/u66tpxbn2b9Tx3qGupOvnbuZ2aW0g9j5TZbn8nivzzO8WNpK48931YStsChE/JJUHtSk0/Oz0AWZ5jCt3DvRxwc6FlMkcTy0kfVd3Gnyt6rvD/ObGBHOf3e6SppnbKDNP+jdvtPhX8J6sicSf567n1rUmEL9vzedOmTB5puZ3/OskrW7eQ9ws4UTtcowD4zloG/r/KcjTvFfYznGxCfgMZCbkWcilkAgU+BzQ+n16hm1/y7hCHinvpL6nPNzl82Xq5DL9fcz7hjm/60pnXuejTV2mme6F46bOvEcYJzqrf07v4/Zr/0XGcbkxcjLCXRm+bEJxzuSCgkLNPjckHGm+Q8jz+rBIvdCT5Ph10qwcynllwr147nllnnP2VbXdBwiPd/8Rc444fsfRfE5DOmc+pZQRNI8XaYPm8VrT2ufIYYmvZK65abI+1DfXr39J/AV4yukccM37StJEM6zyVD7t610wfNrjR6zrXTzXu3+2+2vzOR/Y74I+PLlztdYr+te57ceHqt/T+ZxGIT5nMHxOxUN+klzNjyAb+Hc4+ll4Fer9p7xftfMqviA/6Evyg74h7+ZbYBPgAe7n9x2/yfU9UPFBs/nepb6dDyr7d2pSJy9f5FPy+PYDz+B+nvWoV/v/zWZ57R32/0vSvfVMAcaRF5cIrAFsSD5cY+AZurfeNYFtgLWA7USveJzy/jAgj/MH1vsQeZw/sn7Z5ns4lOnQjj+TB/Ub+TKRurc9KwPlNRSwCvU1qVfl7md9Mu3lCr/SJf3p5WtVAsp6C6xllANsyH1XWwCjyafJcvO9Ct97lfL60IrvVPuxvhfzG3vDgR2AI4DnkcdzAXk8fYx2AA4EHibPJw84AjgGOIX6qcAJ5ENOAl5NXtj1zH8z080HTiFPairwLsYvZfwyYAFwBbAQ+AjjH2f8ZuAl5A8VAT8GTgd+yXTfMN13wJnAH6n/ifqfgbOAv1KPRhK9C3gjMAY4D5gCvBlYC3gbsA3wDmAv4F3Ai4B3Aye6vOUUspxLgAuBM4CLgHOBi43zY7oVTLcSuAS4Brgc+CjwHuA24L3AV4H3Ad8ErgC+x/wfM/9+4Crg18D7gaWMP8L4n4APAX8DPgx06d74Sro3PhL4CDCa+gTqqwI3AmtQn079mcDHgfWBTwCbAbcAWwGfBLZl+o5MnwXcBuxG/XnU9wRuB/aivj/1A4DPAYdQn0P9KODr/HbnG8CZwF3A2cDdwPnAN4GLgG/x25x7gU+wnKdZznbgAaNdqX+D+l3AUuAe6vdSr/ZFzeK8z7fviyr7G7v8+HdVgdFAjBmZr8nAasBq5A2mGOcPrE6+cSr5xjU4n2oCxxj5efzx6r2DvNewf3vyJ67fP3O9+hUYz3AK8CjX21+A9RjfEXgc2InhwRJWvEp5hg/Iq4zGuiXnDawOjAM2ACbo5BWqZ1V5vrbzCs/EeenAukAP+YhxwPrANGADYLpxPGB9YBNgM2BT4LnAZmy35lyPWgBHkZc5CdgaWAA=
*/