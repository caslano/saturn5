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
/OwTzHIy8OcvU6fdJPHPv7mUu6mzNX5IgKxOAzcjmJW5iAC0Po2CP5MibSP1x2kuOwhunI6bWFP7MSshdnW/FxRSLEfBMdfvL/WtgWqY17eniv8UbOLKEWEcRXbaPwaxraE9zZKkkJ29tTJtillJglI//ZiUHY+dvXT+SimaZ0LJa/pW0IbFZ2Vbl78W/tn9lWXyVe1mOSSvK+2YnTesPtWnGADR+5LGhf8psLfPy0LqLdqYDGs6AILhWs+2s7F2wV94TxlZdeT7YnmVZkgzZvFE6q8c9RZ+JsxRXkcgyDG/qWEYdYvxicPrrLZ68vfpYYExPqe9fiaannal6JR/isY08Y99HpCG6cdKY2dSD903lw4XKEbCIxoni12Jlkae8bsE77uKEaHFpMCaW9AOEQGOlJyiYRe35uc72izht+nug4mMVo547MxRyr812PijH/ste8zpfSCCysqhMDqHYfJBRWFFvv2R3pBy38OBJQLvWJO4zQhJoudV0eFt8G9tGC1ZFAf3n0tnI1HH90YTl/8oFJnTkVuUHVSExwBo9+qVRNfBs0bv5lGNo5Q/V1jP6++jGyLt2arzWf4mLllWnAldVvN8nuOJu1Am48zeu8qRxk9jy/Oekypiv9tkfvvKywdZMptzcMwbb9fD6czMGRnX2/Lau/JLlEbS++dhlms1UfZeOBGspCu6XwEpvp7kD9Fr2vu4cMrf4JLc
*/