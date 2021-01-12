/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_SINGLE_VIEW_ADVANCE_IMPL_JUL_07_2011_1348PM)
#define BOOST_FUSION_SINGLE_VIEW_ADVANCE_IMPL_JUL_07_2011_1348PM

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/plus.hpp>

namespace boost { namespace fusion 
{
    struct single_view_iterator_tag;

    template <typename SingleView, typename Pos>
    struct single_view_iterator;

    namespace extension
    {
        template<typename Tag>
        struct advance_impl;

        template<>
        struct advance_impl<single_view_iterator_tag>
        {
            template<typename Iterator, typename Dist>
            struct apply
            {
                typedef single_view_iterator<
                    typename Iterator::single_view_type,
                    typename mpl::plus<typename Iterator::position, Dist>::type>
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(i.view);
                }
            };
        };
    }

}}

#endif

/* advance_impl.hpp
vfcihBBF4gMCJEAUIQESAgQIIcEHEEjwgQ+IIvjte/t2Zp4dCB8cx2/Kzu7O7s7Ozs6+BJwOzvU5h20ey8Hve+1d7Sbr3x1AO8gdh+89fnducG/37ZD71jl0p9nCKZfr0vpJH31Hu1ey65RNhUn5qK9ysP0Es89vdTynPpdV3sY1iPrUpmhjBZ6AHxn8yDZxUpdNDwcNcx52UMLsMUDH94Cn644NhmOKsIv1c/DDDo4UpAvK
*/