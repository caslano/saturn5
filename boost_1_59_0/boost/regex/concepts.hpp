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
  *   FILE         concepts.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Declares regular expression concepts.
  */

#ifndef BOOST_REGEX_CONCEPTS_HPP_INCLUDED
#define BOOST_REGEX_CONCEPTS_HPP_INCLUDED

#include <boost/concept_archetype.hpp>
#include <boost/concept_check.hpp>
#include <boost/type_traits/is_enum.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/static_assert.hpp>
#ifndef BOOST_TEST_TR1_REGEX
#include <boost/regex.hpp>
#endif
#include <bitset>
#include <vector>
#include <ostream>

#ifdef BOOST_REGEX_CXX03
#define RW_NS boost
#else
#define RW_NS std
#endif

namespace boost{

//
// bitmask_archetype:
// this can be either an integer type, an enum, or a std::bitset,
// we use the latter as the architype as it offers the "strictest"
// of the possible interfaces:
//
typedef std::bitset<512> bitmask_archetype;
//
// char_architype:
// A strict model for the character type interface.
//
struct char_architype
{
   // default constructable:
   char_architype();
   // copy constructable / assignable:
   char_architype(const char_architype&);
   char_architype& operator=(const char_architype&);
   // constructable from an integral value:
   char_architype(unsigned long val);
   // comparable:
   bool operator==(const char_architype&)const;
   bool operator!=(const char_architype&)const;
   bool operator<(const char_architype&)const;
   bool operator<=(const char_architype&)const;
   bool operator>=(const char_architype&)const;
   bool operator>(const char_architype&)const;
   // conversion to integral type:
   operator long()const;
};
inline long hash_value(char_architype val)
{  return val;  }
//
// char_architype can not be used with basic_string:
//
} // namespace boost
namespace std{
   template<> struct char_traits<boost::char_architype>
   {
      // The intent is that this template is not instantiated,
      // but this typedef gives us a chance of compilation in
      // case it is:
      typedef boost::char_architype char_type;
   };
}
//
// Allocator architype:
//
template <class T>
class allocator_architype
{
public:
   typedef T* pointer;
   typedef const T* const_pointer;
   typedef T& reference;
   typedef const T& const_reference;
   typedef T value_type;
   typedef unsigned size_type;
   typedef int difference_type;

   template <class U>
   struct rebind
   {
      typedef allocator_architype<U> other;
   };

   pointer address(reference r){ return &r; }
   const_pointer address(const_reference r) { return &r; }
   pointer allocate(size_type n) { return static_cast<pointer>(std::malloc(n)); }
   pointer allocate(size_type n, pointer) { return static_cast<pointer>(std::malloc(n)); }
   void deallocate(pointer p, size_type) { std::free(p); }
   size_type max_size()const { return UINT_MAX; }

   allocator_architype(){}
   allocator_architype(const allocator_architype&){}

   template <class Other>
   allocator_architype(const allocator_architype<Other>&){}

   void construct(pointer p, const_reference r) { new (p)T(r); }
   void destroy(pointer p) { p->~T(); }
};

template <class T>
bool operator == (const allocator_architype<T>&, const allocator_architype<T>&) {return true; }
template <class T>
bool operator != (const allocator_architype<T>&, const allocator_architype<T>&) { return false; }

namespace boost{
//
// regex_traits_architype:
// A strict interpretation of the regular expression traits class requirements.
//
template <class charT>
struct regex_traits_architype
{
public:
   regex_traits_architype(){}
   typedef charT char_type;
   // typedef std::size_t size_type;
   typedef std::vector<char_type> string_type;
   typedef copy_constructible_archetype<assignable_archetype<> > locale_type;
   typedef bitmask_archetype char_class_type;

   static std::size_t length(const char_type* ) { return 0; }

   charT translate(charT ) const { return charT(); }
   charT translate_nocase(charT ) const { return static_object<charT>::get(); }

   template <class ForwardIterator>
   string_type transform(ForwardIterator , ForwardIterator ) const
   { return static_object<string_type>::get(); }
   template <class ForwardIterator>
   string_type transform_primary(ForwardIterator , ForwardIterator ) const
   { return static_object<string_type>::get(); }

   template <class ForwardIterator>
   char_class_type lookup_classname(ForwardIterator , ForwardIterator ) const
   { return static_object<char_class_type>::get(); }
   template <class ForwardIterator>
   string_type lookup_collatename(ForwardIterator , ForwardIterator ) const
   { return static_object<string_type>::get(); }

   bool isctype(charT, char_class_type) const
   { return false; }
   int value(charT, int) const
   { return 0; }

   locale_type imbue(locale_type l)
   { return l; }
   locale_type getloc()const
   { return static_object<locale_type>::get(); }

private:
   // this type is not copyable:
   regex_traits_architype(const regex_traits_architype&){}
   regex_traits_architype& operator=(const regex_traits_architype&){ return *this; }
};

//
// alter this to std::tr1, to test a std implementation:
//
#ifndef BOOST_TEST_TR1_REGEX
namespace global_regex_namespace = ::boost;
#else
namespace global_regex_namespace = ::std::tr1;
#endif

template <class Bitmask>
struct BitmaskConcept
{
   void constraints() 
   {
      function_requires<CopyConstructibleConcept<Bitmask> >();
      function_requires<AssignableConcept<Bitmask> >();

      m_mask1 = m_mask2 | m_mask3;
      m_mask1 = m_mask2 & m_mask3;
      m_mask1 = m_mask2 ^ m_mask3;

      m_mask1 = ~m_mask2;

      m_mask1 |= m_mask2;
      m_mask1 &= m_mask2;
      m_mask1 ^= m_mask2;
   }
   Bitmask m_mask1, m_mask2, m_mask3;
};

template <class traits>
struct RegexTraitsConcept
{
   RegexTraitsConcept();
   // required typedefs:
   typedef typename traits::char_type char_type;
   // typedef typename traits::size_type size_type;
   typedef typename traits::string_type string_type;
   typedef typename traits::locale_type locale_type;
   typedef typename traits::char_class_type char_class_type;

