// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_FRONT_COMMON_STATES_H
#define BOOST_MSM_FRONT_COMMON_STATES_H

#include <boost/mpl/int.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/fusion/container/map.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/msm/front/detail/common_states.hpp>

namespace boost { namespace msm { namespace front
{
// default base: non-polymorphic, not visitable
struct default_base_state 
{
    ~default_base_state(){}
};
// default polymorphic base state. Derive all states from it to get polymorphic behavior
struct polymorphic_state
{
    virtual ~polymorphic_state() {}
};

}}}

#endif //BOOST_MSM_FRONT_COMMON_STATES_H


/* common_states.hpp
419cJshR3nmO9huHwR436mHk6qaZS307oNPBK17/COqLUzKdhd8GGDpQRf9mfzHELLjhLFN7UYxpNILphsI5uVldJQ1l8jvF7Jd5ioO6m5Z+gPHzVPi9ZmyeeK0+xHQ2EqpMsxpVs3fwYYeTH1O8HUb5bYplzchhlNu05uQQyvaYw9l+Hnnp+XlRp+vNJoE4w+LxpPFZGtdHsW4Pl8PociE9bSIYWz3fxMyg7FgOJipqxo7RHM61NGPHaDCla2sma2wYa0IMj6v8Ld4cTnwPt4m6yWFtHvh9tVyOxlficF7lOmEOHbSIezKPtZ0nzm/kcGTjKsxumM06vw7yncNZQ0DcI4/TD8Bz3MXr5rDjYZbrp7wbR6uLMj/bmpWPwXPb2Z2rmMeM6J98N3V3nlLBPm3heprN3kdDHbmMXq2R3/gNstrmekFO29wgzLHNSd8qyGqbK1w/zJHNqTBLQVbbXDnIaZuLwxzbnCzLIKttrrcbR7Ut8zMIstrmRrty2uYKN9iVp1SIOZfXt282yFltrktXsIU3kv7gsnKu3Lt8wdcqNJo7b9UtX8FhuJjlOZIrhhn/Pb/CHzkt/AKY3f0W3HaA48kAc6MAh4mA4Jb/5HIJvTcqCwv9uM/JqYJ8n/vPHuf5ONtBnXwTOVdUjPZxin/xGe3jxJrRPo70rTSfLvoJH2eYw9i1MfFmnFvv1Fzcb35cWunWJngfo/BXLy5aQXXW3zyd0uHofVe3t4BY713GTYNtpg3YdyGku3OP4l7FyCZcwzrfvt24NEzMF/+FdC/SR+Ht+i/f6x+5+qzz2wjx8K63KNPuHuhyt5rfeHxSFrZdWVnHOzunYePflAwO8Wyg3B3duqBCL1+B9XpSoe/8ms/Q8npU/5ohfTybMF9m3u+8FbE7S99iFGvLgXhXN/ltnTig02eIue0GdfqPmLftBJmDPN8N6NRyoPe0Tt/xZb2v9XXKA/SB1lvy98OAvib0kdbPtKsx++1XDOrUZfLct6AZ+kA9l1HR028zYeqM9ZLWqZ5Yn1S6W0/lsE71JGxBMW49xUp362lb6W497Sjdraeu0t166indrae+0t16Gihd19PQZaitpPUA//Cavp7fDkeKzW+HIxWv2w6jK2ld1m9B6bodFhXj1m9J6W79Tirdrd+y0t36XVa6W7+x0t363Va6W787Stf121VM2g6vgnkX9JW1cdVHZzOt5GrmE9b8VpvU0mKBVnY0kyWR5+9fGNoGPX03sXL+/glRZ9HQ0xNKMunof2+KsFft998xeMCvz2PIQEiegF+az9F/mOvlcwdNePCdcjgyKm6TOQyVIJhhmKGSZGYUYqiBy3KIbhZkVDkUwpwqh2KYU+VQCnNOOUyGGaccymHGKYdlzaATw9pPmFHlsB3mVDnshDlVDt0w55RDL8w45dDPYagcuD/dL5ikc/64AGS7mvB105xZL/i6SYDsS32dIjc6+oO7sH6ySv+fKPFeutbo0uHGuf0HSueblOFcaRlcjfoqygGH3/M0qhIeB5VGOaM9Q6x1Kv0g77s4WpprxHk/V6vVWesr7QD7X1ozmeH2rfXMFs9H+w4zlDFmovuHGMocMajXAGMyiXrVutO+SgHdDDIyjknFjLMbox1r3WaFw1jWjEnmLTFuKJ2SSTrmQ249ksZrHMsPk9rZceLwu3VoNCOmA7Ab4nzpt6DxJbaVc87b6sVvS8bOczym+zqHic/QSgS989SR+38xp6NRq1dNGtkPcDVbeHzOZsfTTcGhTXmaKRh80+/j0DZr1Bdkfx/Jv5/PbXDn0/LvqfuHMv6M0NJiRDxFqa1OcLtt4e/t1YnKLUvjXIt7Dq5+q1taHW3X1Y0=
*/