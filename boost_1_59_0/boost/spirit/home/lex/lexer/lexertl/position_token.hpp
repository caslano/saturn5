//  Copyright (c) 2001-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_LEX_POSITION_TOKEN_MAY_13_2011_0846PM)
#define BOOST_SPIRIT_LEX_POSITION_TOKEN_MAY_13_2011_0846PM

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
#include <boost/mpl/vector.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/range/iterator_range_core.hpp>
#include <boost/static_assert.hpp>

#if defined(BOOST_SPIRIT_DEBUG)
#include <iosfwd>
#endif

namespace boost { namespace spirit { namespace lex { namespace lexertl
{ 
    ///////////////////////////////////////////////////////////////////////////
    //
    //  The position_token is the type of the objects returned by the 
    //  iterator if it has been specified while instantiating the lexer object.
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
    struct position_token;

    ///////////////////////////////////////////////////////////////////////////
    //  This specialization of the token type doesn't contain any item data and
    //  doesn't support working with lexer states. Although, like all other
    //  variants of position_token, it carries a pair of iterators marking the
    //  begin and the end of the matched character sequence.
    ///////////////////////////////////////////////////////////////////////////
    template <typename Iterator, typename Idtype>
    struct position_token<Iterator, lex::omit, mpl::false_, Idtype>
    {
        typedef Iterator iterator_type;
        typedef iterator_range<iterator_type> iterpair_type;
        typedef mpl::false_ has_state;
        typedef Idtype id_type;
        typedef unused_type token_value_type;

        //  default constructed tokens correspond to EOI tokens
        position_token() 
          : id_(id_type(boost::lexer::npos)) {}

        //  construct an invalid token
        explicit position_token(int) 
          : id_(id_type(0)) {}

        position_token(id_type id, std::size_t) 
          : id_(id) {}

        position_token(id_type id, std::size_t, token_value_type)
          : id_(id) {}

        position_token(id_type id, std::size_t, Iterator const& first
              , Iterator const& last)
          : id_(id), matched_(first, last) {}

        //  this default conversion operator is needed to allow the direct 
        //  usage of tokens in conjunction with the primitive parsers defined 
        //  in Qi
        operator id_type() const { return id_; }

        //  Retrieve or set the token id of this token instance. 
        id_type id() const { return id_; }
        void id(id_type newid) { id_ = newid; }

        std::size_t state() const { return 0; }   // always '0' (INITIAL state)

        bool is_valid() const 
        { 
            return 0 != id_ && id_type(boost::lexer::npos) != id_; 
        }

        // access the stored iterator range of the matched input sequence
        iterator_type begin() const { return matched_.begin(); }
        iterator_type end() const { return matched_.end(); }

        iterpair_type& matched() { return matched_; }
        iterpair_type const& matched() const { return matched_; }

        token_value_type& value() { static token_value_type u; return u; }
        token_value_type const& value() const { return unused; }

#if BOOST_WORKAROUND(BOOST_MSVC, == 1600)
        // workaround for MSVC10 which has problems copying a default 
        // constructed iterator_range
        position_token& operator= (position_token const& rhs)
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

