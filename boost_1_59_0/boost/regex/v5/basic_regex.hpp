/*
 *
 * Copyright (c) 1998-2004 John Maddock
 * Copyright 2011 Garmin Ltd. or its subsidiaries
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 */

 /*
  *   LOCATION:    see http://www.boost.org/ for most recent version.
  *   FILE         basic_regex.cpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Declares template class basic_regex.
  */

#ifndef BOOST_REGEX_V5_BASIC_REGEX_HPP
#define BOOST_REGEX_V5_BASIC_REGEX_HPP

#include <vector>

namespace boost{
#ifdef BOOST_REGEX_MSVC
#pragma warning(push)
#pragma warning(disable : 4251)
#if BOOST_REGEX_MSVC < 1700
#     pragma warning(disable : 4231)
#endif
#if BOOST_REGEX_MSVC < 1600
#pragma warning(disable : 4660)
#endif
#if BOOST_REGEX_MSVC < 1910
#pragma warning(disable:4800)
#endif
#endif

namespace BOOST_REGEX_DETAIL_NS{

//
// forward declaration, we will need this one later:
//
template <class charT, class traits>
class basic_regex_parser;

template <class I>
void bubble_down_one(I first, I last)
{
   if(first != last)
   {
      I next = last - 1;
      while((next != first) && (*next < *(next-1)))
      {
         (next-1)->swap(*next);
         --next;
      }
   }
}

static const int hash_value_mask = 1 << (std::numeric_limits<int>::digits - 1);

template <class Iterator>
inline int hash_value_from_capture_name(Iterator i, Iterator j)
{
   std::size_t r = 0;
   while (i != j)
   {
      r ^= *i + 0x9e3779b9 + (r << 6) + (r >> 2);
      ++i;
   }
   r %= ((std::numeric_limits<int>::max)());
   return static_cast<int>(r) | hash_value_mask;
}

class named_subexpressions
{
public:
   struct name
   {
      template <class charT>
      name(const charT* i, const charT* j, int idx)
         : index(idx) 
      { 
         hash = hash_value_from_capture_name(i, j); 
      }
      name(int h, int idx)
         : index(idx), hash(h)
      { 
      }
      int index;
      int hash;
      bool operator < (const name& other)const
      {
         return hash < other.hash;
      }
      bool operator == (const name& other)const
      {
         return hash == other.hash; 
      }
      void swap(name& other)
      {
         std::swap(index, other.index);
         std::swap(hash, other.hash);
      }
   };

   typedef std::vector<name>::const_iterator const_iterator;
   typedef std::pair<const_iterator, const_iterator> range_type;

   named_subexpressions(){}

   template <class charT>
   void set_name(const charT* i, const charT* j, int index)
   {
      m_sub_names.push_back(name(i, j, index));
      bubble_down_one(m_sub_names.begin(), m_sub_names.end());
   }
   template <class charT>
   int get_id(const charT* i, const charT* j)const
   {
      name t(i, j, 0);
      typename std::vector<name>::const_iterator pos = std::lower_bound(m_sub_names.begin(), m_sub_names.end(), t);
      if((pos != m_sub_names.end()) && (*pos == t))
      {
         return pos->index;
      }
      return -1;
   }
   template <class charT>
   range_type equal_range(const charT* i, const charT* j)const
   {
      name t(i, j, 0);
      return std::equal_range(m_sub_names.begin(), m_sub_names.end(), t);
   }
   int get_id(int h)const
   {
      name t(h, 0);
      std::vector<name>::const_iterator pos = std::lower_bound(m_sub_names.begin(), m_sub_names.end(), t);
      if((pos != m_sub_names.end()) && (*pos == t))
      {
         return pos->index;
      }
      return -1;
   }
   range_type equal_range(int h)const
   {
      name t(h, 0);
      return std::equal_range(m_sub_names.begin(), m_sub_names.end(), t);
   }
private:
   std::vector<name> m_sub_names;
};

//
// class regex_data:
// represents the data we wish to expose to the matching algorithms.
//
template <class charT, class traits>
struct regex_data : public named_subexpressions
{
   typedef regex_constants::syntax_option_type   flag_type;
   typedef std::size_t                           size_type;  

