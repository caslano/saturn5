
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/or.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {
template< bool C_ > struct or_impl
{
    template<
          typename T1, typename T2, typename T3, typename T4
        >
    struct result_
        : true_
    {
    };
};

template<> struct or_impl<false>
{
    template<
          typename T1, typename T2, typename T3, typename T4
        >
    struct result_
        : or_impl<
              BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
            >::template result_< T2,T3,T4,false_ >
    {
    };

    template<> struct result_< false_,false_,false_,false_ >
        : false_
    {
    };
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    , typename T3 = false_, typename T4 = false_, typename T5 = false_
    >
struct or_

    : aux::or_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        >::template result_< T2,T3,T4,T5 >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , or_
        , ( T1, T2, T3, T4, T5)
        )
};

BOOST_MPL_AUX_NA_SPEC2(
      2
    , 5
    , or_
    )

}}

/* or.hpp
RrtYv11eEUreqGWz2UTfHsI1GfVpTWFIuiTP8Ytu1PWOVg8+NehapC5RCjWNnvahg7G8/YVwKQa9sjQtBH3ue/yMydq00mij/g8Jl2XUz2MtcN3v+axNe99kbVpjtHme2010Vy3NLXEULq38ofm9oKN5+1Jj1CnL4YIvV4b2RSln+030f6TVbaP+yh9azgxr4ZT7ni1r+nuJHT2QQq0uu+zwvg44q5b/56Rbd752/xwVujzfLrrGiK5RyGuD+Oczly75gHNqcrVogeuT7xrd83++rPu/Wp5pVyCNWplGn6zn0nTyuPX/DdNJeZ7lQeXemvmEc70LaHrk3U3N8/1i1zKxqwL5q5YPn+vt0t4DA3k3NdimruEWW6Zpccv7pVr3MiV328s9aYt8TJhaly2VS1xlcOo5MyfPdu1SUxXQWmD1vm+NMdbvz7SybqaDGh5MGd9PPJVL9GmaFmusWwe0Mm2mz15u1wpcMO8Pm0Sn+928SN7B5RVcl/YdJrYcJHyTqS28kIdgh5RF0zo3rYtRfxPhYg6Y6F+WV1pVGLj+/T76HUhJQbVnXR7z7CzWf/3n+UIwX9dmte4v+HV25uv+rNYJBr/ub8ZE7Xr3/gNu+FXemOxjExY/kXLZC0x2Fh970ieFffxTjKg+9p6SeWXb4EmwHv4MPgeHw+fhafAFmA1fhHPhDpgHX4aL4U5YCV+Bv4CvwlWwAd4KX4e1cBd8Br4LD8l6gdbY9B6Mgn+DPeH7MAV+ANPgR3As/BiSLubfSZ8UfFjmhXWG6OQgzTI/Kh92gwWwFyyC/eAiOBIWw6lwMZwDl8BcWArL4FJ4KSyDa2A5vBna4Tp4IXwQVkDXPD7po4LjxC51Hl+82JUAu8IesAfsCU+CiXA0PFHis9ukTwluk/g6wAKJ71SJb4LEdzocByfBiXAynAYz4PlwKqyC0+D18Ex4DzxL1ifMgK51YdLnAx8Tveq6sA1Sbu6AcfBO2BPeBfvAu2Xd40Y4WtbBTIL3wZnwfilPD0h5egja4e/gMviwrPuog1fBR+A6+Hu4Hv4B3gMfhffBx+DDsp7yEbhFykmOTfp9QLGkoy3MlHRMknRMht1gBjwRToED4VQ4AZ4Bp8FpsACeKfFrZbRG4r9O6lc/mSOsHTMl/lkS/2yYBLPhYHgOTIPnST2bAzPgPJgJ58N58Hx4JbwA3gBzJf0LJN158DG4EP4Z5sPXYaGsFy2C++AieBCWwEhsXAw7wVIYB5fCQbAMjoflMB1eCKfACjgPVsI86IAlsAqWw2WwGl4EL4HVsr50ObwaXuypv9J/BF8wqb+fSr4dkHz7u9yXQzAZNsGT4WHJvy/gdPglzIJfwXJ4VNqdYzK/2OacFw7gNniCzA+PgK55xNJHBAeKXeo84mjCRcCOsDPsBAfAzvL7dKRefj9afq/OB06R+jpc6muq1P80OAKO9LQj0v8Cp5q0Iz+TeAZKPIOk/RgM+8ChcBIcBj3zciW+eFlrpM6/jFbn5QYYrk7C9TCZlxur6G2QcLF+4msKMFzMp4GFS/k0sHRkBRjOHqDemgDjqwsgXArSIOF6ST6r823nSXmcL+XofKX82NzfICblZ5b8bjZsB7NhB3iulJ/z4CiYI/EtQLIkvqslPufvJL5fKvPTe8Jfw0R4GTwVroLF8Aq4GF4JL4NXQa4Rp9Jey/fKMpP2+lrRcwMcAn8j9f0mOAveLO3zOqn/v4UV8FYl32sl/vYm+d5BvT8SLtZPuAYJF+8nXFOA4Xg/tw4n6/HXMid0M7ITOYBYzXtefRz9XDE32eDrijnIlv6umG/s8XkVeUHUcfd7lfxWpIXvKwRbkrFhxRyuwxykGlmH1CM=
*/