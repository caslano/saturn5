/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_REVERSE_VIEW_07202005_0836)
#define FUSION_REVERSE_VIEW_07202005_0836

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/support/is_view.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/view/reverse_view/reverse_view_iterator.hpp>
#include <boost/fusion/view/reverse_view/detail/begin_impl.hpp>
#include <boost/fusion/view/reverse_view/detail/end_impl.hpp>
#include <boost/fusion/view/reverse_view/detail/at_impl.hpp>
#include <boost/fusion/view/reverse_view/detail/value_at_impl.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/inherit.hpp>
#include <boost/mpl/identity.hpp>

namespace boost { namespace fusion
{
    struct reverse_view_tag;
    struct fusion_sequence_tag;

    template <typename Sequence>
    struct reverse_view : sequence_base<reverse_view<Sequence> >
    {
        typedef reverse_view_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef mpl::true_ is_view;

        typedef Sequence seq_type;
        typedef typename traits::category_of<Sequence>::type category;
        typedef typename result_of::begin<Sequence>::type first_type;
        typedef typename result_of::end<Sequence>::type last_type;
        typedef typename result_of::size<Sequence>::type size;

        BOOST_STATIC_ASSERT((
            is_base_of<
                bidirectional_traversal_tag
              , typename traits::category_of<first_type>::type>::value));

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        reverse_view(Sequence& in_seq)
            : seq(in_seq)
        {}

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        first_type first() const { return fusion::begin(seq); }
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        last_type last() const { return fusion::end(seq); }
        typename mpl::if_<traits::is_view<Sequence>, Sequence, Sequence&>::type seq;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(reverse_view& operator= (reverse_view const&))
    };
}}

#endif



/* reverse_view.hpp
Q5QySwQsjwZGOsi9kI3cCkBeWIIFrqL3tFK10Iy3IoyAw4flC23biOin7j3k0lhGHE8lgF1qvhaGxJr9WlcEZABVAEj2XwK146ytzdMqFt3JEQAi/LJAVGE3G7L5yreMjsHvz02C9ZBrk8poNF2QDxURU/WMa0Xz5TYnnkee6GZkI54zUnasg+wK4M9BdjzRWRq7DP2WC5BgB0xBcu4vdvnfKDxWH02VfdLYv5CwmKtAVzjwY/rv5CsFp68XKiy/DHZcNq78kS5LVVtxe59BtY1KkfmVGGpeP5ROUQu0gv7SuTm4r2qi9mBf5zWnQnhzp93Mqe/nJepnz+VLayqst64kq799T/zpnbmiEXiMpa7uv9WnKJMOeT8bKmdx1zIBGh5wXTrsRhjxYzy9HKYATOoY5VzDk2J013Tgy79eAr12lxGCkLVQilr/ogULwJTKiRx1qZmfKwB3oAFOjNyi0ycV8+ftzT936Dx7HSLYXo90mXHySuQZ5WJroyERo5o+yyDinxyZk82UpDDgs33t4Qqa6K/rxIaTw18mPo8O081Hx/KyMhXCLNkJ5Nq53+N5qFZfWjCEFm30Ice4aQTHVRhOaHES5BT/JJr4DDPXL4vsZjHWfUSXjRuCOl+pemQzqwJtv5o7+rzj5IUzI5lNg5cC2wZ8nprchyd9CXlmXMr8hJoN1b03BL+WaS0NA7LQe43OLD2O2Fkh3aKW
*/