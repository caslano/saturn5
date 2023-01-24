/*=============================================================================
    Copyright (c) 2013 Mateusz Loskot
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_STD_ARRAY_IS_SEQUENCE_IMPL_01062013_1700)
#define BOOST_FUSION_STD_ARRAY_IS_SEQUENCE_IMPL_01062013_1700

#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion {

    struct std_array_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_sequence_impl;

        template<>
        struct is_sequence_impl<std_array_tag>
        {
            template<typename Sequence>
            struct apply : mpl::true_ {};
        };
    }
}}

#endif

/* is_sequence_impl.hpp
LM5arQ0axgvyZZhsB1F6g9BtYwbQgj9e9dJAOJmvV02xMGrNPXA4GnX+Zk64cyTgcrXbN6AaumzEI4SblG3BVWXrseGrnzgf3dOTxGzCXiV+oBeKaHjHkMmtOBPLitftgFsRA4ZMLCfEtGKTMqew/DSPPIyTirKONki4+BsmmgN/MFHNMLWae9Vqxk+V1dzVxGpeoGpKIRRLkA5VSTdTSW8tl6T905pGujuTfp9Iz31cIf3R4wrpHWbjzG4i6e8eAtKewbUh3n9hMMiGTln7UMA5QHadcwA8JXX3sE5JLZ9AIRnjy4TobTYK6PJwGciFmgfJZVzVA1Yqt2ZTgF3R8GzpkOO7tZ2a1mj6aCWtkYrLBcuRmkPWhkjm8FMEzVX36Cvkobp4dGIQ+0DjI+gPee4kkayzFW1zlT2R7faeqID1tvvEIU4jJZNHpV4vvqLsZpewr0+3h+Dom1199NiwK4/pz4QJw+qOxe0zI63smSzzgG3MmKYcsP15JWITpQZCaSWUSu/U9qUWJvhTf7X/v2KdyXkrLZCn/Gq2a2qm92SG96cMbw3BzJF/PnzHx6PVlEmJ3n8zSw4SUAqu72CLyJ1yt4v+SvMe8x5L71mQpfsgIhn8wd/l0TQZ4ASG73Ct+CnMHTrQhYBoMKTGeo+VVKbqr68R4/AduCZzUyYlMWt0RPzVCuOP0Z0bxxdsSq8tE1w1B2YzLrte+oH5
*/