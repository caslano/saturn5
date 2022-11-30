//  Copyright (c) 2001-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_LEX_LEXER_FUNCTOR_NOV_18_2007_1112PM)
#define BOOST_SPIRIT_LEX_LEXER_FUNCTOR_NOV_18_2007_1112PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/mpl/bool.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/spirit/home/lex/lexer/pass_flags.hpp>
#include <boost/assert.hpp>
#include <iterator> // for std::iterator_traits

#if 0 != __COMO_VERSION__ || !BOOST_WORKAROUND(BOOST_MSVC, <= 1310)
#define BOOST_SPIRIT_STATIC_EOF 1
#define BOOST_SPIRIT_EOF_PREFIX static
#else
#define BOOST_SPIRIT_EOF_PREFIX 
#endif

namespace boost { namespace spirit { namespace lex { namespace lexertl
{ 
    ///////////////////////////////////////////////////////////////////////////
    //
    //  functor is a template usable as the functor object for the 
    //  multi_pass iterator allowing to wrap a lexertl based dfa into a 
    //  iterator based interface.
    //  
    //    Token:      the type of the tokens produced by this functor
    //                this needs to expose a constructor with the following
    //                prototype:
    //
    //                Token(std::size_t id, std::size_t state, 
    //                      Iterator start, Iterator end)
    //
    //                where 'id' is the token id, state is the lexer state,
    //                this token has been matched in, and 'first' and 'end'  
    //                mark the start and the end of the token with respect 
    //                to the underlying character stream.
    //    FunctorData:
    //                this is expected to encapsulate the shared part of the 
    //                functor (see lex/lexer/lexertl/functor_data.hpp for an
    //                example and documentation).
    //    Iterator:   the type of the underlying iterator
    //    SupportsActors:
    //                this is expected to be a mpl::bool_, if mpl::true_ the
    //                functor invokes functors which (optionally) have 
    //                been attached to the token definitions.
    //    SupportState:
    //                this is expected to be a mpl::bool_, if mpl::true_ the
    //                functor supports different lexer states, 
    //                otherwise no lexer state is supported.
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename Token
      , template <typename, typename, typename, typename> class FunctorData
      , typename Iterator = typename Token::iterator_type
      , typename SupportsActors = mpl::false_
      , typename SupportsState = typename Token::has_state>
    class functor
    {
    public:
        typedef typename 
            std::iterator_traits<Iterator>::value_type 
        char_type;

    private:
        // Needed by compilers not implementing the resolution to DR45. For
        // reference, see
        // http://www.open-std.org/JTC1/SC22/WG21/docs/cwg_defects.html#45.
        typedef typename Token::token_value_type token_value_type;
        friend class FunctorData<Iterator, SupportsActors, SupportsState
          , token_value_type>;

        // Helper template allowing to assign a value on exit
        template <typename T>
        struct assign_on_exit
        {
            assign_on_exit(T& dst, T const& src)
              : dst_(dst), src_(src) {}

            ~assign_on_exit()
            {
                dst_ = src_;
            }

            T& dst_;
            T const& src_;

            // silence MSVC warning C4512: assignment operator could not be generated
            BOOST_DELETED_FUNCTION(assign_on_exit& operator= (assign_on_exit const&))
        };

    public:
        functor() {}

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1310)
        // somehow VC7.1 needs this (meaningless) assignment operator
        functor& operator=(functor const& rhs)
        {
            return *this;
        }
#endif

        ///////////////////////////////////////////////////////////////////////
        // interface to the iterator_policies::split_functor_input policy
        typedef Token result_type;
        typedef functor unique;
        typedef FunctorData<Iterator, SupportsActors, SupportsState
          , token_value_type> shared;

        BOOST_SPIRIT_EOF_PREFIX result_type const eof;

        ///////////////////////////////////////////////////////////////////////
        typedef Iterator iterator_type;
        typedef typename shared::semantic_actions_type semantic_actions_type;
        typedef typename shared::next_token_functor next_token_functor;
        typedef typename shared::get_state_name_type get_state_name_type;

        // this is needed to wrap the semantic actions in a proper way
        typedef typename shared::wrap_action_type wrap_action_type;

