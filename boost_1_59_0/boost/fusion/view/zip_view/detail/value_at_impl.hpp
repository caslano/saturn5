/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_AT_IMPL_20060124_2129)
#define FUSION_VALUE_AT_IMPL_20060124_2129

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/convert.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/fusion/support/unused.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/config.hpp>

namespace boost { namespace fusion {
    
    struct zip_view_tag;

    namespace detail
    {
        template<typename N>
        struct poly_value_at
        {
            template<typename T>
            struct result;

            template<typename N1, typename Seq>
            struct result<poly_value_at<N1>(Seq)>
                : mpl::eval_if<is_same<Seq, unused_type const&>,
                               mpl::identity<unused_type>,
                               result_of::value_at<typename remove_reference<Seq>::type, N> >
            {};

            // never called, but needed for decltype-based result_of (C++0x)
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
            template<typename Seq>
            BOOST_FUSION_GPU_ENABLED
            typename result<poly_value_at(Seq)>::type
            operator()(Seq&&) const;
#endif
        };
    }
    
    namespace extension
    {
        template<typename Tag>
        struct value_at_impl;

        template<>
        struct value_at_impl<zip_view_tag>
        {
            template<typename Sequence, typename N>
            struct apply
            {
                typedef typename result_of::transform<
                    typename Sequence::sequences, 
                    detail::poly_value_at<N> >::type values;
                typedef typename result_of::as_vector<values>::type type;
            };
        };
    }
}}

#endif

/* value_at_impl.hpp
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
*/