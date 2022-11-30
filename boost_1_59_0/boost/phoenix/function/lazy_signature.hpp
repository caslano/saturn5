////////////////////////////////////////////////////////////////////////////
// lazy_signature.hpp
//
// Build signature structs for Phoenix equivalents for FC++
// which are located in lazy_prelude.hpp
//
// These are not direct equivalents of the Boost FC++ structs.
// This file has to be included after lazy_list.hpp
//
// Implemented so far:
//
//   RTEFH    == ReturnTypeEnumFromHelper    (used in enum_from, enum_from_to)
//   RTFD     == ReturnTypeFunctionDelay     (used in repeat)
//   RTFFX    == ReturnTypeFunctoidFwithX     (used in thunk1)
//   RTFFXY   == ReturnTypeFunctoidFwithXandY (used in thunk2)
//   RTFFXYZ  == ReturnTypeFunctoidFwithXandYandZ (used in thunk3)
//   RTF      == ReturnTypeF                  (used in ptr_to_fun0)
//   RTFX     == ReturnTypeFwithX          (used in ptr_to_fun, ptr_to_mem_fun)
//   RTFXY    == ReturnTypeFwithXandY      (used in ptr_to_fun, ptr_to_mem_fun)
//   RTFXYZ   == ReturnTypeFwithXandYandZ  (used in ptr_to_fun, ptr_to_mem_fun)
//   RTFWXYZ  == ReturnTypeFwithWandXandYandZ (used in ptr_to_fun)
//   RTFGHX   == ReturnTypeFandGandHwithX    (used in compose)
//   RTFGHXY  == ReturnTypeFandGandHwithXY   (used in compose)
//   RTFGHXYZ == ReturnTypeFandGandHwithXYZ  (used in compose)
//   RTFGX    == ReturnTypeFandGwithX        (used in compose)
//   RTFGXY   == ReturnTypeFandGwithXY       (used in compose)
//   RTFGXYZ  == ReturnTypeFandGwithXYZ      (used in compose)
//   RTFL     == ReturnTypeFunctionList      (used in map)
//   RTAB     == ReturnTypeListAListB        (used in zip)
//   RTZAB    == ReturnTypeZipListAListB     (used in zip_with)
//
////////////////////////////////////////////////////////////////////////////
/*=============================================================================
    Copyright (c) 2000-2003 Brian McNamara and Yannis Smaragdakis
    Copyright (c) 2001-2007 Joel de Guzman
    Copyright (c) 2015 John Fletcher

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_PHOENIX_FUNCTION_LAZY_SIGNATURE
#define BOOST_PHOENIX_FUNCTION_LAZY_SIGNATURE

namespace boost {

  namespace phoenix {

    namespace impl {

      //template <class T> struct remove_RC; in lazy_operator.hpp

      // RTEFH == ReturnTypeEnumFromHelper
      template <class T>
      struct RTEFH
      {
          typedef typename UseList::template List<T>::type LType;
          typedef typename result_of::ListType<LType>::
                           delay_result_type type;
      };

      // RTFD == ReturnTypeFunctionDelay (used in repeat)
      template <class T>
      struct RTFD {
          typedef typename remove_RC<T>::type TTT;
          typedef typename UseList::template List<TTT>::type LType;
          typedef typename result_of::ListType<LType>::
                           delay_result_type type;
      };


      //   RTFFX   == ReturnTypeFunctoidFwithX   (used in thunk1)
      template <class F,class X>
      struct RTFFX {
          typedef typename remove_RC<F>::type FType;
          typedef typename remove_RC<X>::type XType;
          typedef typename boost::result_of<FType(XType)>::type FR;
          typedef typename boost::result_of<FR()>::type RR;
          typedef typename remove_RC<RR>::type RType;
          typedef RType type;
      };

      //   RTFFXY   == ReturnTypeFunctoidFwithXandY   (used in thunk2)
      template <class F,class X,class Y>
      struct RTFFXY {
          typedef typename remove_RC<F>::type FType;
          typedef typename remove_RC<X>::type XType;
          typedef typename remove_RC<Y>::type YType;
          typedef typename boost::result_of<FType(XType,YType)>::type FR;
          typedef typename boost::result_of<FR()>::type RR;
          typedef typename remove_RC<RR>::type RType;
          typedef RType type;
      };

      //   RTFFXYZ  == ReturnTypeFunctoidFwithXandYandZ  (used in thunk3)
      template <class F,class X,class Y,class Z>
      struct RTFFXYZ {
          typedef typename remove_RC<F>::type FType;
          typedef typename remove_RC<X>::type XType;
          typedef typename remove_RC<Y>::type YType;
          typedef typename remove_RC<Z>::type ZType;
          typedef typename boost::result_of<FType(XType,YType,ZType)>::type FR;
          typedef typename boost::result_of<FR()>::type RR;
          typedef typename remove_RC<RR>::type RType;
          typedef RType type;
      };

      //   RTF   == ReturnTypeF     (used in ptr_to_fun0)
      template <class F>
      struct RTF {
          typedef typename remove_RC<F>::type FType;
          typedef typename boost::result_of<FType()>::type FR;
          typedef typename remove_RC<FR>::type RType;
          typedef RType type;
      };

      //   RTFX   == ReturnTypeFwithX     (used in ptr_to_fun)
      template <class F,class X>
      struct RTFX {
          typedef typename remove_RC<F>::type FType;
          typedef typename remove_RC<X>::type XType;
          typedef typename boost::result_of<FType(XType)>::type FR;
          typedef typename remove_RC<FR>::type RType;
          typedef RType type;
      };

      //   RTFXY  == ReturnTypeFwithXandY     (used in ptr_to_fun)
      template <class F,class X,class Y>
      struct RTFXY {
          typedef typename remove_RC<F>::type FType;
          typedef typename remove_RC<X>::type XType;
          typedef typename remove_RC<Y>::type YType;
          typedef typename boost::result_of<FType(XType,YType)>::type FR;
          typedef typename remove_RC<FR>::type RType;
          typedef RType type;
      };

      //   RTFXYZ  == ReturnTypeFwithXandYandZ  (used in ptr_to_fun)
      template <class F,class X,class Y,class Z>
      struct RTFXYZ {
          typedef typename remove_RC<F>::type FType;
          typedef typename remove_RC<X>::type XType;
          typedef typename remove_RC<Y>::type YType;
          typedef typename remove_RC<Z>::type ZType;
          typedef typename boost::result_of<FType(XType,YType,ZType)>::type FR;
          typedef typename remove_RC<FR>::type RType;
          typedef RType type;
      };

      //   RTFWXYZ  == ReturnTypeFwithWandXandYandZ  (used in ptr_to_fun)
      template <class F,class W,class X,class Y,class Z>
      struct RTFWXYZ {
          typedef typename remove_RC<F>::type FType;
          typedef typename remove_RC<W>::type WType;
          typedef typename remove_RC<X>::type XType;
          typedef typename remove_RC<Y>::type YType;
          typedef typename remove_RC<Z>::type ZType;
          typedef typename boost::result_of<FType(WType,XType,YType,ZType)>::
                  type FR;
          typedef typename remove_RC<FR>::type RType;
          typedef RType type;
      };

      //   RTFGHX  == ReturnTypeFandGandHwithX (used in compose)
      template <class F,class G,class H,class X>
      struct RTFGHX {
          typedef typename remove_RC<F>::type FType;
          typedef typename remove_RC<G>::type GType;
          typedef typename remove_RC<H>::type HType;
          typedef typename remove_RC<X>::type XType;
          typedef typename boost::result_of<GType(XType)>::type GR;
          typedef typename boost::result_of<GR()>::type GRR;
          typedef typename remove_RC<GRR>::type GRType;
          typedef typename boost::result_of<HType(XType)>::type HR;
          typedef typename boost::result_of<HR()>::type HRR;
          typedef typename remove_RC<HRR>::type HRType;
          typedef typename boost::result_of<FType(GRType,HRType)>::type FR;
          typedef typename boost::result_of<FR()>::type RR;
          typedef typename remove_RC<RR>::type RType;
          typedef RType type;
      };

      //   RTFGHXY == ReturnTypeFandGandHwithXY (used in compose)
      template <class F,class G,class H,class X,class Y>
      struct RTFGHXY {
          typedef typename remove_RC<F>::type FType;
          typedef typename remove_RC<G>::type GType;
          typedef typename remove_RC<H>::type HType;
          typedef typename remove_RC<X>::type XType;
          typedef typename remove_RC<Y>::type YType;
          typedef typename boost::result_of<GType(XType,YType)>::type GR;
          typedef typename boost::result_of<GR()>::type GRR;
          typedef typename remove_RC<GRR>::type GRType;
          typedef typename boost::result_of<HType(XType,YType)>::type HR;
          typedef typename boost::result_of<HR()>::type HRR;
          typedef typename remove_RC<HRR>::type HRType;
          typedef typename boost::result_of<FType(GRType,HRType)>::type FR;
          typedef typename boost::result_of<FR()>::type RR;
          typedef typename remove_RC<RR>::type RType;
          typedef RType type;
      };

      //   RTFGHXYZ == ReturnTypeFandGandHwithXYZ (used in compose)
      template <class F,class G,class H,class X,class Y,class Z>
      struct RTFGHXYZ {
          typedef typename remove_RC<F>::type FType;
          typedef typename remove_RC<G>::type GType;
          typedef typename remove_RC<H>::type HType;
          typedef typename remove_RC<X>::type XType;
          typedef typename remove_RC<Y>::type YType;
          typedef typename remove_RC<Z>::type ZType;
          typedef typename boost::result_of<GType(XType,YType,ZType)>::type GR;
          typedef typename boost::result_of<GR()>::type GRR;
          typedef typename remove_RC<GRR>::type GRType;
          typedef typename boost::result_of<HType(XType,YType,ZType)>::type HR;
          typedef typename boost::result_of<HR()>::type HRR;
          typedef typename remove_RC<HRR>::type HRType;
          typedef typename boost::result_of<FType(GRType,HRType)>::type FR;
          typedef typename boost::result_of<FR()>::type RR;
          typedef typename remove_RC<RR>::type RType;
          typedef RType type;
      };

      //   RTFGX   == ReturnTypeFandGwithX     (used in compose)
      template <class F,class G,class X>
      struct RTFGX {
          typedef typename remove_RC<F>::type FType;
          typedef typename remove_RC<G>::type GType;
          typedef typename remove_RC<X>::type XType;
          typedef typename boost::result_of<GType(XType)>::type GR;
          typedef typename boost::result_of<GR()>::type GRR;
          typedef typename remove_RC<GRR>::type GRType;
          typedef typename boost::result_of<FType(GRType)>::type FR;
          typedef typename boost::result_of<FR()>::type RR;
          typedef typename remove_RC<RR>::type RType;
          typedef RType type;
      };

      //   RTFGXY  == ReturnTypeFandGwithXY    (used in compose)
      template <class F,class G,class X,class Y>
      struct RTFGXY {
          typedef typename remove_RC<F>::type FType;
          typedef typename remove_RC<G>::type GType;
          typedef typename remove_RC<X>::type XType;
          typedef typename remove_RC<Y>::type YType;
          typedef typename boost::result_of<GType(XType,YType)>::type GR;
          typedef typename boost::result_of<GR()>::type GRR;
          typedef typename remove_RC<GRR>::type GRType;
          typedef typename boost::result_of<FType(GRType)>::type FR;
          typedef typename boost::result_of<FR()>::type RR;
          typedef typename remove_RC<RR>::type RType;
          typedef RType type;
      };

      //   RTFGXYZ == ReturnTypeFandGwithXYZ   (used in compose)
      template <class F,class G,class X,class Y,class Z>
      struct RTFGXYZ {
          typedef typename remove_RC<F>::type FType;
          typedef typename remove_RC<G>::type GType;
          typedef typename remove_RC<X>::type XType;
          typedef typename remove_RC<Y>::type YType;
          typedef typename remove_RC<Z>::type ZType;
          typedef typename boost::result_of<GType(XType,YType,ZType)>::type GR;
          typedef typename boost::result_of<GR()>::type GRR;
          typedef typename remove_RC<GRR>::type GRType;
          typedef typename boost::result_of<FType(GRType)>::type FR;
          typedef typename boost::result_of<FR()>::type RR;
          typedef typename remove_RC<RR>::type RType;
          typedef RType type;
      };

      // This is the way to make the return type for
      // map(f,l). It is used four times in the code
      // so I have made it a separate struct.
      // RTFL == ReturnTypeFunctionList
      template <class F,class L>
      struct RTFL {
           typedef typename remove_RC<F>::type Ftype;
           typedef typename result_of::ListType<L>::tail_result_type
                                   Ttype;
           typedef typename result_of::ListType<L>::value_type Vtype;
           // NOTE: FR is the type of the functor.
           typedef typename boost::result_of<Ftype(Vtype)>::type FR;
           // NOTE: RR is the type returned, which then needs
           // reference and const removal.
           typedef typename boost::result_of<FR()>::type RR;
           typedef typename remove_RC<RR>::type Rtype;
           typedef typename boost::remove_reference<L>::type LL;
           typedef typename LL::template cons_rebind<Rtype>::delay_type
                   type;
      };

      // RTAB == ReturnTypeListAListB
      template <typename LA, typename LB>
      struct RTAB {
                  typedef typename result_of::ListType<LA>::tail_result_type
                                   LAtype;
                  typedef typename result_of::ListType<LB>::tail_result_type
                                   LBtype;
                  typedef typename result_of::ListType<LA>::value_type VAA;
                  typedef typename boost::remove_const<VAA>::type VAtype;
                  typedef typename result_of::ListType<LB>::value_type VBB;
                  typedef typename boost::remove_const<VBB>::type VBtype;
                  typedef typename boost::result_of<Make_pair(VAtype,VBtype)>
                                  ::type FR;
                  typedef typename boost::result_of<FR()>::type RR;
                  typedef typename remove_RC<RR>::type Rtype;
                  typedef typename boost::remove_reference<LA>::type LLA;
                  typedef typename LLA::template cons_rebind<Rtype>::type type;
      };


      // RTZAB == ReturnTypeZipListAListB
      template <typename Z, typename LA, typename LB>
      struct RTZAB {
                  typedef typename remove_RC<Z>::type Ztype;
                  typedef typename result_of::ListType<LA>::tail_result_type
                                   LAtype;
                  typedef typename result_of::ListType<LB>::tail_result_type
                                   LBtype;
                  typedef typename result_of::ListType<LA>::value_type VAtype;
                  typedef typename result_of::ListType<LB>::value_type VBtype;
                  typedef typename boost::result_of<Ztype(VAtype,VBtype)>::type
                                   FR;
                  typedef typename boost::result_of<FR()>::type RR;
                  typedef typename remove_RC<RR>::type Rtype;
                  typedef typename boost::remove_reference<LA>::type LLA;
                  typedef typename LLA::template cons_rebind<Rtype>::type type;
      };

    }
  }
}

#endif

/* lazy_signature.hpp
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
*/