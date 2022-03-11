// ----------------------------------------------------------------------------
//  workarounds for gcc < 3.0. 
// ----------------------------------------------------------------------------

//  Copyright Samuel Krempp 2003. Use, modification, and distribution are
//  subject to the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/format for library home page


// ----------------------------------------------------------------------------

// There's a lot to do, the stdlib shipped with gcc prior to 3.x 
// was terribly non-conforming. 
// . defines macros switches
// . supplies template classes basic_foo<char,Tr> where gcc only supplies foo.
//  i.e :
//     -  basic_ios<char, Tr>        from ios
//     -  basic_ostream<char, Tr>    from ostream
//     -  basic_srteambuf<char, Tr>  from streambuf
// these can be used transparently. (it obviously does not work for wchar_t)
// . specialise CompatAlloc and CompatTraits to wrap gcc-2.95's 
//    string_char_traits and std::alloc 

#if  BOOST_WORKAROUND(__GNUC__, < 3) && !defined(__SGI_STL_PORT) && !defined(_STLPORT_VERSION)
   // only for gcc-2.95's native stdlib

#ifndef BOOST_FORMAT_WORKAROUNDS_GCC295_H
#define BOOST_FORMAT_WORKAROUNDS_GCC295_H

// SGI STL doesnt have <ostream> and others, so we need iostream.
#include <iostream> 
#define BOOST_FORMAT_OSTREAM_DEFINED

#include <streambuf.h>
#define BOOST_FORMAT_STREAMBUF_DEFINED

#define BOOST_NO_TEMPLATE_STD_STREAM

#ifndef BOOST_IO_STD
#  define BOOST_IO_STD std::
#endif



// *** 
// gcc's simple classes turned into standard-like template classes :

namespace std {


    // gcc has string_char_traits, it's incomplete.
    // we declare a std::char_traits, and specialize CompatTraits<..> on it
    // to do what is required
    template<class Ch>
    class char_traits; // no definition here, we will just use it as a tag.

    template <class Ch, class Tr>
    class basic_streambuf;

    template <class Tr> 
    class basic_streambuf<char, Tr> : public streambuf {
    };

    template <class Ch, class Tr=::std::char_traits<Ch> >
    class basic_ios;

    template <class Tr>
    class basic_ios<char, Tr> : public ostream {
    public:
        basic_ios(streambuf * p) : ostream(p) {};
         char fill()  const { return ios::fill(); } // gcc returns wchar..
         char fill(char c)  { return ios::fill(c); } // gcc takes wchar..
         char widen(char c) { return c; }
         char narrow(char c, char def) { return c; }
        basic_ios& copyfmt(const ios& right) {
            fill(right.fill());
            flags(right.flags() );
            exceptions(right.exceptions());
            width(right.width());
            precision(right.precision());
            return *this;
        }
     };


    typedef ios ios_base;

    template <class Ch, class Tr>
    class basic_ostream;

     template <class Tr> 
     class basic_ostream<char, Tr> : public basic_ios<char, Tr>
     {
     public:
         basic_ostream(streambuf * p) : basic_ios<char,Tr> (p) {}
     };

} // namespace std


namespace boost {
    namespace io {


        // ** CompatTraits gcc2.95 specialisations ----------------------------
        template<class Ch>
        class CompatTraits< ::std::string_char_traits<Ch> >
            : public ::std::string_char_traits<Ch> 
        {
        public:
            typedef CompatTraits                compatible_type;

            typedef Ch char_type;
            typedef int int_type;
            typedef ::std::streampos pos_type;
            typedef ::std::streamoff off_type;
        
            static char_type 
            to_char_type(const int_type& meta) {
                return static_cast<char_type>(meta); }
            static int_type 
            to_int_type(const char_type& ch) {
                return static_cast<int_type>(static_cast<unsigned char>(ch) );}
            static bool 
            eq_int_type(const int_type& left, const int_type& right) {
                return left == right; }
            static int_type 
            eof() {
                return static_cast<int_type>(EOF);
            }
            static int_type 
            not_eof(const int_type& meta) {
                return (meta == eof()) ? 0 : meta;
            }
        };

        template<class Ch>
        class CompatTraits< ::std::char_traits<Ch> > {
        public:
            typedef CompatTraits< ::std::string_char_traits<Ch> >  compatible_type;
        };

