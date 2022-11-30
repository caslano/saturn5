/*
 *
 * Copyright (c) 1998-2009 John Maddock
 * Copyright 2008 Eric Niebler. 
 *
 * Use, modification and distribution are subject to the 
 * Boost Software License, Version 1.0. (See accompanying file 
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */

 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE         regex_format.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Provides formatting output routines for search and replace
  *                operations.  Note this is an internal header file included
  *                by regex.hpp, do not include on its own.
  */

#ifndef BOOST_REGEX_FORMAT_HPP
#define BOOST_REGEX_FORMAT_HPP

#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/type_traits/is_class.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#ifndef BOOST_NO_SFINAE
#include <boost/mpl/has_xxx.hpp>
#endif
#include <boost/ref.hpp>

namespace boost{

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

//
// Forward declaration:
//
   template <class BidiIterator, class Allocator = BOOST_DEDUCED_TYPENAME std::vector<sub_match<BidiIterator> >::allocator_type >
class match_results;

namespace BOOST_REGEX_DETAIL_NS{

//
// struct trivial_format_traits:
// defines minimum localisation support for formatting
// in the case that the actual regex traits is unavailable.
//
template <class charT>
struct trivial_format_traits
{
   typedef charT char_type;

   static std::ptrdiff_t length(const charT* p)
   {
      return global_length(p);
   }
   static charT tolower(charT c)
   {
      return ::boost::BOOST_REGEX_DETAIL_NS::global_lower(c);
   }
   static charT toupper(charT c)
   {
      return ::boost::BOOST_REGEX_DETAIL_NS::global_upper(c);
   }
   static int value(const charT c, int radix)
   {
      int result = global_value(c);
      return result >= radix ? -1 : result;
   }
   int toi(const charT*& p1, const charT* p2, int radix)const
   {
      return (int)global_toi(p1, p2, radix, *this);
   }
};

#ifdef BOOST_MSVC
#  pragma warning(push)
#pragma warning(disable:26812)
#endif
template <class OutputIterator, class Results, class traits, class ForwardIter>
class basic_regex_formatter
{
public:
   typedef typename traits::char_type char_type;
   basic_regex_formatter(OutputIterator o, const Results& r, const traits& t)
      : m_traits(t), m_results(r), m_out(o), m_position(), m_end(), m_flags(), m_state(output_copy), m_restore_state(output_copy), m_have_conditional(false) {}
   OutputIterator format(ForwardIter p1, ForwardIter p2, match_flag_type f);
   OutputIterator format(ForwardIter p1, match_flag_type f)
   {
      return format(p1, p1 + m_traits.length(p1), f);
   }
private:
   typedef typename Results::value_type sub_match_type;
   enum output_state
   {
      output_copy,
      output_next_lower,
      output_next_upper,
      output_lower,
      output_upper,
      output_none
   };

   void put(char_type c);
   void put(const sub_match_type& sub);
   void format_all();
   void format_perl();
   void format_escape();
   void format_conditional();
   void format_until_scope_end();
   bool handle_perl_verb(bool have_brace);

