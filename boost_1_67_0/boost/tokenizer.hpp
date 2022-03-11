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