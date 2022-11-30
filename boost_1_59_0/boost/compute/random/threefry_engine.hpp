//---------------------------------------------------------------------------//
// Copyright (c) 2015 Muhammad Junaid Muzammil <mjunaidmuzammil@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_RANDOM_THREEFRY_HPP
#define BOOST_COMPUTE_RANDOM_THREEFRY_HPP

#include <algorithm>

#include <boost/compute/types.hpp>
#include <boost/compute/buffer.hpp>
#include <boost/compute/kernel.hpp>
#include <boost/compute/context.hpp>
#include <boost/compute/program.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/transform.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/utility/program_cache.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/iterator/discard_iterator.hpp>

namespace boost {
namespace compute {

/// \class threefry_engine
/// \brief Threefry pseudorandom number generator.
template<class T = uint_>
class threefry_engine
{
public:
    typedef T result_type;
    static const ulong_ default_seed = 0UL;

    /// Creates a new threefry_engine and seeds it with \p value.
    explicit threefry_engine(command_queue &queue,
                             ulong_ value = default_seed)
        : m_key(value),
          m_counter(0),
          m_context(queue.get_context())
    {
        // Load program
        load_program();
    }

    /// Creates a new threefry_engine object as a copy of \p other.
    threefry_engine(const threefry_engine<T> &other)
        : m_key(other.m_key),
          m_counter(other.m_counter),
          m_context(other.m_context),
          m_program(other.m_program)
    {
    }

    /// Copies \p other to \c *this.
    threefry_engine<T>& operator=(const threefry_engine<T> &other)
    {
        if(this != &other){
            m_key = other.m_key;
            m_counter = other.m_counter;
            m_context = other.m_context;
            m_program = other.m_program;
        }

        return *this;
    }

    /// Destroys the threefry_engine object.
    ~threefry_engine()
    {
    }

    /// Seeds the random number generator with \p value.
    ///
    /// \param value seed value for the random-number generator
    /// \param queue command queue to perform the operation
    ///
    /// If no seed value is provided, \c default_seed is used.
    void seed(ulong_ value, command_queue &queue)
    {
        (void) queue;
        m_key = value;
        // Reset counter
        m_counter = 0;
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
        fill_kernel.set_arg(0, first.get_buffer());
        fill_kernel.set_arg(1, static_cast<const uint_>(size));
        fill_kernel.set_arg(2, m_key);
        fill_kernel.set_arg(3, m_counter);

        queue.enqueue_1d_range_kernel(fill_kernel, 0, (size + 1)/2, 0);

        discard(size, queue);
    }

    /// \internal_
    void generate(discard_iterator first, discard_iterator last, command_queue &queue)
    {
        (void) queue;
        ulong_ offset = std::distance(first, last);
        m_counter += offset;
    }

    /// Generates random numbers, transforms them with \p op, and then stores
    /// them to the range [\p first, \p last).
    template<class OutputIterator, class Function>
    void generate(OutputIterator first, OutputIterator last, Function op, command_queue &queue)
    {
        vector<T> tmp(std::distance(first, last), queue.get_context());
        generate(tmp.begin(), tmp.end(), queue);
        ::boost::compute::transform(tmp.begin(), tmp.end(), first, op, queue);
    }

