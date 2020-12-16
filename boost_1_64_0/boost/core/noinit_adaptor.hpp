/*
Copyright 2019 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_CORE_NOINIT_ADAPTOR_HPP
#define BOOST_CORE_NOINIT_ADAPTOR_HPP

#include <boost/config.hpp>
#if !defined(BOOST_NO_CXX11_ALLOCATOR)
#include <memory>
#endif
#include <new>
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#include <utility>
#endif

namespace boost {

template<class A>
struct noinit_adaptor
    : A {
    template<class U>
    struct rebind {
#if !defined(BOOST_NO_CXX11_ALLOCATOR)
        typedef noinit_adaptor<typename std::allocator_traits<A>::template
            rebind_alloc<U> > other;
#else
        typedef noinit_adaptor<typename A::template rebind<U>::other> other;
#endif
    };

    noinit_adaptor()
        : A() { }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    template<class U>
    noinit_adaptor(U&& u) BOOST_NOEXCEPT
        : A(std::forward<U>(u)) { }
#else
    template<class U>
    noinit_adaptor(const U& u) BOOST_NOEXCEPT
        : A(u) { }
#endif

    template<class U>
    noinit_adaptor(const noinit_adaptor<U>& u) BOOST_NOEXCEPT
        : A(static_cast<const U&>(u)) { }

    template<class U>
    void construct(U* p) {
        ::new((void*)p) U;
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
    template<class U, class V, class... Args>
    void construct(U* p, V&& v, Args&&... args) {
        ::new((void*)p) U(std::forward<V>(v), std::forward<Args>(args)...);
    }
#else
    template<class U, class V>
    void construct(U* p, V&& v) {
        ::new((void*)p) U(std::forward<V>(v));
    }
#endif
#else
    template<class U, class V>
    void construct(U* p, const V& v) {
        ::new((void*)p) U(v);
    }

    template<class U, class V>
    void construct(U* p, V& v) {
        ::new((void*)p) U(v);
    }
#endif

    template<class U>
    void destroy(U* p) {
        p->~U();
    }
};

template<class T, class U>
inline bool
operator==(const noinit_adaptor<T>& lhs,
    const noinit_adaptor<U>& rhs) BOOST_NOEXCEPT
{
    return static_cast<const T&>(lhs) == static_cast<const U&>(rhs);
}

template<class T, class U>
inline bool
operator!=(const noinit_adaptor<T>& lhs,
    const noinit_adaptor<U>& rhs) BOOST_NOEXCEPT
{
    return !(lhs == rhs);
}

template<class A>
inline noinit_adaptor<A>
noinit_adapt(const A& a) BOOST_NOEXCEPT
{
    return noinit_adaptor<A>(a);
}

} /* boost */

#endif

/* noinit_adaptor.hpp
ryP6l2jd9JG70lnBIk17A9N+CrQ3M+2kEy3tbUy7H9DeybQRoL2Hac8G2vuY9gmgfZBpA3extBsSeSdZ2keY9kGgfZxp3wHaTUxbe7KlfYZpZaB9jmkvBNoXmfZhoH2FabcC7etMW3Y3S/sW0/qA9l2mHQbaD5h2r1Ms7cdMOxdoP2NaBLRbmHY90G5l2ta7W9pvmZYD2p+ZtqPJ0v7GtGmg3cG0lwLt30y7fJGlLVqnaTcD7a5M+zXQTmbaudC+d2fatUC7F9OGT7C0U5n2AqAtZdrDwE5PZ9qWe1raGUxbA/W4D9HUeevjoHyrme+Lsa4a2UPE3U16D35f6fykmfKhRPHy0czxfIdc3u/JfoWn6bmdkWI+Q15gXIO/AXGFEUMeyrGWykE4jcLJ0xzNG+FdAOLB9Ujsm23ofMze416Hsog/fqdWZ9wY1vOR8Jsw7wh0zGcOmBfOM1weOMcqx9qB+3UBTsfSBq+dR7m+d9y6TlL8ouvuWzN+UX9vQ/GLdF5S3J0PiPPSD+06IDc6o29Krw4wCOsIa8pN6wzOqwT3Tc79AVcnHCYuHejTP4/O2DTkoQXfmKVjrBiD77BlxedpQl3g1QvsHbtAvu+dwXXdFsMXHMYbWZ+H+vlcOFd/m/jQv64WIC2Bbl0vEJblAcDj+/dXi3JCf9x+17+NRxGG5xEODxw1gB1dsA7GCGo5PM/uIUxMLwwk8bjT0Nk53ZEMbMDGxGmB9tcdg4+XwKRbIb3Lg6ZEfb02n/jtxO/5/HbJbXi+7fNYk7gN61dSl0mZkXKt690CjwkpZ1/fFMeg7XGbudG10K4eatuU/TK0RYDz5d0+HkTnARsUeemIEPrUAZGH5HjxUkYkPj2sWT+RzwOPw7COYz6ft2fOB3iUWsfxkDeo4+GQR6zjJSFfUMepkAfqCO88DZ+NvdYaYHLsL3Nm5/DVHcervxfGj9I64NGYKUcZxo+FylFBPsYbW3dI8dh+i/3D903R6B43ePBeYFaXhWS6LOYsJsDd+e4xhDu+PL2Ist+NDPbX7OoDvV/mydCrG3zDGMphl6KR8ThfhiqGCmGm84H7ITDTQUbG/+TaSGHOK8flBpdjq70b5wK6YYQ2fB1idHsI555X+3PIQ8uV0iWFHN3nDCYSlIl3T/hmiqnLs2CuA3+1SftZSBvFm3BbnqtRblS7PImOb4J0/p2IVuNrh/0GzyJwNB/vfV5CZb/LMh2P5+SG9j5UD/FO311XS+vKKykfNG4aORtYv0rf5j3ZyafFvztYDq8OJjxv9XnA4RPcuSvXceVO3RNr+M5hOX5j8SrSS+cy/Z7zlIb0nxaLbDHqJYz9RSmD2F+ABbG/AAtjf1ksjP2FmBz7i3ET+2u1gNHVgCA22DW8FuGop+RUxbhhJi3PlCQ3xMR4YLcD7sdeeb3Ok18k2vz+DGn8eCpTyTmrRuqOvcvtq86LhfZdDe0Le34cg8Zm2OLh/SbihwtzzGDwtzCOZ00zkP5tIX643rgpcX04qq0Qq351o2/BWF7K2+5WcVy4mNoiTsS9GVdlyMPraWJkjga+FRCXCx6du+XaKLbbO+Jx0X31jTY5CmViJvvdC7YvE+GHpkmcI/KYFjOA/IsCD/3P5DHl4GFcoEuxDIy2ABakVdIb1acqVaDPLnGce9c6TyeAjZqysrLwfBcxVlND/ZUfHYf2uPX47HuSn5WH9xNAnh2fPkD1jkcMmttxLXY90Z0zEXi8nfDcoHlCDtDdjeDnYLT+vabyo4ljWQ/WJbyTrdPx6b65f7MwH99KwX7wJYmP12EbYd0b8vAF1dIMyAvytRfGQd4TPJ7w4jf5DwLe9GvimP+TJdl65oa75J4=
*/