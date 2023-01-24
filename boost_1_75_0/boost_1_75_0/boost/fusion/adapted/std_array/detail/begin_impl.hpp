/*=============================================================================
    Copyright (c) 2013 Mateusz Loskot
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_STD_ARRAY_BEGIN_OF_IMPL_01062013_1700)
#define BOOST_FUSION_STD_ARRAY_BEGIN_OF_IMPL_01062013_1700

#include <boost/fusion/adapted/std_array/std_array_iterator.hpp>

namespace boost { namespace fusion {

    struct std_array_tag;

    namespace extension
    {
        template<typename T>
        struct begin_impl;

        template <>
        struct begin_impl<std_array_tag>
        {
            template <typename Sequence>
            struct apply 
            {
                typedef std_array_iterator<Sequence, 0> type;
           
                static type
                call(Sequence& v)
                {
                    return type(v);
                }
            };
        };
    }
}}

#endif

/* begin_impl.hpp
8gqIAO+YGORj9KIEtvU45obOAylTPA+Rx9GCeDeZ2O/A7dV4Nvmduo+2bcUzmrtiGtyYgeI0yuRWJtJoW4YytnIkyaVCaNZiWpivjYLbzINPxFnoVyP8gv2E+vUTpFdCj9onuN7j5GummG/ySPnuNpgyo4r/hJb7TPaW4rWYVLEvS2lxeZ0FLjSJdynvwPYWbV6SmSDFDWXJXNTd1dEIspNR0/xxwy+us5hlSDoL2cWabfZcNDQ5SsbHsBcARkSF9P5j3EexHem42hTqywlbDK6QRi6cIy+XfZFOvGzxyZKcXntvN3ktuAtk/0myZ1+LrFSrP4CW5LB9sq8IN1tFI8oG+CJ7yLpDFTx2BKaBVTmog/uujmDz6T1WC9ytavI5p2TFXQAaDm62CzrBhtqXwBytx5jUYOPkAni56y98YVINxmzfdT/SwdzL9/WzqL2P87gXcXk2uRik6MSTGuotPgVhNc5CqMPaWOQmZ2Gm78a/8HrsmmISxKzZRQPmsBe2VsnO0WwXsNhyxQfabHCazKa3HJeyOQtcCDLe5QpsV0HsjAKWbQ4ruwBZKZI1e6Z3FgQW64GHWW6iENYwTpkVkqrZau9lhVTGIr9D+IwC2bsgQ7I6U6WhTuvvkjVb/l1KyGabUttXT/WAfrWovV6KY92qSCx/q6wwqVLn0B4phBUh259liwE9huUMFn20zMnOZeuTe0G0O9kb8dP5
*/