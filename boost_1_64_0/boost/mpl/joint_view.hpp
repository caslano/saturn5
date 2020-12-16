
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
usBT6hHBMkNdQ9srR9IqFT8+ipG6vC/OrY3Kj+SsK2rAdKahTg/aBop9FkiVAvmVAvEqSbJYHO8DlieJYTIsHk8TsH4HyJWTvwULltdC7VZqz9umBCfkevq8agcnZcnIVUvvcgGObeYAeedWCB1LHFxnNiXr8d+xj77/8FVTwvsPDxFVceO/fJm4/EXtlL8tifIHqfKx/LfK/m63f+HEktYTERXVg/imbLVcgxMxxFUa/JG8VWx+/LEU/gC5y3btMLRdmNlbM0sH+TP5OXOV8+husaSZ8+d4HPoV+nrlM1wv1Kz60Cmhk0ALhQ5XdOB1U1i7DtsmkCgP9K/b0ECBq07hqhO46qCKivjP5s9mZdLxrcZ8ZucfWgBWUZtNJ6lV4rBg5UeSVWjFqeZO2PkQ1gopY4hL2BvUk0FxvbKyifev1sK7DPGrcDopBLtHuKjZ4ld99/ketE6d17yHyexWlylwQGZdc90LBDgciV1YrPMPoh5eBXl8t/YhUof0S3aBojx9/jFYOxzlTTSfTg27WwvCdmxr6sjdWv1+w72favmprgVnm192gUOhevjfJx0K+dFP00sEWwaOgLLJ8AqcTTr7CsUP2GtIZ88lD0WcZrOXem6hud4G8RuhJrIud1wN6Edb/vJIHC/EvqI2bDJwiTKfzCF43gteFRkLODwrfXOWZNBfV8aCp1k/eRWJWWx7nmncQ6qJfzo9gdHfPBHO8pnIN4/YADdMIG2F92qr8HtUfjdZpLPZSL8ZSDN3k/vquqcwWKmczS3SFbqSDB+shmAK3kowSgE+IzTSnPIZl6lDdXWoro7LjAntZ56IrNoKbmEtbNy1nNWPnBf2p8Zrl4wzafzEOOc6p7Yj51z/qo+2H4/Z0aSPKc3PtEf6fsZKyqXewPVmg3rjhXdEb/CrHfKusl+L6PzvLc6HqGCc68ozrGu3v9LXlR9Iibqu/J3yWeFBzXgqxVUn3OfNPoiviPPhl1fcgz3rGQVNnQq7rbjP+8kGK/1MInn+Jw4yW1AYR4dyMNr9jQVxJIYDOCG9a3LpIF1Zf0//G59ee2CvyBY+lb+onYD6C1MEzomw8KchDmKWuMHpEVcwaZrzgbpTxEUk7pIawnPQJ25tEnj5+gHUzkBaEvIvMp6GFD8lVsNjxIumzutB2bHv63j1+6npBIMlPTr+wUda3pk1tPBbFydmssIgpdGnj1kddx4OgjHDLjR/S6fa2kUec72Vyx5tsLAzL4VXHwI7nMS3jeHqTHdFSMF9QC11vbfrQyJ7SIcBz+7RtFX6zp8+S6zvjKiP7S97PS3/sfxln349NvxEwIfXf2AS9Z+r8MXJX/apyo+xXjWReIt8BbVVeQ8oX4gg6wmvwfqm/CFI+B9iVJG4oXPdS0jcnPyWEDdPuwhp8xblg89wvxJw4wCXJ+Bg+yA8rtJMOicg3076yc96Z5ZvISNtJh8Y1LlLZ0EhmVuvli8sW/v5jwRCg98DAc6qKoHzCkKiTJ4Yubn8FUeJJ9DaRArSWgDKJszb13+0IK0UaAISTSNWUQo57MtYyNodU/WJp8Qr+QPLp1QxSmZjbpcoTeKgdPlGe3N0xHqM1uPTpURtKRvDdg6szzch0SNuzFxAP1S8igl2zn3xpiDvNnbXe5QQs8zLo6q4GBljIAwhSKc+Jz1X6ngZJDxFAk934HlQ4IGy4PdAIucL6we278+vUoeOwFWxSdnCwbJ8wA/+UtlqyNsZqC8C6hMEahhvFn8jjUnXvZ3Np/td12CeNtzI3EOXU/3WBb7Z/HQEhvwB4e99uELnojNy6VsxA5kOL3hIfgiFbJ83C9ULT7V0dWEl0NdSyJBG6SXrLNnbf42g8go=
*/