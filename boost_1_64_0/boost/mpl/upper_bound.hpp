
#ifndef BOOST_MPL_UPPER_BOUND_HPP_INCLUDED
#define BOOST_MPL_UPPER_BOUND_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
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
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610))
#   define BOOST_MPL_CFG_STRIPPED_DOWN_UPPER_BOUND_IMPL
#endif

#if !defined(BOOST_MPL_CFG_STRIPPED_DOWN_UPPER_BOUND_IMPL)
#   include <boost/mpl/minus.hpp>
#   include <boost/mpl/divides.hpp>
#   include <boost/mpl/size.hpp>
#   include <boost/mpl/advance.hpp>
#   include <boost/mpl/begin_end.hpp>
#   include <boost/mpl/long.hpp>
#   include <boost/mpl/eval_if.hpp>
#   include <boost/mpl/prior.hpp>
#   include <boost/mpl/deref.hpp>
#   include <boost/mpl/apply.hpp>
#   include <boost/mpl/aux_/value_wknd.hpp>
#else
#   include <boost/mpl/find.hpp>
#   include <boost/mpl/bind.hpp>
#endif

#include <boost/config.hpp>

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_STRIPPED_DOWN_UPPER_BOUND_IMPL)

// agurt 23/oct/02: has a wrong complexity etc., but at least it works;
// feel free to contribute a better implementation!
template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    , typename Predicate = less<>
    , typename pred_ = typename lambda<Predicate>::type
    >
struct upper_bound
    : find_if< Sequence, bind2<pred_,T,_> >
{
};

#else

namespace aux {

template<
      typename Distance
    , typename Predicate
    , typename T
    , typename DeferredIterator
    >
struct upper_bound_step_impl;

template< 
      typename Distance
    , typename Predicate
    , typename T
    , typename DeferredIterator
    >
struct upper_bound_step
{
    typedef typename eval_if<
          Distance
        , upper_bound_step_impl<Distance,Predicate,T,DeferredIterator>
        , DeferredIterator
        >::type type;
};
    
template<
      typename Distance
    , typename Predicate
    , typename T
    , typename DeferredIterator
    >
struct upper_bound_step_impl
{
    typedef typename divides< Distance, long_<2> >::type offset_;
    typedef typename DeferredIterator::type iter_;
    typedef typename advance< iter_,offset_ >::type middle_;
    typedef typename apply2<
              Predicate
            , T
            , typename deref<middle_>::type
            >::type cond_;

    typedef typename prior< minus< Distance, offset_ > >::type step_;
    typedef upper_bound_step< offset_,Predicate,T,DeferredIterator > step_forward_;
    typedef upper_bound_step< step_,Predicate,T,next<middle_> > step_backward_;
    typedef typename eval_if<
          cond_
        , step_forward_
        , step_backward_
        >::type type;
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    , typename Predicate = less<>
    >
struct upper_bound
{
 private:
    typedef typename lambda<Predicate>::type pred_;
    typedef typename size<Sequence>::type size_;

 public:
    typedef typename aux::upper_bound_step<
        size_,pred_,T,begin<Sequence>
        >::type type;
};

#endif // BOOST_MPL_CFG_STRIPPED_DOWN_UPPER_BOUND_IMPL

BOOST_MPL_AUX_NA_SPEC(2, upper_bound)

}}

#endif // BOOST_MPL_UPPER_BOUND_HPP_INCLUDED

