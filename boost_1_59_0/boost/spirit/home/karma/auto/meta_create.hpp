//  Copyright (c) 2001-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_META_CREATE_NOV_21_2009_0425PM)
#define BOOST_SPIRIT_KARMA_META_CREATE_NOV_21_2009_0425PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/karma/domain.hpp>
#include <boost/spirit/home/support/common_terminals.hpp>
#include <boost/spirit/home/support/auto/meta_create.hpp>

#include <boost/utility/enable_if.hpp>
#include <boost/variant.hpp>
#include <boost/optional.hpp>
#include <boost/config.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/fusion/include/as_vector.hpp>
#include <boost/proto/tags.hpp>
#include <boost/type_traits/is_same.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace karma
{
    ///////////////////////////////////////////////////////////////////////////
    // compatible STL containers
    template <typename Container>
    struct meta_create_container
    {
        typedef make_unary_proto_expr<
            typename Container::value_type
          , proto::tag::dereference, karma::domain
        > make_proto_expr;

        typedef typename make_proto_expr::type type;

        static type call()
        {
            return make_proto_expr::call();
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    // String types
    template <typename String>
    struct meta_create_string
    {
        typedef spirit::standard::string_type type;
        static type const call() { return type(); }
    };

    template <>
    struct meta_create_string<wchar_t*>
    {
        typedef spirit::standard_wide::string_type type;
        static type const call() { return type(); }
    };

    template <>
    struct meta_create_string<wchar_t const*>
    {
        typedef spirit::standard_wide::string_type type;
        static type const call() { return type(); }
    };

    template <int N>
    struct meta_create_string<wchar_t[N]>
    {
        typedef spirit::standard_wide::string_type type;
        static type const call() { return type(); }
    };

    template <int N>
    struct meta_create_string<wchar_t const[N]>
    {
        typedef spirit::standard_wide::string_type type;
        static type const call() { return type(); }
    };

    template <int N>
    struct meta_create_string<wchar_t(&)[N]>
    {
        typedef spirit::standard_wide::string_type type;
        static type const call() { return type(); }
    };

    template <int N>
    struct meta_create_string<wchar_t const(&)[N]>
    {
        typedef spirit::standard_wide::string_type type;
        static type const call() { return type(); }
    };

    template <typename Traits, typename Allocator>
    struct meta_create_string<std::basic_string<wchar_t, Traits, Allocator> >
    {
        typedef spirit::standard_wide::string_type type;
        static type const call() { return type(); }
    };

    ///////////////////////////////////////////////////////////////////////////
    // Fusion sequences
    template <typename Sequence>
    struct meta_create_sequence
    {
        // create a mpl sequence from the given fusion sequence
        typedef typename mpl::fold<
            typename fusion::result_of::as_vector<Sequence>::type
          , mpl::vector<>, mpl::push_back<mpl::_, mpl::_>
        >::type sequence_type;

        typedef make_nary_proto_expr<
            sequence_type, proto::tag::shift_left, karma::domain
        > make_proto_expr;

        typedef typename make_proto_expr::type type;

        static type call()
        {
            return make_proto_expr::call();
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    // the default is to use the standard streaming operator unless it's a
    // STL container or a fusion sequence

    // The default implementation will be chosen if no predefined mapping of
    // the data type T to a Karma component is defined.
    struct no_auto_mapping_exists {};

    template <typename T, typename Enable = void>
    struct meta_create_impl : mpl::identity<no_auto_mapping_exists> {};

    template <typename T>
    struct meta_create_impl<T
          , typename enable_if<
                mpl::and_<
                    traits::is_container<T>
                  , mpl::not_<traits::is_string<T> >
                  , mpl::not_<fusion::traits::is_sequence<T> >
                > >::type>
      : meta_create_container<T> {};

    template <typename T>
    struct meta_create_impl<T
          , typename enable_if<traits::is_string<T> >::type>
      : meta_create_string<T> {};

    template <typename T>
    struct meta_create_impl<T, typename enable_if<
                spirit::detail::is_fusion_sequence_but_not_proto_expr<T>
            >::type>
      : meta_create_sequence<T> {};

    template <typename T, typename Enable = void>
    struct meta_create : meta_create_impl<T> {};

    ///////////////////////////////////////////////////////////////////////////
    // optional
    template <typename T>
    struct meta_create<boost::optional<T> >
    {
        typedef make_unary_proto_expr<
            T, proto::tag::negate, karma::domain
        > make_proto_expr;

        typedef typename make_proto_expr::type type;

        static type call()
        {
            return make_proto_expr::call();
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    // alternatives
    template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
    struct meta_create<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
    {
        typedef make_nary_proto_expr<
            typename boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>::types
          , proto::tag::bitwise_or, karma::domain
        > make_proto_expr;

        typedef typename make_proto_expr::type type;

        static type call()
        {
            return make_proto_expr::call();
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    // predefined specializations for primitive components

    // character generator
    template <>
    struct meta_create<char>
    {
        typedef spirit::standard::char_type type;
        static type const call() { return type(); }
    };
    template <>
    struct meta_create<signed char>
    {
        typedef spirit::standard::char_type type;
        static type const call() { return type(); }
    };
    template <>
    struct meta_create<wchar_t>
    {
        typedef spirit::standard_wide::char_type type;
        static type const call() { return type(); }
    };

    template <>
    struct meta_create<unsigned char>
    {
        typedef spirit::standard::char_type type;
        static type const call() { return type(); }
    };

    // boolean generator
    template <>
    struct meta_create<bool>
    {
        typedef spirit::bool_type type;
        static type call() { return type(); }
    };

    // integral generators
    template <>
    struct meta_create<int>
    {
        typedef spirit::int_type type;
        static type call() { return type(); }
    };
    template <>
    struct meta_create<short>
    {
        typedef spirit::short_type type;
        static type call() { return type(); }
    };
    template <>
    struct meta_create<long>
    {
        typedef spirit::long_type type;
        static type call() { return type(); }
    };
    template <>
    struct meta_create<unsigned int>
    {
        typedef spirit::uint_type type;
        static type call() { return type(); }
    };
#if !defined(BOOST_NO_INTRINSIC_WCHAR_T)
    template <>
    struct meta_create<unsigned short>
    {
        typedef spirit::ushort_type type;
        static type call() { return type(); }
    };
#endif
    template <>
    struct meta_create<unsigned long>
    {
        typedef spirit::ulong_type type;
        static type call() { return type(); }
    };

#ifdef BOOST_HAS_LONG_LONG
    template <>
    struct meta_create<boost::long_long_type>
    {
        typedef spirit::long_long_type type;
        static type call() { return type(); }
    };
    template <>
    struct meta_create<boost::ulong_long_type>
    {
        typedef spirit::ulong_long_type type;
        static type call() { return type(); }
    };
#endif

    // floating point generators
    template <>
    struct meta_create<float>
    {
        typedef spirit::float_type type;
        static type call() { return type(); }
    };
    template <>
    struct meta_create<double>
    {
        typedef spirit::double_type type;
        static type call() { return type(); }
    };
    template <>
    struct meta_create<long double>
    {
        typedef spirit::long_double_type type;
        static type call() { return type(); }
    };
}}}

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace traits
{
    ///////////////////////////////////////////////////////////////////////////
    // main customization point for create_generator
    template <typename T, typename Enable = void>
    struct create_generator : karma::meta_create<T> {};

    ///////////////////////////////////////////////////////////////////////////
    // dispatch this to the karma related specializations
    template <typename T>
    struct meta_create<karma::domain, T>
      : create_generator<typename spirit::detail::remove_const_ref<T>::type> {};

    ///////////////////////////////////////////////////////////////////////////
    // Check whether a valid mapping exits for the given data type to a Karma
    // component
    template <typename T>
    struct meta_create_exists<karma::domain, T>
      : mpl::not_<is_same<
            karma::no_auto_mapping_exists
          , typename meta_create<karma::domain, T>::type
        > > {};
}}}

#endif

/* meta_create.hpp
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
*/