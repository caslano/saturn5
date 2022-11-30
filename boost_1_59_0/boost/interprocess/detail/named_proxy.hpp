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
                     , std::size_t &constructed) BOOST_OVERRIDE
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
   virtual void construct_n(void *mem, std::size_t num, std::size_t &constructed) BOOST_OVERRIDE\
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
   virtual void construct_n(void *mem, std::size_t num, std::size_t &constructed) BOOST_OVERRIDE\
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