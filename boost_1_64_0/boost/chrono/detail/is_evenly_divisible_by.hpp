//  is_evenly_divisible_by.hpp  --------------------------------------------------------------//

//  Copyright 2009-2010 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_CHRONO_DETAIL_IS_EVENLY_DIVISIBLE_BY_HPP
#define BOOST_CHRONO_DETAIL_IS_EVENLY_DIVISIBLE_BY_HPP

#include <boost/chrono/config.hpp>

#include <boost/mpl/logical.hpp>
#include <boost/ratio/detail/overflow_helpers.hpp>

namespace boost {
namespace chrono {
namespace chrono_detail {

//  template <class R1, class R2>
//  struct is_evenly_divisible_by : public boost::mpl::bool_ < ratio_divide<R1, R2>::type::den == 1 >
//  {};
  template <class R1, class R2>
  struct is_evenly_divisible_by : public boost::ratio_detail::is_evenly_divisible_by<R1, R2>
  {};

} // namespace chrono_detail
} // namespace detail
} // namespace chrono

#endif // BOOST_CHRONO_DETAIL_IS_EVENLY_DIVISIBLE_BY_HPP

/* is_evenly_divisible_by.hpp
l3T1nNZOPZReXZixE7DUZ+5K/2rogsYxBidNJKZr5Y6+NHG8HxDXoVO8K/xQzy9G3r+tY33DcsxnFKloaK86AYag9mlfnrlPY3s3WecQkTemhRt1cWCHynH1Z+vupiKRehIPK1WgHz0Je76erxOd3hkt0UCVSkhy7D8dsGNB5aJS0ngw/+GDapRbSG64q2ohMEQo0ZNN5dN82C6U3Aq3rTnm9WzTwInpFFLEfycSYl/W6rE9tF2n+6g4GLtup+dPtYxzD0toSmxdPRwxp+2VP8VwgAPEszaghIU5rHurOHB9PAow1eNRuqpLTugXzr6NmmVVFUcpPJyNRZeNKw7RsJXNUum+A5reapXfXQFMKCv12o76dOnlxHBRf6pjj1kAnTTgVXxxw9f1Pb9GzWLkuTeHxfxBmJlWIIYMlKOu2kC367BxyxkPMQfHK8gdW/2YAUHbvF34jH269g5cF/Lg28r2ODSU56fHKYbc8ZFtgvN9wvdm/5kO4+XRcGOGD7fLcDB/hFCXTpHcR67ZGjZ0yb3Q4VdVZIQTWuIsVu7JhOk5e+X6F0qJ7tqguw==
*/