// Copyright 2016 Klemens Morgenstern
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org

#ifndef BOOST_DLL_DETAIL_GET_MEM_FN_TYPE_HPP_
#define BOOST_DLL_DETAIL_GET_MEM_FN_TYPE_HPP_

namespace boost { namespace dll { namespace detail {

template<typename Class, typename Func>
struct get_mem_fn_type;

template<typename Class, typename Return, typename ...Args>
struct get_mem_fn_type<Class, Return(Args...)> {
    typedef Return (Class::*mem_fn)(Args...);
};

template<typename Class, typename Return, typename ...Args>
struct get_mem_fn_type<const Class, Return(Args...)> {
    typedef Return (Class::*mem_fn)(Args...) const ;
};

template<typename Class, typename Return, typename ...Args>
struct get_mem_fn_type<volatile Class, Return(Args...)> {
    typedef Return (Class::*mem_fn)(Args...) volatile;
};

template<typename Class, typename Return, typename ...Args>
struct get_mem_fn_type<const volatile Class, Return(Args...)> {
    typedef Return (Class::*mem_fn)(Args...) const volatile ;
};

}}} // namespace boost::dll::detail


#endif /* BOOST_DLL_SMART_LIBRARY_HPP_ */

/* get_mem_fn_type.hpp
TGeHDvVM7hYvfZBAz5w7VdiPy/6m2Y8zNPsxgbvNIPr2dxtgMoDJBuhwmhLHm0GvUzcWL4iz2GzuiTPbbIJcoV92yQ0Ki83G5/USbrbZYBGcbQVki2GzyeRE8yiR1WaTiTabq7EPeV6A/ymrZQS6CwWE3CKW8Qz+XKgYx4lYMXZPGY/cEdmWYDaO6C4iDOS1u9ymd92SrHSj2gomGpGYDDq61emjnRGrQacPpCbGiBYKZ7oMs6zgdRdXLLP1Mc9FbM3WS1opc/FXOFd54Ks75pe2S8bvGpUkv9xjsCRwlWFpI+xChGkeDiuZe5MTuJeqiGQkXoGkWG/WHzaJgdaaVxmiRudhEg7JNjok/BfLNP7gz3IT01LX1S2t/SqZaQ7reynXECmtRGLYy2NR9qrFmJsBQiTNqdm3sefhMJUe8abZjiEef9YhpZSFIaaXaGiW+O5fNPppSgVZGRTyNkObfXqPDyplpKP2JE85Bte1hBXdmOoY87fY/9Lh39yi2PH3/TXVsRXiB8o0T8u/X9x40P61N7/Y+lnt+/r5F3mzw2+vn33vMPQzpdn6NUWq7Tq2F+mK1MZ3dRfO1LvRPPuXhyCcJsfVIj6nAucMQltRieMotIjzrhqXp/V2P5t4pGZUFGXNqD95aBViR0gQGLGzNV2tBJblShFj7ciR5CXEbNDZn8qSrT4kRvrx/5LtkeD76DB2p6Z73jr5Xd1iE0xAblIj2FhwPjMsMV4nW3CqpAVnsTSxLNLxr+8ETf2ovQVHTLyccvpHYh5LkwkdTi3h1WTqEagdnkk1DgIXC2TXx2qhfIMK0IUVqUrusjvd2zbq6/nflJGeRJ6TlveYMbzJxdWIF9S1QSIwyqFyv+wiXlBB0wWFVMqlcGxVIZrlYvql2J5kRV0Qq1IFXKnfnjBXqkCv1CPv6pXqVrdSjKbDh5hSHINls06ekNy95TjDsUJqrd7ci+pU8edX6KhRpFv96eK+pHQwwHKYcxOcTKLDwvdCp1zOobULE5vJvKCJZK6+HypMvpSCfLEnKC/2CJ0kEqgfQ/8wY8hlDLkSQy5iIJvzVcq8g9JH+nIqIhTtcNxBA53GSSTxhdwwo74lyVIo2/Uu8SzFfaLoFpI3KIfQl2W0pA2SiEHK5BXa+QjkN1t0mME6yFM7Tsi6D76XN0X+tD74/ky/nJjr0Wc2aOvRt9/S9k8K5HyYz/PhB8YidAxluP09MYaP1XZS6AGj1212UvJDL8KEGZGmI2M1ud5I7NcSD10CxBAdXsqiLcBoCXwmIXgIZCeJniwKmPCoXJ/SjEd24lZxXgdFX/mocQRm1/40EzXivOrx6zV9ZCDwR5u43wTxOWFXvBjFmTyKM+VAyGTFhQT0qfLWVSnPSfj0BGH6UMjaEp+I9/5NKOWlwQmbEoOGBI5CCXTIOs0uGu9C5agDr0XSZDRNNL+4TfCGW9wmaP0s3iZYiLcJHufbBJe9iKf6xZpGalgDia7TaA7oSXcbOshyaxJ7vlMtVtI7twexZ5DZmeLc4YvQiq6qEHKHz1SEeyZOZd9ZoX8KzPK1oLtabpqDrM2lDloKX2SjKCLTB21ETN0lFzld3pAnESP9VP5jm5L/h0dk/vAUJuhiC0EDm4Jw02d1CJo7uwn5eyyW+Wn7szhJziNZokdlYQOjzWf/KH8H4Ge1//DwemetNry+XyONP8givjpRfDz+get2j1A/8jX3TLzfQZ9ez8TTZOghnonPoRD8SC3aldmZwR0MYmGtFpGQyQAZw+Pw64UyECRPlctYyNLuBuN1mfFKkIRwAdFT5BiTiH88wghwtiIKe0B5GRZIqU9wslA4TuQaJXKR6aCNOdduzrXboSI=
*/