// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_POSIX_COMPARE_HANDLES_HPP_
#define BOOST_PROCESS_DETAIL_POSIX_COMPARE_HANDLES_HPP_


#include <boost/process/detail/config.hpp>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

namespace boost { namespace process { namespace detail { namespace posix {


inline bool compare_handles(int lhs, int rhs)
{

    if ((lhs == -1) || (rhs == -1))
        return false;

    if (lhs == rhs)
        return true;

    struct stat stat1, stat2;
    if(fstat(lhs, &stat1) < 0) ::boost::process::detail::throw_last_error("fstat() failed");
    if(fstat(rhs, &stat2) < 0) ::boost::process::detail::throw_last_error("fstat() failed");
    
    return (stat1.st_dev == stat2.st_dev) && (stat1.st_ino == stat2.st_ino);   
}





}}}}



#endif /* BOOST_PROCESS_DETAIL_POSIX_COMPARE_HANDLES_HPP_ */

/* compare_handles.hpp
tgWozCtn53Uz38Yj8zRc2zj+7bk5jVsGdMWr634dTt1hEq69t4bfoet36Go7Ud3iwlLHHgkVovMp78nTJYxERxiJrmHweZZF8JWOtnaD6MxlhfsICSPFEUZKRBjlUZKOwpJgskW/qUO/aUQeD0seuWZUt4VDt0WEbjNp49PyZxJwqrbxq8X9GXJ3BuvYeoTauub7Le4jd0bMU7LPMh0pOmkyL6e5hJ1fmT+jsNI5R2WM6DRiXoeX9Uxe5xwis0fK+aLj83xuRWs5ajojrtklopdN/G3NPKI3VZZAK4ycJyN5gQtFp5qyS3fLn8zPWBrNu1wa0BoS7fd0kWkUi5/6gXkU6mc1ftYG/MQOtSLnUaSqzk501gV0Ei5u6Pc1NHq/itD7AL0bA3oxi/f74+rZehFx+uNVL+7ijpE6HbATjHWT9i3rtf8ImJv5ewPmFj0PIuoH51VEJw0qCc4/qKiw5xosTNS5ApY914BrEhnXpMr8cFhi+JryRDNPwVxjIk8xcr1uVN4Uyvpu+1qQsFvAwxI2bV77n4Ha/xxsaMlvsA9dZbeWhFMS2f+USwcUvBIi+yC7vX0p/nZaDa0N5p7QvTQg6+TWTxGPfa11lX5KYjDzqhaLe4bva289q6Ev3q3/Iozj77/QPVb/5dpXoe/eVzmu1+tFp4lvH/uEfO2NceuvCOfE+qvykuPvr1Q3cq6hhHmJuHXxHfb6mZGYINdtVD2+SVAYGwPXQ5Tf74mRS/dnb3Dpul23d6ofi7ZyK358/RNGxET52ia0j/H6GiVkyf+dkDTmr2aYpgndEgpj4nzR/J2Y0CHhlITsoBY6zZGjh04H/m8e0HSEk5wwLOGsANFMiYlC2jnG669XL6FBDCfSxDTzeYPKCE9uTEinBmLA0ig55mx/fA+uVdLfkaTelkL69TreBO/Q/T/uxGzSPUB8un/IXfx9N+ZmddscobskQv9XKr8HsyXFno+VkmTHdy/mFo3/1/A+/ZuwXO4NXDtwZ5nUoumDJ8l184pVn9XDadoHr5f6/MQbz3LNX3h7W3u9Kfg38/J6Z/S3x2I3l+n4Uv1eXh6we0W/V/DeU1VVUWm10vm6wbATfQusbNal5lrtaQ37icm5N5DzHvGkpO9JTx6rRV3icO5nFBHHEVI9w3qSmQWrPF9Z5EP039M4pjvGk/Uljna18pCs43x6wvJ+DM+cY/dAWG+3UDdH+V4sYdUP3RekTbejTW8NXAfxGVbtuYLJiXHu/f2Zznl0qyVNP9zfd22JTPq2/0x/30efpXYE/tc9CnyY1ZgzSdsWycPimYUyLZf/Ztnzy2lbuAXErmNN/Np91espAd3KqrKKQte+2qnbLFXClZhc+mp0Xfo1bRcPituVVhtSUIhJRofrlZ/EnTe9qsb0gY+K7jKexaOt8zCO+bazSh39+P2id7XVgf9nY0LjgisCzxqYKzGrMH2TsMO5Kqed8L/987uMC7pfYOYlmnbyvNSRlKtpJ5QfMsmDaSeUEzIpJ6nLbnrv7tTIkl9PjBfTA5NNXY6VuBbPKqyR5+LIe7WZTzxD9Jq51Slh2PWUjoD7cvUMx9zdfHFv7VbHtl9zz5S2bJ49J4h7F9c6x29knZu+YKK4dTbX6Ty77N3HZD9yTZIvZJIvLWu9zjS9lLVZkzH25GCgB1A6RahnJAbLOvjWSxZlRK7JsPfO2yW62/xJ3vbW8z6/9amvQdzRhCTX8idc9/0XtSx2iPuZHrfyV7/2c0HE81UyvGOu7AdodcRHW63TThUBWa5/s6e9dYUv2nrE18Ta63s8dl1CQytN951rMy+gc5WnDbO4niO0eM8iM3/7xUoP/7f1plsHZe+98k+PHu0=
*/