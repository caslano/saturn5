//  Copyright (c) 2001-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_LEX_STATIC_LEXER_FEB_10_2008_0753PM)
#define BOOST_SPIRIT_LEX_STATIC_LEXER_FEB_10_2008_0753PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/lex/lexer/lexertl/token.hpp>
#include <boost/spirit/home/lex/lexer/lexertl/functor.hpp>
#include <boost/spirit/home/lex/lexer/lexertl/static_functor_data.hpp>
#include <boost/spirit/home/lex/lexer/lexertl/iterator.hpp>
#include <boost/spirit/home/lex/lexer/lexertl/static_version.hpp>
#if defined(BOOST_SPIRIT_DEBUG)
#include <boost/spirit/home/support/detail/lexer/debug.hpp>
#endif
#include <iterator> // for std::iterator_traits

namespace boost { namespace spirit { namespace lex { namespace lexertl
{ 
    ///////////////////////////////////////////////////////////////////////////
    //  forward declaration
    ///////////////////////////////////////////////////////////////////////////
    namespace static_
    {
        struct lexer;
    }

    ///////////////////////////////////////////////////////////////////////////
    //
    //  Every lexer type to be used as a lexer for Spirit has to conform to 
    //  the following public interface:
    //
    //    typedefs: 
    //        iterator_type   The type of the iterator exposed by this lexer.
    //        token_type      The type of the tokens returned from the exposed 
    //                        iterators.
    //
    //    functions:
    //        default constructor
    //                        Since lexers are instantiated as base classes 
    //                        only it might be a good idea to make this 
    //                        constructor protected.
    //        begin, end      Return a pair of iterators, when dereferenced
    //                        returning the sequence of tokens recognized in 
    //                        the input stream given as the parameters to the 
    //                        begin() function.
    //        add_token       Should add the definition of a token to be 
    //                        recognized by this lexer.
    //        clear           Should delete all current token definitions
    //                        associated with the given state of this lexer 
    //                        object.
    //
    //    template parameters:
    //        Token           The type of the tokens to be returned from the
    //                        exposed token iterator.
    //        LexerTables     See explanations below.
    //        Iterator        The type of the iterator used to access the
    //                        underlying character stream.
    //        Functor         The type of the InputPolicy to use to instantiate
    //                        the multi_pass iterator type to be used as the 
    //                        token iterator (returned from begin()/end()).
    //
    //    Additionally, this implementation of a static lexer has a template
    //    parameter LexerTables allowing to customize the static lexer tables
    //    to be used. The LexerTables is expected to be a type exposing 
    //    the following functions:
    //
    //        static std::size_t const state_count()
    //
    //                This function needs toreturn the number of lexer states
    //                contained in the table returned from the state_names()
    //                function.
    //
    //        static char const* const* state_names()
    //
    //                This function needs to return a pointer to a table of
    //                names of all lexer states. The table needs to have as 
    //                much entries as the state_count() function returns
    //
    //        template<typename Iterator>
    //        std::size_t next(std::size_t &start_state_, Iterator const& start_
    //          , Iterator &start_token_, Iterator const& end_
    //          , std::size_t& unique_id_);
    //
    //                This function is expected to return the next matched
    //                token from the underlying input stream.
    //
    ///////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    //
    //  The static_lexer class is a implementation of a Spirit.Lex 
    //  lexer on top of Ben Hanson's lexertl library (For more information 
    //  about lexertl go here: http://www.benhanson.net/lexertl.html). 
    //
    //  This class is designed to be used in conjunction with a generated, 
    //  static lexer. For more information see the documentation (The Static 
    //  Lexer Model).
    //
    //  This class is supposed to be used as the first and only template 
    //  parameter while instantiating instances of a lex::lexer class.
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename Token = token<>
      , typename LexerTables = static_::lexer
      , typename Iterator = typename Token::iterator_type
      , typename Functor = functor<Token, detail::static_data, Iterator> >
    class static_lexer 
    {
    private:
        struct dummy { void true_() {} };
        typedef void (dummy::*safe_bool)();

    public:
        // object is always valid
        operator safe_bool() const { return &dummy::true_; }

        typedef typename std::iterator_traits<Iterator>::value_type char_type;
        typedef std::basic_string<char_type> string_type;

        //  Every lexer type to be used as a lexer for Spirit has to conform to 
        //  a public interface 
        typedef Token token_type;
        typedef typename Token::id_type id_type;
        typedef iterator<Functor> iterator_type;

