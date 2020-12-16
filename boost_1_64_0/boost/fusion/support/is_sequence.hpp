/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_IS_SEQUENCE_05052005_1002)
#define FUSION_IS_SEQUENCE_05052005_1002

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/support/detail/is_native_fusion_sequence.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct non_fusion_tag;
    struct boost_tuple_tag; // boost::tuples::tuple tag
    struct boost_array_tag; // boost::array tag
    struct mpl_sequence_tag; // mpl sequence tag
    struct std_pair_tag; // std::pair tag

    namespace extension
    {
        template <typename T>
        struct is_sequence_impl
        {
            template <typename Sequence>
            struct apply
              : is_convertible<Sequence, fusion::detail::from_sequence_convertible_type>
            {};
        };

        template <>
        struct is_sequence_impl<non_fusion_tag>
        {
            template <typename T>
            struct apply : mpl::false_ {};
        };

        template <>
        struct is_sequence_impl<boost_tuple_tag>;

        template <>
        struct is_sequence_impl<boost_array_tag>;

        template <>
        struct is_sequence_impl<mpl_sequence_tag>;

        template <>
        struct is_sequence_impl<std_pair_tag>;
    }

    namespace traits
    {
        template <typename T>
        struct is_sequence
          : mpl::bool_<
                (bool)extension::is_sequence_impl<
                    typename fusion::detail::tag_of<T>::type
                >::template apply<T>::type::value
            >
        {};

        using detail::is_native_fusion_sequence;
    }
}}

#endif

/* is_sequence.hpp
qyRVMqowrx4bw/e+C4SvKgNRpkoH7SdM1BZ4gc4N2hRYBGHOzjzm5IkTYGJGmfHpqTs/vN+OnzhtwkaO7fgYuHSyACNGTgOGjEFMB+eHMzMeRmnEcLtxfoe47X0ebmKebzsAODtuCQhtIQ4SjJcp7ulmPRxJ73i3zhz6b7il7S0I+wE2oTCcHd8XRI4LbWsdp2V1o2JM5vP32fZplHNTrg+dgU9f0tKtrQfMWwk7ryMW21rjXV8bN3mYiWli+VZmAG/bqEsQ2/oPk+i2EbEeV/f9V5w22bA+efYT7KQCYp3VAYJ1K43p/dDHeOWE9jFxdP8nVpcV8ZdnPfyk8mJ7yUOAx7PYQn+Dg7jdW+yFOz9y9x/yloBr/QUtjHDviD4TCQ1YMf2/3RpoeB7buxw/vA3F0XLYNv7sbRHnt1abJmLfffi/YE26GGupN94qLoosS2924H0z4Mh4e2/TX/pVLg4CjJd51I2lub11bjzasP6TT/b8RcRlWZcx441F/Dwkqh8kjMfwu7q1PB52cRbxDvQkrUshAli3Mnmjdcm7+2A3vZizMky54KJmJvv5tbH2hbupA4xvgl53rg0m1XwEz7pDbWeO/lnctB4DrZymgsd2dTcLzSbGHiN4XkGn1HHMyiw6+ZhI8jZAJbP4v7j4hbSSeVXVvMXXlXxaP/1/EnxeqVTlKmIhBAB9zOLTFO/w+F6HkbVWP2JQkYyYjvoIHGCzpsOUn4A2oG8vjtC9QF7XZVqFksW8OPmYDC4cNFvPZwoj+3f9rKgogyCsmd5o+pt3G3/m0T2/v2EcyCoSINRPpWzzp/iTnoxuXtCehvBzppJMCP0gZW/W+6MvdUZ5o7oMRFS0dxpNSPYY3P0aPxvzeLuBMR///hr3nkfWJbRTDMmUp6kd+ptYzy9FJjiPBeO7o+E5/SLFtmcsuvtGlydWTAtHWIiMwVgabukVuH3hMFzRzNp6LspUCq/8IKi29q+CcdTcfhE5q4Kai6DeI53W3FZHRIYIAvAf8LecTaH8uWU6kaZRHMZSMCi7dslanXxUW4f1Dj8VOPhHllwlZREqxLdox6/LPoLnWQIirsoWP9e7F5kNqN8YmZci5gB+TPdPyJOs6tp1G2Xb5XtUlcisVKJw2LpaODbqRwN3XBfAIosidXh4FZuMyPnnPXROJbbTltYukjTWI6HjIkre/O83mDbWl5203bjdBzoM3A8swTXq+llQddkz2vsPWvrzWtejSHvtLNI2O7UH2qQf6mj6YtXKntkmYRpXbtnhRjDjtEay+Kb3Vh1Nl9zysFt337FGyPPS2xqaabK7oQ9C8p3oPL59O6BZO3L8Lm8P340OCtYQa+t1B/1d29rDSHL9xt5Rf/fPnVUnj0+kZ7lK8Ezl+c2Of2jWMRxrq48mvoiqKs54GHaz6SnZ+VHCOy8yDwYsqkOZ6DcRp04Hk45+Hd/VHl8uiyou8pTF/53v8AJ901mlJU95xnjkc/X1z+9u+kpXpfUtYMJ627fJAw+D0uDiPjvj4dzBgn36+P2AszJgbdr0d7T3cPw/dDZxBzy6Z4vyBg+DdnXomwPp1qct5vE6n462dejvym3rR3OuzQRKyYyylq41z3axJeN1rYoqTZijdW4Y3PRHNP08DqpQSGaUvr33iQs9H/lFVqRKVoyqezu2g2g/0OMrlcrSVNWUbwv5ME4N4cuYEIGUaVyxPY4LnZ8lfO9K+FPGVS4SJQs2+RiB8e26tvmby/8oUaY8jdOCtcriFr2F66OLlUwJyas0y5nVLNO+mn0MffubJongRcyotpn6xDr6GLo3C4s6qgLB7ImG5jHn4mtWpxkv07pAvFNr5GGPoTKkwiSP05A=
*/