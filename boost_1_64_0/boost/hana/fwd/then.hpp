/*!
@file
Forward declares `boost::hana::then`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_THEN_HPP
#define BOOST_HANA_FWD_THEN_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Sequentially compose two monadic actions, discarding any value
    //! produced by the first but not its effects.
    //! @ingroup group-Monad
    //!
    //!
    //! @param before
    //! The first `Monad` in the monadic composition chain. The result of
    //! this monad is ignored, but its effects are combined with that of the
    //! second monad.
    //!
    //! @param xs
    //! The second `Monad` in the monadic composition chain.
    //!
    //!
    //! Example
    //! -------
    //! @include example/then.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto then = [](auto&& before, auto&& xs) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct then_impl : then_impl<M, when<true>> { };

    struct then_t {
        template <typename Before, typename Xs>
        constexpr decltype(auto) operator()(Before&& before, Xs&& xs) const;
    };

    constexpr then_t then{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_THEN_HPP

/* then.hpp
E+tmPm+XUX1XqupbCi2/0LuJDcGZP1OsByIsWnZ7mqMBf5X4ew1/KeYP9TMlnKn4O0rgp/57fnRmo/7E1FLUlIcN1lorRjhEHW+zXWSQcu/mQw+4lSSnF/fcncyfuExsH8NrYjaFv3YH/q9wXGKf3WEftpCv63r7L7Ff+aLNPqzVS7LxNvlBiJ6YcHnPsxXBp496lkQE+PF8cWsBX/St1xZ7WwlpGeZ7FvC06GK2VAZvam4yasbYdMZOBzbFxNiFErs5CRsC1iKxixjL5ClsA7BWiV0ssduTsI3A2iT2Jol9LQkbAdYhsbdKrEjCzgLWKbG3Sezfk7DNwLokdonE7jawC/mSNQK4ZYClMsB7KgDc/TIAP7wvjbhJi8ViNMRz8vEJWRLov2bZOJAgKChu8bFZE9Lnw96ReCb7MuKZ3KZ/F890pF+1fYX+ALSDj3qx/xRUTdV0/6i9PCsg0iUUAISyoeRUjMNu9OwrIGCyr4AIKTdWEROnHEpf216HTptiH1aE/rsJdw+Ogu9OSTp3o+tnxLOBYjiGmslEapnFDOuoxRbc5zGXWKPFdKfcXEIHNlqZw1ziiBbTZSIzbrsVO3Gf0YybbsW42Og2l7ijxbiZ7jGXeEhdqcxrLvFGi71H2r/T2ZJ+RymVVubcoXu3nd49dqg20ZJbZTl93dgqizbRmltlJadVm2jLrbKR06ZNdORWOciJJ0qduVVOcjq1ia7cKhc5XdpEd26Vm5xuvGGaW+Uhp0eb6M2t8pLTe0xyhXCWmn3kg9zJylGq/rju9m5Be1MVavbc2OmrcnuidpTiAgtqU4cvsIwts2gXWFGtysc6Fhf2L7ChfpWPbSzu71/gQEUrH8fYMgcUe1Djysc5tsypXUBXSZWPa2wZlH9Q9W7l4x5b5tYu8KAxlI9nbJlHu8CLVlE+3rFlx1YJh/9h/8D2XyGSZklkfbDOvsI/9GatR3sHjiH2Jc9Yb47tsGa8k9ED2DIItgEeCniotp+tMpNfhn3JOhlmP4dJHwRnAjYDNmubAQ1HvBxtrX3JiwjzqjVjbQb5DhsEO5JhxPDCb2QURgtvhubnWgCu5ADkhhPeJ92csTlj7QL/KfAa4p0Te3WIfUXHzYiYz5l/Dkk5D8r85EGwGXAq4FTtTcScPK8TNWaCq5C1Tqe3PJtiX/IyjNxzlkWplOWbQITYN1P6mpRvA/myX4ryKrUv6xkZ2zdyEh7IhqzbzKkifQc2MFmZb+r5QQ8T6Rx3c8umFK0H2CIKpb1pX/K0FXULlPXmjB5Ob3rCL036ddqX7R4J3yGxAyNjO4aYe1Du7My3NFQ90nXPi1EOWgPK8kIKUKUotP1mbbe2BY4T7EveRdJbYq9bM3YDPl6HEdzLfloM8/dIpJUHTGosPjL2eqp5N5cBBiEyt8nUQbEHBJ3Y8nzKzVo/MqmkEMhhyfvW2BtE64ibM/qRLHwTfk72A5xGuYiRsTfSYv8cae4nkyyZL1NY5Jtv5OBFujUt2DqkIK6b+gbXh1HlRaOpzgf5jZJ+Nd5sLYbUnNQawFrQIrFXLWa+EJPZC4yD80mNop4Qsg/5uFLmrSIvNNQ0gO6UeV0EwulJmdetO70p89bozukpZ8D1wRjaveAvaqZTQvuy2KhY/yg4iwh7wNejrTJjMHHQ6PkWDW0FP0gm7MtWjYqeb4VHhYxQKiOs17rMNd4cjuDriVbbgPJEz3fYl3WNQuCADFwpA+/WujmgGSrFCHylEyivfVk3UnZR8WXgGhm4X1tjbvbmq5Svc3PVLVszaqoMls/Boud7fMLc4K2ZEp3hpc1T5cebk/6XfyuJFRPbIAQh1nWZfGugORgQE4Yzk9Sqc1I=
*/