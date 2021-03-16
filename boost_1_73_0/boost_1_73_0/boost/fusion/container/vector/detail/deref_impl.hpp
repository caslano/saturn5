/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEREF_IMPL_05042005_1037)
#define FUSION_DEREF_IMPL_05042005_1037

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/container/vector/detail/value_at_impl.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace fusion
{
    struct vector_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct deref_impl;

        template <>
        struct deref_impl<vector_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::vector vector;
                typedef typename Iterator::index index;
                typedef typename value_at_impl<vector_tag>::template apply<vector, index>::type element;

                typedef typename
                    mpl::if_<
                        is_const<vector>
                      , typename fusion::detail::cref_result<element>::type
                      , typename fusion::detail::ref_result<element>::type
                    >::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return i.vec.at_impl(index());
                }
            };
        };
    }
}}

#endif

/* deref_impl.hpp
Ii+PTqVhVZeUFQCF/OpyPL1C3NcBGltS9r/QZGFcvDKI1UcD8iu3qXpnMhrVI+3U0xfmIroJpJ2VQ8lrSA/IRnI3DnBXgolPLdLn1VXPAonN9dKtIfiFck7VCCr1NdkCF2dKRkLJ8ArG8PgZUA6YZFQBO4nmM8BTZ9q8oObBuYRFV1L2QBVjAVuQhsQ50/NNGQlxH5LP35+jDl93caWRb4QIeRnje21BUPBA0O/0NIJKlJSVVRDNVNioeYA2Fy8=
*/