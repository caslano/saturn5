/*!
@file
Defines `boost::hana::is_a` and `boost::hana::is_an`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CORE_IS_A_HPP
#define BOOST_HANA_CORE_IS_A_HPP

#include <boost/hana/fwd/core/is_a.hpp>

#include <boost/hana/bool.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/tag_of.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    //////////////////////////////////////////////////////////////////////////
    // is_a
    //////////////////////////////////////////////////////////////////////////
    template <typename DataType, typename T>
    struct is_a_t<DataType, T>
        : integral_constant<bool,
            std::is_same<DataType, typename hana::tag_of<T>::type>::value
        >
    { };

    template <typename DataType>
    struct is_a_t<DataType> {
        template <typename T>
        constexpr auto operator()(T const&) const
        { return hana::is_a<DataType, T>; }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CORE_IS_A_HPP

/* is_a.hpp
3VdY4MSoKUAvrUkuGTr1ZkQ2HWRuoQKW/AkfXo/OXzhx6MR4vFDTNscy6tXWEckSsoe61kbJeV+KgWSdYFSjDfY0Rfq6XPQ0RfSytEnhda3PZA9Ct6uyof5+8OeTUzog1QeXkOUsXHpBaSvAr1bj7Vwonoj2dPLJNTydw2MeYQYlHZ39SNxl5ZxtDJaiIrJ8F1ksAxvMubR8rwMfT8lmK89LpssoZ+WyCaV+1dTSmsQpcEa+lLLTw2cWFHZlguef2hMRC4VLhV5eNcBj//AIJLrcXUXTOTTEAtIWLg/pAgge+3MM+yBM0RZc5+KYGMuvbLsmPMdonNvs5SbIr4b64vP/LPYzyE/wA1vdgIK7oDF/D/CHtLS3nH0mgmqwuf+RgvAw77O7WPIoTuMwjkF0D2cmCqSPcxROfHe+t0BXZzMQyXm4Wi+ifWE8n3rRxzhc7mcQqX+8YPd6uH/s/TSe/Px8tjs+OnR3fxhPprvj6dFk96fZzz//+NPhi4nrPVfN7CQt8s2Odija7HAmEAMJKt8h599hy+gffZAs7sLVNHkn9prl3VQ4rB1onBHdCOKVc5d9pd+15vzrNrxDbJITDCesU0Et2tg3p5tNySahBJMVkRsqX0befG4ORmyrMCbQ4taesxLEArwx8ryP
*/