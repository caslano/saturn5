/*==============================================================================
    Copyright (c) 2006 Tobias Schwinger
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
// The comment below contains a unnamed 'namespace {', which is flagged by the
// Boost inspect tool as a violation of common C++ programming rules. Since it's
// in a comment, well, we switch it off :-P
// boostinspect:nounnamed

//
// About:
// =====
//
// Using a typeof operator or Boost.Typeof to automatically set the type of
// variables (as done in the Spirit example demonstrating typeof) is by far not
// all we can do to tighten up our grammars as there are some significant
// drawbacks of this approach:
// - the types complexity scales with the complexity of the grammar (sooner or
//   later hitting the limits of the compiler),
// - recursive grammars are not possible, and
// - all parser objects are embedded by value.
//
// The Spirit documentation therefore recommends creating custom parser classes
// (derived from the a sub_grammar template):
//
//   http://www.boost.org/libs/spirit/doc/techniques.html#no_rules
//   http://www.boost.org/libs/spirit/doc/techniques.html#typeof
//
// In practice manually applying this technique leads to rather lengthy code and
// overthis requires the user to have a solid understanding of Spirit details.
//
// Here is a generalized, macro-based approach to easily create typeof-based
// grammars that can be recursive and arbitrarily complex.
//
//
// Quick manual:
// ============
//
// 1. Setup
//
// Before the rule parser macro (the protagonist of the facility) can be used
// the user must define the macro BOOST_SPIRIT__NAMESPACE (note the double
// underscore characeter) and setup a registration group for Boost.Typeof.
//
// Examples:
//
//   // should come after regular #includeS
//   #include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
//
//   // [...]
//
//   #define BOOST_SPIRIT__NAMESPACE (2,(my_project, my_module))
//   //                             | |     +- outer     +- inner
//   //                  ! space ! -+ |         namespace    namespace
//   //                               |
//   //                               +--- number of nested namespaces
//
//   namespace my_project { namespace my_module {
//
//   // [...]
//
//  ---
//
//   // should come after regular #includeS
//   #include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
//
//   // [...]
//
//   #define BOOST_SPIRIT__NAMESPACE (2,(my_project, (anonymous) ))
//
//   namespace my_project { namespace {
//
//   // [...]
//
//  ---
//
//   // should come after regular #includeS
//   #include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
//
//   // [...]
//
//
//   #define BOOST_SPIRIT__NAMESPACE -
//   // we're working at root namespace
//
//
// Why do I have to do this?
//
//   Boost.Typeof needs to assign a unique ID for each registration. This ID is
//   created composed of the line number and the registration group. The
//   facility performs Typeof registration and thus requires the source file to
//   have its own registration group. Further Boost.Typeof requires registration
//   to happen at root namespace so we have to close and reopen the namespace
//   we're in.
//
//
// 2. The rule parser macro
//
// A simple rule parser definition looks like that:
//
//   // we're at namespace scope here
//
//   // Skip parser for C/C++ comments and whitespace
//   BOOST_SPIRIT_RULE_PARSER(skipper,
//     -,-,-,
//
//     +(   confix_p("//",*anychar_p,eol_p)
//        | confix_p("/*",*anychar_p,"*/")
//        | space_p
//     )
//   )
//
// Now we can use 'skipper' in other Spirit expressions.
//
// The code above creates a parser (template) class 'skpper_t' and (in this
// case, because there are no parameters) a static const instance 'skipper' of
// that class. The class is automatically registered with Boost.Typeof. The type
// name our parser is skipper_t here.
//
//
// 2.1. Parametrized rule parsers
//
// Rule parser definitions can have parameters.
//
// Parameters are passed to the BOOST_SPIRIT_RULE_PARSER macro as its second
// argument (just pass '-' if there are no parameters) with the following
// format:
//
//   (N,( param1,param2, / ... / paramN ))
//    +-- number of parameters
//
// Example of a whole rule parser:
//
//   BOOST_SPIRIT_RULE_PARSER(new_name,
//     (1,( symbol_table )),-,-,
//
//     lexeme_d[ (alpha_p >> *alnum_p)[ symbol_table.add ] ]
//   )
//
// The expression 'new_name(my_symbols)' parses a string literal and adds it to
// the symbol table 'my_symbols'.
//
// The rule parser macro creates a function template as called 'new_name' that
// takes one parameter of deduced reference type and returns a specialization of
// 'new_name_t' in this case.
//
// Since parsers that require to be fast and lightweight often also require to
// be reentrant, it's quite common to pass in some semantic controller (the
// symbol table in the example above).
// However, parameters are templated so they can be anything (including parsers
// of course) so refactoring tasks can be abstracted with rule parsers as well.
//
//   BOOST_SPIRIT_RULE_PARSER(enumeration_parser,
//     (2,( element_parser, delimiter_parser )),-,-,
//
//     element_parser >> *(delimiter_parser >> element_parser)
//   )
//
// The expression 'enumeration_parser(int_p[ some_action ], ',')' creates a
// parser for a comma-separated list of integers.
//
//
// 2.2. Rule parsrs and semantic actions
//
// While semantic actions can be globally attached to a rule parser or passed
// to a parametrized rule parser as (part of) an argument, even more control is
// possible by using action placeholders. E.g:
//
//   BOOST_SPIRIT_ACTION_PLACEHOLDER(int_action)
//
//   BOOST_SPIRIT_RULE_PARSER(int_list,
//     -,(1,( int_action )),-,
//
//     int_p[ int_action ] >> *(',' >> int_p[ int_action ])
//   )
//
// The expression 'int_list[ my_action ]' parses a comma separated list of
// integers and calls 'my_action' for every integer parsed therein.
//
// Of course multiple actions can be attached to one placeholder as usual (in
// this case 'int_list[ my_action1 ][ my_action2 ] would call two actions).
//
// Further there can be multiple action placeholders for a single rule parser:
//
//   BOOST_SPIRIT_ACTION_PLACEHOLDER(feed_int)
//   BOOST_SPIRIT_ACTION_PLACEHOLDER(next_int)
//
//   BOOST_SPIRIT_RULE_PARSER(int_list,
//     -,(2,( feed_int, next_int )),-,
//
//     int_p[ feed_int ] >> *(',' >> int_p[ next_int ][ feed_int ])
//   )
//
// The expression 'int_list[ (feed_int = my_action1), (next_int = my_action2) ]'
// creates a parser for a comma separated list of integers with the actions
// attached appropriately.
//
//   int_list[ feed_int = my_action1,my_action2, next_int = my_action3 ]
//
// works too (in this case the action placeholder 'feed_int' has two actions
// attached to it).
//
// You can both override and append actions associated with an action
// placeholder:
//
//   var = int_list[ feed_int = my_action1, next_int = my_action2 ]
//
//   // [...]
//
//   ... var[ feed_int = another_action ]
//   // 'another_action' overrides the actions previously attached to 'feed_int'
//
//   ... var[ next_int += another_action ]
//   // 'another_action' is appended to the list of actions attached to
//   // 'next_int'
//
// Action placeholders are not entirely for free -- they add to the size and the
// initialization time of the rule parser. However, the impact on an already
// initialized rule parser instance should be quite small.
//
//
// 2.3. Member variables
//
// You can add member variables to the rule parser class using the third
// parameter of the rule parser macro:
//
//   BOOST_SPIRIT_RULE_PARSER( calc,
//     -,
//     -,
//     (3,( ((subrule<0>),expression,()),
//          ((subrule<1>),term,()),
//          ((subrule<2>),factor,() )) ),
//
//     // [...]
//
// adds three subrules to the rule parser.
// Each parameter must have the following type to allow commas to be handled
// safely from within the preprocessing code:
//
//   ((type)),name,(constructor argument(s)))
//
//
// 2.4. The opaque rule parser
//
// Rule parsers usually are templates. Building large grammars pushes the
// compiler really hard (and eventually to its limits) because of the
// metafunction complexity involved.
// If a rule parser without parameters and action placeholders is defined, a
// non-template class is created. Non-templated rule parsers can also be created
// explicitly by using BOOST_SPIRIT_OPAQUE_RULE_PARSER.
// Opaque rule parsers can have parameters and member variables (note: no action
// placeholders are possible). The parameters of an opaque rule parsers are
// strictly typed, e.g:
//
//   BOOST_SPIRIT_OPAQUE_RULE_PARSER(new_identifier,
//     (1,( ((my_symbol_table_t &),symbol_table) ))
//     ,-,
//     (alpha_p >> *alnum_p) [ symbol_table.add ]
//   )
//
// Note it's also possible to have opaque rule parsers accept parameters of
// non-const reference types which is not possible with regular rule parsers.
//
//
// 3. Utilities for by-reference embedding
//
// When using parsers multiple times or recursively it can be helpful to embed
// them by-reference into the final parser expression.
// For this purpose the library provides a wrapper template 'parser_reference'.
// There is also a function template to create a wrapped parser which can deduce
// the parser's type from its argument.
//
// --- --- - - --- - - --- - - - - --- - - - - - - - - - - - - - - - - - - - - -
#if !defined(BOOST_SPIRIT_UTILITY_RULE_PARSER_HPP_INCLUDED)
#   define BOOST_SPIRIT_UTILITY_RULE_PARSER_HPP_INCLUDED
//==============================================================================
// Dependencies
//==============================================================================
#   include <boost/config.hpp>
#   include <boost/detail/workaround.hpp>
#   include <boost/call_traits.hpp>
#   include <boost/typeof/typeof.hpp>
#   include <boost/spirit/home/classic/namespace.hpp>
#   include <boost/spirit/home/classic/core/parser.hpp>
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#   include <boost/preprocessor/cat.hpp>
#   include <boost/preprocessor/seq/seq.hpp>
#   include <boost/preprocessor/seq/for_each_i.hpp>
#   include <boost/preprocessor/tuple/eat.hpp>
#   include <boost/preprocessor/tuple/to_seq.hpp>
#   include <boost/preprocessor/array/size.hpp>
#   include <boost/preprocessor/control/if.hpp>
#   include <boost/preprocessor/control/iif.hpp>
#   include <boost/preprocessor/control/expr_iif.hpp>
#   include <boost/preprocessor/logical/or.hpp>
#   include <boost/preprocessor/logical/nor.hpp>
#   include <boost/preprocessor/logical/not.hpp>
#   include <boost/preprocessor/logical/compl.hpp>
#   include <boost/preprocessor/arithmetic/inc.hpp>
#   include <boost/preprocessor/arithmetic/dec.hpp>
#   include <boost/preprocessor/arithmetic/add.hpp>
#   include <boost/preprocessor/detail/is_unary.hpp>
#   include <boost/preprocessor/detail/is_binary.hpp>
#   include <boost/preprocessor/repetition/repeat.hpp>
#   include <boost/preprocessor/repetition/enum_params.hpp>
#   include <boost/preprocessor/repetition/enum_binary_params.hpp>
#   include <boost/preprocessor/repetition/enum_shifted_params.hpp>
#   include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#   include <boost/preprocessor/punctuation/comma.hpp>
#   include <boost/preprocessor/punctuation/comma_if.hpp>
#   include <boost/preprocessor/facilities/empty.hpp>
#   include <boost/preprocessor/facilities/identity.hpp>
#   include <boost/preprocessor/facilities/intercept.hpp>
//==============================================================================
// Interface
//==============================================================================
// Creates a rule parser. Use at namespace scope.
#   define BOOST_SPIRIT_RULE_PARSER(name,params,actions,members,rule)          \
      BOOST_SPIRIT_RP_IMPL_I(name,params,actions,members,rule)
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Creates a non-templated rule parser. Use at namespace scope.
#   define BOOST_SPIRIT_OPAQUE_RULE_PARSER(name,params,members,rule)           \
      BOOST_SPIRIT_RP_OPAQUE_IMPL_I(name,params,members,rule)
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Defines an action placeholder. Use at namespace scope.
#   define BOOST_SPIRIT_ACTION_PLACEHOLDER(name)                               \
      BOOST_SPIRIT_RP_AP_IMPL(name,::BOOST_SPIRIT_CLASSIC_NS::type_of)
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Utilities to embed parsers by reference.
namespace boost
{
  namespace spirit
  {
    BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    template<class P> class parser_reference;
    template<class P> parser_reference<P> embed_by_reference(parser<P> const &);

