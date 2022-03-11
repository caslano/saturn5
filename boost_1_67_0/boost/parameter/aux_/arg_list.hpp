// Copyright Daniel Wallin, David Abrahams 2005.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_ARG_LIST_HPP
#define BOOST_PARAMETER_AUX_ARG_LIST_HPP

namespace boost { namespace parameter { namespace aux {

    //
    // Structures used to build the tuple of actual arguments.  The tuple is a
    // nested cons-style list of arg_list specializations terminated by an
    // empty_arg_list.
    //
    // Each specialization of arg_list is derived from its successor in the
    // list type.  This feature is used along with using declarations to build
    // member function overload sets that can match against keywords.
    //

    // MPL sequence support
    struct arg_list_tag;

    template <typename T>
    struct get_reference
    {
        typedef typename T::reference type;
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)

namespace boost { namespace parameter { namespace aux {

    struct value_type_is_void
    {
    };

    struct value_type_is_not_void
    {
    };
}}} // namespace boost::parameter::aux

#endif

#include <boost/parameter/aux_/void.hpp>
#include <boost/parameter/aux_/yesno.hpp>
#include <boost/parameter/aux_/result_of0.hpp>
#include <boost/parameter/aux_/default.hpp>

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
#include <utility>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/integral.hpp>
#include <boost/mp11/list.hpp>
#include <boost/mp11/utility.hpp>
#include <type_traits>
#endif

namespace boost { namespace parameter { namespace aux {

    // Terminates arg_list<> and represents an empty list.  Since this is just
    // the terminating case, you might want to look at arg_list first to get a
    // feel for what's really happening here.
    struct empty_arg_list
    {
        struct tagged_arg
        {
            typedef ::boost::parameter::void_ value_type;
        };

        // Variadic constructor also serves as default constructor.
        template <typename ...Args>
        inline BOOST_CONSTEXPR empty_arg_list(Args&&...)
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
                typedef Default type;
            };

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
            template <typename KW, typename Default, typename Reference>
            using fn = Default;
#endif
        };

        // Terminator for has_key, indicating that the keyword is unique.
        template <typename KW>
        static ::boost::parameter::aux::no_tag has_key(KW*);

        // If either of these operators are called, it means there is no
        // argument in the list that matches the supplied keyword.  Just
        // return the default value.
        template <typename K, typename Default>
        inline BOOST_CONSTEXPR Default&
            operator[](::boost::parameter::aux::default_<K,Default> x) const
        {
            return x.value;
        }

        template <typename K, typename Default>
        inline BOOST_CONSTEXPR Default&&
            operator[](::boost::parameter::aux::default_r_<K,Default> x) const
        {
            return ::std::forward<Default>(x.value);
        }

        // If this operator is called, it means there is no argument in the
        // list that matches the supplied keyword.  Just evaluate and return
        // the default value.
        template <typename K, typename F>
        inline BOOST_CONSTEXPR
        typename ::boost::parameter::aux::result_of0<F>::type
            operator[](BOOST_PARAMETER_lazy_default_fallback<K,F> x) const
        {
            return x.compute_default();
        }

        // No argument corresponding to ParameterRequirements::key_type
        // was found if we match this overload, so unless that parameter
        // has a default, we indicate that the actual arguments don't
        // match the function's requirements.
        template <typename ParameterRequirements, typename ArgPack>
        static typename ParameterRequirements::has_default
            satisfies(ParameterRequirements*, ArgPack*);

        // MPL sequence support
        typedef ::boost::parameter::aux::empty_arg_list type; // convenience
        // For dispatching to sequence intrinsics
        typedef ::boost::parameter::aux::arg_list_tag tag;
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/aux_/preprocessor/nullptr.hpp>
#include <boost/parameter/aux_/yesno.hpp>
#include <boost/parameter/aux_/is_maybe.hpp>
#include <boost/parameter/aux_/tagged_argument_fwd.hpp>
#include <boost/parameter/aux_/parameter_requirements.hpp>
#include <boost/parameter/aux_/augment_predicate.hpp>
#include <boost/parameter/keyword_fwd.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/core/enable_if.hpp>

namespace boost { namespace parameter { namespace aux {

    // A tuple of tagged arguments, terminated with empty_arg_list.  Every
    // TaggedArg is an instance of tagged_argument<> or
    // tagged_argument_rref<>.
    template <
        typename TaggedArg
      , typename Next = ::boost::parameter::aux::empty_arg_list
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
      , typename EmitsErrors = ::boost::mp11::mp_true
#else
      , typename EmitsErrors = ::boost::mpl::true_
#endif
    >
    class arg_list : public Next
    {
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        using _holds_maybe = typename ::boost::parameter::aux
        ::is_maybe<typename TaggedArg::value_type>::type;
#else
        typedef typename ::boost::parameter::aux
        ::is_maybe<typename TaggedArg::value_type>::type _holds_maybe;
#endif

