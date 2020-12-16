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
nzkcNZj+fCOpB9u1oZXP+iVqpOP3eD0Rv9VRfB1St0RSS+lTYIoEMkSxSzxWt/7PRkmVS/OK1rAEiqR264jv69BW1xyR1Oup7ODZjFTqtX0Z8n9Rkz4AtJDe/Tn8+R1R7SS+XIQRqpW/QORX4f8L4xpJbdYW9QotzW/E4de3cK5haIC98QJyE2/CS1SfRpoO67UVWXbvGbOlPKUB6zdkOUneR8evCVejXJKPQI5i6j+Usv4DCVpCSpytVCkKU13DSS3Kh+oIoqzPmKr8DtU44hSbhZ6AevnGrXJ2KDmfRCLl+PYwvqUYnxmzUcYMRwwXYKhOnZz/PdWfpqSV1WnPULe+Pb2nH/PujH0PDjimvOAA5K/F/3/K85cH42zCA+vA4/8x8cRXg9d9vzaVj/da8u9P5Wpp9MMFrUB4vSAs3EnEwwpDsfowjdZRlkkvmCptYCothjVIAqGL9UAemJWHLiT5z2OY84iaTkp9+qodph69lxMfR6K+ALFK0RMCDodcKKZyHmdtNILqcnJzps9iQz1E5lPkg39GhvKEbIQt9ZJ01P2TrivTWf5BggPpurKSCJmLqUupGHJQbq1fEdvgb7KrlqV7m9H9/Rc0Ib9F5MxGpqXqX79IkhfjuFooFpL6SVAe3A8urkmfZMXmoyUnrps5a57wQzBS3jczC5ISl7YaJeSymnu+Xc/EpdAYlEQ0x+ptKqwEtz/PVoIrY/CJWcevUXI8mb0fj96+9Yb2Y+bnmcu1A252RKl/9hL1WCdAuZY4aYf+550m6OSR3e3X0KaWXoHmLeCZbqtULXN6M/SyN6XOnR+S8db6zD9WR9iYLux0s1dJ+sQN0NX2UsmpStEDQqeh+fkCiIZgv6I8Q4qkITQb3rHLE6FP/usN76T91zruu0SaMFCBb6DvFjEEzzkPwHrFXDRykz9snTyVQKHmepqCHDCdeX4bg4Z/crpleiLZW/viYd2vIMNgkeFa1uZ36G2203/WyLgwg1bRVFpF4xALBUuxipohnuDmOkSi1ilPSazYqBG1pvg5sY2LS+wBis2RcuBcpPR4mRfVN+f+ukVVS98Q2oaSnFm5VmKyw4qmQ/dMSjS6YMu/8bwmUv5MW35fQenn6H96TxIxpm+aIUOZkc6noRxMJ0zDcsmckuX9cKrZAWczs4q9beR5Y0UkdU2bNnwnnlRbgqK9rrA7wUjqt83bsOuNnmXeG2b0tABGkTERalSRcFtkyCyu82hbDU2NqLZqVAaxFvbx20UFTUfi/OpKHPTA7OQ6jvLtyfiJmIlrrOH4zPV8N6gS2Yil3RQHFrDKCV1vpQvpDZyB/jCAUn+G1ejyP+o2lFM9v5f672sE/WFdWC0siZlu+OEdkB4n9dfHyOLD1fLAtfed5wDWPNKpFt3cCSw69mVm74chic9g5vJRww65G3UlfYfO4BgYoNY/ZWKTsUrRHr6vlXI0RQ5a+99SOrmOD04kKUEaoV67UnSA0EgXwP1PnVAJVlfOaywx7SK1zz85h1ZWNdXQ7FtaWUT3kD434vkyI0RK18z/UGOV2PsMeeT+8JEgTfMbQ74TST0ztY2FCE6WxcZnHA134NtJsxK9qTHnsw14ZrNa+PbSxBJr18hG/Sahrv7G09KLzvA9I2cjpbIjoxsnZCRs77MBpZP/qUjqNS0ZzM9Fpg+RCTuO72necZbTAkVZNBRyFCSRWx7+ftWv+dE2PFrS9A+uqq7L/lSSG+06HUtukBMiSW4kdDLJjb7bYsiNXR3FdHZD5MmVz2Ptv1bF8Bf6HyCklYAzp6OJkr/cGoOS/aImrqSyDCn12l9rOTXTVkr8WR0aty4X+BOItKijqCIdVcDqII+P8F8=
*/