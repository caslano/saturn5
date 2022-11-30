/*
 *
 * Copyright (c) 1998-2009
 * John Maddock
 *
 * Use, modification and distribution are subject to the 
 * Boost Software License, Version 1.0. (See accompanying file 
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */

 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE         match_results.cpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Declares template class match_results.
  */

#ifndef BOOST_REGEX_V5_MATCH_RESULTS_HPP
#define BOOST_REGEX_V5_MATCH_RESULTS_HPP

namespace boost{
#ifdef BOOST_REGEX_MSVC
#pragma warning(push)
#pragma warning(disable : 4251 4459)
#if BOOST_REGEX_MSVC < 1700
#     pragma warning(disable : 4231)
#endif
#  if BOOST_REGEX_MSVC < 1600
#     pragma warning(disable : 4660)
#  endif
#endif

namespace BOOST_REGEX_DETAIL_NS{

class named_subexpressions;

}

template <class BidiIterator, class Allocator>
class match_results
{ 
private:
   typedef          std::vector<sub_match<BidiIterator>, Allocator> vector_type;
public: 
   typedef          sub_match<BidiIterator>                         value_type;
   typedef typename std::allocator_traits<Allocator>::value_type const &    const_reference;
   typedef          const_reference                                         reference;
   typedef typename vector_type::const_iterator                             const_iterator;
   typedef          const_iterator                                          iterator;
   typedef typename std::iterator_traits<
                                    BidiIterator>::difference_type          difference_type;
   typedef typename std::allocator_traits<Allocator>::size_type             size_type;
   typedef          Allocator                                               allocator_type;
   typedef typename std::iterator_traits<
                                    BidiIterator>::value_type               char_type;
   typedef          std::basic_string<char_type>                            string_type;
   typedef          BOOST_REGEX_DETAIL_NS::named_subexpressions             named_sub_type;

   // construct/copy/destroy:
   explicit match_results(const Allocator& a = Allocator())
      : m_subs(a), m_base(), m_null(), m_last_closed_paren(0), m_is_singular(true) {}
   //
   // IMPORTANT: in the code below, the crazy looking checks around m_is_singular are
   // all required because it is illegal to copy a singular iterator.
   // See https://svn.boost.org/trac/boost/ticket/3632.
   //
   match_results(const match_results& m)
      : m_subs(m.m_subs), m_base(), m_null(), m_named_subs(m.m_named_subs), m_last_closed_paren(m.m_last_closed_paren), m_is_singular(m.m_is_singular)
   {
      if(!m_is_singular)
      {
         m_base = m.m_base;
         m_null = m.m_null;
      }
   }
   match_results& operator=(const match_results& m)
   {
      m_subs = m.m_subs;
      m_named_subs = m.m_named_subs;
      m_last_closed_paren = m.m_last_closed_paren;
      m_is_singular = m.m_is_singular;
      if(!m_is_singular)
      {
         m_base = m.m_base;
         m_null = m.m_null;
      }
      return *this;
   }
   ~match_results(){}