        TaggedArg arg;      // Stores the argument

     public:
        typedef TaggedArg tagged_arg;
        typedef ::boost::parameter::aux::arg_list<TaggedArg,Next> self;
        typedef typename TaggedArg::key_type key_type;

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        using reference = typename ::boost::mp11::mp_if<
            _holds_maybe
          , ::boost::parameter::aux
            ::get_reference<typename TaggedArg::value_type>
          , ::boost::parameter::aux::get_reference<TaggedArg>
        >::type;

        using value_type = ::boost::mp11
        ::mp_if<_holds_maybe,reference,typename TaggedArg::value_type>;
#else   // !defined(BOOST_PARAMETER_CAN_USE_MP11)
        typedef typename ::boost::mpl::eval_if<
            _holds_maybe
          , ::boost::parameter::aux
            ::get_reference<typename TaggedArg::value_type>
          , ::boost::parameter::aux::get_reference<TaggedArg>
        >::type reference;

        typedef typename ::boost::mpl::if_<
            _holds_maybe
          , reference
          , typename TaggedArg::value_type
        >::type value_type;
#endif  // BOOST_PARAMETER_CAN_USE_MP11

        // Create a new list by prepending arg to a copy of tail.  Used when
        // incrementally building this structure with the comma operator.
        inline BOOST_CONSTEXPR arg_list(
            TaggedArg const& head
          , Next const& tail
        ) : Next(tail), arg(head)
        {
        }

        // Store the arguments in successive nodes of this list.
        // Use tag dispatching to determine whether to forward all arguments
        // to the Next constructor, or store the first argument and forward
        // the rest. -- Cromwell D. Enage
        template <typename A0>
        inline BOOST_CONSTEXPR arg_list(
            ::boost::parameter::aux::value_type_is_not_void
          , A0&& a0
        ) : Next(
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
                ::boost::mp11::mp_if<
                    ::std::is_same<
#else
                typename ::boost::mpl::if_<
                    ::boost::is_same<
#endif
                        typename Next::tagged_arg::value_type
                      , ::boost::parameter::void_
                    >
                  , ::boost::parameter::aux::value_type_is_void
                  , ::boost::parameter::aux::value_type_is_not_void
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
                >()
#else
                >::type()
#endif
            )
          , arg(::std::forward<A0>(a0))
        {
        }

        template <typename ...Args>
        inline BOOST_CONSTEXPR arg_list(
            ::boost::parameter::aux::value_type_is_void
          , Args&&... args
        ) : Next(
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
                ::boost::mp11::mp_if<
                    ::std::is_same<
#else
                typename ::boost::mpl::if_<
                    ::boost::is_same<
#endif
                        typename Next::tagged_arg::value_type
                      , ::boost::parameter::void_
                    >
                  , ::boost::parameter::aux::value_type_is_void
                  , ::boost::parameter::aux::value_type_is_not_void
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
                >()
#else
                >::type()
#endif
              , ::std::forward<Args>(args)...
            )
          , arg(::boost::parameter::aux::void_reference())
        {
        }

        template <typename A0, typename A1, typename ...Args>
        inline BOOST_CONSTEXPR arg_list(
            ::boost::parameter::aux::value_type_is_not_void
          , A0&& a0
          , A1&& a1
          , Args&&... args
        ) : Next(
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
                ::boost::mp11::mp_if<
                    ::std::is_same<
#else
                typename ::boost::mpl::if_<
                    ::boost::is_same<
#endif
                        typename Next::tagged_arg::value_type
                      , ::boost::parameter::void_
                    >
                  , ::boost::parameter::aux::value_type_is_void
                  , ::boost::parameter::aux::value_type_is_not_void
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
                >()
#else
                >::type()
#endif
              , ::std::forward<A1>(a1)
              , ::std::forward<Args>(args)...
            )
          , arg(::std::forward<A0>(a0))
        {
        }

        // A metafunction class that, given a keyword and a default type,
        // returns the appropriate result type for a keyword lookup given
        // that default.
        struct binding
        {
            typedef typename Next::binding next_binding;

            template <typename KW, typename Default, typename Reference>
            struct apply
            {
                typedef typename ::boost::mpl::eval_if<
                    ::boost::is_same<KW,key_type>
                  , ::boost::mpl::if_<Reference,reference,value_type>
                  , ::boost::mpl
                    ::apply_wrap3<next_binding,KW,Default,Reference>
                >::type type;
            };

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
            template <typename KW, typename Default, typename Reference>
            using fn = ::boost::mp11::mp_if<
                ::std::is_same<KW,key_type>
              , ::boost::mp11::mp_if<Reference,reference,value_type>
              , ::boost::mp11::mp_apply_q<
                    next_binding
                  , ::boost::mp11::mp_list<KW,Default,Reference>
                >
            >;
#endif
        };

