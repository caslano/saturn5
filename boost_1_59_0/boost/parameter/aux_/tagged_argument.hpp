// Copyright Daniel Wallin, David Abrahams 2005.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_TAGGED_ARGUMENT_050328_HPP
#define BOOST_PARAMETER_TAGGED_ARGUMENT_050328_HPP

namespace boost { namespace parameter { namespace aux {

    struct error_const_lvalue_bound_to_out_parameter;
    struct error_lvalue_bound_to_consume_parameter;
    struct error_rvalue_bound_to_out_parameter;
}}} // namespace boost::parameter::aux

#include <boost/parameter/keyword_fwd.hpp>
#include <boost/parameter/config.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/integral.hpp>
#include <boost/mp11/utility.hpp>
#include <type_traits>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename Keyword, typename Arg>
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
    using tagged_argument_type = ::boost::mp11::mp_if<
        ::boost::mp11::mp_if<
            ::std::is_scalar<Arg>
          , ::boost::mp11::mp_false
          , ::std::is_same<
                typename Keyword::qualifier
              , ::boost::parameter::consume_reference
            >
        >
      , ::boost::parameter::aux::error_lvalue_bound_to_consume_parameter
      , ::boost::mp11::mp_if<
            ::std::is_const<Arg>
          , ::boost::mp11::mp_if<
                ::std::is_same<
                    typename Keyword::qualifier
                  , ::boost::parameter::out_reference
                >
              , ::boost::parameter::aux
                ::error_const_lvalue_bound_to_out_parameter
              , ::std::remove_const<Arg>
            >
          , ::boost::mp11::mp_identity<Arg>
        >
    >;
#else   // !defined(BOOST_PARAMETER_CAN_USE_MP11)
    struct tagged_argument_type
      : ::boost::mpl::eval_if<
            ::boost::is_same<
                typename Keyword::qualifier
              , ::boost::parameter::out_reference
            >
          , ::boost::parameter::aux::error_const_lvalue_bound_to_out_parameter
          , ::boost::remove_const<Arg>
        >
    {
    };
#endif  // BOOST_PARAMETER_CAN_USE_MP11
}}} // namespace boost::parameter::aux

#include <boost/parameter/aux_/tagged_argument_fwd.hpp>
#include <boost/parameter/aux_/is_tagged_argument.hpp>
#include <boost/parameter/aux_/default.hpp>
#include <boost/parameter/aux_/void.hpp>
#include <boost/parameter/aux_/arg_list.hpp>
#include <boost/parameter/aux_/result_of0.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/type_traits/is_scalar.hpp>
#include <boost/type_traits/remove_reference.hpp>

#if defined(BOOST_NO_CXX11_HDR_FUNCTIONAL)
#include <boost/function.hpp>
#else
#include <functional>
#endif

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
#include <boost/core/enable_if.hpp>
#include <utility>

namespace boost { namespace parameter { namespace aux {

