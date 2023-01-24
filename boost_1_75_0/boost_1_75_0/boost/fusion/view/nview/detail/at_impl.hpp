/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_AT_IMPL_SEP_24_2009_0225PM)
#define BOOST_FUSION_NVIEW_AT_IMPL_SEP_24_2009_0225PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>

namespace boost { namespace fusion
{
    struct nview_tag;

    namespace extension
    {
        template<typename Tag>
        struct at_impl;

        template<>
        struct at_impl<nview_tag>
        {
            template<typename Sequence, typename N>
            struct apply
            {
                typedef typename Sequence::sequence_type sequence_type;
                typedef typename Sequence::index_type index_type;

                typedef typename result_of::value_at<index_type, N>::type index;
                typedef typename result_of::at<sequence_type, index>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& seq)
                {
                    return fusion::at<index>(seq.seq);
                }
            };
        };
    }

}}

#endif

/* at_impl.hpp
/pcwKUkm15FumvM6oBy4wJS+K2qA/dLjwg/pGe65obzhHBtQZmE/qmH+Ny9vn5y8nTyoCuv6DVbqsTziHHplWZUmJQbbiPSFv1or32LdM9JWHT7bCS2hANhylpofj5jA6HsezHkPk0Sg9TWu2nF57CySg3wduc+WFiSuzkVNm+7LPR4N7y4QH9wtPcstrdQqmlQiexnG8m53Pb6OBFHzqdaYM0iTzwVMWLT4Fhmg3+2jHa1UX08o81ugiBD/MKthrIM1K6x8BlOZ7t7bpNrKSSkqjjHBk+zP9RQk0/4Ufhk9Tsb25n1f65VU3CnsxxzxNrqm3Z3YkXsSs+xc09nwr8RLfzEcmEWsWVbc+bItpthTK/JLHNiujMJrr6ugCH7ssuaOzR44NlOSfF4yO9CWt/2K+SBj2jILWJvJf75fGBCic654/tQybl9VKIo7ftSe2/d5mn/Qs08A64tWuOys8sEY4UrEFnVYL0mZsy91acL76V+4o9Ev33Xt1qOwSJfs/Yqct3ABNqwfSeglghXb9GMnzKQpkKeUeD39P82W9tWzAYJkPuBC4mgDnwKqy8Uk4CxK+qQmil1z38ccCaA7Carm9DlscHJwCbKh/2sW6y3LnZRakagbo1jbHgORZ5ykP9AVwxi/b5QUsgTq+1HWeK7EBxAoLQUZ6bOW4iBtcDgOsIPvdTxvlHGviXbI4tZwwh5kF3aXxs7JyCdX
*/