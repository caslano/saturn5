/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BEGIN_IMPL_07202005_0849)
#define FUSION_BEGIN_IMPL_07202005_0849

namespace boost { namespace fusion
{
    struct reverse_view_tag;

    template <typename Iterator>
    struct reverse_view_iterator;

    namespace extension
    {
        template <typename Tag>
        struct begin_impl;

        template <>
        struct begin_impl<reverse_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef reverse_view_iterator<typename Sequence::last_type> type;
    
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence const& s)
                {
                    return type(s.last());
                }
            };
        };
    }
}}

#endif



/* begin_impl.hpp
4tlRwCy1ZvAWiSrVRe3zt1cxeNpCx6b23cWFBTm1xgWAwqxfJVZkzMecOVBkLZx20XIgcuIvb08bb8PWcAf8LDxXH3wXexCgQYuxeIDwJqlYdbOeynUfVjxKchKMLJmXSPjfZ3EebfJOVrUsE7xiPMn+5vgUB/c4PacpghBUdlV4ZrTzmYdTkirYyF1QAEzeRjBCQS1fGOA7fsfi45itd2fRTymoaaiTCZ6uFvdXqmQBFO4N2UpHHfbnBq4wrLZ3hDg1+4+wrIml1ySJqyUG9IEHbYF+3CDbqbW1sziLwL1kDCrky6yXff8xrRltUcpY3V/BF8oUg20qxd8VzDZS2I85VaIqHYYECdo1uPANFULQd6BnUpLJgLZm9S8lm0sFIWuX+xpR45Sp3WFxwpQGxE4g2LfLvN7VF5NNOBDfNQ87RSH0s9L/2cr8NTYAlnT0vHNU/BoApjN/9C6gOYPmVZNbnCWyUT5flWyo9gSSkmT0Mw5wY5464rrCPExShrSFGCYzLtRk3M5jwhqJi7e0zoy21oNQGMaI32J9SUlR/e7eOC/Q2+c1GyX8Iw==
*/