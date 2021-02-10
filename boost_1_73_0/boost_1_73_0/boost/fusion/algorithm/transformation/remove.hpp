/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_REMOVE_07162005_0818)
#define FUSION_REMOVE_07162005_0818

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/filter_view/filter_view.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename T>
        struct remove
        {
            typedef filter_view<Sequence, mpl::not_<is_same<mpl::_, T> > > type;
        };
    }

    template <typename T, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::remove<Sequence const, T>::type
    remove(Sequence const& seq)
    {
        typedef typename result_of::remove<Sequence const, T>::type result_type;
        return result_type(seq);
    }
}}

#endif


/* remove.hpp
nGjAJshwbeFCdCMOsGuFn8uYUKNQX6AIjcF46f4KUuibXeehzt9NohsTK1Lj9OzFC+Yjmcv8fsdXsJaRPn20c6PXsk+Ho2a9+Cj3pJ2qhtQTv9UutPLbjdPT+ltOlGRnJvp+BzTlbNxW/g96lqaVFhWAt9jM5/tp6jydqpMd35EJHMwGapufnZQw4LQFyDMVSdpuO8WwSvjwchU8vLSCHFItARJYFZaQBin5LlR66bWVPRbxH/GNVkNKngXiJ5BRRjmn6AyE0DFgDbSGAYO3XVHsbuGXY+0cnHkmF3BIb7bbcFdlr7ri69wjUdKoNEP/ipuVh2J8QEym06DgDqIg0Eljb2RgohSgE29zL6LTzjWXQpWJM1gkDyiowIk1kZe/IiOnSgKsCpiIUpd7UqMAYGvPKuQ2y59Fe2XNwxvOvksEDTlaC1PiZYT6rdnylSqGZyS54ZbzQLFF4lpI+5UHYKfGi6V2Cc2kJkYOFAJZfUeFEhRuDZL1frTY105v5eij/LDEQYRl1mihkbUMR8QDLEUS9jSzknBRTzknMd3msjNK3dL4BmEn3xpfJNoH8DfndyOJTxGyaXLvA8Yh30JZZ2H9YZqy6tcWzU5g5qUaO/s07eoMM1DSGX/drTV2QpOK9GqP3f7pN14riQH4
*/