/* upper_bound.hpp
ltvaXhiqzkKfuU4K6dB6YTXsMDtB77d6RrbnEAuR2Myk9ZhskALbUI64R9AXNkKtvPC2s3jhrS8oOZAeeg+4U69dePbXjacmw6q+g/jOEgqWkkKN3U+XRyhc7Fj8ir8rxPVONyyDZWQpsuwI34WVjkjUL45Tvoch5ucN3w1CJx+ogTN/uPLKohxUMHkAU3zz88eb9zM5IVvopgEkuXBld7V0/5HTkak8vkYVfos7Pq2uI5GJw+791v/U/ZRpPFmF7Sqot0/ld2E0AJNmch+ejyD5p8oX3BIyPavP8Z6nl92DGWrZhc913CzUagZ/iYgci8V9Ku89ppF5s6/kclApYvvxlUJRqkhkjNSx5mLxEzpK66NcQbrkqIpsQz6Yp0YRTBGp+vfzPOqQInHW+Cd3vRlgASjF9nFDBZY0aY2YTA4HIC9RZc/I05IFKnvLUI7Ih0C1nifrGjuk7WYTe4TXg0tpF20vsZXGrZtbT644VsnP1GQV7ceFYZJSmP4WX8OSxtzaLzCa79osVB12XbBHoZsPJ3uZkSxkn7jDoaFhDCvE4gtWaDSQ5Q6blSJPwCZkDLKDJkzgaT6GuYX3Tjazj0F/TbH9fJyU1l+1qjp8izGECkxcfOp5DPCpoMjl74gVzXEA/oZoieRlD9zQCz0wgSQbmr5YKOEj9e5wo1wTeyhK+atBWpQv8aIiVrCnEg8dpA0jjqJITW434nuqMsPo8mXwFcyDVP4Xig0Tdi+HsZXs3wLxmnLEemR62Fz/Bkh+MitfceaKZ8mlqaT9Ik8CryU7YLSYYR020KwkHyqZ4i+dBANNb/5GNCZZxCeHVlNExZGZPKb9qwEWeXOZ0pk2VoFd0QI6CWcXMQRe82r1U8e29HRE1JcP+3dHG41nq+Xj7GPMnWQDbvXiEJyRaOkdDqxSWpiz4xg15uAmOlDDWZpALqy2YjVk4Uz6ojsJWsjQdnRQrC1kc5U58nW3Vl7ZoyRXakf1ZywKgAm7InvASdHFOCJTYp0nOE010b7dZcY6fiNaWVDv04kPoMADfOM6qbNIIu7z5+ucB3BmCEfEnWRsOccW1Pt1MQ/YZJ2fFEYoAuZ5ZjjMSy8r+D5H1+6x2idn2y1w+ArlPK3FweOwb4Fd5K3/EAKsB9HBT4dguznDOYXa0YOECBnrO5s2QRZ+hrzCwrWP+PN6kDdt6/y2gRbpDWxuqSl87gBz8A0x9Q2cbxt0HbygvCH95tvQgYYe/leQPrV6wXKKIIkgTvtINLyX/Q9vsgFSdsBP23fMNDoK3OsGJtj/+amMrha6vKR5sotsDNH/HX3J4TbhXN7l7gdp1+zmnwdYZUTpdVOIqak7W4mBLmwB3v+3/kz9v35qv6nl/XukTt8zuL7pG+vVQ9bmaLVC5XkGtjHR71ZGv5VdgX6QSSr0q6bCTMGDCg1UhBwXcqfwnQ+6rl2DUcpgzcBgDQOgLxuf2h8Yg5HN8wyJBaBr11idpDQCABZN50Ky3+Qq86dcvcqcZl1lzu5vWWVYvJhqE2L/573HQk6lrAo80t+K5XeIWu7izqzmzc+P/gGAaroptB0keVIvS9iycawRvhDS2d6eSbp1E1TrRnRRCrsjrHprBBHNO+sNXrfXwZv8xrd+Ln7ip/40f/F8DuSNSeqQJIM0FyqO0XfPCoqz/D28yaq92byzd5yoLgDC5L/VvWS7sDx6vCp8bjCQZauMXS8xaC4WgF2iBGD1oF/p9L/d51BlDA5n8uKNXWuOXga9MPqgl8FH+7V0GUw8Hx/pHcefkkWGn6zknQsiv6f6uqqV9VAf68raVR29yAacjqLjs/rz+1MG0bXjpvJ58ceNViMZKUTdySb3qz8Bo/Q=
*/