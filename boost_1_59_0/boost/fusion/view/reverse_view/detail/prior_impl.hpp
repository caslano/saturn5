/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_PRIOR_IMPL_07202005_0857)
#define FUSION_PRIOR_IMPL_07202005_0857

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/prior.hpp>

namespace boost { namespace fusion
{
    struct reverse_view_iterator_tag;

    template <typename Iterator>
    struct reverse_view_iterator;

    namespace extension
    {
        template <>
        struct prior_impl<reverse_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::first_type first_type;
                typedef typename next_impl<typename first_type::fusion_tag>::
                    template apply<first_type>
                wrapped;
    
                typedef reverse_view_iterator<typename wrapped::type> type;
    
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(wrapped::call(i.first));
                }
            };
        };
    }
}}

#endif



/* prior_impl.hpp
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
*/