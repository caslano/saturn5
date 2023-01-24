
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
LWxCK2TSlTb5dBmpv0il0IbSQDKs3Ko7KtWQtcQsI5gsjKO73UnpTVz6AUTWgt9Ca4t2GoLXjdedGdKMQhVCFbX4ftp6q7KtutJbEDUzZDWYs1vXjMq5vWhkCIhmFev3qYtgCesMzTdkXZJuqnp1LcrLTO4RmXBsZrskTHSCY4iZh35ds18vvX20lVRLWC5CGU8g769bsVkrbyRCeXxyaOPFz2vmdpBITFNL7XXW1bxhT9AijTpGS+3abrRY+7hTRSpinu3pV5FI5VWxJQYO3l9K+lhNg/XBQl56W8iXjjZKruI71Znri92+YYU8o2tEiNGCjYguiMpjMNRL3yJS6uJPGeds289RlHOmPWFmr2p6GeEiLDZNJqDn4qlC/5L7ECfLQnd5t1bGJqqmunNfB5YDawn/hREN0azHM3xZeGWNLh+L81nJfn837ELDkpuWsuGiyaJK0NeAwjtaKeASegw1e3OylyBTLfYq6Rl+tqQgxM+MiS1832bxpZxlDuDysTogApPtZFiz+nwQvBH0W3CJKro/tHNq35J7idbhw+L8IiYVvn7Sc9IPKuxIaYdX9ZPRrXrGflPRlrIxWQ2Yu/EV81L9j+ZV54Ote87uDSwnuJEF93/2k7tKr9C6KiQMvkhVtJgQMxZZfW43aAs1rkTcb8Xfr7eHNp+fHeM3eXgAoBdnJycry7MbK2u9v1WO4tqd+HulS1yHuNtf
*/