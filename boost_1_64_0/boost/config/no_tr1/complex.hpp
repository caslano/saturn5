//  (C) Copyright John Maddock 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// The aim of this header is just to include <complex> but to do
// so in a way that does not result in recursive inclusion of
// the Boost TR1 components if boost/tr1/tr1/complex is in the
// include search path.  We have to do this to avoid circular
// dependencies:
//

#ifndef BOOST_CONFIG_COMPLEX
#  define BOOST_CONFIG_COMPLEX

#  ifndef BOOST_TR1_NO_RECURSION
#     define BOOST_TR1_NO_RECURSION
#     define BOOST_CONFIG_NO_COMPLEX_RECURSION
#  endif

#  include <complex>

#  ifdef BOOST_CONFIG_NO_COMPLEX_RECURSION
#     undef BOOST_TR1_NO_RECURSION
#     undef BOOST_CONFIG_NO_COMPLEX_RECURSION
#  endif

#endif

/* complex.hpp
7GetsVpYWl8cFEcIF4UFYtto5bpI6Rg/WTrGCCjhvZuOw6TVMQyEU/eWPNQgD3tUTOSRPX7VvTWwEnfMeJDlrg0OklamNBD7vT8Mr6+1of4DqThlwew3H9X1tV/WlJPl2LQg7PXR0i96oC9HLYxHLtrZTPcmoCQX37kB6/oYUVpR0J6aiSTIfs+JKliR+ZGei9jgSLSULPol46+bmPoCvzgZ98nf5POsAR2r9NsNg74j0H4vT5CmDO8uk8gPr6qJtS8sbNeFjAIbxI59udYvmiIXv8tn11NbzcaTAt5qgjqGl2VNxCLyq72qwU52wcCCsO1SU/xiF+rff8jPO3cG9ujeSpiE+ndfVh4Ikzo4EEzsywy/KMO5sE/lvJr29C79lhVQdiz6+xtycpAoj5OdmRaErW8u9IuD8Zz4U36+7KZfJ+recujZCd/5IJZco8lB0npzLAjbx7fWb+Li/rLi4sog2gXlhlwWfTM5SFJPjgPB+PZ+94vtOBfUMfnJTTl4PA41NeNKeO6vJ0dIGxdnQdhr4k+/WIRzQTU0/e7eGbr3Klh5INpg3Jw8yBON7OqRDWHXrg2Y+i4gG+7I39tC95ZCGxfmCmSdDzW0x4QByJgLnoDRt7MgU98u4Y4PTA6RUts2AE6bg+SgJXKQLRt2NuiNtrgh0OYo/VO/A1n8N8khUnqxDIAzVjY3IFrg3uiSz9iBY5/QvcVweNNUfnaWnHg4RPpzcui/1b1qFRA9cS64ZcMXj71coXtj0LUnroxcxj2B0OpiAJy69ZkBUYgceGTD+qoT+uleuSMcinMhyCgrkKsRBiE9Dy4PiIeRA69sOO/iDZgjMQIL8B5BN84zklqF+Je8cPmyuNlZyIFPNvTolD9a9w6GMVj3Ky/E4r9LDpHWe2dB2HvjsIDIwb3RL58Tdty8UPeGoZsf9UkXl41BDbKqtIJ4NhiIzPwFwwPiD+QhIJ/TNxzSPWWRvwblpWZZLHnpk4OkjSK3IGw7y4iAOAjvaqvseIMWTkVvdhHsxjePu/j2x2gJqX+/DoY5J64OiIZYYzikZMdBKbnpShh0EJ6VAb49kjrQwQJxnplTAqI/7pUHyIan11wxV/deAT1xj3C5eLmgdGxbIE6d4raA6IVcNJANeyfMQY/VQNidnaopy8sFoXM7E8OWISQPObg+GsqGW8Nno3Z9OTRpgHFhPPdNkmMcShny4UAw8fUzAyZGMEfJkqe80EG/5WXQFTlY6eGbC3GZG5747DQQ1pqYGxCtkYdGsqHPw/ddpHsvhemp2tOM+0O8qKI0Qc2DhNj/GqoD4C1mX1V6kPH27cluGzhg9puPS+qVj8KOLHwUdtxvPi6uTz4K29Maq9Mw+81H//rkY3h1Ka2Y5cQxOukjAfEE+vaayoY2Nz75J1roYE8IY0oZfXtxcsXcIKTPkkUBkcCzRPm2XBvGlum3vAi2nIx3OJtxckDu2zMQll6+OSC+Rx6ayYYF61e9rnsvhCjeyMjlucOYHGQtabi5BWHf7d4ZEK2Qh0Nkw6aLf1ytey+AfPULqo+ntk2sYkhpRUw9ighrHv0LitHNJRfHIxeHyoZrI6NxbfSF2U2QCylvtWTlIlJBp31YKLa/87eAyEYumsuGE844fpp+2/OhNc6LpTw1TjJHmWyJxsgKdf8nlrmnInm5AnnJlQ2/H9zjI/3m50Ec58g+H/d6iVRXcSwYA5NxB9oVFLnIx2GyYbk4Fe83ngsLmqKeyrSPpgcaHUmnq9ZFMVw0Dhp/aAvLH9oHqnnrAqVHSeoUrYtizpUmQXEDctFSNvT+8RIMMe0Nmz2os3q499LiMJ28ZaHYd5kODYqtyMXhsqHTkIlYcfM=
*/