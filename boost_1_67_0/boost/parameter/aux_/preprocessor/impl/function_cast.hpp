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

#elif BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
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