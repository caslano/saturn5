/* Copyright 2003-2020 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_SCOPE_GUARD_HPP
#define BOOST_MULTI_INDEX_DETAIL_SCOPE_GUARD_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/core/no_exceptions_support.hpp>
#include <boost/mpl/if.hpp>

namespace boost{

namespace multi_index{

namespace detail{

/* Until some official version of the ScopeGuard idiom makes it into Boost,
 * we locally define our own. This is a merely reformated version of
 * ScopeGuard.h as defined in:
 *   Alexandrescu, A., Marginean, P.:"Generic<Programming>: Change the Way You
 *     Write Exception-Safe Code - Forever", C/C++ Users Jornal, Dec 2000,
 *     http://www.drdobbs.com/184403758
 * with the following modifications:
 *   - General pretty formatting (pretty to my taste at least.)
 *   - Naming style changed to standard C++ library requirements.
 *   - Added scope_guard_impl4 and obj_scope_guard_impl3, (Boost.MultiIndex
 *     needs them). A better design would provide guards for many more
 *     arguments through the Boost Preprocessor Library.
 *   - Added scope_guard_impl_base::touch (see below.)
 *   - Removed RefHolder and ByRef, whose functionality is provided
 *     already by Boost.Ref.
 *   - Removed static make_guard's and make_obj_guard's, so that the code
 *     will work even if BOOST_NO_MEMBER_TEMPLATES is defined. This forces
 *     us to move some private ctors to public, though.
 *
 * NB: CodeWarrior Pro 8 seems to have problems looking up safe_execute
 * without an explicit qualification.
 * 
 * We also define the following variants of the idiom:
 * 
 *   - make_guard_if_c<bool>( ... )
 *   - make_guard_if<IntegralConstant>( ... )
 *   - make_obj_guard_if_c<bool>( ... )
 *   - make_obj_guard_if<IntegralConstant>( ... )
 * which may be used with a compile-time constant to yield
 * a "null_guard" if the boolean compile-time parameter is false,
 * or conversely, the guard is only constructed if the constant is true.
 * This is useful to avoid extra tagging, because the returned
 * null_guard can be optimzed comlpetely away by the compiler.
 */

class scope_guard_impl_base
{
public:
  scope_guard_impl_base():dismissed_(false){}
  void dismiss()const{dismissed_=true;}

  /* This helps prevent some "unused variable" warnings under, for instance,
   * GCC 3.2.
   */
  void touch()const{}

protected:
  ~scope_guard_impl_base(){}

  scope_guard_impl_base(const scope_guard_impl_base& other):
    dismissed_(other.dismissed_)
  {
    other.dismiss();
  }

  template<typename J>
  static void safe_execute(J& j){
    BOOST_TRY{
      if(!j.dismissed_)j.execute();
    }
    BOOST_CATCH(...){}
    BOOST_CATCH_END
  }
  
  mutable bool dismissed_;

private:
  scope_guard_impl_base& operator=(const scope_guard_impl_base&);
};

typedef const scope_guard_impl_base& scope_guard;

struct null_guard : public scope_guard_impl_base
{
    template< class T1 >
    null_guard( const T1& )
    { }

    template< class T1, class T2 >
    null_guard( const T1&, const T2& )
    { }

    template< class T1, class T2, class T3 >
    null_guard( const T1&, const T2&, const T3& )
    { }

    template< class T1, class T2, class T3, class T4 >
    null_guard( const T1&, const T2&, const T3&, const T4& )
    { }

    template< class T1, class T2, class T3, class T4, class T5 >
    null_guard( const T1&, const T2&, const T3&, const T4&, const T5& )
    { }
};

template< bool cond, class T >
struct null_guard_return
{
    typedef typename boost::mpl::if_c<cond,T,null_guard>::type type;
};

template<typename F>
class scope_guard_impl0:public scope_guard_impl_base
{
public:
  scope_guard_impl0(F fun):fun_(fun){}
  ~scope_guard_impl0(){scope_guard_impl_base::safe_execute(*this);}
  void execute(){fun_();}

protected:

  F fun_;
};

template<typename F> 
inline scope_guard_impl0<F> make_guard(F fun)
{
  return scope_guard_impl0<F>(fun);
}

template<bool cond, typename F> 
inline typename null_guard_return<cond,scope_guard_impl0<F> >::type  
make_guard_if_c(F fun)
{
  return typename null_guard_return<cond,scope_guard_impl0<F> >::type(fun);
}

