//  Copyright (c) 2001-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_LEX_TOKEN_FEB_10_2008_0751PM)
#define BOOST_SPIRIT_LEX_TOKEN_FEB_10_2008_0751PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/spirit/home/qi/detail/assign_to.hpp>
#include <boost/spirit/home/support/attributes.hpp>
#include <boost/spirit/home/support/argument.hpp>
#include <boost/spirit/home/support/detail/lexer/generator.hpp>
#include <boost/spirit/home/support/detail/lexer/rules.hpp>
#include <boost/spirit/home/support/detail/lexer/consts.hpp>
#include <boost/spirit/home/support/utree/utree_traits_fwd.hpp>
#include <boost/spirit/home/lex/lexer/terminals.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/value_at.hpp>
#include <boost/variant.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/range/iterator_range_core.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/make_unsigned.hpp>
#include <boost/static_assert.hpp>

#if defined(BOOST_SPIRIT_DEBUG)
#include <iosfwd>
#endif

namespace boost { namespace spirit { namespace lex { namespace lexertl
{ 
    ///////////////////////////////////////////////////////////////////////////
    //
    //  The token is the type of the objects returned by default by the 
    //  iterator.
    //
    //    template parameters:
    //        Iterator        The type of the iterator used to access the
    //                        underlying character stream.
    //        AttributeTypes  A mpl sequence containing the types of all 
    //                        required different token values to be supported 
    //                        by this token type.
    //        HasState        A mpl::bool_ indicating, whether this token type
    //                        should support lexer states.
    //        Idtype          The type to use for the token id (defaults to 
    //                        std::size_t).
    //
    //  It is possible to use other token types with the spirit::lex 
    //  framework as well. If you plan to use a different type as your token 
    //  type, you'll need to expose the following things from your token type 
    //  to make it compatible with spirit::lex:
    //
    //    typedefs
    //        iterator_type   The type of the iterator used to access the
    //                        underlying character stream.
    //
    //        id_type         The type of the token id used.
    //
    //    methods
    //        default constructor
    //                        This should initialize the token as an end of 
    //                        input token.
    //        constructors    The prototype of the other required 
    //                        constructors should be:
    //
    //              token(int)
    //                        This constructor should initialize the token as 
    //                        an invalid token (not carrying any specific 
    //                        values)
    //
    //              where:  the int is used as a tag only and its value is 
    //                      ignored
    //
    //                        and:
    //
    //              token(Idtype id, std::size_t state, 
    //                    iterator_type first, iterator_type last);
    //
    //              where:  id:           token id
    //                      state:        lexer state this token was matched in
    //                      first, last:  pair of iterators marking the matched 
    //                                    range in the underlying input stream 
    //
    //        accessors
    //              id()      return the token id of the matched input sequence
    //              id(newid) set the token id of the token instance
    //
    //              state()   return the lexer state this token was matched in
    //
    //              value()   return the token value
    //
    //  Additionally, you will have to implement a couple of helper functions
    //  in the same namespace as the token type: a comparison operator==() to 
    //  compare your token instances, a token_is_valid() function and different 
    //  specializations of the Spirit customization point 
    //  assign_to_attribute_from_value as shown below.
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename Iterator = char const*
      , typename AttributeTypes = mpl::vector0<>
      , typename HasState = mpl::true_
      , typename Idtype = std::size_t> 
    struct token;

    ///////////////////////////////////////////////////////////////////////////
    //  This specialization of the token type doesn't contain any item data and
    //  doesn't support working with lexer states.
    ///////////////////////////////////////////////////////////////////////////
    template <typename Iterator, typename Idtype>
    struct token<Iterator, lex::omit, mpl::false_, Idtype>
    {
        typedef Iterator iterator_type;
        typedef mpl::false_ has_state;
        typedef Idtype id_type;
        typedef unused_type token_value_type;
        typedef typename make_unsigned<id_type>::type uid_type;

        //  default constructed tokens correspond to EOI tokens
        token() : id_(boost::lexer::npos) {}

        //  construct an invalid token
        explicit token(int) : id_(0) {}

        token(id_type id, std::size_t) : id_(id) {}

        token(id_type id, std::size_t, token_value_type)
          : id_(id) {}

        token_value_type& value() { static token_value_type u; return u; }
        token_value_type const& value() const { return unused; }

#if defined(BOOST_SPIRIT_DEBUG)
        token(id_type id, std::size_t, Iterator const& first
              , Iterator const& last)
          : matched_(first, last)
          , id_(id) {}
#else
        token(id_type id, std::size_t, Iterator const&, Iterator const&)
          : id_(id) {}
#endif

