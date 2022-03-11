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