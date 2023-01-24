
#ifndef BOOST_MPL_INSERTER_HPP_INCLUDED
#define BOOST_MPL_INSERTER_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

namespace boost { namespace mpl {

template<
      typename Sequence
    , typename Operation
    >
struct inserter
{
    typedef Sequence    state;
    typedef Operation   operation;
};

}}

#endif // BOOST_MPL_INSERTER_HPP_INCLUDED

/* inserter.hpp
1hjdF0Fo084RceGoQg73itL0F58Owl8COTrtI6gyLto3ISeEv5n3ec7JIhIyNPr0upJ6N/dhi7PhqLNw/l71vrfVmr+XfGBRhvXl2aJCt0G1Z6nrsQXpWh1HD/4Nf7SE1ZHlgeXaXknkSNo0FvnIl6jl55trVFt4jcdvsn2INRY0mUxHqf11qQupFK9AzmG97oiznxB27hbG0FvkJ8kTUvWO2oBL548Xc/TJfqeeReUYfkmis9LAU3nXGX5LxsTCbWdLV7OP1PgREmcyxNY39/P1OBpCyGEX5eCwwekPI7jtlhT9c2G847lir1yf7oNJpOPNSxFMrqQdY9aGO9HXPShXBO5mZnaMHHy0v2OsWHEQtMtYCFS8v73usdP+ecRiXJy0MQ7aJzYmMvzNk8mYzLOoAcBEcNyMqkUGj7jLwu2OtYh/veZ4sOOt//PUkxvJK2eeC0sHdcdzon//ETNvxex4f5IZu2yphgX8yJK/f0YBYZeuDR0AOeM8mGaWhc43msw0kBDeZ4duhE20F9sKLVZ/iQ+/aErgWxQbOJRqkpWZIJGE/HHaWHqlUOHocMsFErrAgTrhKJi9LKpIfeHzyIGYveeUjc1TEyZMJZlbeP2r2SQRCEC6sQnVwDzi+QuP84xDp4dOLq1SZzZHBG9/PJnH3c8832AB2v2DgiXV3NMVx+i6aSVdubUr91iCMDYtDfMFBrSDVM3W/BiH
*/