/*=============================================================================
    Copyright (c) 2006 Tobias Schwinger
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_CORE_TYPEOF_HPP)
#define BOOST_SPIRIT_CORE_TYPEOF_HPP

#include <boost/config.hpp>
#include <boost/cstdint.hpp>

#include <boost/typeof/typeof.hpp>

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/nil.hpp>
#include <boost/spirit/home/classic/core/primitives/numerics_fwd.hpp>
#include <boost/spirit/home/classic/core/scanner/scanner_fwd.hpp>
#include <boost/spirit/home/classic/core/scanner/skipper_fwd.hpp>
#include <boost/spirit/home/classic/core/non_terminal/subrule_fwd.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    // parser.hpp
    template <typename IteratorT> struct parse_info;
    struct plain_parser_category;
    struct binary_parser_category;
    struct unary_parser_category;
    struct action_parser_category;

    // match.hpp
    template<typename T> class match; 

    // primitives/primitives.hpp
    template<class ParserT> struct negated_char_parser;
    template<typename CharT> struct chlit;
    template<typename CharT> struct range;
    template<typename IteratorT> class chseq;
    template<typename IteratorT> class strlit;
    struct nothing_parser;
    struct anychar_parser;
    struct alnum_parser;
    struct alpha_parser;
    struct cntrl_parser;
    struct digit_parser;
    struct xdigit_parser;
    struct graph_parser;
    struct upper_parser;
    struct lower_parser;
    struct print_parser;
    struct punct_parser;
    struct blank_parser;
    struct space_parser;
    struct eol_parser;
    struct end_parser; 

    // non_terminal/parser_context.hpp
    template<typename T> struct parser_context;

    // non_terminal/parser_id.hpp
    class parser_id;
    template<int N> struct parser_tag;
    class dynamic_parser_tag;
    struct parser_address_tag;

    // non_terminal/rule.hpp
    template<typename T0, typename T1, typename T2> class rule; 

    // non_terminal/grammar.hpp
    template<class DerivedT, typename ContextT> struct grammar; 

    // composite.hpp
    template<class ParserT, typename ActionT> class action;
    template<class A, class B> struct alternative;
    template<class A, class B> struct difference;
    template<class A, class B> struct exclusive_or;
    template<class A, class B> struct intersection;
    template<class a, class b> struct sequence;
    template<class A, class B> struct sequential_or;
    template<class S> struct kleene_star;
    template<class S> struct positive;
    template<class S> struct optional;
    // composite/directives.hpp
    template<class ParserT> struct contiguous;
    template<class ParserT> struct inhibit_case;
    template<class BaseT> struct inhibit_case_iteration_policy;
    template<class A, class B> struct longest_alternative;
    template<class A, class B> struct shortest_alternative;
    template<class ParserT, typename BoundsT> struct min_bounded;
    template<class ParserT, typename BoundsT> struct max_bounded;
    template<class ParserT, typename BoundsT> struct bounded;
    // composite/no_actions.hpp
    template<class Parser> struct no_actions_parser;
    template<class Base> struct no_actions_action_policy;
    // composite/epsilon.hpp
    struct epsilon_parser;
    template<typename CondT, bool positive> struct condition_parser;
    template<typename SubjectT> struct empty_match_parser;
    template<typename SubjectT> struct negated_empty_match_parser;

    // deprecated assign/push_back actor -- they live somewhere else, now
    struct assign_action;
    struct push_back_action;
    template<typename T, typename ActionT> class ref_value_actor;
    template<typename T, typename ValueT, typename ActionT> 
    class ref_const_ref_actor;

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS



#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()


// parser.hpp

BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::parse_info,1)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::plain_parser_category)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::binary_parser_category)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::unary_parser_category)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::action_parser_category)


// nil.hpp (included directly)

#if !defined(BOOST_SPIRIT_NIL_T_TYPEOF_REGISTERED)
// registration guard to decouple the iterators from the core
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::nil_t)
#   define BOOST_SPIRIT_NIL_T_TYPEOF_REGISTERED
#endif

// match.hpp

BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::match, 1)

BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::match<BOOST_SPIRIT_CLASSIC_NS::nil_t>)


// primitives/primitives.hpp

BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::negated_char_parser, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::chlit, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::range, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::chseq, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::strlit, 1)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::nothing_parser)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::anychar_parser)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::alnum_parser)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::alpha_parser)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::cntrl_parser)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::digit_parser)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::xdigit_parser)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::graph_parser)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::upper_parser)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::lower_parser)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::print_parser)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::punct_parser)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::blank_parser)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::space_parser)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::eol_parser)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::end_parser)

BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::chlit<char>)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::chlit<wchar_t>)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::range<char>)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::range<wchar_t>)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::chseq<char const *>)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::chseq<wchar_t const *>)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::strlit<char const *>)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::strlit<wchar_t const *>)


// primitives/numerics.hpp (has forward header)

BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::int_parser, (class)(int)(unsigned)(int))
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::uint_parser, (class)(int)(unsigned)(int))
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::sign_parser)
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::real_parser, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::real_parser_policies, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::ureal_parser_policies, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::strict_real_parser_policies, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::strict_ureal_parser_policies, 1)

BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::int_parser, (class)(int))
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::uint_parser, (class)(int))
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::int_parser<boost::int32_t>)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::uint_parser<boost::uint32_t>)
#if !defined(BOOST_NO_INT64_T)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::int_parser<boost::int64_t>)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::uint_parser<boost::uint64_t>)
#endif
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::real_parser_policies<float>)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::real_parser_policies<double>)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::ureal_parser_policies<float>)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::ureal_parser_policies<double>)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::strict_real_parser_policies<float>)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::strict_real_parser_policies<double>)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::strict_ureal_parser_policies<float>)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::strict_ureal_parser_policies<double>)


// scanner/scanner.hpp (has forward header)

BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::scanner,2)
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::scanner_policies,3)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::iteration_policy)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::action_policy)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::match_policy)

BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::scanner,1)
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::scanner_policies,2)


// scanner/skipper.hpp (has forward header)

BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::skipper_iteration_policy,1)
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::no_skipper_iteration_policy,1)
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::skip_parser_iteration_policy,2)

BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::skipper_iteration_policy<>)
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::skip_parser_iteration_policy,1)


// non_terminal/parser_context.hpp

BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::parser_context,1)

BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::parser_context<BOOST_SPIRIT_CLASSIC_NS::nil_t>)


// non_terminal/parser_id.hpp

BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::parser_id)
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::parser_tag, (int))
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::dynamic_parser_tag)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::parser_address_tag)


// non_terminal/subrule.hpp (has forward header)

BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::subrule,(int)(class))
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::subrule_parser,(int)(class)(class))
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::subrule_list,2)
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::subrules_scanner,2)

BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::subrule,(int))
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::subrule_parser,(int)(class))
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::subrule<0>)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::subrule<1>)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::subrule<2>)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::subrule<3>)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::subrule<4>)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::subrule<5>)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::subrule<6>)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::subrule<7>)


// non_terminal/rule.hpp

BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::rule,3)
#if BOOST_SPIRIT_RULE_SCANNERTYPE_LIMIT > 1
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::scanner_list,1)
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::scanner_list,BOOST_SPIRIT_RULE_SCANNERTYPE_LIMIT)
#endif


// non_terminal/grammar.hpp

BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::grammar,2)


// composite.hpp

BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::action, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::alternative, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::difference, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::exclusive_or, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::intersection, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::sequence, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::sequential_or, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::kleene_star, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::positive, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::optional, 1)


// composite/directives.hpp

BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::contiguous, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::inhibit_case, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::inhibit_case_iteration_policy,1)
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::longest_alternative, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::shortest_alternative, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::min_bounded, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::max_bounded, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::bounded, 2)


// composite/no_actions.hpp

BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::no_actions_parser, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::no_actions_action_policy, 1)

BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::no_actions_action_policy<BOOST_SPIRIT_CLASSIC_NS::action_policy>)


// composite/epsilon.hpp

BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::epsilon_parser)
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::condition_parser, (class)(bool))
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::empty_match_parser, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::negated_empty_match_parser, 1)


#if !defined(BOOST_SPIRIT_ACTOR_TYPEOF_HPP)
// deprecated assign/push_back actor -- they live somewhere else, now
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::ref_value_actor,2)
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::ref_const_ref_actor,3)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::assign_action)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::push_back_action)
#endif


#if BOOST_WORKAROUND(BOOST_MSVC,BOOST_TESTED_AT(1400)) && BOOST_MSVC >= 1400
namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    nil_t & operator* (nil_t);
    nil_t & operator+ (nil_t);

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

} } // namespace ::BOOST_SPIRIT_CLASSIC_NS
#endif


#endif
 

/* typeof.hpp
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
*/