        //  this default conversion operator is needed to allow the direct 
        //  usage of tokens in conjunction with the primitive parsers defined 
        //  in Qi
        operator id_type() const { return id_type(uid_type(id_)); }

        //  Retrieve or set the token id of this token instance. 
        id_type id() const { return id_type(uid_type(id_)); }
        void id(id_type newid) { id_ = uid_type(newid); }

        std::size_t state() const { return 0; }   // always '0' (INITIAL state)

        bool is_valid() const 
        { 
            return 0 != id_ && boost::lexer::npos != id_; 
        }

#if defined(BOOST_SPIRIT_DEBUG)
#if BOOST_WORKAROUND(BOOST_MSVC, == 1600)
        // workaround for MSVC10 which has problems copying a default 
        // constructed iterator_range
        token& operator= (token const& rhs)
        {
            if (this != &rhs) 
            {
                id_ = rhs.id_;
                if (is_valid()) 
                    matched_ = rhs.matched_;
            }
            return *this;
        }
#endif
        std::pair<Iterator, Iterator> matched_;
#endif

    protected:
        std::size_t id_;            // token id, 0 if nothing has been matched
    };

#if defined(BOOST_SPIRIT_DEBUG)
    template <typename Char, typename Traits, typename Iterator
      , typename AttributeTypes, typename HasState, typename Idtype> 
    inline std::basic_ostream<Char, Traits>& 
    operator<< (std::basic_ostream<Char, Traits>& os
      , token<Iterator, AttributeTypes, HasState, Idtype> const& t)
    {
        if (t.is_valid()) {
            Iterator end = t.matched_.second;
            for (Iterator it = t.matched_.first; it != end; ++it)
                os << *it;
        }
        else {
            os << "<invalid token>";
        }
        return os;
    }
#endif

    ///////////////////////////////////////////////////////////////////////////
    //  This specialization of the token type doesn't contain any item data but
    //  supports working with lexer states.
    ///////////////////////////////////////////////////////////////////////////
    template <typename Iterator, typename Idtype>
    struct token<Iterator, lex::omit, mpl::true_, Idtype>
      : token<Iterator, lex::omit, mpl::false_, Idtype>
    {
    private:
        typedef token<Iterator, lex::omit, mpl::false_, Idtype> base_type;

    public:
        typedef typename base_type::id_type id_type;
        typedef Iterator iterator_type;
        typedef mpl::true_ has_state;
        typedef unused_type token_value_type;

        //  default constructed tokens correspond to EOI tokens
        token() : state_(boost::lexer::npos) {}

        //  construct an invalid token
        explicit token(int) : base_type(0), state_(boost::lexer::npos) {}

        token(id_type id, std::size_t state)
          : base_type(id, boost::lexer::npos), state_(state) {}

        token(id_type id, std::size_t state, token_value_type)
          : base_type(id, boost::lexer::npos, unused)
          , state_(state) {}

        token(id_type id, std::size_t state
              , Iterator const& first, Iterator const& last)
          : base_type(id, boost::lexer::npos, first, last)
          , state_(state) {}

        std::size_t state() const { return state_; }

#if defined(BOOST_SPIRIT_DEBUG) && BOOST_WORKAROUND(BOOST_MSVC, == 1600)
        // workaround for MSVC10 which has problems copying a default 
        // constructed iterator_range
        token& operator= (token const& rhs)
        {
            if (this != &rhs) 
            {
                this->base_type::operator=(static_cast<base_type const&>(rhs));
                state_ = rhs.state_;
            }
            return *this;
        }
#endif

    protected:
        std::size_t state_;      // lexer state this token was matched in
    };

    ///////////////////////////////////////////////////////////////////////////
    //  The generic version of the token type derives from the 
    //  specialization above and adds a single data member holding the item 
    //  data carried by the token instance.
    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        ///////////////////////////////////////////////////////////////////////
        //  Meta-function to calculate the type of the variant data item to be 
        //  stored with each token instance.
        //
        //  Note: The iterator pair needs to be the first type in the list of 
        //        types supported by the generated variant type (this is being 
        //        used to identify whether the stored data item in a particular 
        //        token instance needs to be converted from the pair of 
        //        iterators (see the first of the assign_to_attribute_from_value 
        //        specializations below).
        ///////////////////////////////////////////////////////////////////////
        template <typename IteratorPair, typename AttributeTypes>
        struct token_value_typesequence
        {
            typedef typename mpl::insert<
                AttributeTypes
              , typename mpl::begin<AttributeTypes>::type
              , IteratorPair
            >::type sequence_type;
            typedef typename make_variant_over<sequence_type>::type type;
        };

