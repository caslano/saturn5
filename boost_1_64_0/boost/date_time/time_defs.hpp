#ifndef DATE_TIME_TIME_PRECISION_LIMITS_HPP
#define DATE_TIME_TIME_PRECISION_LIMITS_HPP

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland 
 * $Date$
 */



/*! \file time_defs.hpp 
  This file contains nice definitions for handling the resoluion of various time
  reprsentations.
*/

namespace boost {
namespace date_time {

  //!Defines some nice types for handling time level resolutions
  enum time_resolutions {
    sec,
    tenth,
    hundreth, // deprecated misspelled version of hundredth
    hundredth = hundreth,
    milli,
    ten_thousandth,
    micro,
    nano,
    NumResolutions
  };

  //! Flags for daylight savings or summer time
  enum dst_flags {not_dst, is_dst, calculate};


} } //namespace date_time



#endif

/* time_defs.hpp
cu4bX3HfeP47b8IK59ibuZNv4wT3QAKxwmlWnbzkZtnJf8pnXVghnUrkg15aRii8ch+hUMgSI/bbgwEVhuKwCPdLHt/pwr05XR23lltFYfWrg5ErzHUoDsatnLp99QGaw5AkCVCyiLNkMYFJedq/kZSLkZRXKlJuBekOjQdsfCzXpKNf0dEv6Ogn+fbKe9ulSuZ2kYn3COYQa8DyHMKFexmsCw19hhtKdQtNiBf+dRR3g1MYtae/5W7QU3WD4C+5G0zmBHd8i7g3W3EvZtz3UGh4OkIDUqATPYHGraMkGpMFGmdyKWOS0Nh4I6MxlRMMIjSutKJxy42ExgoxLmojp/ye1zP89YdLxKQKJIQ1zFM0SPKgYFy1nLoeO2Bky/VyfPzhIMboXC7w3nbGyK4wGi4wOo8TXNmOGJ1lxSjvxp0+A36/R+u/as1y9H1KcrIpyYlPmYt+vIqrfMM3qh+HVZWLVlIjnJTFsladVdYKQE+0yFojy0rZS68QQBzYG35WxrRfLebXb5j2bkX7h29g2t/FCXoSIldYEfnFDYTIFsiAuj1zQJWrAVUuBlQ5ra9Gr1ED6iaVSQ2oOr0n+xMH1KsjZU++ZiTj/hijdtHXiT152/WM++NCvviaB5QF9z9CGjTDUGh4UqOROKDGKzTyBBpPcykfbU9Eo0Gg8XvB/7fzgLKgUc1oLLNJNOy4/gzLY0CRl2BexAsaUmK2B8LaX2L28IESs5kHMmYviPonYfbadYzZi5xgBGG2xIrZQ9cRZl8oVBo2srKCv96bxUMdZaMKOdRXjSAUQHT+ZASj8Ccu4aVtjEK2QuF4gcJrnOD+bYhCoxWF4YRC7CJcO9tDZxEJNqD6ner7uxHMV6C0+aK0txnY6aK0HFXa31dwae9wggCV9nNraRtXMCf5r9A677yH/S8lC8XX3mVRrEWuWyDW5ixXhKqkoIxTJ9xD4NdFI+iU7wznNhrBTfD4l9xGDtVGlddyGx3ICW7+EttoFrbRUtVGe0IaKi+TlWIafqwrLR5dbfH9JLbJc5AhG/OQXb1qN6SRfMCvGbqH8oUJ+2xhln8vJEQ2KlRkZ58HgGlDKcDXzmVVFvP1c+McvJfNTqTQhdSck5idczQkmwjJf+qVN7QFwxOKglnggfgP4CEQQ2ojR70x2JDQs2TW5kqCiBfj4fZVdIBA3Y+eQt2LAmx75TWa5mJx3i4U9/rrUJzMUytvGmRDT6+2O1/H31w+rkc0HL0SRwqDs/VIDixtXBEDpM+qMCbYIigeLCdWIO/YM+aNZeK+D3ovCpi7N614mnAnrhjVQ7TB7xVXBvqi/WSdG3tgimg2fAucijWcBJ7Q/wHXko0WTMnNKlhBRKtIWYor2AD3FYbjwEs03EtxuqSRQBQz8b9ghY7/GMZ/iMJ/sBX/UoV/aRi/TmLkszE6Vp1I3YyaBLuyhJAbPRoV2VPBX96OjKDu/aQc36/dnjy+ebzWZDqw94OEnN8ywJecrQa4RzUwa5DluG5y4RtGypbCjj+urxxmLm2YvcyC9HmvqoHdV+ugfbUO6lEd1JPYIfAbu6Po7edBb0/sDin7DEM3qCdf9XAHPXnmgylG4omXZDgS3zesI/Fl+E6D/v2GkRnXiY6XQ7OKTzQBcWtcJubrHkgxBm+5OMMxOEwfg3sKDtDX5ADVkDboiX723zaoEl3j3XubUiqXR+a5oRMw+y/nex4e3x5nF3ldGn+TbtPGX+KAY5eE2ILauPJPhxzMeD1g/J4LfVjOGH3ljOEyO0M5a7hSe2mU45P8NJ4gh+XcY7RehRUkuzo+ZSc0WrWcwryNI7exr1SqmeDhYrNrk/uwtW+mHriphjh0Mx9wHOY=
*/