    // Holds an lvalue reference to an argument of type Arg associated with
    // keyword Keyword
    template <typename Keyword, typename Arg>
    class tagged_argument
      : public ::boost::parameter::aux::tagged_argument_base
    {
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        using arg_type = typename ::boost::parameter::aux
        ::tagged_argument_type<Keyword,Arg>::type;
#else
        typedef typename ::boost::mpl::eval_if<
            typename ::boost::mpl::eval_if<
                ::boost::is_scalar<Arg>
              , ::boost::mpl::false_
              , ::boost::is_same<
                    typename Keyword::qualifier
                  , ::boost::parameter::consume_reference
                >
            >::type
          , ::boost::parameter::aux::error_lvalue_bound_to_consume_parameter
          , ::boost::mpl::eval_if<
                ::boost::is_const<Arg>
              , ::boost::parameter::aux::tagged_argument_type<Keyword,Arg>
              , ::boost::mpl::identity<Arg>
            >
        >::type arg_type;
#endif  // BOOST_PARAMETER_CAN_USE_MP11

     public:
        typedef Keyword key_type;

        // Wrap plain (non-UDT) function objects in either
        // a boost::function or a std::function. -- Cromwell D. Enage
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        using value_type = ::boost::mp11::mp_if<
            ::std::is_function<arg_type>
          , ::std::function<arg_type>
          , Arg
        >;
#else   // !defined(BOOST_PARAMETER_CAN_USE_MP11)
        typedef typename ::boost::mpl::if_<
            ::boost::is_function<arg_type>
#if defined(BOOST_NO_CXX11_HDR_FUNCTIONAL)
          , ::boost::function<arg_type>
#else
          , ::std::function<arg_type>
#endif
          , Arg
        >::type value_type;
#endif  // BOOST_PARAMETER_CAN_USE_MP11

        // If Arg is void_, then this type will evaluate to void_&.  If the
        // supplied argument is a plain function, then this type will evaluate
        // to a reference-to-const function wrapper type.  If the supplied
        // argument is an lvalue, then Arg will be deduced to the lvalue
        // reference. -- Cromwell D. Enage
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        using reference = ::boost::mp11::mp_if<
            ::std::is_function<arg_type>
          , value_type const&
          , Arg&
        >;
#else
        typedef typename ::boost::mpl::if_<
            ::boost::is_function<arg_type>
          , value_type const&
          , Arg&
        >::type reference;
#endif

     private:
        // Store plain functions by value, everything else by reference.
        // -- Cromwell D. Enage
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        ::boost::mp11::mp_if<
            ::std::is_function<arg_type>
          , value_type
          , reference
        > value;
#else
        typename ::boost::mpl::if_<
            ::boost::is_function<arg_type>
          , value_type
          , reference
        >::type value;
#endif

     public:
        inline explicit BOOST_CONSTEXPR tagged_argument(reference x)
          : value(x)
        {
        }

        inline BOOST_CONSTEXPR tagged_argument(tagged_argument const& copy)
          : value(copy.value)
        {
        }

        // A metafunction class that, given a keyword and a default type,
        // returns the appropriate result type for a keyword lookup given
        // that default.
        struct binding
        {
            template <typename KW, typename Default, typename Reference>
            struct apply
              : ::boost::mpl::eval_if<
                    ::boost::is_same<KW,key_type>
                  , ::boost::mpl::if_<Reference,reference,value_type>
                  , ::boost::mpl::identity<Default>
                >
            {
            };

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
            template <typename KW, typename Default, typename Reference>
            using fn = ::boost::mp11::mp_if<
                ::std::is_same<KW,key_type>
              , ::boost::mp11::mp_if<Reference,reference,value_type>
              , Default
            >;
#endif
        };

#if !defined(BOOST_PARAMETER_CAN_USE_MP11)
        // Comma operator to compose argument list without using parameters<>.
        // Useful for argument lists with undetermined length.
        template <typename Keyword2, typename Arg2>
        inline BOOST_CONSTEXPR ::boost::parameter::aux::arg_list<
            ::boost::parameter::aux::tagged_argument<Keyword,Arg>
          , ::boost::parameter::aux::arg_list<
                ::boost::parameter::aux::tagged_argument<Keyword2,Arg2>
            >
        >
            operator,(
                ::boost::parameter::aux
                ::tagged_argument<Keyword2,Arg2> const& x
            ) const
        {
            return ::boost::parameter::aux::arg_list<
                ::boost::parameter::aux::tagged_argument<Keyword,Arg>
              , ::boost::parameter::aux::arg_list<
                    ::boost::parameter::aux::tagged_argument<Keyword2,Arg2>
                >
            >(
                *this
              , ::boost::parameter::aux::arg_list<
                    ::boost::parameter::aux::tagged_argument<Keyword2,Arg2>
                >(x, ::boost::parameter::aux::empty_arg_list())
            );
        }

        template <typename Keyword2, typename Arg2>
        inline BOOST_CONSTEXPR ::boost::parameter::aux::arg_list<
            ::boost::parameter::aux::tagged_argument<Keyword,Arg>
          , ::boost::parameter::aux::arg_list<
                ::boost::parameter::aux::tagged_argument_rref<Keyword2,Arg2>
            >
        >
            operator,(
                ::boost::parameter::aux
                ::tagged_argument_rref<Keyword2,Arg2> const& x
            ) const
        {
            return ::boost::parameter::aux::arg_list<
                ::boost::parameter::aux::tagged_argument<Keyword,Arg>
              , boost::parameter::aux::arg_list<
                    boost::parameter::aux::tagged_argument_rref<Keyword2,Arg2>
                >
            >(
                *this
              , ::boost::parameter::aux::arg_list<
                    ::boost::parameter::aux
                    ::tagged_argument_rref<Keyword2,Arg2>
                >(x, ::boost::parameter::aux::empty_arg_list())
            );
        }
#endif  // BOOST_PARAMETER_CAN_USE_MP11

        // Accessor interface.
        inline BOOST_CONSTEXPR reference get_value() const
        {
            return this->value;
        }

        inline BOOST_CONSTEXPR reference
            operator[](::boost::parameter::keyword<Keyword> const&) const
        {
            return this->get_value();
        }

        template <typename Default>
        inline BOOST_CONSTEXPR reference
            operator[](
                ::boost::parameter::aux::default_<key_type,Default> const&
            ) const
        {
            return this->get_value();
        }

        template <typename Default>
        inline BOOST_CONSTEXPR reference
            operator[](
                ::boost::parameter::aux::default_r_<key_type,Default> const&
            ) const
        {
            return this->get_value();
        }

        template <typename F>
        inline BOOST_CONSTEXPR reference
            operator[](
                ::boost::parameter::aux::lazy_default<key_type,F> const&
            ) const
        {
            return this->get_value();
        }

        template <typename KW, typename Default>
        inline BOOST_CONSTEXPR Default&
            operator[](
                ::boost::parameter::aux::default_<KW,Default> const& x
            ) const
        {
            return x.value;
        }

        template <typename KW, typename Default>
        inline BOOST_CONSTEXPR Default&&
            operator[](
                ::boost::parameter::aux::default_r_<KW,Default> const& x
            ) const
        {
            return ::std::forward<Default>(x.value);
        }

        template <typename KW, typename F>
        inline BOOST_CONSTEXPR
        typename ::boost::parameter::aux::result_of0<F>::type
            operator[](
                ::boost::parameter::aux::lazy_default<KW,F> const& x
            ) const
        {
            return x.compute_default();
        }

        template <typename ParameterRequirements>
        static BOOST_CONSTEXPR typename ParameterRequirements::has_default
            satisfies(ParameterRequirements*);

        template <typename HasDefault, typename Predicate>
        static BOOST_CONSTEXPR
        typename ::boost::mpl::apply_wrap1<Predicate,value_type>::type
            satisfies(
                ::boost::parameter::aux::parameter_requirements<
                    key_type
                  , Predicate
                  , HasDefault
                >*
            );

        // MPL sequence support
        // Convenience for users
        typedef ::boost::parameter::aux::tagged_argument<Keyword,Arg> type;
        // For the benefit of iterators
        typedef ::boost::parameter::aux::empty_arg_list tail_type;
        // For dispatching to sequence intrinsics
        typedef ::boost::parameter::aux::arg_list_tag tag;
    };

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
    template <typename Keyword>
    using tagged_argument_rref_key = ::boost::mp11::mp_if<
        ::std::is_same<
            typename Keyword::qualifier
          , ::boost::parameter::out_reference
        >
      , ::boost::parameter::aux::error_rvalue_bound_to_out_parameter
      , ::boost::mp11::mp_identity<Keyword>
    >;
#endif