template<typename C, typename F> 
inline typename null_guard_return<C::value,scope_guard_impl0<F> >::type  
make_guard_if(F fun)
{
  return make_guard_if<C::value>(fun);
}

template<typename F,typename P1>
class scope_guard_impl1:public scope_guard_impl_base
{
public:
  scope_guard_impl1(F fun,P1 p1):fun_(fun),p1_(p1){}
  ~scope_guard_impl1(){scope_guard_impl_base::safe_execute(*this);}
  void execute(){fun_(p1_);}

protected:
  F        fun_;
  const P1 p1_;
};

template<typename F,typename P1> 
inline scope_guard_impl1<F,P1> make_guard(F fun,P1 p1)
{
  return scope_guard_impl1<F,P1>(fun,p1);
}

template<bool cond, typename F,typename P1> 
inline typename null_guard_return<cond,scope_guard_impl1<F,P1> >::type 
make_guard_if_c(F fun,P1 p1)
{
  return typename null_guard_return<cond,scope_guard_impl1<F,P1> >::type(fun,p1);
}

template<typename C, typename F,typename P1> 
inline typename null_guard_return<C::value,scope_guard_impl1<F,P1> >::type 
make_guard_if(F fun,P1 p1)
{
  return make_guard_if_c<C::value>(fun,p1);
}

template<typename F,typename P1,typename P2>
class scope_guard_impl2:public scope_guard_impl_base
{
public:
  scope_guard_impl2(F fun,P1 p1,P2 p2):fun_(fun),p1_(p1),p2_(p2){}
  ~scope_guard_impl2(){scope_guard_impl_base::safe_execute(*this);}
  void execute(){fun_(p1_,p2_);}

protected:
  F        fun_;
  const P1 p1_;
  const P2 p2_;
};

template<typename F,typename P1,typename P2>
inline scope_guard_impl2<F,P1,P2> make_guard(F fun,P1 p1,P2 p2)
{
  return scope_guard_impl2<F,P1,P2>(fun,p1,p2);
}

template<bool cond, typename F,typename P1,typename P2>
inline typename null_guard_return<cond,scope_guard_impl2<F,P1,P2> >::type
make_guard_if_c(F fun,P1 p1,P2 p2)
{
  return typename null_guard_return<cond,scope_guard_impl2<F,P1,P2> >::type(fun,p1,p2);
}

template<typename C, typename F,typename P1,typename P2>
inline typename null_guard_return<C::value,scope_guard_impl2<F,P1,P2> >::type
make_guard_if(F fun,P1 p1,P2 p2)
{
  return make_guard_if_c<C::value>(fun,p1,p2);
}

template<typename F,typename P1,typename P2,typename P3>
class scope_guard_impl3:public scope_guard_impl_base
{
public:
  scope_guard_impl3(F fun,P1 p1,P2 p2,P3 p3):fun_(fun),p1_(p1),p2_(p2),p3_(p3){}
  ~scope_guard_impl3(){scope_guard_impl_base::safe_execute(*this);}
  void execute(){fun_(p1_,p2_,p3_);}

protected:
  F        fun_;
  const P1 p1_;
  const P2 p2_;
  const P3 p3_;
};

template<typename F,typename P1,typename P2,typename P3>
inline scope_guard_impl3<F,P1,P2,P3> make_guard(F fun,P1 p1,P2 p2,P3 p3)
{
  return scope_guard_impl3<F,P1,P2,P3>(fun,p1,p2,p3);
}

template<bool cond,typename F,typename P1,typename P2,typename P3>
inline typename null_guard_return<cond,scope_guard_impl3<F,P1,P2,P3> >::type 
make_guard_if_c(F fun,P1 p1,P2 p2,P3 p3)
{
  return typename null_guard_return<cond,scope_guard_impl3<F,P1,P2,P3> >::type(fun,p1,p2,p3);
}

template<typename C,typename F,typename P1,typename P2,typename P3>
inline typename null_guard_return< C::value,scope_guard_impl3<F,P1,P2,P3> >::type 
make_guard_if(F fun,P1 p1,P2 p2,P3 p3)
{
  return make_guard_if_c<C::value>(fun,p1,p2,p3);
}

