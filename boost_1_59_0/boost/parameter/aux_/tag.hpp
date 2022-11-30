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
#if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))
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

#if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))
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
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
*/