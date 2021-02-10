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
T0CW9yE94gqakeW5KtdaLDML7fMOHB4f/wb7cHRwdODDBSsElzC3vIi4XvpwkriVPzL2+Ngz/MwHboHJXuNqkQkDRqV2xTQHfJYi5oXhCTADCTexFhG+iAJsxiEVksP57OpuPL30YZWJOCMna1WByVQlE8jYAwfNYy4eah8l0xZUiuboPBHGosPKClX0EJuD5To35IPgmTQK2AMTkkUIxCxk1pbm9yCIKy2RfZCo2ATxJvxeZvNtJHdIImdrUKUFq6Ay3Ac66UOuEpHSHQXBxbKKpDCZv2ODUEUSKA2GS0m+0E5wU9PmMG/k8ekYlMhYWLoZVRiCWmUqf3UQdSQvaaULBEId8FCiUGYfqiLh2h12kW8gGk2dwP+Zmh3fBFSBZKA1mMN43oKIGWF8uB0v/pzdLOB2cH09mC7uYDaCwfSOnH0aTy8w9QLBNPDHUnOD4BpEXkrBkwbzx12B95MoYlklHE6MTYTqZWfeizVKaJ1VWg+6cHIxnJ+fEdVLKlAwoljKpuJSjQJjuKPFFaZIP3BNfOEk2NgEnofSVNjnI1uOyOQfDzCLhbEQZ0xDl/wULOd9XB+NJ0PoogFned977pMxsyJGzC88tJCvw3SlheXtByUS6EZVmnLtb7bptn0pcp5HPtQHa5cdj8Df
*/