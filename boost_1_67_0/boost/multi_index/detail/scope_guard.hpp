/* Copyright 2003-2013 Joaquin M Lopez Munoz.
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

#include <boost/detail/no_exceptions_support.hpp>
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