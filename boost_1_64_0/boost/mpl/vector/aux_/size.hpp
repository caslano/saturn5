
#ifndef BOOST_MPL_VECTOR_AUX_SIZE_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_SIZE_HPP_INCLUDED

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
#include <boost/mpl/vector/aux_/O1_size.hpp>
#include <boost/mpl/vector/aux_/tag.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

template<>
struct size_impl< aux::vector_tag >
    : O1_size_impl< aux::vector_tag >
{
};

#else

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< long N >
struct size_impl< aux::vector_tag<N> >
    : O1_size_impl< aux::vector_tag<N> >
{
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

}}

#endif // BOOST_MPL_VECTOR_AUX_SIZE_HPP_INCLUDED

/* size.hpp
jyDftZ39EMSn1Q74+8TdfhnIy/v4Pa346W3sX6hlXczn/Q2LsGu8jzWLz7jHqNtcj/33Ro7gXTQYO8lTf409mkk/bfHXxuEH5aDf5yKnbzGfFdQp5WN/kOvuq+nHGPx0V/ScH3Xe5dijcYPIW6LXiLtcniVPl8x+bV/yqchpgSd5ODN8EO0q/hLeiHxqyVnitf7YEXiiMm/iDvahJLer6zqYH6sd2r4U9vfeSpw3iXagL0tfw34YWZeO+AvsT1lGnX7FKwbqVpHzm5C/xdj114hP0vFnRhjUc+GpSjqwV3x/0o44Gh6+mHW734P1yzpbdYK87grkFPu91UD+YRB2fws8HHaocwTrDDnXf4hdPUqcd4q8ryf9ccDu5WH34blL/VW/og9q/BD6YDh1A/7oV+avivmt0N7Hynp2iCG/wns8jT7Ibxj2j33Bx4YyTpvhB+5ETljfkchBjQXxlo59g8xXZAr8VTn1MWexG6nEJyb86AOso0fI38yCN27HbvohPznYjRDqjL3w/9hfWldLnPk6/lgH8UA7+tSJ+aqBh2d+ypgfD3icffCs5hz4BvRC3WLWRRf2cRP728YQJ7+LX4X/64e+a0SuUjT/tpn3P1XjD32FXXFBPu/AD/yT9yAcIA9tzf3e57porQ4deY8iL9dGHQT7QBx2UCdrZFzQk2VP8972FObxQeSs3UD8Q57qBP66Lfm6JeSx1yEfvyHv5PU9iHcTWHcBVrwXFz8xZSHr6gfqfbLQw/BsAefg/aYTb2xlPZxh/Gejb1g/Xa7EabTD7gsT+w3gMxu4fhL1WmXa+3+oV9rH/ohN8FrL0UPYzX0R2M9K/HnWfxf+pw31Y/vvxj6UwQ8Sn9aRv3fQ9LgL6+55eLCj6MPPWKf/IB64BT00ln4wvsVr6efLyNUS5Gcm7SM+ceb6HFd+RxyfkED+5Rb8AeyFyz+waz7oZcbBlroMW+xfCv7TsuP050H8323wAz7sB6XezNmW/TPkfzoPMw+11G1mw9N2w8+m0q8o1vO76LECxjeLcQ9iHpKolxqCHP2NXBD/pRCPF3urflTx+84C5vUu8uev8Hcd+uZT6hlWUI9zEn1CvaO5nvHg/cLGePh/8tEV9sQB+ONeX8KTdlIPSF27cwj+yCTqTNmXEBgDj5APz824dDJvVs7km2zxV9zRK+nMM/svQ+/DD3Fnn9Mz8M9HkQvyOfk28DabyGs+Tb7dEv4hg7gS+UxBPvWzkbvN2A/4WK9ZrKMf4POQm/3WyEUV/rqd9h544tCB/dXfr0Ie8YMCsD8ep2gvPIYX+tbDnbzgfvJk5F9tQ/HH8OPieK+E8Tb8b/YfevzKftkI4inqYbYWE6814tdOIV/5Iv4b47TqLq6D57e1Jc/0KXk1/Cc/4gQ7PXFSlZG6AdZ/IfsKH+B9TNRxhN9EHHo9/qIr6/sB+PD7yPs1kje0IX4Yyf1+pg4hiHw8PGjou8R3+M1On5E3TaQ+LcPMeznIozrCS8WRX6oi/zGOuPxZ/L9D8NUu+BMl+C1F1AvZkTf1ox3n9Pgn5APggbuGMm+T0FP0P+113vM9C/8/DzmkrrMmvR/xHvnxa3lPVzbztpZ6IvwN/dPwNwfwR/dRZ1EFf8z7No3o1VW57J8OYt1Us89mHHbkJ/z+H5mP2/D7LNCf+Jll+Jnp+KXGEvhz6kLT7PEfg7TzGHTYDfaP3QEPXwlvMlzL+1uqv89hPZwaSF0W6/4jeJBOeF/yFA3wGo3O2E031tcu/KZC8oHwo7lxyP8e8kT0z+Zr1ncq+oT/dzejT/Aj8onbi8MN1GdizxKoA6e/gdR9difAM5APLVmDf27ALiZSf4XcVLBOIz8=
*/