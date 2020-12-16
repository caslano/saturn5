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
xuHPASEP/vjdi1C7EP2cazgRrSjgJ4PinlU57BnmuE7lcGSWIzadk7syTH4wJ/dkmJya1o61H50nSIc64cILS3HmGjUDeluu+wlgLsuqXFua4SsDmKdzk8OGy7HSioK3ufldhoUD2zMDiChm8XJEvEWXgpGCKOUnjaUY7DAy6SAMwokgxuVq9R06k+p7JIyMycZcSAQ/8MyAX0v1J2dQRJeqnwFAxtiC+7IeAnexwTCfN8Kq3YveNr/qQ3uKt3NDR4i3mTwcou8yR6m1ZUS16Fo9GW6Hntu4J2Znoqemcq09I9ixSZg2w9YbhmmzMkqLtMrGqp7uEl0FIhbh6OOfhZGhGMCcDH+Ody/+KIc52SLmZA0r2+PuRxfZtgArA462QnI0FNlxL4jz4o8t1E+82UNl4s0ROi42q7MOgPYX2+k+sNhFnaY7Uyar7jRZWCYbmhE05BNi0TcZFSQ8sfDOUa5SyaZn0hsGKSZ9P9Avele25HBe5EH8GsBXQbcVTLcVim4riG4j+Q3odmws1FkN3OtkRWd2lkyR45jMqFacCTAxtC9oLBDWVC4cmH4R3EjBN0NQLqmpxIcHex2/Cuuljmgf5miUUTIl/6F7KPIPB8pHfU7W3mc1lnZWoX+6PYHt/3T3QuMdHFiZp2WxVNWhXNTBL+rgg9ScEHKkxf6FAoX9TEA8eo7D0nl2ekVsP1RFHGZF1jjwuumsXVsR+w9VkUPzVUXey4KK4O016aexNEC/cimgVyLQhQA0/ahksz+ekvdR8mkoVwi682I9WVIVp7UnJ40mpodPHiLMYDQV7KUQfd8OiL5lywRR5qYspKVmqJ4uMNSz+yscTkUcJkE5vEs3Jj0q0gKQf9GKsh5MzqOPqj298kxgsMUw/+K+Htzq/HPM7mg8JJPsrZydfzF/EACMyiRnm9zaNgs+OcPFwjXZimz7oqywd3oZIX2KjlZfOJXpa67o3f+Mx80l1BR9CRVvo1XULJwb7sRJj+cG/pALfAyFmmBQs0sG4MZ/HysoWvFJ3V3nBFngRILQkYwi6cAfI7ezTROpcGBFjovNTctfOcNhjD3TYTRNdRgl0xzG+fA3bDr4gT/LYfS5wGFkzQDf7/D3TL3DuO5ch3EnhPeE7yOBY78Ov/3PdxgvQ9y15zmMDyH+GMhzHvwZPTt/bD3tiUFZ5qvDmZ3j6unE1x65eT175vfM7VmQu3n3s/vZ/fxPPrr93+u7QJ+OIpEscB4XCOISQIMIgHJi63T3cPia1ZtD3Sc6Tx46xKBICHEUpykjtX4vSPs/XBpbAKO9TkmQ7qdt3KeyZT9Wt67bh0yAIvATmQGmN8kGJnyoGmdKNKwZ7fo5CkfF0pJoGINpYDDvI5hiBlOMYLg896KRtmRA7sv35FAIWFAO1jvzZuHMepkMxNnIicYlnIftjmrZGm0VWSkdyIV/sfcQmcMVOeMmNgOq1TPQlL2/xAFDZh0vqcLSnk9WaBTDvG1vqlAAK3Q8bHJgEpukBpxS4NxhDxcB5X6U4+VAafg7tnJ9RRbtnh4v8dPTD75bP8XJGC4WBdSyLXazK5FkF51pYn2AiCTy1EA8Xg3eAFeDq/B4K0bVASFiJXri2s4T71Ljpx14Uvb3CPb3Ia/KTRDPG2oT5A1lx6KOwamrb6QVhmbgNFn81ggbFK9NGqbgG6p7eMSyUDkrF0GTIcNPxDGThVvtwEAovATD+6lwB4S7MNzLoNHWzu6+/BqDVlsMcLr7J8527xDjknxSZldTV5oJ0c4vIdRabjUN1IkSycY+GpThlP6ioTKyaWh4KZ+rmduXilsqE7ZdaMJycZFs/wL4sf2LQBWGcbuOKvG1OgvmlYi5PYQ=
*/