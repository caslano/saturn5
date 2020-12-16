
#ifndef BOOST_MPL_AUX_PREPROCESSOR_DEFAULT_PARAMS_HPP_INCLUDED
#define BOOST_MPL_AUX_PREPROCESSOR_DEFAULT_PARAMS_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/preprocessor.hpp>

// BOOST_MPL_PP_DEFAULT_PARAMS(0,T,int): <nothing>
// BOOST_MPL_PP_DEFAULT_PARAMS(1,T,int): T1 = int
// BOOST_MPL_PP_DEFAULT_PARAMS(2,T,int): T1 = int, T2 = int
// BOOST_MPL_PP_DEFAULT_PARAMS(n,T,int): T1 = int, T2 = int, .., Tn = int

#if !defined(BOOST_MPL_CFG_NO_OWN_PP_PRIMITIVES)

#   include <boost/preprocessor/cat.hpp>

#   define BOOST_MPL_PP_DEFAULT_PARAMS(n,p,v) \
    BOOST_PP_CAT(BOOST_MPL_PP_DEFAULT_PARAMS_,n)(p,v) \
    /**/
    
#   define BOOST_MPL_PP_DEFAULT_PARAMS_0(p,v)
#   define BOOST_MPL_PP_DEFAULT_PARAMS_1(p,v) p##1=v
#   define BOOST_MPL_PP_DEFAULT_PARAMS_2(p,v) p##1=v,p##2=v
#   define BOOST_MPL_PP_DEFAULT_PARAMS_3(p,v) p##1=v,p##2=v,p##3=v
#   define BOOST_MPL_PP_DEFAULT_PARAMS_4(p,v) p##1=v,p##2=v,p##3=v,p##4=v
#   define BOOST_MPL_PP_DEFAULT_PARAMS_5(p,v) p##1=v,p##2=v,p##3=v,p##4=v,p##5=v
#   define BOOST_MPL_PP_DEFAULT_PARAMS_6(p,v) p##1=v,p##2=v,p##3=v,p##4=v,p##5=v,p##6=v
#   define BOOST_MPL_PP_DEFAULT_PARAMS_7(p,v) p##1=v,p##2=v,p##3=v,p##4=v,p##5=v,p##6=v,p##7=v
#   define BOOST_MPL_PP_DEFAULT_PARAMS_8(p,v) p##1=v,p##2=v,p##3=v,p##4=v,p##5=v,p##6=v,p##7=v,p##8=v
#   define BOOST_MPL_PP_DEFAULT_PARAMS_9(p,v) p##1=v,p##2=v,p##3=v,p##4=v,p##5=v,p##6=v,p##7=v,p##8=v,p##9=v

#else

#   include <boost/preprocessor/tuple/elem.hpp>
#   include <boost/preprocessor/comma_if.hpp>
#   include <boost/preprocessor/repeat.hpp>
#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/cat.hpp>

#   define BOOST_MPL_PP_AUX_DEFAULT_PARAM_FUNC(unused, i, pv) \
    BOOST_PP_COMMA_IF(i) \
    BOOST_PP_CAT( BOOST_PP_TUPLE_ELEM(2,0,pv), BOOST_PP_INC(i) ) \
        = BOOST_PP_TUPLE_ELEM(2,1,pv) \
    /**/

#   define BOOST_MPL_PP_DEFAULT_PARAMS(n, param, value) \
    BOOST_PP_REPEAT( \
          n \
        , BOOST_MPL_PP_AUX_DEFAULT_PARAM_FUNC \
        , (param,value) \
        ) \
    /**/

#endif

#endif // BOOST_MPL_AUX_PREPROCESSOR_DEFAULT_PARAMS_HPP_INCLUDED

