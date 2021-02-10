//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WEBSOCKET_IMPL_ERROR_HPP
#define BOOST_BEAST_WEBSOCKET_IMPL_ERROR_HPP

namespace boost {
namespace system {
template<>
struct is_error_code_enum<::boost::beast::websocket::error>
{
    static bool const value = true;
};
template<>
struct is_error_condition_enum<::boost::beast::websocket::condition>
{
    static bool const value = true;
};
} // system
} // boost

namespace boost {
namespace beast {
namespace websocket {

BOOST_BEAST_DECL
error_code
make_error_code(error e);

BOOST_BEAST_DECL
error_condition
make_error_condition(condition c);

} // websocket
} // beast
} // boost

#endif

/* error.hpp
0PofJKp8SUWzJ4a7aPMr7umyRAeCbu2Q+CQtO5IW5D9RXPDg0ZQNt7K4NRnczaJ1rz2UPyF8mczJJlov7lfTPzbTaI2CnYptf9uH4UuRS64zpZsDJEFP8CyhGHF0p+VpQnBmq5qKZq3PQJOcJ39ihHF/a60wxW05poIQvjnnyGtnlFUao5gNcFthCUr8nMODDJPP0zfwndnKvt950VlytsBqR0tc3gtV4+LATgaSgjNZV59b177oJgPwkUoxM3h4wgDleQh43fvY+wdQSwMECgAAAAgALWdKUmbxfa/ZBwAAExMAACYACQBjdXJsLW1hc3Rlci9kb2NzL2V4YW1wbGVzL2ltYXAtbXVsdGkuY1VUBQABtkgkYK1Xa2/bRhb9rl9x66KJ6EqUlALtNn5gFdtJhdqSIdnwZhGAGJEja1qSo+UMJRtJ/vueO0PqZafeBao8KA3v89zndA7/vk+DDunFT+T+Rfjg6TiuC/2HjO3z1FH0hfwfcH3C8yUlHdqwfIkCepnlCzUdS1RpOebvUfSSok9sG//XYc5PEX/FCdiY80wvHgt1P7fUPAuo9+uv/6A2vem+6bboXORKpjSxMp/K4r5Fx4k7+edcPDyERp62SFoSaViJupkrQ0bP7EoUkvA9VbHMjUxIGEqk
*/