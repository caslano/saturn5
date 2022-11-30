/*=============================================================================
    Copyright (c) 2001-2011 Hartmut Kaiser
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_SPIRIT_EOL_APRIL_18_2008_0751PM)
#define BOOST_SPIRIT_EOL_APRIL_18_2008_0751PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/mpl/bool.hpp>
#include <boost/spirit/home/qi/domain.hpp>
#include <boost/spirit/home/qi/parser.hpp>
#include <boost/spirit/home/qi/meta_compiler.hpp>
#include <boost/spirit/home/qi/skip_over.hpp>
#include <boost/spirit/home/support/common_terminals.hpp>

namespace boost { namespace spirit
{
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////
    template <>
    struct use_terminal<qi::domain, tag::eol>       // enables eol
      : mpl::true_ {};
}}

namespace boost { namespace spirit { namespace qi
{
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
    using spirit::eol;
#endif
    using spirit::eol_type;

    struct eol_parser : primitive_parser<eol_parser>
    {
        template <typename Context, typename Iterator>
        struct attribute
        {
            typedef unused_type type;
        };

        template <typename Iterator, typename Context
          , typename Skipper, typename Attribute>
        bool parse(Iterator& first, Iterator const& last
          , Context& /*context*/, Skipper const& skipper
          , Attribute& /*attr*/) const
        {
            qi::skip_over(first, last, skipper);

            Iterator it = first;
            bool matched = false;
            if (it != last && *it == '\r')  // CR
            {
                matched = true;
                ++it;
            }
            if (it != last && *it == '\n')  // LF
            {
                matched = true;
                ++it;
            }

            if (!matched)
                return false;

            first = it;
            return true;
        }

        template <typename Context>
        info what(Context& /*context*/) const
        {
            return info("eol");
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    // Parser generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    template <typename Modifiers>
    struct make_primitive<tag::eol, Modifiers>
    {
        typedef eol_parser result_type;
        result_type operator()(unused_type, unused_type) const
        {
            return result_type();
        }
    };
}}}

#endif



