//
//  bind/mem_fn_template.hpp
//
//  Do not include this header directly
//
//  Copyright (c) 2001 Peter Dimov and Multi Media Ltd.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/bind/mem_fn.html for documentation.
//

#if !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)
# define BOOST_MEM_FN_ENABLE_CONST_OVERLOADS
#endif

// mf0

template<class R, class T BOOST_MEM_FN_CLASS_F> class BOOST_MEM_FN_NAME(mf0)
{
public:

    typedef R result_type;
    typedef T * argument_type;

private:
    
    BOOST_MEM_FN_TYPEDEF(R (BOOST_MEM_FN_CC T::*F) ())
    F f_;

    template<class U> R call(U & u, T const *) const
    {
        BOOST_MEM_FN_RETURN (u.*f_)();
    }

    template<class U> R call(U & u, void const *) const
    {
        BOOST_MEM_FN_RETURN (get_pointer(u)->*f_)();
    }

public:
    
    explicit BOOST_MEM_FN_NAME(mf0)(F f): f_(f) {}

    R operator()(T * p) const
    {
        BOOST_MEM_FN_RETURN (p->*f_)();
    }

    template<class U> R operator()(U & u) const
    {
        U const * p = 0;
        BOOST_MEM_FN_RETURN call(u, p);
    }

#ifdef BOOST_MEM_FN_ENABLE_CONST_OVERLOADS

    template<class U> R operator()(U const & u) const
    {
        U const * p = 0;
        BOOST_MEM_FN_RETURN call(u, p);
    }

#endif

    R operator()(T & t) const
    {
        BOOST_MEM_FN_RETURN (t.*f_)();
    }

    bool operator==(BOOST_MEM_FN_NAME(mf0) const & rhs) const
    {
        return f_ == rhs.f_;
    }

    bool operator!=(BOOST_MEM_FN_NAME(mf0) const & rhs) const
    {
        return f_ != rhs.f_;
    }
};

// cmf0

template<class R, class T BOOST_MEM_FN_CLASS_F> class BOOST_MEM_FN_NAME(cmf0)
{
public:

    typedef R result_type;
    typedef T const * argument_type;

private:
    
    BOOST_MEM_FN_TYPEDEF(R (BOOST_MEM_FN_CC T::*F) () const)
    F f_;

    template<class U> R call(U & u, T const *) const
    {
        BOOST_MEM_FN_RETURN (u.*f_)();
    }

    template<class U> R call(U & u, void const *) const
    {
        BOOST_MEM_FN_RETURN (get_pointer(u)->*f_)();
    }

public:
    
    explicit BOOST_MEM_FN_NAME(cmf0)(F f): f_(f) {}

    template<class U> R operator()(U const & u) const
    {
        U const * p = 0;
        BOOST_MEM_FN_RETURN call(u, p);
    }

    R operator()(T const & t) const
    {
        BOOST_MEM_FN_RETURN (t.*f_)();
    }

    bool operator==(BOOST_MEM_FN_NAME(cmf0) const & rhs) const
    {
        return f_ == rhs.f_;
    }

    bool operator!=(BOOST_MEM_FN_NAME(cmf0) const & rhs) const
    {
        return f_ != rhs.f_;
    }
};

// mf1

template<class R, class T, class A1 BOOST_MEM_FN_CLASS_F> class BOOST_MEM_FN_NAME(mf1)
{
public:

    typedef R result_type;
    typedef T * first_argument_type;
    typedef A1 second_argument_type;

private:
    
    BOOST_MEM_FN_TYPEDEF(R (BOOST_MEM_FN_CC T::*F) (A1))
    F f_;

    template<class U, class B1> R call(U & u, T const *, B1 & b1) const
    {
        BOOST_MEM_FN_RETURN (u.*f_)(b1);
    }

    template<class U, class B1> R call(U & u, void const *, B1 & b1) const
    {
        BOOST_MEM_FN_RETURN (get_pointer(u)->*f_)(b1);
    }

public:
    
    explicit BOOST_MEM_FN_NAME(mf1)(F f): f_(f) {}

    R operator()(T * p, A1 a1) const
    {
        BOOST_MEM_FN_RETURN (p->*f_)(a1);
    }

    template<class U> R operator()(U & u, A1 a1) const
    {
        U const * p = 0;
        BOOST_MEM_FN_RETURN call(u, p, a1);
    }

#ifdef BOOST_MEM_FN_ENABLE_CONST_OVERLOADS

    template<class U> R operator()(U const & u, A1 a1) const
    {
        U const * p = 0;
        BOOST_MEM_FN_RETURN call(u, p, a1);
    }

#endif

    R operator()(T & t, A1 a1) const
    {
        BOOST_MEM_FN_RETURN (t.*f_)(a1);
    }

    bool operator==(BOOST_MEM_FN_NAME(mf1) const & rhs) const
    {
        return f_ == rhs.f_;
    }

    bool operator!=(BOOST_MEM_FN_NAME(mf1) const & rhs) const
    {
        return f_ != rhs.f_;
    }
};

