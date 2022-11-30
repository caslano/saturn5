//  Copyright (c) 2001-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_LEX_LEXER_FUNCTOR_DATA_JUN_10_2009_0954AM)
#define BOOST_SPIRIT_LEX_LEXER_FUNCTOR_DATA_JUN_10_2009_0954AM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/qi/detail/assign_to.hpp>
#include <boost/spirit/home/support/detail/lexer/generator.hpp>
#include <boost/spirit/home/support/detail/lexer/rules.hpp>
#include <boost/spirit/home/support/detail/lexer/state_machine.hpp>
#include <boost/spirit/home/lex/lexer/lexertl/iterator_tokenizer.hpp>
#include <boost/spirit/home/lex/lexer/lexertl/semantic_action_data.hpp>
#include <boost/spirit/home/lex/lexer/lexertl/wrap_action.hpp>
#include <boost/spirit/home/support/assert_msg.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/optional.hpp>
#include <iterator> // for std::iterator_traits

namespace boost { namespace spirit { namespace lex { namespace lexertl
{ 
    namespace detail
    {
        ///////////////////////////////////////////////////////////////////////
        template <typename Iterator, typename HasActors, typename HasState
          , typename TokenValue>
        class data;    // no default specialization

        ///////////////////////////////////////////////////////////////////////
        //  neither supports state, nor actors
        template <typename Iterator, typename TokenValue>
        class data<Iterator, mpl::false_, mpl::false_, TokenValue>
        {
        protected:
            typedef typename 
                std::iterator_traits<Iterator>::value_type 
            char_type;

        public:
            typedef Iterator base_iterator_type;
            typedef iterator_range<Iterator> token_value_type;
            typedef token_value_type get_value_type;
            typedef std::size_t state_type;
            typedef char_type const* state_name_type;
            typedef unused_type semantic_actions_type;
            typedef detail::wrap_action<unused_type, Iterator, data, std::size_t>
                wrap_action_type;

            typedef unused_type next_token_functor;
            typedef unused_type get_state_name_type;

            // initialize the shared data 
            template <typename IterData>
            data (IterData const& data_, Iterator& first, Iterator const& last)
              : first_(first), last_(last)
              , state_machine_(data_.state_machine_)
              , rules_(data_.rules_)
              , bol_(data_.state_machine_.data()._seen_BOL_assertion) {}

            // The following functions are used by the implementation of the 
            // placeholder '_state'.
            template <typename Char>
            void set_state_name (Char const*) 
            {
                // If you see a compile time assertion below you're probably 
                // using a token type not supporting lexer states (the 3rd 
                // template parameter of the token is mpl::false_), but your 
                // code uses state changes anyways.
                BOOST_SPIRIT_ASSERT_FAIL(Char,
                    tried_to_set_state_of_stateless_token, ());
            }
            char_type const* get_state_name() const { return rules_.initial(); }
            std::size_t get_state_id (char_type const*) const
            {
                return 0;
            }

            // The function get_eoi() is used by the implementation of the 
            // placeholder '_eoi'.
            Iterator const& get_eoi() const { return last_; }

            // The function less() is used by the implementation of the support
            // function lex::less(). Its functionality is equivalent to flex'
            // function yyless(): it returns an iterator positioned to the 
            // nth input character beyond the current start iterator (i.e. by
            // assigning the return value to the placeholder '_end' it is 
            // possible to return all but the first n characters of the current 
            // token back to the input stream. 
            //
            // This function does nothing as long as no semantic actions are 
            // used.
            Iterator const& less(Iterator const& it, int) 
            { 
                // The following assertion fires most likely because you are 
                // using lexer semantic actions without using the actor_lexer
                // as the base class for your token definition class.
                BOOST_ASSERT(false && 
                    "Are you using lexer semantic actions without using the "
                    "actor_lexer base?");
                return it; 
            }

            // The function more() is used by the implementation of the support 
            // function lex::more(). Its functionality is equivalent to flex'
            // function yymore(): it tells the lexer that the next time it 
            // matches a rule, the corresponding token should be appended onto 
            // the current token value rather than replacing it.
            // 
            // These functions do nothing as long as no semantic actions are 
            // used.
            void more() 
            { 
                // The following assertion fires most likely because you are 
                // using lexer semantic actions without using the actor_lexer
                // as the base class for your token definition class.
                BOOST_ASSERT(false && 
                    "Are you using lexer semantic actions without using the "
                    "actor_lexer base?"); 
            }
            bool adjust_start() { return false; }
            void revert_adjust_start() {}

