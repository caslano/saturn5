/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_BEGIN_IMPL_31122005_1209)
#define BOOST_FUSION_BEGIN_IMPL_31122005_1209

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/mpl/mpl_iterator.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace fusion {
    
    struct mpl_sequence_tag;

    namespace extension
    {
        template <typename Tag>
        struct begin_impl;

        template <>
        struct begin_impl<mpl_sequence_tag>
        {
            template <typename Sequence>
            struct apply 
            {
                typedef typename mpl::begin<
                    typename remove_const<Sequence>::type
                >::type iterator;
                typedef mpl_iterator<iterator> type;
                
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence)
                {
                    return type();
                }
            };
        };
    }
}}

#endif

/* begin_impl.hpp
WYweGU43QzA90oY+sEQ6vobIyHpmcqsU7cuSubUlOnfsWliaYfqytNyLvTM2Sfw9Thnwa1PWHi26RVYDV3ruEt2jtJQ6sR4oH//c+cSn5XksPbI1vbU8nzOtStdH6TUeEHvP0D//G+PXOeJXowPORe6qcVZXPjNzT2LlGM+bXN7pHDNz+ZdP1nFCSStP+yZfnFNzT2o26Sb5ZK/rnp+zVqFzvV/yS2mrx+75c7F3itXBamXu
*/