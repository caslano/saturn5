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
u+UaLt8Jp6p67zOO9300GZielisMnOYZ1bQ8LZQjaXm6yUnLaJDnm+0c9obieKbO8e+oPcvUVyXqyK53tobJN1ezqlf2rqzU9Yl4tC4WjxJ2jo6xLYmwc03MHWJiOp9nx3BchHuHNRxrDc0d+3pIgkJ9j+uFAQxzFhW8jzgMxwEE+XGxhaOex//jIB6LNAXb/0sCHExJnktZFcD8i41VT/hdl4ZxaSyKnNUBDg+RuBrw+dAeBw9+k770ck0vfekVoqdjvWaXFBSqe48Fr8z3feR56ACGhmbG1hiY3F//ExtGu5wwrFcHcZ6vuCagV9f7rQ1gWIr4fdcamP8+dHudgpeVlpRjc8durzcwz3rPe48NHCOKbm80MP3smZvseAoJ/P51JodXPETQj/UhOPlCftxs5ci34S1WPBbxwrDBisNcYIry5VYDl7OTb/MwnNXRbTi3m5g/jrnDwKSNulPF5LRGTI+77JjW1t5t52jr9++xc7j7I869AY46geCN+e9rgUNTJeTX/SqPbT98zIS/D+UBlcPdKsWc9zOreMCe85COYfnF/cyqXsLmzws9ouKKvedRVc8VuHExhJTj81MDN+0rj+kc3ABfXx3zvy8eD+JqJeY4bzQ4mCDo/gkDU4sCcZ40OVIUmPOUlcMViPN5k8FR01L2sD0dzkMOzm0bHEpa/+xnFTdtJMjZbHC4w6mSduEZnWN82z+r4oqt5DlVr9hEnlf1Sh/ygqqXoQFiL1qw2iSl6UsalrKkKc+N6zwjvV42cDMtXtE5Rlq8quKKnWOrqhc7B2K/0LA036ZF2GsqJvYMmg8XjOyNmh2ZwrvNxlHsj780cLEL+3u7TY7fr71pYFj3MV/eMjDDVovjn1/ZeGQvr8GTHgrEpvVrK5e/xWc31i/mMftvDB7XIfZnux2X0Tbz3rbzZMTNcXjH5Jk2WE7z35pc1Q5Ld0WbHNUWS3PuBkfOHnjPwLD+YVjfNzAox0ZyU/x3WLlqclO5/73Pg6P5lf3gf1D1mFek/yCoryf9h6peaUv+qOqVc+D+JPqKkrJCdXEt4n82cW0O7yMTx1Cqd2l9HMKh/auUpp+EchobGqLxNJ3YT9xPW+Z65ld8906TqwyDKY8+a4ETpWPS8b1/CePx2uu0ki6fh3BpZS+9d1cYpzGOg75ohPz6q8mT+8pSxPkihENpTJy/hXIa6lIc7i9DOJymGO6v7Bz1awt5X9t5GGzKT+J9Y+fR6AyJlO+7W+JRACNeGfl7S1zOMO+uzn+0yJV67d9rbed79Qbfv8fOkeKs7J3+p51L6205jb5riQN9TjJN3657TZ66bpTuut43jJN094Sn1T3sGXYuCGYhrT0I53Cx4f33Iby6RGJZY5JLs7f+oEUullj0s1MIL95Yr1Yj5HY2uZ5pUi27GO997FweQfDe/BY5uOEP29CuFl5MOeemm4n7cwTdLViysSGZSEXBD1huymf8Z5k8/PxW6/a+YZxIdTzKnB52DreXlI77hXEouXGhV80ySqPsEK5kDvmZE8bjg1X4sAMMY087l+sU+dfLyrHXv94mV53tQ04fO4dqHvvT18YJ1ON+Vo5Zj/vbeFKPkfMDk6NuQkHOADvHK0PI2d/kqNuBkDPQzqEsZ84PbZxAnTnAyjHrzIE6T+6w5DozyIY30N6mH5kYtxvkdnAAV8czBwUwWWsk+/6HmByuH+THwQau9nnEOcTkSH/HZeVQg2P0dcgbavCMfg7rxDCTZ/ZxHMfhJlcbFx4WxKVsIj4iiEufgfEfaeBqf8F3dhsco69Av44weWo/geEZZXK4zJEfo0Nx2ceeq3PoaJo6Tjg+Z2CMwalZ5o3Bx+qYf6fHkZo=
*/