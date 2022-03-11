//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_SET_INTERSECTION_HPP
#define BOOST_COMPUTE_ALGORITHM_SET_INTERSECTION_HPP

#include <iterator>

#include <boost/static_assert.hpp>

#include <boost/compute/algorithm/detail/compact.hpp>
#include <boost/compute/algorithm/detail/balanced_path.hpp>
#include <boost/compute/algorithm/exclusive_scan.hpp>
#include <boost/compute/algorithm/fill_n.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

///
/// \brief Serial set intersection kernel class
///
/// Subclass of meta_kernel to perform serial set intersection after tiling
///
class serial_set_intersection_kernel : meta_kernel
{
public:
    unsigned int tile_size;

    serial_set_intersection_kernel() : meta_kernel("set_intersection")
    {
        tile_size = 4;
    }

    template<class InputIterator1, class InputIterator2,
             class InputIterator3, class InputIterator4,
             class OutputIterator1, class OutputIterator2>
    void set_range(InputIterator1 first1,
                    InputIterator2 first2,
                    InputIterator3 tile_first1,
                    InputIterator3 tile_last1,
                    InputIterator4 tile_first2,
                    OutputIterator1 result,
                    OutputIterator2 counts)
    {
        m_count = iterator_range_size(tile_first1, tile_last1) - 1;

        *this <<
        "uint i = get_global_id(0);\n" <<
        "uint start1 = " << tile_first1[expr<uint_>("i")] << ";\n" <<
        "uint end1 = " << tile_first1[expr<uint_>("i+1")] << ";\n" <<
        "uint start2 = " << tile_first2[expr<uint_>("i")] << ";\n" <<
        "uint end2 = " << tile_first2[expr<uint_>("i+1")] << ";\n" <<
        "uint index = i*" << tile_size << ";\n" <<
        "uint count = 0;\n" <<
        "while(start1<end1 && start2<end2)\n" <<
        "{\n" <<
        "   if(" << first1[expr<uint_>("start1")] << " == " <<
                    first2[expr<uint_>("start2")] << ")\n" <<
        "   {\n" <<
                result[expr<uint_>("index")] <<
                    " = " << first1[expr<uint_>("start1")] << ";\n" <<
        "       index++; count++;\n" <<
        "       start1++; start2++;\n" <<
        "   }\n" <<
        "   else if(" << first1[expr<uint_>("start1")] << " < " <<
                        first2[expr<uint_>("start2")] << ")\n" <<
        "       start1++;\n" <<
        "   else start2++;\n" <<
        "}\n" <<
        counts[expr<uint_>("i")] << " = count;\n";
    }

    event exec(command_queue &queue)
    {
        if(m_count == 0) {
            return event();
        }

        return exec_1d(queue, 0, m_count);
    }

private:
    size_t m_count;
};

} //end detail namespace

