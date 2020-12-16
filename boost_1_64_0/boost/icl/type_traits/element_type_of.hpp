/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_ELEMENT_TYPE_OF_HPP_JOFA_100902
#define BOOST_ICL_TYPE_TRAITS_ELEMENT_TYPE_OF_HPP_JOFA_100902

#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/icl/type_traits/no_type.hpp>

namespace boost{ namespace icl
{
    namespace detail
    {
        BOOST_MPL_HAS_XXX_TRAIT_DEF(element_type)
        BOOST_MPL_HAS_XXX_TRAIT_DEF(value_type)
        BOOST_MPL_HAS_XXX_TRAIT_DEF(key_type)
    }

    //--------------------------------------------------------------------------
    template <class Type>
    struct has_element_type 
      : mpl::bool_<detail::has_element_type<Type>::value>
    {};

    template <class Type, bool has_element_type> 
    struct get_element_type;

    template <class Type>
    struct get_element_type<Type, false>
    {
        typedef no_type type;
    };

    template <class Type>
    struct get_element_type<Type, true>
    {
        typedef typename Type::element_type type;
    };

    template <class Type>
    struct element_type_of
    {
        typedef typename 
            get_element_type<Type, has_element_type<Type>::value>::type type;
    };

    //--------------------------------------------------------------------------
    template <class Type>
    struct has_value_type 
      : mpl::bool_<detail::has_value_type<Type>::value>
    {};

    template <class Type, bool has_value_type> 
    struct get_value_type;

    template <class Type>
    struct get_value_type<Type, false>
    {
        typedef no_type type;
    };

    template <class Type>
    struct get_value_type<Type, true>
    {
        typedef typename Type::value_type type;
    };

    template <class Type>
    struct value_type_of
    {
        typedef typename 
            get_value_type<Type, has_value_type<Type>::value>::type type;
    };

    //--------------------------------------------------------------------------
    template <class Type>
    struct has_key_type 
      : mpl::bool_<detail::has_key_type<Type>::value>
    {};

    template <class Type, bool has_key_type> 
    struct get_key_type;

    template <class Type>
    struct get_key_type<Type, false>
    {
        typedef no_type type;
    };

    template <class Type>
    struct get_key_type<Type, true>
    {
        typedef typename Type::key_type type;
    };

    template <class Type>
    struct key_type_of
    {
        typedef typename 
            get_key_type<Type, has_key_type<Type>::value>::type type;
    };

}} // namespace boost icl

#endif



/* element_type_of.hpp
7f93XuB/Nef3cDh73i89H5FD86Ka98uak7g0kp4fDEfScxOd6NaseYl9zUMsiP5n5g99HqM69K/NZSTmpf7JuYyFmv/cpHnLY7LmLn2O46Dw35/nmB9JznOMCvmcxsfnMy6x+y6cfB6dytct+5rD+BtzF9lzp/uey9j33MXl4X987mJf8xYT/oX5isRcxT8wJ5GYi/A5iPa5h3947uHfnXdIzzX8c3MM7fML/5n5hR37mEfI/izE5xOmhYjvf0T+ucSDoeT7p2tplx2LI9lzCP/45yaZ8wydqTVjniFq+5L/tyAZn6nUU37Gf29xARc8Q+/1DtXnLZlzED7HcC/fX6DPXV7XZy0+Z3CP5g06sbyY5ayMz18aMj6DWU7LMj6L+SJ9QZ/JjP835hv+2TmGfc4t/APzChdH9zWX8K99TnQetiXs//3JX85FdAtlzkf4Z0P//3MSC2j2Pj7DmhH6x+cfsuYc0nMN7fMK/xfzCplzCf7Z5Dw6mvy/WfL/Fsn/GyP/b6UGhT4+/xALJecfsuca6kL7nms4H/9Q8wzr+ToU+uvzDD/6L8w1XB5Knh4M+fvl9Ofd39L7cTtOrrbtqbnkhfrc9TK91glhXJ/EceQhW2fGe9K78c/xdUd9rjuDOun47tuqSyh5/D2fLtBjf4of0zR3ejbV0jnahlN1W6bReTSd/Lh3vuaiZ9Ismk1zqIEupLk0jxrp/hDromn6rO89+oY+K7yYLqH5dCldRgtooY6by8jfF58WSr9XPp0+lfG++xvh5BzGUr3PjtJt9ljn60/T63q//oXwx9+X36Q5cJ+7jOpYkkO5uv+v0JxIk+aJr6ZrNFcyn67XsbeWzqbfRZJzSnl6rBTo8dMh43HSSceSmI4ZXfWYKdbjpkfG8aWnHu+9dTwq0zGmX+bxIvMYkfkYz3pc++P2YB2DqmioHqOHZhwvRtDIjMfzERnHvTEZx52xdLQf7/w4lnXsOt6PPVnHm09StY6Dp2Ycs+J0uo6NNRnzkWfSFB1DPqPj/Cwd1+fQ2TqGn6Pj+FSq8+N5xnF/ho79F9BCPX9cpeeWK/TcMiDKNqRn6Pf0huaI2jQ380V7DOvzl3q+LqN+NIT60qXh9HvMQVQeSh/3jtOx7yK6MZR+3txG/pzqz8tP0Cb6Ef3Mn0P9OXcfz7P+PJ79/O3P3dnPvQ10Ic2ledSo58yL9dz64t883mUeF5PHvhw6kAbSQTSIBlMlDaFDqIqG0jB6Vq+Xw5rvytM83x/1udYloaz3//uYI7gk63OEBTrOD+d7h1L2+9XDaASNpOz3yqNpDB1JR9Hfei88gfb1Hvqnev2/Ta/7X9B7hZf1nuA1ioSSc7Tr6AHNSVwYSr6evIVW0CrNRZTSCkp9Rqb3fVG9pwxY5lAu5VE+FVAhdaAivQ9cx2U/0Hvaw/U37D+id8jmqh7T3NUmzUv9id6lJ/j6Sc1XbdZcVEjzVE+x/JHmqLbo9Xd+NP1arpAmU5xOpdPoFDqddvm8t89z+/y3z2lnvL/aofdS2a/bDwll/huwvz5XMkCvrStpvuaw1lD2XGDm3J/PGz5ImfOAPo/oc4aP0PfpUfpb7wWy55M66n16Z4ppLqBrxlxA94y5gFL7ec0P9NbcwQN2e/W+oh+V0356jd+fKjRn/HnNk+/NmDsfgF0VSv87pUWhj39GcG2I265/z/dRxr998jn1KAXk8+mDNOdRSUPoYM2RVGXMgxxKw+kwGqF5lFEUs8eg5h+OofF0rOaCJmTM4Zyg+ZlJmr85WXM91ZrfOZVOo8kZczufypj3OYPO1L/lmKL5k7Mz5lXOpalUlzFvdSNNp/qM+acVdj/T7fStEPuJPk8=
*/