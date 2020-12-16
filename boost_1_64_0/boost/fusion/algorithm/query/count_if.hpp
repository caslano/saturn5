/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2007 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_COUNT_IF_09162005_0137)
#define BOOST_FUSION_COUNT_IF_09162005_0137

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/query/detail/count_if.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename F>
        struct count_if
        {
            typedef int type;
        };
    }

    template <typename Sequence, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        enable_if<
            traits::is_sequence<Sequence>
          , int
        >::type
    count_if(Sequence const& seq, F f)
    {
        return detail::count_if(
            seq, f, typename traits::category_of<Sequence>::type());
    }
}}

#endif


/* count_if.hpp
dZc1vTxvNqFu1L5jsZ/Bs7Hos0c3Z0kK5Hsc8uRf04T5SmoMI1m/v0n8thuR5zhf1I88c4aa1p/pk3br9kVPc9uIlvHO6j5lRHuznkPpY/Wqnk3rp++2kJ7qHEbRM1/0zEaW8j/Ve1U9RUnf93OeuBU19nErpM3p9JG2qutnOltWdjDb8mfUefSPPTo2rV+92UK2FD25kTHPZ3sBPRtUPZvWX7BL4zFIZD5Yl4784dgm8xs2y1y2qkdd+ctVldlsftTl2ZjPFuEI6RSKjY4hPZWxRNELRujq362mxO1QfxNG2SYq67Q1v4my/o1uD46jYpNxci8YA19U2k6NNx6FGCY7Z15Rdo4f7Ue5H5zzE/39YLju2uN0ckKxQWPPFkoy9z3hl259HLWxzYtJkeyaM3fs1uw7H+/25dOfdJ374aHVL176vz8nL8yV73vJDyR88kTBiKrBdW/87buN/YNz9f7Tc/VmXax8PyAqp/Xpg68c6vKbLhEP3/XA4mbM1dthH/MhVhPzoUrSjbOI+bBbYi08AfvAJ+FAuAcOhz+CMXCvnK8cqZfzbZHzdYAFcr6Ncr47YU9YBYfCu+V898DxcDO8Gj4IZ8NqmAUfhmvgI/Au+Bi8Gz4u+ec55N0BrJD828E5kn9OK/aKgLmwF5wPh8I8OBrmwyS4AN4IC2AuXASXwEK4AhZBdS7h4/YxJ0Zr5xJKut6N1Ec9Uinpxsva+u7K2CvpxkpMgHEwCo6HA2Cc2PEqGA8nwEkwAabASXAunAwrYCKshlfDx2AS3AmnwcNwOvyVYe+JL2EK/ArOhK3RbxY8H14LL4DpsD+cDS+Dc2AMvAGOgTeqe8LIszisQ6oNe8KkYd8+cCaMh7NgIrwWJsN0WARnw5vhdbAKzoFPwhvgqzADHoaZUPa4kGdkqQfDHhfFpDsHlsDzYCnsBMvghXAJ9Owtkyzn2Y1UG/aWCZX21RYOhOfC8bAdnAzbw6mwA7wOngezYUdYAM+HLhvBlbATXAPD4SbYGT4Eu8IdMMKrF8+v9noNFr2iRa9hotflotdw0WuE6DVS9Boleo0WvWJEr1jRa4zodYXoNU70utKrF8+h9no9I7FOnocD4c/geHgAToYvwKnw5/A6+CLMhrWwAL4EnfBluBL+Aq6BB+Em+Ap8CP4S7oCHoEevhkb0OiZ61YteH4peH4leH4teJ0SvP4hefxS9/iR6fSJ6/Vn0+ovo9VfR61PR62/aucJ77GOsxKrjrTyvwU0W42137N8N9oK94QWwL7wQDoG94UgYBWfDPvAG2BcWwH5wFbwYroeXwI2wP/T043o1f3M/jpf8J0r+CZL/JMl3suSbKPleLflOlXyTJN9pku906B7n5bkK5luM84dlnDwCo+AbcAB8Ew6GdVKPb8EJ8G04C74DM+FRmA3f9dqZZyR7O38u+Z2CveFXsC/8Gg6B38CR8DScDf8Ob4D/gAXwDFwFv4Pr4T/hRvgvbcwiyX+4bXvgj0OeUeA2Safdk6i32CMK9od94Ah4EZwI+8Kp8GKYDi+BuXAwXAiHwLXwMng7HArvgsPgZni56LEfia6R9ivXMUXXPYa9t/JhH7gQDoQFcBpcBK+FTrgULob3w2JYDctgDVwBX4cV8G9wJWyAqzz24L8I8r8ZRsLV8GK4Bg6G6+AouB7GwNsVhvqeq76Vm8T9CHPWtXPUm7XvzuDj//k56scoUwNiN1c9/XjLzFdffdw8Z73LqhDTvPUBq0LO6tz1muPu+etJ5NPYHPZs/t0zj33dqpCzMpf94HH9fPb64/o57dtXhZzVee2O+v/c3PZ9q0K+9317jpDnSaRDZYhjMJKGlCKbkX3IMST05hA=
*/