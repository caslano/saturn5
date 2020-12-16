
#ifndef BOOST_MPL_EMPTY_HPP_INCLUDED
#define BOOST_MPL_EMPTY_HPP_INCLUDED

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

#include <boost/mpl/empty_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/empty_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct empty
    : empty_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,empty,(Sequence))
};

BOOST_MPL_AUX_NA_SPEC(1, empty)

}}

#endif // BOOST_MPL_EMPTY_HPP_INCLUDED

/* empty.hpp
kSe3yZRBeeZ06P8ZlfDEgLr0m65tXoJIhRN0BXrpCkSuRg9Tsw5nAiG7iw6hFo4j8xI5VvcMgFm/tvFIon8/LYKFP6Ys5diig+g5uzqo3CAqP17P8f+eB+PF5iqoeTJhj4FyhPG1YLCwGz26+twGajzC/UdEyRhAfrmhorhv6HnNaQpvKfwq9UxZHnpGGVRS1hh+RI0BFg/Mv56lRhAlrbWSnoWkF1tJr/BoGqIdDW9xDyE0uk+i0AfErxrittnGzupj6cItUjR/M2veg6hBX62DiH7tVYbwX8QDfrki164gzdsxs3cCgR6m2SsyNfSWxhJkASIdf3UskVJ9fmfVZwLqc1uurg8Mw+1RE6DKWHzyNEJSMsMYSA5fkoyBQiR9HoWAht/ojaqhQAMFktGcgVr/UFgSG1SqkZpK9q26SxVXTm19g5rrpM6snMrH9n8xC/MX33UyVnXCYBrJ2ugpaqIa3Lrbvk8cZ3s6yqj10n7EUf0tEz2UnyMUMhK9hOabOyl2QoH8eZ70ZIq57WodI8YeW20CsdtUVYvzVC1owuyvJqIvz9fmvl1jplA1KWWrOZwI8EIOuiNAjaBIvb+VvG/hmfHZ718ngv1qhvesRSwYcVdcpIYF6ps+5Bhtwvk56v72OzPV/to3v2LvrwVwd0Jz1+CKJ2AyR6dFll3wIRsMVqTRD28ylTXRF20quKxZAchpiGwM41Kx/V45twHdlw5c71XJ6uiFscBVY3u9kgdy36cA6Z5Byp52CZtEB5ewrd7p+qCuEV5GhaiIrTBHpbOF53D0xRzdQPS/IGPI9nfXWdF3W3bVGZUcWizGvMMsizhO+gRFEt6cLE7lNlBM4rR/w6CXjFbEz+ivV6uMtM2VId6WOAfKi06s7XvHziWSRaNG72P6Q/Y+ZkvZNp4Q8y2ndCzm5km4h3G5ow/IJ5JYvhMbudevKfl7F+PXH3Qx3qPfe+m3F/2dQV2X0E4ej1d+E327PhePbf81Q9FjhxtswypmlTxp6eFaaAl7H0i/yuRniHK4ti4xF87S5g/AuJcmo4gS6+AYd6xb+in/O6HR5yQYocfoH5XC9vzXjts51+w6wXnKvZ49KrxSXAr8UnB1HsZBkdyvxlQezhGBcRKTKsg9F1eZMMXCiNLuTvMnw+XC4BYPyO5O59jy6EHSpAAiJjJUfa4J5Q0+htznSu6RNMTlGODPgBhT0qpEQIoYfrrMf9tsY50nySHRGWa+irk0WSb5aAA0eLGf6L6BpWZ0QpMdNkT7TF/+gFcZ+Pfg7txOEI00tM8+9FNL5AoM7i0MwQFHu72I1GKvNuk1kEgc+Knz9ZJzYKhzEu945ZN0/m2WHR4X4Xb8FC03PJEIUwG4ikkRb9TPMctL98tht4yC5NuG2LNlCxlsJ3rJwVyD6owW3ttPplRhg3Kbw7nlmDY+TYzPvRKZGEo6ex3idUYiGynLmDmr0BDrhsOaXZTPUvhLI/kp08hctO6o2ZYHt0JDn0iz6T9yLYhIJ3zdSwnPjhdx9TxXxO9SROpEQ11M7rGOuMh9aQY8eCfT5UQGLici0w6qSwZNO8uf1ucy0imC+IE1nFWpucJVlXGM0U2oyo2zdFWGUg+mk10FlRU9Knq6K/Qpr/mGoB2bYbsZXVpU/SlQ0EpkC/RGKScxx8Cwb064LZWmThQJlt74V3STugTNy276qimHhkr6B8SMGTB41zp91nHjFboKo8FR+LvlfZ4J1VmVy7/swm0EV+ULGN6cTFYWmsAdPfVnd7LD+uJQTgT3rfbMLEhiZl5yEXLeZ+HAA8rZUmkzXf3ymOZfSK3F/Z0z9fSYh4Fbxx9LcCx2ISrMAXrOdWFdNUCPQMQ=
*/