        // Overload for key_type, so the assert below will fire
        // if the same keyword is used again.
        static ::boost::parameter::aux::yes_tag has_key(key_type*);
        using Next::has_key;

     private:
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        using _has_unique_key = ::boost::mp11::mp_bool<
#else
        typedef ::boost::mpl::bool_<
#endif
            sizeof(
                Next::has_key(
                    static_cast<key_type*>(BOOST_PARAMETER_AUX_PP_NULLPTR)
                )
            ) == sizeof(::boost::parameter::aux::no_tag)
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        >;
#else
        > _has_unique_key;
#endif

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        static_assert(
            !(EmitsErrors::value) || (_has_unique_key::value)
          , "duplicate keyword"
        );
#else
        BOOST_MPL_ASSERT_MSG(
            !(EmitsErrors::value) || (_has_unique_key::value)
          , duplicate_keyword
          , (key_type)
        );
#endif

        //
        // Begin implementation of indexing operators
        // for looking up specific arguments by name.
        //

        // Helpers that handle the case when TaggedArg is empty<T>.
        template <typename D>
        inline BOOST_CONSTEXPR reference
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
            get_default(D const&, ::boost::mp11::mp_false) const
#else
            get_default(D const&, ::boost::mpl::false_) const
#endif
        {
            return this->arg.get_value();
        }

        template <typename D>
        inline BOOST_CONSTEXPR reference
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
            get_default(D const& d, ::boost::mp11::mp_true) const
#else
            get_default(D const& d, ::boost::mpl::true_) const
#endif
        {
            return (
                this->arg.get_value()
              ? this->arg.get_value().get()
              : this->arg.get_value().construct(d.value)
            );
        }

     public:
        inline BOOST_CONSTEXPR reference
            operator[](::boost::parameter::keyword<key_type> const&) const
        {
#if !defined(BOOST_NO_CXX14_CONSTEXPR)
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
            static_assert(!_holds_maybe::value, "must not hold maybe");
#elif !( \
        BOOST_WORKAROUND(BOOST_GCC, >= 40700) && \
        BOOST_WORKAROUND(BOOST_GCC, < 40900) \
    ) && !BOOST_WORKAROUND(BOOST_GCC, >= 50000) && \
    !BOOST_WORKAROUND(BOOST_MSVC, < 1910)
            BOOST_MPL_ASSERT_NOT((_holds_maybe));
#endif
#endif
            return this->arg.get_value();
        }

        template <typename Default>
        inline BOOST_CONSTEXPR reference
            operator[](
                ::boost::parameter::aux::default_<key_type,Default> const& d
            ) const
        {
            return this->get_default(d, _holds_maybe());
        }

        template <typename Default>
        inline BOOST_CONSTEXPR reference
            operator[](
                ::boost::parameter::aux::default_r_<key_type,Default> const& d
            ) const
        {
            return this->get_default(d, _holds_maybe());
        }

        template <typename Default>
        inline BOOST_CONSTEXPR reference
            operator[](
                BOOST_PARAMETER_lazy_default_fallback<key_type,Default> const&
            ) const
        {
#if !defined(BOOST_NO_CXX14_CONSTEXPR)
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
            static_assert(!_holds_maybe::value, "must not hold maybe");
#elif !( \
        BOOST_WORKAROUND(BOOST_GCC, >= 40700) && \
        BOOST_WORKAROUND(BOOST_GCC, < 40900) \
    ) && !BOOST_WORKAROUND(BOOST_GCC, >= 50000) && \
    !BOOST_WORKAROUND(BOOST_MSVC, < 1910)
            BOOST_MPL_ASSERT_NOT((_holds_maybe));
#endif
#endif
            return this->arg.get_value();
        }

        // Builds an overload set including operator[]s defined
        // in base classes.
        using Next::operator[];

        //
        // End of indexing support
        //

        // For parameter_requirements matching this node's key_type, return
        // a bool constant wrapper indicating whether the requirements are
        // satisfied by TaggedArg.  Used only for compile-time computation
        // and never really called, so a declaration is enough.
        template <typename HasDefault, typename Predicate, typename ArgPack>
        static typename ::boost::lazy_enable_if<
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
            ::boost::mp11::mp_if<
                EmitsErrors
              , ::boost::mp11::mp_true
              , _has_unique_key
            >
          , ::boost::parameter::aux::augment_predicate_mp11<
#else
            typename ::boost::mpl::if_<
                EmitsErrors
              , ::boost::mpl::true_
              , _has_unique_key
            >::type
          , ::boost::parameter::aux::augment_predicate<
#endif
                Predicate
              , reference
              , key_type
              , value_type
              , ArgPack
            >
        >::type
            satisfies(
                ::boost::parameter::aux::parameter_requirements<
                    key_type
                  , Predicate
                  , HasDefault
                >*
              , ArgPack*
            );