   inline typename Results::value_type const& get_named_sub(ForwardIter i, ForwardIter j, const mpl::false_&)
   {
      std::vector<char_type> v(i, j);
      return (i != j) ? this->m_results.named_subexpression(&v[0], &v[0] + v.size())
         : this->m_results.named_subexpression(static_cast<const char_type*>(0), static_cast<const char_type*>(0));
   }
   inline typename Results::value_type const& get_named_sub(ForwardIter i, ForwardIter j, const mpl::true_&)
   {
      return this->m_results.named_subexpression(i, j);
   }
   inline typename Results::value_type const& get_named_sub(ForwardIter i, ForwardIter j)
   {
      typedef typename boost::is_convertible<ForwardIter, const char_type*>::type tag_type;
      return get_named_sub(i, j, tag_type());
   }
   inline int get_named_sub_index(ForwardIter i, ForwardIter j, const mpl::false_&)
   {
      std::vector<char_type> v(i, j);
      return (i != j) ? this->m_results.named_subexpression_index(&v[0], &v[0] + v.size())
         : this->m_results.named_subexpression_index(static_cast<const char_type*>(0), static_cast<const char_type*>(0));
   }
   inline int get_named_sub_index(ForwardIter i, ForwardIter j, const mpl::true_&)
   {
      return this->m_results.named_subexpression_index(i, j);
   }
   inline int get_named_sub_index(ForwardIter i, ForwardIter j)
   {
      typedef typename boost::is_convertible<ForwardIter, const char_type*>::type tag_type;
      return get_named_sub_index(i, j, tag_type());
   }
#ifdef BOOST_MSVC
   // msvc-8.0 issues a spurious warning on the call to std::advance here:
#pragma warning(push)
#pragma warning(disable:4244)
#endif
   inline int toi(ForwardIter& i, ForwardIter j, int base, const boost::mpl::false_&)
   {
      if(i != j)
      {
         std::vector<char_type> v(i, j);
         const char_type* start = &v[0];
         const char_type* pos = start;
         int r = (int)m_traits.toi(pos, &v[0] + v.size(), base);
         std::advance(i, pos - start);
         return r;
      }
      return -1;
   }
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif
   inline int toi(ForwardIter& i, ForwardIter j, int base, const boost::mpl::true_&)
   {
      return m_traits.toi(i, j, base);
   }
   inline int toi(ForwardIter& i, ForwardIter j, int base)
   {
#if defined(_MSC_VER) && defined(__INTEL_COMPILER) && ((__INTEL_COMPILER == 9999) || (__INTEL_COMPILER == 1210))
      // Workaround for Intel support issue #656654.
      // See also https://svn.boost.org/trac/boost/ticket/6359
      return toi(i, j, base, mpl::false_());
#else
      typedef typename boost::is_convertible<ForwardIter, const char_type*&>::type tag_type;
      return toi(i, j, base, tag_type());
#endif
   }