    // Holds an rvalue reference to an argument of type Arg associated with
    // keyword Keyword
    template <typename Keyword, typename Arg>
    struct tagged_argument_rref
      : ::boost::parameter::aux::tagged_argument_base
    {
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        using key_type = typename ::boost::parameter::aux
        ::tagged_argument_rref_key<Keyword>::type;
#else
        typedef typename ::boost::mpl::eval_if<
            ::boost::is_same<
                typename Keyword::qualifier
              , ::boost::parameter::out_reference
            >
          , ::boost::parameter::aux::error_rvalue_bound_to_out_parameter
          , ::boost::mpl::identity<Keyword>
        >::type key_type;
#endif
        typedef Arg value_type;
        typedef Arg&& reference;

     private:
        reference value;

     public:
        inline explicit BOOST_CONSTEXPR tagged_argument_rref(reference x)
          : value(::std::forward<Arg>(x))
        {
        }

        inline BOOST_CONSTEXPR tagged_argument_rref(
            tagged_argument_rref const& copy
        ) : value(::std::forward<Arg>(copy.value))
        {
        }

        // A metafunction class that, given a keyword and a default type,
        // returns the appropriate result type for a keyword lookup given
        // that default.
        struct binding
        {
            template <typename KW, typename Default, typename Reference>
            struct apply
            {
                typedef typename ::boost::mpl::eval_if<
                    ::boost::is_same<KW,key_type>
                  , ::boost::mpl::if_<Reference,reference,value_type>
                  , ::boost::mpl::identity<Default>
                >::type type;
            };

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
            template <typename KW, typename Default, typename Reference>
            using fn = ::boost::mp11::mp_if<
                ::std::is_same<KW,key_type>
              , ::boost::mp11::mp_if<Reference,reference,value_type>
              , Default
            >;
#endif
        };

#if !defined(BOOST_PARAMETER_CAN_USE_MP11)
        // Comma operator to compose argument list without using parameters<>.
        // Useful for argument lists with undetermined length.
        template <typename Keyword2, typename Arg2>
        inline BOOST_CONSTEXPR ::boost::parameter::aux::arg_list<
            ::boost::parameter::aux::tagged_argument_rref<Keyword,Arg>
          , ::boost::parameter::aux::arg_list<
                ::boost::parameter::aux::tagged_argument<Keyword2,Arg2>
            >
        >
            operator,(
                ::boost::parameter::aux
                ::tagged_argument<Keyword2,Arg2> const& x
            ) const
        {
            return boost::parameter::aux::arg_list<
                ::boost::parameter::aux::tagged_argument_rref<Keyword,Arg>
              , ::boost::parameter::aux::arg_list<
                    ::boost::parameter::aux::tagged_argument<Keyword2,Arg2>
                >
            >(
                *this
              , ::boost::parameter::aux::arg_list<
                    ::boost::parameter::aux::tagged_argument<Keyword2,Arg2>
                >(x, ::boost::parameter::aux::empty_arg_list())
            );
        }

        template <typename Keyword2, typename Arg2>
        inline BOOST_CONSTEXPR ::boost::parameter::aux::arg_list<
            ::boost::parameter::aux::tagged_argument_rref<Keyword,Arg>
          , ::boost::parameter::aux::arg_list<
                ::boost::parameter::aux::tagged_argument_rref<Keyword2,Arg2>
            >
        >
            operator,(
                ::boost::parameter::aux
                ::tagged_argument_rref<Keyword2,Arg2> const& x
            ) const
        {
            return ::boost::parameter::aux::arg_list<
                ::boost::parameter::aux::tagged_argument_rref<Keyword,Arg>
              , ::boost::parameter::aux::arg_list<
                    ::boost::parameter::aux
                    ::tagged_argument_rref<Keyword2,Arg2>
                >
            >(
                *this
              , ::boost::parameter::aux::arg_list<
                    ::boost::parameter::aux::tagged_argument_rref<
                        Keyword2
                      , Arg2
                    >
                >(x, ::boost::parameter::aux::empty_arg_list())
            );
        }
#endif  // BOOST_PARAMETER_CAN_USE_MP11

        // Accessor interface.
        inline BOOST_CONSTEXPR reference get_value() const
        {
            return ::std::forward<Arg>(this->value);
        }

        inline BOOST_CONSTEXPR reference
            operator[](::boost::parameter::keyword<Keyword> const&) const
        {
            return this->get_value();
        }

        template <typename Default>
        inline BOOST_CONSTEXPR reference
            operator[](
                ::boost::parameter::aux::default_<key_type,Default> const&
            ) const
        {
            return this->get_value();
        }

        template <typename Default>
        inline BOOST_CONSTEXPR reference
            operator[](
                ::boost::parameter::aux::default_r_<key_type,Default> const&
            ) const
        {
            return this->get_value();
        }

        template <typename F>
        inline BOOST_CONSTEXPR reference
            operator[](
                ::boost::parameter::aux::lazy_default<key_type,F> const&
            ) const
        {
            return this->get_value();
        }

        template <typename KW, typename Default>
        inline BOOST_CONSTEXPR Default&
            operator[](
                ::boost::parameter::aux::default_<KW,Default> const& x
            ) const
        {
            return x.value;
        }

        template <typename KW, typename Default>
        inline BOOST_CONSTEXPR Default&&
            operator[](
                ::boost::parameter::aux::default_r_<KW,Default> const& x
            ) const
        {
            return ::std::forward<Default>(x.value);
        }

        template <typename KW, typename F>
        inline BOOST_CONSTEXPR
        typename ::boost::parameter::aux::result_of0<F>::type
            operator[](
                ::boost::parameter::aux::lazy_default<KW,F> const& x
            ) const
        {
            return x.compute_default();
        }

        template <typename ParameterRequirements>
        static BOOST_CONSTEXPR typename ParameterRequirements::has_default
            satisfies(ParameterRequirements*);

        template <typename HasDefault, typename Predicate>
        static BOOST_CONSTEXPR
        typename ::boost::mpl::apply_wrap1<Predicate,value_type>::type
            satisfies(
                ::boost::parameter::aux::parameter_requirements<
                    key_type
                  , Predicate
                  , HasDefault
                >*
            );

        // MPL sequence support
        // Convenience for users
        typedef ::boost::parameter::aux
        ::tagged_argument_rref<Keyword,Arg> type;
        // For the benefit of iterators
        typedef ::boost::parameter::aux::empty_arg_list tail_type;
        // For dispatching to sequence intrinsics
        typedef ::boost::parameter::aux::arg_list_tag tag;
    };
}}} // namespace boost::parameter::aux

