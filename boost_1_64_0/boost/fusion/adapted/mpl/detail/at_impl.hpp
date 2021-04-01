/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_AT_IMPL_31122005_1642)
#define BOOST_FUSION_AT_IMPL_31122005_1642

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/at.hpp>

namespace boost { namespace fusion 
{
    struct mpl_sequence_tag;

    namespace extension
    {
        template<typename Tag>
        struct at_impl;

        template <>
        struct at_impl<mpl_sequence_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef typename mpl::at<Sequence, N>::type type;
                
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

/* at_impl.hpp
e4jr787iHXeas8xdCl/Y85krKZ29jo9m6K0CGPlWa87R4n6R0EVDuUQ/G8n0/hGWWI0+C1bx2B2a27zr2l3XU/Wbq/nlhT5uekum1e1t5uieTTb6HdbJoXaNZoCmcI9/5JDFLKQ/zgA2bVyb1iAK0Y/OEbMcO7QKYQjvQhYZuYLke+gohjw+j2aWyrjpRP8WQPmGE2nKQHXmPV4/3e3IaEYtsd7w86abWbgmxHZW/wue9kjcdscFet/kTTBmpPAv/FlOvT3XIq//FYwRaIhKkipbTQuy8+SQt2FOI8yURmS2ch1Z2qwM5/tAnebEmKBN/VDXqw6QnliuMQHAqn5mTdVadg9/kNat0bQZ+3/MgsQK09ZckWY6Tuh+4qvGtlX8BWDqeLFwwwR1c1omyqOLThSq+0vQSHVSlcIHuZYv0/PwPXUeol40K2wRh3bDgI1fdi5BS6VxeVkFcsMqtk6SuXNsRpdPCfxTAx5q4VCVFQZDYeZtT4c5XtmJQbl/mPN+h9upAYTFXbYPo62GdNLdEV6srVFYa99q5ctoxiLblSkB+7wqgcaJEVfqFw==
*/