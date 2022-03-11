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