#ifndef BOOST_SERIALIZATION_SERIALIZATION_HPP
#define BOOST_SERIALIZATION_SERIALIZATION_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

#if defined(_MSC_VER)
#  pragma warning (disable : 4675) // suppress ADL warning
#endif

#include <boost/config.hpp>
#include <boost/serialization/strong_typedef.hpp>

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// serialization.hpp: interface for serialization system.

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

//////////////////////////////////////////////////////////////////////
// public interface to serialization.

/////////////////////////////////////////////////////////////////////////////
// layer 0 - intrusive verison
// declared and implemented for each user defined class to be serialized
//
//  template<Archive>
//  serialize(Archive &ar, const unsigned int file_version){
//      ar & base_object<base>(*this) & member1 & member2 ... ;
//  }

/////////////////////////////////////////////////////////////////////////////
// layer 1 - layer that routes member access through the access class.
// this is what permits us to grant access to private class member functions
// by specifying friend class boost::serialization::access

#include <boost/serialization/access.hpp>

/////////////////////////////////////////////////////////////////////////////
// layer 2 - default implementation of non-intrusive serialization.
//

namespace boost {
namespace serialization {

BOOST_STRONG_TYPEDEF(unsigned int, version_type)

// default implementation - call the member function "serialize"
template<class Archive, class T>
inline void serialize(
    Archive & ar, T & t, const unsigned int file_version
){
    access::serialize(ar, t, static_cast<unsigned int>(file_version));
}

// save data required for construction
template<class Archive, class T>
inline void save_construct_data(
    Archive & /*ar*/,
    const T * /*t*/,
    const unsigned int /*file_version */
){
    // default is to save no data because default constructor
    // requires no arguments.
}

// load data required for construction and invoke constructor in place
template<class Archive, class T>
inline void load_construct_data(
    Archive & /*ar*/,
    T * t,
    const unsigned int /*file_version*/
){
    // default just uses the default constructor.  going
    // through access permits usage of otherwise private default
    // constructor
    access::construct(t);
}

/////////////////////////////////////////////////////////////////////////////
// layer 3 - move call into serialization namespace so that ADL will function
// in the manner we desire.
//
// on compilers which don't implement ADL. only the current namespace
// i.e. boost::serialization will be searched.
//
// on compilers which DO implement ADL
// serialize overrides can be in any of the following
//
// 1) same namepace as Archive
// 2) same namespace as T
// 3) boost::serialization
//
// Due to Martin Ecker

template<class Archive, class T>
inline void serialize_adl(
    Archive & ar,
    T & t,
    const unsigned int file_version
){
    const version_type v(file_version);
    serialize(ar, t, v);
}

template<class Archive, class T>
inline void save_construct_data_adl(
    Archive & ar,
    const T * t,
    const unsigned int file_version
){

    const version_type v(file_version);
    save_construct_data(ar, t, v);
}

template<class Archive, class T>
inline void load_construct_data_adl(
    Archive & ar,
    T * t,
    const unsigned int file_version
){
    // see above comment
    const version_type v(file_version);
    load_construct_data(ar, t, v);
}

} // namespace serialization
} // namespace boost

#endif //BOOST_SERIALIZATION_SERIALIZATION_HPP

