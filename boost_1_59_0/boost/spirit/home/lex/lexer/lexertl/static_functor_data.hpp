//  Copyright (c) 2001-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_LEX_LEXER_STATIC_FUNCTOR_DATA_FEB_10_2008_0755PM)
#define BOOST_SPIRIT_LEX_LEXER_STATIC_FUNCTOR_DATA_FEB_10_2008_0755PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/detail/lexer/generator.hpp>
#include <boost/spirit/home/support/detail/lexer/rules.hpp>
#include <boost/spirit/home/support/detail/lexer/state_machine.hpp>
#include <boost/spirit/home/lex/lexer/lexertl/iterator_tokenizer.hpp>
#include <boost/spirit/home/lex/lexer/lexertl/semantic_action_data.hpp>
#include <boost/spirit/home/lex/lexer/lexertl/wrap_action.hpp>
#include <boost/spirit/home/support/assert_msg.hpp>
#include <boost/mpl/bool.hpp>
#include <iterator> // for std::iterator_traits

namespace boost { namespace spirit { namespace lex { namespace lexertl
{ 
    namespace detail
    {
        ///////////////////////////////////////////////////////////////////////
        template <typename Char>
        inline bool zstr_compare(Char const* s1, Char const* s2)
        {
            for (; *s1 || *s2; ++s1, ++s2)
                if (*s1 != *s2)
                    return false;
            return true;
        }

        template <typename Char, typename F>
        inline std::size_t get_state_id(Char const* state, F f
          , std::size_t numstates)
        {
            for (std::size_t i = 0; i < numstates; ++i)
            {
                if (zstr_compare(f(i), state))
                    return i;
            }
            return boost::lexer::npos;
        }

        ///////////////////////////////////////////////////////////////////////
        template <typename Iterator, typename HasActors, typename HasState
          , typename TokenValue>
        class static_data;    // no default specialization

        ///////////////////////////////////////////////////////////////////////
        //  doesn't support no state and no actors
        template <typename Iterator, typename TokenValue>
        class static_data<Iterator, mpl::false_, mpl::false_, TokenValue>
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
            typedef detail::wrap_action<unused_type, Iterator, static_data
              , std::size_t> wrap_action_type;
 
            typedef std::size_t (*next_token_functor)(std::size_t&, 
                bool&, Iterator&, Iterator const&, std::size_t&);
            typedef char_type const* (*get_state_name_type)(std::size_t);

            // initialize the shared data 
            template <typename IterData>
            static_data (IterData const& data, Iterator& first
                  , Iterator const& last)
              : first_(first), last_(last) 
              , next_token_(data.next_)
              , get_state_name_(data.get_state_name_)
              , bol_(data.bol_) {}

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
            char_type const* get_state_name() const 
            { 
                return get_state_name_(0); 
            }
            std::size_t get_state_id(char_type const*) const 
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

                std::size_t state = 0;
                return next_token_(state, bol_, end, last_, unique_id);
            }

            // nothing to invoke, so this is empty
            BOOST_SCOPED_ENUM(pass_flags) invoke_actions(std::size_t
              , std::size_t, std::size_t, Iterator const&) 
            {
                return pass_flags::pass_normal;    // always accept
            }

            std::size_t get_state() const { return 0; }
            void set_state(std::size_t) {}

            void set_end(Iterator const&) {}

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

            next_token_functor next_token_;
            get_state_name_type get_state_name_;

            bool bol_;      // helper storing whether last character was \n

            // silence MSVC warning C4512: assignment operator could not be generated
            BOOST_DELETED_FUNCTION(static_data& operator= (static_data const&))
        };

