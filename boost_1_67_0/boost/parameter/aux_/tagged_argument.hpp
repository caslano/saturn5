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
    BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
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
SuhrjfgJ/vMPlNZOawWNRus2iu2yUt0fR1QHso63DkFG3tOhqeMpCI2FTwzKDkH3i/C6KgtHTm7nk8Iz97lBetnId/TimzvgMh03CR5RalSDtNP4CrbHsTesBcnoGXdduELzbodp7qdiCnuUTyvBH22laWwSdPO8dKspyGwY2fk6LUgO6N6tiLneauYowrtR3dxqIDQlPp8hU+YO3ecMPuDSde923LblM9TPW3PxC/zwXzBYs62S+PCp8Ln84uOMbe7QPZN7jZMqBfnX1mOfEx2AZbbCFy14mbjbeL+E9b1D9FtiKBv9WYcgpKNiU/4J39z/I1xkbLV5OChLFtEKeSkDvZ1B3YcmQcWr8AqQgaOqgRuKOW4E0QNl46L7PR9+3k5eZmivhCs+ukL6/d7P+T6A2KuF+7m4T3EVI2zhOzTpRtjt3XzSre5aPpsrq9vR5hwpn4bbspFCuonHf7Nj/mFl5AU2lk7t7PUmaEnIaMeM2Byc/QMmJJxf3/t3RLC2sbfhMCzHRRMDidJZejeHNDWwIRUdenh2L4+didpq4mBK5KHMjH1qRELd/V1IqPB117jsbWNHHyZ/1Nr8HyAZIP0a3htmMyzR5hwrSXw5Sw5plWhEFsYw3D+yaZWor4WTtMomQQ2yZcIpQfNlTQZJcrinMmKDpbJPqBKjkx3yVCJ3A55uNUjDKk39sdDKRnsvDrZRosDanl5Ua3jGxhzr6EW15q5DXd5gVVhPvFob6Hct/W6k35cpTKO6ejudbaXf/fS7g34P0+9O+qWgOKsRCZ8TWo3dTFLXETX8ujriZag8gqTWPv3jBSWHQLCTsdv+4aEoXdvp7JFOHkAWnVhIOAMFdpi6EQNZh1NDM8pYzrIu9OXrK8wPM62ekpXKF5wpDNIHav0DPaOdmcfkPkUS03+VaIKbaoovsjnLuwzqt/czQVfu+8NkU5R1hYhZQJ2XXJyozVOJdQCRAiu5ESuZAJUMHHbCjWV7rzYmtvq/1dnbkOXQIUEKRn/4P0/lflFYFISCIng7u20qMudvjDa1toY3MYGW1+yINrG25nC0obU1O6PNra3hVGhElbZmV/QDaGtqo59Bf3t/dCeu02Q04kWlSyejsdGIwYqVJuVz7Rk5/H2tHjSpe7R8m3aPStg+t2bWcRc0AwZVT0s794UdjjouriNSShGWqMFnqdaV94S5gM38pD0KuuEW7DN341cldzWCaxfY/AErcjDlftYO89U0NIx6SlxyIn5QB/RQz0bs4RQHIkGrVytsaok97MQsfTGLSMfOPW7haNF/WVcLCTG3qQeoI9NNeEsq3iIwAW0mzoaE8VbXE0mAummDqbepg9NN4fZMexHqmPs8sIpUgAiWQk01IL4k2cXcDZ20l+MUK51NO2/w2k8itK4twxIPuiosRPdktielG0PZFdgoXFGwzqJSEBr2l/kXKB2G6tHe4XCQUnGW9i0J4AfqOwVEDMlVzBb2GiZEqIT5WHKPoPZB2jyLpc+CEjXXNu9ofMhhGjbYH2HuvI0PHfjiw4lHDlTxd3+ZaILeMIBfKTX72WuQoh7Yb+qFK6GJh3oksnthd4wROf73flwr5PAg7Uh1lzwI+5VZu0tfT1wHXUprySF2S7PRV7RCF8bnkVwUtjdLK1yZKa1UOn3a47JfWy6HR0JlbqWCRmFB02zaQO0u7R5Jf34D/xLXQZFnMdQ7VY4dPwtdqy7cDqN4H47irGKDHieIvVEv7Qd9Vy2/yGceZpcxiApOW+qB4/TbSL+nedzSA0101ky/LfSLzMtsN0YZO8LeLo5nkhn+bYxJZsnuK5hkepG4CCPAGeiORFPtIU5qeZGn3K4s8OzDN1P8Wq4LPlEeMqfk0GanQLq4SEbulKIcK7rSEwrSAq90ClCcSnGyQBoYCNKAz4xeBRQxNOo0IbqxB5844X8vvalX6TCStvNYbEo61fLJVKylk7+GYvPsw/lMrtKXLuHj/fF/tKOLPqfbpn2gkWot+ohyTmuYbaSFWkGPum8t53J71B9egDfjKGcT/oFCCFRUToMbUzyT02HdVOw8WOsbcxNM4Qx0ijopD/Sz9Ou6EazUh8bIzDkCdd4gwgsiGzrPmlTEFud1656nl8iTQktnhcrJ2YYtOAyjaRVOzPFoIIpCW0pb7VrukqgMEY8AT7nH8NDgBju0lCJ1mrsLZt/pZayiDJawI/FL2FJYwoj5sFFsYiaReGRjuY3cK9BR1UnkXz7K1YRy9jIrNCJn1UWjjmLLPOJYd8L4pkgsNv1sO+13RyCvnrocM+a5OIdv3jiiLjjJBp2CB+S5EAo1LTr+h2jDMQfbsSGR6MB/gQ/XinFeo6KW0I7eH06eNyJtiKCvOGbCjkxvj9KvnlY07GKCr5ffWQV3bs+W+1TOGAWXXNst4tBq8mHLeB/v0kWMLm+nY+2duq4vKJkXZ/y8AntOXQjW08nCUEfMwchH8WS0LwleGEc1OfNRqruL9U38VkeefZ7gYzY6j3UVSs5j/7R+q2dGVp6JlUY2VHpscLPLHC2y1MTuv+FbHXpE8BU8J/ifUZl74jpVv/eu1am404rRnzBOsXGMsPjgK1uJs9voX7uy4pxRriBJQrxAuc2zaS0hmmC890fB+FvFrlUsgT+JbO9HGI8ZFgXaNWzJPGSsZc281sf52emoGAg5klHdSm2DaoVfg3513EKNN9BT3CLbo5fU4hb9ySVq8Tm+HBczVnMG+t+TS7QmPu5xfyF42AnCw0+0vDlBlkBUQufcRyW14BwhPA8TwvM7venY+3XGgneaCChAt2R3PWYgMfqT2thcCuPiXHiS5u20eJvxMAPeahy/jbvcKcO1vPnajDlwEZ4PT2fRp5da5oVnBA/UEkK0L8+WHx7CZdJgbe0ATHdS+sL8e5EOqYCF+2t5C7UZs/LhNfgrSVCe+2wuL5Lfq+7MJ5wMHW/cOgBR9rxPuc8WFZH5n4Fei5vtnA8rWaVv2Oq5bMCRKBwMCYHwSW6Ncx1+czjqaJH7oI1TmwQ8Z7C2CjUBAurQg7hmED9NPfZ9A1fgC71BdRkAY38wux0+LxEfmuJw98isewiUGWjLB3wc/uoXXCFufPy7+Hg/e+FjYSsegzAgrQmvDxpOVvynxCUQ1mGCmregRN/cRFaIa6AEsSPX1ZPwS+Ha8pbI7iu7BfuiSxfeXlpe3MDJiw0c4TlR5YmOl0JkKR2o5diKtGHrjxMb8Fr4k/GeH7eoZtszI8/YtRVW7XF7RnfmJxX9jWM013+S4b1IctoKq/soiJ4N2pGMQzwB94xn26o/gMlwppXTN6Md0NKDMqHX7rcclGbqqatWECw7igYgnSN4cA6zFXTr6MfQ3SQ2vD9FYeXns0DlwDCV7NKOq1WOsd26zqbOjoochlJR4DWZaF9/Lgqq8jCSzu2l15T356GpFBaB2y/yhSKqJYRIv8BLKXApRBoGniXBWXi0vod0ipPsh9/AfXt28pPZdFLHT/LhBB6smf26ZOPCWGlabb8fwWvVFnEIIgrkQ/nSIw+CfurwbEJBgbYsXoev/i5x55dzSqIYd34zW3QU1x1lIFzjVrRm9j+QFK7X8uRgQZuOFscccoshdnmbVmZz11V3gQIGgxUX1zQK7TnKTZ4xLtlSmr3gVVyCZEvwZAJvhAifDCHBBVVEenoBXoTK3u5Zh/O3bIEeqT85DlmrWjhK+Q0K375cGeGs9zZj9VvnRcGExMwgqEO953iQlJ9jY+WNIwb/l76IIIP/XOjjGrUvbn2AoJsSXZX7hbwRycdeCSVCv4kETzppvsBnI05XSeJPjqO0f/FMRA+nFRYGTDZcgY2MA3hGaJGq2Rg4opzR3MlaT2EIhJca23VqevdZbNmbGzDYQhuoFXJyEQEHUjfgksQbHj4Bux1ygPS7dybuRFlrJ+E3Pl1oyNlDx6HWx+XsYkPO3hroQsCAuolE7U0kam+iBWkTrTsUeE/dRIL2phZOFGnivCJ5Lm3aKKRYm2ZV86zYRp4FVjlRmzYpbNGmTSAumTHIYDxOCs0Yx15JAlmzJB00BTUP9AW7mmfX1vCNDophu2ZDdNPj/0UTF9r0Cbavwwh/x9dRG4XMKz7ZTiFTLF0ENODrYihvlsDa8BldLVmibkJxuX71ZkMK//9U6qG57ytMNsUpcuwONFB7bTDfYBOR97xAIpFaloKembXoD0vNMr8zokdZxo9z/uEUHKEP49cbLOHX0wpSQCOh3RtPhaQMhNLdR90fqDZVsrY+htum5RHPASHjk7YtTxd/rwOhus+WWe+Pdobv2IJs6+FbIaU/YuTYvwtQtQ3bcZlk/8CTbFiwI57Jo0CQlxMtMMFFgo9FEjyTZ51FhGcPRancQCxFbTReXJMRjvFE8uRIOyQ++zGJX6V98b0mrsaN+OVjKboSJowZ3UF7kXTyohUjPrRg38X9w2UfRXT2x+3tPL7Fin9GdG3GkqhJUElhmzwdBsTlnUZcvMIObRgClKvPKsls+u3n+VZIPigfFBTjSRf7z9QLODelSzHrqGRcO0XX5Ot5Vf117RQtqqwTziT2/V9i3ZhRt7N/i+huPVjhuqwV29Vypjg0C49Kc0yXxoCUgWz7CEF0aieKJGa9HZFpzKRNotZsQU58xrdnxoAExlWnCyejgLxiXj2EpwT32fpzUVCeFsf5VDIYZYr1qTc62cGTYk0fjaRKTr+PNmrbCg0ENohWBTZ8bo5VHagdDM8KlqeY4EuWk6t+xOxt0faQet6FbvlOzRRa2ScpfBPT98RvX/CbQlnTwn3hG1Ho6xZkUC5oUSep+VY2dwZ0eKfR4RW7n7aVLrDH76GZ2l+fl2bHQYXb+05T97RROLTkPnCeYpzDDG8Nzkg3B5pzRjpDM5xsdjvMue9i3Uy1xyENhojzrAuHSArzwDWxkUAuBc/hyLh4vzGv5Y6+xv7B8Ydh4CtpfAsBvhDfRcAxSRsJ0G58L4FccynszHdtKYy6SFsKiwrIkBjAu2t7sAb/whp47Qi36tLOqGTbQlAUGUOCT7suq+Vr1er5cMKdq9hLu6GVd1M2vjnFzbJrySp7P1fcZo7nOciyW2raplbfj6j3SziKRLAtuENLCj7WlhAXG2neuNJRGLtWX9qJW02IHZIC+u77jTVPGm8YTFtPOJBzIcVR1U0KKmj4uP7hiUoGE9Dv1d358JcrD1QGy3+/nXjbQ9US2n3U3WWY+qy5W8e1y4uQrQPUeR1V+029AIybB0V7r+V9jkpsxge+gC2yZhf2u1KKR9FQpD//Mrl9ppnUaixfHsce2RVrslAIEwuNloMlcC3t6tHqUb5WpzqJyGZYYEFzkRZBsYej6MhCIo1vPQECf3cu9UFHVV+4pb4aXxunmlYK8LbuuJ0wBU8E96IBwCQvZl99qetqdT73IXxQSwqFsrEqbp18qfT14zGSpc0TwsZBHTyEPtqKFaTDvto7mKgWNGshvB/ftTlEQe78Eru36htdo3J5R9GedrHtORcglz+UP4c9PcUQRtF0l+uavHIKqpKTy6egcAaCDa1Y/ce3gqyuq++geQq3WzxPWxW7xJZHLkGxAfqkLrYxiGbPKhGbjP132gXdQ9s6IO3t22riBaaR20z7m506N54hfir2ZdTqhfjVP3jTmCxwfebMstUyxhorT5MlT7lLmc5e75UHPaDZr9+M/5QLv/NTBrdhWSaNPqdbp08F08cw9mC0zJ1817hfPT2WGiHXpb6DN2TWy+NQMhzN97qUEZnd8lDParTMKIO0grWamUYNztzUx4zRtp62BLrf6LWN613PPu+VYqHuH1LWW7zrQ+WwPm6k2+reuOJtv28UW0fXN9N1HJ+Yp4nMVi1mb53mPYfOCt62sQhG2ah6G8IDOG1GndiNcOueyS7Q2OU8/IbzH+zGDvj96BbcG0cFfGt0HBj4NmdUB33OuN5Ha2CDv/4GP5GSypxQH8/y5XKyuytP3Y10v+G+7i71HTzK046x35gJ2TvPU16l+LRcuzbdqi61q0utnqcnlQ9Qn4a/E8qT1Fy7Oh0OrfKdZDLzUBeWb9YifNKAlr/ej1GxeXdHaWxu5Te6uhuzqeU16jtZNPomRWMGrpdgAo+GDMR05jzSoXvewc8sp2HXGoRQ3DRqIOgzx9iPhyODRLOCob6/MNH4tHnewScoyVB9R9W/0HODuubtnvIU5VY2aCe+fJns8ky2gTykpHkmW/Gvk3paoqneW2PmOkV5DXSYENVPYvP3oc395QzvBq1gfUY1DnBkZ47Ad8ugXnHqcsZB4mvWckedQn0mwaQM4cqMM1iebpL74brqqCIbsHdDKCVJnX3O8gIWFLI6xDQxu83SA4KdtwUEDc/sKsGk9kKAFhH07dfKN5xhlstqAUwJTZ7URUhiZPtH4nyU7BLO1P299dOWrsNTn5Y9qZNQiFuiKRsz2rUQTS45s/h0AMpyjmSoz3XhQde4YPY2aTmSWr1IpM6KZU+FC9q9s6LXDtIlrLZndg30TW/TNE8R6gHTUQ+YPiGgEzGTVGqWJKmQV8WP8bqUtewfv/lGDz7WlBD8KgFufwGnHLmfZ3a6nAg9M5zg7uIl5WJJubwknforOgz7ClHfa2olUfQFibejpZGElQ2WI6DaWegzqbMZqIcYsKZKHqwrVYRFoc4jf6Xrrejk4KHXl4doZOIXGdi7PzObWskM4K2R/cioiV2UAy2CT8N3vfY7wtPFa1qOwMl6Sz2V1v7yNzoPF7o+ykmx3l0H703rj+OF9zy5cS9rUTbEva/lAm5kzCw1SWgJW8uLZ5ugSNFdcaI4h5Cmvp7yGkf1a9gm05dkngTZ+Ye3RWXnyr8I2XkiOfd1K32YYxQ6l/q4W99DfxHzRQpOV+sL+cSsP48Q4PBcH/fuy/qOTGRHn+DjTn5DRCZloI87+SUZd6X2vitCLss40vzsZ3+GMZY7Cha7V2nOXyFG/hQcvils7g4YubWraDu1cjoM1lUm5t1BEoSBtamLX01qSN9qVnNH4QRQoyxiQyC3/hYZcnFlg/xXLUG4FIYn4VQzEe6Rx+OjM0Q9bmIf/Q89LuG7HufW/UYvobioBVU6fY8LfI36ngvUJXl8kDnlG4NsvJzyPdQtHdV/R3HZW2XFZ18PB4l44ISDJMLJwoGFAomvNwB/M7AeETYN/8SZFmE64powBZj3dTfFxbZFAjSXMtSzm17lynn0pusRdtSEbn608qtKE+7SKM28BKUKu/DxbBAalDT5NixprChpJDv4x/97oxiL4U6q+i/+2FvXSDNpBQ2hqbYE1buT78Owsj/2Xk+VhUIKiItGngyDEoOkVemwuHl35uOw5yJ4ti0fvVUyoJBguQu+tHJbvLwRhWDFRI5wOmaUB7PuVzsNdPyGqMCj5fJtoWdPG9tCNagwsG9eQn2Vo9OOfBjRSfOdPo7HkF/WQTjo5cjMAW1YUMPGpFH4xhoK1fji14idaTaCJS6rj+jTeM7p49ixFR1GwRRmfnHvzPdBZpR3l9n0VPkJ6GTenZbg0ykmLoQ5qj9ES8+qTzH6Jk4djO1qp+irmrcmuLzTVJEZqsZ0+LA1Eu0DjJz6ta4ptcEQKi7mDGVn8LAdFu05Oqemu2HPebg/aPaMf8YKf01d1ZRPvg7rtA2PL6Oe/NaRiL6qPGiCV5TvhGdp2Z35UH4VCCRDom+exF7uxJep4i+TyMrhrtYfUnjpqRT4uVNie9eAdkx1N17ZD7mCk12wyJmUu4JkaDQp39MnRmDGo1CdPmzhSL9OvfQWPFr5aLfu45fx9GO4AN2fOrY8A3qwci+zb4fJpEyW74GZR5/4Mgb6NYN6EFJ2ctXLTBGOSemiuRpeSOpEAfIO0LTKW/wzJd0XILVjYUzt0ApqtJxObQhkUXb6JPQxmhnQaHHBpndUvURTUm0GSeG8KweZJfgO1gyUPS+TJRwRyn1syR+g+y6XTVdXkMe4FxVsjFaQhARtiqjjLZDJL83EOipGHYUiyJf6/E5tMOZq8VO0KKjmZdBZdXlwkIzFJqV/kCRoqPRQcn0LNKO2ibFgo3unzbh3qiSyyL52Q7SfviRUvpnG+ZgiYQ2qdU4hfd4Of6BbY4dhs95s14P7cDMNN1f7yNcfsMFVH/sgM9k0V/KJXAs/iei9zOLzxFNALNuH6vq2bSHqjNuM7rqNLXkLWetQf8+whd4inX4AG/H7KzSa+GkfJgHaXKSSsF1gZqCm2Ww0Dbp6JXFFmypmdMu6Q1C/y0FSPExy/3gNdIxOs6PRL0j3A53SLmRhtnIuaH6h+69IfYRSA/wR7CEsvqAGD31wyAGHk3rJzOzndR06a85KNr2XbhhmZ/XmxONkeD5NcWpnDICZ9zQHJkiqskP/mMMIJP1jWCYJ4yAPAyFjFDrJYnAdn66cRgY8M0pLyE7MGrfCNJm9RPU2evbt5Mvxw9Ch0eklXUnmm11luGePNi7ltF/yoePuMXbgOhPhv1mZBxYSvs0II6sBdxobNO9x/Hs8VN7MCTY9S/PlVLZoK9edakl3ykIZoy+HLoe8tRptdhXAbYczT4C+fUS+kcN3/qpnNGoHZ/KTo3pGQyGnJ+P7J6eFCTgEqvi+BhMnGGTfvBK/MGkFKd1nhh7tPnVTQ/eZQnFGxzFbMbYXAURAU0qRp2pKHb7MkbHoENyZHdJoT90MYlaip/ywfJfmPQwVcn9wqmdKRuNM7UjcSSEfxOHrgg16hvc4kaL0qMHjJDaAQHTYU94o96VWvqiHJ3CQhzyMQ1EGo8I7UCi8PNMlPewQ6j0XlRIwzpG2dKquuIhBJR2/blp97lROHZiiKzuI5nDzMKjy0qn8vRxVZrPYLLHA8gh1UAaSGMw7D68zfvOBlCeBICb00JW8ZgrWrEzULBB6C2/jcoC7bpvHm4IMujuDBxPUglrca9xFh/vh03vTlb7Gcy2gC3gIJqPcxGb/DtFdIHn6xGK+k4/iJlrM15oMZW8474ULkWYIyoPPc4OoxnXuo+GBYgNIPod6xmfuoznYLd11md0g9Eji9QqxPc7cfQHUvsMgQ0KpjmpkLn0Va6WM5G+qXA/v76iq5umpJqWCvbkFlqGE8DxsrgfEl5rG2yMb2yNTVMSteztZ9ZZeslNb/Nug7MQWYWlm3nThfmw2nUIXjm0h9sofNSnfkI4mZZeAfn3Y1qHXJ92/00U=
*/