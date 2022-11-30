/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   attribute_predicate.hpp
 * \author Andrey Semashev
 * \date   02.09.2012
 *
 * The header contains implementation of a generic predicate in template expressions.
 */

#ifndef BOOST_LOG_DETAIL_ATTRIBUTE_PREDICATE_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_ATTRIBUTE_PREDICATE_HPP_INCLUDED_

#include <boost/phoenix/core/actor.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/attributes/attribute_name.hpp>
#include <boost/log/attributes/value_visitation.hpp>
#include <boost/log/attributes/fallback_policy.hpp>
#include <boost/log/utility/functional/bind.hpp>
#include <boost/log/utility/functional/save_result.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

namespace aux {

/*!
 * The predicate checks if the attribute value satisfies a predicate.
 */
template< typename T, typename ArgT, typename PredicateT, typename FallbackPolicyT = fallback_to_none >
class attribute_predicate
{
public:
    //! Function result_type
    typedef bool result_type;
    //! Expected attribute value type
    typedef T value_type;
    //! Predicate type
    typedef PredicateT predicate_type;
    //! Argument type for the predicate
    typedef ArgT argument_type;
    //! Fallback policy
    typedef FallbackPolicyT fallback_policy;

private:
    //! Argument for the predicate
    const argument_type m_arg;
    //! Attribute value name
    const attribute_name m_name;
    //! Visitor invoker
    value_visitor_invoker< value_type, fallback_policy > m_visitor_invoker;

public:
    /*!
     * Initializing constructor
     *
     * \param name Attribute name
     * \param pred_arg The predicate argument
     */
    attribute_predicate(attribute_name const& name, argument_type const& pred_arg) : m_arg(pred_arg), m_name(name)
    {
    }

    /*!
     * Initializing constructor
     *
     * \param name Attribute name
     * \param pred_arg The predicate argument
     * \param arg Additional parameter for the fallback policy
     */
    template< typename U >
    attribute_predicate(attribute_name const& name, argument_type const& pred_arg, U const& arg) : m_arg(pred_arg), m_name(name), m_visitor_invoker(arg)
    {
    }

    /*!
     * Checking operator
     *
     * \param arg A set of attribute values or a log record
     * \return \c true if the log record contains the sought attribute value, \c false otherwise
     */
    template< typename ArgumentT >
    result_type operator() (ArgumentT const& arg) const
    {
        typedef binder2nd< predicate_type, argument_type const& > visitor_type;

        bool res = false;
        m_visitor_invoker(m_name, arg, boost::log::save_result(visitor_type(predicate_type(), m_arg), res));
        return res;
    }
};

} // namespace aux

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_ATTRIBUTE_PREDICATE_HPP_INCLUDED_

