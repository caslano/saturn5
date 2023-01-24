/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_IMPL_05062005_0906)
#define FUSION_END_IMPL_05062005_0906

namespace boost { namespace fusion
{
    struct filter_view_tag;

    template <typename Category,  typename First, typename Last, typename Pred>
    struct filter_iterator;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<filter_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::last_type last_type;
                typedef typename Sequence::pred_type pred_type;
                typedef typename Sequence::category category;
                typedef filter_iterator<category,last_type, last_type, pred_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return type(s.last());
                }
            };
        };
    }
}}

#endif



/* end_impl.hpp
NlWRnnu/OACX1ccR9fuNlvGeu9OqwZMmDdyH6Bd3Tb6yMxYxhladV55xNvm5Oat6g3ZX7ZJFpUvj3Kq85Nx3el9EXUnc66yi6VhQb7Dmd3MiHe5zIggJi7+/APPdHd33WXtYzuxGDrRm5U2pLipqecjSMsAEVVoXupp2vSoekBJJLtbli/NsikToGu3EOEOWBdRzpzfQ03tgbF7Pry1SJ5h7QHdu26+zxoaVzkdFEHXyrNU96QmiyS3Ej81zGOsWuQgqVlgo1P9mHnjGNkDND/wtBD6EqGAyYwJOri1Q304AKuh4bWL1JgnylMTjtodGkLaU/Vs2XvYnQt5Vq12J+vJ7Z9MWpktfZdKyfSh7/ubfcb3XZQICIH7c5s5ONmdEGQ364pPi450F6ib4hn7/9rQD1q1i+fip5plVjfxc2ePqwo2Demx6p6ZA5wvl11wPGajyLHOvs5CefNb7fP5mlvgqXWWJixDtu22lxTE0ZtF+8f9ECmUGvcha67H+kjaxPm9rdlCx8sH2Ta6iCe7c2/BTRAUTxEGHrBVL8wv3LabZcxlgHsVDykgSQcuS8rrw7+GMBhayC1ydcWC/33Yaa8nSIJVbnDjWdxl/0xgae/BX+babzVN2YZ/zYYakIuAUbkE24+CXlHHbu4ML9PpXtFOIh62Am604SVBU/05yFlrYjXny/KrKy1MCSbSBJ7ro01iLVlVnjC/W+HG8
*/