        ///////////////////////////////////////////////////////////////////////
        //  The type of the data item stored with a token instance is defined 
        //  by the template parameter 'AttributeTypes' and may be:
        //  
        //     lex::omit:         no data item is stored with the token 
        //                        instance (this is handled by the 
        //                        specializations of the token class
        //                        below)
        //     mpl::vector0<>:    each token instance stores a pair of 
        //                        iterators pointing to the matched input 
        //                        sequence
        //     mpl::vector<...>:  each token instance stores a variant being 
        //                        able to store the pair of iterators pointing 
        //                        to the matched input sequence, or any of the 
        //                        types a specified in the mpl::vector<>
        //
        //  All this is done to ensure the token type is as small (in terms 
        //  of its byte-size) as possible.
        ///////////////////////////////////////////////////////////////////////
        template <typename IteratorPair, typename AttributeTypes>
        struct token_value_type
          : mpl::eval_if<
                mpl::or_<
                    is_same<AttributeTypes, mpl::vector0<> >
                  , is_same<AttributeTypes, mpl::vector<> > >
              , mpl::identity<IteratorPair>
              , token_value_typesequence<IteratorPair, AttributeTypes> >
        {};
    }

    template <typename Iterator, typename AttributeTypes, typename HasState
      , typename Idtype>
    struct token : token<Iterator, lex::omit, HasState, Idtype>
    {
    private: // precondition assertions
        BOOST_STATIC_ASSERT((mpl::is_sequence<AttributeTypes>::value || 
                            is_same<AttributeTypes, lex::omit>::value));
        typedef token<Iterator, lex::omit, HasState, Idtype> base_type;

    protected: 
        //  If no additional token value types are given, the token will 
        //  hold the plain pair of iterators pointing to the matched range
        //  in the underlying input sequence. Otherwise the token value is 
        //  stored as a variant and will again hold the pair of iterators but
        //  is able to hold any of the given data types as well. The conversion 
        //  from the iterator pair to the required data type is done when it is
        //  accessed for the first time.
        typedef iterator_range<Iterator> iterpair_type;

    public:
        typedef typename base_type::id_type id_type;
        typedef typename detail::token_value_type<
            iterpair_type, AttributeTypes
        >::type token_value_type;

        typedef Iterator iterator_type;

        //  default constructed tokens correspond to EOI tokens
        token() : value_(iterpair_type(iterator_type(), iterator_type())) {}

        //  construct an invalid token
        explicit token(int)
          : base_type(0)
          , value_(iterpair_type(iterator_type(), iterator_type())) {}

        token(id_type id, std::size_t state, token_value_type const& value)
          : base_type(id, state, value)
          , value_(value) {}

        token(id_type id, std::size_t state, Iterator const& first
              , Iterator const& last)
          : base_type(id, state, first, last)
          , value_(iterpair_type(first, last)) {}

        token_value_type& value() { return value_; }
        token_value_type const& value() const { return value_; }

#if BOOST_WORKAROUND(BOOST_MSVC, == 1600)
        // workaround for MSVC10 which has problems copying a default 
        // constructed iterator_range
        token& operator= (token const& rhs)
        {
            if (this != &rhs) 
            {
                this->base_type::operator=(static_cast<base_type const&>(rhs));
                if (this->is_valid()) 
                    value_ = rhs.value_;
            }
            return *this;
        }
#endif

    protected:
        token_value_type value_; // token value, by default a pair of iterators
    };

    ///////////////////////////////////////////////////////////////////////////
    //  tokens are considered equal, if their id's match (these are unique)
    template <typename Iterator, typename AttributeTypes, typename HasState
      , typename Idtype>
    inline bool 
    operator== (token<Iterator, AttributeTypes, HasState, Idtype> const& lhs, 
                token<Iterator, AttributeTypes, HasState, Idtype> const& rhs)
    {
        return lhs.id() == rhs.id();
    }

    ///////////////////////////////////////////////////////////////////////////
    //  This overload is needed by the multi_pass/functor_input_policy to 
    //  validate a token instance. It has to be defined in the same namespace 
    //  as the token class itself to allow ADL to find it.
    ///////////////////////////////////////////////////////////////////////////
    template <typename Iterator, typename AttributeTypes, typename HasState
      , typename Idtype>
    inline bool 
    token_is_valid(token<Iterator, AttributeTypes, HasState, Idtype> const& t)
    {
        return t.is_valid();
    }
}}}}

namespace boost { namespace spirit { namespace traits
{
    ///////////////////////////////////////////////////////////////////////////
    //  We have to provide specializations for the customization point
    //  assign_to_attribute_from_value allowing to extract the needed value 
    //  from the token. 
    ///////////////////////////////////////////////////////////////////////////