template<typename F,typename P1,typename P2,typename P3,typename P4>
class scope_guard_impl4:public scope_guard_impl_base
{
public:
  scope_guard_impl4(F fun,P1 p1,P2 p2,P3 p3,P4 p4):
    fun_(fun),p1_(p1),p2_(p2),p3_(p3),p4_(p4){}
  ~scope_guard_impl4(){scope_guard_impl_base::safe_execute(*this);}
  void execute(){fun_(p1_,p2_,p3_,p4_);}

protected:
  F        fun_;
  const P1 p1_;
  const P2 p2_;
  const P3 p3_;
  const P4 p4_;
};

template<typename F,typename P1,typename P2,typename P3,typename P4>
inline scope_guard_impl4<F,P1,P2,P3,P4> make_guard(
  F fun,P1 p1,P2 p2,P3 p3,P4 p4)
{
  return scope_guard_impl4<F,P1,P2,P3,P4>(fun,p1,p2,p3,p4);
}

template<bool cond, typename F,typename P1,typename P2,typename P3,typename P4>
inline typename null_guard_return<cond,scope_guard_impl4<F,P1,P2,P3,P4> >::type 
make_guard_if_c(
  F fun,P1 p1,P2 p2,P3 p3,P4 p4)
{
  return typename null_guard_return<cond,scope_guard_impl4<F,P1,P2,P3,P4> >::type(fun,p1,p2,p3,p4);
}

template<typename C, typename F,typename P1,typename P2,typename P3,typename P4>
inline typename null_guard_return<C::value,scope_guard_impl4<F,P1,P2,P3,P4> >::type 
make_guard_if(
  F fun,P1 p1,P2 p2,P3 p3,P4 p4)
{
  return make_guard_if_c<C::value>(fun,p1,p2,p3,p4);
}

template<class Obj,typename MemFun>
class obj_scope_guard_impl0:public scope_guard_impl_base
{
public:
  obj_scope_guard_impl0(Obj& obj,MemFun mem_fun):obj_(obj),mem_fun_(mem_fun){}
  ~obj_scope_guard_impl0(){scope_guard_impl_base::safe_execute(*this);}
  void execute(){(obj_.*mem_fun_)();}

protected:
  Obj&   obj_;
  MemFun mem_fun_;
};

template<class Obj,typename MemFun>
inline obj_scope_guard_impl0<Obj,MemFun> make_obj_guard(Obj& obj,MemFun mem_fun)
{
  return obj_scope_guard_impl0<Obj,MemFun>(obj,mem_fun);
}

template<bool cond, class Obj,typename MemFun>
inline typename null_guard_return<cond,obj_scope_guard_impl0<Obj,MemFun> >::type 
make_obj_guard_if_c(Obj& obj,MemFun mem_fun)
{
  return typename null_guard_return<cond,obj_scope_guard_impl0<Obj,MemFun> >::type(obj,mem_fun);
}

template<typename C, class Obj,typename MemFun>
inline typename null_guard_return<C::value,obj_scope_guard_impl0<Obj,MemFun> >::type 
make_obj_guard_if(Obj& obj,MemFun mem_fun)
{
  return make_obj_guard_if_c<C::value>(obj,mem_fun);
}

template<class Obj,typename MemFun,typename P1>
class obj_scope_guard_impl1:public scope_guard_impl_base
{
public:
  obj_scope_guard_impl1(Obj& obj,MemFun mem_fun,P1 p1):
    obj_(obj),mem_fun_(mem_fun),p1_(p1){}
  ~obj_scope_guard_impl1(){scope_guard_impl_base::safe_execute(*this);}
  void execute(){(obj_.*mem_fun_)(p1_);}

protected:
  Obj&     obj_;
  MemFun   mem_fun_;
  const P1 p1_;
};

template<class Obj,typename MemFun,typename P1>
inline obj_scope_guard_impl1<Obj,MemFun,P1> make_obj_guard(
  Obj& obj,MemFun mem_fun,P1 p1)
{
  return obj_scope_guard_impl1<Obj,MemFun,P1>(obj,mem_fun,p1);
}

template<bool cond, class Obj,typename MemFun,typename P1>
inline typename null_guard_return<cond,obj_scope_guard_impl1<Obj,MemFun,P1> >::type 
make_obj_guard_if_c(  Obj& obj,MemFun mem_fun,P1 p1)
{
  return typename null_guard_return<cond,obj_scope_guard_impl1<Obj,MemFun,P1> >::type(obj,mem_fun,p1);
}

