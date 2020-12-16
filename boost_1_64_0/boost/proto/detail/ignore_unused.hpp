///////////////////////////////////////////////////////////////////////////////
/// \file ignore_unused.hpp
/// Definintion of ignore_unused, a dummy function for suppressing compiler
/// warnings
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_DETAIL_IGNORE_UNUSED_HPP_EAN_03_03_2008
#define BOOST_PROTO_DETAIL_IGNORE_UNUSED_HPP_EAN_03_03_2008

#include <boost/config.hpp>

#if defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable : 4714) // function 'xxx' marked as __forceinline not inlined
#endif

namespace boost { namespace proto
{
    namespace detail
    {
        template<typename T>
        BOOST_FORCEINLINE void ignore_unused(T const &)
        {}
    }
}}

#if defined(_MSC_VER)
# pragma warning(pop)
#endif

#endif

/* ignore_unused.hpp
79qvbo5i/PHOOtP4xXexYjjujTLaD28y5/VGfocvyTJZX61vPCmIakOuDGXodyifSspuD2XZnjXWFjPC1HItf785+hgK2W9UCI+x5dpqvd30vRhksM/GTXIB2pY4xTxO72kK/YDXHTyb2ZnOJHL+WzvRu2/ME36yKf2MG1eJSrS+9EUBCnC/IhHM7U5ie7eFb5Uwfacgl246G2Ptp2jjRmKalThW9dJb0yIObfGQC6ct1pwOpqpja7eeP81s6j6ugcttuQYcFxHaDLaJ3K7PYhyebdH7bjffMxT/ch2cruOIsrjgJsTFcuU07yEKb1kj6qbvQ5sQUtyOBZy9trSHFaLtatOxdGdskqecAefFJU7ddKIx3iMOqWm4M99U9EUaF7Rt6hwSC9tVIfx72pKXllXnxSw1Z4mC9/nH2lJPZDvl43A5zMCwsy1gFLaX5lgY4cognLJmhEpDcg9r/jvlWATpney4YCkAd1HdMfbtprqI3xbXRGOtZJPp1v5+3FW7GEcX19y2KeKdutZ67Tnohfe3EbZG3bYZxZmGcBBKt/NY5mfJ+yeJMfvbMaAwaO5OSr3UZwsanHXxVOW1mEXbm6luD8uFkWOaU7zAtBBKCd4D2uT09ITgkNypHcGRkKNF6LpuOVNph8/kwbS7QPDOPj7bKfwerJkhh0FXzqMPdei102y+k+OOfsEZrFAiYNTY9gK3Y9a4JnDdZnkBtupaogN/ACHMB4H1/7ygIZnoVWVjG8b1Q8R1zLWYc0CM2t57Cfl/qjFuSnNXnkk37YucUFbJRvSx11unw8sl1nPbftTGlkMwEoZdK6XmMk7mi/uxD6frVe81A6VV3CZj5n97PzY+mlPOp5zlObd0ziXTNngvqv8452naSvnqM5TWo0Rn60aLWcCneOQPjuvTi7jXKTyEDDUKQjUNCPuD3JvXNcXxrIEc5p227Dje35sYRnsUV/x7JY7icbAsBKzBDQSR80a5TF/lShvQrm88l5rD5Owf70esNMJkknKM4X0Si+qTlM5l21emdsIwQB1uKZKj/bNubPvediJIzfgwnWWQ7nL9PcfTO1H0wtetmMVXzu+5O3nuffmW1ylVq74SoIMoffFLa8JpetEt9vs7fXm/KmerqhNqcc+Ahja90yDupwtcwWTPe6urfgH39CjH8se5vfyk0hfEQICJVrDJzvTCxctPeNSLTtAhb9CBCIpTt8yI3jup+3QuV3I9YiJTGLFpzIXDf1F2nSGSPFV8zTnnfOase3u3F4zVFbq7OlS1u3tmHOd2527H/+7OujOrnpjAHFAxJ0RUREVEVFRUTIiICTOifhAR8YOIiB9ERK3XNa/6Vc+s4X/cf/f6/epVTq9eCPt7nG+d1LpssgrydU7JonyPgo5AP98mN6W2NuQLKf9Lvi+L803LMi1FIyBf55Rseb5v6OVrS1vL0sqQL6Q8Id8wji9Fc9smqVI8hSh7Z2imkxBXOsqzYGWaZWUtuc/zjFSbT7yopFqaLd79/uRjkyab5vTABzhEZfXOxvevCxh/XYVzFo3H8cbnhfd1V+bBaGd0ZgDZUrvjt3WYocO4UeAhSH9PTHe9FdM/ENNdq3o6luGbnp4pozaSqr3yohh/iJjvLGL8FkkwP1zEbMJ7AuXz82UYyIzU99ceM1wbR7hQ3t96uqg3B8KvlNqFPfJcsP3/0GHm29Z8P/Yw+TDsy6W8fNVcWFewtbgYYtMDNn6jgIThHeXvzwtvJcAPxCUDLPPK81GegjTnHNtx2Sf+TG/8/Ng2ATNAJJbjlh63Weta+ZJAKVY2kX57SvecALCJ5byrpwPnK3M9EIG6HPfuaHChCnk+gHwnV7UVTPewQPc=
*/