        // Builds an overload set including satisfies functions defined
        // in base classes.
        using Next::satisfies;

        // Comma operator to compose argument list without using parameters<>.
        // Useful for argument lists with undetermined length.
        template <typename KW, typename T2>
        inline BOOST_CONSTEXPR ::boost::parameter::aux::arg_list<
            ::boost::parameter::aux::tagged_argument<KW,T2>
          , self
        >
            operator,(
                ::boost::parameter::aux::tagged_argument<KW,T2> const& x
            ) const
        {
            return ::boost::parameter::aux::arg_list<
                ::boost::parameter::aux::tagged_argument<KW,T2>
              , self
            >(x, *this);
        }

        template <typename KW, typename T2>
        inline BOOST_CONSTEXPR ::boost::parameter::aux::arg_list<
            ::boost::parameter::aux::tagged_argument_rref<KW,T2>
          , self
        >
            operator,(
                ::boost::parameter::aux::tagged_argument_rref<KW,T2> const& x
            ) const
        {
            return ::boost::parameter::aux::arg_list<
                ::boost::parameter::aux::tagged_argument_rref<KW,T2>
              , self
            >(x, *this);
        }

        // MPL sequence support
        typedef self type;        // Convenience for users
        typedef Next tail_type;   // For the benefit of iterators
        // For dispatching to sequence intrinsics
        typedef ::boost::parameter::aux::arg_list_tag tag;
    };
}}} // namespace boost::parameter::aux

#else   // !defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>

namespace boost { namespace parameter { namespace aux {

    // Terminates arg_list<> and represents an empty list.  Since this is just
    // the terminating case, you might want to look at arg_list first to get a
    // feel for what's really happening here.
    struct empty_arg_list
    {
        inline BOOST_CONSTEXPR empty_arg_list()
        {
        }

        // Constructor taking BOOST_PARAMETER_COMPOSE_MAX_ARITY empty_arg_list
        // arguments; this makes initialization.
        inline BOOST_CONSTEXPR empty_arg_list(
            BOOST_PP_ENUM_PARAMS(
                BOOST_PARAMETER_COMPOSE_MAX_ARITY
              , ::boost::parameter::void_ BOOST_PP_INTERCEPT
            )
        )
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
                typedef Default type;
            };
        };

        // Terminator for has_key, indicating that the keyword is unique.
        template <typename KW>
        static ::boost::parameter::aux::no_tag has_key(KW*);

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
        // The overload set technique doesn't work with these older compilers,
        // so they need some explicit handholding.

        // A metafunction class that, given a keyword, returns the type of the
        // base sublist whose get() function can produce the value for that key.
        struct key_owner
        {
            template <typename KW>
            struct apply
            {
                typedef ::boost::parameter::aux::empty_arg_list type;
            };
        };
#endif  // Borland workarounds needed

        // If either of these operators are called, it means there is no
        // argument in the list that matches the supplied keyword.  Just
        // return the default value.
        template <typename K, typename Default>
        inline BOOST_CONSTEXPR Default&
            operator[](::boost::parameter::aux::default_<K,Default> x) const
        {
            return x.value;
        }

        // If this operator is called, it means there is no argument in the
        // list that matches the supplied keyword.  Just evaluate and return
        // the default value.
        template <typename K, typename F>
        inline BOOST_CONSTEXPR
        typename ::boost::parameter::aux::result_of0<F>::type
            operator[](BOOST_PARAMETER_lazy_default_fallback<K,F> x) const
        {
            return x.compute_default();
        }

        // No argument corresponding to ParameterRequirements::key_type
        // was found if we match this overload, so unless that parameter
        // has a default, we indicate that the actual arguments don't
        // match the function's requirements.
        template <typename ParameterRequirements, typename ArgPack>
        static typename ParameterRequirements::has_default
            satisfies(ParameterRequirements*, ArgPack*);

        // MPL sequence support
        typedef ::boost::parameter::aux::empty_arg_list type; // convenience
        // For dispatching to sequence intrinsics
        typedef ::boost::parameter::aux::arg_list_tag tag;
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/aux_/yesno.hpp>
#include <boost/parameter/aux_/is_maybe.hpp>
#include <boost/parameter/aux_/tagged_argument_fwd.hpp>
#include <boost/parameter/aux_/parameter_requirements.hpp>
#include <boost/parameter/aux_/augment_predicate.hpp>
#include <boost/parameter/keyword_fwd.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>

#if !defined(BOOST_NO_SFINAE) && !BOOST_WORKAROUND(BOOST_MSVC, < 1800)
#include <boost/core/enable_if.hpp>
#endif

#if !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
#include <boost/parameter/aux_/preprocessor/nullptr.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    // A tuple of tagged arguments, terminated with empty_arg_list.  Every
    // TaggedArg is an instance of tagged_argument<>.
    template <
        typename TaggedArg
      , typename Next = ::boost::parameter::aux::empty_arg_list
      , typename EmitsErrors = ::boost::mpl::true_
    >
    class arg_list : public Next
    {
        typedef typename ::boost::parameter::aux
        ::is_maybe<typename TaggedArg::value_type>::type _holds_maybe;

