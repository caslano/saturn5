/*
 *             Copyright Andrey Semashev 2020.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          https://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   utility/manipulators/range.hpp
 * \author Andrey Semashev
 * \date   11.05.2020
 *
 * The header contains implementation of a stream manipulator for inserting a range of elements, optionally separated with a delimiter.
 */

#ifndef BOOST_LOG_UTILITY_MANIPULATORS_RANGE_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_MANIPULATORS_RANGE_HPP_INCLUDED_

#include <cstddef>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/const_iterator.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/type_traits/is_scalar.hpp>
#include <boost/type_traits/conditional.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/is_ostream.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * Stream manipulator for inserting a range of elements, optionally separated with a delimiter.
 */
template< typename RangeT, typename DelimiterT >
class range_manipulator
{
private:
    typedef typename conditional<
        is_scalar< DelimiterT >::value,
        DelimiterT,
        DelimiterT const&
    >::type stored_delimiter_type;

private:
    RangeT const& m_range;
    stored_delimiter_type m_delimiter;

public:
    //! Initializing constructor
    range_manipulator(RangeT const& range, stored_delimiter_type delimiter) BOOST_NOEXCEPT :
        m_range(range),
        m_delimiter(delimiter)
    {
    }

    //! The method outputs elements of the range separated with delimiter
    template< typename StreamT >
    void output(StreamT& stream) const
    {
        typedef typename boost::range_const_iterator< RangeT >::type const_iterator;
        const_iterator it = boost::begin(m_range);
        const const_iterator end = boost::end(m_range);
        if (BOOST_LIKELY(it != end))
        {
            stream << *it;

            for (++it; it != end; ++it)
            {
                stream << m_delimiter;
                stream << *it;
            }
        }
    }
};

/*!
 * Stream manipulator for inserting a range of elements. Specialization for when there is no delimiter.
 */
template< typename RangeT >
class range_manipulator< RangeT, void >
{
private:
    RangeT const& m_range;

public:
    //! Initializing constructor
    explicit range_manipulator(RangeT const& range) BOOST_NOEXCEPT :
        m_range(range)
    {
    }

    //! The method outputs elements of the range
    template< typename StreamT >
    void output(StreamT& stream) const
    {
        typedef typename boost::range_const_iterator< RangeT >::type const_iterator;
        const_iterator it = boost::begin(m_range);
        const const_iterator end = boost::end(m_range);
        for (; it != end; ++it)
        {
            stream << *it;
        }
    }
};

/*!
 * Stream output operator for \c range_manipulator. Outputs every element of the range, separated with a delimiter, if one was specified on manipulator construction.
 */
template< typename StreamT, typename RangeT, typename DelimiterT >
inline typename boost::enable_if_c< log::aux::is_ostream< StreamT >::value, StreamT& >::type operator<< (StreamT& strm, range_manipulator< RangeT, DelimiterT > const& manip)
{
    if (BOOST_LIKELY(strm.good()))
        manip.output(strm);

    return strm;
}

/*!
 * Range manipulator generator function.
 *
 * \param range Range of elements to output. The range must support begin and end iterators, and its elements must support stream output.
 * \param delimiter Delimiter to separate elements in the output. Optional. If not specified, elements are output without separation.
 * \returns Manipulator to be inserted into the stream.
 *
 * \note Both \a range and \a delimiter objects must outlive the created manipulator object.
 */
template< typename RangeT, typename DelimiterT >
inline typename boost::enable_if_c<
    is_scalar< DelimiterT >::value,
    range_manipulator< RangeT, DelimiterT >
>::type range_manip(RangeT const& range, DelimiterT delimiter) BOOST_NOEXCEPT
{
    return range_manipulator< RangeT, DelimiterT >(range, delimiter);
}

/*!
 * Range manipulator generator function.
 *
 * \param range Range of elements to output. The range must support begin and end iterators, and its elements must support stream output.
 * \param delimiter Delimiter to separate elements in the output. Optional. If not specified, elements are output without separation.
 * \returns Manipulator to be inserted into the stream.
 *
 * \note Both \a range and \a delimiter objects must outlive the created manipulator object.
 */
