
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
bWYd1Hk1dJ70g40+ito+gyK6bHiwb4F4oPlOFz0cV6bKi/Ylx6f4twiYddrTxXRmo7iosrC4wqB/jenqNlPpKOX4cqumMzeZRbgpRj2kqz2jCdyAZI5PpTMv8b5cFi/YjuZ+h/lJLy+tyC73Zzjpco5U4N9dnvkhNAWzlVe625HzkyA1nvsd5ibDV1hSgFJ13jHzTKIE021fckGBb7TTAyed+Yopq2TBjrikJphR32/T+inehtS6vuvRia21TpxeTZ1YwaumOlTPjj7UD9Hy70lK4NQ/rAt1Y6Ya+APtq/v4tf5zdJ58vlrrvOtb+nsUpXXeDNKdsUudd416NpsN3jGANlT70qdqfXftSeu7P2eM8myMX6dlsTO6XIautT4rw1ctcHhFotdSn8NvoshXwTWzBZpna4pRxeXscRkP79TUvDMrFO+U55WyoE+9gT4aaQ7DGAnR7hdC47hR1eMTozKTaNVrQ53ndNnC2YYtlHnXa764Qc2lOy80frtR47eb+Bur+UjWa5JF4rWbzTQXP8nyDj9JWtSAn24x+elPpoXhc4DYSrVNlFvlJ/hyHD3N84SsShXHNn2OW0PxRdbo0aWoLhnDPQGsMkr+KdjeVZ9Biuq2pLH9PBdvzDV4Q+bN17xxm5oXd15o3rhd88YdBm/M1bjKwfF38mx21Y3j5xrYaozmjbtM3vg30WR89fxMjpj48uGh6niarrKh572oevPurtEcZfVb03N/j557Jw6xQMbcjDmW+feqOeassaa94hNV1lVO88kiXc6dZ/JJC80n92k+Waz/3s/fKzS/LDD5hRl5gGf3AE0svsDl93VRPFKQVcl2Dm+Or8RXlMPLfjqHwUsPGrxU+99I5xEBO5VTUBDQMb6JPuHYJxn9zs/Wz/S5okheY5Ofm2/opIThCYHybLwemhwnn3Ph1TDNq0tC8WqhQlzH51FXmVC8eUX1eNOpyaTViWvXvLhU82Is/HU6tT/Ec8dw865XxZvOb3e6k6f+O7wn63xY8d7p4hGTf1X9ocrx3XRVzp0Xmn8f1Xz7mP67nL+jLMW/qn6Tfx/n2SGGybcPmXxr3mdqPIcbdwY7ac1ERUW+cSdThCjI1s+KFu1Etn9t0nino5DIqozmi0Y7sWBFPyM9W4eynXd6GXmSg530aJWubh0L1JOk0pwaDgT6kiLy8nNy9P1JOm2QKPXJWrM5uqTSVb3qjq8K1iULzbThsqwKrngVYSQ/NkSGnzBkeOSfyI/ttcxGU2c2N5EV+k8xeUv8J5W9ZXn5uXJ8Rcifpc9RPUVfAntrfHhnFxzn3b5+Cax+eX+/+gbwS4V5GlfjmECKnF2tN4xS6nw6tk339xmlL8pkk/4ALNehgKMrSuTfcq0ijlPAwZbsoVPxXGfddYWaE66jKy1TsSsnDR1bkEWS88w6GCpZBM5/PWfMJfcBFRf5JuaXe5XF9vrvbXGlHXO99eTOtKs7F/oe59zBSZwnlHW9oOtaEZirmDQ2I8hdafHBGDdprIyrREfHy7T0zNTUNA7UkKpsgUxLSxg0JCMhnVR5Jk/HX0gflJnCjgeS/O+Hy7TBQ9K5JGxImk6L8KdlqHqHpGVQrUqPVu0PiRuo25kun1NiWDVMFZ3gkVM0j7wkdVjWaDLlJcEJfp4wEiQPVL03TwZXgmu7NdRzZOA5TD1fKJz9QbXVczfRXu/9eKXqOmn/TH3BuvpFYyHXuR0unsARRy9bJsZ79UdP1Juh86hL6nc5xtWBNg39zpjqs8thDXlos9z80RWl/vfFfvqgZP414z3rD/ZB8ssWvSabq/YfzXb2H2WkeuNiUlJiY+IGwj1Dk9PYJTD0wqiogMqQFuOCCmM=
*/