            // The function lookahead() is used by the implementation of the 
            // support function lex::lookahead. It can be used to implement 
            // lookahead for lexer engines not supporting constructs like flex'
            // a/b  (match a, but only when followed by b):
            //
            // This function does nothing as long as no semantic actions are 
            // used.
            bool lookahead(std::size_t, std::size_t /*state*/ = std::size_t(~0)) 
            { 
                // The following assertion fires most likely because you are 
                // using lexer semantic actions without using the actor_lexer
                // as the base class for your token definition class.
                BOOST_ASSERT(false && 
                    "Are you using lexer semantic actions without using the "
                    "actor_lexer base?");
                return false; 
            }

            // the functions next, invoke_actions, and get_state are used by 
            // the functor implementation below

            // The function next() tries to match the next token from the 
            // underlying input sequence. 
            std::size_t next(Iterator& end, std::size_t& unique_id, bool& prev_bol)
            {
                prev_bol = bol_;

                typedef basic_iterator_tokeniser<Iterator> tokenizer;
                return tokenizer::next(state_machine_, bol_, end, last_
                  , unique_id);
            }

            // nothing to invoke, so this is empty
            BOOST_SCOPED_ENUM(pass_flags) invoke_actions(std::size_t
              , std::size_t, std::size_t, Iterator const&) 
            {
                return pass_flags::pass_normal;    // always accept
            }

            std::size_t get_state() const { return 0; }
            void set_state(std::size_t) {}

            void set_end(Iterator const& /*it*/) {}

            Iterator& get_first() { return first_; }
            Iterator const& get_first() const { return first_; }
            Iterator const& get_last() const { return last_; }

            iterator_range<Iterator> get_value() const 
            { 
                return iterator_range<Iterator>(first_, last_); 
            }
            bool has_value() const { return false; }
            void reset_value() {}

            void reset_bol(bool bol) { bol_ = bol; }

        protected:
            Iterator& first_;
            Iterator last_;

            boost::lexer::basic_state_machine<char_type> const& state_machine_;
            boost::lexer::basic_rules<char_type> const& rules_;

            bool bol_;      // helper storing whether last character was \n

            // silence MSVC warning C4512: assignment operator could not be generated
            BOOST_DELETED_FUNCTION(data& operator= (data const&))
        };

        ///////////////////////////////////////////////////////////////////////
        //  doesn't support lexer semantic actions, but supports state
        template <typename Iterator, typename TokenValue>
        class data<Iterator, mpl::false_, mpl::true_, TokenValue>
          : public data<Iterator, mpl::false_, mpl::false_, TokenValue>
        {
        protected:
            typedef data<Iterator, mpl::false_, mpl::false_, TokenValue> base_type;
            typedef typename base_type::char_type char_type;

        public:
            typedef Iterator base_iterator_type;
            typedef iterator_range<Iterator> token_value_type;
            typedef token_value_type get_value_type;
            typedef typename base_type::state_type state_type;
            typedef typename base_type::state_name_type state_name_type;
            typedef typename base_type::semantic_actions_type 
                semantic_actions_type;

            // initialize the shared data 
            template <typename IterData>
            data (IterData const& data_, Iterator& first, Iterator const& last)
              : base_type(data_, first, last)
              , state_(0) {}

            // The following functions are used by the implementation of the 
            // placeholder '_state'.
            void set_state_name (char_type const* new_state) 
            { 
                std::size_t state_id = this->rules_.state(new_state);

                // If the following assertion fires you've probably been using 
                // a lexer state name which was not defined in your token 
                // definition.
                BOOST_ASSERT(state_id != boost::lexer::npos);

                if (state_id != boost::lexer::npos)
                    state_ = state_id;
            }
            char_type const* get_state_name() const
            {
                return this->rules_.state(state_);
            }
            std::size_t get_state_id (char_type const* state) const
            {
                return this->rules_.state(state);
            }

            // the functions next() and get_state() are used by the functor 
            // implementation below

            // The function next() tries to match the next token from the 
            // underlying input sequence. 
            std::size_t next(Iterator& end, std::size_t& unique_id, bool& prev_bol)
            {
                prev_bol = this->bol_;

                typedef basic_iterator_tokeniser<Iterator> tokenizer;
                return tokenizer::next(this->state_machine_, state_, 
                    this->bol_, end, this->get_eoi(), unique_id);
            }

            std::size_t& get_state() { return state_; }
            void set_state(std::size_t state) { state_ = state; }

        protected:
            std::size_t state_;

            // silence MSVC warning C4512: assignment operator could not be generated
            BOOST_DELETED_FUNCTION(data& operator= (data const&))
        };

