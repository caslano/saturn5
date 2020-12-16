/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_ASSOCIATIVE_ELEMENT_CONTAINER_HPP_JOFA_100831
#define BOOST_ICL_TYPE_TRAITS_IS_ASSOCIATIVE_ELEMENT_CONTAINER_HPP_JOFA_100831

#include <boost/mpl/and.hpp> 
#include <boost/mpl/or.hpp> 
#include <boost/mpl/not.hpp> 
#include <boost/icl/type_traits/is_element_container.hpp> 
#include <boost/icl/type_traits/is_set.hpp> 

namespace boost{ namespace icl
{
    template <class Type> 
    struct is_associative_element_container
    { 
        typedef is_associative_element_container type;
        BOOST_STATIC_CONSTANT(bool, value = 
            (mpl::or_<is_element_set<Type>, is_element_map<Type> >::value));
    };


}} // namespace boost icl

#endif



/* is_associative_element_container.hpp
j1kPylvlmzDrO/Kd8q2Y9ZC8Tb4DszbI98h3Y9Z35aHFOg6P5vhA30s4yYsx62F5TF6BWRvlpfLhmPWIvFw+HrO+Lx8on4xZj8qr5HWY1azj+Sh5A2b9QD5GvhCzHpOPky/BrMflE+TLMWuTfJJ8FWY9IT9FvhaznpSfLt+AWT+UnynfhFmb5bXyFsx6Sj5Nvh2zfiQ/X74Ts56Wz5Hvxqwt8kZ5aAyPL/qx/FJ5EWY9I79CXopZP5Ff4/cvZrXIl8irMOtZ+Q3y0Zj1U/lN8omY9TP5LX6/Y9ZW+Up5LWb9XH6nfCZm/UL+Nfl8zPql/D75IszaJl8nX4ZZv5I/KF+JWb+Wf0++BrOekz8qX49Z2+Wb5M2Y9by/DpFvwawX5M/It2HWi/Kf+f2LWa3ybfLYkbxepd/In5dXYtZL8pd8+2PWy/JX/fGFWTvku+RNmPWK/E3fPpj1W/m7vv9j1qvyD+RbMWunPHSd5oUw67WEk7zoKPZD+h0e8HWhvAobT69H9O8H5LVYI+2Sd5Evx1bT7/HM01psI72R5a18vrwJ/wPega+LtZ5i/jvcbXibvJ98Ir4Lf1M+SB4ay3GS3tJx7DD5QGw0vS0fI6/G6mi3/Fj5fGwpvSM/Sb4KW0/vyuPyzdh2ek9+lm9nLP9o5iCybm85Nor+mOXVWD29n+VN2Ar6IMvXYZtpb/b2tN9JH2Z5bBzHE/pI13OarucobBL9ST7L71+skUJRvX6QL8M2Uhjnf6HL/fZilfb3f+RN8inYCorKr5H/tdNGLruZcvT/27PYLv8vnFpYx3bK1/Vf6reL/4ajDS+QL/f9fzzbhwrlK+WTsDrqIF8tX4qtoSL5WnkLtos6ytf7/nwsz8vUCS+w2ymfiS2izvIn5GswK6b1POPrx3ZQF/kv5AF/+8fqGk0+Ll7w/R+zuslf8+vD4y6Rfu9ueQ1mdZd/KF+JWT3kuUuS3si6rZKo/nsK+WrMKpX3kG/CrJ66/mXyPZjVSz5AHpvANqDe8iHySszqIz9MPgmzyuRj5DMxq6/8WPlyzOonP0nejFnl8rhfT8zaT36WvHwil6X9tX2m+fXBrP7y2fJ6zKrQfn6JfAlmDYgmj8+Xy1dh1gHyq+UbsDY6UOu5zrfP8Ty/00D5DfKl2Ao6SH6zrwdroUHyW+W7sdAJzP/L75BXYKOoUn63vAabSUPk9/ntwqyD8czTCmwdHaLLP6DLb8V2U5X8IXnpiRzPaaj8EXkdtoSGyR/3/RCzDtV++JSvH7OGy1vk+fytI+sw+S/lEzFrhPwFeRNmjZS/Il+PWaPku+StmHW4/G15H/4+knWE/H35ZMz6hDz8Wd2PmDVani9vwawx/niUF/M3k6wj/fEor8aso+Rl8kWYNVZeId+EWUfLB8vbMGucfJi8kr+ZZB0jP1xej1nj5WPlazHrWPkE+W7MOk5+snx0NduAJsjj8iWYNVE+xa8/Zh0vnyov5e8sWSfIz5dPxqwT5RfK12HWJPl8v56YdZL8SnkFf3/JOlm+2Lc/Zn1SfoN8PmZVy5fLV2Nb6BQdf26XB6dx/KFT5XfJJ2Ez6TT5fb7/YBtosvzbfj9ioycz/y9/2PeHyVyeTpc/Lm8azn+jFmf+H888VWI1lo57T+vyC7GV9GncfmSrfDO2h87Q+n/p+w9/l8k6U5d/UT4Rs6bIX5I3YtZZ8lfkKzDrM/Kdvj9g1tny1+V7MatW/oa8ir/5ZJ0jf9PvR8w6V77btzNmTZW/J9+IWXXy9+U7MWua/EPfP/kbUdZ58tDn9Hsxa3rCST4fs+rlufI1mDVDXiDfilnny4vkffg7UdYF8s7yCsyaKe8qH4VZs+Td/Xo=
*/