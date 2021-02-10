/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_REPLACE_IF_08182005_0939)
#define FUSION_REPLACE_IF_08182005_0939

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/transform_view/transform_view.hpp>
#include <boost/fusion/algorithm/transformation/detail/replace_if.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename F, typename T>
        struct replace_if
        {
            typedef transform_view<Sequence, detail::replacer_if<F, T> > type;
        };
    }

    template <typename Sequence, typename F, typename T>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        enable_if<
            traits::is_sequence<Sequence>
          , typename result_of::replace_if<Sequence const, F, T>::type
        >::type
    replace_if(Sequence const& seq, F pred, T const& new_value)
    {
        typedef typename result_of::replace_if<Sequence const, F, T>::type result;
        detail::replacer_if<F, T> f(pred, new_value);
        return result(seq, f);
    }
}}

#endif


/* replace_if.hpp
Z5e9vb60JZdfjXn/y09tiVNECCe9e8r6KrGMBAcfcu5ppCxgS7yHPoREwk/uKUg6Kl9qfJZMg1OZfavpabBk+/tNI1RFj/C1hAiWrqc+NNsfGSkLEK22QRZoni798cd+ewsckYbp8fHyB2gZ2WFY6ReX1LxDi6PqIIgJEAtpZcGiwSEJF8r23DHH6QLU6wsUvR4MJFh7maoHaXMcgK7Pn1BzmAjQHlbMDX1AS1STfeMkKRhEJkdaCsfK0b31NtCa38Uz2YNrMfZnPFwNu8M+ovRbnmlQeYSvep0L+LLn6iSotyOfeGY2d6eCCBtmuuPR59Zkj29np6CpWrTGQ1vmzxiBpAW8YWF1YhdZR01L1exj3cJyRy1L3ayRa5Y3w6lmx7lmpzS3jAL6LlmD0149WiUhdTlInVqa/lRK4EwVg2gxnW9m4Whz3Y65jte7+nsNI/y5jFbhP9ff/IW1Kt/o5/Ky3fY+fnx3efluNPL+OafP/ovWatmDI1Y6/MkDU0PhB+/FPSTU9dGR/YUm8CrxXvL7lx77z24W64wemyuJy7f4TYUCQ3jH58rVLgnE3PMfpRVJxiPLTxZ/tfupihl/w19QefjRn8q/z3awU0+1xg47kCsYY+nsnull5t7avWfW3814mFmZyEtGny+R
*/