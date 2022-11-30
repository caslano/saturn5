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

#ifndef BOOST_REGEX_MATCHER_HPP
#define BOOST_REGEX_MATCHER_HPP

#include <boost/regex/v5/iterator_category.hpp>

#ifdef BOOST_REGEX_MSVC
#  pragma warning(push)
#pragma warning(disable : 4251 4459)
#if BOOST_REGEX_MSVC < 1700
#     pragma warning(disable : 4231)
#endif
#  if BOOST_REGEX_MSVC < 1600
#     pragma warning(disable : 4660)
#  endif
#if BOOST_REGEX_MSVC < 1910
#pragma warning(disable:4800)
#endif
#endif

namespace boost{
namespace BOOST_REGEX_DETAIL_NS{

//
// error checking API:
//
inline void  verify_options(boost::regex_constants::syntax_option_type, match_flag_type mf)
{
   //
   // can't mix match_extra with POSIX matching rules:
   //
   if ((mf & match_extra) && (mf & match_posix))
   {
      std::logic_error msg("Usage Error: Can't mix regular expression captures with POSIX matching rules");
#ifndef BOOST_REGEX_STANDALONE
      throw_exception(msg);
#else
      throw msg;
#endif
   }
}
//
// function can_start:
//
template <class charT>
inline bool can_start(charT c, const unsigned char* map, unsigned char mask)
{
   return ((c < static_cast<charT>(0)) ? true : ((c >= static_cast<charT>(1 << CHAR_BIT)) ? true : map[c] & mask));
}
inline bool can_start(char c, const unsigned char* map, unsigned char mask)
{
   return map[(unsigned char)c] & mask;
}
inline bool can_start(signed char c, const unsigned char* map, unsigned char mask)
{
   return map[(unsigned char)c] & mask;
}
inline bool can_start(unsigned char c, const unsigned char* map, unsigned char mask)
{
   return map[c] & mask;
}
inline bool can_start(unsigned short c, const unsigned char* map, unsigned char mask)
{
   return ((c >= (1 << CHAR_BIT)) ? true : map[c] & mask);
}
#if defined(WCHAR_MIN) && (WCHAR_MIN == 0) && !defined(BOOST_NO_INTRINSIC_WCHAR_T)
inline bool can_start(wchar_t c, const unsigned char* map, unsigned char mask)
{
   return ((c >= static_cast<wchar_t>(1u << CHAR_BIT)) ? true : map[c] & mask);
}
#endif
#if !defined(BOOST_NO_INTRINSIC_WCHAR_T)
inline bool can_start(unsigned int c, const unsigned char* map, unsigned char mask)
{
   return (((c >= static_cast<unsigned int>(1u << CHAR_BIT)) ? true : map[c] & mask));
}
#endif

template <class C, class T, class A>
inline int string_compare(const std::basic_string<C,T,A>& s, const C* p)
{ 
   if(0 == *p)
   {
      if(s.empty() || ((s.size() == 1) && (s[0] == 0)))
         return 0;
   }
   return s.compare(p); 
}
template <class Seq, class C>
inline int string_compare(const Seq& s, const C* p)
{
   std::size_t i = 0;
   while((i < s.size()) && (p[i] == s[i]))
   {
      ++i;
   }
   return (i == s.size()) ? -(int)p[i] : (int)s[i] - (int)p[i];
}
# define STR_COMP(s,p) string_compare(s,p)

template<class charT>
inline const charT* re_skip_past_null(const charT* p)
{
  while (*p != static_cast<charT>(0)) ++p;
  return ++p;
}

template <class iterator, class charT, class traits_type, class char_classT>
iterator  re_is_set_member(iterator next, 
                          iterator last, 
                          const re_set_long<char_classT>* set_, 
                          const regex_data<charT, traits_type>& e, bool icase)
{   
   const charT* p = reinterpret_cast<const charT*>(set_+1);
   iterator ptr;
   unsigned int i;
   //bool icase = e.m_flags & regex_constants::icase;

   if(next == last) return next;

   typedef typename traits_type::string_type traits_string_type;
   const ::boost::regex_traits_wrapper<traits_type>& traits_inst = *(e.m_ptraits);
   
   // dwa 9/13/00 suppress incorrect MSVC warning - it claims this is never
   // referenced
   (void)traits_inst;

   // try and match a single character, could be a multi-character
   // collating element...
   for(i = 0; i < set_->csingles; ++i)
   {
      ptr = next;
      if(*p == static_cast<charT>(0))
      {
         // treat null string as special case:
         if(traits_inst.translate(*ptr, icase))
         {
            ++p;
            continue;
         }
         return set_->isnot ? next : (ptr == next) ? ++next : ptr;
      }
      else
      {
         while(*p && (ptr != last))
         {
            if(traits_inst.translate(*ptr, icase) != *p)
               break;
            ++p;
            ++ptr;
         }

         if(*p == static_cast<charT>(0)) // if null we've matched
            return set_->isnot ? next : (ptr == next) ? ++next : ptr;

         p = re_skip_past_null(p);     // skip null
      }
   }

   charT col = traits_inst.translate(*next, icase);


   if(set_->cranges || set_->cequivalents)
   {
      traits_string_type s1;
      //
      // try and match a range, NB only a single character can match
      if(set_->cranges)
      {
         if((e.m_flags & regex_constants::collate) == 0)
            s1.assign(1, col);
         else
         {
            charT a[2] = { col, charT(0), };
            s1 = traits_inst.transform(a, a + 1);
         }
         for(i = 0; i < set_->cranges; ++i)
         {
            if(STR_COMP(s1, p) >= 0)
            {
               do{ ++p; }while(*p);
               ++p;
               if(STR_COMP(s1, p) <= 0)
                  return set_->isnot ? next : ++next;
            }
            else
            {
               // skip first string
               do{ ++p; }while(*p);
               ++p;
            }
            // skip second string
            do{ ++p; }while(*p);
            ++p;
         }
      }
      //
      // try and match an equivalence class, NB only a single character can match
      if(set_->cequivalents)
      {
         charT a[2] = { col, charT(0), };
         s1 = traits_inst.transform_primary(a, a +1);
         for(i = 0; i < set_->cequivalents; ++i)
         {
            if(STR_COMP(s1, p) == 0)
               return set_->isnot ? next : ++next;
            // skip string
            do{ ++p; }while(*p);
            ++p;
         }
      }
   }
   if(traits_inst.isctype(col, set_->cclasses) == true)
      return set_->isnot ? next : ++next;
   if((set_->cnclasses != 0) && (traits_inst.isctype(col, set_->cnclasses) == false))
      return set_->isnot ? next : ++next;
   return set_->isnot ? ++next : next;
}

template <class BidiIterator>
class repeater_count
{
   repeater_count** stack;
   repeater_count* next;
   int state_id;
   std::size_t count;        // the number of iterations so far
   BidiIterator start_pos;   // where the last repeat started

