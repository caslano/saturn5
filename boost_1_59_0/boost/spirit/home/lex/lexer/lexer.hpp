//  Copyright (c) 2001-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_LEX_LEXER_MAR_13_2007_0145PM)
#define BOOST_SPIRIT_LEX_LEXER_MAR_13_2007_0145PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/qi/skip_over.hpp>
#include <boost/spirit/home/qi/parser.hpp>
#include <boost/spirit/home/qi/detail/assign_to.hpp>
#include <boost/spirit/home/lex/reference.hpp>
#include <boost/spirit/home/lex/meta_compiler.hpp>
#include <boost/spirit/home/lex/lexer_type.hpp>
#include <boost/spirit/home/lex/lexer/token_def.hpp>
#include <boost/assert.hpp>
#include <boost/noncopyable.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/proto/extends.hpp>
#include <boost/proto/traits.hpp>
#include <boost/range/iterator_range_core.hpp>
#include <iterator> // for std::iterator_traits
#include <string>

namespace boost { namespace spirit { namespace lex
{
    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        ///////////////////////////////////////////////////////////////////////
        template <typename LexerDef>
        struct lexer_def_
          : proto::extends<
                typename proto::terminal<
                   lex::reference<lexer_def_<LexerDef> const> 
                >::type
              , lexer_def_<LexerDef> >
          , qi::parser<lexer_def_<LexerDef> >
          , lex::lexer_type<lexer_def_<LexerDef> >
        {
        private:
            // avoid warnings about using 'this' in constructor
            lexer_def_& this_() { return *this; }

            typedef typename LexerDef::char_type char_type;
            typedef typename LexerDef::string_type string_type;
            typedef typename LexerDef::id_type id_type;

            typedef lex::reference<lexer_def_ const> reference_;
            typedef typename proto::terminal<reference_>::type terminal_type;
            typedef proto::extends<terminal_type, lexer_def_> proto_base_type;

            reference_ alias() const
            {
                return reference_(*this);
            }

        public:
            // Qi interface: metafunction calculating parser attribute type
            template <typename Context, typename Iterator>
            struct attribute
            {
                //  the return value of a token set contains the matched token 
                //  id, and the corresponding pair of iterators
                typedef typename Iterator::base_iterator_type iterator_type;
                typedef 
                    fusion::vector2<id_type, iterator_range<iterator_type> > 
                type;
            };

            // Qi interface: parse functionality
            template <typename Iterator, typename Context
              , typename Skipper, typename Attribute>
            bool parse(Iterator& first, Iterator const& last
              , Context& /*context*/, Skipper const& skipper
              , Attribute& attr) const
            {
                qi::skip_over(first, last, skipper);   // always do a pre-skip

                if (first != last) {
                    typedef typename 
                        std::iterator_traits<Iterator>::value_type 
                    token_type;

                    token_type const& t = *first;
                    if (token_is_valid(t) && t.state() == first.get_state()) {
                    // any of the token definitions matched
                        spirit::traits::assign_to(t, attr);
                        ++first;
                        return true;
                    }
                }
                return false;
            }

            // Qi interface: 'what' functionality
            template <typename Context>
            info what(Context& /*context*/) const
            {
                return info("lexer");
            }

        private:
            // allow to use the lexer.self.add("regex1", id1)("regex2", id2);
            // syntax
            struct adder
            {
                adder(lexer_def_& def_) 
                  : def(def_) {}

                // Add a token definition based on a single character as given
                // by the first parameter, the second parameter allows to 
                // specify the token id to use for the new token. If no token
                // id is given the character code is used.
                adder const& operator()(char_type c
                  , id_type token_id = id_type()) const
                {
                    if (id_type() == token_id)
                        token_id = static_cast<id_type>(c);
                    def.def.add_token (def.state.c_str(), c, token_id
                        , def.targetstate.empty() ? 0 : def.targetstate.c_str());
                    return *this;
                }

                // Add a token definition based on a character sequence as 
                // given by the first parameter, the second parameter allows to 
                // specify the token id to use for the new token. If no token
                // id is given this function will generate a unique id to be 
                // used as the token's id.
                adder const& operator()(string_type const& s
                  , id_type token_id = id_type()) const
                {
                    if (id_type() == token_id)
                        token_id = def.def.get_next_id();
                    def.def.add_token (def.state.c_str(), s, token_id
                        , def.targetstate.empty() ? 0 : def.targetstate.c_str());
                    return *this;
                }

                template <typename Attribute>
                adder const& operator()(
                    token_def<Attribute, char_type, id_type>& tokdef
                  , id_type token_id = id_type()) const
                {
                    // make sure we have a token id
                    if (id_type() == token_id) {
                        if (id_type() == tokdef.id()) {
                            token_id = def.def.get_next_id();
                            tokdef.id(token_id);
                        }
                        else {
                            token_id = tokdef.id();
                        }
                    }
                    else { 
                    // the following assertion makes sure that the token_def
                    // instance has not been assigned a different id earlier
                        BOOST_ASSERT(id_type() == tokdef.id() 
                                  || token_id == tokdef.id());
                        tokdef.id(token_id);
                    }

                    def.define(tokdef);
                    return *this;
                }

//                 template <typename F>
//                 adder const& operator()(char_type c, id_type token_id, F act) const
//                 {
//                     if (id_type() == token_id)
//                         token_id = def.def.get_next_id();
//                     std::size_t unique_id = 
//                         def.def.add_token (def.state.c_str(), s, token_id);
//                     def.def.add_action(unique_id, def.state.c_str(), act);
//                     return *this;
//                 }

                lexer_def_& def;

                // silence MSVC warning C4512: assignment operator could not be generated
                BOOST_DELETED_FUNCTION(adder& operator= (adder const&))
            };
            friend struct adder;

            // allow to use lexer.self.add_pattern("pattern1", "regex1")(...);
            // syntax
            struct pattern_adder
            {
                pattern_adder(lexer_def_& def_) 
                  : def(def_) {}

                pattern_adder const& operator()(string_type const& p
                  , string_type const& s) const
                {
                    def.def.add_pattern (def.state.c_str(), p, s);
                    return *this;
                }

                lexer_def_& def;

                // silence MSVC warning C4512: assignment operator could not be generated
                BOOST_DELETED_FUNCTION(pattern_adder& operator= (pattern_adder const&))
            };
            friend struct pattern_adder;

        private:
            // Helper function to invoke the necessary 2 step compilation
            // process on token definition expressions
            template <typename TokenExpr>
            void compile2pass(TokenExpr const& expr) 
            {
                expr.collect(def, state, targetstate);
                expr.add_actions(def);
            }

        public:
            ///////////////////////////////////////////////////////////////////
            template <typename Expr>
            void define(Expr const& expr)
            {
                compile2pass(compile<lex::domain>(expr));
            }

            lexer_def_(LexerDef& def_, string_type const& state_
                  , string_type const& targetstate_ = string_type())
              : proto_base_type(terminal_type::make(alias()))
              , add(this_()), add_pattern(this_()), def(def_)
              , state(state_), targetstate(targetstate_)
            {}

            // allow to switch states
            lexer_def_ operator()(char_type const* state_) const
            {
                return lexer_def_(def, state_);
            }
            lexer_def_ operator()(char_type const* state_
              , char_type const* targetstate_) const
            {
                return lexer_def_(def, state_, targetstate_);
            }
            lexer_def_ operator()(string_type const& state_
              , string_type const& targetstate_ = string_type()) const
            {
                return lexer_def_(def, state_, targetstate_);
            }

            // allow to assign a token definition expression
            template <typename Expr>
            lexer_def_& operator= (Expr const& xpr)
            {
                // Report invalid expression error as early as possible.
                // If you got an error_invalid_expression error message here,
                // then the expression (expr) is not a valid spirit lex 
                // expression.
                BOOST_SPIRIT_ASSERT_MATCH(lex::domain, Expr);

                def.clear(state.c_str());
                define(xpr);
                return *this;
            }

            // explicitly tell the lexer that the given state will be defined
            // (useful in conjunction with "*")
            std::size_t add_state(char_type const* state_ = 0)
            {
                return def.add_state(state_ ? state_ : def.initial_state().c_str());
            }

            adder add;
            pattern_adder add_pattern;

        private:
            LexerDef& def;
            string_type state;
            string_type targetstate;

            // silence MSVC warning C4512: assignment operator could not be generated
            BOOST_DELETED_FUNCTION(lexer_def_& operator= (lexer_def_ const&))
        };

#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        // allow to assign a token definition expression
        template <typename LexerDef, typename Expr>
        inline lexer_def_<LexerDef>&
        operator+= (lexer_def_<LexerDef>& lexdef, Expr& xpr)
        {
            // Report invalid expression error as early as possible.
            // If you got an error_invalid_expression error message here,
            // then the expression (expr) is not a valid spirit lex 
            // expression.
            BOOST_SPIRIT_ASSERT_MATCH(lex::domain, Expr);

            lexdef.define(xpr);
            return lexdef;
        }
#else
        // allow to assign a token definition expression
        template <typename LexerDef, typename Expr>
        inline lexer_def_<LexerDef>&
        operator+= (lexer_def_<LexerDef>& lexdef, Expr&& xpr)
        {
            // Report invalid expression error as early as possible.
            // If you got an error_invalid_expression error message here,
            // then the expression (expr) is not a valid spirit lex 
            // expression.
            BOOST_SPIRIT_ASSERT_MATCH(lex::domain, Expr);

            lexdef.define(xpr);
            return lexdef;
        }
#endif

