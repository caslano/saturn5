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