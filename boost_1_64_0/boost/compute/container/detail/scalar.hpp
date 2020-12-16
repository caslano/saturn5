//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_CONTAINER_DETAIL_SCALAR_HPP
#define BOOST_COMPUTE_CONTAINER_DETAIL_SCALAR_HPP

#include <boost/compute/buffer.hpp>
#include <boost/compute/event.hpp>
#include <boost/compute/detail/read_write_single_value.hpp>

namespace boost {
namespace compute {
namespace detail {

// scalar<T> provides a trivial "container" that stores a
// single value in a memory buffer on a compute device
template<class T>
class scalar
{
public:
    typedef T value_type;

    scalar(const context &context)
        : m_buffer(context, sizeof(T))
    {
    }

    ~scalar()
    {
    }

    T read(command_queue &queue) const
    {
        return read_single_value<T>(m_buffer, 0, queue);
    }

    event write(const T &value, command_queue &queue)
    {
        return write_single_value<T>(value, m_buffer, 0, queue);
    }

    const buffer& get_buffer() const
    {
        return m_buffer;
    }

private:
    buffer m_buffer;
};

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_CONTAINER_DETAIL_SCALAR_HPP

/* scalar.hpp
XNcxS9Y7+1r/wP/VMd+P8BzOL6kvhaJDthOvehFnzUTnwM/F++Lf/Pk+9YxZ/sTR6cRJCeSvvA+2eIbxXD/2fUy2ZJ6gZ7VjD/HPjZO4T9SnSi+jboaOHMVxDt5GHbIOnaOJdebD/V9LfaWDfCiS/PkEcbLRv9nJujX6Fz/Bbl7FeSejqztgZ3g+qf8Y/qGN95lYUt91xb8Ucp3d7C/4Dr19PXb3n5znF/Tv5JFnsQ/G90d0iWrizijyaN57axol3kTvbjSxHt6ibvwKfbFXsL6zuT76jzeuJl+nb6FyBn5zN9dFvO9n5j6s5vmg7PMIvYs4a5y+5C/Qc8hXKlcxzpdy3onUN+vIT1zJz6/ET9BfHLCI+j751P4B/EM18ZklcVcgukQMccVO7MxC5vUU9hfdzfrfxLjHU185hZ63lXjDz3jODH65jvFZSN/8J8yTT5ln3G8zeoH/L+wbZpz8yNOiQtgHQB+Bowd+1B//N5s8nPGKLyfuzycPOcN12qLf/UZ/7f34lwT6+H7FP75K/38EeQV9m3U72cdqS781zwEoiMCO4Sftd6FzB9iif5C3byPPtqQ+TZxxsp95VoOuPRO7cJct40WdAT/hkUi+Sr+7iTr5/rnEM/iLdO7n2IPEf53kxc+T19GnneeL3fdGf+N5uwGPoad+jd//x2T0ucnER+y/pq5QT/1yFs+JtUlGN8uiXuZC38ZB/NLtJurrrCt0Ovs26gKhvMdtHn15Icw3dMRZxE+7Z5GXXoJ9If82z2FeVRvvY2L+o++PHWH9sX/qZDH1f/IZ52vwp8nUiXrJa+4jL3VhXcaw/v0mkw/Zomvjh+tZf39xvdTVBnivnFck+wHvIf+j/pv+BvlEJnpSDvoa62Z/Fnon/nbnE+g6Z3geBHbH53vsArp76Rh9GMx7X+aDcxr34VM+Zyn6mIsd/Zz0SzuTF/ijL73LPqi16CsZ2PdO7DPjFfgj65d47Th9uYcs2e++kLz5J+Yhz1PwmU78+zT+Zh/XS/yQVUAd6gTXiy7s2ou+xHibPrDCj/McgIPoYtnErcRvZp4zNDyNOM+Oz8Nv7sznfv6X/Ba9yP0gdZYZ6BDszzr0MHYwk3FZTRzTha7xAPFCH33ZvHdk4wbmCTpg/UL0Z+M9EQvQTT7kft1N/tWJbnEl/RnkZ17dnMda+kvWsB5Y11t+Ybyf4rgbiGOJd0+SD/cRV3gQr21B3/Gx4fPfIL+gr+CQLzoE+U0xumuEkRedJq+kv8CReoc986OSeNl1HnHgWZ63dA39FP9F9zpIvrycfjr8chT9NFHv0o++kPrkcvzDs+xLGSBvJP8Kqbbhufz4FexEG/1rvnuI46433rPG/GF/cBZ5btKsSYw7/u4/6KSX2pEHoseQX/fRT2jeS98M/Qpj6FWJlzAPjjNO4+RVo9ijT6krorOtwq80D6GLoT/67EcHvI46HvmW6zhxG/Pf7ER9PRo/8QLxEs+3azb62njeqs8aoz+addJAv9GNnN/F5IXzyXuIN8zb2UdDPut+NfaX5+OaLuH9koxHN3FRzs/4qUPUkYk7Ns4hbscuun5MnMx9PvgB86+D+Phm7NwpxudJ/MhW/LwlzxVAH/M/xvz8Hvt2G3ELelAL8fvaDfTHXU3/7WTqm5nkK7vpt8RP772a+0V9PIk4Nh39J2o98Rf9B1n0bfpz3iHrsLMRxPtrmef4lZb95HW/EQ8RN69twD9lTSZ+ZF1gRw/yHHd7+tL3k4/t/JW8Cl01gHntThwyfLktfRDkbW7kKcTTdcP4b8Yr3kS878U6Ynx6iFeKpxp9aOiT3McFl+GXY9HFec9z2zHGoZL14El/cgrrmLgltMo=
*/