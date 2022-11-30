////////////////////////////////////////////////////////////////////////////
// lazy prelude.hpp
//
// Build lazy operations for Phoenix equivalents for FC++
//
// These are equivalents of the Boost FC++ functoids in prelude.hpp
//
// Usage:  All of these are functors which need various numbers of arguments.
//         Those can be supplied as real arguments or as Phoenix arguments.
//         Execution will happen when all the arguments are supplied.
// e.g.
//         take(2,list)()  or  take(2,arg1)(list)
//
// Implemented so far:
//
// id (moved back to operators.hpp)
//
// A lot of what comes here uses the list type, so that will be needed first.
//
// Now that list<T> is available I can start to build things here.
//
//
// until(pred,f,start)         - if pred(start) is true, return start
//                               apply value = f(start)
//                               apply value = f(value)
//                               until pred(value) is true
//                               return value
//
// The predicate argument pred must be a lazy function taking one argument
// and returning bool.
// This can be a lazy function with an argument already.
// This has to be declared before the call to until.
// The type can be declated using Predicate as in this example:
//
//    Predicate<int>::type f(greater(arg1,10));
//    std::cout << until(f, inc, 1)() << std::endl;
//
// until2(pred,f,start,value2) - if pred(start,value2) is true, return start
//                               apply value1 = f(start)
//                               apply value1 = f(value1)
//                               until pred(value1,value2) is true
//                               return value1
//
// NOTE: until2 has been defined because this code does not support
//       FC++ currying, so that a partial function cannot be passed
//       as an argument. This provides a way of passing a second parameter.
//       There is now the option to use Predicate<T> as shown above.
//
// odd(n)     true if n is odd
// even(n)    true if n is even
//
// last(list)
// all_but_last(list)
// at(list,n)
// length(list)
// filter(pred,list)
// iterate(function,value)
// repeat(value)
// take(n,list)
// drop(n,list)
// enum_from(x)
// enum_from_to(x,y)
//
////////////////////////////////////////////////////////////////////////////
// Interdependence:
// The old Boost FC++ has a set of headers which interelate and call each
// other in a complicated way. I am going to document the interdependence
// of the files here. I will then make sure that they are called correctly
// starting from this file. John Fletcher. February 2015.
////////////////////////////////////////////////////////////////////////////
// BoostFC++ header sequence:
// 
// prelude.hpp   -> list.hpp (optinally monad.hpp at end)
// list.hpp      -> reuse.hpp
// reuse.hpp     -> function.hpp
// function.hpp  -> ref_count.hpp operator.hpp
// ref_count.hpp -> config.hpp boost headers and RefCountType definition
// operator.hpp  -> lambda.hpp
// lambda.hpp    -> full.hpp (use of lambda internals is optional)
// full.hpp      -> smart.hpp curry.hpp pre_lambda.hpp (optionally full4.hpp)
// smart.hpp     -> signature.hpp
// curry.hpp     -> signature.hpp
// signature.hpp -> config.hpp
//
////////////////////////////////////////////////////////////////////////////
// Proposed order in lazy_prelude.hpp
// on the basis that files need what they call.
//
// lazy_config.hpp    (If needed)* probably not needed.
// lazy_signature.hpp (If needed)*
// lazy_smart.hpp     (If needed)*
// lazy_curry.hpp     (If needed)*
// lazy_full.hpp      (If needed)*
// lazy_operator.hpp  (absorb definition of RefCountType)
// lazy_function.hpp  (may not now be needed)
// lazy_reuse.hpp     (implemented without use of FC++ functions)
// lazy_list.hpp
//
// * file does not yet exist.
////////////////////////////////////////////////////////////////////////////
// This is implemented such that no other lazy_ file calls other lazy_ files.
// They do call their own external files, which may well be duplicates.
// That can be sorted out later.
////////////////////////////////////////////////////////////////////////////
// Notes: full and curry operations should be covered by Phoenix.
// The lambda operations are quite different from Phoenix lambda
// and will be omitted.
// The implementation monad can be postponed.
// Some of function and reuse are needed for the list type.
// I will review later whether they are part of the external interface.
//
// John Fletcher  February 2015.
////////////////////////////////////////////////////////////////////////////
/*=============================================================================
    Copyright (c) 2000-2003 Brian McNamara and Yannis Smaragdakis
    Copyright (c) 2001-2007 Joel de Guzman
    Copyright (c) 2015 John Fletcher

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/


#ifndef BOOST_PHOENIX_FUNCTION_LAZY_PRELUDE
#define BOOST_PHOENIX_FUNCTION_LAZY_PRELUDE

#include <exception>
#include <vector>
#include <boost/phoenix/core.hpp>
#include <boost/phoenix/function.hpp>
#include <boost/phoenix/scope.hpp>
#include <boost/phoenix/operator.hpp>
#include <boost/phoenix/function/lazy_operator.hpp>
#include <boost/phoenix/function/lazy_reuse.hpp>
#include <boost/phoenix/function/lazy_list.hpp>

////////////////////////////////////////////////////////////////////////////
// To come here, the Haskell Prelude things which need list<T>.
// Things which do not need list<T> are in lazy_operator.hpp.
////////////////////////////////////////////////////////////////////////////

namespace boost {

  namespace phoenix {

    // These are in fcpp namespace as they introduce an FC++ style.
    namespace fcpp {

    template <typename T>
    struct Predicate {
        typedef typename boost::function1<bool,T> fun1_bool_T;
        typedef typename boost::phoenix::function<fun1_bool_T> bool_F_T;
        typedef bool_F_T type;
    };

    template <typename R>
    struct Function0 {
        typedef typename boost::function0<R> fun0_R;
        typedef typename boost::phoenix::function<fun0_R> R_F;
        typedef R_F type;
    };

    template <typename R,typename A0>
    struct Function1 {
        typedef typename boost::function1<R,A0> fun1_R_A0;
        typedef typename boost::phoenix::function<fun1_R_A0> R_F_A0;
        typedef R_F_A0 type;
    };

    template <typename R, typename A0, typename A1>
    struct Function2 {
      typedef typename boost::function2<R,A0,A1> fun2_R_A0_A1;
        typedef typename boost::phoenix::function<fun2_R_A0_A1> R_F_A0_A1;
        typedef R_F_A0_A1 type;
    };

    }

    namespace impl {
      using fcpp::INV;
      using fcpp::VAR;
      using fcpp::reuser1;
      using fcpp::reuser2;
      using fcpp::reuser3;
      using boost::phoenix::arg_names::arg1;

         struct Pow {

            template <typename Sig>
            struct result;

            template <typename This, typename N, typename A0>
            struct result<This(N,A0)>
               : boost::remove_reference<A0>
            {};

            template <typename N, typename A0>
            A0 operator()(N n, const A0 & a0,
            reuser2<INV,VAR,INV,Pow,N,A0> r = NIL ) const {
              if ( n <= 0 )
                 return A0(1);
              else if ( n==1 )
                 return a0;
              else {
                A0 a1 = r( Pow(), n-1, a0)();
                return a0*a1;
              }
            }

         };

         struct Apply {

            template <typename Sig>
            struct result;

            template <typename This, typename N, typename F,typename A0>
            struct result<This(N,F,A0)>
               : boost::remove_reference<A0>
            {};

            template <typename N, typename F, typename A0>
            A0 operator()(N n, const F &f, const A0 & a0,
            reuser3<INV,VAR,INV,INV,Apply,N,F,A0> r = NIL ) const {
              if ( n <= 0 )
                 return a0;
              else if ( n==1 )
                 return f(arg1)(a0);
              else {
                A0 a1 = r( Apply(), n-1, f, a0)();
                return f(a1)();
              }
            }

         };

         struct Odd {
            template <typename Sig>
            struct result;

            template <typename This, typename T>
            struct result<This(T)>
            {
              typedef bool type;
            };

            template <class T>
            typename result<Odd(T)>::type operator()( const T& x ) const {
               return x%2==1;
            }
         };

         struct Even {
            template <typename Sig>
            struct result;

            template <typename This, typename T>
            struct result<This(T)>
            {
              typedef bool type;
            };

            template <class T>
            typename result<Even(T)>::type operator()( const T& x ) const {
               return x%2==0;
            }
         };

    }
    typedef boost::phoenix::function<impl::Pow>   Pow;
    typedef boost::phoenix::function<impl::Apply> Apply;
    typedef boost::phoenix::function<impl::Odd>   Odd;
    typedef boost::phoenix::function<impl::Even>  Even;
    Pow   pow;
    Apply apply;
    Odd   odd;
    Even  even;

    namespace impl {
      using fcpp::INV;
      using fcpp::VAR;
      using fcpp::reuser1;
      using fcpp::reuser2;
      using fcpp::reuser3;
      using boost::phoenix::arg_names::arg1;

      // I cannot yet do currying to pass e.g. greater(9,arg1)
      // as a function. This can be done using Predicate<T>::type.
         struct Until {

             template <typename Sig> struct result;

             template <typename This, typename Pred, typename Unary, typename T>
             struct result<This(Pred,Unary,T)>
                : boost::remove_reference<T> {};

             template <class Pred, class Unary, class T>
             T operator()( const Pred& p,const Unary& op,const T &start) const
             {
               T tmp = start;
               while( !p(tmp)() ) {
                 tmp = apply(1,op,tmp)();
               }
                return tmp;
             }

          };

          struct Until2 {

             template <typename Sig> struct result;

             template <typename This, typename Binary, typename Unary,
                       typename T, typename X>
             struct result<This(Binary,Unary,T,X)>
                : boost::remove_reference<T> {};

             template <class Binary, class Unary, class T, class X>
             typename result<Until2(Binary,Unary,T,X)>::type
             operator()( const Binary& p, const Unary& op, const T & start,
                        const X & check ) const
             {
               T tmp1 = start;
               T tmp2;
               while( !p(tmp1,check)() ) {
                 tmp2 = apply(1,op,tmp1)();
                 tmp1 = tmp2;
                 
               }
               return tmp1;
             }
          };

          struct Last {
             template <typename Sig> struct result;

             template <typename This, typename L>
             struct result<This(L)>
             {
               typedef typename result_of::ListType<L>::value_type type;
             };

             template <class L>
             typename result<Last(L)>::type
             operator()( const L& ll ) const {
               size_t x = 0;
               typename result_of::ListType<L>::delay_result_type l = delay(ll);
               while( !null( tail(l)() )() ) {
                 l = tail(l)();
                 ++x;
#ifndef BOOST_PHOENIX_NO_LAZY_EXCEPTIONS
                 if (x > BOOST_PHOENIX_FUNCTION_MAX_LAZY_LIST_LENGTH)
                   break;
#endif
               }
#ifndef BOOST_PHOENIX_NO_LAZY_EXCEPTIONS
                 if (x > BOOST_PHOENIX_FUNCTION_MAX_LAZY_LIST_LENGTH)
                     throw lazy_exception("Your list is too long!!");
#endif
                 return head(l)();
             }
          };

          struct Init {

             template <typename Sig> struct result;

             template <typename This, typename L>
             struct result<This(L)>
             {
               typedef typename result_of::ListType<L>::force_result_type type;
             };

             template <class L>
             typename result<Init(L)>::type
             operator()( const L& l,
                         reuser1<INV,VAR,Init,
                         typename result_of::ListType<L>::delay_result_type>
                         r = NIL ) const {
               if( null( tail( l )() )() )
                   return NIL;
               else
                   return cons( head(l)(), r( Init(), tail(l)() )() )();
               }
          };

          struct Length {
            template <typename Sig> struct result;

            template <typename This, typename L>
            struct result<This(L)>
            {
               typedef size_t type;
            };

            template <class L>
            size_t operator()( const L& ll ) const {
              typename L::delay_result_type l = delay(ll);
              size_t x = 0;
              while( !null(l)() ) {
                  l = tail(l);
                  ++x;
                  if (x > BOOST_PHOENIX_FUNCTION_MAX_LAZY_LIST_LENGTH)
                     break;
              }
#ifndef BOOST_PHOENIX_NO_LAZY_EXCEPTIONS
              if (x > BOOST_PHOENIX_FUNCTION_MAX_LAZY_LIST_LENGTH)
                   throw lazy_exception("Your list is too long!!");
#endif
              return x;
            }
          };

          // at is Haskell's operator (!!)
          // This is zero indexed.  at(l,0)() returns the first element.
          struct At {
            template <typename Sig> struct result;

            template <typename This, typename L, typename N>
            struct result<This(L,N)>
            {
               typedef typename result_of::ListType<L>::value_type type;
            };

              template <class L>
              typename result<At(L,size_t)>::type
              operator()( L l, size_t n ) const {
                  while( n!=0 ) {
                      l = tail(l);
                      --n;
                  }
                  return head(l)();
              }
          };

         template <class P,class L>
         struct FilterH
          {
              P p;
              L l;
              FilterH( const P& pp, const L& ll) : p(pp), l(ll) {}
              template <typename Sig> struct result;

              template <typename This, class PP, class LL>
              struct result<This(PP,LL)>
              {
                typedef typename boost::phoenix::result_of::
                        ListType<LL>::delay_result_type type;
              };
                typename result<FilterH(P,L)>::type operator()() const {
                typedef typename result_of::ListType<L>::
                        delay_result_type result_type;
                typedef boost::function0<result_type> Fun2_R_P_L;
                typedef boost::phoenix::function<Fun2_R_P_L> FilterH_R_P_L;
                if (null(l)() )
                   return NIL;
                Fun2_R_P_L fun2_R_P_L = FilterH<P,L>(p,tail(l));
                FilterH_R_P_L filterh_R_P_L(fun2_R_P_L);
                if( p(head(l))() )
                   return cons( head(l)(), filterh_R_P_L() );
                else
                   return filterh_R_P_L();
              }
          };

          struct Filter {
            template <typename Sig> struct result;

                template <typename This, typename P, typename L>
                struct result<This(P,L)>
                {
                  typedef typename result_of::ListType<L>::delay_result_type
                          type;
                };

                template <class P, class L>
                typename result<Filter(P,L)>::type
                operator()( const P& p, const L& ll) const
                {
                     typename  result_of::ListType<L>::delay_result_type
                     l = delay(ll);
                     typedef typename result_of::ListType<L>::
                           delay_result_type result_type;
                     typedef boost::function0<result_type> Fun2_R_P_L;
                     typedef boost::phoenix::function<Fun2_R_P_L> FilterH_R_P_L;
                     Fun2_R_P_L fun2_R_P_L = FilterH<P,L>(p,l);
                     FilterH_R_P_L filterh_R_P_L(fun2_R_P_L);
                     return filterh_R_P_L();
                }
          };

         template <class F,class T>
         struct IterateH
          {
              F f;
              T t;
              IterateH( const F& ff, const T& tt) : f(ff), t(tt) {}
              template <typename Sig> struct result;

              template <typename This,class F2,class T2>
              struct result<This(F2,T2)>
              {
                typedef typename boost::remove_reference<T2>::type TT;
                typedef typename boost::remove_const<TT>::type TTT;
                typedef typename UseList::template List<TTT>::type LType;
                typedef typename result_of::ListType<LType>::
                        delay_result_type type;
              };

                typename result<IterateH(F,T)>::type operator()() const {
                typedef typename UseList::template List<T>::type LType;
                typedef typename result_of::ListType<LType>::
                        delay_result_type result_type;
                typedef boost::function0<result_type> Fun2_R_F_T;
                typedef boost::phoenix::function<Fun2_R_F_T> IterateH_R_F_T;
                Fun2_R_F_T fun2_R_F_T = IterateH<F,T>(f,f(t)());
                IterateH_R_F_T iterateh_R_F_T(fun2_R_F_T);
                   return cons( t, iterateh_R_F_T() );
              }
          };


          struct Iterate {
   // Note: this does always return an odd_list; iterate() takes no ListLike
   // parameter, and it requires that its result be lazy.
              template <typename Sig> struct result;

              template <typename This, typename F, typename T>
              struct result<This(F,T)>
              {
                typedef typename boost::remove_reference<T>::type TT;
                typedef typename boost::remove_const<TT>::type TTT;
                typedef typename UseList::template List<TTT>::type LType;
                typedef typename result_of::ListType<LType>::
                        delay_result_type type;
              };

              template <class F, class T>
                typename result<Iterate(F,T)>::type operator()
                (const F& f, const T& t) const {
                typedef typename UseList::template List<T>::type LType;
                typedef typename result_of::ListType<LType>::
                        delay_result_type result_type;
                typedef boost::function0<result_type> Fun2_R_F_T;
                typedef boost::phoenix::function<Fun2_R_F_T> IterateH_R_F_T;
                Fun2_R_F_T fun2_R_F_T = IterateH<F,T>(f,f(t)());
                IterateH_R_F_T iterateh_R_F_T(fun2_R_F_T);
                   return iterateh_R_F_T();
              }
          };

    }

    typedef boost::phoenix::function<impl::Until> Until;
    typedef boost::phoenix::function<impl::Until2> Until2;
    typedef boost::phoenix::function<impl::Last>  Last;
    typedef boost::phoenix::function<impl::Init>  Init;
    typedef boost::phoenix::function<impl::Length> Length;
    typedef boost::phoenix::function<impl::At>    At;
    typedef boost::phoenix::function<impl::Filter> Filter;
    typedef boost::phoenix::function<impl::Iterate> Iterate;
    Until until;
    Until2 until2;
    Last  last;
    Init  all_but_last;  // renamed from init which is not available.
    Length length;
    At at_;  //Renamed from at.
    Filter filter;
    Iterate iterate;

    namespace impl {

          struct Repeat {
         // See note for iterate()
              template <typename Sig> struct result;

              template <typename This, typename T>
              struct result<This(T)>
              {
                typedef typename boost::remove_reference<T>::type TT;
                typedef typename boost::remove_const<TT>::type TTT;
                typedef typename UseList::template List<TTT>::type LType;
                typedef typename result_of::ListType<LType>::
                        delay_result_type type;
              };

              template <class T>
              typename result<Repeat(T)>::type operator()( const T& x) const
              {
                return iterate(id,x);
              }
          };

          struct Take {

             template <typename Sig> struct result;

             template <typename This, typename N, typename L>
             struct result<This(N,L)>
             {
               typedef typename result_of::ListType<L>::force_result_type type;
             };

             template <class N,class L>
             typename result<Take(N,L)>::type
             operator()( N n, const L& l,
               reuser2<INV,VAR,VAR,Take,N,
               typename result_of::ListType<L>::force_result_type>
               r = NIL
             ) const {
               if( n <= 0 || null(l)() )
                 return NIL;
               else {
                 return cons( head(l)(), r( Take(), n-1, tail(l)() )() )();
               }
             }
          };

          struct Drop {
             template <typename Sig> struct result;

             template <typename This, typename Dummy, typename L>
             struct result<This(Dummy,L)>
             {
               typedef typename result_of::ListType<L>::delay_result_type type;
             };
   
             template <class L>
             typename result<Drop(size_t,L)>::type
             operator()( size_t n, const L& ll ) const {
               typename L::delay_result_type l = delay(ll);
               while( n!=0 && !null(l)() ) {
                 --n;
                 l = tail(l)();
               }
               return l;
             }
          };
 
          template <class T>
          struct EFH
          {
              mutable T x;
              EFH( const T& xx) : x(xx) {}
              template <typename Sig> struct result;

              template <typename This, class TT>
              struct result<This(TT)>
              {
                typedef typename boost::phoenix::UseList::template
                        List<TT>::type LType;
                typedef typename boost::phoenix::result_of::
                        ListType<LType>::delay_result_type type;
              };
              typename result<EFH(T)>::type operator()() const {
                typedef typename UseList::template List<T>::type LType;
                typedef typename result_of::ListType<LType>::
                        delay_result_type result_type;
                typedef boost::function0<result_type> fun1_R_TTT;
                //std::cout << "EFH (" << x << ")" << std::endl;
                ++x;
                fun1_R_TTT efh_R_TTT = EFH<T>(x);
                typedef boost::phoenix::function<fun1_R_TTT> EFH_R_T;
                EFH_R_T efh_R_T(efh_R_TTT);
#ifndef BOOST_PHOENIX_NO_LAZY_EXCEPTIONS
                if (x > BOOST_PHOENIX_FUNCTION_MAX_LAZY_LIST_LENGTH)
                     throw lazy_exception("Running away in EFH!!");
#endif
                return cons( x-1, efh_R_T() );
              }
          };

          struct Enum_from {
             template <typename Sig> struct result;

             template <typename This, typename T>
             struct result<This(T)>
             {
               typedef typename boost::remove_reference<T>::type TT;
               typedef typename boost::remove_const<TT>::type TTT;
               typedef typename UseList::template List<TTT>::type LType;
               typedef typename result_of::ListType<LType>::
                       delay_result_type type;
             };

             template <class T>
             typename result<Enum_from(T)>::type operator()
                (const T & x) const
              {
                typedef typename boost::remove_reference<T>::type TT;
                typedef typename boost::remove_const<TT>::type TTT;
                typedef typename UseList::template List<T>::type LType;
                typedef typename result_of::ListType<LType>::
                        delay_result_type result_type;
                typedef boost::function0<result_type> fun1_R_TTT;
                fun1_R_TTT efh_R_TTT = EFH<TTT>(x);
                typedef boost::phoenix::function<fun1_R_TTT> EFH_R_T;
                EFH_R_T efh_R_T(efh_R_TTT);
                //std::cout << "enum_from (" << x << ")" << std::endl;
                return efh_R_T();
              }
          };

       template <class T>
         struct EFTH
          {
              mutable T x;
              T y;
              EFTH( const T& xx, const T& yy) : x(xx), y(yy) {}
              template <typename Sig> struct result;

              template <typename This, class TT>
              struct result<This(TT)>
              {
                typedef typename boost::phoenix::UseList::template
                        List<TT>::type LType;
                typedef typename boost::phoenix::result_of::
                        ListType<LType>::delay_result_type type;
              };
              typename result<EFTH(T)>::type operator()() const {
                typedef typename UseList::template List<T>::type LType;
                typedef typename result_of::ListType<LType>::
                        delay_result_type result_type;
                typedef boost::function0<result_type> fun1_R_TTT;
                //std::cout << "EFTH (" << x << ")" << std::endl;
                if (x > y ) return NIL;
                ++x;
                fun1_R_TTT efth_R_TTT = EFTH<T>(x,y);
                typedef boost::phoenix::function<fun1_R_TTT> EFTH_R_T;
                EFTH_R_T efth_R_T(efth_R_TTT);
#ifndef BOOST_PHOENIX_NO_LAZY_EXCEPTIONS
                if (x > BOOST_PHOENIX_FUNCTION_MAX_LAZY_LIST_LENGTH)
                     throw lazy_exception("Running away in EFTH!!");
#endif
                return cons( x-1, efth_R_T() );
              }
          };

          struct Enum_from_to {
             template <typename Sig> struct result;

             template <typename This, typename T>
             struct result<This(T,T)>
             {
               typedef typename boost::remove_reference<T>::type TT;
               typedef typename boost::remove_const<TT>::type TTT;
               typedef typename UseList::template List<TTT>::type LType;
               typedef typename result_of::ListType<LType>::
                       delay_result_type type;
             };

             template <class T>
             typename result<Enum_from(T,T)>::type operator()
             (const T & x, const T & y) const
              {
                typedef typename boost::remove_reference<T>::type TT;
                typedef typename boost::remove_const<TT>::type TTT;
                typedef typename UseList::template List<T>::type LType;
                typedef typename result_of::ListType<LType>::
                        delay_result_type result_type;
                typedef boost::function0<result_type> fun1_R_TTT;
                fun1_R_TTT efth_R_TTT = EFTH<TTT>(x,y);
                typedef boost::phoenix::function<fun1_R_TTT> EFTH_R_T;
                EFTH_R_T efth_R_T(efth_R_TTT);
                //std::cout << "enum_from (" << x << ")" << std::endl;
                return efth_R_T();
              }
          };

    }


    //BOOST_PHOENIX_ADAPT_CALLABLE(apply, impl::apply, 3)
    // Functors to be used in reuser will have to be defined
    // using boost::phoenix::function directly
    // in order to be able to be used as arguments.
    typedef boost::phoenix::function<impl::Repeat> Repeat;
    typedef boost::phoenix::function<impl::Take>  Take;
    typedef boost::phoenix::function<impl::Drop>  Drop;
    typedef boost::phoenix::function<impl::Enum_from>     Enum_from;
    typedef boost::phoenix::function<impl::Enum_from_to>  Enum_from_to;
    Repeat repeat;
    Take  take;
    Drop  drop;
    Enum_from enum_from;
    Enum_from_to enum_from_to;

    namespace fcpp {


    }

  }

}


#endif

/* lazy_prelude.hpp
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
*/