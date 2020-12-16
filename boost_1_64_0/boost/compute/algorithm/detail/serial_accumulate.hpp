//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_SERIAL_ACCUMULATE_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_SERIAL_ACCUMULATE_HPP

#include <boost/compute/command_queue.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class InputIterator, class OutputIterator, class T, class BinaryFunction>
inline void serial_accumulate(InputIterator first,
                              InputIterator last,
                              OutputIterator result,
                              T init,
                              BinaryFunction function,
                              command_queue &queue)
{
    const context &context = queue.get_context();
    size_t count = detail::iterator_range_size(first, last);

    meta_kernel k("serial_accumulate");
    size_t init_arg = k.add_arg<T>("init");
    size_t count_arg = k.add_arg<cl_uint>("count");

    k <<
        k.decl<T>("result") << " = init;\n" <<
        "for(uint i = 0; i < count; i++)\n" <<
        "    result = " << function(k.var<T>("result"),
                                    first[k.var<cl_uint>("i")]) << ";\n" <<
        result[0] << " = result;\n";

    kernel kernel = k.compile(context);

    kernel.set_arg(init_arg, init);
    kernel.set_arg(count_arg, static_cast<cl_uint>(count));

    queue.enqueue_task(kernel);
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_SERIAL_ACCUMULATE_HPP

/* serial_accumulate.hpp
OtGFPgwgBksZxwDDyKL8TMJHKxxwogdB9COBDGreRPhohg2d8COAAYwgj1lv5njDCx96EUYUKYzBXE55oRFO9COJDEZRO418wA4/AhjAEEaQg+UtHB/Uowlt6IALvYhiGFmMwfxW8oo6tMKDHgQRRwJJjKKygvjRCTf8GMAQRpBGHpbppAFt8KEXIQxiGCmY38YxRCNaEUEcSZS9nXJFA5phRyf86EMMI8ihupK8ogVt8CKEKLIYQ9UM8odGWNEKB5zwoAf9iCOBUZjOorxhQxcGEEMaOdS/g/jgghc+hBBGFIPIwlxF/KiDFU50I4h+xJHAKCrPJt9ogA2dCCCGEaRR/U7iRgtc6EUYKWRR/i7iQiNa4YATQcSRRE01caATbvjRhyGMII08LOdMMlVgFlrQBh9CCGMQKdS9mzjgQQ/6EUcCle8hLtjQCTdiyKGihrygCW3wohdRpGA+l/MBjWiFB90IIoIEMhhF2XnEhWbY4UYX/BhADpb3Un5oQhs64EIvUjDPJD40ogcRZGA6n/BRAzv8GEEes95HHuBCL4aRhfn9HHc0wgoHPOhBAhnUzCK9sKMLfgxgCCPIwTKbckIT2uDDMLIYg/kDpBl1aIUTHnQjiAgSyKDyAuo0bHDDjwAGMII0cshjVi35QhO86MUgzBdSx+BBN/qRgemDhA0b7OhCAH0YQQ55tH2IsoIPvQhhGOY6ygt1aIUH3ehBHAlkYLqIfKAGDWhGFwIYQBo5zLqYOosOuOBDFINIYQyNH+a4oBv9iCODsnrCRy2aYYMdnQigDzGkUTGHckIT2tABL3oRxTBSKP8I+UMjPAiiHxmUXUJ8sMGOTrgRwADSqGggHrSgDWFEMYjyudQBNMIKB5wIIo4kMjB9lLjQgGbYYEcn3PCjDwOIYQh5WD7GeYN6NKENLvjQi2GYG0kHrHAiiASSyKBsHuWJBjTDhi74MYAhjCANy8fJL9rggg+9CCGMLMZgvpQ4MRON8CCICOJIIIlR1DQRP2zoRABDsMwnb2iBC174EEUKY6j6BHUSHvQgiDjKLiNcNMMGNwIYwgjSyCGP6mbKDm1wwYsQBpFCFuYFxIWZsKIb/YgggQzKPkn9RwNscMOPGIaQg+VTlB/a4EUYWZitlBcaYUUrPOhHBAmMwrSQeNAMO7oQQB9iGEEOeVQvol6gCR1wwYswohhEClmYLyd/sKIbcSQvNx7IrYUNdrjhRx8GMIQ8Zl1BPGhBB7yIYgzmK8kb6tAKBzzoQT/iSCCDUZgWU46ohR2dcMOPAAaQQx4VNuJGC1zwohdhRJGF+SqOG6xohQdBJDGKmk9TnrCjE13wow8xjCCPWVeTR7TBhV5EMYgUzK3kE3VohRMedCOCOJLIYBSV15BHNMONLvRhADnkYfkMxxFN6EAIUQwjhSzKP8uxQyNa4YAHQSQwirI28olaNKAZNrjhRwB9iCEHyxLKFtWYhXpUXUscaIUTESQwisqlhI0GNMMGN7rQhxhGkIbFTrioRwdc8KIXw0jBvIx8oQp1sKIVTvQggiQyqLmOeNEMO/oQQw4Vy0k/6tGCNvgQQhSDSMHsID7MhBVOeBBEHEmMoqadfKIBdnShDwMYgeV64kQ16tEBL0KIYhApZFF+A+UJBzwIIoEkMjB1cNzQDBs64ccAYkjDsoK4UI82uOCFDyGEEUUKWZg/R7yYCSc86EESGZR9nmOJGjTDDT/6EMMQ0sjD0km8aEIbOtCLMKIYhHkl8aEOrXDCgyAiSCCDUVSuolxhhx8xpJFHxWrigAte+BBFCjOdhI0eBJHAKGrWcKxghxtd8KMPI7DcSNrhRRjDSGEM5Ws5NrCiFd0IIoIkMjA=
*/