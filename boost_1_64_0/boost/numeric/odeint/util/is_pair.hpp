/*
 [auto_generated]
 boost/numeric/odeint/util/is_pair.hpp

 [begin_description]
 Metafunction to determine if a type is a std::pair<>.
 [end_description]

 Copyright 2011 Karsten Ahnert
 Copyright 2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_UTIL_IS_PAIR_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_UTIL_IS_PAIR_HPP_INCLUDED


#include <boost/mpl/bool.hpp>
#include <utility>


namespace boost {
namespace numeric {
namespace odeint {

template< class T >
struct is_pair : public boost::mpl::false_
{
};

template< class T1 , class T2 >
struct is_pair< std::pair< T1 , T2 > > : public boost::mpl::true_
{
};

} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_UTIL_IS_PAIR_HPP_INCLUDED

/* is_pair.hpp
kWS3rRDBzbFu+ywpPX45UVSIXtti7oxA/AwzdS/x8mY2BdpBk4jC+q3x7rsQt0AmWL+F5usV680Bp9Fq9uy2Vk+5aG2UPfF7ZvKB0ezWRuK3mmMpqLfmamWo5tZUbXzCSFynRuKnDQwHRooV0GSj+8WKLaq5oxXi6/CWI07ADfc4IJDqQ6miDV6gi32pO8HE9Z4dRPx1c8J6D5ek9Z5TFJdDe+zgfGiMBVU+A3kNp6GKhvvFxXI85OJrUocz/EB0LkEQQxEZuLFIhsQfgpkpsZ1jOyTfUoZqSrSXJNmHJtmHJ9oTy4scpSSUNa1rTKrltk2d4d2QZPcn2R9v6GyvSPK/cnNn+6lJ/v2S7Ac2drafkhT/wqT03tmYZE/yfyzJ/85Eu0kfrOypz5xaLg7EWixLc6aYPTtdy1dzY9bG2En9RvYLD3W2/5Fzi4s8Jh43eY22xQ5u4g2acD23o211ZMc5Kly1Z+CPaLWn4q8OV+lr+MV83NeIoTk5I3CHJhY1qIEdPF0bEstPkZmfVb8052qeylHCnBV+USFL4fajGP3EWFi04bG4vVrzxSY4iRWI6xelMIITLSotFT5gpsPElLdJB6QgRAeuVfSLFEYfZ0b3mSl/RaaccYU6xVkhxsKuCzmP1H6w6DSfXNey4eiFaUi58CGaOsGcUZz3SdXbfvEzNLspciKzj7lTOcWKU+aHIpC3SFV087ap07RyMx9eMx+3bkisAU4rPGlWUS7eAVhD442f17ZgDbt3g7mGDcEcdwdsXgTcYIkR5b7KgMVi/gZz5doNqMYJJcPwBYm2X+Jj0H/fkuuPOq0mnkE/NRRjLZxLfisJw3qf0OaUlBfLKkTfjeZCXa5fCtVVKX3Qe52b293LwQPWx8N40LG81ErT8qm2CH4hvCleCXuqGfnGdK2dawCu5UqxKlWhcuLW9tviA+dC1Ux/Xm800/FP7UofwUdvSv4gO5BDHcZt7SlZ2GESici/ldjkKCywe8Jwh0wCVRKhP4waGBykXWd2HI3LpjZR5apM5aqFgkdtW+yupYQlDm5gV+YIvB/uONiPrvP19WbXKffBRUyDHSti+wZzRRwmqjgCmmvIfI7WHMS3l6v2CgA4I+rivSpXu2on2cjoRExAKBZuGFQveyz6tQrx2AZz5vGL87oAdUInUHaCal4HtPJs/RFj9ugn66aaM0irnedUMY+0bbECJSpxSGWM529QODW399SyFp9PzAopXKcq5KdWtU9Dxnwi3Swk4twTn0fMOE4jzg3GgViwiM4gXRz8hgPPUyKxbENMcGPxSVQOscYRGLTGjeU+HVHlydnITKvEWxqeVwhyO4IWaj+PNVpdQqOtRmvx7lOfqENoSJjwq+Vw32UTH9YTwJCWd4k0iT1sJVEjK9rRhpRtgdGYZerNtsTKvQKWUuwil9cz6FMyffcjFuzOAy6/uF8CKFQAOIVMj8U9D1NIOWzEj+RFVnzFVa+hm2LgZYYOWYMXYC45p95s5ZeR6UwlMD7fIW6SteYIL3JIcssedY5i/G7c09xkFrvcLPIjz9ksMqZfjEU8xBiGJLL3QANFG4tlD/SoEKWqP6G+lUFuI//TlDt8CY+pz8Unu788qgo+5JNyWhgJhPc8thCXI9y22vgqFxMPF5MB1MRjLiaXq3ouWmvOUo2hRQ5L0CEWwCVcDJ6f5Hiyj3pFUIaiw+vHRoHr/JAMaL7ib79hhqgY0tooHdJkv7B3z/k05ZkDV/tD2zM3pVso39suVj9nw/9wU3G7RUrXqR5DnK+p+LB0ctCJUwrLjD5oV7Q3sfYZppjZVGyntanYwV9kvoe3qvzkGFjUaj9fvhvrT2W5Gq7tdJn6THw=
*/