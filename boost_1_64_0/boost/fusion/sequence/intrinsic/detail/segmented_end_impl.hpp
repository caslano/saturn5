/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_END_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_END_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/container/list/cons_fwd.hpp>
#include <boost/fusion/support/is_segmented.hpp>

namespace boost { namespace fusion
{
    template <typename First, typename Last>
    struct iterator_range;
}}

namespace boost { namespace fusion { namespace detail
{
    //auto segmented_end_impl( seq, stack )
    //{
    //    assert(is_segmented(seq));
    //    auto it = end(segments(seq));
    //    return cons(iterator_range(it, it), stack);
    //}

    template <typename Sequence, typename Stack>
    struct segmented_end_impl
    {
        BOOST_MPL_ASSERT((traits::is_segmented<Sequence>));

        typedef
            typename result_of::end<
                typename remove_reference<
                    typename add_const<
                        typename result_of::segments<Sequence>::type
                    >::type
                >::type
            >::type
        end_type;

        typedef iterator_range<end_type, end_type>  pair_type;
        typedef cons<pair_type, Stack>              type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static pair_type make_pair(end_type end)
        {
            return pair_type(end, end);
        }

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type call(Sequence & seq, Stack stack)
        {
            return type(
                make_pair(fusion::end(fusion::segments(seq))),
                stack);
        }
    };

}}}

#endif

/* segmented_end_impl.hpp
X4iDLxmZPAc1VQ9tFCF4W6kP7WAD2H2LGDZCiPIng2oZXLtEbEqCAHhg4vVLHawAeqFcHJ/QCgW0R8BQOphsL56yCLYiZPBcUDpVY9xuLIXtxc+JV9WDMlN2tS6Nxln2Lxws+1jjGmKiGpWFZCJAQetGps+S2/LIF70emg4XXwvyacsILu7a9nifKIHn8euoitjpy1ljhQVRlJc3Exvp67RlRzo85DUSt2GpLA+0E56GrmM1eEGZVM1dRhwxsmewTY0HbZmYhw+x3cmkGYA2PBj7/eEPnu5rABKV6oGiIXgrV7u/eKi5EQMjfYJBfn2X+9e285Wm4fqOEM0avzTKc6o7vK7neYrRgcQUmHL5RtJ1aErN0P82fu7FA2jBDCsmtmYg5Xge2Hl2cUlDpWY5K4yysUKWAsf9XBRvdImTCNnE2pZBq8VSJNT7lxtgRPKmbn9HaeZoGyXukqUYyMFvoA+Iy+/tD2sS02hKvO8mJF/2U83jX32T4DNeBP3QNf1NzpLSChduhEGf0GVyiNgHX8FazsBRS/OLl4nsZhK37eWr62PLQvw27huBJA==
*/