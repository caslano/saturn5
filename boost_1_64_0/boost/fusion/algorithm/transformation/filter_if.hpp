/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_FILTER_IF_07172005_0818)
#define FUSION_FILTER_IF_07172005_0818

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/filter_view/filter_view.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename Pred>
        struct filter_if
        {
            typedef filter_view<Sequence, Pred> type;
        };
    }

    template <typename Pred, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::filter_if<Sequence const, Pred>::type
    filter_if(Sequence const& seq)
    {
        return filter_view<Sequence const, Pred>(seq);
    }
}}

#endif


/* filter_if.hpp
ahLq091wFnT4VGmHjIxsZo4EB2wkCDbI7U7raEAX4UxTM7eITQARJWhUzBjXGsupTF47EMkLWtik3BslA+7fhjTHzhAZ7JBnPM1umDZD5H7EcBxvX8VslKAPWcwIIHegEqxI0/DMopsZy6XUQ1nPZNpl6MVlpM1dCKGC8+H2WIC406QpHuxyhEv5sQ7MZ9SJjM9rbm48fIorUpN7vrTjFiiGRR8WuI8w/Fb3qqI/9U8SGMFZUzlXDUObMr2wVqnu4eWp79sZs+AUt7pS+iW9dstN6Pxn6qi1fe/tUUozBBxSV6ujE93dsiVSmeL6ID/Mq9ZA6u4NXsslEyMZrKFLhlLYXAhiyJiA/gVihdPHkNXaUEhEj4Q24gP4/Yx0ewXGKh2CxtHTR0l2B+QySny2X1GIENz9/Pr4uiH8RFdAvizYVC3f1Eb4BbEWTAsbZaAFxtm5R0QNPImzy2Fss0iR2hMy5MKNjX5gVaC4VTAfwv1VaAukUXXITBkSpsIits/XqL7CHTV9QE/t9EZd6hbLbDt97+SoFFfIBz42SGRSJkD4J1ZFwryM8MFMEQ==
*/