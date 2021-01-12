/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_VALUE_AT_IMPL_SEP_24_2009_0234PM)
#define BOOST_FUSION_NVIEW_VALUE_AT_IMPL_SEP_24_2009_0234PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>

namespace boost { namespace fusion 
{
    struct nview_tag;

    namespace extension
    {
        template<typename Tag>
        struct value_at_impl;

        template<>
        struct value_at_impl<nview_tag>
        {
            template<typename Sequence, typename N>
            struct apply
            {
                typedef typename Sequence::sequence_type sequence_type;
                typedef typename Sequence::index_type index_type;

                typedef typename result_of::at<index_type, N>::type index;
                typedef typename result_of::at<sequence_type, index>::type type;
            };
        };
    }

}}

#endif

/* value_at_impl.hpp
M1uL3ib95yWYv3VJvWfcX+Nvt76Ey8FEATO10Idz80J9ZG1+/ngleS+y51V4EA4n7w/4It//5LgpjCR4pqyKrToYwuJjCc/XVILlXQp/q9W+FbxbzIc5diL38J8de9b4cdZHjr1XyMOSGrNCW79SjD8GALd53MGxk4hFTXM8E25NT4X5HE/36JX5/AUrQijPza1pVdeHNGYnl4XpvZPArLIkq1NG1a5P729+m+C/TZnfdsvf
*/