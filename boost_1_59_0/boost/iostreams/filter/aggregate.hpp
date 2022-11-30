// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_AGGREGATE_FILTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_AGGREGATE_FILTER_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <algorithm>                          // copy, min.
#include <boost/assert.hpp>
#include <iterator>                           // back_inserter
#include <vector>
#include <boost/iostreams/constants.hpp>      // default_device_buffer_size 
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/char_traits.hpp>
#include <boost/iostreams/detail/ios.hpp>     // openmode, streamsize.
#include <boost/iostreams/pipeline.hpp>
#include <boost/iostreams/read.hpp>           // check_eof 
#include <boost/iostreams/write.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_convertible.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp>  // MSVC.

namespace boost { namespace iostreams {

//
// Template name: aggregate_filter.
// Template parameters:
//      Ch - The character type.
//      Alloc - The allocator type.
// Description: Utility for defining DualUseFilters which filter an
//      entire stream at once. To use, override the protected virtual
//      member do_filter.
// Note: This filter should not be copied while it is in use.
//
template<typename Ch, typename Alloc = std::allocator<Ch> >
class aggregate_filter  {
public:
    typedef Ch char_type;
    struct category
        : dual_use,
          filter_tag,
          multichar_tag,
          closable_tag
        { };
    aggregate_filter() : ptr_(0), state_(0) { }
    virtual ~aggregate_filter() { }

    template<typename Source>
    std::streamsize read(Source& src, char_type* s, std::streamsize n)
    {
        using namespace std;
        BOOST_ASSERT(!(state_ & f_write));
        state_ |= f_read;
        if (!(state_ & f_eof))
            do_read(src);
        std::streamsize amt =
            (std::min)(n, static_cast<std::streamsize>(data_.size() - ptr_));
        if (amt) {
            BOOST_IOSTREAMS_CHAR_TRAITS(char_type)::copy(s, &data_[ptr_], amt);
            ptr_ += amt;
        }
        return detail::check_eof(amt);
    }

    template<typename Sink>
    std::streamsize write(Sink&, const char_type* s, std::streamsize n)
    {
        BOOST_ASSERT(!(state_ & f_read));
        state_ |= f_write;
        data_.insert(data_.end(), s, s + n);
        return n;
    }

    template<typename Sink>
    void close(Sink& sink, BOOST_IOS::openmode which)
    {
        if ((state_ & f_read) != 0 && which == BOOST_IOS::in)
            close_impl();
        if ((state_ & f_write) != 0 && which == BOOST_IOS::out) {
            try {
                vector_type filtered;
                do_filter(data_, filtered);
                do_write( 
                    sink, &filtered[0],
                    static_cast<std::streamsize>(filtered.size())
                );
            } catch (...) {
                close_impl();
                throw;
            }
            close_impl();
        }
    }

protected:
    typedef std::vector<Ch, Alloc>           vector_type;
    typedef typename vector_type::size_type  size_type;
private:
    virtual void do_filter(const vector_type& src, vector_type& dest) = 0;
    virtual void do_close() { }

    template<typename Source>
    void do_read(Source& src)
    {
        using std::streamsize;
        vector_type data;
        while (true) {
            const std::streamsize  size = default_device_buffer_size;
            Ch                     buf[size];
            std::streamsize        amt;
            if ((amt = boost::iostreams::read(src, buf, size)) == -1)
                break;
            data.insert(data.end(), buf, buf + amt);
        }
        do_filter(data, data_);
        state_ |= f_eof;
    }

    template<typename Sink>
    void do_write(Sink& sink, const char_type* s, std::streamsize n) 
    { 
        typedef typename iostreams::category_of<Sink>::type  category;
        typedef is_convertible<category, output>             can_write;
        do_write(sink, s, n, can_write()); 
    }

    template<typename Sink>
    void do_write(Sink& sink, const char_type* s, std::streamsize n, mpl::true_) 
    { iostreams::write(sink, s, n); }

    template<typename Sink>
    void do_write(Sink&, const char_type*, std::streamsize, mpl::false_) { }

    void close_impl()
    {
        data_.clear();
        ptr_ = 0;
        state_ = 0;
        do_close();
    }

    enum flag_type {
        f_read   = 1,
        f_write  = f_read << 1,
        f_eof    = f_write << 1
    };

