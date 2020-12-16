/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller
    Copyright (c) 2014 John Fletcher
 
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_DEBUG_HPP
#define BOOST_PHOENIX_DEBUG_HPP

#include <iostream>
#include <boost/phoenix/version.hpp>
// Some other things may be needed here...

// Include all proto for the time being...
#include <boost/proto/proto.hpp>

namespace boost { namespace phoenix
  {

    // For now just drop through to the Proto versions.

    /// \brief Pretty-print a Phoenix expression tree using the Proto code.
    ///
    /// \note Equivalent to <tt>functional::display_expr(0, sout)(expr)</tt>
    /// \param expr The Phoenix expression tree to pretty-print
    /// \param sout The \c ostream to which the output should be
    ///             written. If not specified, defaults to
    ///             <tt>std::cout</tt>.
    template<typename Expr>
    void display_expr(Expr const &expr, std::ostream &sout)
    {
      boost::proto::display_expr(expr,sout);
    }

    /// \overload
    ///
    template<typename Expr>
    void display_expr(Expr const &expr)
    {
      boost::proto::display_expr(expr);
    }

  } // namespace phoenix
} // namespace boost



#endif

/* debug.hpp
Bcg4H5vCQeiEYZiF1LXYAILQCxMwD2kXYDuohlbohmGYhYx3MR81MAY41kIb9MIELEDGu7EZ88FhGID+TNoIM5C4gvKw+VrGVDmM8LltBXJ87uU4CjOQgv47oBOGYQ5GsWkqvrIWKqAXpiA9jTZAFbRCBX67Hw5DCnPZHP7YwhzQCXOQzDybBWXYq92ca2CYz/1d+C0c5XsKfjVxDX0HaehWxPeDHIMcpzimMK47+TwM05DM2PBBJvY3Ho68a7OOsnZACA5DkLI6YAAqyH8IxiBJzynyoQIOQgfzURtzSj8+NAozkFpDedABA5CL31TBIZjdG3lmkQOt0A2J9bQTiiAEA1DdgDwMYIcJyEXPkN7nGYYZSM4lHxRBNbRCFwzDxNPMYXnI5WLTq5k/nuC+idnff2ZeIm3THvLwu/V2mPonYxuq/sL8Ns+5v7O+QPVR1ifIgll+87c2camRw7EXUmEQ2ZHnkYEK8rdDFZ8XIJvPqRwPIteK3Ays4/skf9P3KMy+RB5+DzqE3OFT+Q7DkMrfEqiGEJ87nmSehXHIfIo5ChKh9znmZkh7hnPQwe8A2/ht5jqORzmO0tYh/iZFFd8r+M1sGsd+WJtK+VCBTCvHtRxToRfGoHVn5J78BGnr+FtPQajCDh3U2cfffsx/NWVx7OP3egN87oTaNGxC24pgiB/rJPPb59VQBW0wAFOwAFXYooi2ZdD+TP72TCLyHXwe5vN+A1k+z/O506AuPpfxOcvAHnw+xOciPmcnUx7HsheYpyET1kGIvTHaoBsGYeEb2P6bpJn3EiE5gN/CYXxh5svY/vOsxzAF6V9gfYOeT5LvY/TpQe4rQdHHWbcvp54PIQtjUH0Scy5pWeCD/ZB0AH+5gv5upD+gFg7DMMxBbhO6wQRkhvClGvSi3CFI2ks6TFXxOUC/wjhk8jczys6nXdAN45C0Fh+GFhiAWci6AJ+DThiDxAuJnaAdxiDlnegJbTACieuoD1phGrLehb7QC7OQ8W7qhXYYBYPfoq6GEPTDLGTmYj/ohHFIzsNW0AajkLyeOqEDxiF1A2VCO4xBSj7jD1phCBIL+A5t0Hkq+eEon9ddjAwMwFEo30iZMAapm/gOnTAFGYXoBN0wA9mXEAdAH8xB1mbSoRtmIKuIvoRemIOcLZQFU5BZjE2gH+Ygp4SyoA+Owlof/Q6DYLyHPoE2GIfUUvwNumAaMrbSP9ADM5BZRr3QC6nbsBu0wzikXIodoA3GIPky7AadMA3Z5egFvTAHq7ejBwxC4nspC9pgFFLeRx9AK/TDHGTvwAbQBqMfoE/XoMs7sCmkzCUYIxznISuHeqEFemECUleiG7TAAMxC9irKgzYYglnoORe5TM7BJCSvoB8hCJ0wDakLrNczxBoc+2AW0l5kHYcgHIZhmIP0f7GGQwi6YQwWIIu/NVwGLdAD45B+wOAfekE5tEIfTEJiAuehHFphlHmul+M4GEtoM/jgIHTDKMxDxlLsCvuhG8ZgHjITkYeD0AfTkHoC54K0C/L5XAuHYQSOQsaJ9FkuMSAU8bnnIuIcjt0wBguQdRJ9Ai0ncw7SXoGNoQcmIPmV2BOC0A0TkJZMu6ATpiDlFHwS9kMvTELZqegIvayBKa+iDKiFw3D0b6yZHOcgM4WyoA2G4ChkLcOnoQNGIXE5+SEEvTADmaeRD9phHIxUxg30wjS0098TtLedtg+a8H0OMp/GFtACA7AA2X8ipoJOGIGjkPFn5GA/dMM4JM4SV8MOOASDMAvpf+G6ETpgHFL/StwFB6EHZiD9GfwKQtADk7COMVALnTAGic8Sw0EVdMAIHIXMv6ELtEA/TEPac5yDFuiHGUg/Ssw=
*/