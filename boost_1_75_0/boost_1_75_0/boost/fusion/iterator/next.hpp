/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NEXT_05042005_1101)
#define FUSION_NEXT_05042005_1101

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct iterator_facade_tag; // iterator facade tag
    struct boost_array_iterator_tag; // boost::array iterator tag
    struct mpl_iterator_tag; // mpl sequence iterator tag
    struct std_pair_iterator_tag; // std::pair iterator tag

    namespace extension
    {
        template <typename Tag>
        struct next_impl
        {
            template <typename Iterator>
            struct apply {};
        };

        template <>
        struct next_impl<iterator_facade_tag>
        {
            template <typename Iterator>
            struct apply : Iterator::template next<Iterator> {};
        };

        template <>
        struct next_impl<boost_array_iterator_tag>;

        template <>
        struct next_impl<mpl_iterator_tag>;

        template <>
        struct next_impl<std_pair_iterator_tag>;
    }

    namespace result_of
    {
        template <typename Iterator>
        struct next
            : extension::next_impl<typename detail::tag_of<Iterator>::type>::
                template apply<Iterator>
        {};
    }

    template <typename Iterator>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::next<Iterator>::type const
    next(Iterator const& i)
    {
        return result_of::next<Iterator>::call(i);
    }
}}

#endif

/* next.hpp
CbyPAGWuzWO9BvloYgZlJTn5OeNEIhNOB0r73pBdZFIS4RLJ16ApLWKT6COj+PoMk5o/UyArjJRyUsqkNeTZQTkrzRSOpMPT+ZR3RfxLHsW4x1I2iRBfmkJ8rJIJ/1HlCbCe7RvF7LxrxFxnzcHTyx/Y9aOUN+yJ/6OfXtip94JMER4sTcUJA9CFZ+9KxQ1Ts+VewZL+70igyz8UXUR6iJjUQGdS1MFoNm0wnUUmczoqIgqfAuG8AfXp/ka1V7kxf8InXDoDkclF2J+WSeU1WwTuafWohfIxYEWxazOrdZTBzCjycGv7OYWalNKlSLGwBxZ+aeJQRwt5+mKItZ1CrIVeOxaPjmfN3GdjSm2yEmyXQ1ehflllvSgmj2pU/3F/LF0EKU+DEka2XXOVxfQm6jOjU8hRyt8sYyA5zITAbSgM2S6NtejwERWZFLroacasUGF/czQJqmrmlU7R5wI3Q+hmxdvx2tqLFlilgfS1F1HbEEiqPl4xRI5ZDbxfmHSPl5XAMOA8O79e2ateNwl3K3LQxnkRSe51CB0qzS11w02mdxBrvsCVFugDf7sF0c3LpRxYl1nmDrvSGMcg+aoBKN4BR+DcWr7sNDyf51E2U0uo4lvTym5wu1Vzfhu9BvEAs0TxZBW/wQqGzvRWUfqHTV+sL4S8y7v9cp9reSG6k6+9CNN1zfLF+W3Vh4JwOkp+juuM3haZanbsXXkn
*/