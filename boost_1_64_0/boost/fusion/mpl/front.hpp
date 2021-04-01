/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_FRONT_10022005_1618)
#define FUSION_FRONT_10022005_1618

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/front.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/iterator/value_of.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct front_impl;

    template <>
    struct front_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence>
        struct apply : 
            fusion::result_of::value_of<typename fusion::result_of::begin<Sequence>::type> {};
    };
}}

#endif

/* front.hpp
Un6XdSB02nYAjvj9jlQC3Un+CaGkxJdeA/gvMl1qzzBq2ajfOY1pbkZLqnmBVkaXwEWwqgyqrQBVYNRZtCM3gYN+j8c3BKSprafd/V2LJIR3e7nv5Mq3kvqGOH7av/Qac51m9o/xgZzXaMMu0dU0YrqHDmC8Vlm58JZVhbKO5PR+IpiIRHyxjBcoL0o1oQw57NLgeXwXW/EKmHPsx7t18epPFL/BfOoFd+7kwCcJ0ipMP6+b/dIZQ1jJ5Ijjb6/Z0kpg5UkzrRgc4ngwFNdyA4ObeoXEUbilkpUCfRBMHdMlw446inzNVh3YW2OrvE8HcEu/PTbZ7xEJUgMFgIjKQtJTxzRhZEV66U1H/B7MYMyQVmahUnJSfEZNwgZCCv0NBPSlY0JBv/BeC9pcGaTzLcWRCQNlrMQtAwR7U+ox5CXLI3sV/BLKL9VMSN5+FNbfXYZh09l5+NKyBXPBSepPkbLJW5s6rLp/Jr6sSD9BGQLmwu0PVZ374Rc8VSN+Y54f+qy2RxOt6UwGZm2DOiL2iUdVK/iEu495G1nQxHyX0uiXbblqM+8YEynLiA==
*/