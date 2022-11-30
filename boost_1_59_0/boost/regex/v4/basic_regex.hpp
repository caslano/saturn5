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

#ifndef BOOST_REGEX_V4_BASIC_REGEX_HPP
#define BOOST_REGEX_V4_BASIC_REGEX_HPP

#include <boost/type_traits/is_same.hpp>
#include <boost/container_hash/hash.hpp>

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

namespace boost{
#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable : 4251)
#if BOOST_MSVC < 1700
#     pragma warning(disable : 4231)
#endif
#if BOOST_MSVC < 1600
#pragma warning(disable : 4660)
#endif
#if BOOST_MSVC < 1910
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
   std::size_t r = boost::hash_range(i, j);
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

   regex_data(const ::boost::shared_ptr<
      ::boost::regex_traits_wrapper<traits> >& t) 
      : m_ptraits(t), m_flags(0), m_status(0), m_expression(0), m_expression_len(0),
         m_mark_count(0), m_first_state(0), m_restart_type(0),
#if !defined(BOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX) && !(defined(BOOST_MSVC) && (BOOST_MSVC < 1900))
         m_startmap{ 0 },
#endif
         m_can_be_null(0), m_word_mask(0), m_has_recursions(false), m_disable_match_any(false) {}
   regex_data() 
      : m_ptraits(new ::boost::regex_traits_wrapper<traits>()), m_flags(0), m_status(0), m_expression(0), m_expression_len(0), 
         m_mark_count(0), m_first_state(0), m_restart_type(0), 
#if !defined(BOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX) && !(defined(BOOST_MSVC) && (BOOST_MSVC < 1900))
      m_startmap{ 0 },
#endif
         m_can_be_null(0), m_word_mask(0), m_has_recursions(false), m_disable_match_any(false) {}

