/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEREF_IMPL_20061024_1959)
#define FUSION_DEREF_IMPL_20061024_1959

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/fusion/container/vector/convert.hpp>
#include <boost/fusion/support/unused.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace fusion {

    struct zip_view_iterator_tag;

    namespace detail
    {
        struct poly_deref
        {
            template<typename Sig>
            struct result;

            template<typename It>
            struct result<poly_deref(It)>
            {
                typedef typename remove_const<
                    typename remove_reference<It>::type>::type it;

                typedef typename mpl::eval_if<is_same<it, unused_type>,
                    mpl::identity<unused_type>,
                    result_of::deref<it> >::type type;
            };

            template<typename It>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            typename result<poly_deref(It)>::type
            operator()(const It& it) const
            {
                return fusion::deref(it);
            }

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            unused_type operator()(unused_type const&) const
            {
                return unused_type();
            }
        };
    }

    namespace extension
    {
        template<typename Tag>
        struct deref_impl;

        template<>
        struct deref_impl<zip_view_iterator_tag>
        {
            template<typename It>
            struct apply
            {
                typedef typename result_of::as_vector<
                    typename result_of::transform<typename It::iterators, detail::poly_deref>::type>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(It const& it)
                {
                    return type(
                        fusion::transform(it.iterators_, detail::poly_deref()));
                }
            };
        };
    }
}}

#endif

/* deref_impl.hpp
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
*/