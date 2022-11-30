// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_SAFE_COMPARISON_HPP
#define BOOST_HISTOGRAM_DETAIL_SAFE_COMPARISON_HPP

#include <boost/mp11/utility.hpp>
#include <boost/type.hpp>
#include <type_traits>

namespace boost {
namespace histogram {
namespace detail {

template <class T>
auto make_unsigned(const T& t) noexcept {
  static_assert(std::is_integral<T>::value, "");
  return static_cast<std::make_unsigned_t<T>>(t);
}

template <class T>
using number_category =
    mp11::mp_if<std::is_integral<T>,
                mp11::mp_if<std::is_signed<T>, type<int>, type<unsigned>>, type<void>>;

// version of std::equal_to<> which handles signed and unsigned integers correctly
struct safe_equal {
  template <class T, class U>
  bool operator()(const T& t, const U& u) const noexcept {
    return impl(number_category<T>{}, number_category<U>{}, t, u);
  }

  template <class C1, class C2, class T, class U>
  bool impl(C1, C2, const T& t, const U& u) const noexcept {
    return t == u;
  }

  template <class T, class U>
  bool impl(type<int>, type<unsigned>, const T& t, const U& u) const noexcept {
    return t >= 0 && make_unsigned(t) == u;
  }

  template <class T, class U>
  bool impl(type<unsigned>, type<int>, const T& t, const U& u) const noexcept {
    return impl(type<int>{}, type<unsigned>{}, u, t);
  }
};

// version of std::less<> which handles signed and unsigned integers correctly
struct safe_less {
  template <class T, class U>
  bool operator()(const T& t, const U& u) const noexcept {
    return impl(number_category<T>{}, number_category<U>{}, t, u);
  }

  template <class C1, class C2, class T, class U>
  bool impl(C1, C2, const T& t, const U& u) const noexcept {
    return t < u;
  }

  template <class T, class U>
  bool impl(type<int>, type<unsigned>, const T& t, const U& u) const noexcept {
    return t < 0 || make_unsigned(t) < u;
  }

