/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SINGLE_VIEW_END_IMPL_05052005_0332)
#define BOOST_FUSION_SINGLE_VIEW_END_IMPL_05052005_0332

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
        struct end_impl;

        template <>
        struct end_impl<single_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef single_view_iterator<Sequence, mpl::int_<1> > type;
    
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



/* end_impl.hpp
zDfrq664x81z+Gf52d71GAeI8uG252EZu3/2OdamDY4JHrfhOHZy2V63GHRW9mfpI7fbK+7jf8Ze/njv4Sc+Gz8m3zOd/RH8yHcJvrn0XDjYu/g/r0PrfYzj+dl5hDiyu2p3vZW8i5WGOi1bnQh7E00H5wp2NbQnvpL3gSrhn26VKuoAA77HB/ZWv310Dmpn8j5QYaMzXd9eor2o4bxi61uJM1OFOfY4q2DQbfhgK8H7BQcb
*/