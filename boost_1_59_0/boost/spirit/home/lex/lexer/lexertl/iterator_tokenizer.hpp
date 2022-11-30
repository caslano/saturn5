//  Copyright (c) 2001-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_LEXERTL_ITERATOR_TOKENISER_MARCH_22_2007_0859AM)
#define BOOST_SPIRIT_LEXERTL_ITERATOR_TOKENISER_MARCH_22_2007_0859AM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/detail/lexer/state_machine.hpp>
#include <boost/spirit/home/support/detail/lexer/consts.hpp>
#include <boost/spirit/home/support/detail/lexer/size_t.hpp>
#include <boost/spirit/home/support/detail/lexer/char_traits.hpp>
#include <iterator> // for std::iterator_traits
#include <vector>

namespace boost { namespace spirit { namespace lex { namespace lexertl
{ 
    ///////////////////////////////////////////////////////////////////////////
    template<typename Iterator>
    class basic_iterator_tokeniser
    {
    public:
        typedef std::vector<std::size_t> size_t_vector;
        typedef typename std::iterator_traits<Iterator>::value_type char_type;

        static std::size_t next (
            boost::lexer::basic_state_machine<char_type> const& state_machine_
          , std::size_t &dfa_state_, bool& bol_, Iterator &start_token_
          , Iterator const& end_, std::size_t& unique_id_)
        {
            if (start_token_ == end_) 
            {
                unique_id_ = boost::lexer::npos;
                return 0;
            }

            bool bol = bol_;
            boost::lexer::detail::internals const& internals_ =
                state_machine_.data();

        again:
            std::size_t const* lookup_ = &internals_._lookup[dfa_state_]->
                front ();
            std::size_t dfa_alphabet_ = internals_._dfa_alphabet[dfa_state_];
            std::size_t const* dfa_ = &internals_._dfa[dfa_state_]->front ();

            std::size_t const* ptr_ = dfa_ + dfa_alphabet_;
            Iterator curr_ = start_token_;
            bool end_state_ = *ptr_ != 0;
            std::size_t id_ = *(ptr_ + boost::lexer::id_index);
            std::size_t uid_ = *(ptr_ + boost::lexer::unique_id_index);
            std::size_t end_start_state_ = dfa_state_;
            bool end_bol_ = bol_;
            Iterator end_token_ = start_token_;

            while (curr_ != end_)
            {
                std::size_t const BOL_state_ = ptr_[boost::lexer::bol_index];
                std::size_t const EOL_state_ = ptr_[boost::lexer::eol_index];

                if (BOL_state_ && bol)
                {
                    ptr_ = &dfa_[BOL_state_ * dfa_alphabet_];
                }
                else if (EOL_state_ && *curr_ == '\n')
                {
                    ptr_ = &dfa_[EOL_state_ * dfa_alphabet_];
                }
                else
                {
                    typedef typename 
                        std::iterator_traits<Iterator>::value_type 
                    value_type;
                    typedef typename 
                        boost::lexer::char_traits<value_type>::index_type 
                    index_type;

                    index_type index = 
                        boost::lexer::char_traits<value_type>::call(*curr_++);
                    bol = (index == '\n') ? true : false;
                    std::size_t const state_ = ptr_[
                        lookup_[static_cast<std::size_t>(index)]];

                    if (state_ == 0)
                    {
                        break;
                    }

                    ptr_ = &dfa_[state_ * dfa_alphabet_];
                }

                if (*ptr_)
                {
                    end_state_ = true;
                    id_ = *(ptr_ + boost::lexer::id_index);
                    uid_ = *(ptr_ + boost::lexer::unique_id_index);
                    end_start_state_ = *(ptr_ + boost::lexer::state_index);
                    end_bol_ = bol;
                    end_token_ = curr_;
                }
            }

            std::size_t const EOL_state_ = ptr_[boost::lexer::eol_index];

            if (EOL_state_ && curr_ == end_)
            {
                ptr_ = &dfa_[EOL_state_ * dfa_alphabet_];

                if (*ptr_)
                {
                    end_state_ = true;
                    id_ = *(ptr_ + boost::lexer::id_index);
                    uid_ = *(ptr_ + boost::lexer::unique_id_index);
                    end_start_state_ = *(ptr_ + boost::lexer::state_index);
                    end_bol_ = bol;
                    end_token_ = curr_;
                }
            }

            if (end_state_) {
                // return longest match
                dfa_state_ = end_start_state_;
                start_token_ = end_token_;

                if (id_ == 0)
                {
                    bol = end_bol_;
                    goto again;
                }
                else
                {
                    bol_ = end_bol_;
                }
            }
            else {
                bol_ = (*start_token_ == '\n') ? true : false;
                id_ = boost::lexer::npos;
                uid_ = boost::lexer::npos;
            }

            unique_id_ = uid_;
            return id_;
        }

