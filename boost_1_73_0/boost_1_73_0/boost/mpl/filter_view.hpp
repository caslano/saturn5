
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
V2Fb/wCphPMYLrW36cXF+fd01oMNyiiawbtSwsgcOJSod9RCpQ1OoFDCvEBnW6AuOti2MroevOT83RtZvqp11B4sy35DAN83v2AqhIbgH1vIjdji4pAo7HVQcIgVTvYKDQSFMFRQU30uHow1eEr1fCCAXNrtVphykMg4H6/uNsXNOhtH7vXdfcFn518hLaC2z7xpQ79rIR52S+RZfGiE9/D3oR5I80rXCFHrcnQkGC1YobQHumIQsEdom9qKcvARR0RQ59KaEmpKkcWF7DhEVtnWxcJozrTbJzJnqx7lSTjKxVw/AqRgH9HpqhuERBUIH0tj26CEhyekpEZe2TBi+a7HEkHjbLDS1ov+SPsIPgYvYSvrQwb/BJWwBwokXT6TMs1E62o+fry+39zc3SZsKSU29PqMnx0H7Rea56AyuDhP2PVrQ+OUwWw6Tcl40KbtR+o/BXU0mPODa378hf8AUEsDBAoAAAAIAC1nSlI+Ua7NGAEAAEECAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTU2MFVUBQABtkgkYJVSwU7DMAy9+ysiTRxZusImFkWVECckDgiJ07RDlzo0Ik2qxl3Z35O2lAoEQ1yc+PnZ78mJJAyk8oAZSOO0j8crnjrfFCGD
*/