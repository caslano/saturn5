// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_ERROR_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_ERROR_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              
                 
#include <boost/iostreams/detail/ios.hpp>  // failure.

namespace boost { namespace iostreams { namespace detail {

inline BOOST_IOSTREAMS_FAILURE cant_read() 
{ return BOOST_IOSTREAMS_FAILURE("no read access"); }

inline BOOST_IOSTREAMS_FAILURE cant_write() 
{ return BOOST_IOSTREAMS_FAILURE("no write access"); }

inline BOOST_IOSTREAMS_FAILURE cant_seek() 
{ return BOOST_IOSTREAMS_FAILURE("no random access"); }

inline BOOST_IOSTREAMS_FAILURE bad_read() 
{ return BOOST_IOSTREAMS_FAILURE("bad read"); }

inline BOOST_IOSTREAMS_FAILURE bad_putback() 
{ return BOOST_IOSTREAMS_FAILURE("putback buffer full"); }

inline BOOST_IOSTREAMS_FAILURE bad_write() 
{ return BOOST_IOSTREAMS_FAILURE("bad write"); }

inline BOOST_IOSTREAMS_FAILURE write_area_exhausted() 
{ return BOOST_IOSTREAMS_FAILURE("write area exhausted"); }

inline BOOST_IOSTREAMS_FAILURE bad_seek() 
{ return BOOST_IOSTREAMS_FAILURE("bad seek"); }

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_ERROR_HPP_INCLUDED

/* error.hpp
Yqi2RMfjJDbMygKjbSysK23KbJLPY5KtxSJSQUC7CjDK8ks9eQkvutsTg7RdqC/yNm8e41iJSjUHYRJp9uM7RIWG/WnoubW9EOTt/XSl5Yrc8qF56081BaxTDnx2G4FROEz+J8slgZrARpn3dj7A0SSFVqagRJ2mgGJZnBng7A/cpzOi1fIdHeqCTJE65RlSXLGJ7Bq771vSWqmPaK0SpSqogJooVsDZ8N4cRYQqIUvNHBJTa1OHz0Nrg2dPQpJWBrOX0DZy+SEPMfLolPzhNwSlmti3ToTvbzzbgQZ/FMrWklGHytYHs4xTgFLcEicrKEcXxYYrzkmpu2nlxJqMappkF4eq5DEnwsbLF62jGH/Dl6+E9qgrdsi1DjML8OXGXXy3Nuwb2gp2VpsZJ2MblmeFtjOCXR9A3OMrHuZOaymd2T6nR++rH0Z4Z4QQ5C+ij3yHMZjoSJQq3z+Q815WEtViji6lOjrNEkfKRYYTSJ1K6eGlsj7xquK/GEuJdCZ2gM6sIRragfad4IwSPaLpIIaqI3ASkn579UAVLyUOqs2VH+yE9ERz6lY7j4Boxz9PKNkjgtn+LtmV1iWAc1R4rfxjBz8IH6orlaYjsREwcCU3OBPifyVoRx6+ywTJ5ZLFZNAvCN6/8vP/EqvvX3koQNiMTy7E2fNdnhSWszWDI4Vrxe8VcXa3LcHzaJwJroLl7yfRbVlptOJGuV9j
*/