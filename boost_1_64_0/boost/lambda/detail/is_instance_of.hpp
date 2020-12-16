// Boost Lambda Library - is_instance_of.hpp ---------------------

// Copyright (C) 2001 Jaakko Jarvi (jaakko.jarvi@cs.utu.fi)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org

// ---------------------------------------------------------------

#ifndef BOOST_LAMBDA_IS_INSTANCE_OF
#define BOOST_LAMBDA_IS_INSTANCE_OF

#include "boost/config.hpp" // for BOOST_STATIC_CONSTANT
#include "boost/type_traits/conversion_traits.hpp" // for is_convertible
#include "boost/preprocessor/enum_shifted_params.hpp"
#include "boost/preprocessor/repeat_2nd.hpp"

// is_instance_of --------------------------------
// 
// is_instance_of_n<A, B>::value is true, if type A is 
// an instantiation of a template B, or A derives from an instantiation 
// of template B
//
// n is the number of template arguments for B
// 
// Example:
// is_instance_of_2<std::istream, basic_stream>::value == true

// The original implementation was somewhat different, with different versions
// for different compilers. However, there was still a problem
// with gcc.3.0.2 and 3.0.3 compilers, which didn't think regard
// is_instance_of_N<...>::value was a constant.
// John Maddock suggested the way around this problem by building 
// is_instance_of templates using boost::is_convertible.
// Now we only have one version of is_instance_of templates, which delagate
// all the nasty compiler tricks to is_convertible. 

#define BOOST_LAMBDA_CLASS(z, N,A) BOOST_PP_COMMA_IF(N) class
#define BOOST_LAMBDA_CLASS_ARG(z, N,A) BOOST_PP_COMMA_IF(N) class A##N 
#define BOOST_LAMBDA_ARG(z, N,A) BOOST_PP_COMMA_IF(N) A##N 

#define BOOST_LAMBDA_CLASS_LIST(n, NAME) BOOST_PP_REPEAT(n, BOOST_LAMBDA_CLASS, NAME)

#define BOOST_LAMBDA_CLASS_ARG_LIST(n, NAME) BOOST_PP_REPEAT(n, BOOST_LAMBDA_CLASS_ARG, NAME)

#define BOOST_LAMBDA_ARG_LIST(n, NAME) BOOST_PP_REPEAT(n, BOOST_LAMBDA_ARG, NAME)

namespace boost {
namespace lambda {

#define BOOST_LAMBDA_IS_INSTANCE_OF_TEMPLATE(INDEX)                         \
                                                                            \
namespace detail {                                                          \
                                                                            \
template <template<BOOST_LAMBDA_CLASS_LIST(INDEX,T)> class F>               \
struct BOOST_PP_CAT(conversion_tester_,INDEX) {                             \
  template<BOOST_LAMBDA_CLASS_ARG_LIST(INDEX,A)>                            \
  BOOST_PP_CAT(conversion_tester_,INDEX)                                    \
    (const F<BOOST_LAMBDA_ARG_LIST(INDEX,A)>&);                             \
};                                                                          \
                                                                            \
} /* end detail */                                                          \
                                                                            \
template <class From, template <BOOST_LAMBDA_CLASS_LIST(INDEX,T)> class To> \
struct BOOST_PP_CAT(is_instance_of_,INDEX)                                  \
{                                                                           \
 private:                                                                   \
   typedef ::boost::is_convertible<                                         \
     From,                                                                  \
     BOOST_PP_CAT(detail::conversion_tester_,INDEX)<To>                     \
   > helper_type;                                                           \
                                                                            \
public:                                                                     \
  BOOST_STATIC_CONSTANT(bool, value = helper_type::value);                  \
};


#define BOOST_LAMBDA_HELPER(z, N, A) BOOST_LAMBDA_IS_INSTANCE_OF_TEMPLATE( BOOST_PP_INC(N) )

// Generate the traits for 1-4 argument templates

BOOST_PP_REPEAT_2ND(4,BOOST_LAMBDA_HELPER,FOO)

#undef BOOST_LAMBDA_HELPER
#undef BOOST_LAMBDA_IS_INSTANCE_OF_TEMPLATE
#undef BOOST_LAMBDA_CLASS
#undef BOOST_LAMBDA_ARG
#undef BOOST_LAMBDA_CLASS_ARG
#undef BOOST_LAMBDA_CLASS_LIST
#undef BOOST_LAMBDA_ARG_LIST
#undef BOOST_LAMBDA_CLASS_ARG_LIST

} // lambda
} // boost

