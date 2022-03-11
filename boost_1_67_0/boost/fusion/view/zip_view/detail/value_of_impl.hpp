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