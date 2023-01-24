/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_FIND_05052005_1107)
#define FUSION_FIND_05052005_1107

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/query/find_if_fwd.hpp>
#include <boost/fusion/algorithm/query/detail/find_if.hpp>
#include <boost/fusion/algorithm/query/detail/segmented_find.hpp>
#include <boost/fusion/iterator/key_of.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/support/is_segmented.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename T>
        struct find
          : mpl::if_<
                traits::is_segmented<Sequence>
              , detail::result_of_segmented_find<Sequence, T>
              , detail::result_of_find_if<
                    Sequence,
                    is_same<
                        typename mpl::if_<
                            traits::is_associative<Sequence>
                          , key_of<mpl::_1>
                          , value_of<mpl::_1>
                        >::type
                      , T
                    >
                >
            >::type
        {};
    }

    template <typename T, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_disable_if<
            is_const<Sequence>
          , result_of::find<Sequence, T>
        >::type const
    find(Sequence& seq)
    {
        typedef typename result_of::find<Sequence, T>::filter filter;
        return filter::call(seq);
    }

    template <typename T, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::find<Sequence const, T>::type const
    find(Sequence const& seq)
    {
        typedef typename result_of::find<Sequence const, T>::filter filter;
        return filter::call(seq);
    }
}}

#endif

/* find.hpp
dxg8dfhn8FSy+3+Cp6+faQOe3iMU/sbxkDUJiX288uo24WnPLuspYh/Dccaxj1/a1R7YOesZSdKExz6+/o/ElrabhvMl2dDXSLGPz9sV4YCx1X2AXQyLfVzY6hmT2Gbs48KwQybxVIdMzc72HDKnPd3qIfP7UVxE9WhiS1shmpcjBW2uYZedreGEohY4oSgSTvj8q/as6+inWsMJcw+1jRMuKmgbJ4z5KiJOKPpfcEJRC5xQ1CpOSPqHOKGoBU4oCsMJSf8MJ1z75f+EEzY80QZO+O/vCE6//R5pTVrYFT05KsSuiPS50fOJppZbt4N0zYr06CZFSC1vaMtS6AnxVQ2pXKt/fxJEHxlLIWjnUvLTjYUm7rDifbzfYgiT5hEEeZktRbyQkjPoqJRLHRWnYLLOt0nj2vf+TgRtURurPKfkcqiiEHPfn78gbdEBFq3dX0XSikTZnrKxOKsO9r1tcT0ktNn4c1bZ+OD2NH4nN74yRmt88hcwn99CgCa6Ulgoz5perOOFXq7JQMqHGnFUMk9pBi3Ui1HndOAXVg7oaaucBPGxKrYEgQMJflKcdeE13qPiBXWXG4L2WIE2AzFQgHvw23aryfURKhBDSDoPxuxpa9B5neSgrzjRjkF7t9Ogd0drg56x3WoyGsIKDnH0dqvByvdbGbBKzEdB2HxU6/Phj6b5qNbnIwPno892fT4mo1paxLn4E1ANdenn
*/