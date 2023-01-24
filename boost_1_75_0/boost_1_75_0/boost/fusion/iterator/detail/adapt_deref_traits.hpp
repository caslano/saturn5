/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ADAPT_DEREF_TRAITS_05062005_0900)
#define FUSION_ADAPT_DEREF_TRAITS_05062005_0900

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/deref.hpp>

namespace boost { namespace fusion { namespace detail
{
    struct adapt_deref_traits
    {
        template <typename Iterator>
        struct apply
        {
            typedef typename
                result_of::deref<typename Iterator::first_type>::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator const& i)
            {
                return *i.first;
            }
        };
    };
}}}

#endif



/* adapt_deref_traits.hpp
zMXwCH0u6qpQkC5vRRUF7cyoI9qLpuVT0WS3EuDVWBy3Gl1oAomF/l33vik+5C+RId2aq7Oh6blGmGtrHizSB2tUjX9+gj9L8SdlIb0GH6Fvg/EbFdmWp19LM669ZFz79jqoYIhRwefX6TeOX9fpLAL08yoXXAj5FO1pYRiQ8B1ptG2Voa4iYU+0x/ma3B2O8UqQU90cycwCsM4VK3taCDgHmAPdAK4ZmdZKqh9Y6VAk1G6Rnq4LSwbPm9zTIhw6Luf3MQePxsMspVcYDh6Um8gbvj3NG15qnD2wmW+tj2/mWeLqr9FQ5Wve8Iomb2RWE774/Yx4Br6fGDise9iypkEt61KEL4wnsm5TDzZc2NU5k2njtongyz9lkGfKNtSZRVPpQ/mIfUakMzgrocpoMl3HTdGD8mBcvev76PVe8lC9maLemzPIDBBNrj4uuUWF274WFVYfx3IHsQvd9S5Eu3WmH+0ZMfqtP2Qo8ALCS4YOOJ3HuHLd/32Mn03/v46xOXGM70r/34zxyYOXj/Ho2noxzlkwznZ9jI89Gu/29D25i0EZFcZWxRde6NH15nynW5mM6A5qGhH8oUzEAa+1oj8JPhFOlQuHBPCMPoiycEX7XtZcN3eBGpx/MI6o5XzI4pV+z/A4P7d4HcCWEWhCevw7TXNtGkGb8AHaktJ6WfgMvl9pUgd9x+Jh5/P3myNiPkx4tjhc/V/PFqVf
*/