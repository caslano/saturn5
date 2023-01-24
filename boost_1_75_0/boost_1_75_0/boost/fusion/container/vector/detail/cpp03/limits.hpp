/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VECTOR_LIMITS_07072005_1246)
#define FUSION_VECTOR_LIMITS_07072005_1246

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/pp_round.hpp>
#include <boost/preprocessor/stringize.hpp>

#if !defined(FUSION_MAX_VECTOR_SIZE)
# define FUSION_MAX_VECTOR_SIZE 10
#else
# if FUSION_MAX_VECTOR_SIZE < 3
#   undef FUSION_MAX_VECTOR_SIZE
#   define FUSION_MAX_VECTOR_SIZE 10
# endif
#endif

#define FUSION_MAX_VECTOR_SIZE_STR BOOST_PP_STRINGIZE(BOOST_FUSION_PP_ROUND_UP(FUSION_MAX_VECTOR_SIZE))

#endif

/* limits.hpp
3qa5k9xVYuWmC9UxU/zNEGtqCZdMaAeMFj9phw4VJROVPWO11Fvbx1oaSSmWEp396EzOWhJ2JMBEo6/uIdV/C+96Y1cWXe+feANKJAlNSiTLHuY28CfouZD/nvMwmrov5a/b8OdEep1PjxH0uJEegwFUuavzMZWHGWBrkcL66WQrfAUVSaTHxVhyMJQEwtYSC9UqEbztvx+i57MroVgHVmzFRriXpHz/UJTI/d6UneCx45ock8DtBHTv5kS2/H2KSuc4jO9lwFq+OockmAzhUoOn7iftZS0sJMEA2kQbJZgVQoJZNodUBLzi5qMlyA5xsHHyLVnDvWhKEdGjukE1pXw7cuTnosnLUaR7HYzl/HH1KtyM63h5orweu4t8KRKVD9j3YHFO+Un3naojahbtPYbBp2eiJl7A1ZlL5uhuojdGGdWZRHAU7eIiNbxA8xLtCSluYlyk0SQyPPdYKWseHDomaSROgtGjyVOi/b7CuZUTepDxsYvzmPCJqosPLz6hroJ2NIYYI+eQzbNEAj0vEwy/jk6nW+AuxAl54fxq71k30XNhUANHblK5FCR1qVDP5Eg0URYIBohFtW584jFwvwbeis2sWwFVx0o3yR31R2N122DsE8dUqFXwr4aQWmE+8Aj6ZvA55oo4dOZbVn4zUB7/4IzCtAXdiuxZbNWIVEPp6eoK8KmGohApkZWY7o6ybwratD6u5H1cw2di
*/