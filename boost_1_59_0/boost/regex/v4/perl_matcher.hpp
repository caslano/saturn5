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

#include <boost/regex/v4/iterator_category.hpp>

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
#pragma warning(disable : 4251)
#if BOOST_MSVC < 1700
#     pragma warning(disable : 4231)
#endif
#  if BOOST_MSVC < 1600
#     pragma warning(disable : 4660)
#  endif
#if BOOST_MSVC < 1910
#pragma warning(disable:4800)
#endif
#endif

namespace boost{
namespace BOOST_REGEX_DETAIL_NS{

//
// error checking API:
//
inline void BOOST_REGEX_CALL verify_options(boost::regex_constants::syntax_option_type, match_flag_type mf)
{
   //
   // can't mix match_extra with POSIX matching rules:
   //
   if ((mf & match_extra) && (mf & match_posix))
   {
      std::logic_error msg("Usage Error: Can't mix regular expression captures with POSIX matching rules");
      throw_exception(msg);
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
#if !defined(__hpux) && !defined(__WINSCW__)// WCHAR_MIN not usable in pp-directives.
#if defined(WCHAR_MIN) && (WCHAR_MIN == 0) && !defined(BOOST_NO_INTRINSIC_WCHAR_T)
inline bool can_start(wchar_t c, const unsigned char* map, unsigned char mask)
{
   return ((c >= static_cast<wchar_t>(1u << CHAR_BIT)) ? true : map[c] & mask);
}
#endif
#endif
#if !defined(BOOST_NO_INTRINSIC_WCHAR_T)
inline bool can_start(unsigned int c, const unsigned char* map, unsigned char mask)
{
   return (((c >= static_cast<unsigned int>(1u << CHAR_BIT)) ? true : map[c] & mask));
}
#endif


//
// Unfortunately Rogue Waves standard library appears to have a bug
// in std::basic_string::compare that results in erroneous answers
// in some cases (tested with Borland C++ 5.1, Rogue Wave lib version
// 0x020101) the test case was:
// {39135,0} < {0xff,0}
// which succeeds when it should not.
//
#ifndef _RWSTD_VER
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
#else
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
inline int string_compare(const std::string& s, const char* p)
{ return std::strcmp(s.c_str(), p); }
# ifndef BOOST_NO_WREGEX
inline int string_compare(const std::wstring& s, const wchar_t* p)
{ return std::wcscmp(s.c_str(), p); }
#endif
#endif
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
iterator BOOST_REGEX_CALL re_is_set_member(iterator next, 
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

#ifdef BOOST_MSVC
#  pragma warning(push)
#if BOOST_MSVC >= 1800
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
#ifdef BOOST_MSVC
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
   typedef typename regex_iterator_traits<BidiIterator>::difference_type difference_type;
   typedef match_results<BidiIterator, Allocator> results_type;

   perl_matcher(BidiIterator first, BidiIterator end, 
      match_results<BidiIterator, Allocator>& what, 
      const basic_regex<char_type, traits>& e,
      match_flag_type f,
      BidiIterator l_base)
      :  m_result(what), base(first), last(end), 
         position(first), backstop(l_base), re(e), traits_inst(e.get_traits()), 
         m_independent(false), next_count(&rep_obj), rep_obj(&next_count)
#ifdef BOOST_REGEX_NON_RECURSIVE
      , m_recursions(0)
#endif
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
#ifdef BOOST_REGEX_HAS_MS_STACK_GUARD
   typedef bool (perl_matcher::*protected_proc_type)();
   bool protected_call(protected_proc_type);
#endif
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
#ifdef BOOST_REGEX_RECURSIVE
   bool backtrack_till_match(std::size_t count);
#endif
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
   scoped_ptr<match_results<BidiIterator, Allocator> > m_temp_match;
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
#ifdef BOOST_REGEX_RECURSIVE
   // Set to false by a (*COMMIT):
   bool m_can_backtrack;
   bool m_have_accept;
   bool m_have_then;
#endif
#ifdef BOOST_REGEX_NON_RECURSIVE
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
#endif

#ifdef BOOST_MSVC
#  pragma warning(push)
#if BOOST_MSVC >= 1800
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
#ifdef BOOST_MSVC
#  pragma warning(pop)
#endif
};

} // namespace BOOST_REGEX_DETAIL_NS

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

} // namespace boost

//
// include the implementation of perl_matcher:
//
#ifdef BOOST_REGEX_RECURSIVE
#include <boost/regex/v4/perl_matcher_recursive.hpp>
#else
#include <boost/regex/v4/perl_matcher_non_recursive.hpp>
#endif
// this one has to be last:
#include <boost/regex/v4/perl_matcher_common.hpp>

#endif

/* perl_matcher.hpp
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
*/