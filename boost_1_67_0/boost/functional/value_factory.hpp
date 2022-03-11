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