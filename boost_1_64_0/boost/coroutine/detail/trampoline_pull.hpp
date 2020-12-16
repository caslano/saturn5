
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_TRAMPOLINE_PULL_H
#define BOOST_COROUTINES_DETAIL_TRAMPOLINE_PULL_H

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/context/detail/fcontext.hpp>
#include <boost/cstdint.hpp>

#include <boost/coroutine/detail/config.hpp>
#include <boost/coroutine/detail/data.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {
namespace detail {

template< typename Coro >
void trampoline_pull( context::detail::transfer_t t)
{
    typedef typename Coro::param_type   param_type;

    data_t * data = static_cast< data_t * >( t.data);
    data->from->ctx_ = t.fctx;
    param_type * param(
        static_cast< param_type * >( data->data) );
    BOOST_ASSERT( 0 != param);

    Coro * coro(
        static_cast< Coro * >( param->coro) );
    BOOST_ASSERT( 0 != coro);

    coro->run();
}

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_DETAIL_TRAMPOLINE_PULL_H

/* trampoline_pull.hpp
1WnVN/HAk3uth8PxFPyU9BFbxtJ0s/HuUrasiPOvw4e/xddDjQnOBN8BXWmFHA9GP6YWOj8G17wut+AD1b+HS1/zIz7Y/6C+X8k/DrDTJ47TMFPxx9QJ6sAxYrWb/YkvweTOaoeub1wyQv0Htg7iu1vNq9zg6Zr4hI9Ffymu+cXA/HLVIXIN8/BcLXWoJjSzPLN2Y3MJv6btdG/5Su2l8Aun98HXEfz/jgV0Pb4Z9LI5egX2NpYjiIW2X9MwNMfxC/m1WkOVW/FxB1y3Xg6wSl4vR1xdDV6liddTeDSdTiwidkrBj0Z8gp/+XJEu0L9Lh8Ej1+enZa9qhwPUrL5pg7Oj6cgHaRLc8Op76oPXWEtpL45/lmvXkI/y6cgiOJH9uvPPx1vKu2DjQbXwuzvgKX74h2Ral8ZI5zPpntWgr+uKwgT+1GQ9XWpfYDnaYcPV5mEDTqKXTtZST8/WrwvZ5BR9co81m8vEcH64TsMfY7Pf16Or4Fp0rZB8hp3EwtYncY45/vIK8YCzBu/nH9XUB+iqAw1xHN+feDFfKGcMqfisgLo4e8Q2V7/ojnc6i7vH6Z0r1N8f1/+DdBatW/wHMVaQXT5VY8ehl39CFxfS+G6lGcEeLj/llfFfizecFmM+tssFR7eQi6TJk14Mq5vSiPBoBO5JyKN+dgif7Qre/xaXEeJBzS8xqGPf5edRz/oODrDtIyvNyUk1854wciB9nAB3xMmlA3F6e7kcDlxQXU5SnDb1c7G27AZjH2UtASd+gyMWOXbfbHM5FQ/zy7RybFoY94nzQ5X57D1w8yZ431++ehvt/0xILUvsmL9V8XRHIt/eCf+sv/YQxyvN0WK4nzwOn1ljS+nGLmplDWHtcLph2lh8az6nLOYH34hzOexUuuaoulqdsnJguUuimnNpc9GtkLnsiXPaG/cgcbeGD3eVw8C+30Wra+G6+/jzSPWGjnw/T03njrAVyJgOaJ9oRflG9wvo4+ns+q09BWVwgXpPVbXRFc+x6SiY+wzMb2oexWvvBPlGsC/2YbZtia+eos2j+R+tl8HXd7ejwe+D+8WCuWOn3P+uSu938cWT8ia230z3d61Ad73pff+b6AB8dfwyMQQvvlsHl+n7VLXxOUNpYLi7Vs1r2TA1Pvccey074siJm/Gnn6touej97nkx3lVLyDokD6MPR7aj079kW/5c4Se5xAHxxOYF6+a8q/lAhBySHitfQD8refZXbPo6vd9ETCwxN8PxWBmxeoheG6Herj7/Ady8jl6uv8V+EFp3ozxwbDKMde4XF+MvsfJWT309Yl7voG3k/j+ls6u8/BK4nDebXnuK7RbStKniswDbX0Rr1Lc+M58N5sCw8fZO1MhZ21hfWExXgV1XGmusGvGPNM5otplsbDRUBo5M3kK75YFf/GUl/XEpXnkBaXzAHzrN5de089t9rY2kuhZvfrQHN460pjCJj+7jT4fVQD2jz3J4PZRW7aIvNfkHPTBqF05zj+z3zO0sPviEz+jQrH1h+7SNmU/eWdAaYSRdByv3i9P3qsO8l/EA/nkOZ50soaZ2O2wpD3sj1RGukLcE+sL9vlbviKyj33Rdj4fpBFhdbYdYzxCv/CGujnltrg7d2jP4Yvg9/GO/Q8UuNFUeeLwGz2xmM7gx2nOuXwIPO8LTKfztRvcYzI/h/vQP4dcleO8UzDKeLffBR5q46TY1DPeNfEqta5F+qS1sni2Xl8+V/cI8baSlfo+Lvo84PVc7T8knR7K9zx6RYzVPxDc082Ic8CAb1g9qNnXD7hEh75d/P4u/7RPPfjzC2kjId6aKjVl0f14aoJsaawc5hLmOeCL4Ph39vETOmqwuvJ925M8=
*/