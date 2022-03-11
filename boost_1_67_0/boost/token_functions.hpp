// Boost token_functions.hpp  ------------------------------------------------//

// Copyright John R. Bandela 2001.

// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org/libs/tokenizer/ for documentation.

// Revision History:
// 01 Oct 2004   Joaquin M Lopez Munoz
//      Workaround for a problem with string::assign in msvc-stlport
// 06 Apr 2004   John Bandela
//      Fixed a bug involving using char_delimiter with a true input iterator
// 28 Nov 2003   Robert Zeh and John Bandela
//      Converted into "fast" functions that avoid using += when
//      the supplied iterator isn't an input_iterator; based on
//      some work done at Archelon and a version that was checked into
//      the boost CVS for a short period of time.
// 20 Feb 2002   John Maddock
//      Removed using namespace std declarations and added
//      workaround for BOOST_NO_STDC_NAMESPACE (the library
//      can be safely mixed with regex).
// 06 Feb 2002   Jeremy Siek
//      Added char_separator.
// 02 Feb 2002   Jeremy Siek
//      Removed tabs and a little cleanup.


#ifndef BOOST_TOKEN_FUNCTIONS_JRB120303_HPP_
#define BOOST_TOKEN_FUNCTIONS_JRB120303_HPP_

#include <vector>
#include <stdexcept>
#include <string>
#include <cctype>
#include <algorithm> // for find_if
#include <boost/config.hpp>
#include <boost/assert.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/mpl/if.hpp>
#include <boost/throw_exception.hpp>
#if !defined(BOOST_NO_CWCTYPE)
#include <cwctype>
#endif

//
// the following must not be macros if we are to prefix them
// with std:: (they shouldn't be macros anyway...)
//
#ifdef ispunct
#  undef ispunct
#endif
#ifdef iswpunct
#  undef iswpunct
#endif
#ifdef isspace
#  undef isspace
#endif
#ifdef iswspace
#  undef iswspace
#endif
//
// fix namespace problems:
//
#ifdef BOOST_NO_STDC_NAMESPACE
namespace std{
 using ::ispunct;
 using ::isspace;
#if !defined(BOOST_NO_CWCTYPE)
 using ::iswpunct;
 using ::iswspace;
#endif
}
#endif

namespace boost{
  //===========================================================================
  // The escaped_list_separator class. Which is a model of TokenizerFunction
  // An escaped list is a super-set of what is commonly known as a comma
  // separated value (csv) list.It is separated into fields by a comma or
  // other character. If the delimiting character is inside quotes, then it is
  // counted as a regular character.To allow for embedded quotes in a field,
  // there can be escape sequences using the \ much like C.
  // The role of the comma, the quotation mark, and the escape
  // character (backslash \), can be assigned to other characters.

  struct escaped_list_error : public std::runtime_error{
    escaped_list_error(const std::string& what_arg):std::runtime_error(what_arg) { }
  };


// The out of the box GCC 2.95 on cygwin does not have a char_traits class.
// MSVC does not like the following typename
  template <class Char,
    class Traits = BOOST_DEDUCED_TYPENAME std::basic_string<Char>::traits_type >
  class escaped_list_separator {

  private:
    typedef std::basic_string<Char,Traits> string_type;
    struct char_eq {
      Char e_;
      char_eq(Char e):e_(e) { }
      bool operator()(Char c) {
        return Traits::eq(e_,c);
      }
    };
    string_type  escape_;
    string_type  c_;
    string_type  quote_;
    bool last_;

    bool is_escape(Char e) {
      char_eq f(e);
      return std::find_if(escape_.begin(),escape_.end(),f)!=escape_.end();
    }
    bool is_c(Char e) {
      char_eq f(e);
      return std::find_if(c_.begin(),c_.end(),f)!=c_.end();
    }
    bool is_quote(Char e) {
      char_eq f(e);
      return std::find_if(quote_.begin(),quote_.end(),f)!=quote_.end();
    }
    template <typename iterator, typename Token>
    void do_escape(iterator& next,iterator end,Token& tok) {
      if (++next == end)
        BOOST_THROW_EXCEPTION(escaped_list_error(std::string("cannot end with escape")));
      if (Traits::eq(*next,'n')) {
        tok+='\n';
        return;
      }
      else if (is_quote(*next)) {
        tok+=*next;
        return;
      }
      else if (is_c(*next)) {
        tok+=*next;
        return;
      }
      else if (is_escape(*next)) {
        tok+=*next;
        return;
      }
      else
        BOOST_THROW_EXCEPTION(escaped_list_error(std::string("unknown escape sequence")));
    }

    public:

    explicit escaped_list_separator(Char  e = '\\',
                                    Char c = ',',Char  q = '\"')
      : escape_(1,e), c_(1,c), quote_(1,q), last_(false) { }

    escaped_list_separator(string_type e, string_type c, string_type q)
      : escape_(e), c_(c), quote_(q), last_(false) { }

    void reset() {last_=false;}

