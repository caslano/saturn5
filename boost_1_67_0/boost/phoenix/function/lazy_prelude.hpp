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