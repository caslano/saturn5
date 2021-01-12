/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2007 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_NONE_07062005_1128)
#define BOOST_FUSION_NONE_07062005_1128

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/query/any.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename F>
        struct none
        {
            typedef bool type;
        };
    }

    template <typename Sequence, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    none(Sequence const& seq, F f)
    {
        return !fusion::any(seq, f);
    }
}}

#endif


/* none.hpp
R4vr3/hrvfP+xd6dh9d05gEcP3fJHkQiQRLEkgixLyEoQSy1xtqoVEQShJA0glB7bbVVbbUPSq1Fa9/3tdZBS2kpprRVNIxqUfM9r989NzKXMfPM/DHPI56fzz3vfc9+znuWe877aoVZdrmcTmkJLm1NjsqWT231vKp+BnpU4A6Tp4mWMPldcSaxlKclzuMfRH4zdzOIocRp4g/mMdASoN2zBGu1rbFaolMzLb8z9WoSfZz9
*/