    template <typename InputIterator, typename Token>
    bool operator()(InputIterator& next,InputIterator end,Token& tok) {
      bool bInQuote = false;
      tok = Token();

      if (next == end) {
        if (last_) {
          last_ = false;
          return true;
        }
        else
          return false;
      }
      last_ = false;
      for (;next != end;++next) {
        if (is_escape(*next)) {
          do_escape(next,end,tok);
        }
        else if (is_c(*next)) {
          if (!bInQuote) {
            // If we are not in quote, then we are done
            ++next;
            // The last character was a c, that means there is
            // 1 more blank field
            last_ = true;
            return true;
          }
          else tok+=*next;
        }
        else if (is_quote(*next)) {
          bInQuote=!bInQuote;
        }
        else {
          tok += *next;
        }
      }
      return true;
    }
  };

  //===========================================================================
  // The classes here are used by offset_separator and char_separator to implement
  // faster assigning of tokens using assign instead of +=

  namespace tokenizer_detail {
  //===========================================================================
  // Tokenizer was broken for wide character separators, at least on Windows, since
  // CRT functions isspace etc only expect values in [0, 0xFF]. Debug build asserts
  // if higher values are passed in. The traits extension class should take care of this.
  // Assuming that the conditional will always get optimized out in the function
  // implementations, argument types are not a problem since both forms of character classifiers
  // expect an int.

#if !defined(BOOST_NO_CWCTYPE)
  template<typename traits, int N>
  struct traits_extension_details : public traits {
    typedef typename traits::char_type char_type;
    static bool isspace(char_type c)
    {
       return std::iswspace(c) != 0;
    }
    static bool ispunct(char_type c)
    {
       return std::iswpunct(c) != 0;
    }
  };

  template<typename traits>
  struct traits_extension_details<traits, 1> : public traits {
    typedef typename traits::char_type char_type;
    static bool isspace(char_type c)
    {
       return std::isspace(c) != 0;
    }
    static bool ispunct(char_type c)
    {
       return std::ispunct(c) != 0;
    }
  };
#endif


  // In case there is no cwctype header, we implement the checks manually.
  // We make use of the fact that the tested categories should fit in ASCII.
  template<typename traits>
  struct traits_extension : public traits {
    typedef typename traits::char_type char_type;
    static bool isspace(char_type c)
    {
#if !defined(BOOST_NO_CWCTYPE)
      return traits_extension_details<traits, sizeof(char_type)>::isspace(c);
#else
      return static_cast< unsigned >(c) <= 255 && std::isspace(c) != 0;
#endif
    }

    static bool ispunct(char_type c)
    {
#if !defined(BOOST_NO_CWCTYPE)
      return traits_extension_details<traits, sizeof(char_type)>::ispunct(c);
#else
      return static_cast< unsigned >(c) <= 255 && std::ispunct(c) != 0;
#endif
    }
  };

  // The assign_or_plus_equal struct contains functions that implement
  // assign, +=, and clearing based on the iterator type.  The
  // generic case does nothing for plus_equal and clearing, while
  // passing through the call for assign.
  //
  // When an input iterator is being used, the situation is reversed.
  // The assign method does nothing, plus_equal invokes operator +=,
  // and the clearing method sets the supplied token to the default
  // token constructor's result.
  //

  template<class IteratorTag>
  struct assign_or_plus_equal {
    template<class Iterator, class Token>
    static void assign(Iterator b, Iterator e, Token &t) {
      t.assign(b, e);
    }

    template<class Token, class Value>
    static void plus_equal(Token &, const Value &) { }

    // If we are doing an assign, there is no need for the
    // the clear.
    //
    template<class Token>
    static void clear(Token &) { }
  };

  template <>
  struct assign_or_plus_equal<std::input_iterator_tag> {
    template<class Iterator, class Token>
    static void assign(Iterator , Iterator , Token &) { }
    template<class Token, class Value>
    static void plus_equal(Token &t, const Value &v) {
      t += v;
    }
    template<class Token>
    static void clear(Token &t) {
      t = Token();
    }
  };


  template<class Iterator>
  struct pointer_iterator_category{
    typedef std::random_access_iterator_tag type;
  };


  template<class Iterator>
  struct class_iterator_category{
    typedef typename Iterator::iterator_category type;
  };



  // This portably gets the iterator_tag without partial template specialization
  template<class Iterator>
    struct get_iterator_category{
    typedef typename mpl::if_<is_pointer<Iterator>,
      pointer_iterator_category<Iterator>,
      class_iterator_category<Iterator>
    >::type cat;

    typedef typename cat::type iterator_category;
  };


  } // namespace tokenizer_detail


  //===========================================================================
  // The offset_separator class, which is a model of TokenizerFunction.
  // Offset breaks a string into tokens based on a range of offsets

  class offset_separator {
  private:

    std::vector<int> offsets_;
    unsigned int current_offset_;
    bool wrap_offsets_;
    bool return_partial_last_;

  public:
    template <typename Iter>
    offset_separator(Iter begin, Iter end, bool wrap_offsets = true,
                     bool return_partial_last = true)
      : offsets_(begin,end), current_offset_(0),
        wrap_offsets_(wrap_offsets),
        return_partial_last_(return_partial_last) { }

