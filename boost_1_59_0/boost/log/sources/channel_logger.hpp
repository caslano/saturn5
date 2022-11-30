/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   channel_logger.hpp
 * \author Andrey Semashev
 * \date   28.02.2008
 *
 * The header contains implementation of a logger with channel support.
 */

#ifndef BOOST_LOG_SOURCES_CHANNEL_LOGGER_HPP_INCLUDED_
#define BOOST_LOG_SOURCES_CHANNEL_LOGGER_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#if !defined(BOOST_LOG_NO_THREADS)
#include <boost/log/detail/light_rw_mutex.hpp>
#endif // !defined(BOOST_LOG_NO_THREADS)
#include <boost/log/sources/features.hpp>
#include <boost/log/sources/basic_logger.hpp>
#include <boost/log/sources/threading_models.hpp>
#include <boost/log/sources/channel_feature.hpp>
#include <boost/log/keywords/channel.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sources {

#ifndef BOOST_LOG_DOXYGEN_PASS

#ifdef BOOST_LOG_USE_CHAR

//! Narrow-char logger with channel support
template< typename ChannelT = std::string >
class channel_logger :
    public basic_composite_logger<
        char,
        channel_logger< ChannelT >,
        single_thread_model,
        features< channel< ChannelT > >
    >
{
    typedef typename channel_logger::logger_base base_type;

public:
    BOOST_LOG_FORWARD_LOGGER_MEMBERS_TEMPLATE(channel_logger)

    explicit channel_logger(ChannelT const& channel) : base_type(keywords::channel = channel)
    {
    }
};

#if !defined(BOOST_LOG_NO_THREADS)

//! Narrow-char thread-safe logger with channel support
template< typename ChannelT = std::string >
class channel_logger_mt :
    public basic_composite_logger<
        char,
        channel_logger_mt< ChannelT >,
        multi_thread_model< boost::log::aux::light_rw_mutex >,
        features< channel< ChannelT > >
    >
{
    typedef typename channel_logger_mt::logger_base base_type;

public:
    BOOST_LOG_FORWARD_LOGGER_MEMBERS_TEMPLATE(channel_logger_mt)

    explicit channel_logger_mt(ChannelT const& channel) : base_type(keywords::channel = channel)
    {
    }
};

#endif // !defined(BOOST_LOG_NO_THREADS)

#endif // BOOST_LOG_USE_CHAR

#ifdef BOOST_LOG_USE_WCHAR_T

//! Wide-char logger with channel support
template< typename ChannelT = std::wstring >
class wchannel_logger :
    public basic_composite_logger<
        wchar_t,
        wchannel_logger< ChannelT >,
        single_thread_model,
        features< channel< ChannelT > >
    >
{
    typedef typename wchannel_logger::logger_base base_type;

public:
    BOOST_LOG_FORWARD_LOGGER_MEMBERS_TEMPLATE(wchannel_logger)

    explicit wchannel_logger(ChannelT const& channel) : base_type(keywords::channel = channel)
    {
    }
};

#if !defined(BOOST_LOG_NO_THREADS)

//! Wide-char thread-safe logger with channel support
template< typename ChannelT = std::wstring >
class wchannel_logger_mt :
    public basic_composite_logger<
        wchar_t,
        wchannel_logger< ChannelT >,
        multi_thread_model< boost::log::aux::light_rw_mutex >,
        features< channel< ChannelT > >
    >
{
    typedef typename wchannel_logger_mt::logger_base base_type;

public:
    BOOST_LOG_FORWARD_LOGGER_MEMBERS_TEMPLATE(wchannel_logger_mt)

    explicit wchannel_logger_mt(ChannelT const& channel) : base_type(keywords::channel = channel)
    {
    }
};

#endif // !defined(BOOST_LOG_NO_THREADS)

#endif // BOOST_LOG_USE_WCHAR_T

#else // BOOST_LOG_DOXYGEN_PASS

/*!
 * \brief Narrow-char logger. Functionally equivalent to \c basic_channel_logger.
 *
 * See \c channel class template for a more detailed description
 */