        ///////////////////////////////////////////////////////////////////////
        //  doesn't support lexer semantic actions, but supports state
        template <typename Iterator, typename TokenValue>
        class static_data<Iterator, mpl::false_, mpl::true_, TokenValue>
          : public static_data<Iterator, mpl::false_, mpl::false_, TokenValue>
        {
        protected:
            typedef static_data<Iterator, mpl::false_, mpl::false_, TokenValue> base_type;
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
            static_data (IterData const& data, Iterator& first
                  , Iterator const& last)
              : base_type(data, first, last), state_(0)
              , num_states_(data.num_states_) {}

            // The following functions are used by the implementation of the 
            // placeholder '_state'.
            void set_state_name (char_type const* new_state) 
            { 
                std::size_t state_id = lexertl::detail::get_state_id(new_state
                  , this->get_state_name_, num_states_);

                // if the following assertion fires you've probably been using 
                // a lexer state name which was not defined in your token 
                // definition
                BOOST_ASSERT(state_id != boost::lexer::npos);

                if (state_id != boost::lexer::npos)
                    state_ = state_id;
            }
            char_type const* get_state_name() const
            {
                return this->get_state_name_(state_);
            }
            std::size_t get_state_id(char_type const* state) const 
            { 
                return lexertl::detail::get_state_id(state
                  , this->get_state_name_, num_states_); 
            }

            // the functions next() and get_state() are used by the functor 
            // implementation below

            // The function next() tries to match the next token from the 
            // underlying input sequence. 
            std::size_t next(Iterator& end, std::size_t& unique_id, bool& prev_bol)
            {
                prev_bol = this->bol_;
                return this->next_token_(state_, this->bol_, end, this->last_
                  , unique_id);
            }

            std::size_t& get_state() { return state_; }
            void set_state(std::size_t state) { state_ = state; }

        protected:
            std::size_t state_;
            std::size_t num_states_;

            // silence MSVC warning C4512: assignment operator could not be generated
            BOOST_DELETED_FUNCTION(static_data& operator= (static_data const&))
        };

        ///////////////////////////////////////////////////////////////////////
        //  does support actors, but may have no state
        template <typename Iterator, typename HasState, typename TokenValue>
        class static_data<Iterator, mpl::true_, HasState, TokenValue> 
          : public static_data<Iterator, mpl::false_, HasState, TokenValue>
        {
        public:
            typedef semantic_actions<Iterator, HasState, static_data>
                semantic_actions_type;

        protected:
            typedef static_data<Iterator, mpl::false_, HasState, TokenValue> 
                base_type;
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
              , Iterator, static_data, std::size_t> wrap_action_type;

            template <typename IterData>
            static_data (IterData const& data, Iterator& first
                  , Iterator const& last)
              : base_type(data, first, last)
              , actions_(data.actions_), hold_()
              , value_(iterator_range<Iterator>(first, last))
              , has_value_(false)
              , has_hold_(false)
            {}

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

                return id == this->next_token_(
                    state, bol, end, this->get_eoi(), unique_id);
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
            BOOST_DELETED_FUNCTION(static_data& operator= (static_data const&))
        };

        ///////////////////////////////////////////////////////////////////////
        //  does support lexer semantic actions, may support state, is used for
        //  position_token exposing exactly one type
        template <typename Iterator, typename HasState, typename TokenValue>
        class static_data<Iterator, mpl::true_, HasState, boost::optional<TokenValue> > 
          : public static_data<Iterator, mpl::false_, HasState, TokenValue>
        {
        public:
            typedef semantic_actions<Iterator, HasState, static_data> 
                semantic_actions_type;

        protected:
            typedef static_data<Iterator, mpl::false_, HasState, TokenValue> 
                base_type;
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
              , Iterator, static_data, std::size_t> wrap_action_type;

            template <typename IterData>
            static_data (IterData const& data_, Iterator& first, Iterator const& last)
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

                return id == this->next_token_(
                    state, bol, end, this->get_eoi(), unique_id);
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
            BOOST_DELETED_FUNCTION(static_data& operator= (static_data const&))
        };
    }
}}}}

#endif

/* static_functor_data.hpp
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
*/