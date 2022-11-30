//----------------------------------------------------------------------------
/// @file flat_stable_sort.hpp
/// @brief Flat stable sort algorithm
///
/// @author Copyright (c) 2017 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanying file LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#ifndef __BOOST_SORT_FLAT_STABLE_SORT_HPP
#define __BOOST_SORT_FLAT_STABLE_SORT_HPP

#include <boost/sort/insert_sort/insert_sort.hpp>
#include <boost/sort/common/util/insert.hpp>
#include <boost/sort/common/merge_block.hpp>
#include <boost/sort/common/sort_basic.hpp>
#include <boost/sort/common/range.hpp>
#include <boost/sort/common/util/traits.hpp>
#include <boost/sort/common/indirect.hpp>

#include <cstdlib>
#include <functional>
#include <iterator>
#include <memory>
#include <type_traits>
#include <vector>

namespace boost
{
namespace sort
{
namespace flat_internal
{
namespace bsc = boost::sort::common;
namespace bscu = boost::sort::common::util;
//---------------------------------------------------------------------------
/// @struct flat_stable_sort
/// @brief  This class implement s stable sort algorithm with 1 thread, with
///         an auxiliary memory of N/2 elements
//----------------------------------------------------------------------------
template <class Iter_t, typename Compare = bscu::compare_iter<Iter_t>,
           uint32_t Power2 = 10>
class flat_stable_sort: public bsc::merge_block<Iter_t, Compare, Power2>
{
    //------------------------------------------------------------------------
    //               DEFINITIONS AND CONSTANTS
    //------------------------------------------------------------------------
    typedef bsc::merge_block<Iter_t, Compare, Power2> merge_block_t;

    //-------------------------------------------------------------------------
    //                  D E F I N I T I O N S
    //-------------------------------------------------------------------------
    typedef typename merge_block_t::value_t value_t;
    typedef typename merge_block_t::range_pos range_pos;
    typedef typename merge_block_t::range_it range_it;
    typedef typename merge_block_t::range_buf range_buf;
    typedef typename merge_block_t::it_index it_index;
    typedef typename merge_block_t::circular_t circular_t;

    //------------------------------------------------------------------------
    //                          CONSTANTS
    //------------------------------------------------------------------------
    using merge_block_t::BLOCK_SIZE;
    using merge_block_t::LOG_BLOCK;

    using merge_block_t::index;
    using merge_block_t::cmp;
    using merge_block_t::ptr_circ;

    using merge_block_t::get_range;
    using merge_block_t::get_group_range;
    using merge_block_t::merge_range_pos;
    using merge_block_t::move_range_pos_backward;
    using merge_block_t::rearrange_with_index;

public:
    //------------------------------------------------------------------------
    //                   PUBLIC FUNCTIONS
    //-------------------------------------------------------------------------
    flat_stable_sort(Iter_t first, Iter_t last, Compare comp,
                     circular_t *ptr_circ)
                    : merge_block_t(first, last, comp, ptr_circ)
    {
        divide(index.begin(), index.end());
        rearrange_with_index();
    };

    flat_stable_sort(Iter_t first, Iter_t last, Compare comp = Compare())
                    : flat_stable_sort(first, last, comp, nullptr) { };

    void divide(it_index itx_first, it_index itx_last);

    void sort_small(it_index itx_first, it_index itx_last);

    bool is_sorted_forward(it_index itx_first, it_index itx_last);

