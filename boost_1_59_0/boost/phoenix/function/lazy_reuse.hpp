////////////////////////////////////////////////////////////////////////////
// lazy_reuse.hpp
//
// Build lazy operations for Phoenix equivalents for FC++
//
// These are equivalents of the Boost FC++ functoids in reuse.hpp
//
// Implemented so far:
//
// reuser1
// reuser2
// reuser3
// reuser4 (not yet tested)
//
// NOTE: It has been possible to simplify the operation of this code.
//       It now makes no use of boost::function or old FC++ code.
//
//       The functor type F must be an operator defined with
//       boost::phoenix::function.
//       See the example Apply in lazy_prelude.hpp
//
////////////////////////////////////////////////////////////////////////////
/*=============================================================================
    Copyright (c) 2000-2003 Brian McNamara and Yannis Smaragdakis
    Copyright (c) 2001-2007 Joel de Guzman
    Copyright (c) 2015 John Fletcher

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_PHOENIX_FUNCTION_LAZY_REUSE
#define BOOST_PHOENIX_FUNCTION_LAZY_REUSE

#include <boost/phoenix/core.hpp>
#include <boost/phoenix/function.hpp>
#include <boost/intrusive_ptr.hpp>


namespace boost {

  namespace phoenix {

    namespace fcpp {

//////////////////////////////////////////////////////////////////////
// Original FC++ comment:
// "Reuser"s are effectively special-purpose versions of curry() that
// enable recursive list functoids to reuse the thunk of the curried
// recursive call.  See
//    http://www.cc.gatech.edu/~yannis/fc++/New/reusers.html
// for a more detailed description.
//////////////////////////////////////////////////////////////////////

// For efficiency, we mark parameters as either "VAR"iant or "INV"ariant.
struct INV {};
struct VAR {};

template <class V, class X> struct Maybe_Var_Inv;
template <class X>
struct Maybe_Var_Inv<VAR,X> {
   static void remake( X& x, const X& val ) {
      x.~X();
      new (&x) X(val);
   }
   static X clone( const X& x ) { return X(x); }
};
template <class X>
struct Maybe_Var_Inv<INV,X> {
   static void remake( X&, const X& ) {}
   static const X& clone( const X& x ) { return x; }
};

/////////////////////////////////////////////////////////////////////
// ThunkImpl is an implementation of Fun0Impl for this use.
/////////////////////////////////////////////////////////////////////

template <class Result>
class ThunkImpl
{
   mutable RefCountType refC;
public:
   ThunkImpl() : refC(0) {}
   virtual Result operator()() const =0;
   virtual ~ThunkImpl() {}
   template <class X>
   friend void intrusive_ptr_add_ref( const ThunkImpl<X>* p );
   template <class X>
   friend void intrusive_ptr_release( const ThunkImpl<X>* p );
};

template <class T>
void intrusive_ptr_add_ref( const ThunkImpl<T>* p ) {
   ++ (p->refC);
}
template <class T>
void intrusive_ptr_release( const ThunkImpl<T>* p ) {
   if( !--(p->refC) ) delete p;
}

//////////////////////////////////////////////////////////////////////
// reuser1 is needed in list<T> operations
//////////////////////////////////////////////////////////////////////

template <class V1, class V2, class F, class X>
struct reuser1;

template <class V1, class V2, class F, class X, class R>
struct Thunk1 : public ThunkImpl<R> {
   mutable F f;
   mutable X x;
   Thunk1( const F& ff, const X& xx ) : f(ff), x(xx) {}
   void init( const F& ff, const X& xx ) const {
      Maybe_Var_Inv<V1,F>::remake( f, ff );
      Maybe_Var_Inv<V2,X>::remake( x, xx );
   }
   R operator()() const {
      return Maybe_Var_Inv<V1,F>::clone(f)(
         Maybe_Var_Inv<V2,X>::clone(x),
         reuser1<V1,V2,F,X>(this) );
   }
};

template <class V1, class V2, class F, class X>
struct reuser1 {
   typedef typename F::template result<F(X)>::type R;
   typedef typename boost::phoenix::function<R> fun0_type;
   typedef Thunk1<V1,V2,F,X,R> M;
   typedef M result_type;
   boost::intrusive_ptr<const M> ref;
   reuser1(a_unique_type_for_nil) {}
   reuser1(const M* m) : ref(m) {}
   M operator()( const F& f, const X& x ) {
      if( !ref )   ref = boost::intrusive_ptr<const M>( new M(f,x) );
      else         ref->init(f,x);
      return *ref;
   }
   void iter( const F& f, const X& x ) {
      if( ref )    ref->init(f,x);
   }
};

//////////////////////////////////////////////////////////////////////
// reuser2 is needed in list<T>
//////////////////////////////////////////////////////////////////////

template <class V1, class V2, class V3, class F, class X, class Y>
struct reuser2;

template <class V1, class V2, class V3, class F, class X, class Y, class R>
struct Thunk2 : public ThunkImpl<R> {
   mutable F f;
   mutable X x;
   mutable Y y;
   Thunk2( const F& ff, const X& xx, const Y& yy ) : f(ff), x(xx), y(yy) {}
   void init( const F& ff, const X& xx, const Y& yy ) const {
      Maybe_Var_Inv<V1,F>::remake( f, ff );
      Maybe_Var_Inv<V2,X>::remake( x, xx );
      Maybe_Var_Inv<V3,Y>::remake( y, yy );
   }
   R operator()() const {
      return Maybe_Var_Inv<V1,F>::clone(f)(
         Maybe_Var_Inv<V2,X>::clone(x),
         Maybe_Var_Inv<V3,Y>::clone(y),
         reuser2<V1,V2,V3,F,X,Y>(this) );
   }
};

template <class V1, class V2, class V3, class F, class X, class Y>
struct reuser2 {
   typedef typename F::template result<F(X,Y)>::type R;
   typedef Thunk2<V1,V2,V3,F,X,Y,R> M;
   typedef M result_type;
   boost::intrusive_ptr<const M> ref;
   reuser2(a_unique_type_for_nil) {}
   reuser2(const M* m) : ref(m) {}
   M operator()( const F& f, const X& x, const Y& y ) {
      if( !ref )   ref = boost::intrusive_ptr<const M>( new M(f,x,y) );
      else         ref->init(f,x,y);
      return *ref;
   }
   void iter( const F& f, const X& x, const Y& y ) {
      if( ref )    ref->init(f,x,y);
   }
};

//////////////////////////////////////////////////////////////////////
// reuser3
//////////////////////////////////////////////////////////////////////

template <class V1, class V2, class V3, class V4,
          class F, class X, class Y, class Z>
struct reuser3;

template <class V1, class V2, class V3, class V4,
          class F, class X, class Y, class Z, class R>
struct Thunk3 : public ThunkImpl<R> {
   mutable F f;
   mutable X x;
   mutable Y y;
   mutable Z z;
   Thunk3( const F& ff, const X& xx, const Y& yy, const Z& zz )
      : f(ff), x(xx), y(yy), z(zz) {}
   void init( const F& ff, const X& xx, const Y& yy, const Z& zz ) const {
      Maybe_Var_Inv<V1,F>::remake( f, ff );
      Maybe_Var_Inv<V2,X>::remake( x, xx );
      Maybe_Var_Inv<V3,Y>::remake( y, yy );
      Maybe_Var_Inv<V4,Z>::remake( z, zz );
   }
   R operator()() const {
      return Maybe_Var_Inv<V1,F>::clone(f)(
         Maybe_Var_Inv<V2,X>::clone(x),
         Maybe_Var_Inv<V3,Y>::clone(y),
         Maybe_Var_Inv<V4,Z>::clone(z),
         reuser3<V1,V2,V3,V4,F,X,Y,Z>(this) );
   }
};

template <class V1, class V2, class V3, class V4,
          class F, class X, class Y, class Z>
struct reuser3 {
   typedef typename F::template result<F(X,Y,Z)>::type R;
   typedef Thunk3<V1,V2,V3,V4,F,X,Y,Z,R> M;
   typedef M result_type;
   boost::intrusive_ptr<const M> ref;
   reuser3(a_unique_type_for_nil) {}
   reuser3(const M* m) : ref(m) {}
   M operator()( const F& f, const X& x, const Y& y, const Z& z ) {
      if( !ref )   ref = boost::intrusive_ptr<const M>( new M(f,x,y,z) );
      else         ref->init(f,x,y,z);
      return *ref;
   }
   void iter( const F& f, const X& x, const Y& y, const Z& z ) {
      if( ref )    ref->init(f,x,y,z);
   }
};
//////////////////////////////////////////////////////////////////////
// reuser4
//////////////////////////////////////////////////////////////////////

      template <class V1, class V2, class V3, class V4, class V5,
                class F, class W, class X, class Y, class Z>
struct reuser4;

      template <class V1, class V2, class V3, class V4, class V5,
                class F, class W, class X, class Y, class Z, class R>
struct Thunk4 : public ThunkImpl<R> {
      mutable F f;
      mutable W w;
      mutable X x;
      mutable Y y;
      mutable Z z;
      Thunk4( const F& ff, const W& ww, const X& xx, const Y& yy, const Z& zz )
            : f(ff), w(ww), x(xx), y(yy), z(zz) {}
   void init( const F& ff, const W& ww, const X& xx, const Y& yy, const Z& zz ) const {
      Maybe_Var_Inv<V1,F>::remake( f, ff );
      Maybe_Var_Inv<V2,W>::remake( w, ww );
      Maybe_Var_Inv<V3,X>::remake( x, xx );
      Maybe_Var_Inv<V4,Y>::remake( y, yy );
      Maybe_Var_Inv<V5,Z>::remake( z, zz );
   }
   R operator()() const {
      return Maybe_Var_Inv<V1,F>::clone(f)(
         Maybe_Var_Inv<V2,W>::clone(w),
         Maybe_Var_Inv<V3,X>::clone(x),
         Maybe_Var_Inv<V4,Y>::clone(y),
         Maybe_Var_Inv<V5,Z>::clone(z),
         reuser4<V1,V2,V3,V4,V5,F,W,X,Y,Z>(this) );
   }
};

      template <class V1, class V2, class V3, class V4, class V5,
                class F, class W, class X, class Y, class Z>
      struct reuser4 {
        typedef typename F::template result<F(W,X,Y,Z)>::type R;
        typedef Thunk4<V1,V2,V3,V4,V5,F,W,X,Y,Z,R> M;
        typedef M result_type;
        boost::intrusive_ptr<const M> ref;
        reuser4(a_unique_type_for_nil) {}
        reuser4(const M* m) : ref(m) {}
   M operator()( const F& f, const W& w, const X& x, const Y& y, const Z& z ) {
      if( !ref )   ref = boost::intrusive_ptr<const M>( new M(f,w,x,y,z) );
      else         ref->init(f,w,x,y,z);
      return *ref;
   }
   void iter( const F& f, const W& w, const X& x, const Y& y, const Z& z ) {
      if( ref )    ref->init(f,w,x,y,z);
   }
      };

    }

  }
}

#endif

/* lazy_reuse.hpp
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
*/