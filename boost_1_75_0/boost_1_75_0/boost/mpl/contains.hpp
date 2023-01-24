
#ifndef BOOST_MPL_CONTAINS_HPP_INCLUDED
#define BOOST_MPL_CONTAINS_HPP_INCLUDED

// Copyright Eric Friedman 2002
// Copyright Aleksey Gurtovoy 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/contains_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/contains_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct contains
    : contains_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence,T >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,contains,(Sequence,T))
};

BOOST_MPL_AUX_NA_SPEC(2, contains)

}}

#endif // BOOST_MPL_CONTAINS_HPP_INCLUDED

/* contains.hpp
lDEzzMb9MVOrX5s9zDvubmC0v45SVAIBXoGSCnV5GXUxrxNPYRFlSQve2mZ6Id1bvrS2sdGtqIFDqI+Rrqmu5PnX9vbq5mbCxUX/w4NfVcrP2IfNtdj5Ubuywkx65VS5FpryLh1zdmu2ksSg8PZdsesSPjVPBCd2RwonTy0npw76DmHSWQlx7r9LIhfJABzcMx4KDt8eOLjsFJ5+cPq1stKLlg44xycTCYpE7F/UcXLObGrCb0SWpxjClpRgvHv86n15SllQZlH8KAcwAlQVFwnWjqJrZJExCSzN4qrqlcxXmmk5NoSIsFB47461Ut8+7heLp8iUYEqrPBeI2ZUp8HTB/I2zosPdvuW9vcagRsi3XPmbDvnG2dSPRklktuQsf+a196fW97aJCy3Y9/CvuHfU3RoDXod6H8aDc7Dx+LwXa3LmSkv3S3krSjT18UArBGsL5bLTUrNjX50GiqK+SKSeR9MY5Ok285DtKSkY6/bKHZ6vkX0OWs+OzmvTuLg5FWxep9ywld00RtUh7Ieg7fYfUeQZSG8uLa87+NVDb0aAB/2bdGQWtdkn+IzHF8rNrhVZmRzy95GdiN8rOjsPV07MzRTsQyXIxqW4E7zZG2eEGk1lXZ5PfwyQuBpuP88qWywT/XVBPfx5/xAKvwSK8zFOsmsabQNh8NlG5sTWBw8K8z913+VtX6XNw4a+vjDGfPH1tH8abxLD1pm6
*/