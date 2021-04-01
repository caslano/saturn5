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
V1ZGVo4H4/CzpA9XWtXG3q/+hclU0k/RZewDb/juTT5v1nmMFnYMf1vXfIIrFkgX072LJmbjj3CmuCWtLh2hgRg0Z/0btozfi9VhLchwZUfsBF6bglol1wQMlK7NogCIORgltTN6U0hFDRrybzLUdErr/g6u1pctnglCxf+5LY3Rqkn5IajDRYxfT7pIkb2f8EFU0edUemh2q6tjaM9riwYZXzrCQBYpxtB2t6n5Sq6jQBqUnUBtt1qHYIa8Qzg1ern18hmm1EQXd1hPkePc2tzJogughqoEZnlO3SqxfSsk0hjwmaL333yTrRTZ+5PmD/SzZMgyzTHhR4bq1poht5+huXUUQ99wwq60yIqY/IX7QLMj6fpzFDN04J/xI7qSpcvSUwJq1BPGZIN28pSKWuTfmYxc2gzDVaBDBakm+JsxIa1shryDSLsRGktIIl5eUcsAX2oN/nJ5SKyBPi/DKkUnlUB3YqzNy/tBXj78ljkEmKRQS6DDHFbocA62sEkQ47MQuzVxNDl55+S/DwL7FIxKmkWKienYsglOpW2XFij3iw8L9szDYLf/sQ==
*/