template< typename ChannelT = std::string >
class channel_logger :
    public basic_composite_logger<
        char,
        channel_logger< ChannelT >,
        single_thread_model,
        features< channel< ChannelT > >
    >
{
public:
    /*!
     * Default constructor
     */
    channel_logger();
    /*!
     * Copy constructor
     */
    channel_logger(channel_logger const& that);
    /*!
     * Constructor with named arguments
     */
    template< typename... ArgsT >
    explicit channel_logger(ArgsT... const& args);
    /*!
     * The constructor creates the logger with the specified channel name
     *
     * \param channel The channel name
     */
    explicit channel_logger(ChannelT const& channel);
    /*!
     * Assignment operator
     */
    channel_logger& operator= (channel_logger const& that)
    /*!
     * Swaps two loggers
     */
    void swap(channel_logger& that);
};

/*!
 * \brief Narrow-char thread-safe logger. Functionally equivalent to \c basic_channel_logger.
 *
 * See \c channel class template for a more detailed description
 */
template< typename ChannelT = std::string >
class channel_logger_mt :
    public basic_composite_logger<
        char,
        channel_logger_mt< ChannelT >,
        multi_thread_model< implementation_defined >,
        features< channel< ChannelT > >
    >
{
public:
    /*!
     * Default constructor
     */
    channel_logger_mt();
    /*!
     * Copy constructor
     */
    channel_logger_mt(channel_logger_mt const& that);
    /*!
     * Constructor with named arguments
     */
    template< typename... ArgsT >
    explicit channel_logger_mt(ArgsT... const& args);
    /*!
     * The constructor creates the logger with the specified channel name
     *
     * \param channel The channel name
     */
    explicit channel_logger_mt(ChannelT const& channel);
    /*!
     * Assignment operator
     */
    channel_logger_mt& operator= (channel_logger_mt const& that)
    /*!
     * Swaps two loggers
     */
    void swap(channel_logger_mt& that);
};

/*!
 * \brief Wide-char logger. Functionally equivalent to \c basic_channel_logger.
 *
 * See \c channel class template for a more detailed description
 */
template< typename ChannelT = std::wstring >
class wchannel_logger :
    public basic_composite_logger<
        wchar_t,
        wchannel_logger< ChannelT >,
        single_thread_model,
        features< channel< ChannelT > >
    >
{
public:
    /*!
     * Default constructor
     */
    wchannel_logger();
    /*!
     * Copy constructor
     */
    wchannel_logger(wchannel_logger const& that);
    /*!
     * Constructor with named arguments
     */
    template< typename... ArgsT >
    explicit wchannel_logger(ArgsT... const& args);
    /*!
     * The constructor creates the logger with the specified channel name
     *
     * \param channel The channel name
     */
    explicit wchannel_logger(ChannelT const& channel);
    /*!
     * Assignment operator
     */
    wchannel_logger& operator= (wchannel_logger const& that)
    /*!
     * Swaps two loggers
     */
    void swap(wchannel_logger& that);
};

/*!
 * \brief Wide-char thread-safe logger. Functionally equivalent to \c basic_channel_logger.
 *
 * See \c channel class template for a more detailed description
 */
template< typename ChannelT = std::wstring >
class wchannel_logger_mt :
    public basic_composite_logger<
        wchar_t,
        wchannel_logger< ChannelT >,
        multi_thread_model< implementation_defined >,
        features< channel< ChannelT > >
    >
{
public:
    /*!
     * Default constructor
     */
    wchannel_logger_mt();
    /*!
     * Copy constructor
     */
    wchannel_logger_mt(wchannel_logger_mt const& that);
    /*!
     * Constructor with named arguments
     */
    template< typename... ArgsT >
    explicit wchannel_logger_mt(ArgsT... const& args);
    /*!
     * The constructor creates the logger with the specified channel name
     *
     * \param channel The channel name
     */
    explicit wchannel_logger_mt(ChannelT const& channel);
    /*!
     * Assignment operator
     */
    wchannel_logger_mt& operator= (wchannel_logger_mt const& that)
    /*!
     * Swaps two loggers
     */
    void swap(wchannel_logger_mt& that);
};

#endif // BOOST_LOG_DOXYGEN_PASS

} // namespace sources

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SOURCES_CHANNEL_LOGGER_HPP_INCLUDED_

