
#ifndef BOOST_MPL_AUX_CONFIG_BCC_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_BCC_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2008
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date: 2004-09-02 10:41:37 -0500 (Thu, 02 Sep 2004) $
// $Revision: 24874 $

#include <boost/mpl/aux_/config/workaround.hpp>

#if    !defined(BOOST_MPL_CFG_BCC590_WORKAROUNDS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && BOOST_WORKAROUND(__BORLANDC__, >= 0x590) \
    && BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610))

#   define BOOST_MPL_CFG_BCC590_WORKAROUNDS

#endif

#endif // BOOST_MPL_AUX_CONFIG_BCC_HPP_INCLUDED

/* bcc.hpp
fej1AacXmNvNyct4MMNoIz4/nY8/BioxXSIF1T+XYf4NEW9/nZ18Hg3+WeoBtjpPNfN6n/3E+IfeVuaO8IZn3Ng9SqkMxaNFO6aBVPnNb2cXmzvMqfh+t/mpWnNJ4anJdRUeVYHRtJ0kgCfSo5c339DmVbzfExO3+UAzGl/cPPH7/cwPI/CvkVzi6bDUlkcn8gO3hKy+urCXnNSGH1UGV/UeTP6YPlXl68B1bjYP43W2n2dM3/H9h2Jf+dyfAw+77ZofoJbjej3zO/n2MXGfivc/elHgtmXMmZszll63tLfHyqPUVX38rP99owAEIgECSZFQ9ptXgYPuj24AoDvjT1vbj7RM0F0ieiDuh7g3mLzy0uKauupJE86Yof7g9u3/L3v0teh4pISUDV7keq297cNmUOuZzMvue6TEAmCcod17V31ZKz3nZTClGbw8/exWnY6ck+qSmoYyLbCRT+NYNO3tL3fPIqRUCezUM9ZNDH4374bJjFuqC7DoPbjyZrH1cw4AnfIv+T4gTn5m9Yd3TZgX08Xzj8hWrXqTOqXP3ScleYFlYHXDnjcb9JNvn7GsmazqQ9qZFJmsUzHjs1HlMRXXteDQvkveN1rDPWVfrC4uHoK1JfmEDcPXFKzsyL8vkjR+Ol039da+4oeah23W1skDApH6yG1V77k7KkjTyT7zU9tSbe4xqYElQeQMj9DjF8v0VRJabtmD9OKWoU/WmZ1XylFVdgydmy23lJ26fSkYyi9X9lD3bqn1lcHKY6K12mYV/YgXgNTZH6Ebt7FQTEH8edrJH+nnuYvU7lX8OGNPlTs7kME/KHNMJ9LlQtCkfL7n00xSpuYK6aBH9z+2+JrsYxhorVY/FJYr6/Y+ekGi3U7L6E060xteD1fC/CExA7aZyWzYk4n6g/Uz1B950Jkudbv3kKRalUv8k0/2zc+Tu7ey2jt6xrRV715KLZJTKpxu1RZsOtQwrYflHasrD7c/kMHVuPy2mit9sr/ubOymP3JHM0blNeb6rA5om6d3KqPO5WbCiDo5ZZpB5aPDCntXRT3Ur1jebNMSXPBAmrl2zdq9joviFwWFLwqanZCUELcrADjOqHJoLDi4buPE1h9Py3tmNA39Ole6rZ3c8o4uOpuzm6y7oZv+dB0KhZlqcscu+Vf0T39NnmiUIJhg2uOn9PvXW0MWbLuTuiW7b8TtbJfRL81tLcGdoSdZMVt6+myrvON8YPC03on84R9w8VnRGl/fu98OLU+zjvajhvWn8fvL2tt0/OwLB5Y3GkuBLimNBAbOz3ydtG7tRGZtTHOy3cLqnovL9/R9kkwCP7+7n3lxLndz/r68JI2pJ1NKzz6/b+Ka0Z/UlH6SqvR1gmAf6wmnuukMLTHEn3e/5EIt0H6a/TFrdL8rn15tshl0Y3bhIYp6ZPNV9R4kgKOyTxPiM51srqxQLHYHkLrwv+hw+7podPlWzvWHw/r+0n9S6KcpE0efvWq76+2CcLVevc7bVjLXxktxN4BLJzYt0r1913N06oiD8yOnqjxtLPoyxFFlP3hwdJaaoXR4ufSnTYNS51T03zXRQmE/LTWTdHWVWZDcOZl8/frq7w8qSJ/XtOgO86y+xsL7T5qyN0gdBChfuf0u+w6xv2ig6/OufJXp6CP/PJFIPNPi+Tap/EEf9D8aNfVfHbpD7WzUZwXPjezGfTQdUpX/rDcv1YqalQKnhJ/Xza3c8GHx6w1BNaXkoG8vtoM0gCfZjVOPDzh5m/190J0P/L1P8PWggZZBcGfz+9lR9uMUt3qYe1C2Vcls8D33L5SNBMLoqdUss1Gzl/bUOhGsOcZsDKXhqkN6a1/qrMysfeDbpSeX8+cqn9A=
*/