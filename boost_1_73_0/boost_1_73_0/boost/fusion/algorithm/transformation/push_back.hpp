/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_PUSH_BACK_07162005_0235)
#define FUSION_PUSH_BACK_07162005_0235

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/as_fusion_element.hpp>
#include <boost/fusion/view/joint_view/joint_view.hpp>
#include <boost/fusion/view/single_view/single_view.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename T>
        struct push_back
        {
            typedef fusion::single_view<typename detail::as_fusion_element<T>::type> single_view;
            typedef joint_view<Sequence, single_view const> type;
        };
    }

    template <typename Sequence, typename T>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_enable_if<
            traits::is_sequence<Sequence>
          , result_of::push_back<Sequence const, T>
        >::type
    push_back(Sequence const& seq, T const& x)
    {
        typedef typename result_of::push_back<Sequence const, T> push_back;
        typedef typename push_back::single_view single_view; 
        typedef typename push_back::type result; 
        single_view x_(x);
        return result(seq, x_);
    }
}}

#endif


/* push_back.hpp
+ixrdYLJlULty0LQdSiHpHm2oxfzUJKEIK1/FmLi8FIb5LlQk0Sr2BEfT/9ITIjqgpWBkoybg1Y91CDb1nZQ9kPk70s8v4FVnSXj8dfn5SF0wKOR3V+Hs3F39HdAAoT1PJHl5fyyv7JyJpqmJIhErgmwbxxK4nkq3NiItfQMwS3aNHBiPG9E20Twq8akRTvWwdUPLAf7tONJfXLE9XiKnb+Fbz9dUNNQ9aUBPrUOqr8jz9WhFPjJ9XXasB30pDHi00eqqA+1VgWJMiM8PSBIvKJsmoYqU0zVVSNUK+vs7pSLAhV2wT20JpcIyjd+UzKTU3P1oXYQvrpKJKeN6lnHojNLyvUAAuagtlTz36HyBjNxq4Bjp7i0BuB3Bp4Kqj6QkW4DLjMZFUDH5FBVGjncE50nrz5HxucXTLFM59H6Pki+Z1OLARFA+pl/1w95sfip4hTf6ZLP1IAV3VxaSv+wZYTPTlbBnfnivDnqtNIvuPl5kETTvFZ8R52s3czn7c4H30Qtq8/b0S2UvBWd9vwPfRKFxr71VS+8jddISuPtjAZosFsFgfitFMi+10RVJbOAuT52UhY7O/jeuHvp5ebOzyo6lglPOv5TExa+nNrdzIMf8WZV6Hny5fypnomawcFFxSKSiH0dcd3j+TLM
*/