
#ifndef BOOST_MPL_AUX_ERASE_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_ERASE_IMPL_HPP_INCLUDED

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

#include <boost/mpl/clear.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/reverse_fold.hpp>
#include <boost/mpl/iterator_range.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/aux_/na.hpp>

namespace boost { namespace mpl {

// default implementation; conrete sequences might override it by 
// specializing either the 'erase_impl' or the primary 'erase' template

template< typename Tag >
struct erase_impl
{
    template<
          typename Sequence
        , typename First
        , typename Last
        >
    struct apply
    {
        typedef typename if_na< Last,typename next<First>::type >::type last_;
        
        // 1st half: [begin, first)
        typedef iterator_range<
              typename begin<Sequence>::type
            , First
            > first_half_;

        // 2nd half: [last, end) ... that is, [last + 1, end)
        typedef iterator_range<
              last_
            , typename end<Sequence>::type
            > second_half_;

        typedef typename reverse_fold<
              second_half_
            , typename clear<Sequence>::type
            , push_front<_,_>
            >::type half_sequence_;

        typedef typename reverse_fold<
              first_half_
            , half_sequence_
            , push_front<_,_>
            >::type type;
    };
};

}}

#endif // BOOST_MPL_AUX_ERASE_IMPL_HPP_INCLUDED

/* erase_impl.hpp
H+QMDFTceacs6C3MxOPxAU0znfedRQsTNGDDqp0O2WP1TRax94JSA8iqrxBddQhAtbVxX3SG66uFKqnoB3v1GAlnZvZTAW3d8zV3s3aJFQcU2WAh6EJPo7/3t5p7wJO3TLldFXNB+qMFmg6keTPaBeJOtoXDb7Usz+fjL9C9/w6wrR45FQn0DXowiLskzvlcm8/GryWE9WyEDOPSpwMb3430GE+zYgwditODKFUNCB7g6EFsKSQEJwNHFbftGTVH5B1jQCJDJmoHnK86I1GTj2H6Sr5dXvK2HIAfZ22XSH5BLm5NYDAv8pDWglf/m5cBXsJrAnN2P0aT4UV+jZPYyL15jxM31gIV3uvWKLJf+6M8iSaLUh+Pj2eXfce/bQRsoXXPPm2xqzGBAOk9+gdwn0SBH2u6Kq20NO1Z6MOXLn0LQD0wnuIuTFMJq0c1akKGDjKSkxWNGI3V/yUC94pBay7BtIWU0To1/2CL7HR2wl44J0qfnJenW08neOp4kv6pLxAjJ1eAaJ70QoXLE4h0Ql41L26h+7Y4ZrZa5nRpb+EHLxIJKKMDZM3emw==
*/