// cmf1

template<class R, class T, class A1 BOOST_MEM_FN_CLASS_F> class BOOST_MEM_FN_NAME(cmf1)
{
public:

    typedef R result_type;
    typedef T const * first_argument_type;
    typedef A1 second_argument_type;

private:
    
    BOOST_MEM_FN_TYPEDEF(R (BOOST_MEM_FN_CC T::*F) (A1) const)
    F f_;

    template<class U, class B1> R call(U & u, T const *, B1 & b1) const
    {
        BOOST_MEM_FN_RETURN (u.*f_)(b1);
    }

    template<class U, class B1> R call(U & u, void const *, B1 & b1) const
    {
        BOOST_MEM_FN_RETURN (get_pointer(u)->*f_)(b1);
    }

public:
    
    explicit BOOST_MEM_FN_NAME(cmf1)(F f): f_(f) {}

    template<class U> R operator()(U const & u, A1 a1) const
    {
        U const * p = 0;
        BOOST_MEM_FN_RETURN call(u, p, a1);
    }

    R operator()(T const & t, A1 a1) const
    {
        BOOST_MEM_FN_RETURN (t.*f_)(a1);
    }

    bool operator==(BOOST_MEM_FN_NAME(cmf1) const & rhs) const
    {
        return f_ == rhs.f_;
    }

    bool operator!=(BOOST_MEM_FN_NAME(cmf1) const & rhs) const
    {
        return f_ != rhs.f_;
    }
};

// mf2

template<class R, class T, class A1, class A2 BOOST_MEM_FN_CLASS_F> class BOOST_MEM_FN_NAME(mf2)
{
public:

    typedef R result_type;

private:
    
    BOOST_MEM_FN_TYPEDEF(R (BOOST_MEM_FN_CC T::*F) (A1, A2))
    F f_;

    template<class U, class B1, class B2> R call(U & u, T const *, B1 & b1, B2 & b2) const
    {
        BOOST_MEM_FN_RETURN (u.*f_)(b1, b2);
    }

    template<class U, class B1, class B2> R call(U & u, void const *, B1 & b1, B2 & b2) const
    {
        BOOST_MEM_FN_RETURN (get_pointer(u)->*f_)(b1, b2);
    }

public:
    
    explicit BOOST_MEM_FN_NAME(mf2)(F f): f_(f) {}

    R operator()(T * p, A1 a1, A2 a2) const
    {
        BOOST_MEM_FN_RETURN (p->*f_)(a1, a2);
    }

    template<class U> R operator()(U & u, A1 a1, A2 a2) const
    {
        U const * p = 0;
        BOOST_MEM_FN_RETURN call(u, p, a1, a2);
    }

#ifdef BOOST_MEM_FN_ENABLE_CONST_OVERLOADS

    template<class U> R operator()(U const & u, A1 a1, A2 a2) const
    {
        U const * p = 0;
        BOOST_MEM_FN_RETURN call(u, p, a1, a2);
    }

#endif

    R operator()(T & t, A1 a1, A2 a2) const
    {
        BOOST_MEM_FN_RETURN (t.*f_)(a1, a2);
    }

    bool operator==(BOOST_MEM_FN_NAME(mf2) const & rhs) const
    {
        return f_ == rhs.f_;
    }

    bool operator!=(BOOST_MEM_FN_NAME(mf2) const & rhs) const
    {
        return f_ != rhs.f_;
    }
};

// cmf2

