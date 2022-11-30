// Copyright Daniel Wallin 2006.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_FUNCTION_CAST_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_FUNCTION_CAST_HPP

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)

namespace boost { namespace parameter { namespace aux {

    // Handles possible implicit casts.  Used by preprocessor.hpp
    // to normalize user input.
    //
    // cast<void*>::execute() is identity
    // cast<void*(X)>::execute() is identity
    // cast<void(X)>::execute() casts to X
    //
    // preprocessor.hpp uses this like this:
    //
    //     #define X(value, predicate)
    //         cast<void predicate>::execute(value)
    //
    //     X(something, *)
    //     X(something, *(predicate))
    //     X(something, (int))
    template <typename VoidExpr, typename Args>
    struct cast;
}}} // namespace boost::parameter::aux

#include <boost/parameter/aux_/use_default_tag.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename T, typename B>
    inline ::boost::parameter::aux::use_default_tag
        forward(::boost::parameter::aux::use_default_tag)
    {
        return ::boost::parameter::aux::use_default_tag();
    }
}}} // namespace boost::parameter::aux

#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/integral.hpp>
#include <boost/mp11/utility.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename Args>
    struct cast<void*,Args>
    {
        template <typename T, typename B>
        struct apply
        {
            typedef typename ::boost::mpl
            ::if_<B,T,::boost::mpl::true_>::type type;
        };

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        template <typename T, typename B>
        using fn = ::boost::mp11::mp_if<B,T,::boost::mp11::mp_true>;
#endif
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/aux_/void.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename Predicate, typename Args>
    struct cast<void*(Predicate),Args>
      : ::boost::parameter::aux::cast<void*,Args>
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/mpl/placeholders.hpp>

namespace boost { namespace parameter { namespace aux {

    // This is a hack used in cast<> to turn the user supplied type,
    // which may or may not be a placeholder expression, into one,
    // so that it will be properly evaluated by mpl::apply.
    template <typename T, typename Dummy = ::boost::mpl::_1>
    struct as_placeholder_expr
    {
        typedef T type;
    };
}}} // namespace boost::parameter::aux

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/list.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename Target, typename Source, typename Args>
    struct apply_target_fn
    {
        using type = ::boost::mp11
        ::mp_apply_q<Target,::boost::mp11::mp_list<Source,Args> >;
    };
}}} // namespace boost::parameter::aux

#endif

#include <boost/mpl/apply.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/parameter/aux_/has_nested_template_fn.hpp>
#include <type_traits>
#else
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename Target, typename Source, typename Args>
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
    using is_target_same_as_source = ::std::is_same<
        typename ::std::remove_const<
            typename ::std::remove_reference<
                typename ::boost::mp11::mp_if<
                    ::boost::parameter::aux::has_nested_template_fn<Target>
                  , ::boost::parameter::aux
                    ::apply_target_fn<Target,Source,Args>
                  , ::boost::mpl::apply2<
                        ::boost::parameter::aux::as_placeholder_expr<Target>
                      , Source
                      , Args
                    >
                >::type
            >::type
        >::type
      , typename ::std::remove_const<Source>::type
    >;
#else   // !defined(BOOST_PARAMETER_CAN_USE_MP11)
    struct is_target_same_as_source
      : ::boost::mpl::if_<
            ::boost::is_same<
                typename ::boost::remove_const<
                    typename ::boost::remove_reference<
                        typename ::boost::mpl::apply2<
                            ::boost::parameter::aux
                            ::as_placeholder_expr<Target>
                          , Source
                          , Args
                        >::type
                    >::type
                >::type
              , typename ::boost::remove_const<Source>::type
            >
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        >::type
    {
    };
#endif  // BOOST_PARAMETER_CAN_USE_MP11
}}} // namespace boost::parameter::aux

#if !defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/is_const.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    // Covers the case where is_convertible<Source,Target> but not
    // is_same<Source,Target>.  Use cases are covered
    // by test/normalize_argument_types.cpp
    template <typename Source, typename Target>
    class cast_convert
    {
        typedef ::boost::parameter::aux::cast_convert<Source,Target> _self;

     public:
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        using type = typename ::boost::mp11::mp_if<
            ::std::is_const<Source>
          , ::std::add_const<Target>
          , ::std::remove_const<Target>
        >::type;
#else
        typedef typename boost::mpl::eval_if<
            ::boost::is_const<Source>
          , ::boost::add_const<Target>
          , ::boost::remove_const<Target>
        >::type type;
#endif

     private:
        inline static typename _self::type
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
            _copy(typename ::std::remove_const<Target>::type value)
#else
            _copy(typename ::boost::remove_const<Target>::type value)
#endif
        {
            return value;
        }

     public:
        inline static typename _self::type evaluate(Source&& source)
        {
            return _self::_copy(source);
        }
    };

    template <typename Target, typename Source, typename Args>
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
    using cast_impl = ::std::remove_reference<
        typename ::boost::mp11::mp_if<
            ::boost::parameter::aux::has_nested_template_fn<Target>
          , ::boost::parameter::aux
            ::is_target_same_as_source<Target,Source,Args>
          , ::boost::mpl::apply2<
                ::boost::parameter::aux::as_placeholder_expr<Target>
              , Source
              , Args
            >
        >::type
    >;
