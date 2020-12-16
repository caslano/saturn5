//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_RANDOM_MERSENNE_TWISTER_ENGINE_HPP
#define BOOST_COMPUTE_RANDOM_MERSENNE_TWISTER_ENGINE_HPP

#include <algorithm>

#include <boost/compute/types.hpp>
#include <boost/compute/buffer.hpp>
#include <boost/compute/kernel.hpp>
#include <boost/compute/context.hpp>
#include <boost/compute/program.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/transform.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/iterator/discard_iterator.hpp>
#include <boost/compute/utility/program_cache.hpp>

namespace boost {
namespace compute {

/// \class mersenne_twister_engine
/// \brief Mersenne twister pseudorandom number generator.
template<class T>
class mersenne_twister_engine
{
public:
    typedef T result_type;
    static const T default_seed = 5489U;
    static const T n = 624;
    static const T m = 397;

    /// Creates a new mersenne_twister_engine and seeds it with \p value.
    explicit mersenne_twister_engine(command_queue &queue,
                                     result_type value = default_seed)
        : m_context(queue.get_context()),
          m_state_buffer(m_context, n * sizeof(result_type))
    {
        // setup program
        load_program();

        // seed state
        seed(value, queue);
    }

    /// Creates a new mersenne_twister_engine object as a copy of \p other.
    mersenne_twister_engine(const mersenne_twister_engine<T> &other)
        : m_context(other.m_context),
          m_state_index(other.m_state_index),
          m_program(other.m_program),
          m_state_buffer(other.m_state_buffer)
    {
    }

    /// Copies \p other to \c *this.
    mersenne_twister_engine<T>& operator=(const mersenne_twister_engine<T> &other)
    {
        if(this != &other){
            m_context = other.m_context;
            m_state_index = other.m_state_index;
            m_program = other.m_program;
            m_state_buffer = other.m_state_buffer;
        }

        return *this;
    }

    /// Destroys the mersenne_twister_engine object.
    ~mersenne_twister_engine()
    {
    }

    /// Seeds the random number generator with \p value.
    ///
    /// \param value seed value for the random-number generator
    /// \param queue command queue to perform the operation
    ///
    /// If no seed value is provided, \c default_seed is used.
    void seed(result_type value, command_queue &queue)
    {
        kernel seed_kernel = m_program.create_kernel("seed");
        seed_kernel.set_arg(0, value);
        seed_kernel.set_arg(1, m_state_buffer);

        queue.enqueue_task(seed_kernel);

        m_state_index = 0;
    }

    /// \overload
    void seed(command_queue &queue)
    {
        seed(default_seed, queue);
    }

    /// Generates random numbers and stores them to the range [\p first, \p last).
    template<class OutputIterator>
    void generate(OutputIterator first, OutputIterator last, command_queue &queue)
    {
        const size_t size = detail::iterator_range_size(first, last);

        kernel fill_kernel(m_program, "fill");
        fill_kernel.set_arg(0, m_state_buffer);
        fill_kernel.set_arg(2, first.get_buffer());

        size_t offset = 0;
        size_t &p = m_state_index;

        for(;;){
            size_t count = 0;
            if(size > n){
                count = (std::min)(static_cast<size_t>(n), size - offset);
            }
            else {
                count = size;
            }
            fill_kernel.set_arg(1, static_cast<const uint_>(p));
            fill_kernel.set_arg(3, static_cast<const uint_>(offset));
            queue.enqueue_1d_range_kernel(fill_kernel, 0, count, 0);

            p += count;
            offset += count;

            if(offset >= size){
                break;
            }

            generate_state(queue);
            p = 0;
        }
    }

    /// \internal_
    void generate(discard_iterator first, discard_iterator last, command_queue &queue)
    {
        (void) queue;

        m_state_index += std::distance(first, last);
    }

