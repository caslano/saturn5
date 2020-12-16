/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_CODOMAIN_TYPE_OF_HPP_JOFA_100829
#define BOOST_ICL_TYPE_TRAITS_CODOMAIN_TYPE_OF_HPP_JOFA_100829

#include <set>
#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/icl/type_traits/no_type.hpp>
#include <boost/icl/type_traits/is_container.hpp>

namespace boost{ namespace icl
{
    namespace detail
    {
        BOOST_MPL_HAS_XXX_TRAIT_DEF(codomain_type)
    }

    template <class Type>
    struct has_codomain_type 
      : mpl::bool_<detail::has_codomain_type<Type>::value>
    {};

    template <class Type, bool has_codomain_type, bool is_std_set> 
    struct get_codomain_type;

    template <class Type>
    struct get_codomain_type<Type, false, false>
    {
        typedef no_type type;
    };

    template <class Type, bool is_std_set>
    struct get_codomain_type<Type, true, is_std_set>
    {
        typedef typename Type::codomain_type type;
    };

    template <class Type>
    struct get_codomain_type<Type, false, true>
    {
        typedef typename Type::value_type type;
    };

    template <class Type>
    struct codomain_type_of
    {
        typedef typename 
            get_codomain_type< Type
                             , has_codomain_type<Type>::value
                             , is_std_set<Type>::value
                             >::type type;
    };

}} // namespace boost icl

#endif



/* codomain_type_of.hpp
5ZKZ2dQIwqai1EWTSJPGaBIhRYTqzAckow0DhDSVyqdaoTrj9NAv7V2xTU2NTRizMaZWbBMeqnluYjZTU7jNP5cytdcoIhqdhraWxu43qugfknunpKb16dsv/e7+GQMGDsq8Z3BW9pChw4aPuNecY7GKuXn5tjFj7Q6nyz3O4/UVFI4vKp4QHRMbF5/Q5c7Ernd0Jpau8XT60rVr310rl077d3td+/7aXYp9t+49eoJDEgwhoWE1brgxPKJmrZturl3HWPeWevUjG9zasNE1Od3W+PYmTZsJzVu0bNW6Tdt27Tvc0TGqU2fJFVlM1UxVnjfySoLVmiNU1uDV/ekGcpHfumkfXNmF7nIvA+ba3F7+qj+m8k3sx/fVzg+eVOf3OsoPWKN65UivYyhTnj17CjHCxImVyROrkMdoTt/K/JDnV5Vfl5tSsoebbIUmJcBSRNvrRhm9VjXyzbFX59c1Onb+/lHgFkHp59qcZnuAb6JX+iE0WyaZv+rgX/+GL5OrnmuvyEAJuP8Hb+w3bur3TzTLyHCZu5jr8ndOdN814TLVwsz6WkRSS5elbO1TUUAI5JYQuE611ZYrv+ngkyslrWHr1fDLrx0nu8rftxOks0FgZ4O8doZokflmp5DvMJe9T6KVebxmJtLKBGs+k2j5zETLF1WF2Ox2Mc9sF7zSYdNxnr8zMsFc/n0Z+ZUgJaRcS7QGrrejrq2a7z8kjM9Wq+G/o1T/5tpuc9ikF5csomgVrXq/w1Leeiqw27nMl+/SbzrkdAms2eF4yDRvnVzud41xK1rXW34X1Zdvk08ItpYyS9wGJvrhIQRaYtmL5Z9s2c1uN44N+3m5l+uoXjxQ1tJi8deRi04duf9tGXghtSAi8v+mnsUukOdys4Oi4rlzRO3L/Or1uyuTsWCX58Mpfl5pZay+cuXgi+pVI31ducMqL+PvSsnLa0lvlnn1dNyeXB1eWVwrrZvXbPcJqgMv/SBKbutyuHFwXePFwHXN5e40oFtR9atOW9lbKmW8Mg6nXRb+poZfxxfvV+M8yRe1IuqhepEwsH/WFEvlRrP8r8mSxWG3awu0ojycmnEBhbKkrGqOJu4vluSrpKyVDh5b8BxJc/WUunldPpzR43tF2SN2yVXlmapck/pIwUdpWv4QtxVHW60vnxflfUtzavPhfP18BqSW1YOrc77cZDktrZshlcbpzN5pJhwv/u6tlmdiTU4tU8UzkC/362pe/5SsxFj2phvngYqVBYE8xXP1JSFQrjoa+nz+bq5WZi1wB/DYTYMejzcbXZnLbtX6xBb20+PxrPRkcuORvj1RTi4qB1fLU/umI9P3LU/0RZtS++nwspL1dNnnCPTzkW4W9PiDy+elXFz1ePoxcYrj1bR6EUQ9Ps9FLeOLJKppPT22sqMej2vryjy4HmK3Mlk5+yy4IJ+8jB4qq3MOf0e7iFVfeY8kQT6LECxbIQsA5xfGakRaGV7xifWLNXJ2YgbK+RqTaIz8JMcIiMlhzrNZTD6X6kV+8HmvXL1nKGRbxTOUEyrq34hKAc3A6zLZ/ahyO1uh2ix9KLMK7pmR/Qq2mmM9lrIHJ33dMbq66hRByrxMKBG5+pORkGoyXpiKl8rG05JUvDTVWMG9kVQ2RlGD6YXlKrxFkm8a3l+JqKOGt5iI7tDwHiGi1hreEiLK0fBWqnz5NVHhrWM+q+u2nvHUddvA6svrZiCi1Sy/JFKSxGsSqvDCVLymjLc6xM9rxngrVDyB8VaqeM0Zb5WK14Hx2of6eZ8w3ocq3knG+4jxQnSOh8Q7FOrnfRp7/ePKwaTqtHN3TuDATPaIzLSe1bXVnMQGA9E8A5VV7sgDGC8EhIlsfJY=
*/