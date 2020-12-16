
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
}}


/* basic_bind.hpp
TE2OL1kdzcfV/wfb49xWM+8u83U57ue+txx3/64usuyrwmX+lmWnCpd1sSx7qnCZn2VZXeuyLt0ty9bmW5dZ1xtpXdY5wLLst++sy6zlLi5cZs0bbF3m18Oy7Otz1mXWvB8WLuviIv28lnWZv2mdF83zkRFRyidKv5/VUP9eRnMvyuhXGJ/g6mZ6V6bDvtlTjvuByvLODYmBeQ8PKMf9R/vjHpaSmuxSorgX/XpTUam3xB7IsqkR8WkGeZ/EKuodUsn8DrdfqQPY/C7HmGCuv6zLwyDzM7LWP7GubDdX1lViSfgBi836WbJ+nGr9M7J+orywUr1+Aes/wLIsWV/725e6qndRGtMiDelG2/yelc2/ab7jZ3fd8QjU6w6sbC5rhWrdfAfrrmHdCBemX2Rd7TtGVeObxEdEutSVOCCOjzJPs5i3p4zr0V727UhzF9N8kmpefY5Yxb0zZboi57GLpE3KeTTPtq/IGA4lOEfY9BN1PJSM/SG/WTLPU2fb+JvYRJvfKzHPKtb+oj1Gjs/P6y2VlL9x12S/vL6x3S8ZE6bEY9vejP1S3We2/2zLZ2gNx2kNFXiK+b7KPmhiseLYnLSBTTt4VjXvhFGObzxpPfuw/JRtO8QmxiqbKfe/k7lS/m1yHFxxo9K/CmzLx2j2oNj31To6D5meH7AR/qlXJ/mM23+WprKOcWKk9ThIbJXNPrStbq7AkYrsA76LSl8q0HzXMA2aVIr3/ej1JbZh05eYt+tLqZEpNn2JedYpWV+S/bbup9K38jhGl6qZYwkmfyF9S9rL9JvB+NQE+U2fdX1v2qQvy547U7j+eZ311e0YJB+wAukL5/EV2iAr16YdJXiu9H2h8PeRmnZ0KV07Omg3df+wfvbIxzzZ5HPqQ7sEUonFzK88q/v3xdouvaRdQmkMZTrGyrfj+6j0L+M/9Nol2TAxiX/pjMftVsLPimlcIOWkpf4NqSxjT6SN1O2o/f1oyc7HSnv0o8AQ9m8Q8y9+pT5v2fcV9fhTx6RNgkmupPtIV5VrlIumNkkxpKYZw1L5eWspYo+pm7qf0C6FzxwvuTC53vxneaG1lOW359RYMKnl2V4X9/vvrJ8wKMbRMz7Hv3k9a1p+6OMxP74c3yT/+hOZ/U633M5FyLs1leVZ34xtvjb8lWqPVT9WwePypr1/vWeF+r+RdfTbXMfPFmc3VJafmRO19KUGF3fm1488e3juW+1L/8wx0EdZPqjf7v5h3f+1oP7zPg99m3pX2n/uWWQVH9Nx6fB69fsaDFv8zrmKVZsvTKlya55FbnaRewFyb2BBRdv3ZA2oIGMWYT0chE1xMPrgEOyMQzEEh+FoHIETcCQmYiguxlG4EkfjGhyDV9GA1zEGm1KPWGyOidgak1Cencp1P/9PfnOufnYaKc82J6IHRqEnGrADTlK9T2w0xuBkJJm2f9BFruvxsmy/Pu6Q7feS7QdhU+yD3ngPdsS+2A37YRD2x0Ga39hG40BMxPvwIRyM8zAYn8AhuA6H4hs4DE9iCH6Jw/EsjsCfMFTqP0rMqSjX/nIvQNmP0cq/UZmS5bimoAemYhJOxTk4DZ/GdHwOp+MmfAi34QzcgTPxTXwED2MGHsdZeAZn4z9wDn6Hc+U4zsM/cD4q8YCPY0tcjB1xGQbgcrwHV+FgfBJjcTWm4BqcgWtxIa7DZbge1+Iz+DxuwC34PO7EFzAHN+JpfAm/xk14Hl/BurTVq9gRt2B3fB0H4FYchlk4FndgJO7EDNyFj+MeXIl7MRP348t4ALfjW3gUD+IJfBtP4zuYh+/iL/ge/oYfYHVX/mZiO/wQu+BHGIg52B9P4Aj8O07AkxiGn2AMforJ+Dk=
*/