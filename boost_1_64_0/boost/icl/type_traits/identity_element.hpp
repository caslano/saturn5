/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IDENTITY_ELEMENT_HPP_JOFA_080912
#define BOOST_ICL_TYPE_TRAITS_IDENTITY_ELEMENT_HPP_JOFA_080912

#include <boost/icl/type_traits/type_to_string.hpp>

namespace boost{ namespace icl
{
    template <class Type> struct identity_element
    { 
        static Type value(); 
        Type operator()()const { return value(); }
    };

    template <class Type>
    inline Type identity_element<Type>::value()
    {
        static Type _value;
        return _value;
    }

    template<>
    inline std::string unary_template_to_string<identity_element>::apply() { return "0"; }

}} // namespace boost icl

#endif



/* identity_element.hpp
X3YKJc7DifNI4jw5l/qLSyNBJDVKW5Aa5WhvGB0Jh9PDSHroB6NcLfO0LNCyUMteWvbWskzLvloerOUhWg7VcljiV/16QtCB/TMvnDjTuS98GUkufeHLaHLpi4iW+jrQIqylvp2TXORqEdYy+V2dh7XwLyMhDdLf0be0yNEi7EsbRK+KJpZ1ibOonc2xswa9otD79mgXLbtq2U3L7lr20LJES/+5nlr2smUkmjwPEgvmbqbNHjxtTmIT33BEUSQcSw0z5iTD3dLDkvSwT4jTknElsXUUyjrtxGLHlCT+/yhy7XLzeiQuMxlrpEgo+Vn75+UbsE0UZZxPX5Qv/Kh7bM213WKB/MvynVx2F+XI75bvxSz7nQV0v7x0fEmsivLk35HXYA2UL39UvgJbTwXyzfLt2B4qlD8rrzy2JDaJOjAO06/9+mNWEeMIPSdfjTVTR8ZRel7eiu2mTvJWecVxJbHx1Fn+sm9PrIZi8t/KG7Bl1EX+mrwZ205d5bvkdW90jw2cUBLrxjigP8jHY5b//yC8LZ+CWd21HT6QN2FWD3nQmPQ1mFUi7yjfilml8h7yoolsM+op7ycfjlm95APltZjVW9dzqLwRs/ro8ofLl2NrqYxxDo2T78DKjy+J9ZVPkC/9oHusCe8nnyRvxtfi5fJT5Lvwnfh+oY+fxu/tHis9oSS2P+MOdLouX4lNov5Zl6/FFlJFljeyntW4//9en6P1bMZ20gFZly86kf2fDszyGmwhDczyVVgLHaTbNUPr34tVTiqJDZLPljdgq2lw9nrYDkUn8TO6nvN0+YlYEw3RehbIN2H5J5fEDs5az0TMOkTrafL7F7OqdP8uka/DrKHyL8iXXFQcs4bJb5P3+ST7CB0qv0teg1nD5WvlKzDrMPmD8u2YNUL+fXlFNfchjZT/UF6HWaPkLfIN2G46XMfJX/l2O6UktoSO0HZo9f0WKzq1JPYJ+U75WKyeRoc+flqObaQxWb4bi51WEjsyy0djU+ioLF/K8XkVx+exuh/b9HtX4eWTS2JH63a9I5+PraFxuvxH/njB9tAx8uhFOm7Hue40XuvJlzdi1rHyLvKl2Ho6TuvpJd+JFZ9eEpvgxxP5aGwKTfTjiXwRtoaOlw+V78BinyqJnSA/Qj4Wa6AT5cfI12JbaJJ8kjyoYZ+lk+Rx+UxsOZ0s/4y8GdtDn5RPlzfw+Kr8dEmsOvvxglmn6HmnwS8/qzg2Ez9Vx/+58tVYM50mv0jehlWeURKbLJ/v68FWUly+QL4dC84siZ0uv8K3M1ZHn5JfJV+JNVONfJFvZyw2pST2afl18uFYDZ0h/5x80172Q/xMbZ8b5BuwFpoS+vipDcs/qyR2VpaXY6PoM1lejTXQ2Xp+/JLWvwRbTbXy2/z6YNvpnKz1rOV6Fn2mJHZulldiY2mqbtdXtJ4pWAPVye/0/RyzpslXy9dhW+g8xoV0j3wPVnl2SWy6Lv+A34/YEqrX42W9fOPc4pg1Q5f/rq+fy1rnyzfKJ95WHLMukD8qb+X27uDyM3W/PCYP1XK8pVmhj59GYZNpdpYvxFbTnCzfglkNWv/T/vg6h9tLF+r4uVVegzXS3Oz7xY5j+Dxth+f89j5WHNtkP6P1tPr24fJ78Yt0+Vflf+3U51zuX7pEr4d36fL12BKar+P2W/I12Ga6NPt1NZY/tSR2WZYPxCbSgtA/dqrnsk10uV6HvO/HAayVrtD9mHOxXp/UsT3pSl3/fHktZjVp+3SSL8da6Crdru7yimnsa3S1vEzejAXnlcSukQ+QT8Rm0iL5EPkKbBNdKz9M3oaVTi+JLdb+P0Y+BVtE18knyDdjO2mJ/BT5wHq2J31WfqY=
*/