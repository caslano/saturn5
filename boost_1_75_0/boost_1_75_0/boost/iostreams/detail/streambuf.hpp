// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_STREAMBUF_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_STREAMBUF_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              
                 
#include <boost/iostreams/detail/config/wide_streams.hpp>
#ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES
# include <streambuf>
#else 
# include <streambuf.h>
#endif 

#ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES
# define BOOST_IOSTREAMS_BASIC_STREAMBUF(ch, tr) std::basic_streambuf< ch, tr >
# define BOOST_IOSTREAMS_PUBSYNC pubsync
# define BOOST_IOSTREAMS_PUBSEEKOFF pubseekoff
# define BOOST_IOSTREAMS_PUBSEEKPOS pubseekpos
#else
# define BOOST_IOSTREAMS_BASIC_STREAMBUF(ch, tr) std::streambuf
# define BOOST_IOSTREAMS_PUBSYNC sync
# define BOOST_IOSTREAMS_PUBSEEKOFF seekoff
# define BOOST_IOSTREAMS_PUBSEEKPOS seekpos
#endif

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_STREAMBUF_HPP_INCLUDED

/* streambuf.hpp
QikLOk/VqbHa5u+2Qtqe1j/RrtJQvWiopLsr16sEW7blcbSBPgEltq+HdcVJJuS0t0HVXuprPajA0B4oaGO1jzUl/BEn7gGSAB3/mZQjHYjQ48a9M57/rP+cM25+xvMARvPxNjadf7RM5IWeQhfb+3Y5Pvdyrt7dgKjA1neIv6tSTu+2r5v9X8r+n/8+zP03X8rKyd5ZxsXZxt7d6V+0HdNXp89L/OYzXO7jl/YvfsYYrO1vY4lfdprHXtNyRHSg4B0RTln/ZJ8ULjWxpkFLMTd7z1Bu5GJtHM/PtsTH1qi4GRWFzYdhPsTH7kzd6+UAqJ+aVVRYmlbUFim5dG+9Gxs++lyngFTy3Mb/t5n6zWiGEM8un8duesvDRpiiC6WQ+KVRgv6s5ktIEntBbjq/ag5jIsrru0dT4YxR3iKQdlD5IEew8CO/7F3VG59rP65KlI+vWZF/IQNesBCuuBZ8TmhbTUCkWWOGvdDk7leVWu6aTkMwk9ap5HUeZe7yuatvo0yIv20x8rCPGjNgCSL1M6jJgYka1BNpUfQUU6wRtApIRq7EMrIa5m7Jiwm+RoTl4/rtGkcMswRfehm4XC9D2vKsUywLdge9RtkIFOY+WsIA+oMIuTXWwTMz6I6TbfxhY8DyY18Zgs5cWw8BP7xpRAYvzYmdGPLjUOhIg4Jsf4QheNcwjKgRfCQrl319oOF7j6YWzi7EFBi1fIgS
*/