    private:
        // this type is purely used for the iterator_type construction below
        struct iterator_data_type 
        {
            typedef typename Functor::next_token_functor next_token_functor;
            typedef typename Functor::semantic_actions_type semantic_actions_type;
            typedef typename Functor::get_state_name_type get_state_name_type;

            iterator_data_type(next_token_functor next
                  , semantic_actions_type const& actions
                  , get_state_name_type get_state_name, std::size_t num_states
                  , bool bol)
              : next_(next), actions_(actions), get_state_name_(get_state_name)
              , num_states_(num_states), bol_(bol)
            {}

            next_token_functor next_;
            semantic_actions_type const& actions_;
            get_state_name_type get_state_name_;
            std::size_t num_states_;
            bool bol_;

            // silence MSVC warning C4512: assignment operator could not be generated
            BOOST_DELETED_FUNCTION(iterator_data_type& operator= (iterator_data_type const&))
        };

        typedef LexerTables tables_type;

        // The following static assertion fires if the referenced static lexer 
        // tables are generated by a different static lexer version as used for
        // the current compilation unit. Please regenerate your static lexer
        // tables before trying to create a static_lexer<> instance.
        BOOST_SPIRIT_ASSERT_MSG(
            tables_type::static_version == SPIRIT_STATIC_LEXER_VERSION
          , incompatible_static_lexer_version, (LexerTables));

    public:
        //  Return the start iterator usable for iterating over the generated
        //  tokens, the generated function next_token(...) is called to match 
        //  the next token from the input.
        template <typename Iterator_>
        iterator_type begin(Iterator_& first, Iterator_ const& last
          , char_type const* initial_state = 0) const
        { 
            iterator_data_type iterator_data( 
                    &tables_type::template next<Iterator_>, actions_
                  , &tables_type::state_name, tables_type::state_count()
                  , tables_type::supports_bol
                );
            return iterator_type(iterator_data, first, last, initial_state);
        }

        //  Return the end iterator usable to stop iterating over the generated 
        //  tokens.
        iterator_type end() const
        { 
            return iterator_type(); 
        }

    protected:
        //  Lexer instances can be created by means of a derived class only.
        static_lexer(unsigned int) : unique_id_(0) {}

    public:
        // interface for token definition management
        std::size_t add_token (char_type const*, char_type, std::size_t
          , char_type const*) 
        {
            return unique_id_++;
        }
        std::size_t add_token (char_type const*, string_type const&
          , std::size_t, char_type const*) 
        {
            return unique_id_++;
        }

        // interface for pattern definition management
        void add_pattern (char_type const*, string_type const&
          , string_type const&) {}

        void clear(char_type const*) {}

        std::size_t add_state(char_type const* state)
        {
            return detail::get_state_id(state, &tables_type::state_name
              , tables_type::state_count());
        }
        string_type initial_state() const 
        { 
            return tables_type::state_name(0);
        }

        // register a semantic action with the given id
        template <typename F>
        void add_action(id_type unique_id, std::size_t state, F act) 
        {
            typedef typename Functor::wrap_action_type wrapper_type;
            actions_.add_action(unique_id, state, wrapper_type::call(act));
        }

        bool init_dfa(bool /*minimize*/ = false) const { return true; }

    private:
        typename Functor::semantic_actions_type actions_;
        std::size_t unique_id_;
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  The static_actor_lexer class is another implementation of a 
    //  Spirit.Lex lexer on top of Ben Hanson's lexertl library as outlined 
    //  above (For more information about lexertl go here: 
    //  http://www.benhanson.net/lexertl.html).
    //
    //  Just as the static_lexer class it is meant to be used with 
    //  a statically generated lexer as outlined above.
    //
    //  The only difference to the static_lexer class above is that 
    //  token_def definitions may have semantic (lexer) actions attached while 
    //  being defined:
    //
    //      int w;
    //      token_def<> word = "[^ \t\n]+";
    //      self = word[++ref(w)];        // see example: word_count_lexer
    //
    //  This class is supposed to be used as the first and only template 
    //  parameter while instantiating instances of a lex::lexer class.
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename Token = token<>
      , typename LexerTables = static_::lexer
      , typename Iterator = typename Token::iterator_type
      , typename Functor 
          = functor<Token, detail::static_data, Iterator, mpl::true_> >
    class static_actor_lexer 
      : public static_lexer<Token, LexerTables, Iterator, Functor>
    {
    protected:
        // Lexer instances can be created by means of a derived class only.
        static_actor_lexer(unsigned int flags) 
          : static_lexer<Token, LexerTables, Iterator, Functor>(flags) 
        {}
    };

}}}}

#endif

/* static_lexer.hpp
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
*/