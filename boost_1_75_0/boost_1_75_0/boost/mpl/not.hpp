
#ifndef BOOST_MPL_NOT_HPP_INCLUDED
#define BOOST_MPL_NOT_HPP_INCLUDED

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

#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/nttp_decl.hpp>
#include <boost/mpl/aux_/nested_type_wknd.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

namespace aux {

template< BOOST_MPL_AUX_NTTP_DECL(long, C_) > // 'long' is intentional here
struct not_impl
    : bool_<!C_>
{
};

} // namespace aux


template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct not_
    : aux::not_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T)::value
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,not_,(T))
};

BOOST_MPL_AUX_NA_SPEC(1,not_)

}}

#endif // BOOST_MPL_NOT_HPP_INCLUDED

/* not.hpp
IXrvMtV5e4EI316MXX+HRF3+l07EizTRreE1f5wndYq2i2FfhlXgtXwu2bi0lH+3UZpXqXE9fV9evarq6uSaJw1HObzwiwkY5AaIvMXPpIcJGcIKVyR61+MqY+tuU5/hfS9ZpYZtNFduqe2Tt2NYT52T4ERoscoVS/Zzhq8di+gfq0RRYBTMajTt6e6BbpJPyIUDsjr+pI+hog6igzbr3ib0/eGASjR1lVCIMPtZc28fC+eE7zDx4BKjbH1VNzEs7PxbqLxRyUsyFpMcF4FI83uyRJ6LopCSBfNxqd/Up2B+v+g/riebOf5X82AyiCQeTFWtdFtBVp3IWqGwdV7rWuBw6oZ9bZRtbVVj12V9OtU4R8/O+ofY0Iu6DiYbsYWKmTdNdHOw1ZhMTt/Yr7e2GwjZBaZQzKHsAgvf7bPuanwlwwsykcnYQhID8NsEIEpkTLmZ+wJpNdoe8R9eS4FrfhnygKI/skOR20pfpVtOOYAc6/Am406bABhSqf/gJOO5ZQe78IXZfR1ldPremrC2buTMmILhyHP3sU0nIceogk3lh6Ug4vpq6bYC/JWPzNoKh0lk6YCLTiwOrzp03EbNykFjne/HiX0VlAxp26QZFDqYlZ7WBQedXN/vQTtsDswV2pnlX3TO6jqJZXPtCm+8SfNvsIdW7XZZffJiG2W17jUkIpm9cSPcf23MWGMwkBn9hZOVsErFS9NKyWRV
*/