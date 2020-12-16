//  boost/cstdlib.hpp header  ------------------------------------------------//

//  Copyright Beman Dawes 2001.  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/utility/cstdlib.html for documentation.

//  Revision History
//   26 Feb 01  Initial version (Beman Dawes)

#ifndef BOOST_CSTDLIB_HPP
#define BOOST_CSTDLIB_HPP

#include <cstdlib>

namespace boost
{
   //  The intent is to propose the following for addition to namespace std
   //  in the C++ Standard Library, and to then deprecate EXIT_SUCCESS and
   //  EXIT_FAILURE.  As an implementation detail, this header defines the
   //  new constants in terms of EXIT_SUCCESS and EXIT_FAILURE.  In a new
   //  standard, the constants would be implementation-defined, although it
   //  might be worthwhile to "suggest" (which a standard is allowed to do)
   //  values of 0 and 1 respectively.

   //  Rationale for having multiple failure values: some environments may
   //  wish to distinguish between different classes of errors.
   //  Rationale for choice of values: programs often use values < 100 for
   //  their own error reporting.  Values > 255 are sometimes reserved for
   //  system detected errors.  200/201 were suggested to minimize conflict.

   const int exit_success = EXIT_SUCCESS;  // implementation-defined value
   const int exit_failure = EXIT_FAILURE;  // implementation-defined value
   const int exit_exception_failure = 200; // otherwise uncaught exception
   const int exit_test_failure = 201;      // report_error or
                                           //  report_critical_error called.
}

#endif


/* cstdlib.hpp
DZ81kGp1nCT9vetIBPUisTDfav5Pxjv+tn/fyT4jGE+ZYd2lUZl8z/naxdKojAcMpToLXoKJDehqn7R87vrjHjpZvDKuoD7NUUgWUlyKNH4puDMOLy+lXzURTAL/w4FePDEKmGd4GpUnemBKHA7NOwRFgXN3XpgHnncqIIqEABdPbAtIEdImeT0QauIRhvmfxmNwwVDlSpORyl+eiB9+QCHbt692aOkOdaB6JcN6ZH7wQP2bXtNfCKii0bB6Nvxyb5zJVacNXJz1g5tqNVkPuRTxQv452rBAFvO+wZ1cl3wwuU7/aZQUxyRgdHNXIRxLrKlVeGOc3GfRONsojNr8F2boOzhBml0/NpTMB2asYLyUCQ3vIR3TTPRoaWn84hYPekD0iqdZk9cHtmCZ+nk0xbskTGMp5FOPdAMVPk+z9numgO4VCoJ3ylH4qojZ/ghO27yUnB8VnAjP6VlwIi2nw/ITDyPNNxRld6NsLXUXZfwylv3ml1H4solfhi4/8Shgc/osP9HPhs8rhEQn+WDteYB4DxDszC9g94oX8bUUKj2l0gqQhkEHqvSb20CDfdix8oNTAUlwGssPKTqMl0uL4rer4q6pAjO2b/xn/jWL7zxipFx2KX7N7CBX6qvBpn35EL6rvl6KX/0Uv24NEb9GJZ4uyjMQnbsmDiuFtZVP+Sl/vSfGFOrGo9Z182StP25c6836K+eHyGmF0OpnE+Rt8zP0i1UP5G/ZatV3CRO98ez2h2GUHZsaIqmGaQ65wLaLFgmxqz7Mxr7UG6LqL69Tb9A5qm0hc7W3r1jvyZTySS8qT/VoOs5nxstxBgaJT5KbdJF0wpP6ge+T2mgh3IYlAN8bfxJ7qjG2fQ8m1s3sqbuMCA6dz3roUSAer7vp1o/xRI4HLc8rlOX5l9iCBKJ1urPlgPfF6WGpFXmzTPnmT+bz6dNXd4unT2OFlnRSGPkFegd8TyYPYprH9iYmNAxFrhRFypB3bFfXMtgU/gAvnhr/BUNnO6cFaefRFGmaVidcZVR4tRrtCzy2pIjxSmeJRwrxdsNEhXtrcnjwNvlri3rdgZVOS0nMSaJWwONYnQqyEhsvxpzTht/D8b3I5qHPhiQfLKMAJVY9E8bFULdPlU3chiZ4xByyGQ58c0Y5Sy6VmZcic000u6s1NBjuMXp4/IO5Qf3z7BlwSq2PjBPPXJSeyOksuVoW7qaMeVpP5B0zWyZGIpF4/LdMJl4jE7+8Rr7524tE6bwxqxENdP6gbJaH/tgsHBkM+9vAWjITXwd4k8oof5fxlcaMaEseN1C2Yr3vMPYezGkr3V3LnAguzK8oxkTMyfAOjgcqUJXT8UCZK6kCmd/ccyMe6f4LJVml0yvHDEOHsVswJIn6W+JMvd0MJSrFDL+FxEP+PvN7mvnqPU2eakM8Qrgzm2vR2lnyKxuyrvYKR5QUM1ydzaPz10z1ytRoVkIDvENhSLxqABfvd3LxhgGYXentPZvHNc3pZQg/sW+Y2hNgJ7AXtC/Y6iXOku6ypTdhXaOPswYfwtKiRuyCwTlJQfmG2gqxBcGt8PVd5lZI9u3lBpjgLEmUtfpQKzfAFxZzA9ysKu1LexOjvrV3Bev7Q6P6nCVDZFX9rzYeW11xvEFtWLq0bbdbCPgHc8vof7aSFxwbzbwIkDvumJGy/IGr5D7YOZ7zO0omvoNE7pgKkThaJpYxEZDPjeeOaU7M439wrvDfav+IE/exZBO3uYWkq1V+oX8qCyH8drmHjGc0QGwqOi6F3lEmnNFfdrpZP++Zc9Te+T13Sd8Mc+/0ncO98zhTo5GKUIZyxdqLAm/KMK11njP4WKVcKqg/fWuIIZd67e5G+lOcGOA=
*/