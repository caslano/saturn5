
// Copyright Peter Dimov 2001
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/basic_bind.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {
template< bool >
struct resolve_arg_impl
{
    template<
          typename T, typename U1, typename U2, typename U3
        , typename U4, typename U5
        >
    struct result_
    {
        typedef T type;
    };
};

template<>
struct resolve_arg_impl<true>
{
    template<
          typename T, typename U1, typename U2, typename U3
        , typename U4, typename U5
        >
    struct result_
    {
        typedef typename apply_wrap5<
              T
            , U1, U2, U3, U4, U5
            >::type type;
    };
};

template< typename T > struct is_bind_template;

template<
      typename T, typename U1, typename U2, typename U3, typename U4
    , typename U5
    >
struct resolve_bind_arg
    : resolve_arg_impl< is_bind_template<T>::value >
            ::template result_< T,U1,U2,U3,U4,U5 >
{
};

template< int arity_ > struct bind_chooser;

aux::no_tag is_bind_helper(...);
template< typename T > aux::no_tag is_bind_helper(protect<T>*);

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
aux::yes_tag is_bind_helper(bind< F,T1,T2,T3,T4,T5 >*);

template< int N >
aux::yes_tag is_bind_helper(arg<N>*);

template< bool is_ref_  = true >
struct is_bind_template_impl
{
    template< typename T > struct result_
    {
        BOOST_STATIC_CONSTANT(bool, value  = false);
    };
};

template<>
struct is_bind_template_impl<false>
{
    template< typename T > struct result_
    {
        BOOST_STATIC_CONSTANT(bool, value =
              sizeof(aux::is_bind_helper(static_cast<T*>(0)))
                == sizeof(aux::yes_tag)
            );
    };
};

template< typename T > struct is_bind_template
    : is_bind_template_impl< ::boost::detail::is_reference_impl<T>::value >
        ::template result_<T>
{
};

} // namespace aux

template<
      typename F
    >
struct bind0
{
    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
     private:
        typedef typename aux::resolve_bind_arg< F,U1,U2,U3,U4,U5 >::type f_;

     public:
        typedef typename apply_wrap0<
              f_
            >::type type;

    };
};

namespace aux {

template<
      typename F
    >
aux::yes_tag
is_bind_helper(bind0<F>*);

} // namespace aux

BOOST_MPL_AUX_ARITY_SPEC(1, bind0)
BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(1, bind0)

namespace aux {

template<>
struct bind_chooser<0>
{
    template<
          typename F, typename T1, typename T2, typename T3, typename T4
        , typename T5
        >
    struct result_
    {
        typedef bind0<F> type;
    };
};

} // namespace aux

template<
      typename F, typename T1
    >
struct bind1
{
    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
     private:
        typedef typename aux::resolve_bind_arg< F,U1,U2,U3,U4,U5 >::type f_;
        typedef aux::resolve_bind_arg< T1,U1,U2,U3,U4,U5 > t1;

     public:
        typedef typename apply_wrap1<
              f_
            , typename t1::type
            >::type type;

    };
};

namespace aux {

template<
      typename F, typename T1
    >
aux::yes_tag
is_bind_helper(bind1< F,T1 >*);

} // namespace aux

BOOST_MPL_AUX_ARITY_SPEC(2, bind1)
BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(2, bind1)

namespace aux {

template<>
struct bind_chooser<1>
{
    template<
          typename F, typename T1, typename T2, typename T3, typename T4
        , typename T5
        >
    struct result_
    {
        typedef bind1< F,T1 > type;
    };
};

} // namespace aux

template<
      typename F, typename T1, typename T2
    >
struct bind2
{
    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
     private:
        typedef typename aux::resolve_bind_arg< F,U1,U2,U3,U4,U5 >::type f_;
        typedef aux::resolve_bind_arg< T1,U1,U2,U3,U4,U5 > t1;
        typedef aux::resolve_bind_arg< T2,U1,U2,U3,U4,U5 > t2;

     public:
        typedef typename apply_wrap2<
              f_
            , typename t1::type, typename t2::type
            >::type type;

    };
};

namespace aux {

template<
      typename F, typename T1, typename T2
    >
aux::yes_tag
is_bind_helper(bind2< F,T1,T2 >*);

} // namespace aux

BOOST_MPL_AUX_ARITY_SPEC(3, bind2)
BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(3, bind2)

namespace aux {

template<>
struct bind_chooser<2>
{
    template<
          typename F, typename T1, typename T2, typename T3, typename T4
        , typename T5
        >
    struct result_
    {
        typedef bind2< F,T1,T2 > type;
    };
};

} // namespace aux