#else
    struct cast_impl
      : ::boost::remove_reference<
            typename ::boost::mpl::apply2<
                ::boost::parameter::aux::as_placeholder_expr<Target>
              , Source
              , Args
            >::type
        >
    {
    };
#endif  // BOOST_PARAMETER_CAN_USE_MP11
}}} // namespace boost::parameter::aux

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename Target, typename Args>
    struct cast<void(Target),Args>
    {
        template <typename T, typename B>
        struct apply
        {
            typedef typename ::boost::mpl::eval_if<
                B
              , ::boost::mpl::eval_if<
                    ::boost::parameter::aux
                    ::is_target_same_as_source<Target,T,Args>
                  , ::boost::mpl::identity<T>
                  , ::boost::parameter::aux::cast_impl<Target,T,Args>
                >
              , ::boost::parameter::aux
                ::is_target_same_as_source<Target,T,Args>
            >::type type;
        };

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        template <typename T, typename B>
        using fn = typename ::boost::mp11::mp_if<
            B
          , ::boost::mp11::mp_if<
                ::boost::parameter::aux
                ::is_target_same_as_source<Target,T,Args>
              , ::boost::mp11::mp_identity<T>
              , ::boost::parameter::aux::cast_impl<Target,T,Args>
            >
          , ::boost::parameter::aux
            ::is_target_same_as_source<Target,T,Args>
        >::type;
#endif
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/value_type.hpp>

#if !defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mpl/apply_wrap.hpp>
#endif

// Expands to the target type of the argument as indicated by the predicate.
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#define BOOST_PARAMETER_FUNCTION_CAST_T(tag, predicate, args)                \
    ::boost::mp11::mp_apply_q<                                               \
        ::boost::parameter::aux::cast<void predicate, args>                  \
      , ::boost::mp11::mp_list<                                              \
            typename ::boost::parameter::value_type<                         \
                args                                                         \
              , tag                                                          \
              , ::boost::parameter::aux::use_default_tag                     \
            >::type                                                          \
          , ::boost::mp11::mp_true                                           \
        >                                                                    \
    >
/**/
#else   // !defined(BOOST_PARAMETER_CAN_USE_MP11)
#define BOOST_PARAMETER_FUNCTION_CAST_T(tag, predicate, args)                \
    typename ::boost::mpl::apply_wrap2<                                      \
        ::boost::parameter::aux::cast<void predicate, args>                  \
      , typename ::boost::parameter::value_type<                             \
            args                                                             \
          , tag                                                              \
          , ::boost::parameter::aux::use_default_tag                         \
        >::type                                                              \
      , ::boost::mpl::true_                                                  \
    >::type
/**/
#endif  // BOOST_PARAMETER_CAN_USE_MP11

// Expands to boost::mpl::true_ if and only if the argument's source and
// target types are the same.
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#define BOOST_PARAMETER_FUNCTION_CAST_B(tag, predicate, args)                \
    ::boost::mp11::mp_apply_q<                                               \
        ::boost::parameter::aux::cast<void predicate, args>                  \
      , ::boost::mp11::mp_list<                                              \
            typename ::boost::parameter::value_type<                         \
                args                                                         \
              , tag                                                          \
              , ::boost::parameter::aux::use_default_tag                     \
            >::type                                                          \
          , ::boost::mp11::mp_false                                          \
        >                                                                    \
    >
/**/
#else   // !defined(BOOST_PARAMETER_CAN_USE_MP11)
#define BOOST_PARAMETER_FUNCTION_CAST_B(tag, predicate, args)                \
    typename ::boost::mpl::apply_wrap2<                                      \
        ::boost::parameter::aux::cast<void predicate, args>                  \
      , typename ::boost::parameter::value_type<                             \
            args                                                             \
          , tag                                                              \
          , ::boost::parameter::aux::use_default_tag                         \
        >::type                                                              \
      , ::boost::mpl::false_                                                 \
    >::type
/**/
#endif  // BOOST_PARAMETER_CAN_USE_MP11

#include <boost/core/enable_if.hpp>
#include <utility>

namespace boost { namespace parameter { namespace aux {

    // If the source and target types are not the same,
    // then perform an implicit conversion.
    template <typename Target, typename B, typename Source>
    inline typename ::boost::lazy_disable_if<
        B
      , ::boost::parameter::aux::cast_convert<Source,Target>
    >::type
        forward(Source&& source)
    {
        return ::boost::parameter::aux::cast_convert<Source,Target>
        ::evaluate(::std::forward<Source>(source));
    }

    // If the source and target types are the same,
    // then simply forward the argument.
    // However, treat rvalue references to scalars as const lvalue references.
    template <typename T, typename B>
    inline typename ::boost::enable_if<B,T const&>::type forward(T const& t)
    {
        return t;
    }

    template <typename T, typename B>
    inline typename ::boost::enable_if<
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        ::boost::mp11::mp_if<
            B
          , ::boost::mp11::mp_if<
                ::std::is_const<T>
              , ::boost::mp11::mp_false
              , ::boost::mp11::mp_true
            >
          , ::boost::mp11::mp_false
        >
#else
        typename ::boost::mpl::eval_if<
            B
          , ::boost::mpl::if_<
                ::boost::is_const<T>
              , ::boost::mpl::false_
              , ::boost::mpl::true_
            >
          , ::boost::mpl::false_
        >::type
#endif  // BOOST_PARAMETER_CAN_USE_MP11
      , T&
    >::type
        forward(T& t)
    {
        return t;
    }
}}} // namespace boost::parameter::aux

#include <boost/type_traits/is_scalar.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename T, typename B>
    inline typename ::boost::enable_if<
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        ::boost::mp11::mp_if<
            B
          , ::boost::mp11::mp_if<
                ::std::is_scalar<T>
              , ::boost::mp11::mp_false
              , ::boost::mp11::mp_true
            >
          , ::boost::mp11::mp_false
        >
#else
        typename ::boost::mpl::eval_if<
            B
          , ::boost::mpl::if_<
                ::boost::is_scalar<T>
              , ::boost::mpl::false_
              , ::boost::mpl::true_
            >
          , ::boost::mpl::false_
        >::type
#endif  // BOOST_PARAMETER_CAN_USE_MP11
      , T const&&
    >::type
        forward(T const&& t)
    {
        return static_cast<T const&&>(t);
    }

    template <typename T, typename B>
    inline typename ::boost::enable_if<
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        ::boost::mp11::mp_if<
            B
          , ::boost::mp11::mp_if<
                ::std::is_scalar<T>
              , ::boost::mp11::mp_false
              , ::boost::mp11::mp_true
            >
          , ::boost::mp11::mp_false
        >
#else
        typename ::boost::mpl::eval_if<
            B
          , ::boost::mpl::if_<
                ::boost::is_scalar<T>
              , ::boost::mpl::false_
              , ::boost::mpl::true_
            >
          , ::boost::mpl::false_
        >::type
#endif  // BOOST_PARAMETER_CAN_USE_MP11
      , T&&
    >::type
        forward(T&& t)
    {
        return ::std::forward<T>(t);
    }
}}} // namespace boost::parameter::aux

