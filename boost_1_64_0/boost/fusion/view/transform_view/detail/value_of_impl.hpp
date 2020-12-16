/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_OF_IMPL_07162005_1030)
#define FUSION_VALUE_OF_IMPL_07162005_1030

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/utility/result_of.hpp>

namespace boost { namespace fusion
{
    struct transform_view_iterator_tag;
    struct transform_view_iterator2_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl;

        // Unary Version
        template <>
        struct value_of_impl<transform_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename
                    result_of::value_of<typename Iterator::first_type>::type
                value_type;

                typedef typename Iterator::transform_type F;
                typedef typename boost::result_of<F(value_type)>::type type;
            };
        };

        // Binary Version
        template <>
        struct value_of_impl<transform_view_iterator2_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename
                    result_of::value_of<typename Iterator::first1_type>::type
                value1_type;
                typedef typename
                    result_of::value_of<typename Iterator::first2_type>::type
                value2_type;

                typedef typename Iterator::transform_type F;
                typedef typename boost::result_of<F(value1_type, value2_type)>::type type;
            };
        };
    }
}}

#endif



/* value_of_impl.hpp
RWYoGMe2t83e47SXJGF38VycENhtBd/rYHQvyMb6PxoPbca/LyjdREv6+fx3T+uvve9/4iqZ+TF+/su3z/37upMFwlyEFY90ekAWBrMS1mCwIY3MoIwboev7F1kCzFVY+JBa/clSYfbCcg5lFimwwVoGjGq/r/lr3Zcn7y6waloejF7bPMQ8p0q/WkSmHefzmW/akuB1ZF6wgIK/y8q3+J4LrpH5Z/Drz4I5XUIrk4XDrIVdsp+aQhYDsxJmX+RhBlk8zE7YtB8jE8lWwIqJGmLPnjlAtk4xB9fmJci2KLZlwMNnZLsUs9iTVprsoGLzu9R5R/a3YguOxiWRnVWspsPtoWTZMC+zgjwfwSLtwvqSJZ3l57h8q1XRoQhZMoyeU2Fa1ciBWWRpipX23redLANmIexw+2L1yLJglYRdCmzakz83PVd4r3uCa+fChVK7yXxgjsL8Ti7cTBYIcxY2JWzSV7IwmIuw2cUbLCWLg1kLe9x0yR9kCTBbYed/lLpFlgSzEWZVPeUyWapiWU/GvCZLV2pYYHO0L1kWzE7uJaiGG1kuzF7YNF+9CZn5eaP1sO8uG8n0MJlnW7OoZDJ/xX7JO96fLAgm9+Lyd4gn56lYn0YPL5HFwCyE3br1jwVZvDKu8rGnDpwnTPZB7+zclfOEOQnzvtFdR5YBkz2KGTDCl/NU6nvpm1OT81TWW5KXfZ9Mu2C83i8TR9/gPGGO0no2sOM8FWt19dJYzhMm1xvX+0ARslBYeWHnDH4T+X0xrIgG0/wDczSDtvbo065kCTB6foBpZXbtWkTPVRnCnmnRWqhLp9EFNkzTMguvv+e4HisVafjz7PbXAoS9wN6OHxlG77lGGGD0+yBealFR3xNWdWS7yPfkfBtZocVKsmSYg7DsPt4byNJhTsImd/UfRJYF0wkLm/OJv/+SC6P6XuFx0bmNvelnoXwuFY77V4uI8mzm5U0WCLMSVnTNUiuyYJiNsCinTYfIwmDOwjT/09XI4pRxnhX/mkyWoFjjOmf9yJJg5sJ6Bw5bSJYKsxS259m/FcnSYQ7CcpYNmUiWpYy7dSXXmSwHZivsSkpsH7I8pb7E9rdsyfSXcU3LfR44vJOzVqzdgFV/kgXA7IUt2NjiBWcNc5BmPus0WbgyZ7Wh7cLIYmCyvtU9q8eTxcPshHVuejWbs1asVpnYy2Rpyj7vDP2YSJYJk+fF/3dvS7JsmOztol4hDclylRqsbaxXk2lXjOccdsWc89QpZvLMag6ZF0wnrEbrZ7c5a5ijsLiYG4M5a5jc59P4yN1kYcp6f7pVzSQzKOP0sdEHyOJgzjLPq3XDOWuYzNPu+LaXnDVM9qHcuYcpnLWyXvSvo6dy1rASwn6fa+hHpl01rn3i0KfVyfQwuc9t7Ru15cxg5sKOdu3bnSwIJmtYYnPxFGcGKyXs8n+CEvkMwlyEaX+umkuWDCsj7H566nOuHaYXNm+sqYEsF2YtMzvwrSmZdg3PHcIafa4zjswf5iSsbrVOPlwfTNZQ7GNqBPcd5ifMdNmeZ1wDrKywpOZxZ8iyYO7CYsPq8feFteuF9+t3Gn726vqrWfzzxTCq4SMeB5h88SMLh/kJK/Gu1kKyFTB63QrTnq9u1pQsCWYpxrlU7tCQLBVmIexx9pvbZAdhxcWcs+aZdSDLgLmJceOOVehDlgNzFbbz5JDJZOZZuO8K61xqkhmZHmYj7IL5o1D+N/dggTEFz7eftBF9R5gHDaTvasaFm3Ken7VBlV81/GU5fecyDUbvN79o1ep0CprA//5DLizu5/vNr1r0yMAdIVFk6UN4znyL6ZEdRf17B6PPhb+hfy87Fk0hy4PRNfZ/c+h/fCo=
*/