#else   // !defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)

namespace boost { namespace parameter { namespace aux {

    // Holds an lvalue reference to an argument of type Arg associated with
    // keyword Keyword
    template <typename Keyword, typename Arg>
    class tagged_argument
      : public ::boost::parameter::aux::tagged_argument_base
    {
        typedef typename ::boost::remove_const<Arg>::type arg_type;

     public:
        typedef Keyword key_type;

        // Wrap plain (non-UDT) function objects in either
        // a boost::function or a std::function. -- Cromwell D. Enage
        typedef typename ::boost::mpl::if_<
            ::boost::is_function<arg_type>
#if defined(BOOST_NO_CXX11_HDR_FUNCTIONAL)
          , ::boost::function<arg_type>
#else
          , ::std::function<arg_type>
#endif
          , Arg
        >::type value_type;

        // If Arg is void_, then this type will evaluate to void_&.  If the
        // supplied argument is a plain function, then this type will evaluate
        // to a reference-to-const function wrapper type.  If the supplied
        // argument is an lvalue, then Arg will be deduced to the lvalue
        // reference. -- Cromwell D. Enage
        typedef typename ::boost::mpl::if_<
            ::boost::is_function<arg_type>
          , value_type const&
          , Arg&
        >::type reference;

     private:
        // Store plain functions by value, everything else by reference.
        // -- Cromwell D. Enage
        typename ::boost::mpl::if_<
            ::boost::is_function<arg_type>
          , value_type
          , reference
        >::type value;

     public:
        inline explicit BOOST_CONSTEXPR tagged_argument(reference x)
          : value(x)
        {
        }

        inline BOOST_CONSTEXPR tagged_argument(tagged_argument const& copy)
          : value(copy.value)
        {
        }

        // A metafunction class that, given a keyword and a default type,
        // returns the appropriate result type for a keyword lookup given
        // that default.
        struct binding
        {
            template <typename KW, typename Default, typename Reference>
            struct apply
            {
                typedef typename ::boost::mpl::eval_if<
                    ::boost::is_same<KW,key_type>
                  , ::boost::mpl::if_<Reference,reference,value_type>
                  , ::boost::mpl::identity<Default>
                >::type type;
            };
        };

        // Comma operator to compose argument list without using parameters<>.
        // Useful for argument lists with undetermined length.
        template <typename Keyword2, typename Arg2>
        inline ::boost::parameter::aux::arg_list<
            ::boost::parameter::aux::tagged_argument<Keyword,Arg>
          , ::boost::parameter::aux::arg_list<
                ::boost::parameter::aux::tagged_argument<Keyword2,Arg2>
            >
        >
            operator,(
                ::boost::parameter::aux
                ::tagged_argument<Keyword2,Arg2> const& x
            ) const
        {
            return ::boost::parameter::aux::arg_list<
                ::boost::parameter::aux::tagged_argument<Keyword,Arg>
              , ::boost::parameter::aux::arg_list<
                    ::boost::parameter::aux::tagged_argument<Keyword2,Arg2>
                >
            >(
                *this
              , ::boost::parameter::aux::arg_list<
                    ::boost::parameter::aux::tagged_argument<Keyword2,Arg2>
                >(x, ::boost::parameter::aux::empty_arg_list())
            );
        }

        // Accessor interface.
        inline BOOST_CONSTEXPR reference get_value() const
        {
            return this->value;
        }

        inline BOOST_CONSTEXPR reference
            operator[](::boost::parameter::keyword<Keyword> const&) const
        {
            return this->get_value();
        }

#if defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING) || \
    BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))
        template <typename KW, typename Default>
        inline BOOST_CONSTEXPR Default&
            get_with_default(
                ::boost::parameter::aux::default_<KW,Default> const& x
              , int
            ) const
        {
            return x.value;
        }

