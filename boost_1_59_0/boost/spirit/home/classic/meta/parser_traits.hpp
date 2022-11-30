/*=============================================================================
    Copyright (c) 2002-2003 Joel de Guzman
    Copyright (c) 2002-2003 Hartmut Kaiser
    Copyright (c) 2003 Martin Wille
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_PARSER_TRAITS_HPP)
#define BOOST_SPIRIT_PARSER_TRAITS_HPP

#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/static_assert.hpp>

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/parser.hpp>
#include <boost/spirit/home/classic/meta/impl/parser_traits.ipp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

///////////////////////////////////////////////////////////////////////////////
//
//  Parser traits templates
//
//      Used to determine the type and several other characteristics of a given
//      parser type.
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
// The is_parser traits template can be used to tell wether a given
// class is a parser.
//
///////////////////////////////////////////////////////////////////////////////
template <typename T>
struct is_parser
{
    BOOST_STATIC_CONSTANT(bool, value =
        (::boost::is_base_and_derived<parser<T>, T>::value));

//  [JDG 2/3/03] simplified implementation by
//  using boost::is_base_and_derived
};

///////////////////////////////////////////////////////////////////////////////
//
//  The is_unary_composite traits template can be used to tell if a given
//  parser is a unary parser as for instance kleene_star or optional.
//
///////////////////////////////////////////////////////////////////////////////
template <typename UnaryT>
struct is_unary_composite {

    BOOST_STATIC_CONSTANT(bool, value = (::boost::is_convertible<
        typename UnaryT::parser_category_t, unary_parser_category>::value));
};

///////////////////////////////////////////////////////////////////////////////
//
//  The is_acction_parser traits template can be used to tell if a given
//  parser is a action parser, i.e. it is a composite consisting of a
//  auxiliary parser and an attached semantic action.
//
///////////////////////////////////////////////////////////////////////////////
template <typename ActionT>
struct is_action_parser {

    BOOST_STATIC_CONSTANT(bool, value = (::boost::is_convertible<
        typename ActionT::parser_category_t, action_parser_category>::value));
};

///////////////////////////////////////////////////////////////////////////////
//
//  The is_binary_composite traits template can be used to tell if a given
//  parser is a binary parser as for instance sequence or difference.
//
///////////////////////////////////////////////////////////////////////////////
template <typename BinaryT>
struct is_binary_composite {

    BOOST_STATIC_CONSTANT(bool, value = (::boost::is_convertible<
        typename BinaryT::parser_category_t, binary_parser_category>::value));
};

///////////////////////////////////////////////////////////////////////////////
//
//  The is_composite_parser traits template can be used to tell if a given
//  parser is a unary or a binary parser composite type.
//
///////////////////////////////////////////////////////////////////////////////
template <typename CompositeT>
struct is_composite_parser {

    BOOST_STATIC_CONSTANT(bool, value = (
        ::BOOST_SPIRIT_CLASSIC_NS::is_unary_composite<CompositeT>::value ||
        ::BOOST_SPIRIT_CLASSIC_NS::is_binary_composite<CompositeT>::value));
};

///////////////////////////////////////////////////////////////////////////////
template <typename ParserT>
struct is_alternative {

    BOOST_STATIC_CONSTANT(bool, value = (
        ::BOOST_SPIRIT_CLASSIC_NS::impl::parser_type_traits<ParserT>::is_alternative));
};

template <typename ParserT>
struct is_sequence {

    BOOST_STATIC_CONSTANT(bool, value = (
        ::BOOST_SPIRIT_CLASSIC_NS::impl::parser_type_traits<ParserT>::is_sequence));
};

template <typename ParserT>
struct is_sequential_or {

    BOOST_STATIC_CONSTANT(bool, value = (
        ::BOOST_SPIRIT_CLASSIC_NS::impl::parser_type_traits<ParserT>::is_sequential_or));
};

template <typename ParserT>
struct is_intersection {

    BOOST_STATIC_CONSTANT(bool, value = (
        ::BOOST_SPIRIT_CLASSIC_NS::impl::parser_type_traits<ParserT>::is_intersection));
};

template <typename ParserT>
struct is_difference {

    BOOST_STATIC_CONSTANT(bool, value = (
        ::BOOST_SPIRIT_CLASSIC_NS::impl::parser_type_traits<ParserT>::is_difference));
};

template <typename ParserT>
struct is_exclusive_or {

    BOOST_STATIC_CONSTANT(bool, value = (
        ::BOOST_SPIRIT_CLASSIC_NS::impl::parser_type_traits<ParserT>::is_exclusive_or));
};

template <typename ParserT>
struct is_optional {

    BOOST_STATIC_CONSTANT(bool, value = (
        ::BOOST_SPIRIT_CLASSIC_NS::impl::parser_type_traits<ParserT>::is_optional));
};

template <typename ParserT>
struct is_kleene_star {

    BOOST_STATIC_CONSTANT(bool, value = (
        ::BOOST_SPIRIT_CLASSIC_NS::impl::parser_type_traits<ParserT>::is_kleene_star));
};

template <typename ParserT>
struct is_positive {

    BOOST_STATIC_CONSTANT(bool, value = (
        ::BOOST_SPIRIT_CLASSIC_NS::impl::parser_type_traits<ParserT>::is_positive));
};

///////////////////////////////////////////////////////////////////////////////
//
//  Parser extraction templates
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  The unary_subject template can be used to return the type of the
//  parser used as the subject of an unary parser.
//  If the parser under inspection is not an unary type parser the compilation
//  will fail.
//
///////////////////////////////////////////////////////////////////////////////
template <typename UnaryT>
struct unary_subject {

    BOOST_STATIC_ASSERT(BOOST_SPIRIT_CLASSIC_NS::is_unary_composite<UnaryT>::value);
    typedef typename UnaryT::subject_t type;
};

///////////////////////////////////////////////////////////////////////////////
//
//  The get_unary_subject template function returns the parser object, which
//  is used as the subject of an unary parser.
//  If the parser under inspection is not an unary type parser the compilation
//  will fail.
//
///////////////////////////////////////////////////////////////////////////////
template <typename UnaryT>
inline typename unary_subject<UnaryT>::type const &
get_unary_subject(UnaryT const &unary_)
{
    BOOST_STATIC_ASSERT(::BOOST_SPIRIT_CLASSIC_NS::is_unary_composite<UnaryT>::value);
    return unary_.subject();
}

///////////////////////////////////////////////////////////////////////////////
//
//  The binary_left_subject and binary_right_subject templates can be used to
//  return the types of the parsers used as the left and right subject of an
//  binary parser.
//  If the parser under inspection is not a binary type parser the compilation
//  will fail.
//
///////////////////////////////////////////////////////////////////////////////
template <typename BinaryT>
struct binary_left_subject {

    BOOST_STATIC_ASSERT(::BOOST_SPIRIT_CLASSIC_NS::is_binary_composite<BinaryT>::value);
    typedef typename BinaryT::left_t type;
};

template <typename BinaryT>
struct binary_right_subject {

    BOOST_STATIC_ASSERT(::BOOST_SPIRIT_CLASSIC_NS::is_binary_composite<BinaryT>::value);
    typedef typename BinaryT::right_t type;
};

///////////////////////////////////////////////////////////////////////////////
//
//  The get_binary_left_subject and get_binary_right_subject template functions
//  return the parser object, which is used as the left or right subject of a
//  binary parser.
//  If the parser under inspection is not a binary type parser the compilation
//  will fail.
//
///////////////////////////////////////////////////////////////////////////////
template <typename BinaryT>
inline typename binary_left_subject<BinaryT>::type const &
get_binary_left_subject(BinaryT const &binary_)
{
    BOOST_STATIC_ASSERT(::BOOST_SPIRIT_CLASSIC_NS::is_binary_composite<BinaryT>::value);
    return binary_.left();
}

template <typename BinaryT>
inline typename binary_right_subject<BinaryT>::type const &
get_binary_right_subject(BinaryT const &binary_)
{
    BOOST_STATIC_ASSERT(::BOOST_SPIRIT_CLASSIC_NS::is_binary_composite<BinaryT>::value);
    return binary_.right();
}

///////////////////////////////////////////////////////////////////////////////
//
//  The action_subject template can be used to return the type of the
//  parser used as the subject of an action parser.
//  If the parser under inspection is not an action type parser the compilation
//  will fail.
//
///////////////////////////////////////////////////////////////////////////////
template <typename ActionT>
struct action_subject {

    BOOST_STATIC_ASSERT(::BOOST_SPIRIT_CLASSIC_NS::is_action_parser<ActionT>::value);
    typedef typename ActionT::subject_t type;
};

///////////////////////////////////////////////////////////////////////////////
//
//  The get_action_subject template function returns the parser object, which
//  is used as the subject of an action parser.
//  If the parser under inspection is not an action type parser the compilation
//  will fail.
//
///////////////////////////////////////////////////////////////////////////////
template <typename ActionT>
inline typename action_subject<ActionT>::type const &
get_action_subject(ActionT const &action_)
{
    BOOST_STATIC_ASSERT(::BOOST_SPIRIT_CLASSIC_NS::is_action_parser<ActionT>::value);
    return action_.subject();
}

///////////////////////////////////////////////////////////////////////////////
//
//  The semantic_action template can be used to return the type of the
//  attached semantic action of an action parser.
//  If the parser under inspection is not an action type parser the compilation
//  will fail.
//
///////////////////////////////////////////////////////////////////////////////
template <typename ActionT>
struct semantic_action {

    BOOST_STATIC_ASSERT(::BOOST_SPIRIT_CLASSIC_NS::is_action_parser<ActionT>::value);
    typedef typename ActionT::predicate_t type;
};

///////////////////////////////////////////////////////////////////////////////
//
//  The get_semantic_action template function returns the attached semantic
//  action of an action parser.
//  If the parser under inspection is not an action type parser the compilation
//  will fail.
//
///////////////////////////////////////////////////////////////////////////////
template <typename ActionT>
inline typename semantic_action<ActionT>::type const &
get_semantic_action(ActionT const &action_)
{
    BOOST_STATIC_ASSERT(::BOOST_SPIRIT_CLASSIC_NS::is_action_parser<ActionT>::value);
    return action_.predicate();
}

///////////////////////////////////////////////////////////////////////////////
BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif // !defined(BOOST_SPIRIT_PARSER_TRAITS_HPP)

/* parser_traits.hpp
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
*/