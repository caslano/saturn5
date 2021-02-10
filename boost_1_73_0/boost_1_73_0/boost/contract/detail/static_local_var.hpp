
#ifndef BOOST_CONTRACT_DETAIL_STATIC_LOCAL_VAR_HPP_
#define BOOST_CONTRACT_DETAIL_STATIC_LOCAL_VAR_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

namespace boost { namespace contract { namespace detail {

// This is used to hold the state of this library (already checking assertions,
// failure handers, mutexes, etc.). Local static variables are used instead of
// global or class-level static variables to avoid ODR errors when this library
// is used as header-only.

// Use T's default constructor to init the local var.
template<typename Tag, typename T>
struct static_local_var {
    static T& ref() {
        static T data;
        return data;
    }
};

// Use `init` param to init local var (Init same as or convertible to T).
// NOTE: Template specializations could be used to program both this and the
// template above together but some pre-C++11 compilers give errors (e.g., Clang
// without -std=c++11), plus the `_init` postfix is more readable at call site.
template<typename Tag, typename T, typename Init, Init init>
struct static_local_var_init {
    static T& ref() {
        static T data = init;
        return data;
    }
};

} } } // namespace
       
#endif // #include guard


/* static_local_var.hpp
ojYYZhVAHxtBJaIQwJZNxWi+k/yHTrrlJJcwmk7GYZSkozAIvFGShsF4BscwODqFP9taa/uXAQwqttDNhxPn+MQ5xA29SimRq1RSpduMX1SUxKDxJQTutWe9GHn+BiTaY5NojX2tazwxunYogopQ2HZxT4WJEs+CMIr92PqZ1VnV5hTOdNpOhuUHy2TIOO5/i2ZPP4GDEgVSoU5eQmJDxes77Fe12n9n0n304tHEjxI/DKyIYA+IMXHA7xSBY0SWVOkm/d3ikMCRDag8hTqVxgBJEkSsdDEox4KLJc5SZelHAl2YwEIbwR9XQFrcrBXLiCbN6LjnQi+xhraxAQUFNcqUKAJKkFoWVNiWttXOGFKhmh3L0jPcsQ8Zam9B9bwZSqWWEOKhEg+e5xnwGemZ7vKgipdcUAs9i7bqumOiPKAsTXHzwtc0+sFFmLqjxL/x4nB05SV7x/vzIloDUNxCw207sKOsLnhvRHZ50mixVmgbs/0M37pIwx1pcA56prQLXyjSn4dLjpXpo65WWKcBLHn2BWMW+gRpaMZIZRi01gxKzdj6Hg8p8YVuyDdqwJKrConXgTEiYlnhVOKIM5TLFqPUIK3n6/+NtdDnasUfusZooZvoerqN9C7c6TixDs0qmoRJOArHsXWZJJEN
*/