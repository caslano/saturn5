/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DISTANCE_IMPL_09172005_0751)
#define FUSION_DISTANCE_IMPL_09172005_0751

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/minus.hpp>

namespace boost { namespace fusion
{
    struct vector_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct distance_impl;

        template <>
        struct distance_impl<vector_iterator_tag>
        {
            template <typename First, typename Last>
            struct apply : mpl::minus<typename Last::index, typename First::index>
            {
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static typename mpl::minus<
                    typename Last::index, typename First::index>::type
                call(First const&, Last const&)
                {
                    typedef typename mpl::minus<
                        typename Last::index, typename First::index>::type 
                    result;
                    return result();
                }
            };
        };
    }
}}

#endif

/* distance_impl.hpp
mXOPgeU2O47pBkVGq9zEc7y+p/z+7gMY3kz/8kbAWSKwVYTsw0jqx33juZSlFyHOtq94cVLT8DpZ6cGzmqlNVcCpg7xW6IoetCV26fYTk+wnKLP4OyMd7WEEdCKQvTP75e4vzzVe0b3EKvyTbT1Sp9B5ZgjHU60fvNyOW834wR9O/XyUla3XAQYZw9GjmXbhqwgVxr7/PDYW8ief187E6ihs1Lj7A7ecBefFsnWBFjOSWcouFTd2VdvhqLlIQVhPs36NcawCYmHYa8TS1/Mi63QokNwst2XRhf6XjT4rPmr2reOOWsfs+mXgUdCaP09wKsED0wNncV9H9jR6fPZnCgL7GlV6lVlcsjp7PSXM5EadcvsayoHzVp3XYnDw1Z5YegthgVlFJ/AnKO1uYpSLxt+e486Ce0RKzxygPbHCU9OgceG68c1uNGk2606BzcFHhGs5WaEqO1tDZ1oOMJZ/jMHuspU7UkwixWe68P4DHA8j63EQ+OrUJFaSMB2+9OiFkeLQGEa01x3VCc1ZE2uomLGG99mO3H/LlIlauDf0ZTidP3H+PdCP06lxcQ==
*/