   // size:
   size_type size() const
   { return empty() ? 0 : m_subs.size() - 2; }
   size_type max_size() const
   { return m_subs.max_size(); }
   bool empty() const
   { return m_subs.size() < 2; }
   // element access:
   difference_type length(int sub = 0) const
   {
      if(m_is_singular)
         raise_logic_error();
      sub += 2;
      if((sub < (int)m_subs.size()) && (sub > 0))
         return m_subs[sub].length();
      return 0;
   }
   difference_type length(const char_type* sub) const
   {
      if(m_is_singular)
         raise_logic_error();
      const char_type* sub_end = sub;
      while(*sub_end) ++sub_end;
      return length(named_subexpression_index(sub, sub_end));
   }
   template <class charT>
   difference_type length(const charT* sub) const
   {
      if(m_is_singular)
         raise_logic_error();
      const charT* sub_end = sub;
      while(*sub_end) ++sub_end;
      return length(named_subexpression_index(sub, sub_end));
   }
   template <class charT, class Traits, class A>
   difference_type length(const std::basic_string<charT, Traits, A>& sub) const
   {
      return length(sub.c_str());
   }
   difference_type position(size_type sub = 0) const
   {
      if(m_is_singular)
         raise_logic_error();
      sub += 2;
      if(sub < m_subs.size())
      {
         const sub_match<BidiIterator>& s = m_subs[sub];
         if(s.matched || (sub == 2))
         {
            return std::distance((BidiIterator)(m_base), (BidiIterator)(s.first));
         }
      }
      return ~static_cast<difference_type>(0);
   }
   difference_type position(const char_type* sub) const
   {
      const char_type* sub_end = sub;
      while(*sub_end) ++sub_end;
      return position(named_subexpression_index(sub, sub_end));
   }
   template <class charT>
   difference_type position(const charT* sub) const
   {
      const charT* sub_end = sub;
      while(*sub_end) ++sub_end;
      return position(named_subexpression_index(sub, sub_end));
   }
   template <class charT, class Traits, class A>
   difference_type position(const std::basic_string<charT, Traits, A>& sub) const
   {
      return position(sub.c_str());
   }
   string_type str(int sub = 0) const
   {
      if(m_is_singular)
         raise_logic_error();
      sub += 2;
      string_type result;
      if(sub < (int)m_subs.size() && (sub > 0))
      {
         const sub_match<BidiIterator>& s = m_subs[sub];
         if(s.matched)
         {
            result = s.str();
         }
      }
      return result;
   }
   string_type str(const char_type* sub) const
   {
      return (*this)[sub].str();
   }
   template <class Traits, class A>
   string_type str(const std::basic_string<char_type, Traits, A>& sub) const
   {
      return (*this)[sub].str();
   }
   template <class charT>
   string_type str(const charT* sub) const
   {
      return (*this)[sub].str();
   }
   template <class charT, class Traits, class A>
   string_type str(const std::basic_string<charT, Traits, A>& sub) const
   {
      return (*this)[sub].str();
   }
   const_reference operator[](int sub) const
   {
      if(m_is_singular && m_subs.empty())
         raise_logic_error();
      sub += 2;
      if(sub < (int)m_subs.size() && (sub >= 0))
      {
         return m_subs[sub];
      }
      return m_null;
   }
   //
   // Named sub-expressions:
   //
   const_reference named_subexpression(const char_type* i, const char_type* j) const
   {
      //
      // Scan for the leftmost *matched* subexpression with the specified named:
      //
      if(m_is_singular)
         raise_logic_error();
      BOOST_REGEX_DETAIL_NS::named_subexpressions::range_type r = m_named_subs->equal_range(i, j);
      while((r.first != r.second) && ((*this)[r.first->index].matched == false))
         ++r.first;
      return r.first != r.second ? (*this)[r.first->index] : m_null;
   }
   template <class charT>
   const_reference named_subexpression(const charT* i, const charT* j) const
   {
      static_assert(sizeof(charT) <= sizeof(char_type), "Failed internal logic");
      if(i == j)
         return m_null;
      std::vector<char_type> s;
      while(i != j)
         s.insert(s.end(), *i++);
      return named_subexpression(&*s.begin(), &*s.begin() + s.size());
   }
   int named_subexpression_index(const char_type* i, const char_type* j) const
   {
      //
      // Scan for the leftmost *matched* subexpression with the specified named.
      // If none found then return the leftmost expression with that name,
      // otherwise an invalid index:
      //
      if(m_is_singular)
         raise_logic_error();
      BOOST_REGEX_DETAIL_NS::named_subexpressions::range_type s, r;
      s = r = m_named_subs->equal_range(i, j);
      while((r.first != r.second) && ((*this)[r.first->index].matched == false))
         ++r.first;
      if(r.first == r.second)
         r = s;
      return r.first != r.second ? r.first->index : -20;
   }
   template <class charT>
   int named_subexpression_index(const charT* i, const charT* j) const
   {
      static_assert(sizeof(charT) <= sizeof(char_type), "Failed internal logic");
      if(i == j)
         return -20;
      std::vector<char_type> s;
      while(i != j)
         s.insert(s.end(), *i++);
      return named_subexpression_index(&*s.begin(), &*s.begin() + s.size());
   }
   template <class Traits, class A>
   const_reference operator[](const std::basic_string<char_type, Traits, A>& s) const
   {
      return named_subexpression(s.c_str(), s.c_str() + s.size());
   }
   const_reference operator[](const char_type* p) const
   {
      const char_type* e = p;
      while(*e) ++e;
      return named_subexpression(p, e);
   }

