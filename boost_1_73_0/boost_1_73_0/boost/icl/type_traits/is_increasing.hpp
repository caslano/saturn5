/*-----------------------------------------------------------------------------+    
Copyright (c) 2011-2011: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_INCREASING_HPP_JOFA_110416
#define BOOST_ICL_TYPE_TRAITS_IS_INCREASING_HPP_JOFA_110416

#include <functional>

namespace boost{ namespace icl
{

template <class DomainT, class Compare>
struct is_increasing
{
    typedef is_increasing type;
    BOOST_STATIC_CONSTANT(bool, value = true);
};

template <class DomainT>
struct is_increasing<DomainT, std::greater<DomainT> >
{
    typedef is_increasing type;
    BOOST_STATIC_CONSTANT(bool, value = false);
};

}} // namespace boost icl

#endif



/* is_increasing.hpp
NDG6Qq0tgtUjJdFlCnmXqFSuhCyOjG1qKk97+c2xL15zEZe/BQP/tP2Clz9x/E7y9ezW+bJI5eLIuJV3jfoazfU/Tgyzkmaa5tbgeSPHKRQvjurxmE2KF1z/s1mPXJu2zMUru6KrzKL4e3QraPhhk5Y4Fmk04oYo8aNMFBpgvLohuxbrl1aeLycoJVaPWZGettEArbe+hpenBXTlEIbMupXl2T/4/AbXG9v1Sb5Qp20L9/4ZfEt7CEsxO8C6ywc07Ji9tfqFCg/g98I36p4LJhc3O7XIDllBu5Yv8O149ooPdfDWiD3kngu73baf/7Wee8GMfZKDiI3IZ7Lf07qDEQSB8+7m3W/WA2OE9qWxX5E2C5qHSm2+jwcvB0h0rc2n+a0/2/RX3MuslJteItv2LnNlUYtXQ4k4LP43f0NXIuNlORO7NNVDiyJu1qfDQl8t7I05fpBOoqL6XsvXc6zSgsPL+C7Te6nfDdvuSCQOIvx8Yt1uXXnLG3G3hR8jPm8NOOtyv978G5DPRw7D9/CbwP3Zg4XunH+qbJrIm03ttbP/UnUbnrcLa25Cm/+trrdw27IQNKGhe0ZP8frhX1BLAwQKAAAACAAtZ0pSCKftvfUHAACmGAAAIgAJAGN1cmwtbWFzdGVyL3BhY2th
*/