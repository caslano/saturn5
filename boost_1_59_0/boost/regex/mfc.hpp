/*
 *
 * Copyright (c) 2004
 * John Maddock
 *
 * Use, modification and distribution are subject to the 
 * Boost Software License, Version 1.0. (See accompanying file 
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */

 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE         mfc.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Overloads and helpers for using MFC/ATL string types with Boost.Regex.
  */

#ifndef BOOST_REGEX_MFC_HPP
#define BOOST_REGEX_MFC_HPP

#include <atlsimpstr.h>
#include <boost/regex.hpp>

namespace boost{

//
// define the types used for TCHAR's:
typedef basic_regex<TCHAR> tregex;
typedef match_results<TCHAR const*> tmatch;
typedef regex_iterator<TCHAR const*> tregex_iterator;
typedef regex_token_iterator<TCHAR const*> tregex_token_iterator;

// Obsolete. Remove
#define SIMPLE_STRING_PARAM class B, bool b
#define SIMPLE_STRING_ARG_LIST B, b

//
// define regex creation functions:
//
template <class B, bool b>
inline basic_regex<B> 
make_regex(const ATL::CSimpleStringT<B, b>& s, ::boost::regex_constants::syntax_option_type f = boost::regex_constants::normal)
{
   basic_regex<B> result(s.GetString(), s.GetString() + s.GetLength(), f);
   return result;
}
//
// regex_match overloads:
//
template <class B, bool b, class A, class T>
inline bool regex_match(const ATL::CSimpleStringT<B, b>& s,
                 match_results<const B*, A>& what,
                 const basic_regex<B, T>& e,
                 boost::regex_constants::match_flag_type f = boost::regex_constants::match_default)
{
   return ::boost::regex_match(s.GetString(),
                               s.GetString() + s.GetLength(),
                               what,
                               e,
                               f);
}

template <class B, bool b, class T>
inline bool regex_match(const ATL::CSimpleStringT<B, b>& s,
                 const basic_regex<B, T>& e,
                 boost::regex_constants::match_flag_type f = boost::regex_constants::match_default)
{
   return ::boost::regex_match(s.GetString(),
                               s.GetString() + s.GetLength(),
                               e,
                               f);
}
//
// regex_search overloads:
//
template <class B, bool b, class A, class T>
inline bool regex_search(const ATL::CSimpleStringT<B, b>& s,
                 match_results<const B*, A>& what,
                 const basic_regex<B, T>& e,
                 boost::regex_constants::match_flag_type f = boost::regex_constants::match_default)
{
   return ::boost::regex_search(s.GetString(),
                               s.GetString() + s.GetLength(),
                               what,
                               e,
                               f);
}

template <class B, bool b, class T>
inline bool regex_search(const ATL::CSimpleStringT<B, b>& s,
                 const basic_regex<B, T>& e,
                 boost::regex_constants::match_flag_type f = boost::regex_constants::match_default)
{
   return ::boost::regex_search(s.GetString(),
                               s.GetString() + s.GetLength(),
                               e,
                               f);
}
//
// regex_iterator creation:
//
template <class B, bool b>
inline regex_iterator<B const*> 
make_regex_iterator(const ATL::CSimpleStringT<B, b>& s, const basic_regex<B>& e, ::boost::regex_constants::match_flag_type f = boost::regex_constants::match_default)
{
   regex_iterator<B const*> result(s.GetString(), s.GetString() + s.GetLength(), e, f);
   return result;
}

template <class B, bool b>
inline regex_token_iterator<B const*> 
   make_regex_token_iterator(const ATL::CSimpleStringT<B, b>& s, const basic_regex<B>& e, int sub = 0, ::boost::regex_constants::match_flag_type f = boost::regex_constants::match_default)
{
   regex_token_iterator<B const*> result(s.GetString(), s.GetString() + s.GetLength(), e, sub, f);
   return result;
}

template <class B, bool b>
inline regex_token_iterator<B const*> 
make_regex_token_iterator(const ATL::CSimpleStringT<B, b>& s, const basic_regex<B>& e, const std::vector<int>& subs, ::boost::regex_constants::match_flag_type f = boost::regex_constants::match_default)
{
   regex_token_iterator<B const*> result(s.GetString(), s.GetString() + s.GetLength(), e, subs, f);
   return result;
}

template <class B, bool b, std::size_t N>
inline regex_token_iterator<B const*> 
make_regex_token_iterator(const ATL::CSimpleStringT<B, b>& s, const basic_regex<B>& e, const int (& subs)[N], ::boost::regex_constants::match_flag_type f = boost::regex_constants::match_default)
{
   regex_token_iterator<B const*> result(s.GetString(), s.GetString() + s.GetLength(), e, subs, f);
   return result;
}

template <class OutputIterator, class BidirectionalIterator, class traits,
          class B, bool b>
OutputIterator regex_replace(OutputIterator out,
                           BidirectionalIterator first,
                           BidirectionalIterator last,
                           const basic_regex<B, traits>& e,
                           const ATL::CSimpleStringT<B, b>& fmt,
                           match_flag_type flags = match_default)
{
   return ::boost::regex_replace(out, first, last, e, fmt.GetString(), flags);
}

namespace BOOST_REGEX_DETAIL_NS{

template <class B, bool b>
class mfc_string_out_iterator
{
   ATL::CSimpleStringT<B, b>* out;
public:
   mfc_string_out_iterator(ATL::CSimpleStringT<B, b>& s) : out(&s) {}
   mfc_string_out_iterator& operator++() { return *this; }
   mfc_string_out_iterator& operator++(int) { return *this; }
   mfc_string_out_iterator& operator*() { return *this; }
   mfc_string_out_iterator& operator=(B v) 
   { 
      out->AppendChar(v); 
      return *this; 
   }
   typedef std::ptrdiff_t difference_type;
   typedef B value_type;
   typedef value_type* pointer;
   typedef value_type& reference;
   typedef std::output_iterator_tag iterator_category;
};

}

template <class traits, class B, bool b>
ATL::CSimpleStringT<B, b> regex_replace(const ATL::CSimpleStringT<B, b>& s,
                            const basic_regex<B, traits>& e,
                            const ATL::CSimpleStringT<B, b>& fmt,
                            match_flag_type flags = match_default)
{
   ATL::CSimpleStringT<B, b> result(s.GetManager());
   BOOST_REGEX_DETAIL_NS::mfc_string_out_iterator<B, b> i(result);
   regex_replace(i, s.GetString(), s.GetString() + s.GetLength(), e, fmt.GetString(), flags);
   return result;
}

} // namespace boost.

#endif

/* mfc.hpp
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
*/