   ::boost::shared_ptr<
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
   basic_regex_implementation(const ::boost::shared_ptr<
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

   locale_type BOOST_REGEX_CALL imbue(locale_type l)
   { 
      return this->m_ptraits->imbue(l); 
   }
   locale_type BOOST_REGEX_CALL getloc()const
   { 
      return this->m_ptraits->getloc(); 
   }
   std::basic_string<charT> BOOST_REGEX_CALL str()const
   {
      std::basic_string<charT> result;
      if(this->m_status == 0)
         result = std::basic_string<charT>(this->m_expression, this->m_expression_len);
      return result;
   }
   const_iterator BOOST_REGEX_CALL expression()const
   {
      return this->m_expression;
   }
   std::pair<const_iterator, const_iterator> BOOST_REGEX_CALL subexpression(std::size_t n)const
   {
      const std::pair<std::size_t, std::size_t>& pi = this->m_subs.at(n);
      std::pair<const_iterator, const_iterator> p(expression() + pi.first, expression() + pi.second);
      return p;
   }
   //
   // begin, end:
   const_iterator BOOST_REGEX_CALL begin()const
   { 
      return (this->m_status ? 0 : this->m_expression); 
   }
   const_iterator BOOST_REGEX_CALL end()const
   { 
      return (this->m_status ? 0 : this->m_expression + this->m_expression_len); 
   }
   flag_type BOOST_REGEX_CALL flags()const
   {
      return this->m_flags;
   }
   size_type BOOST_REGEX_CALL size()const
   {
      return this->m_expression_len;
   }
   int BOOST_REGEX_CALL status()const
   {
      return this->m_status;
   }
   size_type BOOST_REGEX_CALL mark_count()const
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
   basic_regex& BOOST_REGEX_CALL operator=(const basic_regex& that)
   {
      return assign(that);
   }
   basic_regex& BOOST_REGEX_CALL operator=(const charT* ptr)
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
#if !defined(BOOST_NO_MEMBER_TEMPLATES)

   template <class ST, class SA>
   unsigned int BOOST_REGEX_CALL set_expression(const std::basic_string<charT, ST, SA>& p, flag_type f = regex_constants::normal)
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
   basic_regex& BOOST_REGEX_CALL operator=(const std::basic_string<charT, ST, SA>& p)
   {
      return assign(p.data(), p.data() + p.size(), regex_constants::normal);
   }

   template <class string_traits, class A>
   basic_regex& BOOST_REGEX_CALL assign(
       const std::basic_string<charT, string_traits, A>& s,
       flag_type f = regex_constants::normal)
   {
      return assign(s.data(), s.data() + s.size(), f);
   }

   template <class InputIterator>
   basic_regex& BOOST_REGEX_CALL assign(InputIterator arg_first,
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
#else
   unsigned int BOOST_REGEX_CALL set_expression(const std::basic_string<charT>& p, flag_type f = regex_constants::normal)
   { 
      return set_expression(p.data(), p.data() + p.size(), f); 
   }

   basic_regex(const std::basic_string<charT>& p, flag_type f = regex_constants::normal)
   { 
      assign(p, f); 
   }

   basic_regex& BOOST_REGEX_CALL operator=(const std::basic_string<charT>& p)
   {
      return assign(p.data(), p.data() + p.size(), regex_constants::normal);
   }

   basic_regex& BOOST_REGEX_CALL assign(
       const std::basic_string<charT>& s,
       flag_type f = regex_constants::normal)
   {
      return assign(s.data(), s.data() + s.size(), f);
   }

#endif

   //
   // locale:
   locale_type BOOST_REGEX_CALL imbue(locale_type l);
   locale_type BOOST_REGEX_CALL getloc()const
   { 
      return m_pimpl.get() ? m_pimpl->getloc() : locale_type(); 
   }
   //
   // getflags:
   // retained for backwards compatibility only, "flags"
   // is now the preferred name:
   flag_type BOOST_REGEX_CALL getflags()const
   { 
      return flags();
   }
   flag_type BOOST_REGEX_CALL flags()const
   { 
      return m_pimpl.get() ? m_pimpl->flags() : 0;
   }
   //
   // str:
   std::basic_string<charT> BOOST_REGEX_CALL str()const
   {
      return m_pimpl.get() ? m_pimpl->str() : std::basic_string<charT>();
   }
   //
   // begin, end, subexpression:
   std::pair<const_iterator, const_iterator> BOOST_REGEX_CALL subexpression(std::size_t n)const
   {
      if(!m_pimpl.get())
         boost::throw_exception(std::logic_error("Can't access subexpressions in an invalid regex."));
      return m_pimpl->subexpression(n);
   }
   const_iterator BOOST_REGEX_CALL begin()const
   { 
      return (m_pimpl.get() ? m_pimpl->begin() : 0); 
   }
   const_iterator BOOST_REGEX_CALL end()const
   { 
      return (m_pimpl.get() ? m_pimpl->end() : 0); 
   }
   //
   // swap:
   void BOOST_REGEX_CALL swap(basic_regex& that)throw()
   {
      m_pimpl.swap(that.m_pimpl);
   }
   //
   // size:
   size_type BOOST_REGEX_CALL size()const
   { 
      return (m_pimpl.get() ? m_pimpl->size() : 0); 
   }
   //
   // max_size:
   size_type BOOST_REGEX_CALL max_size()const
   { 
      return UINT_MAX; 
   }
   //
   // empty:
   bool BOOST_REGEX_CALL empty()const
   { 
      return (m_pimpl.get() ? 0 != m_pimpl->status() : true); 
   }

   size_type BOOST_REGEX_CALL mark_count()const 
   { 
      return (m_pimpl.get() ? m_pimpl->mark_count() : 0); 
   }

   int status()const
   {
      return (m_pimpl.get() ? m_pimpl->status() : regex_constants::error_empty);
   }

   int BOOST_REGEX_CALL compare(const basic_regex& that) const
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
   bool BOOST_REGEX_CALL operator==(const basic_regex& e)const
   { 
      return compare(e) == 0; 
   }
   bool BOOST_REGEX_CALL operator != (const basic_regex& e)const
   { 
      return compare(e) != 0; 
   }
   bool BOOST_REGEX_CALL operator<(const basic_regex& e)const
   { 
      return compare(e) < 0; 
   }
   bool BOOST_REGEX_CALL operator>(const basic_regex& e)const
   { 
      return compare(e) > 0; 
   }
   bool BOOST_REGEX_CALL operator<=(const basic_regex& e)const
   { 
      return compare(e) <= 0; 
   }
   bool BOOST_REGEX_CALL operator>=(const basic_regex& e)const
   { 
      return compare(e) >= 0; 
   }

   //
   // The following are deprecated as public interfaces
   // but are available for compatibility with earlier versions.
   const charT* BOOST_REGEX_CALL expression()const 
   { 
      return (m_pimpl.get() && !m_pimpl->status() ? m_pimpl->expression() : 0); 
   }
   unsigned int BOOST_REGEX_CALL set_expression(const charT* p1, const charT* p2, flag_type f = regex_constants::normal)
   {
      assign(p1, p2, f | regex_constants::no_except);
      return status();
   }
   unsigned int BOOST_REGEX_CALL set_expression(const charT* p, flag_type f = regex_constants::normal) 
   { 
      assign(p, f | regex_constants::no_except); 
      return status();
   }
   unsigned int BOOST_REGEX_CALL error_code()const
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
   boost::shared_ptr<BOOST_REGEX_DETAIL_NS::named_subexpressions > get_named_subs()const
   {
      return m_pimpl;
   }

private:
   shared_ptr<BOOST_REGEX_DETAIL_NS::basic_regex_implementation<charT, traits> > m_pimpl;
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
   shared_ptr<BOOST_REGEX_DETAIL_NS::basic_regex_implementation<charT, traits> > temp;
   if(!m_pimpl.get())
   {
      temp = shared_ptr<BOOST_REGEX_DETAIL_NS::basic_regex_implementation<charT, traits> >(new BOOST_REGEX_DETAIL_NS::basic_regex_implementation<charT, traits>());
   }
   else
   {
      temp = shared_ptr<BOOST_REGEX_DETAIL_NS::basic_regex_implementation<charT, traits> >(new BOOST_REGEX_DETAIL_NS::basic_regex_implementation<charT, traits>(m_pimpl->m_ptraits));
   }
   temp->assign(p1, p2, f);
   temp.swap(m_pimpl);
   return *this;
}

template <class charT, class traits>
typename basic_regex<charT, traits>::locale_type BOOST_REGEX_CALL basic_regex<charT, traits>::imbue(locale_type l)
{ 
   shared_ptr<BOOST_REGEX_DETAIL_NS::basic_regex_implementation<charT, traits> > temp(new BOOST_REGEX_DETAIL_NS::basic_regex_implementation<charT, traits>());
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

#ifndef BOOST_NO_STD_LOCALE
template <class charT, class traits, class traits2>
std::basic_ostream<charT, traits>& 
   operator << (std::basic_ostream<charT, traits>& os, 
                const basic_regex<charT, traits2>& e)
{
   return (os << e.str());
}
#else
template <class traits>
std::ostream& operator << (std::ostream& os, const basic_regex<char, traits>& e)
{
   return (os << e.str());
}
#endif

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
   reg_expression& BOOST_REGEX_CALL operator=(const reg_expression& that)
   {
      return this->assign(that);
   }

#if !defined(BOOST_NO_MEMBER_TEMPLATES)
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
   reg_expression& BOOST_REGEX_CALL operator=(const std::basic_string<charT, ST, SA>& p)
   {
      this->assign(p);
      return *this;
   }
#else
   explicit reg_expression(const std::basic_string<charT>& p, flag_type f = regex_constants::normal)
   : basic_regex<charT, traits>(p, f)
   { 
   }

   reg_expression& BOOST_REGEX_CALL operator=(const std::basic_string<charT>& p)
   {
      this->assign(p);
      return *this;
   }
#endif

};

#ifdef BOOST_MSVC
#pragma warning (pop)
#endif

} // namespace boost

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

/* basic_regex.hpp
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
*/