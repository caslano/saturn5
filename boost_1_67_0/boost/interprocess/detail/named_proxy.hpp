//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_NAMED_PROXY_HPP
#define BOOST_INTERPROCESS_NAMED_PROXY_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

// interprocess/detail
#include <boost/interprocess/detail/in_place_interface.hpp>
#include <boost/interprocess/detail/mpl.hpp>
#include <boost/move/utility_core.hpp>
#ifndef BOOST_INTERPROCESS_PERFECT_FORWARDING
#include <boost/move/detail/fwd_macros.hpp>
#else
#include <boost/move/utility_core.hpp>
#include <boost/interprocess/detail/variadic_templates_tools.hpp>
#endif   //#ifdef BOOST_INTERPROCESS_PERFECT_FORWARDING
#include <boost/container/detail/placement_new.hpp>

#include <cstddef>

//!\file
//!Describes a proxy class that implements named allocation syntax.

namespace boost {
namespace interprocess {
namespace ipcdetail {

#ifdef BOOST_INTERPROCESS_PERFECT_FORWARDING

template<class T, bool is_iterator, class ...Args>
struct CtorArgN : public placement_destroy<T>
{
   typedef bool_<is_iterator> IsIterator;
   typedef CtorArgN<T, is_iterator, Args...> self_t;
   typedef typename build_number_seq<sizeof...(Args)>::type index_tuple_t;

   self_t& operator++()
   {
      this->do_increment(IsIterator(), index_tuple_t());
      return *this;
   }

   self_t  operator++(int) {  return ++*this;   *this;  }

   CtorArgN(Args && ...args)
      :  args_(args...)
   {}

   virtual void construct_n(void *mem
                     , std::size_t num
                     , std::size_t &constructed)
   {
      T* memory      = static_cast<T*>(mem);
      for(constructed = 0; constructed < num; ++constructed){
         this->construct(memory++, IsIterator(), index_tuple_t());
         this->do_increment(IsIterator(), index_tuple_t());
      }
   }

   private:
   template<std::size_t ...IdxPack>
   void construct(void *mem, true_, const index_tuple<IdxPack...>&)
   {  ::new((void*)mem, boost_container_new_t())T(*boost::forward<Args>(get<IdxPack>(args_))...); }

   template<std::size_t ...IdxPack>
   void construct(void *mem, false_, const index_tuple<IdxPack...>&)
   {  ::new((void*)mem, boost_container_new_t())T(boost::forward<Args>(get<IdxPack>(args_))...); }

   template<std::size_t ...IdxPack>
   void do_increment(true_, const index_tuple<IdxPack...>&)
   {
      this->expansion_helper(++get<IdxPack>(args_)...);
   }

   template<class ...ExpansionArgs>
   void expansion_helper(ExpansionArgs &&...)
   {}

   template<std::size_t ...IdxPack>
   void do_increment(false_, const index_tuple<IdxPack...>&)
   {}

   tuple<Args&...> args_;
};

//!Describes a proxy class that implements named
//!allocation syntax.
template
   < class SegmentManager  //segment manager to construct the object
   , class T               //type of object to build
   , bool is_iterator      //passing parameters are normal object or iterators?
   >
class named_proxy
{
   typedef typename SegmentManager::char_type char_type;
   const char_type *    mp_name;
   SegmentManager *     mp_mngr;
   mutable std::size_t  m_num;
   const bool           m_find;
   const bool           m_dothrow;

   public:
   named_proxy(SegmentManager *mngr, const char_type *name, bool find, bool dothrow)
      :  mp_name(name), mp_mngr(mngr), m_num(1)
      ,  m_find(find),  m_dothrow(dothrow)
   {}

   template<class ...Args>
   T *operator()(Args &&...args) const
   {
      CtorArgN<T, is_iterator, Args...> &&ctor_obj = CtorArgN<T, is_iterator, Args...>
         (boost::forward<Args>(args)...);
      return mp_mngr->template
         generic_construct<T>(mp_name, m_num, m_find, m_dothrow, ctor_obj);
   }

