/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BEGIN_IMPL_05042005_1136)
#define FUSION_BEGIN_IMPL_05042005_1136

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/vector_iterator.hpp>

namespace boost { namespace fusion
{
    struct vector_tag;

    namespace extension
    {
        template <typename Tag>
        struct begin_impl;

        template <>
        struct begin_impl<vector_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef vector_iterator<Sequence, 0> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& v)
                {
                    return type(v);
                }
            };
        };
    }
}}

#endif

/* begin_impl.hpp
24EEIGZ1NOLktcvNxmG4BRIUEXdAITlOwJ6j3Pka9jrjjmv8fnfsVSNtX2uQTrfrj0bhCA+wvt9o77XJRbszGvnDcf23wlPLLD+9LyZnagXQPdJOYfgTxsOJXwHxAOn73n37L0L6Tj1R8vqLRq0kuybBIfn1f86uzUgeFMgnRfJtpz/aH8qSjC+KvSrnS237ZTlxTDNZxbGzFZonOfxDBb6rZiuTtcqqRzY8gXKkIcOBbLuxFv3c9VGRWWzr2Pywvz0OELYJk8/nSltT7DrBbas297DPrlpgey0Y5CkO19RTNlvkauBYWfCoYUocFwszQ3pqO6TxekJxQ0vKCfl+oFtjUWPF/ZpbHAcNnNHoxrVW2sO2iVOd4x33kdNO3Tr/qaHWH00aTc8RRL422rWFEvG2HM7tVqtliah7bGxatJqWtKZvrcJqj+Y0BolCr7FlMphrdbskG0sj1tzSjg7FYfGu/njuILK8HS2l4no8hBXOPA9qk5UDkFCOEgMTH0dnomuO1G7EOivNNpzrNM8sjiUJzsC7pl1Hd5HOW/zS6g5iKbJTpeS2SGGQWzg4JLsigDqp0COFc/OWWhbHVTob9KES4EmDA2YvHPojnA/LE1rzVC34r7F/v6RjtOhkpeziAM7x4SDLDkpGR1ET
*/