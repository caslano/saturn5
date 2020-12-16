//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_SERIAL_COUNT_IF_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_SERIAL_COUNT_IF_HPP

#include <iterator>

#include <boost/compute/container/detail/scalar.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>

namespace boost {
namespace compute {
namespace detail {

// counts values that match the predicate using a single thread
template<class InputIterator, class Predicate>
inline size_t serial_count_if(InputIterator first,
                              InputIterator last,
                              Predicate predicate,
                              command_queue &queue)
{
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    const context &context = queue.get_context();
    size_t size = iterator_range_size(first, last);

    meta_kernel k("serial_count_if");
    k.add_set_arg("size", static_cast<uint_>(size));
    size_t result_arg = k.add_arg<uint_ *>(memory_object::global_memory, "result");

    k <<
        "uint count = 0;\n" <<
        "for(uint i = 0; i < size; i++){\n" <<
            k.decl<const value_type>("value") << "="
                << first[k.var<uint_>("i")] << ";\n" <<
            "if(" << predicate(k.var<const value_type>("value")) << "){\n" <<
                "count++;\n" <<
            "}\n"
        "}\n"
        "*result = count;\n";

    kernel kernel = k.compile(context);

    // setup result buffer
    scalar<uint_> result(context);
    kernel.set_arg(result_arg, result.get_buffer());

    // run kernel
    queue.enqueue_task(kernel);

    // read index
    return result.read(queue);
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_SERIAL_COUNT_IF_HPP

/* serial_count_if.hpp
uSgvVKIBNtjRCTe6EEAMOeRRsY7jhVmoRwva4EUYUQxiGGMov4lzAFY40Y0e9CMJ03rSgAZ0wo0uxJBDhZvw0YEohpGCeQNhowoz0YhWOOFBN3oQRwJJZGC6mXJFM2yww40u+BHDENKwfIG8ogltcMGHEKJIYQxmD2lBFerQiFY40I0IkhiFaSP5RQ1s6EQXAhjACNKwfJG40YQOuOBFCFGkkMUYzJuIHzNhhQMe9CCICJIweYkbtbChE370IYY0LJspc9TDBR9CCGMYKYzB/CXyizo0woFuBBFBHBmMwvRl6hga0IxO+NGHGNLIo7qL+gQXQhhECmMov4X8oRFWOOBEBAmMwvQV8oZm2OFHDEPIw/JV4kAT2uCCFz6EEcUghpHCGKq6iRdWtCKIfkSQQAajMG0hj6hFMzrRhQBiSCOHPCq+xvmDFnjRixCiGMYYqm4lXljhhAfdiCCOzK3Gl4zK0AAb7AhgADGkYbmN+NACF3wII4phmL9O2aIRrXCiB/1IIINRlH2D/KEGtWhAF/wIoA8DGEEOeVT4KW/UowO9iGIM5bdTd9AIJzyIYBSV3yQe1KIZNrjhxwBisHyLMoQXIQxjDOU9hItGtMIBD4Iou4MwYYcbAxhBGtXfpl6gBW3oQC/CSCGLMZR/h2ODRrSiB/2IIANTL3HAhk74MYIcLHeSZjShDS6EEMUYyr9L2LCiFU540IMg+pFE2feIAza4EcAQRpBGDhUB4oEPIYQxiGGkUH4XcaERDjjhQT+SyKDy+8QDO/wYguVuygpN6IAXIYQRxSCyMAepv7DCiSD6EUfDPRxX2GCHH30YQBo5WH5APKhHE3qRQhZ1P6R84EA3+hFHAklkMIqyEOlHM2xw4/Wf139e/3n95/Wf139e/3n95/Wf139e/3n95/Wf/4+f80xvmjaZ3y3fmM6TTPMuvXT+4sVLm+YvvvTKBS22BZcvWnr9je3tbH+39sttOcV+K1zHwvKeKqxV7etNJ4RVXj6puN/8xUuvW7F0xQ3tS9tXLb9xQ/HbfKb179Q+PAenfZZft/z4Dq5SGLHj26+/7sIP1k8URvVLJ+5T2oNHMkrpPXF7MQRtP0vbU8e2O9oV+AZ9tvg8kLa1L7/uhPSVPlt7VJ89vs2pzxafp9E2Zf41eQueVdq++qS8lcL3H9/H6VqxetVavnVb+nx4Smnb2nZXKe1LP9++gc9rn+KzXCfsowi0j9JZfIZG+6xbtf7GZU5js6n9WB7fUdpe2losH+Wx/JW6sHiB4/Ibr1y26oZ2o0K1l7YnLK/ZXqxIpuJ2Hf/Xft6oRO3nldI2vbS9fZVrxfUr2m+8tGP1iuXFaFRvdYynTryfUW91DsyYeJ/X1lvvSfutVXTFMlO5Tj1pH6Iq5kvHZoIwitGcVSqX+ORXti+6cOm8Rde8UihLS/E7KW9t+/gC29LFtisXLLps6fKO9uWfJ42ql/r8q/ZRKo+V3YTh3EA9uK4Yn8LiZ9cEYRnHacX7Sul1TLTPqmUr25c6b1yxyvWq836i8IxCdpbSFmufcJ91K5cuW7v8hHOkpWqiPKxtJ8K1x47r9ZMn3kdhnVcq14nDUnkU41R9PyH9C1teVbQr3lmK87X7qMhKYdhP3q4iKIahenbCPpdfbp0/r9jKnnjuHt8+f9FVC+dfOc82v8lIyArtU3y+5eR9iseYeM4rtY8fOcU+SzlwF9eRZtXZieIz6sGqY+3xhPsUM1bcR23CRPEZx2zVsWMx8T4npck/4X6u1Us/vsh0rI0+nqZPnFCQq88rbX//sTAum7+IIKwLPjO/ybZg4fylyxyfK76+R/vNPtV+OvlMJ5xbivPkfY0DVNqv/Lc=
*/