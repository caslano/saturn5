//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_COUNT_IF_WITH_THREADS_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_COUNT_IF_WITH_THREADS_HPP

#include <numeric>

#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/container/vector.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class InputIterator, class Predicate>
class count_if_with_threads_kernel : meta_kernel
{
public:
    typedef typename
        std::iterator_traits<InputIterator>::value_type
        value_type;

    count_if_with_threads_kernel()
        : meta_kernel("count_if_with_threads")
    {
    }

    void set_args(InputIterator first,
                  InputIterator last,
                  Predicate predicate)

    {
        typedef typename std::iterator_traits<InputIterator>::value_type T;

        m_size = detail::iterator_range_size(first, last);

        m_size_arg = add_arg<const ulong_>("size");
        m_counts_arg = add_arg<ulong_ *>(memory_object::global_memory, "counts");

        *this <<
            // thread parameters
            "const uint gid = get_global_id(0);\n" <<
            "const uint block_size = size / get_global_size(0);\n" <<
            "const uint start = block_size * gid;\n" <<
            "uint end = 0;\n" <<
            "if(gid == get_global_size(0) - 1)\n" <<
            "    end = size;\n" <<
            "else\n" <<
            "    end = block_size * gid + block_size;\n" <<

            // count values
            "uint count = 0;\n" <<
            "for(uint i = start; i < end; i++){\n" <<
                decl<const T>("value") << "="
                    << first[expr<uint_>("i")] << ";\n" <<
                if_(predicate(var<const T>("value"))) << "{\n" <<
                    "count++;\n" <<
                "}\n" <<
            "}\n" <<

            // write count
            "counts[gid] = count;\n";
    }

    size_t exec(command_queue &queue)
    {
        const device &device = queue.get_device();
        const context &context = queue.get_context();

        size_t threads = device.compute_units();

        const size_t minimum_block_size = 2048;
        if(m_size / threads < minimum_block_size){
            threads = static_cast<size_t>(
                          (std::max)(
                              std::ceil(float(m_size) / minimum_block_size),
                              1.0f
                          )
                      );
        }

        // storage for counts
        ::boost::compute::vector<ulong_> counts(threads, context);

        // exec kernel
        set_arg(m_size_arg, static_cast<ulong_>(m_size));
        set_arg(m_counts_arg, counts.get_buffer());
        exec_1d(queue, 0, threads, 1);

        // copy counts to the host
        std::vector<ulong_> host_counts(threads);
        ::boost::compute::copy(counts.begin(), counts.end(), host_counts.begin(), queue);

        // return sum of counts
        return std::accumulate(host_counts.begin(), host_counts.end(), size_t(0));
    }

private:
    size_t m_size;
    size_t m_size_arg;
    size_t m_counts_arg;
};