#elif BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))
#define BOOST_PARAMETER_FUNCTION_CAST_T(value_t, predicate, args) value_t
#define BOOST_PARAMETER_FUNCTION_CAST_B(value, predicate, args) value
#else   // no perfect forwarding support and no Borland workarounds needed

namespace boost { namespace parameter { namespace aux {

    // Handles possible implicit casts.  Used by preprocessor.hpp
    // to normalize user input.
    //
    // cast<void*>::execute() is identity
    // cast<void*(X)>::execute() is identity
    // cast<void(X)>::execute() casts to X
    //
    // preprocessor.hpp uses this like this:
    //
    //     #define X(value, predicate)
    //         cast<void predicate>::execute(value)
    //
    //     X(something, *)
    //     X(something, *(predicate))
    //     X(something, (int))
    template <typename VoidExpr, typename Args>
    struct cast;
}}} // namespace boost::parameter::aux

#include <boost/parameter/aux_/use_default_tag.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename Args>
    struct cast<void*,Args>
    {
        template <typename T>
        struct apply
        {
            typedef T& type;
        };

        inline static ::boost::parameter::aux::use_default_tag
            execute(::boost::parameter::aux::use_default_tag)
        {
            return ::boost::parameter::aux::use_default_tag();
        }

        template <typename U>
        inline static U& execute(U& value)
        {
            return value;
        }
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/aux_/void.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename Predicate, typename Args>
#if BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x580))
    struct cast< ::boost::parameter::aux::voidstar(Predicate),Args>
#else
    struct cast<void*(Predicate),Args>
#endif
      : ::boost::parameter::aux::cast<void*,Args>
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/mpl/placeholders.hpp>

namespace boost { namespace parameter { namespace aux {

    // This is a hack used in cast<> to turn the user supplied type,
    // which may or may not be a placeholder expression, into one,
    // so that it will be properly evaluated by mpl::apply.
    template <typename T, typename Dummy = ::boost::mpl::_1>
    struct as_placeholder_expr
    {
        typedef T type;
    };
}}} // namespace boost::parameter::aux

#include <boost/mpl/apply.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename Target, typename Source, typename Args>
    struct is_target_same_as_source
      : ::boost::mpl::if_<
            ::boost::is_same<
                typename ::boost::remove_const<
                    typename ::boost::remove_reference<
                        typename ::boost::mpl::apply2<
                            ::boost::parameter::aux
                            ::as_placeholder_expr<Target>
                          , Source
                          , Args
                        >::type
                    >::type
                >::type
              , typename ::boost::remove_const<Source>::type
            >
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        >::type
    {
    };

    template <
        typename Target
      , typename Source
      , typename Args
      , typename Enable = ::boost::parameter::aux
        ::is_target_same_as_source<Target,Source,Args>
    >
    struct cast_impl
    {
        typedef Source& type;

        inline static Source& evaluate(Source& value)
        {
            return value;
        }
    };
}}} // namespace boost::parameter::aux

