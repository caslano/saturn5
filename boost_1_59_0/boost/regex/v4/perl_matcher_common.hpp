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

#ifndef BOOST_REGEX_V4_PERL_MATCHER_COMMON_HPP
#define BOOST_REGEX_V4_PERL_MATCHER_COMMON_HPP

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4103)
#if BOOST_MSVC >= 1800
#pragma warning(disable: 26812)
#endif
#endif
#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#ifdef BOOST_BORLANDC
#  pragma option push -w-8008 -w-8066
#endif
#ifdef BOOST_MSVC
#  pragma warning(push)
#if BOOST_MSVC < 1910
#pragma warning(disable:4800)
#endif
#endif

namespace boost{
namespace BOOST_REGEX_DETAIL_NS{

#ifdef BOOST_MSVC
#  pragma warning(push)
#pragma warning(disable:26812)
#endif
   template <class BidiIterator, class Allocator, class traits>
void perl_matcher<BidiIterator, Allocator, traits>::construct_init(const basic_regex<char_type, traits>& e, match_flag_type f)
{ 
   typedef typename regex_iterator_traits<BidiIterator>::iterator_category category;
   typedef typename basic_regex<char_type, traits>::flag_type expression_flag_type;
   
   if(e.empty())
   {
      // precondition failure: e is not a valid regex.
      std::invalid_argument ex("Invalid regular expression object");
      boost::throw_exception(ex);
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
#ifdef BOOST_REGEX_NON_RECURSIVE
   m_stack_base = 0;
   m_backup_state = 0;
#elif defined(BOOST_REGEX_RECURSIVE)
   m_can_backtrack = true;
   m_have_accept = false;
#endif
   // find the value to use for matching word boundaries:
   m_word_mask = re.get_data().m_word_mask; 
   // find bitmask to use for matching '.':
   match_any_mask = static_cast<unsigned char>((f & match_not_dot_newline) ? BOOST_REGEX_DETAIL_NS::test_not_newline : BOOST_REGEX_DETAIL_NS::test_newline);
   // Disable match_any if requested in the state machine:
   if(e.get_data().m_disable_match_any)
      m_match_flags &= regex_constants::match_not_any;
}
#ifdef BOOST_MSVC
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
   std::ptrdiff_t dist = boost::BOOST_REGEX_DETAIL_NS::distance(base, last);
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

#ifdef BOOST_REGEX_HAS_MS_STACK_GUARD
template <class BidiIterator, class Allocator, class traits>
inline bool perl_matcher<BidiIterator, Allocator, traits>::protected_call(
   protected_proc_type proc)
{
   ::boost::BOOST_REGEX_DETAIL_NS::concrete_protected_call
      <perl_matcher<BidiIterator, Allocator, traits> >
      obj(this, proc);
   return obj.execute();

}
#endif

template <class BidiIterator, class Allocator, class traits>
inline bool perl_matcher<BidiIterator, Allocator, traits>::match()
{
#ifdef BOOST_REGEX_HAS_MS_STACK_GUARD
   return protected_call(&perl_matcher<BidiIterator, Allocator, traits>::match_imp);
#else
   return match_imp();
#endif
}

template <class BidiIterator, class Allocator, class traits>
bool perl_matcher<BidiIterator, Allocator, traits>::match_imp()
{
   // initialise our stack if we are non-recursive:
#ifdef BOOST_REGEX_NON_RECURSIVE
   save_state_init init(&m_stack_base, &m_backup_state);
   used_block_count = BOOST_REGEX_MAX_BLOCKS;
#if !defined(BOOST_NO_EXCEPTIONS)
   try{
#endif
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

#if defined(BOOST_REGEX_NON_RECURSIVE) && !defined(BOOST_NO_EXCEPTIONS)
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
#ifdef BOOST_REGEX_HAS_MS_STACK_GUARD
   return protected_call(&perl_matcher<BidiIterator, Allocator, traits>::find_imp);
#else
   return find_imp();
#endif
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
#ifdef BOOST_REGEX_NON_RECURSIVE
   save_state_init init(&m_stack_base, &m_backup_state);
   used_block_count = BOOST_REGEX_MAX_BLOCKS;
#if !defined(BOOST_NO_EXCEPTIONS)
   try{
#endif
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

#if defined(BOOST_REGEX_NON_RECURSIVE) && !defined(BOOST_NO_EXCEPTIONS)
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
#ifdef BOOST_REGEX_RECURSIVE
   m_can_backtrack = true; // reset for further searches
#endif
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
#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable:4127)
#endif
   if( ::boost::is_random_access_iterator<BidiIterator>::value)
   {
      std::ptrdiff_t maxlen = ::boost::BOOST_REGEX_DETAIL_NS::distance(backstop, position);
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
#ifdef BOOST_MSVC
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
#ifdef BOOST_MSVC
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
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif
}

template <class BidiIterator, class Allocator, class traits>
bool perl_matcher<BidiIterator, Allocator, traits>::find_restart_word()
{
#ifdef BOOST_MSVC
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
#ifdef BOOST_MSVC
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
#if 0
   if(position == last)
      return false; // can't possibly match if we're at the end already

   unsigned type = (m_match_flags & match_continuous) ? 
      static_cast<unsigned int>(regbase::restart_continue) 
         : static_cast<unsigned int>(re.get_restart_type());

   const kmp_info<char_type>* info = access::get_kmp(re);
   int len = info->len;
   const char_type* x = info->pstr;
   int j = 0; 
   while (position != last) 
   {
      while((j > -1) && (x[j] != traits_inst.translate(*position, icase))) 
         j = info->kmp_next[j];
      ++position;
      ++j;
      if(j >= len) 
      {
         if(type == regbase::restart_fixed_lit)
         {
            std::advance(position, -j);
            restart = position;
            std::advance(restart, len);
            m_result.set_first(position);
            m_result.set_second(restart);
            position = restart;
            return true;
         }
         else
         {
            restart = position;
            std::advance(position, -j);
            if(match_prefix())
               return true;
            else
            {
               for(int k = 0; (restart != position) && (k < j); ++k, --restart)
                     {} // dwa 10/20/2000 - warning suppression for MWCW
               if(restart != last)
                  ++restart;
               position = restart;
               j = 0;  //we could do better than this...
            }
         }
      }
   }
   if((m_match_flags & match_partial) && (position == last) && j)
   {
      // we need to check for a partial match:
      restart = position;
      std::advance(position, -j);
      return match_prefix();
   }
#endif
   return false;
}

} // namespace BOOST_REGEX_DETAIL_NS

} // namespace boost

#ifdef BOOST_MSVC
#  pragma warning(pop)
#endif

#ifdef BOOST_BORLANDC
#  pragma option pop
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


/* perl_matcher_common.hpp
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
*/