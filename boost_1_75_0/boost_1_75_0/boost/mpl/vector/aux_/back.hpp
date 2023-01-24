
#ifndef BOOST_MPL_VECTOR_AUX_BACK_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_BACK_HPP_INCLUDED

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

#include <boost/mpl/back_fwd.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/vector/aux_/at.hpp>
#include <boost/mpl/vector/aux_/tag.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

template<>
struct back_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
        : v_at<
              Vector
            , prior<typename Vector::size>::type::value
            >
    {
    };
};

#else

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< long n_ >
struct back_impl< aux::vector_tag<n_> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

}}

#endif // BOOST_MPL_VECTOR_AUX_BACK_HPP_INCLUDED

/* back.hpp
+l54VGm7wxr3HkaoMyn7LRdyq2nRNj8jv2mNyR67JyPavl7N3y+PveyD1ekCe8AmR98B2LX+F0lYXwNiwEx1l0KRhP3sdihcuZOWpF13oQc/N1ApL5BVBtaYR5DgyxiLZK8aszlo4NssHglL8DBgxnONRk4qhSHGSQffILOKR6Kpobnf2iU2dwMWUz3tG4WImu1kDsmSCE2um5oUuchSvLBAwpO/X4dDr8qJrDVxH3Q3crrIs3sO11JGns8/b2VlmITt8/vxwuJfXw+hglbQMebvvQMxa3DjXCFFhcCYmLz5WRTkC8aRM90KSQup+MQQRl6WpTgld1I+9yBWu070hmwK6IGag8o7fwcmD6u7ecmMPtdsHEMZQ8x4zy/KZii/kX/XHzAiI5kUCKiGZ5Xz14sw6ReOy5uI7UhCs9DHXE7ikofgqRE0I6A8RvBndohEvxUs+TtvsPgcpXQx8dIS3w5PfTZzStKSJGYhP3leztNOZWx6yVs0kEwZDXXzudbTxZfyLNmFfnJs2/qSZqVwhHYxkzQQXvUBfjnPRCpK1r8q3LDwwuBKwAvYUbU/u6mrw0YFvRr5ossUUvsRx9BPcXzMVfkvXCRsPUu3H1CFvTatvcicXwYlC2+Gk3+erMYkrAa228oJtWwImnHxd/rMqL5wYwhIrl3FTk6FCk5CQR9opyhoXz1Jg2cUQ1tuZEnf8+ql2HIRHfbc0k1E
*/