template< typename RangeT, typename DelimiterT >
inline typename boost::disable_if_c<
    is_scalar< DelimiterT >::value,
    range_manipulator< RangeT, DelimiterT >
>::type range_manip(RangeT const& range, DelimiterT const& delimiter) BOOST_NOEXCEPT
{
    return range_manipulator< RangeT, DelimiterT >(range, delimiter);
}

/*!
 * Range manipulator generator function.
 *
 * \param range Range of elements to output. The range must support begin and end iterators, and its elements must support stream output.
 * \param delimiter Delimiter to separate elements in the output. Optional. If not specified, elements are output without separation.
 * \returns Manipulator to be inserted into the stream.
 *
 * \note Both \a range and \a delimiter objects must outlive the created manipulator object.
 */
template< typename RangeT, typename DelimiterElementT, std::size_t N >
inline range_manipulator< RangeT, DelimiterElementT* > range_manip(RangeT const& range, DelimiterElementT (&delimiter)[N]) BOOST_NOEXCEPT
{
    return range_manipulator< RangeT, DelimiterElementT* >(range, delimiter);
}

/*!
 * Range manipulator generator function.
 *
 * \param range Range of elements to output. The range must support begin and end iterators, and its elements must support stream output.
 * \returns Manipulator to be inserted into the stream.
 *
 * \note \a delimiter object must outlive the created manipulator object.
 */
