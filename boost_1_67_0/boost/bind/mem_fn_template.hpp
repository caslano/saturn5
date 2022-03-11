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
02L+AG/1T7pkkD0T53c8eVcNZsC8Ux2d5XWw8+lAFqStRttpIu3m+073YNfhY6QO/+KwMiJv2ayIECu6exbelcdeMHaZw61Jkq55D5MRe1vXImv3a/lrsWl48Uh656rjneEkHEwQUAtFRYWWficGSIsZh50c0S8EChsc8KWMAAnE3/Ge32pySIURx1QpLyqvov+Vn6aSXTxMsdCtkbvB3MDO5dyRIrrFOh/0uHtnb6seWll75Urs/qz8XNNCPwwmanGPAQcTDStNTWH+16fK4RI5JVBGra378RSSdPzHuz2/0Dbfq/G9KWG6VJkKB8lRqtDoin2A6z9iLjecRV6oXK8CF4i6XScloO02vxXEH2H7cczzvOHpEmZQNMWAR6XWMfbrz2YQ7OvKaGKdftQMsP5UakPQFiRg/hDp4jrpp+B5/+HZ2RvUysLOcfdX1+NVh6DetcBXn8nVpS1P/YHSIkSQ3ZrPxe7s8KGGebq/3DAWDJzr5o5/THyo1DcBLTZTHuDMVBYWJsiYx/zpB8q9EZGkfsPvMYTu/QyVUpEKTDoc67Qyn8uN2Dbi731NdSXt64SAPneIYKP1B56sl88e11yic0GTP9WragT+az21v44Yiji4uGmoCXGUvm7bqUxqnlaIBQd0nTVPzxCDBxA2kqHwRMjX2zyAw9HvdtIvzlK/kPVeKIKK1uaJGFwn7cBgWIn7b4kxkNAs/8HiXzmA1GJcHSWGE7zmpMKWgs9rVcfF89fK58PKhs7lIE0N3D0CW9bsdJrqsTy3c0Imm20WsKFKZ1B0ave7LHtW4xIrG9DHINA2N2c7LJHUxXB4ZZzrPap7H9rCW1ERvN67Dxvqw7Zcg4Fhc5fjcVb+l3tFLINuFH43XDOFM9WyDvr8KMByz1hEiGzvhTGsAWHA+nK+WMbMGKKcbC8qLKSubQglKPr5/fo7+r2/p8pR1wQH92xE00XTPSNmwI+KKfvAdF/nF+QR/ohsFhggbzdGm307202ZXO3y43dKZmETIvqmMf7G1vm2c+T7HRexo+5We5V2me7+D7ER0wIklI51VSvPKgelKQFytIT50PLfpKJuAmdgYHsApKAXGpiGsNpuo+os3sPDvbC+t/ibI6w/EJzLqTWei11P2T0u+C3O7Wf2iPVbNhXK/4ZyYjrFTYkjsggm+LgK3AsTkcln+RWs2pMxPPbPYTynu94IuTqWYi8J78wD3M0g3fPq6+NbRrLA1F4YeRXpHBu3CmlJuLwsT8lQdqFQjCjld5aZ9DrTUqlGx7XWR/3LAhDrvtZMnzMsbVIkjIH1qFN1+Wv409qzu24XwDSaaDAC8TKXqWBa6aWkEOv+17GrI1DXKeKtw+6bpaVAPLmqrtOGwMEPx+Win4lnILl8d79ciooNefnKY/FShQCA4xdiFAO0aWWOLLf98M4dzuaLKMnyH1tGF65fxzTPIc9f65d8s3TRpq9raRhwcNDBB2m4eJAlspXOMsxgjhScA8aAJnS8LeRv10RPoCezA7K9TUAzHe9pUaKpEZg+8rXszTjyvARa861i1V7uBD/tPwOnBUvrjkQkgqzqHsr50iKillSxy7Ek2/bb37t6PXA+H9oKnlYMcxhhb8biodf/7jhICreBw0tEiV3byxdWNWnLjJU/DhpCN6r0IZDjvLxysXV7nrqS5LKhrvjsb06RiPVB0QuZ2sNdZNzNBp8I79gMJCjB//ldBg8TVIiK+cnjEfSrzMyBMAtTdpobJ8QJ8rJQ4cq1tuuIsuUt3DTd0u5nQshECjxWjCv8LRqqWhTsZRohKB47ex14RtDcoG2jcjVDJeH111VlbLuC15NemY435Ea8tZwx4yeqQlic0FYF5ExW2Ms5CQWkekuaL2Cy7B86DnCCzgxLi3NQGhPwJLMKW0egIpS87iGeb2kLuEXyzh4Z0anwYTnMJ4Q3wBP58R8RksLVwXJnEIROw2CvytB4QfpFknPttImq1Fx2rEdiJVBkHKBO/jQtEK3298Vd/zpHScjvWU2gpz50V4GEwHynvZiwF+liRUPSrG6YG9jE4PsbIPCdHLpl1nMXVlklWQgxIta61oTT3wc8HJk8UfajQpHncS/IMm9OKHfgb6kGF3H467mfvq8PyqKXJwPfTXN8hsWIeIz43Mn7qkVnTLGlhI7SSfQ+U7ZYSUKAuQqRFWwdM2mFu6cs2R5sZXvt977Qo7n39f52rINY892SmixbnMFFLNO+FjgvNX+Dc+EH5kV6EYSOv6UiezClsrTUkUJ+yLouWGfq2sfJSWTgA0R8Y/FIAnY9px+QBukHG9MclBfsFRf/2PQyVYGAqFgSBGvjurfC5AzQ6KM9Jw1jl8O7G2M+a7h+X9hpy7TZidnDz/QxiRDQV+QpUT60PJqLNk6czl7ZPTJGMs9W/WGjdM1Q63z9MbCz+6NRTrzJdRRfDdyl6oD0Dm1/x+u669lnbl+in9Ae1N+uEy7ge1kKYLor5V+FqHWoWV5EUsR/H5FVybKj0ebSAxcqC3g0KUbH5mrP4ClTSWoydpmc9ZvopcqzttIjs/29zNEq+DXpfdXj++akdJlzgH4H7w5ztoxwg1kwsQ1K2pawR24ooSJEQnCvBHoWYaIxnh31U60rmuAI61d5dsfGFv72PV2LjXHlhS01NEAyO7WjYyQmHEN0qDBRgtMslX0/KnMalo62UpdDpabn80zr+fD8Rbx1P/oWQbfqj72nAesPiCMtmLEw+u+YND+d76lftP4AhaOYkeRcxM6nxKLev4pBNiwuKzkDZATaLs7CgDO2xYPfXqR6iOJMImUjFzgloMu/637youZGLViUVtktrbTZfqz8umL7bm2gFmDWIwXHQd7rjwlf/U0UagY3LlitUW+0+uq+CtoAxi70orX61+0GwZPQy1cn6hHsKWuGf3Vxb/vDP3PrS/SzRlpgpbKfAzwU/nivoVFq+c4fgMUlQU2S6AoTTugxKNleNzq/63MTebzZ4yXZPa3NXkKKbEhuj6fCWGN1+x4/0N3AQQYGthShb/XGP8l7kI10FqHmGYS9ZHxjGuP6OWe7GeO9xbK3e2C7bOVLu7JL5DgiADkKNZKLkoUAxaQC3Mpi8jXLfu+bicxNjAudtLOJTGbIjLWb/1o3cqcPMr5JuKqDh1GpPKV+YdIEIBHL771+/c4Pzumw31ng/b5Rex50zHJUrFYOmMxgm5YbgpcbmYxMBaOk6IQNCWlRcDj+/PVt19NxmcOApjaOLIl+o8EhkVAeb/CxxP+8ObDyN3QIocMPZMzXLzsqdoF9N2vJzQiXVK/xvTS3bYP/4UUYoY+Ahqzpj2lXJqjnZOcLjRCpZlAXGnqCQye2nirX9mcflc+xWs26Jnsujn48WRpQPmza6hbtfgYZOzlEVShPyxthVHc6c6kcHwlqTOHz0/uqhLd5OCiwJdzuAWCqx4NRFx/kqcHe6VNW1b7dda3gc74s6GmniBk83K9t2xr+Ii27+m2gKISWHiL372EMIEbEwc6AEj7CFvEkhHftHd9N7+9hM5O7EBsxxUPlq49gdDRzYk8vGkW/WlI7ij2InJKGknXnJ9W2Hc9vOZvn7YEf6qh86qCk6RJEFEwiSwmBdT/A4ViTJgeFt9OwYbzhQJteHnrdLlyT+JTc7KYYn19r+cquIyX7lWI9jbENaNQF0HvrjJ9+SAZWnMG1mN8OnkDSe/Gi8V5VE05736C3tF0R+Qb/iVq74zPw/U2wwySSEL47RrqzDqAAzS+aF2ry4PrgC9Kot9vrT6CSumAQAAlQWb5b0thS3DccAM512FEzTt3Y4dvqDkI7vnkYdNijaq3Uafafj5hBQdlhxjByvWnzSA84sv+SfMYEN9sX+GAHzRa2nefXCWBoDlH5W0SeVLKcXD2yTOzg63g5biQ8OG8Ibk+7bXvM+V7JEqFDGEl/K4zZi8bG0gY7MlPLm852jMyMYAspz6DaZMTUtx3QJeFMaDs7a7ILZHa4Kc6al3V6h01P7e+TQJcYfmTVuMRpEA71Ey12QJR3h7RxZhqRRuCkjcYSDREUAQmyoCFQKmW5YO/jBUgj6w1o0bAb8aYY4dl7jldxI9qsxLjg/mgTuhfVmXNaPmWz17/5WewXMK6m2qdabZbjbkq8ftQ16iX6EyRgMBALpZ/E2CAW+Mvu2B4SFLvT3pxuzOsw03LL+DzTeRsV1RnpiceN5t4gKooIBSkGr4s/e14bCeFmQvaDOCOurntzlwxdRWVP+byCR/2KuS3p+a+McVjforWdu6LlJtLAXGNLKXiuMIhcUUsLqp2dYjr8Iooh9UAHcXIyoAs+ow7cHvyCXTp0QnX8qdlGJzJCYYFUcAfh8+D42vk4m2ViKld7nS+JrkyxReu2fu5HWp3vbcME47vVKQ5otJ1UJzCGNyJAWCLf344+pCsZ398s23lZp0pyQniwwI8E9ZjQ9qtXrsbjg6KXTFbvcYycohh1IDUU/z1PJA6VkdexwPM6U15CtB4Vek6LyDwllv19FfvapVqyLkSffzoZ6BXPLKE2XkhMQihh23J+KnBBufjc5vt9gTkgj6w302j4K7HjyVOh8HmYDkY0D9q2ZMfvutZpgooASsdVMlTbRSSw45HKdloHQ4le1f37er3J0hVE0Cf14I6uptVIst6dQbecJ+oQnUyU+Ys4rRZhxzfNT2ZbGi3mKIXxub6nG/0eiVmDgoBvlhN5Zz3xKlB3lIR+BIb1Bjz2argyB+enHT4Jg+B+uPZ7yG/YAYEWu7efiYcJZpfRmme7N4SnXkWQ9heBcVn2dxgvjx03osWhc/2bmJUte3ju+IVjaoGF0JzDW7eRlBIik69S2Z77a1jPS7bVoJPzCO5o7+TAscLdpR5qhpYSRk0hxZSDIE9cPnWRHbpcQd8vDPzwEyzj2s/hARtbx1ovz8BBCh204ZpEpQfp7+B5SfOrm3gi1+8zbB1t7UwYSPz5NDB9I+diLbjUPoNPRg2BkUfHO+Sl4K7GE7viQt5+7lUsDJjJERKS42xObYjBsz6eZGnokpYPpzmZjk/ojM0z5465qAoHxCZllVq2dz0Drm67R+esFQ+Hz68CN7oDcR0PgfQRJb8Fy+vu96v7hE5NmBVhmrffplIHHbAE/Szh6Pco5SLBAk17fu97jzOjxcbzcyQDWW2Bua4vdyqzs7qjYm+kOr+bnZQKH94+sAhvTZH/tL55BXtPwov83U54GQxO1PG2Tj9vxmSQXY3/LYs7Ws+oDCK5L51lDcHSoqIlZs3EXuS3+x7Yymxcez7YmK+1PWaIj5CNsGAWNRB9r3vFfKXCONJZUlCy/XlqdmXf00FUoQZLl2n+LH1jDjyaysyccyGGMEVODdD9SQ4TLgr+zAdItWsCkYyhwomfShbj9nljRvAFq528AzuFySDgTuMBjzREwKmABJ+IgBMoa/ORybQcgOaSYyDzaSxxCOY3FBBcyGziScAozWUlRBhBDcKON8bApb0ayCLmgPRRrH3r2OIunRpnrpnrPUuqvTIkWPhVZ24x2fNWHpjmetKCdxtNwDoaZ9HX9hUApCx7Q3T74BuC8qJ/5BXUoDLBfqt3KYjsagtfdIo7ZqV/11OmtsXRT/BjJg+GePJ+mMnkilV/+c2oR8IaTC+JpKbSPUJaBwJ9jzTvBEDYuzkjhoPVmuJv/xIKaVvLC8nlsGGpYUlog5JcpNfkGdoGUx8PaZXmJHh8ZlbpwtuNwJSIY0udjmtHd60MbRua7Z3H+aS3RT9KyHQl6DvRqmanMkNOLC+vdvqbrxkm3HE3f1vrc4560dBitj53M3ZsdEANXStPQeC2UwkS+c7QzomBgNfKFNiVsPGWBnJ73iBOvuFVtvC50FO9rC1F5p8WcO2B7PKTqyuiAtoxtgBMpAFvh4kqxspgmbTx9NUxVEsXNvLrl3zaPi1dq8PywBWGYdt9jAuC/Z4PtH2lhH79w2A5Lo8Gv/TQmPmIFyXJc836pcv1lV2Hq3N79gZSB+HL17iLF2raE4iAJfY6Oc6UhXNwRet8qfxIKe3vsdw/3sHnV7WDjyXIMrpVREOtH3isnA3cxa0QhaMmQ8kxxUdG6Ky6YnnIc7GGlmBUgiEEAyczZl9PucROoR11rKTQi8xW+2l9Vpo7MUU/9I+U92cjwzOC9ayf/dVawHkf4U3VpQoLoOM9ksBiLKpzjlij8NNLcwCQI3cbpMTeSIO7N0NlhbatlQxg8+fTPM4hu38CrJ2pF/UMf8gCTuaZmfa2HI45XU9Q0loasBE2MWsFIShy+/rgOxl1Y7gQX39a30DmjA3wGf2O5KC3YWSPOl7mAuWkunBubTSO9JzRdu1wTJmZhBbAgu6cOJ7O/pdOevOCfPP6f8NR1r0NokEjizeZgvxm+egM8pfp+BFNVFl38SbjBR1Hh1ZQCR7O7ThiBoO6y/6b6RaSn4SC56LW+y2PvSSabOAHxe8E+BRjk7BKsTpjMw6ZJTputQDueVyZ0hGITYhiFRF8YmZBybhSe6WXK2/dPA5s6oI2SVihV2UCySTw99jWrpcDTsnsYy7ONiqirfMcd6OejYB37+e9ZEtGNPm0UV2IRrovt9eBHZ13gyp5q0iRFMn9tfJCoqzILC2ECnFYGNB4gEFV7DxxNBEmqYjEAzP9w/fASr5WvlEVCd04HR0V5Ioq2tUNblK/O8wRyWajBwS+gne81iBrQXudwP6xY/3y2eDbfFZzELSEM2uVJOAutiDBIsgXQjKKqEsj4ZJn81Iem8BZeQqQYXRueSpFV7N/m+5c2uV4iDSL2w/KAwSA5sNd7L3k37BzCVtvbFOKLERgMrBQFzSUQOEnVl+l8HIeYkZQKIA9O9wx7vV++0CmfbeYg4KmtYG8eaBEFI5QoK3DqI52eR66PAPSkjDJEYWNuVyDYuv+krpDBFQsx8sf5/h8KUrYUv6UBdwlUhFZ9qO2PwJU2g5aw3ki/GjmjG5lC1/EOrVYLLbbupaqfeG6bhI9Ny9oZvf8jcP+vkaKy5mPSQQa6jW7qqvXareZEuMlmtUahCoB7oBDCQ9sW/qfy4U1pSu1VZj7ovvTmNVlAra91P3bDLU01CQQEuDPeO1ev1DQH6TJjAdZA44deu7kdFDh9hTJUtrCAfJoPmHBdqE7eexlmlllv6SWBaorNQd52dV6mKviBKuoFs6gCNQafo+l3kgqSL15vN9yHyO1nLaZllG+b8LPcLZ5d2zomElir5eu6Hp88ZXLh7F9FuPMhxHCIarSzd98LXUUA2noRkAXhMvUi5Nyk7Hox2p1rNd9Vj/PWpiK4Hw1thCeG/9XC7ATpz7WcWC4DPtkrVmHDgoJGXRKbmA2h8xfMweHDN9cV+S58rmxxTbTlCfi85DGEcqVABNAfuawFDgRS/+eLmdtrshaD8c50SJh1hXBoSbYz6IxodCHRpv6izvAQPB30bkErq3AKo3I7QHwfXNZjqGhPIRcUokjDqRfSW35Ws/ntl9W0hSAra1e8rddg2g5V8RhJbBDpSvAro5cRFqGFY6xQ+sqerHV93sbvaZFYWNxndKpOnrShGAbu56ubJopyEoJDIykNkB3OjLQfkj6qPKvxI3Xle/HDc1FgNEDiGhCWGLpIndnvDZMrWF46nD0kxhUncHzKNtaovOvpihUuDaLMLl0jXMsQw4bEHKYHoZpCRzYhZCNH9z23mhUEM1WPBQi8aoYYG4e6WCeeNN6cr06TFMYFWY4CnhzDXpW594o0874WgGvkvVWSSFjJAO98ln6Nlvuq/Xo0yOBYwAdcdVQRy2NDxez/04kTj0cILGdAiPrivepAaOAhy/mOPUl+DOV4QxtR7/JNR+l+SM3bCbU1x8Qo2yl8+tvp5+GRGUhPzaQ8nyMz6zHqqTmt4lEghEJpvwCPOYfZAHCm8V276s2RGjx7DtycVbBIHDytChTHGGAx2zQi7QQrCCpt2xX+7s/od9YPDgfZeI9GgiStrIUjFtC9nWL741KVYyh91Tugfadg0rLzkyosh5oOKsDoB2NXwp3+xlnJqBKsX3smPmqx+cuikji4AR0A1C+vCbz9hqHtwxImmjBcD88jOnStWF6cLY8qbuVoWGrKnwtN11rOLOjf3bZrTtcnmK4oilT7HBpxOxpo7zuvrns1nM9DF47w7xlWA56qPdIcHGtUnmMoMIU0vUrdGF+CyluuNcNhSTxkRqzk23/SXTItq2PBgoapm6IsSfjW16CA7onrmOSSKVwZFZHC5MlxkoJdMw4tGxs2epiSMvi1dlge+NKNCe/P4F9FqPdoq2qxe8uChtO3e61gggU/dbphOLH7+jGQLvsizQbrDN56Z/9e45shHnmxxv26b9ZKJ5GdweODEc1IQhr+1s+VwvbOCOJADIwSqDqv4XWkxgSnv6H8OKtA+jJu6B2rgWyZWoR/h1DShUdWY4psEdAvZ4bMigofJLuRGQfL4rmBKuB6+MNUp2yAnN3tweJVn/Abetijij0RnLg7jeTPmRxhiqQqK9jehOd9NZcQ2GhPhoXri2B5TD0ONsJY06pOentlqE9Oo1cCUBNEciiUmtXQ2i9cK7nfmrPLYxRkTuErwsTNjnE2QP8it94Hw23y4GRX6azV36PeXdpDZzKhnydd0u7tH1uBu28cdNi+Te0cGFqvXwH0iW6TZV5g8KQnwX8VD+SLRe+3zPl9LpEfriVHJnjWtjBwUrEN5N/XmlerGoRRuFKD03xwCxn++Ap/e3Na6hkpNMKlkS90rZy8xDkHEDaN3/ehRC1l9Qk4Cch0Olrf9l8RbNCMHz5s97fI4Hdzl71nxxFQLAeO4pl3ZPY/Qbzoc4PJMvncWOKWxLV0hao2b57an9gnSaTZzr2I3Qs4Q4OBm3jRHirjB4Dgtwt4/2G3HOr5lPXQEr2IA4V0DqGcyVp0mvgr4n1ibCdXt4bbzUtrvbjYYmCDUREafjMRsRh3v4lzcQYEy98RH4W6CBIAY/tJ6EhKRkr206Dw2fD8pu8kMfzVa8FZOKEij6LOsCyFXVFOWou6DWq/Aq4DR2jTpjcFZs1GpiGYlShuahVJXfXNjwCojk9Qy2Wp5+oJlbhFweIb0tjdGqyl6BwrI5jf/b1/YubSFVlF4d+Iwgr0/GmrA7xSA3QmWrIfizVN3cknMuBUWJR7U8rwOFSx0zJ5UME6//EquCpGA626LhNrmI=
*/