template<typename C, class Obj,typename MemFun,typename P1>
inline typename null_guard_return<C::value,obj_scope_guard_impl1<Obj,MemFun,P1> >::type 
make_obj_guard_if( Obj& obj,MemFun mem_fun,P1 p1)
{
  return make_obj_guard_if_c<C::value>(obj,mem_fun,p1);
}

template<class Obj,typename MemFun,typename P1,typename P2>
class obj_scope_guard_impl2:public scope_guard_impl_base
{
public:
  obj_scope_guard_impl2(Obj& obj,MemFun mem_fun,P1 p1,P2 p2):
    obj_(obj),mem_fun_(mem_fun),p1_(p1),p2_(p2)
  {}
  ~obj_scope_guard_impl2(){scope_guard_impl_base::safe_execute(*this);}
  void execute(){(obj_.*mem_fun_)(p1_,p2_);}

protected:
  Obj&     obj_;
  MemFun   mem_fun_;
  const P1 p1_;
  const P2 p2_;
};

template<class Obj,typename MemFun,typename P1,typename P2>
inline obj_scope_guard_impl2<Obj,MemFun,P1,P2>
make_obj_guard(Obj& obj,MemFun mem_fun,P1 p1,P2 p2)
{
  return obj_scope_guard_impl2<Obj,MemFun,P1,P2>(obj,mem_fun,p1,p2);
}

template<bool cond, class Obj,typename MemFun,typename P1,typename P2>
inline typename null_guard_return<cond,obj_scope_guard_impl2<Obj,MemFun,P1,P2> >::type
make_obj_guard_if_c(Obj& obj,MemFun mem_fun,P1 p1,P2 p2)
{
  return typename null_guard_return<cond,obj_scope_guard_impl2<Obj,MemFun,P1,P2> >::type(obj,mem_fun,p1,p2);
}

template<typename C, class Obj,typename MemFun,typename P1,typename P2>
inline typename null_guard_return<C::value,obj_scope_guard_impl2<Obj,MemFun,P1,P2> >::type
make_obj_guard_if(Obj& obj,MemFun mem_fun,P1 p1,P2 p2)
{
  return make_obj_guard_if_c<C::value>(obj,mem_fun,p1,p2);
}

template<class Obj,typename MemFun,typename P1,typename P2,typename P3>
class obj_scope_guard_impl3:public scope_guard_impl_base
{
public:
  obj_scope_guard_impl3(Obj& obj,MemFun mem_fun,P1 p1,P2 p2,P3 p3):
    obj_(obj),mem_fun_(mem_fun),p1_(p1),p2_(p2),p3_(p3)
  {}
  ~obj_scope_guard_impl3(){scope_guard_impl_base::safe_execute(*this);}
  void execute(){(obj_.*mem_fun_)(p1_,p2_,p3_);}

protected:
  Obj&     obj_;
  MemFun   mem_fun_;
  const P1 p1_;
  const P2 p2_;
  const P3 p3_;
};

template<class Obj,typename MemFun,typename P1,typename P2,typename P3>
inline obj_scope_guard_impl3<Obj,MemFun,P1,P2,P3>
make_obj_guard(Obj& obj,MemFun mem_fun,P1 p1,P2 p2,P3 p3)
{
  return obj_scope_guard_impl3<Obj,MemFun,P1,P2,P3>(obj,mem_fun,p1,p2,p3);
}

template<bool cond, class Obj,typename MemFun,typename P1,typename P2,typename P3>
inline typename null_guard_return<cond,obj_scope_guard_impl3<Obj,MemFun,P1,P2,P3> >::type
make_obj_guard_if_c(Obj& obj,MemFun mem_fun,P1 p1,P2 p2,P3 p3)
{
  return typename null_guard_return<cond,obj_scope_guard_impl3<Obj,MemFun,P1,P2,P3> >::type(obj,mem_fun,p1,p2,p3);
}

template<typename C, class Obj,typename MemFun,typename P1,typename P2,typename P3>
inline typename null_guard_return<C::value,obj_scope_guard_impl3<Obj,MemFun,P1,P2,P3> >::type
make_obj_guard_if(Obj& obj,MemFun mem_fun,P1 p1,P2 p2,P3 p3)
{
  return make_obj_guard_if_c<C::value>(obj,mem_fun,p1,p2,p3);
}

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* scope_guard.hpp
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
*/