    protected:
        id_type id_;              // token id, 0 if nothing has been matched
        iterpair_type matched_;   // matched input sequence
    };

#if defined(BOOST_SPIRIT_DEBUG)
    template <typename Char, typename Traits, typename Iterator
      , typename AttributeTypes, typename HasState, typename Idtype> 
    inline std::basic_ostream<Char, Traits>& 
    operator<< (std::basic_ostream<Char, Traits>& os
      , position_token<Iterator, AttributeTypes, HasState, Idtype> const& t)
    {
        if (t.is_valid()) {
            Iterator end = t.end();
            for (Iterator it = t.begin(); it != end; ++it)
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
    struct position_token<Iterator, lex::omit, mpl::true_, Idtype>
      : position_token<Iterator, lex::omit, mpl::false_, Idtype>
    {
    private:
        typedef position_token<Iterator, lex::omit, mpl::false_, Idtype> 
            base_type;

    public:
        typedef typename base_type::id_type id_type;
        typedef Iterator iterator_type;
        typedef mpl::true_ has_state;
        typedef unused_type token_value_type;

        //  default constructed tokens correspond to EOI tokens
        position_token() : state_(boost::lexer::npos) {}

        //  construct an invalid token
        explicit position_token(int) 
          : base_type(0), state_(boost::lexer::npos) {}

        position_token(id_type id, std::size_t state)
          : base_type(id, boost::lexer::npos), state_(state) {}

        position_token(id_type id, std::size_t state, token_value_type)
          : base_type(id, boost::lexer::npos, unused)
          , state_(state) {}

        position_token(id_type id, std::size_t state
              , Iterator const& first, Iterator const& last)
          : base_type(id, boost::lexer::npos, first, last)
          , state_(state) {}

        std::size_t state() const { return state_; }

#if BOOST_WORKAROUND(BOOST_MSVC, == 1600)
        // workaround for MSVC10 which has problems copying a default 
        // constructed iterator_range
        position_token& operator= (position_token const& rhs)
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
    // These specializations for an empty attribute list cause all token 
    // instances to expose as it attribute the iterator_range pointing to the
    // matched input sequence.
    ///////////////////////////////////////////////////////////////////////////
    template <typename Iterator, typename HasState, typename Idtype>
    struct position_token<Iterator, mpl::vector<>, HasState, Idtype>
      : position_token<Iterator, lex::omit, HasState, Idtype>
    {
    private:
        typedef position_token<Iterator, lex::omit, HasState, Idtype> base_type;

    public:
        typedef typename base_type::id_type id_type;
        typedef typename base_type::iterator_type iterator_type;
        typedef typename base_type::iterpair_type iterpair_type;
        typedef HasState has_state;
        typedef iterpair_type token_value_type;

        //  default constructed tokens correspond to EOI tokens
        position_token() {}

        //  construct an invalid token
        explicit position_token(int) 
          : base_type(0) {}

        position_token(id_type id, std::size_t state)
          : base_type(id, state) {}

        position_token(id_type id, std::size_t state, token_value_type)
          : base_type(id, state, unused) {}

        position_token(id_type id, std::size_t state
              , Iterator const& first, Iterator const& last)
          : base_type(id, state, first, last) {}

        token_value_type& value() { return this->base_type::matched(); }
        token_value_type const& value() const { return this->base_type::matched(); }
    };

    template <typename Iterator, typename HasState, typename Idtype>
    struct position_token<Iterator, mpl::vector0<>, HasState, Idtype>
      : position_token<Iterator, lex::omit, HasState, Idtype>
    {
    private:
        typedef position_token<Iterator, lex::omit, HasState, Idtype> base_type;

    public:
        typedef typename base_type::id_type id_type;
        typedef typename base_type::iterator_type iterator_type;
        typedef typename base_type::iterpair_type iterpair_type;
        typedef HasState has_state;
        typedef iterpair_type token_value_type;

        //  default constructed tokens correspond to EOI tokens
        position_token() {}

        //  construct an invalid token
        explicit position_token(int) 
          : base_type(0) {}

        position_token(id_type id, std::size_t state)
          : base_type(id, state) {}

        position_token(id_type id, std::size_t state, token_value_type)
          : base_type(id, state, unused) {}

        position_token(id_type id, std::size_t state
              , Iterator const& first, Iterator const& last)
          : base_type(id, state, first, last) {}

        token_value_type& value() { return this->base_type::matched(); }
        token_value_type const& value() const { return this->base_type::matched(); }
    };

    ///////////////////////////////////////////////////////////////////////////
    // These specializations for an attribute list of length one cause all token 
    // instances to expose the specified type as its attribute.
    ///////////////////////////////////////////////////////////////////////////
    template <typename Iterator, typename Attribute, typename HasState
      , typename Idtype>
    struct position_token<Iterator, mpl::vector<Attribute>, HasState, Idtype>
      : position_token<Iterator, lex::omit, HasState, Idtype>
    {
    private:
        typedef position_token<Iterator, lex::omit, HasState, Idtype> base_type;

    public:
        typedef typename base_type::id_type id_type;
        typedef typename base_type::iterator_type iterator_type;
        typedef typename base_type::iterpair_type iterpair_type;
        typedef HasState has_state;
        typedef boost::optional<Attribute> token_value_type;

        //  default constructed tokens correspond to EOI tokens
        position_token() {}

        //  construct an invalid token
        explicit position_token(int) 
          : base_type(0) {}

        position_token(id_type id, std::size_t state)
          : base_type(id, state) {}

        position_token(id_type id, std::size_t state, token_value_type const& v)
          : base_type(id, state, unused), value_(v) {}

        position_token(id_type id, std::size_t state
              , Iterator const& first, Iterator const& last)
          : base_type(id, state, first, last) {}

        token_value_type& value() { return value_; }
        token_value_type const& value() const { return value_; }

        bool has_value() const { return !!value_; }

#if BOOST_WORKAROUND(BOOST_MSVC, == 1600)
        // workaround for MSVC10 which has problems copying a default 
        // constructed iterator_range
        position_token& operator= (position_token const& rhs)
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
        token_value_type value_; // token value
    };

    template <typename Iterator, typename Attribute, typename HasState
      , typename Idtype>
    struct position_token<Iterator, mpl::vector1<Attribute>, HasState, Idtype>
      : position_token<Iterator, lex::omit, HasState, Idtype>
    {
    private:
        typedef position_token<Iterator, lex::omit, HasState, Idtype> base_type;

    public:
        typedef typename base_type::id_type id_type;
        typedef typename base_type::iterator_type iterator_type;
        typedef typename base_type::iterpair_type iterpair_type;
        typedef HasState has_state;
        typedef boost::optional<Attribute> token_value_type;

        //  default constructed tokens correspond to EOI tokens
        position_token() {}

        //  construct an invalid token
        explicit position_token(int) 
          : base_type(0) {}

        position_token(id_type id, std::size_t state)
          : base_type(id, state) {}

        position_token(id_type id, std::size_t state, token_value_type const& v)
          : base_type(id, state, unused), value_(v) {}

        position_token(id_type id, std::size_t state
              , Iterator const& first, Iterator const& last)
          : base_type(id, state, first, last) {}

        token_value_type& value() { return value_; }
        token_value_type const& value() const { return value_; }

        bool has_value() const { return value_; }

#if BOOST_WORKAROUND(BOOST_MSVC, == 1600)
        // workaround for MSVC10 which has problems copying a default 
        // constructed iterator_range
        position_token& operator= (position_token const& rhs)
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
        token_value_type value_; // token value
    };

    ///////////////////////////////////////////////////////////////////////////
    //  The generic version of the position_token type derives from the 
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
        struct position_token_value_typesequence
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
        struct position_token_value
          : mpl::eval_if<
                mpl::or_<
                    is_same<AttributeTypes, mpl::vector0<> >
                  , is_same<AttributeTypes, mpl::vector<> > >
              , mpl::identity<IteratorPair>
              , position_token_value_typesequence<IteratorPair, AttributeTypes> >
        {};
    }

    template <typename Iterator, typename AttributeTypes, typename HasState
      , typename Idtype>
    struct position_token 
      : position_token<Iterator, lex::omit, HasState, Idtype>
    {
    private: // precondition assertions
        BOOST_STATIC_ASSERT((mpl::is_sequence<AttributeTypes>::value || 
                            is_same<AttributeTypes, lex::omit>::value));
        typedef position_token<Iterator, lex::omit, HasState, Idtype> 
            base_type;

    protected: 
        //  If no additional token value types are given, the token will 
        //  hold no token value at all as the base class already has the 
        //  iterator pair of the matched range in the underlying input sequence. 
        //  Otherwise the token value is stored as a variant and will 
        //  initially hold an unused_type but is able to hold any of 
        //  the given data types as well. The conversion from the iterator pair 
        //  to the required data type is done when it is accessed for the first 
        //  time.
        typedef iterator_range<Iterator> iterpair_type;

    public:
        typedef typename base_type::id_type id_type;
        typedef typename detail::position_token_value<
            iterpair_type, AttributeTypes>::type token_value_type;

        typedef Iterator iterator_type;

        //  default constructed tokens correspond to EOI tokens
        position_token() {}

        //  construct an invalid token
        explicit position_token(int)
          : base_type(0) {}

        position_token(id_type id, std::size_t state, token_value_type const& value)
          : base_type(id, state, value), value_(value) {}

        position_token(id_type id, std::size_t state, Iterator const& first
              , Iterator const& last)
          : base_type(id, state, first, last)
          , value_(iterpair_type(first, last)) 
        {}

        token_value_type& value() { return value_; }
        token_value_type const& value() const { return value_; }

#if BOOST_WORKAROUND(BOOST_MSVC, == 1600)
        // workaround for MSVC10 which has problems copying a default 
        // constructed iterator_range
        position_token& operator= (position_token const& rhs)
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
    operator== (position_token<Iterator, AttributeTypes, HasState, Idtype> const& lhs, 
                position_token<Iterator, AttributeTypes, HasState, Idtype> const& rhs)
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
    token_is_valid(position_token<Iterator, AttributeTypes, HasState, Idtype> const& t)
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
      , lex::lexertl::position_token<Iterator, AttributeTypes, HasState, Idtype> >
    {
        static void 
        call(lex::lexertl::position_token<
                Iterator, AttributeTypes, HasState, Idtype> const& t
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
                iterpair_type const& ip = t.matched();

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

                typedef lex::lexertl::position_token<
                    Iterator, AttributeTypes, HasState, Idtype> token_type;
                spirit::traits::assign_to(
                    attr, const_cast<token_type&>(t).value());   // re-assign value
            }
            else {
            // reuse the already assigned value
                spirit::traits::assign_to(get<Attribute>(t.value()), attr);
            }
        }
    };

    template <typename Attribute, typename Iterator, typename AttributeTypes
      , typename HasState, typename Idtype>
    struct assign_to_container_from_value<Attribute
          , lex::lexertl::position_token<Iterator, AttributeTypes, HasState, Idtype> >
      : assign_to_attribute_from_value<Attribute
          , lex::lexertl::position_token<Iterator, AttributeTypes, HasState, Idtype> >
    {};

    ///////////////////////////////////////////////////////////////////////////
    //  These are called from the parse function of token_def if the token type
    //  has no special attribute type assigned 
    template <typename Attribute, typename Iterator, typename HasState
      , typename Idtype>
    struct assign_to_attribute_from_value<Attribute
      , lex::lexertl::position_token<Iterator, mpl::vector0<>, HasState, Idtype> >
    {
        static void 
        call(lex::lexertl::position_token<
                Iterator, mpl::vector0<>, HasState, Idtype> const& t
          , Attribute& attr)
        {
            //  The default type returned by the token_def parser component (if 
            //  it has no token value type assigned) is the pair of iterators 
            //  to the matched character sequence.
            spirit::traits::assign_to(t.begin(), t.end(), attr);
        }
    };

//     template <typename Attribute, typename Iterator, typename HasState
//       , typename Idtype>
//     struct assign_to_container_from_value<Attribute
//           , lex::lexertl::position_token<Iterator, mpl::vector0<>, HasState, Idtype> >
//       : assign_to_attribute_from_value<Attribute
//           , lex::lexertl::position_token<Iterator, mpl::vector0<>, HasState, Idtype> >
//     {};

    // same as above but using mpl::vector<> instead of mpl::vector0<>
    template <typename Attribute, typename Iterator, typename HasState
      , typename Idtype>
    struct assign_to_attribute_from_value<Attribute
      , lex::lexertl::position_token<Iterator, mpl::vector<>, HasState, Idtype> >
    {
        static void 
        call(lex::lexertl::position_token<
                Iterator, mpl::vector<>, HasState, Idtype> const& t
          , Attribute& attr)
        {
            //  The default type returned by the token_def parser component (if 
            //  it has no token value type assigned) is the pair of iterators 
            //  to the matched character sequence.
            spirit::traits::assign_to(t.begin(), t.end(), attr);
        }
    };

//     template <typename Attribute, typename Iterator, typename HasState
//       , typename Idtype>
//     struct assign_to_container_from_value<Attribute
//           , lex::lexertl::position_token<Iterator, mpl::vector<>, HasState, Idtype> >
//       : assign_to_attribute_from_value<Attribute
//           , lex::lexertl::position_token<Iterator, mpl::vector<>, HasState, Idtype> >
//     {};

    ///////////////////////////////////////////////////////////////////////////
    //  These are called from the parse function of token_def if the token type
    //  has no special attribute type assigned 
    template <typename Attribute, typename Iterator, typename Attr
      , typename HasState, typename Idtype>
    struct assign_to_attribute_from_value<Attribute
      , lex::lexertl::position_token<Iterator, mpl::vector1<Attr>, HasState, Idtype> >
    {
        static void 
        call(lex::lexertl::position_token<
                Iterator, mpl::vector1<Attr>, HasState, Idtype> const& t
          , Attribute& attr)
        {
        //  The goal of this function is to avoid the conversion of the pair of
        //  iterators (to the matched character sequence) into the token value 
        //  of the required type being done more than once.

            if (!t.has_value()) {
            //  first access to the token value
                typedef iterator_range<Iterator> iterpair_type;
                iterpair_type const& ip = t.matched();

            // Interestingly enough we use the assign_to() framework defined in 
            // Spirit.Qi allowing to convert the pair of iterators to almost any 
            // required type (assign_to(), if available, uses the standard Spirit 
            // parsers to do the conversion).
                spirit::traits::assign_to(ip.begin(), ip.end(), attr);

            // Re-assign the attribute to the stored value
                typedef lex::lexertl::position_token<
                    Iterator, mpl::vector1<Attr>, HasState, Idtype> token_type;
                spirit::traits::assign_to(
                    attr, const_cast<token_type&>(t).value());
            }
            else {
            // reuse the already assigned value
                spirit::traits::assign_to(t.value(), attr);
            }
        }
    };

//     template <typename Attribute, typename Iterator, typename Attr
//       , typename HasState, typename Idtype>
//     struct assign_to_container_from_value<Attribute
//           , lex::lexertl::position_token<Iterator, mpl::vector1<Attr>, HasState, Idtype> >
//       : assign_to_attribute_from_value<Attribute
//           , lex::lexertl::position_token<Iterator, mpl::vector1<Attr>, HasState, Idtype> >
//     {};

    // same as above but using mpl::vector<Attr> instead of mpl::vector1<Attr>
    template <typename Attribute, typename Iterator, typename Attr
      , typename HasState, typename Idtype>
    struct assign_to_attribute_from_value<Attribute
      , lex::lexertl::position_token<Iterator, mpl::vector<Attr>, HasState, Idtype> >
    {
        static void 
        call(lex::lexertl::position_token<
                Iterator, mpl::vector<Attr>, HasState, Idtype> const& t
          , Attribute& attr)
        {
        //  The goal of this function is to avoid the conversion of the pair of
        //  iterators (to the matched character sequence) into the token value 
        //  of the required type being done more than once.

            if (!t.has_value()) {
            //  first access to the token value
                typedef iterator_range<Iterator> iterpair_type;
                iterpair_type const& ip = t.matched();

            // Interestingly enough we use the assign_to() framework defined in 
            // Spirit.Qi allowing to convert the pair of iterators to almost any 
            // required type (assign_to(), if available, uses the standard Spirit 
            // parsers to do the conversion).
                spirit::traits::assign_to(ip.begin(), ip.end(), attr);

            // Re-assign the attribute to the stored value
                typedef lex::lexertl::position_token<
                    Iterator, mpl::vector<Attr>, HasState, Idtype> token_type;
                spirit::traits::assign_to(
                    attr, const_cast<token_type&>(t).value());
            }
            else {
            // reuse the already assigned value
                spirit::traits::assign_to(t.value(), attr);
            }
        }
    };

//     template <typename Attribute, typename Iterator, typename Attr
//       , typename HasState, typename Idtype>
//     struct assign_to_container_from_value<Attribute
//           , lex::lexertl::position_token<Iterator, mpl::vector<Attr>, HasState, Idtype> >
//       : assign_to_attribute_from_value<Attribute
//           , lex::lexertl::position_token<Iterator, mpl::vector<Attr>, HasState, Idtype> >
//     {};

    //  This is called from the parse function of token_def if the token type
    //  has been explicitly omitted (i.e. no attribute value is used), which
    //  essentially means that every attribute gets initialized using default 
    //  constructed values.
    template <typename Attribute, typename Iterator, typename HasState
      , typename Idtype>
    struct assign_to_attribute_from_value<Attribute
      , lex::lexertl::position_token<Iterator, lex::omit, HasState, Idtype> >
    {
        static void 
        call(lex::lexertl::position_token<Iterator, lex::omit, HasState, Idtype> const&
          , Attribute&)
        {
            // do nothing
        }
    };

    template <typename Attribute, typename Iterator, typename HasState
      , typename Idtype>
    struct assign_to_container_from_value<Attribute
          , lex::lexertl::position_token<Iterator, lex::omit, HasState, Idtype> >
      : assign_to_attribute_from_value<Attribute
          , lex::lexertl::position_token<Iterator, lex::omit, HasState, Idtype> >
    {};

    //  This is called from the parse function of lexer_def_
    template <typename Iterator, typename AttributeTypes, typename HasState
      , typename Idtype_, typename Idtype>
    struct assign_to_attribute_from_value<
        fusion::vector2<Idtype_, iterator_range<Iterator> >
      , lex::lexertl::position_token<Iterator, AttributeTypes, HasState, Idtype> >
    {
        static void 
        call(lex::lexertl::position_token<Iterator, AttributeTypes, HasState, Idtype> const& t
          , fusion::vector2<Idtype_, iterator_range<Iterator> >& attr)
        {
            //  The type returned by the lexer_def_ parser components is a 
            //  fusion::vector containing the token id of the matched token 
            //  and the pair of iterators to the matched character sequence.
            typedef iterator_range<Iterator> iterpair_type;
            typedef fusion::vector2<Idtype_, iterator_range<Iterator> > 
                attribute_type;

            iterpair_type const& ip = t.matched();
            attr = attribute_type(t.id(), ip);
        }
    };

    template <typename Iterator, typename AttributeTypes, typename HasState
      , typename Idtype_, typename Idtype>
    struct assign_to_container_from_value<
            fusion::vector2<Idtype_, iterator_range<Iterator> >
          , lex::lexertl::position_token<Iterator, AttributeTypes, HasState, Idtype> >
      : assign_to_attribute_from_value<
            fusion::vector2<Idtype_, iterator_range<Iterator> >
          , lex::lexertl::position_token<Iterator, AttributeTypes, HasState, Idtype> >
    {};

    ///////////////////////////////////////////////////////////////////////////
    // Overload debug output for a single token, this integrates lexer tokens 
    // with Qi's simple_trace debug facilities
    template <typename Iterator, typename Attribute, typename HasState
      , typename Idtype>
    struct token_printer_debug<
        lex::lexertl::position_token<Iterator, Attribute, HasState, Idtype> >
    {
        typedef lex::lexertl::position_token<Iterator, Attribute, HasState, Idtype> token_type;

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

/* position_token.hpp
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
*/