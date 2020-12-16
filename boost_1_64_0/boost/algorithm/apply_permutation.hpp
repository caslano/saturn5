/*
  Copyright (c) Alexander Zaitsev <zamazan4ik@gmail.com>, 2017

  Distributed under the Boost Software License, Version 1.0. (See
  accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt)

  See http://www.boost.org/ for latest version.


  Based on https://blogs.msdn.microsoft.com/oldnewthing/20170104-00/?p=95115
*/

/// \file  apply_permutation.hpp
/// \brief Apply permutation to a sequence.
/// \author Alexander Zaitsev

#ifndef BOOST_ALGORITHM_APPLY_PERMUTATION_HPP
#define BOOST_ALGORITHM_APPLY_PERMUTATION_HPP

#include <algorithm>
#include <type_traits>

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost { namespace algorithm
{

/// \fn apply_permutation ( RandomAccessIterator1 item_begin, RandomAccessIterator1 item_end, RandomAccessIterator2 ind_begin )
/// \brief Reorder item sequence with index sequence order
///
/// \param item_begin    The start of the item sequence
/// \param item_end		 One past the end of the item sequence
/// \param ind_begin     The start of the index sequence.
///
/// \note Item sequence size should be equal to index size. Otherwise behavior is undefined.
///       Complexity: O(N).
template<typename RandomAccessIterator1, typename RandomAccessIterator2>
void
apply_permutation(RandomAccessIterator1 item_begin, RandomAccessIterator1 item_end,
                  RandomAccessIterator2 ind_begin, RandomAccessIterator2 ind_end)
{
    typedef typename std::iterator_traits<RandomAccessIterator1>::difference_type Diff;
    typedef typename std::iterator_traits<RandomAccessIterator2>::difference_type Index;
    using std::swap;
    Diff size = std::distance(item_begin, item_end);
    for (Diff i = 0; i < size; i++)
    {
        Diff current = i;
        while (i != ind_begin[current])
        {
            Index next = ind_begin[current];
            swap(item_begin[current], item_begin[next]);
            ind_begin[current] = current;
            current = next;
        }
        ind_begin[current] = current;
    }
}

/// \fn apply_reverse_permutation ( RandomAccessIterator1 item_begin, RandomAccessIterator1 item_end, RandomAccessIterator2 ind_begin )
/// \brief Reorder item sequence with index sequence order
///
/// \param item_begin    The start of the item sequence
/// \param item_end		 One past the end of the item sequence
/// \param ind_begin     The start of the index sequence.
///
/// \note Item sequence size should be equal to index size. Otherwise behavior is undefined.
///       Complexity: O(N).
template<typename RandomAccessIterator1, typename RandomAccessIterator2>
void
apply_reverse_permutation(
        RandomAccessIterator1 item_begin,
        RandomAccessIterator1 item_end,
        RandomAccessIterator2 ind_begin,
        RandomAccessIterator2 ind_end)
{
    typedef typename std::iterator_traits<RandomAccessIterator2>::difference_type Diff;
    using std::swap;
    Diff length = std::distance(item_begin, item_end);
    for (Diff i = 0; i < length; i++)
    {
        while (i != ind_begin[i])
        {
            Diff next = ind_begin[i];
            swap(item_begin[i], item_begin[next]);
            swap(ind_begin[i], ind_begin[next]);
        }
    }
}

/// \fn apply_permutation ( Range1 item_range, Range2 ind_range )
/// \brief Reorder item sequence with index sequence order
///
/// \param item_range    The item sequence
/// \param ind_range     The index sequence
///
/// \note Item sequence size should be equal to index size. Otherwise behavior is undefined.
///       Complexity: O(N).
template<typename Range1, typename Range2>
void
apply_permutation(Range1& item_range, Range2& ind_range)
{
    apply_permutation(boost::begin(item_range), boost::end(item_range),
                      boost::begin(ind_range), boost::end(ind_range));
}

/// \fn apply_reverse_permutation ( Range1 item_range, Range2 ind_range )
/// \brief Reorder item sequence with index sequence order
///
/// \param item_range    The item sequence
/// \param ind_range     The index sequence
///
/// \note Item sequence size should be equal to index size. Otherwise behavior is undefined.
///       Complexity: O(N).
template<typename Range1, typename Range2>
void
apply_reverse_permutation(Range1& item_range, Range2& ind_range)
{
    apply_reverse_permutation(boost::begin(item_range), boost::end(item_range),
                              boost::begin(ind_range), boost::end(ind_range));
}

}}
#endif //BOOST_ALGORITHM_APPLY_PERMUTATION_HPP

