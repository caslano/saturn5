
#ifndef BOOST_MPL_MAX_ELEMENT_HPP_INCLUDED
#define BOOST_MPL_MAX_ELEMENT_HPP_INCLUDED

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

#include <boost/mpl/less.hpp>
#include <boost/mpl/iter_fold.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/aux_/common_name_wknd.hpp>
#include <boost/mpl/aux_/na_spec.hpp>

namespace boost { namespace mpl {

BOOST_MPL_AUX_COMMON_NAME_WKND(max_element)

namespace aux {

template< typename Predicate >
struct select_max
{
    template< typename OldIterator, typename Iterator >
    struct apply
    {
        typedef typename apply2<
              Predicate
            , typename deref<OldIterator>::type
            , typename deref<Iterator>::type
            >::type condition_;

        typedef typename if_<
              condition_
            , Iterator
            , OldIterator
            >::type type;
    };
};

} // namespace aux 


template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename Predicate = less<_,_>
    >
struct max_element
    : iter_fold<
          Sequence
        , typename begin<Sequence>::type
        , protect< aux::select_max<Predicate> >
        >
{
};

BOOST_MPL_AUX_NA_SPEC(1, max_element)

}}

#endif // BOOST_MPL_MAX_ELEMENT_HPP_INCLUDED

/* max_element.hpp
cQyrcypr8hzW4kWsy9tYjyvYiA+yMT9kM37Ko/klmzPyUUELluKxLMPWrM02bMK2bMp27MgTOJ6dOJOdeSW78GZ25a08hcvYk/ezF9fzVL7CPvyC/VmslHoPdmQce3IkezOR13Ms72AyVzKFa5jKP3ISd3Ay32Ua7YtCGazIqazHaWzA6ezAc9iPs3kXz+eLnMc3eDF38gru45U8uIzrQJblYpbn9azBG1iHN7MRb+XRvI1t
*/