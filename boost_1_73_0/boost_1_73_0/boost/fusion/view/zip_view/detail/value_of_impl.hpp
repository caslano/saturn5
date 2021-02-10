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
jm59bP4v8shb5h9JQjCP7OtqaeQ8d3DaP4MfX736CX6AF89fPA/hkiuJBcQOVYJmHsKFaCQ/5/z+vmvxbQjogBfd1tQ0lxasztwdNwj0XMgUlUUB3IJAmxqZ0ItU4HKETBYI/dF4Nhj+EsJdLtPcG1nqGmyu60JAzhcIBlOUi5WNihsHOiM4GRfSOjJYO6lVl3wjODSl9Ta8e15YDXzBZcETcsQd5M5V9nUUpbUpKPpI6NRG6Tr9bu7KTSYzCqLkS9CVA6ehthiC1wyh1EJmfiVCSFjVSSFtHm6jIVdKRNqAxaLwtggn0a7CRohbekKvBhVFLJ1frFbWu7rLdbmjSDx6K1ltFDkiHkhJaKI5hFoJNI1yk/naRctpQ/CTR7ONV4BWFAyc9GIYxCeQcCttCJ8G0+vRzRQ+9SaT3nA6g9F76A1n3tivg+ElHb0kZwbwvjJoybkBWVaFRNH6PN4VBcEzqdKiFggn/vSYRVdX3fwkCKIj+fB5jVSxhIwSSWpZCEvHLtUc7FKludFK1xYUL31FWl0s0B4rx4iyywRm0L+ZfJhcxSyeDfvXwVp63ft4xYZX0wHdbDBk11syLhQ6SXckVTd/GzxDRcW5j7t8tw8RyRPavcm4xxo/jxHcVDzybv6KYuzjb/Ej1TaO
*/