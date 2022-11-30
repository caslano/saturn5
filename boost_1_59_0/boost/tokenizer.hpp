// Boost tokenizer.hpp  -----------------------------------------------------//

// (c) Copyright Jeremy Siek and John R. Bandela 2001. 

// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org/libs/tokenizer for documenation

// Revision History:
// 03 Jul 2003   John Bandela
//      Converted to new iterator adapter
// 02 Feb 2002   Jeremy Siek
//      Removed tabs and a little cleanup.

#ifndef BOOST_TOKENIZER_JRB070303_HPP_
#define BOOST_TOKENIZER_JRB070303_HPP_

#include <boost/token_iterator.hpp>

namespace boost {

  
  //===========================================================================
  // A container-view of a tokenized "sequence"
  template <
    typename TokenizerFunc = char_delimiters_separator<char>, 
    typename Iterator = std::string::const_iterator,
    typename Type = std::string
  >
  class tokenizer {
  private:
    typedef token_iterator_generator<TokenizerFunc,Iterator,Type> TGen;
        
    // It seems that MSVC does not like the unqualified use of iterator,
    // Thus we use iter internally when it is used unqualified and
    // the users of this class will always qualify iterator.     
    typedef typename TGen::type iter;
    
  public:
    
    typedef iter iterator;
    typedef iter const_iterator;
    typedef Type value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef value_type* pointer;
    typedef const pointer const_pointer;
    typedef void size_type;
    typedef void difference_type;

    tokenizer(Iterator first, Iterator last,
              const TokenizerFunc& f = TokenizerFunc()) 
      : first_(first), last_(last), f_(f) { }
        
    template <typename Container>
    tokenizer(const Container& c)
      : first_(c.begin()), last_(c.end()), f_() { }
    
    template <typename Container>
    tokenizer(const Container& c,const TokenizerFunc& f)
      : first_(c.begin()), last_(c.end()), f_(f) { }
    
    void assign(Iterator first, Iterator last){
      first_ = first;
      last_ = last;
    }
    
    void assign(Iterator first, Iterator last, const TokenizerFunc& f){
      assign(first,last);
      f_ = f;
    }
    
    template <typename Container>
    void assign(const Container& c){
      assign(c.begin(),c.end());
    }
    
    
    template <typename Container>
    void assign(const Container& c, const TokenizerFunc& f){
      assign(c.begin(),c.end(),f);
    }
    
    iter begin() const { return iter(f_,first_,last_); }
    iter end() const { return iter(f_,last_,last_); }
        
  private:
    Iterator first_;
    Iterator last_;
    TokenizerFunc f_;
  };


} // namespace boost

#endif

/* tokenizer.hpp
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
*/