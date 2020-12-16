/*-----------------------------------------------------------------------------+
Author: Joachim Faulhaber
Copyright (c) 2009-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------+
States of comparison and inclusion relations as static constants
+-----------------------------------------------------------------------------*/
#ifndef  BOOST_ICL_RELATION_STATE_HPP_JOFA_090214
#define  BOOST_ICL_RELATION_STATE_HPP_JOFA_090214

namespace boost{namespace icl
{
    namespace comparison
    {
        static const int less    = -1;
        static const int equal   =  0;
        static const int greater =  1;
    }

    namespace inclusion
    {
        static const int unrelated =  0;
        static const int subset    =  1;
        static const int superset  =  2;
        static const int equal     =  3;
    }


}} // namespace icl boost

#endif // BOOST_ICL_RELATION_STATE_HPP_JOFA_090214



/* relation_state.hpp
U/ENwpHkm9qlm1/kd5AtmXGqvJ7mlekzZ0Z+kQ9lRZxg4cg5nROG6ABfbdzr7Y+CBF5T0lkLtXReob5w3PUFf9ORadlZ05IOUufUlNQLyvGB8caO8cZ7g0KCAs4agrLFS6WRkstpp/Tw+b7GZXGTG2b2k6KvUCusiL+RWUDgzfhFPj83BbUVM2XVPYMm+qj3BD2RIL+d4uRfSEff59rE5LVH5KTTOj1J3775raTcJmjfcM3NO2eZTl5Lu+qldeYrgn25xpbY5ygeOLhi9WlOTYlv/sO8+D3JF9/96tOBe29fOjIiSgI/RSQGjNFJ70PSUvWce72nQxViu5YlNJ6n7Q7F4Mtn9fqBm+eyiy4WhqzffS3s+o03z8V2xNFjk1HXLFfN7PS76Nbt2TVZbx1sY+DzvOF2L3D3pY8nb17dPPEuS3Zt297SMjYWl+lWFvLv/OLuxM7AJBXZ5qM01eoAAD/hX3nl6++izY25ng9fcND+Vf6Y7YSZ3uYbrXJnP8Q4Mi9ffkuuxTk1kMQrA+7VZMXzPnmquTlC4HK0y26GvpHKT6zKDMXQURHOLEzq2Eg6kbU2Yl8T/Vk9Kepi64gkrPW4hDHlTbIi/sGuzx1N2FTKLC+HZtcDt6X8MbMLxixgSNf85GN6+/ffy/qF3+c/4/p16jD454FhPuLV0bIRvmvH+MdFJulP2J5mvuE6Ra15ymPkojUP9tIgfPgtc+X0KiMzx1u851oyxhLeZxj3XCcYzw3kQyQsBcWp3VfXXHvi8Xlt+5jvhe6l87B+QQe/9uzRva6K22hyNSQ12PJekmXo3vwXdMPAwS6iy01CcO+hZZw1puxbJLawDbUqReG0luFJyRdh7l73/aL9dDXsMmM1/pYj9tdkNhzcNDPz3tf7i9FBDFyoTjOTSlEEvYnmq6tPWD4y41jQtMnbMwKbIej/MDDdkN+gSIIzBykrD+mDnmc/zs83Qyj8Ygz7RWD8ORXnYs/vH/JdFnc2lvfc5TaeW5o3mkMF7I2YRaU6A8SoyMaEDTNeYusIovGDUoSiy/7zYgJ77lTaG4w2scF3MAvG74RVDG1Yx3oO+oPOLPUzrgU9qODvgZAL/x5g5KTs8kFNKnHya7dE2YzFvTFo4bHkvG4cwhDrTFd6o4jLVJ1vE9b8QnrVuiyxxOTZPZRvlDzfRqg2vGXanta/y2aTtiStdeArjl1/eco6VCz80D+QZw/ae1x1PcV6hq3Wi37IteCHga9Lfb3er9ov4N5eITQf10JRc6Du36Q7RhLqRN1Ytcv9zOmSBOYcUfmm1C8BqqLZeWei1Mw+8ciJbQnOmyKfleFOrHyV3HtM55BXafew8AfuKqOIoszI171pMy11LTGX2AxIHZ0McS76dVeTBp5cXklyRc9zmkSK5lXpPsfgRrrRbtW6qNWTpOhHjCTLpFjNH0tIZthNJhA2crGMcuk8S36NJ7+IyH+LF/8jwMBq1NI+Sf36RdlL8au8D7DTfFkW20fZqMlb9KBq9lPYjVtWTFnlhYU2HzmEL5UZKTwYItm8HetzJl8epq1UVM1aVE/GnylpFSRy5PBp3gFxPfuhd4S+F5ZuSkO39dcUZuaFmNoOqz3v4XOFvX91q2S5//KTd2wKNLeMwi0e9w027dYw31/Vs97ywaIfSS7YUCG9/LTJ7NPsYPZtyzQ1WrSUbNiX/4dsiwH7mRuNH7Pfm2uc9N8SusN171Ml4bGJV447rOfSnxbxNp7PTb3ss0/ErT3EqFBHt1gslM7QEtujZvUw7lWZuusKKzt/GyuVdV07xwJZtUo34Lsl36SSdnKbxSTQRuoZkxZfsArWNqwJTikA60sPLri+mdhYX7Cf6wM=
*/