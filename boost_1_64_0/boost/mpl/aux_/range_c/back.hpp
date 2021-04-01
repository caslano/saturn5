
#ifndef BOOST_MPL_AUX_RANGE_C_BACK_HPP_INCLUDED
#define BOOST_MPL_AUX_RANGE_C_BACK_HPP_INCLUDED

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
#include <boost/mpl/prior.hpp>
#include <boost/mpl/aux_/range_c/tag.hpp>

namespace boost { namespace mpl {

template<>
struct back_impl< aux::half_open_range_tag >
{
    template< typename Range > struct apply
    {
        typedef typename prior< typename Range::finish >::type type;
    };
};

}}

#endif // BOOST_MPL_AUX_RANGE_C_BACK_HPP_INCLUDED

/* back.hpp
uahfGLYbm8Wp00gVdRUn+0e1W4wjDaQpp4tQaavzoLkF/qE7owcCWna32IMV9SHKQD+FDEafAnbGsi9TAUmbJSZOBsDL5JQ14waz8Qhhalalo+HaPqV8o4Ju+ChliYLIvVjZAWQa2cMyvLSLoEY/pSe3KGMlf3yCTrk5WcQMoeLZCDfjNAT49JxIol9U0IaUTCPVwtwsUNXKWC5VHpfb3wfyoZppbFJnZg6gE4EPpjPxqKjH2yFCnSXX3yEUyOKGWqcgjaZc2M8rKkSpgCk/mnst5QQD/XDMuEW41dAoOijpM6eUref4uGA74m9F0wQ1FaXXROaXXHrqhTthwy1U9IJdZXD9rHusxDPwjEGcWUj/jlGesl/Uzhy4M31hejVMrVsJO0V1+2mO3uX9H8OLrvJ5TyXiar4zQu57DowVDu26ypjLJ0qstjHNve2WIUvDJGDL7akgT8bxrAyI11AoezdsywnQMv32ANa0IMMU7+AQJfwCtjQy6rvkXTp23SPBY9MwTM4VIKPyK2VB2yR7BLWzv8gkjWffccARxnMTMEneI/8fKdyLbv0nNA==
*/