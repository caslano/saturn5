/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_AT_IMPL_20061029_1946)
#define BOOST_FUSION_AT_IMPL_20061029_1946

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/utility/result_of.hpp>

namespace boost { namespace fusion {
    struct transform_view_tag;
    struct transform_view2_tag;

    namespace extension
    {
        template<typename Tag>
        struct at_impl;

        template<>
        struct at_impl<transform_view_tag>
        {
            template<typename Seq, typename N>
            struct apply
            {
                typedef typename Seq::transform_type F;
                typedef typename result_of::at<typename Seq::sequence_type, N>::type value_type;
                typedef typename boost::result_of<F(value_type)>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Seq& seq)
                {
                    return seq.f(boost::fusion::at<N>(seq.seq));
                }
            };
        };

        template<>
        struct at_impl<transform_view2_tag>
        {
            template<typename Seq, typename N>
            struct apply
            {
                typedef typename Seq::transform_type F;
                typedef typename result_of::at<typename Seq::sequence1_type, N>::type value1_type;
                typedef typename result_of::at<typename Seq::sequence2_type, N>::type value2_type;
                typedef typename boost::result_of<F(value1_type, value2_type)>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Seq& seq)
                {
                    return seq.f(boost::fusion::at<N>(seq.seq1), boost::fusion::at<N>(seq.seq2));
                }
            };
        };
    }
}}

#endif

/* at_impl.hpp
K6QPPO9plP9/S7+9H5FRmbRMPl+yUlxs1q+bzmd9nJfi8DeYtzPq3XGnQLlc14MRolAsVCtmZj+cBfM8V6ZB4b10Qb9Gzsft6jAal4rTJq+F/DheX6Fs8qw/MVe2lHdyz9cHHtS9RnMYD7coczIHEy7wkZhD5Y7d7u55wV+QE+vDvSjnfAPu7yzrx5OArQcRDxNYvt4YnorrCpvj31L+PX1D1LtX+ROVfDwqo+d6IB3geDBjR3c8L5UuZkZ00omelj5rT+ZMP8OqMymuoLazKpfRHH8ajhgMZmfiwE5R9vX8TfJqXEsoFB9a/7l/dQ1P+0JLTPK/0Hf58y5BdW6UbjILFNmDWvK58w+UnitbTC0asvXwveDmsxY1XqBVFnFIn4fmghsMfOwq72K7rAc7DB4HZ8P6ily08bvkfME49rIRVXSXfF2VPMw2TtbTXXqP9zcrxu7D1bQl7QVZFeZ7l5l9I3/UB/VdOjz6MP9Vc+yvJ1NNsht0XRFD7pm+qsN8ZUwrxQuyv7YqyqI+Ax7EHloVm+5cnfnPYKPJsJbKEDgXyf2YdKfN7l4HE2166cz2Tj6iYnQgHsCJp9mPfIkxDswBZ0beqGxGf/e8cF94XiUe5nBo/j08j2XXyYFFgVwFFjOf34jGr/We4ac+5zeWYXwONoU1xjBr5B7TJV6tw3P1YJWmo9n86FSxyFF4mgwMe8RT5NW3TB/UOidD
*/