        ///////////////////////////////////////////////////////////////////////
        //  does support lexer semantic actions, may support state
        template <typename Iterator, typename HasState, typename TokenValue>
        class data<Iterator, mpl::true_, HasState, TokenValue> 
          : public data<Iterator, mpl::false_, HasState, TokenValue>
        {
        public:
            typedef semantic_actions<Iterator, HasState, data> 
                semantic_actions_type;

        protected:
            typedef data<Iterator, mpl::false_, HasState, TokenValue> base_type;
            typedef typename base_type::char_type char_type;
            typedef typename semantic_actions_type::functor_wrapper_type
                functor_wrapper_type;

        public:
            typedef Iterator base_iterator_type;
            typedef TokenValue token_value_type;
            typedef TokenValue const& get_value_type;
            typedef typename base_type::state_type state_type;
            typedef typename base_type::state_name_type state_name_type;

            typedef detail::wrap_action<functor_wrapper_type
              , Iterator, data, std::size_t> wrap_action_type;

            template <typename IterData>
            data (IterData const& data_, Iterator& first, Iterator const& last)
              : base_type(data_, first, last)
              , actions_(data_.actions_), hold_(), end_()
              , value_(iterator_range<Iterator>(last, last))
              , has_value_(false), has_hold_(false) {}

            // invoke attached semantic actions, if defined
            BOOST_SCOPED_ENUM(pass_flags) invoke_actions(std::size_t state
              , std::size_t& id, std::size_t unique_id, Iterator& end)
            {
                return actions_.invoke_actions(state, id, unique_id, end, *this); 
            }

            // The function less() is used by the implementation of the support
            // function lex::less(). Its functionality is equivalent to flex'
            // function yyless(): it returns an iterator positioned to the 
            // nth input character beyond the current start iterator (i.e. by
            // assigning the return value to the placeholder '_end' it is 
            // possible to return all but the first n characters of the current 
            // token back to the input stream). 
            Iterator const& less(Iterator& it, int n) 
            {
                it = this->get_first();
                std::advance(it, n);
                return it;
            }

            // The function more() is used by the implementation of the support 
            // function lex::more(). Its functionality is equivalent to flex'
            // function yymore(): it tells the lexer that the next time it 
            // matches a rule, the corresponding token should be appended onto 
            // the current token value rather than replacing it.
            void more()
            {
                hold_ = this->get_first();
                has_hold_ = true;
            }

            // The function lookahead() is used by the implementation of the 
            // support function lex::lookahead. It can be used to implement 
            // lookahead for lexer engines not supporting constructs like flex'
            // a/b  (match a, but only when followed by b)
            bool lookahead(std::size_t id, std::size_t state = std::size_t(~0))
            {
                Iterator end = end_;
                std::size_t unique_id = boost::lexer::npos;
                bool bol = this->bol_;

                if (std::size_t(~0) == state)
                    state = this->state_;

                typedef basic_iterator_tokeniser<Iterator> tokenizer;
                return id == tokenizer::next(this->state_machine_, state, 
                    bol, end, this->get_eoi(), unique_id);
            }

            // The adjust_start() and revert_adjust_start() are helper 
            // functions needed to implement the functionality required for 
            // lex::more(). It is called from the functor body below.
            bool adjust_start()
            {
                if (!has_hold_)
                    return false;

                std::swap(this->get_first(), hold_);
                has_hold_ = false;
                return true;
            }
            void revert_adjust_start()
            {
                // this will be called only if adjust_start above returned true
                std::swap(this->get_first(), hold_);
                has_hold_ = true;
            }

            TokenValue const& get_value() const 
            {
                if (!has_value_) {
                    value_ = iterator_range<Iterator>(this->get_first(), end_);
                    has_value_ = true;
                }
                return value_;
            }
            template <typename Value>
            void set_value(Value const& val)
            {
                value_ = val;
                has_value_ = true;
            }
            void set_end(Iterator const& it)
            {
                end_ = it;
            }
            bool has_value() const { return has_value_; }
            void reset_value() { has_value_ = false; }

        protected:
            semantic_actions_type const& actions_;
            Iterator hold_;     // iterator needed to support lex::more()
            Iterator end_;      // iterator pointing to end of matched token
            mutable TokenValue value_;  // token value to use
            mutable bool has_value_;    // 'true' if value_ is valid
            bool has_hold_;     // 'true' if hold_ is valid

            // silence MSVC warning C4512: assignment operator could not be generated
            BOOST_DELETED_FUNCTION(data& operator= (data const&))
        };

