
#ifndef BOOST_MPL_AS_SEQUENCE_HPP_INCLUDED
#define BOOST_MPL_AS_SEQUENCE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/single_view.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct as_sequence
    : if_< is_sequence<T>, T, single_view<T> >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,as_sequence,(T))
};

BOOST_MPL_AUX_NA_SPEC_NO_ETI(1, as_sequence)

}}

#endif // BOOST_MPL_AS_SEQUENCE_HPP_INCLUDED

/* as_sequence.hpp
bJsPB543NFCMuv/rfqUP00zVdKOeEbL3bjD0Uhz+tujFfa/SyxYKIL9KKoPyOWq9TSWdEq41ks5XSbfeoycdKIL2z9I1Cseyu+83yz+/WLxE7o8gDEPnWaI9OVq/xgKeVCyHo7cI+M3Qz5j74yvvE/9H1EOvqE13mi+9QZX9DHWIrV14i3XJdjupXGx3a4lSjgDaHDOhOgLVDq61JvyQkfCiDMPE/kFKhnf7+6wm9ndk6Cb27z9qmtifXqNcI7HD/oF6jAHZoB7jANepx0GA71CPSYBvVo9DAIfX2Pbul69xmPJK5FyXPTdL3kdVang/3mc5eP0ogTgOA0isUItY4mZQ3MAZsiePIak6w9d+c6NpDfQoD1HIgaOfbPHfb+H15zRoXeQMFmqnWeJ+kWbKGURSo36ut8hpIJhEavSi53V6+uyKl8VF0PDU1LpqzBXW5ziROAeK88pDlsgliFTegInXPp08I+0w7RPcBWSxZx6gXmCR2ufGasqM9Fsif4LIfjNyf7UZ+W22k+xFw4fX5WJNW63U6GUVaHd9Tk3pZxhjyl7xC9CPgdF50J6XKjuKONi+dunPshz9YEXwGUu+Jh6u6WYXPVlPoLXJFi6drtF6O7DBjGe7iCSMiwU2Zom8E5F+VKN44Q6NfRx8JfE2fXA3CxvEXIy2omJuNWOsBzdJ0yKyoNFmEek1LCJLrtOn/j56p6NUn+h737xR8f/3h/WHz3Q2U838uyWoilT+8wYmaHSXHLUeuHK16jHjMcwPvBecVQU/rNyBsF6arNZasuxQPD5eNXx479Kb+cH6YtcqyB79/p4f+59vwB5MFhDHtpW+jL5KTVsTZW76Kv21NHX4Xhr9D8fmnvLPkwd/VnnXCB/jYgVWmqutX2VuPbwIA+IS5Sr6R7E5YkeVWKmmH6wZ9qx0uJD9HW0fG1bRj3Th991p9tJn7Ks5qyPKSCiuxppGoLCKM3xZ4neYXKpckjtxpgYH5RgDLsrnA5sfc6x5RFggciGajpIxpKfVlP/Y2dT9TdlrLQmzwaqgWM3TWEt5oJ9PrTT3S/de/7ZxEjXeH5m8Rewfcr7AzcpoTxesVO1punLg1E4zwiYoz17ZJGIW3rORCGM58ErY0R5vEn9RrAlCBCu/hYhFxFsqTNby425WvXEqNQqpCulQgzepGJI9pGQPieyhPX40YB834LYwGjAN+3TagTA04FeV116+2hf6aEV4rVqKYR1boB77gTxZPQ4CPBGPluZ9u/JnxCmmZp6M/rLYnANWyNCUxErGWJ4+ZEF8QL1yoI03CslfJwNfbbjUUvCYKnhMCs73CWE57kH+X77GdFCe9rm3jdHd8F98eLPZ3lCJqkWU+gzdtV3jaDiMwzh0qrbrGsfYhEX2s3rn1y59wByarrxaLaMxNH0EjxZ7yDrlF2dzLPGtNKvlComRhlmx2dzhzJPxQ97SWGWJKCh2q3F87xfM4OOtu0W0WBkikLE5kjEsRNde9+9xFDP2m5M3Dae4b5qa3uyg58azsW/iRy953Vu9/EtGus0JcPzAVtQTsjymPPPAzPY+hLa+WE3RqeZz4NWUri0C1gtsav6wzkpSmbC18urU/FvL6GQNoVZ9HEvv16isFbu0EDbIHtVopoS/Ci+eJtpEe8M9+vl3tdpEn8KtKbxJvdHx6FeRGLo57O+rVC+mYWfSJ9UrLGZ8cZqeL0aA/5+PdblSakPwbif+R6+Ndznxdxr4sdvPS3U2fR3zSYu+2I7zhNJX+EtsDf+dqOwjG8ZQ2a11h62y19LfOTcp/Tnnu3ORX4+0cbz5xjmdkH3nX+RAeCS/LvfHHows2ZVfphRR2ndFqWvqNo3TP4EWyB4=
*/