   const traits&    m_traits;       // the traits class for localised formatting operations
   const Results&   m_results;     // the match_results being used.
   OutputIterator   m_out;         // where to send output.
   ForwardIter      m_position;  // format string, current position
   ForwardIter      m_end;       // format string end
   match_flag_type  m_flags;      // format flags to use
   output_state     m_state;      // what to do with the next character
   output_state     m_restore_state;  // what state to restore to.
   bool             m_have_conditional; // we are parsing a conditional
private:
   basic_regex_formatter(const basic_regex_formatter&);
   basic_regex_formatter& operator=(const basic_regex_formatter&);
};
#ifdef BOOST_MSVC
#  pragma warning(pop)
#endif

template <class OutputIterator, class Results, class traits, class ForwardIter>
OutputIterator basic_regex_formatter<OutputIterator, Results, traits, ForwardIter>::format(ForwardIter p1, ForwardIter p2, match_flag_type f)
{
   m_position = p1;
   m_end = p2;
   m_flags = f;
   format_all();
   return m_out;
}

template <class OutputIterator, class Results, class traits, class ForwardIter>
void basic_regex_formatter<OutputIterator, Results, traits, ForwardIter>::format_all()
{
   // over and over:
   while(m_position != m_end)
   {
      switch(*m_position)
      {
      case '&':
         if(m_flags & ::boost::regex_constants::format_sed)
         {
            ++m_position;
            put(m_results[0]);
            break;
         }
         put(*m_position++);
         break;
      case '\\':
         format_escape();
         break;
      case '(':
         if(m_flags & boost::regex_constants::format_all)
         {
            ++m_position;
            bool have_conditional = m_have_conditional;
            m_have_conditional = false;
            format_until_scope_end();
            m_have_conditional = have_conditional;
            if(m_position == m_end)
               return;
            BOOST_REGEX_ASSERT(*m_position == static_cast<char_type>(')'));
            ++m_position;  // skip the closing ')'
            break;
         }
         put(*m_position);
         ++m_position;
         break;
      case ')':
         if(m_flags & boost::regex_constants::format_all)
         {
            return;
         }
         put(*m_position);
         ++m_position;
         break;
      case ':':
         if((m_flags & boost::regex_constants::format_all) && m_have_conditional)
         {
            return;
         }
         put(*m_position);
         ++m_position;
         break;
      case '?':
         if(m_flags & boost::regex_constants::format_all)
         {
            ++m_position;
            format_conditional();
            break;
         }
         put(*m_position);
         ++m_position;
         break;
      case '$':
         if((m_flags & format_sed) == 0)
         {
            format_perl();
            break;
         }
         // not a special character:
         BOOST_FALLTHROUGH;
      default:
         put(*m_position);
         ++m_position;
         break;
      }
   }
}

template <class OutputIterator, class Results, class traits, class ForwardIter>
void basic_regex_formatter<OutputIterator, Results, traits, ForwardIter>::format_perl()
{
   //
   // On entry *m_position points to a '$' character
   // output the information that goes with it:
   //
   BOOST_REGEX_ASSERT(*m_position == '$');
   //
   // see if this is a trailing '$':
   //
   if(++m_position == m_end)
   {
      --m_position;
      put(*m_position);
      ++m_position;
      return;
   }
   //
   // OK find out what kind it is:
   //
   bool have_brace = false;
   ForwardIter save_position = m_position;
   switch(*m_position)
   {
   case '&':
      ++m_position;
      put(this->m_results[0]);
      break;
   case '`':
      ++m_position;
      put(this->m_results.prefix());
      break;
   case '\'':
      ++m_position;
      put(this->m_results.suffix());
      break;
   case '$':
      put(*m_position++);
      break;
   case '+':
      if((++m_position != m_end) && (*m_position == '{'))
      {
         ForwardIter base = ++m_position;
         while((m_position != m_end) && (*m_position != '}')) ++m_position;
         if(m_position != m_end)
         {
            // Named sub-expression:
            put(get_named_sub(base, m_position));
            ++m_position;
            break;
         }
         else
         {
            m_position = --base;
         }
      }
      put((this->m_results)[this->m_results.size() > 1 ? static_cast<int>(this->m_results.size() - 1) : 1]);
      break;
   case '{':
      have_brace = true;
      ++m_position;
      BOOST_FALLTHROUGH;
   default:
      // see if we have a number:
      {
         std::ptrdiff_t len = ::boost::BOOST_REGEX_DETAIL_NS::distance(m_position, m_end);
         //len = (std::min)(static_cast<std::ptrdiff_t>(2), len);
         int v = this->toi(m_position, m_position + len, 10);
         if((v < 0) || (have_brace && ((m_position == m_end) || (*m_position != '}'))))
         {
            // Look for a Perl-5.10 verb:
            if(!handle_perl_verb(have_brace))
            {
               // leave the $ as is, and carry on:
               m_position = --save_position;
               put(*m_position);
               ++m_position;
            }
            break;
         }
         // otherwise output sub v:
         put(this->m_results[v]);
         if(have_brace)
            ++m_position;
      }
   }
}

template <class OutputIterator, class Results, class traits, class ForwardIter>
bool basic_regex_formatter<OutputIterator, Results, traits, ForwardIter>::handle_perl_verb(bool have_brace)
{
   // 
   // We may have a capitalised string containing a Perl action:
   //
   static const char_type MATCH[] = { 'M', 'A', 'T', 'C', 'H' };
   static const char_type PREMATCH[] = { 'P', 'R', 'E', 'M', 'A', 'T', 'C', 'H' };
   static const char_type POSTMATCH[] = { 'P', 'O', 'S', 'T', 'M', 'A', 'T', 'C', 'H' };
   static const char_type LAST_PAREN_MATCH[] = { 'L', 'A', 'S', 'T', '_', 'P', 'A', 'R', 'E', 'N', '_', 'M', 'A', 'T', 'C', 'H' };
   static const char_type LAST_SUBMATCH_RESULT[] = { 'L', 'A', 'S', 'T', '_', 'S', 'U', 'B', 'M', 'A', 'T', 'C', 'H', '_', 'R', 'E', 'S', 'U', 'L', 'T' };
   static const char_type LAST_SUBMATCH_RESULT_ALT[] = { '^', 'N' };

   if(m_position == m_end)
      return false;
   if(have_brace && (*m_position == '^'))
      ++m_position;

   std::ptrdiff_t max_len = m_end - m_position;

   if((max_len >= 5) && std::equal(m_position, m_position + 5, MATCH))
   {
      m_position += 5;
      if(have_brace)
      {
         if((m_position != m_end) && (*m_position == '}'))
            ++m_position;
         else
         {
            m_position -= 5;
            return false;
         }
      }
      put(this->m_results[0]);
      return true;
   }
   if((max_len >= 8) && std::equal(m_position, m_position + 8, PREMATCH))
   {
      m_position += 8;
      if(have_brace)
      {
         if((m_position != m_end) && (*m_position == '}'))
            ++m_position;
         else
         {
            m_position -= 8;
            return false;
         }
      }
      put(this->m_results.prefix());
      return true;
   }
   if((max_len >= 9) && std::equal(m_position, m_position + 9, POSTMATCH))
   {
      m_position += 9;
      if(have_brace)
      {
         if((m_position != m_end) && (*m_position == '}'))
            ++m_position;
         else
         {
            m_position -= 9;
            return false;
         }
      }
      put(this->m_results.suffix());
      return true;
   }
   if((max_len >= 16) && std::equal(m_position, m_position + 16, LAST_PAREN_MATCH))
   {
      m_position += 16;
      if(have_brace)
      {
         if((m_position != m_end) && (*m_position == '}'))
            ++m_position;
         else
         {
            m_position -= 16;
            return false;
         }
      }
      put((this->m_results)[this->m_results.size() > 1 ? static_cast<int>(this->m_results.size() - 1) : 1]);
      return true;
   }
   if((max_len >= 20) && std::equal(m_position, m_position + 20, LAST_SUBMATCH_RESULT))
   {
      m_position += 20;
      if(have_brace)
      {
         if((m_position != m_end) && (*m_position == '}'))
            ++m_position;
         else
         {
            m_position -= 20;
            return false;
         }
      }
      put(this->m_results.get_last_closed_paren());
      return true;
   }
   if((max_len >= 2) && std::equal(m_position, m_position + 2, LAST_SUBMATCH_RESULT_ALT))
   {
      m_position += 2;
      if(have_brace)
      {
         if((m_position != m_end) && (*m_position == '}'))
            ++m_position;
         else
         {
            m_position -= 2;
            return false;
         }
      }
      put(this->m_results.get_last_closed_paren());
      return true;
   }
   return false;
}

template <class OutputIterator, class Results, class traits, class ForwardIter>
void basic_regex_formatter<OutputIterator, Results, traits, ForwardIter>::format_escape()
{
   // skip the escape and check for trailing escape:
   if(++m_position == m_end)
   {
      put(static_cast<char_type>('\\'));
      return;
   }
   // now switch on the escape type:
   switch(*m_position)
   {
   case 'a':
      put(static_cast<char_type>('\a'));
      ++m_position;
      break;
   case 'f':
      put(static_cast<char_type>('\f'));
      ++m_position;
      break;
   case 'n':
      put(static_cast<char_type>('\n'));
      ++m_position;
      break;
   case 'r':
      put(static_cast<char_type>('\r'));
      ++m_position;
      break;
   case 't':
      put(static_cast<char_type>('\t'));
      ++m_position;
      break;
   case 'v':
      put(static_cast<char_type>('\v'));
      ++m_position;
      break;
   case 'x':
      if(++m_position == m_end)
      {
         put(static_cast<char_type>('x'));
         return;
      }
      // maybe have \x{ddd}
      if(*m_position == static_cast<char_type>('{'))
      {
         ++m_position;
         int val = this->toi(m_position, m_end, 16);
         if(val < 0)
         {
            // invalid value treat everything as literals:
            put(static_cast<char_type>('x'));
            put(static_cast<char_type>('{'));
            return;
         }
         if((m_position == m_end) || (*m_position != static_cast<char_type>('}')))
         {
            --m_position;
            while(*m_position != static_cast<char_type>('\\'))
               --m_position;
            ++m_position;
            put(*m_position++);
            return;
         }
         ++m_position;
         put(static_cast<char_type>(val));
         return;
      }
      else
      {
         std::ptrdiff_t len = ::boost::BOOST_REGEX_DETAIL_NS::distance(m_position, m_end);
         len = (std::min)(static_cast<std::ptrdiff_t>(2), len);
         int val = this->toi(m_position, m_position + len, 16);
         if(val < 0)
         {
            --m_position;
            put(*m_position++);
            return;
         }
         put(static_cast<char_type>(val));
      }
      break;
   case 'c':
      if(++m_position == m_end)
      {
         --m_position;
         put(*m_position++);
         return;
      }
      put(static_cast<char_type>(*m_position++ % 32));
      break;
   case 'e':
      put(static_cast<char_type>(27));
      ++m_position;
      break;
   default:
      // see if we have a perl specific escape:
      if((m_flags & boost::regex_constants::format_sed) == 0)
      {
         bool breakout = false;
         switch(*m_position)
         {
         case 'l':
            ++m_position;
            m_restore_state = m_state;
            m_state = output_next_lower;
            breakout = true;
            break;
         case 'L':
            ++m_position;
            m_state = output_lower;
            breakout = true;
            break;
         case 'u':
            ++m_position;
            m_restore_state = m_state;
            m_state = output_next_upper;
            breakout = true;
            break;
         case 'U':
            ++m_position;
            m_state = output_upper;
            breakout = true;
            break;
         case 'E':
            ++m_position;
            m_state = output_copy;
            breakout = true;
            break;
         }
         if(breakout)
            break;
      }
      // see if we have a \n sed style backreference:
      std::ptrdiff_t len = ::boost::BOOST_REGEX_DETAIL_NS::distance(m_position, m_end);
      len = (std::min)(static_cast<std::ptrdiff_t>(1), len);
      int v = this->toi(m_position, m_position+len, 10);
      if((v > 0) || ((v == 0) && (m_flags & ::boost::regex_constants::format_sed)))
      {
         put(m_results[v]);
         break;
      }
      else if(v == 0)
      {
         // octal ecape sequence:
         --m_position;
         len = ::boost::BOOST_REGEX_DETAIL_NS::distance(m_position, m_end);
         len = (std::min)(static_cast<std::ptrdiff_t>(4), len);
         v = this->toi(m_position, m_position + len, 8);
         BOOST_REGEX_ASSERT(v >= 0);
         put(static_cast<char_type>(v));
         break;
      }
      // Otherwise output the character "as is":
      put(*m_position++);
      break;
   }
}

template <class OutputIterator, class Results, class traits, class ForwardIter>
void basic_regex_formatter<OutputIterator, Results, traits, ForwardIter>::format_conditional()
{
   if(m_position == m_end)
   {
      // oops trailing '?':
      put(static_cast<char_type>('?'));
      return;
   }
   int v;
   if(*m_position == '{')
   {
      ForwardIter base = m_position;
      ++m_position;
      v = this->toi(m_position, m_end, 10);
      if(v < 0)
      {
         // Try a named subexpression:
         while((m_position != m_end) && (*m_position != '}'))
            ++m_position;
         v = this->get_named_sub_index(base + 1, m_position);
      }
      if((v < 0) || (*m_position != '}'))
      {
         m_position = base;
         // oops trailing '?':
         put(static_cast<char_type>('?'));
         return;
      }
      // Skip trailing '}':
      ++m_position;
   }
   else
   {
      std::ptrdiff_t len = ::boost::BOOST_REGEX_DETAIL_NS::distance(m_position, m_end);
      len = (std::min)(static_cast<std::ptrdiff_t>(2), len);
      v = this->toi(m_position, m_position + len, 10);
   }
   if(v < 0)
   {
      // oops not a number:
      put(static_cast<char_type>('?'));
      return;
   }

   // output varies depending upon whether sub-expression v matched or not:
   if(m_results[v].matched)
   {
      m_have_conditional = true;
      format_all();
      m_have_conditional = false;
      if((m_position != m_end) && (*m_position == static_cast<char_type>(':')))
      {
         // skip the ':':
         ++m_position;
         // save output state, then turn it off:
         output_state saved_state = m_state;
         m_state = output_none;
         // format the rest of this scope:
         format_until_scope_end();
         // restore output state:
         m_state = saved_state;
      }
   }
   else
   {
      // save output state, then turn it off:
      output_state saved_state = m_state;
      m_state = output_none;
      // format until ':' or ')':
      m_have_conditional = true;
      format_all();
      m_have_conditional = false;
      // restore state:
      m_state = saved_state;
      if((m_position != m_end) && (*m_position == static_cast<char_type>(':')))
      {
         // skip the ':':
         ++m_position;
         // format the rest of this scope:
         format_until_scope_end();
      }
   }
}

template <class OutputIterator, class Results, class traits, class ForwardIter>
void basic_regex_formatter<OutputIterator, Results, traits, ForwardIter>::format_until_scope_end()
{
   do
   {
      format_all();
      if((m_position == m_end) || (*m_position == static_cast<char_type>(')')))
         return;
      put(*m_position++);
   }while(m_position != m_end);
}

template <class OutputIterator, class Results, class traits, class ForwardIter>
void basic_regex_formatter<OutputIterator, Results, traits, ForwardIter>::put(char_type c)
{
   // write a single character to output
   // according to which case translation mode we are in:
   switch(this->m_state)
   {
   case output_none:
      return;
   case output_next_lower:
      c = m_traits.tolower(c);
      this->m_state = m_restore_state;
      break;
   case output_next_upper:
      c = m_traits.toupper(c);
      this->m_state = m_restore_state;
      break;
   case output_lower:
      c = m_traits.tolower(c);
      break;
   case output_upper:
      c = m_traits.toupper(c);
      break;
   default:
      break;
   }
   *m_out = c;
   ++m_out;
}

template <class OutputIterator, class Results, class traits, class ForwardIter>
void basic_regex_formatter<OutputIterator, Results, traits, ForwardIter>::put(const sub_match_type& sub)
{
   typedef typename sub_match_type::iterator iterator_type;
   iterator_type i = sub.first;
   while(i != sub.second)
   {
      put(*i);
      ++i;
   }
}

template <class S>
class string_out_iterator
{
   S* out;
public:
   string_out_iterator(S& s) : out(&s) {}
   string_out_iterator& operator++() { return *this; }
   string_out_iterator& operator++(int) { return *this; }
   string_out_iterator& operator*() { return *this; }
   string_out_iterator& operator=(typename S::value_type v) 
   { 
      out->append(1, v); 
      return *this; 
   }