///
/// \brief Set intersection algorithm
///
/// Finds the intersection of the sorted range [first1, last1) with the sorted
/// range [first2, last2) and stores it in range starting at result
/// \return Iterator pointing to end of intersection
///
/// \param first1 Iterator pointing to start of first set
/// \param last1 Iterator pointing to end of first set
/// \param first2 Iterator pointing to start of second set
/// \param last2 Iterator pointing to end of second set
/// \param result Iterator pointing to start of range in which the intersection
/// will be stored
/// \param queue Queue on which to execute
///
/// Space complexity:
/// \Omega(2(distance(\p first1, \p last1) + distance(\p first2, \p last2)))
template<class InputIterator1, class InputIterator2, class OutputIterator>
inline OutputIterator set_intersection(InputIterator1 first1,
                                       InputIterator1 last1,
                                       InputIterator2 first2,
                                       InputIterator2 last2,
                                       OutputIterator result,
                                       command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator1>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator2>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);

    typedef typename std::iterator_traits<InputIterator1>::value_type value_type;

    int tile_size = 1024;

    int count1 = detail::iterator_range_size(first1, last1);
    int count2 = detail::iterator_range_size(first2, last2);

    vector<uint_> tile_a((count1+count2+tile_size-1)/tile_size+1, queue.get_context());
    vector<uint_> tile_b((count1+count2+tile_size-1)/tile_size+1, queue.get_context());

    // Tile the sets
    detail::balanced_path_kernel tiling_kernel;
    tiling_kernel.tile_size = tile_size;
    tiling_kernel.set_range(first1, last1, first2, last2,
                            tile_a.begin()+1, tile_b.begin()+1);
    fill_n(tile_a.begin(), 1, 0, queue);
    fill_n(tile_b.begin(), 1, 0, queue);
    tiling_kernel.exec(queue);

    fill_n(tile_a.end()-1, 1, count1, queue);
    fill_n(tile_b.end()-1, 1, count2, queue);

    vector<value_type> temp_result(count1+count2, queue.get_context());
    vector<uint_> counts((count1+count2+tile_size-1)/tile_size + 1, queue.get_context());
    fill_n(counts.end()-1, 1, 0, queue);

    // Find individual intersections
    detail::serial_set_intersection_kernel intersection_kernel;
    intersection_kernel.tile_size = tile_size;
    intersection_kernel.set_range(first1, first2, tile_a.begin(), tile_a.end(),
                                  tile_b.begin(), temp_result.begin(), counts.begin());

    intersection_kernel.exec(queue);

    exclusive_scan(counts.begin(), counts.end(), counts.begin(), queue);

    // Compact the results
    detail::compact_kernel compact_kernel;
    compact_kernel.tile_size = tile_size;
    compact_kernel.set_range(temp_result.begin(), counts.begin(), counts.end(), result);

    compact_kernel.exec(queue);

    return result + (counts.end() - 1).read(queue);
}

} //end compute namespace
} //end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_SET_INTERSECTION_HPP

