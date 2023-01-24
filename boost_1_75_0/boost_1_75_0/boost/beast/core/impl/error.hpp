//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_IMPL_ERROR_HPP
#define BOOST_BEAST_IMPL_ERROR_HPP

#include <type_traits>

namespace boost {
namespace system {
template<>
struct is_error_code_enum<::boost::beast::error>
{
    static bool const value = true;
};
template<>
struct is_error_condition_enum<::boost::beast::condition>
{
    static bool const value = true;
};
} // system
} // boost

namespace boost {
namespace beast {

BOOST_BEAST_DECL
error_code
make_error_code(error e);

BOOST_BEAST_DECL
error_condition
make_error_condition(condition c);

} // beast
} // boost

#endif

/* error.hpp
BWmC/SwZFbazZOo8I9H9S7Zoi7zEad7Shsd7AiToIfZvewAHe2wZbMj8xNz6B/CoXWkZTgG6WABxSt+8nM/DewbNb6+YKALmsOEsFLsCM8oov0u6t5yOa2xgBy7Nq3FLBqTux7z1YSAQt82r/4iOeRjBS7FMDRJy+0odQVsc4OPa5zg+mtYiPnrHaph6ixO/wNjlwJcdHLUzgiPPlfpXZFxudtSK8W0IRi4/DXAIKeWnhKm4U8EAFYf6QNUhXEPeQlxDhwM4W40kwFGNVB6PLLpd0m4eNYWirJDoWu1dJPr3ANHbCX3KFn2tMG63wKsVSTXgxGkYcH+b4u1nW13r7W3bYqA1EupF/ZkXoI6aVz8K7YSep0/2B37BWlOodF/IYFuteC92qWh5P0xIqG84h7LGJNQBp4FCw7ZS1KVY/srPoDIkO7aGsIppeYHCJikppNDdQFwh9zKbpnGX/ZwagmXBq/wXoyCE9zl1i7MD6mjEdzW0gJvoGABPDvDWkIQT4Y7QU5DMoMfH4m4aPpZxXERPoBLcF+E5G+PuuYJjGhXLs34TzE5FAOnzHpj6fy01k24nX66OI4X8MtRIkImjOGzieIJQNBk4I0yiM7BBOgMLMyjPT4CC28pMSCwTCRfTxQqMJmTqbtaOr5fSkULoXvpl9K3Wz+eM0TGYgu1+pHBNlDjcwHhtj8oL5bGyLUuw7J8hp3QA9wxPEeAS
*/