        ///////////////////////////////////////////////////////////////////////
        static std::size_t next (
            boost::lexer::basic_state_machine<char_type> const& state_machine_
          , bool& bol_, Iterator &start_token_, Iterator const& end_
          , std::size_t& unique_id_)
        {
            if (start_token_ == end_)
            {
                unique_id_ = boost::lexer::npos;
                return 0;
            }

            bool bol = bol_;
            std::size_t const* lookup_ = &state_machine_.data()._lookup[0]->front();
            std::size_t dfa_alphabet_ = state_machine_.data()._dfa_alphabet[0];
            std::size_t const* dfa_ = &state_machine_.data()._dfa[0]->front ();
            std::size_t const* ptr_ = dfa_ + dfa_alphabet_;

            Iterator curr_ = start_token_;
            bool end_state_ = *ptr_ != 0;
            std::size_t id_ = *(ptr_ + boost::lexer::id_index);
            std::size_t uid_ = *(ptr_ + boost::lexer::unique_id_index);
            bool end_bol_ = bol_;
            Iterator end_token_ = start_token_;

            while (curr_ != end_)
            {
                std::size_t const BOL_state_ = ptr_[boost::lexer::bol_index];
                std::size_t const EOL_state_ = ptr_[boost::lexer::eol_index];

                if (BOL_state_ && bol)
                {
                    ptr_ = &dfa_[BOL_state_ * dfa_alphabet_];
                }
                else if (EOL_state_ && *curr_ == '\n')
                {
                    ptr_ = &dfa_[EOL_state_ * dfa_alphabet_];
                }
                else
                {
                    typedef typename 
                        std::iterator_traits<Iterator>::value_type 
                    value_type;
                    typedef typename 
                        boost::lexer::char_traits<value_type>::index_type 
                    index_type;

                    index_type index = 
                        boost::lexer::char_traits<value_type>::call(*curr_++);
                    bol = (index == '\n') ? true : false;
                    std::size_t const state_ = ptr_[
                        lookup_[static_cast<std::size_t>(index)]];

                    if (state_ == 0)
                    {
                        break;
                    }

                    ptr_ = &dfa_[state_ * dfa_alphabet_];
                }

                if (*ptr_)
                {
                    end_state_ = true;
                    id_ = *(ptr_ + boost::lexer::id_index);
                    uid_ = *(ptr_ + boost::lexer::unique_id_index);
                    end_bol_ = bol;
                    end_token_ = curr_;
                }
            }

            std::size_t const EOL_state_ = ptr_[boost::lexer::eol_index];

            if (EOL_state_ && curr_ == end_)
            {
                ptr_ = &dfa_[EOL_state_ * dfa_alphabet_];

                if (*ptr_)
                {
                    end_state_ = true;
                    id_ = *(ptr_ + boost::lexer::id_index);
                    uid_ = *(ptr_ + boost::lexer::unique_id_index);
                    end_bol_ = bol;
                    end_token_ = curr_;
                }
            }

            if (end_state_) {
                // return longest match
                bol_ = end_bol_;
                start_token_ = end_token_;
            }
            else {
                bol_ = *start_token_ == '\n';
                id_ = boost::lexer::npos;
                uid_ = boost::lexer::npos;
            }

            unique_id_ = uid_;
            return id_;
        }
    };

}}}}

#endif

/* iterator_tokenizer.hpp
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
*/