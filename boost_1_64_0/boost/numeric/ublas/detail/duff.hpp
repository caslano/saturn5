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
iDi1sv4hZUeGdEVWuyJXuCOVntAMhDK27wNRb1FHKm6djilakopbp5lFq+RnZJE/FQeDh8EQP2kwdIq0pqJ8pCn8c3uEit5Uw+ATh9IQMeJcO6khbUHenmPjtaLUavcbYjKGhX/uMMJwarV9dYu/bUOZBleo/Lu6UpB38rxhbnMH58uPLzgnb4/XvjdSdiBS1aeVHdDm9IX3p+btwaH20CQc+rz4a+I53O1W3p3wc7uYvNaZhRdBu7OUcYppnNfx73i1x5TZPKQb6AkN4vmjF1GBKg+/yFrpRo1LdyrVi86npG4lVifsOY3MaEKbCbmjI9OhCAxy2TqiIzOh9EdHZuEH+Yr30XwgG+RoOFP/8HCu5VIaHAsff8/txatSfJGh0wRHFgieky84OVewaDxw2caRC/gzdDZ/zsnhT0o2f8Zm8WdCJn62fjLFjx+tzHZ7KX9dt5fjt63Mfft80be80I83GVI2oQjkmujXxPL22dB1pRQDJQddKaVQcQspxW+oGlwLPtxhwzOFUiEsvcbWHpmdcgT63fuh7zD0gcyXcSzjiTP6o/984Qqp3Xqxtz/KkEjHTEXHMT5FR22O+19Nx5dBx1OjHhIZaRUCKuLcNeKdE4c0yFI0OM/7b6PB/hPSIPwJj+2GweFP+HDFNlzvEf2wG9BLecojZR78FN8uNEqgT7i+39YLR/3F6MvwU1jmWT1Sg3JOv1bl0zwbIp6WBdJpvaAo+aHh75ySxyOtPFKm24J5OHauDqAP5wF09OS9uXpbOuTup+g34gdHtXvPi4akA9DHI7MLe32SU5w5hY1fr7DDqPYBz3EHpQacXPoL0v4ppB0HYcNoKQvXdYhsux65EqLPGtUfbS176W57a+0fhR7hovGrU3wYAxrS9LZB/WjCoreL0yY4xVPQc/TnhvRH9XOGAzJRtwKeGThQ456OSL4zFClZCObSe/QJXjrOCrhKYGsrhu162jJAtu1Jv0KcXWX98uaOXgqDdb/ytiwVzVapsn3hS23Bc6v1rlFMMp6LDnkaHKCBdon2hJ4BukSfjab0N0rXXqxHfP3Rzg21f4yGXoIQvv7oP8tqa/AE2oVuCxHu1yQSsMDkQauF5beLTveOFLq9HCOZgyT7oBtUqRfSjPIBJg4DO3AsKWpm9GxppzYpyieGIpkL8/asU8dp9Ie9yIL+MwQcDb2Mgj+pTCCdz0s674Jn7RMe3BvzTimSFN4sRSyyKJjEqIj2jjrQemt9vRMBlTWShNdhr/VFQi/LDrecrlLGS3DLwzK+1TK+FfmiMYILXdDyGt4Q9Iv59TCvrBbVRfCoVF9VR6dTwlFnqFx5HxwLNThZGX2U8fdma3MOaPaKaG7gLLfLx5ruEWuXl9zUTq1ez3sNHg0aag/rXwRhT0ycE7bAam1yDlo2ssJWNwJRa08Yke8cLjVsMRtWvJ/anhJYUIlexh5K0fejIGOJblAyW2L+lNMD6eH6QyiMIzbu9FTX/OzKPxT/dJc8/1vYFRza8nBw0OG9t8u41rsMUl0xsOc2SV94JK/sELqn6Mjx0E4URY5StJUdgKNsaDAzasMEcM6BvDn9ed2FPw+l3TsXYff6Wp7AHufuocNnyR1JzEEiHEcPPxnh+Fm3+BQ6MzO3I8JFQjFbaBCnI/lNbH7xmQ3YUN2jIwtg02lq9fngELM2t/ug7WzPEtTrpZ2Xu8JuF9671j/pMXQO6Dpj8ZJeWndemTv84nlPdSPJ8Rbh/ec1ZC0c162VuZ/qzksRo9o4zzDW5ngMX/r9jn6IuvAyMZZ9tVY+zdnt/XFJeltFhnMvFKkf7stxvgr5QKPht/ByT+NgbbrbOd1T2N0I+bw5hc+G/iQ=
*/