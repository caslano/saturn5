// Boost.Function library

//  Copyright Douglas Gregor 2002-2003. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org

#ifndef BOOST_FUNCTION_PROLOGUE_HPP
#define BOOST_FUNCTION_PROLOGUE_HPP
#  include <cassert>
#  include <algorithm>
#  include <boost/config/no_tr1/functional.hpp> // unary_function, binary_function
#  include <boost/throw_exception.hpp>
#  include <boost/config.hpp>
#  include <boost/function/function_base.hpp>
#  include <boost/mem_fn.hpp>
#  include <boost/type_traits/is_integral.hpp>
#  include <boost/preprocessor/enum.hpp>
#  include <boost/preprocessor/enum_params.hpp>
#  include <boost/preprocessor/cat.hpp>
#  include <boost/preprocessor/repeat.hpp>
#  include <boost/preprocessor/inc.hpp>
#  include <boost/type_traits/is_void.hpp>
#endif // BOOST_FUNCTION_PROLOGUE_HPP

/* prologue.hpp
aXZpc+lyeezS7/LcZcxF01XHleVq5Grh6uLq7urpGuQa4hrhGu260TXHtcj1qOtJ1wrXatdO127Xftdh1xFXPJ/IV+RT+Tp8K74Nn8t34QfwBfxIfjJ/NX8Xv4Rfwa/m1/Cb+A/5g/yX/BE+2g3rpu5Gd2O6cdzM3Nzd/Nz83QLdQtxEbqluGW6Zbpvdctxy3Qrcyt3q3Zrc2ty63Hrdnrth3cnudHeWO9vdyt3O3cHdx32hu9B9q3uW+y73Q+5H3Y+7l7tXuze4t7j3uD9073cfcH/uPuKO9yB6qHowPTgeXA8XD08Pbw9fDz+PAA+BR6xHhke2R6HHIY8Sj1KPao8aj0aPDo9OjxGPUQ+0p6InxdPI08KT7znL08/T3zPEM9kz1TPNM9uzyLPU87hnlWeDJwn6nZYCoApAA6ADsAA4AEYAZgA2AFwAHoA7gBfALAAfAD+AAIAQAAFABEAkQDRAPEAaQAbAZoCtALsBcgEKAIoAigGOApQClAGUA9QA1ALUAzQAtAF0AXQD9AI8AHgMMAjwHGAYYBQADge/7wCQAMgAVAB1AE0AHQAWgBGAFYAdgAMAD8AdwBvAFyAQIAggBCACQAgQC5AEkAKwGiANIBNgI0AWQA7ALoA8gCKAQwDHAU4ClANUAFQB1AI0AjQDtAC0AXQD9AA8BOgHGAB4CTAMMAaXPJOWCEAGUASgAtAAmABsABMAMwArAAcALgAfwBtgDoAvwEKAAIBggDAAAYAQIBIgCSAZIP0v7J15NNZ7Hse/dkqpZMu+k1wkIZV9q2xZyx7Zl7JmyS57QqLIVvZcZItsMUSILBFlyb6TLeszn/nNnDkzc2bOLP/MmeU553Xuvc+53SPP5/16v0/3ARAIhABRQBwQDyQB6UAmkA8UAyVAJVAD1AFNQCvQCfQDQ8A3YByYBpaBDWAbwAF4BAgRAYcBSoAOYASYAV6ADxACRABRQAK4BCgCyoAmoA3cAPQBY8ASsAfuAs6AO3AfCASCgQggGkgAkoB0IBcoAAqBEqAMqATeAe+BNuAT0A98A0aASWAeWAZWgQ1gF9gHCAjh/gAy4AhAAdAB9AAnwA3wA0KAKCAOSAKygDygDKgB2oAhYAqYAdaAM+AF+AL+QDAQAkQAccBz4AWQCeQCxUAFUAO8AxqB90AH0An0AV+AEWAMmAcWgS1gG9gHcAABEfx+gMPAcYAKoAHoAVaAG+AFBAARQAKQBOQBFUAD0AR0gRuAIXAbsAUcAXfAC/AHAoEwIBqIA+KBp0AqkA3kAwVAMVAC1AB1QCvQBnQCn4A+YAj4BkwDs8AisAbsAnjEcH8ACXAEOA7QAMwAO8AL8AECgChwCZAGFAFlQAXQBLQBfcAUuA3YAncBZ8AD8AUCgWAgGogBkoDnQDrwAsgGCoBCoAyoBN4CTUAb0AH0AP3AF2AEGAdmgVVgA9gCdoF9gIwE7g6gBOgAeoAZ4AS4AWFAFBAHLgHywFVADdAAtAFdwBQwA+wBZ8AV8AB8AX8gBIgAooAYIAF4DqQCmUAukA+UAW+BRqAV6AA6gR5gCBgDJoF5YBFYBbaAbQAHEJHC7QEUABVAAzACrAA7wA3wAsKAJCANyAOKgAagCdwADAFjwAywBhyBu4AXcB8IBEKAeOApkASkAulAJlAAlAAVQA1QBzQCrUAb8AnoB4aAb8AYMA3MAsvAGrABbANEZHB7wCj4nRj+ehjBc+j/j/8//v/4/+M/7/H33weDvSHwH/j5GNg7MC///v2Dv3sLr4v1HTvr207Gv3v+j7/sT34+h7SMrJy8wj/1cfzFG3l+93Pm//j3gkLif/KP8H5T7Jvim/P+w//937199V95n9A=
*/