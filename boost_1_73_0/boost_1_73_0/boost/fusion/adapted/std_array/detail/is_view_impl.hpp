/*=============================================================================
    Copyright (c) 2013 Mateusz Loskot
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_STD_ARRAY_IS_VIEW_IMPL_01062013_1700)
#define BOOST_FUSION_STD_ARRAY_IS_VIEW_IMPL_01062013_1700

#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion 
{
    struct std_array_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_view_impl;

        template<>
        struct is_view_impl<std_array_tag>
        {
            template<typename T>
            struct apply : mpl::false_
            {};
        };
    }
}}

#endif

/* is_view_impl.hpp
hM69I32vba6XEKcrWlXVxr8+P0/qMocl56lL/HnSuKKzqtZfWPUB2qz1ltymospR7U2b+Hyb1i61GV/hIjzc1Mvc+lV7rxYEFum5K8mbPI/sQGqNDyYYmkZvtfkkbaC9rfjiXeFZ2sPKrY8Owq2RUVaXBcTBLTiXOji+TXWRmlLOiyMaKdHL4vLfCdle95RcAa2o1Z3SYNqipfbWt+n9YHY1ms/ofXcy6Q5nH2h0Sd3hh8jv18HwAtiwkFqS+bQpjYcWJdn1JrcmPRL+h2a66syuqDefXI/GswUu9Jxaz17QP+oCkH72Y4tauV1yzOlF5/mLzlM84L8WRvvtwpuKo4tfAMmD1/SKht2bvjpkeHtGm9Ld29SIT/lRgEMD6NL8qza+Eurph+FoPB1M1Z9skeQ1aN6wuIC61c9KOCcOz7/U4oTf0JMV8JADFgcaAHYrXdIT3J7+JFIu+tPeZDCeDUZDNdbwNDTRtHG2qBgGTtS6zQaguM3GgidXfqQHhCekC7JJrw0fjvm2BGRVEMPHNRV1np8xmGyhGROMjuIupCuta18xCfifmYLN2We3y3P3gKMqc+VaV6+V8snKrA1Sb+V89Xrjyup8o6uVUpcAiKa70ugqoCbXEIZQNPgNLGiTw08GyWRoctl7/url
*/