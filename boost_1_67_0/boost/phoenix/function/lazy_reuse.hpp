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