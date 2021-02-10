/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CLEAR_09172005_1127)
#define FUSION_CLEAR_09172005_1127

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/vector10.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence>
        struct clear
        {
            typedef vector0<> type;
        };
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::clear<Sequence const>::type
    clear(Sequence const& /*seq*/)
    {
        return vector0<>();
    }
}}

#endif


/* clear.hpp
+4H4b73PKWbZAVE8u/TSyl2dPN6zIpEH8R+YG7zGeJ6ZxRMl4QthBXmXGTbdgHIhG10xTwoDUnfF9UQvp3mAz9+zvEywrGtYtK2ak219JNowOf9Ax1TLNvl7M9tk0v8k+H1U2eqi2emiVR0zIX5irowJ18wpLmZqrZLvT3U3+tQZAFCDidf3aCl80fRuQ+sZ/xDF1QvRBSfLebRmgYpWnZVgmhsAWtB+ENmcKSWvuRTV76x3vdHCVvywYC0cdm9BmzAjXmMGZZH0y9deODvwevE6FIZqGaxou4EIL1chHM+Slx64SWarYu2GljmpuhcMeEecOh52a14Mb9KHKAk1bjMiWBcbnxh1E/N4Jte3C5tNIaZ1rS5OvQATHP3tb2L5eLnems2RU65mvrsV0sF89QTS6SbVSGdaPQvpXiiisg3OlKJMcEM7vg3GgK2G0zJLVsCa37zmDZONLIdGgkoiWtwFqBkLBqBihmm76A+9ZrcrYBMG50NMhBeChU9a+pHeGSydnaWo07JHjGHYWg8llzzcPXoPkADh5rcg+cJ7mcGmlxbOs7FQtHtmLlBj0Pfw1QEWMyUj1lKGkB6SFMg6jg+q8Zz2sMBsEpKW4dtF77I5bn0sRTLr/YR/YxRjQsMUmkCRUJEsYzgoKPq+
*/