    offset_separator()
      : offsets_(1,1), current_offset_(),
        wrap_offsets_(true), return_partial_last_(true) { }

    void reset() {
      current_offset_ = 0;
    }

    template <typename InputIterator, typename Token>
    bool operator()(InputIterator& next, InputIterator end, Token& tok)
    {
      typedef tokenizer_detail::assign_or_plus_equal<
        BOOST_DEDUCED_TYPENAME tokenizer_detail::get_iterator_category<
          InputIterator
        >::iterator_category
      > assigner;

      BOOST_ASSERT(!offsets_.empty());

      assigner::clear(tok);
      InputIterator start(next);

      if (next == end)
        return false;

      if (current_offset_ == offsets_.size())
      {
        if (wrap_offsets_)
          current_offset_=0;
        else
          return false;
      }

      int c = offsets_[current_offset_];
      int i = 0;
      for (; i < c; ++i) {
        if (next == end)break;
        assigner::plus_equal(tok,*next++);
      }
      assigner::assign(start,next,tok);

      if (!return_partial_last_)
        if (i < (c-1) )
          return false;

      ++current_offset_;
      return true;
    }
  };


  //===========================================================================
  // The char_separator class breaks a sequence of characters into
  // tokens based on the character delimiters (very much like bad old
  // strtok). A delimiter character can either be kept or dropped. A
  // kept delimiter shows up as an output token, whereas a dropped
  // delimiter does not.

  // This class replaces the char_delimiters_separator class. The
  // constructor for the char_delimiters_separator class was too
  // confusing and needed to be deprecated. However, because of the
  // default arguments to the constructor, adding the new constructor
  // would cause ambiguity, so instead I deprecated the whole class.
  // The implementation of the class was also simplified considerably.

  enum empty_token_policy { drop_empty_tokens, keep_empty_tokens };

  // The out of the box GCC 2.95 on cygwin does not have a char_traits class.
  template <typename Char,
    typename Tr = BOOST_DEDUCED_TYPENAME std::basic_string<Char>::traits_type >
  class char_separator
  {
    typedef tokenizer_detail::traits_extension<Tr> Traits;
    typedef std::basic_string<Char,Tr> string_type;
  public:
    explicit
    char_separator(const Char* dropped_delims,
                   const Char* kept_delims = 0,
                   empty_token_policy empty_tokens = drop_empty_tokens)
      : m_dropped_delims(dropped_delims),
        m_use_ispunct(false),
        m_use_isspace(false),
        m_empty_tokens(empty_tokens),
        m_output_done(false)
    {
      // Borland workaround
      if (kept_delims)
        m_kept_delims = kept_delims;
    }

                // use ispunct() for kept delimiters and isspace for dropped.
    explicit
    char_separator()
      : m_use_ispunct(true),
        m_use_isspace(true),
        m_empty_tokens(drop_empty_tokens),
        m_output_done(false) { }

    void reset() { }

    template <typename InputIterator, typename Token>
    bool operator()(InputIterator& next, InputIterator end, Token& tok)
    {
      typedef tokenizer_detail::assign_or_plus_equal<
        BOOST_DEDUCED_TYPENAME tokenizer_detail::get_iterator_category<
          InputIterator
        >::iterator_category
      > assigner;

      assigner::clear(tok);

      // skip past all dropped_delims
      if (m_empty_tokens == drop_empty_tokens)
        for (; next != end  && is_dropped(*next); ++next)
          { }

      InputIterator start(next);

      if (m_empty_tokens == drop_empty_tokens) {

        if (next == end)
          return false;


        // if we are on a kept_delims move past it and stop
        if (is_kept(*next)) {
          assigner::plus_equal(tok,*next);
          ++next;
        } else
          // append all the non delim characters
          for (; next != end && !is_dropped(*next) && !is_kept(*next); ++next)
            assigner::plus_equal(tok,*next);
      }
      else { // m_empty_tokens == keep_empty_tokens

        // Handle empty token at the end
        if (next == end)
        {
          if (m_output_done == false)
          {
            m_output_done = true;
            assigner::assign(start,next,tok);
            return true;
          }
          else
            return false;
        }

        if (is_kept(*next)) {
          if (m_output_done == false)
            m_output_done = true;
          else {
            assigner::plus_equal(tok,*next);
            ++next;
            m_output_done = false;
          }
        }
        else if (m_output_done == false && is_dropped(*next)) {
          m_output_done = true;
        }
        else {
          if (is_dropped(*next))
            start=++next;
          for (; next != end && !is_dropped(*next) && !is_kept(*next); ++next)
            assigner::plus_equal(tok,*next);
          m_output_done = true;
        }
      }
      assigner::assign(start,next,tok);
      return true;
    }

  private:
    string_type m_kept_delims;
    string_type m_dropped_delims;
    bool m_use_ispunct;
    bool m_use_isspace;
    empty_token_policy m_empty_tokens;
    bool m_output_done;