        template <typename LexerDef, typename Expr>
        inline lexer_def_<LexerDef>& 
        operator+= (lexer_def_<LexerDef>& lexdef, Expr const& xpr)
        {
            // Report invalid expression error as early as possible.
            // If you got an error_invalid_expression error message here,
            // then the expression (expr) is not a valid spirit lex 
            // expression.
            BOOST_SPIRIT_ASSERT_MATCH(lex::domain, Expr);

            lexdef.define(xpr);
            return lexdef;
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    //  The match_flags flags are used to influence different matching 
    //  modes of the lexer
    struct match_flags
    {
        enum enum_type 
        {
            match_default = 0,          // no flags
            match_not_dot_newline = 1,  // the regex '.' doesn't match newlines
            match_icase = 2             // all matching operations are case insensitive
        };
    };

    ///////////////////////////////////////////////////////////////////////////
    //  This represents a lexer object
    ///////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    // This is the first token id automatically assigned by the library 
    // if needed
    enum tokenids 
    {
        min_token_id = 0x10000
    };

    template <typename Lexer>
    class lexer : public Lexer
    {
    private:
        // avoid warnings about using 'this' in constructor
        lexer& this_() { return *this; }

        std::size_t next_token_id;   // has to be an integral type

    public:
        typedef Lexer lexer_type;
        typedef typename Lexer::id_type id_type;
        typedef typename Lexer::char_type char_type;
        typedef typename Lexer::iterator_type iterator_type;
        typedef lexer base_type;

        typedef detail::lexer_def_<lexer> lexer_def;
        typedef std::basic_string<char_type> string_type;

        // if `id_type` was specified but `first_id` is not provided
        // the `min_token_id` value may be out of range for `id_type`,
        // but it will be a problem only if unique ids feature is in use.
        lexer(unsigned int flags = match_flags::match_default)
          : lexer_type(flags)
          , next_token_id(min_token_id)
          , self(this_(), lexer_type::initial_state())
        {}

        lexer(unsigned int flags, id_type first_id)
          : lexer_type(flags)
          , next_token_id(first_id)
          , self(this_(), lexer_type::initial_state()) 
        {}

        // access iterator interface
        template <typename Iterator>
        iterator_type begin(Iterator& first, Iterator const& last
                , char_type const* initial_state = 0) const
            { return this->lexer_type::begin(first, last, initial_state); }
        iterator_type end() const 
            { return this->lexer_type::end(); }

        std::size_t map_state(char_type const* state)
            { return this->lexer_type::add_state(state); }

        //  create a unique token id
        id_type get_next_id() { return id_type(next_token_id++); }

        lexer_def self;  // allow for easy token definition
    };

}}}

#endif

/* lexer.hpp
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
*/