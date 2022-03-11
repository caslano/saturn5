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