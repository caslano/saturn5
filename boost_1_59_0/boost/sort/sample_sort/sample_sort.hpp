//----------------------------------------------------------------------------
/// @file sample_sort.hpp
/// @brief contains the class sample_sort
///
/// @author Copyright (c) 2016 Francisco Jose Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanying file LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#ifndef __BOOST_SORT_PARALLEL_DETAIL_SAMPLE_SORT_HPP
#define __BOOST_SORT_PARALLEL_DETAIL_SAMPLE_SORT_HPP

#include <functional>
#include <future>
#include <iterator>
#include <memory>
#include <type_traits>
#include <vector>

#include <algorithm>
#include <boost/sort/spinsort/spinsort.hpp>
#include <boost/sort/common/indirect.hpp>
#include <boost/sort/common/util/atomic.hpp>
#include <boost/sort/common/merge_four.hpp>
#include <boost/sort/common/merge_vector.hpp>
#include <boost/sort/common/range.hpp>

namespace boost
{
namespace sort
{
namespace sample_detail
{
//---------------------------------------------------------------------------
//                    USING SENTENCES
//---------------------------------------------------------------------------
namespace bsc = boost::sort::common;
namespace bss = boost::sort::spin_detail;
namespace bscu = boost::sort::common::util;
using bsc::range;
using bscu::atomic_add;
using bsc::merge_vector4;
using bsc::uninit_merge_level4;
using bsc::less_ptr_no_null;

//
///---------------------------------------------------------------------------
/// @struct sample_sort
/// @brief This a structure for to implement a sample sort, exception
///        safe
/// @tparam
/// @remarks
//----------------------------------------------------------------------------
template<class Iter_t, class Compare>
struct sample_sort
{
    //------------------------------------------------------------------------
    //                     DEFINITIONS
    //------------------------------------------------------------------------
    typedef value_iter<Iter_t> value_t;
    typedef range<Iter_t> range_it;
    typedef range<value_t *> range_buf;
    typedef sample_sort<Iter_t, Compare> this_t;

    //------------------------------------------------------------------------
    //                VARIABLES AND CONSTANTS
    //------------------------------------------------------------------------
    // minimun numbers of elements for to be sortd in parallel mode
    static const uint32_t thread_min = (1 << 16);

    // Number of threads to use in the algorithm
    // Number of intervals for to do the internal division of the data
    uint32_t nthread, ninterval;

    // Bool variables indicating if the auxiliary memory is constructed
    // and indicating in the auxiliary memory had been obtained inside the
    /// algorithm or had been received as a parameter
    bool construct = false, owner = false;

    // Comparison object for to compare two elements
    Compare comp;

    // Range with all the elements to sort
    range_it global_range;

    // range with the auxiliary memory
    range_buf global_buf;

    // vector of futures
    std::vector<std::future<void>> vfuture;

    // vector of vectors which contains the ranges to merge obtained in the
    // subdivision
    std::vector<std::vector<range_it>> vv_range_it;

    // each vector of ranges of the vv_range_it, need their corresponding buffer
    // for to do the merge
    std::vector<std::vector<range_buf>> vv_range_buf;

    // Initial vector of ranges
    std::vector<range_it> vrange_it_ini;

    // Initial vector of buffers
    std::vector<range_buf> vrange_buf_ini;

    // atomic counter for to know when are finished the function_t created
    // inside a function
    std::atomic<uint32_t> njob;

    // Indicate if an error in the algorithm for to undo all
    bool error;

    //------------------------------------------------------------------------
    //                       FUNCTIONS OF THE STRUCT
    //------------------------------------------------------------------------
    void initial_configuration(void);

    sample_sort (Iter_t first, Iter_t last, Compare cmp, uint32_t num_thread,
                 value_t *paux, size_t naux);

    sample_sort(Iter_t first, Iter_t last)
    : sample_sort (first, last, Compare(), std::thread::hardware_concurrency(),
                   nullptr, 0) { };

    sample_sort(Iter_t first, Iter_t last, Compare cmp)
    : sample_sort(first, last, cmp, std::thread::hardware_concurrency(),
                  nullptr, 0) { };

    sample_sort(Iter_t first, Iter_t last, uint32_t num_thread)
    : sample_sort(first, last, Compare(), num_thread, nullptr, 0) { };

    sample_sort(Iter_t first, Iter_t last, Compare cmp, uint32_t num_thread)
    : sample_sort(first, last, cmp, num_thread, nullptr, 0) { };

    sample_sort(Iter_t first, Iter_t last, Compare cmp, uint32_t num_thread,
                range_buf range_buf_initial)
    : sample_sort(first, last, cmp, num_thread,
                  range_buf_initial.first, range_buf_initial.size()) { };