   template <class charT>
   const_reference operator[](const charT* p) const
   {
      static_assert(sizeof(charT) <= sizeof(char_type), "Failed internal logic");
      if(*p == 0)
         return m_null;
      std::vector<char_type> s;
      while(*p)
         s.insert(s.end(), *p++);
      return named_subexpression(&*s.begin(), &*s.begin() + s.size());
   }
   template <class charT, class Traits, class A>
   const_reference operator[](const std::basic_string<charT, Traits, A>& ns) const
   {
      static_assert(sizeof(charT) <= sizeof(char_type), "Failed internal logic");
      if(ns.empty())
         return m_null;
      std::vector<char_type> s;
      for(unsigned i = 0; i < ns.size(); ++i)
         s.insert(s.end(), ns[i]);
      return named_subexpression(&*s.begin(), &*s.begin() + s.size());
   }

   const_reference prefix() const
   {
      if(m_is_singular)
         raise_logic_error();
      return (*this)[-1];
   }

   const_reference suffix() const
   {
      if(m_is_singular)
         raise_logic_error();
      return (*this)[-2];
   }
   const_iterator begin() const
   {
      return (m_subs.size() > 2) ? (m_subs.begin() + 2) : m_subs.end();
   }
   const_iterator end() const
   {
      return m_subs.end();
   }
   // format:
   template <class OutputIterator, class Functor>
   OutputIterator format(OutputIterator out,
                         Functor fmt,
                         match_flag_type flags = format_default) const
   {
      if(m_is_singular)
         raise_logic_error();
      typedef typename BOOST_REGEX_DETAIL_NS::compute_functor_type<Functor, match_results<BidiIterator, Allocator>, OutputIterator>::type F;
      F func(fmt);
      return func(*this, out, flags);
   }
   template <class Functor>
   string_type format(Functor fmt, match_flag_type flags = format_default) const
   {
      if(m_is_singular)
         raise_logic_error();
      std::basic_string<char_type> result;
      BOOST_REGEX_DETAIL_NS::string_out_iterator<std::basic_string<char_type> > i(result);

      typedef typename BOOST_REGEX_DETAIL_NS::compute_functor_type<Functor, match_results<BidiIterator, Allocator>, BOOST_REGEX_DETAIL_NS::string_out_iterator<std::basic_string<char_type> > >::type F;
      F func(fmt);

      func(*this, i, flags);
      return result;
   }
   // format with locale:
   template <class OutputIterator, class Functor, class RegexT>
   OutputIterator format(OutputIterator out,
                         Functor fmt,
                         match_flag_type flags,
                         const RegexT& re) const
   {
      if(m_is_singular)
         raise_logic_error();
      typedef ::boost::regex_traits_wrapper<typename RegexT::traits_type> traits_type;
      typedef typename BOOST_REGEX_DETAIL_NS::compute_functor_type<Functor, match_results<BidiIterator, Allocator>, OutputIterator, traits_type>::type F;
      F func(fmt);
      return func(*this, out, flags, re.get_traits());
   }
   template <class RegexT, class Functor>
   string_type format(Functor fmt,
                      match_flag_type flags,
                      const RegexT& re) const
   {
      if(m_is_singular)
         raise_logic_error();
      typedef ::boost::regex_traits_wrapper<typename RegexT::traits_type> traits_type;
      std::basic_string<char_type> result;
      BOOST_REGEX_DETAIL_NS::string_out_iterator<std::basic_string<char_type> > i(result);

      typedef typename BOOST_REGEX_DETAIL_NS::compute_functor_type<Functor, match_results<BidiIterator, Allocator>, BOOST_REGEX_DETAIL_NS::string_out_iterator<std::basic_string<char_type> >, traits_type >::type F;
      F func(fmt);

      func(*this, i, flags, re.get_traits());
      return result;
   }

   const_reference get_last_closed_paren()const
   {
      if(m_is_singular)
         raise_logic_error();
      return m_last_closed_paren == 0 ? m_null : (*this)[m_last_closed_paren];
   }