   typedef std::ptrdiff_t difference_type;
   typedef typename S::value_type value_type;
   typedef value_type* pointer;
   typedef value_type& reference;
   typedef std::output_iterator_tag iterator_category;
};

template <class OutputIterator, class Iterator, class Alloc, class ForwardIter, class traits>
OutputIterator regex_format_imp(OutputIterator out,
                          const match_results<Iterator, Alloc>& m,
                          ForwardIter p1, ForwardIter p2,
                          match_flag_type flags,
                          const traits& t
                         )
{
   if(flags & regex_constants::format_literal)
   {
      return BOOST_REGEX_DETAIL_NS::copy(p1, p2, out);
   }

   BOOST_REGEX_DETAIL_NS::basic_regex_formatter<
      OutputIterator, 
      match_results<Iterator, Alloc>, 
      traits, ForwardIter> f(out, m, t);
   return f.format(p1, p2, flags);
}

#ifndef BOOST_NO_SFINAE

BOOST_MPL_HAS_XXX_TRAIT_DEF(const_iterator)

struct any_type 
{
   template <class T>
   any_type(const T&); 
   template <class T, class U>
   any_type(const T&, const U&); 
   template <class T, class U, class V>
   any_type(const T&, const U&, const V&); 
};
typedef char no_type;
typedef char (&unary_type)[2];
typedef char (&binary_type)[3];
typedef char (&ternary_type)[4];

no_type check_is_formatter(unary_type, binary_type, ternary_type);
template<typename T>
unary_type check_is_formatter(T const &, binary_type, ternary_type);
template<typename T>
binary_type check_is_formatter(unary_type, T const &, ternary_type);
template<typename T, typename U>
binary_type check_is_formatter(T const &, U const &, ternary_type);
template<typename T>
ternary_type check_is_formatter(unary_type, binary_type, T const &);
template<typename T, typename U>
ternary_type check_is_formatter(T const &, binary_type, U const &);
template<typename T, typename U>
ternary_type check_is_formatter(unary_type, T const &, U const &);
template<typename T, typename U, typename V>
ternary_type check_is_formatter(T const &, U const &, V const &);

struct unary_binary_ternary
{
    typedef unary_type (*unary_fun)(any_type);
    typedef binary_type (*binary_fun)(any_type, any_type);
    typedef ternary_type (*ternary_fun)(any_type, any_type, any_type);
    operator unary_fun();
    operator binary_fun();
    operator ternary_fun();
};

template<typename Formatter, bool IsFunction = boost::is_function<Formatter>::value>
struct formatter_wrapper
  : Formatter
  , unary_binary_ternary
{
   formatter_wrapper(){}
};

template<typename Formatter>
struct formatter_wrapper<Formatter, true>
  : unary_binary_ternary
{
    operator Formatter *();
};

template<typename Formatter>
struct formatter_wrapper<Formatter *, false>
  : unary_binary_ternary
{
    operator Formatter *();
};

template <class F, class M, class O>
struct format_traits_imp
{
private:
   //
   // F must be a pointer, a function, or a class with a function call operator:
   //
   BOOST_STATIC_ASSERT((::boost::is_pointer<F>::value || ::boost::is_function<F>::value || ::boost::is_class<F>::value));
   static formatter_wrapper<typename unwrap_reference<F>::type> f;
   static M m;
   static O out;
   static boost::regex_constants::match_flag_type flags;
public:
   BOOST_STATIC_CONSTANT(int, value = sizeof(check_is_formatter(f(m), f(m, out), f(m, out, flags))));
};

template <class F, class M, class O>
struct format_traits
{
public:
   // 
   // Type is mpl::int_<N> where N is one of:
   //
   // 0 : F is a pointer to a presumably null-terminated string.
   // 1 : F is a character-container such as a std::string.
   // 2 : F is a Unary Functor.
   // 3 : F is a Binary Functor.
   // 4 : F is a Ternary Functor.
   //
   typedef typename boost::mpl::if_<
      boost::mpl::and_<boost::is_pointer<F>, boost::mpl::not_<boost::is_function<typename boost::remove_pointer<F>::type> > >,
      boost::mpl::int_<0>,
      typename boost::mpl::if_<
         has_const_iterator<F>,
         boost::mpl::int_<1>,
         boost::mpl::int_<format_traits_imp<F, M, O>::value>
      >::type
   >::type type;
   //
   // This static assertion will fail if the functor passed does not accept
   // the same type of arguments passed.
   //
   BOOST_STATIC_ASSERT( boost::is_class<F>::value && !has_const_iterator<F>::value ? (type::value > 1) : true);
};

#else // BOOST_NO_SFINAE

template <class F, class M, class O>
struct format_traits
{
public:
   // 
   // Type is mpl::int_<N> where N is one of:
   //
   // 0 : F is a pointer to a presumably null-terminated string.
   // 1 : F is a character-container such as a std::string.
   //
   // Other options such as F being a Functor are not supported without
   // SFINAE support.
   //
   typedef typename boost::mpl::if_<
      boost::is_pointer<F>,
      boost::mpl::int_<0>,
      boost::mpl::int_<1>
   >::type type;
};

#endif // BOOST_NO_SFINAE

template <class Base, class Match>
struct format_functor3
{
   format_functor3(Base b) : func(b) {}
   template <class OutputIter>
   OutputIter operator()(const Match& m, OutputIter i, boost::regex_constants::match_flag_type f)
   {
      return boost::unwrap_ref(func)(m, i, f);
   }
   template <class OutputIter, class Traits>
   OutputIter operator()(const Match& m, OutputIter i, boost::regex_constants::match_flag_type f, const Traits&)
   {
      return (*this)(m, i, f);
   }
private:
   Base func;
   format_functor3(const format_functor3&);
   format_functor3& operator=(const format_functor3&);
};

template <class Base, class Match>
struct format_functor2
{
   format_functor2(Base b) : func(b) {}
   template <class OutputIter>
   OutputIter operator()(const Match& m, OutputIter i, boost::regex_constants::match_flag_type /*f*/)
   {
      return boost::unwrap_ref(func)(m, i);
   }
   template <class OutputIter, class Traits>
   OutputIter operator()(const Match& m, OutputIter i, boost::regex_constants::match_flag_type f, const Traits&)
   {
      return (*this)(m, i, f);
   }
private:
   Base func;
   format_functor2(const format_functor2&);
   format_functor2& operator=(const format_functor2&);
};

template <class Base, class Match>
struct format_functor1
{
   format_functor1(Base b) : func(b) {}

