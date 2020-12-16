//  (c) Copyright Fernando Luis Cacciola Carballal 2000-2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/numeric/conversion
//
// Contact the author at: fernando_cacciola@hotmail.com
// 
#ifndef BOOST_NUMERIC_CONVERSION_DETAIL_META_FLC_12NOV2002_HPP
#define BOOST_NUMERIC_CONVERSION_DETAIL_META_FLC_12NOV2002_HPP

#include "boost/type_traits/remove_cv.hpp"

#include "boost/mpl/if.hpp"
#include "boost/mpl/eval_if.hpp"
#include "boost/mpl/equal_to.hpp"
#include "boost/mpl/not.hpp"
#include "boost/mpl/and.hpp"
#include "boost/mpl/bool.hpp"
#include "boost/mpl/identity.hpp"

namespace boost { namespace numeric { namespace convdetail
{
   template< class T1, class T2>
   struct equal_to
   {
   #if !defined(__BORLANDC__)
   
       enum { x = ( BOOST_MPL_AUX_VALUE_WKND(T1)::value == BOOST_MPL_AUX_VALUE_WKND(T2)::value ) };
           
       BOOST_STATIC_CONSTANT(bool, value = x);
           
       typedef mpl::bool_<value> type;
       
   #else
   
       BOOST_STATIC_CONSTANT(bool, value = (
             BOOST_MPL_AUX_VALUE_WKND(T1)::value 
               == BOOST_MPL_AUX_VALUE_WKND(T2)::value
           ));
           
       typedef mpl::bool_<(
             BOOST_MPL_AUX_VALUE_WKND(T1)::value 
               == BOOST_MPL_AUX_VALUE_WKND(T2)::value
           )> type;
   #endif
   };
    
// Metafunction:
  //
  //   ct_switch4<Value,Case0Val,Case1Val,Case2Val,Case0Type,Case1Type,Case2Type,DefaultType>::type
  //
  // {Value,Case(X)Val} are Integral Constants (such as: mpl::int_<>)
  // {Case(X)Type,DefaultType} are arbitrary types. (not metafunctions)
  //
  // Returns Case(X)Type if Val==Case(X)Val; DefaultType otherwise.
  //
  template<class Value,
           class Case0Val,
           class Case1Val,
           class Case2Val,
           class Case0Type,
           class Case1Type,
           class Case2Type,
           class DefaultType
          >
  struct ct_switch4
  {
    typedef mpl::identity<Case0Type> Case0TypeQ ;
    typedef mpl::identity<Case1Type> Case1TypeQ ;

    typedef equal_to<Value,Case0Val> is_case0 ;
    typedef equal_to<Value,Case1Val> is_case1 ;
    typedef equal_to<Value,Case2Val> is_case2 ;

    typedef mpl::if_<is_case2,Case2Type,DefaultType> choose_2_3Q ;
    typedef mpl::eval_if<is_case1,Case1TypeQ,choose_2_3Q> choose_1_2_3Q ;

    typedef typename
      mpl::eval_if<is_case0,Case0TypeQ,choose_1_2_3Q>::type
        type ;
  } ;




  // Metafunction:
  //
  //   for_both<expr0,expr1,TT,TF,FT,FF>::type
  //
  // {exp0,expr1} are Boolean Integral Constants
  // {TT,TF,FT,FF} are aribtrary types. (not metafunctions)
  //
  // According to the combined boolean value of 'expr0 && expr1', selects the corresponding type.
  //
  template<class expr0, class expr1, class TT, class TF, class FT, class FF>
  struct for_both
  {
    typedef mpl::identity<TF> TF_Q ;
    typedef mpl::identity<TT> TT_Q ;

    typedef typename mpl::not_<expr0>::type not_expr0 ;
    typedef typename mpl::not_<expr1>::type not_expr1 ;

    typedef typename mpl::and_<expr0,expr1>::type     caseTT ;
    typedef typename mpl::and_<expr0,not_expr1>::type caseTF ;
    typedef typename mpl::and_<not_expr0,expr1>::type caseFT ;

    typedef mpl::if_<caseFT,FT,FF>                    choose_FT_FF_Q ;
    typedef mpl::eval_if<caseTF,TF_Q,choose_FT_FF_Q> choose_TF_FT_FF_Q ;

    typedef typename mpl::eval_if<caseTT,TT_Q,choose_TF_FT_FF_Q>::type type ;
  } ;

} } } // namespace boost::numeric::convdetail

#endif