   allocator_type get_allocator() const
   {
      return m_subs.get_allocator();
   }
   void swap(match_results& that)
   {
      std::swap(m_subs, that.m_subs);
      std::swap(m_named_subs, that.m_named_subs);
      std::swap(m_last_closed_paren, that.m_last_closed_paren);
      if(m_is_singular)
      {
         if(!that.m_is_singular)
         {
            m_base = that.m_base;
            m_null = that.m_null;
         }
      }
      else if(that.m_is_singular)
      {
         that.m_base = m_base;
         that.m_null = m_null;
      }
      else
      {
         std::swap(m_base, that.m_base);
         std::swap(m_null, that.m_null);
      }
      std::swap(m_is_singular, that.m_is_singular);
   }
   bool operator==(const match_results& that)const
   {
      if(m_is_singular)
      {
         return that.m_is_singular;
      }
      else if(that.m_is_singular)
      {
         return false;
      }
      return (m_subs == that.m_subs) && (m_base == that.m_base) && (m_last_closed_paren == that.m_last_closed_paren);
   }
   bool operator!=(const match_results& that)const
   { return !(*this == that); }

#ifdef BOOST_REGEX_MATCH_EXTRA
   typedef typename sub_match<BidiIterator>::capture_sequence_type capture_sequence_type;

   const capture_sequence_type& captures(int i)const
   {
      if(m_is_singular)
         raise_logic_error();
      return (*this)[i].captures();
   }
#endif

   //
   // private access functions:
   void  set_second(BidiIterator i)
   {
      BOOST_REGEX_ASSERT(m_subs.size() > 2);
      m_subs[2].second = i;
      m_subs[2].matched = true;
      m_subs[0].first = i;
      m_subs[0].matched = (m_subs[0].first != m_subs[0].second);
      m_null.first = i;
      m_null.second = i;
      m_null.matched = false;
      m_is_singular = false;
   }

   void  set_second(BidiIterator i, size_type pos, bool m = true, bool escape_k = false)
   {
      if(pos)
         m_last_closed_paren = static_cast<int>(pos);
      pos += 2;
      BOOST_REGEX_ASSERT(m_subs.size() > pos);
      m_subs[pos].second = i;
      m_subs[pos].matched = m;
      if((pos == 2) && !escape_k)
      {
         m_subs[0].first = i;
         m_subs[0].matched = (m_subs[0].first != m_subs[0].second);
         m_null.first = i;
         m_null.second = i;
         m_null.matched = false;
         m_is_singular = false;
      }
   }
   void  set_size(size_type n, BidiIterator i, BidiIterator j)
   {
      value_type v(j);
      size_type len = m_subs.size();
      if(len > n + 2)
      {
         m_subs.erase(m_subs.begin()+n+2, m_subs.end());
         std::fill(m_subs.begin(), m_subs.end(), v);
      }
      else
      {
         std::fill(m_subs.begin(), m_subs.end(), v);
         if(n+2 != len)
            m_subs.insert(m_subs.end(), n+2-len, v);
      }
      m_subs[1].first = i;
      m_last_closed_paren = 0;
   }
   void  set_base(BidiIterator pos)
   {
      m_base = pos;
   }
   BidiIterator base()const
   {
      return m_base;
   }
   void  set_first(BidiIterator i)
   {
      BOOST_REGEX_ASSERT(m_subs.size() > 2);
      // set up prefix:
      m_subs[1].second = i;
      m_subs[1].matched = (m_subs[1].first != i);
      // set up $0:
      m_subs[2].first = i;
      // zero out everything else:
      for(size_type n = 3; n < m_subs.size(); ++n)
      {
         m_subs[n].first = m_subs[n].second = m_subs[0].second;
         m_subs[n].matched = false;
      }
   }
   void  set_first(BidiIterator i, size_type pos, bool escape_k = false)
   {
      BOOST_REGEX_ASSERT(pos+2 < m_subs.size());
      if(pos || escape_k)
      {
         m_subs[pos+2].first = i;
         if(escape_k)
         {
            m_subs[1].second = i;
            m_subs[1].matched = (m_subs[1].first != m_subs[1].second);
         }
      }
      else
         set_first(i);
   }
   void  maybe_assign(const match_results<BidiIterator, Allocator>& m);

