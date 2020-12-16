
#ifndef BOOST_MPL_VECTOR_AUX_O1_SIZE_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_O1_SIZE_HPP_INCLUDED

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

#include <boost/mpl/O1_size_fwd.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/long.hpp>
#include <boost/mpl/vector/aux_/tag.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

template<>
struct O1_size_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
        : Vector::size
    {
    };
};

#else

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< long N >
struct O1_size_impl< aux::vector_tag<N> >
{
    template< typename Vector > struct apply
        : mpl::long_<N>
    {
    };
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

}}

#endif // BOOST_MPL_VECTOR_AUX_O1_SIZE_HPP_INCLUDED

/* O1_size.hpp
v51YT04G4oxu7p+M/hsLf/C2TukN7OQ++L+AB+AfCvl+JfHUTybicOw2vFHAUPX/roc56zxVk0/8yGTG7XX1GfqN+t5hOn7davxk1qvNGp263wa9kqMb8KuPquv2/cBZrk3wgK9zthx+U/o89ffAq5C/QfhLltjzkdiPYPWZtAjecTxnkvaHzzrC2Yv4O3U2+MnFBiVvH3KGNevVZQpn731M3Jil2hGax9+x/0W1rOPR6Otp2Iff1PWVnPFeNhM79ArxS4HG9xpUP+ARGmYRXwVyhuBtJtW+7UZ1v0c44+8w+vIE/sQOdd+OPB3+E/47cbmbh/q+5jv4DRfsxVR+P5P1nKKusyXO2cr86W+GH5tOnKLFfaf0ql/qDGcBZ9PfZVDt9cav78I/fwd7Uo4eKmE+H1KfNfdzhuULnKnoDC/2FNc/TvsTib+mmNX6zeM+x9RnYwv+1eec/V6IHo/Gb/2QM7C7eQ7rz3se8dTVZvxa4m38nYJnWX826nuvaM5YtEIvf4AdJZ4uMXC/Ws5ePMrZrXrVDjd75Phj9FS4Gj8j7anG3zTu52xpE3qU/q2LRF6x85HYefO/OEv2QdW+/dgXv3vQb87od65L0+FnL6V/y9Hj2/FLxsK/WbFeC9X1Javg7X9APp2R45Hox+sZD0v8bXif/Hq+N2ln9MP7/Mm8LlP3r3mfccEPj67A3yaOOfKW+vRCr22dpX7nNQF5+Cf+VKT6nV8+dvMkZ7USZ5wkzghEPo9cp8bJzYyfQ5xsl2hQ4zyFMzJ98H/xDw/5WrBOTOgX8jbzue/78Bnvqeu3NsD7wQ84/IS//we/h0c/aYl/MQr7A+9uhv8KJx4qO46+7ULePiXPEjdI3Xex+r/RiTPEv8AvpX3G5fCnL+AfbuEszo34YRnc3w/5c8PufoqfYsO624VeGIw/4Q5vba/uG9zBWd8zOaMa/9whC78xF721jXU/Dbkhbm7Jwx+Hr6iezboqRC6Ow18xv/scGb9P1O8S9sJrBrEu7jar/o5j/U3Brjw/CF6BeYNvKr4Ff2GfWfXPE57wD85Kn8P62wlPW4/e9OB5H+C/jiRevka1x3wd8efH2JFf4bdZLzXXa/w0vPBP+Mk70asl6Ivp6At4ZJds9HAnceAW4tJW8mDunAXsq1NyFIK/Cg/WecSkxhcePTqL+MgLvQ0fZFOjhx9X90tivgNeR/5Xwo98y/rcynjAA+1fShxOe33cNP0Gn70ff3Md84BfHAqvX+DO82IsiQ/wh1Zhj5epTwfygsc6sGvkB8vajOr3LtirHfhryFk+PF9nBTxfHv0K4ndd8D5z4cGuZ9wPsl7vwT/yMKr2Yg+KXfAjsUs5dupzH352zj74TnfsUgj84M3EU/fjxx9nPTG/PoPgCx9S9+sOZn5vxZ59T3z0NnmxPejHJHW/fMZ92WfoE/rjcgd/L8bfdiW/Nhue6U/8I+bLIwN/fBifYzhTeix52r3IMeuk+hnswmjmu5m8Mfm+dR3I5Tb44k/N6nltJnX9vfg3T2HHnkff1mH3RhEH+sM778JvQs9UrkdvLGR+iY9sb8ZO/siZ7FM4O/uEek4wfJjH8yY13jUav884NcN/ZGv8wCDWF3ZG4z8f4KzvTnX9IfROVZ36DPBS93e7Gt5oE8+5mjzsa/i1r+Nn/qA+bfbxyfyX3M64HyIOfo64tpY4LUQ9f18Q+uA11b6uEgP5ZuRzLvI0mfFtIX49hp4/Tb7nqoHqvk/CW2yA34U3SfNj3qfhX9mbVPunILesy7Rk6h3mYdfGIb93wIehD0oskH8j/rsz/EAoec5V3LeFeO1lk+rv0/ghFejjqdjjeO47Qn0mueM/jiI=
*/