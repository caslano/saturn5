//-----------------------------------------------------------------------------
// boost variant.hpp header file
// See http://www.boost.org/libs/variant for documentation.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2003
// Eric Friedman, Itay Maman
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_VARIANT_HPP
#define BOOST_VARIANT_HPP

// variant "main"
#include <boost/variant/variant.hpp>
#include <boost/variant/recursive_variant.hpp>
#include <boost/variant/recursive_wrapper.hpp>

// common applications
#include <boost/variant/get.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/visitor_ptr.hpp>

#endif // BOOST_VARIANT_HPP

/* variant.hpp
UfO6FtFfaiwiBaxvBCtL0bD75m00VhRWEVYU1pUrOO11sbB0N9SEQarNcWdGcCGZO/PbXNt+IIukSRMB04UNd0VX1Uixqr6tuaq2xCySmDcE8cnd4pPtNT+pjvkk5g1BwDuqB7wDwn9StK8rwxLgUxQNzfsCC4AgnmCTIb6AIJ4AXysHhAJqAcF1wL6ilQvgpwBDPwcAyPtB5hvL4ENOOsiBNIB+LMBXMcD/JQbgXYFpewD0rsCIA7j/YP5/G+A/FAX82acM+ARPscCvagUb67UAXJnT5qq2/a7MEX9kGLyekBPA8Pxdsaj1QxO18pyZQRO1duKIcjMbz7oZNLNd6tKmvU7VaSPeqrH0Vv1MFIZ7DTbTr3M1sfFlB7L4WyUAAGSZTraV4QyQogQmQ71a7KBKYLANafEMe4AdhBMQB0mB2G5xScMhkrs76FDpng9ptxf3P11PfMrN3ydZrsWTh6cPnt/iORdPKzwOPBvwrMJTiqcIz5t4XsHzDJ6H8BRXIg7Pi3iexBPCMx3PeDwj8Fy0E+XhOQtPUzyN8MThORROsuwM/5/P+f/v5L9jz5NrsnK3DTVYuRnijKWSuJLJYOliWTkStzAPsxgInZVnwMc5zqZPJP82R/IvLqgyGQzMiXgXmKEcl3H5FKleYRXTF0erGucFL1QHs0LxXsmp4KNfxqb1IDZti9HFjRbZxX9G/24ecXr6d3I27GJ08j+S/couGEgwy+zW1iLC7XrRtQa79cprBrsVIXaLZNLgc9za1jx4/gLPBfYKZNhTYH62Mw2mhDykPQdCLKNUKYlAR2VT0F2mhJQkorEEnVZSbcsdvtZ/+DLHfUcTmIVSrcQv2TCZZMRfLPiqcfGYbeKzArxuduRK+37QUV1xA4srZR9q/ToX9ByXgLlHFAUTXSl7UZTJjO2NYcb2CWYsFEd05DbHzE5oQBGRijjyKWsIFcqMsqD7LXJjE3P/TMEa0FQLFanq7FvoztgW9L2rp0AVFwSWO5QXgUGi7Yhb+1TxH8a5jmd4CZ3rrKqW5zpk3U5X0BILJoOCAzNf7NEXDl3D0dticgPEzcxmmHivhagZvNe7HtuXXPu1svadRu2nRY6IUKApIGAjqlGZIHVpVdr+yksIXzFF6tL2A6lVdrTyDVFlGKc9Qd+BYMEhsN4/uXHI2FYdnvc6aFSQievcIYUYtD2412huawsGrvJ7C3039C0FFBdIy9dzNQzD1Ql7sUAT9qzfgUMhIgDBjvXh6D4Uv2/9NoVpR6RS2l5O28dp+49J28dp+zntwDFp+zntAKf9cEzaAU77gdMOHpP2A6cd5LSqY9IOcloVpx0y0iihyqX59mi+AwR+/uePADM+ZwDjU3ESGBkKyxX4ugMwSvgjqMOgmmA4YiXB4N/ZuxbwqIorvJvdJAsJ7qKgQVGixhoLtpH1AeJjr9mFm7iBWAlgfRCLIipqlESi8uwSyXpZpYqPttZHq1WrVSyoPCpmEyAJEQmgEtQqoOKNEY2AJKKw/c+ZuXc3D0xASGnrfgyZO88zZ87MnDnnzMxsOlY+zrcARIC9CjYtzCdi8uv9TbfmyEU4i5z8LZ9FZiq8TlDhJy2ocFOUsKIf8CH9dJH+sxbpm6Ppox/wCerYw9SRBOpQtKb6ISZ5+LQmRdtZ/3MmjzyDPDApNKEpoI91RSe1oI+LJH0s+1NfZPAtqK8XBAJ9zSpBH1WE4K8Iv41R3K8yaaQH00iPr1vFNXLc1xy3vVXc1xy3neN2tIrbznE7OG5nq7gdHLeT475pFbeT477huF2t4r7huF0c1y6NgP9/DQMO/P9S7tdr6N4AB6kKytCzA0TP8giXuwCb4XWZXnOEn8w=
*/