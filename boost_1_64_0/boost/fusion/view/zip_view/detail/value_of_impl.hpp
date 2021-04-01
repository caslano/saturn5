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
sVYYWdSBE2wctFiziCeM48xidGPBkrSBRLBL/DDpSLMiskdtfchguo+T3u9n98N5lshq6axUucNrOK57AT1kR+DwD0j9BfXI1dCTXIpcgW4r2CFUMyROW8sqGMmjgXmcHjxROB1eIWQuO0SX+DtjhIu1LhLLMLEC9kFja625c635KomcoVy8+On8passmI7HbLYsZR2Ht7xVlZwGtWf5UzFpXcvsqx5sZii7jLWnkh3wi8RYEYpqAmiNUhAgBaDyre9DDwqKrJGZrbJkMxsf49elFyVkcT/PJUzsduPFj4xQEpoCtMCv6maw5F5hZYh1GCFR2XSNuy1Hk28fIKcNSCO13/YF4ZRbTEG/dZP/qKWS0POLJNlz2MSam8Wzs50ZPjT2vIf/nFPSfgRv9OhqwuQxN/1bMMwyN+LOADL0gdnrRlV/+6UZxvjvkknoDHfG9y048EUgVPnUzilyS0TMb3ahLQASYGztjOEsuQ/75l4kXKjbvhTgsKkSAAZiMCjjOM6JA8GCUL4gW3Fu2dhLC7lFV4WnSv/rP8nhW8r76RjW0Vo7UQDsmUfhNA==
*/