/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_REPETITIVE_VIEW_NEXT_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_REPETITIVE_VIEW_NEXT_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>

namespace boost { namespace fusion
{
    struct repetitive_view_iterator_tag;

    template <typename Sequence, typename Pos>
    struct repetitive_view_iterator;

    namespace extension
    {
        template <typename Tag>
        struct next_impl;

        template <>
        struct next_impl<repetitive_view_iterator_tag>
        {
            template<typename Iterator, 
                bool Last = result_of::equal_to<typename Iterator::end_type,
                    typename result_of::next<
                        typename Iterator::pos_type
                    >::type>::value > 
            struct apply_nonempty // <Iterator,false>
            {
                // advanvce to next position

                typedef repetitive_view_iterator<
                    typename Iterator::sequence_type,
                    typename result_of::next<typename Iterator::pos_type>::type
                    >
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Iterator const& i)
                {
                    return type(i.seq, next(i.pos));
                }
            };
            template <typename Iterator>
            struct apply_nonempty<Iterator,true>
            {
                // reset to beginning

                typedef repetitive_view_iterator<
                    typename Iterator::sequence_type,
                    typename Iterator::first_type
                    > 
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Iterator const& i)
                {
                    return type(i.seq);
                }    
            };

            template <typename Iterator,
                bool Empty = result_of::equal_to<typename Iterator::end_type,
                    typename Iterator::pos_type>::value >
            struct apply // <Iterator,false>
                : apply_nonempty<Iterator>
            { };

            template <typename Iterator>
            struct apply<Iterator,true>
            {
                // eps^n = eps

                typedef Iterator type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Iterator const& i)
                {
                    return type(i);
                }
            };
        };
    }
}}

#endif


/* next_impl.hpp
y0V5ZTTKK+O9nnFoWZilXItF32qkS9Ioz1HWez3daOWZ1TyQayiVh/aBt/XLsvRZRihvo3emxuPfDNOuBdO+H60mM33Q9au019YwVwUb1Ga2O0uRINq/o5VmFvBp3wnKE+0PZrYGrQ+RVbTBOou0trPeLaP9e12xhgg7cWxQFooBrSCzbI3yFaY9M1p6ZiWsp+fT/h3NT5r6cwkaBr/gHCNTv6fUjebRSVt3/hyd1yXWt0EESKsX/dSHzgQa2CCR2f0rYTrKs6ENujGbOD+zg+qJVpZZyhwTbdbIBtuYTQvsTt/hsDcW9yHCrq45O5j6tgmuPX7SvgzaKj6DNdyd2FpeH7ZBpz7y+uDu5mxjo7PD7dC1eM72XUsoFoM2hln05PpFFHO0xXsUZr/+s6CLYm60ycysi647FfsPX3cd39T1BQD8JG2hSBrFoYRh7bAAwy3Fx5CU4lqkMDxAcQsw3ALDbcEdgg8P7hDcIdiQMQgyYAzG7/w+vHvuST+fvv/g8/2ce++59u57SV+srfDMx6zdjBHphLnQ2jGrH366jDBorYO5zJZFLH4szIfWjNn7vP++ona20cFEZq93j+gqLICWhdmUC/9spvra6qABs/P7xvei/NB4O9ftahwtLIjG++zK6ba9qT8TdVCcmaNinW3C/CnMvatDK2GGdjr4wGzo/XxxwhztdTCJ2f0Jr7JQDh10cIyZseaXPWQdddCNWe81+ytRO1PYnt3h5Wn8knQwnlnJ1Y0vUg5oTmY39scPEJbYKXS+FD9SJqswD1ocM9eC+tOEQWcddGHmL7xd2Zf6dnejFVBsK/Tv++rIX8q1uEOSD02nrOltUKT4lm7NMggzdFHOPYrRbzWg2VIYnYnQHGh6ZnRGQXOmMHo/O5o7hdE72NG8aJmZ0Tv70fxo2Zhds4W3FhZEq8Ws8/JZw6mdXUPro+dgaE40Xua93XdmUTvRmjBr7+y4TBh000EVDeuX/1Zdp7juOvgC0la3XVeDcuihg53MfshUkNri66mD6azMaQM2ZCJzKvu1YrRfo9l643Wa2eIb9zsJS0SLY2W+j3m1j3Loq4P9PL/9R5dSf6KtZpZ1/ZXilENyaL9snvQ8nzB7Px3EaKW1OFfiDtU3UAeteJ+1XHCF8hukgy3Myr7+JbewwJDQ/OgcgmYYinsWMzq/oNnQUotLVDE3WiFm8myDuaPFMpNnG2zLsNTLtKOl1s5ElTj3MJW2DFNpy3CVtqCljKPPp9Ecim3//+fhPyW9EhZEq8dsp/bdSmGOETrIwExXe0e8cr8CiSNkmTugP/ubmKLgR1uo2E4oAQ8G7H4ozOPSgYYZ3eOhedEaMqvRYsQ5YdaRylxSbO/UsW+E2Ufr4LtwaW+yDqE453h5XkKT5yU0F1o8M1p/aEG0WswybPp7gzDHBB2MYFblh8q9KG6CStzE1OI6QRCtlpLf79AK1hh6lxTmnqyDllppT3rsX0c2DY3FjfdNVMavPzimyzHaBU45RhjnQ6uj2G6M2zxzoUOYdQZe/5hFX3rwQZgfrS6zhPdHTgqz/YrXMY203lObThAGs5SzjWLJP17uQ21Ba8Os/0XfOGH22Toowqzmv/M+CnOhRTGj6xiaB03PTF4fsD60f5hVNjW5LQzm4lmfWcfsvlqUO9ppZke0r7OSzdNBUWYZ28VcF2aYr4O2zJrfaHCDxg+ttIb19fN6ZNaFyv6iGO0vaHa0PMxoL0BzohViRvsLmlfFgmixzGgPwcxsi3SwQ7E9OHcTvi5x0dpcrINkZnnfd2skzIe2OkxaLfd3V4QlLtPBDa20MwV/ykvraKUOzMzm9zt+Wph7DY5RuLRfj6W5S2Vu0sE=
*/