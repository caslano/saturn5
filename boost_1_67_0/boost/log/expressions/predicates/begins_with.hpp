/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   begins_with.hpp
 * \author Andrey Semashev
 * \date   02.09.2012
 *
 * The header contains implementation of a \c begins_with predicate in template expressions.
 */

#ifndef BOOST_LOG_EXPRESSIONS_PREDICATES_BEGINS_WITH_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_PREDICATES_BEGINS_WITH_HPP_INCLUDED_

#include <boost/phoenix/core/actor.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/embedded_string_type.hpp>
#include <boost/log/detail/unary_function_terminal.hpp>
#include <boost/log/detail/attribute_predicate.hpp>
#include <boost/log/attributes/attribute_name.hpp>
#include <boost/log/attributes/fallback_policy.hpp>
#include <boost/log/expressions/attr_fwd.hpp>
#include <boost/log/expressions/keyword_fwd.hpp>
#include <boost/log/utility/functional/begins_with.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

/*!
 * The predicate checks if the attribute value begins with a substring. The attribute value is assumed to be of a string type.
 */
#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template< typename T, typename SubstringT, typename FallbackPolicyT = fallback_to_none >
using attribute_begins_with = aux::attribute_predicate< T, SubstringT, begins_with_fun, FallbackPolicyT >;

#else // !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template< typename T, typename SubstringT, typename FallbackPolicyT = fallback_to_none >
class attribute_begins_with :
    public aux::attribute_predicate< T, SubstringT, begins_with_fun, FallbackPolicyT >
{
    typedef aux::attribute_predicate< T, SubstringT, begins_with_fun, FallbackPolicyT > base_type;

public:
    /*!
     * Initializing constructor
     *
     * \param name Attribute name
     * \param substring The expected attribute value beginning
     */
    attribute_begins_with(attribute_name const& name, SubstringT const& substring) : base_type(name, substring)
    {
    }

    /*!
     * Initializing constructor
     *
     * \param name Attribute name
     * \param substring The expected attribute value beginning
     * \param arg Additional parameter for the fallback policy
     */
    template< typename U >
    attribute_begins_with(attribute_name const& name, SubstringT const& substring, U const& arg) : base_type(name, substring, arg)
    {
    }
};

#endif // !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

/*!
 * The function generates a terminal node in a template expression. The node will check if the attribute value,
 * which is assumed to be a string, begins with the specified substring.
 */
template< typename T, typename FallbackPolicyT, typename TagT, template< typename > class ActorT, typename SubstringT >
BOOST_FORCEINLINE ActorT< aux::unary_function_terminal< attribute_begins_with< T, typename boost::log::aux::make_embedded_string_type< SubstringT >::type, FallbackPolicyT > > >
begins_with(attribute_actor< T, FallbackPolicyT, TagT, ActorT > const& attr, SubstringT const& substring)
{
    typedef aux::unary_function_terminal< attribute_begins_with< T, typename boost::log::aux::make_embedded_string_type< SubstringT >::type, FallbackPolicyT > > terminal_type;
    ActorT< terminal_type > act = {{ terminal_type(attr.get_name(), substring, attr.get_fallback_policy()) }};
    return act;
}

/*!
 * The function generates a terminal node in a template expression. The node will check if the attribute value,
 * which is assumed to be a string, begins with the specified substring.
 */
template< typename DescriptorT, template< typename > class ActorT, typename SubstringT >
BOOST_FORCEINLINE ActorT< aux::unary_function_terminal< attribute_begins_with< typename DescriptorT::value_type, typename boost::log::aux::make_embedded_string_type< SubstringT >::type > > >
begins_with(attribute_keyword< DescriptorT, ActorT > const&, SubstringT const& substring)
{
    typedef aux::unary_function_terminal< attribute_begins_with< typename DescriptorT::value_type, typename boost::log::aux::make_embedded_string_type< SubstringT >::type > > terminal_type;
    ActorT< terminal_type > act = {{ terminal_type(DescriptorT::get_name(), substring) }};
    return act;
}

/*!
 * The function generates a terminal node in a template expression. The node will check if the attribute value,
 * which is assumed to be a string, begins with the specified substring.
 */
