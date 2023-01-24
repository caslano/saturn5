//
//  Copyright (c) 2000-2002
//  Joerg Walter, Mathias Koch
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  The authors gratefully acknowledge the support of
//  GeNeSys mbH & Co. KG in producing this work.
//

#ifndef _BOOST_UBLAS_DUFF_
#define _BOOST_UBLAS_DUFF_

#define DD_SWITCH(n, d, r, expr) \
    { \
        unsigned r = ((n) + (d) - 1) / (d); \
        switch ((n) % (d))  { \
        case 0: do { expr;
#define DD_CASE_I(i, expr) \
        case (i): expr;
#define DD_WHILE(r) \
            } while (-- (r) > 0); \
        } \
    }

#define DD_1T(n, d, r, expr) \
    DD_WHILE(r)
#define DD_2T(n, d, r, expr) \
    DD_CASE_I(1, expr) \
    DD_1T(n, d, r, expr)
#define DD_3T(n, d, r, expr) \
    DD_CASE_I(2, expr) \
    DD_2T(n, d, r, expr)
#define DD_4T(n, d, r, expr) \
    DD_CASE_I(3, expr) \
    DD_3T(n, d, r, expr)
#define DD_5T(n, d, r, expr) \
    DD_CASE_I(4, expr) \
    DD_4T(n, d, r, expr)
#define DD_6T(n, d, r, expr) \
    DD_CASE_I(5, expr) \
    DD_5T(n, d, r, expr)
#define DD_7T(n, d, r, expr) \
    DD_CASE_I(6, expr) \
    DD_6T(n, d, r, expr)
#define DD_8T(n, d, r, expr) \
    DD_CASE_I(7, expr) \
    DD_7T(n, d, r, expr)

#define DD(n, d, r, expr) \
    DD_SWITCH(n, d, r, expr) \
    DD_##d##T(n, d, r, expr)

#endif

/* duff.hpp
4Ra3CCcXkriQll9KU+L5bPuF/Vk9m/uxtRJG5veRXzje0XC8XYYvaWlv4ceBbU0k6bhjy2lztxJva37c/2ojtp2VLiKIv+7ONBFbkdZsfwn2h7E/hP1TsV/c1Xy/D/t3Yf8RuVAM+x0t9tdjfwT7o9i/DPsb7/qf06X/LWBabiU3rWh+bEULPUz9zRb2exXq7yEzyGmkg3yADJLjyLvJLmQH8npyPnkduZLcSM4j55I1ZID0k3VkCtmD1OdhERMLRnsCo6q95R6/uzRQgbL5gbKNLfV6q2eIr5U20eeZUVnqVQELq2eUBiqrq4T4VO2VR47yV88Zk19YWRNAHIMErBM8pV63v3pGXnm531ODJJaJiQF/ddWscaVzPKP8Hs/w2pkzPX7xv/9a/Wcd9WapZPnKNCHvwGRuWdBd2KZiC/dHDZhtiAPnG6IR2wGnIUKwVWHfQmwN2NZhexrbKyvlI8GK+kTGZhHlvnKft1+51yvyvd4RpVWTqrzVpeXjqudJHZdvhLe0puYsWnk80/8fr4iUUsmVK/ki5C5XY7nlWkiSqxxJRNEw18oR5Zibcky5QqYoV+6jubJyjRyTaxhm7rHZ77P5/eP4PPd+vZ+v5/P5es0DFRWjOXxH3d9NvYv0IJAgm7v46Y8tisXduHFl2DTpn8nYcxHjVa86pLrmCbW/+iNE9wqySv6bhG8TOBfbhnNVkL/Rrh6ZnpDm
*/