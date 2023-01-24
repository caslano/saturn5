
#ifndef BOOST_MPL_JOINT_VIEW_HPP_INCLUDED
#define BOOST_MPL_JOINT_VIEW_HPP_INCLUDED

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

#include <boost/mpl/aux_/joint_iter.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/size_fwd.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/aux_/na_spec.hpp>

namespace boost { namespace mpl {

namespace aux {
struct joint_view_tag;
}

template<>
struct size_impl< aux::joint_view_tag >
{
    template < typename JointView > struct apply
      : plus<
            size<typename JointView::sequence1_>
          , size<typename JointView::sequence2_>
          >
    {};
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence1_)
    , typename BOOST_MPL_AUX_NA_PARAM(Sequence2_)
    >
struct joint_view
{
    typedef typename mpl::begin<Sequence1_>::type   first1_;
    typedef typename mpl::end<Sequence1_>::type     last1_;
    typedef typename mpl::begin<Sequence2_>::type   first2_;
    typedef typename mpl::end<Sequence2_>::type     last2_;

    // agurt, 25/may/03: for the 'size_traits' implementation above
    typedef Sequence1_ sequence1_;
    typedef Sequence2_ sequence2_;

    typedef joint_view type;
    typedef aux::joint_view_tag tag;
    typedef joint_iter<first1_,last1_,first2_>  begin;
    typedef joint_iter<last1_,last1_,last2_>    end;
};

BOOST_MPL_AUX_NA_SPEC(2, joint_view)

}}

#endif // BOOST_MPL_JOINT_VIEW_HPP_INCLUDED

/* joint_view.hpp
M5RS9bud14dZuF7+0c5VpZKqs+/6iLr8GQdxlMlIOXEatBO/bPdGN41Bc52SQZRXihoLnbJu62KQ7vVFig7vvFg1esc4p/HFkeabw+8fUvvBbodjiIQ+0h+g24JGhDCa2M3T5boYAx7WxcatjcWzuPP0b/DHfF5KxFjIXA31i1hFqPBkIjL3/nBfuqwfuR4SL7EaSPicj722YzIHLwbP5ZYaEcAfEUZai5LIc/lHz/nt3hWwj4WoL9t74T8RdldBbbBpFICRn1L8x4sXKFC0aKF4cYeixSlOkeDuFCju0BYIxd1dgzvB3d09EBIgWZud2Z1Zufuuv7szz7znXMjE3U6B6r9LSIBa2a/qs9RHGs+QRounCt9QGl4NZ9xo0uNM8ybbdGOv6aFVY1ahbUjOHC6iLKItonps+ZoRO6NfyW2pdltvye3YZ9rWUwJwLgxDOP+2xiMpOIUOYftljptuu9uS6e0g3UC+hHH2Ah4caCZ5t5254MgHR1akow+WLAOoCTIf86VHaihqYp3dW4LMxyHyfSPTCt2xBIMVtd9I49wJbsolKCnqvPfNOIStB4mIvTqv1ezf8hDxVm4nyXgxENbHsxBbd2yKph3xxMnwWuOv0VLxWuhaLtnIxi71f2HM6j/Kt5j+TqGI6z4UkZJf8jLP3+1So4uyxvzAjIEy85V35weXKYVYyW8yHJTpefglxSHoZq94+yxOPrwr
*/