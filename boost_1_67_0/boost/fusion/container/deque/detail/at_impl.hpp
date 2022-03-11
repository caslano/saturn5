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