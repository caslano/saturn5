///////////////////////////////////////////////////////////////////////////////
// features.hpp
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_STATS_HPP_EAN_08_12_2005
#define BOOST_ACCUMULATORS_STATISTICS_STATS_HPP_EAN_08_12_2005

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/accumulators/accumulators_fwd.hpp>

namespace boost { namespace accumulators
{

///////////////////////////////////////////////////////////////////////////////
// features
//
template<BOOST_PP_ENUM_PARAMS(BOOST_ACCUMULATORS_MAX_FEATURES, typename Feature)>
struct features
  : mpl::vector<BOOST_PP_ENUM_PARAMS(BOOST_ACCUMULATORS_MAX_FEATURES, Feature)>
{
};

}} // namespace boost::accumulators

#endif

/* features.hpp
trRfRzPYpJqP1dlozQ18Nno8i96tZI2xEYqy+u1OqK3DVXVhVLXdQBtZeZCcvD85+SJ7ltUZJoOb6AZWLs1PRiNFO8jW+/A+aY37//a7rIwDsLJ2ioPu/02xbiSlP6lgKIIQ0pZuT1MIFE9txhcjZP+xA1+F8VD9P5zowQjXyjuEpbvk9n6dBvXMP3B3/RHdiJlsNVB+a5gWBNBqGbA1QPiI+A810xIkxXTaA7uhgaqu0hbv90a+WQ6RLMtcNZk3Tkjx1to0hNFLturu0q16bOT5+uLtdaAvIikZepOlW0kVUrU2XFI3p3TNDeoEZ0xivYmVxaDDe88ccbH09fIKAml4O8IgDSi+DdLA+Ohh9wVQbBMK04tmrKlPmtmG4cpNZ12v7kk19ruzhKrrivqejE/zhEUyst45k6SEGRwghFXrFbjxyycz5mbLEVxmrk14VJiPJRyV5oN2qF+bdyc8ppg/gAPUlWp+uKq8ar959gzKL7gICgYt3krr17OnsVweSLqfDTUy2W3oxVgFoT1yr2iE2nEbNsJx0GUfjZZKqz5fM/5ClWBuYsuLhSj7fHq4Eg1HHVWnAt51phT0wXngjM6CcCMBgBhtP8VxCfXyuZQhb0HGeZDWLvP8tX2S3AXmULhDsAdFEeb2n8zv5S8K9NjlIONo0zFvt7I845cK6HEGHvJoFmbsRxHZFFWh5yQHLEgKyLlOUwHPRcDCdXghYsHl6Ge5sy9FEWv+ph4iX794/fZ4A56W9DXgweZEfe12Xxvosxn/h/sUTHbvbN3tXhiGm6jbmeq3qXR9JlcvWT9/Q6hk0w1HS3ncqwN9CgqQhB6vB3n+zkXlmxeBrc38lgg4KF0UHrHJYc47HXVJXK5A5bFwGDA2lBtNPD+sOYPmuBeu4pbo7V5yDsK0Tcd/8jIR7AjSzRxVyrHJZKf56RyFJszJli8Kxa7D7zeX6fF1eu0zalLAANf37sBChFeFewZxVelo4mASwJLROZ5UKXz8CapvC3WrJjqnfjlILxILUE0zTGTnHtlN+xnBW6np7Oah9rDeWaHhtWm2pH0Pw+q2UL2gSswZp6nK+B7oo2IZb3Jc48WA+2E+i/joVIk2Bd66MW4ZRcXJVegaIX8d5HijVvKq++ZJcQ6xiIocX8/oQKPVa2cIJGoznF/dVakyPIqpY0lljsGFND+8WoJ/sl88Kij/lyYI0WQipgAsALwfKFyHzH4tmtvXVcxGBDLvwPRKXjg4Zvz0yeL3K5VqJZcgjIE9SvnE2GfcSqFewmnNPY0ymwS7VQtYh31l0Yp9fZi56kruIae4l45BdC3epNV8kuYhs/KTufmrb2XIa56U2t7/OC4HOAzuhKrBFBk3N86S/PsQ129cpc5rwXbYuHIlDHkAHmT+/EoJ0/axsvGEJiFMXRbdwxI63pwhYZoQhjOgiMtVH32EI/KmoxlpmteqBFcyHRNtubGR/GeiWnh9hvmYJLv+LAl5DUJyf+Ng5l+5Q0RC5hnMcR3CU35Figl/N+nGg/ciFKcuSV/LSVf/ru1IYtlp18mn5pqZksxH++JxWryp+q35AR3rEd5A/Gqsuut8t3x4zdvwwUZ609V2j41D7lGumWwa8oPpCdMQb0QXqxBNF7DQYC19OAPRfPSEOrWTD94bTcf/rdxdrwJHakKllee1P/VJa7sYNJ6sMarbKvb9qw52/v/3X/Hnvzj5Hf5KElzyL7NEvaP/YCOO+eFDYmqdg5bsDgIOamWssI/IdxkP4K0UYCuoRKpLkwimcnco9y5201wIEW25vMdvbKd9ynYHfZqh+p1OEutYJOaotDcXGDOezeRZahYUKQUSKy1zQXojxeQjX5xZKVs=
*/