/* channel_logger.hpp
CpMEIC50X1we7DbpE8rXycZ9Oy9LtzTmG7IfWfgIn4CjAxipr8lApcCnYTVgzvQ79Br5hObCDLw1WEpRbjWwe7RLxBQ5dbDjInBDLNDTJxSaBbcBW7oy7pJkSqstKCfPSBm4HeLqHlsfdI+fm9V2d5rHdo9qUGxO61Hb6a2MbT7tIReTpYAhZpAr4ohkaYV6buhW9Gyxp5ZC94h1lQToJ40rcg2gpflUkqBm/jopllmuqse7/2o33ypW9Ns+Yr0mIAKTSdZ3zoBnfc3c/Maludm6QFukwT7CHgwUeQzl3NQiPkU6NNgGjle68PmIuNoiVZjFij75FyqUn0q2J9GShKR4R8DlEfk66dARIhajdtCLdgsuQOnuwKuIyyG77yg/g5QkxbbfkHIaZKLC+Dke4tB6NOrNMwcyobKsuDRlDt6MuyrlSonVfzCwxFAkhbhfNC431g0lchuEatCN9ynFlrrqEU1DksT6C7TN9n5c2mtammJM5BwS27giZRYi2yny4gZGYvPVHIiqU1FnJfKzKOpsRJ1GUVNjqICmV9FmJ3o0/mJSAtVySAnKPJOS1h29rG4LddeJr5VtuB9PLhZb2MfuRFiCtrjfv9RkGNDUsd4e3IVWPQKzglQdbu3mEutsibyxjjHI+rqss1IFeKj9+pBYAY5rv62DFY7gwCq2NGoXTmO9f4TIwmTO3KAvWAIyDv+SDu7+IlvLxgz/Em3dgkTQh0EdJDXpE2Ue5C/fr9gtHo16pZHfroznOqYKIQTSISAdVC0mQxGXWletJHL7m/TJUkJjsdKwwmSUZ9kq+ngTTXgJ2knxKNhOaRfRV0cUbAD8AmAoz25hHylEU5wmJah1z8dK6mRjoxaYl0I59j5sAKgk68M7r1CCePHILY1J3tYtpoLwo3RPVT67p1VmhYihdjIUviHlFnZPUn7dfjSxGo40Tmb3vMseFDHqa+WTyQATuzNJ/sUS9Pv0HXK+xA4svQaqNKugYdU1RiGi2zqhcbLENqxKmVWAL8JisdkFOR3ypMGObR7tSgfWzDaN1gy0Z05F3xGCZxudCt/n0VThHYZK2pv0Apd+EN48VYwO8jyDeqi4F6xon81uxlsLvjTgHVT2XtBOrE/S0gYLC+pTmmJttYXYZ4N6cL36xRXpuXIT9Ikkt/CvOwW9hRhkvJcRhqBb4I4GYSiZm+gWk4QQXi0ILR/eTXtOvxAcsQU3zvAX6dxCXiKfjOeroEsk0jtwsBOhiRLsFl20l+hwBvpjvWQN7SWrY71kjluojiRyf/Ykl+G2SOgpEewpGBiCwCwpoWmpaXaifAX2nAQV2Ue7zggK+LMMKmAVPkElAvzHOtA07EBTYUxzKYYBE3agFJ08wS1pVDRoFFBp4afRzFH+PMZKWxM/hfSZ4pozYsLj/mEPetOR+1nf7Ri4q1cTXjuC9m0dnkUGax5Aa+5JHmPN3zap6vpV01h1ved8a/5cFK16tMh/K/2fWPN9qJNtdstFgXywpiVRMteZ4tcC7nWSm0rOs/fRxRQneVo9qIR2fwrRjpY9QaXzg/bfHLf/JXH7v68Hujg5crmijDkHa1dv/LQqom/eF7idfwH9zYXfvGoLvfbpdRMeYOUvJs8Z8fYIUmOMG4HnXKqtkkxRWyWNOP2Zqhz0qu/buGJBtq61bUjcng00G/yL4bduSMeBStfyl4GyGzyCxmw6ucGoiuXiUfJ5QD48HWgPLF1gyOJYj85Dj1I8mU67kovcmBHdybxNh59IGFiaYAC1+zjeXPliBR4qvM/amleU6vdlQansM0GHpFfmJUjfKmnZ0NlhOAZZ7x2AbfuWMy+grLFeB87v07JwPW47FQnNbA2IvitRKNBXH51pxEOE+V/gaxPM5A2wvrvxOuAkaXc2RQa7wj4DWTIhJpn0zcKWBRourdExr2F1f0Px98IdCzQ49vod8i3swaCDjFxBt5lyN0h+LDPnPX2xBRSirYV9dAfdW+P3Lf2CniD4Gx1GZuogPQ02tEChjMgXebROFclBfjcGB+0s3ojgMfqL+0vALPgRp8Sh7MZqRXOr91NJfb4B1rsIDbPGT2vrcCGPkg8rJWlAdErasagFTKSnFzCz5Mfeog+KPuw7ebsxI/v4AD3Yg/XHb3poxtBE0zRKtMnenzyO8J9oRsTUso/voicakL5CqYdx+9BCLWdYqOMvYfdara3CCEg6iIqQMqMTd2P9RD+WHEVcqVAYee1yek6cCon1LcdyKFFdlE/uctBKDpGmk9pxyJmUjwWUD+QG9HEeLY99ZAj3qjNo+1MaJ6s4DavYeVKKuJRdEP5Gh9fKYNdcgF3zZR3dpo+liX6V9E4cs7Sn5YEX8eg57MnvWQdyaEfw+4rgF9yLjbMbJ4MbsB0bre4MWH6VjyZNcn5hgyW/sH5EmazRbPi71KdmyelDec9R25BCfrgZC3T0rCJKm7Jua2IftyEslEMVgg11M74BC8+Ksw7u5N/GM42rVsIOlAfwrnKOXRaLrUTmC9i9k/XH9R+o/AvA/zTtbuTfk7zGLWZIFKxv0u5GEuqvW7Tom+oPYHAEa7bv/23N7tFeWLOfaM+rGV7+Hr6FYqpj/cpYlXh6YBOj0YqNqdZQtFo26Vna2fdO0tJer/8Aq5aiVupHq7MTFNqGgHXA5apanYzfCuqTYUD6/Ug2J7gt59ARMMlBhyvqeNCR2WE7znr/LTqKaN2hGk0Ov3c+Zv4hAXBm/W5EtB2vfU82qzZT7doAWSvRiuZEK70gJg7cxC0vBl4wJ/q9ym7EUOYtiJNNU2Uq7FhKOzHNO56+QG2Ihr9POEBxuLlgq/PoEIQ5S74yEjNgRRAUc+XF0eG5AqLl8jWxuqAyz+dYtWHqFkzDCyjkbKKh+TMxPwNBNIAwVzdLlJEcOijWxI4GXNE3olCT340mf7NxjMl/f4TmJX8aGRlj8p853+TviKI1xtHIq7f9zybwDy7/MYMePd2rGvTcUcoL1MJ+yKBrjDGDvn/52IvDx1zejZdZwGw5v5T1XYfXY5E9iPkXnP3ivPkqF9mxPDpvvtRFti0fP20Wl4+dNss6KdSYn51du1CnnsNykarl0Qk4EFo7hpDjPEL5P0JIy3p/QwldPIbQ5DGEEs4jNFh0PqGBfEMdV4G3Itr7PUaH394HhjMzdgtUAj16IldYwXHpq8mFGfyWSRK4H4v6YWaXEp3Np0ALLep3OchfttKDLcBGyzJbdd/WNvz2hZwlFBpGtiTT15xuUSuYdHIyXksCGf40k14PHLta+8OvR2KnTkro3cNU9FTarG8Dlf91RaMVvaJotKIzisZXNOUHKppdy92GNUiMc57gInefUgnyibSqYTxIB0gNdmY83uIoHtfRYJ+A9aILNsgg6/uUtsHzy0ZZe3LZKGvCsvGsbVz2Q22g3vpuVZZdwOE7X6t0We/t0Hsb7MPsnoCDXHKp6tzMuwD/2Sg+P5k9aB8GKbfPAimrDVmE102eW1eKl0Xhm1LyERv3anyzcXB8f2YkOgEMy+jqY9uZgfxeLU6LaQEPYKvRO6dAC2heBC3woDauBSaTN86MHf0vjx/9k8gz8WTy+i0w6j/70VFvoqP+Ayd52D5m1Jtg1F/jJCNL1RXJj9UJVlJUWcLwNwh39WiE6h4NN5XcAIVJxT0iQ6aPcvUDquB7TUwVvG6PXT1ErofER8PypeQq3ILTKk/tPNFJGsPXwnw6ujWtE7fz49/pxFbO0CkfPxHdqAXAAPwnxzGRHA8ev2B/mZY3Xvt155lQWfi/PsTNXEfnfobnGHADGZfU1dEpRynheQgIDtJguI7iNv5N1pBWtLISxIVZr74Ek/no8vBqxlXqa+cS6H3T0BqzhkaiF2/iJYlSk2ylh654Q4NO/lz6LqevkWkwm/K9rZz+Nv40ZJnYpNOQbyKQ69JykZG+lZvUJdvzLlD9swE/ooGvQPobV6d6V2mn8zPoms8kqbhPEqNXoC6Zabfgmq+PvnTI/6HbVD0Gulrl0ZB/p+/wLBWh+H4cvBndGhBale9eF4LawU7hG22j3XwOYs3aBQkcGi+d1Dy8buz1rmbkLhXfk9n7YpdHT0a15jHgjPmG/1JfC1nUa1qlYgbYLBK6DT9402v0ame6RSK5I1f9EAwgxy539inq5c7nFf+sflzx6Vh8Fb5hxDz7fqdyMGkcB7Mw+V/xkDqOB4oe46JmPBdzxhswphRsJHQHf/ExMqwD99d+zGE9ihc5luLdk1Tjv3Ul3jrYC2HQF0mXok6YM2Dv1fM5uGFx4oIKgrfM9uBBQY++TL5aiOj4zHFQg0wgg5Y/Cb86/oOxadZAXMN//dXI6F28/4LPVT/C56SxfL45+/83Pu2jfErFqU6pnM7orQFbH59O2r+PDamvC+ldtjh/yrObN30hrbY0mGxtNTrpUD4ANqeQ334/OpDaSv012iZTrtTsa6+Zhst0nIk92Fog6z255Q1M/s2+9towFNcEGrN9y6Q62/ytyfghltyiugV53OCIpu7Ga3ijssQgTyolH+jwDs9SF/EV0lGDgzS2eaREKjaze5eYnFJHUDbMwjdRrrfwbefMz0pFGLJLDNIEdu/Zg9jjZuFrWJEf9incZNsZjqkPaRaCoZjzNm4Dl7Ot7bZD/CTbuzy13kBXdBhEi3xTfUi7EM9vDAMdPCOZFuxOSmpLWj1Md0UlyZMlRuoMyhfr25M+0rfWN9MrjxjI7PuE6wEySR+uq3SLRczoN1Nyxy6ggMgrLC7RfqwUrRRe20kupZ0c9xV4NJ6JQq/Zz7dJwzt2uHeQjlz6gQyxgAGL97moZ9+2d4sFBrx9Fa8OJ5/TvR/ZoPVSsYXFjeZKKYTNXPkFNnPsbsO/gUkZc16r1LXaqli/Vm9Rr05bZsdN46MXy6WK6n1xmbH76DJG0zIhLSN69XoGEojftGyJX72eEb16PYNevd5BMVepV9SddwMd3rycSW9ezojfvJwavXrdol69nnHRquxMevU6vYS9OH4P3ejt67fxMVhF5bpDFs37dUP5G9PqhrI2mtg/tH10MoTX4dWduPgjAgKxtoc8OmIYGIm5xfQYlBk6y6AyswXHwmCwe7hvmMv2DXDJuIBEHsID8OWiibzxXWx4fFBALc40XPcFvAlkdR7dNGUkKyiyNYB2ZQm+vjXucywE8xfb9KIplYa4uS5Ubl/AhMS/Xusit5wawWvzluH3KyZCCmiACeoqXtMyRlu5Dr/oJiku6du6GkbDTVA2GchrmAVfLzUVMprK+MtXwEFgs6kIysQkJZc8gnvWmypVIrEXp9KQbYSbTn6Lm06RqBmISh8S3N8um6RCAzAjNa+jmZq1SCz8MJJR83+r0id40GfAzmjxaw7Hdn6DH2MYUwxU5HxuyMPn8QKWE2XC63CTxdj90k5X6WoUflXGYxY0zGT2zWAV8ObzLyou/H7etfTTfkXD1hZy1+cj+P08i+SYs1JyZK8kqeoO2ws+n4c3ukKnWu3wjFRlPXb+twAd/qXZhjvxfnj8FuAc/BYgfgVQ4W4QtmZfqXAmG5d95aa5/nmbJPMb4opsM34GcOsbBg0/Rf0O4NI3GLJcEw2so6u2yPadYrJGE/8QoDVwp0Tj9Q8ZkAewEiVmaaU5r4SBfkM3oTtL/qK5Hm+NjQYkLOsWBpSAeK95dYmjrLyifA2IU2mLqZvsseqGcdJjgGYXqMce8l6husQtLFrxG7C8op3w1VVVkyZZlLTX6LoBfrkHPygjLToM8aq/Qrs58Qph1ktf4s6/D3xSh/JJ1WuY8AoSUT7F+HM07ojHt9L4qlj8lbW/wd0RnKXqTpUiwsoA9jL+SMVE/VqtLcgty0tGXG4xYCjzMShFlE+AMYW70neUm0PvM54KhrTEg/5IiUfrUD7Ck/YDdjCTE+qLLRpNlka2voy82OyEu9yhXravtIF1xbwvr4qmsGoKo/C9NFGZT+uDMAude/cofDdNpJ9BjxlQQ/fIuAsEtswQhnQ1ZmFIz6e+3PPLdPDy6ENMViOk+tRIbIX63xaP+z5fSXQ9ne41s5S6cIuZJg9QPlTKbc38RHLTqZhrLzVLn8o34+cWiodLFD4C84OOP9NvBADi5Ng7GG6Cg8xDzSB/eOGuBf/SXENd1jkJClsNdaFfesrCOY6/f0QR3lPoBdTddM/HCJ9JOr9W1zIOfh3nISR9pM56AjDrMUbXPP4Uxft1HI/suhG0yBEJ95n4F/rp7KcvOvth2YMrrjEIJ7Rck4NULzhvzSNz3KbQT+k+J6jjMXF1tzyVzBstYaFaqMry+AATLOzTKc8xaXU3UU6PKCGksX9BfP1DMRqgfavwjT2RluCLt2JGXIIfrUnG/cfNS+jLfHki7kD2L0mFJADhK2BpCSP8xKARtWO3xYzwLHmlN8YQqq8xUplEGuJJ5D8WgTSOSy0wMwaBSGYqEJgiwzxQC/PAfOgvOGCFFq21Nc94B/DIPhOUgqNfe8OlGtwHwKXlVVg4y4IZ1Gu3hTijtdWNN7vjhJV2jT7y/eAI+ud5Zan8DBXJxO5JAayxH3TDXWjvodfJ7jE5yEOToveGVuNn4Bpeoy8MtTWz8ootW7Os7XkVDPvsoZUgzBKXZwLek09fbvoCgA36qthio1k2ZC2o1HIXSXUYgcJYrxt1verwh3F+Tzg5NgEfywxOpW0K3e+FJeE1sQyQ9mjHl8b68IIX+a34HuJYL/n7SHRuFWsb+oWTvIpU3mIL8Za8CjM/KepC4lXx4Ibbzm6eTL46GbPluoXUlndhFkNDhtwOvq7tIxrsFKpTFamFnyz15XzXmNhgTr/phve4S2E6KU+nM8zUlIaJS274iGNu44xKcSp/ConoGqbazvIS5uVZ8C08joa1jFIW3oKLHBnk/pOjjvMjUUUwZr6A3NOPr2SO/fhK5ujHV7Lw4yup9OMrltGPr2Tix1egWJw51tYsrMdLgWo3zxv7yZVZsy785Eob+InnfbUEjAD3lt+wGLxRJ/kJ6obDZvwsCY5M/PBKJlWRE/GTM/QUC/1cKCgiJzFdFftGSW/8GyV//2zkwm+U3AZzB4XPpt8oOe/rJHRp5nDmD80X1Q1GrPdn+HYFfKCdwDtuS3qJPs3kOfq0kKfoM5U00GcGqcPndeQhGs0iD9JnNrmHPueQn9DnlaScPnNJCX3OI8vpM5Msoc8FJI8+F5JrvkCR5Cub8slsClpKZtBnEUmnzxUkhT4dxESfq8hIDz7LyAB9riWn6PMO8iV93kmO02cV+YQ+7yMf0Od60kSfHDlIn1vIHvrcSl7vUVmgt7qQlxC6B1/Vk2dpED+7RxppEO8MJbU0iFvgCUeDuHBN7qFBvPmWVNIgHronThp8iS640+CrGFxEg/juiVxLg/RTZpfRYACDmf8Ped8C3lSV/ZsmaRtoIUELlOFVBZQR0GIBKSlDeQQqEixCCygFZoSCRR2EHB5KoTWtND1EUdFBRcUrOChVO4pSkIGWYh/AlPIQi1QNUPEcw0B42AaozV2/vc9JT4P/+/3v/e733f+9l4/m7LPPb6299mvttd/MiTXsUifmxACAFMGcuAxLunlOERkrOqR/n8MHbLCTzjInVoBJ3zInzgKQDjOnB84y5myA80vmxAiztJ05L7D4
*/