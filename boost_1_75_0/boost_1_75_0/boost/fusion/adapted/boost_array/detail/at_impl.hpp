/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_AT_IMPL_27122005_1241)
#define BOOST_FUSION_AT_IMPL_27122005_1241

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_const.hpp>

#include <boost/mpl/if.hpp>

namespace boost { namespace fusion {

    struct boost_array_tag;

    namespace extension
    {
        template<typename T>
        struct at_impl;

        template<>
        struct at_impl<boost_array_tag>
        {
            template<typename Sequence, typename N>
            struct apply
            {
                typedef typename mpl::if_<
                    is_const<Sequence>, 
                    typename Sequence::const_reference, 
                    typename Sequence::reference>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& seq)
                {
                    return seq[N::value];
                }
            };
        };
    }
}}

#endif

/* at_impl.hpp
Q6DTL6limxMYEtBIEGC6MLjlFpt44/Ub1GsvEWoPgRYEm3QLgq+PoUeq3PZn8d1yxKRgyaHWWjHVuBu3m3TPPnjX0NcwnAL6A3PVpwRoxGKTPGJqidFGS9jVqY/xlkC0MMA8ccJ9ytegkggNkK/HxZKBmX8DYKHXpHRG7+OrNolOp9tpn3WdQNV+YwrX8SA7nHf/+w/tcMLMdjj+dizJAhKPS2FHBvvLYX95stdRmHLUOwcCZPaXywIKMsrmsBX1nGLZ+x6utbzv0QH1e3Qa9d5yeqygxYHsc9jd4azRvIvp4u+9Kmzdp2kHOh2w8lJk790xa5NhA/cajCov+z8jhv1Z82syEsPCEMLtYTxPenAcNNME872O7L23uGZsYjzeyVXAmsRbQfc/NVy1CtA/0Yy1adqwdrgui6sx2xOQrU/BPeSIYfAtwkwJizr4rZ/AKSuMRe6dF4Fl4csrKF5ZbsRMppjlPKbciEmnGG6/Z1jusfmTYrj9nrLIiImmmEUUM65Y5th1xYIq3zgZ7fy6kZ3fyOEJFs9NiQKZhnjmgTX/K88IXU+wfMp8Sx9vGVzXcw/1p49rpf4rmVtWoKVSEtjdjs+V04+4wTPrx7xyMKaylCl5WjlUjqzj1pOEKpqDiqxcd02oxd4mJ3C12Bc4B6XKpHuSikMOMUcKKCPUxFM4ZGssT6tvJnAkJpiUZZsjSzUauEj/M8P9dHsC
*/