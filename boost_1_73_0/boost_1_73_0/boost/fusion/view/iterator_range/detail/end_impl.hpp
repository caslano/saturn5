/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_IMPL_05062005_1226)
#define FUSION_END_IMPL_05062005_1226

#include <boost/fusion/support/config.hpp>

namespace boost { namespace fusion
{
    struct iterator_range_tag;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<iterator_range_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::end_type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return s.last;
                }
            };
        };
    }
}}

#endif



/* end_impl.hpp
Mi0SLdHZdIReyewOOgGO2B0U14IvoiOcf/ehI3QAvZiOesH/I+gIr4yiI3ST609HmEM5HU2WO9CVlNv/7dr0veg8dgtd3STpnpejjySXU9q8X2vLvF8ny9ybZ5mcB1om5+FydZLl73cKknDu6nWxqrAU+aEjLnKNi5WlvOUIBoLOWzBnYZlyu1ed76xldKfU11hD4Ool+nZ1QGcr2xru65O6O94YWm0nDn/j62IaIY6MJWtD+WKf+sIxoLjSwU4=
*/