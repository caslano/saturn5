/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ZIP_VIEW_ITERATOR_23012006_0814)
#define FUSION_ZIP_VIEW_ITERATOR_23012006_0814

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/zip_view/zip_view_iterator_fwd.hpp>
#include <boost/fusion/support/iterator_base.hpp>
#include <boost/fusion/view/zip_view/detail/deref_impl.hpp>
#include <boost/fusion/view/zip_view/detail/next_impl.hpp>
#include <boost/fusion/view/zip_view/detail/prior_impl.hpp>
#include <boost/fusion/view/zip_view/detail/advance_impl.hpp>
#include <boost/fusion/view/zip_view/detail/distance_impl.hpp>
#include <boost/fusion/view/zip_view/detail/value_of_impl.hpp>
#include <boost/fusion/view/zip_view/detail/equal_to_impl.hpp>

#include <boost/fusion/container/vector/convert.hpp>

namespace boost { namespace fusion {
    
    struct zip_view_iterator_tag;

    template<
        typename IteratorSequence, 
        typename Traversal>
    struct zip_view_iterator
        : iterator_base<zip_view_iterator<IteratorSequence, Traversal> >
    {
        typedef zip_view_iterator_tag fusion_tag;
        typedef Traversal category;

        template<typename InitSeq>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        zip_view_iterator(
            const InitSeq& iterator_seq)
            : iterators_(iterator_seq)
        {}

        typedef typename result_of::as_vector<IteratorSequence>::type iterators;
        iterators iterators_;
    };
}}

#ifdef BOOST_FUSION_WORKAROUND_FOR_LWG_2408
namespace std
{
    template <typename IteratorSequence, typename Traversal>
    struct iterator_traits< ::boost::fusion::zip_view_iterator<IteratorSequence, Traversal> >
    { };
}
#endif

#endif

/* zip_view_iterator.hpp
DFhJOS5iQgnOGlZZWJ3Xl4qSed01nrOXyX85zyBYSWmRrx3IwmFyTs0vPon3qcx5v/ys87xPZc7bl4IX8D6VOcd3HpPK+8w2ziz6bPoLskDFbo5vO58sDCbzvPbEei1ZPKyCsI5tq3YhS4N5CrvconsyWTZMXrdh+wuvFe2e8b1gZMzGuVyDYjeiemRwDbDSwuKtX5TlrGGVhD28NLoMZ61Yvfeh3mRZMF9hnQ71aE2mu298n7gU+/kwmQ9MZjboTkx9smCYrbDuN0q6c9YwWZ9Ji/HfyOJgJYTFtPqawzXAnITFOr+rwn2AyayrvtxTj+tT9mn/7fYlMu2B8b3HeeG/eq4PJq/NH5VsX3B9MBthRevdecX1weTZ7XtV/x+uDybr86l4sA/Xp+wlRf/fGXw9wGTfvQ8ddiHLhck8K+8cUIP799B4Pbu8+0vI/BXr9LdHMtcHsxe2tIbhOVk4zFrYpwGT+LqNgckeRdUw1CJLgFnJGvo/LLxnwRyEHbG47sO9hemEHYj/fI4sEyb78M+nPRvIspVxu/wtZpLlKfbo/k5vzuyR8fWg/XVnFVkQTGY9KGKIP+cCk3kuSIoYRhav2IXTFSaTJcNc5Lnus7Iz9x0m63t4sMVosizFdic24usoByavv20jTV9z7cq4YfuPzyUzf2yqlRNWudOKrWQBsLLCZnWJOsi1w2Rm4cVfunJvYTLrP87bR3JvYTJPbVH4Ia4P5izMzPKFJdeg2Js6d0LJ9E+M6ysxo3hbMh+Yo7C34a7xZIGKde13n89ZKEzmMtPgtJN7C5O5LFvSbArXB5O5dKz+6TRZLsxH2KKnB3eQeeUYj9sc1TCa9wJzFXYyvuVXshiYzHrk4n6F71dg1sLalbdpyT2CyT4s7/S+DVk6zF5eK7WjenOPYDKzfp8GDOP6lHHLwtPrkpk/Nd5n2xobm3DtMBdhXqM6eHCPFPu7QeUgsjDFsvc0tyWLU9Zzt3+XQ5YIkzUMrjqrC1mqMmeKQ3gcWSbMSdi0bkPdyHKUcWsvRLXk2p8Z7+VkZExbrh1mI6xV24meZP4wmWf9zZOekgXB7IStM7zI5VwUmzu5EfcoRpkT7xCsyBKUvSzsVOcdWRLMSpjD4vSbnBnMVpjZqwfeZOkwmVnvvNo6siyYq7CILrXO8vUOcxdWJiXnb87sufHz5uyxbns5F1hJYd+Llk8mC4c5C+sQvX41X9MwD3n9jd23jeuDyf413Ft5GVkGzFFYUR/T/mTZtBeylc+fk2kvjK36s5ASXB9M7nNSFcN2skCYzMzjl1K3uO8wvbCh+2rzeYmDyR49n1DejfsOsxPWsW+5RmTJMHleot4V68u9VeZ0e7m6IlkmzEbYpVyNs86GOUkzibDgvsOshfV75ZlAZv7S+Bob/nxtCpkPTO4ztPK5m5wZzE1e702u2nBmMLmXvsd9x5HFwGSeMXfsM8gSlXGf64fw+UxV9jl3iOt4zkXZ58f6EzizHJhO9mjXi1lk2ivjvfRNjblH5gWT6909f3sI1w6T56zZyMitXDvMVdZn2mICWRzMQdiKWZM+c+3Kes+nbi18XQ7zEpazPMaB+w6zFLbqzMQoslyYzLNtef0e7vtr41zmetke4dph8gz2PvjsI5m/Ykdjku9zLjBZn/nnkCJkobASwsau/GxCFgOzFjZmyH9Ok8XD6PndDDZzXplqnAuslrDls31fkmm5plrMz+8lFIFp+I8sIZezzjfD+SVxZKmwisIG1Cj5s39bzHJgtJeiJlvMtk65EEGmf2OqBQjrn1JlBVkYjF6HFIOF/4g8T5YIozmLw+7fW3qdLBNG38c0h406+rIt21veZ77pPU/3JjM=
*/