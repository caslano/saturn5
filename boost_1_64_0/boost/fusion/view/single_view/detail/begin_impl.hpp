/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SINGLE_VIEW_BEGIN_IMPL_05052005_0305)
#define BOOST_FUSION_SINGLE_VIEW_BEGIN_IMPL_05052005_0305

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace fusion
{
    struct single_view_tag;

    template <typename SingleView, typename Pos>
    struct single_view_iterator;

    namespace extension
    {
        template <typename Tag>
        struct begin_impl;

        template <>
        struct begin_impl<single_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef single_view_iterator<Sequence, mpl::int_<0> > type;
    
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& seq)
                {
                    return type(seq);
                }
            };
        };
    }
}}

#endif



/* begin_impl.hpp
G37vMoyjO8urcGezKFMSWdi95/Os6qWQC/uONpdT53SkECn/KjF9lWjFouom9U5fGg/2gJRwSna0R8je0oj8ugsJX69+ifEQE//La4sFDroSoEAD7WyM+of6g1V2s3yiBsTB5pHem1YbTj2ibTd827xWDtPerQP/xllea4mICQq0D5njGmjBiLLyOjvwJWuxwMeMFco0nQ3frhkfCspcMipx1wv3SDo232TuP3MyiVVaqTCLHJcWgsYb/vk4yoJ/CkuwjlbOp8eUaVgWXVy505NhkGntG22Lh1Gx7kiu/D6idIhJvpWzk/zxgpal+F9fOU+NnkEtquItFWbm4GnXuMIUbekkKWDKaS6u3MuP3gUgCg5gYn98dIu22Q7ctQ/Ro4b8dv8KBSKud0HS+SlllvpzdlbqyrkKcuy4DjFLb2iO1o7e6b5t1oB6UbkahlNZR0AkMbljjEFglT44ptIWcwYsI6fA5AlX2OpYUz8JqmBthdul9jeZ4yZnQFByzyR3rY13n/RJvcjhiN0GNhhdyARDSsyBLfSBJ3JSWgK37U8iqnVjaUoi7Rqasg==
*/