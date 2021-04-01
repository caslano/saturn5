/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_NEXT_IMPL_SEP_24_2009_0116PM)
#define BOOST_FUSION_NVIEW_NEXT_IMPL_SEP_24_2009_0116PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/next.hpp>

namespace boost { namespace fusion
{
    struct nview_iterator_tag;

    template <typename Sequence, typename Pos>
    struct nview_iterator;

    namespace extension
    {
        template <typename Tag>
        struct next_impl;

        template <>
        struct next_impl<nview_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::first_type first_type;
                typedef typename Iterator::sequence_type sequence_type;

                typedef nview_iterator<sequence_type,
                    typename result_of::next<first_type>::type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(i.seq);
                }
            };
        };
    }

}}

#endif

/* next_impl.hpp
BHo6cQhkJsj9Sjp34lMAVGtmkWQuAz1kI2v7HoMFAMEXwWt9mnx4E7epMzndr60zNZhA+s25BLfVoTJU0pDZhaWHxyXbBhY8V/yt6NU2EljXNx+dqsQXmAIgt8Nz0keUr2ddu57cmliuS5AmkBOFP99tfsdGEW5SmpOG2fE++R1GSAZNeiBL4dMBjwy0i1z5+5QqX4cVWukoqiEwcgdAhKKOk6nyut+/ufjMqV3YdJqTzJ743kuUY9jt70C+48gE7RYRXjVLFfGfLcE/+OUw+wbbPzknGfi88zs/WkdGsJZkeJmS91gGTjKjUG1FeePwm0GenUAeMU3rdWa3o4IgDFIC2yWEh3YzgANFjng2t8JCqU3PswJVOEYJciAJ816lUej6rH1WJ0SjNvEWXeFeqy7I+/Fi5T42vmFPKrOIvRBzV/MgZRUUvXOiCvOrXW09QSPa0u90Zfa8/23AnbO4NbzL49M3nNIMvPaU91Y/rnEM3GUfu0T66r60po3GVaV7WyIcXENMJB1uUSKPP/U+B9XKON8q/R0ulQ2k4vd42sQL46V2lLHeXiOcrA==
*/