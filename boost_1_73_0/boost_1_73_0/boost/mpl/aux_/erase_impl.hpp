
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
zYXdPr267Z9dx9tUwtdXN31OiiUcj8+jL2N5mTnpTMrzufQJX+SFfte7CU4F5zXssVIike3bmw8nZze8UAMqFa4NDhNlnW2UhS9OX6j0YzE8HlcxYq+BYgXP+9p3/BcSaAZ+aIrcyQowdXXZooxYxljLmBrjAlZXAY1YTKUzqcFr4piGmsFixG6xUwwWwxN1ttjPOBTC90MMjlMSVeLbXz7e3J5d/bTF3qepLNH8hr/ZYlvEeBnCl2f01/X5T+eeh6P27eNFN2c50CwUqYQRIoCy4AyqoDPqa4XbLX4ImRoqB6WpHOjJeICCKY1gpNqcBM5CV6nSy99jll8IbIFLbN5cySxuvOEcjU8ekeOv7c63J+aZLC2ncbqG6AVprgmyHE+oxnMAC3lD/3jYGAYzTPAWQ6H/Dw9jnfKFcAdrwlmXYZ/MlavdDuZurU03WVXeDcYmQyvRDlaPWgwlkqKHa+dvX5rd5YPB8RFsNBr/EgWTtTqYS2xvf/Jxg+zWfbDz3Zm1u0njv6JtcrvHbxwvz+NtBv6uK3zFFyLEJ+Ib4dfZavXWmg0XP/wOXXj9GlQOOzu4ePEH8N9W+HwXXr2CxQbm1FRcbdimotJo2l1vOQrCl7OPr/6R/RNQSwMECgAAAAgALWdKUtEM9KDq
*/