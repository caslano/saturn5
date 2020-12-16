/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DISTANCE_09172005_0730)
#define FUSION_DISTANCE_09172005_0730

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>

namespace boost { namespace fusion { namespace distance_detail
{
    // Default distance implementation, linear
    // search for the Last iterator.

    template <typename First, typename Last>
    struct linear_distance;

    template <typename First, typename Last>
    struct next_distance
    {
        typedef typename 
            mpl::next<
                typename linear_distance<
                    typename result_of::next<First>::type
                  , Last
                >::type
            >::type 
        type;
    };

    template <typename First, typename Last>
    struct linear_distance
        : mpl::eval_if<
            result_of::equal_to<First, Last>
          , mpl::identity<mpl::int_<0> >
          , next_distance<First, Last>
        >::type
    {
        typedef typename
            mpl::eval_if<
                result_of::equal_to<First, Last>
              , mpl::identity<mpl::int_<0> >
              , next_distance<First, Last>
            >::type
        type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type
        call(First const&, Last const&)
        {
            return type();
        }
    };

}}}

#endif

/* distance.hpp
sZ/hIznrqOI3cy/13ih4MI89z+Hao8jVQz7RH/5cjF0dUUT+RA/Cwp+M5vdfyOhE8rYniZHoVAYe+GazznX4vV8h413EX/Lo9PBe7Avf+Ry02rn9TvzKJOTzIDTgLz3PEQ9W4bPv60duzNnCDOIC9XgqSB6HjmTgTaKS/CsOb33keA9b5C30Dbpg498wP/mzeIS5ry+BT/TqNlg8H01u8CR+4Df4sYnoBvqUvIc5zkXn7XPMjfiM+6i32beX31B//Jctl0sZObPw3sw8N5FHU8eHzsMuliLz/szTjJ7/0aKvQB2+i/rFfkfWeeghdVLK1kX0PhQjdtMb9hyOTPGFMWQaxV9Hw2OQDfNES8gl4VkYPr0BD0eUICfsIkDv5i30ED5bi8hZgSdj5FlenrFnv5YXnm3EH+M/fWH0Ah3yvtybnBVdZE8W+/G/O5S/oel2D3kWOem9Xcgz+aUXm2CfPn7ju9DDzaz1GPLZH33uNJweCPU7OHHelWlNRn+oJWKPlOBX0L2zWfcyct7J5PXnUUNOg7/kFr5ScvIYstkMTfSoPdcjG64JfmON2MtY+LeT/Jp+rJhCXL2R+aE/wxmsh/juuZ9YYeNOxA5/1puexQjyLOiZgUx34bP+Aq8W4kPT1EJX4B+/g0eb8Ik/oy7tTk4S4jo6H72X8+ZG/Dn7T7I/P7/e2ejzVnz0g/j7B7jn14yP4w+nWOg4OQvPY8bo+4ca+pBvUEvTp0/s7gNN+Nax9BCgLf0Zz/Z8Rk4Zx19eO0SIJ6FhHbnXD8Q75Oq7Ej3+sIRcFrs/F31Czkn6tgnOIMVW+HnHAPhajP9jXXxYiveOJn/oTT5N3mihK++BfyAx6M0S1kLO0/Hpv8/qTCLdlxwR/h4Cr0cg587kubZPK2NufKc4A5tnzcRM4KcTV7kv+k/6OfRLxKUjRejKgfgZ9OhMeM2/9xdv5d61xfj0/vTsexDPyKMvxvc+iZxewh4a8LvUCuIlPr9ObvY74im/VRlqiaYRIkGOENoHH7MX30oO5u81jrqMz+RX3sPpSVwBv/lNY2MZ+3n6V/E51P8WdFRtgP8lxFT4kJgPjfS04vA+w/wp7knSL8nsJKd5Az29Dp2rHkqeAz9vA2cN/CCWRQP4Y2qiOLWU73v6Zt2QObl9VSn+cgt+9hx+rxyIbnDtCIsYjE4+TH29lJzyPvxSb2LI36Ajwhz7W+QV+Dh0wkcOFS3j3o+Q4WZk/mt8zg70lj6F9TLX8NdJ6EwfSP7+Kfa6C/5eOBRfhh+4Abm1IoNHiaV+8OhJCeJ+Yj3zsGb6D/2pL7C1j6iJyGtj49Fx1kz/lj02D6X25XfFGHwZ9OEbPOSviZUlfEcFubUhrw+xp9HoyIv4j6dLsBV77+SlT1OfYNehMnxvmtjC3hMbyQPI+ZKDqWnxRfFbmWsKfHyXvBZ607eVEHOQBzVQ1K63riWP4D0n4lZ4dDU85J2PngfgzW0D2Qu6eDjzlSBHeJo6Azn4iUlrmYuz0sQBFn1GfG8TfnoBNeVsegNB9sv5SBreCWoXAZ2+VvT+YWLnRnzdP9kr8TROTpQ+jXqJ/C1z4QDqafj4LLKgJ5TEzjKPk788hN+DjhR9WS96magih9tvDH4dm5pmMRfzJNAV+JaeN4zcEd37mlwDW/HuC9/Ye+hxrmOPiWZqVmQmjhlDDcM+R9FnvJg+NM+Ni70897QbWVO7ZGy/cRq5DbYXW4B/QP5J4mv0sGH40hL2gdw2j8J+huKnoIM+pCCni/N3ev0AbBM7HuZB3+EP/BIV2FqmEzJgj9SQySkW8mVvL9PbeR9d+jm857nRBLEpvhL5L0Ee60uQNXGC2Bt7Ah//Z2w=
*/