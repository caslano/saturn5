
#ifndef BOOST_MPL_INSERT_IMPL_HPP_INCLUDED
#define BOOST_MPL_INSERT_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/reverse_fold.hpp>
#include <boost/mpl/iterator_range.hpp>
#include <boost/mpl/clear.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

// default implementation; conrete sequences might override it by 
// specializing either the 'insert_impl' or the primary 'insert' template

template< typename Tag >
struct insert_impl
{
    template<
          typename Sequence
        , typename Pos
        , typename T
        >
    struct apply
    {
        typedef iterator_range<
              typename begin<Sequence>::type
            , Pos
            > first_half_;

        typedef iterator_range<
              Pos
            , typename end<Sequence>::type
            > second_half_;

        typedef typename reverse_fold<
              second_half_
            , typename clear<Sequence>::type
            , push_front<_,_>
            >::type half_sequence_;

        typedef typename reverse_fold<
              first_half_
            , typename push_front<half_sequence_,T>::type
            , push_front<_,_>
            >::type type;
    };
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(3,insert_impl)

}}

#endif // BOOST_MPL_INSERT_IMPL_HPP_INCLUDED

/* insert_impl.hpp
tkTnY2NZZot8L58JUyojGpNU5Ch5gRP3ICTDtxBnXBu0k7SScvsWVOk0J8ZqLlfofXTSToY8GQNlSD/P5cTBZtyCyVSVJ8SBhSVCgrkg7JhAqlUBXEJNrEajKh0Tccwx5phtGaypvcyFg9lQG9cHUmlomHqZtSUZ7I5RitxW5HHquVQOdYzY4QYil92hyJCrmOfw5811nf8pcGuxKC18kWIDXyuinVLmyxzre3DWMCc3rPETxaoouEx23PhSdVRly8qe0peQcV4lSLXvdIpdROdnzNjR3eOM5WrFXGkd3d3iALj1OiUOGoAvrGGtBcGURGyqNNbNATsgupKGuNiBnfj/G4MgRe82RQ5EnamBB92eDyhjlQi5mviVTTtD/x2p7UPvVc+cKhlLM/FdESib9Xq99426q/SK+Y5th8PRDv9F1E3UWuaKJw6WUyUVCiBSEXPHZC2BKOMmA0vtO/FNxsPzgT+NL5LeWYJLHPViHo76ozDsnSEfhUFyMRj1g5SPhoN+L07Plhf9fhryYBCPlufD/uAc+XIYRsw5bSKy70JGu5Y0UPBNvB8pSjXwW1CVzltMLnsfSo0p9baMSTLq+dOWk6NPtw+L+d34yLX63e39grlcI0bmbfR9rJoh5ihypLGWtYjtKHXfzW1E
*/