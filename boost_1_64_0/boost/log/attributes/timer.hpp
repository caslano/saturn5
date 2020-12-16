/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   timer.hpp
 * \author Andrey Semashev
 * \date   02.12.2007
 *
 * The header contains implementation of a stop watch attribute.
 */

#ifndef BOOST_LOG_ATTRIBUTES_TIMER_HPP_INCLUDED_
#define BOOST_LOG_ATTRIBUTES_TIMER_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/attributes/attribute.hpp>
#include <boost/log/attributes/attribute_cast.hpp>
#include <boost/log/attributes/time_traits.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace attributes {

/*!
 * \brief A class of an attribute that makes an attribute value of the time interval since construction
 *
 * The timer attribute calculates the time passed since its construction and returns it on value acquisition.
 * The attribute value type is <tt>boost::posix_time::time_duration</tt>.
 *
 * On Windows platform there are two implementations of the attribute. The default one is more precise but
 * a bit slower. This version uses <tt>QueryPerformanceFrequence</tt>/<tt>QueryPerformanceCounter</tt> API
 * to calculate elapsed time.
 *
 * There are known problems with these functions when used with some CPUs, notably AMD Athlon with
 * Cool'n'Quiet technology enabled. See the following links for more information and possible resolutions:
 *
 * http://support.microsoft.com/?scid=kb;en-us;895980
 * http://support.microsoft.com/?id=896256
 *
 * In case if none of these solutions apply, you are free to define <tt>BOOST_LOG_NO_QUERY_PERFORMANCE_COUNTER</tt> macro to
 * fall back to another implementation based on Boost.DateTime.
 */
class BOOST_LOG_API timer :
    public attribute
{
public:
    //! Attribute value type
    typedef utc_time_traits::time_type::time_duration_type value_type;

private:
    //! Factory implementation
    class BOOST_SYMBOL_VISIBLE impl;

public:
    /*!
     * Constructor. Starts time counting.
     */
    timer();
    /*!
     * Constructor for casting support
     */
    explicit timer(cast_source const& source);
};

} // namespace attributes

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_ATTRIBUTES_TIMER_HPP_INCLUDED_

/* timer.hpp
/4/iWtpP4nk/hn6fyc1/8/Rm96Xc7P6K2dNM2C+Yddc/35uStcDet0xC+1lbfv3z9lfo97F43neh38fiab/Kn7cvRb+fx/P+E/2+Hc/7f5z7Qvi5j5+/D1r2hVxHtwkG7bjJ1AT9wZZgANgGHAx2AAPBbmAQeCdYGuwPlgHvBUPBTLAsmAOGg9PAcuD9YHlwFhgJPghWBB8Go8A1YCVwA8f3HBgDHuDrQ2BV8DRYjfeH1AIvgbVBpM2oAyItJB8O1gMrgfXBWuCtYD2wMQhjxIHJYDzYAkwAu4OJ4J1gCjgBbAI+AKaBK8CmYB7YAlwLtgR3gW3AvWBb8CTYHrwAdgAvg7eB34OdwB/B28EI1EcXsCbYFawLdgMbgn3B9mB/sCs4EOwFDgIHgPeAI8HBrm/P2Hhuzc9SB8F2zvU/+s3ken4EvAWcB7YFvwW7gFfAO8DvwL7gQvBe8HFwIrgInAouBmGMJ8BlLP80+BSYBy4FN7L9FnAleAR8GjwOrgY/A/PAM+AaEImmdASBV0C0IfJfHtwAVgY3gnXBTWAcuBVMAbeBLcHnwU7gdrA/uAMcCr4AzgD3gDPBveBTYCG4C9wPHgYPgEfBQ+A34Cvg9+BhMAxleBmsAn4L1gGvgA3A78A48FWwO/g6OAA8Dg4B3wBHg2+C48G3wCzwPXAaeAJcAr4PPg2eBFeDH4DrwY/Aw+Bn4AnwFHgS/BI8BZ4Gz4PnwR/BC6CB+r8IBoDfgaGgw74i21dhe/6WLs+P0Gd4fJC/pZvI7SYJDAVTwHJgGlgRbAZWBZuDdcEWYCMwF0wA24DNwXbgbWB7sCvYAewD3gbeA3YEM8FO4BSwC7gE7Mbtqjt4COwJvg7eAZ4De4N2E/0FrATeBTYG+4O3gXeDXcBBYDp4D3gvOJjbw1DwIXAY+HdwBPgMOBLcAGaAx8HR4EnwXvACmAmWRXlNAiuAk8HK4BSwNpgLjgCv7gik7zq13xlYsvZTsvbzp639rOqGNRuYyyVrMyW/kl/Jr+RX8iv5/d/+/jPr/zilI+fPOf9/e1VDvAM7whTn/gsuRdjVPld026OGTk4fDJX2cIQzKSedEuPTe38IR3l3L+h3nm/pfE+vrPPs3ADeN8bfDugNnkjEc7aa5nGZ43MyMselT5zK7y06Ej06a6z2PJxo1luvpDD226IQ3xA8wcwyD2vzhbisZxoLXeoZcisj1m/Knnau30Szrr89ubf0q4/SngjzDN7c0OjyRRzlhC4/e/jQsUMnyvrtKZDxdC4y/OvfWWe//b5wuG82g6A5qmuON6I5va3IX3u/OOQ0F2YGdsbq1gAQvn7/A4dzgNwr6tYu4bf47xGcI/cb4hzwAVSG5YXe/xtyny2dvz8NOSyK+wS5p8Ed18J/hMf9FV1JvplfOeFO7QLvuRatX98gmd587QqznND/+1F5ZtmK1vumYO2naL0v8UuH+3Z03RyxvnGN/NQVa3nVSOY41gT3wQ4ywu60w07su3Da9Tals8REvZ6iMLubodDoNTODRFwNv+Qy5LXGKyTXiNsS5wexRFrjRR0mGvfz2qIlPbx2+hWF9bBZlPdxQ7PHFNXnGXKfbFrrU6q/BLldX/mc0iK+EfEDXd9ns3yvQayBvEHuK21/xTgTy2uZWJPAWqa6ZrGDz06TzXqYY5BfDTrc51R0mp1VnWYXzAswrusC/laCw89kEAbrGbDjsw6ivKxnDDjt21mJrrPFI+W1DB4DxHqGZV3U03rGY1+o6xn54lrd85Ffyv1+cBQyQ84oY6v1VsBn9xV7L0AY+vFCN/axrLhvlL6J+8amet7Pzm3K+b3I57CbNuee8hsO/SLym3VGt7aLvEI=
*/