
// Copyright Aleksey Gurtovoy 2000-2006
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION!

#include <boost/mpl/integral_c_tag.hpp>
#include <boost/mpl/aux_/static_cast.hpp>
#include <boost/mpl/aux_/nttp_decl.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#include <boost/preprocessor/cat.hpp>

#if !defined(AUX_WRAPPER_NAME)
#   define AUX_WRAPPER_NAME BOOST_PP_CAT(AUX_WRAPPER_VALUE_TYPE,_)
#endif

#if !defined(AUX_WRAPPER_PARAMS)
#   define AUX_WRAPPER_PARAMS(N) BOOST_MPL_AUX_NTTP_DECL(AUX_WRAPPER_VALUE_TYPE, N)
#endif

#if !defined(AUX_WRAPPER_INST)
#   if BOOST_WORKAROUND(__MWERKS__, <= 0x2407)
#       define AUX_WRAPPER_INST(value) AUX_WRAPPER_NAME< value >
#   else 
#       define AUX_WRAPPER_INST(value) BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE::AUX_WRAPPER_NAME< value >
#   endif
#endif

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN

template< AUX_WRAPPER_PARAMS(N) >
struct AUX_WRAPPER_NAME
{
    BOOST_STATIC_CONSTANT(AUX_WRAPPER_VALUE_TYPE, value = N);
// agurt, 08/mar/03: SGI MIPSpro C++ workaround, have to #ifdef because some 
// other compilers (e.g. MSVC) are not particulary happy about it
#if BOOST_WORKAROUND(__EDG_VERSION__, <= 238)
    typedef struct AUX_WRAPPER_NAME type;
#else
    typedef AUX_WRAPPER_NAME type;
#endif
    typedef AUX_WRAPPER_VALUE_TYPE value_type;
    typedef integral_c_tag tag;

// have to #ifdef here: some compilers don't like the 'N + 1' form (MSVC),
// while some other don't like 'value + 1' (Borland), and some don't like
// either
#if BOOST_WORKAROUND(__EDG_VERSION__, <= 243)
 private:
    BOOST_STATIC_CONSTANT(AUX_WRAPPER_VALUE_TYPE, next_value = BOOST_MPL_AUX_STATIC_CAST(AUX_WRAPPER_VALUE_TYPE, (N + 1)));
    BOOST_STATIC_CONSTANT(AUX_WRAPPER_VALUE_TYPE, prior_value = BOOST_MPL_AUX_STATIC_CAST(AUX_WRAPPER_VALUE_TYPE, (N - 1)));
 public:
    typedef AUX_WRAPPER_INST(next_value) next;
    typedef AUX_WRAPPER_INST(prior_value) prior;
#elif BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x561)) \
    || BOOST_WORKAROUND(__IBMCPP__, BOOST_TESTED_AT(502)) \
    || (BOOST_WORKAROUND(__HP_aCC, <= 53800) && (BOOST_WORKAROUND(__hpxstd98, != 1)))
    typedef AUX_WRAPPER_INST( BOOST_MPL_AUX_STATIC_CAST(AUX_WRAPPER_VALUE_TYPE, (N + 1)) ) next;
    typedef AUX_WRAPPER_INST( BOOST_MPL_AUX_STATIC_CAST(AUX_WRAPPER_VALUE_TYPE, (N - 1)) ) prior;
#else
    typedef AUX_WRAPPER_INST( BOOST_MPL_AUX_STATIC_CAST(AUX_WRAPPER_VALUE_TYPE, (value + 1)) ) next;
    typedef AUX_WRAPPER_INST( BOOST_MPL_AUX_STATIC_CAST(AUX_WRAPPER_VALUE_TYPE, (value - 1)) ) prior;
#endif

    // enables uniform function call syntax for families of overloaded 
    // functions that return objects of both arithmetic ('int', 'long',
    // 'double', etc.) and wrapped integral types (for an example, see 
    // "mpl/example/power.cpp")
    BOOST_CONSTEXPR operator AUX_WRAPPER_VALUE_TYPE() const { return static_cast<AUX_WRAPPER_VALUE_TYPE>(this->value); } 
};

#if !defined(BOOST_NO_INCLASS_MEMBER_INITIALIZATION)
template< AUX_WRAPPER_PARAMS(N) >
AUX_WRAPPER_VALUE_TYPE const AUX_WRAPPER_INST(N)::value;
#endif

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE

#undef AUX_WRAPPER_NAME
#undef AUX_WRAPPER_PARAMS
#undef AUX_WRAPPER_INST
#undef AUX_WRAPPER_VALUE_TYPE

