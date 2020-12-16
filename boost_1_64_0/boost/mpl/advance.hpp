
#ifndef BOOST_MPL_ADVANCE_HPP_INCLUDED
#define BOOST_MPL_ADVANCE_HPP_INCLUDED

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

#include <boost/mpl/advance_fwd.hpp>
#include <boost/mpl/less.hpp>
#include <boost/mpl/negate.hpp>
#include <boost/mpl/long.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/tag.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/aux_/advance_forward.hpp>
#include <boost/mpl/aux_/advance_backward.hpp>
#include <boost/mpl/aux_/value_wknd.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/nttp_decl.hpp>

namespace boost { namespace mpl {

// default implementation for forward/bidirectional iterators
template< typename Tag >
struct advance_impl
{
    template< typename Iterator, typename N > struct apply
    {
        typedef typename less< N,long_<0> >::type backward_;
        typedef typename if_< backward_, negate<N>, N >::type offset_;

        typedef typename if_<
              backward_
            , aux::advance_backward< BOOST_MPL_AUX_VALUE_WKND(offset_)::value >
            , aux::advance_forward< BOOST_MPL_AUX_VALUE_WKND(offset_)::value >
            >::type f_;

        typedef typename apply_wrap1<f_,Iterator>::type type;
    };
};


template<
      typename BOOST_MPL_AUX_NA_PARAM(Iterator)
    , typename BOOST_MPL_AUX_NA_PARAM(N)
    >
struct advance
    : advance_impl< typename tag<Iterator>::type >
        ::template apply<Iterator,N>
{
};

template<
      typename Iterator
    , BOOST_MPL_AUX_NTTP_DECL(long, N)
    >
struct advance_c
    : advance_impl< typename tag<Iterator>::type >
        ::template apply<Iterator,long_<N> >
{
};

BOOST_MPL_AUX_NA_SPEC(2, advance)

}}

#endif // BOOST_MPL_ADVANCE_HPP_INCLUDED

/* advance.hpp
g3KH3i7xaYBFIqtmp5vsNVyr2GhkCSq2gmzyQq+2RU0Jo7T3poDrxHO0ZJG7siV0pLmd3KbtQCdJQmHbtdliB0FhwH5QaSNo1j7OedhCOA2wdCjN2boOe2sqAnu0FCD+7nyezr4BzyKcu0YGnR50XmrfIY+GBGP7/c9sn4SJkA766yJySTZNKufYAqAUqOz+puw7sHti6G0+3I1v8Hr3H9qXmqOw1R+od4RkSwwbIf7ANouGkkBDPYEsE8dufbxL307+Nmfb+xo1NVpV+el/rzyw4x+RJxHdCTO/F32/X/1p+m7xiM+KjkeczOoE4hF7XTrQVSY/RYck9u1jSGJr/2XHVDM+8IhOHR+YW1WyN8GB4wcEliDAX6E9Ev9c2iNVBr+PjgNZXHJhzO5I/HgUPZzlQcXyHNF3OfWh/kOcIO9VoLPBJf4QvjicRrIpE8+DmTUkmKFP33/JbJJyBjhJJBtukWwP9xDi7+IFxPb516vjt7d9t/aOrYpqb76jvTnC1UZse/PBav4u2PF2o481V9nta4cI75hV3YH7W441H0KFTJLKLVRN17W8JhIy45Gbl7+cblDEmIX0HwF7GHggPSTxQwCiPeYyF16gMg2VGTou+20CBC37e/QALfsQWJt7SWHr+paJmAzande3jOUkdt1+XHqvpr0oVIJANfdLwtC7PKy+49D/r8ykJZx0aKCOEAjjBoNTSXD9KKgnPw+wthMe6/oXVvaBpNKqKGP2jS6z9iKdGApNQ+3H64RhoQCK9Xc2pxKF0p3NGYZi7SFJWspJx6PgP82k33BSVuC2mEYvu0Sbg8p1i4U3w0VUnJKw9Scpx8l/RwZ+q5EAHfCcL3jQ0Y7YNHdvSzcm0+hOoN8x9DuXfl3u5GQP/eO/SZu+nT+2/CNlNbCxl2lduzst0X0rHUGWytZ9KxLWauxg8Bcu/A809TIvRhlnITk25mKU9iATt3UxigSc7CVIwkWB9l7mrSj9LQxHYKmW8gOMMbF0IMlZdNug/9RlJpb8fO4KiV/qvJ8EGiKuDHmEVK84cfNEx3lmjHVliLgGTRhka4EixN/5mQ6vPIF1HEeUcqpFfHLE1hJp8EgE21kVZrTyNiC4TxDAiYNVCIraiT7vJlbtsNzbHT7tPxR2Y/f56f7L49zP8U/NL6TgTCNmOX6CZrpR6sJTomNXD4FOFcI4V1y+280c5ZfGvZnjiR907WYOO/4/WX3Vn0fpNqDXTD161dnOqnKZwA2tepLWWKYv1kbHP3xNl+Kk2/EvuP5+l3P89q3X7xa/3ZeJ+O2XUJ99Nl732alR8dtLJnG6gbbpln8uapRu23UTu9S2aP6nKVLdURavfxaOcvbPEdQiKKjg/LpxuncA+stpXWyB7f/C9X9Of8rpmG9M/wzQ/fMz6p9XL44f337AxOj49p9PjYpvPyHYxZYlun8bvoPJX3L/dqxtTnvaeDs3I8bLnuHF1OHT8AnjkZTTQpdCVZ5uxyPhlKCL/Q8kHslP8Trvmi7FI5H9v8kWf2NDjXfHmcX/yCx+r5+G4/sUmHyAGnmRHo7xzL60YAbYwxbYJIANsMCGOvvlQPMzvXYgxUetkkGUDF+Ikl2ORB/zPZ9Pcn4Pr+mz3PaXzKCKrtMVtWzQ19h0F1sE4nzg1p7vWWUuQ5lRVplb9WLWRxf1Vw2H6QBb/fbX4tZU+VaJdRoHhDokM6pDCgN5uk4I+Fcujwk8eZzVpGI06c/j9qW/Nu1tf94/Ef5qbCze5CCJS6kFg8dZltq5cupIWoubvDo8IYP+JoUODufyBxf7wpP1Zbs+jiArFoP0St66rS/npDLuzMHkUYXNZTIeclTlJpvAUOmTF+hKw/0=
*/