/* meta.hpp
zTnWna7cmcx1DCbbsqb+Ca7FVWD2wtZGT+jBsVaue7lRr/19G5iHsGfHDtVlfYHJODxf9DOD4wmzEVZ6Ulv+PPQymIx7QLGUScxrmKcwo7Htv/KsBpM5mOtH9Eu+44TJOhH51aIFa7l6XcyBJO6z6uU0x5KBnO8uMBmj8stWl+feBibzs/kmvwCujTA72ZYHPXwYB5iXMPNPV3jPWJhe2Bvrp3xf0BdmLez4ojA/xgHmLWzK543HONYwGffD0W4P/rNUmJuw4Ss7RXM/qPTBv0IbPu+2YnnGdfnIGgKTcWhyM3Im8xrmLmxwY+NpHOv6OfNs9fuYthxPmLzO5cXjEL4LgrkKa2+WsIe1ACbbuTNu5BbWZJiVsLy1m3FdGQ3zEbbnSnJB7iNhpsKGRfhW5j4Ephc2I3/AO+5DYDLP1tUMZ2wvwJxlLnUsbcq8hsn4xdVPusPxhMn87DngcRTXxgY575nb5lJr7e+i5hyXwo+SKnH9g/kJG3/glxPrLsxcWIRPOeZLLMxT2AbPEneZnzBHGfdv97z4Tkex8DfhfTjWSjunpxfNxzoBMxP2feg/bEsaTI51YP313TnWMDlmizz2pbAmK2O2prxPIN8FKfc0uRO3l2PdMOf8uzbpQTxrMkz2r/OdrzVZC2Cewn40TJvO8YSZCvMuvXwcazLMXVjf3B9bcaxhcszOhlb8H2syzEvYxTvpp1gLYNbCyu5crP0eNEzO6R5+vru4H4QVErbge0xhjhmsoMEOwK6ujS/GOd3IiOfb/bDM8hMKsH/C9sHqL2rQkOejRtp82AtrcX2b9u+LKtZsbD7td2Vh7sKMX9Q35r4V5iNselbzCM4xmIcwmzJrHrNmReS0iN+3/dg/mF7Y8oMvCnGvD3MVdm/GqR+MO8xO2IY695rzbA/zElb1Y8IDxhYm+9C95/REvieCOQpbfLXvv4wfzF3YhF8WgzgfYFbCBgyOHMz9IEyO9acZM/h9nK5xzj6MHnWc7+T0MFthT/fm5s9k+MPkuGyOOMKaXAEm+769V/QO7r1hbsLylEqNZp2H+Qr73fQb5/Qixd4NKb2ENUR5XvnlE3kWzYQ5CRvurrvBfIE5y7Feur8K+94kZ98nv5p8n32H+Qlbazy/GfMFJtsy9repI+eKYvc3rGPdHQ3zFuZ0rfVZ7mlhnsIqb203j+/Lles+VBrH8XwI85Bx/10kF+MemXNcHset4d7NA2Ytx+x/DWtwPYLJOLx8ncCzaG2Yo7CFw6/OZdxh7sI+J8dqZy6YjMOFY0PWca7AfIRVSXicxLkC0ws7fmOy9l0PzE3YQ9f4cRwXmLd8XvukBO4xm+Zsy5T2drd5PoJ5CWsc0G8+c16x0v0zmrPvsFzCpnVs5cO4w/yFtVuZdyP3KLBAYfcWWy7k/hqWW1jryEYfGNtmRro8wr4/mK79XB5MPi/LrYgJv4NWbGq1UczBIYp9eX56C/MTJvtX8fOXI9ybKted3Z9qxL2+cp3Fhjo1OdbNc1r730/Gc47BZN8fxDgzP3vA8gkrGd5tFWsITObu4d+79rOGwLyFrWmn/U5TJkz2YZPpEc4VyxY58zOgrnckxxrmKOzRp618j1kFZifMoUBTX57xYA7C0vUN87CGwLyE1fvfsWjmkvK8/ZsrteRaDLMS9sIj4wPjB3MV1n/t9KkcF6V/e+MPTeI8grkIe9WuEmvkD5ibsBljTx9mfYnKOdb/BhZN5XsGmJ+wznnMF3EewWT/tnpo39vHw2yE5c1au5v7LJgczyKrPU5wT6tcd6Vb4eocF+V5PvW3duceBSbHxSWtlZ5nLpinsBqpWdrPLCh2MvjXS+3vMua857YmD1oxX2A=
*/