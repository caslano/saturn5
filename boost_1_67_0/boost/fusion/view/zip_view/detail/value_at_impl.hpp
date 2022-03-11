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