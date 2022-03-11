#ifndef BOOST_DATE_TIME_STRING_PARSE_TREE___HPP__
#define BOOST_DATE_TIME_STRING_PARSE_TREE___HPP__

/* Copyright (c) 2004-2005 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */


#include <boost/algorithm/string/case_conv.hpp>
#include <cctype>
#include <map>
#include <string>
#include <vector>
#include <ostream>
#include <iterator>
#include <algorithm>

namespace boost { namespace date_time {


template<typename charT>
struct parse_match_result
{
  parse_match_result() :
    match_depth(0),
    current_match(PARSE_ERROR)
  {}
  typedef std::basic_string<charT> string_type;
  string_type remaining() const
  {
    if (match_depth == cache.size()) {
      return string_type();
    }
    if (current_match == PARSE_ERROR) {
      return cache;
    }
    //some of the cache was used return the rest
    return string_type(cache, match_depth);
  }
  charT last_char() const
  {
    return cache[cache.size()-1];
  }
  //! Returns true if more characters were parsed than was necessary
  /*! Should be used in conjunction with last_char()
   *  to get the remaining character.
   */
  bool has_remaining() const
  {
    return (cache.size() > match_depth);
  }

  // cache will hold characters that have been read from the stream
  string_type cache;
  unsigned short match_depth;
  short current_match;
  enum PARSE_STATE { PARSE_ERROR = -1 };
};

  //for debug -- really only char streams...
template<typename charT>
std::basic_ostream<charT>&
operator<<(std::basic_ostream<charT>& os, parse_match_result<charT>& mr)
{
  os << "cm: " << mr.current_match
     << " C: '" << mr.cache
     << "' md: " << mr.match_depth
     << " R: " << mr.remaining();
  return os;
}



//! Recursive data structure to allow efficient parsing of various strings
/*! This class provides a quick lookup by building what amounts to a
 *  tree data structure.  It also features a match function which can
 *  can handle nasty input interators by caching values as it recurses
 *  the tree so that it can backtrack as needed.
 */
template<typename charT>
struct string_parse_tree
{
#if BOOST_WORKAROUND( __BORLANDC__, BOOST_TESTED_AT(0x581) )
  typedef std::multimap<charT, string_parse_tree< charT> > ptree_coll;
#else
  typedef std::multimap<charT, string_parse_tree > ptree_coll;
#endif
  typedef typename ptree_coll::value_type value_type;
  typedef typename ptree_coll::iterator iterator;
  typedef typename ptree_coll::const_iterator const_iterator;
  typedef std::basic_string<charT> string_type;
  typedef std::vector<std::basic_string<charT> > collection_type;
  typedef parse_match_result<charT> parse_match_result_type;

  /*! Parameter "starting_point" designates where the numbering begins.
   * A starting_point of zero will start the numbering at zero
   * (Sun=0, Mon=1, ...) were a starting_point of one starts the
   * numbering at one (Jan=1, Feb=2, ...). The default is zero,
   * negative vaules are not allowed */
  string_parse_tree(collection_type names, unsigned int starting_point=0) :
    m_value(parse_match_result_type::PARSE_ERROR)
  {
    // iterate thru all the elements and build the tree
    unsigned short index = 0;
    while (index != names.size() ) {
      string_type s = boost::algorithm::to_lower_copy(names[index]);
      insert(s, static_cast<unsigned short>(index + starting_point));
      index++;
    }
    //set the last tree node = index+1  indicating a value
    index++;
  }


  string_parse_tree(short value = parse_match_result_type::PARSE_ERROR) :
    m_value(value)
  {}
  ptree_coll m_next_chars;
  short m_value;

