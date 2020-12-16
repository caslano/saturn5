#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/transform/detail/preprocessed/construct_funop.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/construct_funop.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file construct_funop.hpp
    /// Overloads of construct_\<\>::operator().
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                         \
        (3, (1, BOOST_PROTO_MAX_ARITY, <boost/proto/transform/detail/construct_funop.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

#else

    #define N BOOST_PP_ITERATION()

    template<BOOST_PP_ENUM_PARAMS(N, typename A)>
    BOOST_FORCEINLINE
    Type operator ()(BOOST_PP_ENUM_BINARY_PARAMS(N, A, &a)) const
    {
        return Type(BOOST_PP_ENUM_PARAMS(N, a));
    }

    #undef N

#endif

/* construct_funop.hpp
J7of3xASZdVN92MbCoxim9Z9WUUjPIsJMLk3NUYiItoQialxE2lGoex1x1JaRJUtNibA5Eq3qzJo+KXWwf6xacc6CBruECiw0O8QZLU+Wc6kNrFfaVZ2d5cxZ9CuBJmdwPBfXm2PwlaFtwU4vGyuUMjtagfVasnPlazKiFVz26Nvrm/lrV0tt2QNuSU32CNVjBI4uweOV7FKeNiPxu4aw3Z+YecwcXirEsg8PVJwU0UuNxjtw7lXr4SfxW086A4svWRu93LZrQSeW0lM39m1EmDQcdfuCeoVd9h1CuAWPtz6UG3S3EhnBu+0WCV3JHkC5Nx2fD8oeo5V8PGUTDHyu4EfxJukOJUmtXxzjDQZl2CPmpPoyWY2Ej3aynrZKdu1PfJ+okRlq1Sq2omFiltDGACWeR7vI1W9f5Ej3knzgnot53vIietHumHX6vmCG77unpBLmKXAj94Aanx8hjVpWHFk1kNdbHzpho0rJ+S+c22WFLP2/78gPvp1s57K7wU2KqVH7TYmF3Jl/PN3BZLfGZXplAayuRrsxRmGihT67UUW6bcCKPtQPQhnN+xquYZ5Dq+/ZV4LJdQF3Kr7jpdYQ0fqbgGZSGQsflAouUMJdBliQQLMyTg2Vq7WagloM9Zb9fZI4HfaV/mKs1uCPDnFpnX5ThGusTQymLL8cs9URadUc7xmyuGgWhoIU/XMW/h4fCuFW5TffOP8aqusv/6qq6y2Xn6NDbdcZ9ONNsxvOdAzA61s20W03FCIwRHMqyVOhQqwizsnSBB7n4ZDtDJLJhJPnAxs/GDnRIlGfPzLe06t6gWJfRzaS9yFpiao6iYDv15rctBxGlHkY8L/9P4KxnASadtFx97ZHh5JWqkjdcsrxMJIYIplKygmkHI9aAR3ucIelXxQ8vOFoOolyBSfLPQTEsnCzKFJzRecAM7FrVYk0tYBSSWEuln1UgCoioANzqlacEJ/1tMB7Gohqd9DiHgwvsq3HH0iT8yEaQW3mqCyWiVpneRh5IjZGsnz1VooDz+hp26kkcplkwuWDgy7I3J5rVS9MrKJpAF8dpjB5Kmdyq6NCpNLFa4uUEjmVnZFeF7IN97qcCCSfOSv5cg0tVsyEdo/hRw3OwZNPUio1O0WNwzf3cpw1VDgA3LdYx6JLDm7205DjRMoGFrHAF1Vx6rUawmVvqXKEZkETKJzUHXyoftAztxKqWeJnCSul6VdttxKoxBs07R5ttkA4ZT9WuVmYTruc5TtZov7MmWSBilyrK3fMBv6LaSJtrbnJ/yZ7xQaYBeNxYwBKWb6PWmUwLZ20Nf6UOTYRUM2ULuCFVgJVI+rcjSn/s5BtaZb9a2vHXE1hluZbNKCj2rjarBZ14dPaORuwfGo49j2Rup6XHQl0fczEu13MtFz6xLtvgbRdYcQjXcb0bOTEM0xQPTe9kSZW4isyYimnZxoofGJFnCItsfvOcNEd1hEs65KlNuByJueaN2Vib5aAMQPJZpmIqK1b4r5ZTYimmUrotkXIlo+1z1Pdw4SLVzpvLdkH9GTB3beG1qFyD4LJ8C2mxp5vQunyDN/HHQ30c9rEr0Z5WPOfbpxjbAViJ6ftHk+zgbN32luJjqtQLThxER3L935fLDzaBoLrEa0zLVEH09LtM8I0SngndmdaFzI+tEiyr8l8r4F0YmQ38YXQ14zEL2KPNVPQXn2IHrhKMjxdsj0eojwDqIP7iS6Bn/hsfsURL8g3W4posNXJNr1AqILIKt3liV6u4rn5ycqLQ/+RxLNtBjRxNcQPXxvnLencH890GWPqVEPi21DtO+CSLM/0RLLEKWgDy9u3fncdzPxJQWvhcELedpp46jsFxHdhfMlNyM=
*/