/* serialization.hpp
wRYbo9OBQsEZIuKWQqKk1+N6VSg9fIsuOCp6JUujUcwmztvKM3s1c5AheMRlplF7cxTGH+J0fhO7tO5o6AUYBtxCe0TQgq2xsekTHFnXqaHUNyBmoQXjYRYO1g5Ohfif1omNe7g6knXBkumEZlqE4yabusgK5mKRTeMv+Hpim6PvNnx9bQpsaBqy7iO2scEl/n3gPsFCegNDYE2EV5nE8UdOHd4+beNPVhBvNISbW5GgcdlVzQ3LRNnVomxTwfZWXRt9KqU5SqmJUFMpzVVK6adZKSVMzVZKs7RTa2n1WWIsOGpvDnpeEW/M0cY5C+eW9vM0SU8Mx14UUJWqLDYKuoxyszQyCI4prMoKXYKX2brdXg8NAdtDFIkkDfnc4HDifuZHDbDmEpYBDeu0flGvbrmbdr2SbEor2K6UGGGkVGZSysxKmVUpy5J2jJQvUmYVPlNorLOBr1XN3EglxdN+4v3FH8NFdTP/ZF4sUo1HNmyW1VUI71EnWZmZurgzeGNhlTUUoom3l+Q8nMr/PIxKVpjOvHXpvvD7X4S3GlbuAMEvJzbdqGY+gNPz4sIqW/AgUZ3QBB+rtcnjeZgpZMedf7j4zU2q6vEExgsJBdz9fCBymY1Dad1aIp4uiF0wl4fk1CBiW/KFr4UF8fZcntgeU1JjFqExNzFwFsFDPmktFn90AvUektZ9wykLDBpN/pOxhMSTmRpYsJ2kif27FaIvxMIi0YjZrMzkewMV+twgH5l+mOWUmcadP62q9rKcxW8SzIxWmmcXFZNZ7qEs86PD2RI4Af0TFsOSHH7NrkSHYCs7cVUt6Ua7mrngppizAssbh5UIDAiVX1TTv+GzxtrU8PnU5al8BLUvfDandlAg506ZJVLc80ze1shDlqZeYlf3qqwFD191550Nq+ZaQ8A8P3xeZJ8nYUk+oG4ZPsFFuLjupaG6yPRze7stf2kh0h5Z5UDiq08TphhOtwp1N02XzrLpErZn4f5/3bbwzH7LyzvZkaaoqT6rvlRvaFEjyBR6W4J1CbODl1BZzMryxRvgQuk3VnBjRA2G+f8lWUATzZaIFdb1/NTv5EV2DRfSfAXbwYKaLE81idMsY2GtOXhbYa01NC2OGykWna5wGmCEhvB14FTFj+Cl6iQBuMRMgj8u5C8RRhCZPZo3pxjHOsvP9JXqgrms+AFqmb6ZFblikqpfFzRr6eugJEk0ykPioFjhOf1SQiMkQRNS7dyb4MLEpItl9vdlGxnLkyuWS8YWWLcZ4zmDfTkzE3Pi+oc+EeSi2JDFHhfN5J/6sPhxVKKZgo2Pxt05zblJM+WBMC4epwFknL42s1m49L+gWkvpvCBlWVyKR5ti9lcP5fCMZzTTPOSjAQOaXSzv+aeT866K5RVm3rQKrx2iGfNI24/Q8MKSB4IdcfM3uKkRBnT/iXXJldSlwaLZtr5mr1ud1Bq8rR04JTLhwFiOuWzKmqSMl/T3LYois0FyRmF3nvUAdme9liauW8bv8Ijy1liZ0puSq1mHHvQ1FU87xpr6fFIL4hDwEmIihBeTGyru2hBODoPmu8jPrLjS++O1uoRHl0XGq1jCje1+F4JQjVVUkxWvZq2oJmawOAce0aTxPsyv7npNSCgTNLv92+knbcUpL0qlrRY7ScZ2/g42CIvktMIAy8UvfQ2WiM1yWtV1G2I9ksb+BaLGa0V+cXfYaXKFm7J50TGhoLGJ7g5lpbQEAjqvfM5DoEDA2FDYM9zKXz0gFJ2AMkybophdZbSc3zZRPJLaxX90C8nhaIJUaXaVy6eyYTzepTG93yEx08XnXiPUe4CTWQTu2dmFp0y7+C/HCoehV/5zaJ+ZNzH1fn6fuLvx/mTRYPGM2w3+zX4R+aaMTG8QTyZe4j8sozdRtLj3lVJEVJf4jhWJ5gNW8Q7TtNli+KHEcZxSD5Uqjm5LPXAPPpPh6TFqYMIUyqQexC0k++Hgw4UOa9DuUQ+hj+I8p3a+cJx80E4JQ+QjXHZH17KPojMltURi5gzoA+616qI30hZV6DhVe41wYGimYs19pU4t64gO00p1i9FBOdXZbVFA/RMtsBiOa2l9OwcJmxtd6MqFRMzwLO9oHKeGS81quNQK95ULFVNrkebBzQRa0cDjnAvxoGfutdbtC6USI7okvWFkSvoKkkWcJmgINaEEB/bSdb4Jluq8WdX0T48YCxq3NwszwNLCEVZtu2HiaaPwDjWv3b53cQykoSkONOaA6t59Q3Fj7YqVEJnuVELStdTpIFSHPyG5N7zQpGtNM9FsknhwGqvS2aMqJSZ/+5qRJOSbXArh04a/xvR3cPEnmMwUJctDsrTV5Yf0rD5k8vh1w3BsEpTObQcRqPqsgsboOCBmTBr752tAzDeu0hDTSkM/URigzeu7di0f75q2qABII60hiJEf6fKn5AB+I2Q9HHOboa0kFCl09Cw9JQ7QJuF9X/Wgh6ZDPQh/mF1g0mlNe3kPVckm4Rnd8DbYWQqkYM1V8xMuhtMSEL4lG6M5PvUmOdziFoKVpbm8Lh9/WbTb2s92OmReCH+MNYQC6ZAgYLpN8oiQSky0nSszSSKxKjM1n4wBm9//1Egrv/mjoboWx7/0BUeVyh6l8pgfbJ+Y/WMuntUrZt/eXJNaX/mv6LXMcYzfTwWUe3k0By4CdUxXsH3aFzodjNhwCnUvJ2A6fpoP1WmerR53/Cty7y5+CRWTOANFkxfuwzDbsPMuWd7PzhtISNhHrXDxp76IIWCai//icuj+emK8TgDe6kkAaAX3xLe+LkTsOniiHKqYlLRwo+a+6+6G+6Hu/Ho79M9my8sVJpIBSXS9PDSZWVhTaTCv1LIqgxZNKf0VDz1wo2WVeDCFmyyrxMs13Br0hnlO6BvKUKXKyNIpJ+xY6M+ftILX67WCQ8SHKZga5vmhGwqrjKEJnnLhknYGTWXBdnszLOlKjKyp4xhO15caPbz+C9gJPK+9U/0PvWDz5DvRHnWpmZgJYgVpCikDIezzsaeYn5dPMUd3sprnfTJSqTW2ptEc6jqW6fEIGjRaHbNohNhyI6WxdB8xhDT4iL4LsmdSNLRKHdNFQWi72EyjMN4+IH34Vgs31OuKAiku/uZ5CL7UDerOqlLAd66LzB6U4qb+uF18+DiBpB14ohLS3HKqwuOhReXKFkqQjvckeGYK6CMVL5JY4s6HXU4vbNBobKyUuWC726VUrlXLbchoFRFul/bTBHPxjWpoA2QI1Z2Nwk19hSlrwWmvyExVWyii0UXCgtsW9VMDI851vGgu5V5Cn8/jGfEb6RcT7TzzzqWnx4aeh8OZsTXrhIRhFdvW83Lb4tm96CsUy2/jsyU6GpNLS66ZhgSjcTMMAEvwDgC/c7c8hYMTm4ZngIXb3hwK2gx7tpBNqYPZBg5Hj7qUugMo9/ph/PuLNvHvNqwg4ZxYqWsUMVz82ykOe/SE/RYl0imiYLZHlT85mOZNCF7qS4hSXzogYGCD88kope54QgIEs4Lt7HBhBLGhSWeaQUmD17I6NIQ9hQojxg2KVYngM9ybWjOIxGN9nWhDS0rHw9Q1JbILIoQzK3g1ZQjlysLhapueOKWXkFN9CT2V7VDqkNunmTp29cJgI6mxU4TZIdqjs6zaj+X3+i75Awou7pwNUdQaicAwkddj5oSFqbjzWn1KFxwSyNESz6/pVbUq+B008ne6tF9a+mvP0L8v4ZP9AvV5Alb1JdSlZk6FxCoHQeQVJ3TGDeEcnVrUQ7PfWoc5wlYr54nvuQTHDNKMUk4a0SJfvIOItmxqHmLFWopeQbyEfcDOw520K+NdT/K4FYE3EGOuioMFVVinShtVu8ANyxOD0crX0SpdyMIEIjGRWTG+zOpEG7fvHIobyOFHjLra2HVZbSuHRCQ1bCs7TSmJUjbTR57qJgJVLo+Cn+rBtzwEHqW+hJRIHeIEwc68WqeDOwf4SGh1mHO6gIndMpXoOp9O6VJsnfYM7oRDl+OHtmmz+Pew+PeUf4Sm3ZFyd4nNpW6CjNFaItRrHE9ESRcySknMbsHtP/YUmIUeF2091c+NsvLlv48xDG7/1J/G06y/pLRvJaSt6Et7EWkzRVpTaxG8fsbeQhdMTakx4TIhdlvck7GfD94CHVYhsSWSJymsMhPVtFOnC6uswUsCqugBjBzv+jtYjxljBOsRTakfQ5ty/OKgxnuI6y4FR332z4LTiU4Q+Kn8zlkQTM1iiL9G+/KddxJhzqi/PF7S8jJRxDt8Xne4McVFtDFzERGt+uz86Lt8JLVjFx8lISRyDBqf8V0oN33Byyxbamyq0+rz8rZXiEh13QlnbVeUCNXnh5YtDhtxMH9+RdoeCyNisPPRobD+9xDuwzdiXgvkDa/LxY07sOYyxoBYmmgnCKi8dhIyCWceVl1D4/0xxrSPMZvyPkbna5eLvSP+HrrN4ytQlVcguinOLqWmR6npbnV0Yq9Sak69NmPdKGvhNPxrWQUR14upDOh9agE8p60g4T9f8ILfgmZ3dsTZ6YaSEfd/fC7B0Npk+hXhmlPG0KU4vnR0FdZ0B02D6lFn1HRm7xXiK6necIuJpdlbQ38WMIz58P/ZE242FdotdXiWtgqHDvO2N//qxJAsa8E+wmX71uDQQu/dIQOeDshENCu7274DzhSxnKJpSmYR9UIaCwPPpR9HvZe6rznowaH8pVKFC0f7Mq/rbtYtP+6JuZEkAW4LxDEYtzwmrr1Zoc3IYo9B3qOSmYxY2TU0Bf76+yFCSf/nWln2mDSTpcJFNtzjHYUbvcP5gRJ5Ji+ur+HKHb8Mht6PPS9zp6jt7LEV8nuoS7t89ltE6ApO8yLNQoBPHorTFlP8gjm/TKZQZehTmtCDtVeq4yaCAmtLzf/it/GOhL9AMsO0uopgziC8Fvqf+DY2t4N+P/7C5RqN09HgVTRWYzUJdj8MnyDNDU8S3w9SdGzxaS46oMSWtQmf9gkV7jkfr/C4VuG2eIXdsAkmJv066Z22x6Xux33a0OXM2c30BadL5AQK7lRMxRTW5YUytaCx77goRlKErnwBqqsw2/cHT7HbjKyrLOgKfzw0ePsWuN2eJuyyBxXeZQ7pSwqOTpfy8R7+p/E0tnswzF5/PrF+0RH+GQ+NsPKnxovLcYO9AcrF0uGxuzmaXu7j0y06XeKl5biv0+VzPHzyCJhdmHTh2rt1wTxCVlyJtopXEoLZ4mekwlQOYOjSj4WFGMTTE32XK6DRYFa4OFDLJ0Qzwuf1oTQPf2c4kJt+VFnWNvZpsuEDjJVUC1ecllVhKu5hl4ELptG0vFyaQjNpaHOrmcelcHePcI0FurEwH4+iBT2sJAh3Ei7+t02whveJPafHx4so3RW4TYptLqUkqO4PpPhcseQrKBmO6jLUJUG+dBMuIARhyG+g+Hkw1TfqGp4HuYq9yfTTZhJn5/AjL+j6P8j09DTane7YRsKOegMx5PGnk90kr3p9OG6cja1ipnymCTysOMLBG0y0Z6qsO2SIzBRXP/BWE6A2B69AS+PZqINWQXIAXLudTUJR9LS2d+OWQd/evZI2YpPQBnjl5R12MiL4v1CWX/fACGvASJLTMVDdDVmC6kZHUhTVAzeLnWKc5Uz4eNo/aFOYwlXqHDFBEorGu2jXU4S7ty24Uuh18Vwhj2XJWvl2lJqiC1r4G9uExcvBZbB4Secb6KcyJSyunajzg5cWCoCLR+A0QrsHQ9JPgVAMNGreZAw/iiu8V3bOSOqvuMOq1G1GTx1mnz/3AfCb4H2IBJ3+GdVpb7Gs+iN1yG98IH5llnXbey2rngKhavTDSeZCpS5fRb9uVGHYrbwkbMGG/EKImBHB+REniSz0B2muwETJEN5LpcVV8K9HXkf6wsKX8CdoD/faam4K0FLw8SnHaSQPQ1g9SlT1z80YmiuDJmWtYD1LKMORobrIspkpC8O36u4M/UPNnAsyNO1ueacMtsGqQad7TUcrbGxzRpNLiaBq9ZD6kpAbVkkW9hB9SO5xQXLBgcsciJURvHuLMTytU1xyMrdKeMCjkgK17nTtWHWjYMhZBOOsviRYy5ovNNdw6TPtvcvelm+tCc+Hc34oGb2OCd2aBdrKTlvSrHlZ0xbwWt6IkGbc6qIZamaXPIMvsLcEryc2Ggk4+5g0wtpCWDaRZi9S0/WCTHjBBYvL5zkMCOcnYMqRJ+M+foUTFCu/ZrvUIAZ0vPasKq6b5g6KaVBx65bXEctCK9reRUT46OcwCRVe45WZC4QiFP7XoeaJvxKSeCscAH6XCODn/xXAamyQ/WF8KxGG97/DWNUPBiH7VTCmkPdmkUlQaLDNrEvTtcR0c9u3DBVuzQunnRqRRTyUMBRIk0+m9t2DOiZ+Bf2F07pwVW1B4RYcDoTm+qEn4aUPxjzLw3hsT3CEugl6aXXTeqSePt1nRaY8Jg4VxB4Iu7ZR7ElEJHgJUgTk1lTUIzSZogQ/R81s9lt79VZ+y29Fy1I7pp6KeRjQjiKD2eLVKF5/Tmgn0mBn6YeumH/DTOTta7q+vm+HNP7m60OlbxX+10Fw10utb02bQahVWGMKDgWk3xJxhNveqEGpdfF9RN61C1eNnxF9uD3I71eFU5VPFByTzYGGpGSCvOKmlOQri4nBXqjAORDRlMegblZqZyhbVogPv1L7gFI7V6m9RxHcmlJ7t1JbqmwB9yVHQdmySvxbL1KDSm21smWtiHlexCxQahe1PraOviGaKVsw3K2PYeiP/8RIX3jGWYxhC3/1dWFw5rfBIPgcOv9d2Xlh6it7TXu6UASK68o7+/w2PYnW9UVka3PWl4O/MlX6EL+ODeE0b5Q0JDadlyGCDTnRP1owwLRhN2PD1uNR7ZJq+ePUn2EEJ0ZrIcWka5doKern/aLYk2v6NSSfGsJKrfYyF/HZc62Fi4z4a4Rb3/qf086zZC5fIf7ew6vFXz9fJP4+wP0/B3m3KVUTOnBrg3sv7TOK/vU4GEUfl0bRRz0XGEUb+hlFn6F0/5wHBzKKTn88ZhQ9YCZpFP2+IiREaRLt8fj466NjRtEp/N7BiUbRf0hLISZDzKLmjOsLohT8P6/FNK4wkkjt7XOs8c/7+xSusVOfba8CF+L27GLJ4xyBHVaeA7LSTjWaH7iZcGyuWd2EGP86bxZx5A9gFkR2SS+CBcKuGEdEH5dQM2+RDHEXrDh+BiIiPtpRiTgI4k8PElIhvwTtDYxvKL+LmvMcmkP07QjfO1ocOB3jObmUDwuUb5FRh/mQXIxDmFtdwla8jIYl3Gi9U3G0Y5gKq0+Flm/JPppplV6K4af3BZKLC4kfflSCOMB3jO3FVZpPXPTPx/jnP/inE/9EXRaoLVLMKToDBSOFVAppFNIpmCgMojCYQgYFM4UhFIZSsFCwUhhGYTiFERRsFDIpjKQwikIWhdEULqFwKYVsCpdRuJzCGAo5FK6gcCWFsRRyKYyj8DUKV1EYT+FqCtdQyKMwgcK1FK6jcD2FfAo3ULiRQgGFiRQmUbiJwmQKUygUUriZgp3CVArTKNxC4VYKRRSKKdxGYTqFGRQcFEoozKRQSmEWha9TuJ3CbApOCmUU7qDgouCmUE7BQ2EOhQoKXgo+CnMp3EnhLgrzKNxNoZJCFYX5FBZQ+AaFb1L4FoV7
*/