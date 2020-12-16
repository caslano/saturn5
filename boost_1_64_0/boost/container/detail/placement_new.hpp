#ifndef BOOST_CONTAINER_DETAIL_PLACEMENT_NEW_HPP
#define BOOST_CONTAINER_DETAIL_PLACEMENT_NEW_HPP
///////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

struct boost_container_new_t{};

//avoid including <new>
inline void *operator new(std::size_t, void *p, boost_container_new_t)
{  return p;  }

inline void operator delete(void *, void *, boost_container_new_t)
{}

#endif   //BOOST_CONTAINER_DETAIL_PLACEMENT_NEW_HPP

/* placement_new.hpp
Gc8GxZp8WnLfFmZvG7ET7PmDtQmzj21gfh06GW5mr/Qf/BbMn8zF7I+Ov9TBwshMHndTQQssWlhUD3MbLEHkfOmr/U/BMsgsZv16f3kHLE/k3P/ez6GwYtEH866WbFi1yJm36ZlOsEZRy/WZI/rB/Dp6x+075tftrPUNcpNhPNcavZPtsYb5KxaoWLBioYqFKxapWLRisYrFK5aoWIpiaYplKJalWI5ieYoVkFnMJr55+CJYmRJXQWYyO3XF4StgtWRuZsbHPTfBWoU983aHb2AuP+/27PUd5iFzMrO3dbAgP991hpC5mP13SIcNsGgy3vcn3+zzFCyRjPfvlshHF8DSRS2b13TrAssWOXef9+hXsEJRS/N9zwbCKkR7Mz76sTOsVuR8fMx/VsKaRdy9z/ynD8zvfO+47ukrfoO5yXjcfeOzVsOCyDzMJndaXAiLJvM1R7GivQtWvz4RliLsdFOfJFiWqGXUXZN2wfJFe/Z+DFbITM57sWKlZHz+7O8OwCpFndPDX78AVi9shzXzHlirMPvcAmZe4N2evX+HeS7wXWcAMznWQYqFkJnM7PMjWCSZi1mXbq/thCWInPZ+E5Z0ge/+ZZJ5mDW//uJoWJFSS7lPM8JrWC3rjKT2e0dgdYo1KNakWItibYr5dfJtTsUsxdyK+ZO5mLHv9YSHKRYr7OHUK3fDUsksZiFvvhcIyyYzma3qkDMIViDick7HJcDKlLhqEVc//8UXYI0iji8TbSJu0FV3PgSzHN6WdZnfRFggGc9pP98BC2Mm24sWOe1lHpbITNaSIWzb3GUHYHmivZIrjnpgxWR8juznDWFVZE5m9jYEVufwPe+topZp+x5Lg5mdveN69WmcDgsk43HPv9vyFCycjPfB7+mTf8NiyNzM2Dcow1OF2b+rwXLJHMzsbQ8sX7FCZnJdKRZ9CJiQOgJWKfrQ/iwUxlPE7R5RmgJrEX3Ym3q8P8y60DvutHNMAiyQjLe3+KZ9S2FhwsYu2bAPFn2h777HkjmZ2fdnwRJFLfPaSr6DZYj22t/xiXkgczG7f1jVZliJyLmkLecLWJWIy6scPwnWKNoLK1r1FqxNxA296u++Zy052dXlXN/X83u36D8PGfq+QVyHDiJzMOPv7A8RcT9H7J8Mi1AshuXcKL8loliCYkmKpSqWrlimYtmK5SqWr1ihYsWKlSpWTuaCid8K6kQcv7+1QbEmMhMmrt0bTm+z39kIs8gcMPFcgZubWM78mcn+BQqz36sJCybjfe/ov3soLIrMYrY9bdAFsATRhxHDfhwESxPWfd93j8GyyZwwsR7l++xD7IRClrOY7n/ZfO3aR2BlZG5m0/rsPgCrE7b//FONsDYyJzO7FpjzIqqFmT0PMEsYr9NNxuu0r3XBgsg8zIzTlz4Hi1Zyxgqzt8mweJ9xk4xEZu8YiV7v6kxh9q4x3cvSyJzM+PsuskQcfw9IjhJXQGYys8cFVqpYlTB7XYHVi/ZSn2r4BNYs4ux3n8L8utJyzSzo/V9LYW4y1r/23wZh/l19txcsbGfEuA9g4SKnPX+wSGH2u65g0YrFKjnju/oez1QlLl2xTCVnnui7fX4LKxJj/WjA7ZthFcJ+SW34DVYnctrHn7Amn3XeYbQwe8+YxZbrPkYbsxKK4+bXzbc5FbMUcyvmr1igYsGKhSoWrlikYtGKxSoWT+ZktiTEeQkshcxiNqbp1HZYFpmL2eiDkdtghdzEu2EqlFqqRNyh49+ugTWKWj7sW5sGM0xa5pl9XbpqGswSdtff910PCzB91xJExtvrOPf2aFiEyNn+bmyMtamMtWKJZLzvBWO7LoVlChtc8q8xsAIyN7P5dwwbC6s=
*/