/* set_intersection.hpp
KnMlVV2WVA7f7OdFr7yNufsJnCrhKP/AKNSZzrBTGlyCM3A/aLZleRZN0D2f0xAz2NBpRgU23vRJwwX/PZU66M+Y7NfNXfVs8791l6sy6ha6KXfdKCUBJCxsRKYJHBRW7CJvP82fZ7dqNQVWryRByY4rkKo3j2GPWP4CGpzPAnwUdcEy3BV3QVgAFu+NlscAfYlTBzjm2DUCkpCNATieUBpv2oodyUMKvO9k+fSm7GaYbUtrmSwUlh3iB0OHHjTzrNmw2UtXrZXDsz8OdXQddHdSy9tjJN7ksYImU2XBEdpYbms4lzdv9De8iZ8752I9hLQrMy5sCasiOS0d7I4rlmXqsq8BTdiGtcurXLadXLLfwKV5BeGbNe9+C+PYjf+k0/CCX7/5wme7q2L8hd8cSearVBu2t0OcBSFrn1iTpRgKiCClqDVn+3XF+8s3RPvPJQ19rV5NLJ4MLOGZAiohxVgdQl3rJCnaZugin5vRpPT2cDNBxyXRu8hf5eiDw7h+Xlsj2wqG8g0QH+aq3IzhdK0RRsXjNM/LQHi+H3uSZz7oxQ+uQ6v918CZsSw6RC2KBRvJdQnujDy/ZYrl+7hxQoB4HMunvbFqUZdKaAB+O0P++CssV2U8i3VD+o/4NA4nYdbXod88rt34tk7Pd508nq9gqFqHe1GUqx5xxvyuxmuxzZ6gBJF9YWHbV+KFtLYPiuQht8Ylc7vqBSdPPFB5WE9Xu4x4kPMQerw2BL+qr+zqkEQePqH2DL6WXcYcKjVt4G7OSa8S4VWAXKjLtlu7f89pJAaGRC+MgrwKLhYQUpomBzmNn09/E+YunbaxyMZuXDAG6vXZoiZ2ZkuFbx0XfwdGeJYgr9DZ36qZ134vHGxLztIHfbKVKZkwtUn4pmlLj/nlWZLe3XMlVntoQSx5eA96gHthx5BgJ6qiOn7z9EPdVL8U7MLLOzzLMZK+JfojD/mUbczmcv2/h1LaxHiB3WC4yeB0KcnS49HR6wg+mhEHjNPVrk3XgAU3nKcXIkdeInrl/DrVx+11U7lAWLlqNWHJuTNhiWgq5Weng7evU5HcsS75Gx2qNPHjT2vZ/luEkh2ulTUfCZA4ALOf6vihMsUdQC+2VIYxfCGKppfpmafsJ4fOZ1aDP/u/GNpEDXb/OnknUbWmmxjih1MaoL+A1k+vo2zXMpWbpnLq4FnBiLhWo+aeyWNw94EzVJN2PsXNjeU8TcVZNXO/yLyKm3XixOkjnoC+PT47IbOclCNyK2+mrdVK73/3Z9IO4lab2M/R1/2o4+X3asyjY5kolMbjB59RW3N+0PUWHd5sqPW1RkBdj1/GP2Sg9RBgrJYC55pg4FxbbFXAe/Yq5ZWraUfDmXnP9YEa4M5n0Zr/ibh66EWgT4yTno99ANxzEVF/Yp4pIvqOjbj5CX1pulJj3uZaWDwQR7SAoKlFHJJfW+hvBzQMHRpjfnbYySypz1/5XfgrtVVZ8BoxSi7AomtJYfH2a0iA8is3qYh6pHmIML/O8C8BC1t5DGkJ/DK+dpghxuvjqwmGd15+7x45U9xnW6Kf4qlV5jje09Si/H+iN/6riWund4+2iFg5+GOsLo/wxXIPP7w5TQUhnkCVZeoWDj+irJzU6aEtV0VnQeYPlURW0SbZP1SNh9cvjpW6PnT4Ccw4Q2MbO65eHGN3fQj4KmAUGQdXvPq9qgLrRUk1gLw27qdUYBI6Gykvut2Hfr9w7Qw4TJ8hMSgehBa6f1yEa4YXbd9GGt8s3A36k1d5WuMiEfbkul3qht86yGx9ESB6yOhqpdjQwroutLQTLLZ7iw1RhiBaumFNcYNpiTclRZnbAWgHplz7MClwDT20DsTVLREFV70Bgn3mEZ2yJ6rHGx7XPoOjeAIs13Yua6A1/czDf+Z66pr4VV7qKdz7TYT9rTRKx1UqtIPLxIsoy1zsE2vI0g3y/rUomrhbNLwODR6Kkxmqlcevulu9hyOZHF0v4qYkE6OMw7zccg9sv1dkkd7t3yQv5AVVla/LpiiZ272/nkZxG78aFg6C3OYGB5HfsQgGYZpsJqhLWBx6zqWpsspzStscuNQVRXb+kYzOxjSllIY7MMHKdc2P1i7nd19RjQi2gvgjzSNeJ74F2pt3zq7oI3LzcRCx3XPO4PC1nta/OAgx1xjLSSHn5h4nN5brYLjVBUZS2HYjyBFj/N8HMZ3BpgO1xI+OrpGvFgMMVxnwJkhdD75v/+53zS7VCmFgrrEiNhDIAv33nQUkfj8HIeSKpOOB6pCU1ucoGIIiZm8MK3NPBPBClVzlZvaXEo8xzq89tnp+/z9FwEPJB4AAgENLAQCA/3/MONEC53/92Pm/gM2Gfi7TTxc4l/tRG7/BOMUCx68/9r77U/6699dtxWejmfswuBPBTYR9qb/O/ShBY3F/nZNUAbsV/nb1Z+O/wCkDp4JxKgRO2wHEuXeA5gR+b+bED2D9X8C+Bf1FAyhfnw+gNrt6gM7bAkHjCDROQKMMGv8wjTxBo30EO//dZMZGM2y4gH2eYacI2OURVI5vI9j+v8D5JYLa+VHGyRU47gPJjzdsG9h7B+p8OW0W6hicJwfit1MGUs5fZRoRgsbqgRR7JuyugWz+E7jXBuq8ZgvYlpHs/MuAtfa6wzPNevdHUtlHR1LZ4yOp7E9H0j3AjEhaa8+PpHuu1Ei651oeSXu/GZF4t5rFlSz4rD9IYzME7L2DSL/bIN0migROLNP32mLGvj6Iyv820w8XOJvB2cE4UwVOKTjljLNC4LSPwnMAUZpzVOA8EKXL7vGDGfsCw4YZsNY9zwJBLxXxpkVRW/o2Cs9ERFFb2g1/9t8/FrQuQes6tOoNxvsjg/H+yGC8PzK4yc370MCtZs1HB5PmU7AvDKa29SpsHOw82BTYjME6T5MFH3+Bc2KwrrMUgXPX/cRpBtvwfrb+FbgDwBlyP1v/Zpk5L93P1r8Cdsn9eP6D6ccLnL+Y/kIB22YIxe89ROtnCZzRQ9j5l4CdDf35TN9vm9zWpxswSu+bIZSXzUOoff40hNrn4SHUPv+A30ZD2f6PoBk5FL/DNJTNfwLneXBegZ0zVLcdp+1mbjqLLUzAnhyKfc+hWI8zPwkCt80wtv8pYEcMwzOfw/AcOq6fG8bWP4LGcnC+G6bz6LVDrvMpBox9jhtGOfgDsZ2Fn8vDqM5v4Pre4YTrNlz7XyhoTxzOzn8F7CLopzH9coGTx/QDsm+j/RswSu8GYqgzgnLRZAS1/9YjKBedR1AuYkew9i9ovsmwuQJ24wic08D/z/B/dIRuJxWCRp1o0mgYTRp3Rus2HfajcG4TrWOdLmCfZdhlAnYZw+YJ2F0MWylgr6GsziN1mwnYKdwvjcRamnHiBM7YkTqmFAH7BsNmCthVDFsiYH9lWK9dZmwlw4YL2A4PsPsfARvzAOVu3APs/kfgzGP6uQL2G+hvZPoVAuc40w/MEe6rHmT7nwK214M4T3hQxzJX4DzK9DcK2GSGLRawqxjW4yczdh/DhgnYiwybIGCbjmLrHwEbyrBZAnbsKMrzpFFs/1fgvA7Ou4zjt9vM2QbOT4wzSuBcGUXj/T+MkyxwWo8mP4GjNSdT4Iweze5/BezLDOu7x4xdgVjWsliiBM5Jpj9DwNaNwdlmDM01vjF6rllh4Ko4rN91tPdxYK13mN/4oZH92npv4kPbtdJV561huXSeUHyLvhXTQMQ0LKbqOeDoGJz/xdA9VgKuE2OqngeqmNzAScnVcWXbG5GOK9N22XM7xaX2JPIR14xcx3F9gLg+gb/lMVXP/75FXN/H0J5EdgzeR2I49bHeQXt1ZyO7Dv+9Ft+9+v3yyXspnsC9juO5FKPPbuw6D1FcDWGvs+8VPvgh1v/31ly34ew6Znejas+Zcax9fNirf+MrDzEX1RDzMywGn5+F9eRDFP8SlOeLhyiP3zzE9r8EjTxoFECjCBolTCNZ0GgQy+Y/AdspFnv7sfjdgVjdnyoE7lRwZ8bqvh6yz8xZw2JLELAHoX+M6S8UOLXHsPW/gA1i2HIBO4lh/fKEuWIM9sLGUE4Xj6E6/GqMrsOhgsYBaPwGjdNjdL2kCFzPh1n9C9j7HsY7kQ+z9Y/Amcr0A38RznSg/ynTjxU4ueDkM84CgVNrLHHqjaV83TFW5ytL4PYby9b/Bmw4u/60UWM7jo+FAfv1WJi4n8aV0P2OxxXr+mnEO20s9srH0hzx+tiq7+cpzez95nKsRA5WQ3MrNPdC87ex+P1qaHvGEb5FHLv/FXwMiGP3vwfM2McYdpQBqz7We9Tn2jT2sOZr6+w/6QCd/b8fV3X++JhdW/1q2QHKe8qB6nnnfi7eXd1PCfz8cIufnQ78uOeTnwrBz8y21f1E55Of07f4ueDAz1T4ic+v2Y96ZmJqu8bVnpnYCD9ejzh+ZuKuR/R4dBR+cgx+VHn+276xOL/6HdTza9BBvP93sLpuTc/RRXalvlXT9y1DzN9fCaEYn0K5X3iE+sOcR/A8Pit3/kFzG94Eje3Q2P0IO/89ZOaeBfcyuLXHae4oA9fq7xmCfuA40g8ZR/r9x1H5osdRfx83jvr7lHHU3xcBv2QcO/8WfOwcx9Y/h83Y09AvZ/oRAqfFeOK0Ha850wXOkPE6plUGrJXHSkHvacQwbTzlce54yuN74ymPaeMpj9+Ox/uJwBcCfwr48+N1uwosEOboeIy98brciQKnDzgD48nvsHjdnpYZuAqjfq/D5VezfiL0p0P/9Xgq18J4ysNn8ZSH9Hi6X/ghHvcL8XSGeSSe3l8piad3oq7E0ztRLhPonSjPCZS/3rADJuiyTzHEZp1LZQvxPzaB4n96AsU/YwL+WwoTKP7UCRT/8gkUfwbiOAZeCXiXJui8Vgo+m08krv9EXZbQI+ayqPfCUgwYpXs/dB+YiPPkiThPnojz5Ik4T56I8+SJOE+eiPPkiVQX2ydSXeRNpLo4jjhVe/D6zRzD/xF2NtBRVFkef0maDyOjHQjQMsggAjIQWQZZQGQx3yQYICYtQWRZOt2VdIXqrqaqOiRs1IwTHceJI8fJYtZhEREVGQ6DDCJmGEROzGQcPyKb42EZZBAU+RIxIgKjuP9X71XXS0iqOOd3qt579953332f1dUdBgSZDzcGmQ83B5kPk4LMhzuDzIe5Qf53YYLMh2CQ+bAyyHx4OMh8eDLIfPhdkI2HV4Is/gd4PR8H7RjWufjmDTEdX4j5Nj7EfJsWsufgdhcb/85thLmNWMju9wsOuta64j/sbH8Dt7+Z29/FfWwNsfgdCLH4HeVy1l7+t4duNOXM3x9wew2H7d/Uv3uYf7/x8LV7Kq33OonZS5fszxmsK613jMR/w8PllnO5qCS036Ftlq/0701U/JztxdYZh16nfNz9b2w8L137d2n8H/Nzwce9t+FtSfj8+2N3X+jZ5LYG+wxk+bKH+3JSuvYMZPlylPvybi++iPZf7MX+yCPM/vUVfdvPPMI/FznibL/m0Wvt13H7kx3sb+D2G3uxT3XvrbBjefiI85hdJcgO/Iez7DpBdpqL7D5BdrmL7KkKNl4u8Ov3/Nq/0p7bjS42ZlSyeN1dyffKSjb3HhBsdDjYoP/6Ol8eW8fOlw2VQvuPOvvzciVrw45K4f2/i85nvA1fCDpNLjppYaZzU9jWaXfRyQ4Lz78usqogO+ETZ9mnBVm/i+xrYf47EsHvehedY4L9nS6yQ2UWl5tlNh4myfZad9RB1/qsNfOYs30/t7+U26+S2XirkfnzvMzW+iaZ7ZUbZbZXbpfZXrlXZu3/nF+/lIXP/13qHlklvP9zkO1rPH/zZzae765ibZhXxf/vjCrmS12VPWc8x519eVHwpcBFtl2QNVxkz3Dfvua+/bPK7r8NLrqTVgjrn4vsAkF24KfOstoK/puTFcLnny46Lwj2wy6ybYJsk4vsZUF2n4vseIX5PVkR3n+56CxThM8/P3OW/bUgW+Qiu437skvwpcZF5/+4zieCzlYXnfSI7dNRF9kZEf4eNmLbH3TCWWcF16mO8GfICH+GjNhzJ9PFxp8EHxtcZI/w+k7w+r6K2PNhu4vuiCj/jm9U6H8XnQKuUyzojP7cWaeW6zQIOn4XnRau83aUv/+IsjieiwrvP1xsDFeZjZ+odr3vuugUcR2/yupdqtrxJCeddX+lCu+/XWR38Xr28nrahHrCLrpfc92rXLd/THj+d9G9MyaMfxfZihh/jo4J4/+Us06TYD/TRfYtQVZxkf1UkG12kR2wkj+vrrT9bnXRmb3Stn/JRVYWZMeedpZtFGSLXWT/IMjWucgeXsn25M/49dxK4f23i+5gTfj+h4vsvwqy3jPO52Trd6lvql6v+Ptbcz6csX/f2nCGPacU9bBn1RnWWP/FtO7v0Ws0doaq59dfC+Xi72nN97ln7Pfn1Kf7V5p/EjPxW9nfI235k36W+bOnD39e5f68wet7S+v+/vyvGjvTfSjkW5/vxM46x/cKt52s89+g6czGKJ21MUNntmfp7LxYoLPz4iKdnRdDOvtsRdPZZyv1Ovts5Tc66zfqwwUXH17XmQ9vch/e4z78nftwivvwLfehn8F8GGIwH24xmA//YjAf/s1gPtxjsLFpGML5/wtnX543mC+vGMyX1w17XNe76B7i9R0zhO+/OOhQGfr5U/o5Z7v94vx7jXH+f6jE+f8vE+ffnefXyfw6g18z+bWQX0v49YE48/NhbveX3O5TcbutiotPe7huK9c9wH06Grf3x80uNq6rtvvlrIOs9XnT7C9d3kNU8/cQ1fw9RDV/D1HN30NU898DCPWGXGzuFGTXuMh+wus/xev/ttqO5x4X3dGrhPXfRTZnFavnnlX2OBt73uVduWB/sYvsRm5/i2C/wUXnPa5zcBVr+/FVdtt3u+gOq2G6o2qYbkaN8Pmfi+59NXa7pnzlLPsIr+eJGrtdS110Xuc6+wWdNS46XYJPrS6yQ2v55wG1tv3zLjr5tcL+3+X+nN35Q/fn7G+Ps72ot+fwpy56vbsvdi/vqT/02+7lB3uUey71rR+67PXGL3cv7+ihP/1q9/J9Pcon3pLWp/3scWneReP6LqfX307qXt7eo3zx7WmJmDZlpHn7sjNvcppjHAZOcfbj1BRn/Sd/5qw/YZpz+bDpaY5xbulR3vPzGH2Gs33lTudybZaz/e/vsuP817v6jvPC2X3X84+iNO/XRc5+DFec41CmsvKbcL1Vtf0Q++MH5A+MpXX7+yZdSP/wg/N3EDZ9Y38HYec37JzX+k3vn79b9e7sOd415t+zK9O8L6zsPU5pRpp3qNH3eNqCsm28/E8RdjUuDjf3x3pcjRuYT9sf9XnF9tDz2/O1zuOU1Nk+3VjXe/zodf+Ddtn7D/Yud/zhNO/nD/dd3x31ad4Z9c79PflXzuOOPOms37DGub2+p23fxwr3PeuZ+Zw9vr9Zb98PeK67/Z79/fs/Otfv3+3s/3/t7lv/+vfSvKPec9aPfNK9vOf6qxx3nk//c9K5/Oopl/KvnMs/uOxcPu+qc/mtP/Qdn7YfD/YeA2J5z34dN2qwo/3n/mOwY3w7gqw8o/naufbKM6xsE7/6rgxn/4ckrmcv2/O0qBfdiz10/Vw31ENX6UU3p3kwOxsLZ4v6K87nkC387LJDOLtsddCh//ZN83n9d7H6Pf18ifLO/j6ydfMQMvvq8ETeksE+8unzQ0gsyZY7NNpHfC8OIZu+s+VSb/ORog1DSCex5aYhr27TELJOkCtGXi7kLnhsuSbkrUO9iwW5ugkoh1yGUK//pz7SCXtrBLlG5M2E3GJB7jvkEfgXEtq2e5KPDHplCDkv+Lcfec2wd1jwZXCGjzTAl6OCnIK8xyGXIcRlO/I6EZezgm478pqg29s/Be3ZgXa2gk5wAlwA/ZE/AkwEc8BG5C3BtWgCs7scbTF+yu4zb2PX5LE+MgyMATPBPLAEVIFq8ATYCLaDvaAdHAVdwDMOfQcmg1xQAspBNVgDNoI9oANcAOdu9ZHU8T6SDkaDDJAJFoAloALUgUawAewAbaATHAGnwRUwAnaOwt4NuHrA+TEoB4dx3w52gQ2gEVSDcrD2FsQd1IEwWAb8YB6YCcaCYYCAEshng+mAoL4TGKMdsAAdLOLTvx/sBi+BZtAIHgHVoAIsAvlgKhgPRoBUcBU2z4EjoAO0gO1gI5h4K+uHRvR3DdiQwdINXpSDXeAdcAJcBJ40HxkMRuN+Aq7TQD5YDjTQAJ4FO0Er+AicAJdAKubfaDAFZIJ02OhP7d4IGXAQvAP2gC2gGTwGFLAUFIFMMA1MAIMBAV03oG/AQdAKtoNmUA+qgB/kg+kgA4wEN4BkcOJH8BG0gd1gC1gLHgJVYDGYB2aBDDAaDAJXBiGm4Bj4CLSBMNqyFdcm8DhQwAIwHYwHw0AquHA91iHQAVrBdtAE6sAyUACmgpEgFVxKhTw4APaDHWATeBo8BuqAApaAfDAdTAAjQCr47jrEBxwA+8Eu8BJoBBpYDkpALpgGxgIfSAXfDYQu6ATtYAdYD54G9SAKloJ8MBOMBgNB1wDEFhwA+8BmUA9iYDHIBJPBGDAYJIMurNlHwWLEsQDMBG23o1/BqDQ2LtOxbozha8csjNVRYDEfs29gi8HeU38dGAg8YGgSqX8B1xaA/aS+P/24FewGA8DzgOoOwrq0EevUbvAuOAyykTcNjAFPIH2Fr2PPIr0dtIJD4Bxf07SfoA/AHJABRoD+4OIojBPwPtgLNoE1oA6EwRKQDaaD8WAQIKDrZvgBOsB+sBWsBQ1gNagAxWAOmArGAh/oDy6NRPxBJ2gDLWAbWA/WAA0sBUUgE4wFXpAMTv8Y9YJ2sAtsBk3gEaCB5WABmAPGgEHg3Aj0HXgf7AU7QDNoBNWgCiwHJSADjASDAAEXboKvoAO0gJfAGlAHFLAEzALjQTpIBl0+1AcOgHawC2wCTaABRMEysADMBhlgJEgFl4b7yEnwEdgHdoKN4GnwCFDAIpALpoIJYCTwgK5h8BUcAu+APWAbWAcawWpQAYrBHDAVjAc+kAouDYU+6AD7wDawHqwBdSAKloMiMAtMAKngSjp8Bp2gHbSABoytteAd7A8tYAtoAg2gAiwGmWAq2Ar59WANeARoYBkoAXPAVDAWDAajIH8DuALbp8Fh0AZ2gnmI/WY=
*/