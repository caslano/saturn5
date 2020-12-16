// Boost.Function library - Typeof support
//  Copyright (C) Douglas Gregor 2008
//
//  Use, modification and distribution is subject to the Boost
//  Software License, Version 1.0.  (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org
#ifndef BOOST_FUNCTION_TYPEOF_HPP
#define BOOST_FUNCTION_TYPEOF_HPP
#include <boost/function/function_fwd.hpp>
#include <boost/typeof/typeof.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TYPE(boost::bad_function_call)

#if !defined(BOOST_FUNCTION_NO_FUNCTION_TYPE_SYNTAX)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function, (typename))
#endif

BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function0, (typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function1, (typename)(typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function2, (typename)(typename)(typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function3, 
  (typename)(typename)(typename)(typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function4, 
  (typename)(typename)(typename)(typename)(typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function5, 
  (typename)(typename)(typename)(typename)(typename)(typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function6, 
  (typename)(typename)(typename)(typename)(typename)(typename)(typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function7, 
  (typename)(typename)(typename)(typename)(typename)(typename)(typename)
  (typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function8, 
  (typename)(typename)(typename)(typename)(typename)(typename)(typename)
  (typename)(typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function9, 
  (typename)(typename)(typename)(typename)(typename)(typename)(typename)
  (typename)(typename)(typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::function10, 
  (typename)(typename)(typename)(typename)(typename)(typename)(typename)
  (typename)(typename)(typename)(typename))
#endif

/* function_typeof.hpp
kAS98Er6fjnx+2okzgOOnjqP4ya3eYgn8ZQEcd7okJgUhjARTHJxdaIP9YmCaBBGHwKColaEJAjF8fyiz1u3gWdNwz4vP9j++fnnh4iw6e5zy76TAS1h0u9uihBXhjgV4q4Q50PcA+KeEJ8HcV+IfwFxf9in0Se0Z6ll9N/jB8l6D0p+1BfjgKZwoP94XkaH5HskfIoOMZEBgUACQkGEliHMHxD2HyTcv5lg/yD9cT9O3UXyz4nXiIIJPxolFiKNhJas2QYgVywoFQ7KJAKAzyBNH2D6FBMACxgH/EkjeP7OdoMF/LPWC/Fp9u+ZJ+C090/2bzQsCeSf1r9AFzVt5MtyaTxLCMgBxblM0YYC7XR04rZkXuIkkM7Lu10SvZwEUv3+OxK94gQgvczcfz/+V5LOc2na9PT+I/LYpEJGfiej/2BNmWLPx+px7Zz+dza4bKzOZ7QFLlNGdh2E2iVrs/TY72XslB4LsnFMpt2Q3dLzkjhtdEo60EkJDSBO+1g/vYfSZPnk5wn7ZNoFlfs4SesFJG3f36Yxabul7f2b9E7qB2n7/yaNTvGL+PPbP8g/0X6ZvpfK05zzPre9/zBBB7vaOd3vtJ/2Dq2/RcCp/yBJekfh9vT2PYP0GAmkeldoncFLINVv6pw+Pw7SYyUA9Gnvw/pvJwRYOdDAI0QYCazXFJgqjAajw1jg/GoEM4PZwLjg7OAOYh5ngdhHPxDbGgLOWBGwSHAOioelwTJgm2FbYbthubACWBGsGFYKK4OVw2pgtbB6WAOsDdYN64U9gD2GDcKew0ZhcDgWToKT4VS4OlwTzoJbwe3gDnAe3BvuCw+EB8FD4BHwWHgSfDU8DZ4Jz4LnwPPgRfBD8OPwk/AKeBW8Ft4Ib4a3wNvg3fCH8H74S/gwfAyORxARNAQTYYKwQjgguAg+whvhi1iICEAEIwQIISISkYxIR2QgNiKyELsQuxGFiEOIEkQZohpRj2hBdCC6EL2Ih4hBxBBiBAFHopEUJA3JQRohbZB2SC6Sh/RC+iMDkIHIYGQ0Mh4pQiYjtyKzkbnIQuRRZCmyDFmJbEA2IVuRHchu5APkc+QQchQ5hsSi8CgySh2liWKh2CgTlAvKHeWJmoXyQfmjglBhKCEqDZWO2orahSpAFaGOok6iqlG1qAZUM6oF1Y7qQfWjxlDjKCQajyaiFdFUtCpaE81Gc9BmaF/0QnQQWoBORqejs9G70LvReeh96GJ0CboUXYauQTeim9At6FZ0O7oT/RD9Ej2KxmJIGEWMKoaOYWKMMGYYHoaP8cLMwszB+GH8MYEYASYFk4bJwGRiCjCFmCJMKaYSU4WpxzRj2jA3Md2Y55hhzChmDIPHUrB0LBtrh/XEemN9sL5Yf+xCbAg2GivCpmC3YrOwBdh92HJsFbYO24htxrZg27Cd2B5sP3YAO4xF48g4Kk4Hx8SxcRycFc4Fx8f54vxwAbggXDBOiIvHZeDycftwh3CluGpcDa4O14TrxHXhenCPcYO4IdwIDo3H4ml4Jp6FN8Kb4W3w7vhZ+Dl4H7w/PgAfjI/Ex+OT8Zn4zfhsfD6+CH8UX4pvwN/E9+L78YP4IfwwfgxPIdAJOgQLggOBR5hFWEgIIYQRIgixhCTCakIaIZ2QSdhK2EXIJeQR9hGOEkoI5YRqQi2hhXCT8IDwkDBAeE54SUASFYlUoiaRSeQQTYguRC+iL3EhMYgoIMYSVxM3E7OIu4h5xHxiBbGSWEdsIrYQu4g9xMfEIeIoEStHlFOUY8mZyVnI8eUC5YLlQuSi5URyyXIZcpvlcuR2yxXIlcmVy1XKVck1yPXKPZDrl3suNyw3KgcnIUlkEoVEJ+mQjEg=
*/