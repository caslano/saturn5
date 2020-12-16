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
vLAJOJZtsyEXltnGqistq6RKgovBgvMhJ7jFtSCLoxRg0GuVj2pu+8lldg5ACt+6UVdm5WxWkTnqMVhwPsjkqCyOVoALRN/WmtvT5C6IWfVN5NMLRaUvGKoI0FqdBgu2O6dF189OCtCh7VFwAnyq9AP3KxjtLUWln1wnAIOxsx6I6sMxCvDQtMquoAUtpQ/+4LAAsYFhsOD79zOi+mDF9JpmLTpMc3uKrGwhfQiXkgsCUDjyhWZG5dBZAY6d+lejHj1ZVrSMHAI+arvCIImxOWdF348uChC6Zx3k0p8ks8H+nsX7foQoE0ljsOC43pyoXnRVgNqsLadpbvvIUMvoBbmBBTiwT/ZkVA7HKcDaY0o/1Zye2FLrRC39OgEonHG8eW6xHORQqABPVV2zU4/2luMP0T9NcnOc/9TWDqULXJnJ0X3DNSpmBec+3dSz9WHnQX2OE4y/0cBx9xjIIzzwcCLA+YTvu03/WCvP/qR2t4T0aC95IB7O/1hyyDSJhIlDDgRYBuJDt6iCfjDdFaDNM2lVevR42TkFpJHJkTtVHxpaFqyh66SOEOBY3U63eBVya3sowPd/93pOj/aU++xzrzRGGZCV/UcIsB7E5Ykd8C4UK8CsHmPS9Gix3J4E/nay0g8uGVRR7YtmfuxLpeWJhaADPRUg/Ogq6KXdQ65JhzOdTIbaljZ9NVRXDvH85h3okCfGpGr+j7dyQfYft1dz2F167TNPjtpdFn0+a7EmfAUc8xtb4Lg8xanmv5dlE13ohXh9keF/OksOgE0fof475jc+U2GeuALe/xMUYJn7goDmsJtMSbfPsBhq+EXoU6Y7Yc1vhCK25nGPPPE6yKG3AlwUvxf2gkK5MQXkwBJrU0SSRhLw/MYmOjVPPA/8n2itA2dVwS2742RdF/1TqD1DL3GLvkBJaYCoIo2ZPnYfvDdPxAP/fRTgrsNe+0mPdpWTYB3YLJnegwiBJVabnoqqUl+J+muqnMn/QobtZYdsTkKy6fJ/kA1ddu1/o8P+pJLPYJDPyVL9flTXk/RoZznJrgGawGRDBErKqDKnYHYcW5mWJwbB/nmKev71YNeVkUGVXbgMzruvTuHIBYlQ51N1NSorg1RBheY4jA7MiepAX6QDx8gF/DrgK6XcP2B+pAfz88RHoAenquf+ATdA35ROci7sn7vSmPwIRV9FqfpXVFgSqqm8tlv3wmJSYTRHhuvnv5snhoNunKYAO/MGxevRo2XbNLCxOerna3L9tHsrTO+MOX2cJz4B/vspQGrTaLindZTsnAPxlnQ23VAEdicWQHecH7UzT+TBu3G6eiZsu/JYzeGRcmMSxOL51oagP0C6Ppr5Tdx5T57iTfN/hgL82mObT3N4hKyLAys7no3/6pFkIUczP/7+Ff8FwP+ZCvC3px+UeewoewHHRyv+03j4r6F0MWF6XMtgb54YAfyfpQBHduk8R492kGus9Y+rf4gmsNZHVOfRTB/rW8R7jG3QH9kGh8vNoP8VfPpf6yOMtML0+Cwy3mN6Kp5t3S/oefPzerS9OZe1nlls/GtjvspPahY48Rxkbeh2vLWxbTqJxRBrD4UyPOI00AerxsvUH34Cn+EwOSsJ7KF4Np8hHAiQLohmfrMfuj1iM/A/wIo11V79i+bwUDkD1oOxfOtBpB8wqQQAA9oT8z3iEoi7n2fVeDt+8a+ay0Pk4lQ4f0rjkkG1r8ZPleFn5sfnDkd5zBnk+Qrw3XG3QE2TtqamSTuWs3hFn/oQXrhyIsB2QSeP2AJ28QVWruein5fr0TYywQ15wDlMMVf1oT1/Mwhw/YLzPOYuzUB0l6Y1b08tIJHwIo0TAc6BVjKYAz10LlSAz7Y=
*/