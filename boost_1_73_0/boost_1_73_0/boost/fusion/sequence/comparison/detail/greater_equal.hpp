/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_GREATER_EQUAL_05052005_1142)
#define FUSION_GREATER_EQUAL_05052005_1142

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/support/as_const.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Seq1, typename Seq2>
    struct sequence_greater_equal
    {
        typedef typename result_of::end<Seq1>::type end1_type;
        typedef typename result_of::end<Seq2>::type end2_type;

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const&, I2 const&, mpl::true_)
        {
            return true;
        }

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const& a, I2 const& b, mpl::false_)
        {
            return extension::as_const(*a) >= extension::as_const(*b)
                && (!(extension::as_const(*b) >= extension::as_const(*a)) || 
                    call(fusion::next(a), fusion::next(b)));
        }

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const& a, I2 const& b)
        {
            typename result_of::equal_to<I1, end1_type>::type eq;
            return call(a, b, eq);
        }
    };
}}}

#endif

/* greater_equal.hpp
+F056cqgIy+Vsa98dc85V1cffZ1VijJcT0eT6UKM7xY/xXS0XM8uxXWvzyO6orcH48H7tR4GONhE9wpubDvErTW/KfVvRwvxjN3DqAe2h0RivEKexTEOQ55x1EHEXuUi9IU4JPQQcgufOCAfROiyh2EBOTZ1a/Vj7nE0PsbH8/NPOMHZ6dlphImsNBVYeqoSso8RLlTn+ZbLp6eho68RyEMWwz3VKtcOzmR+Ky2B+4VOqXKkIB0UudTqhH90BZ8TMl0Qxje369n8KsI212keSFrTwOWmKRRyuSFYSklvdhy1tB4mYziTK+08EzZem2rI2gRPtnSBI8jLwhnIjdSFTFhIeuTe1+5zHKeNLTj7WJnUxenL9Ie5L//OZM1JlLKFqT28QeMoQoiMUBqls2C5IOysm6TQLo9es2GpSsXGwlFRBC7GaXK7tAnLfXmiEIaaM9Y+GGcqF6S2uSn/CeQ6BpassRULcR04SBkuc4SGj5LtgruZv0jsa9oV+L9L85qvgqk4GXwYLTFbfkAinXYR7mer65u7Fe5Hi8Vovlrj5hKj+TqQ/ZjNJ7z0msUs6Km25FjcQpd1oUntNd+vxT0+/UGYD6A3vq25nBnrFTqx0rYnW614OzVVGrYC7xJrNuxRSFqQdO0wZWzc6+ss
*/