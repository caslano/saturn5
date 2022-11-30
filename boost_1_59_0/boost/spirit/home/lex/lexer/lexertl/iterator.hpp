//  Copyright (c) 2001-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_LEX_LEXER_ITERATOR_MAR_16_2007_0353PM)
#define BOOST_SPIRIT_LEX_LEXER_ITERATOR_MAR_16_2007_0353PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/multi_pass_wrapper.hpp>
#if defined(BOOST_SPIRIT_DEBUG)
#include <boost/spirit/home/support/iterators/detail/buf_id_check_policy.hpp>
#else
#include <boost/spirit/home/support/iterators/detail/no_check_policy.hpp>
#endif
#include <boost/spirit/home/support/iterators/detail/split_functor_input_policy.hpp>
#include <boost/spirit/home/support/iterators/detail/ref_counted_policy.hpp>
#include <boost/spirit/home/support/iterators/detail/split_std_deque_policy.hpp>
#include <boost/spirit/home/support/iterators/multi_pass.hpp>

namespace boost { namespace spirit { namespace lex { namespace lexertl
{ 
    ///////////////////////////////////////////////////////////////////////////
    template <typename FunctorData>
    struct make_multi_pass
    {
        // Divide the given functor type into its components (unique and 
        // shared) and build a std::pair from these parts
        typedef std::pair<typename FunctorData::unique
          , typename FunctorData::shared> functor_data_type;

        // This is the result type returned from the iterator
        typedef typename FunctorData::result_type result_type;

        // Compose the multi_pass iterator policy type from the appropriate 
        // policies
        typedef iterator_policies::split_functor_input input_policy;
        typedef iterator_policies::ref_counted ownership_policy;
#if defined(BOOST_SPIRIT_DEBUG)
        typedef iterator_policies::buf_id_check check_policy;
#else
        typedef iterator_policies::no_check check_policy;
#endif
        typedef iterator_policies::split_std_deque storage_policy;

        typedef iterator_policies::default_policy<
                ownership_policy, check_policy, input_policy, storage_policy>
            policy_type;

        // Compose the multi_pass iterator from the policy
        typedef spirit::multi_pass<functor_data_type, policy_type> type;
    };

    ///////////////////////////////////////////////////////////////////////////
    //  lexer_iterator exposes an iterator for a lexertl based dfa (lexer) 
    //  The template parameters have the same semantics as described for the
    //  functor above.
    ///////////////////////////////////////////////////////////////////////////
    template <typename Functor>
    class iterator : public make_multi_pass<Functor>::type
    {
    public:
        typedef typename Functor::unique unique_functor_type;
        typedef typename Functor::shared shared_functor_type;

        typedef typename Functor::iterator_type base_iterator_type;
        typedef typename Functor::result_type token_type;

    private:
        typedef typename make_multi_pass<Functor>::functor_data_type 
            functor_type;
        typedef typename make_multi_pass<Functor>::type base_type;
        typedef typename Functor::char_type char_type;

    public:
        // create a new iterator encapsulating the lexer object to be used
        // for tokenization
        template <typename IteratorData>
        iterator(IteratorData const& iterdata_, base_iterator_type& first
              , base_iterator_type const& last, char_type const* state = 0)
          : base_type(functor_type(unique_functor_type()
              , shared_functor_type(iterdata_, first, last))) 
        {
            set_state(map_state(state));
        }

        // create an end iterator usable for end of range checking
        iterator() {}

        // (wash): < mgaunard> T it; T it2 = ++it; doesn't ocmpile
        //         < mgaunard> this gets fixed by adding
        iterator(const base_type& base)
          : base_type(base) { }

        // set the new required state for the underlying lexer object
        std::size_t set_state(std::size_t state)
        {
            return unique_functor_type::set_state(*this, state);
        }

        // get the current state for the underlying lexer object
        std::size_t get_state()
        {
            return unique_functor_type::get_state(*this);
        }

        // map the given state name to a corresponding state id as understood
        // by the underlying lexer object
        std::size_t map_state(char_type const* statename)
        {
            return (0 != statename) 
              ? unique_functor_type::map_state(*this, statename)
              : 0;
        }
    };
}}

namespace traits 
{ 
    template <typename Functor>
    struct is_multi_pass<spirit::lex::lexertl::iterator<Functor> >
      : mpl::true_ {};

    template <typename Functor>
    void clear_queue(spirit::lex::lexertl::iterator<Functor> & mp
        , BOOST_SCOPED_ENUM(traits::clear_mode) mode)
    {
        mp.clear_queue(mode);
    }

    template <typename Functor>
    void inhibit_clear_queue(spirit::lex::lexertl::iterator<Functor>& mp, bool flag)
    {
        mp.inhibit_clear_queue(flag);
    }

    template <typename Functor> 
    bool inhibit_clear_queue(spirit::lex::lexertl::iterator<Functor>& mp)
    {
        return mp.inhibit_clear_queue();
    }
}

}}

#endif

/* iterator.hpp
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
*/