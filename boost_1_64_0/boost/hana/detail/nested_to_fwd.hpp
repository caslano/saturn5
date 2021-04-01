/*!
@file
Forward declares `boost::hana::detail::nested_to`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_NESTED_TO_FWD_HPP
#define BOOST_HANA_DETAIL_NESTED_TO_FWD_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <typename Algorithm>
    struct nested_to_t {
        template <typename X>
        constexpr decltype(auto) operator()(X&& x) const;
    };

    //! @ingroup group-details
    //! Provides a `.to` static constexpr function object.
    //!
    //! When creating a binary function object of type `Algo` whose signature
    //! is `Object x Object -> Return`, `nested_to<Algo>` can be used as a base
    //! class of `Algo`. Doing so will provide a static constexpr member called
    //! `to`, which has the following signature:
    //! @code
    //!     Object -> Object -> Return
    //! @endcode
    //!
    //! Note that the function object `Algo` must be default-constructible,
    //! since the algorithm will be called as `Algo{}(arguments...)`.
    //!
    //! @note
    //! This function object is especially useful because it takes care of
    //! avoiding ODR violations caused by the nested static constexpr member.
    template <typename Algorithm>
    struct nested_to { static constexpr nested_to_t<Algorithm> to{}; };

    template <typename Algorithm>
    constexpr nested_to_t<Algorithm> nested_to<Algorithm>::to;
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_NESTED_TO_FWD_HPP

/* nested_to_fwd.hpp
egahWMFoNv9vWQUNBNQ7MaZFqe+4AJnd+w1D22BncxFte/mxMURbCBvrSMtFw9mMfdy3AQnpML6UK8vUnNbV32ODyCpszTo2fBg50z6R8+kLaD51+ujB/TXacXfgjn0MdMHl/mHxCBN29P70KzeLSZxypUEvMCChRK3sKthKoAQ4yIibv2ArHLBdHf4RXvppjdHX5tvMomhZr9FEg5CbSq0tGnG1YUWrEmTuEZkGgyALhAiTI4IvDJLpebsPFmjLVUapTJmywrooU8tVo5rOlXn7SXGdrW0/F4Zx1tBzrKdS7vX2DQyG3zQXYPXCva2XwYOungnUryJov2QiGkoPt56PEfy1+YCqbqPc3e74kQ3ps5n6guXRNY0NLUItUfh6PYPKla0JdLxuUDxLmPWL6phERI6PkqKN0o6T8HnRVKhxnWTOpqq1VHAT8L+ftC4rxQ5LFOUxRp5jV6WJLV55sHnEuLlleAjvrO5TsWyNtSZuiIQDopOeWoAJ4ycLX3BZxbMgYu5T32ojkUy+hlke4rfOszucN5IykhtcjwQ1TLE8U3tnI7eljO0f0Q==
*/