   regex_data(const ::std::shared_ptr<
      ::boost::regex_traits_wrapper<traits> >& t) 
      : m_ptraits(t), m_flags(0), m_status(0), m_expression(0), m_expression_len(0),
         m_mark_count(0), m_first_state(0), m_restart_type(0),
         m_startmap{ 0 },
         m_can_be_null(0), m_word_mask(0), m_has_recursions(false), m_disable_match_any(false) {}
   regex_data() 
      : m_ptraits(new ::boost::regex_traits_wrapper<traits>()), m_flags(0), m_status(0), m_expression(0), m_expression_len(0), 
         m_mark_count(0), m_first_state(0), m_restart_type(0), 
      m_startmap{ 0 },
         m_can_be_null(0), m_word_mask(0), m_has_recursions(false), m_disable_match_any(false) {}

   ::std::shared_ptr<
      ::boost::regex_traits_wrapper<traits>
      >                        m_ptraits;                 // traits class instance
   flag_type                   m_flags;                   // flags with which we were compiled
   int                         m_status;                  // error code (0 implies OK).
   const charT*                m_expression;              // the original expression
   std::ptrdiff_t              m_expression_len;          // the length of the original expression
   size_type                   m_mark_count;              // the number of marked sub-expressions
   BOOST_REGEX_DETAIL_NS::re_syntax_base*  m_first_state;             // the first state of the machine
   unsigned                    m_restart_type;            // search optimisation type
   unsigned char               m_startmap[1 << CHAR_BIT]; // which characters can start a match
   unsigned int                m_can_be_null;             // whether we can match a null string
   BOOST_REGEX_DETAIL_NS::raw_storage      m_data;                    // the buffer in which our states are constructed
   typename traits::char_class_type    m_word_mask;       // mask used to determine if a character is a word character
   std::vector<
      std::pair<
      std::size_t, std::size_t> > m_subs;                 // Position of sub-expressions within the *string*.
   bool                        m_has_recursions;          // whether we have recursive expressions;
   bool                        m_disable_match_any;       // when set we need to disable the match_any flag as it causes different/buggy behaviour.
};
//
// class basic_regex_implementation
// pimpl implementation class for basic_regex.
//
template <class charT, class traits>
class basic_regex_implementation
   : public regex_data<charT, traits>
{
public:
   typedef regex_constants::syntax_option_type   flag_type;
   typedef std::ptrdiff_t                        difference_type;
   typedef std::size_t                           size_type; 
   typedef typename traits::locale_type          locale_type;
   typedef const charT*                          const_iterator;

   basic_regex_implementation(){}
   basic_regex_implementation(const ::std::shared_ptr<
      ::boost::regex_traits_wrapper<traits> >& t)
      : regex_data<charT, traits>(t) {}
   void assign(const charT* arg_first,
                          const charT* arg_last,
                          flag_type f)
   {
      regex_data<charT, traits>* pdat = this;
      basic_regex_parser<charT, traits> parser(pdat);
      parser.parse(arg_first, arg_last, f);
   }

   locale_type  imbue(locale_type l)
   { 
      return this->m_ptraits->imbue(l); 
   }
   locale_type  getloc()const
   { 
      return this->m_ptraits->getloc(); 
   }
   std::basic_string<charT>  str()const
   {
      std::basic_string<charT> result;
      if(this->m_status == 0)
         result = std::basic_string<charT>(this->m_expression, this->m_expression_len);
      return result;
   }
   const_iterator  expression()const
   {
      return this->m_expression;
   }
   std::pair<const_iterator, const_iterator>  subexpression(std::size_t n)const
   {
      const std::pair<std::size_t, std::size_t>& pi = this->m_subs.at(n);
      std::pair<const_iterator, const_iterator> p(expression() + pi.first, expression() + pi.second);
      return p;
   }
   //
   // begin, end:
   const_iterator  begin()const
   { 
      return (this->m_status ? 0 : this->m_expression); 
   }
   const_iterator  end()const
   { 
      return (this->m_status ? 0 : this->m_expression + this->m_expression_len); 
   }
   flag_type  flags()const
   {
      return this->m_flags;
   }
   size_type  size()const
   {
      return this->m_expression_len;
   }
   int  status()const
   {
      return this->m_status;
   }
   size_type  mark_count()const
   {
      return this->m_mark_count - 1;
   }
   const BOOST_REGEX_DETAIL_NS::re_syntax_base* get_first_state()const
   {
      return this->m_first_state;
   }
   unsigned get_restart_type()const
   {
      return this->m_restart_type;
   }
   const unsigned char* get_map()const
   {
      return this->m_startmap;
   }
   const ::boost::regex_traits_wrapper<traits>& get_traits()const
   {
      return *(this->m_ptraits);
   }
   bool can_be_null()const
   {
      return this->m_can_be_null;
   }
   const regex_data<charT, traits>& get_data()const
   {
      basic_regex_implementation<charT, traits> const* p = this;
      return *static_cast<const regex_data<charT, traits>*>(p);
   }
};

} // namespace BOOST_REGEX_DETAIL_NS
//
// class basic_regex:
// represents the compiled
// regular expression:
//

#ifdef BOOST_REGEX_NO_FWD
template <class charT, class traits = regex_traits<charT> >
#else
template <class charT, class traits >
#endif
class basic_regex : public regbase
{
public:
   // typedefs:
   typedef std::size_t                           traits_size_type;
   typedef typename traits::string_type          traits_string_type;
   typedef charT                                 char_type;
   typedef traits                                traits_type;

