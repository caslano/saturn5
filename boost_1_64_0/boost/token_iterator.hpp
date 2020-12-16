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
4qQ+0cjBookHEhaK3Hi7GPI7UtoAeN9pTPnPuo8MFUGiXwtQHtGKQPmDOHN6h9Dn2VggTsHHA+pptWjrWP0XK5U0FrBuRwKQOmOeuLZIaiMqgWbtZ2sbS7i5ssjJw5LQBuVTuyKpnydQjhABFS2LZ1cRgn2pc5xxvet1Q8tyQkmW6/FchWcwnlw8v8djSUjAYzF/CcbPmlDzF3fMu+2Y9/hV/3U/suvu1+qX218c5/6v9w1VcOPct1K/968SzgBjAH/T3SRIfxPOXiacSIJVrG+i1wFRLL/CSq8n0V53e156r3Z7ql4llENNkS0gUzdqBtOxKIfgMvXXNqju9qTW0Z6Rr558fHYn/crmHKc9he/Wbs+Gv9RjfIb+2gZlFwwSR7hx7xrn0tTzfNHzfUQK5mPHAOekvwHkTddpnEN+45vL64jpOHfQHfB1nhS6opu+6mXjOBesBTiec01m5yF532pzVnGopmtV5sZmpv4MptpGMWPv0oqFz/ZRrIqqaytYyCNkdluaASkJv7j9SPys4VPaJc5HBR8ijep7ipX60LC+t4eu7KZnvkz5UJJZoXS22eM1mvVEIh+b0fuOJ4/NaIpyu1LE6WaZju9vcfwiKRna52aYcCyo1HXQ+iwdlCcTJJ2TB+wrU0XH+1rkrQvd+IC9B7iLcP9sxwLu7RKNxSGDkH+OzJ8fm3+invwSDfQUMdCTUqX/N5Lu0q3gRTEqiOTrkMT0UYeHpgfU+6wkQ5pyDptRkifI6dJveiqxum8xqzvvRTFzXcOz+R/KB2+QO7xYf3eBsBL1gSYwbxbnog27Fr2TqIC9A9xAkt9nVU04ZaUCPgBHSR8Gan+4y8IfsjzoZtJcv5EqofopYxa+Rhk8rvr368Sh6W4yzSi6XYzIiDPFiKyH1JaEZny69wmJ3cSVC/nviLYvYoPU8sq1R0+r9uup/6gv8mo5qZXVYqHkPdhrpH8l2bHM6NXC4jsEigiLINiSpzj2ZjY68ywThEWJHodhuL4pyeg6EOjEZ+N6er3BXSg0xitDJyQR/IXbuUxtQ8+9kEZUYPR7sRUscghlosV3yXsDmxJ0LNDve4FAMEsM+A9nCCPeG1exdCWMo5q+OKopm5HV29cY9toRcCDZEbx5D3qCl2glLKyONv9X3sZzXP+X70j+8/0g+M/ZL0f5z1eDzHF+C76Zxknjtw31MOSMkY/3kDz12HcMmTSK2sRA3UCf+RcanYlidG4XmFDPWWmIu+slf5aHNg5ZPh3W6CgbIAFonjCTjw8uYnsbMgLB2cEnS/nsgCF+Lyh3u35HUwcxEBlIx7HBpTP52GD9CT19qRC6bll1ij9T/+ft6Fg0WphKVG/bo61pDBYLJKWy0u1aIY8PPFlPebzcfxOM0ncAaFOw75G8mZCVqsOVyGXTTfHqWaTHfKbAnJfyFnMnthd2J70WZ8K0Z2XqCwHo8nZj9qFHDLJwBKzPfoIPxJONC0jD15AsHIT2GNQGrYR76VPD78mnlOGSxecbWhuo+6ME9nYMDPqpnvgoleVtpHaf6pyU9AEfpLel7z7npXWbWFX90VoFp0u4Pkm/AE2k+vRWTxEQuaVfRonTjlYYp+rlp+Fi1nr+DH+Z/jd5BjD8F6JJjxMqUDfpS6eZI9+Z9HgRTR28kbAGXW5v7HJXY3EYFzXr1j8YDu58rZA6WvhkysG3eqsKMx+htF9wszOtT4+EyTVvxKzPbxhRNVCK7HRy8abwMNlZf3o2jXSyOML44Awx0o+W1/N0ivgDBeAa5ym3UJX18b8K/aAT6R+2lI1m9I82ZaBNWoVStIvlaneZ400SZscZYrz3Mo3gM0b7+2fq1gz9QcDT5iYCZfc=
*/