//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_RANDOM_FILL_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_RANDOM_FILL_HPP

#include <iterator>

#include <boost/compute/command_queue.hpp>
#include <boost/compute/random/default_random_engine.hpp>
#include <boost/compute/random/uniform_real_distribution.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class OutputIterator, class Generator>
inline void random_fill(OutputIterator first,
                        OutputIterator last,
                        Generator &g,
                        command_queue &queue)
{
    g.fill(first, last, queue);
}

template<class OutputIterator>
inline void
random_fill(OutputIterator first,
            OutputIterator last,
            typename std::iterator_traits<OutputIterator>::value_type lo,
            typename std::iterator_traits<OutputIterator>::value_type hi,
            command_queue &queue)
{
    typedef typename
        std::iterator_traits<OutputIterator>::value_type value_type;
    typedef typename
        boost::compute::default_random_engine engine_type;
    typedef typename
        boost::compute::uniform_real_distribution<value_type> distribution_type;

    engine_type engine(queue);
    distribution_type generator(lo, hi);
    generator.fill(first, last, engine, queue);
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_RANDOM_FILL_HPP

/* random_fill.hpp
9HVf8auTHf4cbl8MH8wlxxv5i+BzYp6Z/OPTcFX48zhffTofXh8DN1XtxdtP9TxN+fAg/utF+KkIn/EsOzyRHA7kv2fj9z7AS+Wxv8T/3h7POz5P/VPcajO//SwdQl6HyrdvlrdeqA8xk7f+C8+eqT9EvTGOD89L8Zf4vCB4mziuftC0nV153pUFqbx6ltmP9Uk/acjrUX5knH7fkeq3FezvAXzjXn3asQ/xfdI/t1928v1COH0Af1wsvwseP87bSo/g6G0t4sT+/LN1dFjn8I5sv+dhPfDzrI1420OT47Geu/FfkcfF8XPV3fj/ii967i/D3zP4obmu+0Q8YwfVXeIVXFPXbJ/xdXv8zkHVS57jATyx+3dWwNMvy6v0KZbEukPegwf1yw09X4TvLre+v1h/ObuPPv+YBy4eG/WJmL80Pb4z+f8g/UMff5rpH8KLbIJnDsL/Pg2v0qcsvMq23aldFHyi7yXkGeu5wX4/DC/T3wWT4dhD+MWTQw7Jeh6S/27A31pHa7s4UpepB+6D51S//CaeLvL8mP9mcvzQ/LPT4/kXirf+L1npleph6ow1D4lrj/C7j+M9KtVx4fTu8JMxz938/eiQYzKPfuEJ7ldC/3vOwAfeIN+r4cfneJ6/yT934wOXqbPd7furna8u17U9yTvjuOdpmM6P17H3gezt5HjO6K+R5yVyejQrWd8l/PVH/NvpeMPQixifYxcT0uM75VtNl7PDU/B/Z4u/+s+Gw19FO9ivenkLvq+vXTx6KV1/ewF+7+fuFzxerEe9caz9XT1F3fsn8hr+qmX/FA833wuH4H8KP3PfwEcxbyd/uph9WmfnKnzczfKC0Oc4b5o4MVkeCwcOqcLzrYJ3D6d/0+Ad8bHjTrzjE/LB1hijbwT/1YLPEDcXjbP+PfLM4FnivJPw6f/FA7Dvikz/aS6+NvQxzj+Ifn6W+PW4fxP5X5Icj+9/xZ6v8B7ZKPxg+JmYf2fK99bvi7c7Jt4nSs4/Aq8+EJ5Rv2oT//ck+cVRoe8X4E3v1w97m/rrZHzIafZjN959Sy6eRv79q7QeNmm++tA8/HrUF+K86JsMuXve4uf4vWb6/he85jPkegKc385/z8PPjc/0haf36ejCV70dY/x/KXoRvEmcf6Z4qc9ljLpLUbvz99dvor4y8tQ4HuvyPslV4mPkbyH/0Js4nnnfr0Y+8w/x4rNkjPs0ym/wc03P67drxbu9rp8FH1Gc/A52Xtz3uBR3dXXgv35Aj6/DL9wDp2xL7DDkVonvs/762/AJHfiFRn4Rn7yzyz7Ps553k+Mhj0fxni/D4er0u+xLoX1dxN5yp5ALPZwk/2yEB3fxW2PwuD3369PK/J/7R9jLzfD3XHLbHGPkLfLORfz4Inzcf/V1eY+jeQyeFH/XvjHpq4t58Z4j9TPUVbPzw+QheIptJWn8GfVvPGaPPA/PfrDrz458PK7Xz9D0pnxb/Kz+Gz1Xb/3tN5J9jO+vto4X8XTe41/hdyVLDsAfqHuNnc5fTvfeVFIXOCjG78NPCb80IOT1FXX2H6v3ZviG/fDP8v5y+rp8An3epF9np/eI9EeMWhvzxn31EaxNjsc4k73MkZeU4S3HycPmsP8b4XVybbT+Ku/Z5n8Drn4LLtVHtqBBvvyO+18l7l4F79bikwJHhnwDn8Zx/nqs+nlWEV77fbzbDHWDN+zb3/WlDIWr2uxH1Nvi+y3xOX5H0/Vn5uAd8AinwplXJPeN6zeyO+/Rlp09iJ4m58Vz6aPc43hfSRwPHloe181Pi9NZz4sz+gU73XfRP/k7dZLG7+F7npeHvCYu3gYPPSHvuw1Ovpl83pYPO3/JJvyovoJJ6oI=
*/