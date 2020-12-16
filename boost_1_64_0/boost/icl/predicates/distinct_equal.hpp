/*-----------------------------------------------------------------------------+
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_PREDICATES_DISTINCT_EQUAL_HPP_JOFA_101102
#define BOOST_ICL_PREDICATES_DISTINCT_EQUAL_HPP_JOFA_101102

#include <boost/icl/type_traits/predicate.hpp>
#include <boost/icl/type_traits/type_to_string.hpp>

namespace boost{namespace icl
{
    template <class Type> 
    struct distinct_equal : public relation<Type,Type>
    {
        bool operator()(const Type& lhs, const Type& rhs)const
        {
            return is_distinct_equal(lhs, rhs);
        }
    };

    template<>
    inline std::string unary_template_to_string<icl::distinct_equal>::apply()  
    { return "==/0"; }

}} // namespace icl boost

#endif


/* distinct_equal.hpp
/Vi/19B5R++6a8DEm/s3Td5/8Obbx+wy3dbnREZ1/BaY3+t/G3Zi5Tfrd/bKrbnwiQfne5zdr7T8oI3QTqjXr0kzZ9b4SfdGFPzeMXrYN1cKopMnXDv729Qhu9t8Msp+7u7+qT9Eb/tYvf/KRxNfW/JQg/ajfjpzeOzBTxpem3fji3OPPvfS25OHvd2xf7/Ov0/bvvmlU23PfLar5Z5uqVm7Hjscm5M9+eeE14/v/WPpz31uq29u8tae8Wn1oi4+nD2qSfa+zmG2pRr/xs3rOmH1NvOanxY2rT19ab+ha4OtTxVyX25H897oYwOfvpq71tuzVuH21xaf37u5c3rrMV9MM1w9d0fY6q/O99j9ztnt3hb1nu8mmtM3r+y9d8LmnXcUr1w0tFO9Gpejltmnx3d9wzHlgRZn+qQmT7btfPFU1yNtqcmzX/0wsvVbr1a3Pu1Yfd67v6/QZeeg7Wd6FN1/1HBa/GXBO2uuXL7520F/felC0eIL7X5//5Yt373QqW2vz2oNXfByyc8PHjz/vuOu7jtWrU2o9+P54uO5jWqXzLi2/vJffyhYP2lm7a2Dwx985Ik/dvZ+b1OjmUn5c1xn7kqOX5K99bGDMZ8cmp3WdZrr/q0bF2z5bk3KrsmP/ZZ1bMfgv+zc+/AXr335veHOd2uGT37x7KymHYzPLNtn3Dz/5q6f3lC3/h9HhqRduH3/s0mLW00Z3/b+G1OuXaw7bvrX6/cVjd+wccy+9wanvWvr9PAZnXo88+KCW1ZH9eu075uZw8/NXDRkZOobi+teb/2rqddq7Y/m04nnm34w+oV3+54oEurdkNHo+8lHJ+ZN3fDTlB3P9D28bevVyy3iQ7P+OvLcb4bNb/42oNek9IWGOtPiw5812gdFvD35dFH+wXqua3HDrrRa1fjiYMvL3Sa07dfrtdxxJ76d8Er0+W/CBw5fUTJ+U+9nVjz6RNOzjRs/XppmKjn6erD15++HzXup6fTViY52de5zTc78MvnvkZ3HRVzMHrr1li3HG03ZXrflxvfWtl/Y5LZxs/pSvZgbL2Q98Pr0N3vOi7yphye85uEam1fseXXVw4Oebzur3iLx25cX/VJnzjPT7s7s9v75sHX7TrY43K4N387tui27waXUiZ23Tzpz4ydH13SaXfuZXudzPpi4tWvIkhNvPdJt+8y//ZqZUbfJ7dZL+e+kXVu1ptu07bvvGju77+qzk78bhM/DH7h60y7jV1+1OR3f5cM+G76d9fynfd/f3HTOq00KhF/2PD1qy/mHl7zzweCc7bXaX70w3HpmeY1Bvyxq3652nz7Nxy+aVrf39NDkNj2yIiuo7wvNGjjtG8Nar32n24ubx0553dh9dmzIuTBR/GfjFaR+5pR7nty0dte6xsfanFjTd1Gdef0X97k479CbA/vftqtugeNwE8G3oU332VNHXXQn3Bu3ddw3DU89WhL10uobvt98yJPwU4dpj0999pbzH2bd2qrw6qE+HZ69tvdao8aPjDFlHzuyoXPy7PCDrZ+tYct574Z7VtbffLTg3ve6+KYs7jtyQrMD3Wd//+Kq8INX+zwSPnzAnucXtSl4beSTw9u3u954JbF4bTj5xI4T5/bOvev9L5+Le+v3G9+Onv/CC28drf2hZfkBd1z4uEkDHqfH38zv/dyhlR2+XD31y3bTrnWOmv7mjHYbRg8d3q3fD0XRq2Pmju7+l09jx6VtbJnxxiNvn5zf85cGxnXxyQe+ftSyM+riffeua91tZc1O370197H926bUvXXtHd/ve+ns7o0Dxv/+yIFgdD8J75X3aFLm9vtf/uJku4hdlqkNfmo57bnPdx3r9LH13uaxnZZnjFk=
*/