   template <class S, class OutputIter>
   OutputIter do_format_string(const S& s, OutputIter i)
   {
      return BOOST_REGEX_DETAIL_NS::copy(s.begin(), s.end(), i);
   }
   template <class S, class OutputIter>
   inline OutputIter do_format_string(const S* s, OutputIter i)
   {
      while(s && *s)
      {
         *i = *s;
         ++i;
         ++s;
      }
      return i;
   }
   template <class OutputIter>
   OutputIter operator()(const Match& m, OutputIter i, boost::regex_constants::match_flag_type /*f*/)
   {
      return do_format_string(boost::unwrap_ref(func)(m), i);
   }
   template <class OutputIter, class Traits>
   OutputIter operator()(const Match& m, OutputIter i, boost::regex_constants::match_flag_type f, const Traits&)
   {
      return (*this)(m, i, f);
   }
private:
   Base func;
   format_functor1(const format_functor1&);
   format_functor1& operator=(const format_functor1&);
};

template <class charT, class Match, class Traits>
struct format_functor_c_string
{
   format_functor_c_string(const charT* ps) : func(ps) {}

   template <class OutputIter>
   OutputIter operator()(const Match& m, OutputIter i, boost::regex_constants::match_flag_type f, const Traits& t = Traits())
   {
      //typedef typename Match::char_type char_type;
      const charT* end = func;
      while(*end) ++end;
      return regex_format_imp(i, m, func, end, f, t);
   }
private:
   const charT* func;
   format_functor_c_string(const format_functor_c_string&);
   format_functor_c_string& operator=(const format_functor_c_string&);
};

template <class Container, class Match, class Traits>
struct format_functor_container
{
   format_functor_container(const Container& c) : func(c) {}