   //This operator allows --> named_new("Name")[3]; <-- syntax
   const named_proxy &operator[](std::size_t num) const
   {  m_num *= num; return *this;  }
};

#else //#ifdef BOOST_INTERPROCESS_PERFECT_FORWARDING

////////////////////////////////////////////////////////////////
//    What the macro should generate (n == 2):
//
//    template<class T, bool is_iterator, class P1, class P2>
//    struct Ctor2Arg
//      :  public placement_destroy<T>
//    {
//       typedef bool_<is_iterator> IsIterator;
//       typedef Ctor2Arg self_t;
//
//       void do_increment(false_)
//       { ++m_p1; ++m_p2;  }
//
//       void do_increment(true_){}
//
//       self_t& operator++()
//       {
//          this->do_increment(IsIterator());
//          return *this;
//       }
//
//       self_t  operator++(int) {  return ++*this;   *this;  }
//
//       Ctor2Arg(const P1 &p1, const P2 &p2)
//          : p1((P1 &)p_1), p2((P2 &)p_2) {}
//
//       void construct(void *mem)
//       {  new((void*)object)T(m_p1, m_p2); }
//
//       virtual void construct_n(void *mem
//                                , std::size_t num
//                                , std::size_t &constructed)
//       {
//          T* memory      = static_cast<T*>(mem);
//          for(constructed = 0; constructed < num; ++constructed){
//             this->construct(memory++, IsIterator());
//             this->do_increment(IsIterator());
//          }
//       }
//
//       private:
//       void construct(void *mem, true_)
//       {  new((void*)mem)T(*m_p1, *m_p2); }
//
//       void construct(void *mem, false_)
//       {  new((void*)mem)T(m_p1, m_p2); }
//
//       P1 &m_p1; P2 &m_p2;
//    };
////////////////////////////////////////////////////////////////

#define BOOST_INTERPROCESS_NAMED_PROXY_CTORARGN(N)\
\
template<class T BOOST_MOVE_I##N BOOST_MOVE_CLASS##N >  \
struct CtorArg##N : placement_destroy<T>\
{\
   typedef CtorArg##N self_t;\
   \
   CtorArg##N ( BOOST_MOVE_UREF##N  )\
      BOOST_MOVE_COLON##N BOOST_MOVE_FWD_INIT##N{}\
   \
   virtual void construct_n(void *mem, std::size_t num, std::size_t &constructed)\
   {\
      T* memory      = static_cast<T*>(mem);\
      for(constructed = 0; constructed < num; ++constructed){\
         ::new((void*)memory++) T ( BOOST_MOVE_MFWD##N );\
      }\
   }\
   \
   private:\
   BOOST_MOVE_MREF##N\
};\
//!
BOOST_MOVE_ITERATE_0TO9(BOOST_INTERPROCESS_NAMED_PROXY_CTORARGN)
#undef BOOST_INTERPROCESS_NAMED_PROXY_CTORARGN

#define BOOST_INTERPROCESS_NAMED_PROXY_CTORITN(N)\
\
template<class T BOOST_MOVE_I##N BOOST_MOVE_CLASS##N > \
struct CtorIt##N : public placement_destroy<T>\
{\
   typedef CtorIt##N self_t;\
   \
   self_t& operator++()\
   {  BOOST_MOVE_MINC##N;  return *this;  }\
   \
   self_t  operator++(int) {  return ++*this; *this;  }\
   \
   CtorIt##N ( BOOST_MOVE_VAL##N  )\
      BOOST_MOVE_COLON##N BOOST_MOVE_VAL_INIT##N{}\
   \
   virtual void construct_n(void *mem, std::size_t num, std::size_t &constructed)\
   {\
      T* memory      = static_cast<T*>(mem);\
      for(constructed = 0; constructed < num; ++constructed){\
         ::new((void*)memory++) T( BOOST_MOVE_MITFWD##N );\
         ++(*this);\
      }\
   }\
   \
   private:\
   BOOST_MOVE_MEMB##N\
};\
//!
BOOST_MOVE_ITERATE_0TO9(BOOST_INTERPROCESS_NAMED_PROXY_CTORITN)
#undef BOOST_INTERPROCESS_NAMED_PROXY_CTORITN

//!Describes a proxy class that implements named
//!allocation syntax.
template
   < class SegmentManager  //segment manager to construct the object
   , class T               //type of object to build
   , bool is_iterator      //passing parameters are normal object or iterators?
   >
class named_proxy
{
   typedef typename SegmentManager::char_type char_type;
   const char_type *    mp_name;
   SegmentManager *     mp_mngr;
   mutable std::size_t  m_num;
   const bool           m_find;
   const bool           m_dothrow;

   public:
   named_proxy(SegmentManager *mngr, const char_type *name, bool find, bool dothrow)
      :  mp_name(name), mp_mngr(mngr), m_num(1)
      ,  m_find(find),  m_dothrow(dothrow)
   {}

   #define BOOST_INTERPROCESS_NAMED_PROXY_CALL_OPERATOR(N)\
   \
   BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
   T *operator()( BOOST_MOVE_UREF##N ) const\
   {\
      typedef typename if_c<is_iterator \
         , CtorIt##N <T BOOST_MOVE_I##N BOOST_MOVE_TARG##N> \
         , CtorArg##N<T BOOST_MOVE_I##N BOOST_MOVE_TARG##N> \
         >::type ctor_obj_t;\
      ctor_obj_t ctor_obj = ctor_obj_t( BOOST_MOVE_FWD##N );\
      return mp_mngr->template generic_construct<T>(mp_name, m_num, m_find, m_dothrow, ctor_obj);\
   }\
   //
   BOOST_MOVE_ITERATE_0TO9(BOOST_INTERPROCESS_NAMED_PROXY_CALL_OPERATOR)
   #undef BOOST_INTERPROCESS_NAMED_PROXY_CALL_OPERATOR

   ////////////////////////////////////////////////////////////////////////
   //             What the macro should generate (n == 2)
   ////////////////////////////////////////////////////////////////////////
   //
   // template <class P1, class P2>
   // T *operator()(P1 &p1, P2 &p2) const
   // {
   //    typedef CtorArg2
   //       <T, is_iterator, P1, P2>
   //       ctor_obj_t;
   //    ctor_obj_t ctor_obj(p1, p2);
   //
   //    return mp_mngr->template generic_construct<T>
   //       (mp_name, m_num, m_find, m_dothrow, ctor_obj);
   // }
   //
   //////////////////////////////////////////////////////////////////////////

   //This operator allows --> named_new("Name")[3]; <-- syntax
   const named_proxy &operator[](std::size_t num) const
      {  m_num *= num; return *this;  }
};

#endif   //#ifdef BOOST_INTERPROCESS_PERFECT_FORWARDING

}}}   //namespace boost { namespace interprocess { namespace ipcdetail {

#include <boost/interprocess/detail/config_end.hpp>

#endif //#ifndef BOOST_INTERPROCESS_NAMED_PROXY_HPP

/* named_proxy.hpp
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
*/