    bool is_kept(Char E) const
    {
      if (m_kept_delims.length())
        return m_kept_delims.find(E) != string_type::npos;
      else if (m_use_ispunct) {
        return Traits::ispunct(E) != 0;
      } else
        return false;
    }
    bool is_dropped(Char E) const
    {
      if (m_dropped_delims.length())
        return m_dropped_delims.find(E) != string_type::npos;
      else if (m_use_isspace) {
        return Traits::isspace(E) != 0;
      } else
        return false;
    }
  };

  //===========================================================================
  // The following class is DEPRECATED, use class char_separators instead.
  //
  // The char_delimiters_separator class, which is a model of
  // TokenizerFunction.  char_delimiters_separator breaks a string
  // into tokens based on character delimiters. There are 2 types of
  // delimiters. returnable delimiters can be returned as
  // tokens. These are often punctuation. nonreturnable delimiters
  // cannot be returned as tokens. These are often whitespace

  // The out of the box GCC 2.95 on cygwin does not have a char_traits class.
  template <class Char,
    class Tr = BOOST_DEDUCED_TYPENAME std::basic_string<Char>::traits_type >
  class char_delimiters_separator {
  private:

    typedef tokenizer_detail::traits_extension<Tr> Traits;
    typedef std::basic_string<Char,Tr> string_type;
    string_type returnable_;
    string_type nonreturnable_;
    bool return_delims_;
    bool no_ispunct_;
    bool no_isspace_;

    bool is_ret(Char E)const
    {
      if (returnable_.length())
        return  returnable_.find(E) != string_type::npos;
      else{
        if (no_ispunct_) {return false;}
        else{
          int r = Traits::ispunct(E);
          return r != 0;
        }
      }
    }
    bool is_nonret(Char E)const
    {
      if (nonreturnable_.length())
        return  nonreturnable_.find(E) != string_type::npos;
      else{
        if (no_isspace_) {return false;}
        else{
          int r = Traits::isspace(E);
          return r != 0;
        }
      }
    }

  public:
    explicit char_delimiters_separator(bool return_delims = false,
                                       const Char* returnable = 0,
                                       const Char* nonreturnable = 0)
      : returnable_(returnable ? returnable : string_type().c_str()),
        nonreturnable_(nonreturnable ? nonreturnable:string_type().c_str()),
        return_delims_(return_delims), no_ispunct_(returnable!=0),
        no_isspace_(nonreturnable!=0) { }

    void reset() { }

  public:

     template <typename InputIterator, typename Token>
     bool operator()(InputIterator& next, InputIterator end,Token& tok) {
     tok = Token();

     // skip past all nonreturnable delims
     // skip past the returnable only if we are not returning delims
     for (;next!=end && ( is_nonret(*next) || (is_ret(*next)
       && !return_delims_ ) );++next) { }

     if (next == end) {
       return false;
     }

     // if we are to return delims and we are one a returnable one
     // move past it and stop
     if (is_ret(*next) && return_delims_) {
       tok+=*next;
       ++next;
     }
     else
       // append all the non delim characters
       for (;next!=end && !is_nonret(*next) && !is_ret(*next);++next)
         tok+=*next;


     return true;
   }
  };


} //namespace boost

#endif

