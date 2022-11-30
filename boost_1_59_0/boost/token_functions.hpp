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
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
*/