        ///////////////////////////////////////////////////////////////////////
        template <typename MultiPass>
        static result_type& get_next(MultiPass& mp, result_type& result)
        {
            typedef typename result_type::id_type id_type;

            shared& data = mp.shared()->ftor;
            for(;;) 
            {
                if (data.get_first() == data.get_last()) 
#if defined(BOOST_SPIRIT_STATIC_EOF)
                    return result = eof;
#else
                    return result = mp.ftor.eof;
#endif

                data.reset_value();
                Iterator end = data.get_first();
                std::size_t unique_id = boost::lexer::npos;
                bool prev_bol = false;

                // lexer matching might change state
                std::size_t state = data.get_state();
                std::size_t id = data.next(end, unique_id, prev_bol);

                if (boost::lexer::npos == id) {   // no match
#if defined(BOOST_SPIRIT_LEXERTL_DEBUG)
                    std::string next;
                    Iterator it = data.get_first();
                    for (std::size_t i = 0; i < 10 && it != data.get_last(); ++it, ++i)
                        next += *it;

                    std::cerr << "Not matched, in state: " << state 
                              << ", lookahead: >" << next << "<" << std::endl;
#endif
                    return result = result_type(0);
                }
                else if (0 == id) {         // EOF reached
#if defined(BOOST_SPIRIT_STATIC_EOF)
                    return result = eof;
#else
                    return result = mp.ftor.eof;
#endif
                }

#if defined(BOOST_SPIRIT_LEXERTL_DEBUG)
                {
                    std::string next;
                    Iterator it = end;
                    for (std::size_t i = 0; i < 10 && it != data.get_last(); ++it, ++i)
                        next += *it;

                    std::cerr << "Matched: " << id << ", in state: " 
                              << state << ", string: >" 
                              << std::basic_string<char_type>(data.get_first(), end) << "<"
                              << ", lookahead: >" << next << "<" << std::endl;
                    if (data.get_state() != state) {
                        std::cerr << "Switched to state: " 
                                  << data.get_state() << std::endl;
                    }
                }
#endif
                // account for a possibly pending lex::more(), i.e. moving 
                // data.first_ back to the start of the previously matched token.
                bool adjusted = data.adjust_start();

                // set the end of the matched input sequence in the token data
                data.set_end(end);

                // invoke attached semantic actions, if defined, might change
                // state, id, data.first_, and/or end
                BOOST_SCOPED_ENUM(pass_flags) pass = 
                    data.invoke_actions(state, id, unique_id, end);

                if (data.has_value()) {
                    // return matched token using the token value as set before
                    // using data.set_value(), advancing 'data.first_' past the 
                    // matched sequence
                    assign_on_exit<Iterator> on_exit(data.get_first(), end);
                    return result = result_type(id_type(id), state, data.get_value());
                }
                else if (pass_flags::pass_normal == pass) {
                    // return matched token, advancing 'data.first_' past the 
                    // matched sequence
                    assign_on_exit<Iterator> on_exit(data.get_first(), end);
                    return result = result_type(id_type(id), state, data.get_first(), end);
                }
                else if (pass_flags::pass_fail == pass) {
#if defined(BOOST_SPIRIT_LEXERTL_DEBUG)
                    std::cerr << "Matching forced to fail" << std::endl; 
#endif
                    // if the data.first_ got adjusted above, revert this adjustment
                    if (adjusted)
                        data.revert_adjust_start();

                    // one of the semantic actions signaled no-match
                    data.reset_bol(prev_bol);
                    if (state != data.get_state())
                        continue;       // retry matching if state has changed

                    // if the state is unchanged repeating the match wouldn't
                    // move the input forward, causing an infinite loop
                    return result = result_type(0);
                }

#if defined(BOOST_SPIRIT_LEXERTL_DEBUG)
                std::cerr << "Token ignored, continuing matching" << std::endl; 
#endif
            // if this token needs to be ignored, just repeat the matching,
            // while starting right after the current match
                data.get_first() = end;
            }
        }

        // set_state are propagated up to the iterator interface, allowing to 
        // manipulate the current lexer state through any of the exposed 
        // iterators.
        template <typename MultiPass>
        static std::size_t set_state(MultiPass& mp, std::size_t state) 
        { 
            std::size_t oldstate = mp.shared()->ftor.get_state();
            mp.shared()->ftor.set_state(state);

#if defined(BOOST_SPIRIT_LEXERTL_DEBUG)
            std::cerr << "Switching state from: " << oldstate 
                      << " to: " << state
                      << std::endl;
#endif
            return oldstate; 
        }

        template <typename MultiPass>
        static std::size_t get_state(MultiPass& mp) 
        { 
            return mp.shared()->ftor.get_state();
        }

        template <typename MultiPass>
        static std::size_t 
        map_state(MultiPass const& mp, char_type const* statename)  
        { 
            return mp.shared()->ftor.get_state_id(statename);
        }

        // we don't need this, but it must be there
        template <typename MultiPass>
        static void destroy(MultiPass const&) {}
    };

#if defined(BOOST_SPIRIT_STATIC_EOF)
    ///////////////////////////////////////////////////////////////////////////
    //  eof token
    ///////////////////////////////////////////////////////////////////////////
    template <typename Token
      , template <typename, typename, typename, typename> class FunctorData
      , typename Iterator, typename SupportsActors, typename SupportsState>
    typename functor<Token, FunctorData, Iterator, SupportsActors, SupportsState>::result_type const
        functor<Token, FunctorData, Iterator, SupportsActors, SupportsState>::eof = 
            typename functor<Token, FunctorData, Iterator, SupportsActors
              , SupportsState>::result_type();
#endif

}}}}

#undef BOOST_SPIRIT_EOF_PREFIX
#undef BOOST_SPIRIT_STATIC_EOF

#endif

/* functor.hpp
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
*/