  void insert(const string_type& s, unsigned short value)
  {
    unsigned int i = 0;
    iterator ti;
    while(i < s.size()) {
      if (i==0) {
        if (i == (s.size()-1)) {
          ti = m_next_chars.insert(value_type(s[i],
                                              string_parse_tree<charT>(value)));
        }
        else {
          ti = m_next_chars.insert(value_type(s[i],
                                              string_parse_tree<charT>()));
        }
      }
      else {
        if (i == (s.size()-1)) {
          ti = ti->second.m_next_chars.insert(value_type(s[i],
                                                         string_parse_tree<charT>(value)));
        }

        else {
          ti = ti->second.m_next_chars.insert(value_type(s[i],
                                                         string_parse_tree<charT>()));
        }

      }
      i++;
    }
  }


  //! Recursive function that finds a matching string in the tree.
  /*! Must check match_results::has_remaining() after match() is
   * called. This is required so the user can determine if
   * stream iterator is already pointing to the expected
   * character or not (match() might advance sitr to next char in stream).
   *
   * A parse_match_result that has been returned from a failed match
   * attempt can be sent in to the match function of a different
   * string_parse_tree to attempt a match there. Use the iterators
   * for the partially consumed stream, the parse_match_result object,
   * and '0' for the level parameter. */
  short
  match(std::istreambuf_iterator<charT>& sitr,
        std::istreambuf_iterator<charT>& stream_end,
        parse_match_result_type& result,
        unsigned int& level)  const
  {

    level++;
    charT c;
    // if we conditionally advance sitr, we won't have
    // to consume the next character past the input
    bool adv_itr = true;
    if (level > result.cache.size()) {
      if (sitr == stream_end) return 0; //bail - input exhausted
      c = static_cast<charT>(std::tolower(*sitr));
      //result.cache += c;
      //sitr++;
    }
    else {
      // if we're looking for characters from the cache,
      // we don't want to increment sitr
      adv_itr = false;
      c = static_cast<charT>(std::tolower(result.cache[level-1]));
    }
    const_iterator litr = m_next_chars.lower_bound(c);
    const_iterator uitr = m_next_chars.upper_bound(c);
    while (litr != uitr) { // equal if not found
      if(adv_itr) {
        sitr++;
        result.cache += c;
      }
      if (litr->second.m_value != -1) { // -1 is default value
        if (result.match_depth < level) {
          result.current_match = litr->second.m_value;
          result.match_depth = static_cast<unsigned short>(level);
        }
        litr->second.match(sitr, stream_end,
                           result, level);
        level--;
      }
      else {
        litr->second.match(sitr, stream_end,
                           result, level);
        level--;
      }

      if(level <= result.cache.size()) {
        adv_itr = false;
      }

      litr++;
    }
    return result.current_match;

  }

  /*! Must check match_results::has_remaining() after match() is
   * called. This is required so the user can determine if
   * stream iterator is already pointing to the expected
   * character or not (match() might advance sitr to next char in stream).
   */
  parse_match_result_type
  match(std::istreambuf_iterator<charT>& sitr,
        std::istreambuf_iterator<charT>& stream_end) const
  {
    // lookup to_lower of char in tree.
    unsigned int level = 0;
    //    string_type cache;
    parse_match_result_type result;
    match(sitr, stream_end, result, level);
    return result;
  }

  void printme(std::ostream& os, int& level)
  {
    level++;
    iterator itr = m_next_chars.begin();
    iterator end = m_next_chars.end();
    //    os << "starting level: " << level << std::endl;
    while (itr != end) {
      os << "level:  " << level
         << " node:  " << itr->first
         << " value: " << itr->second.m_value
         << std::endl;
      itr->second.printme(os, level);
      itr++;
    }
    level--;
  }

  void print(std::ostream& os)
  {
    int level = 0;
    printme(os, level);
  }

  void printmatch(std::ostream& os, charT c)
  {
    iterator litr = m_next_chars.lower_bound(c);
    iterator uitr = m_next_chars.upper_bound(c);
    os << "matches for: " << c << std::endl;
    while (litr != uitr) {
      os << " node:  " << litr->first
         << " value: " << litr->second.m_value
         << std::endl;
      litr++;
    }
  }

};


} } //namespace
#endif

/* string_parse_tree.hpp
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
*/