   void constraints() 
   {
      //function_requires<UnsignedIntegerConcept<size_type> >();
      function_requires<RandomAccessContainerConcept<string_type> >();
      function_requires<DefaultConstructibleConcept<locale_type> >();
      function_requires<CopyConstructibleConcept<locale_type> >();
      function_requires<AssignableConcept<locale_type> >();
      function_requires<BitmaskConcept<char_class_type> >();

      std::size_t n = traits::length(m_pointer);
      ignore_unused_variable_warning(n);

      char_type c = m_ctraits.translate(m_char);
      ignore_unused_variable_warning(c);
      c = m_ctraits.translate_nocase(m_char);
      
      //string_type::foobar bar;
      string_type s1 = m_ctraits.transform(m_pointer, m_pointer);
      ignore_unused_variable_warning(s1);

      string_type s2 = m_ctraits.transform_primary(m_pointer, m_pointer);
      ignore_unused_variable_warning(s2);

      char_class_type cc = m_ctraits.lookup_classname(m_pointer, m_pointer);
      ignore_unused_variable_warning(cc);

      string_type s3 = m_ctraits.lookup_collatename(m_pointer, m_pointer);
      ignore_unused_variable_warning(s3);

      bool b = m_ctraits.isctype(m_char, cc);
      ignore_unused_variable_warning(b);

      int v = m_ctraits.value(m_char, 16);
      ignore_unused_variable_warning(v);

      locale_type l(m_ctraits.getloc());
      m_traits.imbue(l);
      ignore_unused_variable_warning(l);
   }
   traits m_traits;
   const traits m_ctraits;
   const char_type* m_pointer;
   char_type m_char;
private:
   RegexTraitsConcept& operator=(RegexTraitsConcept&);
};

//
// helper class to compute what traits class a regular expression type is using:
//
template <class Regex>
struct regex_traits_computer;

template <class charT, class traits>
struct regex_traits_computer< global_regex_namespace::basic_regex<charT, traits> >
{
   typedef traits type;
};

//
// BaseRegexConcept does not test anything dependent on basic_string,
// in case our charT does not have an associated char_traits:
//
template <class Regex>
struct BaseRegexConcept
{
   typedef typename Regex::value_type value_type;
   //typedef typename Regex::size_type size_type;
   typedef typename Regex::flag_type flag_type;
   typedef typename Regex::locale_type locale_type;
   typedef input_iterator_archetype<value_type> input_iterator_type;

   // derived test types:
   typedef const value_type* pointer_type;
   typedef bidirectional_iterator_archetype<value_type> BidiIterator;
   typedef global_regex_namespace::sub_match<BidiIterator> sub_match_type;
   typedef global_regex_namespace::match_results<BidiIterator, allocator_architype<sub_match_type> > match_results_type;
   typedef global_regex_namespace::match_results<BidiIterator> match_results_default_type;
   typedef output_iterator_archetype<value_type> OutIterator;
   typedef typename regex_traits_computer<Regex>::type traits_type;
   typedef global_regex_namespace::regex_iterator<BidiIterator, value_type, traits_type> regex_iterator_type;
   typedef global_regex_namespace::regex_token_iterator<BidiIterator, value_type, traits_type> regex_token_iterator_type;

