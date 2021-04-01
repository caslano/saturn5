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
6YJVrOO9xVQiI7n9naxmNbviNL5xs+j4SyKxBxpWSFJ5z9cWsDlPBh+aDaJ4mMFLpmJb/9VqS6QPlBqWe3OIhUM89YOhyTbq5DTIoJ5i847n4gKhNlyo35m5Gs8hoCMM2mHF+Xpcoim2Vwtry50BuWSo7xdTo7AODxwecuKUxxlbt7yi4nxETr/442MGfCDt4TVcEQyyXA9tuiDiYlwtwxSy9kaxwBQhK5eFT+u0wUXE6aCazgzUJiqAU3GxSyiltHiB6sQZ59UZMFxUmEQ73HybcAun6lUiD+7EWMgs5nBt4KSJTwMaSnXNSuNKrKzd95FX1/aYwNHU316WSqKaWGOf+OdP/SWKPn9o8DZbDXrB33VlStwq1cV1Ss/M+dTmYtsksE85ttWUNgDGazMo/PXtU+zBVioM4HSZaxd2Ihu0WF2Np8Tw6FWiO9Qa+ae20OLKaJxEFAOcCeKMCFUDMmAMMx/QdcIo6bBZDo8A6UbVTCmvaQJEfgpxv8YPx793O/1I9UFvtOUJKosbcIguu8rAyDqTmOCbKBk3I8Cztc7ek1q37TqJbz2P5A==
*/