template< typename RangeT >
inline range_manipulator< RangeT, void > range_manip(RangeT const& range) BOOST_NOEXCEPT
{
    return range_manipulator< RangeT, void >(range);
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_MANIPULATORS_RANGE_HPP_INCLUDED_

/* range.hpp
1eosZxu9pmlft7++AOCu0APoU9z2kJmB/Rq4JUOJNx6+W6tXt/Yvn9nG1rTPOXo4+X27KQ2iEZXQ+bGKswb/MTBHbt7HZN3abP5n4Wus4UQpkS9lQRhzFOnivuB1pohv62myFmMW2eyBP7rTPh48V27GdiPhU9lCKaBtKryanb/6J9huOboyaicC4pLUdedSrZa/Ae4rpel8vQpSQeQWvsrDs/b9cgGumZrEoWVbIEjGZqab/y4ZLPjHRLCLCeHgmH8WPJxqqFsIoBvfRGend9OfNRRUJnQYDQBYA07px/p3lBCGLYtITGXU1ZclgzpaVIwtCFGPIa1FT/g2Q08FYzvGVSMlDPYC/0i6CjcI13vZTnVJVqN2TkmYq8gmUajdleHGsCJoEmvkAJk12YMc03P6OwAsCbziJ0PLCZ6fmrIrkWGck8vDKfoCMajtbJPPOAhoCy26j85FgfmdeqbZSevELVcrme9mKfSHW+wIWcmmAzul9/Eq1t6KgFWeverVj2LJY1QJph0XTyRt491qjeVMaDfkEdzzln/Ldeau2UpwJynRx6GDT8/suWVkqWK73VLSMubTdOvyG8wpxt3C9cbLHgh+nlixtCy+1LtDXjB4TbYpE2gm6IPLPvXjY4cnyyrWXGY1A7QzFWfX7vszCIGne/pyQjmo74KW+kBlPdH7JkWlKCVb7/upLDnWx/BgvbU8IP61mgDiA19eChgEBQAAAAIgPFJb+BT+gkZRABIs7dMWAEC0DgCAG4AEwItJgImZVZhdhJaBmZWDloXBhIlWkJVRgFZYhIlJlEOUVYiVQdiHXsnI0cTE1sjAyVnOxdnexZnOwsgOCoAA4P8LEAADwB/Y3WCJZRbQ/zWs4f/1QuIvUP/Vq2/IfzOTrxwx+J/HB7qrPfTxPrM9Zm6IisLx1QgiKEjJKOEFMojhTZYqRSKfRMmCG+FJCwcSkcUcvZyPT8IdLZ+6fLe3v36xXjdPnjmrU1YzXTNZJidZHgBY/fQMTmR3jvLkAEIAGKyS7tdbaH1BPiulctfP9AANwAC+vzru3c2YfaP78lq98DAJIPJY1BW74Fnr3WRYBR9XGcvYfrrKvfDWNlB3a7D6CF5kVkDOAmt0Ybv7yCwVImAyvhbA1VqtoSe9LiF0Op0D+Lxh/1p/iPfU6i3mnOJA/oPHgTgcjQ1rCTIdjAt/NFhKAmWw3mB686mActbiBSeb0gP5XqXzV7hMGWhrr8wrXMidszqFMi9vRuowHxvwj5b6Z70JFSefErLfudLXtn2ZNxkIzKAjiVgiUdm3dtypf9ATzeD3453W7Aw7pdWOZWxsYnAz88ygJYqJNnELxnkcXbfXx5ZW6I6harMMlD7YqX84El0nYMFtvd4D63q1BjhB1ak/u9Od53JHwMJNB997OTlIX8r2j3hymkFDD7QEszIoK4CMApcbAsszbC+2mDz/kon4jMAG0Og4dlBeRQmj95ooSpkdGHK6cc7iWuWsqx+5g+p9cCw7h8G3FBpm8xJMaWnbwH8CFqP4AvTgE0j/C08vTm0ZOKSb3KAnhbNqiQc+8wUXXMaGd63GJ/R5GdQU9y4IlUt3ToUUxfMqIgTvEy/gLUc8jgMD9rt50aBJFumJ6wnlA88Xihk+bGBJiV3/Ix1AnnE57Hs0NiAjndBcE6P/5PBUP3dfg8PaCcv5qvrfaQUrDccNTOVzTf8Usm7dhTrBFHMvKHW17UCKUU3daRKzNcc1zMbJ6r/3YParug5A8JkdkOZJgblvYxpn7lzIxZitEELVe4YXbSCY+clACTBKhrEXRJjm2WAJNea8VltA51YjH25NIKQRev2JdMMzMwp/RjKgNGNVMF463qAAuHaGe028KW4s4IWReoZVMrCV7PCQdXJm/XIPsqoGaWCTSu68oY1sj3O8qXq5QJUZSoLLZ4wX7pFB1VWxvOMkGG474z7vylQCLz74k1wv2MnrCYMcL7iqevoAzh36fyu9CKp6HrCbWVAGj9dEa27dEElbEwLbjTBLXVQCj56cZcGogz1lhhwFtfCho7FB9fWMWYysoELMyAwcJqDkM5r+7e2caZvqAdHJrOrr6kHXHlp1vebgpVezAcfHkfZfVdBpOvZgvFp2de2eqFdd231992hZTk8h1Go1/pWFyBycnEHdmcxt7e0BqWHgHO7tAd2TLnf3T0Cpl7723x8ud6+dgDu+AfbEDAhAmKGg4IOMoxgMbpBByL6Q+oe5AB0xEvqY3vjaX4X7pvIgOO26AB3skwREJCiBxAV9/FSgMTs+oIiIiAjYmKD7Cm57stI0wrvhYW+dboSUhIgFt3zBn68JBHzniEUlJYKyL0bis75QszlH/1xl6brGZsEFzqkpvEj91QJX7z6erf4Jv4H/oBP2/ZYECw/Gkl7scS8PJt6Sg0RhPx6fQjp0cpShlnpXegq6UwkE9g6NzVfyffIQeUy4w2Xjk/o93lc9+LzoBf5OtDudzmx2ayUO3uCWK5E5YPxOfwCOl5enJwcuHd3xmgXbC6b+lqYTVuC/Rn9AQlZ9fDaG7aCA4zMiD2D+yKkxuzy4G3wXBdeukh/sRl8yWwV8ZBOf4Eyd8TMzC01PjSOTy2axOBy8cevVyg2ppUCDAA6ezM4x1gKv9DGq+n0JB864EfVsfHqVlw8n59Pv+Hl7NabGbJ7i6j9/Ruf+m+O8qpyFl5uW9jrNzUpReb7flsF1UgA2PRkt852lG/gAdPu7OxVV4TM+rqGhUaySLra1VRYCrYqFNTGBJQku/MwNuvMheZvIvBjBPOS6M0s17puR7R6lxp+jk4SHMPz7nDYXIrQXeXBA9JH6LvI9NRUl6VC/rzHsNzFJH7c/68bc6pk030MsUErX3FfL9cNX9xa5Y2ZqqhqDjH6pg7PtfDIAyqzhc9EPGh21VOPiEjJXrjQac818uSonPj1FI4NoNosO0my9bNZfRfx1b3uCzgoK2Ot2uVKsxf7D/6JXKqvT0TxLYzn3WQBVH39QfTCp54yAnFj0s/ryr/Ph5HabT2A259vTVe4z8M3+ojttzbweTiU5Ob1S7RZmrtc1unXvxNBFjeHotUa5mbuSO0ngdQ4dENaT/s6OlK/BjzToYaKhai7SdpUHU55YtX34wK+uAzgMDpfRcGipWsguebdGjZeVk7mxrcAjE3X+tqJCHXxismHgmqeW0b7wl84CimkD1pi1VDazxadzgiW84uiDJy1OI+udrrHt4rrz9Xb3EWwBiG63bX+0f/ExdHB/IhiwqiYiImODDvV+QllA8HsH3UxVtafMW01HR+a5kqrRFa7jqwHNlsG+7VPWUFzf3lhZWbuoLa+Mpdn3NpJZqmKRand5Sf77VeXYBps99JH+Eku9xXr9YK2VuHR0mNf9SZynkUcJQe32fjh9+HYR5LbCytId+nj6bHG74MIV+gh1hZJmhhY1coqGCgtXI11bpfc1fVgEFZWeyq7FmlJVY5BrTuDt/YJaLYexTrPNNjE+fr7EJMTCsPg4AOlWqfJm9dLH0kHh/LNpgrtaNNaK9CeFdQ4Cy+HS+6cKF3B/4SGTDRPZeueBTp5HIMulyfc2MTIiYqcoWVXiv20cdkVpeaVvhH9rfYGgXkpKr7XMbGwG+tZdBnbRwpMPBVOtsJ56mEka7zt61k3C1PUPGa/wGiZAcamr4pNLG0OVjR+Zq1ZqqSn8nnp+V0pSkaCxodAVO6XhrZbLE78+05+WBs+i0cfoG6XFI7YHyZjWimmDoe2S8nLe5NARkbv/Daf2+vzy0eprD3h5+tmEPGvRJNFLSOhZkVTZGjYZnA9OoR+rSDxXoKOnqsZoKahKRKlNW/X6ZS4nve61hpw2JiymZC4NKLz7HCcf41+88lW3FREZiTh4LG+23lrt26gsD55Er99N8ytnpGSV/3ORkZGRq9EjKqtyp/f3fJaSAkENGNcwSVZRGQDb6SF9qYXC4lFvIbkUkTwYLCzBkcXTyZgxPfn8qI1RQUfZjhKnNoXdwuQTrdq+c6zQ1VDV1MxKVv0iYtTJpMrl85nw7FY1ETGR6d5p7DeSf2AgICSVYhCX9m5SrxyZnsSMPy6+Tx6GWUCSYs/h89kYP19afraiWluUulQJW6qQtMx/83AvsKaujyce1mQNWVExOZ4nHv5ET0FDJy/h5/N4rkhMXFS5LBZJTrbb9S33YKaurCwD7Xca+ZR2bbHcaLPw1vhIYyxMVU9KNSWFosmCyLJZ2TVRVvkNOZhBUe5FrtNNujp61mKz6ShgMZ2qYI3Qmogk1jXWc3F0dXV1Y1HXmqlIZamayWsr+tApzmuQRiAewagzmfwZPqduObOpp5WRpq13cDXbs2wsa6t40FlevQIDvASO1jSRryyR0aoZo5rhtXMoJmFsf8iq7GztbG09/HB/kaxU6lXM1qTw+80ZsvWQf9QrVFobS224uJ1RNLGzg4d+nqiYiB3Wq53JK0jS1I9LxIjLUsnCcuh9oFR56blxkK0oqGjoeMhURQ+aOHhd1n5BF9vqwozTtbjsp9J7fb5X/y2ruNj+tMPyESyjqvEV21JL56Yj+qkKi42trbXrSd0RGEnAl+rVy9ZEUFZCVlFpn0Q/83B/Pzk93aQjP6D2K+O6HezEUgRQCUmBRrV5fHhI4aut8Pwl7kbv5wa0y49oJqg1r7fnJ/4xOnmt9IE7vuXvqfR8rbloPgYS/eq8qMitnMk7+B59rYL8eK352GbnOK0kcB/VdP+M6Z990QVJvuVTZc5/OjTarQt5xef39f60GflmY3D9QLf8Bf7V6MsNzdh5a0Gk3m3pa1XWAeACMqC0pittgfkuWKqmzfd9r2+pKr+OrbMe2kBLEbTZLGqxJrTOSe7SeJNZuzIrrkvfwb9MZbbMXPXQ6q2yaVGwaSxokLB5pO1Z8bbhLKxB8a1V0sK36tST0i3UfMhcgoNPtvN4HMD2FdqH7VZwB6bfVWwcA5cMS81vLs57KV5mqfAhLmA6OdUjW+C6pwiNuFvncpB6A3leCdcarK3WEkqt2c4TGf25k4pVmKu+/XfG6k0Fg8eDETqdBoJMJhvs0FgqdNkPre8/hHPGrYHlOSb+F6CZ82833hkss1Gi0pqRyOiTgtgspfIXV0gBLiLzwavRbzXAZJpV/51+V+bVNqDAbFBCI7NN9sXxWv0TNOJtSlwKppRiH1hTCdP/6pdhkHTgn8phRy86MhbQ1MRKGR/37woEEp+48W+vdBsYYOXWf/dkVa+qgz65VgZpl4lgEPPCFqesCKpa8F1r8mC2VlYMoK2gGng2av6uc0rlsuZqQne94QTwerkCtLGxAdDRABhkvdtUAH1bNudtYtgGkKFlA16j6O8irqgT9mMfw1kFIf0GnvMdhzTvvWJxjqsPiKm8zlvdcJpz+BRJK/MEKsFpCaLD3sqrbOCP2raEF3rVCznvxNHfwuNXb1zFMMXnA5/4jBnsH+yoExqFScGzD/TYYM/bjIE4K/dF97Q06UeIpkhzpkACw/WG6IbjDeLjaieouYQLinXvQ+E1w3DYgg9ND+5jScxkmGFBIMuCCzw3Fai7/Q/yioEdJLpxJM/CHBZ8Njd0Xax2AMiHPc1nAHflnHMgK1E3Tx8HwIk28N9JFb817w3Up6xuwLQoX91hEnvZxjbIs9PP3KMgmzSXK/hINmQIZYoBwyAXFNgFb6hEaDnDFh1uqK4vTCFOTp/yKMxZtRrEdwza4JqSCMNyVXAtdiwbZdC4qcncJB/6h+5MSH7MrEGwE16Uy1RAPd2sQYUXnjiWcGCRDAoNRzKQ1DSTfrIKl3VjTIAMesO/FUa8E22ZgOuY+LrvCaM0Mw2AhRbQuj1tzKo66rB0vHcCO72x1Ui1d/TALCFO63ZNCK/tSH0pfb6r3nh4yZpageVKJBbvCQHaKogXsdQ+BWBgDscpkCi5nGBi8tk+CSmruro6gMxGs/6tDaip2fW+98fT/YUQaP0zfWCxabqgdVByho49aPRr+oCQSN61Nh3QyckZ+5sK6rV3bWAlNT+GVwgwcHBwe1dHIDVys7aDg/HVqG5env71TWBtXu/+4w/aHt2ra6/IWuQwMPAgP3cIHIcoQOZXEI5LXOia1oJ9UXmQsx13ULGvSQIKHqwaMR6UGtiwMOjV0MLDPdvrjbvtjeb9sTZjcXFPgFe8ov4gcHgC2mPELTmJsKglFnGJ2dCpKOkeXW96VvAGPP5Dq5F3D4+B54OGBr+VcE4Q2Vo/XLwxwu/aW9l2XDw+n4NTlQUlPETv4dDe7JycBEevh7h7F5UI7lnjuffaaV1X7so4HJJWFY/Ll+zQ0NElFknTKROGQ/pbOQlZuVok47DbxgN9C5PyWsUFG7gg23s/Fz93T8/hOX6XBLcsI30ZfWv5ORu2oN6u3G1dIgo4RC0Sp58vTgNUVz81CTCdW7Yu3mxGnfHvhFjUxKI1Z0NWa1ks7EoTt6zhvEO9rdkMP/SEHBVljbqsG36X/T2BZlys82xTl9zlbiNn/cHNRilXXFl695TECp+d6euv5K45SiU0uqyFYu4g2fx8QsJ8StDcVzLmTv25sUAMi/NirJsr3zDidT/ni6Vy6N5e7s/KRbtceEt3V8/5NgFcKK0mnXp37M7d66/6oc1rz7rNTufzhUa53J/vzWFTnw5eTt5O8+s4ASRSXE0X/ddFYFncqbZnrdSc7o/YDHa7n0DQayB+Oz5S7sv8N477qIgoA2JV/DuC0+XrJNf7M1ejtepOzKeMOM79xpNG5khfTBbb2Uz24+J0RPCQVy+Os+T/Yjeqe9zsjI/KAkjH83OfySpZyqK/Ji8sVfPv8ltiY8EDZpO9QHvpoiKlxNXfvCQc+0vnJWbpqijcJ9GHd5LQebs+Doah/YByK+XsWqMmZyK/mgkovxOVcrN07nr2ZKZHY/HVQ/JOolO7EQJn+wszAsMPSDV6wUzJoaH4OrubmppKAtsxWFkH18ANm1tr43TpabWeL/f0yFWFUZRXaF+L0FGWUFCakOxUnu4HmX/GLT9HXx2vVqlt5RU3qlQepCofPkFZY/lgTQREXN+HHFrBZL7eBNpMFszHJ9bWhrGlpaenktj4e/QeKCobzhavQ4r7Q5aRw6TxWG6IL2WNXmrTm5w9O1i2Z6isp+jH6MolfpYyB7pYj1lfh7WaPd/yTWHrNvPXP1w00he+XJlJh4VARXKfS/KKBHlu/1KZpyIXdk4E2ZP/yoKcItMqtN1uXUVZU8mR0iUpamuh5Pqan/7vmr0oq9n1a/OsrITa0Su+mjR6kt+FjKnDfuNe4AO73fum5+fLdKbZ90aTj2KcL/8Jhw1gFttCdVlZeaLquQgp6XnrIvTk7lU8xoLBdCZ78nFxsUhIegjl+eVU2gK3UVNF0cF16XHKU0JCwkHZf0kDcAeHYM2WWznbeKS5qurqb3V9Z1EhIZGLI00RDxdyUdqKCjqaippZPSfo9+FBmqwWODpNZhtvKrURiooxWQ4G+kVKCrpKs5Um1qr9ltKo+EziX6lkxBEk/wNWgKl/Jitsys96WHzRxdXV025VSWXNlwsQRZU1FaUVhQHsBfzSoXDPuk22r+4X2Du7enpe2/S0srKmoSikGhWlRVOb/DKioODJ4/z7WTnOnr6+XnY67Pa/9LFL
*/