        TaggedArg arg;      // Stores the argument

     public:
        typedef TaggedArg tagged_arg;
        typedef ::boost::parameter::aux::arg_list<TaggedArg,Next> self;
        typedef typename TaggedArg::key_type key_type;

        typedef typename ::boost::mpl::eval_if<
            _holds_maybe
          , ::boost::parameter::aux
            ::get_reference<typename TaggedArg::value_type>
          , ::boost::parameter::aux::get_reference<TaggedArg>
        >::type reference;

        typedef typename ::boost::mpl::if_<
            _holds_maybe
          , reference
          , typename TaggedArg::value_type
        >::type value_type;

        // Create a new list by prepending arg to a copy of tail.  Used when
        // incrementally building this structure with the comma operator.
        inline BOOST_CONSTEXPR arg_list(
            TaggedArg const& head
          , Next const& tail
        ) : Next(tail), arg(head)
        {
        }

        // Store the arguments in successive nodes of this list.
        template <
            // typename A0, typename A1, ...
            BOOST_PP_ENUM_PARAMS(
                BOOST_PARAMETER_COMPOSE_MAX_ARITY
              , typename A
            )
        >
        inline BOOST_CONSTEXPR arg_list(
            // A0& a0, A1& a1, ...
            BOOST_PP_ENUM_BINARY_PARAMS(
                BOOST_PARAMETER_COMPOSE_MAX_ARITY
              , A
              , & a
            )
        ) : Next(
                // a1, a2, ...
                BOOST_PP_ENUM_SHIFTED_PARAMS(
                    BOOST_PARAMETER_COMPOSE_MAX_ARITY
                  , a
                )
              , ::boost::parameter::aux::void_reference()
            )
          , arg(a0)
        {
        }

        // A metafunction class that, given a keyword and a default type,
        // returns the appropriate result type for a keyword lookup given
        // that default.
        struct binding
        {
            typedef typename Next::binding next_binding;

            template <typename KW, typename Default, typename Reference>
            struct apply
            {
                typedef typename ::boost::mpl::eval_if<
                    ::boost::is_same<KW,key_type>
                  , ::boost::mpl::if_<Reference,reference,value_type>
                  , ::boost::mpl::apply_wrap3<
                        next_binding
                      , KW
                      , Default
                      , Reference
                    >
                >::type type;
            };
        };

#if !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
        // Overload for key_type, so the assert below will fire
        // if the same keyword is used again.
        static ::boost::parameter::aux::yes_tag has_key(key_type*);
        using Next::has_key;

     private:
#if defined(BOOST_NO_SFINAE) || BOOST_WORKAROUND(BOOST_MSVC, < 1800)
        BOOST_MPL_ASSERT_MSG(
            sizeof(
                Next::has_key(
                    static_cast<key_type*>(BOOST_PARAMETER_AUX_PP_NULLPTR)
                )
            ) == sizeof(::boost::parameter::aux::no_tag)
          , duplicate_keyword
          , (key_type)
        );
#else
        typedef ::boost::mpl::bool_<
            sizeof(
                Next::has_key(
                    static_cast<key_type*>(BOOST_PARAMETER_AUX_PP_NULLPTR)
                )
            ) == sizeof(::boost::parameter::aux::no_tag)
        > _has_unique_key;

        BOOST_MPL_ASSERT_MSG(
            !(EmitsErrors::value) || (_has_unique_key::value)
          , duplicate_keyword
          , (key_type)
        );
#endif  // SFINAE/MSVC workarounds needed
#endif  // Borland workarounds not needed

     private:
        //
        // Begin implementation of indexing operators
        // for looking up specific arguments by name.
        //

        // Helpers that handle the case when TaggedArg is empty<T>.
        template <typename D>
        inline BOOST_CONSTEXPR reference
            get_default(D const&, ::boost::mpl::false_) const
        {
            return this->arg.get_value();
        }

        template <typename D>
        inline BOOST_CONSTEXPR reference
            get_default(D const& d, ::boost::mpl::true_) const
        {
            return (
                this->arg.get_value()
              ? this->arg.get_value().get()
              : this->arg.get_value().construct(d.value)
            );
        }

