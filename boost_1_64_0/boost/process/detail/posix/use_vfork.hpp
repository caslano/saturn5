/*
 * use_vfork.hpp
 *
 *  Created on: 17.06.2016
 *      Author: klemens
 */

#ifndef BOOST_PROCESS_DETAIL_POSIX_USE_VFORK_HPP_
#define BOOST_PROCESS_DETAIL_POSIX_USE_VFORK_HPP_


#include <boost/process/detail/posix/handler.hpp>
#include <boost/fusion/sequence/intrinsic/has_key.hpp>
#include <boost/fusion/container/set/convert.hpp>

namespace boost { namespace process { namespace detail { namespace posix {

struct use_vfork_ : handler_base_ext
{
    constexpr use_vfork_(){};
};

template<typename Sequence>
struct shall_use_vfork
{
    typedef typename boost::fusion::result_of::as_set<Sequence>::type set_type;
    typedef typename boost::fusion::result_of::has_key<set_type, const use_vfork_&>::type type;
};


}}}}

#endif /* BOOST_PROCESS_DETAIL_POSIX_USE_VFORK_HPP_ */

/* use_vfork.hpp
QpeFxUi56yn3Q5F3jz5I3QK/C7SV+OUSPy06Ltpa92H6OirHXk+p6x0e2dfndZ7l+s9M73t1QylzLWWGSn/UjX5BnSt975Q7lNknOTLeJ9OGwLnomG8eorx7Ke97qWOz6Dcoz87/6Kz0zXrUtk7uXD0c8YXG+nynf6yrcaOuTZm05RgrOUZ1qXNM9AOF5rWMzKykFElTQJoGksYZfa9K87BM4Px88X+bSM3Zc+X3jpweke9GbvYtPWUZr49L38bp8Zcv+9XwmnTLcdPJu0HaPyraI78bzbrJEdT8MoV0kVK/S6LXFGoD06xlbq4n8+x0/Xtoqdw7nne+Ziz91bk34PzLcftw3NJy3KrRT6njfpzgu8cmq37ZoebFfSLPyuY5LddQcQ25RZvzTg6ORP55AJ72lluG84qvrNgmq3GUiM2hpU2npc8iLG3mdmmZT1JlbhrAL4pWxglHj5jRyEYwudaMFZs/05/H7ptRKuRb/t5MMMj/BhymQmDejQHfmmoJkRfy/1kYB1XcIvX3AhV+KsNxAr4/9ZAK6jtVUIL+VlVlykkg3E8YXiZgX5V3JtYXflKhGfJJFlnpOPoTesMD/N2VsgtifeG2GF9YjHwzfNBvMwlJS/DJHiZ4yyxHWBLnq8fPlnbcInLzmDVidKAsez5YBE+rehUoloNZ/m9wQatvwMoL9A3Qfk5nDe3XtJG/la9Avfrny+o3ULLs45IH2dXah6mNKdPf7Lpcy67S/krVTZn2Ryhnyhr5ZdGmTPtY9fley/QxbjNl2k/q/WN+WUPti/WGKdN13mjKtN/ValOmj/G4KdPHmK9lV+q23WfKdNvGmzLdtlxTptvW35TpOt+hZFb/sRtNmW5HQ1Om21HTlOl2lDNluh2RSmb1Kfv6uJbpduw2Zbodcu+xfD+tBDJ5TvoNPmPe5+jtZZCpZ2tk8gxdUBaZeq5GxvOg9Ttryt8M2ScJyNTzITJ5/ioRh0w9k5VAtkTmaPFLk31+y6pvsyWTJyrmW8rYjbGK0xic1D/NJzuCbO8LvJcx12qQeyD3RfJxX1Sy3cjmSl3ljiWyHcg+TkCm7hPYQMu9YJ/I1D0i4P1OPnVmY59+JNQlnEHW9Gd5v+N7s4Tsl9YopHtUeofyhfnlNQrTJK1H1ijM5Rz0oZBalB1VqZS2W48r4ysjzXfMTrnZqUlWP4R2UkaMXb30PayFpKltu9ah23atQ/s1DVtSjvL1k/1ktX9bJdWXyvfksPI9eYfgJLxN+JK+z/L1ZU5qbuKA1OFWX2beSVl80oZKujeMhuReaYTa+RWpshz6ucIRsM7BcxI/nREXbuuLYs1PvkLrm8SyP13iLzfKqt/RUTrPBtaRa6/LMuUOq0++7vvhEhdpfSbTz9YFvv6gvDCJryJ1G0h88xj/7WSbL7/IXEp2XGTljHiR+VJuFVkqPdZZ+Rr6ZWPJ24N0vvtVn9LF80WSa17OjzmH0N+F/JOiIH8HrKFCOpENlLHyvhor+ysU9lO6prwh2yJ13S0kfMZY6XjON1YGZA4zfWPpowMJyJVfit24IJ8+ry63endqecf0pMQ3NfD3sh0XKr/dc7w+p7mS5kr9LHpI5Umgn0MM32+/lhJ+2f8rrIg+97YxTtpo9rnLreZtdS32Ole4P48bbH/C9UWL6+NRlM39hrFeeZUXJ/V65MvFN0eccL4U3yxvYfF9G4rr+xFcR9Tr2/C/uV5oLf4YwHka7zTXCxW9EQwhHHYWXi/zdmUX3BV6YDd4DG4PVXoUpffZC08Q8pH701eBfWBrmAN3wlz4M8yD4WQeBcvA0d50cAzsDe+E/eAEOAxOhJPgJPgAXAAfgwvhMvgAXA0Xw3U=
*/