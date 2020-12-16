
// Copyright Peter Dimov 2001-2002
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "arg.hpp" header
// -- DO NOT modify by hand!

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN
template<> struct arg< -1 >
{
    BOOST_STATIC_CONSTANT(int, value  = -1);
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1, typename U2, typename U3, typename U4, typename U5
        >
    struct apply
    {
        typedef U1 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<1>
{
    BOOST_STATIC_CONSTANT(int, value  = 1);
    typedef arg<2> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1, typename U2, typename U3, typename U4, typename U5
        >
    struct apply
    {
        typedef U1 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<2>
{
    BOOST_STATIC_CONSTANT(int, value  = 2);
    typedef arg<3> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1, typename U2, typename U3, typename U4, typename U5
        >
    struct apply
    {
        typedef U2 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<3>
{
    BOOST_STATIC_CONSTANT(int, value  = 3);
    typedef arg<4> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1, typename U2, typename U3, typename U4, typename U5
        >
    struct apply
    {
        typedef U3 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<4>
{
    BOOST_STATIC_CONSTANT(int, value  = 4);
    typedef arg<5> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1, typename U2, typename U3, typename U4, typename U5
        >
    struct apply
    {
        typedef U4 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<5>
{
    BOOST_STATIC_CONSTANT(int, value  = 5);
    typedef arg<6> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1, typename U2, typename U3, typename U4, typename U5
        >
    struct apply
    {
        typedef U5 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

BOOST_MPL_AUX_NONTYPE_ARITY_SPEC(1,int, arg)

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE

/* arg.hpp
1uX3LapsTEQ98ke1jWNoX62nsBY2hIu4EWthQzhsZYB/p9icoC8y1casvsgJNkdJIhFnJzJHTlU1z1yZZuDmmSsnWbg8G+pkE5MdDX42auBqXj/FxBrs+rDG4JjntdRauH1eS53Fsc9riTk57vNa4iFcdV/qegfHPD+pIYSTQR053cCtzgncSdg8NO4Y17Vw9btCcGZYHLUTIN7T6OCg/me8ycJRZ8KfSSeeqfHjNWXjsqOB/JQ2OOo39UwDM+uxZgPX21+M2Vocd5xnLZ4e5zkLt+N8lsWx43y2xdHjfI6F63E+14nLOD/NxmWcg3O64MheXaXSKwFnnslRe27wyxk2B7v2irQ908Ll+o6zbCzhr1eZb2FyvdYCGyO/8xAt+/tsNw5/Y32um4McITgL3ZxMNiXXD50rONgIpGRsmWqNQf4+DxyqBqz+//mMTamKFo5GdwOHD6JtXyRx7ZvuAqmHsVZ/7ucS1/bNvlDq2Wju8xdLvTByw653kaev9g9FFrqLWYdDkaG7ROj8yZMc7iXQVVcVl+Ds+6BcX6pgrjPzLwNOGU7sKQ7Qj9PLJc5NuPrsUg1L5yh2UikvU+LdV5i44faVEmczMAb/xfivxNBVwcPAlwGnbifpc3XZ4ER9rMkVONIaswQQ11cD40Vg4F8DXSxOzqXm4gGsxfWxXNoZR9dJ3Iqj6yXmjKMbLBwPA18ucT0eEJYbgat59iahw+xENkfiIYHfrOKpXFa+FecRq3hzPJNrFHaKW2295u5tKp6NZ8z0vl3BZYJjXS0we2qn8NMdwJWpnWIcWOo5/lD9iHFgiWnpuUrqRTD4wAKe4MH4XQ48kZTns98tcYRQjnXfIzC8jyj8hcnDO4yvtnDycC4TrDG718ZTVNQJFv3s+ywcGV+WhJT/rvstLtcAgV/WWDhXSQH+gI5nzLA8aOBmWB4ycDMsD1t4eFgeMbhmWH5p4QgLxqofBe7vifGYvMczojw9LvS8dW4c+2T8CrpMSN58QsGRN1n/pNRr/KekHvkLZxSzntati7N9NZvjrw3MH7N/RtcH56w/y/qqMbz8DPtUPBfo0jlf97ynO35ccUVJeVkZ5uKv1XTR0YmsP7qMMWkN19dA/EbHgnWxL+p64SDa9nWEccM+ebC3jMjbx0ssUE7Rzkjg/DaEk2SS4LxkcGAD1tx52c2BO9in2uAQLtbC2voozSSpySAPvmLheDfwVx04jUllfXyDjlvhey0Mj2Zm+GnzusFBJ5GxNwxM9dtGBxZVzt5908DpU4z1bxl6ym1iLaytZ+d4jNvAEoNiYh2srhdhg//+aGLSg2KsW8Mx7oBnN1kYpmLi2Xc1nKcHEUfYZ/+kYNhNPtUkB/nEOLfk8HpODhC+id7XMD6rKBmraY4p06/YjQ90ntjLH/7/0IVxPwLrY0PxaBB/Hzk5Mo4+duI579gNMSYucc4bqi3iLxJTguUnAdbJKpyGuBxb+NTQI2bF2LiBqX2NzwxMhlngW2wc4cWYucRxeheXRH72cwWDf7T+1d81PCvio9FbG4R9rU08O0fsa23okb8Z+1JiCKc8M+ArYPjwqfTnPmzT9d4BCKz/h64PxrS+NvTq+qpvDKxBWTO8XceCtudbXR+Mw3yn67H+GGPeNhZtQr8s0h0Yb91TPLq6qghmIYF3sHH070VZ6xiKB8NpYj1sKA9WLfA6t8jLBnbILjYvsJt2tTFtTHYHG5dHvYPTLYSDw+eZs6PNkXv+wZ87WRy5p8/ONhbYUrvbGE8DVf24SwgHfuR37OpzxLLh/GrFRrGbhcm1jHkWJs/H6CExMsHIMtNT08tzNnbX9HIOTS+pryiR1lbG9rAw6bc9LUw=
*/