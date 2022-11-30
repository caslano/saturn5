//  Copyright (c) 2001-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_LEX_TOKEN_DEF_MAR_13_2007_0145PM)
#define BOOST_SPIRIT_LEX_TOKEN_DEF_MAR_13_2007_0145PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/support/argument.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/support/handles_container.hpp>
#include <boost/spirit/home/qi/parser.hpp>
#include <boost/spirit/home/qi/skip_over.hpp>
#include <boost/spirit/home/qi/detail/construct.hpp>
#include <boost/spirit/home/qi/detail/assign_to.hpp>
#include <boost/spirit/home/lex/reference.hpp>
#include <boost/spirit/home/lex/lexer_type.hpp>
#include <boost/spirit/home/lex/lexer/terminals.hpp>

#include <boost/fusion/include/vector.hpp>
#include <boost/mpl/if.hpp>
#include <boost/proto/extends.hpp>
#include <boost/proto/traits.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/variant.hpp>

#include <iterator> // for std::iterator_traits
#include <string>
#include <cstdlib>

#if defined(BOOST_MSVC)
# pragma warning(push)
# pragma warning(disable: 4355) // 'this' : used in base member initializer list warning
#endif

namespace boost { namespace spirit { namespace lex
{
    ///////////////////////////////////////////////////////////////////////////
    //  This component represents a token definition
    ///////////////////////////////////////////////////////////////////////////
    template<typename Attribute = unused_type
      , typename Char = char
      , typename Idtype = std::size_t>
    struct token_def
      : proto::extends<
            typename proto::terminal<
                lex::reference<token_def<Attribute, Char, Idtype> const, Idtype> 
            >::type
          , token_def<Attribute, Char, Idtype> >
      , qi::parser<token_def<Attribute, Char, Idtype> >
      , lex::lexer_type<token_def<Attribute, Char, Idtype> >
    {
    private:
        // initialize proto base class
        typedef lex::reference<token_def const, Idtype> reference_;
        typedef typename proto::terminal<reference_>::type terminal_type;
        typedef proto::extends<terminal_type, token_def> proto_base_type;

        static std::size_t const all_states_id = static_cast<std::size_t>(-2);

    public:
        // Qi interface: meta-function calculating parser return type
        template <typename Context, typename Iterator>
        struct attribute
        {
            //  The return value of the token_def is either the specified 
            //  attribute type, or the pair of iterators from the match of the 
            //  corresponding token (if no attribute type has been specified),
            //  or unused_type (if omit has been specified).
            typedef typename Iterator::base_iterator_type iterator_type;
            typedef typename mpl::if_<
                traits::not_is_unused<Attribute>
              , typename mpl::if_<
                    is_same<Attribute, lex::omit>, unused_type, Attribute
                >::type
              , iterator_range<iterator_type>
            >::type type;
        };

    public:
        // Qi interface: parse functionality
        template <typename Iterator, typename Context
          , typename Skipper, typename Attribute_>
        bool parse(Iterator& first, Iterator const& last
          , Context& /*context*/, Skipper const& skipper
          , Attribute_& attr) const
        {
            qi::skip_over(first, last, skipper);   // always do a pre-skip

            if (first != last) {
                typedef typename 
                    std::iterator_traits<Iterator>::value_type 
                token_type;

                //  If the following assertion fires you probably forgot to  
                //  associate this token definition with a lexer instance.
                BOOST_ASSERT(std::size_t(~0) != token_state_);

                token_type const& t = *first;
                if (token_id_ == t.id() && 
                    (all_states_id == token_state_ || token_state_ == t.state())) 
                {
                    spirit::traits::assign_to(t, attr);
                    ++first;
                    return true;
                }
            }
            return false;
        }

        template <typename Context>
        info what(Context& /*context*/) const
        {
            if (0 == def_.which()) 
                return info("token_def", boost::get<string_type>(def_));

            return info("token_def", boost::get<char_type>(def_));
        }

        ///////////////////////////////////////////////////////////////////////
        // Lex interface: collect token definitions and put it into the 
        // provided lexer def
        template <typename LexerDef, typename String>
        void collect(LexerDef& lexdef, String const& state
          , String const& targetstate) const
        {
            std::size_t state_id = lexdef.add_state(state.c_str());

            // If the following assertion fires you are probably trying to use 
            // a single token_def instance in more than one lexer state. This 
            // is not possible. Please create a separate token_def instance 
            // from the same regular expression for each lexer state it needs 
            // to be associated with.
            BOOST_ASSERT(
                (std::size_t(~0) == token_state_ || state_id == token_state_) &&
                "Can't use single token_def with more than one lexer state");

            char_type const* target = targetstate.empty() ? 0 : targetstate.c_str();
            if (target)
                lexdef.add_state(target);

            token_state_ = state_id;
            if (0 == token_id_)
                token_id_ = lexdef.get_next_id();

            if (0 == def_.which()) {
                unique_id_ = lexdef.add_token(state.c_str()
                  , boost::get<string_type>(def_), token_id_, target);
            }
            else {
                unique_id_ = lexdef.add_token(state.c_str()
                  , boost::get<char_type>(def_), token_id_, target);
            }
        }

        template <typename LexerDef>
        void add_actions(LexerDef&) const {}

    public:
        typedef Char char_type;
        typedef Idtype id_type;
        typedef std::basic_string<char_type> string_type;

        // Lex interface: constructing token definitions
        token_def() 
          : proto_base_type(terminal_type::make(reference_(*this)))
          , def_('\0'), token_id_()
          , unique_id_(std::size_t(~0)), token_state_(std::size_t(~0)) {}

        token_def(token_def const& rhs) 
          : proto_base_type(terminal_type::make(reference_(*this)))
          , def_(rhs.def_), token_id_(rhs.token_id_)
          , unique_id_(rhs.unique_id_), token_state_(rhs.token_state_) {}

        explicit token_def(char_type def_, Idtype id_ = Idtype())
          : proto_base_type(terminal_type::make(reference_(*this)))
          , def_(def_)
          , token_id_(Idtype() == id_ ? Idtype(def_) : id_)
          , unique_id_(std::size_t(~0)), token_state_(std::size_t(~0)) {}

        explicit token_def(string_type const& def_, Idtype id_ = Idtype())
          : proto_base_type(terminal_type::make(reference_(*this)))
          , def_(def_), token_id_(id_)
          , unique_id_(std::size_t(~0)), token_state_(std::size_t(~0)) {}

        template <typename String>
        token_def& operator= (String const& definition)
        {
            def_ = definition;
            token_id_ = Idtype();
            unique_id_ = std::size_t(~0);
            token_state_ = std::size_t(~0);
            return *this;
        }
        token_def& operator= (token_def const& rhs)
        {
            def_ = rhs.def_;
            token_id_ = rhs.token_id_;
            unique_id_ = rhs.unique_id_;
            token_state_ = rhs.token_state_;
            return *this;
        }

        // general accessors 
        Idtype const& id() const { return token_id_; }
        void id(Idtype const& id) { token_id_ = id; }
        std::size_t unique_id() const { return unique_id_; }

        string_type definition() const 
        { 
            return (0 == def_.which()) ? 
                boost::get<string_type>(def_) : 
                string_type(1, boost::get<char_type>(def_));
        }
        std::size_t state() const { return token_state_; }

    private:
        variant<string_type, char_type> def_;
        mutable Idtype token_id_;
        mutable std::size_t unique_id_;
        mutable std::size_t token_state_;
    };
}}}

namespace boost { namespace spirit { namespace traits
{
    ///////////////////////////////////////////////////////////////////////////
    template<typename Attribute, typename Char, typename Idtype
      , typename Attr, typename Context, typename Iterator>
    struct handles_container<
            lex::token_def<Attribute, Char, Idtype>, Attr, Context, Iterator>
      : traits::is_container<
            typename attribute_of<
                lex::token_def<Attribute, Char, Idtype>, Context, Iterator
            >::type>
    {};
}}}

#if defined(BOOST_MSVC)
# pragma warning(pop)
#endif

#endif

/* token_def.hpp
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
*/