   repeater_count* unwind_until(int n, repeater_count* p, int current_recursion_id)
   { 
      while(p && (p->state_id != n))
      {
         if(-2 - current_recursion_id == p->state_id)
            return 0;
         p = p->next;
         if(p && (p->state_id < 0))
         {
            p = unwind_until(p->state_id, p, current_recursion_id);
            if(!p)
               return p;
            p = p->next;
         }
      }
      return p;
   }
public:
   repeater_count(repeater_count** s) : stack(s), next(0), state_id(-1), count(0), start_pos() {}
   
   repeater_count(int i, repeater_count** s, BidiIterator start, int current_recursion_id)
      : start_pos(start)
   {
      state_id = i;
      stack = s;
      next = *stack;
      *stack = this;
      if((state_id > next->state_id) && (next->state_id >= 0))
         count = 0;
      else
      {
         repeater_count* p = next;
         p = unwind_until(state_id, p, current_recursion_id);
         if(p)
         {
            count = p->count;
            start_pos = p->start_pos;
         }
         else
            count = 0;
      }
   }
   ~repeater_count()
   {
      if(next)
         *stack = next;
   }
   std::size_t get_count() { return count; }
   int get_id() { return state_id; }
   std::size_t operator++() { return ++count; }
   bool check_null_repeat(const BidiIterator& pos, std::size_t max)
   {
      // this is called when we are about to start a new repeat,
      // if the last one was NULL move our count to max,
      // otherwise save the current position.
      bool result = (count == 0) ? false : (pos == start_pos);
      if(result)
         count = max;
      else
         start_pos = pos;
      return result;
   }
};

struct saved_state;

enum saved_state_type
{
   saved_type_end = 0,
   saved_type_paren = 1,
   saved_type_recurse = 2,
   saved_type_assertion = 3,
   saved_state_alt = 4,
   saved_state_repeater_count = 5,
   saved_state_extra_block = 6,
   saved_state_greedy_single_repeat = 7,
   saved_state_rep_slow_dot = 8,
   saved_state_rep_fast_dot = 9,
   saved_state_rep_char = 10,
   saved_state_rep_short_set = 11,
   saved_state_rep_long_set = 12,
   saved_state_non_greedy_long_repeat = 13, 
   saved_state_count = 14
};

#ifdef BOOST_REGEX_MSVC
#  pragma warning(push)
#if BOOST_REGEX_MSVC >= 1800
#pragma warning(disable:26495)
#endif
#endif
template <class Results>
struct recursion_info
{
   typedef typename Results::value_type value_type;
   typedef typename value_type::iterator iterator;
   int idx;
   const re_syntax_base* preturn_address;
   Results results;
   repeater_count<iterator>* repeater_stack;
   iterator location_of_start;
};
#ifdef BOOST_REGEX_MSVC
#  pragma warning(pop)
#endif

template <class BidiIterator, class Allocator, class traits>
class perl_matcher
{
public:
   typedef typename traits::char_type char_type;
   typedef perl_matcher<BidiIterator, Allocator, traits> self_type;
   typedef bool (self_type::*matcher_proc_type)();
   typedef std::size_t traits_size_type;
   typedef typename is_byte<char_type>::width_type width_type;
   typedef typename std::iterator_traits<BidiIterator>::difference_type difference_type;
   typedef match_results<BidiIterator, Allocator> results_type;

