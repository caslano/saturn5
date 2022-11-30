//  Copyright (c) 2001-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_QI_META_CREATE_NOV_21_2009_0432PM)
#define BOOST_SPIRIT_QI_META_CREATE_NOV_21_2009_0432PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/qi/domain.hpp>
#include <boost/spirit/home/support/common_terminals.hpp>
#include <boost/spirit/home/support/auto/meta_create.hpp>

#include <boost/utility/enable_if.hpp>
#include <boost/variant.hpp>
#include <boost/optional.hpp>
#include <boost/config.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/proto/tags.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/fusion/include/as_vector.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace qi
{
    ///////////////////////////////////////////////////////////////////////////
    // compatible STL containers
    template <typename Container>
    struct meta_create_container
    {
        typedef make_unary_proto_expr<
            typename Container::value_type
          , proto::tag::dereference, qi::domain
        > make_proto_expr;

        typedef typename make_proto_expr::type type;

        static type call()
        {
            return make_proto_expr::call();
        }
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
            sequence_type, proto::tag::shift_right, qi::domain
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
    // the data type T to a Qi component is defined.
    struct no_auto_mapping_exists {};

    template <typename T, typename Enable = void>
    struct meta_create_impl : mpl::identity<no_auto_mapping_exists> {};

    template <typename T>
    struct meta_create_impl<T
          , typename enable_if<mpl::and_<
                traits::is_container<T>, mpl::not_<traits::is_string<T> > >
            >::type>
      : meta_create_container<T> {};

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
            T, proto::tag::negate, qi::domain
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
          , proto::tag::bitwise_or, qi::domain
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
        static type call() { return type(); }
    };
    template <>
    struct meta_create<signed char>
    {
        typedef spirit::standard::char_type type;
        static type call() { return type(); }
    };
    template <>
    struct meta_create<wchar_t>
    {
        typedef spirit::standard_wide::char_type type;
        static type call() { return type(); }
    };

    template <>
    struct meta_create<unsigned char>
    {
        typedef spirit::standard::char_type type;
        static type call() { return type(); }
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
    // main customization point for create_parser
    template <typename T, typename Enable = void>
    struct create_parser : qi::meta_create<T> {};

    ///////////////////////////////////////////////////////////////////////////
    // dispatch this to the Qi related specializations
    template <typename T>
    struct meta_create<qi::domain, T>
      : create_parser<typename spirit::detail::remove_const_ref<T>::type> {};

    ///////////////////////////////////////////////////////////////////////////
    // Check whether a valid mapping exits for the given data type to a Qi
    // component
    template <typename T>
    struct meta_create_exists<qi::domain, T>
      : mpl::not_<is_same<
            qi::no_auto_mapping_exists
          , typename meta_create<qi::domain, T>::type
        > > {};
}}}

#endif

/* meta_create.hpp
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
*/