    /// Generates random numbers, transforms them with \p op, and then stores
    /// them to the range [\p first, \p last).
    template<class OutputIterator, class Function>
    void generate(OutputIterator first, OutputIterator last, Function op, command_queue &queue)
    {
        vector<T> tmp(std::distance(first, last), queue.get_context());
        generate(tmp.begin(), tmp.end(), queue);
        transform(tmp.begin(), tmp.end(), first, op, queue);
    }

    /// Generates \p z random numbers and discards them.
    void discard(size_t z, command_queue &queue)
    {
        generate(discard_iterator(0), discard_iterator(z), queue);
    }

    /// \internal_ (deprecated)
    template<class OutputIterator>
    void fill(OutputIterator first, OutputIterator last, command_queue &queue)
    {
        generate(first, last, queue);
    }

private:
    /// \internal_
    void generate_state(command_queue &queue)
    {
        kernel generate_state_kernel =
            m_program.create_kernel("generate_state");
        generate_state_kernel.set_arg(0, m_state_buffer);
        queue.enqueue_task(generate_state_kernel);
    }

    /// \internal_
    void load_program()
    {
        boost::shared_ptr<program_cache> cache =
            program_cache::get_global_cache(m_context);

        std::string cache_key =
            std::string("__boost_mersenne_twister_engine_") + type_name<T>();

        const char source[] =
            "static uint twiddle(uint u, uint v)\n"
            "{\n"
            "    return (((u & 0x80000000U) | (v & 0x7FFFFFFFU)) >> 1) ^\n"
            "           ((v & 1U) ? 0x9908B0DFU : 0x0U);\n"
            "}\n"

            "__kernel void generate_state(__global uint *state)\n"
            "{\n"
            "    const uint n = 624;\n"
            "    const uint m = 397;\n"
            "    for(uint i = 0; i < (n - m); i++)\n"
            "        state[i] = state[i+m] ^ twiddle(state[i], state[i+1]);\n"
            "    for(uint i = n - m; i < (n - 1); i++)\n"
            "        state[i] = state[i+m-n] ^ twiddle(state[i], state[i+1]);\n"
            "    state[n-1] = state[m-1] ^ twiddle(state[n-1], state[0]);\n"
            "}\n"

            "__kernel void seed(const uint s, __global uint *state)\n"
            "{\n"
            "    const uint n = 624;\n"
            "    state[0] = s & 0xFFFFFFFFU;\n"
            "    for(uint i = 1; i < n; i++){\n"
            "        state[i] = 1812433253U * (state[i-1] ^ (state[i-1] >> 30)) + i;\n"
            "        state[i] &= 0xFFFFFFFFU;\n"
            "    }\n"
            "    generate_state(state);\n"
            "}\n"

            "static uint random_number(__global uint *state, const uint p)\n"
            "{\n"
            "    uint x = state[p];\n"
            "    x ^= (x >> 11);\n"
            "    x ^= (x << 7) & 0x9D2C5680U;\n"
            "    x ^= (x << 15) & 0xEFC60000U;\n"
            "    return x ^ (x >> 18);\n"
            "}\n"

            "__kernel void fill(__global uint *state,\n"
            "                   const uint state_index,\n"
            "                   __global uint *vector,\n"
            "                   const uint offset)\n"
            "{\n"
            "    const uint i = get_global_id(0);\n"
            "    vector[offset+i] = random_number(state, state_index + i);\n"
            "}\n";

        m_program = cache->get_or_build(cache_key, std::string(), source, m_context);
    }

private:
    context m_context;
    size_t m_state_index;
    program m_program;
    buffer m_state_buffer;
};

typedef mersenne_twister_engine<uint_> mt19937;

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_RANDOM_MERSENNE_TWISTER_ENGINE_HPP

/* mersenne_twister_engine.hpp
2Q57OGBFSLxExkD2tdca8MIdEWFbQLggbIry2rWLX/8T2N8Gfm6d59zrDbmv1k9yF+y3EZaSmFhMkeJ1PPvqjdhfISwnlvucQ5Gj3J0DOlvk/hvCBsJ98jbmtLmeR7HXct/v3ZhfchE982aUu3NK549c9q8e+3imdMqW2vbeiu3Ol4vHwhscxMNIFKx4E9D4Dn7IHOJIIKwkMjhvaVJThMVbO4cXZ3dNCmGg7bDPHngTVcY4isYVeSd38t3dY5+gRIjcrlLGbcr3poFHRpMEzRrLB2sX8XwM9aOjitkYprxemzxfGnhUESpnxbA8aH1yuI/22G3Rjv7FSnJ5UINmr0Vax6360cDlrMw22IRlQmuSwx747tFG4oNnjJPL3ece8FWgxss1JwH/uPeM332qlRIey4fWIYdvcI9NhGkVS+CxxtM4qqr64/7cdBu+wYiPExOC9DZHLCNaf9CfpMcGwng0pdBMjucYJctBCPbHgSsErjMPBcuG1xq80UZYSmRs7ylcIHfXc3R3nxn1fK8a+pMxz6wVtJNv9AcHzg8NnEzRzIQ35HL/8mjk7HPZD5w8N6NSt6Vg53CwOXz3PciuSLN0XPmVhBfHQ0yTgcPltqNog+W6fr39tcduyRKpYEy13Xrnxlz4BnyTx/mYbIgsUSwMXm9gQ3lvv66FdLGo5CtPnUuz0Q54HjyXhf3DF+oljVgevNZA/9tjUzNHZmrLFJNn9NWBeU8GPuWCNT4ELBdeZ3A/7rHb0dZu93oV6e2FVxVyPvi8HiIuTqajsTIKy4bXGMSyQ1hFTPHW+2LJEg7hSVWNuXLw3eJlZ8N/+VMDN2cy5MI1lhPWHJrH33wvvte72mZqJAh6V82zX+OCACf4L6D+sYFFTqWaYJeTpmb2N4RYdqiNdQBLZF7K60R86mX7MyFeAnHC3tevH+YtVcGwifdq78bjN87z3x7eFRTDrFKBzDGZ+vPCUyEf8/vw2VbLHItWU3y4Kbbf6VU7MWz4rD70fdi2F2SIktNq/J64eocLAvN6xoCPk5JKqTxxNSvFHjCtMQTzBM6cbo4+O9FGWSWiZfPcXWYM3G197QhqyrrntneHB5xXMLcRVhIuparDbcnO7cdOlFt893z3OUdVBQNvDW8sc7vHJmIiz7QY1dFegpYY4gD1mEKycTK6oFZHzShuQEStwX/0S5gr2pSzl2qO6/fYG89a668pvMVEsimishd1ica1v+ONjXBakFNkxoIt1FFjPVebeRAa+xIBrjVi6zlHVYnQjPEQP+P9SGYrivLSxEXmrUHmLZhzPS419VgMhcu1zNUEN8r8mBkDcUW8CNx5gX08r5e5vB/LrAzPznL7n2VujQCZ13MDt13nYgvLor9SwBUS5gbuJ+91qK3X3Xza7+NTb0GcnhkHfq3BMOnCeGGufNj/CvSC78f7JLNe69D89Z/VurqfXNvgK95jbhnOHc3FNeX53Vc12TrsqW45T6K+lURp4UzSYYwneKf5dNjZpx/8AXxfjNLRSGVGOnWIl7uFcr/DPvMBJHMqwgqRIsjcTa6z5TxQeszjKymnUShy0En8WIifOJcFPw7rlBAx31lemEsgL9xNkLyc6GCkr11ONoUEP8NlbnwKYQ0RWobikx02qUbfT67HLjJ/q8ffjDJSV0eOwGOm3nflu3NZiMkvqdfF+jtzbbe+XgVVhHVff30QfTdESkHa5o5yCl/ShXvfLd+1HiMEsbYOD6f/Ze12/1hrg3Hu69piQhnFGJ+kWGLH3QQflg9imY0PVvgc/keZHwc5pzGn8dY7JqdalueEl2451w+yulikVvz/khXO4R8c3lEFrrlNcf0GvgW1oHt7EKNo7cM=
*/