
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
OlteXj798OHDdykpKV1RUVG5aHG1x2Kxh/+if4J/yZsUAWca7U0UZIlc+7e0nz+xf+y69OFxO7kjw4bih5qPMW2NJSYiuIJ0FCgoKCTRlicwIyMDxxNQroPe3l4YHByE/v5+6O7uhhcvXgBaQ6Gvrw+Gh4ehubkZysrKID8//3NcXFzmiRMnDnzpmwiBAoHyS0n8L8ZBe2DzRm9zgYODMtd5QDFQAOTuCIJLvCQUuCjAE19laE/QgYogpVHN05x3rllY9EdHR0NCQgLk5ubCs2fPoKOjA88bh1evXuH51tfX4/njxlZcXAwlJSX4djRXkJeXB6KiosaEhIS4+WRDYEdgRNiEQP5PyN/g5zK6Ky00E3hJBOQiBEAmghd4Y9jh+D02UL3HB8GeYvDY6Sx0xmvASKYBpN00gIiwUEA55xsnHOeenh48187OTkA+BGhLip8T5FN4/rg25FOAW+SKiorg0aNHwMXF5YEonPyCIwjMCNt+lXvpuVNGOXInVjzU+IEXywqs9vSwx3E70LtuAWavrcASvQPORO2HKGNeqLguDg1ucvAqVAPybhpBaXER1NXV4Xnh7I/jj7M3biy4NtxnbW1teJ444MaalZUFqampgOIBCgoKwMLCogHNgTRmNc4EEA5hMF8C+28kS5xPJPOs6FyoohAI2eyHnVc2A43VBthpTwkMHtTAfGsHcIXQA3fEHjC5egCyz/FA
*/