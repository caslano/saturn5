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
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
*/