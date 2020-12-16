
#ifndef BOOST_CONTRACT_FUNCTION_HPP_
#define BOOST_CONTRACT_FUNCTION_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Program contracts for (non-public) functions.
*/

#include <boost/contract/core/config.hpp>
#include <boost/contract/core/specify.hpp>
#if     !defined(BOOST_CONTRACT_NO_FUNCTIONS) || \
        !defined(BOOST_CONTRACT_NO_INVARIANTS) || \
         defined(BOOST_CONTRACT_STATIC_LINK)
    #include <boost/contract/detail/operation/function.hpp>
#endif

namespace boost { namespace contract {

/**
Program contracts for non-member, private and protected functions.

This is used to specify preconditions, postconditions, exception guarantees, and
old value copies at body for non-member, private and protected functions (these
functions never check class invariants, see
@RefSect{contract_programming_overview.function_calls, Function Calls}):

@code
void f(...) {
    boost::contract::old_ptr<old_type> old_var;
    boost::contract::check c = boost::contract::function()
        .precondition([&] { // Optional.
            BOOST_CONTRACT_ASSERT(...);
            ...
        })
        .old([&] { // Optional.
            old_var = BOOST_CONTRACT_OLDOF(old_expr);  
            ...
        })
        .postcondition([&] { // Optional.
            BOOST_CONTRACT_ASSERT(...);
            ...
        })
        .except([&] { // Optional.
            BOOST_CONTRACT_ASSERT(...);
            ...
        })
    ;

    ... // Function body.
}
@endcode

This can be used also to program contracts in implementation code for lambda
functions, loops, and arbitrary blocks of code.
For optimization, this can be omitted for code that does not have preconditions,
postconditions, and exception guarantees.

@see    @RefSect{tutorial.non_member_functions, Non-Member Functions},
        @RefSect{advanced.private_and_protected_functions,
        Private and Protected Functions},
        @RefSect{advanced.lambdas__loops__code_blocks__and__constexpr__,
        Lambdas\, Loops\, Code Blocks}

@return The result of this function must be assigned to a variable of type
        @RefClass{boost::contract::check} declared explicitly (i.e., without
        using C++11 @c auto declarations) and locally just before the code of
        the function body (otherwise this library will generate a run-time
        error, see @RefMacro{BOOST_CONTRACT_ON_MISSING_CHECK_DECL}).
*/
inline specify_precondition_old_postcondition_except<> function() {
    // Must #if also on ..._INVARIANTS here because specify_... is generic.
    #if     !defined(BOOST_CONTRACT_NO_FUNCTIONS) || \
            !defined(BOOST_CONTRACT_NO_INVARIANTS) || \
             defined(BOOST_CONTRACT_STATIC_LINK)
        return specify_precondition_old_postcondition_except<>(
                new boost::contract::detail::function());
    #else
        return specify_precondition_old_postcondition_except<>();
    #endif
}

} } // namespace

#endif // #include guard


/* function.hpp
pJ/x63SAgHHzJgf+8SNJp/TQVvMni91N9u1uJ0n/X9auBD7Oqoh/adPQymGatpKWtqQtljRN02RDKyBijqa0JW1D0tIWgWWTbJvQXM1ueiAiIggocoiAchYULIdY5RAPEFQU5BTkEkREERRRKoogl/Pmm9nv/02+3W7B/rq/fG9m3rx58+bNu98rqgifw+C5BNm/q2Vo37hQn1cMe15H8n6b3k7cx/rCOD6P4TacuDDP55fTHDmRJPEcxugKOIfBeiM+HeDPAIJ3EIysMPOZkqfdJU+he/iKvR0/lTzOMHVDYaO1bgCsWOniKXqXysvAS5VW4bqvyNSl/UxduoB1wOcO4bwmH/jsH4J4B7g3crv7/buLKT8HSn2pEn+3F+jMG9u/Hs2ZQ2LNVZG2mYVe39WvGN5+puUv2n4J0U2X/eg8Z4U+wdqNbRMGtwykPWgTTHlcy3dX9HdvhHC5R0Hh85WpohPgsVrW1dUe6c2bgQGZh1GaLrf+LemoHfcYOx6QfHBU4L/ZlSVdgT2USobK70S//Oj5s9R6lO9kn97Td4vHQ5ltZTuXdMDWEar2rmuj3OeV838TxofD+5hwiQmXmvCHIYxroRPMWujkijB+H4OfavClBl8mdfLJcYF/e0S+NR7VCfY7GG8/qdvkQ1jOP4+TvpqJ+3TEWxvlFHcJ7k91ZV7jwboThWN+eAzPG3P58R4QhZX6sJiD6fxxRQXOH29Op2piB8ZddU9u9gsvBArfk9/J5+qH/Lu5/P2NXrAno8MLaNKZe+MrKb3infYh6a6a6PNdJApL5T4y94hVVWT2CHMb5MLaBlVXYLvj389RQzDsB8ekPGsrYC0caPWsK65VzpM48yXOI6KTOazPNd2sdw7z3TmHd3tBuIzC1RCuljl9Ddd5q0PxW7xFrMu5Fa7+L+KlNsUf4GAF6/hBQRf+GIW7Cta56eXMfqOBgt5BfpdRwumCBIfVLjYXsF1kfMXJ7t09WWPYkxR0INjIGQXrOnqtjYRAQX8jMRnOpMGeghlwZ4oLH1xh9xqM9j4u+j1E9DspZHOJkJ3NlPHJoazr5Y0N8Ybm5Y2Hs11lQnDXU73HPHrowXbm8yHHR/YMVQmvOuL1Rh52Gj1/kp+OpM9n9GL3VIzyGkUXC0QXP9R8VKjc6redzLxJKont0NvUxjBI6BpcPFeOQuPSPmNE90bkcy6FnVVq+KsjKMMEQJqvEU18XRh26Yh0Dz3MmeiE9qiJ0ts6ooPXsQ6Wtn4h2NS2EU1HtsTrm9rihzUuzdwRYGBZdd3f0W51LSDU9etGZ9Raexp+g8L0TmYmr68WDNfhvwrCOlzk4hVQQqDD20SHapt3Op1BW//wCF4rcQ18BvbcCKcrafM1/QwdKzGQgWkVDGVuyuptKCutw4uxbzVSdUu1A/WNMPbBcAYoe71i2zxcbPMo6jupX/GwT8Qw3u+YVJj6m2Jns0SK+yhKHYxIFfYJ9pupNI26esP3hPTEu2kedHPofovexOZ4GE7yubtCeCDH8QW2iGCd/T09BGVYM8FWU+9JeR0n95nEuxLc4VV4l8LpDd4OfgPXy/Ac8KTcJXyyR31qsh1XLTDtc73UUC/QbRU6pNnu8X5+R8hlOda96wFleWee9j/d2D+OZd+QPqje+7YcbaVA7WJVa31LYCwGCOc+rD/jb7ZLPNNyhPi0VrGb6aFxTFc3ljGdEet34Zki3wqQr9j0CTCvbUzX0d4BfojC7IfUzx9Zkd/7K/ON/qBfRfoL2s9V7FsDO9V9vatB5tGq08wWVAhn83N59s2iymCPYv4xDMvgU1IGR0sZLDR5rCF+6CNjEj6qwvlISlzCx7h2d4TkGfqWx0I=
*/