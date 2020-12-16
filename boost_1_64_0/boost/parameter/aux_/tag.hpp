// Copyright David Abrahams 2005.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_TAG_DWA2005610_HPP
#define BOOST_PARAMETER_AUX_TAG_DWA2005610_HPP

#include <boost/parameter/aux_/unwrap_cv_reference.hpp>
#include <boost/parameter/aux_/tagged_argument.hpp>
#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11) && \
    !BOOST_WORKAROUND(BOOST_MSVC, >= 1910)
// MSVC-14.1+ assigns rvalue references to tagged_argument instances
// instead of tagged_argument_rref instances with this code.
#include <boost/mp11/integral.hpp>
#include <boost/mp11/utility.hpp>
#include <type_traits>

namespace boost { namespace parameter { namespace aux { 

    template <typename Keyword, typename Arg>
    struct tag_if_lvalue_reference
    {
        using type = ::boost::parameter::aux::tagged_argument_list_of_1<
            ::boost::parameter::aux::tagged_argument<
                Keyword
              , typename ::boost::parameter::aux
                ::unwrap_cv_reference<Arg>::type
            >
        >;
    };

    template <typename Keyword, typename Arg>
    struct tag_if_scalar
    {
        using type = ::boost::parameter::aux::tagged_argument_list_of_1<
            ::boost::parameter::aux
            ::tagged_argument<Keyword,typename ::std::add_const<Arg>::type>
        >;
    };

    template <typename Keyword, typename Arg>
    using tag_if_otherwise = ::boost::mp11::mp_if<
        ::std::is_scalar<typename ::std::remove_const<Arg>::type>
      , ::boost::parameter::aux::tag_if_scalar<Keyword,Arg>
      , ::boost::mp11::mp_identity<
            ::boost::parameter::aux::tagged_argument_list_of_1<
                ::boost::parameter::aux::tagged_argument_rref<Keyword,Arg>
            >
        >
    >;

    template <typename Keyword, typename Arg>
    using tag = ::boost::mp11::mp_if<
        ::boost::mp11::mp_if<
            ::std::is_lvalue_reference<Arg>
          , ::boost::mp11::mp_true
          , ::boost::parameter::aux::is_cv_reference_wrapper<Arg>
        >
      , ::boost::parameter::aux::tag_if_lvalue_reference<Keyword,Arg>
      , ::boost::parameter::aux::tag_if_otherwise<Keyword,Arg>
    >;
}}} // namespace boost::parameter::aux_

#elif defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/is_scalar.hpp>
#include <boost/type_traits/is_lvalue_reference.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace parameter { namespace aux { 

    template <typename Keyword, typename ActualArg>
    struct tag
    {
        typedef typename ::boost::parameter::aux
        ::unwrap_cv_reference<ActualArg>::type Arg;
        typedef typename ::boost::add_const<Arg>::type ConstArg;
        typedef typename ::boost::remove_const<Arg>::type MutArg;
        typedef typename ::boost::mpl::eval_if<
            typename ::boost::mpl::if_<
                ::boost::is_lvalue_reference<ActualArg>
              , ::boost::mpl::true_
              , ::boost::parameter::aux::is_cv_reference_wrapper<ActualArg>
            >::type
          , ::boost::mpl::identity<
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
                ::boost::parameter::aux::tagged_argument_list_of_1<
#endif
                    ::boost::parameter::aux::tagged_argument<Keyword,Arg>
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
                >
#endif
            >
          , ::boost::mpl::if_<
                ::boost::is_scalar<MutArg>
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
              , ::boost::parameter::aux::tagged_argument_list_of_1<
                    ::boost::parameter::aux::tagged_argument<Keyword,ConstArg>
                >
              , ::boost::parameter::aux::tagged_argument_list_of_1<
                    ::boost::parameter::aux::tagged_argument_rref<Keyword,Arg>
                >
#else
              , ::boost::parameter::aux::tagged_argument<Keyword,ConstArg>
              , ::boost::parameter::aux::tagged_argument_rref<Keyword,Arg>
#endif
            >
        >::type type;
    };
}}} // namespace boost::parameter::aux_

#else   // !defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)

namespace boost { namespace parameter { namespace aux { 

    template <
        typename Keyword
      , typename Arg
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
      , typename = typename ::boost::parameter::aux
        ::is_cv_reference_wrapper<Arg>::type
#endif
    >
    struct tag
    {
        typedef ::boost::parameter::aux::tagged_argument<
            Keyword
          , typename ::boost::parameter::aux::unwrap_cv_reference<Arg>::type
        > type;
    };
}}} // namespace boost::parameter::aux_

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace boost { namespace parameter { namespace aux { 

    template <typename Keyword, typename Arg>
    struct tag<Keyword,Arg,::boost::mpl::false_>
    {
        typedef ::boost::parameter::aux::tagged_argument<
            Keyword
          , typename ::boost::remove_reference<Arg>::type
        > type;
    };
}}} // namespace boost::parameter::aux_