   void global_constraints()
   {
      //
      // test non-template components:
      //
      function_requires<BitmaskConcept<global_regex_namespace::regex_constants::syntax_option_type> >();
      global_regex_namespace::regex_constants::syntax_option_type opts
         = global_regex_namespace::regex_constants::icase
         | global_regex_namespace::regex_constants::nosubs
         | global_regex_namespace::regex_constants::optimize
         | global_regex_namespace::regex_constants::collate
         | global_regex_namespace::regex_constants::ECMAScript
         | global_regex_namespace::regex_constants::basic
         | global_regex_namespace::regex_constants::extended
         | global_regex_namespace::regex_constants::awk
         | global_regex_namespace::regex_constants::grep
         | global_regex_namespace::regex_constants::egrep;
      ignore_unused_variable_warning(opts);

      function_requires<BitmaskConcept<global_regex_namespace::regex_constants::match_flag_type> >();
      global_regex_namespace::regex_constants::match_flag_type mopts
         = global_regex_namespace::regex_constants::match_default
         | global_regex_namespace::regex_constants::match_not_bol
         | global_regex_namespace::regex_constants::match_not_eol
         | global_regex_namespace::regex_constants::match_not_bow
         | global_regex_namespace::regex_constants::match_not_eow
         | global_regex_namespace::regex_constants::match_any
         | global_regex_namespace::regex_constants::match_not_null
         | global_regex_namespace::regex_constants::match_continuous
         | global_regex_namespace::regex_constants::match_prev_avail
         | global_regex_namespace::regex_constants::format_default
         | global_regex_namespace::regex_constants::format_sed
         | global_regex_namespace::regex_constants::format_no_copy
         | global_regex_namespace::regex_constants::format_first_only;
      ignore_unused_variable_warning(mopts);

      BOOST_STATIC_ASSERT((::boost::is_enum<global_regex_namespace::regex_constants::error_type>::value));
      global_regex_namespace::regex_constants::error_type e1 = global_regex_namespace::regex_constants::error_collate;
      ignore_unused_variable_warning(e1);
      e1 = global_regex_namespace::regex_constants::error_ctype;
      ignore_unused_variable_warning(e1);
      e1 = global_regex_namespace::regex_constants::error_escape;
      ignore_unused_variable_warning(e1);
      e1 = global_regex_namespace::regex_constants::error_backref;
      ignore_unused_variable_warning(e1);
      e1 = global_regex_namespace::regex_constants::error_brack;
      ignore_unused_variable_warning(e1);
      e1 = global_regex_namespace::regex_constants::error_paren;
      ignore_unused_variable_warning(e1);
      e1 = global_regex_namespace::regex_constants::error_brace;
      ignore_unused_variable_warning(e1);
      e1 = global_regex_namespace::regex_constants::error_badbrace;
      ignore_unused_variable_warning(e1);
      e1 = global_regex_namespace::regex_constants::error_range;
      ignore_unused_variable_warning(e1);
      e1 = global_regex_namespace::regex_constants::error_space;
      ignore_unused_variable_warning(e1);
      e1 = global_regex_namespace::regex_constants::error_badrepeat;
      ignore_unused_variable_warning(e1);
      e1 = global_regex_namespace::regex_constants::error_complexity;
      ignore_unused_variable_warning(e1);
      e1 = global_regex_namespace::regex_constants::error_stack;
      ignore_unused_variable_warning(e1);

      BOOST_STATIC_ASSERT((::boost::is_base_and_derived<std::runtime_error, global_regex_namespace::regex_error>::value  ));
      const global_regex_namespace::regex_error except(e1);
      e1 = except.code();

      typedef typename Regex::value_type regex_value_type;
      function_requires< RegexTraitsConcept<global_regex_namespace::regex_traits<char> > >();
      function_requires< BaseRegexConcept<global_regex_namespace::basic_regex<char> > >();
   }
   void constraints() 
   {
      global_constraints();

      BOOST_STATIC_ASSERT((::boost::is_same< flag_type, global_regex_namespace::regex_constants::syntax_option_type>::value));
      flag_type opts
         = Regex::icase
         | Regex::nosubs
         | Regex::optimize
         | Regex::collate
         | Regex::ECMAScript
         | Regex::basic
         | Regex::extended
         | Regex::awk
         | Regex::grep
         | Regex::egrep;
      ignore_unused_variable_warning(opts);

      function_requires<DefaultConstructibleConcept<Regex> >();
      function_requires<CopyConstructibleConcept<Regex> >();

      // Regex constructors:
      Regex e1(m_pointer);
      ignore_unused_variable_warning(e1);
      Regex e2(m_pointer, m_flags);
      ignore_unused_variable_warning(e2);
      Regex e3(m_pointer, m_size, m_flags);
      ignore_unused_variable_warning(e3);
      Regex e4(in1, in2);
      ignore_unused_variable_warning(e4);
      Regex e5(in1, in2, m_flags);
      ignore_unused_variable_warning(e5);

      // assign etc:
      Regex e;
      e = m_pointer;
      e = e1;
      e.assign(e1);
      e.assign(m_pointer);
      e.assign(m_pointer, m_flags);
      e.assign(m_pointer, m_size, m_flags);
      e.assign(in1, in2);
      e.assign(in1, in2, m_flags);

      // access:
      const Regex ce;
      typename Regex::size_type i = ce.mark_count();
      ignore_unused_variable_warning(i);
      m_flags = ce.flags();
      e.imbue(ce.getloc());
      e.swap(e1);
      
      global_regex_namespace::swap(e, e1);

      // sub_match:
      BOOST_STATIC_ASSERT((::boost::is_base_and_derived<std::pair<BidiIterator, BidiIterator>, sub_match_type>::value));
      typedef typename sub_match_type::value_type sub_value_type;
      typedef typename sub_match_type::difference_type sub_diff_type;
      typedef typename sub_match_type::iterator sub_iter_type;
      BOOST_STATIC_ASSERT((::boost::is_same<sub_value_type, value_type>::value));
      BOOST_STATIC_ASSERT((::boost::is_same<sub_iter_type, BidiIterator>::value));
      bool b = m_sub.matched;
      ignore_unused_variable_warning(b);
      BidiIterator bi = m_sub.first;
      ignore_unused_variable_warning(bi);
      bi = m_sub.second;
      ignore_unused_variable_warning(bi);
      sub_diff_type diff = m_sub.length();
      ignore_unused_variable_warning(diff);
      // match_results tests - some typedefs are not used, however these
      // guarante that they exist (some compilers may warn on non-usage)
      typedef typename match_results_type::value_type mr_value_type;
      typedef typename match_results_type::const_reference mr_const_reference;
      typedef typename match_results_type::reference mr_reference;
      typedef typename match_results_type::const_iterator mr_const_iterator;
      typedef typename match_results_type::iterator mr_iterator;
      typedef typename match_results_type::difference_type mr_difference_type;
      typedef typename match_results_type::size_type mr_size_type;
      typedef typename match_results_type::allocator_type mr_allocator_type;
      typedef typename match_results_type::char_type mr_char_type;
      typedef typename match_results_type::string_type mr_string_type;

      match_results_type m1;
      mr_allocator_type at;
      match_results_type m2(at);
      match_results_type m3(m1);
      m1 = m2;

      int ival = 0;

      mr_size_type mrs = m_cresults.size();
      ignore_unused_variable_warning(mrs);
      mrs = m_cresults.max_size();
      ignore_unused_variable_warning(mrs);
      b = m_cresults.empty();
      ignore_unused_variable_warning(b);
      mr_difference_type mrd = m_cresults.length();
      ignore_unused_variable_warning(mrd);
      mrd = m_cresults.length(ival);
      ignore_unused_variable_warning(mrd);
      mrd = m_cresults.position();
      ignore_unused_variable_warning(mrd);
      mrd = m_cresults.position(mrs);
      ignore_unused_variable_warning(mrd);

      mr_const_reference mrcr = m_cresults[ival];
      ignore_unused_variable_warning(mrcr);
      mr_const_reference mrcr2 = m_cresults.prefix();
      ignore_unused_variable_warning(mrcr2);
      mr_const_reference mrcr3 = m_cresults.suffix();
      ignore_unused_variable_warning(mrcr3);
      mr_const_iterator mrci = m_cresults.begin();
      ignore_unused_variable_warning(mrci);
      mrci = m_cresults.end();
      ignore_unused_variable_warning(mrci);

      (void) m_cresults.get_allocator();
      m_results.swap(m_results);
      global_regex_namespace::swap(m_results, m_results);

      // regex_match:
      b = global_regex_namespace::regex_match(m_in, m_in, m_results, e);
      ignore_unused_variable_warning(b);
      b = global_regex_namespace::regex_match(m_in, m_in, m_results, e, m_mft);
      ignore_unused_variable_warning(b);
      b = global_regex_namespace::regex_match(m_in, m_in, e);
      ignore_unused_variable_warning(b);
      b = global_regex_namespace::regex_match(m_in, m_in, e, m_mft);
      ignore_unused_variable_warning(b);
      b = global_regex_namespace::regex_match(m_pointer, m_pmatch, e);
      ignore_unused_variable_warning(b);
      b = global_regex_namespace::regex_match(m_pointer, m_pmatch, e, m_mft);
      ignore_unused_variable_warning(b);
      b = global_regex_namespace::regex_match(m_pointer, e);
      ignore_unused_variable_warning(b);
      b = global_regex_namespace::regex_match(m_pointer, e, m_mft);
      ignore_unused_variable_warning(b);
      // regex_search:
      b = global_regex_namespace::regex_search(m_in, m_in, m_results, e);
      ignore_unused_variable_warning(b);
      b = global_regex_namespace::regex_search(m_in, m_in, m_results, e, m_mft);
      ignore_unused_variable_warning(b);
      b = global_regex_namespace::regex_search(m_in, m_in, e);
      ignore_unused_variable_warning(b);
      b = global_regex_namespace::regex_search(m_in, m_in, e, m_mft);
      ignore_unused_variable_warning(b);
      b = global_regex_namespace::regex_search(m_pointer, m_pmatch, e);
      ignore_unused_variable_warning(b);
      b = global_regex_namespace::regex_search(m_pointer, m_pmatch, e, m_mft);
      ignore_unused_variable_warning(b);
      b = global_regex_namespace::regex_search(m_pointer, e);
      ignore_unused_variable_warning(b);
      b = global_regex_namespace::regex_search(m_pointer, e, m_mft);
      ignore_unused_variable_warning(b);

      // regex_iterator:
      typedef typename regex_iterator_type::regex_type rit_regex_type;
      typedef typename regex_iterator_type::value_type rit_value_type;
      typedef typename regex_iterator_type::difference_type rit_difference_type;
      typedef typename regex_iterator_type::pointer rit_pointer;
      typedef typename regex_iterator_type::reference rit_reference;
      typedef typename regex_iterator_type::iterator_category rit_iterator_category;
      BOOST_STATIC_ASSERT((::boost::is_same<rit_regex_type, Regex>::value));
      BOOST_STATIC_ASSERT((::boost::is_same<rit_value_type, match_results_default_type>::value));
      BOOST_STATIC_ASSERT((::boost::is_same<rit_difference_type, std::ptrdiff_t>::value));
      BOOST_STATIC_ASSERT((::boost::is_same<rit_pointer, const match_results_default_type*>::value));
      BOOST_STATIC_ASSERT((::boost::is_same<rit_reference, const match_results_default_type&>::value));
      BOOST_STATIC_ASSERT((::boost::is_convertible<rit_iterator_category*, std::forward_iterator_tag*>::value));
      // this takes care of most of the checks needed:
      function_requires<ForwardIteratorConcept<regex_iterator_type> >();
      regex_iterator_type iter1(m_in, m_in, e);
      ignore_unused_variable_warning(iter1);
      regex_iterator_type iter2(m_in, m_in, e, m_mft);
      ignore_unused_variable_warning(iter2);

      // regex_token_iterator:
      typedef typename regex_token_iterator_type::regex_type rtit_regex_type;
      typedef typename regex_token_iterator_type::value_type rtit_value_type;
      typedef typename regex_token_iterator_type::difference_type rtit_difference_type;
      typedef typename regex_token_iterator_type::pointer rtit_pointer;
      typedef typename regex_token_iterator_type::reference rtit_reference;
      typedef typename regex_token_iterator_type::iterator_category rtit_iterator_category;
      BOOST_STATIC_ASSERT((::boost::is_same<rtit_regex_type, Regex>::value));
      BOOST_STATIC_ASSERT((::boost::is_same<rtit_value_type, sub_match_type>::value));
      BOOST_STATIC_ASSERT((::boost::is_same<rtit_difference_type, std::ptrdiff_t>::value));
      BOOST_STATIC_ASSERT((::boost::is_same<rtit_pointer, const sub_match_type*>::value));
      BOOST_STATIC_ASSERT((::boost::is_same<rtit_reference, const sub_match_type&>::value));
      BOOST_STATIC_ASSERT((::boost::is_convertible<rtit_iterator_category*, std::forward_iterator_tag*>::value));
      // this takes care of most of the checks needed:
      function_requires<ForwardIteratorConcept<regex_token_iterator_type> >();
      regex_token_iterator_type ti1(m_in, m_in, e);
      ignore_unused_variable_warning(ti1);
      regex_token_iterator_type ti2(m_in, m_in, e, 0);
      ignore_unused_variable_warning(ti2);
      regex_token_iterator_type ti3(m_in, m_in, e, 0, m_mft);
      ignore_unused_variable_warning(ti3);
      std::vector<int> subs;
      regex_token_iterator_type ti4(m_in, m_in, e, subs);
      ignore_unused_variable_warning(ti4);
      regex_token_iterator_type ti5(m_in, m_in, e, subs, m_mft);
      ignore_unused_variable_warning(ti5);
      static const int i_array[3] = { 1, 2, 3, };
      regex_token_iterator_type ti6(m_in, m_in, e, i_array);
      ignore_unused_variable_warning(ti6);
      regex_token_iterator_type ti7(m_in, m_in, e, i_array, m_mft);
      ignore_unused_variable_warning(ti7);
   }

