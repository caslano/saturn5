
#ifndef BOOST_MPL_FIXED_C_HPP_INCLUDED
#define BOOST_MPL_FIXED_C_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/static_constant.hpp>

namespace boost { namespace mpl {

template<
      long IntegerPart
    , unsigned long FractionPart
    >
struct fixed_c
{
    BOOST_STATIC_CONSTANT(long, integer_part = IntegerPart);
    BOOST_STATIC_CONSTANT(unsigned long, fraction_part = FractionPart);
    typedef fixed_c<IntegerPart, FractionPart> type;
    
    fixed_c() {}
};

}}

#endif // BOOST_MPL_FIXED_C_HPP_INCLUDED

/* fixed_c.hpp
9MANMl8IabnM11rmq4L+Mh//wHyAdbAytkQXvIjnSHtlfu41mN/0nvkxmX2vHB/7sD7uRz98Czvj2xiCB3EQvoPR+C7G4SGchYdxLr6HC/F9XI0f4AtYiC/hR/gKfizHzRH8ED/B4/gpfoefYQkexSv4OVYh719gHfwSG+BxbIQnLOUs9y5Y1045PyXlvEW2+2n1fpT5OpRxPC5x8J3KS3/U0rn+WUvn92ctZ99XNxFnU5Htef7t4mo4JlJIy0k7SCdJ1YlkCyIlkRaSCkhHSLpKrjo/UhTJQFpC2kjaQ3IOzsE5OAfn4Bycg3NwDv/fwy2q/9fnVUD/f0r9/1qlLj9Yed6ayHqNTQsaxz/B+DVdlfE58VMDMxJm5+iN9fvf1tdZ3u3NqSTPROSZtQ9pA/MZ+trWB5reao7V5zn87DrdTVsPe17qS6UeVlVfr60fdq1cOk8byVN+2XmKTTY4/kx9Ez9Emd7hfJnL6pzk60V5rvQ8aTP5Kiydr5xMelobGGLKk68DebroUbqsqLN2qK75pLwnTV99bJW2Tcb0BGVLrO/zWtvQ027bcqn77yNl3ou0RYlNCDVuW3RwQPfYEf2Gh1tKvBx1GLbHwQbWmJFuWx+fpM/Ikfr46xwbc6TunPVb3h17hnzq+tnPJ0dGudq5lGPjpvOqvE+90oX8VTE9//Uw5kvqRtT7TfaR8d1/2W+271fnVZX39aReax0a27voZ30XnLrC1KTYlMzsnBv3m1dP9e66aQ7yK8dTM/42ZOlnJqaYtqSeKm5EmZZoCU2/iqmkenJsnvYwTWOQc6hElqde1p8MykbOSk3KSZF5z2mOR229YZ7UKQ/gnPMWn1WOx/6md8szYxNyze1uBDgcG2PqN/BkuLXfwP0DzH36dQ7Sybht1nFdzOMWWscFmsf5Wcd11qmOIV/2PbnTtFvJZ4pQjiM7bVl6YjPzcaSKaTKwrBm5mTn6bNM4H8ZtpRxSM2nlRNbpiy5MF581VRvvI/9eJPEXiar2VXyV5crnYvlskPUek/k5Zy15Pif7NDPLmENNH5hMZDzu51Rlm6qZltPEXMZyfP3AtTA3J5liMI0rlHkZx+xy7Fv2v1Q4KPmTY78mPs92Lx9o3v9JuelyzW/gwDHfnJQmhSv7pVQ5utmUo6f1u8ESNzWchebIckuk3JL0WcrRaK8s5VptmoYNlfNeW75KvMsWZbskT+o6ZZ3UKbvJeVAZX2Ca4kHmctBnJ8Yq3/tSFg6fC9ZySdRZy8RXcy2jTOQYZEVyGMrxaqf8GljLT44Z63WABVquF9tNsXEp+jzTuPNKmRmnY6y0e9B3sLU8lM+LbD7/bvO5+RDt5z42n5fYfH7N5vOJIfbL/6qU/zJSbal33KEchxHm8mczjMfijdu1lWOxVLm52hx3bjbXEE/tNcR4bxfHzdES470d609K5Rte2rnVnttyjGpjsc5T8cVcFLZp269E2N/2AokrGCrbPoi0k2lCh5q33fRN6EhcpCPbXvo7VttnaqocG1lD7ec3ro5phUtZnjfehbuZJt+S34z4dL313mWLg+eKI3k37Te5X0DZb+ptKR2nKtPlKNsn3786GZdkbh9Gb4jVzzCdi6tkOmVc+sxYy7V5vmraJBm3UDUuXeJW1th8Lyzn8zXyS+aM88yRf0/OiM00SNlHM065BnKfYZxmqfSLzC8XDkfTNGkyXyLLUfK50vRZ8mPNZ5yMl+8Q47gtdr5rChj3UX3jOjhGTdtusC6T8rAuM8+aZ8J1TPlJkfabk+X+Ocbme2obx7UPx4rSn9+sEdbvqSUyHeu1LH+jeflpSbHS5ozxGHx+uPb6cdTmc+uR2s8PjLR/zBY=
*/