/* default_params.hpp
pNRVVOWS8mBY3dV9zMT8AkeR9/dDJX5QWFJeXFThOaAlrUmnHb4gAPbZicQW4C5otKP8MO3IHc98A7vT3ZYq6z2gtCXc0pbpFfmldjnO0g5LvRrXDl+7ZS3Bq9lj0PP7pXZvfOSA7DvoHGirtw+iU/Y5POg9RtkH0ZlQf99CZ5xx7lad1vFdx7ViTT/Y6weuixy3Xn4v1xUv+yt68wPd+Q2+fJw7v82XTzC+A592tWjP3Wdqr1W0P1W01ynaW/1o7xbtV380tdco2rsU7fsU7S1+tDOC0IY99pvaqxXtnYp2jaK92Y92jWg7D5jaNyvaOxTtVYp2rR/tg2iPgi/9bGpXK9rbFe1livZGRdu6ZuZ8bm7DsrvxfwPMgit4pjJt9WOJw7nJpxeVup+jHX/x/4QQy7NUkT/XWE7TjCsGmff4QeWZOKA8E/uUZ6BOeQaC+H8i8XjG23DBgoJoh+huUK7bHuW6bVSu23b1OxHtZWiPRnTicab2uiM8X+sb8XwZ2ntE+6fjTe37jvB8rW3E82Voj2hNQnRkG1O75gjP15pGPF9/sHcvcFFUewDHV8VEEzVFREVFRUXFEiXBNyoqvlHx/eC5KIqwsouCmo80n6RoWPgM85GvEhUVy1daqeUtb3nL0gqfqVmSYVF56/5m97/ssLEJN/J27935dPoy69mZc2Zmd+f8z5kZZdkGZdm8fqu8ZdnJqveq86ZL3mkVLHkX2sh7RvJWeNSSd56NvHmSN1GVd7aNvB4cpP153bGiJe8MG3mDJO96Vd5EG3lnSN6pTpa8Bht5t0pep0qWvDobec9J3o2qvDE28mrKm/LWqGzJO95GXi/J+4oqb6SNvMMlb7cqlryhNvJmljcdazMes+RNe8D37doifN8qy65SwbTsM1Uty055wPdtahG+b5Vld6hgqmOos2XZo23Ucbzk/V6Vd7iNvKmSN7m6JW+wjbzHJG+UiyVvkI28tyXvfVXevjbyuj5qyruihiVvoI28AZLX09WSN8BGXp3kLV3TktffRt61kjdNlbeDjbynJG98LUtePxt5cyVvn9qWvD428rpXNOW9pMrb0kbevpJ3qpslr5eNvImS16mOJa+nVV71eNAAJxvn5Y2sfntj/9rn5WnSs3hZzss/M5+X/6Yef855+R+px8M6Lw904niuZDqXc2/iWKLn5cqyPSqbzkHjPR1L9LxcWfZsWfbbTR1L9LxcWfZFWXat5o4lel6uLNuvimnZsV6OJXperiw7VZZ9vIVjiZ6X5zIfqin+8+JtPf99i7GfvcrNPS8MurN/oHefrGePdPULMY/LlhgAdiUFWo2TrkWXuRPWxk5YB+8ibzC1uaUtHoh1SLnyvq9LaWZXwjvYGL/FOXgXs/E77MSbc3Edfo/bMQ/34o9YjoL8hKP4vP6Mu8ryG4dlqOc/cZgj9wjAbeVZIOXajaVwPzriUSyPX2EFLM3v5KNYEytiT3TCvlgZh2AV3IRVMQeroT/1c8YUrI7Z6CLb4XxpaSdJ+ykQh5PO8LoydaF8ThiAE7E7/g174OO8qSemYC/ZDr3xV+yDYSyjL07AfjgX++NaHIAbMAjLsJ0GohYHYyYOQ+P5Gg7jeBmJW3AU0ozUjMZebJcQHIqhuBrD8DqGYzPqH4FTMBJfQy0+Qv2j0BPHoQHHYxZGYwW+lCdgf5yI6RiDVzEWm7BB4jAJdXgYJ2NlDph4HIx63IwGPIkJWJPviSk4BqfiLkzE7zAJu1ehPYGLcAY+h09hGs7EizgLvZQbSuIMflzm4Bl+P+ZiFX4c5mE4PoNbcD7m4QLsQDxtIS7FRfgBLkEXF35rcDw+iztxKf6Cy7BrDdqLmIrL8Tw=
*/