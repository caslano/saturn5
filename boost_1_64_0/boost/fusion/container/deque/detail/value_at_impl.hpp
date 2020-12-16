/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_DEQUE_VALUE_AT_IMPL_08122006_0756)
#define BOOST_FUSION_DEQUE_VALUE_AT_IMPL_08122006_0756

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/deque/detail/keyed_element.hpp>

#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/assert.hpp>

namespace boost { namespace fusion
{
    struct deque_tag;

    namespace extension
    {
        template<typename T>
        struct value_at_impl;

        template<>
        struct value_at_impl<deque_tag>
        {
            template<typename Sequence, typename N>
            struct apply
            {
                typedef typename Sequence::next_up next_up;
                typedef typename Sequence::next_down next_down;
                BOOST_MPL_ASSERT_RELATION(next_down::value, !=, next_up::value);

                static int const offset = next_down::value + 1;
                typedef mpl::int_<(N::value + offset)> adjusted_index;
                typedef typename
                    detail::keyed_element_value_at<Sequence, adjusted_index>::type
                type;
            };
        };
    }
}}

#endif

/* value_at_impl.hpp
+eHkuVc/r3V97dxi8ne6/cr7O827YU2dP2TdvmRKnl2CSUgGZdKNf7f8J2WAAXbzzsn8Wonqe2a78rzawlYIz1exHbOn8CXKIO+ylKf2fZv6iVHmA3TxLHfmO7ahed+Wa1C+y528V4t18m4qxf7dlLzbNZ6TM0zXL1+e9w3eZXV1ModrmkH/8wTdewx5R2jwzq8WS6Z9QznItxLl38fl3zND7Y/fv7aUNv1St2Px5VD8l3ZfaMa7cGMOMWfv08OclHuE/F2tZ6kp+rnkqHc+pLWEEMrf/L8nfdr3pAbzummfIy5I4+D1sh9WEziGOdHb5dOcNT2Z9wnX3pu5M16is/c+bdX+wGwu29Vcf9OngjWfn5HH08G29+W/saZPzoma93DauesWyjJzQu2vw0Gtpb+NL+tjD1TyXGSXZ+u3HHk3VP6x9dRPrKd9H2SQ53CDbwNmg/cmYQ7lEKG+Azf34g247ThQ9ytT7WrKQB03T/4WbfDOJVbbdknK9SJl2qS17Rrt/8O1ck0yfueinq8uSDlelLrzFuEba39cmWPvWh92vsFYqIDutVFQyvQNtqEt01iD/AXJ38rKNEDqVm9b2SRbrB+CZBwItW+5s77EP38fck/7fhv38a64vujGfcud9xU37lvuvC+3cV99533Ojft+O++LbtyXu+L6qHvaJ9y477fnfdSdjX1wxtrn/PThHsln67/3uc/CTzZkfPTAveX3LS8gSPtH2kXaxvCtK/2mlV/7Kra+KB0wCDtiO+yCvbErJmE3XIwhuAJD8UHsgbuxJ76GvbAUw/Br7IM1iLcv+mE4dsYIDMP+OAIjcSQORNt8FtKmEQ8QCh3msxglfTPjsD2OxjE4BhNwLFowAWfgOJyP43EXTsA9Dn1gSyW+IIlP7TsjfQhrYC0MxDtkvSQfaTeIebJeDYyX9d6TPkYlGIkfYBR+iBPwI7wHP8ZU/BRX4Ge4yqHPe4nEc0ri0fZ5f1XieQ2D8BzGYDEOxzdk+2/iFPwjLsDzmIt/xmV4AR/Ht/EYvoMn8F11ni1p24cvSzq088Uslj6CSzAAl2IgLseOuAL74EocgaswBVdjFq6R9KzFtbgOt2MePobr8Xl8QO3rKG3/0E/S46yPdR2cpN3f5ayXKutNlvWmoFovL9jW22VQL7Okz30OdsMZOBpn4jicI+U/D2fifCn3BbgJcyW/i7T7XeI7Wkm/37+R/f0d3ov/wifw3/gU/oCl+BN+LX0Qu7CdKtgNq2IYWvscYnU8hDXwMNZU8y3t5vBhg3yfkvr3LHbE57A3FmF/fB6j8QWchi/iejyNG/EV3IpnNH34SyS+1hKfto/4VDkeM7A2TkN/zMQgnI6t0Iwy36O0ZaOsZXva+R6flPQfwVb4FN6NRzEGj2EcnsCZDmM0qH0zZftdZPtq30yZT+cODMKm2Bw7YwuU9aV9GOsYrO8n69eV9f2xA9ZTz0PSdguXGZyHNkr+HsLOuAlH4RYcg9swGbejGXfgfNyJ9+HDmnyWSDzNHNMpfetr4kFsiIewKT6h7ldpO4VDDfbrbknnHtkPe7E7PiL1aD8OwgOyvRKCWbY3SY6PRrbzmtrnvDG2wWBsi52wHfbADjgYO2IMdkITdsbJ2AWzsBvuxRDch6H4JvbA89gTv8Be+HcMw2+xD9ZWrn/oh+EYgP2wOd6FURiBI7A/jsMBOBEj1XmxpK0Tpkm5aefFGiz5jMaWOAR74VCMxhhMxOGYjCM09a6oxHm9ayj1rpHUuwCpd41lfcpT2gMp7YRs67ew9VG1/izS13UmBuJsbIdzpbznoRnnYw4uxIcxF4/hfXga78ezuAQv4lL8AJfhl7gcv8IVWJ0=
*/