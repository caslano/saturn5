// Boost token_iterator.hpp  -------------------------------------------------//

// Copyright John R. Bandela 2001
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org/libs/tokenizer for documentation.

// Revision History:
// 16 Jul 2003   John Bandela
//      Allowed conversions from convertible base iterators
// 03 Jul 2003   John Bandela
//      Converted to new iterator adapter



#ifndef BOOST_TOKENIZER_POLICY_JRB070303_HPP_
#define BOOST_TOKENIZER_POLICY_JRB070303_HPP_

#include <boost/assert.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/minimum_category.hpp>
#include <boost/token_functions.hpp>
#include <utility>

namespace boost
{
  template <class TokenizerFunc, class Iterator, class Type>
  class token_iterator
      : public iterator_facade<
            token_iterator<TokenizerFunc, Iterator, Type>
          , Type
          , typename iterators::minimum_category<
                forward_traversal_tag
              , typename iterator_traversal<Iterator>::type
            >::type
          , const Type&
        >
  {

#ifdef __DCC__ 
      friend class boost::iterator_core_access; 
#else 
      friend class iterator_core_access; 
#endif  
      TokenizerFunc f_;
      Iterator begin_;
      Iterator end_;
      bool valid_;
      Type tok_;

      void increment(){
          BOOST_ASSERT(valid_);
          valid_ = f_(begin_,end_,tok_);
      }

      const Type&  dereference() const {
          BOOST_ASSERT(valid_);
          return tok_;
      }
      template<class Other>
      bool equal(const Other& a) const{
          return (a.valid_ && valid_)
              ?( (a.begin_==begin_) && (a.end_ == end_) )
              :(a.valid_==valid_);

      }

      void initialize(){
          if(valid_) return;
          f_.reset();
          valid_ = (begin_ != end_)?
              f_(begin_,end_,tok_):false;
      }
  public:
      token_iterator():begin_(),end_(),valid_(false),tok_() { }

      token_iterator(TokenizerFunc f, Iterator begin, Iterator e = Iterator())
          : f_(f),begin_(begin),end_(e),valid_(false),tok_(){ initialize(); }

      token_iterator(Iterator begin, Iterator e = Iterator())
            : f_(),begin_(begin),end_(e),valid_(false),tok_() {initialize();}

      template<class OtherIter>
      token_iterator(
            token_iterator<TokenizerFunc, OtherIter,Type> const& t
            , typename enable_if_convertible<OtherIter, Iterator>::type* = 0)
            : f_(t.tokenizer_function()),begin_(t.base())
            ,end_(t.end()),valid_(!t.at_end()),tok_(t.current_token()) {}

      Iterator base()const{return begin_;}

      Iterator end()const{return end_;}

      TokenizerFunc tokenizer_function()const{return f_;}

      Type current_token()const{return tok_;}

      bool at_end()const{return !valid_;}




  };
    template <
        class TokenizerFunc = char_delimiters_separator<char>,
        class Iterator = std::string::const_iterator,
        class Type = std::string
    >
    class token_iterator_generator {

    private:
    public:
        typedef token_iterator<TokenizerFunc,Iterator,Type> type;
    };


    // Type has to be first because it needs to be explicitly specified
    // because there is no way the function can deduce it.
    template<class Type, class Iterator, class TokenizerFunc>
        typename token_iterator_generator<TokenizerFunc,Iterator,Type>::type
    make_token_iterator(Iterator begin, Iterator end,const TokenizerFunc& fun){
        typedef typename
            token_iterator_generator<TokenizerFunc,Iterator,Type>::type ret_type;
        return ret_type(fun,begin,end);
    }

} // namespace boost

#endif

/* token_iterator.hpp
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
*/