        template <typename Default>
        inline BOOST_CONSTEXPR reference
            get_with_default(
                ::boost::parameter::aux::default_<key_type,Default> const&
              , long
            ) const
        {
            return this->get_value();
        }

        template <typename KW, typename Default>
        inline BOOST_CONSTEXPR typename ::boost::mpl::apply_wrap3<
            binding
          , KW
          , Default&
          , ::boost::mpl::true_
        >::type
            operator[](
                ::boost::parameter::aux::default_<KW,Default> const& x
            ) const
        {
            return this->get_with_default(x, 0L);
        }

        template <typename KW, typename F>
        inline BOOST_CONSTEXPR
        typename ::boost::parameter::aux::result_of0<F>::type
            get_with_lazy_default(
                ::boost::parameter::aux::lazy_default<KW,F> const& x
              , int
            ) const
        {
            return x.compute_default();
        }

        template <typename F>
        inline BOOST_CONSTEXPR reference
            get_with_lazy_default(
                ::boost::parameter::aux::lazy_default<key_type,F> const&
              , long
            ) const
        {
            return this->get_value();
        }

        template <typename KW, typename F>
        inline BOOST_CONSTEXPR typename ::boost::mpl::apply_wrap3<
            binding
          , KW
          , typename ::boost::parameter::aux::result_of0<F>::type
          , ::boost::mpl::true_
        >::type
            operator[](
                ::boost::parameter::aux::lazy_default<KW,F> const& x
            ) const
        {
            return this->get_with_lazy_default(x, 0L);
        }
#else   // No function template ordering or Borland workarounds needed.
        template <typename Default>
        inline BOOST_CONSTEXPR reference
            operator[](
                ::boost::parameter::aux::default_<key_type,Default> const&
            ) const
        {
            return this->get_value();
        }

