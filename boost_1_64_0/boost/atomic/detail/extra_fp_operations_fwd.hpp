/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/extra_fp_operations_fwd.hpp
 *
 * This header contains forward declaration of the \c extra_fp_operations template.
 */

#ifndef BOOST_ATOMIC_DETAIL_EXTRA_FP_OPERATIONS_FWD_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_EXTRA_FP_OPERATIONS_FWD_HPP_INCLUDED_

#include <cstddef>
#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

template< typename Base, typename Value, std::size_t Size, bool = Base::is_always_lock_free >
struct extra_fp_operations;

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_EXTRA_FP_OPERATIONS_FWD_HPP_INCLUDED_

/* extra_fp_operations_fwd.hpp
4yZMj4rfQ3h2gtmPF5BwxlrpFOe16P8uabgh9qpgT+t1TiaYFvpdwDWmM/n9+W4SniArya3J9IM2sGvjaXLv+sBIqxOmOcGQ2Sv5vjyH9xWV32eG0q2eofAZEp/Is9fFeo05UrV/foe4axnKZGw03HokGDW/Zmc3fukavgp55mWBnuTjT4hjRqDEPP9RCfubgTbsEPAcp+ie0NHyvIyYJoSg1tyf5uuPuuucLvHItd+9xOPWWC857EPluc0Io/u9nWh9gHly8M6A17gmWfdhthb7VTHD8bFWG6fxvknecyJ6R9qULDJjnL4171z17IYUfVMJfx62v5DwXxEbiW95VYXIWZA8YsLclhQtInesDZxu/TpUM5aVYDvkDiTB1RLnFtIuzsBC5zQd88SvmuseO6WrnRlpNX1H7DxJ/3ELPUfvfqPaX5oW7jeu2ufuN2aonTvDzw2tfoxxW0JoqH9/NFXd7Ar7G7v6pYTYeMv47bL3RVp4TLZ6Z0KohdueCWdmm/CY66Ir3GOue9D3dI25OmZHcyI8HXUefvwAtVx5PuoC1ApUz+zIXO0hiDtRK7n3MmzM/e/pfLBtp8A1zztS54YXquqlz16F+0LYJ1nmaczYb349/QPqyaj+wVqPseD62n1padNo+zCTtk/6EZtM/1rbOHVfbcypBNRsa3SfwTybPI0Zedq1D31fW0t+xboPKB/1VF/+9JZ+hN0Br5nkK5A+oukz0g4vcPQl1H5bM+ZrK/qR1I5NnHKtS4oie8HVTZZpK7JE39/qENUPLqw42yF/IkPsjLZ6a1meb56dEV43ikv6Xa1Jx6OQVdNR3gNxqiUnmzCrWZ4xI0yudOzW3jsdV0bSsajk7OLKqnrScaUrHX/RgHRc6UrHmxqQjtd7pONKj3T8WdK/Jx1PDp8toAJudqLaKxP7WRRASUf55lkwj3MjCoqXllRW8f1S09V/fKhuu5i2I+BoOyaY+5lmni5T9NXIOoueM6NFMWP/EWLncmsQ/2rMaFPE7DyrGWZec4y95f7NxD2xznm8LmIvzuSBnqK/xVqpMgbyJDxllUTcuHlY7KSonlBonOy2pRcJWZ0Rbge6UKUnhE6iGfBsW9T+Lux3tu03Hqv1em07RzK0/m82sFbdn44+1qqpu5freSG9uU5swPiqrrnt3+l4ynKdMRajmTMV1UzVa3153nGSbyoX6Crz6ePGTB41rWDc5NFTas4zIj339q1VDtVdqjPuDZbvjn9aBqLz9j6PML6B3Zw6wriksHQxdYpfONVtqqOccxCPqRvM/cj7OcZ4RJdlnuFK//yOteO2PxNzE7dZfHsrGD5xzJRpBYuKzyXxS0uxY+YIGhAu5/Nysmo/7zmeV+71vPKy8oKzKopJR796V92lSrmcLXWE7cDe2eCQtedKy1MbEGaPetGc+cJzMDPPiYrfLo/43UrduNYVvxkzpo07+ZQZoyQza/y6tKkdv7XfID/jn4Y9+ryI0k61w/gW76A6KoyS8jp/UDtc1a5w5SU3PFz4FxWugeG08wjXtYRrZ1S4TC486jxo4t+59nMO8pxDrufwZiT+72a644/db/Be8M/zveR2qR2u9dhNzIkKV/niyvl+70XtpkbW0+h4SMuCuW++sxxFuDt59BF4hmf/NL5r7bi8T1xyouOi1aRvOmO/nnoy59jryXcz668nD8OdQb+zKfzO1vA7K8PvTIyj38t0tHJQvPcg+Z+tcUHINr/x1Cdjmv3o87uz7ns+q9v14088+rM1jnYv01bZc/XT907N+6DXHR1/fOS2mxdv3JxIv038H/pJt+wZHy+/+M4xp6UdbHQpm5e2x9rmv31u1t9uL2174OsrN44=
*/