/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_PRIOR_IMPL_07202005_0857)
#define FUSION_PRIOR_IMPL_07202005_0857

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/prior.hpp>

namespace boost { namespace fusion
{
    struct reverse_view_iterator_tag;

    template <typename Iterator>
    struct reverse_view_iterator;

    namespace extension
    {
        template <>
        struct prior_impl<reverse_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::first_type first_type;
                typedef typename next_impl<typename first_type::fusion_tag>::
                    template apply<first_type>
                wrapped;
    
                typedef reverse_view_iterator<typename wrapped::type> type;
    
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(wrapped::call(i.first));
                }
            };
        };
    }
}}

#endif



/* prior_impl.hpp
DYgSIe8OytBEIDSV2F9GrlcOQyv1xAH/aHpcXrerQk5shbbtFHABXKictm5f/fpObEVcIBgXHhl3fnl5BTEkzeADU8XQML0LQyK+oUtRyky0jE9yGagKL8bJoaoMcDCn/2CqW14n9TyoiZpQ2SFZP+/IwqM8cCjE8P4fRTNZUjO5URK1KFQLk7XjDVyWY6UVlo8qzrgWc96MQRRr20JWaGGZlfpYlFvLfdWU5tdONGohhT10
*/