        ///////////////////////////////////////////////////////////////////////
        //  does support lexer semantic actions, may support state, is used for
        //  position_token exposing exactly one type
        template <typename Iterator, typename HasState, typename TokenValue>
        class data<Iterator, mpl::true_, HasState, boost::optional<TokenValue> > 
          : public data<Iterator, mpl::false_, HasState, TokenValue>
        {
        public:
            typedef semantic_actions<Iterator, HasState, data> 
                semantic_actions_type;

        protected:
            typedef data<Iterator, mpl::false_, HasState, TokenValue> base_type;
            typedef typename base_type::char_type char_type;
            typedef typename semantic_actions_type::functor_wrapper_type
                functor_wrapper_type;

        public:
            typedef Iterator base_iterator_type;
            typedef boost::optional<TokenValue> token_value_type;
            typedef boost::optional<TokenValue> const& get_value_type;
            typedef typename base_type::state_type state_type;
            typedef typename base_type::state_name_type state_name_type;

            typedef detail::wrap_action<functor_wrapper_type
              , Iterator, data, std::size_t> wrap_action_type;

            template <typename IterData>
            data (IterData const& data_, Iterator& first, Iterator const& last)
              : base_type(data_, first, last)
              , actions_(data_.actions_), hold_()
              , has_value_(false), has_hold_(false) 
            {
                spirit::traits::assign_to(first, last, value_);
                has_value_ = true;
            }

            // invoke attached semantic actions, if defined
            BOOST_SCOPED_ENUM(pass_flags) invoke_actions(std::size_t state
              , std::size_t& id, std::size_t unique_id, Iterator& end)
            {
                return actions_.invoke_actions(state, id, unique_id, end, *this); 
            }

            // The function less() is used by the implementation of the support
            // function lex::less(). Its functionality is equivalent to flex'
            // function yyless(): it returns an iterator positioned to the 
            // nth input character beyond the current start iterator (i.e. by
            // assigning the return value to the placeholder '_end' it is 
            // possible to return all but the first n characters of the current 
            // token back to the input stream). 
            Iterator const& less(Iterator& it, int n) 
            {
                it = this->get_first();
                std::advance(it, n);
                return it;
            }

            // The function more() is used by the implementation of the support 
            // function lex::more(). Its functionality is equivalent to flex'
            // function yymore(): it tells the lexer that the next time it 
            // matches a rule, the corresponding token should be appended onto 
            // the current token value rather than replacing it.
            void more()
            {
                hold_ = this->get_first();
                has_hold_ = true;
            }

            // The function lookahead() is used by the implementation of the 
            // support function lex::lookahead. It can be used to implement 
            // lookahead for lexer engines not supporting constructs like flex'
            // a/b  (match a, but only when followed by b)
            bool lookahead(std::size_t id, std::size_t state = std::size_t(~0))
            {
                Iterator end = end_;
                std::size_t unique_id = boost::lexer::npos;
                bool bol = this->bol_;

                if (std::size_t(~0) == state)
                    state = this->state_;

                typedef basic_iterator_tokeniser<Iterator> tokenizer;
                return id == tokenizer::next(this->state_machine_, state, 
                    bol, end, this->get_eoi(), unique_id);
            }

            // The adjust_start() and revert_adjust_start() are helper 
            // functions needed to implement the functionality required for 
            // lex::more(). It is called from the functor body below.
            bool adjust_start()
            {
                if (!has_hold_)
                    return false;

                std::swap(this->get_first(), hold_);
                has_hold_ = false;
                return true;
            }
            void revert_adjust_start()
            {
                // this will be called only if adjust_start above returned true
                std::swap(this->get_first(), hold_);
                has_hold_ = true;
            }

            token_value_type const& get_value() const 
            {
                if (!has_value_) {
                    spirit::traits::assign_to(this->get_first(), end_, value_);
                    has_value_ = true;
                }
                return value_;
            }
            template <typename Value>
            void set_value(Value const& val)
            {
                value_ = val;
                has_value_ = true;
            }
            void set_end(Iterator const& it)
            {
                end_ = it;
            }
            bool has_value() const { return has_value_; }
            void reset_value() { has_value_ = false; }

        protected:
            semantic_actions_type const& actions_;
            Iterator hold_;     // iterator needed to support lex::more()
            Iterator end_;      // iterator pointing to end of matched token
            mutable token_value_type value_;  // token value to use
            mutable bool has_value_;    // 'true' if value_ is valid
            bool has_hold_;     // 'true' if hold_ is valid

            // silence MSVC warning C4512: assignment operator could not be generated
            BOOST_DELETED_FUNCTION(data& operator= (data const&))
        };
    }
}}}}

#endif


/* functor_data.hpp
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
*/