/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_OF_IMPL_20060124_2147)
#define FUSION_VALUE_OF_IMPL_20060124_2147

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/convert.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/fusion/support/unused.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/config.hpp>

namespace boost { namespace fusion
{
    struct zip_view_iterator_tag;

    namespace detail
    {
        struct poly_value_of
        {
            template<typename T>
            struct result;

            template<typename It>
            struct result<poly_value_of(It)>
                : mpl::eval_if<is_same<It, unused_type>,
                               mpl::identity<unused_type>,
                               result_of::value_of<It> >
            {};

            // never called, but needed for decltype-based result_of (C++0x)
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
            template<typename It>
            BOOST_FUSION_GPU_ENABLED
            typename result<poly_value_of(It)>::type
            operator()(It&&) const;
#endif
        };
    }

    namespace extension
    {
        template<typename Tag>
        struct value_of_impl;

        template<>
        struct value_of_impl<zip_view_iterator_tag>
        {
            template<typename Iterator>
            struct apply
            {
                typedef typename result_of::transform<
                    typename Iterator::iterators,
                    detail::poly_value_of>::type values;

                typedef typename result_of::as_vector<values>::type type;
            };
        };
    }
}}

#endif

/* value_of_impl.hpp
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
*/