        template <typename F>
        inline BOOST_CONSTEXPR reference
            operator[](
                ::boost::parameter::aux::lazy_default<key_type,F> const&
            ) const
        {
            return this->get_value();
        }

        template <typename KW, typename Default>
        inline BOOST_CONSTEXPR Default&
            operator[](
                ::boost::parameter::aux::default_<KW,Default> const& x
            ) const
        {
            return x.value;
        }

        template <typename KW, typename F>
        inline BOOST_CONSTEXPR
        typename ::boost::parameter::aux::result_of0<F>::type
            operator[](
                ::boost::parameter::aux::lazy_default<KW,F> const& x
            ) const
        {
            return x.compute_default();
        }

        template <typename ParameterRequirements>
        static BOOST_CONSTEXPR typename ParameterRequirements::has_default
            satisfies(ParameterRequirements*);

        template <typename HasDefault, typename Predicate>
        static BOOST_CONSTEXPR
        typename ::boost::mpl::apply_wrap1<Predicate,value_type>::type
            satisfies(
                ::boost::parameter::aux::parameter_requirements<
                    key_type
                  , Predicate
                  , HasDefault
                >*
            );
#endif  // Function template ordering, Borland workarounds needed.

        // MPL sequence support
        // Convenience for users
        typedef ::boost::parameter::aux::tagged_argument<Keyword,Arg> type;
        // For the benefit of iterators
        typedef ::boost::parameter::aux::empty_arg_list tail_type;
        // For dispatching to sequence intrinsics
        typedef ::boost::parameter::aux::arg_list_tag tag;

#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1310))
        // warning suppression
     private:
        void operator=(type const&);
#endif
    };
}}} // namespace boost::parameter::aux