   perl_matcher(BidiIterator first, BidiIterator end, 
      match_results<BidiIterator, Allocator>& what, 
      const basic_regex<char_type, traits>& e,
      match_flag_type f,
      BidiIterator l_base)
      :  m_result(what), base(first), last(end), 
         position(first), backstop(l_base), re(e), traits_inst(e.get_traits()), 
         m_independent(false), next_count(&rep_obj), rep_obj(&next_count)
      , m_recursions(0)
   {
      construct_init(e, f);
   }

   bool match();
   bool find();

   void setf(match_flag_type f)
   { m_match_flags |= f; }
   void unsetf(match_flag_type f)
   { m_match_flags &= ~f; }

private:
   void construct_init(const basic_regex<char_type, traits>& e, match_flag_type f);

   bool find_imp();
   bool match_imp();
   void estimate_max_state_count(std::random_access_iterator_tag*);
   void estimate_max_state_count(void*);
   bool match_prefix();
   bool match_all_states();

   // match procs, stored in s_match_vtable:
   bool match_startmark();
   bool match_endmark();
   bool match_literal();
   bool match_start_line();
   bool match_end_line();
   bool match_wild();
   bool match_match();
   bool match_word_boundary();
   bool match_within_word();
   bool match_word_start();
   bool match_word_end();
   bool match_buffer_start();
   bool match_buffer_end();
   bool match_backref();
   bool match_long_set();
   bool match_set();
   bool match_jump();
   bool match_alt();
   bool match_rep();
   bool match_combining();
   bool match_soft_buffer_end();
   bool match_restart_continue();
   bool match_long_set_repeat();
   bool match_set_repeat();
   bool match_char_repeat();
   bool match_dot_repeat_fast();
   bool match_dot_repeat_slow();
   bool match_dot_repeat_dispatch()
   {
      return ::boost::is_random_access_iterator<BidiIterator>::value ? match_dot_repeat_fast() : match_dot_repeat_slow();
   }
   bool match_backstep();
   bool match_assert_backref();
   bool match_toggle_case();
   bool match_recursion();
   bool match_fail();
   bool match_accept();
   bool match_commit();
   bool match_then();
   bool skip_until_paren(int index, bool match = true);