    void destroy_all(void);
    //
    //-----------------------------------------------------------------------------
    //  function :~sample_sort
    /// @brief destructor of the class. The utility is to destroy the temporary
    ///        buffer used in the sorting process
    //-----------------------------------------------------------------------------
    ~sample_sort(void) { destroy_all(); };
    //
    //-----------------------------------------------------------------------
    //  function : execute first
    /// @brief this a function to assign to each thread in the first merge
    //-----------------------------------------------------------------------
    void execute_first(void)
    {
        uint32_t job = 0;
        while ((job = atomic_add(njob, 1)) < ninterval)
        {
            uninit_merge_level4(vrange_buf_ini[job], vv_range_it[job],
                            vv_range_buf[job], comp);
        };
    };
    //
    //-----------------------------------------------------------------------
    //  function : execute
    /// @brief this is a function to assignt each thread the final merge
    //-----------------------------------------------------------------------
    void execute(void)
    {
        uint32_t job = 0;
        while ((job = atomic_add(njob, 1)) < ninterval)
        {
            merge_vector4(vrange_buf_ini[job], vrange_it_ini[job],
                            vv_range_buf[job], vv_range_it[job], comp);
        };
    };
    //
    //-----------------------------------------------------------------------
    //  function : first merge
    /// @brief Implement the merge of the initially sparse ranges
    //-----------------------------------------------------------------------
    void first_merge(void)
    { //---------------------------------- begin --------------------------
        njob = 0;

        for (uint32_t i = 0; i < nthread; ++i)
        {
            vfuture[i] = std::async(std::launch::async, &this_t::execute_first,
                            this);
        };
        for (uint32_t i = 0; i < nthread; ++i)
            vfuture[i].get();
    };
    //
    //-----------------------------------------------------------------------
    //  function : final merge
    /// @brief Implement the final merge of the ranges
    //-----------------------------------------------------------------------
    void final_merge(void)
    { //---------------------------------- begin --------------------------
        njob = 0;

        for (uint32_t i = 0; i < nthread; ++i)
        {
            vfuture[i] = std::async(std::launch::async, &this_t::execute, this);
        };
        for (uint32_t i = 0; i < nthread; ++i)
            vfuture[i].get();
    };
    //----------------------------------------------------------------------------
};
//                    End class sample_sort
//----------------------------------------------------------------------------
//
//############################################################################
//                                                                          ##
//              N O N    I N L I N E      F U N C T I O N S                 ##
//                                                                          ##
//                                                                          ##
//############################################################################
//
//-----------------------------------------------------------------------------
//  function : sample_sort
/// @brief constructor of the class
///
/// @param first : iterator to the first element of the range to sort
/// @param last : iterator after the last element to the range to sort
/// @param cmp : object for to compare two elements pointed by Iter_t iterators
/// @param num_thread : Number of threads to use in the process. When this value
///                     is lower than 2, the sorting is done with 1 thread
/// @param paux : pointer to the auxiliary memory. If nullptr, the memory is
///               created inside the class
/// @param naux : number of elements of the memory pointed by paux
//-----------------------------------------------------------------------------
template<class Iter_t, typename Compare>
sample_sort<Iter_t, Compare>
::sample_sort (Iter_t first, Iter_t last, Compare cmp, uint32_t num_thread,
               value_t *paux, size_t naux)
: nthread(num_thread), owner(false), comp(cmp), global_range(first, last),
  global_buf(nullptr, nullptr), error(false)
{
    assert((last - first) >= 0);
    size_t nelem = size_t(last - first);
    construct = false;
    njob = 0;
    vfuture.resize(nthread);

    // Adjust when have many threads and only a few elements
    while (nelem > thread_min and (nthread * nthread) > (nelem >> 3))
    {
        nthread /= 2;
    };
    ninterval = (nthread << 3);

    if (nthread < 2 or nelem <= (thread_min))
    {
        bss::spinsort<Iter_t, Compare>(first, last, comp);
        return;
    };

    //------------------- check if sort --------------------------------------
    bool sw = true;
    for (Iter_t it1 = first, it2 = first + 1;
                    it2 != last and (sw = not comp(*it2, *it1)); it1 = it2++);
    if (sw) return;

    //------------------- check if reverse sort ---------------------------
    sw = true;
    for (Iter_t it1 = first, it2 = first + 1;
                    it2 != last and (sw = comp(*it2, *it1)); it1 = it2++);
    if (sw)
    {
        size_t nelem2 = nelem >> 1;
        Iter_t it1 = first, it2 = last - 1;
        for (size_t i = 0; i < nelem2; ++i)
            std::swap(*(it1++), *(it2--));
        return;
    };

    if (paux != nullptr)
    {
        assert(naux != 0);
        global_buf.first = paux;
        global_buf.last = paux + naux;
        owner = false;
    }
    else
    {
        value_t *ptr = std::get_temporary_buffer<value_t>(nelem).first;
        if (ptr == nullptr) throw std::bad_alloc();
        owner = true;
        global_buf = range_buf(ptr, ptr + nelem);
    };
    //------------------------------------------------------------------------
    //                    PROCESS
    //------------------------------------------------------------------------
    try
    {
        initial_configuration();
    } catch (std::bad_alloc &)
    {
        error = true;
    };
    if (not error)
    {
        first_merge();
        construct = true;
        final_merge();
    };
    if (error)
    {
        destroy_all();
        throw std::bad_alloc();
    };
}
;
//
//-----------------------------------------------------------------------------
//  function : destroy_all
/// @brief destructor of the class. The utility is to destroy the temporary
///        buffer used in the sorting process
//-----------------------------------------------------------------------------
template<class Iter_t, typename Compare>
void sample_sort<Iter_t, Compare>::destroy_all(void)
{
    if (construct)
    {
        destroy(global_buf);
        construct = false;
    }
    if (global_buf.first != nullptr and owner)
        std::return_temporary_buffer(global_buf.first);
}
//
//-----------------------------------------------------------------------------
//  function : initial_configuration
/// @brief Create the internal data structures, and obtain the inital set of
///        ranges to merge
//-----------------------------------------------------------------------------
template<class Iter_t, typename Compare>
void sample_sort<Iter_t, Compare>::initial_configuration(void)
{
    std::vector<range_it> vmem_thread;
    std::vector<range_buf> vbuf_thread;
    size_t nelem = global_range.size();

    //------------------------------------------------------------------------
    size_t cupo = nelem / nthread;
    Iter_t it_first = global_range.first;
    value_t *buf_first = global_buf.first;
    vmem_thread.reserve(nthread + 1);
    vbuf_thread.reserve(nthread + 1);

    for (uint32_t i = 0; i < (nthread - 1); ++i, it_first += cupo, buf_first +=
                    cupo)
    {
        vmem_thread.emplace_back(it_first, it_first + cupo);
        vbuf_thread.emplace_back(buf_first, buf_first + cupo);
    };

    vmem_thread.emplace_back(it_first, global_range.last);
    vbuf_thread.emplace_back(buf_first, global_buf.last);

    //------------------------------------------------------------------------
    // Sorting of the ranges
    //------------------------------------------------------------------------
    std::vector<std::future<void>> vfuture(nthread);

    for (uint32_t i = 0; i < nthread; ++i)
    {
        auto func = [=]()
        {
            bss::spinsort<Iter_t, Compare> (vmem_thread[i].first,
                            vmem_thread[i].last, comp,
                            vbuf_thread[i]);
        };
        vfuture[i] = std::async(std::launch::async, func);
    };

    for (uint32_t i = 0; i < nthread; ++i)
        vfuture[i].get();

    //------------------------------------------------------------------------
    // Obtain the vector of milestones
    //------------------------------------------------------------------------
    std::vector<Iter_t> vsample;
    vsample.reserve(nthread * (ninterval - 1));

    for (uint32_t i = 0; i < nthread; ++i)
    {
        size_t distance = vmem_thread[i].size() / ninterval;
        for (size_t j = 1, pos = distance; j < ninterval; ++j, pos += distance)
        {
            vsample.push_back(vmem_thread[i].first + pos);
        };
    };
    typedef less_ptr_no_null<Iter_t, Compare> compare_ptr;
    typedef typename std::vector<Iter_t>::iterator it_to_it;

    bss::spinsort<it_to_it, compare_ptr>(vsample.begin(), vsample.end(),
                    compare_ptr(comp));

    //------------------------------------------------------------------------
    // Create the final milestone vector
    //------------------------------------------------------------------------
    std::vector<Iter_t> vmilestone;
    vmilestone.reserve(ninterval);

    for (uint32_t pos = nthread >> 1; pos < vsample.size(); pos += nthread)
    {
        vmilestone.push_back(vsample[pos]);
    };

    //------------------------------------------------------------------------
    // Creation of the first vector of ranges
    //------------------------------------------------------------------------
    std::vector<std::vector<range<Iter_t>>>vv_range_first (nthread);

    for (uint32_t i = 0; i < nthread; ++i)
    {
        Iter_t itaux = vmem_thread[i].first;

        for (uint32_t k = 0; k < (ninterval - 1); ++k)
        {
            Iter_t it2 = std::upper_bound(itaux, vmem_thread[i].last,
                            *vmilestone[k], comp);

            vv_range_first[i].emplace_back(itaux, it2);
            itaux = it2;
        };
        vv_range_first[i].emplace_back(itaux, vmem_thread[i].last);
    };

    //------------------------------------------------------------------------
    // Copy in buffer and  creation of the final matrix of ranges
    //------------------------------------------------------------------------
    vv_range_it.resize(ninterval);
    vv_range_buf.resize(ninterval);
    vrange_it_ini.reserve(ninterval);
    vrange_buf_ini.reserve(ninterval);

    for (uint32_t i = 0; i < ninterval; ++i)
    {
        vv_range_it[i].reserve(nthread);
        vv_range_buf[i].reserve(nthread);
    };

    Iter_t it = global_range.first;
    value_t *it_buf = global_buf.first;

    for (uint32_t k = 0; k < ninterval; ++k)
    {
        size_t nelem_interval = 0;

        for (uint32_t i = 0; i < nthread; ++i)
        {
            size_t nelem_range = vv_range_first[i][k].size();
            if (nelem_range != 0)
            {
                vv_range_it[k].push_back(vv_range_first[i][k]);
            };
            nelem_interval += nelem_range;
        };

        vrange_it_ini.emplace_back(it, it + nelem_interval);
        vrange_buf_ini.emplace_back(it_buf, it_buf + nelem_interval);

        it += nelem_interval;
        it_buf += nelem_interval;
    };
}
;
//
//****************************************************************************
}
;
//    End namespace sample_detail
//****************************************************************************
//
namespace bscu = boost::sort::common::util;
//
//############################################################################
//                                                                          ##
//                                                                          ##
//                       S A M P L E _ S O R T                              ##
//                                                                          ##
//                                                                          ##
//############################################################################
//
//-----------------------------------------------------------------------------
//  function : sample_sort
/// @brief parallel sample sort  algorithm (stable sort)
///
/// @param first : iterator to the first element of the range to sort
/// @param last : iterator after the last element to the range to sort
//-----------------------------------------------------------------------------
template<class Iter_t>
void sample_sort(Iter_t first, Iter_t last)
{
    typedef compare_iter<Iter_t> Compare;
    sample_detail::sample_sort<Iter_t, Compare>(first, last);
};
//
//-----------------------------------------------------------------------------
//  function : sample_sort
/// @brief parallel sample sort  algorithm (stable sort)
///
/// @param first : iterator to the first element of the range to sort
/// @param last : iterator after the last element to the range to sort
/// @param nthread : Number of threads to use in the process. When this value
///                  is lower than 2, the sorting is done with 1 thread
//-----------------------------------------------------------------------------
template<class Iter_t>
void sample_sort(Iter_t first, Iter_t last, uint32_t nthread)
{
    typedef compare_iter<Iter_t> Compare;
    sample_detail::sample_sort<Iter_t, Compare>(first, last, nthread);
};
//
//-----------------------------------------------------------------------------
//  function : sample_sort
/// @brief parallel sample sort  algorithm (stable sort)
///
/// @param first : iterator to the first element of the range to sort
/// @param last : iterator after the last element to the range to sort
/// @param comp : object for to compare two elements pointed by Iter_t
///               iterators
//-----------------------------------------------------------------------------
template<class Iter_t, class Compare, bscu::enable_if_not_integral<Compare> * =
                nullptr>
void sample_sort(Iter_t first, Iter_t last, Compare comp)
{
    sample_detail::sample_sort<Iter_t, Compare>(first, last, comp);
};
//
//-----------------------------------------------------------------------------
//  function : sample_sort
/// @brief parallel sample sort  algorithm (stable sort)
///
/// @param first : iterator to the first element of the range to sort
/// @param last : iterator after the last element to the range to sort
/// @param comp : object for to compare two elements pointed by Iter_t
///               iterators
/// @param nthread : Number of threads to use in the process. When this value
///                  is lower than 2, the sorting is done with 1 thread
//-----------------------------------------------------------------------------
template<class Iter_t, class Compare>
void sample_sort(Iter_t first, Iter_t last, Compare comp, uint32_t nthread)
{
    sample_detail::sample_sort<Iter_t, Compare>(first, last, comp, nthread);
};
//
//****************************************************************************
};//    End namespace sort
};//    End namespace boost
//****************************************************************************
//
#endif

/* sample_sort.hpp
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
*/