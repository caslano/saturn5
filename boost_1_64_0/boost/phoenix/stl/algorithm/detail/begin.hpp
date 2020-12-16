// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
// Copyright 2015 John Fletcher.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler

#ifndef BOOST_PHOENIX_ALGORITHM_DETAIL_BEGIN_HPP
#define BOOST_PHOENIX_ALGORITHM_DETAIL_BEGIN_HPP

//#include <boost/range/result_iterator.hpp> is deprecated
#include <boost/range/iterator.hpp>
#include <boost/range/begin.hpp>

namespace boost { namespace phoenix {
namespace detail
{
  template<class R>
  typename range_iterator<R>::type
  begin_(R& r)
  {
      return boost::begin(r);
  }
}
}}

#endif

/* begin.hpp
4wU8PmbMu3UhPQ2EBTnGWhsU8jGYCRzCZA5lNaawHlNjz/8KeZdL7JiQpXl31vuECnmf/1eE913J/Tk7a+xEIbwvWViQY+zC6eF9F7AEL2RZzuRBvCj2+gv7KRUn/klhP5OZwDNj4p8W3ndonPhvDO+bzwTexGTexmq8PWY/i8N+6sXZz1VhP/O4P69mRV7LOrwuJh/bwn5KxsnHJWE/f2EJXsro9RC+p7JCnOthdHjfGCZwLJM5LvO83id83wzfQ71fXeu8ZuS1xXVXkl8xmVt5CL9jDf7A5vyJR/JnHsMd7MZf2Je/8mT+xlP5O4ewkOtyJAozjfvwTBbjNO7Ly7kfr+UBXMQDuYYl+R7L8FuW5fdMCn1ak1mKFViOlVmZh7AGq7A1q7ELa/FU1uZw1uE41udFbMBr2JAPsREfZwvuYCtKW6HWrMk2bMC2bMX27MyjeSo7cjCP5Qh24SR25Wx24wJ25+PswWfYi6+xL9/j8fyBJ/I3nsxI39ZTWImnsQYHshEHsQ0H8wim8FgOZ1eO4mCO5mSO5dlM4wyewYs4kddyEm/lmbyLZ/EenssneB7f4vn8mNP4GS/gFl4Y6ue0IuF7dfi+Le/OYekrEvpih/N4A5P4HqvxfdbmB2zCjWzNj9men7AzN3MEP+dYfsFJ3MIZ/JpXcSsf5Dau4Dd8kSULK3eW4kYm8lOWZmGJTuJBPIgHsxxrsQIbsyJbshKP4cE8gYdwOqtyPqtxIQ/lrTyMi1mDL7Im17Eut7AeD1BW9VmKjViejVmTTViPzdiezXksW7InW/EEHs5UHsFRPJITeTRnsBvnsTuvZy/ewd5cyj5cwb5cxRP5Kk/iO+zPH3gykyPnIVtwCI/lUPZhCk9kKvtzFNM5lhdyHGdyPBdwAh9lOldwEl/jmdzEKfyaU/kDz2WRomEsTU5nBV7AaryQjTmDLTmT7XgRu/Fi9uAl7MW/sA8v5cm8jCN4OcfxCp7JKzmTs3kp53Ae5/IazuN1vIY38Drezut5J2/kvbyJj/BmPsmFXMP7uJ73830u5iYu4U98kCWKuU9kKT6SNQZ6aJfh5Dj3f5eE+6q/sBwvZ21ewTa8kt04h6dyLgfwKk7g1Qz3r6HNxTkW5/7V/5pWhLWYwNqsyTqsy3pszgZsw4bMup8O+y0jrCqc/fOz3D72y2Qmsjy9T/mEdpLQbrJAaBbzm/TTId/PsBxX8WCuZn2uYQu+xLZ8mR25ll25jn34CvvxVZ7C1ziYr3ME3+B4rudUvs3r+S5v4Xu8k+/zcW7kGn7Ez7iJ3/AT7uCn/JWfcz95+YL78ysmcisP4nYew2/ZjT/wBP7Ik7iDg/krx/M3TmYR5T6bRTmf+/Ju7sclLM6HeQCf4oF8gaX4I0vzFyZx3zCGQ3GWZylWZGkezINYhRVZlfp2ecYu/8/5Fb0/PN8X81zfNh8AJb6wrdBZSBGmCfOFZcLrwo9C0pfqSqG/MFWYLyyLhA47nw0sEZ7xq7pYXA/sfMZvmjBPWLzzeb//+mf9/hue8yvIM37/quf7/huf7Vv/5d7n+/LzfN+efLZv85fyu0U+hPbCacI0Yb6wTNgoFP/K8RT6C1OE+cIqYYuQ+LX3CWOEecJyYZNQaKt0CG2F3lsL7X3tfe197X3tfe197X3tfe19/Y+8igpD/jXP/3vqbJK5sTMe/f/Tz/4vTHRfG22PyPP32vi/l+f1O27BfxeP//t3wZ9L2FO/i8d/rmLPzcEZ/3mOgs+1Gf/5hrye/yj48w3/6uc54j+3seeeS5hVJHf7j/aZnG1E8dtg8mx/CW0v/6F2lz3Z5rKn2lsK2tZymbAyH+0r/+l2lZQ92J4S05Y=
*/