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
  *   FILE         basic_regex_creator.cpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Declares template class basic_regex_creator which fills in
  *                the data members of a regex_data object.
  */

#ifndef BOOST_REGEX_V4_BASIC_REGEX_CREATOR_HPP
#define BOOST_REGEX_V4_BASIC_REGEX_CREATOR_HPP

#include <boost/regex/v4/indexed_bit_flag.hpp>

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4103)
#endif
#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#ifdef BOOST_MSVC
#  pragma warning(push)
#if BOOST_MSVC < 1910
#pragma warning(disable:4800)
#endif
#endif

namespace boost{

namespace BOOST_REGEX_DETAIL_NS{

template <class charT>
struct digraph : public std::pair<charT, charT>
{
   digraph() : std::pair<charT, charT>(charT(0), charT(0)){}
   digraph(charT c1) : std::pair<charT, charT>(c1, charT(0)){}
   digraph(charT c1, charT c2) : std::pair<charT, charT>(c1, c2)
   {}
   digraph(const digraph<charT>& d) : std::pair<charT, charT>(d.first, d.second){}
#ifndef BOOST_NO_CXX11_DEFAULTED_FUNCTIONS
   digraph<charT>& operator=(const digraph<charT>&) = default;
#endif
   template <class Seq>
   digraph(const Seq& s) : std::pair<charT, charT>()
   {
      BOOST_REGEX_ASSERT(s.size() <= 2);
      BOOST_REGEX_ASSERT(s.size());
      this->first = s[0];
      this->second = (s.size() > 1) ? s[1] : 0;
   }
};

template <class charT, class traits>
class basic_char_set
{
public:
   typedef digraph<charT>                   digraph_type;
   typedef typename traits::string_type     string_type;
   typedef typename traits::char_class_type m_type;

   basic_char_set()
   {
      m_negate = false;
      m_has_digraphs = false;
      m_classes = 0;
      m_negated_classes = 0;
      m_empty = true;
   }

   void add_single(const digraph_type& s)
   {
      m_singles.insert(s);
      if(s.second)
         m_has_digraphs = true;
      m_empty = false;
   }
   void add_range(const digraph_type& first, const digraph_type& end)
   {
      m_ranges.push_back(first);
      m_ranges.push_back(end);
      if(first.second)
      {
         m_has_digraphs = true;
         add_single(first);
      }
      if(end.second)
      {
         m_has_digraphs = true;
         add_single(end);
      }
      m_empty = false;
   }
   void add_class(m_type m)
   {
      m_classes |= m;
      m_empty = false;
   }
   void add_negated_class(m_type m)
   {
      m_negated_classes |= m;
      m_empty = false;
   }
   void add_equivalent(const digraph_type& s)
   {
      m_equivalents.insert(s);
      if(s.second)
      {
         m_has_digraphs = true;
         add_single(s);
      }
      m_empty = false;
   }
   void negate()
   { 
      m_negate = true;
      //m_empty = false;
   }

   //
   // accessor functions:
   //
   bool has_digraphs()const
   {
      return m_has_digraphs;
   }
   bool is_negated()const
   {
      return m_negate;
   }
   typedef typename std::vector<digraph_type>::const_iterator  list_iterator;
   typedef typename std::set<digraph_type>::const_iterator     set_iterator;
   set_iterator singles_begin()const
   {
      return m_singles.begin();
   }
   set_iterator singles_end()const
   {
      return m_singles.end();
   }
   list_iterator ranges_begin()const
   {
      return m_ranges.begin();
   }
   list_iterator ranges_end()const
   {
      return m_ranges.end();
   }
   set_iterator equivalents_begin()const
   {
      return m_equivalents.begin();
   }
   set_iterator equivalents_end()const
   {
      return m_equivalents.end();
   }
   m_type classes()const
   {
      return m_classes;
   }
   m_type negated_classes()const
   {
      return m_negated_classes;
   }
   bool empty()const
   {
      return m_empty;
   }
private:
   std::set<digraph_type>    m_singles;         // a list of single characters to match
   std::vector<digraph_type> m_ranges;          // a list of end points of our ranges
   bool                      m_negate;          // true if the set is to be negated
   bool                      m_has_digraphs;    // true if we have digraphs present
   m_type                    m_classes;         // character classes to match
   m_type                    m_negated_classes; // negated character classes to match
   bool                      m_empty;           // whether we've added anything yet
   std::set<digraph_type>    m_equivalents;     // a list of equivalence classes
};
   
template <class charT, class traits>
class basic_regex_creator
{
public:
   basic_regex_creator(regex_data<charT, traits>* data);
   std::ptrdiff_t getoffset(void* addr)
   {
      return getoffset(addr, m_pdata->m_data.data());
   }
   std::ptrdiff_t getoffset(const void* addr, const void* base)
   {
      return static_cast<const char*>(addr) - static_cast<const char*>(base);
   }
   re_syntax_base* getaddress(std::ptrdiff_t off)
   {
      return getaddress(off, m_pdata->m_data.data());
   }
   re_syntax_base* getaddress(std::ptrdiff_t off, void* base)
   {
      return static_cast<re_syntax_base*>(static_cast<void*>(static_cast<char*>(base) + off));
   }
   void init(unsigned l_flags)
   {
      m_pdata->m_flags = l_flags;
      m_icase = l_flags & regex_constants::icase;
   }
   regbase::flag_type flags()
   {
      return m_pdata->m_flags;
   }
   void flags(regbase::flag_type f)
   {
      m_pdata->m_flags = f;
      if(m_icase != static_cast<bool>(f & regbase::icase))
      {
         m_icase = static_cast<bool>(f & regbase::icase);
      }
   }
   re_syntax_base* append_state(syntax_element_type t, std::size_t s = sizeof(re_syntax_base));
   re_syntax_base* insert_state(std::ptrdiff_t pos, syntax_element_type t, std::size_t s = sizeof(re_syntax_base));
   re_literal* append_literal(charT c);
   re_syntax_base* append_set(const basic_char_set<charT, traits>& char_set);
   re_syntax_base* append_set(const basic_char_set<charT, traits>& char_set, mpl::false_*);
   re_syntax_base* append_set(const basic_char_set<charT, traits>& char_set, mpl::true_*);
   void finalize(const charT* p1, const charT* p2);
protected:
   regex_data<charT, traits>*    m_pdata;              // pointer to the basic_regex_data struct we are filling in
   const ::boost::regex_traits_wrapper<traits>&  
                                 m_traits;             // convenience reference to traits class
   re_syntax_base*               m_last_state;         // the last state we added
   bool                          m_icase;              // true for case insensitive matches
   unsigned                      m_repeater_id;        // the state_id of the next repeater
   bool                          m_has_backrefs;       // true if there are actually any backrefs
   indexed_bit_flag              m_backrefs;           // bitmask of permitted backrefs
   boost::uintmax_t              m_bad_repeats;        // bitmask of repeats we can't deduce a startmap for;
   bool                          m_has_recursions;     // set when we have recursive expressions to fixup
   std::vector<unsigned char>    m_recursion_checks;   // notes which recursions we've followed while analysing this expression
   typename traits::char_class_type m_word_mask;       // mask used to determine if a character is a word character
   typename traits::char_class_type m_mask_space;      // mask used to determine if a character is a word character
   typename traits::char_class_type m_lower_mask;       // mask used to determine if a character is a lowercase character
   typename traits::char_class_type m_upper_mask;      // mask used to determine if a character is an uppercase character
   typename traits::char_class_type m_alpha_mask;      // mask used to determine if a character is an alphabetic character
private:
   basic_regex_creator& operator=(const basic_regex_creator&);
   basic_regex_creator(const basic_regex_creator&);