    bool is_sorted_backward(it_index itx_first, it_index itx_last);
};
//----------------------------------------------------------------------------
//  End of class flat_stable_sort
//----------------------------------------------------------------------------
//
//------------------------------------------------------------------------
//  function :
/// @brief :
/// @param Pos :
/// @return
//------------------------------------------------------------------------
template <class Iter_t, typename Compare, uint32_t Power2>
void flat_stable_sort <Iter_t, Compare, Power2>
::divide(it_index itx_first, it_index itx_last)
{
    size_t nblock = size_t(itx_last - itx_first);
    if (nblock < 5)
    {   sort_small(itx_first, itx_last);
        return;
    };
    if ( nblock > 7)
    {   if (is_sorted_forward(itx_first, itx_last)) return;
        if (is_sorted_backward(itx_first, itx_last)) return;
    };
    size_t nblock1 = (nblock + 1) >> 1;
    divide(itx_first, itx_first + nblock1);
    divide(itx_first + nblock1, itx_last);
    merge_range_pos(itx_first, itx_first + nblock1, itx_last);
};
//
//------------------------------------------------------------------------
//  function : sort_small
/// @brief :
/// @param
/// @param
/// @param
//------------------------------------------------------------------------
template <class Iter_t, typename Compare, uint32_t Power2>
void flat_stable_sort <Iter_t, Compare, Power2>
::sort_small(it_index itx_first, it_index itx_last)
{
    size_t nblock = size_t(itx_last - itx_first);
    assert(nblock > 0 and nblock < 5);
    value_t *paux = ptr_circ->get_buffer();
    range_it rng_data = get_group_range(*itx_first, nblock);

    if (nblock < 3)
    {
        range_buf rng_aux(paux, paux + rng_data.size());
        range_sort_data(rng_data, rng_aux, cmp);
        return;
    };

    //--------------------------------------------------------------------
    // division of range_data in two ranges for be sorted and merged
    //--------------------------------------------------------------------
    size_t nblock1 = (nblock + 1) >> 1;
    range_it rng_data1 = get_group_range(*itx_first, nblock1);
    range_it rng_data2(rng_data1.last, rng_data.last);
    range_buf rng_aux1(paux, paux + rng_data1.size());
    range_buf rng_aux2(paux, paux + rng_data2.size());

    range_sort_data(rng_data2, rng_aux2, cmp);
    range_sort_buffer(rng_data1, rng_aux1, cmp);
    merge_half(rng_data, rng_aux1, rng_data2, cmp);
};
//
//------------------------------------------------------------------------
//  function : is_sorted_forward
/// @brief : return if the data are ordered,
/// @param itx_first : iterator to the first block in the index
/// @param itx_last : iterator to the last block in the index
/// @return : true : the data are ordered false : not ordered
//------------------------------------------------------------------------
template <class Iter_t, typename Compare, uint32_t Power2>
bool flat_stable_sort <Iter_t, Compare, Power2>
::is_sorted_forward(it_index itx_first, it_index itx_last)
{
    size_t nblock = size_t(itx_last - itx_first);
    range_it rng = get_group_range(*itx_first, nblock);
    size_t nelem = rng.size();
    size_t min_process = (std::max)(BLOCK_SIZE, (nelem >> 3));

    size_t nsorted1 = bsc::number_stable_sorted_forward (rng.first, rng.last,
                                                         min_process, cmp);
    if (nsorted1 == nelem) return true;
    if (nsorted1 == 0) return false;

    size_t nsorted2 = nelem - nsorted1;
    Iter_t itaux = rng.first + nsorted1;
    if (nsorted2 <= (BLOCK_SIZE << 1))
    {
        flat_stable_sort(itaux, rng.last, cmp, ptr_circ);
        bscu::insert_sorted(rng.first, itaux, rng.last, cmp,
                            ptr_circ->get_buffer());
    }
    else
    {   // Adjust the size of the sorted data to a number of blocks
        size_t mask = ~(BLOCK_SIZE - 1);
        size_t nsorted1_adjust = nsorted1 & mask;
        flat_stable_sort(rng.first + nsorted1_adjust, rng.last, cmp,
                         ptr_circ);
        size_t nblock1 = nsorted1_adjust >> Power2;
        merge_range_pos(itx_first, itx_first + nblock1, itx_last);
    };
    return true;
};
//
//------------------------------------------------------------------------
//  function : is_sorted_backward
/// @brief : return if the data are ordered,
/// @param itx_first : iterator to the first block in the index
/// @param itx_last : iterator to the last block in the index
/// @return : true : the data are ordered false : not ordered
//------------------------------------------------------------------------
template <class Iter_t, typename Compare, uint32_t Power2>
bool flat_stable_sort <Iter_t, Compare, Power2>
::is_sorted_backward(it_index itx_first, it_index itx_last)
{
    size_t nblock = size_t(itx_last - itx_first);
    range_it rng = get_group_range(*itx_first, nblock);

    size_t nelem = rng.size();
    size_t min_process = (std::max)(BLOCK_SIZE, (nelem >> 3));

    size_t nsorted2 = bsc::number_stable_sorted_backward(rng.first, rng.last,
                                                         min_process, cmp);
    if (nsorted2 == nelem) return true;
    if (nsorted2 == 0 ) return false;
    Iter_t itaux = rng.last - nsorted2;
    size_t nsorted1 = nelem - nsorted2;

    if (nsorted1 <= (BLOCK_SIZE << 1))
    {
        flat_stable_sort(rng.first, itaux, cmp, ptr_circ);
        bscu::insert_sorted_backward(rng.first, itaux, rng.last, cmp,
                                     ptr_circ->get_buffer());
    }
    else
    {   // Adjust the size of nsorted2 for to be a number of blocks
        size_t nblock1 = (nsorted1 + BLOCK_SIZE - 1) >> Power2;
        size_t nsorted1_adjust = (nblock1 << Power2);
        flat_stable_sort(rng.first, rng.first + nsorted1_adjust, cmp,
                         ptr_circ);
        merge_range_pos(itx_first, itx_first + nblock1, itx_last);
    };
    return true;
};
//****************************************************************************
};// End namespace flat_internal
//****************************************************************************
//
namespace bscu = boost::sort::common::util;
namespace flat = boost::sort::flat_internal;
//
///---------------------------------------------------------------------------
//  function flat_stable_sort
/// @brief This class is select the block size in the block_indirect_sort
///        algorithm depending of the type and size of the data to sort
///
//----------------------------------------------------------------------------
template <class Iter_t, class Compare = bscu::compare_iter<Iter_t>,
           bscu::enable_if_string<value_iter<Iter_t> > * = nullptr>
inline void flat_stable_sort (Iter_t first, Iter_t last,
                                 Compare cmp = Compare())
{
    flat::flat_stable_sort<Iter_t, Compare, 6> (first, last, cmp);
};

template<size_t Size>
struct block_size_fss
{
    static constexpr const uint32_t BitsSize =
                    (Size == 0) ? 0 : (Size > 128) ? 7 : bscu::tmsb[Size - 1];
    static constexpr const uint32_t sz[10] =
    { 10, 10, 10, 9, 8, 7, 6, 6 };
    static constexpr const uint32_t data = sz[BitsSize];
};

//
///---------------------------------------------------------------------------
//  function flat_stable_sort
/// @brief This class is select the block size in the flat_stable_sort
///        algorithm depending of the type and size of the data to sort
///
//----------------------------------------------------------------------------
template <class Iter_t, class Compare = bscu::compare_iter<Iter_t>,
           bscu::enable_if_not_string<value_iter<Iter_t> >* = nullptr>
inline void flat_stable_sort (Iter_t first, Iter_t last,
                                 Compare cmp = Compare())
{
    flat::flat_stable_sort<Iter_t, Compare,
                           block_size_fss<sizeof(value_iter<Iter_t> )>::data>
        (first, last, cmp);
};

template<class Iter_t, class Compare = compare_iter<Iter_t> >
inline void indirect_flat_stable_sort (Iter_t first, Iter_t last,
                                           Compare comp = Compare())
{
    typedef typename std::vector<Iter_t>::iterator itx_iter;
    typedef common::less_ptr_no_null<Iter_t, Compare> itx_comp;
    common::indirect_sort ( flat_stable_sort<itx_iter, itx_comp>,
                            first, last, comp);
};

//****************************************************************************
};//    End namespace sort
};//    End namepspace boost
//****************************************************************************
//
#endif

