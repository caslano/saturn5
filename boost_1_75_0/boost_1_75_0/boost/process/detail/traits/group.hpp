// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_DETAIL_TRAITS_GROUP_HPP_
#define BOOST_PROCESS_DETAIL_TRAITS_GROUP_HPP_

#include <boost/process/detail/config.hpp>
#include <boost/process/detail/traits/decl.hpp>



namespace boost { namespace process {

struct group;

namespace detail {


struct group_tag {};

template<>
struct make_initializer_t<group_tag>;


template<> struct initializer_tag_t<::boost::process::group> { typedef group_tag type;};




}}}



#endif /* BOOST_PROCESS_DETAIL_HANDLER_HPP_ */

/* group.hpp
fSw2Dmk9LJGmRHNu/Fi8SEHbepMJh+JfGAXkxKifsngMYeW3RLvPb0fl1B21YQbzq96IPVuO8Lmnh8xfRwjuF2/cZo/So8QziHJilXeLk7Zu+sGJ+mzFIw8i6Msp2VwFlb1gvmDw5funumEnjhFButPhc7KHSAvX1NENshYupcb4HK0HUhnjOKQBVFUIOZXw2DnKnsfoSvj43q4lsr2fPvrkITJE2iyfRT2TRWEPUOHE1EEUjqYa7cdlmtJYyDotcPzi9/LrY59j9pMMFnHwuz+Gy2uBZT8OLu9C3bOFgrteTDgQHiS6ozf0/VxlbK2AG+UVl+RU9WJlfCjC1cQPubCyeUl+sESBlZHv/5ePW3mQWdjR1jFi+g7UfYuqGDIrYFZIvhE+wffFlPMy5I5yYsbdtMqX6UOlaGom5virw3W35JKxTESC3w/LDd4LvTivKUbwF4trWH1bcMv3wEg9WL2f7BBW6Bn3oNVyX2OdchpX8qr5ykib3EpiTN4+OMRAV2Bt3F1XhNE5o+Qb6TLT4gDJnF7FkphnmpEZ6QrjvqR1mXSMMiqPwW9kIV/FC7b+VmO7LMesZD6fhWJG/obdRT3ONwHp1UaKdC8UZuwvlFAMUd3C1D9mbJCkNv2mNAOzKukHZo8tXP8S3lHtL/ZUWzDtaGHH0PtqsTzUHKDVGyL0edT30IMtv5d/VdXHvqUCUx/bR+BaYt+3EaSF
*/