   pointer_type m_pointer;
   flag_type m_flags;
   std::size_t m_size;
   input_iterator_type in1, in2;
   const sub_match_type m_sub;
   const value_type m_char;
   match_results_type m_results;
   const match_results_type m_cresults;
   OutIterator m_out;
   BidiIterator m_in;
   global_regex_namespace::regex_constants::match_flag_type m_mft;
   global_regex_namespace::match_results<
      pointer_type, 
      allocator_architype<global_regex_namespace::sub_match<pointer_type> > > 
      m_pmatch;

   BaseRegexConcept();
   BaseRegexConcept(const BaseRegexConcept&);
   BaseRegexConcept& operator=(const BaseRegexConcept&);
};

//
// RegexConcept:
// Test every interface in the std:
//
template <class Regex>
struct RegexConcept
{
   typedef typename Regex::value_type value_type;
   //typedef typename Regex::size_type size_type;
   typedef typename Regex::flag_type flag_type;
   typedef typename Regex::locale_type locale_type;

   // derived test types:
   typedef const value_type* pointer_type;
   typedef std::basic_string<value_type> string_type;
   typedef boost::bidirectional_iterator_archetype<value_type> BidiIterator;
   typedef global_regex_namespace::sub_match<BidiIterator> sub_match_type;
   typedef global_regex_namespace::match_results<BidiIterator, allocator_architype<sub_match_type> > match_results_type;
   typedef output_iterator_archetype<value_type> OutIterator;


