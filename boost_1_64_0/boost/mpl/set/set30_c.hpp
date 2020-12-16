
#ifndef BOOST_MPL_SET_SET30_C_HPP_INCLUDED
#define BOOST_MPL_SET_SET30_C_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/set/set20_c.hpp>
#   include <boost/mpl/set/set30.hpp>
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER set30_c.hpp
#   include <boost/mpl/set/aux_/include_preprocessed.hpp>

#else

#   include <boost/preprocessor/iterate.hpp>

namespace boost { namespace mpl {

#   define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(21, 30, <boost/mpl/set/aux_/numbered_c.hpp>))
#   include BOOST_PP_ITERATE()

}}

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS

#endif // BOOST_MPL_SET_SET30_C_HPP_INCLUDED

/* set30_c.hpp
/yqcX/+Ptf++QLfh+v8Fvn8Yvv9s8v0byPfHF4sfgO+99Fba/4+mRVVZm+eBr+3rxvSl0i1L4ldiAPONGMDGmOf5VK8DQ4SHBxib8jcTWcZzAeCG4zPV9A/32x8z/PZg0ej7w9fnjry8MHjPQwctWvTv99uXiN/22//uPfRP4jt88d+9h34p++EMBoPBYDAYDAbDYTi//j8Y7IkG//Pr/2O9xPp/21rYEyn+UCSIae3o4GhsjajXKIRRQDzh4lhawKv6rZhBLexrw0dfvuua8zyjL2zz+LvKdsGZjxw3+XrQ3JsNX/zqseKHZnQsqj33m4H17w8eKsSXqOseQdq2Nm0KG6bPuyBb573A6eAycAa4HLweuAK8IbgSnAmuBm8KrgFvBq4FTwXvC84GN4G3BDeDc8AHgqeDW8Azwa3g7cEHg3PBh4DzwG1gN/gwcD64ndqTUcg+MIPBYDAYDAaDwWA4hVT4/5HA/8H/Ry8T/P/LyP/fOkZg2m86Yvn/KBRbT5AZS9tvbmM1mhtLy46lNVY3H1zdOFfExQVaDT8/9+UHW96597b2jFsvjX5x2Jor/1hc4CJBbbK1NRN2Bn3ekeICbvCa4HzwWuDdwBngYvB64BLwBuDdwRuBZ4EzwWXgjcHl4E3BFeAp4ErwVHAVOBu8D3hL8L7gHPAccDp4Gvv9DAaDwWAwGAwGg+E4fmbvXMCarMI4fpiYqCslL0h5wUuW5QUUARVQBEzMkAAVC51jGzAFNndRUEvUzGuhlmZpiY+aWj5mBV1My9TKiizRUkuLRM1MzRRTnzT67/vezUGgIMOn8v0/z+vP8+3bzvnOdM/+73vOt9rx/6Zbwv+bKvH/bQXR/vsCm5z8v0n2+htxrLz/f3+T3f/HRT0YXdb/PyP5+dfP5y97oHjWhEYd1/h97v3VBzfu/2lMGGPl/t+P/H938v+B5P+DyP/3Iv/fm/x/H/L/YeT/+4PNyPe3cPL9keDd5Xy/D/gw+f8g9v8sFovFYrFYLBaL5XK5fv+/NS1Nqx9P+///1zkAulIkAa7mAHZSDiBVECkH8LV9D4D8JGkPwFn52GD4bKkt8uV2D2p3pbY/tbtRuye1e1C7uyibK9ghef/1B1YH3n7l99Fnhk66t2u9Y4U3livIdKOxO11TZ0QaDtDfs+17CWyHfEEFGAveBsZRziCecgZDaU/BMMoRDKc1Agm0p2AE5QoepbUBj1GOIJFyBCNpT4EW7ADqaE9BMu0pSKG9BHqwOzgG9AfHggFgGhgEpoO9wQwwGDSAoaAR7AdmgRHgRHAAOAkcBE4GB4OPg9HgE2AM+BQYD84Eh4GzwARwNpgIzgFHgfNAFfgMqAZzQA24BNSCL4A6cCnoDsZwLoTFYrFYLBaLxWK5SLXi/0269FvE/+NKK/b/VkEk/z86n/y//CTJv0/NL+v/c8r5/03l/P+2cv5/dyX+/0/Jzy+4srrVlM39FvmteL+T7vOoozfm/7PdaOxO19QFYanE/0eDdcEhYD0wBqwPPgLeDsaCnmAc2ASMB5uBQ0FvcBh4NzgcbAUmgG3AEWBbcDTYHlSD94JJ4AOgBuxG+QA/ygf0oHxATzAVDKS8QC/KC/ShvEAIaAH7glYwHBxP/n8COBDMJP+fRf5/Kvn+aWAsOJ38/5Pk+2eAj1I+YBTlA5LABWAyuBAcAz4LpoHPgRngInAc+DJoAnNBdzCV8wAsFovFYrFYLBarhqoV/49V7reI/8eVlvX/uZXcA8DXfg8A+UnSev9+FdwDYNA17gHQfYN0DwCP0+d2FyyZOmlGnVcfHRM79MZ8/RKEbxXuAeCKPQBNwXDQC4wAvcFI8C7wIbAlOBhsLew=
*/