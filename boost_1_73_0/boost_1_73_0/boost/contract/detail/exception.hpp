
#ifndef BOOST_CONTRACT_DETAIL_EXCEPTION_HPP_
#define BOOST_CONTRACT_DETAIL_EXCEPTION_HPP_

// Copyright (C) 2008-2019 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/config.hpp>
#include <exception>

namespace boost { namespace contract { namespace detail {

// Using this instead of std::uncaught_exception() because
// std::uncaught_exception will be removed in C++20.
inline bool uncaught_exception() BOOST_NOEXCEPT {
    // Alternatively, this could just return `boost::core::uncaught_exceptions()
    // > 0` but that emulates the exception count which is not needed by this
    // lib (the implementation below is simpler and could be faster).
    #ifdef __cpp_lib_uncaught_exceptions
        return std::uncaught_exceptions() > 0;
    #else
        return std::uncaught_exception();
    #endif
}

} } } // namespace

#endif // #include guard


/* exception.hpp
NgAJAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfQ09OTkVDVFRJTUVPVVQuM1VUBQABtkgkYK1VbU/jRhD+7l8xSr8AMg6Uk+j16KkmGHAvsaPYORopkrWx13h7a2/kXRPS0v/e2bUNhB6CD+coWXs8r888M3GWAzj4YZflaHfw5pWYb4IXnr3RtBZ/0VR93yBJHqD9oOESz3eEGsKT1UOyD++yeoA9Y5V0sc70fZK8I9xSJ6l/htp4mehblLSWnf1IrLc1uy0U7I324fjjx1/gEH4+Oj614YJUjHKIFK1WtL614Swzkt8Lcn/vSPrZBqqAcGfHYVwwCVLkakNqCnjPWUorSTMgEjIq05qt8IFVoAoKOeMURuF04QdXNmwKlhadn61oQBai4RkU5I5CTVPK7lo3a1IrEDl6QP8Zkwp9NoqJysHwFBStS9m50UkQLgWQO8I4WWE4oqBQai1/HQ7TpuZYyTATqRymPRROocoXVS0wm5JsQawVKAGNpDZofRtKkbFcnwgRCtfNijNZ2E9pYcAqG4oaJOW8c4emjMq2BApRh5atNWGN2TOlDykqqaNtClHuKCKsnaO8qSsMh7CgXiYQeBuaKqO10TdA9FE6lA3kb7TsKfcMRIVZwcCN
*/