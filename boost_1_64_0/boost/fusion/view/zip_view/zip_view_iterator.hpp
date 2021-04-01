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
LbLeB1k3oGUxV9IHc1d+FKMNbIEqEjvlzjQADepJEnLPvnfSxTGu78bHS5MZ8qIghXwCla8yIHMNyzf7EH4qms9Hi5+hUPfjM9kLa+GTbGPMt1kr+5Ppz4WitCtxioMajVTJAuDr1+445DWxNa38iDrX/ZxBoEfa48+A9zgaaayErdCqHPI7/sUPpQ4QkTvIg1SruRTMUXdmcv5iCv7NUjEcQ/TU9TntNQ3cL0LCkr6wH2ShB8fvYBgTGK/MIpCF4lmP/KA/btuxIMh74Qy5bFcigZm9coEDXhpWHxZVWqALGVKAjrImRGZka4h8yZ21xu1fuoIsZwpI4sSSp8RP4fvAzmfJNKmQhv6nRRoCoRqMMm0Q4xa+r/uspB2uNKPqL6uPdlXzuLJP4SNNPbUg9PrNDelmXnOI3tbH8PtaODzWO7mxAo23bU9BqWY1oWmLKZ4wgW1lFnJeeO9WWC6rvFTLAekJkVWE1VPKMA5Lf8rGlEpPALEAQS98cUjhGW9Nx4LO5AFcpoENxOI+NTgRCAo58D40Pc7XO3VUKqy0ZJQvTxkfk2X4lrx1ww==
*/