   typedef charT                                 value_type;
   typedef charT&                                reference;
   typedef const charT&                          const_reference;
   typedef const charT*                          const_iterator;
   typedef const_iterator                        iterator;
   typedef std::ptrdiff_t                        difference_type;
   typedef std::size_t                           size_type;   
   typedef regex_constants::syntax_option_type   flag_type;
   // locale_type
   // placeholder for actual locale type used by the
   // traits class to localise *this.
   typedef typename traits::locale_type          locale_type;
   
public:
   explicit basic_regex(){}
   explicit basic_regex(const charT* p, flag_type f = regex_constants::normal)
   {
      assign(p, f);
   }
   basic_regex(const charT* p1, const charT* p2, flag_type f = regex_constants::normal)
   {
      assign(p1, p2, f);
   }
   basic_regex(const charT* p, size_type len, flag_type f)
   {
      assign(p, len, f);
   }
   basic_regex(const basic_regex& that)
      : m_pimpl(that.m_pimpl) {}
   ~basic_regex(){}
   basic_regex&  operator=(const basic_regex& that)
   {
      return assign(that);
   }
   basic_regex&  operator=(const charT* ptr)
   {
      return assign(ptr);
   }

   //
   // assign:
   basic_regex& assign(const basic_regex& that)
   { 
      m_pimpl = that.m_pimpl;
      return *this; 
   }
   basic_regex& assign(const charT* p, flag_type f = regex_constants::normal)
   {
      return assign(p, p + traits::length(p), f);
   }
   basic_regex& assign(const charT* p, size_type len, flag_type f)
   {
      return assign(p, p + len, f);
   }
private:
   basic_regex& do_assign(const charT* p1,
                          const charT* p2,
                          flag_type f);
public:
   basic_regex& assign(const charT* p1,
                          const charT* p2,
                          flag_type f = regex_constants::normal)
   {
      return do_assign(p1, p2, f);
   }

   template <class ST, class SA>
   unsigned int  set_expression(const std::basic_string<charT, ST, SA>& p, flag_type f = regex_constants::normal)
   { 
      return set_expression(p.data(), p.data() + p.size(), f); 
   }

   template <class ST, class SA>
   explicit basic_regex(const std::basic_string<charT, ST, SA>& p, flag_type f = regex_constants::normal)
   { 
      assign(p, f); 
   }

   template <class InputIterator>
   basic_regex(InputIterator arg_first, InputIterator arg_last, flag_type f = regex_constants::normal)
   {
      typedef typename traits::string_type seq_type;
      seq_type a(arg_first, arg_last);
      if(!a.empty())
         assign(static_cast<const charT*>(&*a.begin()), static_cast<const charT*>(&*a.begin() + a.size()), f);
      else
         assign(static_cast<const charT*>(0), static_cast<const charT*>(0), f);
   }

   template <class ST, class SA>
   basic_regex&  operator=(const std::basic_string<charT, ST, SA>& p)
   {
      return assign(p.data(), p.data() + p.size(), regex_constants::normal);
   }

   template <class string_traits, class A>
   basic_regex&  assign(
       const std::basic_string<charT, string_traits, A>& s,
       flag_type f = regex_constants::normal)
   {
      return assign(s.data(), s.data() + s.size(), f);
   }

   template <class InputIterator>
   basic_regex&  assign(InputIterator arg_first,
                          InputIterator arg_last,
                          flag_type f = regex_constants::normal)
   {
      typedef typename traits::string_type seq_type;
      seq_type a(arg_first, arg_last);
      if(a.size())
      {
         const charT* p1 = &*a.begin();
         const charT* p2 = &*a.begin() + a.size();
         return assign(p1, p2, f);
      }
      return assign(static_cast<const charT*>(0), static_cast<const charT*>(0), f);
   }

