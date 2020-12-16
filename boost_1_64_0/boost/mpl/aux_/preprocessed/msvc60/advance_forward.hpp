
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/advance_forward.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< long N > struct advance_forward;
template<>
struct advance_forward<0>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef iter0 type;
    };

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
    };

};

template<>
struct advance_forward<1>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef iter1 type;
    };

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
    };

};

template<>
struct advance_forward<2>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef iter2 type;
    };

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
    };

};

template<>
struct advance_forward<3>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef typename next<iter2>::type iter3;
        typedef iter3 type;
    };

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
    };

};

template<>
struct advance_forward<4>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef typename next<iter2>::type iter3;
        typedef typename next<iter3>::type iter4;
        typedef iter4 type;
    };

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
    };

};

template< long N >
struct advance_forward
{
    template< typename Iterator > struct apply
    {
        typedef typename apply_wrap1<
              advance_forward<4>
            , Iterator
            >::type chunk_result_;

        typedef typename apply_wrap1<
              advance_forward<(
                (N - 4) < 0
                    ? 0
                    : N - 4
                    )>
            , chunk_result_
            >::type type;
    };
};

}}}


/* advance_forward.hpp
N2I+emNvW+NxZgQOQUt2fB+cikMxGYehu53xuHMXDsfHcYSyHF+wkfgq+uERHKUsZ8/xD8/gGPwF/ZXl+MKOReXGXQF4PQbiGRyH3m3YtzAIJ2ALR+PxKhaDcTFORO+2xuPVGpyEz2EIxjpxjoD78Gb8EKfgGg7cofg9TsVr2EGnKcthGHbgQBuOnhihLIfT0d+Z8zSMQB126Mg5Fc7FKFyJ0ejfibFUOANj8RQHjDi8mQNgPL7PQTABJ/CFSMSjHPyScDQHvVtwPwe9ZBzKwS4FR+IsjMLZuBzn4JOYhntwLhbgPPwD52N7vpcL8EZciENxkYwNyaK/vGw8wx3kRmbjFCxkLEIeOdi74viCdaYxAsj7ZKrGACww698/y/8rg62dyF7kYHIc+Q7yJnIOueCs1nevJS1pSUta0pKWtKQlLWlJS/+l9Pfe/9/Y/++hi05JVUYAXOb9/5X+/s1V3Of/qPSPHsKRyv2LF5f1sXlI72hN7n1edf/ocFX/aPFF+ke3yxiEdoTqWUtaqa+Nlf7Ryv2hJ6UMY6SNdJSS+cyiZaYyGHpDa9M/PryK/tDQBpX7Q8ew3Ljlps8p7w29hM+qqj9UXU435UPN+kPH8tqk8s+X3tCa94UO/wf7QndJ/3KiK8vhTAxgfRavKOsL9ajcEyr1OkP9/btI2VT9n6xD1f2fZ6Ucw8z680JC3OX6fOnflP/PMv2/p6HceaZpj95Qoa58ZPqMTPvKdIGq7qSfUt7jBsN0jmnaS+77X7luN5iW6WdYZkv5eniAYd7J8nl9QPpfTfPcocK2HF6xT5dl+kqfruk1hvfILZ/uC9KPXDavv2GZ/PJlPKHC2IahMn3QtEwfw/QR03RvwzHBnf1+B/vKdewfWYZ9g2OF9BcHmvX3KsuHsux28jfsGMWyvPQXq/tzK/XTVt1f+vf309a2P7aXqzI/qvPqmOvmlARaWayYZHHi2rW176etul+6+v5bY/+e/DbIb0bRv7h/b5/07x3CMJR+UPld4L3lPsvqftAbpH+vH7aU/mUn6V++XvqX3aV/eYD0L/tK//Io9FZfG7q8vP+uqBb9dxzPpf+O12n9d7Xqv5vRUH4/5HdlizxrnmMCyXgtdTO8C+3wAdm+q6Uf90HsiQ9Jf+7DOAQfk2ttn8RU3Ijz8Cm8GzfjOnwaT+AW/AqfQfrKWAfeD5/FVMzA5fgc7sXn8Ti+gDYcDzKxI76I0/AlTMRtmIHb8Q18GX/FV7AJO9Sr6Ic7cDLuxIfwNXwaX8czuAt/xDewtxXXyuIwfBMXYxbeh3vwKO7FTzAbnajLHJyM+3E6HsBoPIh78C08gIewI8efw9gFj6AO38bdeBRz8B28iuNOLk7BYxiB7+J6PI4lmIcX8D0cqFxbiw/iB7gW8zEfT2Bvvtgfohd+hLPwJL6DH+N7eApt6bf8BOOwAJPxU3wBP8PGTTgnw+Z4Bv3xc9yMX2AGfolf4VkcZm28BnoUnsPb8TwWYCF+gV+jC1/kb/BW/BaXYhFm4XfoyI76PTrjDzgVi/FV/BHfwJ/wV/wZ+zU3Hh8exd/wdyzFcE52fsds/ANdlLMv5fveAvA0NsBhtsbjx0a0kn7ShhiJV2M2XoMufHEaKa/Hxsrr8Vrl9a2Mx5eN2BQt7Y3HmUhsjtlogy6t6d9WXo+2yuuxpfJ6B+Nx5lm0x5ZtjMeZ+eigLIdtcIyjsX97G7bFtm2lfxvb4Xlsj0F8sTvg6+iMLu2Mx6W7sRP+gC44pb2xfzsbr8PuHYz92w9gF/wNXTHS2Xicysbu6NLReJxaij3wNPbEYZ2Mx62N6I6WLsbjViT2xmzsgy6dOX4pr8e+yuvxBuX1HIg=
*/