template< typename T, typename SubstringT >
BOOST_FORCEINLINE phoenix::actor< aux::unary_function_terminal< attribute_begins_with< T, typename boost::log::aux::make_embedded_string_type< SubstringT >::type > > >
begins_with(attribute_name const& name, SubstringT const& substring)
{
    typedef aux::unary_function_terminal< attribute_begins_with< T, typename boost::log::aux::make_embedded_string_type< SubstringT >::type > > terminal_type;
    phoenix::actor< terminal_type > act = {{ terminal_type(name, substring) }};
    return act;
}

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_EXPRESSIONS_PREDICATES_BEGINS_WITH_HPP_INCLUDED_

/* begins_with.hpp
d5aK/uEohMpEZv9Yb15nVXXbZtNm5Ga10rZ09TiXpq8QZel7MC9wdZMnxoC7qG/ZXaBqOYHhbqM4kBzfa8jFZgVRCiPI+xFwJHO8VKTnKcUm0OX7Y5e8IS71Wie9l6Pc4S3tYieSuniDa/a9o427XrTxL6/oqOzz0vcnUFuFA8Zt06n5eMODTjzulYK7Cyd8A6sYuX444vQMjHdDmlY6ngse70AaL7Lj8mCRkEBz+8JtVBsgogFt+9qzdahohW8iPEhnh9wsX4Qz8Y6wCb8sKjX0XBZkRXJPqUJxgsFZtCDsC30849LH84XWLz2YC0aNJKsVL+ZZRQDCiFurEeyReTdSzFStbH/yaa0QhfZm6N9KZxxTPdxI7gUg4BnaV/0UlZrHOyWJVIBATHgFv7KjpEi0L9Onx8Ffj79wZzqy5mU1X4HBxVCHc0LNi8K1zt6g7DTq84zk1ySrnzjlxIGbuGS4HeBw/v7WCaU1U5A4OlndAkCCe4VJRgrLCkAdRTQS3sPSwa+DYlGUcca5TrdqaPsN6lg0UnD0GduogmigjptOogcDQe75fitT64fFm7Pyku7sbfJjx1vtDansxfjNl2G+AWWdi7lgyvXRRHfhIInW0CkQqy6t6MP15P+u5xjiWwKyVbSnII9VTjdOLTc7rnIulF52Vb9B8BoVEmZet+PTETQpdJ+R0M+2/9ojI7lGpEhpFeDbkyEDbF6JtTcbIniflOq5hqpek3SVs4eS8d+rPkdgj9XTIC51GiyUHmosdn0RcyDc/rMRYsBd2ZCqJFU7zsf9TRMHeZVFhPfhHllAvIIM/ZIS6TqUv7EgxBuOiHmm7ZegrkwG35lFq39qm9x498pF4XbtMVWC8MtO7YbLRZTVelthqqpruASR3STBeV9cGHg+/258h5AWYUb0ZFzwV+lAXnK7CXM/R8SmAnzdhvsunG9AIhRA0l+OZ8/NcnEDsnB67d5M2LyiYHhlmpv3Sb65kwjDoHfKSdsCKxx2L9iQ0L/nyBfyLo82E00WfmH5nrZfQKV6SO8EX9TUzz0JPTYJjmBmAhLb3TFQufe63S5Rhrr4li/hIIz8ZyipVoJbEKHxH2lqBYKkKDVQH9y+DAVWxU5P8szhvmiWScioHcxHjDu+x5kmbdaavp+fZpQkM5oDWBaOMtOjly+B9z/zV/rGteKYenEPRwUpzi5ra3dcX9oIAj8pLzzU0BufWExPY9dddDQgtX6RiAdyhmnVwzz/QIvRTXm5Y7/CzZmZI3i07Cxgvax5twEMTI6vcamTa21IywfllZ7d4aOqpBhThuLIWolJTNOMkGxPDJBLD6IIVeiBQyUH+fBrlSbhblmtnRjhWsFDKvbgqn3cbi3NHwyE21eZ1ISfKjChGUd7GlbI9kp1TXGs28nGlYkLBv67HsGNhzMzSdhWG6OpHB0eDWua09ExDDwtAjlibwvEqbSX9UGbO+UORXIPqEgX5viDrNAiv+wd/C5KlBVvd85dFeUpknyR+UaSlnnPmgf1i5uc3qpErzuIp2mJd1itHcRmwa+DKJfXgvlIvBdxyab7Ytjm7Yzuo7SkXzML+TosP8ohkRsKmqlKwOFvlAARlXmYPhOqj+uQ7DWWKuL0PRapga4LMztBc8Rki/5BsObKbxhp0fO1Qmqt2072suL3EgeUgx5hZjBDqxiEa+BMN06CcLQqAV50Kn6TjDB/vqSb51vZPvqRBms6JN3WSQ2UHW5oi2IzQ0fquMmD5jvoCDMj8ODOqSgUY2zqSvhM6bVakrIhkg7UIuOG+t0bS/b8y5kfvJsxwdNhtVQGuAoz3CJWkqmJu1pv3mbZx68f2T45NQmrjEO1gPaPiEFsG4Iz9lPBuTVDDyS6UD6GbmXZR7pd5Nt9j23xtTz6jEd8U3UmzIyUe71fGk9UQ/cc2AAiIdypMfe8sMmndMUUSY7lgmjFmseQ5EU/y/ebC3OOnwUsdcr/1AF9l1L8FCdsdPhh4W2OptUtx5r6HmNPJLKsZoIAoUBXlVfYeQEdxzhxjjz4ywuBMd0VIJQZVTV3j5YVZC8fUGJSMq+p2cUllNL+i6+vqB/2UT9zE3/aQTRPf0v9JUVTXX4DepAWd2Jr+u/2+L1T1+T5ApneDEMmcVJUYRdlM3v9a+fxdrCRZ5VGwvBVwkCHFH6yzLH1S49aojzuUvCCdLWV3qlRANMqdcO3vasdpw8QhLgowA3JO1w+G53EKQKRKLUcEXcerF8Xa3ShEBRANP6o1crHxWrwn+OL+z0X4xCPDVGx5rvfBZHHbm2N4EuRjBQ9pkvpVUmoTqjP1+17W2U7c3xNg9z7ZtxYZYTrHCdiV9h50Tcu2WUydZDl6Yjf8vDLdCe4vMsCsMwp3C3xMAWSgt4Sbc+rYbZF30TxkzmAdOuGzMoyA/ACFpBwv/qWvdx6DqA0IADQH+A/IH9A/4D9Af8D8QfyD9Qf6D8wf2D/wP2B/4PwB/EP0h/kPyh/UP+g/UH/g/EH8w/WH+w/OH9w/+D9wf9D8IfwD9Ef4j8kf0j/kP0h/0Pxh/IP1R/qPzR/aP/Q/aH/w/CH8Q/TH+Y/LH9Y/7D9Yf/D8YfzD9cf7j88f3j/8P3h/yPwR/CP0J//fY+I/BH9I/ZH/I/EH8k/Un+k/8j8kf0j90f+j8IfxT9Kf5T/qPxR/aP2R/2Pxh/NP1p/tP/o/NH9o/dH/4/BH8M/Rn+M/5j8Mf1j9sf8j8Ufyz9Wf6z/2Pyx/WP3x/6Pwx/HP05/nP+4/HH94/bH/Y/HH88/Xn+8//j88f3j98f/T+CfLPzGNrzIqvfdWkuKA/3ykxX0QQ7AwP21F8QnTIJl+DFBjHB8yOtOVQGB7e4dSIzFgszh3vUgDA6s9ILjNQCh02UR9B4zW19yncku1/Mqtc3kxiPlXSN+agXv5FKwrWs+q827aM9Q55FdbiWxO54UYzzoTs8eNSOjhFK5/vOuUoL8BgX/8MSfIf3aihacdxReQzkBzhi9u6QBgw1Fl9DOQCVZC/18k73DSEl7HtFVqkpo9nHDqfUEUeRLUxP3CKWTzpHI1GAqFxuvDeyay9rbugrEN9R//Gy8r3IKcsWFUmrnMJzznKO7VMrYE4GU3atKyZ2rj4Ya4eAIKy7O54lS8ui3Se4Cy0jOZ61kClxPl1RQ8fs1qd6JkfkpiG4/eaDwqtkSyKEsHedmVvDCGg2O52EIcG4ZZlmH10K6pGj0lIvn1T2CgU1O6Nbn0+u7etPOiWA8TV5wE/RPFxVdDtvpilHqByPTjd4MEaUkK6pkVJYzsd2sFqkNmWvUB1weVU0iFKBLpwppO1ELboaegXtMaItY5159X1pXPmt42eyDM9wz70V3OwNCW+BGIzbu/OaVAWfV+Ed0q0ClRImWvA1EEenP0eKrL9k6CvS4b74Row+weYYnUSIFewJI8WpdQyMQjIfVp1htwGED8POyASLJrENjVKnE4rGKwmQ8Y9E/O3dytR1RwaIgK2Zy5NXPHZ8L9TQAVLFrpi40Zewmzt9VeTne34fvsCdEegA4GJFgo4qqLXdoD9trp2zyDJhBnumfthcNCs8x4vu8L40s4Eg70tHJjdfiQPo4IpW7gbM1hCDZGIakJ8VZ/IwcwrKw080b0r4BjxTREvQ2aF2Fn9Ci0d185iPnUgaSx+4+77WSSI//DUcWnWIWkWKY9gSXuL/eJXGCOpY5RGd8/vdS0cXX88aS04mN44dIzi+VP3LKAwQ4Wei4KDbxdTsoESla6kAj+N+Rb1wZO9/XceaIH2j/9tdcWJ22ixklEU5FvzKLTKt6I/OdDH4PiCjp83+iuE8S+1hRUDe/ovrbic9ki2WXCR7zm+rrMq1RX5wu3QaNWj74DCrUQ1RCI4ZwOEbVKp/OepWBbDiw8uS2vvBYWT7ew/2ec2VmnSdoePZSyRrdaELRt6XKBT5i/Hcd8Qsht4hv96PTIOSNZlFGh83l7QwG1ryND30aUcH2J99YURQA/Ppm8jGfAB1eP8Qh8fxBCsNm3a+vL0+UWnQyIqXzGh+JBZchmTJ7BMPxiu51uP4YKBaCz1awfAr1yb2BvT3vHUnEs1urpH+zJfR6+Gus4HTY3XpO/Q2HgtiWISOTCoMM9lozbF6MokqeI2fhiwo6uMUdEeXwJiyckgchZCNGEgXAN3+RelBJE3xXjr0hY9KhOEhIRqzsJ3jJI+DimLdcNiSy4TQP2z80pPU85obYia/yqeWUFB8aOT2JCy6DXZ8nc+JHaflZTOc9jQ/px/BNHWks1aySaPpyUAXJCQ8y+0orx6j3dUq059GylXNJ+qBLax3b4lA/77b+HSx44a+FOgGZ6u2hYGX3fxTkiRqKLpqA1wdd368OoOpgGQiElfS5L/P/+Axfbt+erQ3hK4WRArJCXg62m9ckah5g0rtVlgHV+BsPazcYLYSvYOgoWGDwpFCWDGOcmYy4qvdD9cWRNsfis/EfDsCUND27G24Gw8cLiZWY3AsQzlc0e5uJQxjxwDDxhZ29Ga+1VpKrwDT1l7Ab+hIMN7q9++h7LkbQwQADUXJ4FZjAiJFU+vv7AlfeHs325mNiaOCigjY4Jlgg6NIWLPaSn5/Bp3bBmdRPbcPSWLHH0V1CVw8u2xdbXDeh/uNa12r1rZbuPWtEJGTDQKC4aD1wGHoBKnZ0MR0FgKDlGsr7zq+UE+I/K3/dPsTXguyspSLOjDJ5g/5PTkQ7FI+BfMWfDqQCribdDHX7AMQKXHYPxiPGtS3Xh0KFNxNOTFSBwrj9OjlV133sys3fb4M68VhckGprOZLLA2Z/mlND7Ykxex1GvuDfKeh201mhkWt0Qlvm7UQGuktN1MFp6CyQu3hjW32xg3v5kGjaqTAPtxq0UbepCKvDaAQ9HksQY7R46lcRfMFyL2lGLNc/0SkVJ1/ClgKU1cozKe4AxdogGv4xx+cdnCES8s9Gmsyp8dU7genhwiiFswYK6fzU2uDlJyhLCGyGZK14MqM32+BGidSkO6aG2GS5ru42+gnbfN55BuaZ6REftKA5S1Gp216U9o7MOYcNNNaKDL1HRVKnl5kPFLsbUt/3/0g/dSoECfjVVVT+GSZxoEQxiOTbwtm7Lu2XiYns0aHhKTLMcMlxgy/8+oaTbz0FiA4RS3f+NyLQliPXKLAnrrAv/kYvtOOxPy2/Rs4F+5UgQb88mxDur5MG35O6RITJCiHQVWhqwsUekO2k9oZM+TFskUeHC4mVh31IlnT+CRkyU4361u2ajvG7JCWL6XriqLOMuv0gA6cT95uqAYtevT0rXkDKrDUvgchip7GvqkAVPpxUdBe06IxdbzomUb2XeUMkXdZLJxIHz9W9n8eDBuJ2fnip3dMJ6jao2EMAXCZX2R1Ip+oK9kQdwUwIG7HTxlzBm3un+bywJ71Na6KBP4DTNsp2wCiN752aZP7tSNFGjLNFFFiCw4QcMIJqhmYZg7eLVmCIMJVyAbDNjtDzkHdeziLLgU/QY0qmRxICllQxLqLIhuqSkt+Kxed47SOjZVtjvD/uPM3wr5SI10y0nONgBgjTRjklScPIBgUkFkbc5hKxLJnPgb9Gk0aKT3OKuS226j9YKKOidkxKG1uRZyAlyUiO9HlAA5w6eZgKksJQpucSdYnG3qeNxxnfI49/I+2260JHhJ1gKjuyVRAta9n5gcjqwqQyazQ+jd7hDOG4EMI+mYHdS/M8D49rx9jOWIkfD/XnaELr8+hDHUvP3eOjhwy3ki4kPiLTU24PsvwmdTnNzGLXPFdPEszS56GE5vkarRPhYsN0SFnDZC8veGXH2u/bhQZe82xsZeRn+4bMQL88qOWZ7Gn/JV/iVDbIee2lSkbrt7PKfPVweAfzKKrllbler6708VW4uWxEKImW5VimWKceiKRdfEUQ7ETD8eU4bqocb/lLURCCWbIvNQbI1mAFWdGN284ULdLBqFPVXSNa19MSnhfA50nVrMfUFUpp5tB05ir1ZMU+nSADSjoVfrms4j6QrxmzRZga8bAfRqdWO2/0eUA1NxLHrW0dJYW8Rv5czTZkH1Ja+9P1vOGypXDvFzrw3X00KYPgG/3I4HAkSsi6CyO3emNwfMKd1LIWpjNFbXgouFE+JGYMbdjDqsmt2exdbnZnxDtfCyMSfFNHIjaPoX/xwaG2bKGjwXzhJVkEpuSZSMo0ohygDzVGtsWtfQSzMi3Nxu4qZbU0WhPVyPSnhD9CeaD85yMIrZl+cfnzUbBBsqMWvWSPI2MNT5Uv5IL1jjsfIT96aG+FKLX3daOs6OoQQdoa/zAzwYlz1pehVjl0abwO2D8B+ZXKUza0TxEqgNZeo5BgCKr4ibtALdM73rteJmAJW0qK9lwO8tA1Ht2bmcD4n4JdwRmK2O06tvI6U4FWx7bfBOZt4tNb7fPB55QxEeDBP8RZwu55Dn8Md9qsWwdAf+QC8towR8oqm0YMG+U4syda8kjMe+ASvcnhh6kig1uvBWUFBRPg6jBumTuqG1ho/Fkex+crsTfvkccBNDVxevJuQge3RmRmlWiXQBRQm/ljYyuaCqg24yAngKF+7dVkee/1PH7LaduPT0Zbz8YeZ5Tye5Uii6PLvOt4alaAd51xB1ySKnmB1HTKinT4r5mV5tvgTN6uppvK/3CIa0XCGOTVZ+PKxs0ai/5Jgq0NBmAyp5t2KMc8HSxKooODnbKRyVLTadgh4kraZUlIZPjlFn6A/Bv3+pQdPXb+fYudcfkU6wOUr7hMMMC0nitCynvhAUZNMIRSl9nj9KaY4BKdKgykOFYSclhj2CaoUcwqV2mSoORNi1cRw8Z8/WoH9d9bnR4RX7UkkMnPc9hq7tHAlKRK72Y2jhKypwi/CYeZIczrW+1iCoQp4P+ky/FqAiUnXk9vizRjgIdbYtVE/XttVHbSK5NlfnqJARw4QqRZflDeQNvnTzx0fmzb466LmmY/aU0EXwrckcwzzKKchiW/FxxMjRBBL11DDRTKaDsrxYMqCG5uKKExDYrkn4UD0ykmk+jfrLdIG7z7eSjpHmieJHMZx8t6Kxhox0V/uwoeuBvrvLhT/HVaSWtV6q3EL2IDf0pip1kbndcEWaJcLux0YvSQbpqe2GnXxYUN5o7OJw/a/ivTwFZk+t5XV8EETkrTp0D3bODEarJbPPfBqoVjZy2rpjFxGglxRzjC8WOVXrh2XfTpboXLT/se8HshpP0yvB4oqoxTdnt0yg2jljlKIlYbLYirwIaz3ZKQ6n38Cl7lMh6s+sFrhhaDHQEfe0r572R3mftMtALOwR6RDPWUwlyW272rFLJciDls7alw1uSehjBkoOpNrs0bIzW4yu1qaRxJxhkO9heQm2fMr4qRuxmx/Yx2SYzrhEnF+qFoyamCdunzY4+VSi+OdYtinhkVDsx9WcQgl6FBzNvvOTF6kZV+XAY7JKcPqqtJwksKjSJ/b4oq3XXhXxZZ72ZtTvicXyaZXVC/UKQtG7L3BCDqFBNaBPA408Sl+ikCkAm/+IKzMfZxW7NSODeBVzxSVdj8/HMPDTcnNG5dQvOi76pVtXhsue5oRCI2KYPnu0d+G38C5a5T1IgEE/DljhTYDpiqlXlCFtiEsFy4LnJZAY0VRjAqsTfADe/IBIQF0/4FX+9OUqpufT0FR9OlfzDKNts2sRlsFYHWAp/2Tct7eTYpC4cllQjd/wEegOF/cRrMsOFXjSS+WCAlIMFAWU+OB0uSsS/Ae11TGBUhhV9pLW/XCiRaTB8foE4InT/uEhQh85PXo9tGgl9TbDdJ7axDtioApm6kvCaQgtVJKeHBajD+cQhY8H/3nEF1xeUS/u0dohkr9nJ7Lzz2UBx2KLgl8Yp+zBVGobWZlDvUu0mOARMz9XjCkbvHhKbPboJy6ZKGht7+uYmi0xDh48VvBWKYj5klx51Ut5W7Hds4GzI7ROrPnkS7btW9gp2DDPZKAr6YZii6IEhQghuQePmIz/JBK9X6pBozeNXsMCRbJtBLnCmsxkg0o4MvvYdlKjjIvgcr+h1H305ChK02PKY0Rr6IfJVra47XYzyHoSSPz63X6TBTTTMFhQYhpwn/eU/Qm5rYduHrr6kRNYF3U3F0MoL1tE37Yb6h5CkJLHRPi6BUCqOTTUmciIx8KO01ibiJxzR97xTeGgkW8XJU8DedE4sOIPOnnDWphvb0eoGk/JyUWi66iQQ6/osSsrhCvf6GW7yClwb7F1PzI2LoKB0Igi+/m0zbNctakeW2h0ZvoL3UfqyxS1cOopNJamXDET5FdFuQT/uaQIftx2ACMprvGtJcQ8FA7Hm/cN3GzJVpve++/WqDUmV07gsLVcdV+NF9IAFKkNHYqC+VL5bZGMgBFRgot5df6VEiKqUuh7swpeBNNP/JPKXaUis+3k8B4H4cS1iDwkACLP4Ap6jIx9OkoC8tJhp/HVSY7osSJjANvariVsYQQjJIjKeHmxkmMOK0miwLgNnOo3+ttZ91NQt4U7m68vpXMBOFAXcdkvJsqoRjZrVZ3DNUKGFCVGkM7cYQxYgv+JGs4RDs21XSlXh9Bhz/QuzQ4U4ZCPFMGvhkGr1rfle/FwXRLlAULCp1dZw+hoyimpNxIlsuC+L+yBkLFalAELjTxYeKqFlk0gJ/w4/eQYPar9jhoLhdtMKuWVAQC8ZbGtpQS9KwyVSsMlDFl6u1wdAyCzFmP3hECK87KiIyHObd8il7fSbHSEaISqB/+Y7fWM9B+MGNfJnVLMtv7OGu/ck7on9qhAdpfRRFUnPiflspakUk50v7EY8iPuX2CpWfSyu+nkqhfolTT0KwwFMySwgWudW/kcnkEcLM9v/eMU/5cNZ4qRs0JrKpa2LsXsMSWjHMxavP7sE9UpcBIlWf4y4aY+LLd4Wj0rnLKGDv9ycoN4G1AkBgyBElYHUTYOJdpa0r0nXohLSnIKJk/K54LSec+csIm/L6TPXieVMUB3JZ0uRYn5cE77r3nk6rYBzDOUPQeReRScgSBSUU2BJvVSba6imppflLJWrYTqpdETvfHm4Vd1TNCQ4rpQwEFyWizSNeLtlIgbm/70/R9MnS6WuxBibEWkx30ZxzFDHPA3nCyyhUBf1xuqrIPPitv17S6YEbZJSwUOoUNRhiASIhGl6bDW8wDFCcJsbnfEZF4h+/cl+4nt/fDik5dVVynfh4yrWhVYQ=
*/