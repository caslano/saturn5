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
jO47/xN9h3qTfxKhunPAK72t0DG72qGqityuLjNWWUAjGUwXrQINnBku83hdVxLYsj6t/j9bYsCZDc90GgbbgN4MLSWum+8gggvEdOTZM5N45os/+eZlX/0zWFrwBs7s77df2BcUEF/NwnICd388QIvAkqu+R6LMqFyIi/YiShROZlsmETCo1UnyW7FmynUx8MjXdeUgTXOvRQUgErNPmT/14A+kqwcDKIJe0HuNQTNCxCEDVtfXLYyn6eGyhGKSWS1W2t594fSioB/7UEQD4iQkPU9IKAn0CTJL+7JX8YrzHiVyPMxaWk/DlTV0UDLZ4Y7Sf31IErnnAvYBAg8kXky31JiKjESm9b4A/brbMh8G+PHpgmAT/NeZHmp0c1S1WrfmdIghxgLiqOxH81i9lKAQEtyuur6HRDG9fCS1wFIdCE9N/XODxbt97g2ATyk5ZJ/ZKVCcg1aF6ps3ojF8/Q33zctRJ8JwW5QumzbO/rrCkrlDGMF8J0ohl89FvPdWA3k+h0ZxM0VzaQ9kRX+ng99fvfxvEjRmRRT2AvQJ7/HL5PYKiraQY2L8Fg==
*/