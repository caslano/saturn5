//  Copyright (c) 2001-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_LEX_LEXER_MAR_17_2007_0139PM)
#define BOOST_SPIRIT_LEX_LEXER_MAR_17_2007_0139PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <iosfwd>

#include <boost/spirit/home/support/detail/lexer/generator.hpp>
#include <boost/spirit/home/support/detail/lexer/rules.hpp>
#include <boost/spirit/home/support/detail/lexer/consts.hpp>
#include <boost/spirit/home/support/unused.hpp>

#include <boost/spirit/home/lex/lexer/lexertl/token.hpp>
#include <boost/spirit/home/lex/lexer/lexertl/functor.hpp>
#include <boost/spirit/home/lex/lexer/lexertl/functor_data.hpp>
#include <boost/spirit/home/lex/lexer/lexertl/iterator.hpp>
#if defined(BOOST_SPIRIT_LEXERTL_DEBUG)
#include <boost/spirit/home/support/detail/lexer/debug.hpp>
#endif

#include <iterator> // for std::iterator_traits

namespace boost { namespace spirit { namespace lex { namespace lexertl
{
    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        ///////////////////////////////////////////////////////////////////////
        //  The must_escape function checks if the given character value needs
        //  to be preceded by a backslash character to disable its special
        //  meaning in the context of a regular expression
        ///////////////////////////////////////////////////////////////////////
        template <typename Char>
        inline bool must_escape(Char c)
        {
            // FIXME: more needed?
            switch (c) {
            case '+': case '/': case '*': case '?':
            case '|':
            case '(': case ')':
            case '[': case ']':
            case '{': case '}':
            case '.':
            case '^': case '$':
            case '\\':
            case '"':
                return true;

            default:
                break;
            }
            return false;
        }

        ///////////////////////////////////////////////////////////////////////
        //  The escape function returns the string representation of the given
        //  character value, possibly escaped with a backslash character, to
        //  allow it being safely used in a regular expression definition.
        ///////////////////////////////////////////////////////////////////////
        template <typename Char>
        inline std::basic_string<Char> escape(Char ch)
        {
            std::basic_string<Char> result(1, ch);
            if (detail::must_escape(ch))
            {
                typedef typename std::basic_string<Char>::size_type size_type;
                result.insert((size_type)0, 1, '\\');
            }
            return result;
        }

