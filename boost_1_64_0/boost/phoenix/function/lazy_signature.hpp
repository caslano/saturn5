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
Uy7Qwx8DQBewC9gZTAHTzXEGmAb8WCZ/bnA1uBJcDPzYhmvAVeB34DWwFrwJ3gHdsV19QS+ws2/HQBEoBjNBOZgOZoNV4Brgr3E/B14GH4NngO9nrwNbdUOmoCPoDrYDg3IcOf5TT5z7PJm1VuRvl2OFHnXkLIJy9j/YlblH8nx5gStVLH58erErR7zuSKeernx7jyc/1Xhy3EJHdrrHkUvvcqTPAa5028qRrDaenLvUlUMecuWNHE+u+9yRkzp5cuA8T5Z2cGWzTq4cercnP9/tSt8Nnnz2nCOPVnvS7zBP2s515fpvHZl+jCt3X+7K8zgORy9w5FfdOL+9IxM9V976syt/bse9d3EkYxhtcZQj23Gf70h/LnU6HfjHK7shV/AieA28D9aBnjugY2BfMBOUgOU7cA04G1wAVoFLwOU7kA94AawBb4LV4DXwBlgHtiLQqTeYDU5ezpr+YmRzlidXUr4rb6A+x3vy55Ge3Po9e7S9zfhxpyMvnOPKieLKDddQv4Wu9Djdk4vfduWrTzzpO5s2uYwYqi+RWb0na/ej/Q93pQ/xFQu/8mTBs560GeJK9bbo0CHowVOeHH6VSMaB3GewJz/cxDj2W0euKqYfvezJvDcdefldT06lHdMfYtxj8H9ujCOD93Rlr7Gu/EBbtfnBk9dmurL2C77l/RtX7rwJ2Q525E+v0pdWOXJrhid9enqSeYcrsV08eZPr18U9GbqTK9cMd2TBekf+sgYfZIQrb9Y5ck1fR+5jTNrjb660wy+5P8Z9h7ny6tP0o7cdeZyxdtLljqyg3H/82ZPsaZ4cgH5t9Tp+4XxkArfbhZ5sg7w++diRKVn0p5Md2ZdynbOfKyPKPZnzjCuZfVxZvQfy7+1J6UxPtupKv92T9qwT2WwzR475iyNrKfdRy2m7DxxZtcqjszvyI05H6TMiP2+HPnCfPV90pHeuI7uf6MnNy/DBSLt0mCcd9kf236Fvx3gy5RNXVnZHJtTp2KmOfDXZk1eRQ/0Bnvz6NuS1jUeD4H8c6EjeQ56MqfAkpx7uPlfG7+VJ2k+OfPaTSwLK+DP2a50rC3E8jzjIlfa1jozzkO1Vrmxb48jH7+EHEfidW+VKHpvJvo4TdwxymziAGIzvXelAm3Q70ZExfLTzkYmufLizJyfQT75t64n7AJEVh7nSkz7TrRT5H46suFfRw67My3Lk+nfY0+xIR04/z5EP0IurT8QuTiXNgyJLilx5Bc/jyGdFCj1H7sgjHmSkIyV7ubL/JFdOHezKZzXYMpyx27735OyutO0QT9JZ9Lye49o78C3bujKQv49515WJf0aeP2Bn6QPrsRdb30mfu573/d8XeeIxJ/iO5wfgxR09uZf+v+48T+6ocmTeNrTd0fhV1Y48eR71PN6RIZno/QWufP0TuorN2e1DRw49knrtjW6ySf6P2LCZR7vyyQHsK7hU5Ev00Y1jf9uhP4e6MqDAk3zktGGNJ1M3w/7fLbJhpStdXnBka9KtftWRs99zZaddKW8VdqoL9o7+feDOjlw7zpUd1zkSH8u9T3FkJH2r8nJPfryJJr/Uk8pdPelOH6jfF7sx1pG70c1j96FOlHmr2x3p/ldXemfRtmd6stPO2P9HuJZzQ37PtSd5Mhyf/C/7e/LJavT1YE+2fM2TK9CTJXB7n4DNpb0eXEC//D1jw1ue1N7iyHXozYZBnlz2rUgddrxdR+r9I334ZcaFXR25bQtH1pzlyi7pjpz8PGMe9z6XtsvHvvY/GntwKu11jSf1V2Bv6Ovzsdfb12Cvyh2pWoHtq2UcSePeXV05Oh07OYVzF+Ohfu3KH9Gnx+kbu9LOt4zBjtOXj70aO/Y=
*/