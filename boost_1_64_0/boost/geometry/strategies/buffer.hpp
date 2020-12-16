// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2012-2014 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BUFFER_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BUFFER_HPP

namespace boost { namespace geometry
{

namespace strategy { namespace buffer
{

/*

   A Buffer-join strategy gets 4 input points.
   On the two consecutive segments s1 and s2 (joining at vertex v):

   The lines from parallel at s1, s2 (at buffer-distance) end/start
   in two points perpendicular to the segments: p1 and p2.
   These parallel lines interesct in point ip

             (s2)
              |
              |
              ^
              |
        (p2)  |(v)
        *     +----<--- (s1)

        x(ip) *(p1)


    So, in clockwise order:
        v : vertex point
        p1: perpendicular on left side of segment1<1> (perp1)
        ip: intersection point
        p2: perpendicular on left side of segment2<0> (perp2)
*/



/*!
\brief Enumerates options for side of buffer (left/right w.r.t. directed
    segment)
\ingroup enum
\details Around a linestring, a buffer can be defined left or right.
    Around a polygon, assumed clockwise internally,
    a buffer is either on the left side (inflates the polygon), or on the
    right side (deflates the polygon)
*/
enum buffer_side_selector { buffer_side_left, buffer_side_right };

/*!
\brief Enumerates types of pieces (parts of buffer) around geometries
\ingroup enum
*/
enum piece_type
{
    buffered_segment,
    buffered_join,
    buffered_round_end,
    buffered_flat_end,
    buffered_point,
    buffered_concave,   // always on the inside
    piece_type_unknown
};


/*!
\brief Enumerates types of joins
\ingroup enum
*/
enum join_selector
{
    join_convex,
    join_concave,
    join_continue, // collinear, next segment touches previous segment
    join_spike     // collinear, with overlap, next segment goes back
};

/*!
\brief Enumerates types of result codes from buffer strategies
\ingroup enum
*/
enum result_code
{
    result_normal,
    result_error_numerical,
    result_no_output
};


}} // namespace strategy::buffer


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BUFFER_HPP

/* buffer.hpp
s02HFmld1wJMDSKdeZ+oQ9zchGGaOHsmT30dodzoSEjI1WU3AmZ9KZ+w/uZivwHfwuXB93B58IpLLg+uOsQCQ082Gs4aKRRp6A9NPVOYc3G0plvp80lHjGYiPkJAUWDXg6kyWFaKDJa1FxjM3ReDfd4jg5Wwv5je6Ghz35To9w5RzjMUFILN3FfC3EefyCnnZxikLDH5zPns/7DoecAFJscdaMBh8WYp1vRQu41LFcfefEYix/423eBYspt7W7HBsYEeObau2ODYgEnAgM2xLzPHZp3twLFbxgDHXpneb44996TeObaqZ44NEccKP8hsj+j1gy2HsXSmGEtrkqKqQPgNliCZKwEYCIWlv7DobIAlrBTYy8pqjvsW1HZ0hssP99LS+UDVi/wzjmMr7NgMLXYgx54MsWTLcz0N7HnhgeJtBHtFMC5l1Uiz4LyWxwN5XFgK/0YlbA3dTLec01XjphTT4Q3M3tK3ia09Hssmpu8SwEp7yhyxCytNpbDlorA9QE6lS5pIq910eFGykLjUZRGXzjqDtl0ml44qAi59zSP8utLBoq2Hs4JG3mppKvEqSAsjUoDcVdxCaUiz3cc21rEzQqZVmKmc5izTQwUPmxwEWKN7Isy4gTKyyCg+lnYNU5UtwarRFl905ircfrpDFWpGQRUGQRVUriGjJcqdo2y29LfiGlitHty4y9FcJrMhOd0gUCjaUcQKGBBLhGf3cnnK2tevR9nGiQ5kFHfPdEDxpyOF2dmu5cq57WE2ahn+1iEU7jwNFALRPVAOO0z2SbOvdbk9Vwdoa9ZkI2HqX9wiLSpkI4aZqiaDKD58IfmMAtjrBqmov4+kqKqeiPBLjh+HFhXi8HOiKTQwpT1cI9g4i/WmvulAsKUj0BIWjvfnmjXUN8YB50ZjfLiMiVzGd5zKKMYyfqWsfv54hOLu8MnE2S0gc5iOZaywed21bqiq+G8hhzyNKuOCXE4FPQMzRqx+XVDoX9F6LAOQVCHVGPLJCAhBuqmzwbf1EDprfGWENCl/CRZ6MhfacRrd1zALPRYKNYu8YURikVcnFVmXVOQ5EMLG5peLS+rHfJOuE67+n7qkvu+377eXfiQ/Tbz0uZpMWJ8ojArytJ/ow5Ls2PBKLigXeS3rqRvSmT+HiBvEtBZ0227kh7hJ8XjRSW576r67kGfh5TwLc6GoOOjhgtvsgqUGOqdl3yASHSXY64xeErJsNMV8YK5NWPnI1FBWSaXhVL4xrfSWo0MF2DaufaBHYEtTALb1GGdgTErWNBT6rIZ/Jme4bZaCFd9AoLTM/c8ISGBG17wB+Mp3z8b3TH+ljyvo/8HReMvVz0rms2+1VJbouxCDx02kL6OS1OhJnpNJ9qMkOZzkrmq3nWSlTLKDmYqTnKsnWSCT/NylQZmgJzlDJrnPbMM6tXc09PKgfiSKh9s3avUJH7UdQS/uUbADzdQvn4Z0G9hJpw/KspO2FqrkvsMtpJt+zf0z6QE1keyTtFLcNKWWnoBT6qWosnS4OqL4FEQk8g4KyT5JO5gzZJzAc7CRYZOZoWLtSZQ47a0ZbkSFUFJE+3CYJe+w7LMS2+f4mng+FSUTLlVSVFlTLESVPFTx5c4dpPh+HJ0mZ4BQfjcxcFDzPqlSFQEkwRdy90JZfiYYeofJ0DsMhqbFebZgN5+1d7hZO0CSRq+Rq10WF7NTx/7wd+jY0AvXzQ8MnccZ6UxRsNo1Q2EZmS1ybBNWIuqOp2Vd9F/OeIlNt4KWmcdy0znfIzWVeEXQdXwt51mcYKpEvuN5opjevGEpEYi7eWU7WqYTIlNgnz1pjACPSnzYGKCiOtXoNxGGDXXxdP0feUyxG23v3jOtdFo=
*/