     public:
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
        // These older compilers don't support the overload set creation
        // idiom well, so we need to do all the return type calculation
        // for the compiler and dispatch through an outer function template.

        // A metafunction class that, given a keyword, returns the base
        // sublist whose get() function can produce the value for that key.
        struct key_owner
        {
            typedef typename Next::key_owner next_key_owner;

            template <typename KW>
            struct apply
            {
                typedef typename ::boost::mpl::eval_if<
                    ::boost::is_same<KW,key_type>
                  , ::boost::mpl::identity<
                        ::boost::parameter::aux::arg_list<TaggedArg,Next>
                    >
                  , ::boost::mpl::apply_wrap1<next_key_owner,KW>
                >::type type;
            };
        };

        // Outer indexing operators that dispatch to the right node's
        // get() function.
        template <typename KW>
        inline BOOST_CONSTEXPR typename ::boost::mpl::apply_wrap3<
            binding
          , KW
          , ::boost::parameter::void_
          , ::boost::mpl::true_
        >::type
            operator[](::boost::parameter::keyword<KW> const& x) const
        {
            typename ::boost::mpl::apply_wrap1<key_owner,KW>::type const&
                sublist = *this;
            return sublist.get(x);
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
            typename ::boost::mpl::apply_wrap1<key_owner,KW>::type const&
                sublist = *this;
            return sublist.get(x);
        }

        template <typename KW, typename F>
        inline BOOST_CONSTEXPR typename ::boost::mpl::apply_wrap3<
            binding
          , KW
          , typename ::boost::parameter::aux::result_of0<F>::type
          , ::boost::mpl::true_
        >::type
            operator[](
                BOOST_PARAMETER_lazy_default_fallback<KW,F> const& x
            ) const
        {
            typename ::boost::mpl::apply_wrap1<key_owner,KW>::type const&
                sublist = *this;
            return sublist.get(x);
        }

        // These just return the stored value; when empty_arg_list is reached,
        // indicating no matching argument was passed, the default is
        // returned, or if no default_ or lazy_default was passed, compilation
        // fails.
        inline BOOST_CONSTEXPR reference
            get(::boost::parameter::keyword<key_type> const&) const
        {
            BOOST_MPL_ASSERT_NOT((_holds_maybe));
            return this->arg.get_value();
        }

        template <typename Default>
        inline BOOST_CONSTEXPR reference
            get(
                ::boost::parameter::aux::default_<key_type,Default> const& d
            ) const
        {
            return this->get_default(d, _holds_maybe());
        }

        template <typename Default>
        inline BOOST_CONSTEXPR reference
            get(
                BOOST_PARAMETER_lazy_default_fallback<key_type,Default> const&
            ) const
        {
            return this->arg.get_value();
        }
#else   // !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
        inline BOOST_CONSTEXPR reference
            operator[](::boost::parameter::keyword<key_type> const&) const
        {
            BOOST_MPL_ASSERT_NOT((_holds_maybe));
            return this->arg.get_value();
        }

        template <typename Default>
        inline BOOST_CONSTEXPR reference
            operator[](
                ::boost::parameter::aux::default_<key_type,Default> const& d
            ) const
        {
            return this->get_default(d, _holds_maybe());
        }

        template <typename Default>
        inline BOOST_CONSTEXPR reference
            operator[](
                BOOST_PARAMETER_lazy_default_fallback<key_type,Default> const&
            ) const
        {
            BOOST_MPL_ASSERT_NOT((_holds_maybe));
            return this->arg.get_value();
        }

        // Builds an overload set including operator[]s defined
        // in base classes.
        using Next::operator[];

        //
        // End of indexing support
        //

        // For parameter_requirements matching this node's key_type, return
        // a bool constant wrapper indicating whether the requirements are
        // satisfied by TaggedArg.  Used only for compile-time computation
        // and never really called, so a declaration is enough.
        template <typename HasDefault, typename Predicate, typename ArgPack>
        static typename
#if !defined(BOOST_NO_SFINAE) && !BOOST_WORKAROUND(BOOST_MSVC, < 1800)
        ::boost::lazy_enable_if<
            typename ::boost::mpl::if_<
                EmitsErrors
              , ::boost::mpl::true_
              , _has_unique_key
            >::type,
#endif
            ::boost::parameter::aux::augment_predicate<
                Predicate
              , reference
              , key_type
              , value_type
              , ArgPack
#if !defined(BOOST_NO_SFINAE) && !BOOST_WORKAROUND(BOOST_MSVC, < 1800)
           >
#endif
        >::type
            satisfies(
                ::boost::parameter::aux::parameter_requirements<
                    key_type
                  , Predicate
                  , HasDefault
                >*
              , ArgPack*
            );

        // Builds an overload set including satisfies functions defined
        // in base classes.
        using Next::satisfies;
#endif  // Borland workarounds needed