    //  This is called from the parse function of token_def if the token_def
    //  has been defined to carry a special attribute type
    template <typename Attribute, typename Iterator, typename AttributeTypes
      , typename HasState, typename Idtype>
    struct assign_to_attribute_from_value<Attribute
      , lex::lexertl::token<Iterator, AttributeTypes, HasState, Idtype> >
    {
        static void 
        call(lex::lexertl::token<Iterator, AttributeTypes, HasState, Idtype> const& t
          , Attribute& attr)
        {
        //  The goal of this function is to avoid the conversion of the pair of
        //  iterators (to the matched character sequence) into the token value 
        //  of the required type being done more than once. For this purpose it 
        //  checks whether the stored value type is still the default one (pair 
        //  of iterators) and if yes, replaces the pair of iterators with the 
        //  converted value to be returned from subsequent calls.

            if (0 == t.value().which()) {
            //  first access to the token value
                typedef iterator_range<Iterator> iterpair_type;
                iterpair_type const& ip = boost::get<iterpair_type>(t.value());

            // Interestingly enough we use the assign_to() framework defined in 
            // Spirit.Qi allowing to convert the pair of iterators to almost any 
            // required type (assign_to(), if available, uses the standard Spirit 
            // parsers to do the conversion).
                spirit::traits::assign_to(ip.begin(), ip.end(), attr);

            //  If you get an error during the compilation of the following 
            //  assignment expression, you probably forgot to list one or more 
            //  types used as token value types (in your token_def<...> 
            //  definitions) in your definition of the token class. I.e. any token 
            //  value type used for a token_def<...> definition has to be listed 
            //  during the declaration of the token type to use. For instance let's 
            //  assume we have two token_def's:
            //
            //      token_def<int> number; number = "...";
            //      token_def<std::string> identifier; identifier = "...";
            //
            //  Then you'll have to use the following token type definition 
            //  (assuming you are using the token class):
            //
            //      typedef mpl::vector<int, std::string> token_values;
            //      typedef token<base_iter_type, token_values> token_type;
            //
            //  where: base_iter_type is the iterator type used to expose the 
            //         underlying input stream.
            //
            //  This token_type has to be used as the second template parameter 
            //  to the lexer class:
            //
            //      typedef lexer<base_iter_type, token_type> lexer_type;
            //
            //  again, assuming you're using the lexer<> template for your 
            //  tokenization.

                typedef lex::lexertl::token<
                    Iterator, AttributeTypes, HasState, Idtype> token_type;
                spirit::traits::assign_to(
                    attr, const_cast<token_type&>(t).value());   // re-assign value
            }
            else {
            // reuse the already assigned value
                spirit::traits::assign_to(boost::get<Attribute>(t.value()), attr);
            }
        }
    };

    template <typename Attribute, typename Iterator, typename AttributeTypes
      , typename HasState, typename Idtype>
    struct assign_to_container_from_value<Attribute
          , lex::lexertl::token<Iterator, AttributeTypes, HasState, Idtype> >
      : assign_to_attribute_from_value<Attribute
          , lex::lexertl::token<Iterator, AttributeTypes, HasState, Idtype> >
    {};

    template <typename Iterator, typename AttributeTypes
      , typename HasState, typename Idtype>
    struct assign_to_container_from_value<utree
          , lex::lexertl::token<Iterator, AttributeTypes, HasState, Idtype> >
      : assign_to_attribute_from_value<utree
          , lex::lexertl::token<Iterator, AttributeTypes, HasState, Idtype> >
    {};

    template <typename Iterator>
    struct assign_to_container_from_value<
        iterator_range<Iterator>, iterator_range<Iterator> >
    {
        static void 
        call(iterator_range<Iterator> const& val, iterator_range<Iterator>& attr)
        {
            attr = val;
        }
    };

    //  These are called from the parse function of token_def if the token type
    //  has no special attribute type assigned 
    template <typename Attribute, typename Iterator, typename HasState
      , typename Idtype>
    struct assign_to_attribute_from_value<Attribute
      , lex::lexertl::token<Iterator, mpl::vector0<>, HasState, Idtype> >
    {
        static void 
        call(lex::lexertl::token<Iterator, mpl::vector0<>, HasState, Idtype> const& t
          , Attribute& attr)
        {
            //  The default type returned by the token_def parser component (if 
            //  it has no token value type assigned) is the pair of iterators 
            //  to the matched character sequence.
            spirit::traits::assign_to(t.value().begin(), t.value().end(), attr);
        }
    };

//     template <typename Attribute, typename Iterator, typename HasState
//       , typename Idtype>
//     struct assign_to_container_from_value<Attribute
//           , lex::lexertl::token<Iterator, mpl::vector0<>, HasState, Idtype> >
//       : assign_to_attribute_from_value<Attribute
//           , lex::lexertl::token<Iterator, mpl::vector0<>, HasState, Idtype> >
//     {};

