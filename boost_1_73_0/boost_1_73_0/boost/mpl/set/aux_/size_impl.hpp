
#ifndef BOOST_MPL_SET_AUX_SIZE_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_SIZE_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/size_fwd.hpp>
#include <boost/mpl/set/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct size_impl< aux::set_tag >
{
    template< typename Set > struct apply
        : Set::size
    {
    };
};

}}

#endif // BOOST_MPL_SET_AUX_SIZE_IMPL_HPP_INCLUDED

/* size_impl.hpp
/t7ahXIy7K+dT5vhLOPt2R1/u6iX7UW9GiRPvO3RcUz/hJGM0xxUxblQal1l1Bovjt6MwjLsssdC7jqwEx+V3IlDIgrRYoHswDrcio+5PGlabCWjWs83Ny0GUMuqUKDSnNN2RhumcXRnGqcua9qvl6UiL0/txxvh3H9dtpf79jkn0q9FWFaFoB5uOtKnvv/N912HRWJVxYS8AMDMw5043pCmfyGsyoTcpzwsU5kTwDgigMKVIn/qUjoHAWtZcAGUPchDDolUJWjc70BM0f0RBZQSdlQ7kDvQl5MknqS5IEQk9oI+ecl689no68AOhlM/mODYfuBVkWlvxyhlUWs/lTq6GfW/ujN7NMU+JCHfUrA15LKEEJrKYFWlWcQuqIcr93PfyNKVjm+8oYXSkvavk32jpK7vuS4wudztwjw6MtoxjCudluN2rjQ97nQWGB/++AA3VVMPJVV09GIfKkWkno3NfSF4Ivi2y3iyfQ4G58pM4wIgs9NpNue8EEW6rkG3AITrUrP4zF4SKlgJkcMrlcjyFTOfGmwTTpaSy6zLeuhi6/IWUQP+h5fnB/T//mLqxySYAZ1Hi3lzJ2g1tD4TYRpndozLj+FvUEsDBAoAAAAIAC1nSlLf562ezwIAAEkFAAAeAAkAY3VybC1t
*/