template<
      typename F, typename T1, typename T2, typename T3
    >
struct bind3
{
    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
     private:
        typedef typename aux::resolve_bind_arg< F,U1,U2,U3,U4,U5 >::type f_;
        typedef aux::resolve_bind_arg< T1,U1,U2,U3,U4,U5 > t1;
        typedef aux::resolve_bind_arg< T2,U1,U2,U3,U4,U5 > t2;
        typedef aux::resolve_bind_arg< T3,U1,U2,U3,U4,U5 > t3;

     public:
        typedef typename apply_wrap3<
              f_
            , typename t1::type, typename t2::type, typename t3::type
            >::type type;

    };
};

namespace aux {

template<
      typename F, typename T1, typename T2, typename T3
    >
aux::yes_tag
is_bind_helper(bind3< F,T1,T2,T3 >*);

} // namespace aux

BOOST_MPL_AUX_ARITY_SPEC(4, bind3)
BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(4, bind3)

namespace aux {

template<>
struct bind_chooser<3>
{
    template<
          typename F, typename T1, typename T2, typename T3, typename T4
        , typename T5
        >
    struct result_
    {
        typedef bind3< F,T1,T2,T3 > type;
    };
};

} // namespace aux

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct bind4
{
    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
     private:
        typedef typename aux::resolve_bind_arg< F,U1,U2,U3,U4,U5 >::type f_;
        typedef aux::resolve_bind_arg< T1,U1,U2,U3,U4,U5 > t1;
        typedef aux::resolve_bind_arg< T2,U1,U2,U3,U4,U5 > t2;
        typedef aux::resolve_bind_arg< T3,U1,U2,U3,U4,U5 > t3;
        typedef aux::resolve_bind_arg< T4,U1,U2,U3,U4,U5 > t4;

     public:
        typedef typename apply_wrap4<
              f_
            , typename t1::type, typename t2::type, typename t3::type
            , typename t4::type
            >::type type;

    };
};

namespace aux {

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
aux::yes_tag
is_bind_helper(bind4< F,T1,T2,T3,T4 >*);

} // namespace aux

BOOST_MPL_AUX_ARITY_SPEC(5, bind4)
BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(5, bind4)

namespace aux {

template<>
struct bind_chooser<4>
{
    template<
          typename F, typename T1, typename T2, typename T3, typename T4
        , typename T5
        >
    struct result_
    {
        typedef bind4< F,T1,T2,T3,T4 > type;
    };
};

} // namespace aux

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct bind5
{
    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
     private:
        typedef typename aux::resolve_bind_arg< F,U1,U2,U3,U4,U5 >::type f_;
        typedef aux::resolve_bind_arg< T1,U1,U2,U3,U4,U5 > t1;
        typedef aux::resolve_bind_arg< T2,U1,U2,U3,U4,U5 > t2;
        typedef aux::resolve_bind_arg< T3,U1,U2,U3,U4,U5 > t3;
        typedef aux::resolve_bind_arg< T4,U1,U2,U3,U4,U5 > t4;
        typedef aux::resolve_bind_arg< T5,U1,U2,U3,U4,U5 > t5;

     public:
        typedef typename apply_wrap5<
              f_
            , typename t1::type, typename t2::type, typename t3::type
            , typename t4::type, typename t5::type
            >::type type;

    };
};

namespace aux {

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
aux::yes_tag
is_bind_helper(bind5< F,T1,T2,T3,T4,T5 >*);

} // namespace aux

BOOST_MPL_AUX_ARITY_SPEC(6, bind5)
BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(6, bind5)

namespace aux {

template<>
struct bind_chooser<5>
{
    template<
          typename F, typename T1, typename T2, typename T3, typename T4
        , typename T5
        >
    struct result_
    {
        typedef bind5< F,T1,T2,T3,T4,T5 > type;
    };
};

} // namespace aux

namespace aux {

template< typename T >
struct is_bind_arg
{
    BOOST_STATIC_CONSTANT(bool, value  = true);
};

template<>
struct is_bind_arg<na>
{
    BOOST_STATIC_CONSTANT(bool, value  = false);
};

template<
      typename T1, typename T2, typename T3, typename T4, typename T5
    >
struct bind_count_args
{
    BOOST_STATIC_CONSTANT(int, value =
          is_bind_arg<T1>::value + is_bind_arg<T2>::value 
        + is_bind_arg<T3>::value + is_bind_arg<T4>::value 
        + is_bind_arg<T5>::value
        );

};

}

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct bind
    : aux::bind_chooser<
          aux::bind_count_args< T1,T2,T3,T4,T5 >::value
        >::template result_< F,T1,T2,T3,T4,T5 >::type
{
};