    BOOST_SPIRIT_CLASSIC_NAMESPACE_END
  }
}
//==============================================================================
// Implementation
//==============================================================================
#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// RP_REGISTER_TEMPLATE
//
// Boost.Typeof registration from within BOOST_SPIRIT__NAMESPACE
#   define BOOST_SPIRIT_RP_REGISTER_TEMPLATE(name,params)                      \
      BOOST_SPIRIT_RP_EMIT(NS_CLOSE,BOOST_SPIRIT__NAMESPACE,-)                 \
    BOOST_TYPEOF_REGISTER_TEMPLATE(                                            \
        BOOST_SPIRIT_RP_EMIT(NS_QUALIFY,BOOST_SPIRIT__NAMESPACE,-) name,       \
        params)                                                                \
      BOOST_SPIRIT_RP_EMIT(NS_OPEN,BOOST_SPIRIT__NAMESPACE,-)
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// RP_REGISTER_TYPE
//
// Boost.Typeof registration from within BOOST_SPIRIT__NAMESPACE
#   define BOOST_SPIRIT_RP_REGISTER_TYPE(name)                                 \
      BOOST_SPIRIT_RP_EMIT(NS_CLOSE,BOOST_SPIRIT__NAMESPACE,-)                 \
    BOOST_TYPEOF_REGISTER_TYPE(                                                \
        BOOST_SPIRIT_RP_EMIT(NS_QUALIFY,BOOST_SPIRIT__NAMESPACE,-) name )      \
      BOOST_SPIRIT_RP_EMIT(NS_OPEN,BOOST_SPIRIT__NAMESPACE,-)
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// RP_AP_IMPL
//
// The action placeholder definition
#   define BOOST_SPIRIT_RP_AP_IMPL(name,ns)                                    \
      namespace __action_placeholder                                           \
      {                                                                        \
        struct name                                                            \
        {                                                                      \
          template<typename Action>                                            \
          ns :: action_chain< name, ns :: replace, Action>                     \
          operator=(Action const & __a) const                                  \
          { return ns :: action_chain< name, ns :: replace, Action>(__a); }    \
                                                                               \
          template<typename Action>                                            \
          ns :: action_chain< name, ns :: append, Action>                      \
          operator+=(Action const & __a) const                                 \
          { return ns :: action_chain< name, ns :: append, Action> (__a); }    \
        };                                                                     \
      }                                                                        \
      __action_placeholder:: name const name = __action_placeholder:: name ();
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// RP_IMPL_I
//
// Does some precalculation so RP_IMPL_II can look cleaner
#   define BOOST_SPIRIT_RP_IMPL_I(name,pars,acts,mbrs,expr)                    \
      BOOST_SPIRIT_RP_IMPL_II(name, name ## _t ,                               \
                              pars, BOOST_SPIRIT_RP_ARRAY_SIZE(pars),          \
                              acts, BOOST_SPIRIT_RP_ARRAY_SIZE(acts),          \
                              mbrs, BOOST_SPIRIT_RP_ARRAY_SIZE(mbrs), expr)
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// RP_IMPL_II
#   define BOOST_SPIRIT_RP_IMPL_II(name,name_t,pars,np,acts,na,mbrs,nm,x)      \
      BOOST_PP_IIF(BOOST_PP_OR(np,na),BOOST_SPIRIT_RP_IMPL_III,                \
                                      BOOST_SPIRIT_RP_OPAQUE_IMPL_II)          \
                                         (name,name_t,pars,np,acts,na,mbrs,nm,x)
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// RP_IMPL_III
//
// The rule parser definition
#   define BOOST_SPIRIT_RP_IMPL_III(name,name_t,pars,np,acts,na,mbrs,nm,x)     \
                                                                               \
      template< BOOST_SPIRIT_RP_TPL_PARAMS(pars,acts,typename __,1) >          \
      class name_t                                                             \
        : public ::BOOST_SPIRIT_CLASSIC_NS::parser< name_t                     \
                       < BOOST_SPIRIT_RP_TPL_PARAMS(pars,acts,__,0) > >        \
      {                                                                        \
        class __rule                                                           \
        {                                                                      \
          BOOST_SPIRIT_RP_EMIT(PM_STATIC,pars,__T)                             \
          BOOST_SPIRIT_RP_EMIT(AP_STATIC,acts,-)                               \
          BOOST_SPIRIT_RP_EMIT(MV_STATIC,mbrs,BOOST_PP_IDENTITY(typename))     \
        public:                                                                \
          BOOST_TYPEOF_NESTED_TYPEDEF_TPL(__expr,                              \
            ::BOOST_SPIRIT_CLASSIC_NS::type_of::depend_on_type<__Dummy>(x) )   \
        };                                                                     \
                                                                               \
      public:                                                                  \
                                                                               \
        typedef name_t self_t;                                                 \
        typedef typename __rule::__expr::type::parser_category_t               \
                                                           parser_category_t;  \
                                                                               \
        BOOST_PP_EXPR_IIF(BOOST_PP_NOR(np,na),typedef self_t const & embed_t;) \
                                                                               \
      protected:                                                               \
                                                                               \
        BOOST_SPIRIT_RP_EMIT(MV_NONSTATIC,mbrs,BOOST_PP_IDENTITY(typename))    \
        BOOST_SPIRIT_RP_IF(na,SPIRIT_RP_AP_EXTRA_MBRS,2)(np,na)                \
                                                                               \
        typename __rule::__expr::type::embed_t __parser;                       \
                                                                               \
      public:                                                                  \
                                                                               \
        explicit name_t ( BOOST_SPIRIT_RP_CTOR(PARAMS,pars,np,acts) )          \
          : BOOST_SPIRIT_RP_EMIT(MV_CTOR_INIT_LIST,mbrs,-)                     \
          BOOST_PP_COMMA_IF(nm)                                                \
          BOOST_SPIRIT_RP_IF(na,SPIRIT_RP_CTOR_COMMA,4)(INIT_LIST,pars,np,acts)\
            __parser(x)                                                        \
        { }                                                                    \
                                                                               \
        name_t( name_t const & that)                                           \
          : BOOST_SPIRIT_RP_EMIT(MV_CTOR_COPY_INIT_LIST,mbrs,that)             \
          BOOST_PP_COMMA_IF(nm)                                                \
          BOOST_SPIRIT_RP_IF(na,SPIRIT_RP_CTOR_COMMA,4)                        \
                                                 (COPY_INIT_LIST,pars,np,acts) \
            __parser(that.__parser)                                            \
        { }                                                                    \
                                                                               \
        template<typename Scanner> struct result                               \
        {                                                                      \
          typedef typename ::BOOST_SPIRIT_CLASSIC_NS::parser_result<                     \
                           typename __rule::__expr::type, Scanner>::type type; \
        };                                                                     \
                                                                               \
        template<typename Scanner>                                             \
        typename ::BOOST_SPIRIT_CLASSIC_NS::parser_result<self_t, Scanner>::type         \
        parse(Scanner const & s) const { return __parser.parse(s); }           \
                                                                               \
        BOOST_SPIRIT_RP_IF(na,SPIRIT_RP_AP_HANDLER,5)                          \
                                  (name_t,np,acts,na,::BOOST_SPIRIT_CLASSIC_NS::type_of) \
      };                                                                       \
                                                                               \
      BOOST_PP_IF(np,BOOST_SPIRIT_RP_GEN_FUNC,BOOST_SPIRIT_RP_GLOB_VAR)        \
                                                           (name,name_t,np,na) \
      BOOST_SPIRIT_RP_REGISTER_TEMPLATE                                        \
        (name_t,BOOST_PP_INC(BOOST_PP_ADD(np,na)))
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// RP_OPAQUE_IMPL_I
//
#   define BOOST_SPIRIT_RP_OPAQUE_IMPL_I(name,pars,mbrs,expr)                  \
      BOOST_SPIRIT_RP_OPAQUE_IMPL_II(name, name ## _t,                         \
                                     pars,BOOST_SPIRIT_RP_ARRAY_SIZE(pars),-,-,\
                                     mbrs,BOOST_SPIRIT_RP_ARRAY_SIZE(mbrs),expr)
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// RP_OPAQUE_IMPL_II
//
#   define BOOST_SPIRIT_RP_OPAQUE_IMPL_II(name,name_t,pars,np,_1,_2,mbrs,nm,x) \
      class name_t;                                                            \
                                                                               \
      BOOST_SPIRIT_RP_REGISTER_TYPE(name_t)                                    \
                                                                               \
      class name_t                                                             \
        : public ::BOOST_SPIRIT_CLASSIC_NS::parser< name_t >                             \
      {                                                                        \
        class __rule                                                           \
        {                                                                      \
          BOOST_SPIRIT_RP_EMIT(PM_OPAQUE_STATIC,pars,-)                        \
          BOOST_SPIRIT_RP_EMIT(MV_STATIC,mbrs,BOOST_PP_EMPTY)                  \
        public:                                                                \
          BOOST_TYPEOF_NESTED_TYPEDEF(__expr,x)                                \
        };                                                                     \
                                                                               \
      public:                                                                  \
                                                                               \
        typedef name_t self_t;                                                 \
        typedef __rule::__expr::type::parser_category_t parser_category_t;     \
        BOOST_PP_EXPR_IIF(BOOST_PP_NOT(np),typedef self_t const & embed_t;)    \
                                                                               \
      protected:                                                               \
                                                                               \
        BOOST_SPIRIT_RP_EMIT(MV_NONSTATIC,mbrs,BOOST_PP_EMPTY)                 \
                                                                               \
        __rule::__expr::type::embed_t __parser;                                \
                                                                               \
      public:                                                                  \
                                                                               \
        explicit name_t (BOOST_SPIRIT_RP_EMIT(PM_OPAQUE_CTOR_PARAMS,pars,-))   \
          : BOOST_SPIRIT_RP_EMIT(MV_CTOR_INIT_LIST,mbrs,-)                     \
            BOOST_PP_COMMA_IF(nm) __parser(x)                                  \
        { }                                                                    \
                                                                               \
        name_t(name_t const & that)                                            \
          : BOOST_SPIRIT_RP_EMIT(MV_CTOR_COPY_INIT_LIST,mbrs,that)             \
            BOOST_PP_COMMA_IF(nm) __parser(that.__parser)                      \
        { }                                                                    \
                                                                               \
        template<typename Scanner> struct result                               \
        {                                                                      \
          typedef typename ::BOOST_SPIRIT_CLASSIC_NS::parser_result<                     \
                                   __rule::__expr::type, Scanner>::type type;  \
        };                                                                     \
                                                                               \
        template<typename Scanner>                                             \
        typename ::BOOST_SPIRIT_CLASSIC_NS::parser_result<self_t, Scanner>::type         \
        parse(Scanner const & s) const { return __parser.parse(s); }           \
      };                                                                       \
                                                                               \
      BOOST_PP_IF(np,BOOST_SPIRIT_RP_GEN_OPAQUE,BOOST_SPIRIT_RP_GLOB_OPAQUE)   \
                                                         (name,name_t,np,pars)
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// RP_AP_HANDLER
//
// Part of the rule parser definition for handling action placeholders
#   define BOOST_SPIRIT_RP_AP_HANDLER(name_t,np,acts,na,ns)                    \
      private:                                                                 \
        template<typename A> struct __rebound_1st                              \
        {                                                                      \
          typedef name_t < void BOOST_PP_ENUM_TRAILING_PARAMS(np,__T) ,        \
            typename ns ::action_concatenator<__A0,A>::type                    \
            BOOST_PP_COMMA_IF(BOOST_PP_DEC(na))                                \
            BOOST_PP_ENUM_SHIFTED_PARAMS(na,__A)                               \
          > type;                                                              \
        };                                                                     \
                                                                               \
        template<typename X> struct __rebound                                  \
        {                                                                      \
          typedef name_t <                                                     \
            void BOOST_PP_ENUM_TRAILING_PARAMS(np,__T)                         \
            BOOST_SPIRIT_RP_EMIT(AP_REBOUND_TPL_ARGS,acts,X)                   \
          > type;                                                              \
        };                                                                     \
      public:                                                                  \
        template<typename A>                                                   \
        typename __rebound_1st<A>::type const operator[](A const & a) const    \
        {                                                                      \
          return typename __rebound_1st<A>::type (                             \
            BOOST_PP_ENUM_PARAMS(np,__p) BOOST_PP_COMMA_IF(np)                 \
            ns ::concatenate_actions(__a0,a)                                   \
            BOOST_PP_COMMA_IF(BOOST_PP_DEC(na))                                \
            BOOST_PP_ENUM_SHIFTED_PARAMS(na,__a) );                            \
        }                                                                      \
        template<class PH, ns ::action_chain_mode M, typename A>               \
        typename __rebound< ns ::action_chain<PH,M,A> >::type const            \
        operator[]( ns ::action_chain<PH,M,A> const & x) const                 \
        {                                                                      \
          return typename __rebound< ns ::action_chain<PH,M,A> >::type (       \
            BOOST_PP_ENUM_PARAMS(np,__p) BOOST_PP_COMMA_IF(np)                 \
            BOOST_SPIRIT_RP_EMIT(AP_REBOUND_ARGS,acts,x) );                    \
        }                                                                      \
        template<class Head, class Tail>                                       \
        typename __rebound< ns ::action_chains<Head,Tail> >::type const        \
        operator[]( ns ::action_chains<Head,Tail> const & x) const             \
        {                                                                      \
          return typename __rebound< ns ::action_chains<Head,Tail> >::type (   \
            BOOST_PP_ENUM_PARAMS(np,__p) BOOST_PP_COMMA_IF(np)                 \
            BOOST_SPIRIT_RP_EMIT(AP_REBOUND_ARGS,acts,x) );                    \
        }
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// RP_AP_EXTRA_MBRS
//
// Extra members we need for rebinding if there are action placeholders
#   define BOOST_SPIRIT_RP_AP_EXTRA_MBRS(np,na)                                \
      private:                                                                 \
        BOOST_PP_REPEAT(np,BOOST_SPIRIT_RP_PM_MBRS,-)                          \
        BOOST_PP_REPEAT(na,BOOST_SPIRIT_RP_AP_MBRS,-)
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// RP_PM_MBRS
//
// Member variables to remember parameters if there are action placeholder
#   define BOOST_SPIRIT_RP_PM_MBRS(z,i,d) __T ## i __p ## i ;
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// RP_AP_MBRS
//
// Member variables to remember action placeholder substitutes
#   define BOOST_SPIRIT_RP_AP_MBRS(z,i,d) __A ## i __a ## i ;
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// RP_CTOR
//
// Expands to a fragment of a constructor (parameters or init-list)
#   define BOOST_SPIRIT_RP_CTOR(what,pars,np,acts)                             \
      BOOST_SPIRIT_RP_EMIT(PM_CTOR_ ## what,pars,__T)                          \
      BOOST_SPIRIT_RP_EMIT(AP_CTOR_ ## what,acts,np)
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// RP_CTOR_COMMA
//
// RP_CTOR with a trailing comma
#   define BOOST_SPIRIT_RP_CTOR_COMMA(what,pars,np,acts)                       \
      BOOST_SPIRIT_RP_CTOR(what,pars,np,acts) ,
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// RP_TPL_PARAMS
//
// Expands to the template parameters or arguments of the rule parser template
#   define BOOST_SPIRIT_RP_TPL_PARAMS(pars,acts,prefix,defaults)               \
      prefix ## Dummy                                                          \
      BOOST_SPIRIT_RP_EMIT(PM_TEMPLATE_PARAMS,pars,prefix ## T)                \
      BOOST_SPIRIT_RP_EMIT(AP_TEMPLATE_PARAMS,acts,(prefix ## A,defaults))
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// RP_GEN_FUNC
//
// Generator function
#   define BOOST_SPIRIT_RP_GEN_FUNC(name,name_t,np,na)                         \
      template< BOOST_PP_ENUM_PARAMS(np,typename T) >                          \
      inline name_t < void BOOST_PP_ENUM_TRAILING_PARAMS(np,T) >               \
      name( BOOST_PP_ENUM_BINARY_PARAMS(np,T, const & p) )                     \
      { return name_t < void BOOST_PP_ENUM_TRAILING_PARAMS(np,T) >             \
                 (BOOST_PP_ENUM_PARAMS(np,p) BOOST_PP_ENUM_TRAILING_PARAMS(na, \
                ::BOOST_SPIRIT_CLASSIC_NS::type_of::nop_functor() BOOST_PP_INTERCEPT) ); \
      }
// RP_GEN_OPAQUE
//
// non-templated version for opaque rule parsers.
#   define BOOST_SPIRIT_RP_GEN_OPAQUE(name,name_t,np,pars)                     \
      inline name_t name( BOOST_SPIRIT_RP_EMIT(PM_OPAQUE_GEN_PARAMS,pars,p))   \
      { return name_t (BOOST_PP_ENUM_PARAMS(np,p)); }
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// RP_GLOB_VAR
//
// Global variable -- used instead of the generator function if there are no
// parameters
#   define BOOST_SPIRIT_RP_GLOB_VAR(name,name_t,np,na)                         \
      static name_t <void> const name = name_t <void>(BOOST_PP_ENUM_PARAMS(na, \
                ::BOOST_SPIRIT_CLASSIC_NS::type_of::nop_functor() BOOST_PP_INTERCEPT) );

// RP_GLOB_OPAQUE
//
// non-templated version for opaque rule parsers.
#   define BOOST_SPIRIT_RP_GLOB_OPAQUE(name,name_t,np,pars)                    \
      static name_t const name = name_t () ;
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// PP_EMIT operations (fragment emittion based on array input)

// - - Namespace handling

// NS_OPEN
#   define BOOST_SPIRIT_RP__NS_OPEN(r,data,i,elem)                             \
      namespace BOOST_SPIRIT_RP_OPTIONAL(elem) {

// NS_QUALIFY
#   define BOOST_SPIRIT_RP__NS_QUALIFY(r,data,i,elem)                          \
      BOOST_SPIRIT_RP_OPTIONAL(elem ::)

// NS_CLOSE
#   define BOOST_SPIRIT_RP__NS_CLOSE(r,data,i,elem) }

// - - Parameter handling

// PM_STATIC
#   define BOOST_SPIRIT_RP__PM_STATIC(r,data,i,elem)                           \
      static typename ::boost::call_traits< data ## i >::reference elem ;

// PM_CTOR_PARAMS
#   define BOOST_SPIRIT_RP__PM_CTOR_PARAMS(r,data,i,elem)                      \
      BOOST_PP_COMMA_IF(i)                                                     \
      typename ::boost::call_traits< data ## i >::param_type elem

// PM_CTOR_ARGS
#   define BOOST_SPIRIT_RP__PM_CTOR_ARGS(r,data,i,elem)                        \
      BOOST_PP_COMMA_IF(i) elem

// PM_CTOR_INIT_LIST
#   define BOOST_SPIRIT_RP__PM_CTOR_INIT_LIST(r,data,i,elem)                   \
      BOOST_PP_COMMA_IF(i) __p ## i ( elem )

// PM_CTOR_COPY_INIT_LIST
#   define BOOST_SPIRIT_RP__PM_CTOR_COPY_INIT_LIST(r,data,i,elem)              \
      BOOST_PP_COMMA_IF(i) __p ## i ( that. __p ## i )


// PM_TEMPLATE_PARAMS
#   define BOOST_SPIRIT_RP__PM_TEMPLATE_PARAMS(r,data,i,elem) , data ## i

// - strictly typed parameters of the opaque rule_parser

// PM_OPAQUE_STATIC
#   define BOOST_SPIRIT_RP__PM_OPAQUE_STATIC(r,data,i,elem)                    \
      static ::boost::call_traits<                                             \
          BOOST_SPIRIT_RP_TYPE(BOOST_PP_TUPLE_ELEM(2,0,elem))                  \
        >::reference BOOST_PP_TUPLE_ELEM(2,1,elem) ;

// PM_OPAQUE_CTOR_PARAMS
#   define BOOST_SPIRIT_RP__PM_OPAQUE_CTOR_PARAMS(r,data,i,elem)               \
      BOOST_PP_COMMA_IF(i) ::boost::call_traits<                               \
          BOOST_SPIRIT_RP_TYPE(BOOST_PP_TUPLE_ELEM(2,0,elem))                  \
        >::param_type BOOST_PP_TUPLE_ELEM(2,1,elem)

// PM_OPAQUE_GEN_PARAMS
#   define BOOST_SPIRIT_RP__PM_OPAQUE_GEN_PARAMS(r,data,i,elem)                \
      BOOST_PP_COMMA_IF(i) ::boost::call_traits<                               \
          BOOST_SPIRIT_RP_TYPE(BOOST_PP_TUPLE_ELEM(2,0,elem))                  \
        >::param_type data ## i

// - - Member variable handling

// MV_NONSTATIC
#   define BOOST_SPIRIT_RP__MV_NONSTATIC(r,data,i,elem)                        \
      data() BOOST_SPIRIT_RP_TYPE(BOOST_PP_TUPLE_ELEM(3,0,elem))               \
        BOOST_PP_TUPLE_ELEM(3,1,elem) ;

// MV_STATIC
#   define BOOST_SPIRIT_RP__MV_STATIC(r,data,i,elem)                           \
      static data() ::boost::call_traits<                                      \
            data() BOOST_SPIRIT_RP_TYPE(BOOST_PP_TUPLE_ELEM(3,0,elem))         \
        >::reference BOOST_PP_TUPLE_ELEM(3,1,elem) ;

// MV_CTOR_INIT_LIST
#   define BOOST_SPIRIT_RP__MV_CTOR_INIT_LIST(r,data,i,elem)                   \
      BOOST_PP_COMMA_IF(i)                                                     \
      BOOST_PP_TUPLE_ELEM(3,1,elem) BOOST_PP_TUPLE_ELEM(3,2,elem)

// MV_CTOR_COPY_INIT_LIST
#   define BOOST_SPIRIT_RP__MV_CTOR_COPY_INIT_LIST(r,data,i,elem)              \
      BOOST_PP_COMMA_IF(i)                                                     \
      BOOST_PP_TUPLE_ELEM(3,1,elem) (data . BOOST_PP_TUPLE_ELEM(3,1,elem))

// - - Action placeholder handling

// AP_STATIC
#   define BOOST_SPIRIT_RP__AP_STATIC(r,data,i,elem) static __A ## i & elem ;

// AP_CTOR_PARAMS
#   define BOOST_SPIRIT_RP__AP_CTOR_PARAMS(r,data,i,elem)                      \
      BOOST_SPIRIT_RP_COMMA_IF_OR(data,i)                                      \
      typename ::boost::call_traits< __A ## i >::param_type elem

// AP_CTOR_ARGS
#   define BOOST_SPIRIT_RP__AP_CTOR_ARGS(r,data,i,elem)                        \
      BOOST_SPIRIT_RP_COMMA_IF_OR(data,i) elem

// AP_CTOR_INIT_LIST
#   define BOOST_SPIRIT_RP__AP_CTOR_INIT_LIST(r,data,i,elem)                   \
      BOOST_SPIRIT_RP_COMMA_IF_OR(data,i) __a ## i ( elem )

// AP_CTOR_COPY_INIT_LIST
#   define BOOST_SPIRIT_RP__AP_CTOR_COPY_INIT_LIST(r,data,i,elem)              \
      BOOST_SPIRIT_RP_COMMA_IF_OR(data,i) __a ## i ( that. __a ## i )

// AP_TEMPLATE_PARAMS
#   define BOOST_SPIRIT_RP__AP_TEMPLATE_PARAMS(r,data,i,elem)                  \
      , BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(2,0,data),i)                          \
      BOOST_PP_EXPR_IIF(BOOST_PP_TUPLE_ELEM(2,1,data),                         \
          = ::BOOST_SPIRIT_CLASSIC_NS::type_of::nop_functor)

// AP_REBOUND_ARGS
#   define BOOST_SPIRIT_RP__AP_REBOUND_ARGS(r,data,i,elem)                     \
      BOOST_PP_COMMA_IF(i)                                                     \
      ::BOOST_SPIRIT_CLASSIC_NS::type_of::get_placeholdee< __action_placeholder:: elem > \
                                                           ( __a ## i , data )

// AP_REBOUND_TPL_ARGS
#   define BOOST_SPIRIT_RP__AP_REBOUND_TPL_ARGS(r,data,i,elem)                 \
      , typename ::BOOST_SPIRIT_CLASSIC_NS::type_of::placeholdee<                        \
                  __action_placeholder:: elem , __A ## i, data >::type

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// PP_EMIT
//
// Performs one of the operations in the above section on an optional array.
//
#   define BOOST_SPIRIT_RP_EMIT(op, array, data)                               \
      BOOST_SPIRIT_RP_ARRAY_FOR_EACH_I(BOOST_SPIRIT_RP__ ## op,data,array)
// --- --- - - --- - - --- - - - - --- - - - - - - - - - - - - - - - - - - - - -
// RP_ARRAY_FOR_EACH_I
//
// Iterates an optional array. That is you can pass e.g.'-' or 'none' to denote
// emptiness.
#   define BOOST_SPIRIT_RP_ARRAY_FOR_EACH_I(macro,data,optional_array)         \
      BOOST_PP_IIF(BOOST_PP_IS_BINARY(optional_array),                         \
                   BOOST_SPIRIT_RP_ARRAY_FOR_EACH_I_IMPL,                      \
                   BOOST_PP_TUPLE_EAT(3))(macro,data,optional_array)

// RP_ARRAY_FOR_EACH_I_IMPL
#   define BOOST_SPIRIT_RP_ARRAY_FOR_EACH_I_IMPL(macro,data,array)             \
      BOOST_SPIRIT_RP_IF(BOOST_PP_ARRAY_SIZE(array),PP_SEQ_FOR_EACH_I,3)       \
        (macro,data, BOOST_SPIRIT_RP_IF(BOOST_PP_ARRAY_SIZE(array),            \
                                        PP_TUPLE_TO_SEQ,2) array)
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// RP_ARRAY_SIZE
//
// Expands to the size of an "optional array".
//
// Examples:
//
//   BOOST_SPIRIT_RP_ARRAY_SIZE( (2,(a,b)) ) // 2
//   BOOST_SPIRIT_RP_ARRAY_SIZE( (0,()) )    // 0
//   BOOST_SPIRIT_RP_ARRAY_SIZE( none )      // 0
//   BOOST_SPIRIT_RP_ARRAY_SIZE( - )         // 0
//
#   define BOOST_SPIRIT_RP_ARRAY_SIZE(optional_array)                          \
      BOOST_PP_IIF(BOOST_PP_IS_BINARY(optional_array),                         \
                   BOOST_PP_ARRAY_SIZE, 0 BOOST_PP_TUPLE_EAT(1))(optional_array)
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// RP_OPTIONAL
//
// Expands to nothing if the argument is parenthesized.
//
// Examples:
//
//   BOOST_SPIRIT_RP_OPTIONAL( foobar ) // foobar
//   BOOST_SPIRIT_RP_OPTIONAL( (none) ) // evaluates to nothing
//
#   define BOOST_SPIRIT_RP_OPTIONAL(elem)                                      \
      BOOST_PP_EXPR_IIF(BOOST_PP_COMPL(BOOST_PP_IS_UNARY(elem)),elem)
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// RP_COMMA_IF_OR
//
// Expands to nothing if both arguments are zero, otherwise expands to a comma.
//
#   define BOOST_SPIRIT_RP_COMMA_IF_OR(a,b)                                    \
      BOOST_PP_IIF(BOOST_PP_OR(a,b),BOOST_PP_COMMA,BOOST_PP_EMPTY)()
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// RP_IF
//
//   BOOST_SPIRIT_RP_IF(cond,name,arity)
//
// is equivalent to:
//
//   BOOST_PP_IF(cond,BOOST_name,BOOST_PP_TUPLE_EAT(arity))
//
#   define BOOST_SPIRIT_RP_IF(cond,name,arity) \
      BOOST_PP_IF(cond,BOOST_ ## name,BOOST_PP_TUPLE_EAT(arity))

//------------------------------------------------------------------------------
// Wrapper and gernator function to embed a parser by reference
//------------------------------------------------------------------------------

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

  // Wrapper to embed a parser by reference

  template<class P> class parser_reference
    : public parser< parser_reference<P> >
  {
    P const & ref_that;
  public:
    parser_reference(P & that)
    // we allow implicit conversion but forbid temporaries.
      : ref_that(that)
    { }

    typedef parser_reference<P>           self_t;
    typedef self_t const &                embed_t;
    typedef typename P::parser_category_t parser_category_t;

    template<typename ScannerT> struct result
    { typedef typename P::BOOST_NESTED_TEMPLATE result<ScannerT>::type type; };

    template<typename ScannerT>
    typename result<ScannerT>::type
    parse(ScannerT const & scan) const
    { return this->ref_that.parse(scan); }
  };

  template<class P> parser_reference<P>
  embed_by_reference(::BOOST_SPIRIT_CLASSIC_NS::parser<P> & p)
  { return p; }

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

} } // namespace ::BOOST_SPIRIT_CLASSIC_NS

BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::parser_reference, 1)

//------------------------------------------------------------------------------
// Expression templates for action placeholders.
//------------------------------------------------------------------------------

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

namespace type_of {

  // No-operation functor

  struct nop_functor
  {
    template<typename T>
    bool operator()(T const &) const
    { return false; }
    template<typename T, typename U>
    bool operator()(T const &, U const &) const
    { return false; }

    typedef bool result_type;
  };

  // Composite action

  template<typename Action1, typename Action2>
  class composite_action
  {
    Action1 fnc_a1;
    Action2 fnc_a2;
  public:
    composite_action(Action1 const & a1, Action2 const & a2)
      : fnc_a1(a1), fnc_a2(a2)
    { }

    template<typename T>
    void operator()(T const & inp) const
    { fnc_a1(inp); fnc_a2(inp); }

    template<typename T, typename U>
    void operator()(T const & inp1, U const inp2) const
    { fnc_a1(inp1, inp2); fnc_a2(inp1, inp2); }
  };

  // Action concatenation (and optimize away nop_functorS)

  template<typename Action1, typename Action2>
  struct action_concatenator
  {
    typedef composite_action<Action1,Action2> type;

    static type concatenate(Action1 const & a1, Action2 const & a2)
    { return composite_action<Action1,Action2>(a1,a2); }
  };
  template<typename Action> struct action_concatenator<nop_functor, Action>
  {
    typedef Action type;

    static type concatenate(nop_functor const &, Action const & a)
    { return a; }
  };
  template<typename Action> struct action_concatenator<Action, nop_functor>
  {
    typedef Action type;

    static type concatenate(Action const & a, nop_functor const &)
    { return a; }
  };
  template<> struct action_concatenator<nop_functor, nop_functor>
  {
    typedef nop_functor type;

    static type concatenate(nop_functor const &, nop_functor const &)
    { return nop_functor(); }
  };

  template<typename Action1, typename Action2>
  typename action_concatenator<Action1,Action2>::type
  concatenate_actions(Action1 const & a1, Action2 const & a2)
  {
    return action_concatenator<Action1,Action2>::concatenate(a1,a2);
  }

  // Action chains

  enum action_chain_mode { replace, append };

  template<class Placeholder, action_chain_mode Mode, typename Action>
  class action_chain
  {
    Action fnc_action;
  public:
    action_chain(Action const & a)
      : fnc_action(a)
    { }

    typedef Action action_type;

    Action const & action() const { return fnc_action; }
  };

  // This operator adds actions to an action chain definition
  template<class PH, action_chain_mode M, typename A1, typename A2>
  action_chain<PH, M, typename action_concatenator<A1,A2>::type>
  operator, (action_chain<PH,M,A1> const & chain, A2 const & a)
  {
    return action_chain<PH,M,typename action_concatenator<A1,A2>::type>
        ( concatenate_actions(chain.action(), a) );
  }

  // Expression template for multiple action chain assignments
  template<class ChainOrChains, class LastChain>
  class action_chains
  {
    ChainOrChains obj_head;
    LastChain     obj_tail;
  public:
    action_chains(ChainOrChains const & head, LastChain const & tail)
      : obj_head(head), obj_tail(tail)
    { }

    typedef ChainOrChains head_type;
    typedef LastChain     tail_type;

    head_type const & head() const { return obj_head; }
    tail_type const & tail() const { return obj_tail; }
  };

  // Action chain concatenation
  template<class Head, class Tail>
  action_chains<Head,Tail> make_chain(Head const & h, Tail const & t)
  { return action_chains<Head,Tail>(h,t); }

  template<class PH1, action_chain_mode M1, typename A1,
           class PH2, action_chain_mode M2, typename A2>
  action_chains< action_chain<PH1,M1,A1>, action_chain<PH2,M2,A2> >
  operator, (action_chain<PH1,M1,A1> const & h,
             action_chain<PH2,M2,A2> const & t)
  { return make_chain(h,t); }

  template<class Head, class Tail,class PH, action_chain_mode M, typename A>
  action_chains< action_chains<Head,Tail>, action_chain<PH,M,A> >
  operator, (action_chains<Head,Tail> const & h, action_chain<PH,M,A> const & t)
  { return make_chain(h,t); }


  // Extract the (maybe composite) action associated with an action
  // placeholders from the chains with a fold algorithm.
  template<class Placeholder, typename StartAction, class NewChainOrChains>
  struct placeholdee
  {
    typedef StartAction type;

    static type get(StartAction const & a, NewChainOrChains const &)
    { return a; }
  };

  template<class Placeholder, // <-- non-deduced
           typename StartAction, class NewChainOrChains>
  typename placeholdee<Placeholder,StartAction,NewChainOrChains>::type
  get_placeholdee(StartAction const & a, NewChainOrChains const & c)
  { return placeholdee<Placeholder,StartAction,NewChainOrChains>::get(a,c); }

  template<class Placeholder, typename StartAction, class Head, class Tail>
  struct placeholdee
            < Placeholder, StartAction, action_chains<Head,Tail> >
  {
    typedef typename placeholdee<Placeholder,
      typename placeholdee<Placeholder,StartAction,Head>::type, Tail >::type
    type;

    static type get(StartAction const & a, action_chains<Head,Tail> const & c)
    {
      return get_placeholdee<Placeholder>(
        get_placeholdee<Placeholder>(a,c.head()), c.tail() );
    }
  };

  template<class Placeholder, typename StartAction, typename A>
  struct placeholdee
            < Placeholder, StartAction, action_chain<Placeholder,replace,A> >
  {
    typedef A type;

    static type get(StartAction const &,
                    action_chain<Placeholder,replace,A> const & c)
    { return c.action(); }
  };

  template<class Placeholder, typename StartAction, typename A>
  struct placeholdee
            < Placeholder, StartAction, action_chain<Placeholder,append,A> >
  {
    typedef typename action_concatenator<StartAction,A>::type type;

    static type get(StartAction const & a,
                    action_chain<Placeholder,append,A> const & c)
    { return concatenate_actions(a,c.action()); }
  };

}

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

} } // namespace ::BOOST_SPIRIT_CLASSIC_NS::type_of

BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::type_of::nop_functor)
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::type_of::composite_action,2)

//------------------------------------------------------------------------------
// Misc.utilities
//------------------------------------------------------------------------------

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

namespace type_of {

  // Utility function to create a dependency to a template argument.

  template<typename T, typename X>
  X const & depend_on_type(X const & x)
  { return x; }

  // Utility to allow use parenthesized type expressions with commas inside
  // as a type within macros. Thanks to Dave Abrahams for telling me this nice
  // trick.

  #define BOOST_SPIRIT_RP_TYPE(x) \
    ::BOOST_SPIRIT_CLASSIC_NS::type_of::remove_special_fptr \
      < ::BOOST_SPIRIT_CLASSIC_NS::type_of::special_result & (*) x >::type

  struct special_result;

  template<typename T> struct remove_special_fptr { };
  template<typename T> struct remove_special_fptr< special_result & (*)(T) >
  { typedef T type; };

}

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

} } // namespace ::BOOST_SPIRIT_CLASSIC_NS::type_of

//------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------


/* rule_parser.hpp
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
*/