   //
   // locale:
   locale_type  imbue(locale_type l);
   locale_type  getloc()const
   { 
      return m_pimpl.get() ? m_pimpl->getloc() : locale_type(); 
   }
   //
   // getflags:
   // retained for backwards compatibility only, "flags"
   // is now the preferred name:
   flag_type  getflags()const
   { 
      return flags();
   }
   flag_type  flags()const
   { 
      return m_pimpl.get() ? m_pimpl->flags() : 0;
   }
   //
   // str:
   std::basic_string<charT>  str()const
   {
      return m_pimpl.get() ? m_pimpl->str() : std::basic_string<charT>();
   }
   //
   // begin, end, subexpression:
   std::pair<const_iterator, const_iterator>  subexpression(std::size_t n)const
   {
#ifdef BOOST_REGEX_STANDALONE
      if (!m_pimpl.get())
         throw std::logic_error("Can't access subexpressions in an invalid regex.");
#else
      if(!m_pimpl.get())
         boost::throw_exception(std::logic_error("Can't access subexpressions in an invalid regex."));
#endif
      return m_pimpl->subexpression(n);
   }
   const_iterator  begin()const
   { 
      return (m_pimpl.get() ? m_pimpl->begin() : 0); 
   }
   const_iterator  end()const
   { 
      return (m_pimpl.get() ? m_pimpl->end() : 0); 
   }
   //
   // swap:
   void  swap(basic_regex& that)throw()
   {
      m_pimpl.swap(that.m_pimpl);
   }
   //
   // size:
   size_type  size()const
   { 
      return (m_pimpl.get() ? m_pimpl->size() : 0); 
   }
   //
   // max_size:
   size_type  max_size()const
   { 
      return UINT_MAX; 
   }
   //
   // empty:
   bool  empty()const
   { 
      return (m_pimpl.get() ? 0 != m_pimpl->status() : true); 
   }

   size_type  mark_count()const 
   { 
      return (m_pimpl.get() ? m_pimpl->mark_count() : 0); 
   }

   int status()const
   {
      return (m_pimpl.get() ? m_pimpl->status() : regex_constants::error_empty);
   }

   int  compare(const basic_regex& that) const
   {
      if(m_pimpl.get() == that.m_pimpl.get())
         return 0;
      if(!m_pimpl.get())
         return -1;
      if(!that.m_pimpl.get())
         return 1;
      if(status() != that.status())
         return status() - that.status();
      if(flags() != that.flags())
         return flags() - that.flags();
      return str().compare(that.str());
   }
   bool  operator==(const basic_regex& e)const
   { 
      return compare(e) == 0; 
   }
   bool  operator != (const basic_regex& e)const
   { 
      return compare(e) != 0; 
   }
   bool  operator<(const basic_regex& e)const
   { 
      return compare(e) < 0; 
   }
   bool  operator>(const basic_regex& e)const
   { 
      return compare(e) > 0; 
   }
   bool  operator<=(const basic_regex& e)const
   { 
      return compare(e) <= 0; 
   }
   bool  operator>=(const basic_regex& e)const
   { 
      return compare(e) >= 0; 
   }