        // Comma operator to compose argument list without using parameters<>.
        // Useful for argument lists with undetermined length.
        template <typename KW, typename T2>
        inline BOOST_CONSTEXPR ::boost::parameter::aux::arg_list<
            ::boost::parameter::aux::tagged_argument<KW,T2>
          , self
        >
            operator,(
                ::boost::parameter::aux::tagged_argument<KW,T2> const& x
            ) const
        {
            return ::boost::parameter::aux::arg_list<
                ::boost::parameter::aux::tagged_argument<KW,T2>
              , self
            >(x, *this);
        }

        // MPL sequence support
        typedef self type;        // Convenience for users
        typedef Next tail_type;   // For the benefit of iterators
        // For dispatching to sequence intrinsics
        typedef ::boost::parameter::aux::arg_list_tag tag;
    };
}}} // namespace boost::parameter::aux

#endif  // BOOST_PARAMETER_HAS_PERFECT_FORWARDING

#if defined(BOOST_PARAMETER_CAN_USE_MP11)

namespace boost { namespace parameter { namespace aux {

    template <typename ...ArgTuples>
    struct arg_list_cons;

    template <>
    struct arg_list_cons<>
    {
        using type = ::boost::parameter::aux::empty_arg_list;
    };

    template <typename ArgTuple0, typename ...Tuples>
    struct arg_list_cons<ArgTuple0,Tuples...>
    {
        using type = ::boost::parameter::aux::arg_list<
            typename ArgTuple0::tagged_arg
          , typename ::boost::parameter::aux::arg_list_cons<Tuples...>::type
          , typename ArgTuple0::emits_errors
        >;
    };

    template <
        typename Keyword
      , typename TaggedArg
      , typename EmitsErrors = ::boost::mp11::mp_true
    >
    struct flat_like_arg_tuple
    {
        using tagged_arg = TaggedArg;
        using emits_errors = EmitsErrors;
    };

    template <typename ...ArgTuples>
    class flat_like_arg_list
      : public ::boost::parameter::aux::arg_list_cons<ArgTuples...>::type
    {
        using _base_type = typename ::boost::parameter::aux
        ::arg_list_cons<ArgTuples...>::type;

     public:
        inline BOOST_CONSTEXPR flat_like_arg_list(
            typename _base_type::tagged_arg const& head
          , typename _base_type::tail_type const& tail
        ) : _base_type(head, tail)
        {
        }

        template <typename ...Args>
        inline BOOST_CONSTEXPR flat_like_arg_list(Args&&... args)
          : _base_type(::std::forward<Args>(args)...)
        {
        }

        using _base_type::operator[];
        using _base_type::satisfies;

        // Comma operator to compose argument list without using parameters<>.
        // Useful for argument lists with undetermined length.
        template <typename TaggedArg>
        inline BOOST_CONSTEXPR ::boost::parameter::aux::flat_like_arg_list<
            ::boost::parameter::aux::flat_like_arg_tuple<
                typename TaggedArg::base_type::key_type
              , typename TaggedArg::base_type
            >
          , ArgTuples...
        >
            operator,(TaggedArg const& x) const
        {
            return ::boost::parameter::aux::flat_like_arg_list<
                ::boost::parameter::aux::flat_like_arg_tuple<
                    typename TaggedArg::base_type::key_type
                  , typename TaggedArg::base_type
                >
              , ArgTuples...
            >(
                static_cast<typename TaggedArg::base_type const&>(x)
              , static_cast<_base_type const&>(*this)
            );
        }
    };

    template <>
    class flat_like_arg_list<>
      : public ::boost::parameter::aux::empty_arg_list
    {
        using _base_type = ::boost::parameter::aux::empty_arg_list;

     public:
        template <typename ...Args>
        inline BOOST_CONSTEXPR flat_like_arg_list(Args&&... args)
          : _base_type(::std::forward<Args>(args)...)
        {
        }

        using _base_type::operator[];
        using _base_type::satisfies;

        // Comma operator to compose argument list without using parameters<>.
        // Useful for argument lists with undetermined length.
        template <typename TaggedArg>
        inline BOOST_CONSTEXPR ::boost::parameter::aux::flat_like_arg_list<
            ::boost::parameter::aux::flat_like_arg_tuple<
                typename TaggedArg::base_type::key_type
              , typename TaggedArg::base_type
            >
        >
            operator,(TaggedArg const& x) const
        {
            return ::boost::parameter::aux::flat_like_arg_list<
                ::boost::parameter::aux::flat_like_arg_tuple<
                    typename TaggedArg::base_type::key_type
                  , typename TaggedArg::base_type
                >
            >(
                static_cast<typename TaggedArg::base_type const&>(x)
              , static_cast<_base_type const&>(*this)
            );
        }
    };
}}} // namespace boost::parameter::aux

#endif  // BOOST_PARAMETER_CAN_USE_MP11

#include <boost/mpl/iterator_tags.hpp>

namespace boost { namespace parameter { namespace aux {

