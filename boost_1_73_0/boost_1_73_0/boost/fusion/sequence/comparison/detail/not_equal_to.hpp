/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NOT_EQUAL_TO_05052005_1141)
#define FUSION_NOT_EQUAL_TO_05052005_1141

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/support/as_const.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Seq1, typename Seq2, bool same_size>
    struct sequence_not_equal_to
    {
        typedef typename result_of::end<Seq1>::type end1_type;
        typedef typename result_of::end<Seq2>::type end2_type;

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const&, I2 const&, mpl::true_)
        {
            return false;
        }

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const& a, I2 const& b, mpl::false_)
        {
            return extension::as_const(*a) != extension::as_const(*b)
                || call(fusion::next(a), fusion::next(b));
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

    template <typename Seq1, typename Seq2>
    struct sequence_not_equal_to<Seq1, Seq2, false>
    {
        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const& a, I2 const& b)
        {
            return true;
        }
    };
}}}

#endif

/* not_equal_to.hpp
XEPYWukA1VLgMc+wIMCW6Q9Sluk0aFa8ALLQVYAoyWk19PRSqBK0KJ2arSym1FWYJI6p34xk2YwiwFpFUVKnCEPmtsGTOJqb9BLuYbLEwmNSb43CnCm0GR9myYTHlN0l2a21RVElYcQZz5o3ZcPv3JYVjTPMsqS3xBaVPsPJbUgVMwLAR24pHoaRyRFgD+9nLzNogPWwRPMZtKpNnTwYBrkeIwlHe1U6T5OcDcFHoHZoWdCyk8HP0N8kfhYNZRb8iXkCkRbICsHrBfBU1hd/4yWZ5iyZZPSXKVUDKOOor4AOpiNtgmoxbGoqFSydU8Ed01FAh940YjzNEpb4SaSYUEV4wcNMdA5tPpFQpDmCMPeiKLnj05xmsTehPIz5VNkLYCryGNOMxjkshv6YcnOKNWRYwUAvjBnNhp5PNX6L4+EArSjxvYiH6dcau8XPYn+LsL91siFSM9hsaNwadTPHsE+JaLPXo4YNXe6IHzQYH0XJAApchlwzpYsxS8lY7xEVgtaDjgJjE95iOOvzN8zNkIq8EWxZQy9vTGVZklUbPrkIHYpOH/Q+FQvpzfU1ty7wVjkSuKEXAlB6lSxIKMZT58e7LGTUNv9gtRd8UTjZaQ1hHuOJx/yxvkGUYWzya3Qs858uckyBw0TMMGJs
*/