template<class R, class T, class A1, class A2 BOOST_MEM_FN_CLASS_F> class BOOST_MEM_FN_NAME(cmf2)
{
public:

    typedef R result_type;

private:
    
    BOOST_MEM_FN_TYPEDEF(R (BOOST_MEM_FN_CC T::*F) (A1, A2) const)
    F f_;

    template<class U, class B1, class B2> R call(U & u, T const *, B1 & b1, B2 & b2) const
    {
        BOOST_MEM_FN_RETURN (u.*f_)(b1, b2);
    }

    template<class U, class B1, class B2> R call(U & u, void const *, B1 & b1, B2 & b2) const
    {
        BOOST_MEM_FN_RETURN (get_pointer(u)->*f_)(b1, b2);
    }

public:
    
    explicit BOOST_MEM_FN_NAME(cmf2)(F f): f_(f) {}

    template<class U> R operator()(U const & u, A1 a1, A2 a2) const
    {
        U const * p = 0;
        BOOST_MEM_FN_RETURN call(u, p, a1, a2);
    }

    R operator()(T const & t, A1 a1, A2 a2) const
    {
        BOOST_MEM_FN_RETURN (t.*f_)(a1, a2);
    }

    bool operator==(BOOST_MEM_FN_NAME(cmf2) const & rhs) const
    {
        return f_ == rhs.f_;
    }

    bool operator!=(BOOST_MEM_FN_NAME(cmf2) const & rhs) const
    {
        return f_ != rhs.f_;
    }
};

// mf3

template<class R, class T, class A1, class A2, class A3 BOOST_MEM_FN_CLASS_F> class BOOST_MEM_FN_NAME(mf3)
{
public:

    typedef R result_type;

private:
    
    BOOST_MEM_FN_TYPEDEF(R (BOOST_MEM_FN_CC T::*F) (A1, A2, A3))
    F f_;

    template<class U, class B1, class B2, class B3> R call(U & u, T const *, B1 & b1, B2 & b2, B3 & b3) const
    {
        BOOST_MEM_FN_RETURN (u.*f_)(b1, b2, b3);
    }

    template<class U, class B1, class B2, class B3> R call(U & u, void const *, B1 & b1, B2 & b2, B3 & b3) const
    {
        BOOST_MEM_FN_RETURN (get_pointer(u)->*f_)(b1, b2, b3);
    }

public:
    
    explicit BOOST_MEM_FN_NAME(mf3)(F f): f_(f) {}

    R operator()(T * p, A1 a1, A2 a2, A3 a3) const
    {
        BOOST_MEM_FN_RETURN (p->*f_)(a1, a2, a3);
    }

    template<class U> R operator()(U & u, A1 a1, A2 a2, A3 a3) const
    {
        U const * p = 0;
        BOOST_MEM_FN_RETURN call(u, p, a1, a2, a3);
    }

#ifdef BOOST_MEM_FN_ENABLE_CONST_OVERLOADS

    template<class U> R operator()(U const & u, A1 a1, A2 a2, A3 a3) const
    {
        U const * p = 0;
        BOOST_MEM_FN_RETURN call(u, p, a1, a2, a3);
    }

#endif

    R operator()(T & t, A1 a1, A2 a2, A3 a3) const
    {
        BOOST_MEM_FN_RETURN (t.*f_)(a1, a2, a3);
    }

    bool operator==(BOOST_MEM_FN_NAME(mf3) const & rhs) const
    {
        return f_ == rhs.f_;
    }

    bool operator!=(BOOST_MEM_FN_NAME(mf3) const & rhs) const
    {
        return f_ != rhs.f_;
    }
};

// cmf3

template<class R, class T, class A1, class A2, class A3 BOOST_MEM_FN_CLASS_F> class BOOST_MEM_FN_NAME(cmf3)
{
public:

    typedef R result_type;

private:

    BOOST_MEM_FN_TYPEDEF(R (BOOST_MEM_FN_CC T::*F) (A1, A2, A3) const)
    F f_;

    template<class U, class B1, class B2, class B3> R call(U & u, T const *, B1 & b1, B2 & b2, B3 & b3) const
    {
        BOOST_MEM_FN_RETURN (u.*f_)(b1, b2, b3);
    }

    template<class U, class B1, class B2, class B3> R call(U & u, void const *, B1 & b1, B2 & b2, B3 & b3) const
    {
        BOOST_MEM_FN_RETURN (get_pointer(u)->*f_)(b1, b2, b3);
    }

public:

    explicit BOOST_MEM_FN_NAME(cmf3)(F f): f_(f) {}

    template<class U> R operator()(U const & u, A1 a1, A2 a2, A3 a3) const
    {
        U const * p = 0;
        BOOST_MEM_FN_RETURN call(u, p, a1, a2, a3);
    }

    R operator()(T const & t, A1 a1, A2 a2, A3 a3) const
    {
        BOOST_MEM_FN_RETURN (t.*f_)(a1, a2, a3);
    }

    bool operator==(BOOST_MEM_FN_NAME(cmf3) const & rhs) const
    {
        return f_ == rhs.f_;
    }

    bool operator!=(BOOST_MEM_FN_NAME(cmf3) const & rhs) const
    {
        return f_ != rhs.f_;
    }
};

