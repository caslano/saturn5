// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2005-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Contains implementations of get, read, put, write and seek which
// check a device's mode at runtime instead of compile time.

#ifndef BOOST_IOSTREAMS_DETAIL_CHECKED_OPERATIONS_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CHECKED_OPERATIONS_HPP_INCLUDED

#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/dispatch.hpp>
#include <boost/iostreams/detail/error.hpp>
#include <boost/iostreams/detail/config/unreachable_return.hpp>
#include <boost/iostreams/get.hpp>
#include <boost/iostreams/put.hpp>
#include <boost/iostreams/read.hpp>
#include <boost/iostreams/seek.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/iostreams/write.hpp>
#include <boost/throw_exception.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp>  // MSVC.

namespace boost { namespace iostreams {

namespace detail {

template<typename T> 
struct read_write_if_impl;

template<typename T> 
struct seek_if_impl;

} // End namespace detail.

template<typename T>
typename int_type_of<T>::type get_if(T& t)
{ 
    typedef typename detail::dispatch<T, input, output>::type tag;
    return detail::read_write_if_impl<tag>::get(t);
}

template<typename T>
inline std::streamsize
read_if(T& t, typename char_type_of<T>::type* s, std::streamsize n)
{ 
    typedef typename detail::dispatch<T, input, output>::type tag;
    return detail::read_write_if_impl<tag>::read(t, s, n);
}

template<typename T>
bool put_if(T& t, typename char_type_of<T>::type c)
{ 
    typedef typename detail::dispatch<T, output, input>::type tag;
    return detail::read_write_if_impl<tag>::put(t, c);
}

template<typename T>
inline std::streamsize write_if
    (T& t, const typename char_type_of<T>::type* s, std::streamsize n)
{ 
    typedef typename detail::dispatch<T, output, input>::type tag;
    return detail::read_write_if_impl<tag>::write(t, s, n);
}

template<typename T>
inline std::streampos
seek_if( T& t, stream_offset off, BOOST_IOS::seekdir way, 
         BOOST_IOS::openmode which = BOOST_IOS::in | BOOST_IOS::out )
{ 
    using namespace detail;
    typedef typename dispatch<T, random_access, any_tag>::type tag;
    return seek_if_impl<tag>::seek(t, off, way, which);
}

namespace detail {

//------------------Specializations of read_write_if_impl---------------------//

template<>
struct read_write_if_impl<input> {
    template<typename T>
    static typename int_type_of<T>::type get(T& t)
    { return iostreams::get(t); }

    template<typename T>
    static std::streamsize
    read(T& t, typename char_type_of<T>::type* s, std::streamsize n)
    { return iostreams::read(t, s, n); }

    template<typename T>
    static bool put(T&, typename char_type_of<T>::type)
    { boost::throw_exception(cant_write());
      BOOST_IOSTREAMS_UNREACHABLE_RETURN(false) }

    template<typename T>
    static std::streamsize 
    write(T&, const typename char_type_of<T>::type*, std::streamsize)
    { boost::throw_exception(cant_write());
      BOOST_IOSTREAMS_UNREACHABLE_RETURN(0) }
};

template<>
struct read_write_if_impl<output> {
    template<typename T>
    static typename int_type_of<T>::type get(T&)
    { boost::throw_exception(cant_read());
      BOOST_IOSTREAMS_UNREACHABLE_RETURN(0) }

    template<typename T>
    static std::streamsize
    read(T&, typename char_type_of<T>::type*, std::streamsize)
    { boost::throw_exception(cant_read());
      BOOST_IOSTREAMS_UNREACHABLE_RETURN(0) }

    template<typename T>
    static bool put(T& t, typename char_type_of<T>::type c)
    { return iostreams::put(t, c); }

