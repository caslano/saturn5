/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NEXT_IMPL_07162005_0136)
#define FUSION_NEXT_IMPL_07162005_0136

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace fusion
{
    struct joint_view_iterator_tag;

    template <typename Category, typename First, typename Last, typename Concat>
    struct joint_view_iterator;

    namespace extension
    {
        template <typename Tag>
        struct next_impl;

        template <>
        struct next_impl<joint_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::first_type first_type;
                typedef typename Iterator::last_type last_type;
                typedef typename Iterator::concat_type concat_type;
                typedef typename Iterator::category category;
                typedef typename result_of::next<first_type>::type next_type;
                typedef result_of::equal_to<next_type, last_type> equal_to;

                typedef typename
                    mpl::if_<
                        equal_to
                      , concat_type
                      , joint_view_iterator<category, next_type, last_type, concat_type>
                    >::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i, mpl::true_)
                {
                    return i.concat;
                }

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i, mpl::false_)
                {
                    return type(fusion::next(i.first), i.concat);
                }

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return call(i, equal_to());
                }
            };
        };
    }
}}

#endif



/* next_impl.hpp
muki+dyxyFPceHjKKKd0VSTwOLlG6OiAxXqzWBeqkmfPNBr77JkgGL0z/F9Rtqtx5NVqNZpWM9d00jodtPlsWY5NrFWqzV0+zycm9KyKNBr6CmSxkxUBxbVuwgotqRH6Vj8Efjk1Nsxa5AuxqrqfJUw9nWMxhTVHY5FdsjTJi+ZxUTRErreN3kcWCtnEOjuvqzBXy3YoatEEHN6iL+7Mml3mRUQ6I94E9XDnYv7FuyJYUDN0AVCwSSGlA1UcdaGZIh5XOeCcOJgMmFuKkLhcmFMH9oJol1hYcTywEltMO6MMBMweLEdaZgFZ4SdoyFklNE0ImM6aQefQMulnXFOb+9ZX21sE1GkJ44MGwQhM2re9PSasTdLYYk0ODknv49aWKG5KxRdDo3dinLXPev3PpALwPbbVS/GKDrtbpILbYNWoH671/WXP5zDWfuf9hyH50O636T43bktzSgMyNccOssMERySAoaNwwUEZdAFrZo6mFYGIjeTKg3RgAqYTab3EEL5oh34lvfoHHkUo3GHCpeESgT220HsQKjHz0luEBH1SvO448XxwoIKGDDpSYTaCc/9DSFN3ngt8rOwdlL2F9FkboJILkBCR5DXKaKTgbR2rYpN3Yihc9ieDM7pPS4MNmuyI6wxgt//cF+73
*/