   void constraints() 
   {
      function_requires<BaseRegexConcept<Regex> >();
      // string based construct:
      Regex e1(m_string);
      ignore_unused_variable_warning(e1);
      Regex e2(m_string, m_flags);
      ignore_unused_variable_warning(e2);

      // assign etc:
      Regex e;
      e = m_string;
      e.assign(m_string);
      e.assign(m_string, m_flags);

      // sub_match:
      string_type s(m_sub);
      ignore_unused_variable_warning(s);
      s = m_sub.str();
      ignore_unused_variable_warning(s);
      int i = m_sub.compare(m_string);
      ignore_unused_variable_warning(i);

      int i2 = m_sub.compare(m_sub);
      ignore_unused_variable_warning(i2);
      i2 = m_sub.compare(m_pointer);
      ignore_unused_variable_warning(i2);

      bool b = m_sub == m_sub;
      ignore_unused_variable_warning(b);
      b = m_sub != m_sub;
      ignore_unused_variable_warning(b);
      b = m_sub <= m_sub;
      ignore_unused_variable_warning(b);
      b = m_sub <= m_sub;
      ignore_unused_variable_warning(b);
      b = m_sub > m_sub;
      ignore_unused_variable_warning(b);
      b = m_sub >= m_sub;
      ignore_unused_variable_warning(b);

      b = m_sub == m_pointer;
      ignore_unused_variable_warning(b);
      b = m_sub != m_pointer;
      ignore_unused_variable_warning(b);
      b = m_sub <= m_pointer;
      ignore_unused_variable_warning(b);
      b = m_sub <= m_pointer;
      ignore_unused_variable_warning(b);
      b = m_sub > m_pointer;
      ignore_unused_variable_warning(b);
      b = m_sub >= m_pointer;
      ignore_unused_variable_warning(b);

      b = m_pointer == m_sub;
      ignore_unused_variable_warning(b);
      b = m_pointer != m_sub;
      ignore_unused_variable_warning(b);
      b = m_pointer <= m_sub;
      ignore_unused_variable_warning(b);
      b = m_pointer <= m_sub;
      ignore_unused_variable_warning(b);
      b = m_pointer > m_sub;
      ignore_unused_variable_warning(b);
      b = m_pointer >= m_sub;
      ignore_unused_variable_warning(b);

      b = m_sub == m_char;
      ignore_unused_variable_warning(b);
      b = m_sub != m_char;
      ignore_unused_variable_warning(b);
      b = m_sub <= m_char;
      ignore_unused_variable_warning(b);
      b = m_sub <= m_char;
      ignore_unused_variable_warning(b);
      b = m_sub > m_char;
      ignore_unused_variable_warning(b);
      b = m_sub >= m_char;
      ignore_unused_variable_warning(b);

      b = m_char == m_sub;
      ignore_unused_variable_warning(b);
      b = m_char != m_sub;
      ignore_unused_variable_warning(b);
      b = m_char <= m_sub;
      ignore_unused_variable_warning(b);
      b = m_char <= m_sub;
      ignore_unused_variable_warning(b);
      b = m_char > m_sub;
      ignore_unused_variable_warning(b);
      b = m_char >= m_sub;
      ignore_unused_variable_warning(b);

      b = m_sub == m_string;
      ignore_unused_variable_warning(b);
      b = m_sub != m_string;
      ignore_unused_variable_warning(b);
      b = m_sub <= m_string;
      ignore_unused_variable_warning(b);
      b = m_sub <= m_string;
      ignore_unused_variable_warning(b);
      b = m_sub > m_string;
      ignore_unused_variable_warning(b);
      b = m_sub >= m_string;
      ignore_unused_variable_warning(b);

      b = m_string == m_sub;
      ignore_unused_variable_warning(b);
      b = m_string != m_sub;
      ignore_unused_variable_warning(b);
      b = m_string <= m_sub;
      ignore_unused_variable_warning(b);
      b = m_string <= m_sub;
      ignore_unused_variable_warning(b);
      b = m_string > m_sub;
      ignore_unused_variable_warning(b);
      b = m_string >= m_sub;
      ignore_unused_variable_warning(b);

      // match results:
      m_string = m_results.str();
      ignore_unused_variable_warning(m_string);
      m_string = m_results.str(0);
      ignore_unused_variable_warning(m_string);
      m_out = m_cresults.format(m_out, m_string);
      m_out = m_cresults.format(m_out, m_string, m_mft);
      m_string = m_cresults.format(m_string);
      ignore_unused_variable_warning(m_string);
      m_string = m_cresults.format(m_string, m_mft);
      ignore_unused_variable_warning(m_string);

      // regex_match:
      b = global_regex_namespace::regex_match(m_string, m_smatch, e);
      ignore_unused_variable_warning(b);
      b = global_regex_namespace::regex_match(m_string, m_smatch, e, m_mft);
      ignore_unused_variable_warning(b);
      b = global_regex_namespace::regex_match(m_string, e);
      ignore_unused_variable_warning(b);
      b = global_regex_namespace::regex_match(m_string, e, m_mft);
      ignore_unused_variable_warning(b);

      // regex_search:
      b = global_regex_namespace::regex_search(m_string, m_smatch, e);
      ignore_unused_variable_warning(b);
      b = global_regex_namespace::regex_search(m_string, m_smatch, e, m_mft);
      ignore_unused_variable_warning(b);
      b = global_regex_namespace::regex_search(m_string, e);
      ignore_unused_variable_warning(b);
      b = global_regex_namespace::regex_search(m_string, e, m_mft);
      ignore_unused_variable_warning(b);

      // regex_replace:
      m_out = global_regex_namespace::regex_replace(m_out, m_in, m_in, e, m_string, m_mft);
      m_out = global_regex_namespace::regex_replace(m_out, m_in, m_in, e, m_string);
      m_string = global_regex_namespace::regex_replace(m_string, e, m_string, m_mft);
      ignore_unused_variable_warning(m_string);
      m_string = global_regex_namespace::regex_replace(m_string, e, m_string);
      ignore_unused_variable_warning(m_string);

   }

