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