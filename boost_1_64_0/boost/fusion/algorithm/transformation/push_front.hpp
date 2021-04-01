/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_PUSH_FRONT_07162005_0749)
#define FUSION_PUSH_FRONT_07162005_0749

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
        struct push_front
        {
            typedef fusion::single_view<typename detail::as_fusion_element<T>::type> single_view;
            typedef joint_view<single_view const, Sequence> type;
        };
    }

    template <typename Sequence, typename T>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_enable_if<
            traits::is_sequence<Sequence>
          , result_of::push_front<Sequence const, T>
        >::type
    push_front(Sequence const& seq, T const& x)
    {
        typedef typename result_of::push_front<Sequence const, T> push_front;
        typedef typename push_front::single_view single_view; 
        typedef typename push_front::type result; 
        single_view x_(x);
        return result(x_, seq);
    }
}}

#endif


/* push_front.hpp
Wz9vuGWTYxQo7FLrF2LYNzDSe/TjBUro3a4oZz59HCOjUM8LnCGpOtRAyk1SE1ejtzHWIGXUKLc5f1kXMZUBA60eV26BiuIbi4uzenHQLVZGuO8ygbCwM0GxRHQ0LrS2EYjstUqTPO4P3elg6eMXuyRyPlmZaRNYiP5VSSAK+4Vbu1sJRh623w0hYfK+XGKEjmkHMpPgUexd4Fyw/BxocII7gWD60jtMCM3ztVOBGbkWLLmee1iLzUuiRghuzB9kqKUrCnnSks9xB0TA0GgqvVTejTnAP8B9AEAokju4+eZaY47GV+/s316Smz0NIN2Q/K5/hMnJ4qTmQjGot7e2Gi8L3NnMHbjQgjdHRCxvXqm3ReADQ0aSD4tlDCm9KCmj7GB1frbb9iORnoRMwfkGYByc5j4VIdTpaG+691jnuddLkagokOLeD71Ch/kuYsGWA3fRnoy25l4waCaluM+wYiqBaZO7B6Xb/PcE8SYqm1pp53RheOsxAHanN4WEm3VLPKg5BTk2vL198XVq1nBClJ5MQw5umeQW3YWEVjHta4e1BWF3io4NFkg3Vg==
*/