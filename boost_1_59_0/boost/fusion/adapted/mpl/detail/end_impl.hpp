/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_END_IMPL_31122005_1237)
#define BOOST_FUSION_END_IMPL_31122005_1237

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/mpl/mpl_iterator.hpp>
#include <boost/mpl/end.hpp>
#include <boost/type_traits/add_const.hpp>

namespace boost { namespace fusion
{
    struct mpl_sequence_tag;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<mpl_sequence_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename mpl::end<
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

/* end_impl.hpp
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
*/