    // Note: typically will not be copied while vector contains data.
    vector_type  data_;
    size_type    ptr_;
    int          state_;
};
BOOST_IOSTREAMS_PIPABLE(aggregate_filter, 1)

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>  // MSVC.

#endif // #ifndef BOOST_IOSTREAMS_AGGREGATE_FILTER_HPP_INCLUDED

/* aggregate.hpp
KBkRClI6vXN8uWK2mXG9KuD8YX5kVk4T833Kc8zfDsUzWY7b6Knk8jrDD6JGXkF6ba08b+wWTqUWvYPMNIsDjlVYLPebWX/JsEMfU4f/98vD4HFQfxA3otN6pOrjEnHR2Kk7Y2MCmcxFUFrVf+41m+KfewyljKgsDoh+vHRfxqCQ8ePfNC23qdy9chkWICKt9e8v6aj2kUWfltXXF5HzNDKOwUZHOR8VjGSSyxtVrnuhWC/wRoKN+Dau+mKM/nS5UrMwm85qes2dRKLg7N7FvUEzNw81ifHLJ1aXz1N6SWvctlIHZHzX/c5X+y97nlzuc+LvzXIDKGvtVYECPUycSdnRPA75lZSHZHm6y84DVPK3+cWADD+b1Ra9T2YebDSrOtR6mVUQDUFLBwJdq6TjRgPQEKStKDZd9EpZxeVu6zTMn6DCkiq6xm1dgqTiOVo/N03SJnplbTq/cKDHEvv7Kr3q3h7n5EWXJTqkKGAjEqjL5Hu4YTz+blBm9sNpQfFhtVqUsyzaQW4iI/SchCYEfzlruv/AuZMOoVHYW3nRCd9mFrUx66LIbaH4dawaP3pgPWydcQOHi6uu1dBtpPvSvqXFi43jv3AJc3U08IR8TPFaAbtb859hBEBMF1ANIW2CnTMlHPW01bH6MoFCsYRPFokvHTy2ZPk8QbB8bKGE8Lf2sUsYDe/C2n2ktPuK/vb+qsa7hc/8uhYVeCpGM1F1uTpx9at+8XvrAgp/8stoo7XY7ikeZk69KD/2BX5svyaLIlGG5wALLj9gENunY16a3vdRqd3R1yCdkzcoCdlUeMhqe0x1rxqKl24R7iY9cmtilwLU0RRUQ9RphyOH7iilF4bApvQmnd2xkwUUelcme+DaaIe2keY3bk5svcz4hkui8P+rnmv4K7FMyiyfu3T20rpC9hDD9nf817Fbpf046YgVLolnZy6kEa1LsMSaAvo4OLiIdd2m3ZU8nRM+DpbkXvZjT5O8FNuci4scmO9gti9kPF0KKgk8Mla21/XHjelnegHWALIv1BwtmBvUQzMg/xo+t99eDZTUr6EPdJH1Viid/nTaXznwz2bAAztbFfXyQla2aUu64+Mha5gvJYQ2etpzNPct5xBe1Oo2FA7StX8SfYpcpTCBoAi9HHNFxXD08FK8XFBFICZeGF6iEXX+3/NvKBoxt+2kZiEJwuuEVpLsmFtH1IF/4eaXcOrCzKHD0kjxs0Q8u+pMAv8ypmqHXiiWl6I6C2jvrMma84FKMXE6kUQRJd/LBxxkkyzDYS4uhlYXtDSSg+SoCZG5VKK9oHl8lZecVoOWw+rv1iXKUWbHsMzleBktExh/ON1glMKBZL3aMaw2eoc0xf3h06cMqOfTUik9hU87HfTS9zfsmhFmfSzP0tjqbJHuAW5DULUkzxoiLYwbkMXe+0QGLdWKTGksNnVGBd+0MjywPhThXuPJ7EjrqaFlFWtsVS4cCynxV7/Gd8V+8gC4CkhELXcoiUyWDOaWlbCb/RPptKZ9pnnGITyu4p47V34JM7zvbmxi2D9DqSwo7OFWEMA9JT8tc75JgDNXd3rXNrkyZKY3ls0d393Xu7h5okJLAQu94N/IUFbAOSkeNGhd0UZ1sKHWymtLFHZ3MexmPr4JSyjw4k40r2CORUYvSNLCjEDKryOaQR2B9B6HYvTlY2egAawb8ZMxTnh2ngxCjAylaxlqweRP4UMgnnt+V6SaPN5II02z/FvK9HUbiCHx7LnDAXlpoKwkmNN08ua1vtMekyiDv74uChDMAP0rm6LU6Xpse+HF4YwpmIXDPJ/mtIbtnkW3sWLH9Kj8fk55CjtqjcT/CjU2cIRC6JU2F9UvJ1QcDaYJVAJC+BqL5wHdZ2hIBK8jL9bk7GabtjneX2B9vwJZOipd11sXMWnDplD9WHotn2r6shII6CMYOM587HUbcTKGsRHlRT4iTauShl4eREarrbPk4oIw20RSpvi5YQmy7NgmGiyrynJ7GNy83kCFkDdc0ddHGmhrMFUUXc8oG5dlIx1AUCDXGN2PZjziEaigTk3whtH7FQdCMYrKYR6bjqX2qeXeWxPDjWVyEMSsq3E/uOB8DubFKk3Kxm5YxclswKhWdf/tTJaUu52Tg97W118R4S5VHeqxy5fDLilKSHGNOiiN5km1FLNJaqiAuUjk4b2JbB0E071r7A8FU+yx6aNrJMke3zBtd04+Yhj6+iHRH/CI27nfZbcOd1VEVtGt7Ip+ciZuinXrqYQcX02i2jNua7z7kqHY4DAVS1wqYpUFngNE8e7YlPB8IwSVXSmLW82qfxXbu+NEhKrNdlZUG6CshEe2U7jzGGltXJbYo/zjbqd1MTbT6reF3WU5LX5yNr/CXtZGQ58NSjtXSd62TMEJS7XiPUPlb7RZ5cOrN499vuTxd7jDFGAbJRIblpyxcKmzUmiY3W7WsBAPY0D279apMZJIqCF9IjbzT7aEQeqJKqvnst0MFw7ZOUuBifUO2dLhWaBAq63uRyKehfKPVFvMFr+YSnwbKnjY5agkFTz3+8zk59uuMUGkdDhIhK+Y0ZnCRzx6vtHRIZF9pwGshrxr1JQuS386NNCUHOZEiFdMkrYgbp/QUaqZPyOK9sBmUG7+A5cpfpwxvkj2pCXGMWZLEfANHhza36erXhsMVAspbXw3xvL2PwReWv6VUEglUQT64hOMfP5ekQVncj6g9OOO98pWkZRH8MYzFf2YooT5U/WGV4Yc7Px0m4+jLHKkSlQsIlHMqZmpMsndBmySkaoFz1dTCjJS+vh5erSxQLtlqVLSNHNA+wZiGlnoDVdXldMSziZtnVneJO85CMDGbx5hXLu345fmWcAK8MEKT0OvVNuP6zlPHX2QZQ5bMl4k6/f8E05sJ7b5UbqlJa6BWgEPxQjwKEzSRoGHQo9l3O2Wbup38VtfGce9XKbjOn1kLXxnEi4HNTzNMOzpykfEKlBQ0PXf5vFNRvuauX3NzjBU1FFc8pYwRhqEf9mIPKZ2w0bVmIBx3OSDUO2mfEZPWXKQPwcagUgx1eGVBiT4z8EWvr8xQdpA3Xye1hyHOsg/rxdWYYZqtn/WovAwNQzkxvffFNeDXSpG+Z5QVKgY53Kv7zIklesaSrlHERHmPsO7xyzIT8TmEIc+RhrxWnzIKoap3bXsrIjjH9X9L9SnkiQKPTdb3XXY6EwdylHrxqNu2QKvlHqDkKRYRWNxG44gfXWRU6osPQA7YkjRnwwgjjeh9I8Jfuy94+pEPrE87sZdwQ0Cb2v8T+B+cO2rl3QdKdBfPykqfeAEvJAzOfeVS2uiMaTlqQ44pupsXVdKDscRRQuAxfqd861y30N/Bl33AZGfDLrECNiv/GTu6JAX5vx6ayJU7Zurac3kh4ZJUZvtJfQr1fENSWd7bvOExMuiVH6qtoO+z5Mn/giEPv2W53QNCAPfD3vwIrH5UhCYawYQs5yv58amSihjSEUcVdfpsj4xCK1tcg7t0y3yxOv6zGtBIRWb2P3qd+Kox6ybiWsbXexL6kGjbAq7WowgY1tYbSfcoYgxjWQ5PEWxoyrnDjKpWxqw2EdbjctBmZjCT9+ticOKd/Di0r8vrdN3iI1W04p1uaA2+asKfdO9TqwcIY/2p8vUB3l24+uiznlDp/6lz6eiFhaaPsTWJN8XYfaxLGUTjT2YPjjk/tfKr1+OZHaPL7okAdSwH21P1ayc7qCUKh/MRnULnkyGCqVLeDeDXK4hOni6Mo3PWLz6ctfTKRBmJCqHmNY3zEnb733hLca8CRU9iT/MRXMtfq7EKfWsexygq62RXmg5gXhRByaNoVuUKcnxtO/kzdGanHH+AxWl5FK2rOlz9OYE/GcmnhSm5m0VHGXAIU2uaBR9WdmubVwtNkrd0de9/64WKwc5fbRaTDpUpIuHHdUrMgFEqg+24gvXrpTbtx1hujOeAA6PtB3qGM8LlpgU9XLBAHEqlN82Z2tw6rf04fwnTVHzLRmIBvHJ4kld1hafeqyP0l5qxD9f4Bj1aKBAmN78mYe/hiLeSKxsH+GbidFzyqcArkWLc4qoWddopVRhrLJP44t1yd0e1RbwNfkluOfpMe4X0+y5mEmnhWjkLrrNbQcjwgQmWS0XxfJ9KOb6M9F4LfUw/YL0fFzsspLyT/Yn3HGKaYr+kf/eE4SkuO8J4EpV+iwpv0E3LiB8rwoCOukAJ2JVX7XRxtlLaG/vxcFSO9bQq2ibPwif9tAX8K6F/VT2p6IrFtIDCIqMr8LZVT1xI7C8kiiH1S+Y8bLwb4wItGHF778fgdVbej0g02vCivNEUe3z6LfXjlfaYREcWBB7pMcgRNjI080fHsTzaOu+OJPjaTLPaFpLQ3Z5+QiNaY0cBn1s3RJlAspQf30Pr8dk807wCgp+97rJDb19CDbMXvEEEJjYtUS6XMtIdgiELDdygw+S1bslMtTHQPXlEwEgAXu0r+ey7PUfrs2Qpun4YjqRbXaE5wg48gkkViE3A8a9Ftx/LmhFyd52E7TBaOr+MsGLnPTCmW0nRxElFS8QlbccPMTVa0Jj+YetRjGvKGJkJC6BjT7C9Y8VAaGhIxQXY9bKmaq/wHsUs4vK5j8uE2rgDL188/f109+Fers5GRtasJeFWQhaFBvpUXbCsNwkyoOlrxK+jwjMUgF/nc1T9Ds27pwjIyzpsf26R00J4stE0tM5028joaiXyI83biHsb2oWqW+HEHIoMX9Nehv24eu9y3rvoG2TayGTDD6/LsHLuxEaxnaF5GxLhTsCbd7aQOLQ8O5/xXj1pbU4ZJelcFo8RHuxoV9zXQBPe+ZVPTCA1ZuXYnsnmYAnT10YtcR3bHvoyVGUYvHLUBWLz5wlL4LEL1PmM7pHV9+3t5Oc4eMZIQeHARWNicYc/RqnGYxugCTUKEN+t3Y6yzDcq2cA/8WWaPZbqT3hXesLbT9Fc4yrwKmlhjmD/mUV6WIOOY1tu3nUv6z3Bb4ZQsugKy+CHGHAukaHoUZUxKX0hNmwp82Q5OSda56xM7vSQ5Vyz6CfdZXfj4JLV/J+j0bE/AJYTO/D457+W/+wMkJ9kU/owxGxYnQklo0ncKmbx+PDvc9LEM8rRK2q6Z4odV+ySQ1IhUTZDvJyXBQYvAb5I8L6bnmgnCwLHI0c5J3EgrwGfTq7rFRDuiLjWWOkn4CQ9D/aWrVj7xq2t8kCdacZsN5LVG9yXGGBcprEpolcW0FnRPXUf8sS/x02lsOkv532yOs6iuHUpx0mxqlV5eiN6X62uk/wUPPAzonzaRchLHLXXC9RMRPOz9Ff9YwvZfaXXTSPZCM0A12SYbKumeJDRuChZmdJUg3ru5olrOVu+RR7o4xhF6pwQ3UFZBwtrL0uvkIBGlktjmXUAzQti6bE0WMnIaaqUiFsuv40vFHTiiI2TSpO4k56d9s8RIC56SKk6AbMbqgz6CGOkZaSPWIdfsln0m30geCkDvq2u6eY6Q/cUW0y1wXevmILYEpANfBljMJSUBkgmwNG8rWrRwdq6nb6oAMWLjuymEtkUfWFYU3yFvxAQHYWsVblpOEK6GeF5dNEu/AuHDU/If6lSbu1htVpwkLTsHBIVBxZYsNZoT6OsX0xKa54i2fEhOi0riqKe6XA3rFCBazVcFRNkarXW6+q9NyDL7wmLd7xUgWF3v7BKVXDJ+jC7Cwobg6nnfwNmCqcrU4t4cqDgk9QlPYpyAQ//lYIPd+oJEzHv8uKnYqtYpZrstynXVEtT6evlwXMQLnQDJFCygi355LAhrLoCruTSEgsUh9jLLgdlmwJPT1Vvicd9xaaJFCEhPlsKxknVK1rG3Zpp4uX4YzLDkQ38hW/IeRhZ5bbx6NELvfGZ7AXQ040bgR5y2kMymGtrsLNWT3C7EJHAjo5MBil/QDe21tdapkEiampZK1jwmGoyQiOZvwdfKFGy7p5H77U9yemk8yDB6aj/zZSn05uzOc3lYnk+9A4B5opMLniaUxfa42ohK1lzSmAWcmZg5OQ8L2gp+5pGhmS3PyWhTnAe5J0WHDPKss1U9t5tREbgbvDFhoLzrhBaH4DBTHkTFml6PYQWw/zNQmoOMsBjMi2gOY+vTwt9IeUSSvziWhJ6BifVJ6lF7BN7l1+0+RVpi3qImXctb7TwfCif4+wdu2RjbheyPfp1KP2AFW+FCWAbKk9XC0wXwh83stFngBYPh0GOkT6DG1ZfpQRRl2HyW6zzr8e1mEfxqOBmlzwPbCDQQpX/iu/wrf5mS3AoLzBou7CVsKI6Zwkd5JeVuxICgSbQsikKEdRmSp7lBJXJkefa9jpTQu7pUdbQoYZ+yjZSlUdS73jDotTFu/J5hLLYYfejyStU5kfhLsKEtg1niZ8ra2zQNUu+PKUJ6S+3yBXOvGCmMYr+5NSe3JAwXykEGZNqLhBol0aR19c91LZiqReimWL18jAwtVARhmJVZ7W37eDsTaJ0AUufo58UFqkEXojii0ekQevbsLhpT7r3mcsZ52pTaO+5h71uL0QR+i+9G7/mq6q3ntszbUv27oPPs9Io3bXcYFfGA7svhxDG81WWKCw9xFtx1EXXV/u+UB+JkUOXKtVRIi7/0k0Ci5BIPKnKrh7MsgFrJRI1mfCDK7cayHdz1U91z3cqa/RoX0gBtN6Spd4us0ENCIncYzBtSubaqihOsmlIkO6iXMdKh0I6F4WX7PwaIQQEUo54Ib/7WCDRGYJYjqYtTK6zcCCwt4lelJtx46UHIJ/eKLzUADLi8+fK2jXI1Ogc1bFTdKxJHyNKIUiVirjWuYfO+aCBH+QXFbONVeBCwst3wgUrLrANYvW959J3gWXwGZJDW/GJMfjEkG/EK3JY536rF1CdYXViGtMC89GxG6SEvDLBnZfgZYwopN8eKIBodOLlw12fM8lhQV6SXzyI47gf97x2J9yWW2jeWyiVPPtquwcledCUcZVvmhGZylKHriJOzJTN5OwcxNat2xbVp/ks5oc9Hg7NV/5diRyWBoyDnNF5jLSZtPA9sw8XwZYrV8nyD0hDggN4oyc5cFDIInrNUtA361hyVlykfzX91kYRXiiswVjpkgh7SHPwS/JSKwO0keVr2YDSFoVXKKwyxvdtiAIrNaQzQjdygPIE0oXEhjT80rtd+PGqj+jNtKi3niWk4OJXyby/ond3W4t/Qj+ufmnlnOdKpOE1FLoPoNnMF0EN9NUPCPBJE4vxKDxiwG05PdsN4dHF0NRu1LLzdBZwDJ7D+77prJlRwEttfFezpwNxpPZaxfXJDHlHKrMC8GjCID4Vyi/8LccI/x1ZLramrI1P76q1oVRLzIDc7GjGKdrkVH1E//0S0nr+TqrCzR8bJHY5/MxaSCTCFjJphmAzLUv0zpGu59NUcbAQYzZLFuJKxcNjUFfqKthy2gh3/VvJJ+g/1bFu+HtKL6rTfXrTBsR/DpN2RsGruygSnKjm9bWk42J2JEcO2RgeYkZ3AI2EVkvPUWqbj41MMPmSIVHUdBLGsoo/9BWH/sLNd/X6qbNPSNrMU7Gb7cNhFhUc5k9uxWWplmQUVhZku9AZkyXrwEDMvtxDGBHMcWNdJzejXKNhL1A4pFHDyALUPyN7mlnelBH7ZzyKbqYFEkDeqNDYk6J8Ht/
*/