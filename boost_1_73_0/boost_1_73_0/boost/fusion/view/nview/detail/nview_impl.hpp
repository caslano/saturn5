/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_FUSION_NVIEW_IMPL_17122014_1948
#define BOOST_FUSION_NVIEW_IMPL_17122014_1948

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/config.hpp>

///////////////////////////////////////////////////////////////////////////////
// Without variadics, we will use the PP version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
# include <boost/fusion/view/nview/detail/cpp03/nview_impl.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/container/vector.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, int ...I>
        struct as_nview
        {
            typedef vector<mpl::int_<I>...> index_type;
            typedef nview<Sequence, index_type> type;
        };
    }

    template <int ...I, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline nview<Sequence, vector<mpl::int_<I>...> >
    as_nview(Sequence& s)
    {
        typedef vector<mpl::int_<I>...> index_type;
        return nview<Sequence, index_type>(s);
    }
}}

#endif
#endif


/* nview_impl.hpp
B2czX85BGSUuAVRC5o8EhMpQgSQKPZBQJX8sZeZUpJk20IMJLJkzTIkgiOfOEeNxDIhFgqLjStg2p0oOKD2Ar43AA8oIG3oA6FEumU8/5Sml4vQRWkZM0BLmjIIgeZi4hjLpnrKusu3SfRd+j8qzhPKsZRxaqZprt2uqDYZTiH+bOJvfLGgWDicRAnnY1J5zCk6nkq5Yv4s1lh2rxUG4Q6Czsh0xmPqIVJ1ntcvhZpxL6E2GfNMDcxtOyuR3Q2I7jijBlltG1pL5vJ0xt2bZCmiiVrqR3u+NKmRjQRIt6AkHDbsKqjS7t7wK2tRbg2lMLEMzjKE+toaDmlhTyIOFiR9quRj9t9rNLoFMIaMctYNNNuDNOXAzG1+P9Z/Hlj4xQRIRWPcEQF7g3z0JAEJCan34XSIfUaEHi480tmKCX5YOX1Xi426KrJ34zL3zwacEkTiwEvwmFMHb0g92qr7PxAvjaIMUB9rr2ZvXs+FogIx5UOdlUIwwFBZM/fvWIYcaJmT1QwGoly05pl0qzL2NcBS648BTIzsccHfI2WlbiLgF78r9YqJP09Sc1RTmIPzSBmYqpW7tITbmLCGXgz/LpAoulzAsmwJ+HqOqZQKhWQQ2jNqeFzwQSNIQutHbgCvEOuFYFfrimrWM4b++
*/