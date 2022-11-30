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
#if BOOST_WORKAROUND( BOOST_BORLANDC, BOOST_TESTED_AT(0x581) )
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