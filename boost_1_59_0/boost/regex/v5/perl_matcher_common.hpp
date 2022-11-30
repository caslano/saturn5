/*
 *
 * Copyright (c) 2002
 * John Maddock
 *
 * Use, modification and distribution are subject to the 
 * Boost Software License, Version 1.0. (See accompanying file 
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */

 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE         perl_matcher_common.cpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Definitions of perl_matcher member functions that are 
  *                common to both the recursive and non-recursive versions.
  */

#ifndef BOOST_REGEX_V5_PERL_MATCHER_COMMON_HPP
#define BOOST_REGEX_V5_PERL_MATCHER_COMMON_HPP

#ifdef BOOST_REGEX_MSVC
#  pragma warning(push)
#pragma warning(disable:4459)
#if BOOST_REGEX_MSVC < 1910
#pragma warning(disable:4800)
#endif
#endif

namespace boost{
namespace BOOST_REGEX_DETAIL_NS{

#ifdef BOOST_REGEX_MSVC
#  pragma warning(push)
#pragma warning(disable:26812)
#endif
   template <class BidiIterator, class Allocator, class traits>
void perl_matcher<BidiIterator, Allocator, traits>::construct_init(const basic_regex<char_type, traits>& e, match_flag_type f)
{ 
   typedef typename std::iterator_traits<BidiIterator>::iterator_category category;
   typedef typename basic_regex<char_type, traits>::flag_type expression_flag_type;
   
   if(e.empty())
   {
      // precondition failure: e is not a valid regex.
      std::invalid_argument ex("Invalid regular expression object");
#ifndef BOOST_REGEX_STANDALONE
      boost::throw_exception(ex);
#else
      throw e;
#endif
   }
   pstate = 0;
   m_match_flags = f;
   estimate_max_state_count(static_cast<category*>(0));
   expression_flag_type re_f = re.flags();
   icase = re_f & regex_constants::icase;
   if(!(m_match_flags & (match_perl|match_posix)))
   {
      if((re_f & (regbase::main_option_type|regbase::no_perl_ex)) == 0)
         m_match_flags |= match_perl;
      else if((re_f & (regbase::main_option_type|regbase::emacs_ex)) == (regbase::basic_syntax_group|regbase::emacs_ex))
         m_match_flags |= match_perl;
      else if((re_f & (regbase::main_option_type|regbase::literal)) == (regbase::literal))
         m_match_flags |= match_perl;
      else
         m_match_flags |= match_posix;
   }
   if(m_match_flags & match_posix)
   {
      m_temp_match.reset(new match_results<BidiIterator, Allocator>());
      m_presult = m_temp_match.get();
   }
   else
      m_presult = &m_result;
   m_stack_base = 0;
   m_backup_state = 0;
   // find the value to use for matching word boundaries:
   m_word_mask = re.get_data().m_word_mask; 
   // find bitmask to use for matching '.':
   match_any_mask = static_cast<unsigned char>((f & match_not_dot_newline) ? BOOST_REGEX_DETAIL_NS::test_not_newline : BOOST_REGEX_DETAIL_NS::test_newline);
   // Disable match_any if requested in the state machine:
   if(e.get_data().m_disable_match_any)
      m_match_flags &= regex_constants::match_not_any;
}
#ifdef BOOST_REGEX_MSVC
#  pragma warning(pop)
#endif

template <class BidiIterator, class Allocator, class traits>
void perl_matcher<BidiIterator, Allocator, traits>::estimate_max_state_count(std::random_access_iterator_tag*)
{
   //
   // How many states should we allow our machine to visit before giving up?
   // This is a heuristic: it takes the greater of O(N^2) and O(NS^2)
   // where N is the length of the string, and S is the number of states
   // in the machine.  It's tempting to up this to O(N^2S) or even O(N^2S^2)
   // but these take unreasonably amounts of time to bale out in pathological
   // cases.
   //
   // Calculate NS^2 first:
   //
   static const std::ptrdiff_t k = 100000;
   std::ptrdiff_t dist = std::distance(base, last);
   if(dist == 0)
      dist = 1;
   std::ptrdiff_t states = re.size();
   if(states == 0)
      states = 1;
   if ((std::numeric_limits<std::ptrdiff_t>::max)() / states < states)
   {
      max_state_count = (std::min)((std::ptrdiff_t)BOOST_REGEX_MAX_STATE_COUNT, (std::numeric_limits<std::ptrdiff_t>::max)() - 2);
      return;
   }
   states *= states;
   if((std::numeric_limits<std::ptrdiff_t>::max)() / dist < states)
   {
      max_state_count = (std::min)((std::ptrdiff_t)BOOST_REGEX_MAX_STATE_COUNT, (std::numeric_limits<std::ptrdiff_t>::max)() - 2);
      return;
   }
   states *= dist;
   if((std::numeric_limits<std::ptrdiff_t>::max)() - k < states)
   {
      max_state_count = (std::min)((std::ptrdiff_t)BOOST_REGEX_MAX_STATE_COUNT, (std::numeric_limits<std::ptrdiff_t>::max)() - 2);
      return;
   }
   states += k;

   max_state_count = states;

   //
   // Now calculate N^2:
   //
   states = dist;
   if((std::numeric_limits<std::ptrdiff_t>::max)() / dist < states)
   {
      max_state_count = (std::min)((std::ptrdiff_t)BOOST_REGEX_MAX_STATE_COUNT, (std::numeric_limits<std::ptrdiff_t>::max)() - 2);
      return;
   }
   states *= dist;
   if((std::numeric_limits<std::ptrdiff_t>::max)() - k < states)
   {
      max_state_count = (std::min)((std::ptrdiff_t)BOOST_REGEX_MAX_STATE_COUNT, (std::numeric_limits<std::ptrdiff_t>::max)() - 2);
      return;
   }
   states += k;
   //
   // N^2 can be a very large number indeed, to prevent things getting out
   // of control, cap the max states:
   //
   if(states > BOOST_REGEX_MAX_STATE_COUNT)
      states = BOOST_REGEX_MAX_STATE_COUNT;
   //
   // If (the possibly capped) N^2 is larger than our first estimate,
   // use this instead:
   //
   if(states > max_state_count)
      max_state_count = states;
}

template <class BidiIterator, class Allocator, class traits>
inline void perl_matcher<BidiIterator, Allocator, traits>::estimate_max_state_count(void*)
{
   // we don't know how long the sequence is:
   max_state_count = BOOST_REGEX_MAX_STATE_COUNT;
}

template <class BidiIterator, class Allocator, class traits>
inline bool perl_matcher<BidiIterator, Allocator, traits>::match()
{
   return match_imp();
}

template <class BidiIterator, class Allocator, class traits>
bool perl_matcher<BidiIterator, Allocator, traits>::match_imp()
{
   // initialise our stack if we are non-recursive:
   save_state_init init(&m_stack_base, &m_backup_state);
   used_block_count = BOOST_REGEX_MAX_BLOCKS;
#if !defined(BOOST_NO_EXCEPTIONS)
   try{
#endif

   // reset our state machine:
   position = base;
   search_base = base;
   state_count = 0;
   m_match_flags |= regex_constants::match_all;
   m_presult->set_size((m_match_flags & match_nosubs) ? 1u : static_cast<typename results_type::size_type>(1u + re.mark_count()), search_base, last);
   m_presult->set_base(base);
   m_presult->set_named_subs(this->re.get_named_subs());
   if(m_match_flags & match_posix)
      m_result = *m_presult;
   verify_options(re.flags(), m_match_flags);
   if(0 == match_prefix())
      return false;
   return (m_result[0].second == last) && (m_result[0].first == base);

#if !defined(BOOST_NO_EXCEPTIONS)
   }
   catch(...)
   {
      // unwind all pushed states, apart from anything else this
      // ensures that all the states are correctly destructed
      // not just the memory freed.
      while(unwind(true)){}
      throw;
   }
#endif
}

template <class BidiIterator, class Allocator, class traits>
inline bool perl_matcher<BidiIterator, Allocator, traits>::find()
{
   return find_imp();
}

template <class BidiIterator, class Allocator, class traits>
bool perl_matcher<BidiIterator, Allocator, traits>::find_imp()
{
   static matcher_proc_type const s_find_vtable[7] = 
   {
      &perl_matcher<BidiIterator, Allocator, traits>::find_restart_any,
      &perl_matcher<BidiIterator, Allocator, traits>::find_restart_word,
      &perl_matcher<BidiIterator, Allocator, traits>::find_restart_line,
      &perl_matcher<BidiIterator, Allocator, traits>::find_restart_buf,
      &perl_matcher<BidiIterator, Allocator, traits>::match_prefix,
      &perl_matcher<BidiIterator, Allocator, traits>::find_restart_lit,
      &perl_matcher<BidiIterator, Allocator, traits>::find_restart_lit,
   };

   // initialise our stack if we are non-recursive:
   save_state_init init(&m_stack_base, &m_backup_state);
   used_block_count = BOOST_REGEX_MAX_BLOCKS;
#if !defined(BOOST_NO_EXCEPTIONS)
   try{
#endif

   state_count = 0;
   if((m_match_flags & regex_constants::match_init) == 0)
   {
      // reset our state machine:
      search_base = position = base;
      pstate = re.get_first_state();
      m_presult->set_size((m_match_flags & match_nosubs) ? 1u : static_cast<typename results_type::size_type>(1u + re.mark_count()), base, last);
      m_presult->set_base(base);
      m_presult->set_named_subs(this->re.get_named_subs());
      m_match_flags |= regex_constants::match_init;
   }
   else
   {
      // start again:
      search_base = position = m_result[0].second;
      // If last match was null and match_not_null was not set then increment
      // our start position, otherwise we go into an infinite loop:
      if(((m_match_flags & match_not_null) == 0) && (m_result.length() == 0))
      {
         if(position == last)
            return false;
         else 
            ++position;
      }
      // reset $` start:
      m_presult->set_size((m_match_flags & match_nosubs) ? 1u : static_cast<typename results_type::size_type>(1u + re.mark_count()), search_base, last);
      //if((base != search_base) && (base == backstop))
      //   m_match_flags |= match_prev_avail;
   }
   if(m_match_flags & match_posix)
   {
      m_result.set_size(static_cast<typename results_type::size_type>(1u + re.mark_count()), base, last);
      m_result.set_base(base);
   }

   verify_options(re.flags(), m_match_flags);
   // find out what kind of expression we have:
   unsigned type = (m_match_flags & match_continuous) ? 
      static_cast<unsigned int>(regbase::restart_continue) 
         : static_cast<unsigned int>(re.get_restart_type());

   // call the appropriate search routine:
   matcher_proc_type proc = s_find_vtable[type];
   return (this->*proc)();

#if !defined(BOOST_NO_EXCEPTIONS)
   }
   catch(...)
   {
      // unwind all pushed states, apart from anything else this
      // ensures that all the states are correctly destructed
      // not just the memory freed.
      while(unwind(true)){}
      throw;
   }
#endif
}

template <class BidiIterator, class Allocator, class traits>
bool perl_matcher<BidiIterator, Allocator, traits>::match_prefix()
{
   m_has_partial_match = false;
   m_has_found_match = false;
   pstate = re.get_first_state();
   m_presult->set_first(position);
   restart = position;
   match_all_states();
   if(!m_has_found_match && m_has_partial_match && (m_match_flags & match_partial))
   {
      m_has_found_match = true;
      m_presult->set_second(last, 0, false);
      position = last;
      if((m_match_flags & match_posix) == match_posix)
      {
         m_result.maybe_assign(*m_presult);
      }
   }
#ifdef BOOST_REGEX_MATCH_EXTRA
   if(m_has_found_match && (match_extra & m_match_flags))
   {
      //
      // we have a match, reverse the capture information:
      //
      for(unsigned i = 0; i < m_presult->size(); ++i)
      {
         typename sub_match<BidiIterator>::capture_sequence_type & seq = ((*m_presult)[i]).get_captures();
         std::reverse(seq.begin(), seq.end());
      }
   }
#endif
   if(!m_has_found_match)
      position = restart; // reset search postion
   return m_has_found_match;
}

template <class BidiIterator, class Allocator, class traits>
bool perl_matcher<BidiIterator, Allocator, traits>::match_literal()
{
   unsigned int len = static_cast<const re_literal*>(pstate)->length;
   const char_type* what = reinterpret_cast<const char_type*>(static_cast<const re_literal*>(pstate) + 1);
   //
   // compare string with what we stored in
   // our records:
   for(unsigned int i = 0; i < len; ++i, ++position)
   {
      if((position == last) || (traits_inst.translate(*position, icase) != what[i]))
         return false;
   }
   pstate = pstate->next.p;
   return true;
}

template <class BidiIterator, class Allocator, class traits>
bool perl_matcher<BidiIterator, Allocator, traits>::match_start_line()
{
   if(position == backstop)
   {
      if((m_match_flags & match_prev_avail) == 0)
      {
         if((m_match_flags & match_not_bol) == 0)
         {
            pstate = pstate->next.p;
            return true;
         }
         return false;
      }
   }
   else if(m_match_flags & match_single_line)
      return false;

   // check the previous value character:
   BidiIterator t(position);
   --t;
   if(position != last)
   {
      if(is_separator(*t) && !((*t == static_cast<char_type>('\r')) && (*position == static_cast<char_type>('\n'))) )
      {
         pstate = pstate->next.p;
         return true;
      }
   }
   else if(is_separator(*t))
   {
      pstate = pstate->next.p;
      return true;
   }
   return false;
}

template <class BidiIterator, class Allocator, class traits>
bool perl_matcher<BidiIterator, Allocator, traits>::match_end_line()
{
   if(position != last)
   {
      if(m_match_flags & match_single_line)
         return false;
      // we're not yet at the end so *first is always valid:
      if(is_separator(*position))
      {
         if((position != backstop) || (m_match_flags & match_prev_avail))
         {
            // check that we're not in the middle of \r\n sequence
            BidiIterator t(position);
            --t;
            if((*t == static_cast<char_type>('\r')) && (*position == static_cast<char_type>('\n')))
            {
               return false;
            }
         }
         pstate = pstate->next.p;
         return true;
      }
   }
   else if((m_match_flags & match_not_eol) == 0)
   {
      pstate = pstate->next.p;
      return true;
   }
   return false;
}

template <class BidiIterator, class Allocator, class traits>
bool perl_matcher<BidiIterator, Allocator, traits>::match_wild()
{
   if(position == last) 
      return false;
   if(is_separator(*position) && ((match_any_mask & static_cast<const re_dot*>(pstate)->mask) == 0))
      return false;
   if((*position == char_type(0)) && (m_match_flags & match_not_dot_null))
      return false;
   pstate = pstate->next.p;
   ++position;
   return true;
}

template <class BidiIterator, class Allocator, class traits>
bool perl_matcher<BidiIterator, Allocator, traits>::match_word_boundary()
{
   bool b; // indcates whether next character is a word character
   if(position != last)
   {
      // prev and this character must be opposites:
      b = traits_inst.isctype(*position, m_word_mask);
   }
   else
   {
      if (m_match_flags & match_not_eow)
         return false;
      b = false;
   }
   if((position == backstop) && ((m_match_flags & match_prev_avail) == 0))
   {
      if(m_match_flags & match_not_bow)
         return false;
      else
         b ^= false;
   }
   else
   {
      --position;
      b ^= traits_inst.isctype(*position, m_word_mask);
      ++position;
   }
   if(b)
   {
      pstate = pstate->next.p;
      return true;
   }
   return false; // no match if we get to here...
}

template <class BidiIterator, class Allocator, class traits>
bool perl_matcher<BidiIterator, Allocator, traits>::match_within_word()
{
   bool b = !match_word_boundary();
   if(b)
      pstate = pstate->next.p;
   return b;
   /*
   if(position == last)
      return false;
   // both prev and this character must be m_word_mask:
   bool prev = traits_inst.isctype(*position, m_word_mask);
   {
      bool b;
      if((position == backstop) && ((m_match_flags & match_prev_avail) == 0)) 
         return false;
      else
      {
         --position;
         b = traits_inst.isctype(*position, m_word_mask);
         ++position;
      }
      if(b == prev)
      {
         pstate = pstate->next.p;
         return true;
      }
   }
   return false;
   */
}

template <class BidiIterator, class Allocator, class traits>
bool perl_matcher<BidiIterator, Allocator, traits>::match_word_start()
{
   if(position == last)
      return false; // can't be starting a word if we're already at the end of input
   if(!traits_inst.isctype(*position, m_word_mask))
      return false; // next character isn't a word character
   if((position == backstop) && ((m_match_flags & match_prev_avail) == 0))
   {
      if(m_match_flags & match_not_bow)
         return false; // no previous input
   }
   else
   {
      // otherwise inside buffer:
      BidiIterator t(position);
      --t;
      if(traits_inst.isctype(*t, m_word_mask))
         return false; // previous character not non-word
   }
   // OK we have a match:
   pstate = pstate->next.p;
   return true;
}

template <class BidiIterator, class Allocator, class traits>
bool perl_matcher<BidiIterator, Allocator, traits>::match_word_end()
{
   if((position == backstop) && ((m_match_flags & match_prev_avail) == 0))
      return false;  // start of buffer can't be end of word
   BidiIterator t(position);
   --t;
   if(traits_inst.isctype(*t, m_word_mask) == false)
      return false;  // previous character wasn't a word character

   if(position == last)
   {
      if(m_match_flags & match_not_eow)
         return false; // end of buffer but not end of word
   }
   else
   {
      // otherwise inside buffer:
      if(traits_inst.isctype(*position, m_word_mask))
         return false; // next character is a word character
   }
   pstate = pstate->next.p;
   return true;      // if we fall through to here then we've succeeded
}

template <class BidiIterator, class Allocator, class traits>
bool perl_matcher<BidiIterator, Allocator, traits>::match_buffer_start()
{
   if((position != backstop) || (m_match_flags & match_not_bob))
      return false;
   // OK match:
   pstate = pstate->next.p;
   return true;
}

template <class BidiIterator, class Allocator, class traits>
bool perl_matcher<BidiIterator, Allocator, traits>::match_buffer_end()
{
   if((position != last) || (m_match_flags & match_not_eob))
      return false;
   // OK match:
   pstate = pstate->next.p;
   return true;
}

template <class BidiIterator, class Allocator, class traits>
bool perl_matcher<BidiIterator, Allocator, traits>::match_backref()
{
   //
   // Compare with what we previously matched.
   // Note that this succeeds if the backref did not partisipate
   // in the match, this is in line with ECMAScript, but not Perl
   // or PCRE.
   //
   int index = static_cast<const re_brace*>(pstate)->index;
   if(index >= hash_value_mask)
   {
      named_subexpressions::range_type r = re.get_data().equal_range(index);
      BOOST_REGEX_ASSERT(r.first != r.second);
      do
      {
         index = r.first->index;
         ++r.first;
      }while((r.first != r.second) && ((*m_presult)[index].matched != true));
   }

   if((m_match_flags & match_perl) && !(*m_presult)[index].matched)
      return false;

   BidiIterator i = (*m_presult)[index].first;
   BidiIterator j = (*m_presult)[index].second;
   while(i != j)
   {
      if((position == last) || (traits_inst.translate(*position, icase) != traits_inst.translate(*i, icase)))
         return false;
      ++i;
      ++position;
   }
   pstate = pstate->next.p;
   return true;
}

template <class BidiIterator, class Allocator, class traits>
bool perl_matcher<BidiIterator, Allocator, traits>::match_long_set()
{
   typedef typename traits::char_class_type char_class_type;
   // let the traits class do the work:
   if(position == last)
      return false;
   BidiIterator t = re_is_set_member(position, last, static_cast<const re_set_long<char_class_type>*>(pstate), re.get_data(), icase);
   if(t != position)
   {
      pstate = pstate->next.p;
      position = t;
      return true;
   }
   return false;
}

template <class BidiIterator, class Allocator, class traits>
bool perl_matcher<BidiIterator, Allocator, traits>::match_set()
{
   if(position == last)
      return false;
   if(static_cast<const re_set*>(pstate)->_map[static_cast<unsigned char>(traits_inst.translate(*position, icase))])
   {
      pstate = pstate->next.p;
      ++position;
      return true;
   }
   return false;
}

template <class BidiIterator, class Allocator, class traits>
bool perl_matcher<BidiIterator, Allocator, traits>::match_jump()
{
   pstate = static_cast<const re_jump*>(pstate)->alt.p;
   return true;
}

template <class BidiIterator, class Allocator, class traits>
bool perl_matcher<BidiIterator, Allocator, traits>::match_combining()
{
   if(position == last)
      return false;
   if(is_combining(traits_inst.translate(*position, icase)))
      return false;
   ++position;
   while((position != last) && is_combining(traits_inst.translate(*position, icase)))
      ++position;
   pstate = pstate->next.p;
   return true;
}

template <class BidiIterator, class Allocator, class traits>
bool perl_matcher<BidiIterator, Allocator, traits>::match_soft_buffer_end()
{
   if(m_match_flags & match_not_eob)
      return false;
   BidiIterator p(position);
   while((p != last) && is_separator(traits_inst.translate(*p, icase)))++p;
   if(p != last)
      return false;
   pstate = pstate->next.p;
   return true;
}

template <class BidiIterator, class Allocator, class traits>
bool perl_matcher<BidiIterator, Allocator, traits>::match_restart_continue()
{
   if(position == search_base)
   {
      pstate = pstate->next.p;
      return true;
   }
   return false;
}

template <class BidiIterator, class Allocator, class traits>
bool perl_matcher<BidiIterator, Allocator, traits>::match_backstep()
{
#ifdef BOOST_REGEX_MSVC
#pragma warning(push)
#pragma warning(disable:4127)
#endif
   if( ::boost::is_random_access_iterator<BidiIterator>::value)
   {
      std::ptrdiff_t maxlen = std::distance(backstop, position);
      if(maxlen < static_cast<const re_brace*>(pstate)->index)
         return false;
      std::advance(position, -static_cast<const re_brace*>(pstate)->index);
   }
   else
   {
      int c = static_cast<const re_brace*>(pstate)->index;
      while(c--)
      {
         if(position == backstop)
            return false;
         --position;
      }
   }
   pstate = pstate->next.p;
   return true;
#ifdef BOOST_REGEX_MSVC
#pragma warning(pop)
#endif
}

template <class BidiIterator, class Allocator, class traits>
inline bool perl_matcher<BidiIterator, Allocator, traits>::match_assert_backref()
{
   // return true if marked sub-expression N has been matched:
   int index = static_cast<const re_brace*>(pstate)->index;
   bool result = false;
   if(index == 9999)
   {
      // Magic value for a (DEFINE) block:
      return false;
   }
   else if(index > 0)
   {
      // Have we matched subexpression "index"?
      // Check if index is a hash value:
      if(index >= hash_value_mask)
      {
         named_subexpressions::range_type r = re.get_data().equal_range(index);
         while(r.first != r.second)
         {
            if((*m_presult)[r.first->index].matched)
            {
               result = true;
               break;
            }
            ++r.first;
         }
      }
      else
      {
         result = (*m_presult)[index].matched;
      }
      pstate = pstate->next.p;
   }
   else
   {
      // Have we recursed into subexpression "index"?
      // If index == 0 then check for any recursion at all, otherwise for recursion to -index-1.
      int idx = -(index+1);
      if(idx >= hash_value_mask)
      {
         named_subexpressions::range_type r = re.get_data().equal_range(idx);
         int stack_index = recursion_stack.empty() ? -1 : recursion_stack.back().idx;
         while(r.first != r.second)
         {
            result |= (stack_index == r.first->index);
            if(result)break;
            ++r.first;
         }
      }
      else
      {
         result = !recursion_stack.empty() && ((recursion_stack.back().idx == idx) || (index == 0));
      }
      pstate = pstate->next.p;
   }
   return result;
}

template <class BidiIterator, class Allocator, class traits>
bool perl_matcher<BidiIterator, Allocator, traits>::match_fail()
{
   // Just force a backtrack:
   return false;
}

template <class BidiIterator, class Allocator, class traits>
bool perl_matcher<BidiIterator, Allocator, traits>::match_accept()
{
   if(!recursion_stack.empty())
   {
      return skip_until_paren(recursion_stack.back().idx);
   }
   else
   {
      return skip_until_paren(INT_MAX);
   }
}

template <class BidiIterator, class Allocator, class traits>
bool perl_matcher<BidiIterator, Allocator, traits>::find_restart_any()
{
#ifdef BOOST_REGEX_MSVC
#pragma warning(push)
#pragma warning(disable:4127)
#endif
   const unsigned char* _map = re.get_map();
   while(true)
   {
      // skip everything we can't match:
      while((position != last) && !can_start(*position, _map, (unsigned char)mask_any) )
         ++position;
      if(position == last)
      {
         // run out of characters, try a null match if possible:
         if(re.can_be_null())
            return match_prefix();
         break;
      }
      // now try and obtain a match:
      if(match_prefix())
         return true;
      if(position == last)
         return false;
      ++position;
   }
   return false;
#ifdef BOOST_REGEX_MSVC
#pragma warning(pop)
#endif
}

template <class BidiIterator, class Allocator, class traits>
bool perl_matcher<BidiIterator, Allocator, traits>::find_restart_word()
{
#ifdef BOOST_REGEX_MSVC
#pragma warning(push)
#pragma warning(disable:4127)
#endif
   // do search optimised for word starts:
   const unsigned char* _map = re.get_map();
   if((m_match_flags & match_prev_avail) || (position != base))
      --position;
   else if(match_prefix())
      return true;
   do
   {
      while((position != last) && traits_inst.isctype(*position, m_word_mask))
         ++position;
      while((position != last) && !traits_inst.isctype(*position, m_word_mask))
         ++position;
      if(position == last)
         break;

      if(can_start(*position, _map, (unsigned char)mask_any) )
      {
         if(match_prefix())
            return true;
      }
      if(position == last)
         break;
   } while(true);
   return false;
#ifdef BOOST_REGEX_MSVC
#pragma warning(pop)
#endif
}

template <class BidiIterator, class Allocator, class traits>
bool perl_matcher<BidiIterator, Allocator, traits>::find_restart_line()
{
   // do search optimised for line starts:
   const unsigned char* _map = re.get_map();
   if(match_prefix())
      return true;
   while(position != last)
   {
      while((position != last) && !is_separator(*position))
         ++position;
      if(position == last)
         return false;
      ++position;
      if(position == last)
      {
         if(re.can_be_null() && match_prefix())
            return true;
         return false;
      }

      if( can_start(*position, _map, (unsigned char)mask_any) )
      {
         if(match_prefix())
            return true;
      }
      if(position == last)
         return false;
      //++position;
   }
   return false;
}

template <class BidiIterator, class Allocator, class traits>
bool perl_matcher<BidiIterator, Allocator, traits>::find_restart_buf()
{
   if((position == base) && ((m_match_flags & match_not_bob) == 0))
      return match_prefix();
   return false;
}

template <class BidiIterator, class Allocator, class traits>
bool perl_matcher<BidiIterator, Allocator, traits>::find_restart_lit()
{
   return false;
}

} // namespace BOOST_REGEX_DETAIL_NS

} // namespace boost

#ifdef BOOST_REGEX_MSVC
#  pragma warning(pop)
#endif

#endif


/* perl_matcher_common.hpp
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
*/