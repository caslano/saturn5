
#ifndef BOOST_MPL_AUX_CONFIG_TTP_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_TTP_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/gcc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if !defined(BOOST_MPL_CFG_NO_TEMPLATE_TEMPLATE_PARAMETERS) \
    && ( defined(BOOST_NO_TEMPLATE_TEMPLATES) \
      || BOOST_WORKAROUND( __BORLANDC__, BOOST_TESTED_AT( 0x590) ) \
       )

#   define BOOST_MPL_CFG_NO_TEMPLATE_TEMPLATE_PARAMETERS

#endif


#if    !defined(BOOST_MPL_CFG_EXTENDED_TEMPLATE_PARAMETERS_MATCHING) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && (   BOOST_WORKAROUND(BOOST_MPL_CFG_GCC, BOOST_TESTED_AT(0x0302)) \
        || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610)) \
        )

#   define BOOST_MPL_CFG_EXTENDED_TEMPLATE_PARAMETERS_MATCHING

#endif

#endif // BOOST_MPL_AUX_CONFIG_TTP_HPP_INCLUDED

/* ttp.hpp
Z8ay5bx/31z22GS2ksjmbV9YsZwdj23o32g7TnJcghiGhMYjlXJO32ah+cLlN1HcZhdMjlqZkVqXSlaKrAG+8NK2bGxiNIdwKSK6rrcJl1OZ7KQ9VC1Ip4GfYi4tVae/t1EaqFrFVDGH6lXGoTf3JTRRGeuWkqZfX1gKTuXAKJ7MjYfSttPVpm0XinFU02Rlomz77TJSf0OZPM5pJ5NsN8JKxZK7ncojvIL4jrb/5Fn3nGX51IdJw4FTpzgW8IehdieHbWTJiFMpJwtOMlUt7LQRx7ELabs8WCywPSBHWaSypSzSYpAelkyno1MVu+DwuOhhNsp7uoTTJjYU0zjKrzHPlZMgj81WCrZj+kKDyKZBZzxRa/mcRBXkaWjE5/H0M56QDKhxxC9Px1AYbILJ5YANZAvbhpOFdJGnlhnGzPvDeOJJ/sOplF2qJFmMtCkWQiW77BQLyVwvDluNo4mS42gPjfVky5WMj5dyyZQvgHy8egxr20h7AleP6aGxSLaSfQqOUybLlqSBDVoo1CnfMU6mkuocrjtHGQ6lsM/9rI3+sFQGFzOUoy+UYeO4LJW0bVzkam3Z9pQj5/3UoyPx6UIlORWabPfKNIXGjGer2kbjxbLzMX+bm0yPVNDy4VzLl9SxDfdaCTArTuiyEblMMY5Vu+6PJp1saigSj/ndBnqEWxJg+ULU+VIN0U6eSDmHhoocVdhis5V0a8dozlZuHDePNe5PRNWzQjGSsaUr4KVlKZJ0W84IegdjYyqczalFKgsu0JPoCAwUVUutbONugKVCuNhy1qdxga02XC6Lkrm5ZAiXSnnCqQwXi3JiJmTd4gaWspP0taCbV7S1oZHERamSydNDOotmCOlPW8ypY4UsnxHzPLw+UCyPB3qHegPpYjrQHx4MC88mC0mfH6z3auv58Xw1NxthN17toqn9xLmZle1kzt1H/3apnJ3EOeo+1+2uszzRl2CFj6t14YV8abIDbHBjDL9IL5sTDod2Gc7UUY0a2+lUcfTJyK27PlRb741gu5hPZguRYh61ghknQzh/HTuHGDbOtAp6paPoD4YqXrcJ+WG4FVbhVkIPT+XsZJkN13A8HNrY21Xl+XQXGr0MULTa3PMyxfos196paXWuoTck2ZYWBFXaayfjLrckoJyvtjIWDfT2Ai2TZM6FqrEoFdF5mI7gdMClLet2rFmHVk92WrFqsFUf7naytRT98cIRK6G64TzHhu3J8CSPlrKTMw28mGKmJVzOU7FgGeDSGNq8OrSyw90OD8b7rc2rl6vtklSmEDrlOfdyLA1mEgcCR76SxfV6R9ELZFnYKbfLxL4MfbSv7mAb6W13GNud2nZH52rae9sd/m2//YqVyt5OpZ1kaAcOeyjeF3YhzvjBJHuVG7OpctEpjlUsUEsw9z0aD7V3dIeikR63bGxHtrFDo77t1GjKZz+0zm9fHBv1hUeM8JQWjt3W05NtpudtMz1lz/S88KLhL2KE6+mhmPT0ZJvpedtMT9kzPS+8aPhjel58hmfQ6+2Xij0hHTo0AGm3oPvALS3AYkiDOLgqNYnDkEbpJHO5fseZ4JCuQVyxsGjS2MewzQasYXwtNM2regmNwUQqFyhlc3LZcH9rbZU0VYB13O08AHthbtMZyWH4VGPrpSfCsX14RRyRC+Na1FQSncTxQrFs95uhpl9vO1bt0rEdlC6WapdTE+rqgn57XmdxnPWqxS2vi3R3dOTQsuQwAmTcwTibc7bvKMZcEo22lvYYXBTSuemI26lz210ZFtrqKkRjX97L48lC9ilsBz3eGw/L+vaJZA4RB5Kjdi5np2sdrU3ot0w4MrHgziXgClBMIzfDMjuh9eHzbDU=
*/