/* attribute_predicate.hpp
4LQIzuwz76j3AKZINVQ8L8W1u2KJcYExIjNKUEuBCPD9LygEgHkgoAus/f8nFhgN/09M/ndSMFJOxoIhBCO1hF5YZJabhjYK6cB7PS9/aqd7DJmYq4opg3hrwwXKJm7gjJsakKQFynRarNFNT6HXoikv3SOEW95IFoHn4om6uYqMWB6Hc2dGebOBs8SpJ57p4Fqu4Hcvpqhvv2P9v1y+fnW+sHrU3C9WarlQaCOH3w+CaQQRWa0U9uMip0xvVNambI0gBNypHDUGb/idMD63L0kfEONbFVVCwsA4jNrP2y7HArwDdiWwhERAbUIaEYQUAKnjXDm2JK0L502ziltbR7UvE5tCbKEtYgzWBMhoqXoeJSagwuvEHitem/GKhvUwezRrIcfYOFbdU9qIrHUoCGsgtS4zawA8LJASJJwj4Wifly8mLYl0daGEtnGgU6R1qmDou1KVGchGAaBskpO7E9yzqjvn3n1XeSSlOJbCKhbaMn3gGKIA1jEwRZXDZ0X2/rMyty1tFClAL3pKDrrSk8Qs3SilUdgMnAAhYoMunJydLOwaaceIyTTUaqTU++s9VU+ILmYi0qqC8wts4nupHn+qvrZz6TZymYqsD2d0fXDadKwOEt/u3/Zzd844GIyibr23rDZzIQzPdoRjvDT6NEvDNmMFs1DPEeGybh3lY8y8ARpiTLIVbvqCrDOlgYA4QwLozuXErIhmIgZgkRZFU8i9maqWgCnIGZVRTBuBSkmBuVAKtqLaIBlQy9B6BSEFC213ppfQdcM+cfoe3nld774A+P7GlZ74SqInW+7VHWR2ufkrbj4YRgBdMCwHfz56jzvu5WiEoBqEpQLWZZksEEPaszpBzj4WyxMS6ts6LQltEhETlKYD9FU5b7nexwmeZhmhISMGBKhbE5GdyBILqgFbUrhwy/RZAbuVXq2qmgWDDrHYGhqhliBW+P+QC/n/J1eltC4RxChSwLKo6EpE9QwyLgdiPWNmTadKZHJQT9TRltUBHrvT5LPOm951DfJ06gR92r5STgxdiuHuS3XnV09uI8wy2x15XL5EfjPI2a9+UMPS+RhxYM+GPoDgX5c4ai2b7VEoR/p8GViAJVZPUWLe8CI6N9yzTvtvOQFVRVU4Jz0ILcpsSgr0BCDMUUYNFdE2lYRzu0GHeGvTzH1mAelnZpnCU2oLqppCyD5UNogJZpZZetWhpURCkh76ALdjiH9IX0oAtAIafWxjtDfncMI0s8MRvZNdudGAccpIcZ+c57gAxigISF0F4sspE0aWtnymxaUy7ad4neD2eGnMwNVKAy1ZcC7svxr9oYJuUnZWMQASEmJonxSeh+smnqdYD2etpogFlMzAnIIqyebpabLX/1oxtC9mVAhSYAAdrVhGl1gTIYtOqaVIuavaYjHj1LNEm+9qQFf1Pf7mhsmPJJYizVdTRxWzrmG9gEDZPdWKxfHLTCFUF/LQ0CibRsHSls3JMOAn27Rz1kh18yGRgvj36OQWa5qZE+dqdJXabJ0nkq7kEmDpU5GBgbFva4iH/8vXteOZmiu+oozy8mFd3qzGpFfxVtOiRBlTwa5MwbMTLfFTdH72dHOpNJPgMvCs+7ngFqPaomW6VarrIi+sACPww28vRwCOEluVMCEICUgAcQXmaHhiNsihU2oxEgCiHKbNm88Voa7jRXChrfvZJlQLLa+cu5Hpnu2jA2jTcw40wnxJ3dp1C8fdj6kneIYR14ZRdREoFlS8yQAZHD4m+QV8tr9FanGpWxZKLM9yRK5d2kUEMGGVRoSRbZxGAURjLdePjbsMO+mm3Qn3KpiwifT4MXygCNU8KPH6f3CF/f/iiqVSewg1jBwQxO7KJW10H2snqR6lLbSvpc9rPGfN3+Kb3lU3nMgQOYQngBe/0cpASvkrtu9giE0mR4IudJyzEinS3/2/AMu9Cs7GfgCAQ0uF+wOTMFrUpAuW/ZZt27Zt27Zt27Zt27Zt23bN6e4vJiZibvT9CTvXs3Pl2vB8UGE+/RyT/VOcBW+V2q+mTITvc+FJEKKmuW0BvFrgisT5l1CMO9AJjf+imLt2ujbs5nS2ItYi0/J5kdXsbBH75FvWnWOJIGki8bzjypqOaNWyAcPhE1CHbTaTe1WkyceqhyP+wJbx5Axe5LBbQYX79ZlH9Nw/u5ZS3UikpCTZXoVTQnFS2E9UZ0YCsp4ATddrQ2lmqcVw8qWr03siNps+aVkHtbne7aSolMlvRBZRRTE+DBJf4TdGjdb2uNeIREVCm1qV0iccbAXpmlcowCXljthPaQkLEwoaQKXJRHjEaUutDS11Vu1xkZC+bc1xpZAClVig+1YDJokf3a+SpL/NuFGst6Nq/hoADdTHvMILnrhPmygjaWUT01qb4ylF3cQqkXwUgiimkpITE1AFHcGz/WEEjZIgkc/bhgxUtZ/TGodPwR4goGJNlGxhX0PaUBMCo4inE2fTtjf1X3V8JhEHBcL7BwCNYCTTejQMPLWLNKjfRTH/QE2DQGikcEsRiLMu2snpDRFjNUz0kBLoeJ2rJ2hzUBEbxvn+1eu5S+WQhpax7hBYj65w0IQXsnePbhu/EEPtaNE/9nN165m1Doff5HTsLRAIQgbD8EWxp0VJkjtvS1luV040UdosGx0sT+oDFNg+U/OLRe9r1mC0mbwAYUuE2jc0UBPyQPHTSMvGzPVeypQMkCaNkucqM1TuwJ5QLPhJvXhDWPxo62/lcUJLmlQM4k/k/yj153+KHB+IK3mHQ2UOswP6R0HlUwkpn7/+tyQiVekr1h6QE+S4O2UWuck/AdVc/6EQeWXvl2VrzqZHljYG+PVJA2rKSCBvPXJhaUe7M++2GXI7iqjZK5vi5u8x0U2pJU7MsvR2gF38XnwAEEJaAABJVua//5PKQQikkbb+h3mgxP8/x162WY0AUYAE0PFPKRxZZtSGZU1JYFvWn40s0E/U/LAMgZP88XWJwP5A7UwSesPg9dPPoeQJ+Lhmc7M/mbZPoxPqsji/Docazfa81ur5Lcd0Daw8wpC4dwg1/od1XhUplqmIpzxNK2nGVJ0vRv9G4YXj4uyqzRI0xAbGDGrmXX3LvVhJLBnxFxIJwbEZkmGBQHs5fX/LYP2LTYIzp0yK0v69By/bilpZKYL/GbeFAjQAk7YECjEo0kajjnmNYyctLIUznYAHkWp4fiNFjN+JwEjC1VZHReRIQkR81iiAbS1CHw4FdCyRKUztwA/6NZtHmpNWXXwjVfg2qcAPL4F8CBM1wQvunkju/CWbLsq1rp0HnlrRj6kPZbKnAwj8Lqkpv81mH4qwFj6vAhGNZC3VdqbTvrkZSNWHS9V43GISDmAEqv1f09MZTQA2gOiHbchkklJeXAfud99vb04PSCJYgCAjUJQxxPj2xUmR0mhiZO+jikqALyks589jPlZZ62nTHNQ19rNGXbXmWkJepJhTvyeTfIt8YAMLh3j+PI16/RFT1YZYZVcmvVpUrQFBrMS3mnamjMpyn+7pbI5eiSjU3mObVE1kMV2XB88AB7la40ov4x8jkuU//hrzGSt/Qedv0tg8YsRsHbZeDIumJyR8HiHPXtTOIMJcB8YeF8ZgBYAv4gb3kPsVBG+Re9tgz5AQwAYKUte/TkJHhumz3tShKUYF3jbVQc1Dn9H0hcYuhdHsOE7jClQjYUPyBYoGm+CsdmbQ4wRVAZhGqPWUB/HHbLq/use0zpb9prqqa9ME0Gb+jBqAkH1jAu7AGKSTuKNjKVz9g3mQ3XQcc/s/Dg2GUqryfxwahf7/KVAgpxxCBCLgfFCv8YvvVrdvGFqnCUD8ejN1cpS9/z5Rv/iVap5N0NqSx9eLLaaBAE6gf7bV29BSxzf/lVlquWN71Oh1DynjKea+4Nra7J0VJ9L4cvOyWMyxJGRSjmJb+qSx8FVrb8h6zktr/+Qu3jZXAw/qyPDMqMYcKJNv0IlzlmLkHw4muzJWhOnC8fRJR2fgPFfcMk7ELS2QNrfq+TYnoge4Vk89lOByEh8ARKN7cQ0R8+/f/Wrc3Dp6wO51J1SNPrDl1zZC3CNjjoErRwh4NrUmNmpJuFJDb9oQw8QgZNrAqE9H6AwOWSxJJW67ZV1yUwVtgAQNO/RPEcLbN2cYMRgN5XkBuzC0iPFipJLqNmW18Xztamw7Q/YllZEnO63JkhlTMJ4bQlidsXQ5A1iRmCrqAy79J1vIZASIQXj/+KugdOeMJiZFQW7Jk/mH9NOBuJAvTJXzhPPoa3nYrd2bL/rn2HGF+G40zu/b0lsQmkqnTk8QtyussUQ7t84JWN1fkinImXmCzo+fAdXcP+BFXJ4eR36IRk8Ce8JZpqlQFscniArzZoSb2LcuAVb3sad2V8O3KsKgoIoKdpTAsrhRCmHBz5MGb81DonJMOaQE1KhmyIM2WqkA0xBnu2l7DQ4EJpYmeixj1jb/HWQCbzRBbc9FMGR3qAUYQciAfJIRkpXJxh2wL4ODR2aEV4ITkxtFAgDxbfXJwyBQfFI3OVRJb8UDx7mno8Nkb7jrIj6ChgufG85B5MGHEuF1fskcIkYWgpVBjVDVv9ZX/Mxc2jns+r+Ub8HTmzPoGgvlwloU19N2KIoOBdDatm3btu1217Zt27Zt27Ztndrm7X2Y+YBkJCOLP47N2NXfXdHDv1nSrIRy79cA6eh3tthx3PIYgcg+NjSExkPaG0lrYH3v5NvZxqWeuFAw8GH48XCMWCCIUMHYcBV4ie1IAkdWiGYY4Uv2BWPspW82bK7lZ4yQuWeM3HQgzpzdKLBf2AOWI6X1QR1IzqMapQrwv8KrIlRQSEvS1idNdhQVFZ0sZ2douaZRURB9LyEcRZsl9X7BGZ8aHvdZJhdy7NxpDQIQAun7zmXIp/ZSqs91rhak/OntmLlBocU790bb7A8gbJkv7kqry6srsvBjBOpDYw1pCYBkoWVEEgBfFS2qAUq5Z381Mys4hV/qc4QcEmvmtkYHUGOFc6pQY+wB/NFX25xBnE4Q9FR0sjP3gGAQJ3JL6cSPWasPSQgc+9x1aVkVIHc/nsiGBwNo92+J5G/3+zeZeGCMRM9INf7ejRCWjOlLekEypGVeOAeAHf5O/Kz25l+XU7UMQGsBvG15Qw+AyqJ/gtgrWOk7gUk+deX6P6SAmnps5QSJOGrgEVXAz7GDIiQ4gKBQ/aNBQkUsazbvL7ba0+rCznFpOY+8bfI3fqukShx75ab6WI5D1BV1zdsjmCJRg2GXf2cQbR7JM8bqIGVeCMwrmiptQ1C1rpSI/1AyF2yOKa1nHc5aSJCYC3b1ciMHEvGwGc5k58IAhwEP9fQD4L/pw23GssIBmorOYwlCBkLc5KUy1tumdL+D2HWdnQ0yQIVeqVhRQDHA8EE1UiVSrEW8uN959bq8ZjJV49CcggoJkU6SuAx0bvsUGeScXLCPTbnIYykKc1H90RczdvgL0WhHJmmAtyu92Br1ir2CrgD18y0zrUcpiyLNy5PSwtIjl1b2y/jX7aWCtYlgLpRO49VomG1qH719RUDLDetwIPsv/vzDrz1B2dmKaVyxp7nQBQbb+jFAcqZOv/of42alFMWeQbON+arpRAnN0IIZdFtCCaIST5sgA7IH0h37z3HwXuKNzmSvMkgy5Leba4qjWsk4zCL2eofCUkL9IjCO5+zStIp5FG1oZ8Aborp9IxcGRWB5C/Ce9BmCe9GeYIfQJXOQevJ4wrH911/xCMsftlMqrVE1ZIDHLmbOgR29os2NucT4OAmiOPoeIP8V7I+ZknxQl+w6ruxa5lAlYEpuzgM9YHpLAGJIGk0Dee7czcXobyIvkorAnYL+a/x57cKY4YFBd/ly93TJxgAn2+KDj+TrlajaC0biT10ma941pLtq63w5RXNlLxd/hK02RD4uxT6HfBQaWmiKqQf6eE2kfmIGnLwRgCVF+6IF1f/2JVijGRv469YtWvFINSJsYmvm9F8C+859nAucnu/9ijK5h1Hqw1AI/OTcrfeBq1Mh5s5JM4op+JDopCgB90lXdXLL98oD5VcAmfABp1lW7+vPojVbM1w85QuJzWQ+3RufEcDeVFFP4c9Acs5jfzKqtO28N/gg/bVKQcqNwOn6ZufAyrPI2ReUaTM0xYQY8auUYD38+BrlKTy/IUF1ik0ADHsQCwVGrceERWuVWYdA7RybbOLozFU+afa0g6vRSllcUIrXNKUUiQuAqAgTcrUnISIZ6uM3rrdFe8IxJE6igUVD51o1qLCBKVFRhv0wwN7RtvR9fyjOxylLCY300XVQchObTRDgZW79hfl19ZEwnLwkdwhlyqy37W4Y7tBgY6K+BbzyP4SBXLVDAYFM3cHF4UJbsjVuy/CbP58vgc005CqkmzwTpTux25DbND/bOwx9k68YD1dHltV1A54vc6SYWySh3Q+gtdJgvu7wW5WAMvSfPoLZ/AD8ybKhQBU+xeva4TyWdvBdKMUJDV0Bp6sOxyyuyyvod8vK3q2G8IksMg9pd/SDZ8Mt8UVDbxe7Mt2BxVPcnRFjse5/u7g0CT4Qv13eRLNTPmkJSwI0Um2IxCNO48+g2ONpYfWsZnsJQ1FWOYjYfDXjMGX6iYR81fFezcqi8vK5KljqRmy+FvIwYhfOizxZ7/JL7IarLMW/YGgmGQBa3Ew73tNRM3At/nWMdHwyqx1Awz+LuhTU1iCq9JYuPDfWOD2BrhMULpiSnpNovRMkJYhFCi3IQuaFwG9MbzTnvtfbKUErdhxKuaHU2pRQR5Tiukyiagwc7n8eX0QMDg9NXstgFBoDZB+3rGfdnsgi+RtW9Ex+K9JVIihuHh3y2ePHQyv+XpnmtuxNMUabuqBtey5rR39zmQcEMoygnsXsEa4VEbbeO0xVvNXwzA+5kIEDHLCqtS2ptklgujQIwiyYLBXlkLKkMuvFXmEvhZHykxBWvxT1ylb5q3SQV3LjeuEeDNS9T5wZ/GI3OZIZhEISAXywgvWRzDOLNYcUY8mzKL9/c/JAnTmAoQgFMeyPjOcDAD5ABA49p+DbL2/I65RCMAthBFQMjwpKMG6hzFxw+dx//+eszwTw9i6tZdUU1vs4uA2WpTIapHvVlc34vj9nCqPiZ33Uis1DdAwz2bn6dbT4MHlx9kHV2u/98gNKGHRUSIlk2JMpw36iSELmWMOFe4tL2m1Lh5p75izYLEanQWk/zUFuAgGdTOOm6jwZFjeeQtIe3G7d6VfQrm2iTPxbIKcEgASBvgnI6UX+oMxV0A9CAPiibr9bt1g6gpS+GiHTqgAOwPFS1+mQP8AFzmfvb/nfp8sO22rEMsO9pM0ROUMRACSabedBO40aJaZp2Fu1XD1DQ3VKUZdU5mj5BITmr7lnl1/lA9Dv7PnIN45s3U+Fv0NtpbhcLXdHXkeMGjynsL/cMkYbJJeoRGoZj12e/QbSNNnslMhVtIL7L35bKAHld94losjnr3gbHWVMEEMwjIjp+QVBtw6DGXhXJsaXdcjCF3l1rMRoEzVtCnYvVOHE/NIo2v2DuQzZzjc2J7fy2D+IwcH5/Gofi62GLU3D0iPl/aVe8F2lvNdRvj4rkLFTkewi73YFJQMOZjE0r0pdJCCJVlCNA2dakUuxDLspXGrExzoXJNzmDeKOfabrAaB9
*/