    /// Generates \p z random numbers and discards them.
    void discard(size_t z, command_queue &queue)
    {
        generate(discard_iterator(0), discard_iterator(z), queue);
    }

private:
    void load_program()
    {
        boost::shared_ptr<program_cache> cache =
            program_cache::get_global_cache(m_context);
        std::string cache_key =
            std::string("__boost_threefry_engine_32x2");

        // Copyright 2010-2012, D. E. Shaw Research.
        // All rights reserved.

        // Redistribution and use in source and binary forms, with or without
        // modification, are permitted provided that the following conditions are
        // met:

        // * Redistributions of source code must retain the above copyright
        //   notice, this list of conditions, and the following disclaimer.

        // * Redistributions in binary form must reproduce the above copyright
        //   notice, this list of conditions, and the following disclaimer in the
        //   documentation and/or other materials provided with the distribution.

        // * Neither the name of D. E. Shaw Research nor the names of its
        //   contributors may be used to endorse or promote products derived from
        //   this software without specific prior written permission.

        // THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
        // "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
        // LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
        // A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
        // OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
        // SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
        // LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
        // DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
        // THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
        // (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
        // OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
        const char source[] =
            "#define THREEFRY2x32_DEFAULT_ROUNDS 20\n"
            "#define SKEIN_KS_PARITY_32 0x1BD11BDA\n"

            "enum r123_enum_threefry32x2 {\n"
            "    R_32x2_0_0=13,\n"
            "    R_32x2_1_0=15,\n"
            "    R_32x2_2_0=26,\n"
            "    R_32x2_3_0= 6,\n"
            "    R_32x2_4_0=17,\n"
            "    R_32x2_5_0=29,\n"
            "    R_32x2_6_0=16,\n"
            "    R_32x2_7_0=24\n"
            "};\n"

            "static uint RotL_32(uint x, uint N)\n"
            "{\n"
            "    return (x << (N & 31)) | (x >> ((32-N) & 31));\n"
            "}\n"

            "struct r123array2x32 {\n"
            "    uint v[2];\n"
            "};\n"
            "typedef struct r123array2x32 threefry2x32_ctr_t;\n"
            "typedef struct r123array2x32 threefry2x32_key_t;\n"

            "threefry2x32_ctr_t threefry2x32_R(unsigned int Nrounds, threefry2x32_ctr_t in, threefry2x32_key_t k)\n"
            "{\n"
            "    threefry2x32_ctr_t X;\n"
            "    uint ks[3];\n"
            "    uint  i; \n"
            "    ks[2] =  SKEIN_KS_PARITY_32;\n"
            "    for (i=0;i < 2; i++) {\n"
            "        ks[i] = k.v[i];\n"
            "        X.v[i]  = in.v[i];\n"
            "        ks[2] ^= k.v[i];\n"
            "    }\n"
            "    X.v[0] += ks[0]; X.v[1] += ks[1];\n"
            "    if(Nrounds>0){  X.v[0] += X.v[1]; X.v[1] = RotL_32(X.v[1],R_32x2_0_0); X.v[1] ^= X.v[0]; }\n"
            "    if(Nrounds>1){  X.v[0] += X.v[1]; X.v[1] = RotL_32(X.v[1],R_32x2_1_0); X.v[1] ^= X.v[0]; }\n"
            "    if(Nrounds>2){  X.v[0] += X.v[1]; X.v[1] = RotL_32(X.v[1],R_32x2_2_0); X.v[1] ^= X.v[0]; }\n"
            "    if(Nrounds>3){  X.v[0] += X.v[1]; X.v[1] = RotL_32(X.v[1],R_32x2_3_0); X.v[1] ^= X.v[0]; }\n"
            "    if(Nrounds>3){\n"
            "        X.v[0] += ks[1]; X.v[1] += ks[2];\n"
            "        X.v[1] += 1;\n"
            "    }\n"
            "    if(Nrounds>4){  X.v[0] += X.v[1]; X.v[1] = RotL_32(X.v[1],R_32x2_4_0); X.v[1] ^= X.v[0]; }\n"
            "    if(Nrounds>5){  X.v[0] += X.v[1]; X.v[1] = RotL_32(X.v[1],R_32x2_5_0); X.v[1] ^= X.v[0]; }\n"
            "    if(Nrounds>6){  X.v[0] += X.v[1]; X.v[1] = RotL_32(X.v[1],R_32x2_6_0); X.v[1] ^= X.v[0]; }\n"
            "    if(Nrounds>7){  X.v[0] += X.v[1]; X.v[1] = RotL_32(X.v[1],R_32x2_7_0); X.v[1] ^= X.v[0]; }\n"
            "    if(Nrounds>7){\n"
            "        X.v[0] += ks[2]; X.v[1] += ks[0];\n"
            "        X.v[1] += 2;\n"
            "    }\n"
            "    if(Nrounds>8){  X.v[0] += X.v[1]; X.v[1] = RotL_32(X.v[1],R_32x2_0_0); X.v[1] ^= X.v[0]; }\n"
            "    if(Nrounds>9){  X.v[0] += X.v[1]; X.v[1] = RotL_32(X.v[1],R_32x2_1_0); X.v[1] ^= X.v[0]; }\n"
            "    if(Nrounds>10){  X.v[0] += X.v[1]; X.v[1] = RotL_32(X.v[1],R_32x2_2_0); X.v[1] ^= X.v[0]; }\n"
            "    if(Nrounds>11){  X.v[0] += X.v[1]; X.v[1] = RotL_32(X.v[1],R_32x2_3_0); X.v[1] ^= X.v[0]; }\n"
            "    if(Nrounds>11){\n"
            "        X.v[0] += ks[0]; X.v[1] += ks[1];\n"
            "        X.v[1] += 3;\n"
            "    }\n"
            "    if(Nrounds>12){  X.v[0] += X.v[1]; X.v[1] = RotL_32(X.v[1],R_32x2_4_0); X.v[1] ^= X.v[0]; }\n"
            "    if(Nrounds>13){  X.v[0] += X.v[1]; X.v[1] = RotL_32(X.v[1],R_32x2_5_0); X.v[1] ^= X.v[0]; }\n"
            "    if(Nrounds>14){  X.v[0] += X.v[1]; X.v[1] = RotL_32(X.v[1],R_32x2_6_0); X.v[1] ^= X.v[0]; }\n"
            "    if(Nrounds>15){  X.v[0] += X.v[1]; X.v[1] = RotL_32(X.v[1],R_32x2_7_0); X.v[1] ^= X.v[0]; }\n"
            "    if(Nrounds>15){\n"
            "        X.v[0] += ks[1]; X.v[1] += ks[2];\n"
            "        X.v[1] += 4;\n"
            "    }\n"
            "    if(Nrounds>16){  X.v[0] += X.v[1]; X.v[1] = RotL_32(X.v[1],R_32x2_0_0); X.v[1] ^= X.v[0]; }\n"
            "    if(Nrounds>17){  X.v[0] += X.v[1]; X.v[1] = RotL_32(X.v[1],R_32x2_1_0); X.v[1] ^= X.v[0]; }\n"
            "    if(Nrounds>18){  X.v[0] += X.v[1]; X.v[1] = RotL_32(X.v[1],R_32x2_2_0); X.v[1] ^= X.v[0]; }\n"
            "    if(Nrounds>19){  X.v[0] += X.v[1]; X.v[1] = RotL_32(X.v[1],R_32x2_3_0); X.v[1] ^= X.v[0]; }\n"
            "    if(Nrounds>19){\n"
            "        X.v[0] += ks[2]; X.v[1] += ks[0];\n"
            "        X.v[1] += 5;\n"
            "    }\n"
            "    if(Nrounds>20){  X.v[0] += X.v[1]; X.v[1] = RotL_32(X.v[1],R_32x2_4_0); X.v[1] ^= X.v[0]; }\n"
            "    if(Nrounds>21){  X.v[0] += X.v[1]; X.v[1] = RotL_32(X.v[1],R_32x2_5_0); X.v[1] ^= X.v[0]; }\n"
            "    if(Nrounds>22){  X.v[0] += X.v[1]; X.v[1] = RotL_32(X.v[1],R_32x2_6_0); X.v[1] ^= X.v[0]; }\n"
            "    if(Nrounds>23){  X.v[0] += X.v[1]; X.v[1] = RotL_32(X.v[1],R_32x2_7_0); X.v[1] ^= X.v[0]; }\n"
            "    if(Nrounds>23){\n"
            "        X.v[0] += ks[0]; X.v[1] += ks[1];\n"
            "        X.v[1] += 6;\n"
            "    }\n"
            "    if(Nrounds>24){  X.v[0] += X.v[1]; X.v[1] = RotL_32(X.v[1],R_32x2_0_0); X.v[1] ^= X.v[0]; }\n"
            "    if(Nrounds>25){  X.v[0] += X.v[1]; X.v[1] = RotL_32(X.v[1],R_32x2_1_0); X.v[1] ^= X.v[0]; }\n"
            "    if(Nrounds>26){  X.v[0] += X.v[1]; X.v[1] = RotL_32(X.v[1],R_32x2_2_0); X.v[1] ^= X.v[0]; }\n"
            "    if(Nrounds>27){  X.v[0] += X.v[1]; X.v[1] = RotL_32(X.v[1],R_32x2_3_0); X.v[1] ^= X.v[0]; }\n"
            "    if(Nrounds>27){\n"
            "        X.v[0] += ks[1]; X.v[1] += ks[2];\n"
            "        X.v[1] += 7;\n"
            "    }\n"
            "    if(Nrounds>28){  X.v[0] += X.v[1]; X.v[1] = RotL_32(X.v[1],R_32x2_4_0); X.v[1] ^= X.v[0]; }\n"
            "    if(Nrounds>29){  X.v[0] += X.v[1]; X.v[1] = RotL_32(X.v[1],R_32x2_5_0); X.v[1] ^= X.v[0]; }\n"
            "    if(Nrounds>30){  X.v[0] += X.v[1]; X.v[1] = RotL_32(X.v[1],R_32x2_6_0); X.v[1] ^= X.v[0]; }\n"
            "    if(Nrounds>31){  X.v[0] += X.v[1]; X.v[1] = RotL_32(X.v[1],R_32x2_7_0); X.v[1] ^= X.v[0]; }\n"
            "    if(Nrounds>31){\n"
            "        X.v[0] += ks[2]; X.v[1] += ks[0];\n"
            "        X.v[1] += 8;\n"
            "    }\n"
            "    return X;\n"
            "}\n"
            "__kernel void fill(__global uint * output,\n"
            "                   const uint output_size,\n"
            "                   const uint2 key,\n"
            "                   const uint2 counter)\n"
            "{\n"
            "    uint gid = get_global_id(0);\n"
            "    threefry2x32_ctr_t c;\n"
            "    c.v[0] = counter.x + gid;\n"
            "    c.v[1] = counter.y + (c.v[0] < counter.x ? 1 : 0);\n"
            "\n"
            "    threefry2x32_key_t k = { {key.x, key.y} };\n"
            "\n"
            "    threefry2x32_ctr_t result;\n"
            "    result = threefry2x32_R(THREEFRY2x32_DEFAULT_ROUNDS, c, k);\n"
            "\n"
            "    if(gid < output_size/2)\n"
            "    {\n"
            "       output[2 * gid] = result.v[0];\n"
            "       output[2 * gid + 1] = result.v[1];\n"
            "    }\n"
            "    else if(gid < (output_size+1)/2)\n"
            "       output[2 * gid] = result.v[0];\n"
            "}\n";

        m_program = cache->get_or_build(cache_key, std::string(), source, m_context);
    }

    // Engine state
    ulong_ m_key; // 2 x 32bit
    ulong_ m_counter;
    // OpenCL
    context m_context;
    program m_program;
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_RANDOM_THREEFRY_HPP

/* threefry_engine.hpp
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
*/