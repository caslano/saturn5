
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/advance_backward.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< long N > struct advance_backward;
template<>
struct advance_backward<0>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef iter0 type;
    };
};

template<>
struct advance_backward<1>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef iter1 type;
    };
};

template<>
struct advance_backward<2>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef typename prior<iter1>::type iter2;
        typedef iter2 type;
    };
};

template<>
struct advance_backward<3>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef typename prior<iter1>::type iter2;
        typedef typename prior<iter2>::type iter3;
        typedef iter3 type;
    };
};

template<>
struct advance_backward<4>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef typename prior<iter1>::type iter2;
        typedef typename prior<iter2>::type iter3;
        typedef typename prior<iter3>::type iter4;
        typedef iter4 type;
    };
};

template< long N >
struct advance_backward
{
    template< typename Iterator > struct apply
    {
        typedef typename apply_wrap1<
              advance_backward<4>
            , Iterator
            >::type chunk_result_;

        typedef typename apply_wrap1<
              advance_backward<(
                (N - 4) < 0
                    ? 0
                    : N - 4
                    )>
            , chunk_result_
            >::type type;
    };
};

}}}


/* advance_backward.hpp
71XUXjDPUB8effrHbp8N2vbU4VsbvdO6busltterpX4rx4hjZ+HZ705Sv3XBJuiKHtgYA9ANg7AJhqMPRmN7nIwdMBVvxkmVfL5T7DSHy/bJqetxGVodTQta0IIWtKAFLWhBC1rQwjUerkr9Xxn+X0XP//9ONf5fL/X/WHuGB2M01lbG2X/lKPV/Gf4v48rrWDH+3Xz8fy3v8rHl582emf67asy38dn0GaTpCeLcr0mDalx8S/6dklL+fP0OkodjkodQYuk9auSFfTYvKcuDcquA1fcJSHrlvlnT+wScZR8NifX43NzyfURmMhViYnpmqi33JBj3VV817p67DeLszO5TaCvj/9fLfQpr8SbWLSjbv9ymIPt2rMS+nR1L9x1jV/G9CupjVyLLKcT6coxU6ZfjLcfX7H7sILnHvLoT+cELDdgG6Sk8Z8iPcsYbHrUfY0hQeqaOc1fJV0oV5ov7lU3y0VvePynLUVG+huXtZcsBhm0eLVvu6Acm922EyvJZWQ6T5dPGspLlnWXb6GRY3lu2HMQ+KGsLZVlc9pnOhs8UlqejIxhe21H+mr/xtYPlr5Xda3Gs7LVAw/K+8s8Y1ikqXw40rrOl7LUuhs8cL/9MAJh8v3vJ8qGyz/gblh8rW/Yra9trXom2vQJP5fXj3jfeEx4Y9fh3bh0d3h64dmvVjSGpqjY/W9v2thnaCPen75o9a/ULdy9uMttxxmnfZ0rb/HbYye+y/F77ohPReK9Pj2rc64A9sREGYzMMxbbYCztiGHbGPhiBfTEK++FkHIALcBAuxWH4B0ZgKjsfgTkYiYtwJK7EUViA43A06ZuA0RiDco+x/CaTJmJNs3uMXeQeEFdsgI3RHd2wDbqjLzbBrtgUg7EZlj17ULbvLMvquVGDSIc9dsGG2BVZj9fld1R+X31lHR/5u/Kr3EPym6TLjvVcFbAV2qMf1sQeWAvD8QacgHUwCW/EDKyHM9AR52N9vBMbYCE64UvYEN/ARvguOuMn6IJfYjP8BZvjb9gC2ZZdS2yBrbAtemJHbIudsR0OQi+MRG8cjz6YiDdjCvpiNnbE2egnxzkA12IgUn4Uqvxuy+855WDoR9Dbyz3KUn6eUn7+6IYB6IGB2B47YScMwqHYBR/GrvgEdkPK1q471sOe2AeDcSOG4AMYih9iLwzke98bu2EYTsU++Dr2xcPYDx1Ia3+MwwGYhAPxHhyEP2E4/oGD0Z/fhyG4FIfiKhyG+zECW/F7MBzb4QiMwUh8DkfibhyFP+BoHHo93w8ciWNwCY7Fz3EcfoXR2ILfw/E4EyfgPIzBZzEWlT+AceiME3EwxuNDqMOtmIAnMBF71OJeHeyNk3A6JuMTOAU/xxR0u4FjihGYhrdhOu7CDPwep2K72szngTGYhatRj69jNlbjD3IOdsZpmIq5eD9Ox/dxBtbjhMnDXjgLs3E2bsE5+CHO5b8bb6RfBUPxFtTjfHwIF+AHeCvWZcDfQgzB2zALF+GDeDu+j4uxDhcHSzAYl6Iel+HDuBw/xhXYgKuYO7A/rsRZuAqfwjvxFK5Gdy5M1mAErsWFuA5fwLuwBO/G1nwx1uNY3IDL8V7cghvxZSzAj3ET/oL34QW8H3OvUh/NFj5fRDxGPE90zNX6bLTw/w5XuP4foMSq7P8/b0X/f4ix/h9wdfr/G5j1/9f4D/b/uw5SXvdLWzzsjx4LHKrtWfjITXe3f8n2OoL0/yvH6Jru/7/c35WAXNNx3GHa3xItaEELWtCCFrSgBS1oQQvXeLgq9f8q7P//8TL9/87UxTMOG+v/f7//v2El+/8dj1S+/9+VfRa+Y8yDbf3/Da3s/3fjc47vGvdRuf7/hn8=
*/