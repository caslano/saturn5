//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_TYPE_TRAITS_HPP
#define BOOST_BEAST_TYPE_TRAITS_HPP

#ifndef BOOST_BEAST_DOXYGEN

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/detail/is_invocable.hpp>
#include <boost/config/pragma_message.hpp>
#include <type_traits.hpp>

BOOST_PRAGMA_MESSAGE("<boost/beast/core/type_traits.hpp> is DEPRECATED and will be removed in a future release.")

namespace boost {
namespace beast {

/** Determine if `T` meets the requirements of <em>CompletionHandler</em>.

    This trait checks whether a type meets the requirements for a completion
    handler, and is also callable with the specified signature.
    Metafunctions are used to perform compile time checking of template
    types. This type will be `std::true_type` if `T` meets the requirements,
    else the type will be `std::false_type`. 

    @par Example
    Use with `static_assert`:
    @code
    struct handler
    {
        void operator()(error_code&);
    };
    static_assert(is_completion_handler<handler, void(error_code&)>::value,
        "Not a completion handler");
    @endcode
*/
template<class T, class Signature>
#if BOOST_BEAST_DOXYGEN
using is_completion_handler = __see_below__
#else
using is_completion_handler = std::integral_constant<bool,
    std::is_move_constructible<typename std::decay<T>::type>::value &&
    detail::is_invocable<T, Signature>::value>;
#endif

} // beast
} // boost

#endif

#endif

/* type_traits.hpp
HVH9YZsrLCv9pOb8geIcpgzrOP7Q9y09WwwuV5vom0YzXoICQ/f+k8ByP6VruMerfC5/Skj7aUuhcD94iL4EXGDpJAr4+oOkbsATIEo3kSfx0Z6VPOLeEhW6Kjq86nxAcesYaCA51yZ2KSAw07G4ip92m3A7Q6Hy+fnD85Dec5akSs8BuPm21b4Lttzd/pwsCHMLHMx4BggJEIY+AXjueGEbnkfZdmRv3OR/buBBIYsIwIPBrGkDCS5OLWhCqQ0ICrixR7u4F9r2Xdg80d98J958qM3X9n8jcOI9mICh/MTRsoWe+mA9VSExfxjZxVQRxnoHjG4rX6cr+BvzHldnvGcdtOMa/fkxo0sYw6ehDi3ycintgGp8I9Jer0AMFGLRJ7j+3z8yclOCRJd+nwqtxhhqgnf7ciaxFFRNnINqhNVrEGj+gfs3ZCOAGJoYg1h6fhtgFDOQ/xMfNuYXkg98q3AkUkdiX1y9qToBoz/Lk397pVJiSaIx7cAa9Qv0xv74SYliLcRB7iFr4EYB/hwW7KJAvPjakBO6gUMsK+EC1g7vk3otonYxZIz7HP1y/1SNnfntV43l4zdB35ojmRT6DimQGPdYyasSBD06xYRcUIDP3C29EJtMLsWr3bDrx0fXcYXPL1uOJhLcvdOq9jylhOqIul/95wZpjFUFrTHdiPPCHMsdvhY9D4Wq34dg+C5FEKoHuJ+qd6TxBlOk
*/