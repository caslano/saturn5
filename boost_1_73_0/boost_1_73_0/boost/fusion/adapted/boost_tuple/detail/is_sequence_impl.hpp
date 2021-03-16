/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_IS_SEQUENCE_IMPL_09272006_0726)
#define BOOST_FUSION_IS_SEQUENCE_IMPL_09272006_0726

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion 
{
    struct boost_tuple_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_sequence_impl;

        template<>
        struct is_sequence_impl<boost_tuple_tag>
        {
            template<typename Sequence>
            struct apply : mpl::true_ {};
        };
    }
}}

#endif

/* is_sequence_impl.hpp
UtakGY9Uq2OTpYOefoFC+ggOgxRN40Xx1OrOaq1d013YQ2fE/tleKpnawamSe2sX2LlpHG3gvDRWuZKHwyRE58uyQpYD0jhwpuTS8AOyvFCW62Up2VPl4PpRGs+p95fle7r+YVlenMbxhC6R5SmNkxAPhhAPVoJYBKwY2AJg1cAeAfYrYC8B+x2wU8D+AYycBoylWgbrB6w/sHXA1gOLWBjJ1gq3sd9Gl2SbvJNlUMXichRL84GKqb2zGrZp4Xw=
*/