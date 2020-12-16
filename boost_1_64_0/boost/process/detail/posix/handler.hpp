// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_POSIX_HANDLER_HPP_
#define BOOST_PROCESS_DETAIL_POSIX_HANDLER_HPP_

#include <boost/process/detail/handler_base.hpp>

namespace boost { namespace process { namespace detail { namespace posix {

//does not extend anything.
struct handler_base_ext : handler_base 
{
    template<typename Executor>
    void on_fork_error  (Executor &, const std::error_code&) const {}

    template<typename Executor>
    void on_exec_setup  (Executor &) const {}

    template<typename Executor>
    void on_exec_error  (Executor &, const std::error_code&) const {}
};


template <class Handler>
struct on_fork_error_ : handler_base_ext
{
    explicit on_fork_error_(Handler handler) : handler_(handler) {}

    template <class Executor>
    void on_fork_error(Executor &e, const std::error_code &ec) const
    {
        handler_(e, ec);
    }
private:
    Handler handler_;
};


template <class Handler>
struct on_exec_setup_ : handler_base_ext
{
    explicit on_exec_setup_(Handler handler) : handler_(handler) {}

    template <class Executor>
    void on_exec_setup(Executor &e) const
    {
        handler_(e);
    }
private:
    Handler handler_;
};

template <class Handler>
struct on_exec_error_ : handler_base_ext
{
    explicit on_exec_error_(Handler handler) : handler_(handler) {}

    template <class Executor>
    void on_exec_error(Executor &e, const std::error_code &ec) const
    {
        handler_(e, ec);
    }
private:
    Handler handler_;
};

}}}}



#endif /* BOOST_PROCESS_DETAIL_POSIX_HANDLER_HPP_ */

/* handler.hpp
HQtisnc89chnt9+5/q4jn1fmPh+s4vmHn2QE9BteeuD1n47qd+bTPYpffCbjqYsrnj/mPr+uonmARz6Pzn2+ZUXz/Sqe91i3Q0Dve9yfM3FGy5uuufP+Eb80eiGb93+d08VP7vWVHmz5u6r9N89p87c8i8t0jLuZu6ZtAjJHKGKuRDJjDgOsC+VbAibBNJgMj4In6nEPPe4rxzoXyNI+MRCt4XsD7pb5Rpfwh8N98ACSoPY1vdir7R61f0LHRG+GTeAzsBncArvArfAEHfN8KnwODoXb4Xj4KpwO/wlnwG3wbNXfpPrb4OtwI3wbboY74ZvwHfglfBp+rfbfwl0w3kM5hkkwoK8DP4Kfwd1Q5kxAmTMBq8BPYHU91rHk2seibVMRY8nvwS7Ae6EPrjP+tC8Dprr4q67XMQ7WhTVgyF8P9Zfg4i9B/flhTZio/qgTte1eLq/4q49E6RjUOcTLA8+GdeAC2BAuhMfARbArXAx7wDthT3guHAjXwtNUPwReCMfAZTALXgRz4XI4E14G58HL4XJ4hV7HK+EGeBV8FF4Nn4LXwC3wWvgsvA7uhNfD9+GNcDe8Sce43wKjSdBq2AzeAbvBtbAHvFOvQwNkcC9T3uW+88Ak06dlzzGZoHbDNN+dc0zi9TrXhNIfq/lWR8t3Chyqx/vgBKRMwyvV8Ko62sDq63VsABPgSNgAjoNt4Fy9f5fAwXAFnABvgSXwNr3uO0wbKPeknqcO8kLohUCvez+97v3h0fBk2A4OgifCwXq9h+h9OhQOgKfDEXA4HAVHwnw4ChbAMXAOHAv/BsfBi+B4eAnMgivgRHglzIHXajxug0XwdjgN/h3mwzLV63XRtjP365Km16WeXpd0vS7H6HVpAofqsc690bYtuaaEFz735kvsqsOvYQP4rYb3HewPD8BB8AeYB3+E58Kf4VJ4EF4Hf9H0eAJjx6EXfgCj4I8afjXOH6vXsSjUXgJnajqdcw4f0Ov4EPTB9bC6HqfADfAo+AhsBf+u13MjHK72E+CjsBQ+pvlhebUdQttJyuAJyH4UobmkDeEc2Br+DbaHZ8JOOpfxeHg2PBUu0DmOC2EBPB8ugMvgcngRfBZeDF+Bl8C34KVwN1wJD8AY4lebOFyveyevgl3hTXAAvA0OhbfCEXo8Ht4Os+FqmAfXwLPgHXARvBteAu+FN8B18F54H1wP74ePwAfgdvh3uAs+Bn+Bj8Oq8hwkX+CT8Di4GXaBT8PucAvsA5+Fp8Dn4RD4KZwC98B58Au4EH4Nl8B98Ab4DbwX7odPwW/hVsdeyt/BT+AB+D38Acbp3sfJ8CfYDB6E7eEvsDs8BHvBKJ0DHW3mNus3oH4blkXMiRuj7wUTYCLMgo3gdHg0zIYtYI6Wh1yYCSfBM+AUOANOhVfDfHi9+LfPL99lsMDl/Gu0vrwHpsJ7YUt4n77frIf94INwOHwInqHHE/Q4W4+nwofhdPU3MoZztWUOAtIfmYIsRlYhZchO5GekDhMbOiPDkFJkObIO2Y7sQeLaEwaSiUxBFiOrkE3ITuRnpA4T0zOQwUgRshy5C9mK7EaiOvisBkgPZAKyAFmFlCE7kQNIEh8LbZBMJB9ZhqxB9j5GvkHdk1rmXewI6JGETvhBBiNFyDLk1+Zk3Ir7BmQ7squT73fvb33dqZ4/ZY/rj5DtLvMtliKlf/H5FpvIkwrnXBzr/bfmXewm7HwYlempcP5Fk0zPYc/BGIltEeI+FwNdpudPn4/xe+ZibCJezvkYm5EH/+R9sHdnev7U+Rj7O/n+a3MyYnnoZiChuRmZ/O2cnxHV2feXnKORP8Bz2PM0lmIbmquxhr87k6ZhSBGyFFmFbEI=
*/