#endif  // Borland workarounds needed.
#endif  // MP11 or perfect forwarding support
#endif  // include guard


/* tag.hpp
95r+zmvpO5ZT8xyG/eI/3PX+p6+npS14/aqZxbc8dIKzPAca9vc/cecre/8y7dycqGejW4V8d4WNvc2G/cYPwi+9wXnFT5elhL/4Vsonb9hs00IM+0Yf5IWVjLt80cehN5Ymtci8n32tyv7BNYXDtgZ8+dGLD6T8887VSx/gWa+KNy3tway/7/0xdtj+OfHD7onfxfsRYYa98+XI/PHT2tx356NPjvg5cXceeytU+h8dNXvkiaDlD87bVPfw7odW7mRtKtSwdzxQnJg07+ylcefiIuv9afwB9hEFG/bnD70asm7eghWXfXg2t/ia5MN8R0Ol/2SfofEzUpcveym2+/LQwz//AxXVMuzjXpm77HyzkS8umTnoiRtf+ONunkWpcPoPyYs7OvJ069DS+MPzO557mXgnGPY/NXmzlX1WdNM1o6fuCbqx52vUL6dhXx5305kFV945+oaWI+6JSA89xvMxFf4zt05b1XrZs4Wf1P9p85nUpmy8bKb0s3fOe2/888ytp2fd3KT+U8uuCeK+XuUrxpU/8J0rT0xumbzmprmzHjnDWSEqnO7fpTbPOjt3yebLRseeCL55PutLgYb92bO11m26ZPni7n+pKIvpeITK/KJy//C9D2YsCnD+3Cev8yNTjnRm7fNSpecTyxLuarNzyvkFpzY+t3Bjk8e4D1TpL90z+cYzJ5u/8d5tfeNbH+1Cfk8qPfzZVXdbdnr6jp6BrS6d1rhfQ9Y9gwz72VFrXn11WtzVe+6b+KfDLa7pxLuJKv1P/W7w6fNdO713++efvJ5nz3vbZrtMpXNakxYJW+uvfuKHWc8sfeemU8O471HxDn1m05C//fOxgV8/csfaWo8mr6e/UO5/l1Bw9voxE1o5r50QNvfzgvc4lyjAsP/ryqNv9CkovnfBt7PHP5n4MG4fdKj69mTQ8817LP+h4/qQR0dl3fkm3xM02jjCH/d8bg4w5lim3w+bfnMPpn+fNNm3MNl/I/YD+X3K9LtBtPd3XdPv5qbfUabfcabfkfzOpK4/gfkS+V2AxMjvbxH6EvV7vIPyEvvORhrwswuqb1fKNzuNa9ca4xv2xt93gbaKWvAnGAn/CdMhXUVFF2CHXeHjsCd0wMEwEF4Fg+BwGAxHwRA4FtaCU6ELLoJ14FIYDn8PI+GtMAquhNHwDlgProX14XoYC++FKXAjbA4fknBfhnFwJ2wIX4ON4JuwMXwLJsC9sCncB5vBD2ESPAhbwMOwNTwH28Kf4CXwn7AdDEBn7WEQTIdhsCOsDTvDKNgFRsOusAHsBhvCHjAB9oSJsBdsDnvDFjADtoX9YBq8DHaEl8NCeAWcBIfAUpgJZ8Ar4Wx4FZwPs+BiOBzeBEfA5XAUXAVHw7VwDFwPx8L7JZ7n4Xj4MsyDO2E2fAPmwLfhdfA9OBPuF3/H4Gz4OZwDvxL7KOphAawPC2EDeD1sDOfBBFgEk2ExbA4vh5fASTAdlsBOcArsBqfCHuJuBCyHY+AMOA5Og3lwOiyAC+BEuBCWiL9yuATOgYthBbwZroe3wPvhcrgRroAPw5XwUbgKboGr4ZNwA3wG3gefg3fAl+AauF3C3QfXwQ/hnfAgXA8Pw3vgEXH3D/gH+A3cCM/CR2E8bfQxmAgfh0Z7TtPfH5Tzw/jhhJ73/iuCbRUGF8C6cCE8BXOQUvGXJv5CYZb4u1/8PQAbwYdgE7gJJsAHYbLYNxf7VPgHeImYT8GRyBaJJ17iCYGDJZ5d5MPgmzAE7oYR8C1YD+6BsfBd2EDMDcV8CpYihyX89hJ+GMyX8G+QfCyBAXAprAVvkvzcDJvCW2Ai/D1sLvYtxL4lXAbbidmjv4SB/vW3QuJdKfo=
*/