    template<typename T>
    static std::streamsize 
    write( T& t, const typename char_type_of<T>::type* s, 
           std::streamsize n )
    { return iostreams::write(t, s, n); }
};

//------------------Specializations of seek_if_impl---------------------------//

template<>
struct seek_if_impl<random_access> {
    template<typename T>
    static std::streampos 
    seek( T& t, stream_offset off, BOOST_IOS::seekdir way, 
          BOOST_IOS::openmode which )
    { return iostreams::seek(t, off, way, which); }
};

template<>
struct seek_if_impl<any_tag> {
    template<typename T>
    static std::streampos 
    seek(T&, stream_offset, BOOST_IOS::seekdir, BOOST_IOS::openmode)
    { boost::throw_exception(cant_seek());
      BOOST_IOSTREAMS_UNREACHABLE_RETURN(std::streampos()) }
};

} // End namespace detail.

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>  // MSVC.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CHECKED_OPERATIONS_HPP_INCLUDED

/* checked_operations.hpp
41Ntkd7B9utO2nS8mzZN76FNzsW0XXwvbWkuAWYB76PNSL/B9YbAYQw/DpQHMmjT1qAN2xTgctqSfZThV9IW5YO0RfkQ8CTaUD6VNpXPoK3koYqt5IEgP+NtxXi9oN6M93HGuwoYR5vQybTxbNWHCvofp6kPT9P/M7SpvIY2lZ+lPNYCx/Ke9YFrtKCPmvrwghHQr/WU36vA8cCNwBnATcD5tJF5PXAL8B7ayLyPNjIrge8B19JWZjVtZb7O54HxGNcRATtrxmNbmdRttMX6IeWynf3WDmA67zvx3rYNynCv0vSDb1Nv32M9e5/1bDf1eCv1eBvHaR8CT+L9yby/jHyzgLuAxfRfaqYHOJf3X3O8Xcf0NOH+IMseLm3N2nzGR5HxJSp8O0L40m0+UIR8GRHyDY6QLytCvpx6+IYrfP4I+coj5KuIkK8yQr6qevgyFL7qCPlqIuSrjZCvLkI+Y2/DfAtBieRbralfu9lO72U7/TFtHn8BNPlqgRNoa3gy8ADwXtpCXka++2k7+RHaTn6cz5+gzeIq3n/NOeU6pudCjnu6gYa7uPaS7Ug3tuc9aTu9F3AgbdSPoo36icznJODJQD+wL/AG2qq/GdgfuIg26RfTZv1DwMHAVTzD4FngMOAL1JNqnmmwhWcavMezDHYDzwPuAY4CHgCOBn4FPB/4Lc82+I5nG3hcgfBbAMcBWwPHA9sCJwDbAy8CZgAvBp4NvAQ4DHgG8BzejwSeBBzD+/OB3YFZvIdcMf/AuUvOy+aAOoC8lGs25ZrDcs0FtqGN9DNpk30w8HLgCNpGHwmcxX7FT3lfAcwFFtNGfSmwhDbar6aN9gW00X4TcC7lfhVwOW3kP0ob9H8Azmc5XAtcAyynrfrrgK8Ab+DZDTcBNwNvBr4FXAj8AHgry2URcC/wt8B9wNuAaZ6jtp5f3O5t0N7z+Ble2+bzVvDvwfPvgaG2n+eAbxmoeoa3QTvQKTu8/zVb0AMRt84e9CQ8L8fvUuASEG1D23ah1+BZHXAHMJx96INw09mI9u70/k/aiU7b6Y3YVrRqJzpjp/cn24oeD7+loGWgalAt6AgofZfXGAnKAy0ArQBtBO0HeXd7je6gMSA/aAmoCrQDZOyBnWjQGFApaAnoRdAe0BFQ+kdeYxBoEqgctBJUAzoMarvXawwG5YDm7I3amo5e0St6Ra/oFb2iV/SKXtErekWv/5frP2T/v7Bg8s9j/39NF3yTG2ouVZhRNOvKIph6CNj//4sPc37WWf7uQN7y+M1lCuhZ+Kt8JcHgPu5huYVTsocY6hreXP0ek1ccth6caw21fNN06wpVPtoLG2Lb/NgibqeGtfmVAnxJeIbaa1uNaln3Z++zr1VselUB9wEbOs+da0NpWyI3xPZEZojtiWmBtcKU9TJOITR3IZ/AGOA6yDq9OljWQ4NkPVkna/hxyNpe7zhc3LbpZA9/kcneyTdba5eOfPWWwzThWWuXQ/p62m+zy3XGbOGnTfA5wr9ScZ9m2+LxAU8W96+NL7g2mGHYNtT7i/thxW2ovc64j7j9DRblYsSepLnurs4DEjvP5bdY68v/SnuS/XEfb+sKiTrzNehviu7UkCx7DYruaG0lf1Nt2WgI1avJDeqVeZ9o388Osq9T1TQQkbnmKQH4W+CL5t7D9cF6NqWwIL+oVOz+BusR5fyQ8Ge5NPrHsFT9GKrTN/BFpm9OvjlOfdPy5TrtHGr5yrR2DMmn6MpoW1euF7crXbNciq7SXp5lY6RceOa4/K6m9daBd4Wvi8uqA9+9GloHaAeRNutrhb+1S6fftzJdQX5POVp/bhL3q12mfld6oZMxtn4/G6rfo3CfVI9+HwY=
*/