        ///////////////////////////////////////////////////////////////////////
        //
        ///////////////////////////////////////////////////////////////////////
        inline boost::lexer::regex_flags map_flags(unsigned int flags)
        {
            unsigned int retval = boost::lexer::none;
            if (flags & match_flags::match_not_dot_newline)
                retval |= boost::lexer::dot_not_newline;
            if (flags & match_flags::match_icase)
                retval |= boost::lexer::icase;

            return boost::lexer::regex_flags(retval);
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename Lexer, typename F>
    bool generate_static(Lexer const&
      , std::basic_ostream<typename Lexer::char_type>&
      , typename Lexer::char_type const*, F);

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
    //        Iterator        The type of the iterator used to access the
    //                        underlying character stream.
    //        Token           The type of the tokens to be returned from the
    //                        exposed token iterator.
    //        Functor         The type of the InputPolicy to use to instantiate
    //                        the multi_pass iterator type to be used as the
    //                        token iterator (returned from begin()/end()).
    //
    ///////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    //
    //  The lexer class is a implementation of a Spirit.Lex lexer on
    //  top of Ben Hanson's lexertl library as outlined above (For more
    //  information about lexertl go here: http://www.benhanson.net/lexertl.html).
    //
    //  This class is supposed to be used as the first and only template
    //  parameter while instantiating instances of a lex::lexer class.
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename Token = token<>
      , typename Iterator = typename Token::iterator_type
      , typename Functor = functor<Token, lexertl::detail::data, Iterator> >
    class lexer
    {
    private:
        struct dummy { void true_() {} };
        typedef void (dummy::*safe_bool)();

        static std::size_t const all_states_id = static_cast<std::size_t>(-2);

    public:
        operator safe_bool() const
            { return initialized_dfa_ ? &dummy::true_ : 0; }

        typedef typename std::iterator_traits<Iterator>::value_type char_type;
        typedef std::basic_string<char_type> string_type;

        typedef boost::lexer::basic_rules<char_type> basic_rules_type;

        //  Every lexer type to be used as a lexer for Spirit has to conform to
        //  a public interface .
        typedef Token token_type;
        typedef typename Token::id_type id_type;
        typedef iterator<Functor> iterator_type;

    private:
        // this type is purely used for the iterator_type construction below
        struct iterator_data_type
        {
            typedef typename Functor::semantic_actions_type semantic_actions_type;

            iterator_data_type(
                    boost::lexer::basic_state_machine<char_type> const& sm
                  , boost::lexer::basic_rules<char_type> const& rules
                  , semantic_actions_type const& actions)
              : state_machine_(sm), rules_(rules), actions_(actions)
            {}

            boost::lexer::basic_state_machine<char_type> const& state_machine_;
            boost::lexer::basic_rules<char_type> const& rules_;
            semantic_actions_type const& actions_;

            // silence MSVC warning C4512: assignment operator could not be generated
            BOOST_DELETED_FUNCTION(iterator_data_type& operator= (iterator_data_type const&))
        };

    public:
        //  Return the start iterator usable for iterating over the generated
        //  tokens.
        iterator_type begin(Iterator& first, Iterator const& last
          , char_type const* initial_state = 0) const
        {
            if (!init_dfa())    // never minimize DFA for dynamic lexers
                return iterator_type();

            iterator_data_type iterator_data(state_machine_, rules_, actions_);
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
        lexer(unsigned int flags)
          : flags_(detail::map_flags(flags))
          , rules_(flags_)
          , initialized_dfa_(false)
        {}

    public:
        // interface for token definition management
        std::size_t add_token(char_type const* state, char_type tokendef,
            std::size_t token_id, char_type const* targetstate)
        {
            add_state(state);
            initialized_dfa_ = false;
            if (state == all_states())
                return rules_.add(state, detail::escape(tokendef), token_id, rules_.dot());

            if (0 == targetstate)
                targetstate = state;
            else
                add_state(targetstate);
            return rules_.add(state, detail::escape(tokendef), token_id, targetstate);
        }
        std::size_t add_token(char_type const* state, string_type const& tokendef,
            std::size_t token_id, char_type const* targetstate)
        {
            add_state(state);
            initialized_dfa_ = false;
            if (state == all_states())
                return rules_.add(state, tokendef, token_id, rules_.dot());

            if (0 == targetstate)
                targetstate = state;
            else
                add_state(targetstate);
            return rules_.add(state, tokendef, token_id, targetstate);
        }

        // interface for pattern definition management
        void add_pattern (char_type const* state, string_type const& name,
            string_type const& patterndef)
        {
            add_state(state);
            rules_.add_macro(name.c_str(), patterndef);
            initialized_dfa_ = false;
        }

        boost::lexer::rules const& get_rules() const { return rules_; }

        void clear(char_type const* state)
        {
            std::size_t s = rules_.state(state);
            if (boost::lexer::npos != s)
                rules_.clear(state);
            initialized_dfa_ = false;
        }
        std::size_t add_state(char_type const* state)
        {
            if (state == all_states())
                return all_states_id;

            std::size_t stateid = rules_.state(state);
            if (boost::lexer::npos == stateid) {
                stateid = rules_.add_state(state);
                initialized_dfa_ = false;
            }
            return stateid;
        }
        string_type initial_state() const
        {
            return string_type(rules_.initial());
        }
        string_type all_states() const
        {
            return string_type(rules_.all_states());
        }

        //  Register a semantic action with the given id
        template <typename F>
        void add_action(std::size_t unique_id, std::size_t state, F act)
        {
            // If you see an error here stating add_action is not a member of
            // fusion::unused_type then you are probably having semantic actions
            // attached to at least one token in the lexer definition without
            // using the lex::lexertl::actor_lexer<> as its base class.
            typedef typename Functor::wrap_action_type wrapper_type;
            if (state == all_states_id) {
                // add the action to all known states
                typedef typename
                    basic_rules_type::string_size_t_map::const_iterator
                state_iterator;

                std::size_t states = rules_.statemap().size();
                for (state_iterator it = rules_.statemap().begin(),
                                    end = rules_.statemap().end(); it != end; ++it) {
                    for (std::size_t j = 0; j < states; ++j)
                        actions_.add_action(unique_id + j, it->second, wrapper_type::call(act));
                }
            }
            else {
                actions_.add_action(unique_id, state, wrapper_type::call(act));
            }
        }
//         template <typename F>
//         void add_action(std::size_t unique_id, char_type const* state, F act)
//         {
//             typedef typename Functor::wrap_action_type wrapper_type;
//             actions_.add_action(unique_id, add_state(state), wrapper_type::call(act));
//         }

        // We do not minimize the state machine by default anymore because
        // Ben said: "If you can afford to generate a lexer at runtime, there
        //            is little point in calling minimise."
        // Go figure.
        bool init_dfa(bool minimize = false) const
        {
            if (!initialized_dfa_) {
                state_machine_.clear();
                typedef boost::lexer::basic_generator<char_type> generator;
                generator::build (rules_, state_machine_);
                if (minimize)
                    generator::minimise (state_machine_);

#if defined(BOOST_SPIRIT_LEXERTL_DEBUG)
                boost::lexer::debug::dump(state_machine_, std::cerr);
#endif
                initialized_dfa_ = true;

//                 // release memory held by rules description
//                 basic_rules_type rules;
//                 rules.init_state_info(rules_);        // preserve states
//                 std::swap(rules, rules_);
            }
            return true;
        }

    private:
        // lexertl specific data
        mutable boost::lexer::basic_state_machine<char_type> state_machine_;
        boost::lexer::regex_flags flags_;
        /*mutable*/ basic_rules_type rules_;

        typename Functor::semantic_actions_type actions_;
        mutable bool initialized_dfa_;

        // generator functions must be able to access members directly
        template <typename Lexer, typename F>
        friend bool generate_static(Lexer const&
          , std::basic_ostream<typename Lexer::char_type>&
          , typename Lexer::char_type const*, F);
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  The actor_lexer class is another implementation of a Spirit.Lex
    //  lexer on top of Ben Hanson's lexertl library as outlined above (For
    //  more information about lexertl go here:
    //  http://www.benhanson.net/lexertl.html).
    //
    //  The only difference to the lexer class above is that token_def
    //  definitions may have semantic (lexer) actions attached while being
    //  defined:
    //
    //      int w;
    //      token_def word = "[^ \t\n]+";
    //      self = word[++ref(w)];        // see example: word_count_lexer
    //
    //  This class is supposed to be used as the first and only template
    //  parameter while instantiating instances of a lex::lexer class.
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename Token = token<>
      , typename Iterator = typename Token::iterator_type
      , typename Functor = functor<Token, lexertl::detail::data, Iterator, mpl::true_> >
    class actor_lexer : public lexer<Token, Iterator, Functor>
    {
    protected:
        //  Lexer instances can be created by means of a derived class only.
        actor_lexer(unsigned int flags)
          : lexer<Token, Iterator, Functor>(flags) {}
    };

}}}}

#endif

/* lexer.hpp
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
*/