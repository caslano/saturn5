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
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
*/