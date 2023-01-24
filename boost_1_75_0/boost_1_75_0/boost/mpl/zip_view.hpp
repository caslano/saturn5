
#ifndef BOOST_MPL_ZIP_VIEW_HPP_INCLUDED
#define BOOST_MPL_ZIP_VIEW_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2010
// Copyright David Abrahams 2000-2002
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/transform.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/aux_/na_spec.hpp>

namespace boost { namespace mpl {

template< typename IteratorSeq >
struct zip_iterator
{
    typedef forward_iterator_tag category;
    typedef typename transform1<
          IteratorSeq
        , deref<_1>
        >::type type;

    typedef zip_iterator<
          typename transform1<
                IteratorSeq
              , mpl::next<_1>
            >::type
        > next;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequences)
    >
struct zip_view
{
 private:
    typedef typename transform1< Sequences, mpl::begin<_1> >::type first_ones_;
    typedef typename transform1< Sequences, mpl::end<_1> >::type last_ones_;
    
 public:
    typedef nested_begin_end_tag tag;
    typedef zip_view type;
    typedef zip_iterator<first_ones_> begin;
    typedef zip_iterator<last_ones_> end;
};

BOOST_MPL_AUX_NA_SPEC(1, zip_view)

}}

#endif // BOOST_MPL_ZIP_VIEW_HPP_INCLUDED

/* zip_view.hpp
UAg0iXjjn+wgFckwk0sSr+oDQNlyndFjqhkZaHYSlkSwCaAZzQV+qzZP9QYiRVY0RzZ7YimzdHFfEmeHu9WT38+mKxd2xBy+ihkWau0eNFXOF3TF2ATigfGAwYgw6hksREr7RiSP2jODXjraw2+GzPcCgK7S7r9ocBBkVyqgMjaTzFSYMgvs5VYWNI6X8K8xpbuXrSWvnefKqwhe3ObZ84dq6In4zYh+8mbK4SiHew5LDhd/HCkT+2CQQ0CZrKiRt9nwQz1RoO/LUdx70VAN8SLTrwwTwlXhPp69aSe6B6GtWqG87e9WLznQ6uV3PWjqSDJ0YnTCuHuySkUXN60MQ1+u8J+Put+QzDYR2B/pJQhPNaTwaJrz1v6q0Y30m4pj9f5LAAafdfMHRg0luoDMoBoSyN5joktT53R4jTd+dzsmiwupXA8m9S+Z+k9TdxzxZ8FpGpPon5v5zQXZhrTKdzzXwl/qSVcbiPg3aQy/sbhiOw3ktJNkXaqd9n5eiMPThbuvgnix8/o4cHdmU1hsu9MUQVLjfkI5RyLe4XYpfOQ2pWNT04v6nX1i/JM+4RNPnP4UCRXBqakVb2+aIug/G8g0YHdevc0dIkrxiUv4YayyaTvq9+ti6eOZfKfkY8ZP/5Hx3Py3662ryvHOpOxlT2mEF4Q/8qvzh//UHE3tCNvtjhL1DukdRDodTuYxQYZGquRbKPH2O88lqpjI
*/