   //
   // The following are deprecated as public interfaces
   // but are available for compatibility with earlier versions.
   const charT*  expression()const 
   { 
      return (m_pimpl.get() && !m_pimpl->status() ? m_pimpl->expression() : 0); 
   }
   unsigned int  set_expression(const charT* p1, const charT* p2, flag_type f = regex_constants::normal)
   {
      assign(p1, p2, f | regex_constants::no_except);
      return status();
   }
   unsigned int  set_expression(const charT* p, flag_type f = regex_constants::normal) 
   { 
      assign(p, f | regex_constants::no_except); 
      return status();
   }
   unsigned int  error_code()const
   {
      return status();
   }
   //
   // private access methods:
   //
   const BOOST_REGEX_DETAIL_NS::re_syntax_base* get_first_state()const
   {
      BOOST_REGEX_ASSERT(0 != m_pimpl.get());
      return m_pimpl->get_first_state();
   }
   unsigned get_restart_type()const
   {
      BOOST_REGEX_ASSERT(0 != m_pimpl.get());
      return m_pimpl->get_restart_type();
   }
   const unsigned char* get_map()const
   {
      BOOST_REGEX_ASSERT(0 != m_pimpl.get());
      return m_pimpl->get_map();
   }
   const ::boost::regex_traits_wrapper<traits>& get_traits()const
   {
      BOOST_REGEX_ASSERT(0 != m_pimpl.get());
      return m_pimpl->get_traits();
   }
   bool can_be_null()const
   {
      BOOST_REGEX_ASSERT(0 != m_pimpl.get());
      return m_pimpl->can_be_null();
   }
   const BOOST_REGEX_DETAIL_NS::regex_data<charT, traits>& get_data()const
   {
      BOOST_REGEX_ASSERT(0 != m_pimpl.get());
      return m_pimpl->get_data();
   }
   std::shared_ptr<BOOST_REGEX_DETAIL_NS::named_subexpressions > get_named_subs()const
   {
      return m_pimpl;
   }

private:
   std::shared_ptr<BOOST_REGEX_DETAIL_NS::basic_regex_implementation<charT, traits> > m_pimpl;
};

//
// out of line members;
// these are the only members that mutate the basic_regex object,
// and are designed to provide the strong exception guarantee
// (in the event of a throw, the state of the object remains unchanged).
//
template <class charT, class traits>
basic_regex<charT, traits>& basic_regex<charT, traits>::do_assign(const charT* p1,
                        const charT* p2,
                        flag_type f)
{
   std::shared_ptr<BOOST_REGEX_DETAIL_NS::basic_regex_implementation<charT, traits> > temp;
   if(!m_pimpl.get())
   {
      temp = std::shared_ptr<BOOST_REGEX_DETAIL_NS::basic_regex_implementation<charT, traits> >(new BOOST_REGEX_DETAIL_NS::basic_regex_implementation<charT, traits>());
   }
   else
   {
      temp = std::shared_ptr<BOOST_REGEX_DETAIL_NS::basic_regex_implementation<charT, traits> >(new BOOST_REGEX_DETAIL_NS::basic_regex_implementation<charT, traits>(m_pimpl->m_ptraits));
   }
   temp->assign(p1, p2, f);
   temp.swap(m_pimpl);
   return *this;
}

template <class charT, class traits>
typename basic_regex<charT, traits>::locale_type  basic_regex<charT, traits>::imbue(locale_type l)
{ 
   std::shared_ptr<BOOST_REGEX_DETAIL_NS::basic_regex_implementation<charT, traits> > temp(new BOOST_REGEX_DETAIL_NS::basic_regex_implementation<charT, traits>());
   locale_type result = temp->imbue(l);
   temp.swap(m_pimpl);
   return result;
}

//
// non-members:
//
template <class charT, class traits>
void swap(basic_regex<charT, traits>& e1, basic_regex<charT, traits>& e2)
{
   e1.swap(e2);
}

template <class charT, class traits, class traits2>
std::basic_ostream<charT, traits>& 
   operator << (std::basic_ostream<charT, traits>& os, 
                const basic_regex<charT, traits2>& e)
{
   return (os << e.str());
}

//
// class reg_expression:
// this is provided for backwards compatibility only,
// it is deprecated, no not use!
//
#ifdef BOOST_REGEX_NO_FWD
template <class charT, class traits = regex_traits<charT> >
#else
template <class charT, class traits >
#endif
class reg_expression : public basic_regex<charT, traits>
{
public:
   typedef typename basic_regex<charT, traits>::flag_type flag_type;
   typedef typename basic_regex<charT, traits>::size_type size_type;
   explicit reg_expression(){}
   explicit reg_expression(const charT* p, flag_type f = regex_constants::normal)
      : basic_regex<charT, traits>(p, f){}
   reg_expression(const charT* p1, const charT* p2, flag_type f = regex_constants::normal)
      : basic_regex<charT, traits>(p1, p2, f){}
   reg_expression(const charT* p, size_type len, flag_type f)
      : basic_regex<charT, traits>(p, len, f){}
   reg_expression(const reg_expression& that)
      : basic_regex<charT, traits>(that) {}
   ~reg_expression(){}
   reg_expression&  operator=(const reg_expression& that)
   {
      return this->assign(that);
   }

   template <class ST, class SA>
   explicit reg_expression(const std::basic_string<charT, ST, SA>& p, flag_type f = regex_constants::normal)
   : basic_regex<charT, traits>(p, f)
   { 
   }

   template <class InputIterator>
   reg_expression(InputIterator arg_first, InputIterator arg_last, flag_type f = regex_constants::normal)
   : basic_regex<charT, traits>(arg_first, arg_last, f)
   {
   }

   template <class ST, class SA>
   reg_expression&  operator=(const std::basic_string<charT, ST, SA>& p)
   {
      this->assign(p);
      return *this;
   }

};

#ifdef BOOST_REGEX_MSVC
#pragma warning (pop)
#endif

} // namespace boost

#endif

/* basic_regex.hpp
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
*/