    // MPL sequence support
    template <typename ArgumentPack>
    struct arg_list_iterator
    {
        typedef ::boost::mpl::forward_iterator_tag category;

        // The incremented iterator
        typedef ::boost::parameter::aux
        ::arg_list_iterator<typename ArgumentPack::tail_type> next;

        // dereferencing yields the key type
        typedef typename ArgumentPack::key_type type;
    };

    template <>
    struct arg_list_iterator< ::boost::parameter::aux::empty_arg_list>
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/mpl/begin_end_fwd.hpp>

// MPL sequence support
namespace boost { namespace mpl {

    template <>
    struct begin_impl< ::boost::parameter::aux::arg_list_tag>
    {
        template <typename S>
        struct apply
        {
            typedef ::boost::parameter::aux::arg_list_iterator<S> type;
        };
    };

    template <>
    struct end_impl< ::boost::parameter::aux::arg_list_tag>
    {
        template <typename>
        struct apply
        {
            typedef ::boost::parameter::aux::arg_list_iterator<
                ::boost::parameter::aux::empty_arg_list
            > type;
        };
    };
}} // namespace boost::mpl

#include <boost/parameter/value_type.hpp>
#include <boost/mpl/has_key_fwd.hpp>
#include <boost/type_traits/is_void.hpp>

namespace boost { namespace mpl {

    template <>
    struct has_key_impl< ::boost::parameter::aux::arg_list_tag>
    {
        template <typename ArgList, typename Keyword>
        struct apply
        {
            typedef typename ::boost::mpl::if_<
                ::boost::is_void<
                    typename ::boost::parameter
                    ::value_type<ArgList,Keyword,void>::type
                >
              , ::boost::mpl::false_
              , ::boost::mpl::true_
            >::type type;
        };
    };
}} // namespace boost::mpl

#include <boost/mpl/count_fwd.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace mpl {

    template <>
    struct count_impl< ::boost::parameter::aux::arg_list_tag>
    {
        template <typename ArgList, typename Keyword>
        struct apply
        {
            typedef typename ::boost::mpl::if_<
                ::boost::is_void<
                    typename ::boost::parameter
                    ::value_type<ArgList,Keyword,void>::type
                >
              , ::boost::mpl::int_<0>
              , ::boost::mpl::int_<1>
            >::type type;
        };
    };
}} // namespace boost::mpl

#include <boost/mpl/key_type_fwd.hpp>
#include <boost/mpl/identity.hpp>

namespace boost { namespace mpl {

    template <>
    struct key_type_impl< ::boost::parameter::aux::arg_list_tag>
    {
        template <typename ArgList, typename Keyword>
        struct apply
        {
            typedef typename ::boost::mpl::eval_if<
                ::boost::is_void<
                    typename ::boost::parameter
                    ::value_type<ArgList,Keyword,void>::type
                >
              , void
              , ::boost::mpl::identity<Keyword>
            >::type type;
        };
    };
}} // namespace boost::mpl

#include <boost/mpl/value_type_fwd.hpp>

namespace boost { namespace mpl {

    template <>
    struct value_type_impl< ::boost::parameter::aux::arg_list_tag>
      : ::boost::mpl::key_type_impl< ::boost::parameter::aux::arg_list_tag>
    {
    };
}} // namespace boost::mpl

#include <boost/mpl/at_fwd.hpp>

namespace boost { namespace mpl {

    template <>
    struct at_impl< ::boost::parameter::aux::arg_list_tag>
      : ::boost::mpl::key_type_impl< ::boost::parameter::aux::arg_list_tag>
    {
    };
}} // namespace boost::mpl

#include <boost/mpl/order_fwd.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/distance.hpp>

namespace boost { namespace mpl {

    template <>
    struct order_impl< ::boost::parameter::aux::arg_list_tag>
    {
        template <typename ArgList, typename Keyword>
        struct apply
        {
            typedef typename ::boost::mpl::find<ArgList,Keyword>::type Itr;
            typedef typename ::boost::mpl::eval_if<
                ::boost::is_void<
                    typename ::boost::parameter
                    ::value_type<ArgList,Keyword,void>::type
                >
              , ::boost::mpl::identity< ::boost::mpl::void_>
              , ::boost::mpl::distance<
                    Itr
                  , ::boost::parameter::aux::arg_list_iterator<
                        ::boost::parameter::aux::empty_arg_list
                    >
                >
            >::type type;
        };
    };
}} // namespace boost::mpl

#endif  // include guard


/* arg_list.hpp
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
*/