#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_lvalue_reference.hpp>

namespace boost { namespace parameter { namespace aux {

    // Covers the case where is_convertible<Source,Target> but not
    // is_same<Source,Target>.  Use cases are covered
    // by test/normalize_argument_types.cpp
    template <typename Source, typename Target>
    class cast_convert
    {
        typedef ::boost::parameter::aux::cast_convert<Source,Target> _self;

     public:
        typedef typename ::boost::add_lvalue_reference<
            typename ::boost::add_const<Target>::type
        >::type type;

     private:
        template <typename U>
        inline static typename _self::type _mod_const(U const& u)
        {
            return u;
        }

        inline static Target _copy(Target value)
        {
            return value;
        }

     public:
        inline static typename _self::type evaluate(Source& source)
        {
            return _self::_mod_const(_self::_copy(source));
        }
    };

    template <typename Target, typename Source, typename Args>
    struct cast_impl<Target,Source,Args,::boost::mpl::false_>
      : ::boost::parameter::aux::cast_convert<
            Source,
            typename ::boost::mpl::apply2<
                ::boost::parameter::aux::as_placeholder_expr<Target>
              , Source
              , Args
            >::type
        >
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/mpl/eval_if.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename Target, typename Args>
    struct cast<void(Target),Args>
    {
        template <typename T>
        struct apply
        {
            typedef typename ::boost::mpl::eval_if<
                    ::boost::parameter::aux
                    ::is_target_same_as_source<Target,T,Args>
                  , ::boost::add_lvalue_reference<T>
                  , ::boost::parameter::aux::cast_impl<
                        Target
                      , T
                      , Args
                      , ::boost::mpl::false_
                    >
            >::type type;
        };

        inline static ::boost::parameter::aux::use_default_tag
            execute(::boost::parameter::aux::use_default_tag)
        {
            return ::boost::parameter::aux::use_default_tag();
        }

        template <typename U>
        inline static typename ::boost::parameter::aux
        ::cast_impl<Target,U const,Args>::type
            execute(U const& value)
        {
            return ::boost::parameter::aux
            ::cast_impl<Target,U const,Args>::evaluate(value);
        }

        template <typename U>
        inline static typename ::boost::parameter::aux
        ::cast_impl<Target,U,Args>::type
            execute(U& value)
        {
            return ::boost::parameter::aux
            ::cast_impl<Target,U,Args>::evaluate(value);
        }
    };
}}} // namespace boost::parameter::aux

#include <boost/mpl/apply_wrap.hpp>
#include <boost/parameter/value_type.hpp>

// Expands to the reference-qualified target type of the argument
// as indicated by the predicate.
#define BOOST_PARAMETER_FUNCTION_CAST_T(tag, predicate, args)                \
    typename ::boost::mpl::apply_wrap1<                                      \
        ::boost::parameter::aux::cast<void predicate, args>                  \
      , typename ::boost::parameter::value_type<                             \
            args                                                             \
          , tag                                                              \
          , ::boost::parameter::aux::use_default_tag                         \
        >::type                                                              \
    >::type
/**/

// Expands to the converted or passed-through value
// as indicated by the predicate.
#define BOOST_PARAMETER_FUNCTION_CAST_B(value, predicate, args)              \
    ::boost::parameter::aux::cast<void predicate, args>::execute(value)
/**/

#endif  // perfect forwarding support, or Borland workarounds needed
#endif  // include guard


/* function_cast.hpp
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
*/