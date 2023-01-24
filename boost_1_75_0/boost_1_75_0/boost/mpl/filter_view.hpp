
#ifndef BOOST_MPL_FILTER_VIEW_HPP_INCLUDED
#define BOOST_MPL_FILTER_VIEW_HPP_INCLUDED

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

#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/aux_/filter_iter.hpp>
#include <boost/mpl/aux_/na_spec.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(Predicate)
    >
struct filter_view
{
 private:    
    typedef typename lambda<Predicate>::type pred_;
    typedef typename begin<Sequence>::type first_;
    typedef typename end<Sequence>::type last_;

 public:
    struct tag;
    typedef filter_view type;
    typedef typename aux::next_filter_iter< first_,last_,pred_ >::type begin;
    typedef aux::filter_iter< last_,last_,pred_ > end;
};

BOOST_MPL_AUX_NA_SPEC(2, filter_view)

}}

#endif // BOOST_MPL_FILTER_VIEW_HPP_INCLUDED

/* filter_view.hpp
XSMX+yy3qRxeAoucdloEG7UYbQGWCDSIJ3rFxa7IY2fpW+qK2TzyD+yKhgjLBCZEBojftLGAagXXIe5mSI/CuhUbmH+b0PqK7VjmZ8txXv6GV53Fcwbi8V1lVq9LXIpHUt7taMmMzbHIzwZXROGOsGi0IhdwLCAiowoGkpZ8Iy3FagX693jUSY7IUZyziyo8P4Kaeffgq8m7MGSabpx+JW4oZQCBZiyiSuBfkZTZ78yU35YDHSOXOhjrc++Pu4TrGaH51FV9NGPe4GBWY4kLjOrspNPrCFDt/ty5zimJlxJx3fCtpZu3rC2zqFYGl5pJh3ZGyIgBaq/c23KMuUWvZeu92OP7zF8xlwz1dltatJflpuwZIBVRTr3IxHQNkjE535alXfC0MciIxdTk+7P/t5OVSvKRYVoWpWqTpZdweZlbyIfucbYzBe4rnAqKzydlvd3R+YSwkgOdIyN4gC/ZI61vhNOc1uP2KZS3q0gnYeyDaYChL0/eVjLHpMuWjnj9nD0UfTs0N8FuDwi9GuPVut9gzv+9Cden8OI+SwV7gll/FA8s9P/VaIR2nnK6LwOn6VUy+RXWI+k8R2hUTAa1nJEq8aLs+8xeeIGt94QmAgAKtb/TxF4tkd/bRNWcEjtGH43o5GsJSnjibjFMb80/YD9836nGjgUQAwa6mX4WABqDHy0E+OvcFcyULxLXQ28m/rbTLnnAfOVPTcd8
*/