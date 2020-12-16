/*=============================================================================
    Copyright (c) 2014-2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_LIST_10262014_0537
#define FUSION_LIST_10262014_0537

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/list/list_fwd.hpp>

///////////////////////////////////////////////////////////////////////////////
// Without variadics, we will use the PP version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_LIST)
# include <boost/fusion/container/list/detail/cpp03/list.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <utility>
#include <boost/fusion/container/list/detail/list_to_cons.hpp>

namespace boost { namespace fusion
{
    struct nil_;

    template <>
    struct list<>
        : detail::list_to_cons<>::type
    {
    private:
        typedef detail::list_to_cons<> list_to_cons;
        typedef list_to_cons::type inherited_type;

    public:
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        list()
            : inherited_type() {}

#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename Sequence>
        BOOST_FUSION_GPU_ENABLED
        list(Sequence const& rhs)
            : inherited_type(rhs) {}

        template <typename Sequence>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        list&
        operator=(Sequence const& rhs)
        {
            inherited_type::operator=(rhs);
            return *this;
        }
#else
        template <typename Sequence>
        BOOST_FUSION_GPU_ENABLED
        list(Sequence&& rhs)
            : inherited_type(std::forward<Sequence>(rhs)) {}

        template <typename Sequence>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        list&
        operator=(Sequence&& rhs)
        {
            inherited_type::operator=(std::forward<Sequence>(rhs));
            return *this;
        }
#endif
    };

    template <typename ...T>
    struct list
        : detail::list_to_cons<T...>::type
    {
    private:
        typedef detail::list_to_cons<T...> list_to_cons;
        typedef typename list_to_cons::type inherited_type;

    public:
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        list()
            : inherited_type() {}

#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename Sequence>
        BOOST_FUSION_GPU_ENABLED
        list(Sequence const& rhs)
            : inherited_type(rhs) {}
#else
        template <typename Sequence>
        BOOST_FUSION_GPU_ENABLED
        list(Sequence&& rhs)
            : inherited_type(std::forward<Sequence>(rhs)) {}
#endif

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        explicit
        list(typename detail::call_param<T>::type ...args)
            : inherited_type(list_to_cons::call(args...)) {}

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename Sequence>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        list&
        operator=(Sequence const& rhs)
        {
            inherited_type::operator=(rhs);
            return *this;
        }
#else
        template <typename Sequence>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        list&
        operator=(Sequence&& rhs)
        {
            inherited_type::operator=(std::forward<Sequence>(rhs));
            return *this;
        }
#endif
    };
}}

#endif
#endif

/* list.hpp
9y9BOd3jWX8tHe45ek+nQdJ5RNI5JOk8pkunuoV0HpD5UgiNMt8YmU/fp+UNSecd7I+/x0F4GkOxCSPwD7p0z7eQ7imZr8Ii9+9wv8zXHQtlviRJdx5a8QqMxgU4A9NwFi7EebgMF+NKXImrsBJX426swL1Yqc/nXu/5nCHzJVrknhqOlvn0fayelXy+gAPxOI7AX2I4vqhLL/tu7+kd1a137oF5Xe/DZbschX0wHAdgBLrSOdpCOiH67biFdLpKOr0knQBJpzdq2/E+7+l00aWTts97On+S+vsA++A5HIB/1W/HLaTznq7eGltIp7+UZ7CUJ1jKM0RXnqYW0umnK09Avfd0vpbydJB0Oko6l+rSSaz3ns5XUp5sgl3m2yjzdcF0mS+c+XpjBA7HaIz1GCNmJcZgHsZiGcZhBU7Q9n+5r4GxJvt/jZTneuyHN+NQrMNw3InR+AOU8nGfwnv5rpP5yJfcXyA9z+OvjDGj+AR2xCd1y69rYfk/0+23R2W+MJP99oSU6zfYB1/BYPwthuCr+uNEC+m9pCuPdb/38myS8lRLeTbrls91ttflb5T58gnZMt9ama8rZsp8q2V7W4MhWIARuBZHYyFOwfU4Cx2YjpWYjVWYhxvRuf3JtS8uNdn+Zkt6c3AQzsVgTMUwXIhRmI4TcZmkn4mLcAVKvXGd6/13eISsn1BZPyP1x0n5XoDJfng5y1ecjl1xBvbCJJR65zrUe71PY75TLDClqpMlm1BF2E1oJBwjNBE6b2RcEkIGYRfhBOEcwbqpkyWR4CAcIBwhnCKcJwRf28mSQsgkVBDqCUcJnxICqvkeIZuwi3CIcJbQYTPv5iSkEGybfes7l59AfzXCAYJnHzorJ1uJBM++dInrnf3paj361G0nTc9+deGYQIjj/5nYUh+7lFJjP7uz05x97eIIGWX0VUOH9L3bjW9vaq/1wWvgczgmevTFa5L+eIkOtYOr2i/v1QkdLdZEd/+8lETmw4MO8356DSZ99d5OJB8Es/56B8vdffZCp7SzxEvfvQy0E7z14Wsg7gRB6ct3Ho9i4AzvffrqpV/fGULnJHf/vqCfd3D28UtqecyglCR3X79M/l9N0Pf5253k7vfXmMR3CK7+f2eSnH0Ad1Ua+wGmJbfeFzBgprs/YDK6+gRux0bCSYJn/8DOs5x9BBvYxryNOVRztff+grXENRBOEM4SzPoPBvO5+zXGfoTphCpXf0KPPoUn+fwlfomBKZ79C5G4QtaFq59hBp8rCHXS37ARTyif+f9xZd8hdP4+xwpCGqGC0EA4SbBcx/GCkEywEWoJDYSThE8J1hr2e0IFoZ5wkvAlIfx6lkWoIjQQXiV03kIahAxCFeEA4VVC9xs4fhAyCDWEAzf4+zv6J//kn/zTxZy+1ff/F9jycjILssp4IP9ivP9feYY1TPf+/mq5H6mMkzkAc3Cm8gzrDeo58pzkmdOzeCSRVz6p+ckiG60+x+p6b1O82vaVt073riyJs6lxPY3t4ernUPd7yKQNi89qG9Zqu+79WhLnIM74TGeVjL9f11Gej8DZSnluNJYnr1grT6ttT5IPw3vX5B10Up51Za7ydEaHbtxri1aeUu2dYd3dcdo7wzq442JccUFaOdetdsUFuOMcrrKPcbW7yfsHn5PnKZ4iXBFM2W9Ry15QvCGPx0t9bzt05qeioFhLG9W4VbH68vbRrb8g7bMDKav2uVj7TqAWt17Krs2j1Qe40iJO2v+kLfGAOkZCj5f7ZW6Itg+ru9d6+OG3znBBLGMTy7arbtNMxrGJJ8l9pimYgAmYg1OxGqfhD/FyfAcTsRcLm46TcQZOxyRMwmRciDPxKpyFe3E=
*/