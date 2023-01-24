
#ifndef BOOST_MPL_ERASE_HPP_INCLUDED
#define BOOST_MPL_ERASE_HPP_INCLUDED

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

#include <boost/mpl/erase_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/erase_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/config/msvc_typename.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(First)
    , typename BOOST_MPL_AUX_NA_PARAM(Last)
    >
struct erase
    : erase_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence,First,Last >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,erase,(Sequence,First,Last))
};

BOOST_MPL_AUX_NA_SPEC(3,erase)

}}

#endif // BOOST_MPL_ERASE_HPP_INCLUDED

/* erase.hpp
PO5l35rX2Xh/osRqWKhX5hYUACaHttAc9pUeOT32bvfmPvvB0GEbQnUsVaBppJNpUNkc/ak3/y9/u3oTKvq9UaD+DdXsf45Zycb2X2JW7t+QKKPf19ODEn0ZVpNNtdDdO8i/q6KP+s7I6qBqF1OPJ4oa/IWws2pqg1HCcIECpziFwocXLw7Fg3txijsUd7fgFArF3d3d3aEUDcWCOwR3CZJA4OjMuTkz52Jn/8DePPPs7puks9ea3g29MPraArEiUaw1iaFjdMtZxKL4iIHMEz1vi7Inp/+XTBDU5Kn8J2aLjH5FfxLfTzIB5XOfp9zMTpBiVD29fguSMPrWJjBH8HAyk9v9cqMz6ImfLAhe+3CJsObioPhgudss2VpxNZ8YrtSKTF71rFeo5lKNmV++VQk1GIgArtUczsazTAPp1VA1UeyDW8WxG3B0cR3UqD/yIWcH1w4QbbOzHTa/QlwD8rTTVCIJx/DDf0bS1dlycQWx6H52/PCym3X42KFuQHsqpvYn13izMcj3dJvjc5Dc/lj7Vv3Jc5GcxfCnsZSubtNhGd2UNN64hkRV9sKg+Ks/K+7aZrd/uSyX35xfc7Rie5Jj8Q/riFo5V+GL7t4N2FuUwjUGpH4tbC3Cv+6pQRHLVXfpwoGUJ/FREGd7snj6omkKhAR0m9lfrRsD8RTC8uEW2r4ZJ9ICQPx+whudV7hzX+1aXHj18vA+HLwy
*/