        // ** CompatAlloc gcc-2.95  specialisations ---------------------------
        template<>
        class CompatAlloc< ::std::alloc>
        {
        public:
            typedef ::std::allocator<char> compatible_type;
        };

    } // N.S. io
} // N.S. boost





#endif // include guard

#endif // if workaround

/* workarounds_gcc-2_95.hpp
LqomdZg7zVMx2EGnzgeU81kJSx/Bb23qqXhRcv2rpeJChKAI7Y8wmEjXYjWZJACC24SquuCoTjplu1Np84p0iiLnM+tBc0q9q8C2FIYAUO1h/MYkqppw5Rfj7MFpkOsbCUo+2L4RJIa9UtmCMg1n4fp2YV4rBbHg5j90ipQ0ErFEiqF1ri6bXx8IXiXJd7osxmNPYTvRDmmrHVVvKI4fWVrTyydIGITDN5gOTonyXO+gzVzPPKYZG3pXT6T8/IbtpdmbegLkhnZWh1HZb6p4xT2WjFm3qftnuFZz1J7En+CsWGTJM1Z8F0U9SF+TSrHa2qa8k1xGBsdy9xqtDFU/0pVAE+SI50UBHmjVp+GiiM4Kky7vZGQ8Vkiw57T5/gFZx2PHXkCAlH8viNZe4R5owbkRzO42rIDjV8FmzRYiQIv0D6LOzBCUJQCTDI4KbqLaxMXP7I3DnMj/OQauEopZWPCPOLAhB7vLUrG88IQDsP3x/XGVrFWMpa/NlvtmB2RTkvIqKwLcfst22ttXL2djDBPva1ULkTHrmtrPfQ4I7rXCoX0j9YLngZyibPM+64M5AaOLqjYfAY+4RS14ZZvLEAmKIotirQtKLz7ors3V4oPHHwYRYW8wz5j/Lq0emj5jVCYSTDdcyZ9jwj9yrAgKMYJPsJAYV4Jx52H/Tn9KlTZnyaXh/sUcTnFi+UNRLT4M9MpsnBpFDD25Gh655XEKsDdaVqBkJV3GGd11jezFoD8AKiym/32RIZ9ITTDw5dkITdzLfEL2uZjjsy90bdF+FSIUkpEIrn//AE20t6kLzlKy2jkTq4CbYKUqymALq1YH71OH4QvlVreQ91jbOrooa0VZQGASOD8ORMGC84tiwsqm6K/Vz9pARQbag+dazbsE53wh84FMzp/X1m/A52QbUjmk01mhMwPk0aITro3UuljNJmoFFD44giVxuiikTQuHNwvs0tEiUhCXUvb42lSGt6YHNLG3c2K8yqD5MGKWAGdJpt5zQIFS8ns3aZprqx/zv4NIsHUo94JJPgnvFVNOvIiOddluQPmoJHWe0+2iEe9kmTJfaKVz7pCdObpkzf3IdgwDnlmAc69Tg+Mxp/CVU/Bm26LnwWw2aVdjQvE1gr7jvUv3SI1zp7zAbOsHhx3SQ0S/KEay9eTWDBZ8a98jScverAfjRkV+5Z0YcbR0rZPomXvQ75TVZ9qvCelEt+7tdo2fV0CqJ6Z+lsUx2NsXYar6qt/db75x9X/SwpRaigwnbouTsp81cBfaf+khUxIFoxeYevh6PQ8EVkkG/m0EaA/PsX15SM+1fZdBZHSnd5wI5/TSl36VQ4Fe07+ZNVjXxMzQvvBafGZDV9gj/jz2Rf5DenWhSiMQ6ZfSi/qlQ+zptrC71oSB7uAQbPFb5gK1gqm/u+v0sKOTBSS+Cx3AtnV70xvCOuIVRyua0NMvFpR3QJw4SYd/cJZoqtVvaHAO2DZX41kIbCF4pdmFxkjFK1nP4zk0xeqHTuAJwS1e9WN9sA8g+gDW4CXUoJkq66XXzsx9bTWPR7uvLH7fY7Bu97m//jq+HdkDb7MvqNz8eHQ35DUutWBce9Yy0rsd52sPNTHwVWAtz8hiZmSa0NEtZZyNcXZLdyC1qJOxz1IdHPB4kEYzQQqrNwyrpGliFqkJv685FR+ullK9mrPoOVf1BxsF7GN55PnHr4IRF2a7G3/Uc6hPiJ7f5dFF5ch1zyJQgN6Fh4UHsL/wM3maxB/d+FCvoZBkLAfeT5X1QC7Vdk05pJNqL4JK2vobhYNvCAjU2/J+illg/LrVqJ221HF0+eCTHNWweNihvu0X3oNVvuBhp+KjygFHZV+yMFHKAZdh/bF1I6l0GYXZR9GAD5RxWl9tWESgggcNMeUpHYnXZDCbSwMix6sG6Ale+dyAh8Qt6LexvWtXsGKvS6MJDgWc0tDTs+QRtDVCJMxsP1jd3smJ4GxfuIOT3UGqnmsknMsAXwffDpgy4Kw6SoUzz7nB3wlsWoVO/RuA/PCt8Q1mfaMEz9Y2is16s6ooBvR3tWzPAgAmUXKCUzvc4cu8qyFbZESaNdOzAkUbiaPJx4e5raoSqhpmnVvQy+Vm3f/RnCixDFYUgRAq4OStV2tbPxsfLKUpgPhrWP9H63f9NMU+xyRxjeFRbiBg4pCDxzlhxcLmGQvrgRuEPercd5QpTecRGRDIm726VNGvszL3iIsrSNmwWeHuBQx13GeDkWYDVBs0yGie658jjX+ya5kwUrNPWS0ctkXFWsEu7wz15x/8h5thKO5XsrwKExM4xu4agHmtSgWOUcY30GOqzfFOiS/gdbpUJ5a3AqwA+H6d44WIwueb6wYhwafz3X0VLLm3+y7JPFlEo+4u331BXQ1c+mbRiABDX0E+mW1ux2yWhaK1/sLIFdYRYTvnmmck8Pp79s3YWNpfsU1fhVkDcEcQd8i1nTzKj4hd5+SrStZ1jl7kpm6+mhHgOuuN1KulsU3DVr492dVcL8Tr7Y9CHSlG9LBOeHgs2Zg7xkZITTG8iBg2bjunca6ey6o3T5ehIUE0N1ssCNciNUXdBI6tYmvCZXumCDQm61cslp9M6oO3a8nrdYvVYV1thWZxYvDZZXwEUEG8nL+cdrLACYRc0mUIsrEs6O99F3Th1oju8Lz3cfi4DZiIoF+hGIUzihODo0Ab/kmUJUIEdHZ2fNacs7Z/INq4w8g21C5Nm11Ke9sdFF4YnEE6B0QG6Y0s9SVxidvqpO+bz4C86sc3pU8ANvzDSCSCPHTjJVSHZYxk3qhY11+oCgf+Xt4cBAreoBRtaiGNxMHHAavbEAx2T2/CjRuCFBMH88EHl0a7+eWctkJSLFVngzm1XyBPO5W4/hxhKFxwTZPyNSbURrIu8fO/7UCSihB3qyFw+ABWX8j7X2v5Kq7jnFBKwG/cdS74GuWckPfKM4XOIHj1eMzzbP/bZYAJZEjlbNI6TUhTI6eE9iwEtfA8/PQUrbhEiWI1zDG6yNXVK3d7I4L2beeS43sal40p94nnIEqow2JEr3EYuGfvoAe8nBHQ+Vz/lE0GaynBaE5qZ8kW6q/mRrZe87xIeT7dkOGIvrgaTAnvjjaFntuAW75ZssL0hGrLuuxjVk/oujGXGhgnUPJhW7ekoQEU9OV75tzlJG6u7hx/tzxVN1SQMxRrPnwtlQhIzAz48q3KJ9rrZU5AqI13m4s0dixMMR+0y408k73479H0/Es1J9L9rPXOpRWk4gJMtzcWO7qS0FmnTQlppErETi2FR0sEn3V6taWgcX9Yf1Oz27v4xgw5Ydqcc/r0XEPTcFiohu8ENvitU9QLEJ4nVIQhksUKCP9Yv0ZueohvrUSTb8tAH28NZ7EMQ+dsY/tg6HjqqytMtsrY8Xnv4K30fzWdL7j4By2H+zjojL2rDGszzvWZtazOF6A50cn4/2gjU7vHOzC+H1yIEUlnv7VZNX6yy+tUOvwb/rcHnMu332XbxN75NPa7qkBlxnEzDm+jSep+n3M1jYJp7AjcyjPrZHR3D/ce9rwK83g5zuTXmkKzk7cctz4FmasqnM6O1Pwn9WRXbPZrBNYElntGA54rC3EiVuI3X+pL9sE6MgMPMRyzWMqhyr4TcC0bcmsl16cM+IDzSoFrOVNiR6wEUDTWu/6jMy12W0vajJBQvX1PSHTO+xdcgoxOIsvRjOPa+KF+zabFEtlZCaaaOZrAalLQJoINZymNZ4LCx3MxxEz7SbT37r9OvmR8VX4/vtg/RtDNbRv9t2lTXIHL53gXFpcC/hqhch8aW6H5HIni976+8VQ63GJLKZvF3lMnorUZhnsy0qc9tuMDjjL033nCKoB3oU9/9asOim2qmcFidx2SWYZmnIMzzOROUOCW4DKI5KzA/cDRZQSacZ61JEBWH2ugrbw7ZewnWI8cb3JySz04FqWqJixvM861cCVYVw/oR5NDGuukArcelkO/qIB2QL+laTEWdFJZigrc9ypysJkeUL454UepJ+fy/gMujWmgbwe3yFGApf//5zwO0+FQ8wVuK2W7IrwM2+b8RCLqmUtVE/b15z8aVzTq/C0Tf0QtXJTXjM8ffO7x5MvU45/WKYU9dy4Ufhoc2bF/VLgYn7xYZqXUu9k00OCky/SAAwHkVYelRhCOMe2gUeqYglyLgNW5fam9jeaqZJ55xezJeR5amiYfbo5ArrubIuv6/5W7tXiix/lM0zME/JldTregDz4JgbzL1cPHNKz3ZJghTXhrNRD5g+GXsUrrGnY5/KTq9u6/l3nltXgfSmDL5OzaF3fWu5Z1dRydJyx4ODPAOwMey/6uP/9FkRtXq7E+cFFsvcXnY8DnKcOwG5yRBHClYLdrP/0C81JJiBSlb5eXkj17l1Wpb5ix5VBhrtni1HSW5GjnWJFOWh1yCWO9LG8HrnvYPULg1zdwqYfzAMu+o7Jvc/Msw1jPzDvl8w0LQOvmDsGe5eg1rFNwKRe82/8j/VGOJNMeZx1WkoxT3bBwATmHRtbeCs0ISKwE1rWYNv0leYdtonv7TLku5mxcDQy3RuKobeNqf9cTRLiFlF82jS+K3XfHpXoXhuC0+pfY5m9DcIO91c6UeTrdpnv79Sj79nOO6ivNNakHqqO5+XX3vUutF0C1I/+wdmEVy9eVu6S9a3ZTaspI5WNOjqs6nNfrsZqOU6s/2KWZKzB29Cu7qjeZu8HeRcwL9+pe+Q1zKP17ux6D82nsvswyKtqTO9blNFTgKE34Ecv3Q1A9Q7LIjdaoLuRVZ8WAJ1PJp+Yu6nkV7iE+LFDSgW9VeyGfA0SXBT+9tnv+pulnN7e3niB5ReeSe13qlLPgNH+Yi8Juh8V4rIjPaVkEiXJST0C187IWbwHBVGsfdz0c3m1TmBA+zkkxEgmiCowUJJrUH+LGmzs3Iba0p4+Cuxx9lFG8q3YiwxEVYjlvwn0lBboztISXSFoO70UoYVoS6aTl+hMFJLzPGY7g0uhCnWMi8tAVnSKI0G57/rgYoLWtXprWpbB5DHrUvCOdYknXmY2Z8ewtdzFnndttE9U6oLBuQY1tdY3FEPsgWqjEFJ8+s97CcTFsm1lWbDTRQU/Iu1XN99xA5wWI6Gw0uP0FXdkhFtRmTdcq6wYRJKE87qb/8AN/4FCF3e6D44K0bjO900aE59IIQeTjdZBAgZB5W7yv5GyMms+1gW5eHyBH2rsNT3Keditv5Dqx1CgRdHOHt+rgRZBXFJYQRH/tyJyzmxbEE35kxegSMrROgmJdKFWQGyqdKRRdCBD4rooiCJFHJYAxpo2X0NH2BD/pGDQmfNNQT9zkle1kKD5kSD7f+7MvlRVWkmgAadK8hkwv1y9zszwUcE2a/CnnHPu07Ez3OEBddALiJ+UCH7EqaaspTYSoUfS83LozY232N9QYdrRa+2B/l1ezdeizN9Fat/Y8K6HmvNWnrBXLyClOKo6lxEm4YwLb0ORaR9lQU6D6Bu7Rc8LuOOYbtG5n7E3ad1XZizNm3bxzVss83/PvtUkMNb3YO9Q8Vl3wM6C+1kZpEGyzAFgZqTY/bBcPmTbZ2z6g6vu9MMNJ91w5eB2WHvP6MTlww7PLv39lm3mh1d7DckwNNPI8ZDI+uz5YMzNtfdapOZ43UK0Xfwv63ihAbXdVptO13wpe/hElPCeP6vI2Th/XjVPrtwpXuY87GnB6tj81kyGxcf7uJfdzsLvMoDM9kF87arLZkdHRW8/VNpSI+8DDbJoKAlccxKZS8DNNMbjNn8dMmcgwG9/bjlhOUebP6y0jWy8ErWcjrqObDjXF/tQdYed4vxwOCli5KOtbYf4V/WTNmdt6oII/7D7yF09sh4oA30khV4dp3b+X15Q/Nd0z4p2Vb3aEgp++/7dBFHrbYlhdibIdr44+JN8FcVBZ1bXWkbFJHKxOMpUzvMjxTKiAJ5yOVLaCOyYvg//uxbnPww0aY73B32pKgu2eggZ/5Euay7A9t/Y47bxG94I9hJX3qq0Y/Nua3WHVMRa+4T/Q1/DfDaEmozkr7Et3E6471oGShAR9WyYRmJjLT9YxLnckOcP4S94l9zCmTX2M8y3iiP2BRo/GLEAqd4KW1cdtfoBltR56tF8bKs4Dd+s/hyNrBYWnfMHL4Dx4J3M6ca8r1p/OF5wL8/2eWLBF3LjLAg4e9P7n1UkWgeVQSesFAxGGb+O3D5Mix4pmed4adFn27r17nsu9G/NCS2niH1rIWdCL7FXNvUc5uLHhtYO952tsy7Sa5c6Y5b73Xg31HhU2bKzkVO0MtA7KiXCVWsx10DWK8D7Zu2EIIZ56d0HS3jWiaBbOfPhMjaxSUPVjdovF3oyZS9fUdHn6A/AZLTOrRnp8K9PwvlQNZ+f6dtjNEvfcDcBMxys0b1c8/ZvsXab+JSfLseuh4tv6xp+EwRfC9a4ar3Wo3kMmq3SQ7wkGS6m+pggNi9x5n77FMywYe8PBXcf2NOHNgcxdm7k7FpG8X2BPIDM9e1dmqpfknbVmX+kYPiepmpoL825eGE4x5N/lu6FneASfr9caUHSvy3YoOwyoWDuHe2AuCp7JnyS/+jooO3wnvrZ3adMHqvv3Fdbtu3jdeiFxlO4lvVq6uP1k+WvO8B0Np7MyKo4bpWPmVI6uqYOmI22f/Vv/o0VGD/9ZaoICPAt5p6oLQs3E+PohGqurAR9f7D2saoRYheFWC+J3dssY2FMT645kkIG0B7kRhj0VNtVUpqB2p8FEr90z6hWuLRDYf9pRp36gIMP56/K2KSjnWedw50OoR5SQuYiaMUCm1O1w15VrgPIPC9hVbZPnRN4BcRz2zET92fHPiKquKjr1qQsKqKJBFPxDJxEvOFxuQS1JU3SA8ux3AW68uN0vSno6jbU4h2uoXPewfpFh3X1Fz+LvYE34YqxcKmpZqupGqX1myPcTgBv64OqVPNaUnmkSMmCwLEURUef1BxMwmAqxl/DGzR8nWNX2p8MKlkTkxPCfgH/939KPqWa5fnL9phUplkmJJAo7nQv/6RpFx+7Y2td98wONBXzc/FfSrNH5w3rH4TxUt2mXKzfYs2NXGpQjjXY5E3teFJcjXuIm9nwflDoDftCFgo+rd3OFvzEUo425o/6x4z9KaGkbQ88LIaj4VXZa3G1wIMg1ybQP2WyVtRPoiX9B5FcLn1mK7OucUkGVqYq8+KHpJvKcoxn2Mn6uLApxlZOmBk+aHhyf6PpSW+DWIjPIT8Ltae7ELfqFBxujUQ2lt1iz9Kjl0e28WcPEIbL3fNxd2MZqFKOlymD4ImOsye4HcpFon9iLG8p9BsvWk+yO0Eug/slnDSk81/te7M5UEatQkV1vuv080BpbsPQ8rO5Yr5BpY8Z6afFuv5ByUyGlZFLTiP50FKUtd+q/qpaK13jpa8f+E2Pny/dt54Vs1jPlZbsM85DRNFKBL89AR1G4fyffkxrvJIjMf35hm8q9wf9rjPm135hy+PF+A1jXvtcdU82anJ/Ui0Z0RsYYOn19QvuSzUmqfzaggfiMKPZiGtw9bOXAVR2ph5fdwyRddWH3icZX2Hz25aY6awucVBvLTCUagtTxd415eUqFL0DiqtVe1dRHut6nCfSKOHGicO7b+UzeUqEIU9w6aNvwO5xNrydmqJ5gW4f3tSfQymu+j+MD9R2VBDKBU9WPuuVfNCfT+aua3bscZ1IBUqVDvME220zZAtMm0KvSzxvET1/5v493Vb3LERtVGTgWanFk5yet8mupc6igNajD/d2JLut0etpXOaFTD8kyt6YM4+JpPC3nTjhAtV7txyoK5eujb7yKgh+BMtVGpwnPl5VukU8gcnoRJmC+SYV9PFf6F/5R1grPVfAAxIz2htYOQ0CshyWY4qxuJiHamW9AkwSIlWvuSYCfDzpayJH8+NUtdBNDVNKb3VEgflqWn3y6DDMVPK78hHG/maKnKCLURmXrduU+mFfMJJt4ZQvGs57WyK4l5xB9nzTfdGgBSQuVn7IhCxp1SnVmUjVnzYEiYRGj0IfkTORx9CnckmeDuNj3HBujLI1hy9sOS+YNvwV9s1WNIm1etejyAkQv9C6yQqr9I8fjw6KlSKW3pVvlfSRyFGVOOZxT9InamRnCzwXS4RBejigcaK0WLoo2Z4EdkjLfX4ZHZJKqxvm4b3Wd170WZOtFBTD6vqBpKXw0L8ECckQWkbJ5OivOlRACOQc7odo1AVHfwJvXYO42R9H7IGqzb+Mpsiwg5xQ8CdQBJpVvSrDkOTLcd94kvG982D/AWvxMVq8ZlBclVtdFqefLeROx+WCaz3VOvFlaYS4RckWlXYQyBZHknMZ2/fdtnSpEmyMCis68cwn9ZmoO52PTLBJNovlc4RxBtIPnoimakDPARDESn5YYN1JzLhOiFPReyRtTuhkfNgpZfRMsRMMwfcWBCUwiefMs9CCiVZMSUR+oumC8P3JsB0VESxKUKEK5r8dTjvGnPG4+4o1pgGjOvgO1epM66Mc46MY9IpkiylILWi2F8kjhzSVRUWQ5r6ZMyrtM0tW1xNwKkGwsufuy1lFsWwdFDaI3G1NAxFGgzYKuGU5F4Soyl8Ml4LipJ2RE7CDt82KI3wO9NWLkdSCmKz4CfTr0Dnv7ZYhP/m8fysociVgZr3kELp+2cx1ZvnfEHxT26NPOd064x1Y4Pe9na8qeOLlDoetFlkqLNj2MMJhJtd4TXdZq/oao4LJu5X12Km5RcZRmRVw6B/uKqACzLLLaMExxZhfA8BFgYQXYvV1+/7lzWF4FuES4KVUdDs/VN4ulmQJeBznH/JjIzBFGziHyvVcLOi2GM3fKPnbTRAo6JV4oAw2Gg3iRwvkfqTAQvTpm3R3SMmb+g3uDrkB5gN+DGG5qW0zYjCrc6kbzA1Wj8MXEKOxRsHCICuo0K/pSsK/pJqi9BfmMCgzXpUf9mzEfxfxKL328j0bkYU1DCY3ZOsPfpgSR/CEplPx82j+XRi+ur/15lxrwoHTIj/QVkQW2ffSrJP5eO7vPLxs94anc7K3w5tyAr8uNNP/+jyPgGe+KEFC/xd29rpchHklnBnuPD+nf/qIF/T5KVVtg3zaYlp7ZrLjnwnUN3rFazjRLXmZGHzM6D3ugc6OTEHMuHALOPCM2NHLtc/2e3vcGlyuPkeAbwXqnSvds1rmZuo8e4FrKNYOtMh8=
*/