/* eol.hpp
pejAEFLEC/Ubjr9zWR2IjbyS9nIn3QVMGuy6bI0QcjOUZ4s5xxlCPNNEg5vMHkHn1IuGpWsRTKmEmIX8hLCkuMDkw7KqWa7htY1Q38qUiju1SMwF3YRaWaPMJ2WUeGZI52yt8m5Ni90a5vN7RlWBMDN1FYgENf0X0Lvkz8wsUAxuqRUyfStbag2miBKZOllrsWVZaDabpPOYDXSB0ipn76KyjuGpyHDDyFx8qbQMYix2vucxNlDIBmrChCpnBMd51hATvecyZJqsmDrH14nsoju7sBfSToghXOZjSaidhSarIp/fHju9VYzWnGaE77Bj5YQ8r5QcB8O86AvxfyUGWy4zRReb7ydUvpntrQDBx/qThicw19bcQCOmtkRvCdMZLIvAUjQN1wnbxPu0mh6cWDgZOsxblNCaV8CdcYzAhIVS3laPNp3QVqepXcHknHBvx0AfW9jicSV0YNfksqAykzKTO4VEyBFJyrtlMzrHQArN6HkZkIFM3GyOj6aHLOVmVub0RGxOmOwO/CTOWZfhD2kqc7XLe3rko3nZcdkmZ9wppDjeghnO+j+zHgUW+pymhEmagG0nZDQBb1DHjo8W8ko8bcItsF5xmYMPMcupXBFsI5WGb6nXpYe1ZJ0MK0CEHC8sTDt3SufYczFNwURfZIYVYr4hc/Qrd1SdkLFVAZ9LqcS9fbQAp0yGkDgsw8Wcd2ZcwYQNgZaNd5c5GhM7rngi726BL5uiLWn8llDmtUmML53SxfM6Uqw/xnpXrLekemk5DSf3VyHdKfVzj3XnRG95eRq3lobTfc23pFei96b61Px+f6zfpfvsqW6U4K6nuG9I80S/T97R/OC989QXfd5HPE5P8EoF36d6bZrm6vSZ4sf5p3WF9eskX49J7/N+5R+VlgPXN9Vxk/xQv/N5nwxUl3x1Ts9O8T5uhm9LgquSPtO0V6F6w2XG36F6ewW9z/vdx7p+EreRvr8kfcb5I3GxfQWNR+03aF7n0jC6n57WL/V3UOarAtsQkGuZPwT6zYvRe5pfajNAcV2TXqkvB5oWP2fnBGRloH2J5vVmlJbaWtD85G08SB7oWCNxcT2Se4oLnwGQtet53HkHOKzoVDiPnQcvpkAqsZez6WKdm5qxnpALQv6j2Tkr5zSFu8w1kJChQlnGXV7tXTQv5xSznIsaIUp0gjDQ3PkN+Fyn22WEExORCnHYWf5Vbv9BEZlkMq5IZLNE2TZ/jpoX2ZjIHb/LyADuADwhs4xSrbZB3Y0ho2ykevYoLylUoaV2oJP8GFYI5NdrZjwjJujeSqyN/dfpTFzhMrsEocGSo8Ici1nxC+22FZFRTOz1dBjhL6T0Z+OKO0RKjGEsVSHpGj7DhFmdx4SikK0Ny5XBGBqD2y8gJCdILJOG2Zmlus00MprGbIvQ1JN5L8y5Z+SMIMQ2KZYr2JjaXYyUnxT909ot31XIE9IWlZBzawD3kBPycZpyocouk796zOWbkNx9gu9hzrcLbJDyXLhGJx0hzeW08ZVpNlHTMVmty8aZGEtSOMO57NgaIZlZifaXc2gg5jGxtHNqzIcLmtfToSvEhmeYdG7yjnm8vAhNZxM8bwmWi2dp3E74bZy0jiVjbEqxOI8YQoL+opNWGGYvE2tbnHhH5PiACaMpi2XZMjA2odknPc6HWHKwvsb8i4pZGuTzw1nEie0XnxAqGUzRxPmoinuXkBA1G4kmndOwxI0Gew4dnEKcOytjJqAzuHOMhEiuLWb8bO+JpjJljlCB80ZXKiP18REOmM7P3mMin7a9GN0yTVRtcM4ghKRkW0w5Gmfli2kwauErQs6xvJncKc9CCqritcvgpx0RoycqC8xLAF2MSWh3z8KW1gcwu3ISNOSGJa0zIRKTjReNHSwsYnE8tX94zBhErJMXr2seM0UAYgHX3zY00BSTY1r++no8EvyoZejQ/0OXlNQmytCoDetm6JkaEDZtK1LPJnXMEjNiRmyrcrGezVA5jZfQSS5lg8djp64KTXSTtKRJl/uCE4wxceUyB2FiM0gxuZNJdD2NLcM2kBzFjlu32LM5oLG5DZsuM8oR2sxekkubmYoIaTbK9BjInJ15SBGaySZbSXWpfIFwUjytbnHdSUiVNElls5PSxSjn4npjKgoxYnbaJAK9GS2bFru3NS+W38DYWi7uOGwG4Rw6iW18L542vEwX6jE9t5jIji+Uy07kEOpc2VLEim+o2a2d5cpj+3ZFuhiqV0pP8H4MectXznmZkMFSIn8q2D+qsQNosDw0z7Gy0ydzJEGegQD+MCeAIwOEVQoTvok5ssnbqTiZtwLOp5nQAl7KEFNSTExwOjEXZI5ePI8dTCPS5iWrLEeabGenC7K/MNmKremM/aNSmFzbOQ6dc4REQtOnCzWT7hicvlNMfjFR0QYlSzkJZ940jpt8hby6lNWexZkFirkIzDNpnGM1oYFaNuFlxsswyDhak/mKYKpfAfkH6/7MVOmcksEKyIuC6bnIuXkKk/7bcYSQldnjxYNF53/kZYQZu8VOjBISmeSV9W7mqYDzBicmRyjnszJnJIaK8YpZ45QKVDjphNgGsbJKd6jp9RZiFj0jIh12dqiY8VxutFjcvjSx/UAlXAUjGbeYy4heGOs7H54+0z3O9fSZ6lux7pzq7/FZ8+T5+jSc6DDpmfT0meooqc/4vP/3/F5o8j3qe5/qcXF8rLdP8nL+hL9/rIcmV6r7pvmiZcvr7PF56XPpO6rrp/pjmkdqY4DrkobR+/zed+oXgdxTnS3en03zQYDaMuDzDLAum4RhPwzY1oHuDSf3RB9N4uKz7fM6dZz+FoCHpfdU157XrVN/BTg9gR0FYaQctL/Q9NT/AfYJQPNFy0+eST+g9g/Y1oL2K1x3FLK9+lkdzKY4qR790emVtgFtJ/wdmldcFloP5D3W89N4WHeP42O//zQ99smfzzMdZ3Ss4jJTvPSb9Bs0zZWoTmi5sJ3GpHpLUxmNUXDCM7+8OA6d68RsW4s9BXHWbUJ7MpEbdKx6ZXQCs68X8xOVp9lUJigS8eszybhalDTBYs+8Xoi5bCky652w0kQ6R05fvp1tZmhpo65Yyy0d0P42LWsyztGkkOhrcSElj6ITsG6iHXmMPxfaHsXJNQq2MWDxcraFwfYwX8eLKhwLVS2mVLcjQWarOOeOS0w5lCcEtMzPF+fozjMDsnFGhdUccmM6QYvky2kGGmEbHN112jo6PI8hySgthxmxipEoeRGI5/KasZwvB9RP7OybmVjA8TIhFHPJJibjzckt2BZjMclaLjVzcyZGEE/j9XTOA/p26GLW9JynEqFdyaWUMDQvwiXkPKUUl8EdZS7UD8u0GGZmxm9iUn07Rh5ZA+DsCe3bKcPEmRqImSaXYMokI6aLNbtCQo0ize6+zonsjHubGQOL7KLKDQDHpuucmLCjePXWsbBByAlnOTeo69hGJzEfyUvh2CaLpG4mF9ZsnoNxgyat6VZ9iccTTpTCdU4x2UV+CxITgooZm0ydZrgDmoROoGGLASeHzLb4QZ1Rkm/ScQv1+iMiV2Z5zCTTjmkkuq30A9EzIlYzTCEuJHYuMKCf7sRmQjar6TnpLb94Qf/KvFaxDfJiDn/4djK4SVyITlsoMhsAGgqJNTiyQkSswdlcZqPW4nbobmOqxJYE2XFAFrddTMh6pVS5wZyOiWLhaHh0gqNtIQVY3qaM29Mrok0vW7MzX946t3twO6sHtqPKjjCxMpNPh41dg2tJISdEW0jjmOKFNxnI2w/rmRsNkT3y06Y0hy1jQuahkwwXUxhPeqXiZnOutbfjJDfDxJ2SJ4IpGYjJpkDWeNxcLnTC3EKpPyZVpayUmH3D5F6qTOqf7fl22WYAMQZtWlvDDMxGJozSibPw8I703NZWpHnVmY07GtoTCdgRgjm934TCxM1Krmckg47O9WbbkIU8ELMha+M1QGxjQNngtDjxuNCBERMsJSdp2c4BvZzkHt0z2+oJ1ShPvJmUCEPunFICQ8hjCZsxPDbbmjwBKrJDOXciESqHQYlLlL9JCpPFKjw0nBqmilB7rBAG5g1s6EYBTOPNMOasQrjz28Cat2wPOh1Qmq1yn82Om4k92MFTYu5cpg1dk3NwJJRJdABNppBlZJ8Y25GfP3Ruztg/GqzmLXNV5PdenTzfg9+tgZvW4FSV2zljgU0pGU3kedkWcY15NcEked6qiUk1hHbnTGs2i+tbQqN+IRiurg/XAFUAg+TwcHR6z6i/DGznWref2fhoGK+QjIs7waYApZdZK5sOtz95GwbkWaVnZjqWkQnVLLRzn4mhxCS+06rcYyfFiRGv0/C5WrbrONPoeqgEWhbD4rxXTVHZEx0B3Z+JdXxU70f1TlT/QXUm16XhWNdwXc5/NNU7ERz0DGUC2N913r8xTftIhD/bx5ulw0B1IVi/iHFTnQjWjeS/n7/SfNDzpinuvI6wnl6pr/NL0uvN6T3220xxUv0piUf2EmN952x6pfV9I8M/qUeluOh7vGcW64Sw33D6Lu9THNcPBoqH6j1pOWj+Hp0+Y30jzk8lfcb6M4rn0hSuRfe0f1G9Ia0ncs3v7cV+12n6q9NrkR6Z6v2o32y8vx3XA24rXOe0vWme6BjAaWkZ8nhoPeE+RdPieiH3NB295ush0+1lYTR/V6XX69Mrrut8XJLPwlM92ayiMyt4tGdugnrOpleHGX+J2SLnlnad2Y/zh4Ln6S/mZq7QHL2AXsuOK1aZY2ih/SbTJmYgKTNpY+ZBymObKsUcneRJHIOSONx+J96syOb9xop4fytrZZ1ztRZbxeEK9DKRGKyltIn29rmt23lKP2OpoL2y1ctiq5et06OHqGRmT2Ixyxbo7HhcTUXHFzEfL2LW5SXm1NmeWQGLr+n9QMvOAfGyrbkeswUSc8yVoyKYmEVMjV2yX5ntb+K5ngl9NE8oU5aaI491zD8Kna+2MLlhUec8Jwsdez5hUugh6R7tDmItmSOsbOZeTEgEXbLXESsJhEjVlBDOm5HBdIKHIt57yI+ujKXwnMy8VWXsdQFjmh/TbI+GkOaopG9l7eCxvRhiwvJci3rMm6xYX582IF12AoCYRfM0fDDNUNEoJ7rIi6horYptWcgLrTPNuWlwOxtFeO0tBPTZBK472WJtZ+fuZqI1j40IsY4xKYvN1MWchb4QN72AF36Gk5fS2xa0mgUDzA3a0KA2kRFbRNevtnRPi9nQgmMqDY2ZeWi8JbYYvtLKNTg2eDvIECpewCKAih50kql2NH6fPPErF0VEGK2GMCsC19d0Vc9pOpYPnKkGU7pa4CrUQMpBg7NIFcNXXlucy73tIEOosEBUCBU+jxDnCXcvLQzadsu1m5oTETmkS0z0dWLN1Da1yIb5LJzciAw4UPdScfcSw7dFhXGHem8DGUKFu5cQqi38+2VZNFV153AJQv319T3D0XjX5up19+7fFyy2D+yLFvfs3rufHZcGcTUWN1lOorXO0kq/h1JEu/zWXVF2xBpnNxG0HWKQYzUNw4VpxPZgFjRadpM48g0B2kFri3PVDJfTlm0DV4aJ9xEugintNDS2uWXs7EOZfRp3PLrQN9MG3Ed8CwK3RDHZenwo5WDciHqD8XCUHM6ThTrUuEKb3zPoxpTg5LFzdiZzsvV0uyROgXZK7pg83jL58N7+xnxvZWXHLU2dqEIzfO5WOaAOEkvRkjP6djR23KDtyJY4VY136A3GG+PO6vpGin9f/DCfWYroxMFPUjdxWCMYrhDbwUFmXwpRUt4lS75laQfjNN6gO8Q5Sp1BIiyTtayTgyfLo+V9RWqwNjTRg7pvuDw+2YHq2znojoYb8HQwoQtj6mUElE5K+xw8sDZIDqM9eC/0+d5mdxwMe/1D4WBjfaVzOt7wyh+CeEvWXobHvrO/3z2yb3UwPnIwgKwN1/Ydgbe9A+s94Dz0eJTve4q/NwoP7An9/dGd0T2H9u1uw7q/N0JZjPv5Wh/656n1leGoP2JxMvRJXg46BV9mQaWp3PJUbnmqolKyoNJUWtYI5xTmHPR7PWiTgtooz/w20njbSKOp0xNN7XE0xcF4fmq0hys9CIFuPhpvrm9RnxoLi605+hsH7x6OevOwpqwMujHDVNClzikPSddt5LNCP7dneLI/2jMcrI0LP0qjRae6/ZUtY+zeHK8Mh8dwnL391eGJeLU1tOxeU7N73ULvdXTvoHuUVrfRe5zWQHEQfgvfIzwW+paN4yCcFvqWhfBbKG+Wie5ddO8h/Oi7NvqudXxzY6VnbKzPr6wduz+dqGGRgKcskqMe04+tW5tLK3ysdLXjI9PF7vH8awMVxECZN1BmDFN1x2PjxDF7q9wY1rFep3N8Y5jLc3FuVPXx8+trh/Eb3JQq+ryucg2IalVXUZPoKiqKrqKy6CqqfV1F1Q+rzih+oDM8Oo16YXUdqLx+j49AiAHu2c49W7ln88AGGexoQbHMpaFxYn11I6ujyZU0iUplhsuj4Wrj9HBz1Njojvr9NYzO3Dh6ZNE6fdLL0CUsvE6sEPPkgrZ86qTnDBbHEw1E/qfoG93kuxsNoJmG4yP9UWNAKCeuGMYJZ9XyVjfwd1GwfXh83+JodGJZKFurp5zxKfPk+kSuhiv9ziZBCeQT0ADd8Upyb8476saRlZOd9QF55Pqkp4ZqOyDuRWzLiE3JsT6B+nTFehSsN6B7nOi7/D4trF+g4VgnQfUieE8c1vvldWxUh4hx0O9jnSV9T/c3Yf0J/S65Yv0X1o9hwHoqrF/DZ9/StLTeqL5SJJ4oPlr/symQe1L/1PdxXpdJ8D02vcd1R+7l9Ep1eASIPurG9J7oiq5L80PyN5veU90mSYd93pIrPVv2vDQuzU8lvRI/zsSXMelTBP9VhXB+jJv4LCb1TsECePJM4ov36pmLYv0geSa6TbIHjujtqH7rewWkDFRPSPWTtO9hwHFI3V0EsR6V3k8DUh4ZUtA2pnAR/Eg4aWuyf3Zu5kL2TOqL9Ofroc7oO3q9Kg2jebtwJskzaQe6J/ci6KmkjciezssBd7NFDmXzTTdwTN/SI0dDlIg/GnRW4n+tlc3+vvFocAzokP2D1f6GF/9v7OqfbOwdAv8RwBQ86I9aQD3dQSZKTU/fkChx3AXgLAZdTY/xaWZ8cZMHI7noO/ft66xt7OuPBsvuzn0N8tCIn2IEe/s9zd7fOQKfg0zE1/TJQgk1dee+RfK0mOCJUS+6anrV0s9rXCx4n6BCN0k5k1yT4qcFZyXOIUg+4LVXeqP7SZyEjvSXNogouTM+snR6DPUV/7+j1bijdWercWdrZ6uxs0XkyUm8aG08IGtavxOvbScHQI8u9Ruba50TncEKEZPEwucgvDsNSfm1fq8xHjZGm2vJchiEcbRYZD8ZE6jaFRLSALas1+iNBicSrLv645PD0bGtUa8lkYiblCTLyf/9RwYbfLZhre8M1iDrDE+WJggn429VGJYwLtGUtFA8WJYni8iQpOU8hywQfKjgQVhW6LitMhywKq+v9Mf9ldO3EBKlcXK49rgxiURakn4B1mZUziAsqpy0MiEFJM7VTBCW1Er3SGftcEogoTQNyN24n+ISqrbgyGClFww3oOYOc59ZhoG+0dhcb9yrHSII
*/