   // find procs stored in s_find_vtable:
   bool find_restart_any();
   bool find_restart_word();
   bool find_restart_line();
   bool find_restart_buf();
   bool find_restart_lit();

private:
   // final result structure to be filled in:
   match_results<BidiIterator, Allocator>& m_result;
   // temporary result for POSIX matches:
   std::unique_ptr<match_results<BidiIterator, Allocator> > m_temp_match;
   // pointer to actual result structure to fill in:
   match_results<BidiIterator, Allocator>* m_presult;
   // start of sequence being searched:
   BidiIterator base;
   // end of sequence being searched:
   BidiIterator last; 
   // current character being examined:
   BidiIterator position;
   // where to restart next search after failed match attempt:
   BidiIterator restart;
   // where the current search started from, acts as base for $` during grep:
   BidiIterator search_base;
   // how far we can go back when matching lookbehind:
   BidiIterator backstop;
   // the expression being examined:
   const basic_regex<char_type, traits>& re;
   // the expression's traits class:
   const ::boost::regex_traits_wrapper<traits>& traits_inst;
   // the next state in the machine being matched:
   const re_syntax_base* pstate;
   // matching flags in use:
   match_flag_type m_match_flags;
   // how many states we have examined so far:
   std::ptrdiff_t state_count;
   // max number of states to examine before giving up:
   std::ptrdiff_t max_state_count;
   // whether we should ignore case or not:
   bool icase;
   // set to true when (position == last), indicates that we may have a partial match:
   bool m_has_partial_match;
   // set to true whenever we get a match:
   bool m_has_found_match;
   // set to true whenever we're inside an independent sub-expression:
   bool m_independent;
   // the current repeat being examined:
   repeater_count<BidiIterator>* next_count;
   // the first repeat being examined (top of linked list):
   repeater_count<BidiIterator> rep_obj;
   // the mask to pass when matching word boundaries:
   typename traits::char_class_type m_word_mask;
   // the bitmask to use when determining whether a match_any matches a newline or not:
   unsigned char match_any_mask;
   // recursion information:
   std::vector<recursion_info<results_type> > recursion_stack;
   //
   // additional members for non-recursive version:
   //
   typedef bool (self_type::*unwind_proc_type)(bool);

   void extend_stack();
   bool unwind(bool);
   bool unwind_end(bool);
   bool unwind_paren(bool);
   bool unwind_recursion_stopper(bool);
   bool unwind_assertion(bool);
   bool unwind_alt(bool);
   bool unwind_repeater_counter(bool);
   bool unwind_extra_block(bool);
   bool unwind_greedy_single_repeat(bool);
   bool unwind_slow_dot_repeat(bool);
   bool unwind_fast_dot_repeat(bool);
   bool unwind_char_repeat(bool);
   bool unwind_short_set_repeat(bool);
   bool unwind_long_set_repeat(bool);
   bool unwind_non_greedy_repeat(bool);
   bool unwind_recursion(bool);
   bool unwind_recursion_pop(bool);
   bool unwind_commit(bool);
   bool unwind_then(bool);
   bool unwind_case(bool);
   void destroy_single_repeat();
   void push_matched_paren(int index, const sub_match<BidiIterator>& sub);
   void push_recursion_stopper();
   void push_assertion(const re_syntax_base* ps, bool positive);
   void push_alt(const re_syntax_base* ps);
   void push_repeater_count(int i, repeater_count<BidiIterator>** s);
   void push_single_repeat(std::size_t c, const re_repeat* r, BidiIterator last_position, int state_id);
   void push_non_greedy_repeat(const re_syntax_base* ps);
   void push_recursion(int idx, const re_syntax_base* p, results_type* presults, results_type* presults2);
   void push_recursion_pop();
   void push_case_change(bool);

   // pointer to base of stack:
   saved_state* m_stack_base;
   // pointer to current stack position:
   saved_state* m_backup_state;
   // how many memory blocks have we used up?:
   unsigned used_block_count;
   // determines what value to return when unwinding from recursion,
   // allows for mixed recursive/non-recursive algorithm:
   bool m_recursive_result;
   // We have unwound to a lookahead/lookbehind, used by COMMIT/PRUNE/SKIP:
   bool m_unwound_lookahead;
   // We have unwound to an alternative, used by THEN:
   bool m_unwound_alt;
   // We are unwinding a commit - used by independent subs to determine whether to stop there or carry on unwinding:
   //bool m_unwind_commit;
   // Recursion limit:
   unsigned m_recursions;

#ifdef BOOST_REGEX_MSVC
#  pragma warning(push)
#if BOOST_REGEX_MSVC >= 1800
#pragma warning(disable:26495)
#endif
#endif
   // these operations aren't allowed, so are declared private,
   // bodies are provided to keep explicit-instantiation requests happy:
   perl_matcher& operator=(const perl_matcher&)
   {
      return *this;
   }
   perl_matcher(const perl_matcher& that)
      : m_result(that.m_result), re(that.re), traits_inst(that.traits_inst), rep_obj(0) {}
#ifdef BOOST_REGEX_MSVC
#  pragma warning(pop)
#endif
};

} // namespace BOOST_REGEX_DETAIL_NS

#ifdef BOOST_REGEX_MSVC
#  pragma warning(pop)
#endif

} // namespace boost

//
// include the implementation of perl_matcher:
//
#include <boost/regex/v5/perl_matcher_non_recursive.hpp>
// this one has to be last:
#include <boost/regex/v5/perl_matcher_common.hpp>

#endif

/* perl_matcher.hpp
+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
*/