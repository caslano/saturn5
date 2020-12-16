//
// Boost.Pointer Container
//
//  Copyright Thorsten Ottosen 2006. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/ptr_container/
//

#ifndef BOOST_PTR_CONTAINER_DETAIL_THROW_EXCEPTION
#define BOOST_PTR_CONTAINER_DETAIL_THROW_EXCEPTION

#include <boost/assert.hpp>
#include <boost/config.hpp>

#ifdef BOOST_NO_EXCEPTIONS
#define BOOST_PTR_CONTAINER_NO_EXCEPTIONS
#endif

#ifdef BOOST_PTR_CONTAINER_NO_EXCEPTIONS

#define BOOST_PTR_CONTAINER_THROW_EXCEPTION( If, Ex, Msg ) BOOST_ASSERT( !(If) && Msg ) 

#else

#define BOOST_PTR_CONTAINER_THROW_EXCEPTION( If, Ex, Msg ) if( (If) ) throw Ex ( Msg )

#endif // BOOST_PTR_CONTAINER_NO_EXCEPTIONS


#endif

/* throw_exception.hpp
B1vQ3TBiaHcVP+k5Ffnl3/euQd6Ri7p+2LHhPA+Z3LeA+SeWqmSgn6exO3vRk2TqRcTkkazn1JtDPFwe34UN6DnbdHx3lAs5NOsQR/KdX2/ymMb4kLgvkflZyDg55y104/E9sb1ZNqKrz6k1r2AtCFuwbyVx1XxkaivrYdi4dsxTTCtqRMuxGaxbmNjRG6z5vPohtTv8a/Wd1LLHsca3ErlsiY+syhhWJU4m9khXm/b4jsityPFDaskz8OsLef49amDo14KLrPvmJk5CXg4Ow92RG8Zih9JWsQzrIesbp6mdtEOWNuCvsMeJe5DRyfids8x7aZ6xh+PMcXXWLMPOkGfxXY//HfpDzcDHl1rLY9OojW6V+JocPhd11pepDeaVb9tWhyH3yEuDQuSTfsgmedGSYOSX2oUN+1TzMXNyEF+7Ht+JnLshk6vxSYev4/86MCYe6CN9398C3/4+cdUE1uXG8j7YG5ZJjPrU9a1h9Idx6uvDM2k7tBtrxNi2LMRHE4jTDrAu250xbJaGc4z/pGLEWoz70OncCzu0gO7GfsC6Crr2WlvWhS7QHy9izMrIREdqnMTtcdQNTtMwfB9rhNTtzzBGkeh6Ujf6d4IcnW8Bc+A70hPzT47n/rzHD8jax9jCN/oSAzNPbyehJ1exfTPRVfz+CezF9/eQv9XI6o98i0VMsiUQ29qU2Ax/YPPD961Cz4gzG5aljnAbu/gWseIN1hkaWEalpchOWewXvulhGd53DDUcdPIg+Wcj3mXbdmJf7HHwl6zhYIvWY7+eRqMrXVlTRb+iqYsXPEvNwgubfY7fy0z0iLyB2HHtDPKWV/BhS+z1YWI/bNWqvPz7NXSKmL2CL/Ey+7ktsAvZqQ1WtvHNDXp5lFh4IvEK8xfmj18LwBadxEfxDt/VM1jrxOa5Mu4F8D3Ew53xRyeJB/ox1y3qEGvOQ04qUm8OR197cU0ca9o5iOdDsdXkX1vfpb88JxydGTiYWmEf9BXddiMOfC+M+LoS+pkHO1gLPSH2fmCPUdHHp2fww+Wxh8z9Qj/sQXbG+yw+n7j9wjZstQ91oHLEC8jyY2zBE9Y/PYj5PBsREyPXh/FlSxtgW7h/JIJXF/0bQZ97nEA+I4jXGOeBrWzUjLHH2I2Z7qgQ38teY2zvN7bXOBh/8gADvzwNe5J1J7VpYvaah4mla6BT9v+nDX7m1VCe+zE1TvxcDFzApu36Dpu5gmu8eWZze42d2i5jstv+/WBPZG0H+Q82K+156sj45aLtsVXYwVKB+PIKyEJa4tEm2DCT/JHY42h/apf90I9O3L81MrOFGBH7MOcdapsFsOn2tSxiWnM1z8G/1eD59xmfaguIf8YSn+ZEhqnd5sFB10Eei3POHMO7ITPfLMZX3ySOw07ioo2159GfvqzX7LXba9bY8AOv2L8HPMtJD8Oxvcc+f37yxkwGQReykJk6RjvsYxaO428qZMNfzWHP2PpsY3w9aUec/xV+f46N9S3ep2URcmUv2tXA79u/T8QfL89NXDuQvDgP95mDb8rLdfjY4fk4n0zcwjObGdgMb4MGNsd/S6Qi8ljkFfasAf/b7Y/qU+ehgJvUVFLWp+q7vVijasix1lwXyL4p/FxPSXoNfdhipVqncGEMc4abqbbJ0RTbj/yl1iZLS2LNT1Jtw99/k4+PSb1NGfT+dd/U37k5fZzoh13obKTaLh45WtE69ec9IUbqcCdlnYax05pYO/Yd3f5ePbET7VLWFJkn5kXmpBnY33kszIcpsA/OwRFI/t0cu7rzDLhqfy77osCxX+bcw13mPbO7zHVWd5nvz4jlzlm/rbl5cS43OGpPf7Mv2g/emb6kIodaz3Q=
*/