  template <class T, class U>
  bool impl(type<unsigned>, type<int>, const T& t, const U& u) const noexcept {
    return 0 < u && t < make_unsigned(u);
  }
};

// version of std::greater<> which handles signed and unsigned integers correctly
struct safe_greater {
  template <class T, class U>
  bool operator()(const T& t, const U& u) const noexcept {
    return safe_less()(u, t);
  }
};

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* safe_comparison.hpp
I9Ng5ykwvrJEIdwqTj4yA6ZZDO4/EoV4CA6OrrwolnAbchEH3Dl9iKV1uihVFb9QTXWjbmM+fhBgf2yVEnhyee762K3xP2zx0667ephuSY2wJyk0Gv32fEpuoVPU3bqmjNA3iHfVm9OnFdY5wkreW5C/sYOmiaaHf94KYwT+hjc9UTpQ0geK72LRPpIfOPbJuJAXR3Cu0fpDdQT0qVF/P261HaaEJejoMWpnxW2qBrsLaTIzle4E87hrrTrimQ1fNGgOTRr9Jn4mxwrJm+yghEIR57GVMHN4RhYHCRK6MHUoLHOPPCphXg08pAfp7g2mNbiKjuRuM5+YiEt53cojo+iOHfLB3qjz/gszN8zs2R9PeLs/ET4R6EO6UUqjmK2VtRZVGuwtvRP2eVqGP/lXUTCBJYXMcFk6VCUyGL0kJdtVpoJS3iiml5nrKMj3xOQqCkQoLxKNvSrHx1lVHkeorsLC4ihcQbPXCQe77n3ps3D3YPdgmKKqeCLKy4R6obsvE8FQQgBkg4QcTyve+8IGOm0tuLivLe9q0sxwXceL08NYROgxHfejYYWuKzVyR4N5WLNs2KAwRVTaqQrB++kC86/FKvfBxqHEE/CpwW8L/M5jEQxN1qTBKkGKvZ2o4GqhaSCEJe+mGcd4RouKuQbf8L+SykOvlcp4muhwJAXICRgbiHaR6gPe3ko8T0h1Vh1vjdL60pjnRaL8Go0kNLSHVKw1UkON8zNjzrI+zSnG/bvpDEt3kkCjPYcymL/QP9jegZTmuULaE/fdQ9CXC7dr7DW7y0WeguN0tAwamE9BykMRClmS3VUchRnrxBD//DfwCsg4uwvvSBaNFyow8kkM8ZsBDYf60YNgUVrNfnIUWTS+5VoXvijGGuRoAi+PkX8hvqykl5iLb1GJfHmcbKfx5RnwMvzFhuMUpm8xCQEwzxvgaXaXm4zD5pMmDCZhsJMGFcRvLv4BfAO0ayIYzWWbTOOJ+U5haL493+wrI+gj0uHh/7tB2CsoITJXoDDG6bOZcOnnZWtoTmwxkVFBALOenxZ41PbvP2H73/7F7V9YqP0gRUNpgT6i0MnA2pN3Iu0dSikNIfSJ37+YttwwbPYQtIe5UhtgPwSCK44amrvftr95qIztPUNeY2h0UBzRXh2Vd6MJiRahbYpveorU3TNgFcIWPA2DJ0qdD7/1U1I8Zbe4+8Uh/KshohkkeAUVqU25Aia+PokVjlftMTUN/Jtf22xVKMdv+hxgY8FczhoVo5fqs3jXGrJfx9wFwUpn+t5SSlqgyvS9EqVJYaXqkP+HYgXtWUxFHj+/WVgOWODx9KjqOwrxYYv/3nwye5bR+3/V1H08O4cCsoUstShvQJlJBQyNBYbrTggD9H9ZSwF70HhCKhiF/v2zFbSuL0cYZhJbvop2GCW1UVxBBkEoLJpjSXnyvIEGtsVS4q2S8SYrXHy7WVC1xMHqqvTpbK5qMlja6KvkyZpfescRU99p5qWoKOJLVxwR2459ZDP6R9hH3VhgfD4R31/jncfRv4kN8Xt+hTTnRpqrPFS9DekrPYlRhP8d/O+fEP6Il1rBsIXedVITDITcPcwwFXtylixSqFMtE56BJpqJgC0qbDA/X9so9GDB++YxgXZ5U+QDtOvXWNiU1xeWXVIO8zkorm6y2d2YyM9MbRdHaUdMugZ1BLij0SvJnxq/wAmeB8D78moi33J2hgAvZ/EjhN8HRgi/z1wzQvi10BQh/VLcIkzPekWaN4vUdxEK+Q39UDktktP4T/k5xfC0Spr3M3Vm2bgVLf8/f4ZF3XlFbfIjckjAxE9aRAwDv+2eIKGJCCL83scVDOGmYZ97+BPpI5gs+ly8xDIdEyr+W1xy5mmiQDSKxWJQR8ugS1H2uKsrJFcDril++EPDaCtQD/NnY6pxFBjo+gz/q+LPPXLEIK1cCKMbD6fRWwo9MxqzQyXe1VtElt35z01RYdO681m/IzF5hUtYCJ43W1gIisQr80GWUb4hPl9FkiAAtehDUmz6+dlH1KJC0HX4eSC/9eL0xAQ2/8PHhb9qrvknv5bNCx7Bx5nNv3q4cPOAaYmgPXzvBxhAF43fN71gCiDlbbYc7lihd3bRLc9OUfF3p/yV6+9/CvCLckDOgmdM8BUMAK4DbwCetYO/fDecLuHhoKLjRgu/sdY4HO8TdPR9ZYlhpPoWSA3cEN8HzJsiwZgauD2WXkXI/BX0NmCFhKnGS8kgyPzU3H2NKO97u9tQJ7JcTQ3Jlnm2wa6vCUZs2g7BBfyW0Zxc9H7Rbl1oKrUACyz003wxtLwWvgCVTmRnxLAYXW+5k7KH7zbYtU7BqE2nsU72kHdayethoKFwD1+ZY3gtXKgHZew9LBmlBxP/fEHYwj4hvo7iKq17TGptqZHzGyjGtS/GL1wnXeBnWQrUQNjk+CGSvkUzTaV2Tiaa+RhKdvj4954yqSZAgmDNeNNx8cWtluOi3OsroGIdf7ne9IGrsCmPmhy+xTOoi3vCUneSXMD6c9L1TKf+dWLryPwitRuZpsSRXrfXnbZxC3a/dBP1Q8xye+neqXCMv2fRftRqVnXAn/Awa4TCFw23wBvkf8l8UVjYh/QubYIqPSih7E5+8dsb9xtO+6HepRsTvXc3wTKlyOl7+KNQ5BBmGsQFO552YaXdMlsV8fgrWkcuyRC5rOg3Hag04r1z9uqZr/Quzu/78X5jbf373X1617C3G23Y2SQ2W+mt/1Qr2c2X3LDf0DCtBvethDF1fYqJBQy2Fx4VpavROf4jHvtnP/pG9PQtn5AdMpYpjXqDwuYqle/07PQ+/DqUuPrcIzwChXpQyhwPUuYekDInYXKE2cralosqWJe7ZDebXZ5Y0/oR6/qITU2UbNMi2+oHilj9gNY7ZyDCdkGHxUbUv7Z+AEj1ku31nFKYz2D1X1E0e9biKi/ZgYkPdig972RK4E+HS+PpX/qLNk17YQocCzJfsVKGWSt4ye6ed2QGgfQ0qDLxdRYpNysVafwKqAT4gSK0uU68a79RML2APV+JNmZ8B5afCN/Hrzfx/cTdo+H7k/VjwPfv1/818K2cIr6VxwHfqzecGr73PObA98/uOCG+AdmrCyAbY+cH6DqqemuCHcY0YZgwLH3m9vE7YLFub2iaD8sQ4/+b2abZeFyfipeW5zT2I6XkT6gigxH0tisdQfTkK9eXzOBHYcLWhCsuW1KemcLCOGD4wcBU/AwAXF+iUENwRCzPvlEM7SFviLJdKD4Wk7/6sv0GnWK3O6Kfm6H2pXyW3axYItoX9+03LDsLQV//0jrSheoJsnvDbIKYFceld3lYvQdmwShbMflCtafP2zPOhYnwOop7ezXE7Obj6G6L/6YGAMjKfZq+YJhPv3M/Ck1b3NXfkBZoPJFKyTamqas+Ng4bxqo3MExDQtdUo2wltIxD/ykaee3gBkxZL9KM6AA1bJhLO5dIW4vFjDL/ZDT/y3ZxFdYApjH5XYTPfZr4VocRB9oi/5kFn65Z8DujrBwKFxhMRsVVYbS6O1wJo6wTnsWNsgrxJwh/euesNwlo1hEACr+uxynnE5A9AT3ZqQnJ01kfRUj++fP50bfIfnNteEJ33/bSYcBZ2sPCHo3/9Cnp7Zn8Yv03R4wR9p6wc2UmsVK0bG326OGA3uxnYT/Zd47+PkDvMd6pqzZ4fm3AVUtmc7XOIw8QmgLP9EhQLIm1tW4ArjYoMxDUqmxg+oBe69cjgX5W62ER1fqa83c0bP6OW5/M93ccKLS+RDpCyoweFEkIUXVAbk6LyHhHnLSf//oIChShNWG3iLHsfWhzT9+aZkzIgSovn0sgUm/2ZSZE+G2Pic7jvl5P8dq4u/sdvCtsVreHxYCK2ebpO/TmAB5Q9LCfbbOpJUR+ELTPGLlfU1IbEAQOYg6KLdsbSGdOmRPxanJRKMgVBJTynyE4axvcADGC2aBOb/B0o+eSj+qEfekzNL79F0BEzT4AtWSHgHDQwxIePe6BCnpYXRvGWZBAj2NhdbAECIU1q3bo2+3gq3L9xzGe7dsJtsKH4Xt932eaD55cqWu+NZ6LWaOvtl1v9NkSQrNGFaoEAGPVby8XqUuaQa6NQQse9gZ7T1z47xKhjuBRY6DkiL7C44qobJ6PrVDxwX/p83zT4al6fsTHagLQS8/O9rZMKWapa3Rkn0b+szjk7tkf93bPAS7AMgHU0V/pFtrc7GHFe/8lbgwq473vAnxYT2ZeZ8G/2a6iosxEVq8gJ5qA78LKPzwKLDEzAav1HBqPNwQqbATq429+WqHq9f7kJmAr/9fb18BHVV37zsdJMkDkDDjgqLnPXBlvo4kmOukjMKEGkkwCJsNkkpnBEhJefwhpnComZ4BqwMBkNGc2o15vRG1trX3e3qf90Nf6gNZWM4nJJKAVpB8g2gv2wxNCFGsNEArnrrX2mclMErn+7v39nj/JnH3O/vjvtdfan2uvpa7rD527ifny6v3yLTKsDGVX3qvYk4rh38DPkiarGC406MirT6tOCbwi6OTKImgc6JwHBdN1zGlhPhMsIsug7QYFM2M7LMxlqpLhJw4RTEA6ELYV4V4ZHibE8B4cDHymbuGqKTHhrWUFRuqDz5ATcsByYFy0Imyi71SUVo4OUz+Ek+yq0LlZmMfbQYH1jy5YQtdLt5sc/R1kwofMmlKB86ZkOEd1WuJO4T74PqLgesVtY9UF4XfEnr5LB0IfmIHKPbFLw4sOGg5DM2qh0EkTBs3JoGA4HCoBrCbxiV7DoW6LiMB8OVrNIh6BxbstRAVXDlYvsjKDatidbUYq+nIQUsSTSagwphNjahWNrMzCeP+FqjZpuZTLTZBLNuvX8nHmEMHdwAnsbelLkTJLkjbwkCBPTmTlAkzgtCAKNoQVWlEQ7pWw2dFakbtO+V8/pQ0L4AZNEoGWlUjLZ+gKZBF7CNGFRkyxk9k7YzioOfq323hFAPE1oXOZ27NIl27UbH8HQjCdMh5hfbjSjp3InDPEnAEo0RgazmUx+zuvXwcxz55lg1qT5R8wvq3c/He0tY7Rrhb31d7GBpVr8U1t0c6Tqgr94xUQ0jh3/uMJuKEdQqUY/i1Zbs/hTdlF152RFrlAiBswreNQezuDzC0OZ3ZwMRLg/gKY4uU4Ylus+TE30MEY44RY838TObMB5SAO1ZSIDUm3YTIP0D03YlnKmqB5rdi8Tbll5UBWuSkXAbgtMPBDgazf0df2KL0BJpRQsrAsaBUsrrLIeNjjVk6/nCwLmzfXUWcJzp2k/0qk+A5hpRj+aaJ6yLhdeKkWW3+yPpC6DovJccR5GXEq4/dQRvfLKfW5MJGszznJxly5VKUccW/ObGCWXOTZHBMKVvg4DjLPjmaQBnSSYagaWERtERYBVIsDyW5IFhE+HpwNhADsazn2tWL4Z4kMbNi7fZdj1+y9fwH8Qy+l4HfMiN/238R/10sp+LMA/CYOflPwrmTKBpLk7FCvAZoxC6C8fJ6gMF92tNrgOLB1aaS2KKUj0IQvUnsrl7xWXRkyLjCKMv6TSVEj5ofPYbxwN6CsxUwrccq2OO6kXV+uZdFPQwHqCQWvdzTaLA/mhC4IsCBYgJ0/RJG9Vq37xziJwYLVCsGF4WFp4XM8WsooER4OXsNcEvxcGT4udn0fUFASsetJMvSBYl0fzS7zqZboUzsLzTDFRdtNGaFzRqIQxsXmREPz8EHsuoMe9MG1jqPBOT7l+n+jndLRpVxefcp9P8AX5tAFY/CfmK+GOSs2xivcl7BvqWE7KqI1sy6Rwp29F835Lzr46YtAjppzGjnErjE8mL0AQ98onhM6reHeB2dDxanHwUHPIIaj1FNZIt4iaNhEL23ig1DEeyu+4UNGxHtbWv/MO2evHcPY0/Ju1muCbhbeJMe1iHfWZO+fzHd2ar5zEvnCYDSa6MR8Z1M7sWoMDSj3ndWqsSPj7FGcnbkszWvtveHhJrGH2psWIZcuIgdorECM8FxvYri/RA05Zb4twXwD5hhaf4GEQ1UnmN8IIfUm6caQWinZQupK6bqQula6JqRukhaE1Psk804VW1QyNVO2Tf2szAQsOQdEJM+t+my4Pw0yurwCX8L0wu3RXkKfVFZGL1157jrtJcpMyQzJfXl1Wjp7L5QKQ2xz3EmnXE3VoRMX+7WyU+br5YKXKY4RmKuNhMdwhbWuP38A1TzLoVwr8pvI5rD6Im+dR1GZoBudD5wQvJIZ2R1FXpBs9kMuauVFPmbnmqZTXKqychObYxxoNr4ll5ua2IA8J4WmIPpsVc3hE/KKUraiot5nH98oS9WX4B3x6zE/u78iwbM0a3yR7SIjGUJZ7IRB3Nf9OIiOHEElIAg8RoHdPNBDgcco0LkHAs3yig65LSC3NcptEt28ltta5LbqJnnFNnnFelKZxaMZVwfzBeq97J5tfka2OEhzzIV2fC1sR0H02QmgovGA48iWufm/39mXqSc3ONZRU2LJEWm4Ue1usM2NWG6EH9HxE1JA+LkBIrZlxGDdb2A+aUkD2TvP2ZKNs8jRTK2/9pVEGm2i8VBJzk1iGI13QHBuSeNNqhj+FoauWXq1SDapIl/Vr1h6p14Mh7ArjRlWkH3xyJ365SuWXhMsTzwsTTzcmnjISzxcl3hYmHi4IvEgON5ue4Udxuohasdvo49egkrvuMaBqJ2b2ant+ZHG2WrEMrsb8GEtma940SHmLBP3CW4HEGLLbLUGvR/epNJ5UY5D2WpgA83r1qYd2QJZYT5SH8kx4Uw+GyhmjBnfWnrEH92PBYvhx7GqdfqlbqjpQ6TbZoDKRtx6gFq2fOmR4JqU55qU57KU5+KU57yU55yUZ3PKs+CItz2TH88wUJdr7IDWlxwx+Z7NW+Y0r2Oxtf3EPVCXftIzymaVBT4/2rQYJXczzCuxdaWsNpD/LvMWRHvMyDD5xxwH2u5l20sS/lKKsyZFJLiZeQOstjH/TP4hWJNBMFgj1zay2grZG4ha7hP3rboUOmVwDLUJ+UMw4Rt2bZRnB0eYt4ydiVpWfM5n41FUe0JXflIzq5WwiO0lRpgH1rGD7Kiio6mfZAQ8aPxrwijXSm25rBKAlESLTeLeTFa7Rq6sPnJC3OvS22OLKhsgtHMCGb59LvPq2Aq+euLKRyQ/pGqbzcqzvaHeC8uwO/b5cUsLn9rJ/iArl6BX2WqpV3pxnIEQOoMVu8gd0x0BQAOR5DsC7I5GVh+Il0s6Ene9ZEK1UlwN5R8KD8v1klwe6Mhi9SXGw1Djd1p1MOvz1Ctzvo8KkgFmlCE9LURhxgrDYnI5ugqWo3wxOsJ7qbdmWoy2JBajp+SWaYtRWIq6TbLbDJ0gnw2TqdT6Riy3vCD/wM1IIceQuIs03t4BlOUlRpqnt+rq3PXKpuf+/2MMd5Fd73X23rV34ulaDszNz7D2xvA4hzdIFkPqA/bhkCrAUi3/d3UegPrL7wHU8oBc3siMgFDJOUMXbpfjBGo+jjECjjHQ+DC8GO7s52966E20Qqefdt5aRwJj9vntaLXFDMySwyqlZcRSi7zKj5ElK5El+CsTTp0+02ZC+AvS2LaaVVYDZyI7B4uPnABuFffWzDMQg6LEVFZvZMLyRX8F6dgoC22sshhEEQKLhsR9pasoccVG
*/