
#ifndef BOOST_MPL_LIST_AUX_FRONT_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_FRONT_HPP_INCLUDED

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

#include <boost/mpl/front_fwd.hpp>
#include <boost/mpl/list/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct front_impl< aux::list_tag >
{
    template< typename List > struct apply
    {
        typedef typename List::item type;
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_FRONT_HPP_INCLUDED

/* front.hpp
6B3rImug7RVU5rAGl2M3QMiVhQ9EDQObGzdg4aHDEgUpOpOYcsradjobp+visYWxTsJ/Zj32hwLhDxvSpqns61IM3+fr6Gn55h3nKuFaXHvMI48XhVCcZcXl4v8FUEsDBAoAAAAIAC1nSlI2QjxNcAEAAG8CAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0NzExVVQFAAG2SCRgVVJfT4MwEH+/hO9wcfFRcSZmZqlEMzEuPgxXnNEX08EhZEAXWqd8e49CmD61vf7+Xa/CkrGJMhTAZMtLijrLsCvi7GKGKrPU4PbrExva68biZHo5vQZR1JkOQOyo/dZNagJ4iCOI7uQG1mG8BrlaPMkrUGX5sW/0TwvCP0KF37MnMEFJzYGaM1OkBIItypbvU2VVAKYoyxYTXVuqLZP6qjCOkVRpJ/TvMNCd7qIsmDXoJu4wcgPI7B6MTnbmatRwt+x0CI6pb3rM3PdPH1cyXkbzU9dYtFrHjtjjUdSqIvcEmJFNcvwubI6jDDIQrcbBEYXf41EkuqpUnbpAf11YqfPwZ9Mp+4wo3g6duB431BRZi927DHOyOfWjy5XBLVGNJybX9gTEwWFZghNZnegygBcZrlHVum4r/WW8bnoSOcgt/ahqX9I5+3L1
*/