#endif






/* is_instance_of.hpp
lAdQ1oGm+8P3TB6xxXXswHMPtv1x5bLFD2Idmrif2v9i0IrrF5Rd9s6JzKlXtSnHO764DxyWFfVh6vH4egUx5b/qfvJ5rCX1mO4bxs1NPRqw9OHr159Xvmvt7Tuw3iDIdHc8OLVl6+tP9I46GRUW8fSkd/GuL2s9vi+4pejVpC1PlxSc+P09cViyqR5zmfxvXvfWKz9+c9vxObe0aPJU6VWQ/TyR/5nbZt4ZX7p18t+a/LDxm7jzu6HncpvujT3Zg18ffnR6hzb3LJk359FvMAflMN0vic05MT9tSkfnNVOC5x3JeQtjHnF/+/YPX+mfM/W+BV/PnfRky0cQx++U6V7R/8qYorilpX+I7LO0XvnpTzGHI/JEvTCv9FSr1OduLh6y+abfP7EL5/qLPI/c93DyQpfzdP+sno/mf9AzE/kV96Olsas67cg/teCrh5694aEWj2HGzzDdC3ZPv+mbinavvHXHgJj4D3tBb4ucpvv9Y/7kanDT94+33PLXlnG/GdIPYyPR80ue87ald+v2x37ujr1nNr/U/M6lyDO30T0vvjgzavTu+69+urz9VT1wNr7o4alLhh4/dVGPt+468reXs4ws6PM+0X9CwsOjPn7z+8gR+66LGfGbmJ1Ypy96mNmifeyWJss2fzfnmcWvL/kKiz9WiZxXPrN+2MEfHxv8xaN3L6+/oc29Sp2Q/fZyyTxTGXAC6HveX69kbCT3t4C+ApXoOTOZtxS/BqBCxvMqv6n3Bvf7fwC8HPgh8ErgIWAK/UcB9wLzgO8AFwDfA94LPAB8AngQuBVYDtzG8JSD8ymY87GR47f8Zt3TwPOAW4Htgb8DXgzcBrwC+AdgGvB5YBZwO3Aq8AVgAfAl4EzgH3km5g7gBtOdcqTqeQvoinIEgYZSjmWU4y5+O+9uYB/gPcBk4HKgybuC+lgJzAWutpy9uZ3xBzJ+69mbn4sqUPbAAGAFw2WAdjNcb4Yz0x/FcPMp1/XAJpX6LIkGLgDGAW8AdgEuBHYD3sxvIN4E7GU+M501eiwOHTOdMMl35XUf01nDfN/PevEAz4F4EDgM+DDzv5blsQ6YAXwEOBn4KDAfuAE4G/gYcA7wceCvgE8CS4CbgE8BNwOfMd0pZ6J3vArsSDndoG6U8xPKeZj15QgwBvgpvwH5maW8UxjPepvyzgJfa+AU1rermd885i+f9b0AOB84i2vYirScHDsAu9vIOYrlPZprssYAo4BjWU6pjCfU4Dsn3/PL+P7i4tq6cH7jMgLYEtgUOAHYzHsWLPXegvK2ARYC27GdxgHX8BsaDwE7sJ3GA1/heR3lXHv3ATAF+D2wK9DJ8zka8nyOJjyfoyWwF7Afv6WRyPM5RgIvAebynI6beS5HGc/leBA4EPh74CDgu8DLgRXAK4CngH2ol0HedyO+15X5nI2bRv1OYHudyLNyM3jeRzr1lmFpn4mML8SmfRYzvjksr7kWOTIYrq+NHL9mfbwF2ABYCowA3so1kGVsT7cD8xxIr7dDJYJyQctBu0CnQAkX4e0etMykKxxqI2gnaD+esR1UxYAKQCWgXsMcajWwBLgctNUkPO8D7gTuBw260qEqgOF9HCoOlAwqgFsZaBTus0HluF8MXA7aBjoM8vTFcwrSA/YBDQWlgQpBpaD1oITh4AemAA8DlwFPAsP7OVQ8qA8oA3QY7iXATaDsEQ61HVgOqgDFXgKZQBkg10jED4wHlgJTgGWg1ZdAD6CdoOMgVyLkAsWDhoKyQYWgRaBloIdA20D7QMdNHAXdglxJSGs00gItBq0HxcItAbRzNHhAiUmQe4xD5QFLQMtB2/G8DbgPdBLk6W8uJnWoSFA3UAye40E=
*/