// counts values that match the predicate using one thread per block. this is
// optimized for cpu-type devices with a small number of compute units.
template<class InputIterator, class Predicate>
inline size_t count_if_with_threads(InputIterator first,
                                    InputIterator last,
                                    Predicate predicate,
                                    command_queue &queue)
{
    count_if_with_threads_kernel<InputIterator, Predicate> kernel;
    kernel.set_args(first, last, predicate);
    return kernel.exec(queue);
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_COUNT_IF_WITH_THREADS_HPP

/* count_if_with_threads.hpp
H+hlvCdlJy35j/1XWl2aOix67haO/zPVEuc+9t62S/rIe86R8OM1XRP3SuZ/T40Lv7yXY2emcPzabHnxZvF5ifUbZfuh2lb/TLR84v2Y+PA8BI+P/Bv4gD0/4yQHPzMjfPKbtu8dpha7N1mcWqkFX2+8Pmd+XRQfax4vO97VOPhzxOL9o9UdF0d6a/1i8thJ/uj9tCTr3xsal/ZyWzeZx+RPg/jYTP1HMvUU+s21Og1xgYd37D2a/SR6Rtn57980HvhQ9UPubVun1ske9LB/w84l9nwrUgsPT1m9nb9XRB4zHnnVRzh8Ez/s4D0PO/60+u04cOqJWkewgzoFeodbvrD/YD69oHWKPD6rXDQu/BNfq/eMai854rIAHqhDC0fvccnBH3rByQ/yqLpa+jWKj63WfxzknAj7F4hv9E3RePh5ieXZ97qG14k2b+ZoXOxJZz0UX+3UHz3Ztk+5THLwMpbxFF/eD4j7KPmJnpX2XsA4jI895NlD1i/R4sq+Gp4es3lzg/oxHu9h9M8prpPRUl+XPPNR9chknjfKg8MC2o42PzaYnk52HnaBrtFDi55Ee+/tYPlC3ZN5wXzgeXC1eGBesM8kL1KsTsm+kjj2Zhz2mbaeULeBr+PC0cf8Q26ixgVvbLz9pJZxF9lzbYLs5XqHzZdqEd6B9RB77+K5J7++lh3kLfUFeM+xfOa8hjzcEeHDzP7kFdLDNXUJ8py/c0W8j0keu5KsTlf8vLpN+vGbuif5Nlv6sYt8Q47nE/5zzks+3Kb7jLfB9mXPGm/UYfCT5yP2s15jdxnLS+r55Ou3tr7cq/HR3xC9SrG9dp86MPExuz8fb8/B0+x58Y/o/v4P7f23uvQzT5cl4a/WDL3vE/8rbb7ebnGw/caGA7Yf41wC/T/pPvE4TeOhh3UVezP1G+rwsMz2pyXKaWTOwa0ukSN5/KA+RR7OsHWS907aUrKXlnNI2mYWr4vjY2v0H2M5l6F/oXDsnWzPX86v8buq8dgIefFIXReethivvKfBf6tofjb5iv76z7K2Htxn5y+LbB0vrmvvVos/N1lda6blxX0232kZJz9qj821Ohl5Cx87pR9e69p54fm2Lu+19e8V9eM+5/j4e7qt+9xnPv/Nzh04t4HP062O1N72nQvoR/1ULXFi30Bc2Wfg92p7bxms+/ivfUA8/DIu9zl3Jm95TjAedRHsOqv4fEjjIVfR6mqbhJM/8daP/Rz+U1+FL96riE87teTbUOTE9yTjf7Za9Dxs7dl27s2+Ad76aD8Iv++Z/8etPkZ+MD+pg5F3NXRNHo22eXmNPWeW2PvuQzYv4J/x5qglzg9ZXPraPqmP8ha9nAsyL8vaucdB3ac/51Dw9ZG9/zLvyLe5Fi/ev+H7EvygDq0We5kvxFHPqSrwr/WpNP0vlx2MT3/yuUHUnvmTWvotEG/4Qz0I/R2NZz0PJxB35jv62Y/j52qrX4/T/h0+9ss+8qBQfNByLoR/rAPosXPet/eZvtbCiXMvm9cN2H8oTkeFEz/yg7j/bPNkjHDmQ4704g/PG+T4Pov87C29jMf8wR7JxWPnKPXj/maNx/VLNs85Z8CuJ20+sA/h/rVq4XUKcrLnPo2HH/fLDvT/Yee7f9h6z/4e3jaaP501Hv7wHgkPGy0fFxkPDxSf76klTt1t3fzE9jHsM9D/uu0T46N9fzWeb+RJ42g/NbZIcvjVP7Jnsr5jW6H/2Mz5OXHBbuwabvZSH0Ne1+TF9pZWp2U/x/hLi/dFtq4Okn3YU/xdW4Fa7DW7Bu+1/TV1LNaj39SfPOR5zTj4hf2ZwrGH/QV5RZ2a8Xiu0I9zGHi5z+ovej8sBc/dGId9uOI=
*/