/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEREF_IMPL_07202005_0851)
#define FUSION_DEREF_IMPL_07202005_0851

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/prior.hpp>

namespace boost { namespace fusion
{
    struct reverse_view_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct deref_impl;

        template <>
        struct deref_impl<reverse_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename
                    result_of::deref<
                        typename result_of::prior<
                            typename Iterator::first_type
                        >::type
                    >::type
                type;
    
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return *fusion::prior(i.first);
                }
            };
        };
    }
}}

#endif



/* deref_impl.hpp
2tHxZZ4lSay2l3HclrgHop7N4MkgvhRnzcgWfk5b7p6YJ+J3zWqp8bATHu559Kb4R5utBdpLzpuHHow504n5Rm6PTdm5+GLu1YMgmcfRkE5W4rbFsg2u74l10PhcC97Y0BEaCHfvMokbWm5P8/hwjtyWp4wNj7jJsYNT2nW2W5qJmFJsoelGULJSY8XdgrWKd7nrmijHlhDkcPd9EO5s1zoYRLuHzZvQAIEzi5LBkEli7yQrImXKio8aLxmxiRE=
*/