   void  set_named_subs(std::shared_ptr<named_sub_type> subs)
   {
      m_named_subs = subs;
   }

private:
   //
   // Error handler called when an uninitialized match_results is accessed:
   //
   static void raise_logic_error()
   {
      std::logic_error e("Attempt to access an uninitialized boost::match_results<> class.");
#ifndef BOOST_REGEX_STANDALONE
      boost::throw_exception(e);
#else
      throw e;
#endif
   }


   vector_type            m_subs;                      // subexpressions
   BidiIterator   m_base;                              // where the search started from
   sub_match<BidiIterator> m_null;                     // a null match
   std::shared_ptr<named_sub_type> m_named_subs;     // Shared copy of named subs in the regex object
   int m_last_closed_paren;                            // Last ) to be seen - used for formatting
   bool m_is_singular;                                 // True if our stored iterators are singular
};

template <class BidiIterator, class Allocator>
void  match_results<BidiIterator, Allocator>::maybe_assign(const match_results<BidiIterator, Allocator>& m)
{
   if(m_is_singular)
   {
      *this = m;
      return;
   }
   const_iterator p1, p2;
   p1 = begin();
   p2 = m.begin();
   //
   // Distances are measured from the start of *this* match, unless this isn't
   // a valid match in which case we use the start of the whole sequence.  Note that
   // no subsequent match-candidate can ever be to the left of the first match found.
   // This ensures that when we are using bidirectional iterators, that distances 
   // measured are as short as possible, and therefore as efficient as possible
   // to compute.  Finally note that we don't use the "matched" data member to test
   // whether a sub-expression is a valid match, because partial matches set this
   // to false for sub-expression 0.
   //
   BidiIterator l_end = this->suffix().second;
   BidiIterator l_base = (p1->first == l_end) ? this->prefix().first : (*this)[0].first;
   difference_type len1 = 0;
   difference_type len2 = 0;
   difference_type base1 = 0;
   difference_type base2 = 0;
   std::size_t i;
   for(i = 0; i < size(); ++i, ++p1, ++p2)
   {
      //
      // Leftmost takes priority over longest; handle special cases
      // where distances need not be computed first (an optimisation
      // for bidirectional iterators: ensure that we don't accidently
      // compute the length of the whole sequence, as this can be really
      // expensive).
      //
      if(p1->first == l_end)
      {
         if(p2->first != l_end)
         {
            // p2 must be better than p1, and no need to calculate
            // actual distances:
            base1 = 1;
            base2 = 0;
            break;
         }
         else
         {
            // *p1 and *p2 are either unmatched or match end-of sequence,
            // either way no need to calculate distances:
            if((p1->matched == false) && (p2->matched == true))
               break;
            if((p1->matched == true) && (p2->matched == false))
               return;
            continue;
         }
      }
      else if(p2->first == l_end)
      {
         // p1 better than p2, and no need to calculate distances:
         return;
      }
      base1 = std::distance(l_base, p1->first);
      base2 = std::distance(l_base, p2->first);
      BOOST_REGEX_ASSERT(base1 >= 0);
      BOOST_REGEX_ASSERT(base2 >= 0);
      if(base1 < base2) return;
      if(base2 < base1) break;

      len1 = std::distance((BidiIterator)p1->first, (BidiIterator)p1->second);
      len2 = std::distance((BidiIterator)p2->first, (BidiIterator)p2->second);
      BOOST_REGEX_ASSERT(len1 >= 0);
      BOOST_REGEX_ASSERT(len2 >= 0);
      if((len1 != len2) || ((p1->matched == false) && (p2->matched == true)))
         break;
      if((p1->matched == true) && (p2->matched == false))
         return;
   }
   if(i == size())
      return;
   if(base2 < base1)
      *this = m;
   else if((len2 > len1) || ((p1->matched == false) && (p2->matched == true)) )
      *this = m;
}

template <class BidiIterator, class Allocator>
void swap(match_results<BidiIterator, Allocator>& a, match_results<BidiIterator, Allocator>& b)
{
   a.swap(b);
}

template <class charT, class traits, class BidiIterator, class Allocator>
std::basic_ostream<charT, traits>&
   operator << (std::basic_ostream<charT, traits>& os,
                const match_results<BidiIterator, Allocator>& s)
{
   return (os << s.str());
}

#ifdef BOOST_REGEX_MSVC
#pragma warning(pop)
#endif
} // namespace boost

#endif



/* match_results.hpp
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
*/