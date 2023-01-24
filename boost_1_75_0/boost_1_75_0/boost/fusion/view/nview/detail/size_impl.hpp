/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NVIEW_SIZE_IMPL_OCT_06_2009_0525PM)
#define FUSION_NVIEW_SIZE_IMPL_OCT_06_2009_0525PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/distance.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>

namespace boost { namespace fusion
{
    struct nview_tag;

    namespace extension
    {
        template <typename Tag>
        struct size_impl;

        template <>
        struct size_impl<nview_tag>
        {
            template <typename Sequence>
            struct apply
                : result_of::distance<
                    typename result_of::begin<Sequence>::type
                  , typename result_of::end<Sequence>::type>
            {};
        };
    }
}}

#endif



/* size_impl.hpp
fgsMPBQ9o0E9s18dYs2+8Y8HxaN4SQwpmp5fbglmBwduFffArdnTpMul2xQ/zNVQZZcCquEtgLsVkrysRjoHKVMACreUaO22vmh33v9Zdm5E8RPGBakM309ZQb7AoxkdQknrW7Zgg+DNKbw/tRUU5u3LNB3nQvt0YPwDMQJ61PKvMX2Vma6XvPHH8bF7jTfhWedME7h40cTXH67UcLbAdlZRx1G3dR+l1U+f+BqAP1DtrVFPnUa00e2nzokonNnmoZslyjohR4VfU7hfJ5kJKZ99lNPeInw2FwaZ2J09IqgeA/P4OM+n8pDOqYl7XsYDfEO49+b25mdQ4Swi/yt16aUtS1+7T5beKIOXSVUbWi+ehU5VeiNq5TysRB6XrW+qWMBOP/9HoXKEvpnsmhMAhDrT1h/n7OJkONV4b1xKD9gZxs+epclzrOXFL2EPs17jf2k+8bH6jJ6bcplfBO2PQ8UXV72EYGZYykz+CbwioG3VFbeFaUo03OXSrCeGehXkilyqlCFVG+zNSGKs7JUh2tWOP2booYwiJRJhjB/Tpt6KJTVcU6C6Wf/w+BGCx++o/G7ZwW46qEC283JDudDNiiigfvKeBvR7ba2InjPSc/ivWYbRV9mydPs8W+CWcXXfUwkZ61T6+bQq1lTaVHCAobCrWhdT+FZwC4TPYWiEXlEx2t9Je/ioM3ZNn89rYEVQnPz+w+EMN8zMZAZy
*/