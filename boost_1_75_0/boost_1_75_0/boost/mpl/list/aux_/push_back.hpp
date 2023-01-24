
#ifndef BOOST_MPL_LIST_AUX_PUSH_BACK_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_PUSH_BACK_HPP_INCLUDED

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

#include <boost/mpl/push_back_fwd.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/list/aux_/tag.hpp>

namespace boost { namespace mpl {

template< typename Tag > struct has_push_back_impl;

template<>
struct has_push_back_impl< aux::list_tag >
{
    template< typename Seq > struct apply
        : false_
    {
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_PUSH_BACK_HPP_INCLUDED

/* push_back.hpp
W/abt0lF84WZ2BIyOw6LRfCfuLigeRYlmg1gydwf7ssK6MCJb2eOX+xQE9MQLVbVio574HitBS2IK3wdZIb7I8zGuh27I5rthvbKvHPcVAdnlx3F5LAG50ydXMSYuTlwW+h2AXG8lk6iHPdULB5stPKIrPzQufYeSwdYgmXAgkLxS1H6HbLD7Wap/8z4RoSCgItTFmhtjkve9bHxr6CUx0SR+fMPkqlihdw0cjWLT3bD5+hp2TKxDzTqRaULhGF4bHbqZyqZ0kbeMkzi3g71gutLG6tk51jPmVnP0IsaRejFxks3dGcpF+Dg42Pj07d2uLE2ULxAPrLszvbrMF8N+K1CPEM0C+hryMRnQ3UsZ1LaajoN3VEBywZUjB3abZamtn6dGGdB9bnfVngWOJNm42C3mQkQYP8jDkMOpQxnEmy2YXoaz3ncvxUr9HrB9vLIVadMh5WFCHgtcaEFyP4t7r77W9zNtO4WBVpzYktpwPTm957wXOVbLv7zo/ywsd5Ussblq5Z5bbJTeRADUdR1ylxNnUYJAUMsRkZriVYz98DqfVMrdL0B1EK6mXGw/dTa7FgwPbid9c3SPAzAbOvOyjH99TH9Fx1Bsw5g0nDsEDmtMUPPp71Fq/VedrRJ7wXf9mJvSXG9Q7b1fixi0v7CoL4lDeQtXHfnz4trJcXQrsFubdgX7anrv9S5Vcdx0EpMN5x528aatM4oRG9E
*/