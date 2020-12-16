////////////////////////////////////////////////////////////////////////////
// lazy smart.hpp
//
// Build lazy functoid traits for Phoenix equivalents for FC++
//
// These are equivalents of the Boost FC++ functoid traits in smart.hpp
//
// I have copied the versions for zero, one, two and three arguments.
//
/*=============================================================================
    Copyright (c) 2000-2003 Brian McNamara and Yannis Smaragdakis
    Copyright (c) 2001-2007 Joel de Guzman
    Copyright (c) 2015 John Fletcher

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_PHOENIX_FUNCTION_LAZY_SMART
#define BOOST_PHOENIX_FUNCTION_LAZY_SMART

namespace boost {
    namespace phoenix {
      namespace fcpp {

//////////////////////////////////////////////////////////////////////
// Feature: Smartness
//////////////////////////////////////////////////////////////////////
// If F is smart, then we can refer to these entities:
//
//    functoid_traits<F>::template accepts<N>::args
//       A bool which says whether F can accept N arguments
//
//    functoid_traits<F>::max_args
//       An int which says what the most arguments F can accept is
//
//    functoid_traits<F>::template ensure_accepts<N>::args()
//       A no-op call that compiles only if F can accept N args
//
// We use traits so that if you happen to ask a non-smart functoid these
// questions, you will hopefully get a literate error message.

struct SmartFunctoid {};

// We add crazy identifiers to ensure that users don't accidentally talk
// to functoids directly; they should always be going through the traits
// class to ask for info.
struct smart_functoid0 : public SmartFunctoid {
   template <class Dummy, int i> struct crazy_accepts {
      static const bool args = false;
   };
   template <class Dummy> struct crazy_accepts<Dummy,0> {
      static const bool args = true;
   };
   static const int crazy_max_args = 0;
};

struct smart_functoid1 : public SmartFunctoid {
   template <class Dummy, int i> struct crazy_accepts {
      static const bool args = false;
   };
   template <class Dummy> struct crazy_accepts<Dummy,1> {
      static const bool args = true;
   };
   static const int crazy_max_args = 1;
};

struct smart_functoid2 : public SmartFunctoid {
   template <class Dummy, int i> struct crazy_accepts {
      static const bool args = false;
   };
   template <class Dummy> struct crazy_accepts<Dummy,1> {
      static const bool args = true;
   };
   template <class Dummy> struct crazy_accepts<Dummy,2> {
      static const bool args = true;
   };
   static const int crazy_max_args = 2;
};

struct smart_functoid3 : public SmartFunctoid {
   template <class Dummy, int i> struct crazy_accepts {
      static const bool args = false;
   };
   template <class Dummy> struct crazy_accepts<Dummy,1> {
      static const bool args = true;
   };
   template <class Dummy> struct crazy_accepts<Dummy,2> {
      static const bool args = true;
   };
   template <class Dummy> struct crazy_accepts<Dummy,3> {
      static const bool args = true;
   };
   static const int crazy_max_args = 3;
};


namespace impl {
   template <class F, bool b> struct NeededASmartFunctoidButInsteadGot {};
   template <class F> struct NeededASmartFunctoidButInsteadGot<F,true> {
      typedef F type;
   };
   template <bool b> struct Ensure;
   template <> struct Ensure<true> {};
} // end namespace impl

template <class MaybeASmartFunctoid>
struct functoid_traits {
  typedef typename boost::remove_reference<MaybeASmartFunctoid>::type MaybeASmartFunctoidT;
   typedef
      typename impl::NeededASmartFunctoidButInsteadGot<MaybeASmartFunctoidT,
         boost::is_base_and_derived<SmartFunctoid,
         MaybeASmartFunctoidT>::value>::type F;
      template <int i> struct accepts {
      static const bool args = F::template crazy_accepts<int,i>::args;
   };
   template <int i> struct ensure_accepts {
      static const bool ok = F::template crazy_accepts<int,i>::args;
      inline static void args() { (void) impl::Ensure<ok>(); }
   };
   static const int max_args = F::crazy_max_args;
};

// These can be used to make functoids smart without having to alter
// code elsewhere. These are used instead of boost::phoenix::function
// to declare the object.
template <typename F>
struct smart_function0 : public smart_functoid0,
                         public boost::phoenix::function<F>
{ };

template <typename F>
struct smart_function1 : public smart_functoid1,
                         public boost::phoenix::function<F>
{
  typedef F type;
};

template <typename F>
struct smart_function2 : public smart_functoid2,
                         public boost::phoenix::function<F>
{ };

template <typename F>
struct smart_function3 : public smart_functoid3,
                         public boost::phoenix::function<F>
{ };
      }
    }
}


#endif

/* lazy_smart.hpp
PjLErp1SRVvTX19e48gA2un7Kz0ZfBfjys2uXDvKlV0LXdluO1cuBz3/6Mqi4zyZuLknFR8jr7l8l7ICe7ATdf2Zce1Xrqy62JG99uFdiBzs8dOOfIk+zNrDlclM0t6v5h5/o75fI0fudzjyzClyZOoHrpxBHueBA7CL089B3xnrL3rBlXtn0ebke+YEN8j30O6ejDoAvbzOk7/W04fO8WTHHR254TVHnv2KPv+lKweez9+/Yc2tCDsw25NhPzFecm6P8Z58yvWzN3elO/z1syjrTvTp6xw5Afv++9c9eT6X8acTY+n+jvTbBbnTFgfdTZ3Pxz6vot+Xu3I1NrOsCjv1lCtT0JeqV6jHZ54c8gbrH+3Qm7PRTezcMx95MqmvJ+VraEPG4ooOxH8dRlomPp3nUK41pLmNtmZs3QEZ7bweGV9NGsp4/0rq4ffRzq78zBhxM3lvdpgjF2N37sKW5b6IH4M97Ypdemy+K7vvig80Gjs9zpNj6QufYmtew2YffmmiH3Vegj8yHLt9pCfPZmNbznBk863RR+ZJQw+gPC96cmQH+vxUkU7o0yMfcd0l6NvOrmT0x64McKVgD0d2eRX7Qht+87Irhy+gfyCvP9/H+P+dI5+gV5dti57+BT/heUdO3Zs5fAl+w2P4g/Sle/dlTLzHlXtGu3Ij9umWAfS3AtppoSftb+a7S5Ttywrq+K0r0152pK4dZWD8GYesN2cs+eEjV27Cbs+9g/7YnrcGGLuPp08NIe05Vzqy5/WufEed79kFO7WOefcGVxx05iH048cVrgyvQ//vEWlX6Ejbxx25JQMfinbuezXloHxHcM0LjIu7jfLkovsdyYm78uKtnpQdQZ9agn0bjT+xmHbojd3f4Mjer+MnUrcl9LPbrvLk9j+48tHltOfpzLPZwLU9fW6dv85wDPX/Clme5chxd2Hzezky6RFXas715O2HHJkwx5VRuwmZ4auM5ZkCOn3c7o58cTx9zNdb/IVBp+Ez7Y7/ep8jI95hrME+f8G4MuMN7Paz3Ad9z/iTJ7fd78owyttjuCe7boP+vM14+4Inv12PDcXvu4523vl2T1ZOd+UJyv3xoYyH5FGQyRrEga6UtnfkyDccufpjxqhH0VF8ocwF2Nx7aKPLXLliHL7SBOTPotDk7T155NfozYOurEN+HQagu6AtaFdHP1jtyeiYK8v7e5L7F9Z9tnFliy0Zk5D/QYx7pzPGZqNbT3OsWebKBfBZtZ7cxzhxMnpZQz/MJ69iUAhKwP7gudHkhy+w5WWOjD4EXwG7MRK7/MoUR47KxDbuhE2az3iL7zW4B37vl+jlYOqB7u33OLZpFWMWfToHu3j0ja7M34c093tyNLbv+tPwNXYiz2sd+TN+xzzud9ciVzz61fmMSy8xLp11nSs3z3DlqVJHxjJ23ZblyeXo3G/29OSu/swz5mF7P3flS/Sn27u8xUO7DOS+f5zM2Pq8K4Mo82p8qG3wnX99NLp3LjZkCWPCQRLI5wz8+WL6wfoh+Bz4dXNfp72fcOT56/Hh/sSYvy39t4sjW6BPVWtoS3zW9G886XEq/YbyXvA35PUsbfUcPgL98g8xTx5eiA+T68pB+Pdz0IE0dP/OQYw/X7mSRfpRv8M2ow/96TPzqN/mXzjyxFuk+RxfGftw2YeM8deS/nD8vja00y2urN+Araij33fHR/3ekbQ36RvMP25i/B11EzzXfLIdYwV2pE8n+vt1jJtrGffwLc9i/Lx8pSNbou8/voyPhY87hnt1exOZ0K/fL6MOh7hSt5x2OAUfdDvG+itd+aCa/WYP9eSSwbQhfeCq+fh8J+PfOI6cvxz7Rv2++wP+Wz/kNwE=
*/