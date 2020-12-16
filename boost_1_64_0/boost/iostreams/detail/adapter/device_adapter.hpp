/*
 * Defines the class template boost::iostreams::detail::device_adapter,
 * a convenience base class for device adapters.
 *
 * File:        boost/iostreams/detail/adapter/filter_adapter.hpp
 * Date:        Mon Nov 26 14:35:48 MST 2007
 * 
 * Copyright:   2007-2008 CodeRage, LLC
 * Author:      Jonathan Turkanis
 * Contact:     turkanis at coderage dot com
 *
 * Distributed under the Boost Software License, Version 1.0.(See accompanying 
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)
 * 
 * See http://www.boost.org/libs/iostreams for documentation.
 */

#ifndef BOOST_IOSTREAMS_DETAIL_DEVICE_ADAPTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_DEVICE_ADAPTER_HPP_INCLUDED

#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/call_traits.hpp>
#include <boost/iostreams/detail/ios.hpp>
#include <boost/iostreams/operations.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/static_assert.hpp>

namespace boost { namespace iostreams { namespace detail {

template<typename T>
class device_adapter {
private:
    typedef typename detail::value_type<T>::type value_type;
    typedef typename detail::param_type<T>::type param_type;
public:
    explicit device_adapter(param_type t) : t_(t) { }
    T& component() { return t_; }

    void close() 
    {
        detail::close_all(t_);
    }

    void close(BOOST_IOS::openmode which) 
    { 
        iostreams::close(t_, which); 
    }

    bool flush() 
    { 
        return iostreams::flush(t_); 
    }

    template<typename Locale> // Avoid dependency on <locale>
    void imbue(const Locale& loc) { iostreams::imbue(t_, loc); }

    std::streamsize optimal_buffer_size() const 
    { return iostreams::optimal_buffer_size(t_); }
public:
    value_type t_;
};

//----------------------------------------------------------------------------//

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_DEVICE_ADAPTER_HPP_INCLUDED

/* device_adapter.hpp
P4Zz4Cp4JVwj/n8FF8CX4EL4ClwEX4M/hm/AJbBdnHxPGC6DveFyOBQuhWfJ7/ExW7tH1dYu6+y/NfZ2WaMf+37oEdrdrWFN/zbkEJK7gm+IIuORhcj6FYlf8/z/9JKKo2T/z27DXjkZ3x0jg40f0be0gB/C3zj7lbe5x3fLCssrir1jFPrbc0OU7iyrAz39Rea5ZMIzj01kyTjHFer8RPty3oYfslaJDSssqP0Nd3rd1laOcZzCHe6NmSpcXlzqbZWVqvN32zfxVFNgxxvHLtxh3KDCKCour6x/T56rzq+3ryYlY+wE45iFO4yb/GEUum02nazSMc84PoFfPd5Ro0pllhMBcsfSNo3OUjqv283QKVI68/Q4wDB1brvdiberx5Fr7Thlt6SGczVxlGka6Uys2hBit0R09qEzKROdplUHfPEpvqaX8b/LbklxphLlJxBuWjz78xw/6Ytf99j/0Dr96nWWhNMZi85eJ36+xRd77JZonYXxgTQsPtebhiH8bm5pO48i/t9x1PMlLbkHUwBL4WPyrbnL5G9EvasnhLf7RB4kpu9yyo4sKC+PfL1HYIySOombqpP6Xf0G5abqmB6fvMnvVui1A4f9MnXUEYFM4e+74f6Gap+qYfotEYbaImwr9eMepbvDXkT9vZMn/1PtXtZs+zxTOyXcyNfurHsjujFC9I1tVbeR7c753truZdybzu/LeWdpamxzEp5uN7a73UjbHajC7G9sd+74SJvqnze4fl5znbp+pcTHtjJVWBcj9HJ6HnvyzMIZxXq89j4V5lv2Qvqb5+nLCu1ka5l9qvRngTAu4ewFoTbgpLwuUtftih9+az/jqBcXqrSera5bWFlZXjLRPXb5R3Xtzq64lU53RmXaSl48os6/alcS0tPIWOJ2uT2MMDmvr1NIXp3nstlXruP1DxUvn47X55I/ucSrfuzOsUvlsv+owwkeA3xe+c2Q34Gwmql+a2wCOdJE+oXUxeO8/UJb0RlLJYxvg07rxUsxRJebFO9r3tZlXyShjcuuirYDJmOWKq2jTGXrtleo095FnR9pLJMc4lNJfPOSxT5h08VX+exBvuS4MLafRH9Mstija7J4ndf2kyMjceOnldjGL0+hmwSbIMlCxzZhU9gMSUGcuuGDa6V/S23TUB+n1Imjz1/7nTTBDPq8XP/fnc4Z3aevJW5L3wy49e4fcOtT75ZnSX/57zcCbgNC7W42cnzT1Y/q8U3aPG66zevv7aixUKmH7r60urnMQ8WhK7ynG/nxVnBfSmDeeqOfBdop3c/sZrTwZ+xsUx9KeJH3oWlvRdeHom/qQ7XNz9Xq/GzGfYzPKfgP22ca+0jRd7cJ/WzVWZ37p/2w7bNe4snEaZfrm/IOnxKw05nis5s4ptDsxRtoDaa2MFn8PJ/qb6/xvVKm0pYzU87k/4yUEdjpbItkJSXxq9j5CzkupUtKz5TT1e9MpGVSMm5TU3qldEo5EX/ZSc3jE5Jy49OTUn0dk5Ja+JqecTbXTj+CtpQK4xHalPd+oe38dX/byY/neXc/U9vKO6Dckrz3Cz3ffanKw68orf3iRg+s3AbbKVYnm+c/ZWO0v3L7ux3unrFbne9iZUn/5Nd/Ajt219kb7UzTfUPH4Xyl250ybkF47jikhN5LpJ6NVueftc/G31xrFPeRE6y7iLF6ntfX/5PdhjO/tVsa7ydLVd74rJyQOJ9nl9tdrI12StT3lYlvB99XqvkduK8MpV5uSdX3lSrvfcWRDKmPdakBW6GdjbZCkyPoT60dXNtrV0v1J8euD3T3d8vEFtkHiI28j/zWeXbc4ervyqb37hPhuu51OyLv19AN16/pd77nlM6jvMk=
*/