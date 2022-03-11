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
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
*/