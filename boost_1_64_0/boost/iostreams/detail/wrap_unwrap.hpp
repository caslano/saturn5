// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_WRAP_UNWRAP_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_WRAP_UNWRAP_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <boost/config.hpp>                             // SFINAE, MSVC.
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/detail/enable_if_stream.hpp>
#include <boost/iostreams/traits_fwd.hpp>               // is_std_io.
#include <boost/mpl/bool.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/if.hpp>
#include <boost/ref.hpp>

namespace boost { namespace iostreams { namespace detail {
                    
//------------------Definition of wrap/unwrap traits--------------------------//

template<typename T>
struct wrapped_type 
    : mpl::if_<is_std_io<T>, reference_wrapper<T>, T>
    { };

template<typename T>
struct unwrapped_type 
    : unwrap_reference<T>
    { };

template<typename T>
struct unwrap_ios 
    : mpl::eval_if<
          is_std_io<T>, 
          unwrap_reference<T>, 
          mpl::identity<T>
      >
    { };

//------------------Definition of wrap----------------------------------------//

#ifndef BOOST_NO_SFINAE //----------------------------------------------------//
    template<typename T>
    inline T wrap(const T& t BOOST_IOSTREAMS_DISABLE_IF_STREAM(T)) 
    { return t; }

    template<typename T>
    inline typename wrapped_type<T>::type
    wrap(T& t BOOST_IOSTREAMS_ENABLE_IF_STREAM(T)) { return boost::ref(t); }
#else // #ifndef BOOST_NO_SFINAE //-------------------------------------------//
    template<typename T>
    inline typename wrapped_type<T>::type // BCC 5.x needs namespace qualification.
    wrap_impl(const T& t, mpl::true_) { return boost::ref(const_cast<T&>(t)); }

    template<typename T>
    inline typename wrapped_type<T>::type // BCC 5.x needs namespace qualification.
    wrap_impl(T& t, mpl::true_) { return boost::ref(t); }

    template<typename T>
    inline typename wrapped_type<T>::type 
    wrap_impl(const T& t, mpl::false_) { return t; }

    template<typename T>
    inline typename wrapped_type<T>::type 
    wrap_impl(T& t, mpl::false_) { return t; }

    template<typename T>
    inline typename wrapped_type<T>::type 
    wrap(const T& t) { return wrap_impl(t, is_std_io<T>()); }

    template<typename T>
    inline typename wrapped_type<T>::type 
    wrap(T& t) { return wrap_impl(t, is_std_io<T>()); }
#endif // #ifndef BOOST_NO_SFINAE //------------------------------------------//

//------------------Definition of unwrap--------------------------------------//

template<typename T>
typename unwrapped_type<T>::type& 
unwrap(const reference_wrapper<T>& ref) { return ref.get(); }

template<typename T>
typename unwrapped_type<T>::type& unwrap(T& t) { return t; }

template<typename T>
const typename unwrapped_type<T>::type& unwrap(const T& t) { return t; }

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_WRAP_UNWRAP_HPP_INCLUDED

/* wrap_unwrap.hpp
SiPLNSNofTXXk7L+rqS3oGVoeqfhPy0ovQOdESSqZWkpp+v7zwji5H5mSsgMvdbMbmh6rkX1V3lU2nB+4q/xdb9U51FwfhwyxHEOunmeOOoqL3W+5DBxxb+u8zdkHL7O533c+DpfYqjzXDOkzg+QNNe2Ck1zJWEM9aZ5dsXUSNM71FXXH/XvY6gsDzdG6EnrvijKscRQ17kebup6QenckhWazjL853vSKU06ojqYH0Wbzj+CNl0aQZv+BG6xw605OXprSMxrnMKvNTKvfQq3pij8mp/Baq1R9Zrp725Iuvij4o33Xxi/1dcx/Fom85qi8GuQzGuuwq8pMq+5Crc2Kfo1P5/q76H4n103wxuQ3a6/9+i//c9zU22/jYJdLvd3XX/XunTe0X/7x1i2wTXIDvn7brHZUqXH5dU8gzqXilRK3DrInoVOsCnsDDvArrATHAg7w55wEPwOPF/cx8DesAT2gUvF/Uo4AK6Q3/thQWCMGl4o8WiKjJF4/E72JtwN28B7YDtYA9vD++B34CY4GD4AR8MH4QWitx9uCIy7wqflOhnIWrnOKvkWyBoJ/+eSvl/DHvAWOAz+EubDdbAM3gorRG8evA2uguvhLz02VjaI3kZ4F3wQbnDZWnnCZWtlbGCsTsYbt0l/c47E92qxabMc5sFr4JfyO0u+jZILV8IT4ArYxfWtlKG2vJfLeMc22BnpJ7anT5F8GAJ7wpFwChwFF8CzYTX8HrwZngPvhOfC38DRsAZ+H/4R5sMX4Q/gQXgR/ApeDNtwzUthdzgBDoeFcAIsgjPg2XAJLIHXwWnwF7AU/h7Ogs/Dy+B2WA4PwAUwkfRdDpvChTATLoI58rsd/DHsAauc+gwXw5FwCTxXfufDK+CFjrvkY3v9vK7uPart2S67bXkuvboI9ayPI9NLc+ltRtx6N2g9JEK9vAj1hkaol38YvYI464jWFLrXE25DZB2hew2hrBuMbM3gHihrBfU6wTrEWRt4rWFN4CpErwV0rQPcw+8xyxJZB1i/BnAS0tCav55IYK1fKX7d6/0OIQmyri97TNB6Pr2Wrwo/nvV8HrskxrV87jV8sn7PvXbPs27PuGYv/Bq91WpdXmRr8tzr8ayLg9be6XV31aTxbmQLsguxlidauchQpBRZhWxCtiJ1iO+a2Bq92BE7YkfsiB2xI3bEjtgRO2JH7IgdseN/9fj61v/PmF1ZenTW///Ttf6/NE5/B0cdbZErmSsq2xn87YeZE1i34F3/b57Twm/k+//Ldka3/x99j+0+4mWy8+cJe3ZAVwVttvUn+np+7ZMovseg1540wkaAfIcraB1JJiTO9etFPN/sWCibFhYgNjIfuZ44rPOUW2WeKjiVX08ep/JXfot9NqXf3FiO61z595T2K2s3xf9+8W8qW/Ev19b7B7Rf6x2/38D6xceVfktjuXvDkn0LOqzmKqxmOqyXJV6meuEOa56uy+Y6sc5TJ16J4ns5xJPyU/mt59GfEjfJR9mjILqSP1InxE2lU9s5nKfrmaw7kPqQK8OPqa7179XoDn3HXR+47ISy8uKK4pnUQ0l/g20Z/9F9A0rHz1tfZRNHLzKxE2wNb0Q3Pyh+GFJ04tjAPqMKpf+VNYySXInsQgzxJlxzH5Qj6/7mqfOfWSdjqX0Z8jZiqMOEE13/hL7RtijXVeU3U51PtM9k3ewq5APEUEcJJ8rvK74TxfcVXWEXtVb94iT1VTBXuy5ROtnmby6Kf/Maz/DrODeZ13/qNZ4Be6PLOX9A9mp9IpT1gXr/1jnuvR5Rrg1sfP8c/XcS0VX5Rz7jJvncwPrBTZ51gnr9oHddoad9vSr7RQbKHN4A/ltFmrf+3dM=
*/