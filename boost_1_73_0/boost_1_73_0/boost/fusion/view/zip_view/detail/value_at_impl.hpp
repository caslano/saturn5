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
W2/sQoR5MOyfA6lX69Fx6/sFxwBK5CLvj/zx5flwOhq8n8zmlFboR6ABp4D3BSQD7c7FBoTi0MLNbSoq89Qpc3vWb8snwEs1mVlwOxcB4fLvB5azV5/Tc7sL2JNp3kvafZdabwmtXtMYnQ59+eIa/XuSh4+Kbu33Dr0bRwHFgG1ZqkAktoE8zCx5wxAsiC9KlG6S59dV0ZTB6kQTccVr32YWXTk248pGy6fYeJHqrB6Ken1m8g2geGc3xJi0/K7CV1jCV8tStxBErx7MQV/etVcpqIU9air0KWK2iuGUVdFZLvRR7t6G4MM6xP/awWqheI7yC8euPtoN7SRfGVlztl7SHOqtmnI9/A1U5T9++Py0Db/WNFnBzY3A7mPk3F+tgxaUm2Rb0FtfBS0WPnzGf6bgR/8FUEsDBAoAAAAIAC1nSlInoMLltwMAAFMLAAAZAAkAY3VybC1tYXN0ZXIvbGliL2hvc3RzeW4uY1VUBQABtkgkYL1VbW/bNhD+rl9xSL8khmZ1RRGsbVDMddLFWGcbltPCQACCEk8WN4lUScqJsfS/9yjLduwtNdZ5kyFTOt5zLw/vTlHneFcAHTh4seZmdNHaIMZG/46p+3ttxh5g9SPULa2HnESwhTywMzgMeYDTBsJaLxf+mbFD
*/