BOOST_MPL_AUX_ARITY_SPEC(
      6
    , bind
    )

BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(
      6
    , bind
    )
}}


/* basic_bind.hpp
EogUIqOT1idJm7RJm7RJm7RJm7RJm7SpqNOfkv/3b+fyOPP/aR+r8/+sXGfI/79fhPz/qu2q/L+/X3hgO5ci5f+NufAUC+MAOBrWS2P+83LhnnL/+F4sL/6ktHlzTptpahFyY4bcd8C23Llw9205ufBa20z5bNM9/t9uNS0z5bNXbMk/PsCDzflz3Fc3585xrzTNu+rL/LzlyeS4qxWQ40435e8KH0v9gmz7GXK8hBtzxjHGbf9oeepqZnLGnWVFa6XOVVJnwuumOslTP/w98ubqjJMV1ZPXmyNxX+lvsclUZ9i0iPBCX2sF5V/D2T/qOn0lN+6F5dETyY1zwdZUpyk37vEQdRaWG7+VJ+97ReY5rsweRxfy5IFTjcdRUJ7x3eX/U1R58AqqPPhMmc+Q34mYIvOZMh8mx2VS3vHhVWOQTyKqMp+c8xx8xoUGBBpz8/Gsx+MpQ94vZgPbE9XH/gs0St3f40U57pV+RM4bc49P3tp4XEqefr/srz2oz9MvNe6v3Hl634fYZxby9Bb7MlQrIE+foeXp/2fz9K/p8/SDJm16oVQpl75pt0I92rY5suuvz9Ov2m45T99V8vRuaI3dUPLifP+wnBcvL2NwV0A7fAbrY0VsjJWwGVbGNlgF+6E9DsDqeB8vlJDvDPIdQqmnnSF/z8Q+k7z4UbTDk1gf38PWeAq74GnsiWcwFN/HWZiI8/EcLscPcA+ex7fwIh7GS3gar+ANvIpf4UdYmbYkYV38BLviNeyDyTgQr2MQfoohmII78HOMwxt4GG/ix3gLP8VUvI1f48/4DWbjbRkjOg2fwjtYE79FJ/wO++L3OAx/wDGYjv74DwzAHzESM3Ap3sNYzMS9+AsmYhZ+gP/CZMzGH/F3/Bf+gb+jMpbqA3wKa5TimMBaWA4NeW35HoIzzOS1R0t+zBsr4xishj7YAH3RGf2wJY7DrhiAQzEQfXE8huBEDMcgU/8S+U6Ca/P3LzGNo9AbnbAPNsG+2Bz7oyt6YHccgANwII7AQRiEg3EyDsOX0ROX4QhchSPR8PqT7ytYz8zrz0EZSx5roSPWlu2YVUq+c8h3Ecrpn0O6fPcLlucxGWviVKyL4dgII7A9TsdeOEO230wchS/iBJyNYfgyvohzcD7OxeWS996A83AXLsCDuBC/xUWYiYsxG5fIGNRLsSMuQy+MxrG4HCfgCgzDlTgXV2E0rsZ1uAZfx824C7dgHG7FY7gNT2EMfo9vYAbG4s+4G5W84R6siG9iDdyHdfFtbIQHsAkexBYYj53wXXTHE+iP7+EUPIVz8DSuwgTcoMpzn8Wr+D5+hJcwBS/jl3gF7+JV/B6TsBL79Bo2xGTshJ/iUEzBKXgDl+FN3I5fYBx+icfxKzyJX+NZ/AbP4x38Ar/HTEzH3/HvWMaK9wmsiD9iZczAmngPnVCfr8Z/oidm4hj8Bf0xCwPwVwzB3zAM/4WvoJKXXoSlMAafwr1YBi9iWfwIy+HX+DR+jzaYjeWxdGk+R7A82mFbrILdsBr2Q3scjNXRC2viWHRAX6yFy9AR12E9fB3r4050wv34LL6LDfAINsYz2AQvozN+jM3xLrbAe9gSf8NWWIbXa2u0xTZYA9tifWyHztgeW2EHfA47oid2Qv3nYkn5DivfbZVjX3n/OSn9YLrI52JXC7+50Bu7YB/sif1wGHqgNw7A8TgQQ3EQzsLBOB+H4Br0xHM4HH/BEdhU+m11QC/sgaMwAEfjC/g8TkdvnINj8S30wZPoiz+in/zWgT864zhshYHYCcejO07EwRiEI3ES+mEwzsUQ3IihuBPD8DpOwds4DX/A6XgPZ6DyupuJdXEWNsEXsQ2+hK44G8c=
*/