/* apply_permutation.hpp
QK6uOt8OhD51VHwIR9P0JfpeSgDL6tCyeQHPk6+rTrgU1f8GuIKPy2B4t+Bb876ugPatGv0opUzbx+WT+dg3mIzp9n6pLUPiV3hSwbifhap4FvxOtmXu6TOwh4qxF++MSjUy7ls4xf2rWrRpZhL5w50QiJyHmIynOSZQtHGGD6Y7fNtk3gYMooRAqNpNywYaUGm77E5v6zlqG68yLEe4waIV0+uaTi/T1qDmwbzV2HPYypsBR7xjXQWE0BU+99tASHdUNKIVAEvGfy/CRB6NA75wYizGyhijaYOAy2+uo+0Tdxv6knoqD/aCipbxFy1a6VEjt7ng4FiNLa8s3adF4fU42phVWbq/clRMLfpkegNtfb+P+2u+6694/ASQKm2f9fwTzMXCCTNauPLEppu8zcJUUPsyMCQXhrt+R+MWYzrnLcUvMhAwtptLDYeu4QfFCzxgqhIsD9K0JBBnlkN37oaDYExsut4Pr+RI2hPUy6Zs98Mac4wS2pc2J0WNlOcUN510biRjewILg3rKIdlNYyEkX/7+bsPPZ/lJ2j5Ve5sSwqbRAxX7cSSwCLu2xmrVWE2g6K3ZOg4Apt3fE6J1KOcBsCJVoVqQXSO6kg3cThxrXL6NPCITfhw5z4Mb7RQ9N82yZiRCKFQi48mxMflsOGbfbt78/gTftLdVbR+VYCYqReK2nvrEpt2xooY5GYiAW9JqiDJIjrRc7s/TMvYT1ICgNiab1DxPJck2G8yJsRtuUXJgFCAndoLLDt5OVNnGTavWNiBe/xVWvLBGjdUGir6dHWYX1+w5F1KM8p5KVb601bljsOsFYY+CtJg2u9L84o1ZuH8VP9FdHI8ubeWd+d3TmPdXs3fm/zgKbvkz97tVTGOX9LLWv9NamEfyZVk74BFB35JKld7GpDs1Tro6ky75/5XV7WKDlBex4L1xt1x7MPfCUDPINAgyzW86CSzsYyHTc6Xp144CmR7/LkQxQqZ5ZHypgkZOsvhRQMvIAb0+Ci2lgEmvKgyLPwK9Vt8Lev0cEwiS7VHJBJqd+oHzJAe0XnuaTgHMgwRzugOpBdFFQITohYimO4qfRWoSy/jU0K1ZCeXDMDqI6rL0l3TQZvMcjwyXHE5V35RIFpklbp9xBy3JWJyGX9fYuCwq3Aq16EvPHbOYNUprGAdwRhNpRpNp0oRBIcXJ0h4vn5fJBtav5FN5PfrqT8ECalMSWl0Ld2Mu09vjlofX799M/tWu2NfxoUvaMXLev1n/NQpeQByo3WP+hVtmwWoBXqE/YiYwSGUm8OJpcpR4Ck6exyD9y+KaSvUifGIKv2bj9RR5zUJPvvhzdPAnYM2cgVbbZc8QnfujGX60qbNGFlqpRBjH6Y9+yIRxBDTuWlxL5UDJu+DHNO5/5IK404iNWZyRmJv7tK9Dq2P6FDpxNaaMHmwKhssKivXyXRha4RRqo25EjHX6H5vBZMlf9OWGjPTPIiOdHiRjlT9BQvq2vgAy7cYoD72nuUEhn6d7OgDyAi/DHnhb5grDI8SZQWH1f2Nb5ssjqoc1EYcBTROW94UkAp6Gbp/qZd8PavicbHqZhRf0iUc/Uso0CKiaRgqqv7dEtdtJeiv/kLOL2pHCgl89A/gZwbDtVB4PViaRiTHQxZgPKIxSo8dXLkKPf4szFnZrIsofE+m04V/h8rt4gnBQ4Z/HHWXyz4xrW/HPXeCfYJ8PuuLskzRYWvPOQPhM5qgvMXsImhx0GOobnNIMYTGY6PlKKGZM9vk82e8TLvqetF74XHDRhi3WZN+buKh/YWxuL6y/DLY3hQQdrfnnvLvQkH/DFADgoMGt5p5mTvcDgFYce9N0P82c7ock8nRP5romt74=
*/