/* flat_stable_sort.hpp
eQSuSxwZGUkBfBw2RR0FVUk4rFW0E0LSKjqNgfWMxsqGgk5oT5386RP2oT+D0BuX6uPyVgjzMoSxKBUqOEhThxQV2WLw9V2G70ycTJ74fAcCIIP+U3uJrb/tMlqm8RP0xVNVRL/DcppDocgV1nwSja3X05mqTd+pBer9deqtvoBXneX/0FM1kL7Q6xYN1qbvjWYFU/iBlmCvXqe2ssqe3aLSyTDEsTnMiMxAZoeAWw90jNMCXuQIZcyCLJvJMcSlc7zVZjzk5JxNYO7pPiRTKCzKM539jE8OB1r7Ej5FfA+Eaq3Xp+/kOQCj49r2VRbOYDdyd+zwVP2XiOjoGCmPCQXFXctxKD2lBWr0QD0dTbX8AqeRf0f5hVpgmSm5CcmzahFDnNKXPtGL9+KrcS7NHiuuAyswu97zdI0WOJCcEc0y1Lr0XGiBOn+gXhn9U9WdK6vTpx/QAtWo0fkb3+watbceqKYmkg6j+IAROKAHDvgDO+9/nkr6TlNzUyP0MmnbgpApOpO1Op0MW6aGzCNrr6HupIZoCvjUQtAdPbBFJ7qc4CEylIhjTqTuWYkjUp5nWGOaqt70gOkZOtKc5pEWMtR661BLAu8U5oWCIUnbRLIYTOuNgU9w4NwDqGQXTrmKnXa1KBTidzgBfYED6mjZ2cT0uqn69JrYdtfUqL02AMSXJ4/lI/JG8Rhqjdw12AbJMl75Bj4kZzdagfl+vxpcVBPNER2OzTTAxPSGqdpsQXBnOg5K2EsdjpdnxC2fvdo8INOPJtMj6u+B9CH5CU+Ff0cqcwBvKJ5K3FrLQRPOD3LnWglXNt5qYTRwaX/8H8O+MzavHKrOBLjCfXNa/vd8l3TjjbUOPSFZyiHdBcU4NkMrbQQ2cWy6/TghYIXontbSoLihwsx3moppVNzJGSKBUK++NYN1Mp3Djj3vAOmhOnvXJPtSL/oR0papFYpMAg5d3UilhGZHHqJcGzx35rSIH5FLKDqreg80fN//ns0NiD12xO4UNrg0GBvBUCLjGYKvHACY6AxxbPGD0EyJirYwnQuJitZwiVbcphP4TXW3TLcDTNoIBYXw/ZhE4AkoDuoqqAUH7ctQbeAJDzZ70Bl1WxlSwX+0ImKC2ipRIyR3m9Y7mHhFrOSzI065zbSK6trAKzCsMomdQWGmWhBViOazBJ4URBEG3tQd1FKzrcZDLREENttsWTalf6z4Cdfy4pds1IPlxevAKuLVMptNceNVrPglZ6x4nZM6TfxrpDiTRiKgJGi7LX1obYRxuEk/3elCMG46wq7HGYdsb42G2sQoH9lijJHS/ZWmHuGF//YzSF0aLYuvm+KdhilKCDSUb6UpBu+Jzd82NTG9lbaTuVGrnme9srDIuwOi3+9N31nm9XvoC9pLRZ9PYfttLwmK234AOJXq+4WPnoGx3BH1Vnf1pxW3PYkVF5dcbVofP/EJu/ymXYvd4q+rIbFoBZSekyMD7orjV5kmzBEqH2V9fWSlH1nLmtlCe1QOCxsuMj0LlDyUpUPCSKXte/ajThkwRmPZhelWMKmK412yXdcd2XjMvipXVHEc8fwnLYeUP95Cfb/hCekAzOwwjNnOBMh4qpA8wjfbpZwubNIthjbEmv8iul0bIbCH/83UlXki9rSwtjwwlfvEaKcBdzTx2VRCGLAbXYQwBXT+bWRRSY6xkVEyreg6/hfByTfXdhkv2ekUyQkRRsU7xDmThoSoPIJkIoQuAUPV0PJwWM/ewvEOneOz28qnobs3UzenH4JNrTLQ9wyEO2ofs9E68cpwEwQlNivXGcENzXh0t47+GqNcQ0z0RnMvjv6O1c3VDbQ2OyJttCrVh7DR7/8dTslcZMEy9E8LdvtrEZH3HScRfP79RGBs9MF0xJu/31N1JnVgknLDJOW0Scq10pRxnziEWDW7xF9RvVdSoSZb7qIqSsKgQS2WfE8iPhT0d7I2kYCHGhPpAxvky7+GE3H4+lnea9o77Pn3Dnv+vbOT/7J33Dvs/PcOnP9E5zmSMP8FdC/3X8mmuui6+OwALLm9xAl2qsMPs1feEPVq3SFflxhvwbWNeMK34DBnrEYgsuSQ1OtEAu2xMAQZmvQ4nsZq2oLijw2dxAsn5L2XIFLLEc8s7zRaOmgjRjhA20+M3lMF58hEPJdetMC0JILYZdWX9aBF+M9jcP6G7uW29zuhRu0dcKv9IuUvDsKzzz+m+gE3BQdDW6G/LTVlC2zvWGMf8OHUYCTIxvyOz+BZFtspVRKJRCNmORSM0M2yUmPguA+JzorjITzIV1C9yCzfGIz2pZcuME90I9M+623+HzyrHsEO6aGPa8/fVaTFYWdUtrSUJg8GR/EDZj3P7OmUfnzFjTDN3Y8hJPDSdLU0kdriZXC3VHsZCXy+pDo5yqqowawovrcT/1pZX0sRAYgLW1VcSVVE1o7JxawMJ7Qhrn6M499Gc6v1G2kex6xhOcSn3+muf85uoqMVZxdtSz5eW9lZ4P4OmnlMInCVix8dWATky673QfElgvVID7hdS6mFbWvSsQikzKV/TLiWj/7nP2lX9giKcVV9bJZUR+q4wzqHefTvV4Zoq/CLDZ/E6w5pDfiFFKLJw3gbHZcFH7D+xCXDfRFLpXlZETGkdtxQkElaUZ5WNEwrGq4VjdCKRmaYRuj9NK9e4tSCTp2IlqBLJ1I46NZL6Ht6nqsFc/WSIVSRXjJUCw7VS/K0YJ5eMkwLDtNLhmvB4XrJCC04Qp800kxRWGs/cB0bYMZavC11lZ3phK5fGWkxeuyyU8cVrgZGCMa2OcUltPnM6C/z+tGyrP+tGf2lNgcNiN0jTd/1K99PnTE0M69C9bBL3PyoNHwcWb0YeyNCHyeWOBkKEa7/cj41ONVxg1j4dxmXAg86xcAPCaCvxZly44fYRm36jPZSGGTOPiBOm3XcAPG7y/PwGaAMrhwSyeWqWjU6f/Otelr5UNv7gayoVWRxRa3Utl7ckF+nBRoT44mWRSRJAqyd/jZPYpsNoUQ9Kz/lveJf0O55BOYc82NjFoyR6lc90JC/w99WcWFpIrAXgD4GkG2LFQsQ3YRVnt3Kxhu7Ar3tIPXoX9vhgLAj7NBeAuEu9v8j/nFZRW+b0tMINCeIok2Op+rqUN1/atH7Rp3oidagmAqz5uI6vYFqtFydj5VzYBO3UdwMz/3GhJJj6LMPFPrVnZ6Hr2OVDx+vH5azLxP7f5bzSbvtN7zDImHkCVn3AO3DLkN536c2Ld2LhPdN+n4ZKMIVFI9j68x2y/gPWeJ3O62dxHNahqr3iPsQ62mP+NsuJHCv1/c71EZCZ/Xi9N8brEf2VG3CjDn0ovbYUXvlVfHdZbH5sdHnqiMS47uCsLFi5cvFtUAVMtDEpd0b8lBDkRlNA7wRNy0wlf2813Ej0pCf64045YN/4IGNfkc6RvKDLXjQTr8jrfLBn/EAoBZplg9+jwdD8aBRPtC4UnxSLx+Usasmz2LiwdQs/upB9tpseRN0Gm8WiHNVt5TvymQSBTJWHrGZy8HpKafH3kbkdm95P99y8EVqT99yxLxU7eNMfdDPNyOBFAIV0T8QItlqc1qxdXfN2VFrx6+W/vRYch1vczk1Z3aLvhERiwiZ2Y3VCKoZFNfGmHroQWh7+LYuI8VLmJIZxFfVO6BljWbRudBI/N2yCrfNs6lGPSNulA2OdeQpPebHKlz3EUfLuUFXYwRSTxt1zrBUA5Adcp2yysMcB8Wu9AOj4pYMILzEkx6ipy2pIypKyxst9cKFl3cZpYkF7vhh5YfDOVnEsdlL5fGtFQ49UUhpffQ94ZtY2VCXOkAPDikI5h7eniW9Vvhw54/S3/xEpM47xqcidf4/yymnLHdCOMeq8acM55gRcO26kf//CrimjdZzLHXq3DmaPW2CwZp00BVPx/4PXbqYtywNLBxlNLKouwLim2Vd8ggAczSk+7vdy+CKoAFuEWKfjjJvqU6vf4uQr0SIuFlVQEeNNIRK5+OVQC6uftuW0k0cHn6ibkKCO8JSumJFQ+ziraWyJ/JthasnGCN1jP4I2gcQIPhwrMOuXqQ/hEex6r1cwel6wAtTyYCbUFy0D1t2iOCsLiPZg1AAEizt0+7cpV2miUn03urf45y66OE+HA7f/7mn6pdU1rcwz/Rkdli7rX4pJBlroSGAFQh8Fo2FeZmJamTGn8RmBOFNqIjrE0oUr1wvFl9hGAVG4g0OuVvR6T/iqeqHNiqdMgF2KZUSS0YRjlnkhH0Ncc9royNTCoBEYB1h6dXGQCQEjBtKzzDKT0L5wLptTVlRx5MzjxzVdUSO9m+rzNLr9BgiAOsPljuI0BBaDDGA9VgT/h7Kb5tCdUzWb3bpS53Q+Xse264VP6W/h6wPHOFIR/F8HVVE7bGWrBK9+KmgHmgeFywVGzYTZHNN+W0EnW9T9fqj3Bg3kl/cpH+f35avNkftDrU1f7sj0FxK36/FMSMW4mPW5SCrqmSeVoq/XE4U/wi9j20H9CAmF3Q7QjrWicvvOs6J6zxVR9ic24k4sN0mh+duLHy9O1LxWjxxEOvi7RFWols2yC4LF8DgpwjmGLsV2m95/mK3cuZEQjLfsukSNs+jf5CQ4bKJB+hzid3M9a9IYdu/YSASY0JgDO3ee4nlWF5Tq5e27+2WrViqx0VTeZcR1htE/AoWOY1MFK81I6kPRMj3xCrUJD66An4BNHMDt3AKDPn0TnyTkX87teHOIxrsUlDbsMwZxHlGWGj7yQAv/9jJFk2d0JVD+PX2FFOhagrTZeQ8cPKlWqBDuSzxGkeQK243g3zA/qSdo8pQO26wX4FOOguVvhyO95NYnSHNSwLtiNeKOaeNKg4jmOri8uTF0HHrU2D2qfSJvYv4bzIgIo5PmndtOce8O/B2Fwb3gYzyLqd9Zrn0hAb/XydepxLMhQM1cZ4O8OGmffuQ6rkP0F6evVLKE4gFYhcw3xzayy/gxzMwefDEkQYe21eb3aTNbpbCSJlcOKqIgmEwKZ+pVSD9j/+Y0o/wxfifdxm1PYaeB9YlmVWwm31lonb2Lo/0ud4WfBfUczjScS5RFBzzexVaEn+l7/QV+BnNC0WuAiJNafW4RNSIGqFwSHgQKJkLcsSOs1b2MRXzcHwpMPxHlF/6KvOUqCzjr1Xm+Sq8FQPCYSlHsyrVAqwttMnKQ+GoEQ7TzvNGHSILRvME5fwmTP9FnXoDtTyanvu/SBEACLiu77gl6aAFlRiS9sp5sSV5NuVMXcO3cJ/gc8GZeS7soPKyxzAi4vLeVHkiXnZORESJFCYvqPHXKef4xucpQ2Upuu0Py0j6Lyp9FZ+9USrBM4gQziCof6qUleqjXiG4DiNVgttmfPwuRH7z47Ugvt2uaH/jY75ZVuz2Rr3pG6ceg4yv4HDyDAsN9NOnu+b7JrtV17YW72jCB+cUEj74ks55z6ZJbkyYtKqA1M+yiHaU4gk2frL1lLOTFTWkjuHk2SFMRDSBH9k8lVFyMeiT/Kgj6sCgJxSaGeM3MnTw2TwgU2oJ8Egfl8AoRwmb/zK2lOq7O/YuvrIp8/QeJvU320Xsa5v+EJ7n/xA68nnEJeHljMOFllZfuZx6dInccjhN6cnZ6Tt/Q7n9Rhm1goHDtGTI9HiSwnCm1QovJFqtxq0cNhbk6oOkGFdfVJ7sJ/c+DbUxahf/eYu3eZJW9ZyRmc4QI7pJ2GVM47AWOKA9s9fOwT7RIdrV31i7GokT5Cz693iqwLiJszYS7lcPyKdiCLTSgQYoPBAfk0aeWMXBG36+mhDJ6vGIrg97AfOp7S2rvmiWlJse6KYg+2wCcHIjnUEN2uzGFP7gDcjZ/jjtHDGbUSKDA+35cI/BFheTacjaRoyidgVGgXXCxHjlxPj3KJ6Q+Ij4DP8PaivmuIf48XzYsTHKBsJ2TcpQF8RaczP9Rj6l/dSgzNFvzKN9FPbFMADl5tKwTG6kBWAexPo+s5dqu8y6nq+2Ri8xPnHURLPy24xP8ts8m3YF9ZiEvchZmahlrjTEuUUsK0rZRdNyns3Af1oK+D0cFZsBVzw/IWMHs1sczr/lS512KAQPeeItqdUD7XEQq/dr1sJ44uxSwcgujmzNB+mwm0E9GfEJiIPCRXwk0EGb52/wxP+Ig2q3oW/TVnBqg1WwANYn5sImauIQDqlPpxZXxsOBvlI2K42KOw21Q5x3PTe8Mt/O5ClRZufYU7DgCEZGZO7nWJNjjMMTh5ROD3RAsswtwzpMJq4f+NJH6OjTahfzjzBzoHFnZeH02W11t4TOdHwmnjsk5aA4rIyB62C4gt63ce/b2e/yVL3HLLcbapu4azyAvJPYrwl6oC2f+xIU7S/TMcjLPDN6gxZwGZ/4Aq6KcwCW3Mmg+IBKzIwGUu+yCz64njb3BydNZvwDTxWRWGzwmGPxiS3nwlifqIHCEjYGB3DW2sFptWwYnMpefAh0iEvc8mUWvJCJ2yKATzvRObVCF6OzWjtYr5bF9GGtHQxWyztfpOuozUG1Yia9tViHzUNPFc4YlYgrMoqtOWUxNCBmfZEu9vNuxUrpfOsVhT7l81ctGnAng6LCyrbaH6Bsk8x8LuJN7hNv4hHMv58Yn7L7fOlru0189U1XhppurZH+8rP76Y2p6+tJVVQZOCLnWB0tybABlDGFxYwXQWB1/nSov+EvcNTo7qH+3jo7FervxXO6TD3KvC962/6vUH9WgNZ1lZKe8nGwZU/VXQB1UxiA2jr0fXAJpqOLxvO951dwJYl1/LCoKNbRrgyJdfzPE7+SP7EkBS3n0x//Mc/DZ/JjJjzW8fx6qnqlHyG7TMuPNlkUYcqI8Or4wbNmm1aMJIRO/7FkH1kpDip4iVaB+QuF9DPZHIV1Nh+mA9GtLue6Ma9cP6QztH1iL9SDHNUCQlaGZkFp1HJyHjsO1GyjuC3pQMiEijZWCAqryki6uzgdCXBMXdGHmazDY/fJsDpMlVthJ5gkxqeKy1iNNCtJmlNkUDHlUNl3dxrCVpkZPfInLJ7nXGFZPJeZFs8LTgx1sKFPOkTquj44e04KdTBGTLzCsngeaRS7IK3roOKq/JQALSTu7oMp60B25f2i7HjK7Lk+ZZIGglX0g2tCL8QGzllzPW21ed8ZuJeBrR80bxikH/8OrLG2tQkrIHMf/WQOG6QrqV0BLojzPI0/HXLoVczZ/+lvENTJtEnjtK0seJcpl2Sepa3gOAp2m/mWVoBsmKutQnMQuhF1JuXdvVxU71sPpuTd6LwZ2Ck5EGFMVl7TPWOKM7Z1GYBH/UrnjiDidvFdiLiNbkK+WWvnzg6PIq/pK/JhlkRx4rPPsmyp2Nx2iQKF0j8LEbqhOpXYVNzWXyZTpG07mph+0fog4oTcWz0KvV2A3n4aShQ/LC49zzCeu2PQaV7WhSTewDyWsuBgLZjAUa1I61b8sDFK0I9S0W8y0TJmIl0jHD3GAo2BB5AJ1I7qZpwGHZs4/xXA7nNt9I2a/ZyNqg/ibT29TcQwyoLDxI9c7StzKlfwmw3D6Ls28cchrFpeKfq83Yn4NnbfZky7cn0isBIy4L2/7jKSN2Sw/At+wSz/teHjBlX4Ltd1B9dF1M0RuOrWqn8SzYSpl+/AXEO2Itr+Agn/Sr2oPTosMb1pagmR
*/