#endif  // BOOST_PARAMETER_HAS_PERFECT_FORWARDING

#if defined(BOOST_PARAMETER_CAN_USE_MP11)

namespace boost { namespace parameter { namespace aux {

    template <typename TaggedArg>
    struct tagged_argument_list_of_1 : public TaggedArg
    {
        using base_type = TaggedArg;

        inline explicit BOOST_CONSTEXPR tagged_argument_list_of_1(
            typename base_type::reference x
        ) : base_type(static_cast<typename base_type::reference>(x))
        {
        }

        inline BOOST_CONSTEXPR tagged_argument_list_of_1(
            tagged_argument_list_of_1 const& copy
        ) : base_type(static_cast<base_type const&>(copy))
        {
        }

        using base_type::operator[];
        using base_type::satisfies;

        template <typename TA2>
        inline BOOST_CONSTEXPR ::boost::parameter::aux::flat_like_arg_list<
            ::boost::parameter::aux
            ::flat_like_arg_tuple<typename TaggedArg::key_type,TaggedArg>
          , ::boost::parameter::aux::flat_like_arg_tuple<
                typename TA2::base_type::key_type
              , typename TA2::base_type
            >
        >
            operator,(TA2 const& x) const
        {
            return boost::parameter::aux::flat_like_arg_list<
                ::boost::parameter::aux
                ::flat_like_arg_tuple<typename TaggedArg::key_type,TaggedArg>
              , ::boost::parameter::aux::flat_like_arg_tuple<
                    typename TA2::base_type::key_type
                  , typename TA2::base_type
                >
            >(
                static_cast<base_type const&>(*this)
              , ::boost::parameter::aux::arg_list<typename TA2::base_type>(
                    static_cast<typename TA2::base_type const&>(x)
                  , ::boost::parameter::aux::empty_arg_list()
                )
            );
        }
    };
}}} // namespace boost::parameter::aux

#endif  // BOOST_PARAMETER_CAN_USE_MP11
#endif  // include guard


/* tagged_argument.hpp
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
*/