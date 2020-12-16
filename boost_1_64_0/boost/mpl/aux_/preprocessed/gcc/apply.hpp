
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/apply.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename F
    >
struct apply0

    : apply_wrap0<
          typename lambda<F>::type
       
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          1
        , apply0
        , (F )
        )
};

template<
      typename F
    >
struct apply< F,na,na,na,na,na >
    : apply0<F>
{
};

template<
      typename F, typename T1
    >
struct apply1

    : apply_wrap1<
          typename lambda<F>::type
        , T1
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          2
        , apply1
        , (F, T1)
        )
};

template<
      typename F, typename T1
    >
struct apply< F,T1,na,na,na,na >
    : apply1< F,T1 >
{
};

template<
      typename F, typename T1, typename T2
    >
struct apply2

    : apply_wrap2<
          typename lambda<F>::type
        , T1, T2
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          3
        , apply2
        , (F, T1, T2)
        )
};

template<
      typename F, typename T1, typename T2
    >
struct apply< F,T1,T2,na,na,na >
    : apply2< F,T1,T2 >
{
};

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply3

    : apply_wrap3<
          typename lambda<F>::type
        , T1, T2, T3
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          4
        , apply3
        , (F, T1, T2, T3)
        )
};

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply< F,T1,T2,T3,na,na >
    : apply3< F,T1,T2,T3 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply4

    : apply_wrap4<
          typename lambda<F>::type
        , T1, T2, T3, T4
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , apply4
        , (F, T1, T2, T3, T4)
        )
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply< F,T1,T2,T3,T4,na >
    : apply4< F,T1,T2,T3,T4 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply5

    : apply_wrap5<
          typename lambda<F>::type
        , T1, T2, T3, T4, T5
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          6
        , apply5
        , (F, T1, T2, T3, T4, T5)
        )
};

/// primary template (not a specialization!)

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply
    : apply5< F,T1,T2,T3,T4,T5 >
{
};

}}


/* apply.hpp
DvwB/BiuhJ/BVbAF18ltsBVcDdvCYv6Lg3fAa+EaeANcC2fAdXA2XA/nwA0wFW6ENrgJ3gk3w13wTvgovAsehSXwLXgP/ABuh+fgDvgJ3Am/gbtgC+rZfbA93A2Hwz0wEe6Fc+H9cDF8DFrh4zAfHoTL4RPwNngIboCH4T54BD4An4QH4A/hk/Ap+Awsg+XwaVgJj8L34DH4e/is2hcn9yG5PyV59MVNVo+Tewds7eU4WwB9dsEv1Mf3qe+z+//tszPvr/Nvfff4JsGWFGRTk/r+uvrf/+fvW3r/txY6Xv/r/v4/WPP+b5fvf/HybjYKWcBzdtXd7vf/aTNnTp2ToMx8S7Vmp/of/38uFtLsReo3/5zWmndUea93vDvb8x3b4e73fHXOdmOZd6K807bd5rznL4zSzzUe39CYh3kcE7fNLA+ZlEdGPjOOcwNZc9x7XmT8gn7OuV/5yZb83OyRn8ggY37mckyxWX4kKrgExr6i+ZFY1Oq+cH3cbNM8PS95uilKP+fvrORpsuRpIjKbYyrN8iQzyK70+dHkR86P3vewEqfvieK7OkZGbm1TxPdJSIJSv0oMvqfZ8wM/B9p+i7ScdPFX4h3kL07TlD907LMCtfy/DHfnYYnk4UaPPIQ3krHwkocJSBJ/KTHkIbB1g9U8YPslsT2vpd52idgeJravQ6bjX7XRdnZuds3r5JrZbnuP0/YMj3zHXiVrwyHNpd8uU5lrfY/BNquB1xxPPkxsT8FOToY9K08zRw5/1POwUe+Pu7/1KvOyqDT6U5BVaE/PW+7/fEZteXzupTxCrjbGUx9FIrHbVfuyOLyjHtRYHi7bXEekpb/mi682rsuxmLIvNdhyTsNXdgQyX7Sp2NS2nZdMbGZhs9KHzeRxs6YFYlebVzUmTmPj3Ols7FruNbOrLEDi/zVmls/GMp8+Suy1RZZiL9Roj67Q2rWpWVGOvhO/21RtPbOLf/Okns1BrMp1Z/DPv+vOdY1Je+2wdYPY6tFU1hEVW6OQHGyVGW2hmp+dsSxDUyD+2a5Nebh8lv5o3fmrEp8bybjLBjBPOX87vPuck2pPy/IrPorWX+kXl3pb5BGnI9ujbHnC9JwDr7umE5vJ3CUp6ymIDb9Tdnr6LctBOAMT+F3GjU3q+hmTuAS3Kte0xubsxJmzJiSPS0ySiB72vPyA5p5/FeloO3V2z0khH5VzVAZbt+XcebM7IDktI99e4LIbHYDdFtr1P3LccQjK2C5Yaj7H+gLb2jU0zunOob7uKdvnZTuN8xFhCWpZ2Yy8YPQI+/ruIk9Sjy9JOkUkJNe1rg68J3PyfyDlsgy2oVxCd3svl3xrwRUpEyVPT9dQJtvNy8Qkb1LO3stJVx9CZO56i4bkGzaFjch39R5v+ZaHcz/qg+u5YjPPcqIk+deXR6jHuinV7jHSOt9pNHT5teny6/vaP6fGNpIy1ZYPzxYr9jrrShPyrmzvul/d1rXLXeTK+1Tain8gBUo8g31eykvTKgd6DS0rCKxd1j37Sxl8qSnnanmesxaShpTJbtIt4GOxt3K8oP82rJY9Ko5ymeK6fqRcZkm5zEAKlfZsv7dy4cxoyiaQdY9qUzaa+6x+7b6W8n1KrvsIuBy/4x/w9JsoZY6m0OJHjAr8hNqyD/Go45f0dVotd6xkpBvrsM7n8WFGn1fgc+mDpj7z9lZ7n7fX0WdX+3pJfH5a6scPkZX4bHnIzGdrXt7SQpslgOcCxe9l6nOBvMto6vSSKHf7etl9HUi+zNdp2tHKaWiglHM/eBs+Vxl8Vl4rAivjZZkrxLbet4uqb6ZrSKnl2TjcGLvmdnxLecTDN+ezQ57jIgsg7oiUp87mKhM=
*/