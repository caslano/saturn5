//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_RANDOM_LINEAR_CONGRUENTIAL_ENGINE_HPP
#define BOOST_COMPUTE_RANDOM_LINEAR_CONGRUENTIAL_ENGINE_HPP

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

///
/// \class linear_congruential_engine
/// \brief 'Quick and Dirty' linear congruential engine
///
/// Quick and dirty linear congruential engine to generate low quality
/// random numbers very quickly. For uses in which good quality of random
/// numbers is required(Monte-Carlo Simulations), use other engines like
/// Mersenne Twister instead.
///
template<class T = uint_>
class linear_congruential_engine
{
public:
    typedef T result_type;
    static const T default_seed = 1;
    static const T a = 1099087573;
    static const size_t threads = 1024;

    /// Creates a new linear_congruential_engine and seeds it with \p value.
    explicit linear_congruential_engine(command_queue &queue,
                                        result_type value = default_seed)
        : m_context(queue.get_context()),
          m_multiplicands(m_context, threads * sizeof(result_type))
    {
        // setup program
        load_program();

        // seed state
        seed(value, queue);

        // generate multiplicands
        generate_multiplicands(queue);
    }

    /// Creates a new linear_congruential_engine object as a copy of \p other.
    linear_congruential_engine(const linear_congruential_engine<T> &other)
        : m_context(other.m_context),
          m_program(other.m_program),
          m_seed(other.m_seed),
          m_multiplicands(other.m_multiplicands)
    {
    }

    /// Copies \p other to \c *this.
    linear_congruential_engine<T>&
    operator=(const linear_congruential_engine<T> &other)
    {
        if(this != &other){
            m_context = other.m_context;
            m_program = other.m_program;
            m_seed = other.m_seed;
            m_multiplicands = other.m_multiplicands;
        }

        return *this;
    }

    /// Destroys the linear_congruential_engine object.
    ~linear_congruential_engine()
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
        (void) queue;

        m_seed = value;
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
        size_t size = detail::iterator_range_size(first, last);

        kernel fill_kernel(m_program, "fill");
        fill_kernel.set_arg(1, m_multiplicands);
        fill_kernel.set_arg(2, first.get_buffer());

        size_t offset = 0;

        for(;;){
            size_t count = 0;
            if(size > threads){
                count = (std::min)(static_cast<size_t>(threads), size - offset);
            }
            else {
                count = size;
            }
            fill_kernel.set_arg(0, static_cast<const uint_>(m_seed));
            fill_kernel.set_arg(3, static_cast<const uint_>(offset));
            queue.enqueue_1d_range_kernel(fill_kernel, 0, count, 0);

            offset += count;

            if(offset >= size){
                break;
            }

            update_seed(queue);
        }
    }

    /// \internal_
    void generate(discard_iterator first, discard_iterator last, command_queue &queue)
    {
        (void) queue;

        size_t size = detail::iterator_range_size(first, last);
        uint_ max_mult =
            detail::read_single_value<T>(m_multiplicands, threads-1, queue);
        while(size >= threads) {
            m_seed *= max_mult;
            size -= threads;
        }
        m_seed *=
            detail::read_single_value<T>(m_multiplicands, size-1, queue);
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

private:
    /// \internal_
    /// Generates the multiplicands for each thread
    void generate_multiplicands(command_queue &queue)
    {
        kernel multiplicand_kernel =
            m_program.create_kernel("multiplicand");
        multiplicand_kernel.set_arg(0, m_multiplicands);

        queue.enqueue_task(multiplicand_kernel);
    }

    /// \internal_
    void update_seed(command_queue &queue)
    {
        m_seed *=
            detail::read_single_value<T>(m_multiplicands, threads-1, queue);
    }

    /// \internal_
    void load_program()
    {
        boost::shared_ptr<program_cache> cache =
            program_cache::get_global_cache(m_context);

        std::string cache_key =
            std::string("__boost_linear_congruential_engine_") + type_name<T>();

        const char source[] =
            "__kernel void multiplicand(__global uint *multiplicands)\n"
            "{\n"
            "    uint a = 1099087573;\n"
            "    multiplicands[0] = a;\n"
            "    for(uint i = 1; i < 1024; i++){\n"
            "        multiplicands[i] = a * multiplicands[i-1];\n"
            "    }\n"
            "}\n"

            "__kernel void fill(const uint seed,\n"
            "                   __global uint *multiplicands,\n"
            "                   __global uint *result,"
            "                   const uint offset)\n"
            "{\n"
            "    const uint i = get_global_id(0);\n"
            "    result[offset+i] = seed * multiplicands[i];\n"
            "}\n";

        m_program = cache->get_or_build(cache_key, std::string(), source, m_context);
    }

private:
    context m_context;
    program m_program;
    T m_seed;
    buffer m_multiplicands;
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_RANDOM_LINEAR_CONGRUENTIAL_ENGINE_HPP

/* linear_congruential_engine.hpp
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
*/