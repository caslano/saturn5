/*-----------------------------------------------------------------------------+
Copyright (c) 2007-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TO_STRING_HPP_JOFA_080416
#define BOOST_ICL_TYPE_TO_STRING_HPP_JOFA_080416

#include <stdio.h>
#include <string>
#include <sstream>

#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_float.hpp>
#include <boost/mpl/if.hpp>

namespace boost{ namespace icl
{
    //--------------------------------------------------------------------------
    template<class Type>
    struct type_to_string
    {
        /** Convert the type to it's typestring */
        static std::string apply();
    };


    //--------------------------------------------------------------------------
    template<>inline std::string type_to_string<bool>::apply() { return "bool"; }
    template<>inline std::string type_to_string<char>::apply() { return "char"; }
    template<>inline std::string type_to_string<short>::apply(){ return "short"; }
    template<>inline std::string type_to_string<int>::apply()  { return "int"; }
    template<>inline std::string type_to_string<long>::apply() { return "long"; }
    template<>inline std::string type_to_string<long long>::apply(){ return "Long"; }

    template<>inline std::string type_to_string<unsigned char>::apply(){ return "char+"; }
    template<>inline std::string type_to_string<unsigned short>::apply(){ return "short+"; }
    template<>inline std::string type_to_string<unsigned int>::apply()  { return "int+"; }
    template<>inline std::string type_to_string<unsigned long>::apply() { return "long+"; }
    template<>inline std::string type_to_string<unsigned long long>::apply(){ return "Long+"; }

    template<>inline std::string type_to_string<float>::apply() { return "flt"; }
    template<>inline std::string type_to_string<double>::apply() { return "dbl"; }

    //-------------------------------------------------------------------------
    template<template<class> class Templ>
    struct unary_template_to_string
    {
        static std::string apply();
    };

    template <template<class>class Unary, class Type>
    struct type_to_string<Unary<Type> >
    {
        static std::string to_string()
        { 
            return unary_template_to_string<Unary>::apply()+"<"+type_to_string<Type>::apply()+">"; 
        }
    };

    // ---------------------------------------------------------------------------
    template<template<class,class>class Templ>
    struct binary_template_to_string
    {
        static std::string apply();
    };

    template <template<class Type1, class Type2>class Binary, class Type1, class Type2>
    struct type_to_string<Binary<Type1, Type2> >
    {
        static std::string apply()
        { 
            return binary_template_to_string<Binary>::apply()+
                "<"+type_to_string<Type1>::apply()+","+type_to_string<Type2>::apply()+">"; 
        }
    };

    // ---------------------------------------------------------------------------
    template<>
    struct type_to_string<std::string>
    {
        static std::string apply() { return "string"; }
    };

}} // namespace boost icl

#endif



/* type_to_string.hpp
lcZ6pqLzOn1r9Z2or66Yb8I+kx95sfJ5IPnh+SvEvzv9Bof/d0K82FDcVj44r5cHh/jufPq37cUO/ltg7ZfC92r6prp+uutD2HFMTs9PkRfsOsOYV11far1q+lcWq7Fsm9NN7piTTlZDOnn5aor+6yfI9fAdphwaav4Y485T8ytCTdGe4/wOtvwaZ60s+vPvb/zxghzoy5Yrwvf41p8bvj8zvz39S605Q/yS6tQ9dvXrxH4+naQG1mhPc6/6sTv72DLU9WOt2ISzC+1hPnmZjJZJ/NqerCHWLlHjXesnJlvCdzIt2ZTpewNzZmXJ0Xr+dPwom5r2kcvhd77wu3GiuEwiz3qZcuHuZP5LM5e818Lv2Pbp4vAZq0HesPFNdi1k39gJfFVmj+gbZv419C7ltxl0bx1+t0N0pH2EvWL5IFlPlciTUeTyeQp/5ufbF3HqPPl1+iu0/XuRJ3+30mFk+H09z54eKf5hv4Z7NB13yIsm/ekuVuHfp+rQmWx6F3al6wj1gA8+DN8zJdBBjN/X7h9p3Tq6R/FT+IxDz9V0jqrk2yo6p7hurescn5Zu35LxNdsmD5Tjhfac+JzTmz+L1Fl7Ym6x3K3xfNVSjeLfVvb5HmvvdLwuyf2LvjeT0YyMq3L5iX1Hwm+05WrMEP05bCD3x+n2bwV/tvz/y4bXkf9dtXzOIVdM8tqbb8yxfuxid/iL3VlsT2/gO7rN5+dMfXfzWQv5tEDM3+WP13P5XI2eF74nMmaQ/l6hJg3RJ38u5+dTnPdL1W+dh+Vxu+FsrmZ/lvqGDV35agI9yPgnzx4w5s6OoOtm+fRDAv372L/0OJgiz0+nVzX9rdHX3Juwgs8GWv8PsXzMvLflbUI52aeRW2m9sfwVK0Y9yGHD8+ZvZ+ub9Ku27r/kLyTnvAq+0E7vTQad3qBLf3KiyU3GafoWhO+zxrvG/rWutx4mB8TyFWssdtw3R97Lq5baAXS5mLyu4XNBiniH74Osl9hKPXG8Urye1D8uPH/FiWWiPOsmTvRv3olL9V0in87MILPM3sx2Pwt13toH5dyrnehU6Z6jvU4e1E5SP5DqfKz+Z2vVIkSL7fLwjNqdPjnaEezrqA6PpUOUMWI7bwL5dMqwXg6iYjw/u5bfiixxmkjmArIbprCR799i4/F8cT+ZJ7jes16u8W/xYLaFfwyOXbe0llPhN+U8NTZ8f4CPXJvCp03j2TFJXwwb7JW/6JWdKNc7ihkyQg5ksUtfN/6eRW7brvyXLpdr+Fdst9fz3Rh7yrifyPwNtXxzSI5cpH1f/8aQW+bcEr4fEueCOPkz1h4rIxt9Q41k/+P0XVDhfjLdHPPeqGEHmz8wfrV9/MRocsOztjmt+XIuGb3C7wfaolS+HsOmYfRq757bUX5qV/XTr+/KOjL5bZM47w21HPeP5xN2L1CvYl2fKX49wjsmzps7/ipajMxpUqcvU92m41Ny408+/8W8e8WlT3gGlht/G3+Eve0SPQfE8ZO+evssOdL64beZaWpRqAGZfCUXR5Dx7whraKvMWV/FbrqN0/dXkhwj67KRfG0Pf0L/ePo2TGBPmXzto07S6WwxzUlnvzhk8s+YGmvjH31vyaPN8uNp6xa0Zn+lfVrO53S6fbo5fFNLz0Y54jqBbda9O7xTE94rEbs5o+kxSn3pwN448rLtX3PuoNujE+nVw14fRE/2l4zhxxg+J2ee9hxxzrfOpeOtFUlvurbK5yv23NrLuB76+oujmC0Sn4dDLmWwK16O96RvprxOZk94jrfuM+YOM7cm/H7Smp9S+JycBzAkRq1wrapen70yv1Z86f67/duxAcYcjOTLCvZhcpzxna2TT772GB0=
*/