    // same as above but using mpl::vector<> instead of mpl::vector0<>
    template <typename Attribute, typename Iterator, typename HasState
      , typename Idtype>
    struct assign_to_attribute_from_value<Attribute
      , lex::lexertl::token<Iterator, mpl::vector<>, HasState, Idtype> >
    {
        static void 
        call(lex::lexertl::token<Iterator, mpl::vector<>, HasState, Idtype> const& t
          , Attribute& attr)
        {
            //  The default type returned by the token_def parser component (if 
            //  it has no token value type assigned) is the pair of iterators 
            //  to the matched character sequence.
            spirit::traits::assign_to(t.value().begin(), t.value().end(), attr);
        }
    };

//     template <typename Attribute, typename Iterator, typename HasState
//       , typename Idtype>
//     struct assign_to_container_from_value<Attribute
//           , lex::lexertl::token<Iterator, mpl::vector<>, HasState, Idtype> >
//       : assign_to_attribute_from_value<Attribute
//           , lex::lexertl::token<Iterator, mpl::vector<>, HasState, Idtype> >
//     {};

    //  This is called from the parse function of token_def if the token type
    //  has been explicitly omitted (i.e. no attribute value is used), which
    //  essentially means that every attribute gets initialized using default 
    //  constructed values.
    template <typename Attribute, typename Iterator, typename HasState
      , typename Idtype>
    struct assign_to_attribute_from_value<Attribute
      , lex::lexertl::token<Iterator, lex::omit, HasState, Idtype> >
    {
        static void 
        call(lex::lexertl::token<Iterator, lex::omit, HasState, Idtype> const&
          , Attribute&)
        {
            // do nothing
        }
    };

    template <typename Attribute, typename Iterator, typename HasState
      , typename Idtype>
    struct assign_to_container_from_value<Attribute
          , lex::lexertl::token<Iterator, lex::omit, HasState, Idtype> >
      : assign_to_attribute_from_value<Attribute
          , lex::lexertl::token<Iterator, lex::omit, HasState, Idtype> >
    {};

    //  This is called from the parse function of lexer_def_
    template <typename Iterator, typename AttributeTypes, typename HasState
      , typename Idtype_, typename Idtype>
    struct assign_to_attribute_from_value<
        fusion::vector2<Idtype_, iterator_range<Iterator> >
      , lex::lexertl::token<Iterator, AttributeTypes, HasState, Idtype> >
    {
        static void 
        call(lex::lexertl::token<Iterator, AttributeTypes, HasState, Idtype> const& t
          , fusion::vector2<Idtype_, iterator_range<Iterator> >& attr)
        {
            //  The type returned by the lexer_def_ parser components is a 
            //  fusion::vector containing the token id of the matched token 
            //  and the pair of iterators to the matched character sequence.
            typedef iterator_range<Iterator> iterpair_type;
            typedef fusion::vector2<Idtype_, iterator_range<Iterator> > 
                attribute_type;

            iterpair_type const& ip = boost::get<iterpair_type>(t.value());
            attr = attribute_type(t.id(), ip);
        }
    };

    template <typename Iterator, typename AttributeTypes, typename HasState
      , typename Idtype_, typename Idtype>
    struct assign_to_container_from_value<
            fusion::vector2<Idtype_, iterator_range<Iterator> >
          , lex::lexertl::token<Iterator, AttributeTypes, HasState, Idtype> >
      : assign_to_attribute_from_value<
            fusion::vector2<Idtype_, iterator_range<Iterator> >
          , lex::lexertl::token<Iterator, AttributeTypes, HasState, Idtype> >
    {};

    ///////////////////////////////////////////////////////////////////////////
    // Overload debug output for a single token, this integrates lexer tokens 
    // with Qi's simple_trace debug facilities
    template <typename Iterator, typename Attribute, typename HasState
      , typename Idtype>
    struct token_printer_debug<
        lex::lexertl::token<Iterator, Attribute, HasState, Idtype> >
    {
        typedef lex::lexertl::token<Iterator, Attribute, HasState, Idtype> token_type;

        template <typename Out>
        static void print(Out& out, token_type const& val) 
        {
            out << '[';
            spirit::traits::print_token(out, val.value());
            out << ']';
        }
    };
}}}

#endif

/* token.hpp
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
*/