
#ifndef BOOST_MPL_SIZE_HPP_INCLUDED
#define BOOST_MPL_SIZE_HPP_INCLUDED

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

#include <boost/mpl/size_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/size_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/msvc_eti_base.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct size
    : aux::msvc_eti_base<
        typename size_impl< typename sequence_tag<Sequence>::type >
            ::template apply< Sequence >::type
      >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1, size, (Sequence))
};

BOOST_MPL_AUX_NA_SPEC(1, size)

}}

#endif // BOOST_MPL_SIZE_HPP_INCLUDED

/* size.hpp
p5vVTzlryBqyhqwha8gasoasIWvIGrKGf8fwn3z+f1CEOdgU+e/5/r/93XdJ8rt4dxpoSiHyXWjaYjyt7c62RfIBZ3s7ua/h3XcZ9f//uZm+v3+6IZ5miO81xJMl/mfP5LtT0PJZafX7d2bShkabdN/Pl3fkBdt/j7gmaVGmUNv3dCVuW1FlTPnWKekO32L3C4uS75OSrqyrf1hEdLgl4+9Ukya/b9m+RRkUaEvbYn/PXrA/
*/