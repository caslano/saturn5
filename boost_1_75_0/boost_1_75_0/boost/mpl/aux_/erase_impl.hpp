
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
SDunGkXdJdyW9+0air7otd84bB4l9b8Z5MVb58sgXoZtSvAFSQbb2HHVlJqY9bFHT/X2Xt6E8B8JShrYbuMUU5dejU8Ijla6eMi8AWVZ9+qeyvb2yaba2b/Su55Qy4/5NI2Eq/PBEygbXqyIZffJMhb2nU29c+9vV98ofv2S/YpbHdPDJbBu2fidRgrfCHM2c4W7j/e9cLY/65nKTMbeNqJRycfIFlcl4Ibyo4qz6UI8yiFHoH3ck9VRWQYZB9AzLKxCIjRWpAzKjw+cQRl1OUn7g6PRt1tl6r9s3qFpxHoHijrE6rCEjAzC1eohnWT8MMgAAT/aVzf3SfChdpiUVDM1pMuPKCypQtGjaiyz6bxL+8Xtdc4TLzuxqJB8FuPE4n/VbVwoHOT2Y9Pg02hjsY0Rov2gc7J2Qa6fPXWLL4QBPkNQggfRnsN3in9CmSk91mb+eG28rYIABSnVBt/ckp+oar78I/72H9hFFZvYl0HXl+KFW/q/Mp77C4PCPrnmBVUdFPGd/PHfW+596H6ptEqyefzVdtK3fniyWhtT1E9i0ceQXGFTivRdewBDhQekDLtiWhKcR3a8nOHeGGGW0xJkKHf1eyWINiy85uQEWytAQk3NLKGwcReKj+Y1Sb74tmj4m/tAQRM0bm06HirvC4I1H7LmmCwqwQnVdLUmyvKUx7wF7d/eUA3H0SrMpVpNxznflqTXhxzHmBRz
*/