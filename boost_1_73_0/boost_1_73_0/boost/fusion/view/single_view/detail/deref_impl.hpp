/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SINGLE_VIEW_DEREF_IMPL_05052005_0258)
#define BOOST_FUSION_SINGLE_VIEW_DEREF_IMPL_05052005_0258

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/equal_to.hpp>

namespace boost { namespace fusion
{
    struct single_view_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct deref_impl;

        template <>
        struct deref_impl<single_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                BOOST_MPL_ASSERT((mpl::equal_to<typename Iterator::position, mpl::int_<0> >));
                typedef typename Iterator::value_type type;
    
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return i.view.val;
                }
            };
        };
    }
}}

#endif



/* deref_impl.hpp
tShJ82sCAM62PohxpKqYlbGSjcip4XUlt7WoVid3dPbLFghpwhXsC4KyEteyjpIEMGRUdAMSLqNokmZ3LGjq8awStwR9HKkeRzXLTOqPoi4vajweEpawYuDpRQbi9+jsZqsnQE5g76TI12pcegZnSdK5Lmi46L2kMWGP0DeK42KWwwQvYPCKX8BmsC8O15c5zqLku7Op73AshVuDxp734R/YM0oubiAApbP0CvEfn17N0kzLahH3YbpKjIqStIHqLo/HZZEXAIM8mki9uWrAchHRE7b+Gg6nuCVJtp6nH5oruHxxPtw/HB4+aBXlLFfiuZsDRt/IAIdSM+gjkawIuUsCygCquCJQE0OIRC5voRnii+lHmDKbIgrDEvbPjkw3HK/C8SLaPoK96uOqkkrv52gEw9xpZaG+LQQI8JsUgYMYpzbWs5AnRuHuuS6KAQyDgzl7JwRyTwGg6oFebbG0Q+uRW8790tKFIopK8UtcZAWKRi1mU5ifMC+tNI0YyhVwThNZj4ukD1BXLKY2iwCFKo9RdawIqKBFwoh39qkeC3cAo/Wd9gTXhTilO3K/uY739kun33E/IJXvYKMyTkdpPL+wdLpl2m21t9NwxDNeuOASFL74PUCHIYs6nJwApEhR39b0QwSloNqABGLY
*/