// mf4

template<class R, class T, class A1, class A2, class A3, class A4 BOOST_MEM_FN_CLASS_F> class BOOST_MEM_FN_NAME(mf4)
{
public:

    typedef R result_type;

private:
    
    BOOST_MEM_FN_TYPEDEF(R (BOOST_MEM_FN_CC T::*F) (A1, A2, A3, A4))
    F f_;

    template<class U, class B1, class B2, class B3, class B4> R call(U & u, T const *, B1 & b1, B2 & b2, B3 & b3, B4 & b4) const
    {
        BOOST_MEM_FN_RETURN (u.*f_)(b1, b2, b3, b4);
    }

    template<class U, class B1, class B2, class B3, class B4> R call(U & u, void const *, B1 & b1, B2 & b2, B3 & b3, B4 & b4) const
    {
        BOOST_MEM_FN_RETURN (get_pointer(u)->*f_)(b1, b2, b3, b4);
    }

public:
    
    explicit BOOST_MEM_FN_NAME(mf4)(F f): f_(f) {}

    R operator()(T * p, A1 a1, A2 a2, A3 a3, A4 a4) const
    {
        BOOST_MEM_FN_RETURN (p->*f_)(a1, a2, a3, a4);
    }

    template<class U> R operator()(U & u, A1 a1, A2 a2, A3 a3, A4 a4) const
    {
        U const * p = 0;
        BOOST_MEM_FN_RETURN call(u, p, a1, a2, a3, a4);
    }

#ifdef BOOST_MEM_FN_ENABLE_CONST_OVERLOADS

    template<class U> R operator()(U const & u, A1 a1, A2 a2, A3 a3, A4 a4) const
    {
        U const * p = 0;
        BOOST_MEM_FN_RETURN call(u, p, a1, a2, a3, a4);
    }

#endif

    R operator()(T & t, A1 a1, A2 a2, A3 a3, A4 a4) const
    {
        BOOST_MEM_FN_RETURN (t.*f_)(a1, a2, a3, a4);
    }

    bool operator==(BOOST_MEM_FN_NAME(mf4) const & rhs) const
    {
        return f_ == rhs.f_;
    }

    bool operator!=(BOOST_MEM_FN_NAME(mf4) const & rhs) const
    {
        return f_ != rhs.f_;
    }
};

// cmf4

template<class R, class T, class A1, class A2, class A3, class A4 BOOST_MEM_FN_CLASS_F> class BOOST_MEM_FN_NAME(cmf4)
{
public:

    typedef R result_type;

private:
    
    BOOST_MEM_FN_TYPEDEF(R (BOOST_MEM_FN_CC T::*F) (A1, A2, A3, A4) const)
    F f_;

    template<class U, class B1, class B2, class B3, class B4> R call(U & u, T const *, B1 & b1, B2 & b2, B3 & b3, B4 & b4) const
    {
        BOOST_MEM_FN_RETURN (u.*f_)(b1, b2, b3, b4);
    }

    template<class U, class B1, class B2, class B3, class B4> R call(U & u, void const *, B1 & b1, B2 & b2, B3 & b3, B4 & b4) const
    {
        BOOST_MEM_FN_RETURN (get_pointer(u)->*f_)(b1, b2, b3, b4);
    }

public:
    
    explicit BOOST_MEM_FN_NAME(cmf4)(F f): f_(f) {}

    template<class U> R operator()(U const & u, A1 a1, A2 a2, A3 a3, A4 a4) const
    {
        U const * p = 0;
        BOOST_MEM_FN_RETURN call(u, p, a1, a2, a3, a4);
    }

    R operator()(T const & t, A1 a1, A2 a2, A3 a3, A4 a4) const
    {
        BOOST_MEM_FN_RETURN (t.*f_)(a1, a2, a3, a4);
    }

    bool operator==(BOOST_MEM_FN_NAME(cmf4) const & rhs) const
    {
        return f_ == rhs.f_;
    }

    bool operator!=(BOOST_MEM_FN_NAME(cmf4) const & rhs) const
    {
        return f_ != rhs.f_;
    }
};

