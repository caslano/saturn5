///////////////////////////////////////////////////////////////////////////////
/// \file pop_back.hpp
/// Proto callables Fusion pop_back
//
//  Copyright 2010 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUNCTIONAL_FUSION_POP_BACK_HPP_EAN_11_27_2010
#define BOOST_PROTO_FUNCTIONAL_FUSION_POP_BACK_HPP_EAN_11_27_2010

#include <boost/fusion/include/begin.hpp>
#include <boost/fusion/include/end.hpp>
#include <boost/fusion/include/prior.hpp>
#include <boost/fusion/include/pop_back.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace functional
{
    /// \brief A PolymorphicFunctionObject type that invokes the
    /// \c fusion::pop_back() algorithm on its argument.
    ///
    /// A PolymorphicFunctionObject type that invokes the
    /// \c fusion::pop_back() algorithm on its argument.
    struct pop_back
    {
        BOOST_PROTO_CALLABLE()

        template<typename Sig>
        struct result;

        template<typename This, typename Seq>
        struct result<This(Seq)>
          : result<This(Seq const &)>
        {};

        template<typename This, typename Seq>
        struct result<This(Seq &)>
          : fusion::result_of::pop_back<Seq>
        {};

        template<typename Seq>
        typename fusion::result_of::pop_back<Seq>::type
        operator ()(Seq &seq) const
        {
            // Work around a const-correctness issue in Fusion
            typedef typename fusion::result_of::pop_back<Seq>::type result_type;
            return result_type(fusion::begin(seq), fusion::prior(fusion::end(seq)));
        }

        template<typename Seq>
        typename fusion::result_of::pop_back<Seq const>::type
        operator ()(Seq const &seq) const
        {
            return fusion::pop_back(seq);
        }
    };
}}}

#endif

/* pop_back.hpp
t8KaMevSu4etMlP8VPJD1pPXXCj5lvogjMes0YXh3SjPYL3Yuo9bHXKmmoZZ8Tzr9BPVbSHMkte7V1YHijXMgc8xjx8Sqc9XGn622e7SyYpiDXM3+Fnd/PrKAmHWvG5v5H6lLAxWk9/7tORgZZEwM/7MwnEhdEewLjznqx4toz4Pq8Vsxtd+82i+w0yY1bu0qx3FDMbj8vBswc8UM1hdZhNrf/ZQWam2l37OS4dQjb02/Cx8utY9D+qRML7PjaOtZ1P9wSLY3b5y/9ccZemwtnzmjDnZhvqEZh6xnf+imfPG8LOUy54zFM9AmBnP69l3P6UchNkzu/XB0X9Rv4b58J51+eh1qhWYE7ODh14epljDPJk5b2izV1k5jN/Rzda3G9C8hfH8bO2y8S2d761hn3BLm25HsYY15vc+Jbg19QIY72d3x936SFkMjJ990M5+lcqSYG7M4trenkXzCMbzZbz33jV0dhivze+mBDlTnmnrlm4+foryTLOYZAd7iotmOXeGrqC6NapiYEMjo2mdI4zX37EBDlmUuzALZsOvO5dRPGE1mA2o2/CQMj9YHWZOe37pR7NfszvLrFdTL9DsuzNxNyjPNOvY63t6ZiyM51nGJlc6Q4p29qMjX/5KdQQz5TnYfEop3Z+2rnT4zEF0fzA7Zm1bd6a5WaTF84qZ73S6PxivsSG9i/srq4BVZzZ94+yNNN+rVDGYcatXXy6g+Q4zZ1azwMlCmQvM4Od4bvZ3lHnCeM5fWzG9K/UCGK/NQxkVdA/RMD7HVh6a7qlsC4zHpVHX8h3KMmEOvI5OvT1LsxHGc8lsUYkRxRPWlefn3TJfOl/VKga91eTufepLXjB+Dws/2tpJmS+M19/roO8OUH7CeC4lWP9CZ5gBc2dmeWzVNmXJMEtmvwRdjlWWBuO5dH764v4UF5gts24Np/ZVlg/j9fem57hn1OdhPCc+XdF8J+USrCmz6N/TW1LMqhneg9/ygcMpLjB+hp+PL3aguMDqMdu8epKrsggYz7PZSR3ofFGapX4zeDfVrfbMs6OmB1M8YfzsY3qeiaO5AuP3t/fMZ7cpntozT50+dYHiCeO5m9W3AfUCI+MqBp+zzjzxLaU+CFPvqwsz/2RNQ4oZzJbZD/M/ofkQDDNhNix2Ij0zFObO7Ex+NZpVcTBLZoVNs7woLjAbZu5mq0dSnsF8mM0Isr1K+QIzZnbczIPmSgnMg1nXTmcrlFlUN1x3NPs8xcwG1pRZ6TybJxQXWBNmn++e9e67E4yfr/vmVtQLomFtmWXbveu7abAazBrPM09Rth/WlVm9ma5zlJXDqjP7qXc/yrNKWCdmDp90OEMzrobhul5BN1/TjIO1YBb8q9d9ZZGwmsyat1lym84Ha8lsw5oRP1New3hO7BnexUxZHsyc2Rc3jz1UVgjzZLayx+C9ykxNqtDv9/zHRrw5MUxZAKwLWzf8wsxoykGYGbM/6trbKkuE1WM2K8XMhs4A42cfcvFaId0RrD2zmYmVL2g2wni+zLt92Y3yzNQwz94GeX9BeQazZzZtkkcQ1R+sLj/ftr9sKAdhbZi9PD30Y6oxbd3uiuVL6HwwV2YPHBx7KsuF1WI2ulb9dJpxMEdm0RMiUyk/YTwn3CzLxypzMzOshwv3B7ZXFgIbzO526q7yJlQrMCe27tlaFw/aJ8yL2fjFO/tTPcD4vfduNs6PcqlmFaP6zFr9o0sr2ieMr8vJGkI90gvWgNn6pCcU60CYObMvC0a8pPPBeE44tD+7nWYHzILZ70uCL1J+wqyYXZ7guVXZFs2ar+hzXlkGzJbZgUaVj6n+tPc57e5voqwIZs2s4fnLIXS3MBNm7b9JSaA=
*/