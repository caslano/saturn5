/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_TAG_OF_09112011_1842)
#define BOOST_FUSION_TAG_OF_09112011_1842

#include <boost/fusion/support/config.hpp>
#include <tuple>
#include <boost/fusion/support/tag_of_fwd.hpp>

namespace boost { namespace fusion
{
    struct std_tuple_tag;
    struct fusion_sequence_tag;

    namespace traits
    {
        template <typename... Elements>
        struct tag_of<std::tuple<Elements...>>
        {
            typedef std_tuple_tag type;
        };
    }
}}

namespace boost { namespace mpl
{
    template <typename>
    struct sequence_tag;

    template <typename... Elements>
    struct sequence_tag<std::tuple<Elements...>>
    {
        typedef fusion::fusion_sequence_tag type;
    };

    template <typename... Elements>
    struct sequence_tag<std::tuple<Elements...> const>
    {
        typedef fusion::fusion_sequence_tag type;
    };
}}

#endif

/* tag_of.hpp
bVQy0bPBMtI/cBnWaVzpsDQ/6zwVmkl/Np8M6V33et5XExlKPTW7De8YWFeSuPbHx/PZYnS5uOnfjCYfeEKppMY/aF5YfZ1lNuEyq1ZGb1BZdWKAjKGTHQ6B/saa5bgHoPnU3NA577w52Kpi5fVOhb819iABWZvru5TOOJ5jjg2jQFgKvzlRK49hjVPaMlbzvOkxrWm/T93r6ailOm8nuyi960/ejqZ9aoEBwkWPcqF5c0R1OZq8HVwAb/OvkF5O+tOrBVrZsN+bHZE/0voR88HwchRgDFr5v8Yjxbqzq0V3uhhMH72SsXDH8n9QSwMECgAAAAgALWdKUm1xrsU6BAAA3AgAADEACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX1VTRVJBR0VOVC4zVVQFAAG2SCRgrVVRb9s2EH7Xrzh4L06gyEkzIGubFVMTpdHiSIYkNzNgQKAlKmIrkxpJxTGW/fcdKXlpkgLNQ2XYkkjed3fffXf2liPY/2mX4xk4+OGV22+OF953RjMpvtBCf98gzx+g/6DhEu+vcDWBR6uHfA9eZfUAY2uVD75OzXOev8Ld0gRpfibGeJmbR1zpLQf7M9FuJbutNYzP9uDo7dvf4ADeHL45dOGccEYb
*/