// mf5

template<class R, class T, class A1, class A2, class A3, class A4, class A5 BOOST_MEM_FN_CLASS_F> class BOOST_MEM_FN_NAME(mf5)
{
public:

    typedef R result_type;

private:
    
    BOOST_MEM_FN_TYPEDEF(R (BOOST_MEM_FN_CC T::*F) (A1, A2, A3, A4, A5))
    F f_;

    template<class U, class B1, class B2, class B3, class B4, class B5> R call(U & u, T const *, B1 & b1, B2 & b2, B3 & b3, B4 & b4, B5 & b5) const
    {
        BOOST_MEM_FN_RETURN (u.*f_)(b1, b2, b3, b4, b5);
    }

    template<class U, class B1, class B2, class B3, class B4, class B5> R call(U & u, void const *, B1 & b1, B2 & b2, B3 & b3, B4 & b4, B5 & b5) const
    {
        BOOST_MEM_FN_RETURN (get_pointer(u)->*f_)(b1, b2, b3, b4, b5);
    }

public:
    
    explicit BOOST_MEM_FN_NAME(mf5)(F f): f_(f) {}

    R operator()(T * p, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const
    {
        BOOST_MEM_FN_RETURN (p->*f_)(a1, a2, a3, a4, a5);
    }

    template<class U> R operator()(U & u, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const
    {
        U const * p = 0;
        BOOST_MEM_FN_RETURN call(u, p, a1, a2, a3, a4, a5);
    }

#ifdef BOOST_MEM_FN_ENABLE_CONST_OVERLOADS

    template<class U> R operator()(U const & u, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const
    {
        U const * p = 0;
        BOOST_MEM_FN_RETURN call(u, p, a1, a2, a3, a4, a5);
    }

#endif

    R operator()(T & t, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const
    {
        BOOST_MEM_FN_RETURN (t.*f_)(a1, a2, a3, a4, a5);
    }

    bool operator==(BOOST_MEM_FN_NAME(mf5) const & rhs) const
    {
        return f_ == rhs.f_;
    }

    bool operator!=(BOOST_MEM_FN_NAME(mf5) const & rhs) const
    {
        return f_ != rhs.f_;
    }
};

// cmf5

template<class R, class T, class A1, class A2, class A3, class A4, class A5 BOOST_MEM_FN_CLASS_F> class BOOST_MEM_FN_NAME(cmf5)
{
public:

    typedef R result_type;

private:
    
    BOOST_MEM_FN_TYPEDEF(R (BOOST_MEM_FN_CC T::*F) (A1, A2, A3, A4, A5) const)
    F f_;

    template<class U, class B1, class B2, class B3, class B4, class B5> R call(U & u, T const *, B1 & b1, B2 & b2, B3 & b3, B4 & b4, B5 & b5) const
    {
        BOOST_MEM_FN_RETURN (u.*f_)(b1, b2, b3, b4, b5);
    }

    template<class U, class B1, class B2, class B3, class B4, class B5> R call(U & u, void const *, B1 & b1, B2 & b2, B3 & b3, B4 & b4, B5 & b5) const
    {
        BOOST_MEM_FN_RETURN (get_pointer(u)->*f_)(b1, b2, b3, b4, b5);
    }

public:
    
    explicit BOOST_MEM_FN_NAME(cmf5)(F f): f_(f) {}

    template<class U> R operator()(U const & u, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const
    {
        U const * p = 0;
        BOOST_MEM_FN_RETURN call(u, p, a1, a2, a3, a4, a5);
    }

    R operator()(T const & t, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const
    {
        BOOST_MEM_FN_RETURN (t.*f_)(a1, a2, a3, a4, a5);
    }

    bool operator==(BOOST_MEM_FN_NAME(cmf5) const & rhs) const
    {
        return f_ == rhs.f_;
    }

    bool operator!=(BOOST_MEM_FN_NAME(cmf5) const & rhs) const
    {
        return f_ != rhs.f_;
    }
};

// mf6

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6 BOOST_MEM_FN_CLASS_F> class BOOST_MEM_FN_NAME(mf6)
{
public:

    typedef R result_type;

private:

    BOOST_MEM_FN_TYPEDEF(R (BOOST_MEM_FN_CC T::*F) (A1, A2, A3, A4, A5, A6))
    F f_;

    template<class U, class B1, class B2, class B3, class B4, class B5, class B6> R call(U & u, T const *, B1 & b1, B2 & b2, B3 & b3, B4 & b4, B5 & b5, B6 & b6) const
    {
        BOOST_MEM_FN_RETURN (u.*f_)(b1, b2, b3, b4, b5, b6);
    }

    template<class U, class B1, class B2, class B3, class B4, class B5, class B6> R call(U & u, void const *, B1 & b1, B2 & b2, B3 & b3, B4 & b4, B5 & b5, B6 & b6) const
    {
        BOOST_MEM_FN_RETURN (get_pointer(u)->*f_)(b1, b2, b3, b4, b5, b6);
    }

public:

    explicit BOOST_MEM_FN_NAME(mf6)(F f): f_(f) {}

    R operator()(T * p, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const
    {
        BOOST_MEM_FN_RETURN (p->*f_)(a1, a2, a3, a4, a5, a6);
    }

    template<class U> R operator()(U & u, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const
    {
        U const * p = 0;
        BOOST_MEM_FN_RETURN call(u, p, a1, a2, a3, a4, a5, a6);
    }

#ifdef BOOST_MEM_FN_ENABLE_CONST_OVERLOADS

    template<class U> R operator()(U const & u, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const
    {
        U const * p = 0;
        BOOST_MEM_FN_RETURN call(u, p, a1, a2, a3, a4, a5, a6);
    }

#endif

    R operator()(T & t, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const
    {
        BOOST_MEM_FN_RETURN (t.*f_)(a1, a2, a3, a4, a5, a6);
    }

    bool operator==(BOOST_MEM_FN_NAME(mf6) const & rhs) const
    {
        return f_ == rhs.f_;
    }

    bool operator!=(BOOST_MEM_FN_NAME(mf6) const & rhs) const
    {
        return f_ != rhs.f_;
    }
};

// cmf6

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6 BOOST_MEM_FN_CLASS_F> class BOOST_MEM_FN_NAME(cmf6)
{
public:

    typedef R result_type;

private:
    
    BOOST_MEM_FN_TYPEDEF(R (BOOST_MEM_FN_CC T::*F) (A1, A2, A3, A4, A5, A6) const)
    F f_;

    template<class U, class B1, class B2, class B3, class B4, class B5, class B6> R call(U & u, T const *, B1 & b1, B2 & b2, B3 & b3, B4 & b4, B5 & b5, B6 & b6) const
    {
        BOOST_MEM_FN_RETURN (u.*f_)(b1, b2, b3, b4, b5, b6);
    }

    template<class U, class B1, class B2, class B3, class B4, class B5, class B6> R call(U & u, void const *, B1 & b1, B2 & b2, B3 & b3, B4 & b4, B5 & b5, B6 & b6) const
    {
        BOOST_MEM_FN_RETURN (get_pointer(u)->*f_)(b1, b2, b3, b4, b5, b6);
    }

public:
    
    explicit BOOST_MEM_FN_NAME(cmf6)(F f): f_(f) {}

    template<class U> R operator()(U const & u, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const
    {
        U const * p = 0;
        BOOST_MEM_FN_RETURN call(u, p, a1, a2, a3, a4, a5, a6);
    }

    R operator()(T const & t, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const
    {
        BOOST_MEM_FN_RETURN (t.*f_)(a1, a2, a3, a4, a5, a6);
    }

    bool operator==(BOOST_MEM_FN_NAME(cmf6) const & rhs) const
    {
        return f_ == rhs.f_;
    }

    bool operator!=(BOOST_MEM_FN_NAME(cmf6) const & rhs) const
    {
        return f_ != rhs.f_;
    }
};

// mf7

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7 BOOST_MEM_FN_CLASS_F> class BOOST_MEM_FN_NAME(mf7)
{
public:

    typedef R result_type;

private:
    
    BOOST_MEM_FN_TYPEDEF(R (BOOST_MEM_FN_CC T::*F) (A1, A2, A3, A4, A5, A6, A7))
    F f_;

    template<class U, class B1, class B2, class B3, class B4, class B5, class B6, class B7> R call(U & u, T const *, B1 & b1, B2 & b2, B3 & b3, B4 & b4, B5 & b5, B6 & b6, B7 & b7) const
    {
        BOOST_MEM_FN_RETURN (u.*f_)(b1, b2, b3, b4, b5, b6, b7);
    }

    template<class U, class B1, class B2, class B3, class B4, class B5, class B6, class B7> R call(U & u, void const *, B1 & b1, B2 & b2, B3 & b3, B4 & b4, B5 & b5, B6 & b6, B7 & b7) const
    {
        BOOST_MEM_FN_RETURN (get_pointer(u)->*f_)(b1, b2, b3, b4, b5, b6, b7);
    }

public:
    
    explicit BOOST_MEM_FN_NAME(mf7)(F f): f_(f) {}

    R operator()(T * p, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const
    {
        BOOST_MEM_FN_RETURN (p->*f_)(a1, a2, a3, a4, a5, a6, a7);
    }

    template<class U> R operator()(U & u, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const
    {
        U const * p = 0;
        BOOST_MEM_FN_RETURN call(u, p, a1, a2, a3, a4, a5, a6, a7);
    }

#ifdef BOOST_MEM_FN_ENABLE_CONST_OVERLOADS

    template<class U> R operator()(U const & u, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const
    {
        U const * p = 0;
        BOOST_MEM_FN_RETURN call(u, p, a1, a2, a3, a4, a5, a6, a7);
    }

#endif

    R operator()(T & t, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const
    {
        BOOST_MEM_FN_RETURN (t.*f_)(a1, a2, a3, a4, a5, a6, a7);
    }

    bool operator==(BOOST_MEM_FN_NAME(mf7) const & rhs) const
    {
        return f_ == rhs.f_;
    }

    bool operator!=(BOOST_MEM_FN_NAME(mf7) const & rhs) const
    {
        return f_ != rhs.f_;
    }
};

// cmf7

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7 BOOST_MEM_FN_CLASS_F> class BOOST_MEM_FN_NAME(cmf7)
{
public:

    typedef R result_type;

private:
    
    BOOST_MEM_FN_TYPEDEF(R (BOOST_MEM_FN_CC T::*F) (A1, A2, A3, A4, A5, A6, A7) const)
    F f_;

    template<class U, class B1, class B2, class B3, class B4, class B5, class B6, class B7> R call(U & u, T const *, B1 & b1, B2 & b2, B3 & b3, B4 & b4, B5 & b5, B6 & b6, B7 & b7) const
    {
        BOOST_MEM_FN_RETURN (u.*f_)(b1, b2, b3, b4, b5, b6, b7);
    }

    template<class U, class B1, class B2, class B3, class B4, class B5, class B6, class B7> R call(U & u, void const *, B1 & b1, B2 & b2, B3 & b3, B4 & b4, B5 & b5, B6 & b6, B7 & b7) const
    {
        BOOST_MEM_FN_RETURN (get_pointer(u)->*f_)(b1, b2, b3, b4, b5, b6, b7);
    }

public:
    
    explicit BOOST_MEM_FN_NAME(cmf7)(F f): f_(f) {}

    template<class U> R operator()(U const & u, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const
    {
        U const * p = 0;
        BOOST_MEM_FN_RETURN call(u, p, a1, a2, a3, a4, a5, a6, a7);
    }

    R operator()(T const & t, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const
    {
        BOOST_MEM_FN_RETURN (t.*f_)(a1, a2, a3, a4, a5, a6, a7);
    }

    bool operator==(BOOST_MEM_FN_NAME(cmf7) const & rhs) const
    {
        return f_ == rhs.f_;
    }

    bool operator!=(BOOST_MEM_FN_NAME(cmf7) const & rhs) const
    {
        return f_ != rhs.f_;
    }
};

// mf8

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8 BOOST_MEM_FN_CLASS_F> class BOOST_MEM_FN_NAME(mf8)
{
public:

    typedef R result_type;

private:
    
    BOOST_MEM_FN_TYPEDEF(R (BOOST_MEM_FN_CC T::*F) (A1, A2, A3, A4, A5, A6, A7, A8))
    F f_;

    template<class U, class B1, class B2, class B3, class B4, class B5, class B6, class B7, class B8> R call(U & u, T const *, B1 & b1, B2 & b2, B3 & b3, B4 & b4, B5 & b5, B6 & b6, B7 & b7, B8 & b8) const
    {
        BOOST_MEM_FN_RETURN (u.*f_)(b1, b2, b3, b4, b5, b6, b7, b8);
    }

    template<class U, class B1, class B2, class B3, class B4, class B5, class B6, class B7, class B8> R call(U & u, void const *, B1 & b1, B2 & b2, B3 & b3, B4 & b4, B5 & b5, B6 & b6, B7 & b7, B8 & b8) const
    {
        BOOST_MEM_FN_RETURN (get_pointer(u)->*f_)(b1, b2, b3, b4, b5, b6, b7, b8);
    }

public:
    
    explicit BOOST_MEM_FN_NAME(mf8)(F f): f_(f) {}

    R operator()(T * p, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const
    {
        BOOST_MEM_FN_RETURN (p->*f_)(a1, a2, a3, a4, a5, a6, a7, a8);
    }

    template<class U> R operator()(U & u, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const
    {
        U const * p = 0;
        BOOST_MEM_FN_RETURN call(u, p, a1, a2, a3, a4, a5, a6, a7, a8);
    }

#ifdef BOOST_MEM_FN_ENABLE_CONST_OVERLOADS

    template<class U> R operator()(U const & u, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const
    {
        U const * p = 0;
        BOOST_MEM_FN_RETURN call(u, p, a1, a2, a3, a4, a5, a6, a7, a8);
    }

#endif

    R operator()(T & t, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const
    {
        BOOST_MEM_FN_RETURN (t.*f_)(a1, a2, a3, a4, a5, a6, a7, a8);
    }

    bool operator==(BOOST_MEM_FN_NAME(mf8) const & rhs) const
    {
        return f_ == rhs.f_;
    }

    bool operator!=(BOOST_MEM_FN_NAME(mf8) const & rhs) const
    {
        return f_ != rhs.f_;
    }
};

// cmf8

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8 BOOST_MEM_FN_CLASS_F> class BOOST_MEM_FN_NAME(cmf8)
{
public:

    typedef R result_type;

private:
    
    BOOST_MEM_FN_TYPEDEF(R (BOOST_MEM_FN_CC T::*F) (A1, A2, A3, A4, A5, A6, A7, A8) const)
    F f_;

    template<class U, class B1, class B2, class B3, class B4, class B5, class B6, class B7, class B8> R call(U & u, T const *, B1 & b1, B2 & b2, B3 & b3, B4 & b4, B5 & b5, B6 & b6, B7 & b7, B8 & b8) const
    {
        BOOST_MEM_FN_RETURN (u.*f_)(b1, b2, b3, b4, b5, b6, b7, b8);
    }

    template<class U, class B1, class B2, class B3, class B4, class B5, class B6, class B7, class B8> R call(U & u, void const *, B1 & b1, B2 & b2, B3 & b3, B4 & b4, B5 & b5, B6 & b6, B7 & b7, B8 & b8) const
    {
        BOOST_MEM_FN_RETURN (get_pointer(u)->*f_)(b1, b2, b3, b4, b5, b6, b7, b8);
    }

public:
    
    explicit BOOST_MEM_FN_NAME(cmf8)(F f): f_(f) {}

    R operator()(T const * p, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const
    {
        BOOST_MEM_FN_RETURN (p->*f_)(a1, a2, a3, a4, a5, a6, a7, a8);
    }

    template<class U> R operator()(U const & u, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const
    {
        U const * p = 0;
        BOOST_MEM_FN_RETURN call(u, p, a1, a2, a3, a4, a5, a6, a7, a8);
    }

    R operator()(T const & t, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const
    {
        BOOST_MEM_FN_RETURN (t.*f_)(a1, a2, a3, a4, a5, a6, a7, a8);
    }

    bool operator==(BOOST_MEM_FN_NAME(cmf8) const & rhs) const
    {
        return f_ == rhs.f_;
    }

    bool operator!=(BOOST_MEM_FN_NAME(cmf8) const & rhs) const
    {
        return f_ != rhs.f_;
    }
};

#undef BOOST_MEM_FN_ENABLE_CONST_OVERLOADS

/* mem_fn_template.hpp
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
*/