   flag_type m_flags;
   string_type m_string;
   const sub_match_type m_sub;
   match_results_type m_results;
   pointer_type m_pointer;
   value_type m_char;
   const match_results_type m_cresults;
   OutIterator m_out;
   BidiIterator m_in;
   global_regex_namespace::regex_constants::match_flag_type m_mft;
   global_regex_namespace::match_results<typename string_type::const_iterator, allocator_architype<global_regex_namespace::sub_match<typename string_type::const_iterator> > > m_smatch;

   RegexConcept();
   RegexConcept(const RegexConcept&);
   RegexConcept& operator=(const RegexConcept&);
};

#ifndef BOOST_REGEX_TEST_STD

template <class M>
struct functor1
{
   typedef typename M::char_type char_type;
   const char_type* operator()(const M&)const
   {
      static const char_type c = static_cast<char_type>(0);
      return &c;
   }
};
template <class M>
struct functor1b
{
   typedef typename M::char_type char_type;
   std::vector<char_type> operator()(const M&)const
   {
      static const std::vector<char_type> c;
      return c;
   }
};
template <class M>
struct functor2
{
   template <class O>
   O operator()(const M& /*m*/, O i)const
   {
      return i;
   }
};
template <class M>
struct functor3
{
   template <class O>
   O operator()(const M& /*m*/, O i, regex_constants::match_flag_type)const
   {
      return i;
   }
};

//
// BoostRegexConcept:
// Test every interface in the Boost implementation:
//
template <class Regex>
struct BoostRegexConcept
{
   typedef typename Regex::value_type value_type;
   typedef typename Regex::size_type size_type;
   typedef typename Regex::flag_type flag_type;
   typedef typename Regex::locale_type locale_type;

   // derived test types:
   typedef const value_type* pointer_type;
   typedef std::basic_string<value_type> string_type;
   typedef typename Regex::const_iterator const_iterator;
   typedef bidirectional_iterator_archetype<value_type> BidiIterator;
   typedef output_iterator_archetype<value_type> OutputIterator;
   typedef global_regex_namespace::sub_match<BidiIterator> sub_match_type;
   typedef global_regex_namespace::match_results<BidiIterator, allocator_architype<sub_match_type> > match_results_type;
   typedef global_regex_namespace::match_results<BidiIterator> match_results_default_type;