   void fixup_pointers(re_syntax_base* state);
   void fixup_recursions(re_syntax_base* state);
   void create_startmaps(re_syntax_base* state);
   int calculate_backstep(re_syntax_base* state);
   void create_startmap(re_syntax_base* state, unsigned char* l_map, unsigned int* pnull, unsigned char mask);
   unsigned get_restart_type(re_syntax_base* state);
   void set_all_masks(unsigned char* bits, unsigned char);
   bool is_bad_repeat(re_syntax_base* pt);
   void set_bad_repeat(re_syntax_base* pt);
   syntax_element_type get_repeat_type(re_syntax_base* state);
   void probe_leading_repeat(re_syntax_base* state);
};

template <class charT, class traits>
basic_regex_creator<charT, traits>::basic_regex_creator(regex_data<charT, traits>* data)
   : m_pdata(data), m_traits(*(data->m_ptraits)), m_last_state(0), m_icase(false), m_repeater_id(0), 
   m_has_backrefs(false), m_bad_repeats(0), m_has_recursions(false), m_word_mask(0), m_mask_space(0), m_lower_mask(0), m_upper_mask(0), m_alpha_mask(0)
{
   m_pdata->m_data.clear();
   m_pdata->m_status = ::boost::regex_constants::error_ok;
   static const charT w = 'w';
   static const charT s = 's';
   static const charT l[5] = { 'l', 'o', 'w', 'e', 'r', };
   static const charT u[5] = { 'u', 'p', 'p', 'e', 'r', };
   static const charT a[5] = { 'a', 'l', 'p', 'h', 'a', };
   m_word_mask = m_traits.lookup_classname(&w, &w +1);
   m_mask_space = m_traits.lookup_classname(&s, &s +1);
   m_lower_mask = m_traits.lookup_classname(l, l + 5);
   m_upper_mask = m_traits.lookup_classname(u, u + 5);
   m_alpha_mask = m_traits.lookup_classname(a, a + 5);
   m_pdata->m_word_mask = m_word_mask;
   BOOST_REGEX_ASSERT(m_word_mask != 0); 
   BOOST_REGEX_ASSERT(m_mask_space != 0); 
   BOOST_REGEX_ASSERT(m_lower_mask != 0); 
   BOOST_REGEX_ASSERT(m_upper_mask != 0); 
   BOOST_REGEX_ASSERT(m_alpha_mask != 0); 
}

template <class charT, class traits>
re_syntax_base* basic_regex_creator<charT, traits>::append_state(syntax_element_type t, std::size_t s)
{
   // if the state is a backref then make a note of it:
   if(t == syntax_element_backref)
      this->m_has_backrefs = true;
   // append a new state, start by aligning our last one:
   m_pdata->m_data.align();
   // set the offset to the next state in our last one:
   if(m_last_state)
      m_last_state->next.i = m_pdata->m_data.size() - getoffset(m_last_state);
   // now actually extend our data:
   m_last_state = static_cast<re_syntax_base*>(m_pdata->m_data.extend(s));
   // fill in boilerplate options in the new state:
   m_last_state->next.i = 0;
   m_last_state->type = t;
   return m_last_state;
}

template <class charT, class traits>
re_syntax_base* basic_regex_creator<charT, traits>::insert_state(std::ptrdiff_t pos, syntax_element_type t, std::size_t s)
{
   // append a new state, start by aligning our last one:
   m_pdata->m_data.align();
   // set the offset to the next state in our last one:
   if(m_last_state)
      m_last_state->next.i = m_pdata->m_data.size() - getoffset(m_last_state);
   // remember the last state position:
   std::ptrdiff_t off = getoffset(m_last_state) + s;
   // now actually insert our data:
   re_syntax_base* new_state = static_cast<re_syntax_base*>(m_pdata->m_data.insert(pos, s));
   // fill in boilerplate options in the new state:
   new_state->next.i = s;
   new_state->type = t;
   m_last_state = getaddress(off);
   return new_state;
}

template <class charT, class traits>
re_literal* basic_regex_creator<charT, traits>::append_literal(charT c)
{
   re_literal* result;
   // start by seeing if we have an existing re_literal we can extend:
   if((0 == m_last_state) || (m_last_state->type != syntax_element_literal))
   {
      // no existing re_literal, create a new one:
      result = static_cast<re_literal*>(append_state(syntax_element_literal, sizeof(re_literal) + sizeof(charT)));
      result->length = 1;
      *static_cast<charT*>(static_cast<void*>(result+1)) = m_traits.translate(c, m_icase);
   }
   else
   {
      // we have an existing re_literal, extend it:
      std::ptrdiff_t off = getoffset(m_last_state);
      m_pdata->m_data.extend(sizeof(charT));
      m_last_state = result = static_cast<re_literal*>(getaddress(off));
      charT* characters = static_cast<charT*>(static_cast<void*>(result+1));
      characters[result->length] = m_traits.translate(c, m_icase);
      result->length += 1;
   }
   return result;
}

template <class charT, class traits>
inline re_syntax_base* basic_regex_creator<charT, traits>::append_set(
   const basic_char_set<charT, traits>& char_set)
{
   typedef mpl::bool_< (sizeof(charT) == 1) > truth_type;
   return char_set.has_digraphs() 
      ? append_set(char_set, static_cast<mpl::false_*>(0))
      : append_set(char_set, static_cast<truth_type*>(0));
}

template <class charT, class traits>
re_syntax_base* basic_regex_creator<charT, traits>::append_set(
   const basic_char_set<charT, traits>& char_set, mpl::false_*)
{
   typedef typename traits::string_type string_type;
   typedef typename basic_char_set<charT, traits>::list_iterator item_iterator;
   typedef typename basic_char_set<charT, traits>::set_iterator  set_iterator;
   typedef typename traits::char_class_type m_type;
   
   re_set_long<m_type>* result = static_cast<re_set_long<m_type>*>(append_state(syntax_element_long_set, sizeof(re_set_long<m_type>)));
   //
   // fill in the basics:
   //
   result->csingles = static_cast<unsigned int>(::boost::BOOST_REGEX_DETAIL_NS::distance(char_set.singles_begin(), char_set.singles_end()));
   result->cranges = static_cast<unsigned int>(::boost::BOOST_REGEX_DETAIL_NS::distance(char_set.ranges_begin(), char_set.ranges_end())) / 2;
   result->cequivalents = static_cast<unsigned int>(::boost::BOOST_REGEX_DETAIL_NS::distance(char_set.equivalents_begin(), char_set.equivalents_end()));
   result->cclasses = char_set.classes();
   result->cnclasses = char_set.negated_classes();
   if(flags() & regbase::icase)
   {
      // adjust classes as needed:
      if(((result->cclasses & m_lower_mask) == m_lower_mask) || ((result->cclasses & m_upper_mask) == m_upper_mask))
         result->cclasses |= m_alpha_mask;
      if(((result->cnclasses & m_lower_mask) == m_lower_mask) || ((result->cnclasses & m_upper_mask) == m_upper_mask))
         result->cnclasses |= m_alpha_mask;
   }

   result->isnot = char_set.is_negated();
   result->singleton = !char_set.has_digraphs();
   //
   // remember where the state is for later:
   //
   std::ptrdiff_t offset = getoffset(result);
   //
   // now extend with all the singles:
   //
   item_iterator first, last;
   set_iterator sfirst, slast;
   sfirst = char_set.singles_begin();
   slast = char_set.singles_end();
   while(sfirst != slast)
   {
      charT* p = static_cast<charT*>(this->m_pdata->m_data.extend(sizeof(charT) * (sfirst->first == static_cast<charT>(0) ? 1 : sfirst->second ? 3 : 2)));
      p[0] = m_traits.translate(sfirst->first, m_icase);
      if(sfirst->first == static_cast<charT>(0))
      {
         p[0] = 0;
      }
      else if(sfirst->second)
      {
         p[1] = m_traits.translate(sfirst->second, m_icase);
         p[2] = 0;
      }
      else
         p[1] = 0;
      ++sfirst;
   }
   //
   // now extend with all the ranges:
   //
   first = char_set.ranges_begin();
   last = char_set.ranges_end();
   while(first != last)
   {
      // first grab the endpoints of the range:
      digraph<charT> c1 = *first;
      c1.first = this->m_traits.translate(c1.first, this->m_icase);
      c1.second = this->m_traits.translate(c1.second, this->m_icase);
      ++first;
      digraph<charT> c2 = *first;
      c2.first = this->m_traits.translate(c2.first, this->m_icase);
      c2.second = this->m_traits.translate(c2.second, this->m_icase);
      ++first;
      string_type s1, s2;
      // different actions now depending upon whether collation is turned on:
      if(flags() & regex_constants::collate)
      {
         // we need to transform our range into sort keys:
         charT a1[3] = { c1.first, c1.second, charT(0), };
         charT a2[3] = { c2.first, c2.second, charT(0), };
         s1 = this->m_traits.transform(a1, (a1[1] ? a1+2 : a1+1));
         s2 = this->m_traits.transform(a2, (a2[1] ? a2+2 : a2+1));
         if(s1.empty())
            s1 = string_type(1, charT(0));
         if(s2.empty())
            s2 = string_type(1, charT(0));
      }
      else
      {
         if(c1.second)
         {
            s1.insert(s1.end(), c1.first);
            s1.insert(s1.end(), c1.second);
         }
         else
            s1 = string_type(1, c1.first);
         if(c2.second)
         {
            s2.insert(s2.end(), c2.first);
            s2.insert(s2.end(), c2.second);
         }
         else
            s2.insert(s2.end(), c2.first);
      }
      if(s1 > s2)
      {
         // Oops error:
         return 0;
      }
      charT* p = static_cast<charT*>(this->m_pdata->m_data.extend(sizeof(charT) * (s1.size() + s2.size() + 2) ) );
      BOOST_REGEX_DETAIL_NS::copy(s1.begin(), s1.end(), p);
      p[s1.size()] = charT(0);
      p += s1.size() + 1;
      BOOST_REGEX_DETAIL_NS::copy(s2.begin(), s2.end(), p);
      p[s2.size()] = charT(0);
   }
   //
   // now process the equivalence classes:
   //
   sfirst = char_set.equivalents_begin();
   slast = char_set.equivalents_end();
   while(sfirst != slast)
   {
      string_type s;
      if(sfirst->second)
      {
         charT cs[3] = { sfirst->first, sfirst->second, charT(0), };
         s = m_traits.transform_primary(cs, cs+2);
      }
      else
         s = m_traits.transform_primary(&sfirst->first, &sfirst->first+1);
      if(s.empty())
         return 0;  // invalid or unsupported equivalence class
      charT* p = static_cast<charT*>(this->m_pdata->m_data.extend(sizeof(charT) * (s.size()+1) ) );
      BOOST_REGEX_DETAIL_NS::copy(s.begin(), s.end(), p);
      p[s.size()] = charT(0);
      ++sfirst;
   }
   //
   // finally reset the address of our last state:
   //
   m_last_state = result = static_cast<re_set_long<m_type>*>(getaddress(offset));
   return result;
}

template<class T>
inline bool char_less(T t1, T t2)
{
   return t1 < t2;
}
inline bool char_less(char t1, char t2)
{
   return static_cast<unsigned char>(t1) < static_cast<unsigned char>(t2);
}
inline bool char_less(signed char t1, signed char t2)
{
   return static_cast<unsigned char>(t1) < static_cast<unsigned char>(t2);
}

template <class charT, class traits>
re_syntax_base* basic_regex_creator<charT, traits>::append_set(
   const basic_char_set<charT, traits>& char_set, mpl::true_*)
{
   typedef typename traits::string_type string_type;
   typedef typename basic_char_set<charT, traits>::list_iterator item_iterator;
   typedef typename basic_char_set<charT, traits>::set_iterator set_iterator;

   re_set* result = static_cast<re_set*>(append_state(syntax_element_set, sizeof(re_set)));
   bool negate = char_set.is_negated();
   std::memset(result->_map, 0, sizeof(result->_map));
   //
   // handle singles first:
   //
   item_iterator first, last;
   set_iterator sfirst, slast;
   sfirst = char_set.singles_begin();
   slast = char_set.singles_end();
   while(sfirst != slast)
   {
      for(unsigned int i = 0; i < (1 << CHAR_BIT); ++i)
      {
         if(this->m_traits.translate(static_cast<charT>(i), this->m_icase)
            == this->m_traits.translate(sfirst->first, this->m_icase))
            result->_map[i] = true;
      }
      ++sfirst;
   }
   //
   // OK now handle ranges:
   //
   first = char_set.ranges_begin();
   last = char_set.ranges_end();
   while(first != last)
   {
      // first grab the endpoints of the range:
      charT c1 = this->m_traits.translate(first->first, this->m_icase);
      ++first;
      charT c2 = this->m_traits.translate(first->first, this->m_icase);
      ++first;
      // different actions now depending upon whether collation is turned on:
      if(flags() & regex_constants::collate)
      {
         // we need to transform our range into sort keys:
         charT c3[2] = { c1, charT(0), };
         string_type s1 = this->m_traits.transform(c3, c3+1);
         c3[0] = c2;
         string_type s2 = this->m_traits.transform(c3, c3+1);
         if(s1 > s2)
         {
            // Oops error:
            return 0;
         }
         BOOST_REGEX_ASSERT(c3[1] == charT(0));
         for(unsigned i = 0; i < (1u << CHAR_BIT); ++i)
         {
            c3[0] = static_cast<charT>(i);
            string_type s3 = this->m_traits.transform(c3, c3 +1);
            if((s1 <= s3) && (s3 <= s2))
               result->_map[i] = true;
         }
      }
      else
      {
         if(char_less(c2, c1))
         {
            // Oops error:
            return 0;
         }
         // everything in range matches:
         std::memset(result->_map + static_cast<unsigned char>(c1), true, static_cast<unsigned char>(1u) + static_cast<unsigned char>(static_cast<unsigned char>(c2) - static_cast<unsigned char>(c1)));
      }
   }
   //
   // and now the classes:
   //
   typedef typename traits::char_class_type m_type;
   m_type m = char_set.classes();
   if(flags() & regbase::icase)
   {
      // adjust m as needed:
      if(((m & m_lower_mask) == m_lower_mask) || ((m & m_upper_mask) == m_upper_mask))
         m |= m_alpha_mask;
   }
   if(m != 0)
   {
      for(unsigned i = 0; i < (1u << CHAR_BIT); ++i)
      {
         if(this->m_traits.isctype(static_cast<charT>(i), m))
            result->_map[i] = true;
      }
   }
   //
   // and now the negated classes:
   //
   m = char_set.negated_classes();
   if(flags() & regbase::icase)
   {
      // adjust m as needed:
      if(((m & m_lower_mask) == m_lower_mask) || ((m & m_upper_mask) == m_upper_mask))
         m |= m_alpha_mask;
   }
   if(m != 0)
   {
      for(unsigned i = 0; i < (1u << CHAR_BIT); ++i)
      {
         if(0 == this->m_traits.isctype(static_cast<charT>(i), m))
            result->_map[i] = true;
      }
   }
   //
   // now process the equivalence classes:
   //
   sfirst = char_set.equivalents_begin();
   slast = char_set.equivalents_end();
   while(sfirst != slast)
   {
      string_type s;
      BOOST_REGEX_ASSERT(static_cast<charT>(0) == sfirst->second);
      s = m_traits.transform_primary(&sfirst->first, &sfirst->first+1);
      if(s.empty())
         return 0;  // invalid or unsupported equivalence class
      for(unsigned i = 0; i < (1u << CHAR_BIT); ++i)
      {
         charT c[2] = { (static_cast<charT>(i)), charT(0), };
         string_type s2 = this->m_traits.transform_primary(c, c+1);
         if(s == s2)
            result->_map[i] = true;
      }
      ++sfirst;
   }
   if(negate)
   {
      for(unsigned i = 0; i < (1u << CHAR_BIT); ++i)
      {
         result->_map[i] = !(result->_map[i]);
      }
   }
   return result;
}

template <class charT, class traits>
void basic_regex_creator<charT, traits>::finalize(const charT* p1, const charT* p2)
{
   if(this->m_pdata->m_status)
      return;
   // we've added all the states we need, now finish things off.
   // start by adding a terminating state:
   append_state(syntax_element_match);
   // extend storage to store original expression:
   std::ptrdiff_t len = p2 - p1;
   m_pdata->m_expression_len = len;
   charT* ps = static_cast<charT*>(m_pdata->m_data.extend(sizeof(charT) * (1 + (p2 - p1))));
   m_pdata->m_expression = ps;
   BOOST_REGEX_DETAIL_NS::copy(p1, p2, ps);
   ps[p2 - p1] = 0;
   // fill in our other data...
   // successful parsing implies a zero status:
   m_pdata->m_status = 0;
   // get the first state of the machine:
   m_pdata->m_first_state = static_cast<re_syntax_base*>(m_pdata->m_data.data());
   // fixup pointers in the machine:
   fixup_pointers(m_pdata->m_first_state);
   if(m_has_recursions)
   {
      m_pdata->m_has_recursions = true;
      fixup_recursions(m_pdata->m_first_state);
      if(this->m_pdata->m_status)
         return;
   }
   else
      m_pdata->m_has_recursions = false;
   // create nested startmaps:
   create_startmaps(m_pdata->m_first_state);
   // create main startmap:
   std::memset(m_pdata->m_startmap, 0, sizeof(m_pdata->m_startmap));
   m_pdata->m_can_be_null = 0;

   m_bad_repeats = 0;
   if(m_has_recursions)
      m_recursion_checks.assign(1 + m_pdata->m_mark_count, 0u);
   create_startmap(m_pdata->m_first_state, m_pdata->m_startmap, &(m_pdata->m_can_be_null), mask_all);
   // get the restart type:
   m_pdata->m_restart_type = get_restart_type(m_pdata->m_first_state);
   // optimise a leading repeat if there is one:
   probe_leading_repeat(m_pdata->m_first_state);
}

template <class charT, class traits>
void basic_regex_creator<charT, traits>::fixup_pointers(re_syntax_base* state)
{
   while(state)
   {
      switch(state->type)
      {
      case syntax_element_recurse:
         m_has_recursions = true;
         if(state->next.i)
            state->next.p = getaddress(state->next.i, state);
         else
            state->next.p = 0;
         break;
      case syntax_element_rep:
      case syntax_element_dot_rep:
      case syntax_element_char_rep:
      case syntax_element_short_set_rep:
      case syntax_element_long_set_rep:
         // set the state_id of this repeat:
         static_cast<re_repeat*>(state)->state_id = m_repeater_id++;
         BOOST_FALLTHROUGH;
      case syntax_element_alt:
         std::memset(static_cast<re_alt*>(state)->_map, 0, sizeof(static_cast<re_alt*>(state)->_map));
         static_cast<re_alt*>(state)->can_be_null = 0;
         BOOST_FALLTHROUGH;
      case syntax_element_jump:
         static_cast<re_jump*>(state)->alt.p = getaddress(static_cast<re_jump*>(state)->alt.i, state);
         BOOST_FALLTHROUGH;
      default:
         if(state->next.i)
            state->next.p = getaddress(state->next.i, state);
         else
            state->next.p = 0;
      }
      state = state->next.p;
   }
}

template <class charT, class traits>
void basic_regex_creator<charT, traits>::fixup_recursions(re_syntax_base* state)
{
   re_syntax_base* base = state;
   while(state)
   {
      switch(state->type)
      {
      case syntax_element_assert_backref:
         {
            // just check that the index is valid:
            int idx = static_cast<const re_brace*>(state)->index;
            if(idx < 0)
            {
               idx = -idx-1;
               if(idx >= hash_value_mask)
               {
                  idx = m_pdata->get_id(idx);
                  if(idx <= 0)
                  {
                     // check of sub-expression that doesn't exist:
                     if(0 == this->m_pdata->m_status) // update the error code if not already set
                        this->m_pdata->m_status = boost::regex_constants::error_bad_pattern;
                     //
                     // clear the expression, we should be empty:
                     //
                     this->m_pdata->m_expression = 0;
                     this->m_pdata->m_expression_len = 0;
                     //
                     // and throw if required:
                     //
                     if(0 == (this->flags() & regex_constants::no_except))
                     {
                        std::string message = "Encountered a forward reference to a marked sub-expression that does not exist.";
                        boost::regex_error e(message, boost::regex_constants::error_bad_pattern, 0);
                        e.raise();
                     }
                  }
               }
            }
         }
         break;
      case syntax_element_recurse:
         {
            bool ok = false;
            re_syntax_base* p = base;
            std::ptrdiff_t idx = static_cast<re_jump*>(state)->alt.i;
            if(idx >= hash_value_mask)
            {
               //
               // There may be more than one capture group with this hash, just do what Perl
               // does and recurse to the leftmost:
               //
               idx = m_pdata->get_id(static_cast<int>(idx));
            }
            if(idx < 0)
            {
               ok = false;
            }
            else
            {
               while(p)
               {
                  if((p->type == syntax_element_startmark) && (static_cast<re_brace*>(p)->index == idx))
                  {
                     //
                     // We've found the target of the recursion, set the jump target:
                     //
                     static_cast<re_jump*>(state)->alt.p = p;
                     ok = true;
                     // 
                     // Now scan the target for nested repeats:
                     //
                     p = p->next.p;
                     int next_rep_id = 0;
                     while(p)
                     {
                        switch(p->type)
                        {
                        case syntax_element_rep:
                        case syntax_element_dot_rep:
                        case syntax_element_char_rep:
                        case syntax_element_short_set_rep:
                        case syntax_element_long_set_rep:
                           next_rep_id = static_cast<re_repeat*>(p)->state_id;
                           break;
                        case syntax_element_endmark:
                           if(static_cast<const re_brace*>(p)->index == idx)
                              next_rep_id = -1;
                           break;
                        default:
                           break;
                        }
                        if(next_rep_id)
                           break;
                        p = p->next.p;
                     }
                     if(next_rep_id > 0)
                     {
                        static_cast<re_recurse*>(state)->state_id = next_rep_id - 1;
                     }

                     break;
                  }
                  p = p->next.p;
               }
            }
            if(!ok)
            {
               // recursion to sub-expression that doesn't exist:
               if(0 == this->m_pdata->m_status) // update the error code if not already set
                  this->m_pdata->m_status = boost::regex_constants::error_bad_pattern;
               //
               // clear the expression, we should be empty:
               //
               this->m_pdata->m_expression = 0;
               this->m_pdata->m_expression_len = 0;
               //
               // and throw if required:
               //
               if(0 == (this->flags() & regex_constants::no_except))
               {
                  std::string message = "Encountered a forward reference to a recursive sub-expression that does not exist.";
                  boost::regex_error e(message, boost::regex_constants::error_bad_pattern, 0);
                  e.raise();
               }
            }
         }
         break;
      default:
         break;
      }
      state = state->next.p;
   }
}

template <class charT, class traits>
void basic_regex_creator<charT, traits>::create_startmaps(re_syntax_base* state)
{
   // non-recursive implementation:
   // create the last map in the machine first, so that earlier maps
   // can make use of the result...
   //
   // This was originally a recursive implementation, but that caused stack
   // overflows with complex expressions on small stacks (think COM+).

   // start by saving the case setting:
   bool l_icase = m_icase;
   std::vector<std::pair<bool, re_syntax_base*> > v;

   while(state)
   {
      switch(state->type)
      {
      case syntax_element_toggle_case:
         // we need to track case changes here:
         m_icase = static_cast<re_case*>(state)->icase;
         state = state->next.p;
         continue;
      case syntax_element_alt:
      case syntax_element_rep:
      case syntax_element_dot_rep:
      case syntax_element_char_rep:
      case syntax_element_short_set_rep:
      case syntax_element_long_set_rep:
         // just push the state onto our stack for now:
         v.push_back(std::pair<bool, re_syntax_base*>(m_icase, state));
         state = state->next.p;
         break;
      case syntax_element_backstep:
         // we need to calculate how big the backstep is:
         static_cast<re_brace*>(state)->index
            = this->calculate_backstep(state->next.p);
         if(static_cast<re_brace*>(state)->index < 0)
         {
            // Oops error:
            if(0 == this->m_pdata->m_status) // update the error code if not already set
               this->m_pdata->m_status = boost::regex_constants::error_bad_pattern;
            //
            // clear the expression, we should be empty:
            //
            this->m_pdata->m_expression = 0;
            this->m_pdata->m_expression_len = 0;
            //
            // and throw if required:
            //
            if(0 == (this->flags() & regex_constants::no_except))
            {
               std::string message = "Invalid lookbehind assertion encountered in the regular expression.";
               boost::regex_error e(message, boost::regex_constants::error_bad_pattern, 0);
               e.raise();
            }
         }
         BOOST_FALLTHROUGH;
      default:
         state = state->next.p;
      }
   }

   // now work through our list, building all the maps as we go:
   while(!v.empty())
   {
      // Initialize m_recursion_checks if we need it:
      if(m_has_recursions)
         m_recursion_checks.assign(1 + m_pdata->m_mark_count, 0u);

      const std::pair<bool, re_syntax_base*>& p = v.back();
      m_icase = p.first;
      state = p.second;
      v.pop_back();

      // Build maps:
      m_bad_repeats = 0;
      create_startmap(state->next.p, static_cast<re_alt*>(state)->_map, &static_cast<re_alt*>(state)->can_be_null, mask_take);
      m_bad_repeats = 0;

      if(m_has_recursions)
         m_recursion_checks.assign(1 + m_pdata->m_mark_count, 0u);
      create_startmap(static_cast<re_alt*>(state)->alt.p, static_cast<re_alt*>(state)->_map, &static_cast<re_alt*>(state)->can_be_null, mask_skip);
      // adjust the type of the state to allow for faster matching:
      state->type = this->get_repeat_type(state);
   }
   // restore case sensitivity:
   m_icase = l_icase;
}

template <class charT, class traits>
int basic_regex_creator<charT, traits>::calculate_backstep(re_syntax_base* state)
{
   typedef typename traits::char_class_type m_type;
   int result = 0;
   while(state)
   {
      switch(state->type)
      {
      case syntax_element_startmark:
         if((static_cast<re_brace*>(state)->index == -1)
            || (static_cast<re_brace*>(state)->index == -2))
         {
            state = static_cast<re_jump*>(state->next.p)->alt.p->next.p;
            continue;
         }
         else if(static_cast<re_brace*>(state)->index == -3)
         {
            state = state->next.p->next.p;
            continue;
         }
         break;
      case syntax_element_endmark:
         if((static_cast<re_brace*>(state)->index == -1)
            || (static_cast<re_brace*>(state)->index == -2))
            return result;
         break;
      case syntax_element_literal:
         result += static_cast<re_literal*>(state)->length;
         break;
      case syntax_element_wild:
      case syntax_element_set:
         result += 1;
         break;
      case syntax_element_dot_rep:
      case syntax_element_char_rep:
      case syntax_element_short_set_rep:
      case syntax_element_backref:
      case syntax_element_rep:
      case syntax_element_combining:
      case syntax_element_long_set_rep:
      case syntax_element_backstep:
         {
            re_repeat* rep = static_cast<re_repeat *>(state);
            // adjust the type of the state to allow for faster matching:
            state->type = this->get_repeat_type(state);
            if((state->type == syntax_element_dot_rep) 
               || (state->type == syntax_element_char_rep)
               || (state->type == syntax_element_short_set_rep))
            {
               if(rep->max != rep->min)
                  return -1;
               result += static_cast<int>(rep->min);
               state = rep->alt.p;
               continue;
            }
            else if(state->type == syntax_element_long_set_rep)
            {
               BOOST_REGEX_ASSERT(rep->next.p->type == syntax_element_long_set);
               if(static_cast<re_set_long<m_type>*>(rep->next.p)->singleton == 0)
                  return -1;
               if(rep->max != rep->min)
                  return -1;
               result += static_cast<int>(rep->min);
               state = rep->alt.p;
               continue;
            }
         }
         return -1;
      case syntax_element_long_set:
         if(static_cast<re_set_long<m_type>*>(state)->singleton == 0)
            return -1;
         result += 1;
         break;
      case syntax_element_jump:
         state = static_cast<re_jump*>(state)->alt.p;
         continue;
      case syntax_element_alt:
         {
            int r1 = calculate_backstep(state->next.p);
            int r2 = calculate_backstep(static_cast<re_alt*>(state)->alt.p);
            if((r1 < 0) || (r1 != r2))
               return -1;
            return result + r1;
         }
      default:
         break;
      }
      state = state->next.p;
   }
   return -1;
}

struct recursion_saver
{
   std::vector<unsigned char> saved_state;
   std::vector<unsigned char>* state;
   recursion_saver(std::vector<unsigned char>* p) : saved_state(*p), state(p) {}
   ~recursion_saver()
   {
      state->swap(saved_state);
   }
};

template <class charT, class traits>
void basic_regex_creator<charT, traits>::create_startmap(re_syntax_base* state, unsigned char* l_map, unsigned int* pnull, unsigned char mask)
{
   recursion_saver saved_recursions(&m_recursion_checks);
   int not_last_jump = 1;
   re_syntax_base* recursion_start = 0;
   int recursion_sub = 0;
   re_syntax_base* recursion_restart = 0;

   // track case sensitivity:
   bool l_icase = m_icase;

   while(state)
   {
      switch(state->type)
      {
      case syntax_element_toggle_case:
         l_icase = static_cast<re_case*>(state)->icase;
         state = state->next.p;
         break;
      case syntax_element_literal:
      {
         // don't set anything in *pnull, set each element in l_map
         // that could match the first character in the literal:
         if(l_map)
         {
            l_map[0] |= mask_init;
            charT first_char = *static_cast<charT*>(static_cast<void*>(static_cast<re_literal*>(state) + 1));
            for(unsigned int i = 0; i < (1u << CHAR_BIT); ++i)
            {
               if(m_traits.translate(static_cast<charT>(i), l_icase) == first_char)
                  l_map[i] |= mask;
            }
         }
         return;
      }
      case syntax_element_end_line:
      {
         // next character must be a line separator (if there is one):
         if(l_map)
         {
            l_map[0] |= mask_init;
            l_map[static_cast<unsigned>('\n')] |= mask;
            l_map[static_cast<unsigned>('\r')] |= mask;
            l_map[static_cast<unsigned>('\f')] |= mask;
            l_map[0x85] |= mask;
         }
         // now figure out if we can match a NULL string at this point:
         if(pnull)
            create_startmap(state->next.p, 0, pnull, mask);
         return;
      }
      case syntax_element_recurse:
         {
            BOOST_REGEX_ASSERT(static_cast<const re_jump*>(state)->alt.p->type == syntax_element_startmark);
            recursion_sub = static_cast<re_brace*>(static_cast<const re_jump*>(state)->alt.p)->index;
            if(m_recursion_checks[recursion_sub] & 1u)
            {
               // Infinite recursion!!
               if(0 == this->m_pdata->m_status) // update the error code if not already set
                  this->m_pdata->m_status = boost::regex_constants::error_bad_pattern;
               //
               // clear the expression, we should be empty:
               //
               this->m_pdata->m_expression = 0;
               this->m_pdata->m_expression_len = 0;
               //
               // and throw if required:
               //
               if(0 == (this->flags() & regex_constants::no_except))
               {
                  std::string message = "Encountered an infinite recursion.";
                  boost::regex_error e(message, boost::regex_constants::error_bad_pattern, 0);
                  e.raise();
               }
            }
            else if(recursion_start == 0)
            {
               recursion_start = state;
               recursion_restart = state->next.p;
               state = static_cast<re_jump*>(state)->alt.p;
               m_recursion_checks[recursion_sub] |= 1u;
               break;
            }
            m_recursion_checks[recursion_sub] |= 1u;
            // can't handle nested recursion here...
            BOOST_FALLTHROUGH;
         }
      case syntax_element_backref:
         // can be null, and any character can match:
         if(pnull)
            *pnull |= mask;
         BOOST_FALLTHROUGH;
      case syntax_element_wild:
      {
         // can't be null, any character can match:
         set_all_masks(l_map, mask);
         return;
      }
      case syntax_element_accept:
      case syntax_element_match:
      {
         // must be null, any character can match:
         set_all_masks(l_map, mask);
         if(pnull)
            *pnull |= mask;
         return;
      }
      case syntax_element_word_start:
      {
         // recurse, then AND with all the word characters:
         create_startmap(state->next.p, l_map, pnull, mask);
         if(l_map)
         {
            l_map[0] |= mask_init;
            for(unsigned int i = 0; i < (1u << CHAR_BIT); ++i)
            {
               if(!m_traits.isctype(static_cast<charT>(i), m_word_mask))
                  l_map[i] &= static_cast<unsigned char>(~mask);
            }
         }
         return;
      }
      case syntax_element_word_end:
      {
         // recurse, then AND with all the word characters:
         create_startmap(state->next.p, l_map, pnull, mask);
         if(l_map)
         {
            l_map[0] |= mask_init;
            for(unsigned int i = 0; i < (1u << CHAR_BIT); ++i)
            {
               if(m_traits.isctype(static_cast<charT>(i), m_word_mask))
                  l_map[i] &= static_cast<unsigned char>(~mask);
            }
         }
         return;
      }
      case syntax_element_buffer_end:
      {
         // we *must be null* :
         if(pnull)
            *pnull |= mask;
         return;
      }
      case syntax_element_long_set:
         if(l_map)
         {
            typedef typename traits::char_class_type m_type;
            if(static_cast<re_set_long<m_type>*>(state)->singleton)
            {
               l_map[0] |= mask_init;
               for(unsigned int i = 0; i < (1u << CHAR_BIT); ++i)
               {
                  charT c = static_cast<charT>(i);
                  if(&c != re_is_set_member(&c, &c + 1, static_cast<re_set_long<m_type>*>(state), *m_pdata, l_icase))
                     l_map[i] |= mask;
               }
            }
            else
               set_all_masks(l_map, mask);
         }
         return;
      case syntax_element_set:
         if(l_map)
         {
            l_map[0] |= mask_init;
            for(unsigned int i = 0; i < (1u << CHAR_BIT); ++i)
            {
               if(static_cast<re_set*>(state)->_map[
                  static_cast<unsigned char>(m_traits.translate(static_cast<charT>(i), l_icase))])
                  l_map[i] |= mask;
            }
         }
         return;
      case syntax_element_jump:
         // take the jump:
         state = static_cast<re_alt*>(state)->alt.p;
         not_last_jump = -1;
         break;
      case syntax_element_alt:
      case syntax_element_rep:
      case syntax_element_dot_rep:
      case syntax_element_char_rep:
      case syntax_element_short_set_rep:
      case syntax_element_long_set_rep:
         {
            re_alt* rep = static_cast<re_alt*>(state);
            if(rep->_map[0] & mask_init)
            {
               if(l_map)
               {
                  // copy previous results:
                  l_map[0] |= mask_init;
                  for(unsigned int i = 0; i <= UCHAR_MAX; ++i)
                  {
                     if(rep->_map[i] & mask_any)
                        l_map[i] |= mask;
                  }
               }
               if(pnull)
               {
                  if(rep->can_be_null & mask_any)
                     *pnull |= mask;
               }
            }
            else
            {
               // we haven't created a startmap for this alternative yet
               // so take the union of the two options:
               if(is_bad_repeat(state))
               {
                  set_all_masks(l_map, mask);
                  if(pnull)
                     *pnull |= mask;
                  return;
               }
               set_bad_repeat(state);
               create_startmap(state->next.p, l_map, pnull, mask);
               if((state->type == syntax_element_alt)
                  || (static_cast<re_repeat*>(state)->min == 0)
                  || (not_last_jump == 0))
                  create_startmap(rep->alt.p, l_map, pnull, mask);
            }
         }
         return;
      case syntax_element_soft_buffer_end:
         // match newline or null:
         if(l_map)
         {
            l_map[0] |= mask_init;
            l_map[static_cast<unsigned>('\n')] |= mask;
            l_map[static_cast<unsigned>('\r')] |= mask;
         }
         if(pnull)
            *pnull |= mask;
         return;
      case syntax_element_endmark:
         // need to handle independent subs as a special case:
         if(static_cast<re_brace*>(state)->index < 0)
         {
            // can be null, any character can match:
            set_all_masks(l_map, mask);
            if(pnull)
               *pnull |= mask;
            return;
         }
         else if(recursion_start && (recursion_sub != 0) && (recursion_sub == static_cast<re_brace*>(state)->index))
         {
            // recursion termination:
            recursion_start = 0;
            state = recursion_restart;
            break;
         }

         //
         // Normally we just go to the next state... but if this sub-expression is
         // the target of a recursion, then we might be ending a recursion, in which
         // case we should check whatever follows that recursion, as well as whatever
         // follows this state:
         //
         if(m_pdata->m_has_recursions && static_cast<re_brace*>(state)->index)
         {
            bool ok = false;
            re_syntax_base* p = m_pdata->m_first_state;
            while(p)
            {
               if(p->type == syntax_element_recurse)
               {
                  re_brace* p2 = static_cast<re_brace*>(static_cast<re_jump*>(p)->alt.p);
                  if((p2->type == syntax_element_startmark) && (p2->index == static_cast<re_brace*>(state)->index))
                  {
                     ok = true;
                     break;
                  }
               }
               p = p->next.p;
            }
            if(ok && ((m_recursion_checks[static_cast<re_brace*>(state)->index] & 2u) == 0))
            {
               m_recursion_checks[static_cast<re_brace*>(state)->index] |= 2u;
               create_startmap(p->next.p, l_map, pnull, mask);
            }
         }
         state = state->next.p;
         break;

      case syntax_element_commit:
         set_all_masks(l_map, mask);
         // Continue scanning so we can figure out whether we can be null:
         state = state->next.p;
         break;
      case syntax_element_startmark:
         // need to handle independent subs as a special case:
         if(static_cast<re_brace*>(state)->index == -3)
         {
            state = state->next.p->next.p;
            break;
         }
         BOOST_FALLTHROUGH;
      default:
         state = state->next.p;
      }
      ++not_last_jump;
   }
}

template <class charT, class traits>
unsigned basic_regex_creator<charT, traits>::get_restart_type(re_syntax_base* state)
{
   //
   // find out how the machine starts, so we can optimise the search:
   //
   while(state)
   {
      switch(state->type)
      {
      case syntax_element_startmark:
      case syntax_element_endmark:
         state = state->next.p;
         continue;
      case syntax_element_start_line:
         return regbase::restart_line;
      case syntax_element_word_start:
         return regbase::restart_word;
      case syntax_element_buffer_start:
         return regbase::restart_buf;
      case syntax_element_restart_continue:
         return regbase::restart_continue;
      default:
         state = 0;
         continue;
      }
   }
   return regbase::restart_any;
}

template <class charT, class traits>
void basic_regex_creator<charT, traits>::set_all_masks(unsigned char* bits, unsigned char mask)
{
   //
   // set mask in all of bits elements, 
   // if bits[0] has mask_init not set then we can 
   // optimise this to a call to memset:
   //
   if(bits)
   {
      if(bits[0] == 0)
         (std::memset)(bits, mask, 1u << CHAR_BIT);
      else
      {
         for(unsigned i = 0; i < (1u << CHAR_BIT); ++i)
            bits[i] |= mask;
      }
      bits[0] |= mask_init;
   }
}

template <class charT, class traits>
bool basic_regex_creator<charT, traits>::is_bad_repeat(re_syntax_base* pt)
{
   switch(pt->type)
   {
   case syntax_element_rep:
   case syntax_element_dot_rep:
   case syntax_element_char_rep:
   case syntax_element_short_set_rep:
   case syntax_element_long_set_rep:
      {
         unsigned state_id = static_cast<re_repeat*>(pt)->state_id;
         if(state_id >= sizeof(m_bad_repeats) * CHAR_BIT)
            return true;  // run out of bits, assume we can't traverse this one.
         static const boost::uintmax_t one = 1uL;
         return m_bad_repeats & (one << state_id);
      }
   default:
      return false;
   }
}

template <class charT, class traits>
void basic_regex_creator<charT, traits>::set_bad_repeat(re_syntax_base* pt)
{
   switch(pt->type)
   {
   case syntax_element_rep:
   case syntax_element_dot_rep:
   case syntax_element_char_rep:
   case syntax_element_short_set_rep:
   case syntax_element_long_set_rep:
      {
         unsigned state_id = static_cast<re_repeat*>(pt)->state_id;
         static const boost::uintmax_t one = 1uL;
         if(state_id <= sizeof(m_bad_repeats) * CHAR_BIT)
            m_bad_repeats |= (one << state_id);
      }
      break;
   default:
      break;
   }
}

template <class charT, class traits>
syntax_element_type basic_regex_creator<charT, traits>::get_repeat_type(re_syntax_base* state)
{
   typedef typename traits::char_class_type m_type;
   if(state->type == syntax_element_rep)
   {
      // check to see if we are repeating a single state:
      if(state->next.p->next.p->next.p == static_cast<re_alt*>(state)->alt.p)
      {
         switch(state->next.p->type)
         {
         case BOOST_REGEX_DETAIL_NS::syntax_element_wild:
            return BOOST_REGEX_DETAIL_NS::syntax_element_dot_rep;
         case BOOST_REGEX_DETAIL_NS::syntax_element_literal:
            return BOOST_REGEX_DETAIL_NS::syntax_element_char_rep;
         case BOOST_REGEX_DETAIL_NS::syntax_element_set:
            return BOOST_REGEX_DETAIL_NS::syntax_element_short_set_rep;
         case BOOST_REGEX_DETAIL_NS::syntax_element_long_set:
            if(static_cast<BOOST_REGEX_DETAIL_NS::re_set_long<m_type>*>(state->next.p)->singleton)
               return BOOST_REGEX_DETAIL_NS::syntax_element_long_set_rep;
            break;
         default:
            break;
         }
      }
   }
   return state->type;
}

template <class charT, class traits>
void basic_regex_creator<charT, traits>::probe_leading_repeat(re_syntax_base* state)
{
   // enumerate our states, and see if we have a leading repeat 
   // for which failed search restarts can be optimized;
   do
   {
      switch(state->type)
      {
      case syntax_element_startmark:
         if(static_cast<re_brace*>(state)->index >= 0)
         {
            state = state->next.p;
            continue;
         }
#ifdef BOOST_MSVC
#  pragma warning(push)
#pragma warning(disable:6011)
#endif
         if((static_cast<re_brace*>(state)->index == -1)
            || (static_cast<re_brace*>(state)->index == -2))
         {
            // skip past the zero width assertion:
            state = static_cast<const re_jump*>(state->next.p)->alt.p->next.p;
            continue;
         }
#ifdef BOOST_MSVC
#  pragma warning(pop)
#endif
         if(static_cast<re_brace*>(state)->index == -3)
         {
            // Have to skip the leading jump state:
            state = state->next.p->next.p;
            continue;
         }
         return;
      case syntax_element_endmark:
      case syntax_element_start_line:
      case syntax_element_end_line:
      case syntax_element_word_boundary:
      case syntax_element_within_word:
      case syntax_element_word_start:
      case syntax_element_word_end:
      case syntax_element_buffer_start:
      case syntax_element_buffer_end:
      case syntax_element_restart_continue:
         state = state->next.p;
         break;
      case syntax_element_dot_rep:
      case syntax_element_char_rep:
      case syntax_element_short_set_rep:
      case syntax_element_long_set_rep:
         if(this->m_has_backrefs == 0)
            static_cast<re_repeat*>(state)->leading = true;
         BOOST_FALLTHROUGH;
      default:
         return;
      }
   }while(state);
}

} // namespace BOOST_REGEX_DETAIL_NS

} // namespace boost

#ifdef BOOST_MSVC
#  pragma warning(pop)
#endif

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4103)
#endif
#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif

/* basic_regex_creator.hpp
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
*/