/* token_functions.hpp
33i7spQHS2RQKlRIDuuH4dKKq9fN3QCBU3Zcq7ugIKXLw5oZPrPjiwf79JkQpleFsjXQbwVzPhXOn7cULwG6s7s1Zi9ez5S3+OP6mAx5Y0RwqAbmHpWRDI0AaFzv4jf+FH7engbAb7mjA7Kz29EEjR2w0YfW38WQuLTcrjdGhhwl4s3CO1WAmOCYHsFgg8iJfObWY+eWSUjZnp5jQ/rlmQvmiF2HIdkUouVTFnhRAjEFVTDIZWH6IhBgl43iN286CAK4GgEfMXBiU7tswGYJNU9t9v+d9TBJho9YHtqBsdjhdlTgF1XwKZ7/5BBGbrwruUHSiy6a/oTrGo+0A0cn+zWH7rHWERcpedq6qUJiI8zSHbmr3hOFErG7kJwXWUqMINTXT/NBwGqzEV97uaSk/Lfst1UYl0ve8e4k4sl6MD2YYubiqk0N9WzDxdx+Y8QtVOEhw2wKl273LI72V4Vo8nIvfNhLpFh95RyZ+LCZbsGcGvxYUsQq+9GH5aeX+UA6xp9LfKExOeS/GAdHUvsxO99J4OFdRbVBqabG9Sx27ypjpTTGAVUgvTttxKxOBnBquiExe3tFhdM6HBcEeK+hP8bSudxBAMqaRkeHS+zeVpCvj4YnEpGZVWiDGeIaWYMGuYJI7K1XGGcXsnVRG0zLpJ5NDR5RWU7Roh5RKy8si1JEUpO3XTnRwZ4cJ6jMva2VXbAE9aLjrz/FiVKGuhldsf+Y65KVv3Hxxr8TH1KZhPkZrGPysg50z7gjJFALZCyctub5skigTpdvG4J+BMxePuMrWhwe+MkUZ0j4PYGvVQkCAPNld+5gp1JY8u3eGqPl9LatfehaKWywRiA/R3vlEaScAi3gwoKEDg0fkwfFXGcnjzbq+y6pV5kH/ikDzp38hvuTT2ynXcqzymq2gaYfvxKpcLf0hI8Ix8ZisWJ2WQcO7S2ZXD80McySJ9WIQQr1uIhIjX/LFtRhy2C+MEaktJz4g9+ng5/za9ymHxwOGKDsLjrKzQRWrqAlORa05SkmdEB5Opp8f+rh+A+Fmee9JDyuG3ozWhy3FOYyK4WjPIVjnaHhE3PpJQ8pL9VXjGRyGDAD8WB/YLP+vbmRNt/WPlxp26od3PHMs7WGh5A39SZFF0sPicUJVpaMQEdePOvolBbj8MAPUQDmBB+yiiNZXs7i+3PqMleUQSuQiY6ZubDniNozx861VgJfx1A+l9Cmx9ldJZ5Q12DwzefM2cUYHzRufZdKwaJRHCIFAFwaQY6IYKOK6GGGOtDhBMGKokAIg4KDURcNEynhM0ztLZMyHeaK2ZgJWxrO8lQ6zgY593XiN4kaS71/QhcLe/ackLvEmihy84ZlMIHyNNxnJy4nfm1pgu3L1L+SjuEXTerEkRbij1WJ+hx5Ydg/4VG2QFK2CLJLtAT4ycKNkGJmHa592FBZs5sEqVGrNzbAV7IBTy5+ovj8lZ8xYMVNELCynWSfjOBnl6Z6B14JY9MDN6TQ73CoBo6ZLFqIILpKNiT6Wy5ywH+jgjMzQNGz7RmdbxLg7q7s61Ihk4tx35KeIqmJ7GA65BIKf7juy5OYrMBMg8WDyboi+cYOIjp8G5KkWXOEAW7t/BQH3hgbr9CSIUkF2ofd4z3sN3lGSSSnLAPA+pJRtfjBkLujMuRJ1iUWpDqVuI0HQKw4n1mg4uQS9jM3M5CYBBz/ZSBablHpVqbRGiMVIkcqRQsopkU3i+vOx8mERZ0EHjFfxDun1blgLcFFu/7qWnYgr2/D548lOc2bgH+9xVV/YYlh0431dniZn5KZcYUnKgPEXVOhyGyWWGIlB+0l0gODzrDw4P1evCf3V1EfLrUtvIzuGWZet+rcUVEw1RLmsFd5ywfYXaeX3fDs8h1Ydz2KKX1E03qYMLX95KSSeWK9HKDy6Y6iT1nRQWfffBilIZxoTnPlud9xjcg2ZzuaDxJQlqtXWql+Q/ce3/NTFWTWLw+o1v71Hh64hUTYXd1PsBQ/ETdvGpgumtpIaNpDgIYXVJetwZDpnJLm20zExOs9QZpe0btL5ypuD/GNfmOil0HabY0wcD5Rve3HPNUHQAvVJbhREbvr48xxNearhBwCKTBLJsic+uCkCfUkZAvTMQEJmSwU5JTm9WCFtTuKneTqnFnC6Xkxgr/FgjBNmFlzKBU7vcd4m8cwDOrxlhUlMJ+U39HRP5q/zuDbSpB+4FEuG8e8KCAVBwSDcgv1iX/H+VQVJ9twK4doAX6CxBzDhbxNY/ExwmRadhFcqXnfY+hLQTwJ7xa8Uhyttda0pCwuynuyMO0hPBellkMH00IaSMWDN+nLiSXPFbuAl9LwQT3fNobvBXP8QHb3fvUrT/2PRc1XfXzmpi5kq+rHaC/oFW0uRz9EpoEsBdC1q/Ojkvb7GwebJ80gmSRDnsNqojVkUwhY0I3Ozw9F7s/64CU3uPFR9MKrLlyH+B7a0H0WIVQoZToAXPUUSVBbqWqDShm1iYSh171lwcvyqzt0AFmP4Mtkj9WIyLrVSDc2YyYQ8IwO+qijMDqurk5ehKW+TjjQDbeSihQ3yWOwkcrHIp/J7cn5XLTs28P9QN0HE8Am9S/oNHTxKrJosfjEtkO1wCqsCnz6yuT8vDnC5oz9CBMupeE5FKzi6+aTDaQ6clfLQ4Q9Ppf1CBy/Ae873q2yeDMd19DRkYiH7x0dSxFIYHcsKB03GKDAzgxlP70HQhlsq8q6PcxPgGZ8mI3PJ7avWaz6tRoWp/ER7ulR06tOgU5b7TLzHbzk+1W3cDeeZu6D0McqyYFKxVhSGWL/cXahXUG3qx7isspIVm4jt5FHBOT+PQLRY6sWHcHB7cegqS7EO5ohtogry4GfE19RLEtUjJaxHrZILLWVgKQZu6iGb0XFiEt46+MsO5krhA1PH8OFP/1bt/gsKntg7/1OIvSh/NWeZXRznSbuxKhy1p8dGaalSmDXFA1Qcj4YPhdqiZ2S7IASWYvBGKvzQ9sy4JRX9h8I4l11O7eKpRIxesnVIPeH/SM5v/D75/x3AJ9C/zgDD30iiUip7UcDkssX99+gfkJ4Q+lARTEEtQYo+Ysy+6TqodGJc6SerTzF4GGQtWVSrlUQ5V3F8WW6rvJ1DkeGhqtH/S5+2qtRy+pUTk/rtiTZheNYWmgVA990Im1+wcsBkS+JCPPlkoaGNP3V+YR7PbMbZUghhR98zJZs9n0SBAQUEkLf5NB1Kh4zieHjOQK4NzHdrdQzu6oPfSILc57DQ7yU2nYZVLwUkJdKfr521pwUz/TiJ50X5UxLEAlDiqFAIOgTOPqsrw/zF3sFA851Q2VGfq/xSAHvhbWM7KLBoTbs0M1KOfjJiMtIRiangeSRxLvbS1uH4G2KZN9BU691aN0GxtrQ4ikW/0rBoIXqGhhWsr3IEXdoaOKOXjMpeAbNo2a9pMoeqI8NkZeAiqVOMVofEDW0OLglj9BdeGAyyXtMoo2S9dQ5dJXNickoCHdbIaj2zE9uWQW/BZm2zi0GKPRVNdmfB34nwB04T80tS4N41askYTYR0k/sba2w1yliQVLW36eIZe3UrYGf2PnWLlOkoHHsB51TwFIXLREGFE6UOVXBLw2f+DsPvx8ivFmCIzssdwGO161aYgYbA9tqu/8NB8xAF0I9C9z3QduRCIjcYojr2nTUt5NZcAhbiZYW0rnBid+JplNkJ6qQ/eEDu9G8D/SpwMjcEP2cnkVjGMl9ginWjA/DuFuqu1ICfcj8Z0p8dXbYUNTN2UGnMYtGgq7nA2GlUCkqcDrK1br9jguCvDxC8P53hJs9r/dJW6E3PQOkEC3NOL1qDRnkE4a/CbvRZ4YVn6vONUpKHlwsru78w1q6MjZ32zJbOPDlrPmHgSE5en4cvk5eNZIcWekB1OeKXav2sj90QSznhuwTGYUkFHLrjRh3y8exJrn3gfEPqMUlp2wf24Al0nasDllOjGw79TX2t8iVy6S9YBT7g5gKUwKqyhhkOQRVSnI9WmYSWX5GEEdeBOoxkV+c7zZYgBGnKvm9xS6xjyHMYOysFwvR1HvHdt65+UKvKTcmltdTa/dTiMJ9FTtalZ1dy12jUJjfwvBbqWn1F/I27HPQpWIKhLWV2X5SF8dCqWriN7qh5XtezU/9fsiN4p5FzHR7ETdb/b9nz8wkHvJlsxl7hAx2LtuUvj0PAMrDIAbYWSCk9GRw5EZ3YDyxnQFfRBWQ6800XmKgmaG3wfVZLvJ0XAyuoKYuHDHiLW6RyjgZz+AIBaC+sABehMHLVV8E6fMFKD8cr132MfIiyKEWpMaLpGNKzxRRNME3XK6OqHR0jKJjJxmxvCR3dlNWcu32wPqNm5rGTBYnB7KGfqKGQO7apesHWDds7pmV1Yvdx3ln/Ozkfdt/B5X1C15gsICnF4uIyW7fu9onlTaIcCvP8pMu9ut0ZxlfbQzvmBRmUo+hIEzkp3tWjL0apVlleCMjKJZW64LzGi2mOOC/gKzZ/8BT0e4y++pMNi8NBVfTZy2llsoBtYeim7/SM4toVrx1hcWgV/VTWWdO3aYpy7B6c+zM4Ip/RXMa7P54eZcZY647GrL0A0eyUcyf3m4J9nPOyh86rHO+FK2G90pIGXglzWKOwTpckZFS3QwNU2tZBrZKaWco4YVljA282t6eO9zjkwO0ugsgJKDJDI7w+udUZC645EnAfGOthhxcoudzvpxnc+UrA3hcziJhxIsE3CV1SRkpdMSjgEHghCdmGygFOAV1xhpN0w3ehExuiduWCtAEDD0SAJ960/1pZr/HF8cWF0NOVxqRQJToV8FcQJpz+VU3khqDacssriL3UJAo7UlVRf76G7BNFu4+i7S4uFt8TdQGxXLswVh5OdkU21ExVvAUEe330W56xkowchiYEJRCgNZzfNkzwPRHXOs7wzdrmaojAC00tVvgkQgLQhlztOkzvz4Bh64jtdPyd9kvyB2etD4xeMs+xQmx7FJvWBLktq6EAQEIWyu90KbpqM+yZogXJmDM0kMZ/Ckk7Ph6ErcQrFWRKh5VFMt2+rHibuaswjK1oKdgZytnGo0YofyFU52i4ICXs90a2iD7NgeZAO02y3Mf0zTV+qEXL5C1xFFUen8howp2qm3wPYE8XSbC+fvQ1+vPfhOeoj6qNVI7GkM34HLaLDudq9qo62mNz1LqYZBVwcdZSj0OF/B0TQSAKR6I2hDnIrb7qjhjSsNBLYlLlY2A3btEHkY5MeTDweaeSe7BfpbJ8YmqxKIW8KeSZjn0UZqZOav2ow6qI9dZ57JtiBb74CwwkTeW+QP5BLmy7Nfn7hNqwyWR2UWvsJ2ADUBnS7yX4LW1EnDiRvhHIdwIue1JJZpL9jwHIsP1wfXnqCx74SaVixdhB4/utENo4KMKbGQm/sZRVrP2l9d69CdgFqyoT6hh40OA2Pwc2D4RcoJodnZaZZ5ns9mSV6l0DUKMa0nzuM4fNCztZTXvQfz8ojpDPU57RY+B3xNvr3oSDI24cadbkAr3mNNnyvpK2Lfsr+Y0LXUR/zWfeF5v9+MbFudSIwia/TLEq2PlabSzmlJCDClITyHKCOBlgMNRUxT6qRIfphIxxuh0awKz1CEEewjH25oSwnBZx6oZCchqkSSofANihP+nmaZOpvELluzkLNE6fe4htr41T4e52nE7uf6oD8OT4ou2OpjGHiTuk2ImRPLkgoa1W7tz39BRE1oqFoVWLCyrpOBKbC2LkWRvqBzG9BzJT6tfEOUWOEonJuZROI5zpVolCHXSSuE9pieHi5hWowbNNMJEdxVWrMNdXoQUxw5dheWNVF1lSoMxxjNZifsfqQnHWzIAcfOPbSHL0og8HGp800HictITiIwFWduChqIx0t5dDfgqMp7lyBMUNjYi2pMEVZ/QxrrRqe5v366fkxIPtbSbbUdRrJhCE0Fnwzn0KhgV+NZdNO/6dWtRAeXHfTPWMQAh2ochB3MEwk2BKm2roVChpcw2LjmrOJ1/AeOzwmJt+gtasP+lGpq3vAS6H8tXDdNaqB83jKymJ0yl6bX87fX0rcWU2toX67eyTPN8mc0unppMGDakQqPzfFBwCbOaS7GvpRc4rFkD3eBtMq9cUgKttr4XEIfHnCJozujvSlkjojQnHA9Y1upMYp8yvotzpTBGQ9gwV/pL0ZhdUlIKn9IKlXBt6aTk2fTxSmfILlnDLIwsrVUfmWQB+aSTam5KLbrfhNpjSqEE5GLJo3Jxqf9Y71rJclEuFaGSSp4RPo3eks73krOEAayKSOLsL390nCJqucrJBXEdUFWul776i5dmzTt4cbzyQMW1orhI2ElmYZLRCnBPsB5gNsx9QKFUKhOr6GU4tF4BfYgP4f9Ipg97VvCSkouiBwCy5Wt3Et+8ifdD7p0L3iQorrEFcbo6tum+ugQJ0Pbq8pyjWNFvbgOWhTUh8JO655S63960MKJjWmO2NA+0vYZBKVQQ4q1plv/gM5IpCz930xqLVs2drl5pKvECA8pQb6+XLrjM87S0RTcGMhYAvXNiyH6Ka+V0x2O7qajeA2kJIaGStCnetNcnwUCkOhpQF8dSnscqm2t5NSEuNa74N2I7zxu0bAVci6p7C7CTDaoVMzmZP7RhXegj+aA2iBBsDg7n8bQ8capGI8PwE78Xy8Kq1Qd/e4/ZzcqV3nnuLbSdCdp32UQ1w1r/cj9UcD8Bpp7ni0cUad85ZiRoMB/JpfDNKHk1dlbc0hmcXYMxT6BWj255JqLx3eIRozhGotPQAa8Y/Jbn2o0WijyeYTK+6b5q+j+xZTgpct72+GdxGXfT6l+zubZ2n8I6bKRA4hntJ2ax/2kbPy0AO1l6KT5EEnzDad+/BAbtafLDgQWPoDHpaM8I6hwAlc/gT20Ybcj7iIp88ui7Rvg8W7q3RFJ2Ck1F13Ctm2CJNg98CH0csS+bdgEw5IhGiOprYI4lqwJW3zsv6E7267vyt8uHVXMaJFxo1ei/oEcHOhE1vzWDLF76o5GbNc0xg+iyLaE2QqdvOoAK6EKeS0cIfKs5vQniWAwVZb8TUI2B2+u5WPvuCLcdpZUjD52DJ4/y6wCUoXkS8QSIsAGA77bWjjoEdDi1b0t1g8r11u9XabSpox8FXxKRmw+e1nvny4lffZP2fYss8ekBhEg/G+wUQDJDeCdLynoiaqz1XcOub/9OAwMHlJocCBgIRp0SkxWrMnOXtR58BucZJ6Kob8ZTlgWf4U7XDBxd6eQBpw1GH5DXBpsnX02k/B2M5BjEbqRYnNbn9ytqrOmzPHDRyMZA15+Xv5jxGY3PA5zzhXeW15H/OJXWpHyWu8k2JktZGV/3F3LrBuPjgSsIjdz7N3q1TAr62RA1p+7RHp1cZ30nAj1zk6X/OydneNeO2PdILouM2d6ChRHjhL/6B0N/ud3+aby8gn6iKIHoIOxscQYGskmPOoESyKNWoMnjsWzmQPC75ZtamJs5ZhVpR0KKRwejWdIDyHMYzxABMqsgHhAYOlwzbf4jcJxv8DaMQlzRvtbM1/XLay8Dedj/WTB3xJE5uM9+rF1TD7tsD3Rxi4s3vk03AijZ02U1IEv6RtGdPqIxdqJKBfjKU/KVTjkHISspzPMy1Psb9rLw8goHel/JVcHm6iwwk6dzbifjGgJrJotpIXnMAyxWKbc+YD7FKW0TjjSeQshl0RYe66V9gLwtPujmCrnikJ4YHYyNoD1pZfA9+taSrUdvOczciA/zB8yH3pxp/JxTp4wPfQ8emzL0NT5lCBH6D9KGiPYeH+Bqx3YqvDYS3mUt9/ecOHYx6A1sutNpvGxwSp4Mn5VjQBG4hD5qsBj80emQ3xIjzwuny9MUfJPUMiOuB09Quj32MS89kixo10hUr81neXqV/LXL2v/EiqWfyLx4LBGMgmIh5vXEiXtVHo+FDxOan+RRIR5ukrXSAbgGK55oHi1UBxFqZmoGqfcAqBWSY+tc7ZjiX2XcejIU95q8F61m5vRnyiFWAa4+tPUrNF9Dsu80rSNPit4hbOmNeiSiksw8cBMxztD7PGRXhn9tq56bZ4uKxfzXD1CvWrLzmJHktKK65otpwLNDh1ZPv1rt8PwYSkq4HEZJFs/FF+s5msYh9QWJd5DcoFNAdUZf4nCLTKoITgAALP/Th9Wy0gj0mX7GysHj9Se/2ZtI8i2hWoHimh0cQGjaEthTmRUnkGz7nOc649u8AIe+shrMmyX72qyqIuTeXEFUjyZ2aVEJVXgqMzeZZU1qxqq8r7C+mOs/J7Fq510jFZVEo9ALud4Dy3CcjxgpcJIZrOFzaYnaik10jftHEzJ1CLUDeSFHzH3skfXVngh6aFE4ZEBnz0ht31wOBvPWQmFo+nlAbFYQSomd9yMF4GnxpAtyYV+ygm6mAPOVdOWXP1VBx+wXUgEbDfLBzQ+CrdBNVU5LBg0B9RpPpofQUFhn/zck7nTIf3/v6Leyqa/FL7ooWhMhogycwWjomOlCsl6T621yohFK34ptTKfCiPf58Wvnxoz1JGu6AWEKkIpyXAnsxJP14/hMCY9OtHCrJ+2kEdXU326GqZwGDLk/oVKwRYb4m8Fa7dG5sJWJyZfSgw9etlE+LEoA+hzdnMDayypSLiVhhM31cAYxrcoh3RN6RNZv1sIZb8e9aODKLwpLrhdJIsh/CMO67XLEYYwp5IvSHjYryQbqkqlWDOWTTtD7A/czRdqT8ciRCGLEE7tc3n1KrH1zCcqGqyFI2o7fLoroPnL1UkM4lByRf3iixNYtSQN8mGN1sO6d8WPFTJFeQzDpPjYIsNtCeEyTTWH5xZ1FxwvJMp1MwcFRhnWE5ZOQW/lbMX2twyzo0bTO5i0+yN7ZiIscZXlumhzNcxqjquSX9chWzCn7ssBE9vdjVQcZHHT1hJk20yOQp+OubD/aMJNxhlnLBsYAAfN2PnIFL59KNyXSL7GgfFoOZcFcrEfjpm+MtpQX9rhEJ5A7AxULUdJdRz7BO8UZW8bOHL7l+2BxGpd1sQAAAPejks7YJ7/8mlKB7ICZTt7iJGHHQxuiwxH6ilyQh3BEJd0dkAcuZlFXCnQLeKsQCuQy7Zdci7pmNnkBXDFs0L3LV3j93cXT6E0pos4S6vAM7hh2L88LuN5ExE/Ym+CyLCiwWgq/e+TxUiwuKpobRWKRfU/qWnZxEIK3mXsogFsa408=
*/