/* integral_wrapper.hpp
bwT/kfCvBP8D8P8A/6fwvwL/cfAvA/988HeBvzv8a8F/AfxrwN8V/l3gfxv+heC/Gf5t4B8M/0nwbwr/qvCfCv+O8D8J/4XwzwP/ePhfg/+38N8J/3nw/w7+R+DfCv4F4L8J/q/h/yv8R8P/e/hXg39++M+G/wj4B8F/K/zj4O8M/43w/xH+EfC/B//j8DfAfw7868I/F/yHw38t/MvCfzr8Q+C/Df6H4X8C/hfgPwv+l+DvDf9X8D8H/9Xw7wB/a/ivh/8E+JeCf2f4P4R/Hfjr4N8c/iXgfwr+XeHfGv4B8LeDvxP8G8O/AvwPwf8u/NfA/zr8Y+B/DP714H8U/svhHwn/y/B/Dv998K8N/2bw3wv/cvBvC/8Z8LeA/2/wvwP/3fAfC/8N8O8N/27wfwH/5vAvDP8KjWgAwH8e/N/B/zb8XeEfC/8j8LeE/134V4Z/HfgHwn8N/Ld40gCA/yf414C/12QaAPA/bUUDoCANAPiHw78L/HfAXwf/G/A/pKcB8IIGAPy7w38z/G/CfwL81SNoAMD/OvyLwr8z/H3gHwz/gfCPh78t/NvA3xP+17rQAIB/DPzbw78U/P3gnwL/9fDfD/968K8I/53wt4J/Ifgfh/8Q+OfsSAMA/pfgbwP/2vD/Bf7V4f/chgYA/F/BPwH+/eA/CP4R8C8N/6vwbwL/e/D3hf8+axoA8PeG/yz4b4d/M/hfhL8B/onwLwL/ZPgPh38L+I+V/MN/NPyrwD8f/HvCPy/8x7nTAIB/Nfg7hNIAgH8vFxoA8M8N/27raADAfw78d8H/CvwHwz//LRoA8J8P/zLwLwb/XPBPgv8GJxoA8H8Kfz38Z8N/FPwt4B8N/xD4v0+iAQD/svB/DP878K/ZggYA/GfC/wD828F/K/zfwr8S/H+C/1p7GgDw312FBgD8o+A/Hf4P4P8B/qnwHwF/N/i3hX99+B+G/xn4v4T/UPhvhP9K+DeEf9wAGgDwHwn/yfC/AP8G8N8L/z7wPwH/s/AvB/8V8Hc20ACAfyP4l4d/j0c0ABJoAMB/BvzT4L8N/gXhf78dDQD4/wz/1fBfDP+m8F8C/4U6GgDwHwP/qW40AOBvDf9H8D8K/2nw7wD/J/BffocGAPxPwn8A/KvCXwP/vhY0AOA/Hv554N8f/pfh7wj/c/A/D/8F8H+TQgMA/svgHwD/4vBvDf9TfjQA4O8E/4Pwfw3/j/B3h78H/H+Ffyj8XeC/CP4l4H8L/o3TaADAfyn87eC/Dv5d4f87/GvBPwz+m7rkGnDWte6S+jubLfop/vn598NvNxgzp0ba+NrftvTYd+3B777Dptf6ZU9Z9z+8ZuRp8W5vR9vqC0IqXnRZG9trYdvwpJPlot+8Cv4mdFahM4t7H+mj2fBdWFQb74+PN1/qW7BVt79Mnjd26oW/qiZtO5379Z3uNpt+88xxomrJKYebOlju/nW7lUWBiQMbTsvXvFP/Kw9nPjt+LHXdvZgfVujK3F9ZZ9ytt/UMxfXXI1o/LTqoRKX9iZEbA/Mud95R7EPXJu0PnBqi/vHyrk9xR3u+KHV1qduEnAdrrsnv2KPC6Ef+/TqPWlZkfTv7aneH/vz9oblP5t9o1GFV5Zerk1O2Nk7wmR1QuIr1yC2Dz5W/qXUK8ittNwJyFvxZ8mfNny1/jvyp+WsmHY75K8ZfXZUSlKAEJShBCf/HoTr/ehvjSFWUSqOKUMXwL0xVTVWTVOnPVRXC0CBVtGoIOXSqSPoCyBlj6vozNJLhGnIHZTsfLdNVq8rzT01OvUpn6hvIWEP+7cujYXigWJrsQ0VVc5WnyoecnqqOqpaqLqoeKm+VL8vjzj+1NF/GrcSn4fw=
*/