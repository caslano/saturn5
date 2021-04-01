
#ifndef BOOST_MPL_SIZEOF_HPP_INCLUDED
#define BOOST_MPL_SIZEOF_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/size_t.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct sizeof_
    : mpl::size_t< sizeof(T) >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,sizeof_,(T))
};

BOOST_MPL_AUX_NA_SPEC_NO_ETI(1, sizeof_)

}}

#endif // BOOST_MPL_SIZEOF_HPP_INCLUDED

/* sizeof.hpp
BNhVH6+eaa/W9EVwICse6CPm/flBfsrvz/A5Hm08U6L+Fid0QCfRbblViue9mIo4BhURy9Rm1PFpfX97thI7VMe4AyO0fum6FMkP6BkK+MDc+PdjemaGhwAP3gcYvuN+dn50PsVj6i26Fiv0HhYp3Lod5/m8phthgDleUWxfcyOiMSfwRGoD0jdKcY+g7H+ywDHAnErAvW1+qRWENDb0OPlwaRoh5MhNGmzPpHOm0YqvdP64UoSYNltNu8qEnBXbdsVK31khL7pnybG+cl0I8AHsaT0xz4U/AUAU7r6sb1/km++f3frbIaweNyUW58+KLs99dpknt30jo8sI+ywwFn/cdK7OLW1NJ+IhgnOG1zWIU9eC4PWGmW4yM4OkMerpeelwUyP6BMevk866fsaTtHwBR50DSmlQxoZ0AxreIqXWuMs5ko+M/uDvmpCtkURyHc9iOdP9E7w/Ur9pWxuIF3Wh98AWnlNVQPa1Rvtx3WAnUc3pAMB6xYxUPkuLpdUQrU8Y9qJOGmLyTfd/1RrMBYvnR3Nq0irftvJinSpqTxIoSo85ISBra9tDnA==
*/