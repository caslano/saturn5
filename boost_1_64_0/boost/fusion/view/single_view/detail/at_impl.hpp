/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_SINGLE_VIEW_AT_IMPL_JUL_07_2011_1348PM)
#define BOOST_FUSION_SINGLE_VIEW_AT_IMPL_JUL_07_2011_1348PM

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/equal_to.hpp>

namespace boost { namespace fusion 
{
    struct single_view_tag;

    namespace extension
    {
        template<typename Tag>
        struct at_impl;

        template<>
        struct at_impl<single_view_tag>
        {
            template<typename Sequence, typename N>
            struct apply
            {
                BOOST_MPL_ASSERT((mpl::equal_to<N, mpl::int_<0> >));
                typedef typename Sequence::value_type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type 
                call(Sequence& seq)
                {
                    return seq.val;
                }
            };
        };
    }

}}

#endif

/* at_impl.hpp
68vK3NDPlbS9G2QwUsYs80hBRcqoIgxZ9ABFxcSXBT04Uq4xqV6Sn72TM013Age0YWKl8Mo3F+mELoXCbBRqnBEsDNWBZLSSMSlUcjG8FK5DN4ocIeKStyqAZvbN8bPrnE157+VAqy1RjKnAiPEthGlAB0i8SJHgM+ee6sZmwAizCbrWrzhaQ9vhWE89LifeeCNmk8EMTdeT6SgyYmhmKWK0XvNfEni0IaYW/+AQg81ursJm3heRJjXcO+ZOGQOLdlQcrESkBtZp6y6Ku4HaGVSImduR64MX3pZ7EpnlieNIydHuowcRRn3Nbs/fv7MVmfZdNl24TFVruupoeIPTnRf6zKEM4W8sya7rMr2gNKu2qz7Q7fJYda/VxXAFnmOTJUOcfEE8ak1R2gHprEwOxM+b/yywdkgQ3zeelP96lNszBYiQrkvgBRIgsyzmFI82G5h5ZgJIZ5F+U7NlGyJiA8KgYmmnMrFU6Ny6A8FKBSUXJSN1OaCQ1qtXOYKwyEe/+m8sXUPwyhc1l1wOtqwTNep6/q1W8lAIKNroGzbNy6VpiKRnmOR5P2ZxUw==
*/