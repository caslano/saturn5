/*=============================================================================
    Copyright (c) 2011 Eric Niebler
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_FOR_EACH_FWD_HPP_INCLUDED)
#define BOOST_FUSION_FOR_EACH_FWD_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/core/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename F>
        struct for_each;
    }

    template <typename Sequence, typename F>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename enable_if<traits::is_sequence<Sequence> >::type
    for_each(Sequence& seq, F f);

    template <typename Sequence, typename F>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename enable_if<traits::is_sequence<Sequence> >::type
    for_each(Sequence const& seq, F f);
}}

#endif

/* for_each_fwd.hpp
x/QtBTZ+GlfTwFzNbuZ8GpBCf34wAilKVefrPqrmp6Uz59UQxnkdZc5LDeFEbswkzks1GV3HqEbOazm3X8/tk8+ZMwYbOS/0J+JjU0S/dKRx8mJjmSVczzKuB1GIfU9ImXIuU8NlyrHMBxeTY5r9JhoasZ+LmOeQsrUlg5H1gkTJo0k3J6EFJ+sFpbXXkog1DtcLRnPB8ogFTx8MnJjlzTuIQiwAICx0VpcSyVqorr2K8FU1HAbiICzMV7qAFyNiakGqoUjmWhDS2cy6gE9Hsv28Lh59nVxdApVcGWXS3NjlUiBKdmN3cl4nUslAPRNRbKM4WMxQNh7BLA7gI55rhm8YCyLMRUcZl3fQRTbDQp7Jv2jJuvIvWpwE/kVg+deFjDuxRekbhZrXGEfpLs8W6i6vRq/0vQuZHaUWX5I/qTuPyZ/U13myTVUeK00nwL3PQpHe9K14tVWfbzbunbHyg2PGjhwzhXTSZByAyTgARq2CeT0yyMCOojeJz0Ul+f5pZXSBLAhF38X6uaNs1I8dZHRfNtGxg8ht+aAQ3taA0+OzlfcY4hj7h7poyGA+t8txQuvOVvjcX8YSbj7Az2+vRRzdfzT93HotPddx9of8fHcsFnt9rFFXynCfOvfXckLgH7yhIfAyicBzfe8eFHRyrv9ReMA4t11gwzO/mlEO4HH2lIZUGu6Y24cTKmeJfMOoEIl8W6i8sAUqn4hy
*/