   void constraints() 
   {
      global_regex_namespace::regex_constants::match_flag_type mopts
         = global_regex_namespace::regex_constants::match_default
         | global_regex_namespace::regex_constants::match_not_bol
         | global_regex_namespace::regex_constants::match_not_eol
         | global_regex_namespace::regex_constants::match_not_bow
         | global_regex_namespace::regex_constants::match_not_eow
         | global_regex_namespace::regex_constants::match_any
         | global_regex_namespace::regex_constants::match_not_null
         | global_regex_namespace::regex_constants::match_continuous
         | global_regex_namespace::regex_constants::match_partial
         | global_regex_namespace::regex_constants::match_prev_avail
         | global_regex_namespace::regex_constants::format_default
         | global_regex_namespace::regex_constants::format_sed
         | global_regex_namespace::regex_constants::format_perl
         | global_regex_namespace::regex_constants::format_no_copy
         | global_regex_namespace::regex_constants::format_first_only;

      (void)mopts;

      function_requires<RegexConcept<Regex> >();
      const global_regex_namespace::regex_error except(global_regex_namespace::regex_constants::error_collate);
      std::ptrdiff_t pt = except.position();
      ignore_unused_variable_warning(pt);
      const Regex ce, ce2;
#ifndef BOOST_NO_STD_LOCALE
      m_stream << ce;
#endif
      unsigned i = ce.error_code();
      ignore_unused_variable_warning(i);
      pointer_type p = ce.expression();
      ignore_unused_variable_warning(p);
      int i2 = ce.compare(ce2);
      ignore_unused_variable_warning(i2);
      bool b = ce == ce2;
      ignore_unused_variable_warning(b);
      b = ce.empty();
      ignore_unused_variable_warning(b);
      b = ce != ce2;
      ignore_unused_variable_warning(b);
      b = ce < ce2;
      ignore_unused_variable_warning(b);
      b = ce > ce2;
      ignore_unused_variable_warning(b);
      b = ce <= ce2;
      ignore_unused_variable_warning(b);
      b = ce >= ce2;
      ignore_unused_variable_warning(b);
      i = ce.status();
      ignore_unused_variable_warning(i);
      size_type s = ce.max_size();
      ignore_unused_variable_warning(s);
      s = ce.size();
      ignore_unused_variable_warning(s);
      const_iterator pi = ce.begin();
      ignore_unused_variable_warning(pi);
      pi = ce.end();
      ignore_unused_variable_warning(pi);
      string_type s2 = ce.str();
      ignore_unused_variable_warning(s2);

      m_string = m_sub + m_sub;
      ignore_unused_variable_warning(m_string);
      m_string = m_sub + m_pointer;
      ignore_unused_variable_warning(m_string);
      m_string = m_pointer + m_sub;
      ignore_unused_variable_warning(m_string);
      m_string = m_sub + m_string;
      ignore_unused_variable_warning(m_string);
      m_string = m_string + m_sub;
      ignore_unused_variable_warning(m_string);
      m_string = m_sub + m_char;
      ignore_unused_variable_warning(m_string);
      m_string = m_char + m_sub;
      ignore_unused_variable_warning(m_string);

      // Named sub-expressions:
      m_sub = m_cresults[&m_char];
      ignore_unused_variable_warning(m_sub);
      m_sub = m_cresults[m_string];
      ignore_unused_variable_warning(m_sub);
      m_sub = m_cresults[""];
      ignore_unused_variable_warning(m_sub);
      m_sub = m_cresults[std::string("")];
      ignore_unused_variable_warning(m_sub);
      m_string = m_cresults.str(&m_char);
      ignore_unused_variable_warning(m_string);
      m_string = m_cresults.str(m_string);
      ignore_unused_variable_warning(m_string);
      m_string = m_cresults.str("");
      ignore_unused_variable_warning(m_string);
      m_string = m_cresults.str(std::string(""));
      ignore_unused_variable_warning(m_string);

      typename match_results_type::difference_type diff;
      diff = m_cresults.length(&m_char);
      ignore_unused_variable_warning(diff);
      diff = m_cresults.length(m_string);
      ignore_unused_variable_warning(diff);
      diff = m_cresults.length("");
      ignore_unused_variable_warning(diff);
      diff = m_cresults.length(std::string(""));
      ignore_unused_variable_warning(diff);
      diff = m_cresults.position(&m_char);
      ignore_unused_variable_warning(diff);
      diff = m_cresults.position(m_string);
      ignore_unused_variable_warning(diff);
      diff = m_cresults.position("");
      ignore_unused_variable_warning(diff);
      diff = m_cresults.position(std::string(""));
      ignore_unused_variable_warning(diff);

#ifndef BOOST_NO_STD_LOCALE
      m_stream << m_sub;
      m_stream << m_cresults;
#endif
      //
      // Extended formatting with a functor:
      //
      regex_constants::match_flag_type f = regex_constants::match_default;
      OutputIterator out = static_object<OutputIterator>::get();
      
      functor3<match_results_default_type> func3;
      functor2<match_results_default_type> func2;
      functor1<match_results_default_type> func1;
      
      functor3<match_results_type> func3b;
      functor2<match_results_type> func2b;
      functor1<match_results_type> func1b;

      out = regex_format(out, m_cresults, func3b, f);
      out = regex_format(out, m_cresults, func3b);
      out = regex_format(out, m_cresults, func2b, f);
      out = regex_format(out, m_cresults, func2b);
      out = regex_format(out, m_cresults, func1b, f);
      out = regex_format(out, m_cresults, func1b);
      out = regex_format(out, m_cresults, RW_NS::ref(func3b), f);
      out = regex_format(out, m_cresults, RW_NS::ref(func3b));
      out = regex_format(out, m_cresults, RW_NS::ref(func2b), f);
      out = regex_format(out, m_cresults, RW_NS::ref(func2b));
      out = regex_format(out, m_cresults, RW_NS::ref(func1b), f);
      out = regex_format(out, m_cresults, RW_NS::ref(func1b));
      out = regex_format(out, m_cresults, RW_NS::cref(func3b), f);
      out = regex_format(out, m_cresults, RW_NS::cref(func3b));
      out = regex_format(out, m_cresults, RW_NS::cref(func2b), f);
      out = regex_format(out, m_cresults, RW_NS::cref(func2b));
      out = regex_format(out, m_cresults, RW_NS::cref(func1b), f);
      out = regex_format(out, m_cresults, RW_NS::cref(func1b));
      m_string += regex_format(m_cresults, func3b, f);
      m_string += regex_format(m_cresults, func3b);
      m_string += regex_format(m_cresults, func2b, f);
      m_string += regex_format(m_cresults, func2b);
      m_string += regex_format(m_cresults, func1b, f);
      m_string += regex_format(m_cresults, func1b);
      m_string += regex_format(m_cresults, RW_NS::ref(func3b), f);
      m_string += regex_format(m_cresults, RW_NS::ref(func3b));
      m_string += regex_format(m_cresults, RW_NS::ref(func2b), f);
      m_string += regex_format(m_cresults, RW_NS::ref(func2b));
      m_string += regex_format(m_cresults, RW_NS::ref(func1b), f);
      m_string += regex_format(m_cresults, RW_NS::ref(func1b));
      m_string += regex_format(m_cresults, RW_NS::cref(func3b), f);
      m_string += regex_format(m_cresults, RW_NS::cref(func3b));
      m_string += regex_format(m_cresults, RW_NS::cref(func2b), f);
      m_string += regex_format(m_cresults, RW_NS::cref(func2b));
      m_string += regex_format(m_cresults, RW_NS::cref(func1b), f);
      m_string += regex_format(m_cresults, RW_NS::cref(func1b));

      out = m_cresults.format(out, func3b, f);
      out = m_cresults.format(out, func3b);
      out = m_cresults.format(out, func2b, f);
      out = m_cresults.format(out, func2b);
      out = m_cresults.format(out, func1b, f);
      out = m_cresults.format(out, func1b);
      out = m_cresults.format(out, RW_NS::ref(func3b), f);
      out = m_cresults.format(out, RW_NS::ref(func3b));
      out = m_cresults.format(out, RW_NS::ref(func2b), f);
      out = m_cresults.format(out, RW_NS::ref(func2b));
      out = m_cresults.format(out, RW_NS::ref(func1b), f);
      out = m_cresults.format(out, RW_NS::ref(func1b));
      out = m_cresults.format(out, RW_NS::cref(func3b), f);
      out = m_cresults.format(out, RW_NS::cref(func3b));
      out = m_cresults.format(out, RW_NS::cref(func2b), f);
      out = m_cresults.format(out, RW_NS::cref(func2b));
      out = m_cresults.format(out, RW_NS::cref(func1b), f);
      out = m_cresults.format(out, RW_NS::cref(func1b));

      m_string += m_cresults.format(func3b, f);
      m_string += m_cresults.format(func3b);
      m_string += m_cresults.format(func2b, f);
      m_string += m_cresults.format(func2b);
      m_string += m_cresults.format(func1b, f);
      m_string += m_cresults.format(func1b);
      m_string += m_cresults.format(RW_NS::ref(func3b), f);
      m_string += m_cresults.format(RW_NS::ref(func3b));
      m_string += m_cresults.format(RW_NS::ref(func2b), f);
      m_string += m_cresults.format(RW_NS::ref(func2b));
      m_string += m_cresults.format(RW_NS::ref(func1b), f);
      m_string += m_cresults.format(RW_NS::ref(func1b));
      m_string += m_cresults.format(RW_NS::cref(func3b), f);
      m_string += m_cresults.format(RW_NS::cref(func3b));
      m_string += m_cresults.format(RW_NS::cref(func2b), f);
      m_string += m_cresults.format(RW_NS::cref(func2b));
      m_string += m_cresults.format(RW_NS::cref(func1b), f);
      m_string += m_cresults.format(RW_NS::cref(func1b));

      out = regex_replace(out, m_in, m_in, ce, func3, f);
      out = regex_replace(out, m_in, m_in, ce, func3);
      out = regex_replace(out, m_in, m_in, ce, func2, f);
      out = regex_replace(out, m_in, m_in, ce, func2);
      out = regex_replace(out, m_in, m_in, ce, func1, f);
      out = regex_replace(out, m_in, m_in, ce, func1);
      out = regex_replace(out, m_in, m_in, ce, RW_NS::ref(func3), f);
      out = regex_replace(out, m_in, m_in, ce, RW_NS::ref(func3));
      out = regex_replace(out, m_in, m_in, ce, RW_NS::ref(func2), f);
      out = regex_replace(out, m_in, m_in, ce, RW_NS::ref(func2));
      out = regex_replace(out, m_in, m_in, ce, RW_NS::ref(func1), f);
      out = regex_replace(out, m_in, m_in, ce, RW_NS::ref(func1));
      out = regex_replace(out, m_in, m_in, ce, RW_NS::cref(func3), f);
      out = regex_replace(out, m_in, m_in, ce, RW_NS::cref(func3));
      out = regex_replace(out, m_in, m_in, ce, RW_NS::cref(func2), f);
      out = regex_replace(out, m_in, m_in, ce, RW_NS::cref(func2));
      out = regex_replace(out, m_in, m_in, ce, RW_NS::cref(func1), f);
      out = regex_replace(out, m_in, m_in, ce, RW_NS::cref(func1));

      functor3<match_results<typename string_type::const_iterator> > func3s;
      functor2<match_results<typename string_type::const_iterator> > func2s;
      functor1<match_results<typename string_type::const_iterator> > func1s;
      m_string += regex_replace(m_string, ce, func3s, f);
      m_string += regex_replace(m_string, ce, func3s);
      m_string += regex_replace(m_string, ce, func2s, f);
      m_string += regex_replace(m_string, ce, func2s);
      m_string += regex_replace(m_string, ce, func1s, f);
      m_string += regex_replace(m_string, ce, func1s);
      m_string += regex_replace(m_string, ce, RW_NS::ref(func3s), f);
      m_string += regex_replace(m_string, ce, RW_NS::ref(func3s));
      m_string += regex_replace(m_string, ce, RW_NS::ref(func2s), f);
      m_string += regex_replace(m_string, ce, RW_NS::ref(func2s));
      m_string += regex_replace(m_string, ce, RW_NS::ref(func1s), f);
      m_string += regex_replace(m_string, ce, RW_NS::ref(func1s));
      m_string += regex_replace(m_string, ce, RW_NS::cref(func3s), f);
      m_string += regex_replace(m_string, ce, RW_NS::cref(func3s));
      m_string += regex_replace(m_string, ce, RW_NS::cref(func2s), f);
      m_string += regex_replace(m_string, ce, RW_NS::cref(func2s));
      m_string += regex_replace(m_string, ce, RW_NS::cref(func1s), f);
      m_string += regex_replace(m_string, ce, RW_NS::cref(func1s));
   }

   std::basic_ostream<value_type> m_stream;
   sub_match_type m_sub;
   pointer_type m_pointer;
   string_type m_string;
   const value_type m_char;
   match_results_type m_results;
   const match_results_type m_cresults;
   BidiIterator m_in;

   BoostRegexConcept();
   BoostRegexConcept(const BoostRegexConcept&);
   BoostRegexConcept& operator=(const BoostRegexConcept&);
};

#endif // BOOST_REGEX_TEST_STD

}

#endif

/* concepts.hpp
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
*/