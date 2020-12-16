
#ifndef BOOST_MPL_EQUAL_HPP_INCLUDED
#define BOOST_MPL_EQUAL_HPP_INCLUDED

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

#include <boost/mpl/aux_/iter_fold_if_impl.hpp>
#include <boost/mpl/aux_/iter_apply.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/always.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/bind.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/msvc_eti_base.hpp>

#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

namespace aux {

template<
      typename Predicate
    , typename LastIterator1
    , typename LastIterator2
    >
struct equal_pred
{
    template<
          typename Iterator2
        , typename Iterator1
        >
    struct apply
    {
        typedef typename and_< 
              not_< is_same<Iterator1,LastIterator1> >
            , not_< is_same<Iterator2,LastIterator2> >
            , aux::iter_apply2<Predicate,Iterator1,Iterator2>
            >::type type;
    };
};

template<
      typename Sequence1
    , typename Sequence2
    , typename Predicate
    >
struct equal_impl
{
    typedef typename begin<Sequence1>::type first1_;
    typedef typename begin<Sequence2>::type first2_;
    typedef typename end<Sequence1>::type last1_;
    typedef typename end<Sequence2>::type last2_;

    typedef aux::iter_fold_if_impl<
          first1_
        , first2_
        , next<>
        , protect< aux::equal_pred<Predicate,last1_,last2_> >
        , void_
        , always<false_>
        > fold_;

    typedef typename fold_::iterator iter1_;
    typedef typename fold_::state iter2_;
    typedef and_<
          is_same<iter1_,last1_>
        , is_same<iter2_,last2_>
        > result_;

    typedef typename result_::type type;
};


} // namespace aux


template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence1)
    , typename BOOST_MPL_AUX_NA_PARAM(Sequence2)
    , typename Predicate = is_same<_,_>
    >
struct equal
    : aux::msvc_eti_base< 
          typename aux::equal_impl<Sequence1,Sequence2,Predicate>::type
        >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,equal,(Sequence1,Sequence2))
};

BOOST_MPL_AUX_NA_SPEC(2, equal)

}}

#endif // BOOST_MPL_EQUAL_HPP_INCLUDED

/* equal.hpp
6WUcQH4XHtJux+iDaXvEXvNxK8+INT65q9AaPrSnXVxfldU+LZzVdRGFMq/C4MNFh/g4rUtaeJqxSA3JRBWJELJSJi2KdGfpo9DygW2mSXlotatk/3JWx3/x/iX37yDYf7Zz9q/uXhO7tdwBdEUz9o7RM8GKrS4GZO7I8uDKNhpPMKfcNizffP4BNDObRr6clkuR8goz1TcKw5B7H3IKLD5peNHHsm0vUy50NbOJmdge4lRCUppH2eZlzrcM8yxiKtPERHFjSE/b9DHynIlQ0tPa8GmGbQxktnsZNPJ6b7XnT/yQQhMrOcfT1jwoOYUBhgECjY0JtvXkmSSswI0wzCZB1kWTeVetlBM5nMXJ7n7frXCrV1CXH7pyVh/DRmGaoKDztytnj4f61mK/XJ9Ne+I0FmsNsrQQe4EHqOng0NVPVllEpe6TggM/AulRGoTZhf5G/EKBj9VrblsP0bd+xCtUfOKy9dwSKzcINmGAYYCRG3Q5jp68UzKMweA7LcDghAqC8MERM7KTg8t/QAdHlMEBKFS1OCj3+Fr8t71iWxzZrD+ubO6VbII/ydlX8UpRv0IDzcGoOBr6qxKpobdYJa+8m7+rG2kTKqd3brTwr7qHyexHfvN60ijra20rs2JjGGYWYoD3xIuQYvZHBLm0tTLr9EY2FClDjLsRI830UAx9BW68GIPMPzarGDe+2i5eKcPMF5utUtrHy+MC8wE7jw4qj5VoZVW/RCvj9ch4g7TAPDvjjlbG65HxBmmBiXbGSTF5oAnS7Dw6xeSBJvj0fSuPQEweaIL971t5dI7JA02w1c6jS0weaIL77DyCnEehwaYusKRiCiEdUw9QiB7EnZl2loMT74+0J9uZcM5+ssVxkNRLnaC1BPlucprMzsEysr6oAP67Ka+ehQYK4uxE3PJ/A8w6MgwmBWI63SVRmxH0ZDMdlpQC6Wzp8/Y6ROZjjqPZppvvgCDXxajjZkZFZy7m2ubPvK7jq4nEsmS6u9H7L57u/v+c5GPth938jyZ7PSSX0pijiKSFFuEBfC4Zj+85yooa9qjQf1B+MfIlBBByvs8HFs4Irji/Hc+w+4PPVG6awUcEqyvpp7zETCgeGppGRYQWEx82N7+nsTDLvMrL4T5CiM8gTJwLUzQTiQaGLpNE+taLZ2Sfc8yhJrXPud13ZHkiVpSNna03ORNsdkSDNBqIntRFhr6UCmYci2Zjet8butqq3p5DqnoQqcyDCVDj0GEJrlz23vJFc7lm11g1e9JRs6ubdM0OJurTcXWJyn+QfSbvNfHWi0N8hKSK+KxEDOBk3veRXktnybTET9JTE8BAEtb36vpvEqNocd8Vi3s9/VhhKZ3IcHO3lrpR7u4wLWgdwl9V9m6WoO27ySnpNMOn5imBpxu+2gP+Tq+qa8WBRZaXNrmNTjv1HeZ2YEqnneGcXUpORwm7eGlorxQRElumP6pMf5wy/fHK9Ksyd1IRUn82m91Jq4a0rT5pJB2wSNp7sjemY0Z6laLhLH1M1ea0ZvYatawxcUZ1s+44eAdGRkF4iOqoGTbneIC+IS81uUBDan682nHg8yWno5+nPMopTr3q/U40NXDv19b5VVMFSKrknuVurVMzTvHlJDLJCef5MMSrK28gf3d1hZxcbDzvlDJp5oERcV3tQb8ugsUh1ZyBlf9k71oAoyyO8N3lAieczQERTgkaIWgU0KiIQEACEgtI6iUSRYyKSO154qOQACIBYsRyxFStUGnBFitY2qLSFm202IIvqEUF37VYAan946GmSm20kXTmm93/cY/keNnntcT//3d3dnZ3dnZ2dma2ZOei8Zl70cqdUUwbvVGzk1CVUTeh+2yQkfo=
*/