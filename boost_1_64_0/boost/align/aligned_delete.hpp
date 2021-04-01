/*
Copyright 2014-2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_ALIGNED_DELETE_HPP
#define BOOST_ALIGN_ALIGNED_DELETE_HPP

#include <boost/align/aligned_alloc.hpp>
#include <boost/align/aligned_delete_forward.hpp>

namespace boost {
namespace alignment {

struct aligned_delete {
    template<class T>
    void operator()(T* ptr) const
        BOOST_NOEXCEPT_IF(BOOST_NOEXCEPT_EXPR(ptr->~T())) {
        if (ptr) {
            ptr->~T();
            boost::alignment::aligned_free(ptr);
        }
    }
};

} /* alignment */
} /* boost */

#endif

/* aligned_delete.hpp
ZVil08rI2hjYAlhMO49Hfpd8WIn5rTx5pTobHxcQuNagGzRXuanPQuFwUp+bNc59pdxP1gNVoN24Pc3YrNTIN5VtDdN6zD1TSko4s+6RazRHJui30rrSajzZ6SkI7lgZdJNOzmIFV8+NlUqVxTgNkD0/AZXatMB/HTQuuES/gzIflpTpK2eeWmBJp/1xORI27RL7vnyvqsoRV/dnSSD3cS/XNikaGitrrSD+oetacvKInHlGe45bz0L53QQbHnF8widaDV/7FM4vEfXdAbA6AYbsiXHZOoaSoB96MelsTDBVXmb+EJ8PrEAyrEh5zxR9N/kzNaFETbNkP+In/Hkaz3+V/9E8e4WcB7YsiaONL2VzeOgQxEmUc7YoqPnlGtJtwAWuZrFVLU5jmfA2RKwwQjZbrIxcaJcw/JV76Fykmm1ax+MApKWhTxkGKKUoq8B0grBtcgPKDlC1tbemINpcEn/VR8c8iSIkqtI50mphPRkBUQBd/CGlMiDA3lxs0vy1A+AwPhaEyKF5rOiMCC1YfKAeKmqwyUOmpJ2kBRnwfp9HFBc7E1of47A4KQ==
*/