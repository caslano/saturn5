/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_DEQUE_AT_IMPL_09122006_2017)
#define BOOST_FUSION_DEQUE_AT_IMPL_09122006_2017

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/deque/detail/keyed_element.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/identity.hpp>

#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>

namespace boost { namespace fusion
{
    struct deque_tag;

    namespace extension
    {
        template<typename T>
        struct at_impl;

        template<>
        struct at_impl<deque_tag>
        {
            template<typename Sequence, typename N>
            struct apply
            {
                typedef typename Sequence::next_up next_up;
                typedef typename Sequence::next_down next_down;
                BOOST_MPL_ASSERT_RELATION(next_down::value, !=, next_up::value);

                static int const offset = next_down::value + 1;
                typedef mpl::int_<(N::value + offset)> adjusted_index;
                typedef typename
                    detail::keyed_element_value_at<Sequence, adjusted_index>::type
                element_type;

                typedef typename
                    add_reference<
                      typename mpl::eval_if<
                      is_const<Sequence>,
                      add_const<element_type>,
                      mpl::identity<element_type> >::type
                    >::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& seq)
                {
                    return seq.get(adjusted_index());
                }
            };
        };
    }
}}

#endif

/* at_impl.hpp
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
*/