   template <class OutputIter>
   OutputIter operator()(const Match& m, OutputIter i, boost::regex_constants::match_flag_type f, const Traits& t = Traits())
   {
      //typedef typename Match::char_type char_type;
      return BOOST_REGEX_DETAIL_NS::regex_format_imp(i, m, func.begin(), func.end(), f, t);
   }
private:
   const Container& func;
   format_functor_container(const format_functor_container&);
   format_functor_container& operator=(const format_functor_container&);
};

template <class Func, class Match, class OutputIterator, class Traits = BOOST_REGEX_DETAIL_NS::trivial_format_traits<typename Match::char_type> >
struct compute_functor_type
{
   typedef typename format_traits<Func, Match, OutputIterator>::type tag;
   typedef typename boost::remove_cv< typename boost::remove_pointer<Func>::type>::type maybe_char_type;

   typedef typename mpl::if_<
      ::boost::is_same<tag, mpl::int_<0> >, format_functor_c_string<maybe_char_type, Match, Traits>,
      typename mpl::if_<
         ::boost::is_same<tag, mpl::int_<1> >, format_functor_container<Func, Match, Traits>,
         typename mpl::if_<
            ::boost::is_same<tag, mpl::int_<2> >, format_functor1<Func, Match>,
            typename mpl::if_<
               ::boost::is_same<tag, mpl::int_<3> >, format_functor2<Func, Match>, 
               format_functor3<Func, Match>
            >::type
         >::type
      >::type
   >::type type;
};

} // namespace BOOST_REGEX_DETAIL_NS

template <class OutputIterator, class Iterator, class Allocator, class Functor>
inline OutputIterator regex_format(OutputIterator out,
                          const match_results<Iterator, Allocator>& m,
                          Functor fmt,
                          match_flag_type flags = format_all
                         )
{
   return m.format(out, fmt, flags);
}

template <class Iterator, class Allocator, class Functor>
inline std::basic_string<typename match_results<Iterator, Allocator>::char_type> regex_format(const match_results<Iterator, Allocator>& m, 
                                      Functor fmt, 
                                      match_flag_type flags = format_all)
{
   return m.format(fmt, flags);
}

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

} // namespace boost

#endif  // BOOST_REGEX_FORMAT_HPP







/* regex_format.hpp
+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
*/