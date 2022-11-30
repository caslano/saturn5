/*
Copyright 2007 Tobias Schwinger

Copyright 2019 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_FUNCTIONAL_VALUE_FACTORY_HPP
#define BOOST_FUNCTIONAL_VALUE_FACTORY_HPP

#include <boost/config.hpp>
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && \
    !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
#include <utility>
#endif

namespace boost {

template<class  T>
class value_factory;

template<class T>
class value_factory {
public:
    typedef T result_type;

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && \
    !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
    template<class... Args>
    result_type operator()(Args&&... args) const {
        return result_type(std::forward<Args>(args)...);
    }
#else
    result_type operator()() const {
        return result_type();
    }

    template<class A0>
    result_type operator()(A0& a0) const {
        return result_type(a0);
    }

    template<class A0, class A1>
    result_type operator()(A0& a0, A1& a1) const {
        return result_type(a0, a1);
    }

    template<class A0, class A1, class A2>
    result_type operator()(A0& a0, A1& a1, A2& a2) const {
        return result_type(a0, a1, a2);
    }

    template<class A0, class A1, class A2, class A3>
    result_type operator()(A0& a0, A1& a1, A2& a2, A3& a3) const {
        return result_type(a0, a1, a2, a3);
    }

    template<class A0, class A1, class A2, class A3, class A4>
    result_type operator()(A0& a0, A1& a1, A2& a2, A3& a3, A4& a4) const {
        return result_type(a0, a1, a2, a3, a4);
    }

    template<class A0, class A1, class A2, class A3, class A4, class A5>
    result_type operator()(A0& a0, A1& a1, A2& a2, A3& a3, A4& a4,
        A5& a5) const {
        return result_type(a0, a1, a2, a3, a4, a5);
    }

    template<class A0, class A1, class A2, class A3, class A4, class A5,
        class A6>
    result_type operator()(A0& a0, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5,
        A6& a6) const {
        return result_type(a0, a1, a2, a3, a4, a5, a6);
    }

    template<class A0, class A1, class A2, class A3, class A4, class A5,
        class A6, class A7>
    result_type operator()(A0& a0, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5,
        A6& a6, A7& a7) const {
        return result_type(a0, a1, a2, a3, a4, a5, a6, a7);
    }

    template<class A0, class A1, class A2, class A3, class A4, class A5,
        class A6, class A7, class A8>
    result_type operator()(A0& a0, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5,
        A6& a6, A7& a7, A8& a8) const {
        return result_type(a0, a1, a2, a3, a4, a5, a6, a7, a8);
    }

    template<class A0, class A1, class A2, class A3, class A4, class A5,
        class A6, class A7, class A8, class A9>
    result_type operator()(A0& a0, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5,
        A6& a6, A7& a7, A8& a8, A9& a9) const {
        return result_type(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
    }
#endif
};

template<class T>
class value_factory<T&> { };

} /* boost */

#endif

/* value_factory.hpp
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
*/